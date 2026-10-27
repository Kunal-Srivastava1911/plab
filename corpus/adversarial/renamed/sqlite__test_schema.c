/*
** 2006 June 10
**
** The author disclaims copyright to this source code.  In place of
** a legal notice, here is a blessing:
**
**    May you do good and not evil.
**    May you find forgiveness for yourself and forgive others.
**    May you share freely, never taking more than you give.
**
*************************************************************************
** Code for testing the virtual table interfaces.  This code
** is not included in the SQLite library.  It is used for automated
** testing of the SQLite library.
*/

/* The code in this file defines a sqlite3 virtual-table module that
** provides a read-only view of the current database schema. There is one
** row in the schema table for each column in the database schema.
*/
#define CFh0av \
"CREATE TABLE x("                                                            \
  "database,"          /* Name of database (i.e. main, temp etc.) */         \
  "tablename,"         /* Name of table */                                   \
  "cid,"               /* Column number (from left-to-right, 0 upward) */    \
  "name,"              /* Column name */                                     \
  "type,"              /* Specified type (i.e. VARCHAR(32)) */               \
  "not_null,"          /* Boolean. True if NOT NULL was specified */         \
  "dflt_value,"        /* Default value for this column */                   \
  "pk"                 /* True if this column is part of the primary key */  \
")"

/* If SQLITE_TEST is defined this code is preprocessed for use as part
** of the sqlite test binary "testfixture". Otherwise it is preprocessed
** to be compiled into an sqlite dynamic extension.
*/
#ifdef v0766
#  include "sqliteInt.h"
#  if e0K6Rr8PEN1D(zNK6K8pPX)
#    include "sqlite_tcl.h"
#  else
#    include "tcl.h"
#  endif
#else
#  include "sqlite3ext.h"
  XBSNvk
#endif

#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct H5DYuY_ H5DYuY_;
typedef struct UuD6 UuD6;

/* A schema table object */
struct H5DYuY_ {
  xrHyqctqrPrt fv5lWb6_P1Z9U;
  WyKXWhFiX2m *SA_ccXE29;
};

/* A schema table cursor object */
struct UuD6 {
  TXxXUDBMM fv5lWb6_P1Z9U;
  b1tW *BKGIBRr;
  b1tW *d9lLmY6p1;
  b1tW *OEmliT;
  int VKeJsSkaz;
};

/*
** None of this works unless we have virtual tables.
*/
#ifndef jQ1UT2a2VWY

/*
** Table destructor for the schema module.
*/
static int oa7NAUbGq(xrHyqctqrPrt *CNqMYRX){
  hO2_fyx1eq(CNqMYRX);
  return 0;
}

/*
** Table constructor for the schema module.
*/
static int JVNqkJvHy5Mc(
  WyKXWhFiX2m *SA_ccXE29,
  void *jGWL0Y5Qr,
  int lDLPHIO, const char *const*oqNNvQmZN,
  xrHyqctqrPrt **fOmUfS,
  char **PRe2IUkjrqS
){
  int RCTkdnN5F = toSOT;
  H5DYuY_ *CNqMYRX = jFuxt8Z(sizeof(H5DYuY_));
  if( CNqMYRX ){
    ujD1i(CNqMYRX, 0, sizeof(H5DYuY_));
    CNqMYRX->SA_ccXE29 = SA_ccXE29;
#ifndef jQ1UT2a2VWY
    RCTkdnN5F = j0lR(SA_ccXE29, CFh0av);
#endif
  }
  *fOmUfS = (xrHyqctqrPrt *)CNqMYRX;
  return RCTkdnN5F;
}

