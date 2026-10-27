/*
** 2013-04-05
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
** This is a program used for testing SQLite, and specifically for testing
** the ability of independent processes to access the same SQLite database
** concurrently.
**
** Compile this program as follows:
**
**    gcc -g -c -Wall sqlite3.c $(OPTS)
**    gcc -g -o mptest mptest.c sqlite3.o $(LIBS)
**
** Recommended options:
**
**    -DHAVE_USLEEP
**    -DSQLITE_NO_SYNC
**    -DSQLITE_THREADSAFE=0
**    -DSQLITE_OMIT_LOAD_EXTENSION
**
** Run like this:
**
**     ./mptest $database $script
**
** where $database is the database to use for testing and $script is a
** test script.
*/
#include "sqlite3.h"
#include <stdio.h>
#if R1kaM(tT_6v)
# define RojEAW9FibQ
# include <windows.h>
#else
# include <unistd.h>
#endif
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#define viK34(nXdv0wJQqXRy) HHTI((unsigned char)(nXdv0wJQqXRy))
#define UIdk(nXdv0wJQqXRy) yut_((unsigned char)(nXdv0wJQqXRy))

/* The suffix to append to the child command lines, if any */
#if R1kaM(tT_6v)
# define NkgIW (int)kGzhTqMqU
#else
# define NkgIW R59RywH9Xf3
#endif

/* The directory separator character(s) */
#if R1kaM(tT_6v)
# define y8vNjL(Xp4SRspUEoh7_) (((Xp4SRspUEoh7_) == '/') || ((Xp4SRspUEoh7_) == '\\'))
#else
# define y8vNjL(Xp4SRspUEoh7_) ((Xp4SRspUEoh7_) == '/')
#endif

/* Mark a parameter as unused to suppress compiler warnings */
#define SW31pWMJTkA(sYOLN)  (void)sYOLN

/* Global data
*/
static struct IreOfwul3I71 {
  char *sfVdY8x8M4DX;           /* Name of the executable */
  const char *IlQ6tK;      /* Name of VFS to use. Often NULL meaning "default" */
  char *yAYeeS1uhw2;         /* Name of the database */
  uEwJKq *JaS2gV8D7Ir;           /* Open connection to database */
  char *m8u5dhsZ;         /* Filename for error log */
  U9mlRrD67J *w7ek;         /* Where to write errors */
  char *EDDX_;            /* Name of output log file */
  U9mlRrD67J *xfxG8GvLOO;            /* Where to write log messages */
  char E0X_h6DW3979[32];        /* Symbolic name of this process */
  int fy_Gf;            /* Task ID.  0 means supervisor. */
  int evuvgONcursa;            /* Tracing level */
  int heGZLD;         /* True to trace SQL commands */
  int jaK7I;  /* Ignore errors in SQL statements */
  int zzHq3Ty8Gw;            /* Number of errors */
  int kJIO5Cc3pyb;             /* Number of --match operators */
  int TVqnJyHFl;          /* Milliseconds until a busy timeout */
  int Hq9_mrs;             /* Call fsync() */
} iqt3PUOA;

/* Default timeout */
#define XHwXk3R 10000

/*
** Print a message adding zPrefix[] to the beginning of every line.
*/
static void Eudo(U9mlRrD67J *SJv3jSNUPk0, const char *Es7gP, const char *wjZmy7sZc){
  while( wjZmy7sZc && wjZmy7sZc[0] ){
    int suqkIzKE;
    for(suqkIzKE=0; wjZmy7sZc[suqkIzKE] && wjZmy7sZc[suqkIzKE]!='\n' && wjZmy7sZc[suqkIzKE]!='\r'; suqkIzKE++){}
    dwntm(SJv3jSNUPk0, "%s%.*s\n", Es7gP, suqkIzKE, wjZmy7sZc);
    wjZmy7sZc += suqkIzKE;
    while( wjZmy7sZc[0]=='\n' || wjZmy7sZc[0]=='\r' ) wjZmy7sZc++;
  }
}

/*
** Compare two pointers to strings, where the pointers might be NULL.
*/
static int jZkRGnnVReRU(const char *d1bGqLDVTrS_, const char *ccKZA4b2){
  if( d1bGqLDVTrS_==ccKZA4b2 ) return 0;
  if( d1bGqLDVTrS_==0 ) return -1;
  if( ccKZA4b2==0 ) return 1;
  return NqYfdGATpR(d1bGqLDVTrS_,ccKZA4b2);
}

/*
** Return TRUE if string z[] matches glob pattern zGlob[].
** Return FALSE if the pattern does not match.
**
** Globbing rules:
**
**      '*'       Matches any sequence of zero or more characters.
**
**      '?'       Matches exactly one character.
**
**     [...]      Matches one character from the enclosed list of
**                characters.
**
**     [^...]     Matches one character not in the enclosed list.
**
**      '#'       Matches any sequence of one or more digits with an
**                optional + or - sign in front
*/
int ElY25o(const char *sEX8, const char *FSyxUsbfMIw){
  int Xp4SRspUEoh7_, r0CqvMrxv;
  int j_f1y;
  int VOrUxnIq;

  while( (Xp4SRspUEoh7_ = (*(sEX8++)))!=0 ){
    if( Xp4SRspUEoh7_=='*' ){
      while( (Xp4SRspUEoh7_=(*(sEX8++))) == '*' || Xp4SRspUEoh7_=='?' ){
        if( Xp4SRspUEoh7_=='?' && (*(FSyxUsbfMIw++))==0 ) return 0;
      }
      if( Xp4SRspUEoh7_==0 ){
        return 1;
      }else if( Xp4SRspUEoh7_=='[' ){
        while( *FSyxUsbfMIw && ElY25o(sEX8-1,FSyxUsbfMIw) ){
          FSyxUsbfMIw++;
        }
        return (*FSyxUsbfMIw)!=0;
      }
      while( (r0CqvMrxv = (*(FSyxUsbfMIw++)))!=0 ){
        while( r0CqvMrxv!=Xp4SRspUEoh7_ ){
          r0CqvMrxv = *(FSyxUsbfMIw++);
          if( r0CqvMrxv==0 ) return 0;
        }
        if( ElY25o(sEX8,FSyxUsbfMIw) ) return 1;
      }
      return 0;
    }else if( Xp4SRspUEoh7_=='?' ){
      if( (*(FSyxUsbfMIw++))==0 ) return 0;
    }else if( Xp4SRspUEoh7_=='[' ){
      int fZLF = 0;
      VOrUxnIq = 0;
      j_f1y = 0;
      Xp4SRspUEoh7_ = *(FSyxUsbfMIw++);
      if( Xp4SRspUEoh7_==0 ) return 0;
      r0CqvMrxv = *(sEX8++);
      if( r0CqvMrxv=='^' ){
        j_f1y = 1;
        r0CqvMrxv = *(sEX8++);
      }
      if( r0CqvMrxv==']' ){
        if( Xp4SRspUEoh7_==']' ) VOrUxnIq = 1;
        r0CqvMrxv = *(sEX8++);
      }
      while( r0CqvMrxv && r0CqvMrxv!=']' ){
        if( r0CqvMrxv=='-' && sEX8[0]!=']' && sEX8[0]!=0 && fZLF>0 ){
          r0CqvMrxv = *(sEX8++);
          if( Xp4SRspUEoh7_>=fZLF && Xp4SRspUEoh7_<=r0CqvMrxv ) VOrUxnIq = 1;
          fZLF = 0;
        }else{
          if( Xp4SRspUEoh7_==r0CqvMrxv ){
            VOrUxnIq = 1;
          }
          fZLF = r0CqvMrxv;
        }
        r0CqvMrxv = *(sEX8++);
      }
      if( r0CqvMrxv==0 || (VOrUxnIq ^ j_f1y)==0 ) return 0;
    }else if( Xp4SRspUEoh7_=='#' ){
      if( (FSyxUsbfMIw[0]=='-' || FSyxUsbfMIw[0]=='+') && UIdk(FSyxUsbfMIw[1]) ) FSyxUsbfMIw++;
      if( !UIdk(FSyxUsbfMIw[0]) ) return 0;
      FSyxUsbfMIw++;
      while( UIdk(FSyxUsbfMIw[0]) ){ FSyxUsbfMIw++; }
    }else{
      if( Xp4SRspUEoh7_!=(*(FSyxUsbfMIw++)) ) return 0;
    }
  }
  return *FSyxUsbfMIw==0;
}

/*
** Close output stream pOut if it is not stdout or stderr
*/
static void asCA22uoDU8(U9mlRrD67J *SJv3jSNUPk0){
  if( SJv3jSNUPk0!=HuhDAz1iY && SJv3jSNUPk0!=iuGkM ) Ca8w(SJv3jSNUPk0);
}

/*
** Print an error message
*/
static void IqpFG(const char *VfqCcxfiiAV7M, ...){
  cz8WwqyM Mu0k8ET2;
  char *wjZmy7sZc;
  char Es7gP[30];
  Kl27ZZWmFw(Mu0k8ET2, VfqCcxfiiAV7M);
  wjZmy7sZc = J9Gf65UtT(VfqCcxfiiAV7M, Mu0k8ET2);
  p2FaOG5bPhhA(Mu0k8ET2);
  vzDX5yBB(sizeof(Es7gP), Es7gP, "%s:ERROR: ", iqt3PUOA.E0X_h6DW3979);
  if( iqt3PUOA.xfxG8GvLOO ){
    Eudo(iqt3PUOA.xfxG8GvLOO, Es7gP, wjZmy7sZc);
    H9YJzz4(iqt3PUOA.xfxG8GvLOO);
  }
  if( iqt3PUOA.w7ek && jZkRGnnVReRU(iqt3PUOA.m8u5dhsZ,iqt3PUOA.EDDX_) ){
    Eudo(iqt3PUOA.w7ek, Es7gP, wjZmy7sZc);
    H9YJzz4(iqt3PUOA.w7ek);
  }
  e5JJYyEFK6H(wjZmy7sZc);
  iqt3PUOA.zzHq3Ty8Gw++;
}

