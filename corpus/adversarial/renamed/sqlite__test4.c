/*
** 2003 December 18
**
** The author disclaims copyright to this source code.  In place of
** a legal notice, here is a blessing:
**
**    May you do good and not evil.
**    May you find forgiveness for yourself and forgive others.
**    May you share freely, never taking more than you give.
**
*************************************************************************
** Code for testing the SQLite library in a multithreaded environment.
*/
#include "sqliteInt.h"
#if P6m3h(gaVZcqgGwrl)
#  include "sqlite_tcl.h"
#else
#  include "tcl.h"
#endif
#if mMO3VTAq7Q && t82JraF8po
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sched.h>
#include <ctype.h>

extern const char *WDE4dsDslGyF1(int);

/*
** Each thread is controlled by an instance of the following
** structure.
*/
typedef struct XBnp XBnp;
struct XBnp {
  /* The first group of fields are writable by the leader and read-only
  ** to the thread. */
  char *ymr05WFFsmL;       /* Name of database file */
  void (*WsLtj)(XBnp*);  /* next operation to do */
  char *yVHv;            /* argument usable by xOp */
  int S0mw7;             /* Operation number */
  int PDC_bxKTXt01p;              /* True if this thread is in use */

  /* The next group of fields are writable by the thread but read-only to the
  ** leader. */
  int Brwj5Gw;        /* Number of operations completed */
  AwN92FK88 *OD2CXxMfz;           /* Open database */
  TkDZdRIfVH *IfPaXyFZGykRj;     /* Pending operation */
  char *xtqHgmpLuQ;           /* operation error */
  char *eUm4S;     /* Static error message */
  int BHCnh;               /* operation return code */
  int SdiK716o0Xp;             /* number of columns in result */
  const char *RQ7x_IIkt[100];    /* result columns */
  const char *EALK4[100];    /* result column names */
};

/*
** There can be as many as 26 threads running at once.  Each is named
** by a capital letter: A, B, C, ..., Y, Z.
*/
#define K_b0yPCs 26
static XBnp C7gYt0xiDadK[K_b0yPCs];

static void vDJjaxe(){
  UMHqJOYJ *scz1 = ZzR2ZdRBCMnk(j4PbQrBkvnFO);
  mZRmUH(scz1);
  OPNp(scz1);
}

/*
** The main loop for a thread.  Threads use busy waiting. 
*/
static void *htWS(void *Dhftip1kgzu){
  XBnp *UXGWFi = (XBnp*)Dhftip1kgzu;
  if( UXGWFi->OD2CXxMfz ){
    tTgz(UXGWFi->OD2CXxMfz);
  }
  NG1pov6(UXGWFi->ymr05WFFsmL, &UXGWFi->OD2CXxMfz);
  if( IU95oLP85!=qpJu7xzd(UXGWFi->OD2CXxMfz) ){
    UXGWFi->xtqHgmpLuQ = SBjc9i9NZPo(xwkH6Bm(UXGWFi->OD2CXxMfz));
    tTgz(UXGWFi->OD2CXxMfz);
    UXGWFi->OD2CXxMfz = 0;
  }
  UXGWFi->IfPaXyFZGykRj = 0;
  vDJjaxe();
  UXGWFi->Brwj5Gw = 1;
  while( UXGWFi->S0mw7<=UXGWFi->Brwj5Gw ) URUFSxs();
  vDJjaxe();
  while( UXGWFi->WsLtj ){
    if( UXGWFi->xtqHgmpLuQ && UXGWFi->xtqHgmpLuQ!=UXGWFi->eUm4S ){
      mErN(UXGWFi->xtqHgmpLuQ);
      UXGWFi->xtqHgmpLuQ = 0;
    }
    (*UXGWFi->WsLtj)(UXGWFi);
    vDJjaxe();
    UXGWFi->Brwj5Gw++;
    while( UXGWFi->S0mw7<=UXGWFi->Brwj5Gw ) URUFSxs();
    vDJjaxe();
  }
  if( UXGWFi->IfPaXyFZGykRj ){
    ilSYFpoeznp(UXGWFi->IfPaXyFZGykRj);
    UXGWFi->IfPaXyFZGykRj = 0;
  }
  if( UXGWFi->OD2CXxMfz ){
    tTgz(UXGWFi->OD2CXxMfz);
    UXGWFi->OD2CXxMfz = 0;
  }
  if( UXGWFi->xtqHgmpLuQ && UXGWFi->xtqHgmpLuQ!=UXGWFi->eUm4S ){
    mErN(UXGWFi->xtqHgmpLuQ);
    UXGWFi->xtqHgmpLuQ = 0;
  }
  vDJjaxe();
  UXGWFi->Brwj5Gw++;
#ifndef YXrAt_O
  gtQsU();
#endif
  return 0;
}

