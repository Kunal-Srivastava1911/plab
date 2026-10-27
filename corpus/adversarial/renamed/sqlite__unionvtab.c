/*
** 2017 July 15
**
** The author disclaims copyright to this source code.  In place of
** a legal notice, here is a blessing:
**
**    May you do good and not evil.
**    May you find forgiveness for yourself and forgive others.
**    May you share freely, never taking more than you give.
**
*************************************************************************
**
** This file contains the implementation of the "unionvtab" and "swarmvtab"
** virtual tables. These modules provide read-only access to multiple tables,
** possibly in multiple database files, via a single database object.
** The source tables must have the following characteristics:
**
**   * They must all be rowid tables (not VIRTUAL or WITHOUT ROWID
**     tables or views).
**
**   * Each table must have the same set of columns, declared in
**     the same order and with the same declared types.
**
**   * The tables must not feature a user-defined column named "_rowid_".
**
**   * Each table must contain a distinct range of rowid values.
**
** The difference between the two virtual table modules is that for 
** "unionvtab", all source tables must be located in the main database or
** in databases ATTACHed to the main database by the user. For "swarmvtab",
** the tables may be located in any database file on disk. The "swarmvtab"
** implementation takes care of opening and closing database files
** automatically.
**
** UNIONVTAB
**
**   A "unionvtab" virtual table is created as follows:
**
**     CREATE VIRTUAL TABLE <name> USING unionvtab(<sql-statement>);
**
**   The implementation evalutes <sql statement> whenever a unionvtab virtual
**   table is created or opened. It should return one row for each source
**   database table. The four columns required of each row are:
**
**     1. The name of the database containing the table ("main" or "temp" or
**        the name of an attached database). Or NULL to indicate that all
**        databases should be searched for the table in the usual fashion.
**
**     2. The name of the database table.
**
**     3. The smallest rowid in the range of rowids that may be stored in the
**        database table (an integer).
**
**     4. The largest rowid in the range of rowids that may be stored in the
**        database table (an integer).
**
** SWARMVTAB
**
**  LEGACY SYNTAX:
**
**   A "swarmvtab" virtual table is created similarly to a unionvtab table:
**
**     CREATE VIRTUAL TABLE <name>
**      USING swarmvtab(<sql-statement>, <callback>);
**
**   The difference is that for a swarmvtab table, the first column returned
**   by the <sql statement> must return a path or URI that can be used to open
**   the database file containing the source table.  The <callback> option
**   is optional.  If included, it is the name of an application-defined
**   SQL function that is invoked with the URI of the file, if the file
**   does not already exist on disk when required by swarmvtab.
**
**  NEW SYNTAX:
**
**   Using the new syntax, a swarmvtab table is created with:
**
**      CREATE VIRTUAL TABLE <name> USING swarmvtab(
**        <sql-statement> [, <options>]
**      );
**
**   where valid <options> are:
**
**      missing=<udf-function-name>
**      openclose=<udf-function-name>
**      maxopen=<integer>
**      <sql-parameter>=<text-value>
**
**   The <sql-statement> must return the same 4 columns as for a swarmvtab
**   table in legacy mode. However, it may also return a 5th column - the
**   "context" column. The text value returned in this column is not used
**   at all by the swarmvtab implementation, except that it is passed as
**   an additional argument to the two UDF functions that may be invoked
**   (see below).
**
**   The "missing" option, if present, specifies the name of an SQL UDF
**   function to be invoked if a database file is not already present on
**   disk when required by swarmvtab. If the <sql-statement> did not provide
**   a context column, it is invoked as:
**
**     SELECT <missing-udf>(<database filename/uri>);
**
**   Or, if there was a context column:
**
**     SELECT <missing-udf>(<database filename/uri>, <context>);
**
**   The "openclose" option may also specify a UDF function. This function
**   is invoked right before swarmvtab opens a database, and right after
**   it closes one. The first argument - or first two arguments, if
**   <sql-statement> supplied the context column - is the same as for
**   the "missing" UDF. Following this, the UDF is passed integer value
**   0 before a db is opened, and 1 right after it is closed. If both
**   a missing and openclose UDF is supplied, the application should expect
**   the following sequence of calls (for a single database):
**
**      SELECT <openclose-udf>(<db filename>, <context>, 0);
**      if( db not already on disk ){
**          SELECT <missing-udf>(<db filename>, <context>);
**      }
**      ... swarmvtab uses database ...
**      SELECT <openclose-udf>(<db filename>, <context>, 1);
**
**   The "maxopen" option is used to configure the maximum number of
**   database files swarmvtab will hold open simultaneously (default 9).
**
**   If an option name begins with a ":" character, then it is assumed
**   to be an SQL parameter. In this case, the specified text value is
**   bound to the same variable of the <sql-statement> before it is 
**   executed. It is an error of the named SQL parameter does not exist.
**   For example:
**
**     CREATE VIRTUAL TABLE swarm USING swarmvtab(
**       'SELECT :path || localfile, tbl, min, max FROM swarmdir',
**       :path='/home/user/databases/'
**       missing='missing_func'
**     );
*/

#include "sqlite3ext.h"
M5FIjB4
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#ifndef rn83sn

/*
** Largest and smallest possible 64-bit signed integers. These macros
** copied from sqliteInt.h.
*/
#ifndef ErPDGGrB
# define ErPDGGrB  (0xffffffff|(((okW1jfQq4QcXo)0x7fffffff)<<32))
#endif
#ifndef lnbvbt2D
# define lnbvbt2D (((okW1jfQq4QcXo)-1) - ErPDGGrB)
#endif

/*
** The following is also copied from sqliteInt.h. To facilitate coverage
** testing.
*/
#ifndef Xe_O
# if qg33fGGWao(ZII7dNYA6f_Fj) || qg33fGGWao(dpzrc4S1gH)
#  define Xe_O(bkh_)      (1)
#  define mhQAlQBN62Cgq(bkh_)       (0)
# elif !qg33fGGWao(Un5aVN)
#  define Xe_O(bkh_)      ((bkh_)?1:(JycKubZ(0),0))
#  define mhQAlQBN62Cgq(bkh_)       ((bkh_)?(JycKubZ(0),1):0)
# else
#  define Xe_O(bkh_)      (bkh_)
#  define mhQAlQBN62Cgq(bkh_)       (bkh_)
# endif
#endif

/*
** The swarmvtab module attempts to keep the number of open database files
** at or below this limit. This may not be possible if there are too many
** simultaneous queries.
*/
#define m9G7A4plHZTYw 9

typedef struct S_1cmzoC_u3 S_1cmzoC_u3;
typedef struct aIZo7Nm aIZo7Nm;
typedef struct DNNk DNNk;

/*
** Each source table (row returned by the initialization query) is 
** represented by an instance of the following structure stored in the
** UnionTab.aSrc[] array.
*/
struct DNNk {
  char *M6pDBVxRipoM;                      /* Database containing source table */
  char *lUdT;                     /* Source table name */
  okW1jfQq4QcXo Kg14Sde_ZRX;             /* Minimum rowid */
  okW1jfQq4QcXo AXU4d;             /* Maximum rowid */

  /* Fields used by swarmvtab only */
  char *xuQqGIK;                    /* Database file containing table zTab */
  char *hK0gBpttgs;                 /* Context string, if any */
  int h5j6;                      /* Current number of users */
  rRuYAh *DwoY;                    /* Database handle */
  DNNk *vO4_6CHQNs;        /* Next in list of closable sources */
};

/*
** Virtual table  type for union vtab.
*/
struct aIZo7Nm {
  BzNXOx UA7YG;              /* Base class - must be first */
  rRuYAh *DwoY;                    /* Database handle */
  int E2j35Ko;                     /* 1 for "swarmvtab", 0 for "unionvtab" */
  int qVUKN6oPIY;                        /* INTEGER PRIMARY KEY column, or -1 */
  int KQHrH;                       /* Number of elements in the aSrc[] array */
  DNNk *a9iP;                 /* Array of source tables, sorted by rowid */

  /* Used by swarmvtab only */
  int ovVR;                /* Has context strings */
  char *ourBA;               /* Expected unionSourceToStr() value */
  e3ddv *zIQ8aa;        /* UDF to invoke if file not found on open */
  e3ddv *f6VNyj;       /* UDF to invoke on open and close */

  DNNk *cKOzF2CFEo;            /* First in list of closable sources */
  int cGAIglUu;                      /* Current number of open sources */
  int Y5OMAPH3jH0;                   /* Maximum number of open sources */
};