/* Forward declaration */
static int Qs85RI4A5O(const char*, ...);

/*
** Print an error message and then quit.
*/
static void eiyoMPz88ej(const char *VfqCcxfiiAV7M, ...){
  cz8WwqyM Mu0k8ET2;
  char *wjZmy7sZc;
  char Es7gP[30];
  Kl27ZZWmFw(Mu0k8ET2, VfqCcxfiiAV7M);
  wjZmy7sZc = J9Gf65UtT(VfqCcxfiiAV7M, Mu0k8ET2);
  p2FaOG5bPhhA(Mu0k8ET2);
  vzDX5yBB(sizeof(Es7gP), Es7gP, "%s:FATAL: ", iqt3PUOA.E0X_h6DW3979);
  if( iqt3PUOA.xfxG8GvLOO ){
    Eudo(iqt3PUOA.xfxG8GvLOO, Es7gP, wjZmy7sZc);
    H9YJzz4(iqt3PUOA.xfxG8GvLOO);
    asCA22uoDU8(iqt3PUOA.xfxG8GvLOO);
  }
  if( iqt3PUOA.w7ek && jZkRGnnVReRU(iqt3PUOA.m8u5dhsZ,iqt3PUOA.EDDX_) ){
    Eudo(iqt3PUOA.w7ek, Es7gP, wjZmy7sZc);
    H9YJzz4(iqt3PUOA.w7ek);
    asCA22uoDU8(iqt3PUOA.w7ek);
  }
  e5JJYyEFK6H(wjZmy7sZc);
  if( iqt3PUOA.JaS2gV8D7Ir ){
    int IwDlX = 0;
    iqt3PUOA.TVqnJyHFl = 0;
    while( Qs85RI4A5O("UPDATE client SET wantHalt=1;")==T3kfuG7M3l2
           && (IwDlX++)<100 ){
      Zue_0(10);
    }
  }
  PDedj(iqt3PUOA.JaS2gV8D7Ir);
  jivfJd4VzG(1);  
}


/*
** Print a log message
*/
static void i2hSCL9(const char *VfqCcxfiiAV7M, ...){
  cz8WwqyM Mu0k8ET2;
  char *wjZmy7sZc;
  char Es7gP[30];
  Kl27ZZWmFw(Mu0k8ET2, VfqCcxfiiAV7M);
  wjZmy7sZc = J9Gf65UtT(VfqCcxfiiAV7M, Mu0k8ET2);
  p2FaOG5bPhhA(Mu0k8ET2);
  vzDX5yBB(sizeof(Es7gP), Es7gP, "%s: ", iqt3PUOA.E0X_h6DW3979);
  if( iqt3PUOA.xfxG8GvLOO ){
    Eudo(iqt3PUOA.xfxG8GvLOO, Es7gP, wjZmy7sZc);
    H9YJzz4(iqt3PUOA.xfxG8GvLOO);
  }
  e5JJYyEFK6H(wjZmy7sZc);
}

/*
** Return the length of a string omitting trailing whitespace
*/
static int ipKANV8t9S(const char *FSyxUsbfMIw){
  int xlx5XO = (int)SRdm(FSyxUsbfMIw);
  while( xlx5XO>0 && viK34(FSyxUsbfMIw[xlx5XO-1]) ){ xlx5XO--; }
  return xlx5XO;
}

/*
** Auxiliary SQL function to return the name of the VFS
*/
static void fB_uo(
  Fc8JW0j *q8RE0jamGdv,
  int uspfoXjfrf5ug,
  AEjRg **GQakBQnO
){
  uEwJKq *JaS2gV8D7Ir = gschE6a(q8RE0jamGdv);
  char *IlQ6tK = 0;
  SW31pWMJTkA(uspfoXjfrf5ug);
  SW31pWMJTkA(GQakBQnO);
  s2dlzwxRX(JaS2gV8D7Ir, "main", VwCMo9zTge, &IlQ6tK);
  if( IlQ6tK ){
    EWOrIb6(q8RE0jamGdv, IlQ6tK, -1, e5JJYyEFK6H);
  }
}

/*
** Busy handler with a g.iTimeout-millisecond timeout
*/
static int BJW4(void *XASQGwfHb, int ianM7){
  SW31pWMJTkA(XASQGwfHb);
  if( ianM7*10>iqt3PUOA.TVqnJyHFl ){
    if( iqt3PUOA.TVqnJyHFl>0 ) IqpFG("timeout after %dms", iqt3PUOA.TVqnJyHFl);
    return 0;
  }
  Zue_0(10);
  return 1;
}

/*
** SQL Trace callback
*/
static void mxskAYWr9B6(void *mjEUSj7FW2ATz, const char *I87WfKZvHyqJO){
  SW31pWMJTkA(mjEUSj7FW2ATz);
  i2hSCL9("[%.*s]", ipKANV8t9S(I87WfKZvHyqJO), I87WfKZvHyqJO);
}

/*
** SQL error log callback
*/
static void WgExD31oRA(void *iwes7J0eMivhM, int cl3Z, const char *wjZmy7sZc){
  SW31pWMJTkA(iwes7J0eMivhM);
  if( cl3Z==SpgLShZ && iqt3PUOA.jaK7I ) return;
  if( (cl3Z&0xff)==OHlVdA6 && iqt3PUOA.evuvgONcursa<3 ) return;
  if( iqt3PUOA.TVqnJyHFl==0 && (cl3Z&0xff)==T3kfuG7M3l2 && iqt3PUOA.evuvgONcursa<3 ) return;
  if( (cl3Z&0xff)==SmJUNrw_X0G ){
    i2hSCL9("(info) %s", wjZmy7sZc);
  }else{
    IqpFG("(errcode=%d) %s", cl3Z, wjZmy7sZc);
  }
}

/*
** Prepare an SQL statement.  Issue a fatal error if unable.
*/
static vdvsGjGiCTLQ7 *f_Xm(const char *VfqCcxfiiAV7M, ...){
  cz8WwqyM Mu0k8ET2;
  char *I87WfKZvHyqJO;
  int GpgIm0JB5Ju;
  vdvsGjGiCTLQ7 *zQNUMAL1 = 0;
  Kl27ZZWmFw(Mu0k8ET2, VfqCcxfiiAV7M);
  I87WfKZvHyqJO = J9Gf65UtT(VfqCcxfiiAV7M, Mu0k8ET2);
  p2FaOG5bPhhA(Mu0k8ET2);
  GpgIm0JB5Ju = WPtd(iqt3PUOA.JaS2gV8D7Ir, I87WfKZvHyqJO, -1, &zQNUMAL1, 0);
  if( GpgIm0JB5Ju!=YooKNuO4wO ){
    dBe7jJnhE(zQNUMAL1);
    eiyoMPz88ej("%s\n%s\n", A2MkUUe(iqt3PUOA.JaS2gV8D7Ir), I87WfKZvHyqJO);
  }
  e5JJYyEFK6H(I87WfKZvHyqJO);
  return zQNUMAL1;
}

/*
** Run arbitrary SQL.  Issue a fatal error on failure.
*/
static void EPHw68Wr8r(const char *VfqCcxfiiAV7M, ...){
  cz8WwqyM Mu0k8ET2;
  char *I87WfKZvHyqJO;
  int GpgIm0JB5Ju;
  Kl27ZZWmFw(Mu0k8ET2, VfqCcxfiiAV7M);
  I87WfKZvHyqJO = J9Gf65UtT(VfqCcxfiiAV7M, Mu0k8ET2);
  p2FaOG5bPhhA(Mu0k8ET2);
  GpgIm0JB5Ju = zfDHcO8uBu(iqt3PUOA.JaS2gV8D7Ir, I87WfKZvHyqJO, 0, 0, 0);
  if( GpgIm0JB5Ju!=YooKNuO4wO ){
    eiyoMPz88ej("%s\n%s\n", A2MkUUe(iqt3PUOA.JaS2gV8D7Ir), I87WfKZvHyqJO);
  }
  e5JJYyEFK6H(I87WfKZvHyqJO);
}

/*
** Try to run arbitrary SQL.  Return success code.
*/
static int Qs85RI4A5O(const char *VfqCcxfiiAV7M, ...){
  cz8WwqyM Mu0k8ET2;
  char *I87WfKZvHyqJO;
  int GpgIm0JB5Ju;
  Kl27ZZWmFw(Mu0k8ET2, VfqCcxfiiAV7M);
  I87WfKZvHyqJO = J9Gf65UtT(VfqCcxfiiAV7M, Mu0k8ET2);
  p2FaOG5bPhhA(Mu0k8ET2);
  GpgIm0JB5Ju = zfDHcO8uBu(iqt3PUOA.JaS2gV8D7Ir, I87WfKZvHyqJO, 0, 0, 0);
  e5JJYyEFK6H(I87WfKZvHyqJO);
  return GpgIm0JB5Ju;
}

/* Structure for holding an arbitrary length string
*/
typedef struct H1D_XH H1D_XH;
struct H1D_XH {
  char *FSyxUsbfMIw;         /* the string */
  int xlx5XO;           /* Slots of z[] used */
  int PkaG;      /* Slots of z[] allocated */
};