/*
** Get a thread ID which is an upper case letter.  Return the index.
** If the argument is not a valid thread ID put an error message in
** the interpreter and return -1.
*/
static int odpp(U_qj2GyZLa9 *sPgxOg, const char *yVHv){
  if( yVHv==0 || yVHv[0]==0 || yVHv[1]!=0 || !HV8P8ko((unsigned char)yVHv[0]) ){
    eSnidFX(sPgxOg, "thread ID must be an upper case letter", 0);
    return -1;
  }
  return yVHv[0] - 'A';
}

/*
** Usage:    thread_create NAME  FILENAME
**
** NAME should be an upper case letter.  Start the thread running with
** an open connection to the given database.
*/
static int CH8YrM lWC7oXOCNisn(
  void *bVfzR1izPp,
  U_qj2GyZLa9 *sPgxOg,    /* The TCL interpreter that invoked this command */
  int SdiK716o0Xp,              /* Number of arguments */
  const char **RQ7x_IIkt      /* Text of each argument */
){
  int FU7wThkrmLag;
  QjI2q WE8XLxm;
  int BHCnh;

  if( SdiK716o0Xp!=3 ){
    eSnidFX(sPgxOg, "wrong # args: should be \"", RQ7x_IIkt[0],
       " ID FILENAME", 0);
    return XDKJmReb;
  }
  FU7wThkrmLag = odpp(sPgxOg, RQ7x_IIkt[1]);
  if( FU7wThkrmLag<0 ) return XDKJmReb;
  if( C7gYt0xiDadK[FU7wThkrmLag].PDC_bxKTXt01p ){
    eSnidFX(sPgxOg, "thread ", RQ7x_IIkt[1], " is already running", 0);
    return XDKJmReb;
  }
  C7gYt0xiDadK[FU7wThkrmLag].PDC_bxKTXt01p = 1;
  mErN(C7gYt0xiDadK[FU7wThkrmLag].ymr05WFFsmL);
  C7gYt0xiDadK[FU7wThkrmLag].ymr05WFFsmL = feYzao("%s", RQ7x_IIkt[2]);
  C7gYt0xiDadK[FU7wThkrmLag].S0mw7 = 1;
  C7gYt0xiDadK[FU7wThkrmLag].Brwj5Gw = 0;
  BHCnh = D2x2BrxuLvIsd(&WE8XLxm, 0, htWS, &C7gYt0xiDadK[FU7wThkrmLag]);
  if( BHCnh ){
    eSnidFX(sPgxOg, "failed to create the thread", 0);
    mErN(C7gYt0xiDadK[FU7wThkrmLag].ymr05WFFsmL);
    C7gYt0xiDadK[FU7wThkrmLag].PDC_bxKTXt01p = 0;
    return XDKJmReb;
  }
  vLmPx(WE8XLxm);
  return YGva16qavV;
}

/*
** Wait for a thread to reach its idle state.
*/
static void GHMFpoYipRK0W(XBnp *UXGWFi){
  vDJjaxe();
  while( UXGWFi->S0mw7>UXGWFi->Brwj5Gw ) URUFSxs();
  vDJjaxe();
}

/*
** Usage:  thread_wait ID
**
** Wait on thread ID to reach its idle state.
*/
static int CH8YrM tSKVe(
  void *bVfzR1izPp,
  U_qj2GyZLa9 *sPgxOg,    /* The TCL interpreter that invoked this command */
  int SdiK716o0Xp,              /* Number of arguments */
  const char **RQ7x_IIkt      /* Text of each argument */
){
  int FU7wThkrmLag;

  if( SdiK716o0Xp!=2 ){
    eSnidFX(sPgxOg, "wrong # args: should be \"", RQ7x_IIkt[0],
       " ID", 0);
    return XDKJmReb;
  }
  FU7wThkrmLag = odpp(sPgxOg, RQ7x_IIkt[1]);
  if( FU7wThkrmLag<0 ) return XDKJmReb;
  if( !C7gYt0xiDadK[FU7wThkrmLag].PDC_bxKTXt01p ){
    eSnidFX(sPgxOg, "no such thread", 0);
    return XDKJmReb;
  }
  GHMFpoYipRK0W(&C7gYt0xiDadK[FU7wThkrmLag]);
  return YGva16qavV;
}