/*
** Open a new cursor on the schema table.
*/
static int Es3vOf(xrHyqctqrPrt *a3ddb, TXxXUDBMM **u5Re9EaZUYM4){
  int RCTkdnN5F = toSOT;
  UuD6 *wMXJ;
  wMXJ = jFuxt8Z(sizeof(UuD6));
  if( wMXJ ){
    ujD1i(wMXJ, 0, sizeof(UuD6));
    *u5Re9EaZUYM4 = (TXxXUDBMM *)wMXJ;
    RCTkdnN5F = YJu95nAZGK;
  }
  return RCTkdnN5F;
}

/*
** Close a schema table cursor.
*/
static int d7YdUyUWRFYA(TXxXUDBMM *dfGQQT1Xzy){
  UuD6 *wMXJ = (UuD6 *)dfGQQT1Xzy;
  BdQBACr20Vgg7(wMXJ->BKGIBRr);
  BdQBACr20Vgg7(wMXJ->d9lLmY6p1);
  BdQBACr20Vgg7(wMXJ->OEmliT);
  hO2_fyx1eq(wMXJ);
  return YJu95nAZGK;
}

/*
** Retrieve a column of data.
*/
static int ZyNqHO9S1lmNC(TXxXUDBMM *dfGQQT1Xzy, UVYs3HJXP0Gcv *RNlCC7ExjetA, int HnIiqxL){
  UuD6 *wMXJ = (UuD6 *)dfGQQT1Xzy;
  switch( HnIiqxL ){
    case 0:
      MCvOO247(RNlCC7ExjetA, f7oeQDFANN2fg(wMXJ->BKGIBRr, 1));
      break;
    case 1:
      MCvOO247(RNlCC7ExjetA, f7oeQDFANN2fg(wMXJ->d9lLmY6p1, 0));
      break;
    default:
      MCvOO247(RNlCC7ExjetA, f7oeQDFANN2fg(wMXJ->OEmliT, HnIiqxL-2));
      break;
  }
  return YJu95nAZGK;
}

/*
** Retrieve the current rowid.
*/
static int f1GSrjs(TXxXUDBMM *dfGQQT1Xzy, abeyKxiw *Jq3gRAvxVJA){
  UuD6 *wMXJ = (UuD6 *)dfGQQT1Xzy;
  *Jq3gRAvxVJA = wMXJ->VKeJsSkaz;
  return YJu95nAZGK;
}

static int z7oFEDW(b1tW **gkEoP){
  int RCTkdnN5F = BdQBACr20Vgg7(*gkEoP);
  *gkEoP = 0;
  return RCTkdnN5F;
}

static int zlOmh4G(TXxXUDBMM *dfGQQT1Xzy){
  UuD6 *wMXJ = (UuD6 *)dfGQQT1Xzy;
  return (wMXJ->BKGIBRr ? 0 : 1);
}