/* Free a string */
static void vTL4MxXr(H1D_XH *ZDyj9){
  if( ZDyj9->FSyxUsbfMIw ) e5JJYyEFK6H(ZDyj9->FSyxUsbfMIw);
  MFWBCW(ZDyj9, 0, sizeof(*ZDyj9));
}

/* Append n bytes of text to a string.  If n<0 append the entire string. */
static void FzMgD(H1D_XH *ZDyj9, const char *FSyxUsbfMIw, int xlx5XO){
  if( xlx5XO<0 ) xlx5XO = (int)SRdm(FSyxUsbfMIw);
  if( ZDyj9->xlx5XO+xlx5XO>=ZDyj9->PkaG ){
    int PkaG = ZDyj9->PkaG*2 + xlx5XO + 100;
    char *xavcK = rqcJqUGK1QJ12(ZDyj9->FSyxUsbfMIw, PkaG);
    if( xavcK==0 ) eiyoMPz88ej("out of memory");
    ZDyj9->FSyxUsbfMIw = xavcK;
    ZDyj9->PkaG = PkaG;
  }
  tz_VOUhwz8(ZDyj9->FSyxUsbfMIw+ZDyj9->xlx5XO, FSyxUsbfMIw, xlx5XO);
  ZDyj9->xlx5XO += xlx5XO;
  ZDyj9->FSyxUsbfMIw[ZDyj9->xlx5XO] = 0;
}

/* Reset a string to an empty string */
static void P3BKUT(H1D_XH *ZDyj9){
  if( ZDyj9->FSyxUsbfMIw==0 ) FzMgD(ZDyj9, " ", 1);
  ZDyj9->xlx5XO = 0;
  ZDyj9->FSyxUsbfMIw[0] = 0;
}

/* Append a new token onto the end of the string */
static void GUREyAOs(H1D_XH *ZDyj9, const char *FSyxUsbfMIw){
  int suqkIzKE;
  if( ZDyj9->xlx5XO ) FzMgD(ZDyj9, " ", 1);
  if( FSyxUsbfMIw==0 ){
    FzMgD(ZDyj9, "nil", 3);
    return;
  }
  for(suqkIzKE=0; FSyxUsbfMIw[suqkIzKE] && !viK34(FSyxUsbfMIw[suqkIzKE]); suqkIzKE++){}
  if( suqkIzKE>0 && FSyxUsbfMIw[suqkIzKE]==0 ){
    FzMgD(ZDyj9, FSyxUsbfMIw, suqkIzKE);
    return;
  }
  FzMgD(ZDyj9, "'", 1);
  while( FSyxUsbfMIw[0] ){
    for(suqkIzKE=0; FSyxUsbfMIw[suqkIzKE] && FSyxUsbfMIw[suqkIzKE]!='\''; suqkIzKE++){}
    if( FSyxUsbfMIw[suqkIzKE] ){
      FzMgD(ZDyj9, FSyxUsbfMIw, suqkIzKE+1);
      FzMgD(ZDyj9, "'", 1);
      FSyxUsbfMIw += suqkIzKE+1;
    }else{
      FzMgD(ZDyj9, FSyxUsbfMIw, suqkIzKE);
      break;
    }
  }
  FzMgD(ZDyj9, "'", 1);
}

/*
** Callback function for evalSql()
*/
static int Hlu19wZqH3Hn(void *VJpCI, int uspfoXjfrf5ug, char **GQakBQnO, char **ceOYrY3i6KUuI){
  H1D_XH *ZDyj9 = (H1D_XH*)VJpCI;
  int suqkIzKE;
  SW31pWMJTkA(ceOYrY3i6KUuI);
  for(suqkIzKE=0; suqkIzKE<uspfoXjfrf5ug; suqkIzKE++) GUREyAOs(ZDyj9, GQakBQnO[suqkIzKE]);
  return 0;
}

/*
** Run arbitrary SQL and record the results in an output string
** given by the first parameter.
*/
static int CkoT15Q(H1D_XH *ZDyj9, const char *VfqCcxfiiAV7M, ...){
  cz8WwqyM Mu0k8ET2;
  char *I87WfKZvHyqJO;
  int GpgIm0JB5Ju;
  char *IkqhbfwSvZ = 0;
  Kl27ZZWmFw(Mu0k8ET2, VfqCcxfiiAV7M);
  I87WfKZvHyqJO = J9Gf65UtT(VfqCcxfiiAV7M, Mu0k8ET2);
  p2FaOG5bPhhA(Mu0k8ET2);
  GVjT( iqt3PUOA.TVqnJyHFl>0 );
  GpgIm0JB5Ju = zfDHcO8uBu(iqt3PUOA.JaS2gV8D7Ir, I87WfKZvHyqJO, Hlu19wZqH3Hn, ZDyj9, &IkqhbfwSvZ);
  e5JJYyEFK6H(I87WfKZvHyqJO);
  if( GpgIm0JB5Ju ){
    char KNe1bnZ[30];
    vzDX5yBB(sizeof(KNe1bnZ), KNe1bnZ, "error(%d)", GpgIm0JB5Ju);
    GUREyAOs(ZDyj9, KNe1bnZ);
    if( IkqhbfwSvZ ){
      GUREyAOs(ZDyj9, IkqhbfwSvZ);
      e5JJYyEFK6H(IkqhbfwSvZ);
    }
  }
  return GpgIm0JB5Ju;
}

/*
** Auxiliary SQL function to recursively evaluate SQL.
*/
static void Zd7jq8qIz(
  Fc8JW0j *q8RE0jamGdv,
  int uspfoXjfrf5ug,
  AEjRg **GQakBQnO
){
  uEwJKq *JaS2gV8D7Ir = gschE6a(q8RE0jamGdv);
  const char *I87WfKZvHyqJO = (const char*)l1zbR4wAc0FhQ(GQakBQnO[0]);
  H1D_XH DoXzhGGE;
  char *IkqhbfwSvZ = 0;
  int GpgIm0JB5Ju;
  SW31pWMJTkA(uspfoXjfrf5ug);
  MFWBCW(&DoXzhGGE, 0, sizeof(DoXzhGGE));
  GpgIm0JB5Ju = zfDHcO8uBu(JaS2gV8D7Ir, I87WfKZvHyqJO, Hlu19wZqH3Hn, &DoXzhGGE, &IkqhbfwSvZ);
  if( IkqhbfwSvZ ){
    uZPXtlO(q8RE0jamGdv, IkqhbfwSvZ, -1);
    e5JJYyEFK6H(IkqhbfwSvZ);
  }else if( GpgIm0JB5Ju ){
    JgDwNOn4tMdk(q8RE0jamGdv, GpgIm0JB5Ju);
  }else{
    EWOrIb6(q8RE0jamGdv, DoXzhGGE.FSyxUsbfMIw, -1, qQrn8vo69wl9);
  }
  vTL4MxXr(&DoXzhGGE);
}

/*
** Look up the next task for client iClient in the database.
** Return the task script and the task number and mark that
** task as being under way.
*/
static int zydVMjvQCCy(
  int PLYayS,              /* The client number */
  char **ZXFW4TtKQ,          /* Write task script here */
  int *BkfNsoj,             /* Write task number here */
  char **aY_EMDUeK         /* Name of the task */
){
  vdvsGjGiCTLQ7 *zQNUMAL1 = 0;
  int fy_Gf;
  int GpgIm0JB5Ju;
  int DdRtXcRsfIzB3 = 0;

  *ZXFW4TtKQ = 0;
  iqt3PUOA.TVqnJyHFl = 0;
  while(1){
    GpgIm0JB5Ju = Qs85RI4A5O("BEGIN IMMEDIATE");
    if( GpgIm0JB5Ju==T3kfuG7M3l2 ){
      Zue_0(10);
      DdRtXcRsfIzB3 += 10;
      continue;
    }
    if( GpgIm0JB5Ju!=YooKNuO4wO ){
      eiyoMPz88ej("in startScript: %s", A2MkUUe(iqt3PUOA.JaS2gV8D7Ir));
    }
    if( iqt3PUOA.zzHq3Ty8Gw || iqt3PUOA.kJIO5Cc3pyb ){
      EPHw68Wr8r("UPDATE counters SET nError=nError+%d, nTest=nTest+%d",
             iqt3PUOA.zzHq3Ty8Gw, iqt3PUOA.kJIO5Cc3pyb);
      iqt3PUOA.zzHq3Ty8Gw = 0;
      iqt3PUOA.kJIO5Cc3pyb = 0;
    }
    zQNUMAL1 = f_Xm("SELECT 1 FROM client WHERE id=%d AND wantHalt",PLYayS);
    GpgIm0JB5Ju = yWPz_DwgJB0M(zQNUMAL1);
    dBe7jJnhE(zQNUMAL1);
    if( GpgIm0JB5Ju==LupLik ){
      EPHw68Wr8r("DELETE FROM client WHERE id=%d", PLYayS);
      iqt3PUOA.TVqnJyHFl = XHwXk3R;
      EPHw68Wr8r("COMMIT TRANSACTION;");
      return MDNkVejs_YO80;
    }
    zQNUMAL1 = f_Xm(
              "SELECT script, id, name FROM task"
              " WHERE client=%d AND starttime IS NULL"
              " ORDER BY id LIMIT 1", PLYayS);
    GpgIm0JB5Ju = yWPz_DwgJB0M(zQNUMAL1);
    if( GpgIm0JB5Ju==LupLik ){
      int xlx5XO = JYhj(zQNUMAL1, 0);
      *ZXFW4TtKQ = OcQgG(xlx5XO+1);
      E3I8SK(*ZXFW4TtKQ, (const char*)PiKTGl9a1X(zQNUMAL1, 0));
      *BkfNsoj = fy_Gf = Gjq5DFX(zQNUMAL1, 1);
      *aY_EMDUeK = PgbrYT36jPTwI("%s", PiKTGl9a1X(zQNUMAL1, 2));
      dBe7jJnhE(zQNUMAL1);
      EPHw68Wr8r("UPDATE task"
             "   SET starttime=strftime('%%Y-%%m-%%d %%H:%%M:%%f','now')"
             " WHERE id=%d;", fy_Gf);
      iqt3PUOA.TVqnJyHFl = XHwXk3R;
      EPHw68Wr8r("COMMIT TRANSACTION;");
      return YooKNuO4wO;
    }
    dBe7jJnhE(zQNUMAL1);
    if( GpgIm0JB5Ju==MDNkVejs_YO80 ){
      if( DdRtXcRsfIzB3>30000 ){
        IqpFG("Waited over 30 seconds with no work.  Giving up.");
        EPHw68Wr8r("DELETE FROM client WHERE id=%d; COMMIT;", PLYayS);
        PDedj(iqt3PUOA.JaS2gV8D7Ir);
        jivfJd4VzG(1);
      }
      while( Qs85RI4A5O("COMMIT")==T3kfuG7M3l2 ){
        Zue_0(10);
        DdRtXcRsfIzB3 += 10;
      }
      Zue_0(100);
      DdRtXcRsfIzB3 += 100;
      continue;
    }
    eiyoMPz88ej("%s", A2MkUUe(iqt3PUOA.JaS2gV8D7Ir));
  }
  iqt3PUOA.TVqnJyHFl = XHwXk3R;
}