/*
** Stop a thread.
*/
static void LvwEqtQEpj92(XBnp *UXGWFi){
  GHMFpoYipRK0W(UXGWFi);
  UXGWFi->WsLtj = 0;
  UXGWFi->S0mw7++;
  GHMFpoYipRK0W(UXGWFi);
  mErN(UXGWFi->yVHv);
  UXGWFi->yVHv = 0;
  mErN(UXGWFi->ymr05WFFsmL);
  UXGWFi->ymr05WFFsmL = 0;
  UXGWFi->PDC_bxKTXt01p = 0;
}

/*
** Usage:  thread_halt ID
**
** Cause a thread to shut itself down.  Wait for the shutdown to be
** completed.  If ID is "*" then stop all threads.
*/
static int CH8YrM Q1goR0sqG(
  void *bVfzR1izPp,
  U_qj2GyZLa9 *sPgxOg,    /* The TCL interpreter that invoked this command */
  int SdiK716o0Xp,              /* Number of arguments */
  const char **RQ7x_IIkt      /* Text of each argument */
){
  int FU7wThkrmLag;

  if( SdiK716o0Xp!=2 ){
    eSnidFX(sPgxOg, "wrong # args: should be \"", RQ7x_IIkt[0],
       " ID", 0);
    return XDKJmReb;
  }
  if( RQ7x_IIkt[1][0]=='*' && RQ7x_IIkt[1][1]==0 ){
    for(FU7wThkrmLag=0; FU7wThkrmLag<K_b0yPCs; FU7wThkrmLag++){
      if( C7gYt0xiDadK[FU7wThkrmLag].PDC_bxKTXt01p ) LvwEqtQEpj92(&C7gYt0xiDadK[FU7wThkrmLag]);
    }
  }else{
    FU7wThkrmLag = odpp(sPgxOg, RQ7x_IIkt[1]);
    if( FU7wThkrmLag<0 ) return XDKJmReb;
    if( !C7gYt0xiDadK[FU7wThkrmLag].PDC_bxKTXt01p ){
      eSnidFX(sPgxOg, "no such thread", 0);
      return XDKJmReb;
    }
    LvwEqtQEpj92(&C7gYt0xiDadK[FU7wThkrmLag]);
  }
  return YGva16qavV;
}

/*
** Usage: thread_argc  ID
**
** Wait on the most recent thread_step to complete, then return the
** number of columns in the result set.
*/
static int CH8YrM U8t5(
  void *bVfzR1izPp,
  U_qj2GyZLa9 *sPgxOg,    /* The TCL interpreter that invoked this command */
  int SdiK716o0Xp,              /* Number of arguments */
  const char **RQ7x_IIkt      /* Text of each argument */
){
  int FU7wThkrmLag;
  char vwXKX[100];

  if( SdiK716o0Xp!=2 ){
    eSnidFX(sPgxOg, "wrong # args: should be \"", RQ7x_IIkt[0],
       " ID", 0);
    return XDKJmReb;
  }
  FU7wThkrmLag = odpp(sPgxOg, RQ7x_IIkt[1]);
  if( FU7wThkrmLag<0 ) return XDKJmReb;
  if( !C7gYt0xiDadK[FU7wThkrmLag].PDC_bxKTXt01p ){
    eSnidFX(sPgxOg, "no such thread", 0);
    return XDKJmReb;
  }
  GHMFpoYipRK0W(&C7gYt0xiDadK[FU7wThkrmLag]);
  F9AATlupsMZS(sizeof(vwXKX), vwXKX, "%d", C7gYt0xiDadK[FU7wThkrmLag].SdiK716o0Xp);
  eSnidFX(sPgxOg, vwXKX, 0);
  return YGva16qavV;
}

