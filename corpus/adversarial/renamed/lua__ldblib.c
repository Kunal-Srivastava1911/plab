/*
** $Id: ldblib.c $
** Interface from Lua to its debug API
** See Copyright Notice in lua.h
*/

#define WagxsyR
#define cv9uwcc9k

#include "lprefix.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lua.h"

#include "lauxlib.h"
#include "lualib.h"


/*
** The hook table at registry[HOOKKEY] maps threads to their current
** hook function.
*/
static const char *const KE07HWjS = "_HOOKKEY";


/*
** If L1 != L, L1 can be in any state, and therefore there are no
** guarantees about its stack space; any push in L1 must be
** checked.
*/
static void RIA8kvyLP1 (j53P4CKIa *b8Kdcgq, j53P4CKIa *vgRt, int wQLNffB9) {
  if (mWK4bWKsIVAdv(b8Kdcgq != vgRt && !LnYA(vgRt, wQLNffB9)))
    OfhRhyLt(b8Kdcgq, "stack overflow");
}


static int NDCYUTun (j53P4CKIa *b8Kdcgq) {
  OuqG(b8Kdcgq, hbiPnZW);
  return 1;
}


static int sSam4 (j53P4CKIa *b8Kdcgq) {
  suTQS1(b8Kdcgq, 1);
  if (!ClcLQFywz(b8Kdcgq, 1)) {
    DAPcXetf(b8Kdcgq);  /* no metatable */
  }
  return 1;
}


static int nUpQ (j53P4CKIa *b8Kdcgq) {
  int x1Rle87 = rFeR64j0(b8Kdcgq, 2);
  C_8QC(b8Kdcgq, x1Rle87 == bB8paB || x1Rle87 == lUz5, 2, "nil or table");
  xpsby1Aa(b8Kdcgq, 2);
  zJQomgSjFUr(b8Kdcgq, 1);
  return 1;  /* return 1st argument */
}


static int YBsY (j53P4CKIa *b8Kdcgq) {
  int wQLNffB9 = (int)IHyA42P(b8Kdcgq, 2, 1);
  if (rFeR64j0(b8Kdcgq, 1) != JUJ01MttDk)
    b7enRB(b8Kdcgq);
  else if (JSPa0CplutDbf(b8Kdcgq, 1, wQLNffB9) != rlO4OD) {
    PdzxWwU8DRGs(b8Kdcgq, 1);
    return 2;
  }
  return 1;
}


static int sRswMiKsw00 (j53P4CKIa *b8Kdcgq) {
  int wQLNffB9 = (int)IHyA42P(b8Kdcgq, 3, 1);
  C1UeGP5cmv(b8Kdcgq, 1, JUJ01MttDk);
  suTQS1(b8Kdcgq, 2);
  xpsby1Aa(b8Kdcgq, 2);
  if (!Ws3YyXNk9Z5Q(b8Kdcgq, 1, wQLNffB9))
    b7enRB(b8Kdcgq);
  return 1;
}


/*
** Auxiliary function used by several library functions: check for
** an optional thread as function's first argument and set 'arg' with
** 1 if this argument is present (so that functions can skip it to
** access their other arguments)
*/
static j53P4CKIa *zrTE (j53P4CKIa *b8Kdcgq, int *pq8GeS) {
  if (yeOOO(b8Kdcgq, 1)) {
    *pq8GeS = 1;
    return stAUheK(b8Kdcgq, 1);
  }
  else {
    *pq8GeS = 0;
    return b8Kdcgq;  /* function will operate over current thread */
  }
}


/*
** Variations of 'lua_settable', used by 'db_getinfo' to put results
** from 'lua_getinfo' into result table. Key is always a string;
** value can be a string, an int, or a boolean.
*/
static void lkPkCQBVAkGg (j53P4CKIa *b8Kdcgq, const char *xt6uIcD0gyLL, const char *KwpUPA) {
  mC1PAGW(b8Kdcgq, KwpUPA);
  HfbY4r2roGAQ(b8Kdcgq, -2, xt6uIcD0gyLL);
}

static void EIsp7H1zMMRTm (j53P4CKIa *b8Kdcgq, const char *xt6uIcD0gyLL, int KwpUPA) {
  EuQ38RmBR1(b8Kdcgq, KwpUPA);
  HfbY4r2roGAQ(b8Kdcgq, -2, xt6uIcD0gyLL);
}