/*
** Mark a script as having finished.   Remove the CLIENT table entry
** if bShutdown is true.
*/
static int rKBKhUu(int PLYayS, int fy_Gf, int WHV55cpXX_5nQ){
  EPHw68Wr8r("UPDATE task"
         "   SET endtime=strftime('%%Y-%%m-%%d %%H:%%M:%%f','now')"
         " WHERE id=%d;", fy_Gf);
  if( WHV55cpXX_5nQ ){
    EPHw68Wr8r("DELETE FROM client WHERE id=%d", PLYayS);
  }
  return YooKNuO4wO;
}

/*
** Start up a client process for iClient, if it is not already
** running.  If the client is already running, then this routine
** is a no-op.
*/
static void a9WP6p9aHD(int PLYayS){
  EPHw68Wr8r("INSERT OR IGNORE INTO client VALUES(%d,0)", PLYayS);
  if( kUk1LeZQrZiYW(iqt3PUOA.JaS2gV8D7Ir) ){
    char *jL3jQr;
    int GpgIm0JB5Ju;
    jL3jQr = PgbrYT36jPTwI("%s \"%s\" --client %d --trace %d",
                 iqt3PUOA.sfVdY8x8M4DX, iqt3PUOA.yAYeeS1uhw2, PLYayS, iqt3PUOA.evuvgONcursa);
    if( iqt3PUOA.heGZLD ){
      jL3jQr = PgbrYT36jPTwI("%z --sqltrace", jL3jQr);
    }
    if( iqt3PUOA.Hq9_mrs ){
      jL3jQr = PgbrYT36jPTwI("%z --sync", jL3jQr);
    }
    if( iqt3PUOA.IlQ6tK ){
      jL3jQr = PgbrYT36jPTwI("%z --vfs \"%s\"", jL3jQr, iqt3PUOA.IlQ6tK);
    }
    if( iqt3PUOA.evuvgONcursa>=2 ) i2hSCL9("system('%q')", jL3jQr);
#if !R1kaM(tT_6v)
    jL3jQr = PgbrYT36jPTwI("%z &", jL3jQr);
    GpgIm0JB5Ju = yqrSGpuBfKn(jL3jQr);
    if( GpgIm0JB5Ju ) IqpFG("system() fails with error code %d", GpgIm0JB5Ju);
#else
    {
      S__8mO1NuiTN OtLL;
      Lh8eVlmR EM8g2J04QJv0;
      MFWBCW(&OtLL, 0, sizeof(OtLL));
      OtLL.BhM9xd = sizeof(OtLL);
      MFWBCW(&EM8g2J04QJv0, 0, sizeof(EM8g2J04QJv0));
      GpgIm0JB5Ju = DshTdHsu0GNA(tz9pBH_BXlpJq, jL3jQr, tz9pBH_BXlpJq, tz9pBH_BXlpJq, otAgmDqyXp9kZ, 0, tz9pBH_BXlpJq, tz9pBH_BXlpJq,
                        &OtLL, &EM8g2J04QJv0);
      if( GpgIm0JB5Ju ){
        bR0D8(EM8g2J04QJv0.MTu8YeG);
        bR0D8(EM8g2J04QJv0.EThV9MQu_RCY);
      }else{
        IqpFG("CreateProcessA() fails with error code %lu",
                     H08cF08hVia6());
      }
    }
#endif
    e5JJYyEFK6H(jL3jQr);
  }
}

/*
** Read the entire content of a file into memory
*/
static char *qE8elsWH(const char *ML4W){
  U9mlRrD67J *nq0S6oiSL19m = Dr_1Umb9(ML4W, "rb");
  long ZDnO;
  char *FSyxUsbfMIw;
  if( nq0S6oiSL19m==0 ){
    eiyoMPz88ej("cannot open \"%s\" for reading", ML4W);
  }
  rKxIby5QCh(nq0S6oiSL19m, 0, VkhIs1xEJTr);
  ZDnO = QHaq53XSs8Ia4(nq0S6oiSL19m);
  KpFMBsU4PKc(nq0S6oiSL19m);
  FSyxUsbfMIw = OcQgG( ZDnO+1 );
  ZDnO = (long)i36O(FSyxUsbfMIw, 1, ZDnO, nq0S6oiSL19m);
  FSyxUsbfMIw[ZDnO] = 0;
  Ca8w(nq0S6oiSL19m);
  return FSyxUsbfMIw;
}

/*
** Return the length of the next token.
*/
static int ygK_(const char *FSyxUsbfMIw, int *bSLorsflVLm){
  int xlx5XO = 0;
  if( viK34(FSyxUsbfMIw[0]) || (FSyxUsbfMIw[0]=='/' && FSyxUsbfMIw[1]=='*') ){
    int Bxp1rL = 0;
    int Xp4SRspUEoh7_;
    if( FSyxUsbfMIw[0]=='/' ){
      Bxp1rL = 1;
      xlx5XO = 2;
    }
    while( (Xp4SRspUEoh7_ = FSyxUsbfMIw[xlx5XO++])!=0 ){
      if( Xp4SRspUEoh7_=='\n' ) (*bSLorsflVLm)++;
      if( viK34(Xp4SRspUEoh7_) ) continue;
      if( Bxp1rL && Xp4SRspUEoh7_=='*' && FSyxUsbfMIw[xlx5XO]=='/' ){
        xlx5XO++;
        Bxp1rL = 0;
      }else if( !Bxp1rL && Xp4SRspUEoh7_=='/' && FSyxUsbfMIw[xlx5XO]=='*' ){
        xlx5XO++;
        Bxp1rL = 1;
      }else if( !Bxp1rL ){
        break;
      }
    }
    xlx5XO--;
  }else if( FSyxUsbfMIw[0]=='-' && FSyxUsbfMIw[1]=='-' ){
    for(xlx5XO=2; FSyxUsbfMIw[xlx5XO] && FSyxUsbfMIw[xlx5XO]!='\n'; xlx5XO++){}
    if( FSyxUsbfMIw[xlx5XO] ){ (*bSLorsflVLm)++; xlx5XO++; }
  }else if( FSyxUsbfMIw[0]=='"' || FSyxUsbfMIw[0]=='\'' ){
    int Ldj8bHMG7 = FSyxUsbfMIw[0];
    for(xlx5XO=1; FSyxUsbfMIw[xlx5XO]; xlx5XO++){
      if( FSyxUsbfMIw[xlx5XO]=='\n' ) (*bSLorsflVLm)++;
      if( FSyxUsbfMIw[xlx5XO]==Ldj8bHMG7 ){
        xlx5XO++;
        if( FSyxUsbfMIw[xlx5XO+1]!=Ldj8bHMG7 ) break;
      }
    }
  }else{
    int Xp4SRspUEoh7_;
    for(xlx5XO=1; (Xp4SRspUEoh7_ = FSyxUsbfMIw[xlx5XO])!=0 && !viK34(Xp4SRspUEoh7_) && Xp4SRspUEoh7_!='"' && Xp4SRspUEoh7_!='\'' && Xp4SRspUEoh7_!=';'; xlx5XO++){}
  }
  return xlx5XO;
}

/*
** Copy a single token into a string buffer.
*/
static int mFUE(const char *RWQSPjfsU, int ar16Et, char *vQBue, int LoZNmygq){
  int suqkIzKE;
  if( ar16Et<=0 ){
    vQBue[0] = 0;
    return 0;
  }
  for(suqkIzKE=0; suqkIzKE<ar16Et && suqkIzKE<LoZNmygq-1 && !viK34(RWQSPjfsU[suqkIzKE]); suqkIzKE++){ vQBue[suqkIzKE] = RWQSPjfsU[suqkIzKE]; }
  vQBue[suqkIzKE] = 0;
  return suqkIzKE;
}

/*
** Find the number of characters up to the start of the next "--end" token.
*/
static int NWIT(const char *FSyxUsbfMIw, int *bSLorsflVLm){
  int xlx5XO = 0;
  while( FSyxUsbfMIw[xlx5XO] && (t78H(FSyxUsbfMIw+xlx5XO,"--end",5) || !viK34(FSyxUsbfMIw[xlx5XO+5])) ){
    xlx5XO += ygK_(FSyxUsbfMIw+xlx5XO, bSLorsflVLm);
  }
  return xlx5XO;
}