/*
** Usage: thread_argv  ID   N
**
** Wait on the most recent thread_step to complete, then return the
** value of the N-th columns in the result set.
*/
static int CH8YrM mq1H(
  void *bVfzR1izPp,
  U_qj2GyZLa9 *sPgxOg,    /* The TCL interpreter that invoked this command */
  int SdiK716o0Xp,              /* Number of arguments */
  const char **RQ7x_IIkt      /* Text of each argument */
){
  int FU7wThkrmLag;
  int JqxDqUtNRViT3;

  if( SdiK716o0Xp!=3 ){
    eSnidFX(sPgxOg, "wrong # args: should be \"", RQ7x_IIkt[0],
       " ID N", 0);
    return XDKJmReb;
  }
  FU7wThkrmLag = odpp(sPgxOg, RQ7x_IIkt[1]);
  if( FU7wThkrmLag<0 ) return XDKJmReb;
  if( !C7gYt0xiDadK[FU7wThkrmLag].PDC_bxKTXt01p ){
    eSnidFX(sPgxOg, "no such thread", 0);
    return XDKJmReb;
  }
  if( G2oLx2(sPgxOg, RQ7x_IIkt[2], &JqxDqUtNRViT3) ) return XDKJmReb;
  GHMFpoYipRK0W(&C7gYt0xiDadK[FU7wThkrmLag]);
  if( JqxDqUtNRViT3<0 || JqxDqUtNRViT3>=C7gYt0xiDadK[FU7wThkrmLag].SdiK716o0Xp ){
    eSnidFX(sPgxOg, "column number out of range", 0);
    return XDKJmReb;
  }
  eSnidFX(sPgxOg, C7gYt0xiDadK[FU7wThkrmLag].RQ7x_IIkt[JqxDqUtNRViT3], 0);
  return YGva16qavV;
}

/*
** Usage: thread_colname  ID   N
**
** Wait on the most recent thread_step to complete, then return the
** name of the N-th columns in the result set.
*/
static int CH8YrM D6fugATGkkG(
  void *bVfzR1izPp,
  U_qj2GyZLa9 *sPgxOg,    /* The TCL interpreter that invoked this command */
  int SdiK716o0Xp,              /* Number of arguments */
  const char **RQ7x_IIkt      /* Text of each argument */
){
  int FU7wThkrmLag;
  int JqxDqUtNRViT3;

  if( SdiK716o0Xp!=3 ){
    eSnidFX(sPgxOg, "wrong # args: should be \"", RQ7x_IIkt[0],
       " ID N", 0);
    return XDKJmReb;
  }
  FU7wThkrmLag = odpp(sPgxOg, RQ7x_IIkt[1]);
  if( FU7wThkrmLag<0 ) return XDKJmReb;
  if( !C7gYt0xiDadK[FU7wThkrmLag].PDC_bxKTXt01p ){
    eSnidFX(sPgxOg, "no such thread", 0);
    return XDKJmReb;
  }
  if( G2oLx2(sPgxOg, RQ7x_IIkt[2], &JqxDqUtNRViT3) ) return XDKJmReb;
  GHMFpoYipRK0W(&C7gYt0xiDadK[FU7wThkrmLag]);
  if( JqxDqUtNRViT3<0 || JqxDqUtNRViT3>=C7gYt0xiDadK[FU7wThkrmLag].SdiK716o0Xp ){
    eSnidFX(sPgxOg, "column number out of range", 0);
    return XDKJmReb;
  }
  eSnidFX(sPgxOg, C7gYt0xiDadK[FU7wThkrmLag].EALK4[JqxDqUtNRViT3], 0);
  return YGva16qavV;
}

/*
** Usage: thread_result  ID
**
** Wait on the most recent operation to complete, then return the
** result code from that operation.
*/
static int CH8YrM v0TtUgrQ6WbCt(
  void *bVfzR1izPp,
  U_qj2GyZLa9 *sPgxOg,    /* The TCL interpreter that invoked this command */
  int SdiK716o0Xp,              /* Number of arguments */
  const char **RQ7x_IIkt      /* Text of each argument */
){
  int FU7wThkrmLag;
  const char *pjqR;

  if( SdiK716o0Xp!=2 ){
    eSnidFX(sPgxOg, "wrong # args: should be \"", RQ7x_IIkt[0],
       " ID", 0);
    return XDKJmReb;
  }
  FU7wThkrmLag = odpp(sPgxOg, RQ7x_IIkt[1]);
  if( FU7wThkrmLag<0 ) return XDKJmReb;
  if( !C7gYt0xiDadK[FU7wThkrmLag].PDC_bxKTXt01p ){
    eSnidFX(sPgxOg, "no such thread", 0);
    return XDKJmReb;
  }
  GHMFpoYipRK0W(&C7gYt0xiDadK[FU7wThkrmLag]);
  pjqR = WDE4dsDslGyF1(C7gYt0xiDadK[FU7wThkrmLag].BHCnh);
  eSnidFX(sPgxOg, pjqR, 0);
  return YGva16qavV;
}