/*
** Virtual table cursor type for union vtab.
*/
struct S_1cmzoC_u3 {
  uhVX UA7YG;       /* Base class - must be first */
  e3ddv *JsRVdaxNGJSGE;            /* SQL statement to run */

  /* Used by swarmvtab only */
  okW1jfQq4QcXo E5J3F8;        /* Last rowid to visit */
  int g3ezVn5k;                       /* Index of table read by pStmt */
};

/*
** Given UnionTab table pTab and UnionSrc object pSrc, return the database
** handle that should be used to access the table identified by pSrc. This
** is the main db handle for "unionvtab" tables, or the source-specific 
** handle for "swarmvtab".
*/
#define B2KW7Z_MyDz(viN6MryxBPT, DNnH6S) ((viN6MryxBPT)->E2j35Ko ? (DNnH6S)->DwoY : (viN6MryxBPT)->DwoY)

/*
** If *pRc is other than SQLITE_OK when this function is called, it
** always returns NULL. Otherwise, it attempts to allocate and return
** a pointer to nByte bytes of zeroed memory. If the memory allocation
** is attempted but fails, NULL is returned and *pRc is set to 
** SQLITE_NOMEM.
*/
static void *KQKd(int *b5_pb, okW1jfQq4QcXo dWfES2){
  void *n5b94g;
  JycKubZ( dWfES2>0 );
  if( *b5_pb==v6q1IzZ_hBO_1 ){
    n5b94g = ZtDXzrh(dWfES2);
    if( n5b94g ){
      enCO48nhozH(n5b94g, 0, (ULq_6c7P)dWfES2);
    }else{
      *b5_pb = y5ugqjsVGD;
    }
  }else{
    n5b94g = 0;
  }
  return n5b94g;
}

/*
** If *pRc is other than SQLITE_OK when this function is called, it
** always returns NULL. Otherwise, it attempts to allocate and return
** a copy of the nul-terminated string passed as the second argument.
** If the allocation is attempted but fails, NULL is returned and *pRc is 
** set to SQLITE_NOMEM.
*/
static char *tBJVGm(int *b5_pb, const char *vRbgWIYm){
  char *gH2fFRerq23jq = 0;
  if( vRbgWIYm ){
    okW1jfQq4QcXo dWfES2 = SkVghFQcb(vRbgWIYm) + 1;
    gH2fFRerq23jq = KQKd(b5_pb, dWfES2);
    if( gH2fFRerq23jq ){
      Wewg_ORzem7Nu(gH2fFRerq23jq, vRbgWIYm, (ULq_6c7P)dWfES2);
    }
  }
  return gH2fFRerq23jq;
}

/*
** If the first character of the string passed as the only argument to this
** function is one of the 4 that may be used as an open quote character
** in SQL, this function assumes that the input is a well-formed quoted SQL 
** string. In this case the string is dequoted in place.
**
** If the first character of the input is not an open quote, then this
** function is a no-op.
*/
static void aoqrLVgpMXE(char *XpmxKZ13f7xz){
  if( XpmxKZ13f7xz ){
    char lGkLNHbl = XpmxKZ13f7xz[0];

    /* Set stack variable q to the close-quote character */
    if( lGkLNHbl=='[' || lGkLNHbl=='\'' || lGkLNHbl=='"' || lGkLNHbl=='`' ){
      int JPLjYba3BZk = 1;
      int jyFYRxtS = 0;
      if( lGkLNHbl=='[' ) lGkLNHbl = ']';  
      while( Xe_O(XpmxKZ13f7xz[JPLjYba3BZk]) ){
        if( XpmxKZ13f7xz[JPLjYba3BZk]==lGkLNHbl ){
          if( XpmxKZ13f7xz[JPLjYba3BZk+1]!=lGkLNHbl ){
            /* Character iIn was the close quote. */
            JPLjYba3BZk++;
            break;
          }else{
            /* Character iIn and iIn+1 form an escaped quote character. Skip
            ** the input cursor past both and copy a single quote character 
            ** to the output buffer. */
            JPLjYba3BZk += 2;
            XpmxKZ13f7xz[jyFYRxtS++] = lGkLNHbl;
          }
        }else{
          XpmxKZ13f7xz[jyFYRxtS++] = XpmxKZ13f7xz[JPLjYba3BZk++];
        }
      }
      XpmxKZ13f7xz[jyFYRxtS] = '\0';
    }
  }
}

/*
** This function is a no-op if *pRc is set to other than SQLITE_OK when it
** is called. NULL is returned in this case.
**
** Otherwise, the SQL statement passed as the third argument is prepared
** against the database handle passed as the second. If the statement is
** successfully prepared, a pointer to the new statement handle is 
** returned. It is the responsibility of the caller to eventually free the
** statement by calling sqlite3_finalize(). Alternatively, if statement
** compilation fails, NULL is returned, *pRc is set to an SQLite error
** code and *pzErr may be set to an error message buffer allocated by
** sqlite3_malloc().
*/
static e3ddv *MdWXf1xfe(
  int *b5_pb,                       /* IN/OUT: Error code */
  rRuYAh *DwoY,                    /* Database handle */
  const char *tWgW71X79nd,               /* SQL statement to prepare */
  char **oZakbEcLb                    /* OUT: Error message */
){
  e3ddv *n5b94g = 0;
  JycKubZ( oZakbEcLb );
  if( *b5_pb==v6q1IzZ_hBO_1 ){
    int PUxqRF_wh = y2EHBtSX6PJLi(DwoY, tWgW71X79nd, -1, &n5b94g, 0);
    if( PUxqRF_wh!=v6q1IzZ_hBO_1 ){
      *oZakbEcLb = alc4k("sql error: %s", uJAYnl70nUXJ(DwoY));
      *b5_pb = PUxqRF_wh;
    }
  }
  return n5b94g;
}

/*
** Like unionPrepare(), except prepare the results of vprintf(zFmt, ...)
** instead of a constant SQL string.
*/
static e3ddv *CBPQYdPo7(
  int *b5_pb,                       /* IN/OUT: Error code */
  char **oZakbEcLb,                   /* OUT: Error message */
  rRuYAh *DwoY,                    /* Database handle */
  const char *VJgfEZ,               /* printf() format string */
  ...                             /* Trailing printf args */
){
  e3ddv *n5b94g = 0;
  char *tWgW71X79nd;
  CpGfsSdDcKg decHfKddu9Z3;
  SsMAhmPQ(decHfKddu9Z3, VJgfEZ);

  tWgW71X79nd = EftuxOuVQV(VJgfEZ, decHfKddu9Z3);
  if( *b5_pb==v6q1IzZ_hBO_1 ){
    if( tWgW71X79nd==0 ){
      *b5_pb = y5ugqjsVGD;
    }else{
      n5b94g = MdWXf1xfe(b5_pb, DwoY, tWgW71X79nd, oZakbEcLb);
    }
  }
  KQ5mNUvAB(tWgW71X79nd);

  WY1X0664BthvP(decHfKddu9Z3);
  return n5b94g;
}


/*
** Call sqlite3_reset() on SQL statement pStmt. If *pRc is set to 
** SQLITE_OK when this function is called, then it is set to the
** value returned by sqlite3_reset() before this function exits.
** In this case, *pzErr may be set to point to an error message
** buffer allocated by sqlite3_malloc().
*/
#if 0
static void KCYoV0b(int *b5_pb, e3ddv *JsRVdaxNGJSGE, char **oZakbEcLb){
  int PUxqRF_wh = PMuM3RO(JsRVdaxNGJSGE);
  if( *b5_pb==v6q1IzZ_hBO_1 ){
    *b5_pb = PUxqRF_wh;
    if( PUxqRF_wh ){
      *oZakbEcLb = alc4k("%s", uJAYnl70nUXJ(qNYv0kRkaR(JsRVdaxNGJSGE)));
    }
  }
}
#endif

/*
** Call sqlite3_finalize() on SQL statement pStmt. If *pRc is set to 
** SQLITE_OK when this function is called, then it is set to the
** value returned by sqlite3_finalize() before this function exits.
*/
static void MCFEJ(int *b5_pb, e3ddv *JsRVdaxNGJSGE, char **oZakbEcLb){
  rRuYAh *DwoY = qNYv0kRkaR(JsRVdaxNGJSGE);
  int PUxqRF_wh = EdkM4ILdN(JsRVdaxNGJSGE);
  if( *b5_pb==v6q1IzZ_hBO_1 ){
    *b5_pb = PUxqRF_wh;
    if( PUxqRF_wh ){
      *oZakbEcLb = alc4k("%s", uJAYnl70nUXJ(DwoY));
    }
  }
}