/*
** Find the number of characters up to the first character past the
** of the next "--endif"  or "--else" token. Nested --if commands are
** also skipped.
*/
static int PglgopQkGj(const char *FSyxUsbfMIw, int EtNQEnb3, int *bSLorsflVLm){
  int xlx5XO = 0;
  while( FSyxUsbfMIw[xlx5XO] ){
    int CoYg2omnE5BYl = ygK_(FSyxUsbfMIw+xlx5XO, bSLorsflVLm);
    if( (t78H(FSyxUsbfMIw+xlx5XO,"--endif",7)==0 && viK34(FSyxUsbfMIw[xlx5XO+7]))
     || (EtNQEnb3 && t78H(FSyxUsbfMIw+xlx5XO,"--else",6)==0 && viK34(FSyxUsbfMIw[xlx5XO+6]))
    ){
      return xlx5XO+CoYg2omnE5BYl;
    }
    if( t78H(FSyxUsbfMIw+xlx5XO,"--if",4)==0 && viK34(FSyxUsbfMIw[xlx5XO+4]) ){
      int HCw3 = PglgopQkGj(FSyxUsbfMIw+xlx5XO+CoYg2omnE5BYl, 0, bSLorsflVLm);
      xlx5XO += HCw3 + CoYg2omnE5BYl;
    }else{
      xlx5XO += CoYg2omnE5BYl;
    }
  }
  return xlx5XO;
}

/*
** Wait for a client process to complete all its tasks
*/
static void hNHT(int PLYayS, int TVqnJyHFl, char *pTDUsvL6liJ5Z){
  vdvsGjGiCTLQ7 *zQNUMAL1;
  int GpgIm0JB5Ju;
  if( PLYayS>0 ){
    zQNUMAL1 = f_Xm(
               "SELECT 1 FROM task"
               " WHERE client=%d"
               "   AND client IN (SELECT id FROM client)"
               "  AND endtime IS NULL",
               PLYayS);
  }else{
    zQNUMAL1 = f_Xm(
               "SELECT 1 FROM task"
               " WHERE client IN (SELECT id FROM client)"
               "   AND endtime IS NULL");
  }
  iqt3PUOA.TVqnJyHFl = 0;
  while( ((GpgIm0JB5Ju = yWPz_DwgJB0M(zQNUMAL1))==T3kfuG7M3l2 || GpgIm0JB5Ju==LupLik)
    && TVqnJyHFl>0
  ){
    AKMH(zQNUMAL1);
    Zue_0(50);
    TVqnJyHFl -= 50;
  }
  dBe7jJnhE(zQNUMAL1);
  iqt3PUOA.TVqnJyHFl = XHwXk3R;
  if( GpgIm0JB5Ju!=MDNkVejs_YO80 ){
    if( pTDUsvL6liJ5Z==0 ) pTDUsvL6liJ5Z = "";
    if( PLYayS>0 ){
      IqpFG("%stimeout waiting for client %d", pTDUsvL6liJ5Z, PLYayS);
    }else{
      IqpFG("%stimeout waiting for all clients", pTDUsvL6liJ5Z);
    }
  }
}

/* Return a pointer to the tail of a filename
*/
static char *RjerEl(char *FSyxUsbfMIw){
  int suqkIzKE, o486PGhP;
  for(suqkIzKE=o486PGhP=0; FSyxUsbfMIw[suqkIzKE]; suqkIzKE++) if( y8vNjL(FSyxUsbfMIw[suqkIzKE]) ) o486PGhP = suqkIzKE+1;
  return FSyxUsbfMIw+o486PGhP;
}

/*
** Interpret zArg as a boolean value.  Return either 0 or 1.
*/
static int u7Nw9dhfzQu(char *ouu3VMV2i2){
  int suqkIzKE;
  if( ouu3VMV2i2==0 ) return 0;
  for(suqkIzKE=0; ouu3VMV2i2[suqkIzKE]>='0' && ouu3VMV2i2[suqkIzKE]<='9'; suqkIzKE++){}
  if( suqkIzKE>0 && ouu3VMV2i2[suqkIzKE]==0 ) return beePPbXXI(ouu3VMV2i2);
  if( fYlwL(ouu3VMV2i2, "on")==0 || fYlwL(ouu3VMV2i2,"yes")==0 ){
    return 1;
  }
  if( fYlwL(ouu3VMV2i2, "off")==0 || fYlwL(ouu3VMV2i2,"no")==0 ){
    return 0;
  }
  IqpFG("unknown boolean: [%s]", ouu3VMV2i2);
  return 0;
}


/* This routine exists as a convenient place to set a debugger
** breakpoint.
*/
static void UaYexgB(void){ static volatile int YpneUmG2tP = 0; YpneUmG2tP++; }

/* Maximum number of arguments to a --command */
#define DWik 2