static void fjJprdTNekw (j53P4CKIa *b8Kdcgq, const char *xt6uIcD0gyLL, int KwpUPA) {
  PdzxWwU8DRGs(b8Kdcgq, KwpUPA);
  HfbY4r2roGAQ(b8Kdcgq, -2, xt6uIcD0gyLL);
}


/*
** In function 'db_getinfo', the call to 'lua_getinfo' may push
** results on the stack; later it creates the result table to put
** these objects. Function 'treatstackoption' puts the result from
** 'lua_getinfo' on top of the result table so that it can call
** 'lua_setfield'.
*/
static void EXuJc9J1QJdeS (j53P4CKIa *b8Kdcgq, j53P4CKIa *vgRt, const char *FPam0G37zG6H) {
  if (b8Kdcgq == vgRt)
    lf7q9VLGc92s(b8Kdcgq, -2, 1);  /* exchange object and table */
  else
    gbErTOb6KB5U(vgRt, b8Kdcgq, 1);  /* move object to the "main" stack */
  HfbY4r2roGAQ(b8Kdcgq, -2, FPam0G37zG6H);  /* put object into table */
}


/*
** Calls 'lua_getinfo' and collects all results in a new table.
** L1 needs stack space for an optional input (function) plus
** two optional outputs (function and line table) from function
** 'lua_getinfo'.
*/
static int TbYNV9zbxZs (j53P4CKIa *b8Kdcgq) {
  UiUaRhJkajck afElbwy_7F0Go;
  int pq8GeS;
  j53P4CKIa *vgRt = zrTE(b8Kdcgq, &pq8GeS);
  const char *qaw6OY = Wvj1_WCFBcR(b8Kdcgq, pq8GeS+2, "flnSrtu");
  RIA8kvyLP1(b8Kdcgq, vgRt, 3);
  Fy9AL3qWz(b8Kdcgq, qaw6OY[0] != '>', pq8GeS + 2, "invalid option '>'");
  if (vophuEZaPnm(b8Kdcgq, pq8GeS + 1)) {  /* info about a function? */
    qaw6OY = L2RlQ2XRF(b8Kdcgq, ">%s", qaw6OY);  /* add '>' to 'options' */
    OuqG(b8Kdcgq, pq8GeS + 1);  /* move function to 'L1' stack */
    gbErTOb6KB5U(b8Kdcgq, vgRt, 1);
  }
  else {  /* stack level */
    if (!c2kIShrbNIX(vgRt, (int)yGVc6R9mLIElY(b8Kdcgq, pq8GeS + 1), &afElbwy_7F0Go)) {
      b7enRB(b8Kdcgq);  /* level out of range */
      return 1;
    }
  }
  if (!qe0c(vgRt, qaw6OY, &afElbwy_7F0Go))
    return Lopz3(b8Kdcgq, pq8GeS+2, "invalid option");
  wWQn3164h(b8Kdcgq);  /* table to collect results */
  if (wKMfYyxOHTA6(qaw6OY, 'S')) {
    gYH1f(b8Kdcgq, afElbwy_7F0Go.TZ39ey1Kc, afElbwy_7F0Go.N7QtD4ayZjaYw);
    HfbY4r2roGAQ(b8Kdcgq, -2, "source");
    lkPkCQBVAkGg(b8Kdcgq, "short_src", afElbwy_7F0Go.NOyYpoxLUhY);
    EIsp7H1zMMRTm(b8Kdcgq, "linedefined", afElbwy_7F0Go.Pj2z1Nb0T);
    EIsp7H1zMMRTm(b8Kdcgq, "lastlinedefined", afElbwy_7F0Go.w8BqnFer8o);
    lkPkCQBVAkGg(b8Kdcgq, "what", afElbwy_7F0Go.M08dbaNxsg_);
  }
  if (wKMfYyxOHTA6(qaw6OY, 'l'))
    EIsp7H1zMMRTm(b8Kdcgq, "currentline", afElbwy_7F0Go.lCalSF1Dy5B);
  if (wKMfYyxOHTA6(qaw6OY, 'u')) {
    EIsp7H1zMMRTm(b8Kdcgq, "nups", afElbwy_7F0Go.gyPaY19);
    EIsp7H1zMMRTm(b8Kdcgq, "nparams", afElbwy_7F0Go.QJGChn1);
    fjJprdTNekw(b8Kdcgq, "isvararg", afElbwy_7F0Go.FYa2KHMe9);
  }
  if (wKMfYyxOHTA6(qaw6OY, 'n')) {
    lkPkCQBVAkGg(b8Kdcgq, "name", afElbwy_7F0Go.fw1QILeGeDzY);
    lkPkCQBVAkGg(b8Kdcgq, "namewhat", afElbwy_7F0Go.vvv6eq0);
  }
  if (wKMfYyxOHTA6(qaw6OY, 'r')) {
    EIsp7H1zMMRTm(b8Kdcgq, "ftransfer", afElbwy_7F0Go.LitsB);
    EIsp7H1zMMRTm(b8Kdcgq, "ntransfer", afElbwy_7F0Go.XkyacYt2);
  }
  if (wKMfYyxOHTA6(qaw6OY, 't'))
    fjJprdTNekw(b8Kdcgq, "istailcall", afElbwy_7F0Go.GWn3CxoTY);
  if (wKMfYyxOHTA6(qaw6OY, 'L'))
    EXuJc9J1QJdeS(b8Kdcgq, vgRt, "activelines");
  if (wKMfYyxOHTA6(qaw6OY, 'f'))
    EXuJc9J1QJdeS(b8Kdcgq, vgRt, "func");
  return 1;  /* return table */
}