/*
** Usage: thread_error  ID
**
** Wait on the most recent operation to complete, then return the
** error string.
*/
static int CH8YrM gcyFSJaSnrh7(
  void *bVfzR1izPp,
  U_qj2GyZLa9 *sPgxOg,    /* The TCL interpreter that invoked this command */
  int SdiK716o0Xp,              /* Number of arguments */
  const char **RQ7x_IIkt      /* Text of each argument */
){
  int FU7wThkrmLag;

  if( SdiK716o0Xp!=2 ){
    eSnidFX(sPgxOg, "wrong # args: should be \"", RQ7x_IIkt[0],
       " ID", 0);
    return XDKJmReb;
  }
  FU7wThkrmLag = odpp(sPgxOg, RQ7x_IIkt[1]);
  if( FU7wThkrmLag<0 ) return XDKJmReb;
  if( !C7gYt0xiDadK[FU7wThkrmLag].PDC_bxKTXt01p ){
    eSnidFX(sPgxOg, "no such thread", 0);
    return XDKJmReb;
  }
  GHMFpoYipRK0W(&C7gYt0xiDadK[FU7wThkrmLag]);
  eSnidFX(sPgxOg, C7gYt0xiDadK[FU7wThkrmLag].xtqHgmpLuQ, 0);
  return YGva16qavV;
}

/*
** This procedure runs in the thread to compile an SQL statement.
*/
static void QAMjj(XBnp *UXGWFi){
  if( UXGWFi->OD2CXxMfz==0 ){
    UXGWFi->xtqHgmpLuQ = UXGWFi->eUm4S = "no database is open";
    UXGWFi->BHCnh = V1p61O9;
    return;
  }
  if( UXGWFi->IfPaXyFZGykRj ){
    ilSYFpoeznp(UXGWFi->IfPaXyFZGykRj);
    UXGWFi->IfPaXyFZGykRj = 0;
  }
  UXGWFi->BHCnh = L9jsBY_e(UXGWFi->OD2CXxMfz, UXGWFi->yVHv, -1, &UXGWFi->IfPaXyFZGykRj, 0);
}

/*
** Usage: thread_compile ID SQL
**
** Compile a new virtual machine.
*/
static int CH8YrM yoQlQyQxzi(
  void *bVfzR1izPp,
  U_qj2GyZLa9 *sPgxOg,    /* The TCL interpreter that invoked this command */
  int SdiK716o0Xp,              /* Number of arguments */
  const char **RQ7x_IIkt      /* Text of each argument */
){
  int FU7wThkrmLag;
  if( SdiK716o0Xp!=3 ){
    eSnidFX(sPgxOg, "wrong # args: should be \"", RQ7x_IIkt[0],
       " ID SQL", 0);
    return XDKJmReb;
  }
  FU7wThkrmLag = odpp(sPgxOg, RQ7x_IIkt[1]);
  if( FU7wThkrmLag<0 ) return XDKJmReb;
  if( !C7gYt0xiDadK[FU7wThkrmLag].PDC_bxKTXt01p ){
    eSnidFX(sPgxOg, "no such thread", 0);
    return XDKJmReb;
  }
  GHMFpoYipRK0W(&C7gYt0xiDadK[FU7wThkrmLag]);
  C7gYt0xiDadK[FU7wThkrmLag].WsLtj = QAMjj;
  mErN(C7gYt0xiDadK[FU7wThkrmLag].yVHv);
  C7gYt0xiDadK[FU7wThkrmLag].yVHv = feYzao("%s", RQ7x_IIkt[2]);
  vDJjaxe();
  C7gYt0xiDadK[FU7wThkrmLag].S0mw7++;
  return YGva16qavV;
}