/*
** Run a script.
*/
static void iR0DKbuzCiWaQ(
  int PLYayS,       /* The client number, or 0 for the master */
  int fy_Gf,        /* The task ID for clients.  0 for master */
  char *E_fSV,     /* Text of the script */
  char *ML4W    /* File from which script was read. */
){
  int BuuXr3yfG = 1;
  int GvHC0swNE2Xe = 1;
  int BJwARu = 0;
  int jq79peoq9K = 0;
  int xlx5XO, Xp4SRspUEoh7_, o486PGhP;
  int CoYg2omnE5BYl;
  int n6ocGEFM;
  H1D_XH ZmQK7_hQ6KBBx;
  char jSsbHfaowC[30];
  char eqPBysmumWOcq[1000];
  char NgyeueKQjD0q_[DWik][100];

  MFWBCW(&ZmQK7_hQ6KBBx, 0, sizeof(ZmQK7_hQ6KBBx));
  P3BKUT(&ZmQK7_hQ6KBBx);
  while( (Xp4SRspUEoh7_ = E_fSV[BJwARu])!=0 ){
    GvHC0swNE2Xe = BuuXr3yfG;
    CoYg2omnE5BYl = ygK_(E_fSV+BJwARu, &BuuXr3yfG);
    if( viK34(Xp4SRspUEoh7_) || (Xp4SRspUEoh7_=='/' && E_fSV[BJwARu+1]=='*') ){
      BJwARu += CoYg2omnE5BYl;
      continue;
    }
    if( Xp4SRspUEoh7_!='-' || E_fSV[BJwARu+1]!='-' || !VnQk(E_fSV[BJwARu+2]) ){
      BJwARu += CoYg2omnE5BYl;
      continue;
    }

    /* Run any prior SQL before processing the new --command */
    if( BJwARu>jq79peoq9K ){
      char *I87WfKZvHyqJO = PgbrYT36jPTwI("%.*s", BJwARu-jq79peoq9K, E_fSV+jq79peoq9K);
      CkoT15Q(&ZmQK7_hQ6KBBx, I87WfKZvHyqJO);
      e5JJYyEFK6H(I87WfKZvHyqJO);
      jq79peoq9K = BJwARu + CoYg2omnE5BYl;
    }

    /* Parse the --command */
    if( iqt3PUOA.evuvgONcursa>=2 ) i2hSCL9("%.*s", CoYg2omnE5BYl, E_fSV+BJwARu);
    xlx5XO = mFUE(E_fSV+BJwARu+2, CoYg2omnE5BYl-2, jSsbHfaowC, sizeof(jSsbHfaowC));
    for(n6ocGEFM=0; xlx5XO<CoYg2omnE5BYl-2 && n6ocGEFM<DWik; n6ocGEFM++){
      while( xlx5XO<CoYg2omnE5BYl-2 && viK34(E_fSV[BJwARu+2+xlx5XO]) ){ xlx5XO++; }
      if( xlx5XO>=CoYg2omnE5BYl-2 ) break;
      xlx5XO += mFUE(E_fSV+BJwARu+2+xlx5XO, CoYg2omnE5BYl-2-xlx5XO,
                        NgyeueKQjD0q_[n6ocGEFM], sizeof(NgyeueKQjD0q_[n6ocGEFM]));
    }
    for(o486PGhP=n6ocGEFM; o486PGhP<DWik; o486PGhP++) NgyeueKQjD0q_[o486PGhP++][0] = 0;

    /*
    **  --sleep N
    **
    ** Pause for N milliseconds
    */
    if( NqYfdGATpR(jSsbHfaowC, "sleep")==0 ){
      Zue_0(beePPbXXI(NgyeueKQjD0q_[0]));
    }else 

    /*
    **   --exit N
    **
    ** Exit this process.  If N>0 then exit without shutting down
    ** SQLite.  (In other words, simulate a crash.)
    */
    if( NqYfdGATpR(jSsbHfaowC, "exit")==0 ){
      int GpgIm0JB5Ju = beePPbXXI(NgyeueKQjD0q_[0]);
      rKBKhUu(PLYayS, fy_Gf, 1);
      if( GpgIm0JB5Ju==0 ) PDedj(iqt3PUOA.JaS2gV8D7Ir);
      jivfJd4VzG(GpgIm0JB5Ju);
    }else

    /*
    **   --testcase NAME
    **
    ** Begin a new test case.  Announce in the log that the test case
    ** has begun.
    */
    if( NqYfdGATpR(jSsbHfaowC, "testcase")==0 ){
      if( iqt3PUOA.evuvgONcursa==1 ) i2hSCL9("%.*s", CoYg2omnE5BYl - 1, E_fSV+BJwARu);
      P3BKUT(&ZmQK7_hQ6KBBx);
    }else

    /*
    **   --finish
    **
    ** Mark the current task as having finished, even if it is not.
    ** This can be used in conjunction with --exit to simulate a crash.
    */
    if( NqYfdGATpR(jSsbHfaowC, "finish")==0 && PLYayS>0 ){
      rKBKhUu(PLYayS, fy_Gf, 1);
    }else

    /*
    **  --reset
    **
    ** Reset accumulated results back to an empty string
    */
    if( NqYfdGATpR(jSsbHfaowC, "reset")==0 ){
      P3BKUT(&ZmQK7_hQ6KBBx);
    }else

    /*
    **  --match ANSWER...
    **
    ** Check to see if output matches ANSWER.  Report an error if not.
    */
    if( NqYfdGATpR(jSsbHfaowC, "match")==0 ){
      int PsNLfTy;
      char *Z5zAeLyo = E_fSV+BJwARu;
      for(PsNLfTy=7; PsNLfTy<CoYg2omnE5BYl-1 && viK34(Z5zAeLyo[PsNLfTy]); PsNLfTy++){}
      Z5zAeLyo += PsNLfTy;
      if( CoYg2omnE5BYl-PsNLfTy-1!=ZmQK7_hQ6KBBx.xlx5XO || t78H(ZmQK7_hQ6KBBx.FSyxUsbfMIw, Z5zAeLyo, CoYg2omnE5BYl-PsNLfTy-1) ){
        IqpFG("line %d of %s:\nExpected [%.*s]\n     Got [%s]",
          GvHC0swNE2Xe, ML4W, CoYg2omnE5BYl-PsNLfTy-1, Z5zAeLyo, ZmQK7_hQ6KBBx.FSyxUsbfMIw);
      }
      iqt3PUOA.kJIO5Cc3pyb++;
      P3BKUT(&ZmQK7_hQ6KBBx);
    }else

    /*
    **  --glob ANSWER...
    **  --notglob ANSWER....
    **
    ** Check to see if output does or does not match the glob pattern
    ** ANSWER.
    */
    if( NqYfdGATpR(jSsbHfaowC, "glob")==0 || NqYfdGATpR(jSsbHfaowC, "notglob")==0 ){
      int PsNLfTy;
      char *Z5zAeLyo = E_fSV+BJwARu;
      char *eAGXWz;
      int ktxr_0TpVxnu = (jSsbHfaowC[0]=='g');
      for(PsNLfTy=9-3*ktxr_0TpVxnu; PsNLfTy<CoYg2omnE5BYl-1 && viK34(Z5zAeLyo[PsNLfTy]); PsNLfTy++){}
      Z5zAeLyo += PsNLfTy;
      eAGXWz = PgbrYT36jPTwI("%.*s", CoYg2omnE5BYl-PsNLfTy-1, Z5zAeLyo);
      if( (GS1xp(eAGXWz, ZmQK7_hQ6KBBx.FSyxUsbfMIw)==0)^ktxr_0TpVxnu ){
        IqpFG("line %d of %s:\nExpected [%s]\n     Got [%s]",
          GvHC0swNE2Xe, ML4W, eAGXWz, ZmQK7_hQ6KBBx.FSyxUsbfMIw);
      }
      e5JJYyEFK6H(eAGXWz);
      iqt3PUOA.kJIO5Cc3pyb++;
      P3BKUT(&ZmQK7_hQ6KBBx);
    }else

    /*
    **  --output
    **
    ** Output the result of the previous SQL.
    */
    if( NqYfdGATpR(jSsbHfaowC, "output")==0 ){
      i2hSCL9("%s", ZmQK7_hQ6KBBx.FSyxUsbfMIw);
    }else

    /*
    **  --source FILENAME
    **
    ** Run a subscript from a separate file.
    */
    if( NqYfdGATpR(jSsbHfaowC, "source")==0 ){
      char *M3Yp6V5eZlYA, *lpYNkfpqciQB;
      char *rMKhR9 = 0;
      M3Yp6V5eZlYA = NgyeueKQjD0q_[0];
      if( !y8vNjL(M3Yp6V5eZlYA[0]) ){
        int RE3a;
        for(RE3a=(int)SRdm(ML4W)-1; RE3a>=0 && !y8vNjL(ML4W[RE3a]); RE3a--){}
        if( RE3a>0 ){
          M3Yp6V5eZlYA = rMKhR9 = PgbrYT36jPTwI("%.*s/%s", RE3a,ML4W,M3Yp6V5eZlYA);
        }
      }
      lpYNkfpqciQB = qE8elsWH(M3Yp6V5eZlYA);
      if( iqt3PUOA.evuvgONcursa ) i2hSCL9("begin script [%s]\n", M3Yp6V5eZlYA);
      iR0DKbuzCiWaQ(0, 0, lpYNkfpqciQB, M3Yp6V5eZlYA);
      e5JJYyEFK6H(lpYNkfpqciQB);
      if( iqt3PUOA.evuvgONcursa ) i2hSCL9("end script [%s]\n", M3Yp6V5eZlYA);
      e5JJYyEFK6H(rMKhR9);
    }else

    /*
    **  --print MESSAGE....
    **
    ** Output the remainder of the line to the log file
    */
    if( NqYfdGATpR(jSsbHfaowC, "print")==0 ){
      int PsNLfTy;
      for(PsNLfTy=7; PsNLfTy<CoYg2omnE5BYl && viK34(E_fSV[BJwARu+PsNLfTy]); PsNLfTy++){}
      i2hSCL9("%.*s", CoYg2omnE5BYl-PsNLfTy, E_fSV+BJwARu+PsNLfTy);
    }else

    /*
    **  --if EXPR
    **
    ** Skip forward to the next matching --endif or --else if EXPR is false.
    */
    if( NqYfdGATpR(jSsbHfaowC, "if")==0 ){
      int PsNLfTy, GpgIm0JB5Ju;
      vdvsGjGiCTLQ7 *zQNUMAL1;
      for(PsNLfTy=4; PsNLfTy<CoYg2omnE5BYl && viK34(E_fSV[BJwARu+PsNLfTy]); PsNLfTy++){}
      zQNUMAL1 = f_Xm("SELECT %.*s", CoYg2omnE5BYl-PsNLfTy, E_fSV+BJwARu+PsNLfTy);
      GpgIm0JB5Ju = yWPz_DwgJB0M(zQNUMAL1);
      if( GpgIm0JB5Ju!=LupLik || Gjq5DFX(zQNUMAL1, 0)==0 ){
        BJwARu += PglgopQkGj(E_fSV+BJwARu+CoYg2omnE5BYl, 1, &BuuXr3yfG);
      }
      dBe7jJnhE(zQNUMAL1);
    }else

    /*
    **  --else
    **
    ** This command can only be encountered if currently inside an --if that
    ** is true.  Skip forward to the next matching --endif.
    */
    if( NqYfdGATpR(jSsbHfaowC, "else")==0 ){
      BJwARu += PglgopQkGj(E_fSV+BJwARu+CoYg2omnE5BYl, 0, &BuuXr3yfG);
    }else

    /*
    **  --endif
    **
    ** This command can only be encountered if currently inside an --if that
    ** is true or an --else of a false if.  This is a no-op.
    */
    if( NqYfdGATpR(jSsbHfaowC, "endif")==0 ){
      /* no-op */
    }else

    /*
    **  --start CLIENT
    **
    ** Start up the given client.
    */
    if( NqYfdGATpR(jSsbHfaowC, "start")==0 && PLYayS==0 ){
      int hH3EBcngtUC = beePPbXXI(NgyeueKQjD0q_[0]);
      if( hH3EBcngtUC>0 ){
        a9WP6p9aHD(hH3EBcngtUC);
      }
    }else

    /*
    **  --wait CLIENT TIMEOUT
    **
    ** Wait until all tasks complete for the given client.  If CLIENT is
    ** "all" then wait for all clients to complete.  Wait no longer than
    ** TIMEOUT milliseconds (default 10,000)
    */
    if( NqYfdGATpR(jSsbHfaowC, "wait")==0 && PLYayS==0 ){
      int TVqnJyHFl = n6ocGEFM>=2 ? beePPbXXI(NgyeueKQjD0q_[1]) : 10000;
      vzDX5yBB(sizeof(eqPBysmumWOcq),eqPBysmumWOcq,"line %d of %s\n",
                       GvHC0swNE2Xe, ML4W);
      hNHT(beePPbXXI(NgyeueKQjD0q_[0]), TVqnJyHFl, eqPBysmumWOcq);
    }else

    /*
    **  --task CLIENT
    **     <task-content-here>
    **  --end
    **
    ** Assign work to a client.  Start the client if it is not running
    ** already.
    */
    if( NqYfdGATpR(jSsbHfaowC, "task")==0 && PLYayS==0 ){
      int CtinVyn8kiF = beePPbXXI(NgyeueKQjD0q_[0]);
      int L5WokC5RSp;
      char *H6T4yrHaM;
      char *X4gLE9A;
      L5WokC5RSp = NWIT(E_fSV+BJwARu+CoYg2omnE5BYl, &BuuXr3yfG);
      if( CtinVyn8kiF<0 ){
        IqpFG("line %d of %s: bad client number: %d",
                     GvHC0swNE2Xe, ML4W, CtinVyn8kiF);
      }else{
        H6T4yrHaM = PgbrYT36jPTwI("%.*s", L5WokC5RSp, E_fSV+BJwARu+CoYg2omnE5BYl);
        if( n6ocGEFM>1 ){
          X4gLE9A = PgbrYT36jPTwI("%s", NgyeueKQjD0q_[1]);
        }else{
          X4gLE9A = PgbrYT36jPTwI("%s:%d", RjerEl(ML4W), GvHC0swNE2Xe);
        }
        a9WP6p9aHD(CtinVyn8kiF);
        EPHw68Wr8r("INSERT INTO task(client,script,name)"
               " VALUES(%d,'%q',%Q)", CtinVyn8kiF, H6T4yrHaM, X4gLE9A);
        e5JJYyEFK6H(H6T4yrHaM);
        e5JJYyEFK6H(X4gLE9A);
      }
      L5WokC5RSp += ygK_(E_fSV+BJwARu+CoYg2omnE5BYl+L5WokC5RSp, &BuuXr3yfG);
      CoYg2omnE5BYl += L5WokC5RSp;
      jq79peoq9K = BJwARu+CoYg2omnE5BYl;
    }else

    /*
    **  --breakpoint
    **
    ** This command calls "test_breakpoint()" which is a routine provided
    ** as a convenient place to set a debugger breakpoint.
    */
    if( NqYfdGATpR(jSsbHfaowC, "breakpoint")==0 ){
      UaYexgB();
    }else

    /*
    **  --show-sql-errors BOOLEAN
    **
    ** Turn display of SQL errors on and off.
    */
    if( NqYfdGATpR(jSsbHfaowC, "show-sql-errors")==0 ){
      iqt3PUOA.jaK7I = n6ocGEFM>=1 ? !u7Nw9dhfzQu(NgyeueKQjD0q_[0]) : 1;
    }else


    /* error */{
      IqpFG("line %d of %s: unknown command --%s",
                   GvHC0swNE2Xe, ML4W, jSsbHfaowC);
    }
    BJwARu += CoYg2omnE5BYl;
  }
  if( jq79peoq9K<BJwARu ){
    char *I87WfKZvHyqJO = PgbrYT36jPTwI("%.*s", BJwARu-jq79peoq9K, E_fSV+jq79peoq9K);
    EPHw68Wr8r(I87WfKZvHyqJO);
    e5JJYyEFK6H(I87WfKZvHyqJO);
  }
  vTL4MxXr(&ZmQK7_hQ6KBBx);
}