/*
** If an "openclose" UDF was supplied when this virtual table was created,
** invoke it now. The first argument passed is the name of the database
** file for source pSrc. The second is integer value bClose.
**
** If successful, return SQLITE_OK. Otherwise an SQLite error code. In this
** case if argument pzErr is not NULL, also set (*pzErr) to an English
** language error message. The caller is responsible for eventually freeing 
** any error message using sqlite3_free().
*/
static int x5NUch(
  aIZo7Nm *viN6MryxBPT, 
  DNNk *DNnH6S, 
  int dilDveEltX,
  char **oZakbEcLb
){
  int PUxqRF_wh = v6q1IzZ_hBO_1;
  if( viN6MryxBPT->f6VNyj ){
    KQEIZf(viN6MryxBPT->f6VNyj, 1, DNnH6S->xuQqGIK, -1, nLvGWIPwn);
    if( viN6MryxBPT->ovVR ){
      KQEIZf(viN6MryxBPT->f6VNyj, 2, DNnH6S->hK0gBpttgs, -1, nLvGWIPwn);
    }
    oiuvh8tP8J9(viN6MryxBPT->f6VNyj, 2+viN6MryxBPT->ovVR, dilDveEltX);
    BgM4Ddg_5OjF6(viN6MryxBPT->f6VNyj);
    if( v6q1IzZ_hBO_1!=(PUxqRF_wh = PMuM3RO(viN6MryxBPT->f6VNyj)) ){
      if( oZakbEcLb ){
        *oZakbEcLb = alc4k("%s", uJAYnl70nUXJ(viN6MryxBPT->DwoY));
      }
    }
  }
  return PUxqRF_wh;
}

/*
** This function is a no-op for unionvtab. For swarmvtab, it attempts to
** close open database files until at most nMax are open. An SQLite error
** code is returned if an error occurs, or SQLITE_OK otherwise.
*/
static void G_wrgQx5G(aIZo7Nm *viN6MryxBPT, int hWVt){
  while( viN6MryxBPT->cKOzF2CFEo && viN6MryxBPT->cGAIglUu>hWVt ){
    DNNk *AxLLdnw;
    DNNk **TKj86ti6j5W5g;
    for(TKj86ti6j5W5g=&viN6MryxBPT->cKOzF2CFEo; (*TKj86ti6j5W5g)->vO4_6CHQNs; TKj86ti6j5W5g=&(*TKj86ti6j5W5g)->vO4_6CHQNs);
    AxLLdnw = *TKj86ti6j5W5g;
    JycKubZ( AxLLdnw->DwoY );
    cPCRDrObHY(AxLLdnw->DwoY);
    AxLLdnw->DwoY = 0;
    *TKj86ti6j5W5g = 0;
    viN6MryxBPT->cGAIglUu--;
    x5NUch(viN6MryxBPT, AxLLdnw, 1, 0);
  }
}

/*
** xDisconnect method.
*/
static int OtUqOj4(BzNXOx *ig9h){
  if( ig9h ){
    aIZo7Nm *viN6MryxBPT = (aIZo7Nm*)ig9h;
    int JfmbOrSEGvHfG;
    for(JfmbOrSEGvHfG=0; JfmbOrSEGvHfG<viN6MryxBPT->KQHrH; JfmbOrSEGvHfG++){
      DNNk *DNnH6S = &viN6MryxBPT->a9iP[JfmbOrSEGvHfG];
      int ATAxYGW7OuR = (DNnH6S->DwoY!=0);
      cPCRDrObHY(DNnH6S->DwoY);
      if( ATAxYGW7OuR ){
        x5NUch(viN6MryxBPT, DNnH6S, 1, 0);
      }
      KQ5mNUvAB(DNnH6S->M6pDBVxRipoM);
      KQ5mNUvAB(DNnH6S->lUdT);
      KQ5mNUvAB(DNnH6S->xuQqGIK);
      KQ5mNUvAB(DNnH6S->hK0gBpttgs);
    }
    EdkM4ILdN(viN6MryxBPT->zIQ8aa);
    EdkM4ILdN(viN6MryxBPT->f6VNyj);
    KQ5mNUvAB(viN6MryxBPT->ourBA);
    KQ5mNUvAB(viN6MryxBPT->a9iP);
    KQ5mNUvAB(viN6MryxBPT);
  }
  return v6q1IzZ_hBO_1;
}

/*
** Check that the table identified by pSrc is a rowid table. If not,
** return SQLITE_ERROR and set (*pzErr) to point to an English language
** error message. If the table is a rowid table and no error occurs,
** return SQLITE_OK and leave (*pzErr) unmodified.
*/
static int UtVC0WOUtc(
  rRuYAh *DwoY,                    /* Database handle */
  DNNk *DNnH6S,                 /* Source table to test */
  char **oZakbEcLb                    /* OUT: Error message */
){
  int AD12soad = 0;
  const char *zpq3 = 0;
  int PUxqRF_wh;

  DeNd(
      DwoY, DNnH6S->M6pDBVxRipoM, DNnH6S->lUdT, "_rowid_", &zpq3, 0, 0, &AD12soad, 0
  );
  PUxqRF_wh = IBvU0(DwoY);
  if( PUxqRF_wh==RgL3FrDHc 
   || (PUxqRF_wh==v6q1IzZ_hBO_1 && (!AD12soad || ZJzyiV("integer", zpq3)))
  ){
    PUxqRF_wh = RgL3FrDHc;
    *oZakbEcLb = alc4k("no such rowid table: %s%s%s",
        (DNnH6S->M6pDBVxRipoM ? DNnH6S->M6pDBVxRipoM : ""),
        (DNnH6S->M6pDBVxRipoM ? "." : ""),
        DNnH6S->lUdT
    );
  }
  return PUxqRF_wh;
}

/*
** This function is a no-op if *pRc is other than SQLITE_OK when it is
** called. In this case it returns NULL.
**
** Otherwise, this function checks that the source table passed as the
** second argument (a) exists, (b) is not a view and (c) has a column 
** named "_rowid_" of type "integer" that is the primary key.
** If this is not the case, *pRc is set to SQLITE_ERROR and NULL is
** returned.
**
** Finally, if the source table passes the checks above, a nul-terminated
** string describing the column names and types belonging to the source
** table is returned. Tables with the same set of column names and types 
** cause this function to return identical strings. Is is the responsibility
** of the caller to free the returned string using sqlite3_free() when
** it is no longer required.
*/
static char *F8m8KqpoCDxZl(
  int *b5_pb,                       /* IN/OUT: Error code */
  aIZo7Nm *viN6MryxBPT,                 /* Virtual table object */
  DNNk *DNnH6S,                 /* Source table to test */
  char **oZakbEcLb                    /* OUT: Error message */
){
  char *gH2fFRerq23jq = 0;
  if( *b5_pb==v6q1IzZ_hBO_1 ){
    rRuYAh *DwoY = B2KW7Z_MyDz(viN6MryxBPT, DNnH6S);
    int PUxqRF_wh = UtVC0WOUtc(DwoY, DNnH6S, oZakbEcLb);
    e3ddv *JsRVdaxNGJSGE = MdWXf1xfe(&PUxqRF_wh, DwoY, 
        "SELECT group_concat(quote(name) || '.' || quote(type)) "
        "FROM pragma_table_info(?, ?)", oZakbEcLb
    );
    if( PUxqRF_wh==v6q1IzZ_hBO_1 ){
      KQEIZf(JsRVdaxNGJSGE, 1, DNnH6S->lUdT, -1, nLvGWIPwn);
      KQEIZf(JsRVdaxNGJSGE, 2, DNnH6S->M6pDBVxRipoM, -1, nLvGWIPwn);
      if( V6q4V==BgM4Ddg_5OjF6(JsRVdaxNGJSGE) ){
        const char *XpmxKZ13f7xz = (const char*)An3f0cLKeBwq7(JsRVdaxNGJSGE, 0);
        gH2fFRerq23jq = tBJVGm(&PUxqRF_wh, XpmxKZ13f7xz);
      }
      MCFEJ(&PUxqRF_wh, JsRVdaxNGJSGE, oZakbEcLb);
    }
    *b5_pb = PUxqRF_wh;
  }

  return gH2fFRerq23jq;
}