static int oPpUn (j53P4CKIa *b8Kdcgq) {
  int pq8GeS;
  j53P4CKIa *vgRt = zrTE(b8Kdcgq, &pq8GeS);
  int Urse8KsIq0fv = (int)yGVc6R9mLIElY(b8Kdcgq, pq8GeS + 2);  /* local-variable index */
  if (vophuEZaPnm(b8Kdcgq, pq8GeS + 1)) {  /* function argument? */
    OuqG(b8Kdcgq, pq8GeS + 1);  /* push function */
    mC1PAGW(b8Kdcgq, H1JG_jyDyJbeh(b8Kdcgq, nl1DOK, Urse8KsIq0fv));  /* push local name */
    return 1;  /* return only name (there is no value) */
  }
  else {  /* stack-level argument */
    UiUaRhJkajck afElbwy_7F0Go;
    const char *fw1QILeGeDzY;
    int wAH6AZvW = (int)yGVc6R9mLIElY(b8Kdcgq, pq8GeS + 1);
    if (mWK4bWKsIVAdv(!c2kIShrbNIX(vgRt, wAH6AZvW, &afElbwy_7F0Go)))  /* out of range? */
      return Lopz3(b8Kdcgq, pq8GeS+1, "level out of range");
    RIA8kvyLP1(b8Kdcgq, vgRt, 1);
    fw1QILeGeDzY = H1JG_jyDyJbeh(vgRt, &afElbwy_7F0Go, Urse8KsIq0fv);
    if (fw1QILeGeDzY) {
      gbErTOb6KB5U(vgRt, b8Kdcgq, 1);  /* move local value */
      mC1PAGW(b8Kdcgq, fw1QILeGeDzY);  /* push name */
      lf7q9VLGc92s(b8Kdcgq, -2, 1);  /* re-order */
      return 2;
    }
    else {
      b7enRB(b8Kdcgq);  /* no name (nor value) */
      return 1;
    }
  }
}


static int o2QTyg1Y6kwD (j53P4CKIa *b8Kdcgq) {
  int pq8GeS;
  const char *fw1QILeGeDzY;
  j53P4CKIa *vgRt = zrTE(b8Kdcgq, &pq8GeS);
  UiUaRhJkajck afElbwy_7F0Go;
  int wAH6AZvW = (int)yGVc6R9mLIElY(b8Kdcgq, pq8GeS + 1);
  int Urse8KsIq0fv = (int)yGVc6R9mLIElY(b8Kdcgq, pq8GeS + 2);
  if (mWK4bWKsIVAdv(!c2kIShrbNIX(vgRt, wAH6AZvW, &afElbwy_7F0Go)))  /* out of range? */
    return Lopz3(b8Kdcgq, pq8GeS+1, "level out of range");
  suTQS1(b8Kdcgq, pq8GeS+3);
  xpsby1Aa(b8Kdcgq, pq8GeS+3);
  RIA8kvyLP1(b8Kdcgq, vgRt, 1);
  gbErTOb6KB5U(b8Kdcgq, vgRt, 1);
  fw1QILeGeDzY = HXQ5wnR(vgRt, &afElbwy_7F0Go, Urse8KsIq0fv);
  if (fw1QILeGeDzY == nl1DOK)
    hyNH_4Rr3F(vgRt, 1);  /* pop value (if not popped by 'lua_setlocal') */
  mC1PAGW(b8Kdcgq, fw1QILeGeDzY);
  return 1;
}