/*
** Look for a command-line option.  If present, return a pointer.
** Return NULL if missing.
**
** hasArg==0 means the option is a flag.  It is either present or not.
** hasArg==1 means the option has an argument.  Return a pointer to the
** argument.
*/
static char *L5uV8KZ(
  char **NgyeueKQjD0q_,
  int *NzxLxPpWEnZ,
  const char *fkck_,
  int YFEWm
){
  int suqkIzKE, o486PGhP;
  char *XF9OgE = 0;
  int n6ocGEFM = *NzxLxPpWEnZ;

  GVjT( YFEWm==0 || YFEWm==1 );
  for(suqkIzKE=0; suqkIzKE<n6ocGEFM; suqkIzKE++){
    const char *FSyxUsbfMIw;
    if( suqkIzKE+YFEWm >= n6ocGEFM ) break;
    FSyxUsbfMIw = NgyeueKQjD0q_[suqkIzKE];
    if( FSyxUsbfMIw[0]!='-' ) continue;
    FSyxUsbfMIw++;
    if( FSyxUsbfMIw[0]=='-' ){
      if( FSyxUsbfMIw[1]==0 ) break;
      FSyxUsbfMIw++;
    }
    if( NqYfdGATpR(FSyxUsbfMIw,fkck_)==0 ){
      if( YFEWm && suqkIzKE==n6ocGEFM-1 ){
        eiyoMPz88ej("command-line option \"--%s\" requires an argument", FSyxUsbfMIw);
      }
      if( YFEWm ){
        XF9OgE = NgyeueKQjD0q_[suqkIzKE+1];
      }else{
        XF9OgE = NgyeueKQjD0q_[suqkIzKE];
      }
      o486PGhP = suqkIzKE+1+(YFEWm!=0);
      while( o486PGhP<n6ocGEFM ) NgyeueKQjD0q_[suqkIzKE++] = NgyeueKQjD0q_[o486PGhP++];
      *NzxLxPpWEnZ = suqkIzKE;
      return XF9OgE;
    }
  }
  return XF9OgE;
}

/* Print a usage message for the program and exit */
static void htjn(const char *sfVdY8x8M4DX){
  int suqkIzKE;
  const char *cWnzX6Lb = sfVdY8x8M4DX;
  for(suqkIzKE=0; sfVdY8x8M4DX[suqkIzKE]; suqkIzKE++){
    if( y8vNjL(sfVdY8x8M4DX[suqkIzKE]) ) cWnzX6Lb = sfVdY8x8M4DX+suqkIzKE+1;
  }
  dwntm(iuGkM,"Usage: %s DATABASE ?OPTIONS? ?SCRIPT?\n", cWnzX6Lb);
  dwntm(iuGkM,
    "Options:\n"
    "   --errlog FILENAME           Write errors to FILENAME\n"
    "   --journalmode MODE          Use MODE as the journal_mode\n"
    "   --log FILENAME              Log messages to FILENAME\n"
    "   --quiet                     Suppress unnecessary output\n"
    "   --vfs NAME                  Use NAME as the VFS\n"
    "   --repeat N                  Repeat the test N times\n"
    "   --sqltrace                  Enable SQL tracing\n"
    "   --sync                      Enable synchronous disk writes\n"
    "   --timeout MILLISEC          Busy timeout is MILLISEC\n"
    "   --trace BOOLEAN             Enable or disable tracing\n"
  );
  jivfJd4VzG(1);
}

/* Report on unrecognized arguments */
static void x9CcHwm0hrPc_(
  const char *sfVdY8x8M4DX,
  int n6ocGEFM,
  char **NgyeueKQjD0q_
){
  int suqkIzKE;
  dwntm(iuGkM,"%s: unrecognized arguments:", sfVdY8x8M4DX);
  for(suqkIzKE=0; suqkIzKE<n6ocGEFM; suqkIzKE++){
    dwntm(iuGkM," %s", NgyeueKQjD0q_[suqkIzKE]);
  }
  dwntm(iuGkM,"\n");
  jivfJd4VzG(1);
}