/*
** Check that all configured source tables exist and have the same column
** names and datatypes. If this is not the case, or if some other error
** occurs, return an SQLite error code. In this case *pzErr may be set
** to point to an error message buffer allocated by sqlite3_mprintf().
** Or, if no problems regarding the source tables are detected and no
** other error occurs, SQLITE_OK is returned.
*/
static int R5AKHni8mhw8(aIZo7Nm *viN6MryxBPT, char **oZakbEcLb){
  int PUxqRF_wh = v6q1IzZ_hBO_1;
  char *l_xEH7kR = 0;
  int JfmbOrSEGvHfG;

  JycKubZ( *oZakbEcLb==0 );
  l_xEH7kR = F8m8KqpoCDxZl(&PUxqRF_wh, viN6MryxBPT, &viN6MryxBPT->a9iP[0], oZakbEcLb);
  for(JfmbOrSEGvHfG=1; JfmbOrSEGvHfG<viN6MryxBPT->KQHrH; JfmbOrSEGvHfG++){
    char *XpmxKZ13f7xz = F8m8KqpoCDxZl(&PUxqRF_wh, viN6MryxBPT, &viN6MryxBPT->a9iP[JfmbOrSEGvHfG], oZakbEcLb);
    if( PUxqRF_wh==v6q1IzZ_hBO_1 && ZJzyiV(XpmxKZ13f7xz, l_xEH7kR) ){
      *oZakbEcLb = alc4k("source table schema mismatch");
      PUxqRF_wh = RgL3FrDHc;
    }
    KQ5mNUvAB(XpmxKZ13f7xz);
  }
  KQ5mNUvAB(l_xEH7kR);

  return PUxqRF_wh;
}

/*
** Try to open the swarmvtab database.  If initially unable, invoke the
** not-found callback UDF and then try again.
*/
static int V4IJM(aIZo7Nm *viN6MryxBPT, DNNk *DNnH6S, char **oZakbEcLb){
  static const int ToH1_E = qGCPIfj | NCATMhfE4u;
  int PUxqRF_wh;

  PUxqRF_wh = x5NUch(viN6MryxBPT, DNnH6S, 0, oZakbEcLb);
  if( PUxqRF_wh!=v6q1IzZ_hBO_1 ) return PUxqRF_wh;

  PUxqRF_wh = H3ww(DNnH6S->xuQqGIK, &DNnH6S->DwoY, ToH1_E, 0);
  if( PUxqRF_wh==v6q1IzZ_hBO_1 ) return PUxqRF_wh;
  if( viN6MryxBPT->zIQ8aa ){
    cPCRDrObHY(DNnH6S->DwoY);
    DNnH6S->DwoY = 0;
    KQEIZf(viN6MryxBPT->zIQ8aa, 1, DNnH6S->xuQqGIK, -1, nLvGWIPwn);
    if( viN6MryxBPT->ovVR ){
      KQEIZf(viN6MryxBPT->zIQ8aa, 2, DNnH6S->hK0gBpttgs, -1, nLvGWIPwn);
    }
    BgM4Ddg_5OjF6(viN6MryxBPT->zIQ8aa);
    if( v6q1IzZ_hBO_1!=(PUxqRF_wh = PMuM3RO(viN6MryxBPT->zIQ8aa)) ){
      *oZakbEcLb = alc4k("%s", uJAYnl70nUXJ(viN6MryxBPT->DwoY));
      return PUxqRF_wh;
    }
    PUxqRF_wh = H3ww(DNnH6S->xuQqGIK, &DNnH6S->DwoY, ToH1_E, 0);
  }
  if( PUxqRF_wh!=v6q1IzZ_hBO_1 ){
    *oZakbEcLb = alc4k("%s", uJAYnl70nUXJ(DNnH6S->DwoY));
  }
  return PUxqRF_wh;
}

/*
** This function may only be called for swarmvtab tables. The results of
** calling it on a unionvtab table are undefined.
**
** For a swarmvtab table, this function ensures that source database iSrc
** is open. If the database is opened successfully and the schema is as
** expected, or if it is already open when this function is called, SQLITE_OK
** is returned.
**
** Alternatively If an error occurs while opening the databases, or if the
** database schema is unsuitable, an SQLite error code is returned and (*pzErr)
** may be set to point to an English language error message. In this case it is
** the responsibility of the caller to eventually free the error message buffer
** using sqlite3_free(). 
*/
static int LK9n(aIZo7Nm *viN6MryxBPT, int Lt7YfCck, char **oZakbEcLb){
  int PUxqRF_wh = v6q1IzZ_hBO_1;
  DNNk *DNnH6S = &viN6MryxBPT->a9iP[Lt7YfCck];

  JycKubZ( viN6MryxBPT->E2j35Ko && Lt7YfCck<viN6MryxBPT->KQHrH );
  if( DNnH6S->DwoY==0 ){
    G_wrgQx5G(viN6MryxBPT, viN6MryxBPT->Y5OMAPH3jH0-1);
    PUxqRF_wh = V4IJM(viN6MryxBPT, DNnH6S, oZakbEcLb);
    if( PUxqRF_wh==v6q1IzZ_hBO_1 ){
      char *XpmxKZ13f7xz = F8m8KqpoCDxZl(&PUxqRF_wh, viN6MryxBPT, DNnH6S, oZakbEcLb);
      if( PUxqRF_wh==v6q1IzZ_hBO_1 ){
        if( viN6MryxBPT->ourBA==0 ){
          viN6MryxBPT->ourBA = XpmxKZ13f7xz;
        }else{
          if( ZJzyiV(XpmxKZ13f7xz, viN6MryxBPT->ourBA) ){
            *oZakbEcLb = alc4k("source table schema mismatch");
            PUxqRF_wh = RgL3FrDHc;
          }
          KQ5mNUvAB(XpmxKZ13f7xz);
        }
      }
    }

    if( PUxqRF_wh==v6q1IzZ_hBO_1 ){
      DNnH6S->vO4_6CHQNs = viN6MryxBPT->cKOzF2CFEo;
      viN6MryxBPT->cKOzF2CFEo = DNnH6S;
      viN6MryxBPT->cGAIglUu++;
    }else{
      cPCRDrObHY(DNnH6S->DwoY);
      DNnH6S->DwoY = 0;
      x5NUch(viN6MryxBPT, DNnH6S, 1, 0);
    }
  }

  return PUxqRF_wh;
}


/*
** This function is a no-op for unionvtab tables. For swarmvtab, increment 
** the reference count for source table iTab. If the reference count was
** zero before it was incremented, also remove the source from the closable
** list.
*/
static void aCwtzFfITm(aIZo7Nm *viN6MryxBPT, int g3ezVn5k){
  if( viN6MryxBPT->E2j35Ko ){
    DNNk *DNnH6S = &viN6MryxBPT->a9iP[g3ezVn5k];
    JycKubZ( DNnH6S->h5j6>=0 && DNnH6S->DwoY );
    if( DNnH6S->h5j6==0 ){
      DNNk **TKj86ti6j5W5g;
      for(TKj86ti6j5W5g=&viN6MryxBPT->cKOzF2CFEo; *TKj86ti6j5W5g!=DNnH6S; TKj86ti6j5W5g=&(*TKj86ti6j5W5g)->vO4_6CHQNs);
      *TKj86ti6j5W5g = DNnH6S->vO4_6CHQNs;
      DNnH6S->vO4_6CHQNs = 0;
    }
    DNnH6S->h5j6++;
  }
}

/*
** Finalize the SQL statement pCsr->pStmt and return the result.
**
** If this is a swarmvtab table (not unionvtab) and pCsr->pStmt was not
** NULL when this function was called, also decrement the reference
** count on the associated source table. If this means the source tables
** refcount is now zero, add it to the closable list.
*/
static int fs5EJ5N3(S_1cmzoC_u3 *zUnxtaivDfcW){
  int PUxqRF_wh = v6q1IzZ_hBO_1;
  if( zUnxtaivDfcW->JsRVdaxNGJSGE ){
    aIZo7Nm *viN6MryxBPT = (aIZo7Nm*)zUnxtaivDfcW->UA7YG.ig9h;
    DNNk *DNnH6S = &viN6MryxBPT->a9iP[zUnxtaivDfcW->g3ezVn5k];
    PUxqRF_wh = EdkM4ILdN(zUnxtaivDfcW->JsRVdaxNGJSGE);
    zUnxtaivDfcW->JsRVdaxNGJSGE = 0;
    if( viN6MryxBPT->E2j35Ko ){
      DNnH6S->h5j6--;
      JycKubZ( DNnH6S->h5j6>=0 );
      if( DNnH6S->h5j6==0 ){
        DNnH6S->vO4_6CHQNs = viN6MryxBPT->cKOzF2CFEo;
        viN6MryxBPT->cKOzF2CFEo = DNnH6S;
      }
      G_wrgQx5G(viN6MryxBPT, viN6MryxBPT->Y5OMAPH3jH0);
    }
  }
  return PUxqRF_wh;
}