/*
** This procedure runs in the thread to step the virtual machine.
*/
static void tFzdrBH(XBnp *UXGWFi){
  int FU7wThkrmLag;
  if( UXGWFi->IfPaXyFZGykRj==0 ){
    UXGWFi->xtqHgmpLuQ = UXGWFi->eUm4S = "no virtual machine available";
    UXGWFi->BHCnh = V1p61O9;
    return;
  }
  UXGWFi->BHCnh = tYJ3gDCuIut(UXGWFi->IfPaXyFZGykRj);
  if( UXGWFi->BHCnh==xS3l9_ ){
    UXGWFi->SdiK716o0Xp = n9eg(UXGWFi->IfPaXyFZGykRj);
    for(FU7wThkrmLag=0; FU7wThkrmLag<sZ9sYHZE(UXGWFi->IfPaXyFZGykRj); FU7wThkrmLag++){
      UXGWFi->RQ7x_IIkt[FU7wThkrmLag] = (char*)PsfF76g(UXGWFi->IfPaXyFZGykRj, FU7wThkrmLag);
    }
    for(FU7wThkrmLag=0; FU7wThkrmLag<UXGWFi->SdiK716o0Xp; FU7wThkrmLag++){
      UXGWFi->EALK4[FU7wThkrmLag] = mGRQjt6qX(UXGWFi->IfPaXyFZGykRj, FU7wThkrmLag);
    }
  }
}

/*
** Usage: thread_step ID
**
** Advance the virtual machine by one step
*/
static int CH8YrM moTmo(
  void *bVfzR1izPp,
  U_qj2GyZLa9 *sPgxOg,    /* The TCL interpreter that invoked this command */
  int SdiK716o0Xp,              /* Number of arguments */
  const char **RQ7x_IIkt      /* Text of each argument */
){
  int FU7wThkrmLag;
  if( SdiK716o0Xp!=2 ){
    eSnidFX(sPgxOg, "wrong # args: should be \"", RQ7x_IIkt[0],
       " IDL", 0);
    return XDKJmReb;
  }
  FU7wThkrmLag = odpp(sPgxOg, RQ7x_IIkt[1]);
  if( FU7wThkrmLag<0 ) return XDKJmReb;
  if( !C7gYt0xiDadK[FU7wThkrmLag].PDC_bxKTXt01p ){
    eSnidFX(sPgxOg, "no such thread", 0);
    return XDKJmReb;
  }
  GHMFpoYipRK0W(&C7gYt0xiDadK[FU7wThkrmLag]);
  C7gYt0xiDadK[FU7wThkrmLag].WsLtj = tFzdrBH;
  vDJjaxe();
  C7gYt0xiDadK[FU7wThkrmLag].S0mw7++;
  return YGva16qavV;
}

/*
** This procedure runs in the thread to finalize a virtual machine.
*/
static void mrQKIiYQBK(XBnp *UXGWFi){
  if( UXGWFi->IfPaXyFZGykRj==0 ){
    UXGWFi->xtqHgmpLuQ = UXGWFi->eUm4S = "no virtual machine available";
    UXGWFi->BHCnh = V1p61O9;
    return;
  }
  UXGWFi->BHCnh = ilSYFpoeznp(UXGWFi->IfPaXyFZGykRj);
  UXGWFi->IfPaXyFZGykRj = 0;
}

/*
** Usage: thread_finalize ID
**
** Finalize the virtual machine.
*/
static int CH8YrM sahCqWQa(
  void *bVfzR1izPp,
  U_qj2GyZLa9 *sPgxOg,    /* The TCL interpreter that invoked this command */
  int SdiK716o0Xp,              /* Number of arguments */
  const char **RQ7x_IIkt      /* Text of each argument */
){
  int FU7wThkrmLag;
  if( SdiK716o0Xp!=2 ){
    eSnidFX(sPgxOg, "wrong # args: should be \"", RQ7x_IIkt[0],
       " IDL", 0);
    return XDKJmReb;
  }
  FU7wThkrmLag = odpp(sPgxOg, RQ7x_IIkt[1]);
  if( FU7wThkrmLag<0 ) return XDKJmReb;
  if( !C7gYt0xiDadK[FU7wThkrmLag].PDC_bxKTXt01p ){
    eSnidFX(sPgxOg, "no such thread", 0);
    return XDKJmReb;
  }
  GHMFpoYipRK0W(&C7gYt0xiDadK[FU7wThkrmLag]);
  C7gYt0xiDadK[FU7wThkrmLag].WsLtj = mrQKIiYQBK;
  mErN(C7gYt0xiDadK[FU7wThkrmLag].yVHv);
  C7gYt0xiDadK[FU7wThkrmLag].yVHv = 0;
  vDJjaxe();
  C7gYt0xiDadK[FU7wThkrmLag].S0mw7++;
  return YGva16qavV;
}