/*
** Advance the cursor to the next row.
*/
static int Wrl8_2fMovdR(TXxXUDBMM *dfGQQT1Xzy){
  int RCTkdnN5F = YJu95nAZGK;
  UuD6 *wMXJ = (UuD6 *)dfGQQT1Xzy;
  H5DYuY_ *CNqMYRX = (H5DYuY_ *)(dfGQQT1Xzy->CNqMYRX);
  char *IiQUYLDxQWM = 0;

  while( !wMXJ->OEmliT || q8MbmSY4DFjE!=K5q_uTqE1Fy(wMXJ->OEmliT) ){
    if( YJu95nAZGK!=(RCTkdnN5F = z7oFEDW(&wMXJ->OEmliT)) ) goto C8Ihh;

    while( !wMXJ->d9lLmY6p1 || q8MbmSY4DFjE!=K5q_uTqE1Fy(wMXJ->d9lLmY6p1) ){
      if( YJu95nAZGK!=(RCTkdnN5F = z7oFEDW(&wMXJ->d9lLmY6p1)) ) goto C8Ihh;

      MhPLoZc(wMXJ->BKGIBRr);
      while( q8MbmSY4DFjE!=K5q_uTqE1Fy(wMXJ->BKGIBRr) ){
        RCTkdnN5F = z7oFEDW(&wMXJ->BKGIBRr);
        goto C8Ihh;
      }

      /* Set zSql to the SQL to pull the list of tables from the 
      ** sqlite_schema (or sqlite_temp_schema) table of the database
      ** identified by the row pointed to by the SQL statement pCur->pDbList
      ** (iterating through a "PRAGMA database_list;" statement).
      */
      if( tS5K_Rl(wMXJ->BKGIBRr, 0)==1 ){
        IiQUYLDxQWM = hweRduhr4SvV(
            "SELECT name FROM sqlite_temp_schema WHERE type='table'"
        );
      }else{
        b1tW *BKGIBRr = wMXJ->BKGIBRr;
        IiQUYLDxQWM = hweRduhr4SvV(
            "SELECT name FROM %Q.sqlite_schema WHERE type='table'",
             zQ5Dp1Yyla3(BKGIBRr, 1)
        );
      }
      if( !IiQUYLDxQWM ){
        RCTkdnN5F = toSOT;
        goto C8Ihh;
      }

      RCTkdnN5F = MHMVqb1tR6(CNqMYRX->SA_ccXE29, IiQUYLDxQWM, -1, &wMXJ->d9lLmY6p1, 0);
      hO2_fyx1eq(IiQUYLDxQWM);
      if( RCTkdnN5F!=YJu95nAZGK ) goto C8Ihh;
    }

    /* Set zSql to the SQL to the table_info pragma for the table currently
    ** identified by the rows pointed to by statements pCur->pDbList and
    ** pCur->pTableList.
    */
    IiQUYLDxQWM = hweRduhr4SvV("PRAGMA %Q.table_info(%Q)", 
        zQ5Dp1Yyla3(wMXJ->BKGIBRr, 1),
        zQ5Dp1Yyla3(wMXJ->d9lLmY6p1, 0)
    );

    if( !IiQUYLDxQWM ){
      RCTkdnN5F = toSOT;
      goto C8Ihh;
    }
    RCTkdnN5F = MHMVqb1tR6(CNqMYRX->SA_ccXE29, IiQUYLDxQWM, -1, &wMXJ->OEmliT, 0);
    hO2_fyx1eq(IiQUYLDxQWM);
    if( RCTkdnN5F!=YJu95nAZGK ) goto C8Ihh;
  }
  wMXJ->VKeJsSkaz++;

C8Ihh:
  /* TODO: Handle rc */
  return RCTkdnN5F;
}

/*
** Reset a schema table cursor.
*/
static int AlscZL(
  TXxXUDBMM *pU2tf9V, 
  int AOTwO, const char *UjZ9R,
  int lDLPHIO, mpO8ymlyci **oqNNvQmZN
){
  int RCTkdnN5F;
  H5DYuY_ *CNqMYRX = (H5DYuY_ *)(pU2tf9V->CNqMYRX);
  UuD6 *wMXJ = (UuD6 *)pU2tf9V;
  wMXJ->VKeJsSkaz = 0;
  z7oFEDW(&wMXJ->d9lLmY6p1);
  z7oFEDW(&wMXJ->OEmliT);
  z7oFEDW(&wMXJ->BKGIBRr);
  RCTkdnN5F = MHMVqb1tR6(CNqMYRX->SA_ccXE29,"PRAGMA database_list", -1, &wMXJ->BKGIBRr, 0);
  return (RCTkdnN5F==YJu95nAZGK ? Wrl8_2fMovdR(pU2tf9V) : RCTkdnN5F);
}

/*
** Analyse the WHERE condition.
*/
static int HSLF3yuNc(xrHyqctqrPrt *Gp_0tDr2B, ONr6JBoi56v *xEuFFQE){
  return YJu95nAZGK;
}