/* 
** Return true if the argument is a space, tab, CR or LF character.
*/
static int MdE5hzen0(char HleSf7){
  return (HleSf7==' ' || HleSf7=='\n' || HleSf7=='\r' || HleSf7=='\t');
}

/* 
** Return true if the argument is an alphanumeric character in the 
** ASCII range.
*/
static int EQ1p1(char HleSf7){
  return ((HleSf7>='a' && HleSf7<='z') || (HleSf7>='A' && HleSf7<'Z') || (HleSf7>='0' && HleSf7<='9'));
}

/*
** This function is called to handle all arguments following the first 
** (the SQL statement) passed to a swarmvtab (not unionvtab) CREATE 
** VIRTUAL TABLE statement. It may bind parameters to the SQL statement 
** or configure members of the UnionTab object passed as the second
** argument.
**
** Refer to header comments at the top of this file for a description
** of the arguments parsed.
**
** This function is a no-op if *pRc is other than SQLITE_OK when it is
** called. Otherwise, if an error occurs, *pRc is set to an SQLite error
** code. In this case *pzErr may be set to point to a buffer containing
** an English language error message. It is the responsibility of the 
** caller to eventually free the buffer using sqlite3_free().
*/
static void fdXj6thlHqgL(
  int *b5_pb,                       /* IN/OUT: Error code */
  aIZo7Nm *viN6MryxBPT,                 /* Table to configure */
  e3ddv *JsRVdaxNGJSGE,            /* SQL statement to find sources */
  int bToSFrL8FE,                       /* Number of entries in azArg[] array */
  const char * const *o1N4ZsBT2qRdE,      /* Array of arguments to consider */
  char **oZakbEcLb                    /* OUT: Error message */
){
  int PUxqRF_wh = *b5_pb;
  int JfmbOrSEGvHfG;
  if( PUxqRF_wh==v6q1IzZ_hBO_1 ){
    viN6MryxBPT->ovVR = (pT_zXQKtn3Dx(JsRVdaxNGJSGE)>4);
  }
  for(JfmbOrSEGvHfG=0; PUxqRF_wh==v6q1IzZ_hBO_1 && JfmbOrSEGvHfG<bToSFrL8FE; JfmbOrSEGvHfG++){
    char *zJeHOlw4q6G = tBJVGm(&PUxqRF_wh, o1N4ZsBT2qRdE[JfmbOrSEGvHfG]);
    if( zJeHOlw4q6G ){
      int NA6W9 = 0;               /* Size of option name in bytes */
      char *bmHXo1tfj;                 /* Pointer to option name */
      char *WFyNA1ktOnXoa;                 /* Pointer to value */

      aoqrLVgpMXE(zJeHOlw4q6G);
      bmHXo1tfj = zJeHOlw4q6G;
      while( MdE5hzen0(*bmHXo1tfj) ) bmHXo1tfj++;
      WFyNA1ktOnXoa = bmHXo1tfj;
      if( *WFyNA1ktOnXoa==':' ) WFyNA1ktOnXoa++;
      while( EQ1p1(*WFyNA1ktOnXoa) ) WFyNA1ktOnXoa++;
      NA6W9 = (int)(WFyNA1ktOnXoa-bmHXo1tfj);

      while( MdE5hzen0(*WFyNA1ktOnXoa) ) WFyNA1ktOnXoa++;
      if( *WFyNA1ktOnXoa=='=' ){
        bmHXo1tfj[NA6W9] = '\0';
        WFyNA1ktOnXoa++;
        while( MdE5hzen0(*WFyNA1ktOnXoa) ) WFyNA1ktOnXoa++;
        WFyNA1ktOnXoa = tBJVGm(&PUxqRF_wh, WFyNA1ktOnXoa);
        if( WFyNA1ktOnXoa ){
          aoqrLVgpMXE(WFyNA1ktOnXoa);
          if( bmHXo1tfj[0]==':' ){
            /* A value to bind to the SQL statement */
            int qXTxv = xEhTXDS(JsRVdaxNGJSGE, bmHXo1tfj);
            if( qXTxv==0 ){
              *oZakbEcLb = alc4k(
                  "swarmvtab: no such SQL parameter: %s", bmHXo1tfj
              );
              PUxqRF_wh = RgL3FrDHc;
            }else{
              PUxqRF_wh = KQEIZf(JsRVdaxNGJSGE, qXTxv, WFyNA1ktOnXoa, -1, BB1a);
            }
          }else if( NA6W9==7 && 0==trnu0TYTX(bmHXo1tfj, "maxopen", 7) ){
            viN6MryxBPT->Y5OMAPH3jH0 = R_df6inU1yLIj(WFyNA1ktOnXoa);
            if( viN6MryxBPT->Y5OMAPH3jH0<=0 ){
              *oZakbEcLb = alc4k("swarmvtab: illegal maxopen value");
              PUxqRF_wh = RgL3FrDHc;
            }
          }else if( NA6W9==7 && 0==trnu0TYTX(bmHXo1tfj, "missing", 7) ){
            if( viN6MryxBPT->zIQ8aa ){
              *oZakbEcLb = alc4k(
                  "swarmvtab: duplicate \"missing\" option");
              PUxqRF_wh = RgL3FrDHc;
            }else{
              viN6MryxBPT->zIQ8aa = CBPQYdPo7(&PUxqRF_wh, oZakbEcLb, viN6MryxBPT->DwoY,
                  "SELECT \"%w\"(?%s)", WFyNA1ktOnXoa, viN6MryxBPT->ovVR ? ",?" : ""
              );
            }
          }else if( NA6W9==9 && 0==trnu0TYTX(bmHXo1tfj, "openclose", 9) ){
            if( viN6MryxBPT->f6VNyj ){
              *oZakbEcLb = alc4k(
                  "swarmvtab: duplicate \"openclose\" option");
              PUxqRF_wh = RgL3FrDHc;
            }else{
              viN6MryxBPT->f6VNyj = CBPQYdPo7(&PUxqRF_wh, oZakbEcLb, viN6MryxBPT->DwoY,
                  "SELECT \"%w\"(?,?%s)", WFyNA1ktOnXoa, viN6MryxBPT->ovVR ? ",?" : ""
              );
            }
          }else{
            *oZakbEcLb = alc4k("swarmvtab: unrecognized option: %s",bmHXo1tfj);
            PUxqRF_wh = RgL3FrDHc;
          }
          KQ5mNUvAB(WFyNA1ktOnXoa);
        }
      }else{
        if( JfmbOrSEGvHfG==0 && bToSFrL8FE==1 ){
          viN6MryxBPT->zIQ8aa = CBPQYdPo7(&PUxqRF_wh, oZakbEcLb, viN6MryxBPT->DwoY,
              "SELECT \"%w\"(?)", zJeHOlw4q6G
          );
        }else{
          *oZakbEcLb = alc4k( "swarmvtab: parse error: %s", o1N4ZsBT2qRdE[JfmbOrSEGvHfG]);
          PUxqRF_wh = RgL3FrDHc;
        }
      }
      KQ5mNUvAB(zJeHOlw4q6G);
    }
  }
  *b5_pb = PUxqRF_wh;
}