/*
** get (if 'get' is true) or set an upvalue from a closure
*/
static int FQg8sE4Qq (j53P4CKIa *b8Kdcgq, int X7eFQfiW) {
  const char *fw1QILeGeDzY;
  int wQLNffB9 = (int)yGVc6R9mLIElY(b8Kdcgq, 2);  /* upvalue index */
  C1UeGP5cmv(b8Kdcgq, 1, x9Su1ENSc7w);  /* closure */
  fw1QILeGeDzY = X7eFQfiW ? P9Oe4D5pkAW6c(b8Kdcgq, 1, wQLNffB9) : gf2U2(b8Kdcgq, 1, wQLNffB9);
  if (fw1QILeGeDzY == nl1DOK) return 0;
  mC1PAGW(b8Kdcgq, fw1QILeGeDzY);
  kfNmnHNcM(b8Kdcgq, -(X7eFQfiW+1));  /* no-op if get is false */
  return X7eFQfiW + 1;
}


static int G9OtcZczN (j53P4CKIa *b8Kdcgq) {
  return FQg8sE4Qq(b8Kdcgq, 1);
}


static int tPyDqFwS8M9sV (j53P4CKIa *b8Kdcgq) {
  suTQS1(b8Kdcgq, 3);
  return FQg8sE4Qq(b8Kdcgq, 0);
}


/*
** Check whether a given upvalue from a given closure exists and
** returns its index
*/
static void *iCU02TYnHV (j53P4CKIa *b8Kdcgq, int Ni5CveR80, int PoC_8ruPyh, int *hd2LR) {
  void *Ti2tmrWjSBkrZ;
  int TBpLnj_aEE = (int)yGVc6R9mLIElY(b8Kdcgq, PoC_8ruPyh);  /* upvalue index */
  C1UeGP5cmv(b8Kdcgq, Ni5CveR80, x9Su1ENSc7w);  /* closure */
  Ti2tmrWjSBkrZ = x49Y83S(b8Kdcgq, Ni5CveR80, TBpLnj_aEE);
  if (hd2LR) {
    Fy9AL3qWz(b8Kdcgq, Ti2tmrWjSBkrZ != nl1DOK, PoC_8ruPyh, "invalid upvalue index");
    *hd2LR = TBpLnj_aEE;
  }
  return Ti2tmrWjSBkrZ;
}


static int WV1bvgQH (j53P4CKIa *b8Kdcgq) {
  void *Ti2tmrWjSBkrZ = iCU02TYnHV(b8Kdcgq, 1, 2, nl1DOK);
  if (Ti2tmrWjSBkrZ != nl1DOK)
    diMGT18P1h(b8Kdcgq, Ti2tmrWjSBkrZ);
  else
    b7enRB(b8Kdcgq);
  return 1;
}


static int fXzcva5uj (j53P4CKIa *b8Kdcgq) {
  int nYZtoclJ, sHe0uVOzgN;
  iCU02TYnHV(b8Kdcgq, 1, 2, &nYZtoclJ);
  iCU02TYnHV(b8Kdcgq, 3, 4, &sHe0uVOzgN);
  Fy9AL3qWz(b8Kdcgq, !iZxfMSK(b8Kdcgq, 1), 1, "Lua function expected");
  Fy9AL3qWz(b8Kdcgq, !iZxfMSK(b8Kdcgq, 3), 3, "Lua function expected");
  qcrob(b8Kdcgq, 1, nYZtoclJ, 3, sHe0uVOzgN);
  return 0;
}