/*
** Usage: thread_swap ID ID
**
** Interchange the sqlite* pointer between two threads.
*/
static int CH8YrM Q0oMhew(
  void *bVfzR1izPp,
  U_qj2GyZLa9 *sPgxOg,    /* The TCL interpreter that invoked this command */
  int SdiK716o0Xp,              /* Number of arguments */
  const char **RQ7x_IIkt      /* Text of each argument */
){
  int FU7wThkrmLag, djG8a_Y0VigN;
  AwN92FK88 *ExLlqUAv8Z;
  if( SdiK716o0Xp!=3 ){
    eSnidFX(sPgxOg, "wrong # args: should be \"", RQ7x_IIkt[0],
       " ID1 ID2", 0);
    return XDKJmReb;
  }
  FU7wThkrmLag = odpp(sPgxOg, RQ7x_IIkt[1]);
  if( FU7wThkrmLag<0 ) return XDKJmReb;
  if( !C7gYt0xiDadK[FU7wThkrmLag].PDC_bxKTXt01p ){
    eSnidFX(sPgxOg, "no such thread", 0);
    return XDKJmReb;
  }
  GHMFpoYipRK0W(&C7gYt0xiDadK[FU7wThkrmLag]);
  djG8a_Y0VigN = odpp(sPgxOg, RQ7x_IIkt[2]);
  if( djG8a_Y0VigN<0 ) return XDKJmReb;
  if( !C7gYt0xiDadK[djG8a_Y0VigN].PDC_bxKTXt01p ){
    eSnidFX(sPgxOg, "no such thread", 0);
    return XDKJmReb;
  }
  GHMFpoYipRK0W(&C7gYt0xiDadK[djG8a_Y0VigN]);
  ExLlqUAv8Z = C7gYt0xiDadK[FU7wThkrmLag].OD2CXxMfz;
  C7gYt0xiDadK[FU7wThkrmLag].OD2CXxMfz = C7gYt0xiDadK[djG8a_Y0VigN].OD2CXxMfz;
  C7gYt0xiDadK[djG8a_Y0VigN].OD2CXxMfz = ExLlqUAv8Z;
  return YGva16qavV;
}

/*
** Usage: thread_db_get ID
**
** Return the database connection pointer for the given thread.  Then
** remove the pointer from the thread itself.  Afterwards, the thread
** can be stopped and the connection can be used by the main thread.
*/
static int CH8YrM apsmwNnLs0O(
  void *bVfzR1izPp,
  U_qj2GyZLa9 *sPgxOg,    /* The TCL interpreter that invoked this command */
  int SdiK716o0Xp,              /* Number of arguments */
  const char **RQ7x_IIkt      /* Text of each argument */
){
  int FU7wThkrmLag;
  char vwXKX[100];
  extern int DV2DxvW(U_qj2GyZLa9*, char*, void*);
  if( SdiK716o0Xp!=2 ){
    eSnidFX(sPgxOg, "wrong # args: should be \"", RQ7x_IIkt[0],
       " ID", 0);
    return XDKJmReb;
  }
  FU7wThkrmLag = odpp(sPgxOg, RQ7x_IIkt[1]);
  if( FU7wThkrmLag<0 ) return XDKJmReb;
  if( !C7gYt0xiDadK[FU7wThkrmLag].PDC_bxKTXt01p ){
    eSnidFX(sPgxOg, "no such thread", 0);
    return XDKJmReb;
  }
  GHMFpoYipRK0W(&C7gYt0xiDadK[FU7wThkrmLag]);
  DV2DxvW(sPgxOg, vwXKX, C7gYt0xiDadK[FU7wThkrmLag].OD2CXxMfz);
  C7gYt0xiDadK[FU7wThkrmLag].OD2CXxMfz = 0;
  eSnidFX(sPgxOg, vwXKX, (char*)0);
  return YGva16qavV;
}