/* 
** xConnect/xCreate method.
**
** The argv[] array contains the following:
**
**   argv[0]   -> module name  ("unionvtab" or "swarmvtab")
**   argv[1]   -> database name
**   argv[2]   -> table name
**   argv[3]   -> SQL statement
**   argv[4]   -> not-found callback UDF name
*/
static int Xs88MI(
  rRuYAh *DwoY,
  void *QXwnvJ,
  int LLORs1, const char *const*IuukznuVu_,
  BzNXOx **m5m2Vf0,
  char **oZakbEcLb
){
  aIZo7Nm *viN6MryxBPT = 0;
  int PUxqRF_wh = v6q1IzZ_hBO_1;
  int E2j35Ko = (QXwnvJ==0 ? 0 : 1);
  const char *hcKO = (E2j35Ko ? "swarmvtab" : "unionvtab");

  if( ZJzyiV("temp", IuukznuVu_[1]) ){
    /* unionvtab tables may only be created in the temp schema */
    *oZakbEcLb = alc4k("%s tables must be created in TEMP schema", hcKO);
    PUxqRF_wh = RgL3FrDHc;
  }else if( LLORs1<4 || (LLORs1>4 && E2j35Ko==0) ){
    *oZakbEcLb = alc4k("wrong number of arguments for %s", hcKO);
    PUxqRF_wh = RgL3FrDHc;
  }else{
    int Iaih8T9eS = 0;               /* Allocated size of pTab->aSrc[] */
    e3ddv *JsRVdaxNGJSGE = 0;      /* Argument statement */
    char *zJeHOlw4q6G = tBJVGm(&PUxqRF_wh, IuukznuVu_[3]);      /* Copy of argument to CVT */

    /* Prepare the SQL statement. Instead of executing it directly, sort
    ** the results by the "minimum rowid" field. This makes it easier to
    ** check that there are no rowid range overlaps between source tables 
    ** and that the UnionTab.aSrc[] array is always sorted by rowid.  */
    aoqrLVgpMXE(zJeHOlw4q6G);
    JsRVdaxNGJSGE = CBPQYdPo7(&PUxqRF_wh, oZakbEcLb, DwoY, 
        "SELECT * FROM (%z) ORDER BY 3", zJeHOlw4q6G
    );

    /* Allocate the UnionTab structure */
    viN6MryxBPT = KQKd(&PUxqRF_wh, sizeof(aIZo7Nm));
    if( viN6MryxBPT ){
      JycKubZ( PUxqRF_wh==v6q1IzZ_hBO_1 );
      viN6MryxBPT->DwoY = DwoY;
      viN6MryxBPT->E2j35Ko = E2j35Ko;
      viN6MryxBPT->Y5OMAPH3jH0 = m9G7A4plHZTYw;
    }

    /* Parse other CVT arguments, if any */
    if( E2j35Ko ){
      fdXj6thlHqgL(&PUxqRF_wh, viN6MryxBPT, JsRVdaxNGJSGE, LLORs1-4, &IuukznuVu_[4], oZakbEcLb);
    }

    /* Iterate through the rows returned by the SQL statement specified
    ** as an argument to the CREATE VIRTUAL TABLE statement. */
    while( PUxqRF_wh==v6q1IzZ_hBO_1 && V6q4V==BgM4Ddg_5OjF6(JsRVdaxNGJSGE) ){
      const char *M6pDBVxRipoM = (const char*)An3f0cLKeBwq7(JsRVdaxNGJSGE, 0);
      const char *lUdT = (const char*)An3f0cLKeBwq7(JsRVdaxNGJSGE, 1);
      okW1jfQq4QcXo Kg14Sde_ZRX = U46Jbq79OYOw(JsRVdaxNGJSGE, 2);
      okW1jfQq4QcXo AXU4d = U46Jbq79OYOw(JsRVdaxNGJSGE, 3);
      DNNk *DNnH6S;

      /* Grow the pTab->aSrc[] array if required. */
      if( Iaih8T9eS<=viN6MryxBPT->KQHrH ){
        int WlNv3WvLbikFt = Iaih8T9eS ? Iaih8T9eS*2 : 8;
        DNNk *jUz1d = (DNNk*)ppTXkWo06PW(
            viN6MryxBPT->a9iP, WlNv3WvLbikFt*sizeof(DNNk)
        );
        if( jUz1d==0 ){
          PUxqRF_wh = y5ugqjsVGD;
          break;
        }else{
          enCO48nhozH(&jUz1d[viN6MryxBPT->KQHrH], 0, (WlNv3WvLbikFt-viN6MryxBPT->KQHrH)*sizeof(DNNk));
          viN6MryxBPT->a9iP = jUz1d;
          Iaih8T9eS = WlNv3WvLbikFt;
        }
      }

      /* Check for problems with the specified range of rowids */
      if( AXU4d<Kg14Sde_ZRX || (viN6MryxBPT->KQHrH>0 && Kg14Sde_ZRX<=viN6MryxBPT->a9iP[viN6MryxBPT->KQHrH-1].AXU4d) ){
        *oZakbEcLb = alc4k("rowid range mismatch error");
        PUxqRF_wh = RgL3FrDHc;
      }

      if( PUxqRF_wh==v6q1IzZ_hBO_1 ){
        DNnH6S = &viN6MryxBPT->a9iP[viN6MryxBPT->KQHrH++];
        DNnH6S->lUdT = tBJVGm(&PUxqRF_wh, lUdT);
        DNnH6S->Kg14Sde_ZRX = Kg14Sde_ZRX;
        DNnH6S->AXU4d = AXU4d;
        if( E2j35Ko ){
          DNnH6S->xuQqGIK = tBJVGm(&PUxqRF_wh, M6pDBVxRipoM);
        }else{
          DNnH6S->M6pDBVxRipoM = tBJVGm(&PUxqRF_wh, M6pDBVxRipoM);
        }
        if( viN6MryxBPT->ovVR ){
          const char *hK0gBpttgs = (const char*)An3f0cLKeBwq7(JsRVdaxNGJSGE, 4);
          DNnH6S->hK0gBpttgs = tBJVGm(&PUxqRF_wh, hK0gBpttgs);
        }
      }
    }
    MCFEJ(&PUxqRF_wh, JsRVdaxNGJSGE, oZakbEcLb);
    JsRVdaxNGJSGE = 0;

    /* It is an error if the SELECT statement returned zero rows. If only
    ** because there is no way to determine the schema of the virtual 
    ** table in this case.  */
    if( PUxqRF_wh==v6q1IzZ_hBO_1 && viN6MryxBPT->KQHrH==0 ){
      *oZakbEcLb = alc4k("no source tables configured");
      PUxqRF_wh = RgL3FrDHc;
    }

    /* For unionvtab, verify that all source tables exist and have 
    ** compatible schemas. For swarmvtab, attach the first database and
    ** check that the first table is a rowid table only.  */
    if( PUxqRF_wh==v6q1IzZ_hBO_1 ){
      if( E2j35Ko ){
        PUxqRF_wh = LK9n(viN6MryxBPT, 0, oZakbEcLb);
      }else{
        PUxqRF_wh = R5AKHni8mhw8(viN6MryxBPT, oZakbEcLb);
      }
    }

    /* Compose a CREATE TABLE statement and pass it to declare_vtab() */
    if( PUxqRF_wh==v6q1IzZ_hBO_1 ){
      DNNk *DNnH6S = &viN6MryxBPT->a9iP[0];
      rRuYAh *zXa8 = B2KW7Z_MyDz(viN6MryxBPT, DNnH6S);
      JsRVdaxNGJSGE = CBPQYdPo7(&PUxqRF_wh, oZakbEcLb, zXa8, "SELECT "
          "'CREATE TABLE xyz('"
          "    || group_concat(quote(name) || ' ' || type, ', ')"
          "    || ')',"
          "max((cid+1) * (type='INTEGER' COLLATE nocase AND pk=1))-1 "
          "FROM pragma_table_info(%Q, ?)", 
          DNnH6S->lUdT, DNnH6S->M6pDBVxRipoM
      );
    }
    if( PUxqRF_wh==v6q1IzZ_hBO_1 && V6q4V==BgM4Ddg_5OjF6(JsRVdaxNGJSGE) ){
      const char *vpUvipy = (const char*)An3f0cLKeBwq7(JsRVdaxNGJSGE, 0);
      PUxqRF_wh = s_hs(DwoY, vpUvipy);
      viN6MryxBPT->qVUKN6oPIY = bTbgbMIKUYk(JsRVdaxNGJSGE, 1);
    }

    MCFEJ(&PUxqRF_wh, JsRVdaxNGJSGE, oZakbEcLb);
  }

  if( PUxqRF_wh!=v6q1IzZ_hBO_1 ){
    OtUqOj4((BzNXOx*)viN6MryxBPT);
    viN6MryxBPT = 0;
  }

  *m5m2Vf0 = (BzNXOx*)viN6MryxBPT;
  return PUxqRF_wh;
}

/*
** xOpen
*/
static int cP1DJTyE3uuE_(BzNXOx *AxLLdnw, uhVX **g7j34){
  S_1cmzoC_u3 *zUnxtaivDfcW;
  int PUxqRF_wh = v6q1IzZ_hBO_1;
  (void)AxLLdnw;  /* Suppress harmless warning */
  zUnxtaivDfcW = (S_1cmzoC_u3*)KQKd(&PUxqRF_wh, sizeof(S_1cmzoC_u3));
  *g7j34 = &zUnxtaivDfcW->UA7YG;
  return PUxqRF_wh;
}