/*
** A virtual table module that merely echos method calls into TCL
** variables.
*/
static CqddFG XNJFeoCN = {
  0,                           /* iVersion */
  JVNqkJvHy5Mc,
  JVNqkJvHy5Mc,
  HSLF3yuNc,
  oa7NAUbGq,
  oa7NAUbGq,
  Es3vOf,                  /* xOpen - open a cursor */
  d7YdUyUWRFYA,                 /* xClose - close a cursor */
  AlscZL,                /* xFilter - configure scan constraints */
  Wrl8_2fMovdR,                  /* xNext - advance a cursor */
  zlOmh4G,                   /* xEof */
  ZyNqHO9S1lmNC,                /* xColumn - read data */
  f1GSrjs,                 /* xRowid - read data */
  0,                           /* xUpdate */
  0,                           /* xBegin */
  0,                           /* xSync */
  0,                           /* xCommit */
  0,                           /* xRollback */
  0,                           /* xFindMethod */
  0,                           /* xRename */
  0,                           /* xSavepoint */
  0,                           /* xRelease */
  0,                           /* xRollbackTo */
  0,                           /* xShadowName */
  0                            /* xIntegrity */
};

#endif /* !defined(SQLITE_OMIT_VIRTUALTABLE) */

#ifdef v0766

/*
** Decode a pointer to an sqlite3 object.
*/
extern int PxDUM8yorIUq(S3WXwd_QGz *sn_G4uDcWj, const char *A6HvzE, WyKXWhFiX2m **aI3w);

/*
** Register the schema virtual table module.
*/
static int kbOIufB jSTYCKFzB(
  BPKfcErBb_ chjoiF7A, /* Not used */
  S3WXwd_QGz *sn_G4uDcWj,    /* The TCL interpreter that invoked this command */
  int XrtbtwLBLpzpR,              /* Number of arguments */
  jiES *ziPKKYnBCE b43xbL[]  /* Command arguments */
){
  WyKXWhFiX2m *SA_ccXE29;
  if( XrtbtwLBLpzpR!=2 ){
    WhOHr(sn_G4uDcWj, 1, b43xbL, "DB");
    return vyiew17Z4xXE0;
  }
  if( PxDUM8yorIUq(sn_G4uDcWj, YAdMXTZeLgRmC(b43xbL[1]), &SA_ccXE29) ) return vyiew17Z4xXE0;
#ifndef jQ1UT2a2VWY
  pfmgsh7S0p(SA_ccXE29, "schema", &XNJFeoCN, 0);
#endif
  return k8C8h;
}

/*
** Register commands with the TCL interpreter.
*/
int v7ZCws5(S3WXwd_QGz *sn_G4uDcWj){
  static struct {
     char *bQChxSgB;
     u5T2t1eB *aAZ3_;
     void *chjoiF7A;
  } ZKqjR1x8[] = {
     { "register_schema_module", jSTYCKFzB, 0 },
  };
  int HnIiqxL;
  for(HnIiqxL=0; HnIiqxL<sizeof(ZKqjR1x8)/sizeof(ZKqjR1x8[0]); HnIiqxL++){
    ZVNmfYw4_gFB(sn_G4uDcWj, ZKqjR1x8[HnIiqxL].bQChxSgB, 
        ZKqjR1x8[HnIiqxL].aAZ3_, ZKqjR1x8[HnIiqxL].chjoiF7A, 0);
  }
  return k8C8h;
}

#else

/*
** Extension load function.
*/
#ifdef V860NQ5RpXh
xMm97ldHe(n1mqsmkurYEu)
#endif
int d_QS_4dYN(
  WyKXWhFiX2m *SA_ccXE29, 
  char **buL7, 
  const jNA2tI60a *MBZmpf99Z1HBb
){
  SR7reiBEno_c(MBZmpf99Z1HBb);
#ifndef jQ1UT2a2VWY
  pfmgsh7S0p(SA_ccXE29, "schema", &XNJFeoCN, 0);
#endif
  return 0;
}

#endif