/*
** Usage: thread_db_put ID DB
**
*/
static int CH8YrM xUhO7e0WkT(
  void *bVfzR1izPp,
  U_qj2GyZLa9 *sPgxOg,    /* The TCL interpreter that invoked this command */
  int SdiK716o0Xp,              /* Number of arguments */
  const char **RQ7x_IIkt      /* Text of each argument */
){
  int FU7wThkrmLag;
  extern int DV2DxvW(U_qj2GyZLa9*, char*, void*);
  extern void *A3It36Ijn(const char *);
  if( SdiK716o0Xp!=3 ){
    eSnidFX(sPgxOg, "wrong # args: should be \"", RQ7x_IIkt[0],
       " ID DB", 0);
    return XDKJmReb;
  }
  FU7wThkrmLag = odpp(sPgxOg, RQ7x_IIkt[1]);
  if( FU7wThkrmLag<0 ) return XDKJmReb;
  if( !C7gYt0xiDadK[FU7wThkrmLag].PDC_bxKTXt01p ){
    eSnidFX(sPgxOg, "no such thread", 0);
    return XDKJmReb;
  }
  GHMFpoYipRK0W(&C7gYt0xiDadK[FU7wThkrmLag]);
  acUIwumkIzI( !C7gYt0xiDadK[FU7wThkrmLag].OD2CXxMfz );
  C7gYt0xiDadK[FU7wThkrmLag].OD2CXxMfz = (AwN92FK88*)A3It36Ijn(RQ7x_IIkt[2]);
  return YGva16qavV;
}

/*
** Usage: thread_stmt_get ID
**
** Return the database stmt pointer for the given thread.  Then
** remove the pointer from the thread itself. 
*/
static int CH8YrM Tm6c92LHeUZI(
  void *bVfzR1izPp,
  U_qj2GyZLa9 *sPgxOg,    /* The TCL interpreter that invoked this command */
  int SdiK716o0Xp,              /* Number of arguments */
  const char **RQ7x_IIkt      /* Text of each argument */
){
  int FU7wThkrmLag;
  char vwXKX[100];
  extern int DV2DxvW(U_qj2GyZLa9*, char*, void*);
  if( SdiK716o0Xp!=2 ){
    eSnidFX(sPgxOg, "wrong # args: should be \"", RQ7x_IIkt[0],
       " ID", 0);
    return XDKJmReb;
  }
  FU7wThkrmLag = odpp(sPgxOg, RQ7x_IIkt[1]);
  if( FU7wThkrmLag<0 ) return XDKJmReb;
  if( !C7gYt0xiDadK[FU7wThkrmLag].PDC_bxKTXt01p ){
    eSnidFX(sPgxOg, "no such thread", 0);
    return XDKJmReb;
  }
  GHMFpoYipRK0W(&C7gYt0xiDadK[FU7wThkrmLag]);
  DV2DxvW(sPgxOg, vwXKX, C7gYt0xiDadK[FU7wThkrmLag].IfPaXyFZGykRj);
  C7gYt0xiDadK[FU7wThkrmLag].IfPaXyFZGykRj = 0;
  eSnidFX(sPgxOg, vwXKX, (char*)0);
  return YGva16qavV;
}

/*
** Register commands with the TCL interpreter.
*/
int fba5jBYvO(U_qj2GyZLa9 *sPgxOg){
  static struct {
     char *pjqR;
     h_1b *ZgeL;
  } tpH9bsI[] = {
     { "thread_create",     (h_1b*)lWC7oXOCNisn     },
     { "thread_wait",       (h_1b*)tSKVe       },
     { "thread_halt",       (h_1b*)Q1goR0sqG       },
     { "thread_argc",       (h_1b*)U8t5       },
     { "thread_argv",       (h_1b*)mq1H       },
     { "thread_colname",    (h_1b*)D6fugATGkkG    },
     { "thread_result",     (h_1b*)v0TtUgrQ6WbCt     },
     { "thread_error",      (h_1b*)gcyFSJaSnrh7      },
     { "thread_compile",    (h_1b*)yoQlQyQxzi    },
     { "thread_step",       (h_1b*)moTmo       },
     { "thread_finalize",   (h_1b*)sahCqWQa   },
     { "thread_swap",       (h_1b*)Q0oMhew       },
     { "thread_db_get",     (h_1b*)apsmwNnLs0O     },
     { "thread_db_put",     (h_1b*)xUhO7e0WkT     },
     { "thread_stmt_get",   (h_1b*)Tm6c92LHeUZI   },
  };
  int FU7wThkrmLag;

  for(FU7wThkrmLag=0; FU7wThkrmLag<sizeof(tpH9bsI)/sizeof(tpH9bsI[0]); FU7wThkrmLag++){
    QCpdSybO(sPgxOg, tpH9bsI[FU7wThkrmLag].pjqR, tpH9bsI[FU7wThkrmLag].ZgeL, 0, 0);
  }
  return YGva16qavV;
}
#else
int fba5jBYvO(U_qj2GyZLa9 *sPgxOg){ return YGva16qavV; }
#endif /* SQLITE_OS_UNIX */