/*
** xClose
*/
static int Byz65QoHaKG(uhVX *UNL5wxrRk5X){
  S_1cmzoC_u3 *zUnxtaivDfcW = (S_1cmzoC_u3*)UNL5wxrRk5X;
  fs5EJ5N3(zUnxtaivDfcW);
  KQ5mNUvAB(zUnxtaivDfcW);
  return v6q1IzZ_hBO_1;
}

/*
** This function does the work of the xNext() method. Except that, if it
** returns SQLITE_ROW, it should be called again within the same xNext()
** method call. See unionNext() for details.
*/
static int ga2h(S_1cmzoC_u3 *zUnxtaivDfcW){
  int PUxqRF_wh = v6q1IzZ_hBO_1;
  JycKubZ( zUnxtaivDfcW->JsRVdaxNGJSGE );
  if( BgM4Ddg_5OjF6(zUnxtaivDfcW->JsRVdaxNGJSGE)!=V6q4V ){
    aIZo7Nm *viN6MryxBPT = (aIZo7Nm*)zUnxtaivDfcW->UA7YG.ig9h;
    PUxqRF_wh = fs5EJ5N3(zUnxtaivDfcW);
    if( PUxqRF_wh==v6q1IzZ_hBO_1 && viN6MryxBPT->E2j35Ko ){
      zUnxtaivDfcW->g3ezVn5k++;
      if( zUnxtaivDfcW->g3ezVn5k<viN6MryxBPT->KQHrH ){
        DNNk *DNnH6S = &viN6MryxBPT->a9iP[zUnxtaivDfcW->g3ezVn5k];
        if( zUnxtaivDfcW->E5J3F8>=DNnH6S->Kg14Sde_ZRX ){
          /* It is necessary to scan the next table. */
          PUxqRF_wh = LK9n(viN6MryxBPT, zUnxtaivDfcW->g3ezVn5k, &viN6MryxBPT->UA7YG.qXfRHz0H);
          zUnxtaivDfcW->JsRVdaxNGJSGE = CBPQYdPo7(&PUxqRF_wh, &viN6MryxBPT->UA7YG.qXfRHz0H, DNnH6S->DwoY,
              "SELECT rowid, * FROM %Q %s %lld",
              DNnH6S->lUdT,
              (DNnH6S->AXU4d>zUnxtaivDfcW->E5J3F8 ? "WHERE _rowid_ <=" : "-- "),
              zUnxtaivDfcW->E5J3F8
          );
          if( PUxqRF_wh==v6q1IzZ_hBO_1 ){
            JycKubZ( zUnxtaivDfcW->JsRVdaxNGJSGE );
            aCwtzFfITm(viN6MryxBPT, zUnxtaivDfcW->g3ezVn5k);
            PUxqRF_wh = V6q4V;
          }
        }
      }
    }
  }

  return PUxqRF_wh;
}

/*
** xNext
*/
static int ONnljmqHa7(uhVX *UNL5wxrRk5X){
  int PUxqRF_wh;
  do {
    PUxqRF_wh = ga2h((S_1cmzoC_u3*)UNL5wxrRk5X);
  }while( PUxqRF_wh==V6q4V );
  return PUxqRF_wh;
}

/*
** xColumn
*/
static int smR0w(
  uhVX *UNL5wxrRk5X,
  bd38tIq58qFfZ *ELwj_gqp7,
  int JfmbOrSEGvHfG
){
  S_1cmzoC_u3 *zUnxtaivDfcW = (S_1cmzoC_u3*)UNL5wxrRk5X;
  HnBo06yHC0L(ELwj_gqp7, mq8hs7TLqCC(zUnxtaivDfcW->JsRVdaxNGJSGE, JfmbOrSEGvHfG+1));
  return v6q1IzZ_hBO_1;
}

/*
** xRowid
*/
static int uPkQFiehw(uhVX *UNL5wxrRk5X, XbCYmCq *esSTK){
  S_1cmzoC_u3 *zUnxtaivDfcW = (S_1cmzoC_u3*)UNL5wxrRk5X;
  *esSTK = U46Jbq79OYOw(zUnxtaivDfcW->JsRVdaxNGJSGE, 0);
  return v6q1IzZ_hBO_1;
}

/*
** xEof
*/
static int sdXu_T55FyW(uhVX *UNL5wxrRk5X){
  S_1cmzoC_u3 *zUnxtaivDfcW = (S_1cmzoC_u3*)UNL5wxrRk5X;
  return zUnxtaivDfcW->JsRVdaxNGJSGE==0;
}

/*
** xFilter
*/
static int uVetFIp11F(
  uhVX *l3Y4sjDzGPOVY, 
  int Nt_8DDB0umS9r, const char *UvI36N,
  int LLORs1, KSV9 **IuukznuVu_
){
  aIZo7Nm *viN6MryxBPT = (aIZo7Nm*)(l3Y4sjDzGPOVY->ig9h);
  S_1cmzoC_u3 *zUnxtaivDfcW = (S_1cmzoC_u3*)l3Y4sjDzGPOVY;
  int PUxqRF_wh = v6q1IzZ_hBO_1;
  int JfmbOrSEGvHfG;
  char *tWgW71X79nd = 0;
  int GLoQuGF = 0;

  okW1jfQq4QcXo Kg14Sde_ZRX = lnbvbt2D;
  okW1jfQq4QcXo AXU4d = ErPDGGrB;

  JycKubZ( Nt_8DDB0umS9r==0 
       || Nt_8DDB0umS9r==Ifrx
       || Nt_8DDB0umS9r==kX6TA
       || Nt_8DDB0umS9r==a3FXn5wBJI3E
       || Nt_8DDB0umS9r==z7U_KQTmBxVw
       || Nt_8DDB0umS9r==wqwRiSp
       || Nt_8DDB0umS9r==(a3FXn5wBJI3E|kX6TA)
  );

  (void)UvI36N;  /* Suppress harmless warning */
  
  if( Nt_8DDB0umS9r==Ifrx ){
    JycKubZ( LLORs1==1 );
    Kg14Sde_ZRX = AXU4d = fOn3Krbdc(IuukznuVu_[0]);
  }else{

    if( Nt_8DDB0umS9r & (kX6TA|z7U_KQTmBxVw) ){
      JycKubZ( LLORs1>=1 );
      AXU4d = fOn3Krbdc(IuukznuVu_[0]);
      if( Nt_8DDB0umS9r & z7U_KQTmBxVw ){
        if( AXU4d==lnbvbt2D ){
          GLoQuGF = 1;
        }else{
          AXU4d--;
        }
      }
    }

    if( Nt_8DDB0umS9r & (a3FXn5wBJI3E|wqwRiSp) ){
      JycKubZ( LLORs1>=1 );
      Kg14Sde_ZRX = fOn3Krbdc(IuukznuVu_[LLORs1-1]);
      if( Nt_8DDB0umS9r & wqwRiSp ){
        if( Kg14Sde_ZRX==ErPDGGrB ){
          GLoQuGF = 1;
        }else{
          Kg14Sde_ZRX++;
        }
      }
    }
  }

  fs5EJ5N3(zUnxtaivDfcW);
  if( GLoQuGF ){
    return v6q1IzZ_hBO_1;
  }

  for(JfmbOrSEGvHfG=0; JfmbOrSEGvHfG<viN6MryxBPT->KQHrH; JfmbOrSEGvHfG++){
    DNNk *DNnH6S = &viN6MryxBPT->a9iP[JfmbOrSEGvHfG];
    if( Kg14Sde_ZRX>DNnH6S->AXU4d || AXU4d<DNnH6S->Kg14Sde_ZRX ){
      continue;
    }

    tWgW71X79nd = alc4k("%z%sSELECT rowid, * FROM %s%q%s%Q"
        , tWgW71X79nd
        , (tWgW71X79nd ? " UNION ALL " : "")
        , (DNnH6S->M6pDBVxRipoM ? "'" : "")
        , (DNnH6S->M6pDBVxRipoM ? DNnH6S->M6pDBVxRipoM : "")
        , (DNnH6S->M6pDBVxRipoM ? "'." : "")
        , DNnH6S->lUdT
    );
    if( tWgW71X79nd==0 ){
      PUxqRF_wh = y5ugqjsVGD;
      break;
    }

    if( Kg14Sde_ZRX==AXU4d ){
      tWgW71X79nd = alc4k("%z WHERE rowid=%lld", tWgW71X79nd, Kg14Sde_ZRX);
    }else{
      const char *RgU8iK = "WHERE";
      if( Kg14Sde_ZRX!=lnbvbt2D && Kg14Sde_ZRX>DNnH6S->Kg14Sde_ZRX ){
        tWgW71X79nd = alc4k("%z WHERE rowid>=%lld", tWgW71X79nd, Kg14Sde_ZRX);
        RgU8iK = "AND";
      }
      if( AXU4d!=ErPDGGrB && AXU4d<DNnH6S->AXU4d ){
        tWgW71X79nd = alc4k("%z %s rowid<=%lld", tWgW71X79nd, RgU8iK, AXU4d);
      }
    }

    if( viN6MryxBPT->E2j35Ko ){
      zUnxtaivDfcW->g3ezVn5k = JfmbOrSEGvHfG;
      zUnxtaivDfcW->E5J3F8 = AXU4d;
      PUxqRF_wh = LK9n(viN6MryxBPT, JfmbOrSEGvHfG, &viN6MryxBPT->UA7YG.qXfRHz0H);
      break;
    }
  }

  if( tWgW71X79nd==0 ){
    return PUxqRF_wh;
  }else{
    rRuYAh *DwoY = B2KW7Z_MyDz(viN6MryxBPT, &viN6MryxBPT->a9iP[zUnxtaivDfcW->g3ezVn5k]);
    zUnxtaivDfcW->JsRVdaxNGJSGE = MdWXf1xfe(&PUxqRF_wh, DwoY, tWgW71X79nd, &viN6MryxBPT->UA7YG.qXfRHz0H);
    if( zUnxtaivDfcW->JsRVdaxNGJSGE ){
      aCwtzFfITm(viN6MryxBPT, zUnxtaivDfcW->g3ezVn5k);
    }
    KQ5mNUvAB(tWgW71X79nd);
  }
  if( PUxqRF_wh!=v6q1IzZ_hBO_1 ) return PUxqRF_wh;
  return ONnljmqHa7(l3Y4sjDzGPOVY);
}