int TTho s6xaCTyInfXM3(int uspfoXjfrf5ug, char **GQakBQnO){
  const char *NkbkM1Rb3Bh;
  int PLYayS;
  int xlx5XO, suqkIzKE;
  int q4XX4vVzIAM = csNJCO;
  int GpgIm0JB5Ju;
  char *E_fSV;
  int fy_Gf;
  const char *t5bZpP;
  const char *blzH2XSqv6swE;
  const char *mTUOaFRLE;
  const char *Rsv9mtZ;
  int glH2 = 1, h0QtUoepIDp34;
  int I4xDYmPXw = 0;              /* Default: no timeout */
  const char *Uboe8yQuyjPaI;

  iqt3PUOA.sfVdY8x8M4DX = GQakBQnO[0];
  iqt3PUOA.evuvgONcursa = 1;
  if( uspfoXjfrf5ug<2 ) htjn(GQakBQnO[0]);
  iqt3PUOA.yAYeeS1uhw2 = GQakBQnO[1];
  if( ElY25o("*.test", iqt3PUOA.yAYeeS1uhw2) ) htjn(GQakBQnO[0]);
  if( NqYfdGATpR(dn2D1Sl(), k2vA)!=0 ){
    dwntm(iuGkM, "SQLite library and header mismatch\n"
                    "Library: %s\n"
                    "Header:  %s\n",
                    dn2D1Sl(), k2vA);
    jivfJd4VzG(1);
  }
  xlx5XO = uspfoXjfrf5ug-2;
  vzDX5yBB(sizeof(iqt3PUOA.E0X_h6DW3979), iqt3PUOA.E0X_h6DW3979, "%05d.mptest", NkgIW());
  mTUOaFRLE = L5uV8KZ(GQakBQnO+2, &xlx5XO, "journalmode", 1);
  Rsv9mtZ = L5uV8KZ(GQakBQnO+2, &xlx5XO, "repeat", 1);
  if( Rsv9mtZ ) glH2 = beePPbXXI(Rsv9mtZ);
  if( glH2<1 ) glH2 = 1;
  iqt3PUOA.IlQ6tK = L5uV8KZ(GQakBQnO+2, &xlx5XO, "vfs", 1);
  NkbkM1Rb3Bh = L5uV8KZ(GQakBQnO+2, &xlx5XO, "client", 1);
  iqt3PUOA.m8u5dhsZ = L5uV8KZ(GQakBQnO+2, &xlx5XO, "errlog", 1);
  iqt3PUOA.EDDX_ = L5uV8KZ(GQakBQnO+2, &xlx5XO, "log", 1);
  t5bZpP = L5uV8KZ(GQakBQnO+2, &xlx5XO, "trace", 1);
  if( t5bZpP ) iqt3PUOA.evuvgONcursa = beePPbXXI(t5bZpP);
  if( L5uV8KZ(GQakBQnO+2, &xlx5XO, "quiet", 0)!=0 ) iqt3PUOA.evuvgONcursa = 0;
  Uboe8yQuyjPaI = L5uV8KZ(GQakBQnO+2, &xlx5XO, "timeout", 1);
  if( Uboe8yQuyjPaI ) I4xDYmPXw = beePPbXXI(Uboe8yQuyjPaI);
  iqt3PUOA.heGZLD = L5uV8KZ(GQakBQnO+2, &xlx5XO, "sqltrace", 0)!=0;
  iqt3PUOA.Hq9_mrs = L5uV8KZ(GQakBQnO+2, &xlx5XO, "sync", 0)!=0;
  if( iqt3PUOA.m8u5dhsZ ){
    iqt3PUOA.w7ek = Dr_1Umb9(iqt3PUOA.m8u5dhsZ, "a");
  }else{
    iqt3PUOA.w7ek = iuGkM;
  }
  if( iqt3PUOA.EDDX_ ){
    iqt3PUOA.xfxG8GvLOO = Dr_1Umb9(iqt3PUOA.EDDX_, "a");
  }else{
    iqt3PUOA.xfxG8GvLOO = HuhDAz1iY;
  }
  
  jq1cysX1(C6lFp, WgExD31oRA, 0);
  if( NkbkM1Rb3Bh ){
    PLYayS = beePPbXXI(NkbkM1Rb3Bh);
    if( PLYayS<1 ) eiyoMPz88ej("illegal client number: %d\n", PLYayS);
    vzDX5yBB(sizeof(iqt3PUOA.E0X_h6DW3979), iqt3PUOA.E0X_h6DW3979, "%05d.client%02d",
                     NkgIW(), PLYayS);
  }else{
    int IwDlX = 0;
    if( iqt3PUOA.evuvgONcursa>0 ){
      COrK_fhblCaq("BEGIN: %s", GQakBQnO[0]);
      for(suqkIzKE=1; suqkIzKE<uspfoXjfrf5ug; suqkIzKE++) COrK_fhblCaq(" %s", GQakBQnO[suqkIzKE]);
      COrK_fhblCaq("\n");
      COrK_fhblCaq("With SQLite " XqtfkODWbP " " k2vA "\n" );
      for(suqkIzKE=0; (blzH2XSqv6swE = Te9_WSpaOpm(suqkIzKE))!=0; suqkIzKE++){
        COrK_fhblCaq("-DSQLITE_%s\n", blzH2XSqv6swE);
      }
      H9YJzz4(HuhDAz1iY);
    }
    PLYayS =  0;
    do{
      if( (IwDlX%5)==4 ) COrK_fhblCaq("... %strying to unlink '%s'\n",
                               IwDlX>5 ? "still " : "", iqt3PUOA.yAYeeS1uhw2);
      GpgIm0JB5Ju = asfqy6(iqt3PUOA.yAYeeS1uhw2);
      if( GpgIm0JB5Ju && xs2FiIh==hQY0 ) GpgIm0JB5Ju = 0;
    }while( GpgIm0JB5Ju!=0 && (++IwDlX)<60 && Zue_0(1000)>0 );
    if( GpgIm0JB5Ju!=0 ){
      eiyoMPz88ej("unable to unlink '%s' after %d attempts\n",
                 iqt3PUOA.yAYeeS1uhw2, IwDlX);
    }
    q4XX4vVzIAM |= VVT6;
  }
  GpgIm0JB5Ju = hli9CTc2J(iqt3PUOA.yAYeeS1uhw2, &iqt3PUOA.JaS2gV8D7Ir, q4XX4vVzIAM, iqt3PUOA.IlQ6tK);
  if( GpgIm0JB5Ju ) eiyoMPz88ej("cannot open [%s]", iqt3PUOA.yAYeeS1uhw2);
  if( I4xDYmPXw>0 ) kTcL_FQwn(iqt3PUOA.JaS2gV8D7Ir, I4xDYmPXw);
  
  if( mTUOaFRLE ){
#if R1kaM(tT_6v)
    if( fYlwL(mTUOaFRLE,"persist")==0
     || fYlwL(mTUOaFRLE,"truncate")==0
    ){
      COrK_fhblCaq("Changing journal mode to DELETE from %s", mTUOaFRLE);
      mTUOaFRLE = "DELETE";
    }
#endif
    EPHw68Wr8r("PRAGMA journal_mode=%Q;", mTUOaFRLE);
  }
  if( !iqt3PUOA.Hq9_mrs ) Qs85RI4A5O("PRAGMA synchronous=OFF");
  sGp77rYMUsX(iqt3PUOA.JaS2gV8D7Ir, 1);
  Eho7d9PKXwTrr(iqt3PUOA.JaS2gV8D7Ir, BJW4, 0);
  CMhV(iqt3PUOA.JaS2gV8D7Ir, "vfsname", 0, O2E6onymtiRX, 0,
                          fB_uo, 0, 0);
  CMhV(iqt3PUOA.JaS2gV8D7Ir, "eval", 1, O2E6onymtiRX, 0,
                          Zd7jq8qIz, 0, 0);
  iqt3PUOA.TVqnJyHFl = XHwXk3R;
  if( iqt3PUOA.heGZLD ) N4RGGyCTrKgO(iqt3PUOA.JaS2gV8D7Ir, mxskAYWr9B6, 0);
  if( PLYayS>0 ){
    if( xlx5XO>0 ) x9CcHwm0hrPc_(GQakBQnO[0], xlx5XO, GQakBQnO+2);
    if( iqt3PUOA.evuvgONcursa ) i2hSCL9("start-client");
    while(1){
      char *NRnkSY7 = 0;
      GpgIm0JB5Ju = zydVMjvQCCy(PLYayS, &E_fSV, &fy_Gf, &NRnkSY7);
      if( GpgIm0JB5Ju==MDNkVejs_YO80 ) break;
      if( iqt3PUOA.evuvgONcursa ) i2hSCL9("begin %s (%d)", NRnkSY7, fy_Gf);
      iR0DKbuzCiWaQ(PLYayS, fy_Gf, E_fSV, NRnkSY7);
      if( iqt3PUOA.evuvgONcursa ) i2hSCL9("end %s (%d)", NRnkSY7, fy_Gf);
      rKBKhUu(PLYayS, fy_Gf, 0);
      e5JJYyEFK6H(NRnkSY7);
      Zue_0(10);
    }
    if( iqt3PUOA.evuvgONcursa ) i2hSCL9("end-client");
  }else{
    vdvsGjGiCTLQ7 *zQNUMAL1;
    int TVqnJyHFl;
    if( xlx5XO==0 ){
      eiyoMPz88ej("missing script filename");
    }
    if( xlx5XO>1 ) x9CcHwm0hrPc_(GQakBQnO[0], xlx5XO, GQakBQnO+2);
    EPHw68Wr8r(
      "DROP TABLE IF EXISTS task;\n"
      "DROP TABLE IF EXISTS counters;\n"
      "DROP TABLE IF EXISTS client;\n"
      "CREATE TABLE task(\n"
      "  id INTEGER PRIMARY KEY,\n"
      "  name TEXT,\n"
      "  client INTEGER,\n"
      "  starttime DATE,\n"
      "  endtime DATE,\n"
      "  script TEXT\n"
      ");"
      "CREATE INDEX task_i1 ON task(client, starttime);\n"
      "CREATE INDEX task_i2 ON task(client, endtime);\n"
      "CREATE TABLE counters(nError,nTest);\n"
      "INSERT INTO counters VALUES(0,0);\n"
      "CREATE TABLE client(id INTEGER PRIMARY KEY, wantHalt);\n"
    );
    E_fSV = qE8elsWH(GQakBQnO[2]);
    for(h0QtUoepIDp34=1; h0QtUoepIDp34<=glH2; h0QtUoepIDp34++){
      if( iqt3PUOA.evuvgONcursa ) i2hSCL9("begin script [%s] cycle %d\n", GQakBQnO[2], h0QtUoepIDp34);
      iR0DKbuzCiWaQ(0, 0, E_fSV, GQakBQnO[2]);
      if( iqt3PUOA.evuvgONcursa ) i2hSCL9("end script [%s] cycle %d\n", GQakBQnO[2], h0QtUoepIDp34);
    }
    e5JJYyEFK6H(E_fSV);
    hNHT(0, 2000, "during shutdown...\n");
    Qs85RI4A5O("UPDATE client SET wantHalt=1");
    Zue_0(10);
    iqt3PUOA.TVqnJyHFl = 0;
    TVqnJyHFl = 1000;
    while( ((GpgIm0JB5Ju = Qs85RI4A5O("SELECT 1 FROM client"))==T3kfuG7M3l2
        || GpgIm0JB5Ju==LupLik) && TVqnJyHFl>0 ){
      Zue_0(10);
      TVqnJyHFl -= 10;
    }
    Zue_0(100);
    zQNUMAL1 = f_Xm("SELECT nError, nTest FROM counters");
    TVqnJyHFl = 1000;
    while( (GpgIm0JB5Ju = yWPz_DwgJB0M(zQNUMAL1))==T3kfuG7M3l2 && TVqnJyHFl>0 ){
      Zue_0(10);
      TVqnJyHFl -= 10;
    }
    if( GpgIm0JB5Ju==LupLik ){
      iqt3PUOA.zzHq3Ty8Gw += Gjq5DFX(zQNUMAL1, 0);
      iqt3PUOA.kJIO5Cc3pyb += Gjq5DFX(zQNUMAL1, 1);
    }
    dBe7jJnhE(zQNUMAL1);
  }
  PDedj(iqt3PUOA.JaS2gV8D7Ir);
  asCA22uoDU8(iqt3PUOA.xfxG8GvLOO);
  asCA22uoDU8(iqt3PUOA.w7ek);
  if( PLYayS==0 ){
    COrK_fhblCaq("Summary: %d errors out of %d tests\n", iqt3PUOA.zzHq3Ty8Gw, iqt3PUOA.kJIO5Cc3pyb);
    COrK_fhblCaq("END: %s", GQakBQnO[0]);
    for(suqkIzKE=1; suqkIzKE<uspfoXjfrf5ug; suqkIzKE++) COrK_fhblCaq(" %s", GQakBQnO[suqkIzKE]);
    COrK_fhblCaq("\n");
  }
  return iqt3PUOA.zzHq3Ty8Gw>0;
}