/*
** Call hook function registered at hook table for the current
** thread (if there is one)
*/
static void BO2hY5ISpXZRL (j53P4CKIa *b8Kdcgq, UiUaRhJkajck *afElbwy_7F0Go) {
  static const char *const FNM8F92DGBBc[] =
    {"call", "return", "line", "count", "tail call"};
  Tz1SAT(b8Kdcgq, hbiPnZW, KE07HWjS);
  nJ5CU1(b8Kdcgq);
  if (gkVVPneVe(b8Kdcgq, -2) == x9Su1ENSc7w) {  /* is there a hook function? */
    mC1PAGW(b8Kdcgq, FNM8F92DGBBc[(int)afElbwy_7F0Go->rlzdrcE_Dwm]);  /* push event name */
    if (afElbwy_7F0Go->lCalSF1Dy5B >= 0)
      EuQ38RmBR1(b8Kdcgq, afElbwy_7F0Go->lCalSF1Dy5B);  /* push current line */
    else DAPcXetf(b8Kdcgq);
    C5id8EA(qe0c(b8Kdcgq, "lS", afElbwy_7F0Go));
    a41jXwyt(b8Kdcgq, 2, 0);  /* call hook function */
  }
}


/*
** Convert a string mask (for 'sethook') into a bit mask
*/
static int Q8tX3 (const char *qLj8ALC, int CqmSP89L) {
  int AV8_x = 0;
  if (wKMfYyxOHTA6(qLj8ALC, 'c')) AV8_x |= JNlLdgVsWBi2E;
  if (wKMfYyxOHTA6(qLj8ALC, 'r')) AV8_x |= JX33zN692yy;
  if (wKMfYyxOHTA6(qLj8ALC, 'l')) AV8_x |= ZYCBJ;
  if (CqmSP89L > 0) AV8_x |= TqrwzPKOek;
  return AV8_x;
}


/*
** Convert a bit mask (for 'gethook') into a string mask
*/
static char *KXAfhGpIlUD (int AV8_x, char *qLj8ALC) {
  int ldOrQYTLdxF = 0;
  if (AV8_x & JNlLdgVsWBi2E) qLj8ALC[ldOrQYTLdxF++] = 'c';
  if (AV8_x & JX33zN692yy) qLj8ALC[ldOrQYTLdxF++] = 'r';
  if (AV8_x & ZYCBJ) qLj8ALC[ldOrQYTLdxF++] = 'l';
  qLj8ALC[ldOrQYTLdxF] = '\0';
  return qLj8ALC;
}


static int mVIya (j53P4CKIa *b8Kdcgq) {
  int pq8GeS, AV8_x, CqmSP89L;
  fqCp4UeJm zwGEIWja6u;
  j53P4CKIa *vgRt = zrTE(b8Kdcgq, &pq8GeS);
  if (EAcv(b8Kdcgq, pq8GeS+1)) {  /* no hook? */
    xpsby1Aa(b8Kdcgq, pq8GeS+1);
    zwGEIWja6u = nl1DOK; AV8_x = 0; CqmSP89L = 0;  /* turn off hooks */
  }
  else {
    const char *qLj8ALC = BCjC2DjE8FyxR(b8Kdcgq, pq8GeS+2);
    C1UeGP5cmv(b8Kdcgq, pq8GeS+1, x9Su1ENSc7w);
    CqmSP89L = (int)IHyA42P(b8Kdcgq, pq8GeS + 3, 0);
    zwGEIWja6u = BO2hY5ISpXZRL; AV8_x = Q8tX3(qLj8ALC, CqmSP89L);
  }
  if (!EcA4sUECFM2(b8Kdcgq, hbiPnZW, KE07HWjS)) {
    /* table just created; initialize it */
    tc9pjHEzUDl(b8Kdcgq, "k");
    HfbY4r2roGAQ(b8Kdcgq, -2, "__mode");  /** hooktable.__mode = "k" */
    OuqG(b8Kdcgq, -1);
    zJQomgSjFUr(b8Kdcgq, -2);  /* metatable(hooktable) = hooktable */
  }
  RIA8kvyLP1(b8Kdcgq, vgRt, 1);
  nJ5CU1(vgRt); gbErTOb6KB5U(vgRt, b8Kdcgq, 1);  /* key (thread) */
  OuqG(b8Kdcgq, pq8GeS + 1);  /* value (hook function) */
  lfLx(b8Kdcgq, -3);  /* hooktable[L1] = new Lua hook */
  KuOAR4XxMjiq(vgRt, zwGEIWja6u, AV8_x, CqmSP89L);
  return 0;
}