/*
** xBestIndex.
**
** This implementation searches for constraints on the rowid field. EQ, 
** LE, LT, GE and GT are handled.
**
** If there is an EQ comparison, then idxNum is set to INDEX_CONSTRAINT_EQ.
** In this case the only argument passed to xFilter is the rhs of the ==
** operator.
**
** Otherwise, if an LE or LT constraint is found, then the INDEX_CONSTRAINT_LE
** or INDEX_CONSTRAINT_LT (but not both) bit is set in idxNum. The first
** argument to xFilter is the rhs of the <= or < operator.  Similarly, if 
** an GE or GT constraint is found, then the INDEX_CONSTRAINT_GE or
** INDEX_CONSTRAINT_GT bit is set in idxNum. The rhs of the >= or > operator
** is passed as either the first or second argument to xFilter, depending
** on whether or not there is also a LT|LE constraint.
*/
static int nfbaRPK(
  BzNXOx *AJNRn15OpgVr,
  eNbmuY0uZUYlC *W6bJeR0F
){
  aIZo7Nm *viN6MryxBPT = (aIZo7Nm*)AJNRn15OpgVr;
  int HOnXM = -1;
  int pyRaBGXXr = -1;
  int PptegjM = -1;
  int JfmbOrSEGvHfG;

  for(JfmbOrSEGvHfG=0; JfmbOrSEGvHfG<W6bJeR0F->uavKBwlzMv4i_; JfmbOrSEGvHfG++){
    struct EIzaxdDD *AxLLdnw = &W6bJeR0F->hrnd3n1v[JfmbOrSEGvHfG];
    if( AxLLdnw->ekBv7F1ecuP && (AxLLdnw->k6PnnkAs<0 || AxLLdnw->k6PnnkAs==viN6MryxBPT->qVUKN6oPIY) ){
      switch( AxLLdnw->rNxnJ5BOCu1OZ ){
        case Ifrx:
          HOnXM = JfmbOrSEGvHfG;
          break;
        case kX6TA:
        case z7U_KQTmBxVw:
          pyRaBGXXr = JfmbOrSEGvHfG;
          break;
        case a3FXn5wBJI3E:
        case wqwRiSp:
          PptegjM = JfmbOrSEGvHfG;
          break;
      }
    }
  }

  if( HOnXM>=0 ){
    W6bJeR0F->o6IIkZvBL = 1;
    W6bJeR0F->RTtvei = ysqMFmJe6Fh;
    W6bJeR0F->NL2s6lyyp = 3.0;
    W6bJeR0F->Nt_8DDB0umS9r = Ifrx;
    W6bJeR0F->v2NT[HOnXM].TY79UKadIz = 1;
    W6bJeR0F->v2NT[HOnXM].TdbNFbfgM = 1;
  }else{
    int Gszm7swXLC = 1;
    int Nt_8DDB0umS9r = 0;
    okW1jfQq4QcXo Z8F3j = 1000000;
    if( pyRaBGXXr>=0 ){
      Z8F3j = Z8F3j / 2;
      W6bJeR0F->v2NT[pyRaBGXXr].TY79UKadIz = Gszm7swXLC++;
      W6bJeR0F->v2NT[pyRaBGXXr].TdbNFbfgM = 1;
      Nt_8DDB0umS9r |= W6bJeR0F->hrnd3n1v[pyRaBGXXr].rNxnJ5BOCu1OZ;
    }
    if( PptegjM>=0 ){
      Z8F3j = Z8F3j / 2;
      W6bJeR0F->v2NT[PptegjM].TY79UKadIz = Gszm7swXLC++;
      W6bJeR0F->v2NT[PptegjM].TdbNFbfgM = 1;
      Nt_8DDB0umS9r |= W6bJeR0F->hrnd3n1v[PptegjM].rNxnJ5BOCu1OZ;
    }
    W6bJeR0F->o6IIkZvBL = Z8F3j;
    W6bJeR0F->NL2s6lyyp = 3.0 * (double)Z8F3j;
    W6bJeR0F->Nt_8DDB0umS9r = Nt_8DDB0umS9r;
  }

  return v6q1IzZ_hBO_1;
}

/*
** Register the unionvtab virtual table module with database handle db.
*/
static int huaGw(rRuYAh *DwoY){
  static l1tHoWjG HTr9y3B0s0 = {
    0,                            /* iVersion */
    Xs88MI,
    Xs88MI,
    nfbaRPK,               /* xBestIndex - query planner */
    OtUqOj4, 
    OtUqOj4,
    cP1DJTyE3uuE_,                    /* xOpen - open a cursor */
    Byz65QoHaKG,                   /* xClose - close a cursor */
    uVetFIp11F,                  /* xFilter - configure scan constraints */
    ONnljmqHa7,                    /* xNext - advance a cursor */
    sdXu_T55FyW,                     /* xEof - check for end of scan */
    smR0w,                  /* xColumn - read data */
    uPkQFiehw,                   /* xRowid - read data */
    0,                            /* xUpdate */
    0,                            /* xBegin */
    0,                            /* xSync */
    0,                            /* xCommit */
    0,                            /* xRollback */
    0,                            /* xFindMethod */
    0,                            /* xRename */
    0,                            /* xSavepoint */
    0,                            /* xRelease */
    0,                            /* xRollbackTo */
    0,                            /* xShadowName */
    0                             /* xIntegrity */
  };
  int PUxqRF_wh;

  PUxqRF_wh = s8RF3(DwoY, "unionvtab", &HTr9y3B0s0, 0);
  if( PUxqRF_wh==v6q1IzZ_hBO_1 ){
    PUxqRF_wh = s8RF3(DwoY, "swarmvtab", &HTr9y3B0s0, (void*)DwoY);
  }
  return PUxqRF_wh;
}

#endif /* SQLITE_OMIT_VIRTUALTABLE */

#ifdef xoMZxcNF
NQb5xJ(E2UQ_c5dChb)
#endif
int Zm9aMQp6us8OF(
  rRuYAh *DwoY, 
  char **y3RXdGuIlITd, 
  const h9nffbbC *yDk_a
){
  int PUxqRF_wh = v6q1IzZ_hBO_1;
  Md8msN1iqa(yDk_a);
  (void)y3RXdGuIlITd;  /* Suppress harmless warning */
#ifndef rn83sn
  PUxqRF_wh = huaGw(DwoY);
#endif
  return PUxqRF_wh;
}