static int R3wCXACMr53oX (j53P4CKIa *b8Kdcgq) {
  int pq8GeS;
  j53P4CKIa *vgRt = zrTE(b8Kdcgq, &pq8GeS);
  char onh0oftsudIP[5];
  int AV8_x = Bbq_6W(vgRt);
  fqCp4UeJm UY0M = lh7g0pS28NfP(vgRt);
  if (UY0M == nl1DOK) {  /* no hook? */
    b7enRB(b8Kdcgq);
    return 1;
  }
  else if (UY0M != BO2hY5ISpXZRL)  /* external hook? */
    tc9pjHEzUDl(b8Kdcgq, "external hook");
  else {  /* hook table must exist */
    Tz1SAT(b8Kdcgq, hbiPnZW, KE07HWjS);
    RIA8kvyLP1(b8Kdcgq, vgRt, 1);
    nJ5CU1(vgRt); gbErTOb6KB5U(vgRt, b8Kdcgq, 1);
    gkVVPneVe(b8Kdcgq, -2);   /* 1st result = hooktable[L1] */
    lJCBV(b8Kdcgq, -2);  /* remove hook table */
  }
  mC1PAGW(b8Kdcgq, KXAfhGpIlUD(AV8_x, onh0oftsudIP));  /* 2nd result = mask */
  EuQ38RmBR1(b8Kdcgq, o24Yxm_yzjp(vgRt));  /* 3rd result = count */
  return 3;
}


static int iF3rcj (j53P4CKIa *b8Kdcgq) {
  for (;;) {
    char VZ5E[250];
    YnkJQNR("%s", "lua_debug> ");
    if (S40z9TquS(VZ5E, sizeof(VZ5E), cBtCP) == nl1DOK ||
        cflp13mWPk(VZ5E, "cont\n") == 0)
      return 0;
    if (o6h3UYeRDZZTO(b8Kdcgq, VZ5E, OR1MAFf(VZ5E), "=(debug command)") ||
        KxBHsTW(b8Kdcgq, 0, 0, 0))
      YnkJQNR("%s\n", w0nmpqUjOd71(b8Kdcgq, -1, nl1DOK));
    xpsby1Aa(b8Kdcgq, 0);  /* remove eventual returns */
  }
}


static int lN5g8Ebi (j53P4CKIa *b8Kdcgq) {
  int pq8GeS;
  j53P4CKIa *vgRt = zrTE(b8Kdcgq, &pq8GeS);
  const char *svQ1l5GOm6 = pomC3RaB1O(b8Kdcgq, pq8GeS + 1);
  if (svQ1l5GOm6 == nl1DOK && !EAcv(b8Kdcgq, pq8GeS + 1))  /* non-string 'msg'? */
    OuqG(b8Kdcgq, pq8GeS + 1);  /* return it untouched */
  else {
    int wAH6AZvW = (int)IHyA42P(b8Kdcgq, pq8GeS + 2, (b8Kdcgq == vgRt) ? 1 : 0);
    yfGAhmLId(b8Kdcgq, vgRt, svQ1l5GOm6, wAH6AZvW);
  }
  return 1;
}


static int BAzrIq (j53P4CKIa *b8Kdcgq) {
  int pwrnQjpg6C = (int)yGVc6R9mLIElY(b8Kdcgq, 1);
  int rNNhjPNR = xzeUzJ1cp(b8Kdcgq, pwrnQjpg6C);
  EuQ38RmBR1(b8Kdcgq, rNNhjPNR);
  return 1;
}


static const NYsoqx9bLfN ytz15vqu0Yn[] = {
  {"debug", iF3rcj},
  {"getuservalue", YBsY},
  {"gethook", R3wCXACMr53oX},
  {"getinfo", TbYNV9zbxZs},
  {"getlocal", oPpUn},
  {"getregistry", NDCYUTun},
  {"getmetatable", sSam4},
  {"getupvalue", G9OtcZczN},
  {"upvaluejoin", fXzcva5uj},
  {"upvalueid", WV1bvgQH},
  {"setuservalue", sRswMiKsw00},
  {"sethook", mVIya},
  {"setlocal", o2QTyg1Y6kwD},
  {"setmetatable", nUpQ},
  {"setupvalue", tPyDqFwS8M9sV},
  {"traceback", lN5g8Ebi},
  {"setcstacklimit", BAzrIq},
  {nl1DOK, nl1DOK}
};


dT5_mcDr9A3U int HdrwOpWZ_J (j53P4CKIa *b8Kdcgq) {
  WQmGYQFDQ(b8Kdcgq, ytz15vqu0Yn);
  return 1;
}

