/*
** $Id: ltests.c $
** Internal Module for Debugging of the Lua Implementation
** See Copyright Notice in lua.h
*/

#define h1kNz5prDzPN
#define ybrdTP80h08Z

#include "lprefix.h"


#include <limits.h>
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lua.h"

#include "lapi.h"
#include "lauxlib.h"
#include "lcode.h"
#include "lctype.h"
#include "ldebug.h"
#include "ldo.h"
#include "lfunc.h"
#include "lmem.h"
#include "lopcodes.h"
#include "lopnames.h"
#include "lstate.h"
#include "lstring.h"
#include "ltable.h"
#include "lualib.h"



/*
** The whole module only makes sense with LUA_DEBUG on
*/
#if GAVf_Rlr(xW_Dr)


void *ZH98TRL = 0;


#define nl14(dANGorZhNcp,F6fLjE)	qYo2Qk(dANGorZhNcp->HSNz0_OOHAEcp->qiUEcxF2uu.bIf_6NS_ + (F6fLjE))


static int aFoNWlK08 (oKhhn5 *dANGorZhNcp, oKhhn5 *F1cW6, const char *d2UwF29q1PF3g);


static void AQAJmhrLOSJwa (oKhhn5 *dANGorZhNcp, const char *nqRl4nbsb4ute, int CRTowNkI9UsA) {
  fkeYjCR(dANGorZhNcp, CRTowNkI9UsA);
  LlBlEdffFES(dANGorZhNcp, -2, nqRl4nbsb4ute);
}


static void qBXxgkSl (oKhhn5 *dANGorZhNcp, const kxUFNdHfDo1yl *Gq1g5) {
  Z6uqGSTBb(dANGorZhNcp, dANGorZhNcp->bP971Q5jVlY9.bIf_6NS_, Gq1g5);
  ml7Sru(dANGorZhNcp);
}


static void uauqoVqtju (const char *gW9lah_, const char *P9gjLrnk, const char *XsruY) {
  vm1Pm9TH7j(OVVkG85, gW9lah_, P9gjLrnk);
  if (XsruY)
    vm1Pm9TH7j(OVVkG85, "extra info: %s\n", XsruY);
  /* avoid assertion failures when exiting */
  FEtY9Gx.fllG = FEtY9Gx.ik3GsL = 0;
  dDYQnbq4BWPu(oLcWmv);
}


static int aWIvuRrCLcXIt (oKhhn5 *dANGorZhNcp) {
  const char *qpnIOpMLY = (GZtg(dANGorZhNcp, -1) == t5Z_5teTn7)
                  ? aCBxOp(dANGorZhNcp, -1)
                  : "error object is not a string";
  return (uauqoVqtju("PANIC: unprotected error in call to Lua API (%s)\n",
                   qpnIOpMLY, qzdsHHKSA4),
          0);  /* do not return to Lua */
}


/*
** Warning function for tests. First, it concatenates all parts of
** a warning in buffer 'buff'. Then, it has three modes:
** - 0.normal: messages starting with '#' are shown on standard output;
** - other messages abort the tests (they represent real warning
** conditions; the standard tests should not generate these conditions
** unexpectedly);
** - 1.allow: all messages are shown;
** - 2.store: all warnings go to the global '_WARN';
*/
static void E1Jqc (void *fNsyd7Ax, const char *qpnIOpMLY, int iAGfTFmw) {
  oKhhn5 *dANGorZhNcp = gYyWgWC(oKhhn5 *, fNsyd7Ax);
  static char Khh7WZvdP[200] = "";  /* should be enough for tests... */
  static int bkf4ongeg9 = 0;
  static int wqN1tWuU = 0;  /* start in normal mode */
  static int WMRFgIeBsC_no = 0;
  if (!WMRFgIeBsC_no && !iAGfTFmw && *qpnIOpMLY == '@') {  /* control message? */
    if (Khh7WZvdP[0] != '\0')
      uauqoVqtju("Control warning during warning: %s\naborting...\n", qpnIOpMLY, Khh7WZvdP);
    if (ZJzN(qpnIOpMLY, "@off") == 0)
      bkf4ongeg9 = 0;
    else if (ZJzN(qpnIOpMLY, "@on") == 0)
      bkf4ongeg9 = 1;
    else if (ZJzN(qpnIOpMLY, "@normal") == 0)
      wqN1tWuU = 0;
    else if (ZJzN(qpnIOpMLY, "@allow") == 0)
      wqN1tWuU = 1;
    else if (ZJzN(qpnIOpMLY, "@store") == 0)
      wqN1tWuU = 2;
    else
      uauqoVqtju("Invalid control warning in test mode: %s\naborting...\n",
              qpnIOpMLY, qzdsHHKSA4);
    return;
  }
  WMRFgIeBsC_no = iAGfTFmw;
  if (nkLSGsqq(qpnIOpMLY) >= sizeof(Khh7WZvdP) - nkLSGsqq(Khh7WZvdP))
    uauqoVqtju("warnf-buffer overflow (%s)\n", qpnIOpMLY, Khh7WZvdP);
  vOpFavaa03(Khh7WZvdP, qpnIOpMLY);  /* add new message to current warning */
  if (!iAGfTFmw) {  /* message finished? */
    j28agnKV1g(dANGorZhNcp);
    gi1pjOw2(dANGorZhNcp, 1, "warn stack space");
    eV75(dANGorZhNcp, "_WARN");
    if (!HpPj68yPUp9(dANGorZhNcp, -1))
      T8YUzJ0(dANGorZhNcp, 1);  /* ok, no previous unexpected warning */
    else {
      uauqoVqtju("Unhandled warning in store mode: %s\naborting...\n",
              aCBxOp(dANGorZhNcp, -1), Khh7WZvdP);
    }
    OzVt2IX51dE(dANGorZhNcp);
    switch (wqN1tWuU) {
      case 0: {  /* normal */
        if (Khh7WZvdP[0] != '#' && bkf4ongeg9)  /* unexpected warning? */
          uauqoVqtju("Unexpected warning in test mode: %s\naborting...\n",
                  Khh7WZvdP, qzdsHHKSA4);
      }  /* FALLTHROUGH */
      case 1: {  /* allow */
        if (bkf4ongeg9)
          vm1Pm9TH7j(OVVkG85, "Lua warning: %s\n", Khh7WZvdP);  /* print warning */
        break;
      }
      case 2: {  /* store */
        j28agnKV1g(dANGorZhNcp);
        gi1pjOw2(dANGorZhNcp, 1, "warn stack space");
        U5Uep4tkbF(dANGorZhNcp, Khh7WZvdP);
        QZ_KqhQywuF(dANGorZhNcp, "_WARN");  /* assign message to global '_WARN' */
        OzVt2IX51dE(dANGorZhNcp);
        break;
      }
    }
    Khh7WZvdP[0] = '\0';  /* prepare buffer for next warning */
  }
}


/*
** {======================================================================
** Controlled version for realloc.
** =======================================================================
*/

#define GwrEz5		0x55  /* 01010101 (a nice pattern) */

typedef union PFCyXor86q {
  JhbkVnKYowXQ;
  struct {
    PIP7A Zx4tsBq;
    int mmlLsUoU;
  } pdqL;
} PFCyXor86q;


#if !GAVf_Rlr(h1XFp1w7)

/* full memory check */
#define PQka7EhbeP_	16  /* size of marks after each block */
#define y_6kFa3(XcS6tyW,Zx4tsBq)	VWYSH(XcS6tyW, -GwrEz5, Zx4tsBq)

#else

/* external memory check: don't do it twice */
#define PQka7EhbeP_	0
#define y_6kFa3(XcS6tyW,Zx4tsBq)	/* empty */

#endif


AMtfuwY1W3 FEtY9Gx =
  {0, 0UL, 0UL, 0UL, 0UL, (~0UL),
   {0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL}};


static void VPWAY40 (AMtfuwY1W3 *vtLlBtc, PFCyXor86q *I6zk2gQ6uYtE) {
  if (I6zk2gQ6uYtE) {
    PIP7A Zx4tsBq = I6zk2gQ6uYtE->pdqL.Zx4tsBq;
    int Ug3WiOFRVtz;
    for (Ug3WiOFRVtz = 0; Ug3WiOFRVtz < PQka7EhbeP_; Ug3WiOFRVtz++)  /* check marks after block */
      j8hck5(*(XMXG2v(I6zk2gQ6uYtE + 1) + Zx4tsBq + Ug3WiOFRVtz) == GwrEz5);
    vtLlBtc->IHK3wfbHIiJp[I6zk2gQ6uYtE->pdqL.mmlLsUoU]--;
    y_6kFa3(I6zk2gQ6uYtE, sizeof(PFCyXor86q) + Zx4tsBq + PQka7EhbeP_);  /* erase block */
    uYK9q3(I6zk2gQ6uYtE);  /* actually free block */
    vtLlBtc->fllG--;  /* update counts */
    vtLlBtc->ik3GsL -= Zx4tsBq;
  }
}


void *NpR710XusKht (void *fNsyd7Ax, void *Qxjv9GmlqX, PIP7A BoeJSYt, PIP7A Zx4tsBq) {
  AMtfuwY1W3 *vtLlBtc = gYyWgWC(AMtfuwY1W3 *, fNsyd7Ax);
  PFCyXor86q *I6zk2gQ6uYtE = gYyWgWC(PFCyXor86q *, Qxjv9GmlqX);
  int mmlLsUoU;
  if (vtLlBtc->YyPROIqkrLe == 0) {  /* first time? */
    char *WH07HSfUJ = N_a_S("MEMLIMIT");  /* initialize memory limit */
    vtLlBtc->YyPROIqkrLe = WH07HSfUJ ? oRF9QFhfDi(WH07HSfUJ, qzdsHHKSA4, 10) : TQ0tjxy0q6Mom;
  }
  if (I6zk2gQ6uYtE == qzdsHHKSA4) {
    mmlLsUoU = (BoeJSYt < qwxP3AlaW) ? BoeJSYt : 0;
    BoeJSYt = 0;
  }
  else {
    I6zk2gQ6uYtE--;  /* go to real header */
    mmlLsUoU = I6zk2gQ6uYtE->pdqL.mmlLsUoU;
    j8hck5(BoeJSYt == I6zk2gQ6uYtE->pdqL.Zx4tsBq);
  }
  if (Zx4tsBq == 0) {
    VPWAY40(vtLlBtc, I6zk2gQ6uYtE);
    return qzdsHHKSA4;
  }
  if (vtLlBtc->n2_mCqu0Ni7) {
    vtLlBtc->n2_mCqu0Ni7 = 0;
    return qzdsHHKSA4;  /* fake a single memory allocation error */
  }
  if (vtLlBtc->diN4o1kvJm != ~0UL && Zx4tsBq != BoeJSYt) {  /* count limit in use? */
    if (vtLlBtc->diN4o1kvJm == 0)
      return qzdsHHKSA4;  /* fake a memory allocation error */
    vtLlBtc->diN4o1kvJm--;
  }
  if (Zx4tsBq > BoeJSYt && vtLlBtc->ik3GsL+Zx4tsBq-BoeJSYt > vtLlBtc->YyPROIqkrLe)
    return qzdsHHKSA4;  /* fake a memory allocation error */
  else {
    PFCyXor86q *vh42unq4IPiG;
    int Ug3WiOFRVtz;
    PIP7A rRytY7k6UJ = (BoeJSYt < Zx4tsBq) ? BoeJSYt : Zx4tsBq;
    PIP7A tlL57I53RXEo3 = sizeof(PFCyXor86q) + Zx4tsBq + PQka7EhbeP_;
    if (tlL57I53RXEo3 < Zx4tsBq) return qzdsHHKSA4;  /* arithmetic overflow! */
    vh42unq4IPiG = gYyWgWC(PFCyXor86q *, JmBBk1P(tlL57I53RXEo3));  /* alloc a new block */
    if (vh42unq4IPiG == qzdsHHKSA4)
      return qzdsHHKSA4;  /* really out of memory? */
    if (I6zk2gQ6uYtE) {
      kjNk(vh42unq4IPiG + 1, I6zk2gQ6uYtE + 1, rRytY7k6UJ);  /* copy old contents */
      VPWAY40(vtLlBtc, I6zk2gQ6uYtE);  /* erase (and check) old copy */
    }
    /* initialize new part of the block with something weird */
    y_6kFa3(XMXG2v(vh42unq4IPiG + 1) + rRytY7k6UJ, Zx4tsBq - rRytY7k6UJ);
    /* initialize marks after block */
    for (Ug3WiOFRVtz = 0; Ug3WiOFRVtz < PQka7EhbeP_; Ug3WiOFRVtz++)
      *(XMXG2v(vh42unq4IPiG + 1) + Zx4tsBq + Ug3WiOFRVtz) = GwrEz5;
    vh42unq4IPiG->pdqL.Zx4tsBq = Zx4tsBq;
    vh42unq4IPiG->pdqL.mmlLsUoU = mmlLsUoU;
    vtLlBtc->ik3GsL += Zx4tsBq;
    if (vtLlBtc->ik3GsL > vtLlBtc->cRjM)
      vtLlBtc->cRjM = vtLlBtc->ik3GsL;
    vtLlBtc->fllG++;
    vtLlBtc->IHK3wfbHIiJp[mmlLsUoU]++;
    return vh42unq4IPiG + 1;
  }
}


/* }====================================================================== */



/*
** {=====================================================================
** Functions to check memory consistency.
** Most of these checks are done through asserts, so this code does
** not make sense with asserts off. For this reason, it uses 'assert'
** directly, instead of 'lua_assert'.
** ======================================================================
*/

#include <assert.h>

/*
** Check GC invariants. For incremental mode, a black object cannot
** point to a white one. For generational mode, really old objects
** cannot point to young objects. Both old1 and touched2 objects
** cannot point to new objects (but can point to survivals).
** (Threads and open upvalues, despite being marked "really old",
** continue to be visited in all collections, and therefore can point to
** new objects. They, and only they, are old but gray.)
*/
static int EJ7futEHxdSsk (a1WmD *GxL2EpLSjV3, e9bY73cQhQC *Yv4Is, e9bY73cQhQC *HTm5wQ43ct) {
  if (RAe9(GxL2EpLSjV3,HTm5wQ43ct)) return 0;
  if (DjwiqbATIApU(GxL2EpLSjV3))
    return 1;  /* no invariants */
  else if (GxL2EpLSjV3->oFsU == qvnJfaxKGXfm)
    return !(eFcp3enA(Yv4Is) && sM2oiF(HTm5wQ43ct));  /* basic incremental invariant */
  else {  /* generational mode */
    if ((yXbmdJRUV1wCz(Yv4Is) == m4Dx_x1 && eFcp3enA(Yv4Is)) && !I2LEajIuPOj(HTm5wQ43ct))
      return 0;
    if (((yXbmdJRUV1wCz(Yv4Is) == VfnjW7rG || yXbmdJRUV1wCz(Yv4Is) == t8dODH5) && eFcp3enA(Yv4Is)) &&
          yXbmdJRUV1wCz(HTm5wQ43ct) == s7Zitgw)
      return 0;
    return 1;
  }
}


static void BG4lCGRl (a1WmD *GxL2EpLSjV3, e9bY73cQhQC *Gq1g5) {
  wscxoCnE2("||%s(%p)-%c%c(%02X)||",
           bQaitc2M(Os4dT8OF(Gq1g5->gfmLF8se)), (void *)Gq1g5,
           RAe9(GxL2EpLSjV3,Gq1g5) ? 'd' : eFcp3enA(Gq1g5) ? 'b' : sM2oiF(Gq1g5) ? 'w' : 'g',
           "ns01oTt"[yXbmdJRUV1wCz(Gq1g5)], Gq1g5->Xb9Ou4ahF);
  if (Gq1g5->gfmLF8se == tgUDA || Gq1g5->gfmLF8se == TQKYUc0fq)
    wscxoCnE2(" '%s'", KtkvwjQ5(NYqhAI_nVD(Gq1g5)));
}


void XVIp (oKhhn5 *dANGorZhNcp, struct e9bY73cQhQC *Gq1g5) {
  BG4lCGRl(W9BtJO1VI745j(dANGorZhNcp), Gq1g5);
}

static int u4S7OZC_lONL (a1WmD *GxL2EpLSjV3, e9bY73cQhQC *Yv4Is, e9bY73cQhQC *HTm5wQ43ct) {
  int Hs15ZFRdX = EJ7futEHxdSsk(GxL2EpLSjV3, Yv4Is, HTm5wQ43ct);
  if (!Hs15ZFRdX) {
    wscxoCnE2("%d(%02X) - ", GxL2EpLSjV3->YBvtpV, GxL2EpLSjV3->qvPgxx);
    BG4lCGRl(GxL2EpLSjV3, Yv4Is);
    wscxoCnE2("  ->  ");
    BG4lCGRl(GxL2EpLSjV3, HTm5wQ43ct);
    wscxoCnE2("\n");
  }
  return Hs15ZFRdX;
}


static void ydr6UMyq36l (a1WmD *GxL2EpLSjV3, e9bY73cQhQC *Yv4Is, e9bY73cQhQC *HTm5wQ43ct) {
    C37TwhweKOR(u4S7OZC_lONL(GxL2EpLSjV3, Yv4Is, HTm5wQ43ct));
}


/*
** Version where 't' can be NULL. In that case, it should not apply the
** macro 'obj2gco' over the object. ('t' may have several types, so this
** definition must be a macro.)  Most checks need this version, because
** the check may run while an object is still being created.
*/
#define SrElEDHwRZ0(GxL2EpLSjV3,Yv4Is,HTm5wQ43ct)	{ if (HTm5wQ43ct) ydr6UMyq36l(GxL2EpLSjV3,Yv4Is,ojj1VAM4whQSI(HTm5wQ43ct)); }


static void wbHtEYZ (a1WmD *GxL2EpLSjV3, e9bY73cQhQC *Yv4Is, const kxUFNdHfDo1yl *HTm5wQ43ct) {
  C37TwhweKOR(!oGDpQT(HTm5wQ43ct) || (T2xw4ot(HTm5wQ43ct) && u4S7OZC_lONL(GxL2EpLSjV3, Yv4Is, hiTZwvR(HTm5wQ43ct))));
}


static void clWiiKFFQ5CLC (a1WmD *GxL2EpLSjV3, vz35xTxsDS *kRXwBT) {
  unsigned int Ug3WiOFRVtz;
  unsigned int ifHCHP3F3be = xYd8j2(kRXwBT);
  LmZVUm4ugCEyI *sxS1yv0OWbd, *WH07HSfUJ = HwmLE(kRXwBT, MVMJfUUhKf(kRXwBT));
  e9bY73cQhQC *SlDML = ojj1VAM4whQSI(kRXwBT);
  SrElEDHwRZ0(GxL2EpLSjV3, SlDML, kRXwBT->fOvpgXh);
  for (Ug3WiOFRVtz = 0; Ug3WiOFRVtz < ifHCHP3F3be; Ug3WiOFRVtz++)
    wbHtEYZ(GxL2EpLSjV3, SlDML, &kRXwBT->cx1DgEI[Ug3WiOFRVtz]);
  for (sxS1yv0OWbd = HwmLE(kRXwBT, 0); sxS1yv0OWbd < WH07HSfUJ; sxS1yv0OWbd++) {
    if (!xPUTzhdd_y(l6Ump1suvf(sxS1yv0OWbd))) {
      kxUFNdHfDo1yl F6fLjE;
      RCXkcm(GxL2EpLSjV3->ipiv, &F6fLjE, sxS1yv0OWbd);
      C37TwhweKOR(!dH26C0sbEqb(sxS1yv0OWbd));
      wbHtEYZ(GxL2EpLSjV3, SlDML, &F6fLjE);
      wbHtEYZ(GxL2EpLSjV3, SlDML, l6Ump1suvf(sxS1yv0OWbd));
    }
  }
}


static void JT9ElGi3JZu (a1WmD *GxL2EpLSjV3, jnLFnpfjeMz *emra) {
  int Ug3WiOFRVtz;
  e9bY73cQhQC *SlDML = ojj1VAM4whQSI(emra);
  SrElEDHwRZ0(GxL2EpLSjV3, SlDML, emra->fOvpgXh);
  for (Ug3WiOFRVtz = 0; Ug3WiOFRVtz < emra->wFzxBHG5; Ug3WiOFRVtz++)
    wbHtEYZ(GxL2EpLSjV3, SlDML, &emra->rVFdOyECG[Ug3WiOFRVtz].rVFdOyECG);
}


static void wDzU (a1WmD *GxL2EpLSjV3, hIcdmtM0 *Yv4Is) {
  int Ug3WiOFRVtz;
  e9bY73cQhQC *D6BWRiUxAPM8h = ojj1VAM4whQSI(Yv4Is);
  SrElEDHwRZ0(GxL2EpLSjV3, D6BWRiUxAPM8h, Yv4Is->gE7ubTDuC);
  for (Ug3WiOFRVtz=0; Ug3WiOFRVtz<Yv4Is->hyZj5s; Ug3WiOFRVtz++) {
    if (oGDpQT(Yv4Is->F6fLjE + Ug3WiOFRVtz))
      ydr6UMyq36l(GxL2EpLSjV3, D6BWRiUxAPM8h, hiTZwvR(Yv4Is->F6fLjE + Ug3WiOFRVtz));
  }
  for (Ug3WiOFRVtz=0; Ug3WiOFRVtz<Yv4Is->VA7UzDq; Ug3WiOFRVtz++)
    SrElEDHwRZ0(GxL2EpLSjV3, D6BWRiUxAPM8h, Yv4Is->nEcQJBElJ[Ug3WiOFRVtz].nqRl4nbsb4ute);
  for (Ug3WiOFRVtz=0; Ug3WiOFRVtz<Yv4Is->ctFkHe; Ug3WiOFRVtz++)
    SrElEDHwRZ0(GxL2EpLSjV3, D6BWRiUxAPM8h, Yv4Is->bIf_6NS_[Ug3WiOFRVtz]);
  for (Ug3WiOFRVtz=0; Ug3WiOFRVtz<Yv4Is->FASanK3WMQ8; Ug3WiOFRVtz++)
    SrElEDHwRZ0(GxL2EpLSjV3, D6BWRiUxAPM8h, Yv4Is->jqO_ymD1B9E[Ug3WiOFRVtz].CT9HOW4);
}


static void nbq8kEEjc (a1WmD *GxL2EpLSjV3, OliZBUrg3amRv *FQdtm) {
  e9bY73cQhQC *wyGpGW6ib = ojj1VAM4whQSI(FQdtm);
  int Ug3WiOFRVtz;
  for (Ug3WiOFRVtz = 0; Ug3WiOFRVtz < FQdtm->aeO0fS7Qjx94; Ug3WiOFRVtz++)
    wbHtEYZ(GxL2EpLSjV3, wyGpGW6ib, &FQdtm->aBVw[Ug3WiOFRVtz]);
}


static void Rb8JiIa (a1WmD *GxL2EpLSjV3, Gysihg_xj9z8 *FQdtm) {
  e9bY73cQhQC *wyGpGW6ib = ojj1VAM4whQSI(FQdtm);
  int Ug3WiOFRVtz;
  SrElEDHwRZ0(GxL2EpLSjV3, wyGpGW6ib, FQdtm->bIf_6NS_);
  for (Ug3WiOFRVtz=0; Ug3WiOFRVtz<FQdtm->aeO0fS7Qjx94; Ug3WiOFRVtz++) {
    ZSU9u0k *rVFdOyECG = FQdtm->gXJdzL7[Ug3WiOFRVtz];
    if (rVFdOyECG) {
      SrElEDHwRZ0(GxL2EpLSjV3, wyGpGW6ib, rVFdOyECG);
      if (!r8dEoFriczgC(rVFdOyECG))
        wbHtEYZ(GxL2EpLSjV3, ojj1VAM4whQSI(rVFdOyECG), rVFdOyECG->ADRxlYWSxK.bIf_6NS_);
    }
  }
}


static int BgFQ (rVefXuEF1y *HSNz0_OOHAEcp) {
  if (!SUghYxw(HSNz0_OOHAEcp)) return 1;
  else {
    j2Tyj Yv4Is = HSNz0_OOHAEcp->qiUEcxF2uu.bIf_6NS_;
    hIcdmtM0 *bIf_6NS_ = qAvWooIOF__9M(qYo2Qk(Yv4Is))->bIf_6NS_;
    return bIf_6NS_->iiK0a58EC <= HSNz0_OOHAEcp->emra.VE6iJGqjdzk.vpqv &&
           HSNz0_OOHAEcp->emra.VE6iJGqjdzk.vpqv <= bIf_6NS_->iiK0a58EC + bIf_6NS_->DgRehOek;
  }
}


static void UCp0yaCSm (a1WmD *GxL2EpLSjV3, oKhhn5 *F1cW6) {
  j2Tyj Gq1g5;
  rVefXuEF1y *HSNz0_OOHAEcp;
  ZSU9u0k *rVFdOyECG;
  C37TwhweKOR(!RAe9(GxL2EpLSjV3, F1cW6));
  if (F1cW6->t1lfjaHcT.bIf_6NS_ == qzdsHHKSA4) {  /* incomplete thread? */
    C37TwhweKOR(F1cW6->nnWp9ioeNXyW == qzdsHHKSA4 && F1cW6->HSNz0_OOHAEcp == qzdsHHKSA4);
    return;
  }
  for (rVFdOyECG = F1cW6->nnWp9ioeNXyW; rVFdOyECG != qzdsHHKSA4; rVFdOyECG = rVFdOyECG->emra.cEPr2qYcgIE.uLFb4k1SMQYr)
    C37TwhweKOR(r8dEoFriczgC(rVFdOyECG));  /* must be open */
  C37TwhweKOR(F1cW6->bP971Q5jVlY9.bIf_6NS_ <= F1cW6->bPNs.bIf_6NS_);
  C37TwhweKOR(F1cW6->lS6oUJUNMGVD8.bIf_6NS_ <= F1cW6->bP971Q5jVlY9.bIf_6NS_);
  for (HSNz0_OOHAEcp = F1cW6->HSNz0_OOHAEcp; HSNz0_OOHAEcp != qzdsHHKSA4; HSNz0_OOHAEcp = HSNz0_OOHAEcp->DBosdBb_We) {
    C37TwhweKOR(HSNz0_OOHAEcp->bP971Q5jVlY9.bIf_6NS_ <= F1cW6->bPNs.bIf_6NS_);
    C37TwhweKOR(BgFQ(HSNz0_OOHAEcp));
  }
  for (Gq1g5 = F1cW6->t1lfjaHcT.bIf_6NS_; Gq1g5 < F1cW6->bPNs.bIf_6NS_; Gq1g5++)
    rJ5DQYSiH5(F1cW6, qYo2Qk(Gq1g5));  /* entire stack must have valid values */
}


static void NbdwMj9uBvC (a1WmD *GxL2EpLSjV3, e9bY73cQhQC *Gq1g5) {
  switch (Gq1g5->gfmLF8se) {
    case GxjL: {
      JT9ElGi3JZu(GxL2EpLSjV3, VtXUhT4T0(Gq1g5));
      break;
    }
    case n7PDqe4J8: {
      wbHtEYZ(GxL2EpLSjV3, Gq1g5, Ef99_cl(Gq1g5)->ADRxlYWSxK.bIf_6NS_);
      break;
    }
    case VNplb6F: {
      clWiiKFFQ5CLC(GxL2EpLSjV3, gBzqO(Gq1g5));
      break;
    }
    case DlBBb8mM: {
      UCp0yaCSm(GxL2EpLSjV3, VbybI7aq(Gq1g5));
      break;
    }
    case OK9oi: {
      Rb8JiIa(GxL2EpLSjV3, VWHiF4uWH(Gq1g5));
      break;
    }
    case WXqEU: {
      nbq8kEEjc(GxL2EpLSjV3, o_5U2NsjXw2P(Gq1g5));
      break;
    }
    case D3CyKxNnZY: {
      wDzU(GxL2EpLSjV3, cUQnwTe2z(Gq1g5));
      break;
    }
    case tgUDA:
    case TQKYUc0fq: {
      C37TwhweKOR(!UbU9O(Gq1g5));  /* strings are never gray */
      break;
    }
    default: C37TwhweKOR(0);
  }
}


/*
** Check consistency of an object:
** - Dead objects can only happen in the 'allgc' list during a sweep
** phase (controlled by the caller through 'maybedead').
** - During pause, all objects must be white.
** - In generational mode:
**   * objects must be old enough for their lists ('listage').
**   * old objects cannot be white.
**   * old objects must be black, except for 'touched1', 'old0',
** threads, and open upvalues.
*/
static void LuRGFHYhgvHx (a1WmD *GxL2EpLSjV3, e9bY73cQhQC *Gq1g5, int cwl6jxiDOc,
                         int W_cjART8) {
  if (RAe9(GxL2EpLSjV3, Gq1g5))
    C37TwhweKOR(cwl6jxiDOc);
  else {
    C37TwhweKOR(GxL2EpLSjV3->YBvtpV != qM7vt2Wh || sM2oiF(Gq1g5));
    if (GxL2EpLSjV3->oFsU == SLwavq_L) {  /* generational mode? */
      C37TwhweKOR(yXbmdJRUV1wCz(Gq1g5) >= W_cjART8);
      C37TwhweKOR(!sM2oiF(Gq1g5) || !I2LEajIuPOj(Gq1g5));
      if (I2LEajIuPOj(Gq1g5)) {
        C37TwhweKOR(eFcp3enA(Gq1g5) ||
        yXbmdJRUV1wCz(Gq1g5) == dpmbUXO ||
        yXbmdJRUV1wCz(Gq1g5) == Q099k5G ||
        Gq1g5->gfmLF8se == DlBBb8mM ||
        (Gq1g5->gfmLF8se == n7PDqe4J8 && r8dEoFriczgC(Ef99_cl(Gq1g5))));
      }
    }
    NbdwMj9uBvC(GxL2EpLSjV3, Gq1g5);
  }
}


static lBURzSN xDMFOpDMShh (a1WmD *GxL2EpLSjV3, e9bY73cQhQC *Gq1g5) {
  int ik3GsL = 0;  /* count number of elements in the list */
  nUwjhF(GxL2EpLSjV3);  /* better to keep it if we need to print an object */
  while (Gq1g5) {
    C37TwhweKOR(!!UbU9O(Gq1g5) ^ (yXbmdJRUV1wCz(Gq1g5) == t8dODH5));
    C37TwhweKOR(!BwyO(Gq1g5->Xb9Ou4ahF, tOLqKgvP));
    if (zMeu7JNXnF2v(GxL2EpLSjV3))
      DJlTYi2rSE(Gq1g5->Xb9Ou4ahF, tOLqKgvP);  /* mark that object is in a gray list */
    ik3GsL++;
    switch (Gq1g5->gfmLF8se) {
      case VNplb6F: Gq1g5 = gBzqO(Gq1g5)->bEgGc5fh; break;
      case OK9oi: Gq1g5 = VWHiF4uWH(Gq1g5)->bEgGc5fh; break;
      case WXqEU: Gq1g5 = o_5U2NsjXw2P(Gq1g5)->bEgGc5fh; break;
      case DlBBb8mM: Gq1g5 = VbybI7aq(Gq1g5)->bEgGc5fh; break;
      case D3CyKxNnZY: Gq1g5 = cUQnwTe2z(Gq1g5)->bEgGc5fh; break;
      case GxjL:
        C37TwhweKOR(VtXUhT4T0(Gq1g5)->wFzxBHG5 > 0);
        Gq1g5 = VtXUhT4T0(Gq1g5)->bEgGc5fh;
        break;
      default: C37TwhweKOR(0);  /* other objects cannot be in a gray list */
    }
  }
  return ik3GsL;
}


/*
** Check objects in gray lists.
*/
static lBURzSN dJYWpZ (a1WmD *GxL2EpLSjV3) {
  int ik3GsL = 0;  /* count number of elements in all lists */
  if (!zMeu7JNXnF2v(GxL2EpLSjV3)) return ik3GsL;
  ik3GsL += xDMFOpDMShh(GxL2EpLSjV3, GxL2EpLSjV3->hsRPc);
  ik3GsL += xDMFOpDMShh(GxL2EpLSjV3, GxL2EpLSjV3->QZipRSOB);
  ik3GsL += xDMFOpDMShh(GxL2EpLSjV3, GxL2EpLSjV3->P66zS);
  ik3GsL += xDMFOpDMShh(GxL2EpLSjV3, GxL2EpLSjV3->tYZ62DRU);
  ik3GsL += xDMFOpDMShh(GxL2EpLSjV3, GxL2EpLSjV3->vnlpP);
  return ik3GsL;
}


/*
** Check whether 'o' should be in a gray list. If so, increment
** 'count' and check its TESTBIT. (It must have been previously set by
** 'checkgraylist'.)
*/
static void DKsErt (a1WmD *GxL2EpLSjV3, e9bY73cQhQC *Gq1g5, lBURzSN *FG5BSdPLq) {
  if (!zMeu7JNXnF2v(GxL2EpLSjV3))
    return;  /* gray lists not being kept in these phases */
  if (Gq1g5->gfmLF8se == n7PDqe4J8) {
    /* only open upvalues can be gray */
    C37TwhweKOR(!UbU9O(Gq1g5) || r8dEoFriczgC(Ef99_cl(Gq1g5)));
    return;  /* upvalues are never in gray lists */
  }
  /* these are the ones that must be in gray lists */
  if (UbU9O(Gq1g5) || yXbmdJRUV1wCz(Gq1g5) == t8dODH5) {
    (*FG5BSdPLq)++;
    C37TwhweKOR(BwyO(Gq1g5->Xb9Ou4ahF, tOLqKgvP));
    XkMUDkgH4Q(Gq1g5->Xb9Ou4ahF, tOLqKgvP);  /* prepare for next cycle */
  }
}


static lBURzSN n_O4G_Ae (a1WmD *GxL2EpLSjV3, int cwl6jxiDOc, int cXGAgCihs,
  e9bY73cQhQC *BZVxsdX0DPTLl, e9bY73cQhQC *ZZPh0, e9bY73cQhQC *VwLePo, e9bY73cQhQC *N99dTcf_kvI3) {
  e9bY73cQhQC *Gq1g5;
  lBURzSN ik3GsL = 0;  /* number of object that should be in  gray lists */
  for (Gq1g5 = BZVxsdX0DPTLl; Gq1g5 != ZZPh0; Gq1g5 = Gq1g5->uLFb4k1SMQYr) {
    LuRGFHYhgvHx(GxL2EpLSjV3, Gq1g5, cwl6jxiDOc, s7Zitgw);
    DKsErt(GxL2EpLSjV3, Gq1g5, &ik3GsL);
    C37TwhweKOR(!cXGAgCihs == !tJHueRQ(Gq1g5));
  }
  for (Gq1g5 = ZZPh0; Gq1g5 != VwLePo; Gq1g5 = Gq1g5->uLFb4k1SMQYr) {
    LuRGFHYhgvHx(GxL2EpLSjV3, Gq1g5, 0, G0v1);
    DKsErt(GxL2EpLSjV3, Gq1g5, &ik3GsL);
    C37TwhweKOR(!cXGAgCihs == !tJHueRQ(Gq1g5));
  }
  for (Gq1g5 = VwLePo; Gq1g5 != N99dTcf_kvI3; Gq1g5 = Gq1g5->uLFb4k1SMQYr) {
    LuRGFHYhgvHx(GxL2EpLSjV3, Gq1g5, 0, VfnjW7rG);
    DKsErt(GxL2EpLSjV3, Gq1g5, &ik3GsL);
    C37TwhweKOR(!cXGAgCihs == !tJHueRQ(Gq1g5));
  }
  for (Gq1g5 = N99dTcf_kvI3; Gq1g5 != qzdsHHKSA4; Gq1g5 = Gq1g5->uLFb4k1SMQYr) {
    LuRGFHYhgvHx(GxL2EpLSjV3, Gq1g5, 0, m4Dx_x1);
    DKsErt(GxL2EpLSjV3, Gq1g5, &ik3GsL);
    C37TwhweKOR(!cXGAgCihs == !tJHueRQ(Gq1g5));
  }
  return ik3GsL;
}


int kMNwQFYT9S (oKhhn5 *dANGorZhNcp) {
  a1WmD *GxL2EpLSjV3 = W9BtJO1VI745j(dANGorZhNcp);
  e9bY73cQhQC *Gq1g5;
  int cwl6jxiDOc;
  lBURzSN Ul2h;  /* total of objects that are in gray lists */
  lBURzSN KFPPU;  /* total of objects that should be in gray lists */
  if (zMeu7JNXnF2v(GxL2EpLSjV3)) {
    C37TwhweKOR(!sM2oiF(GxL2EpLSjV3->ipiv));
    C37TwhweKOR(!sM2oiF(hiTZwvR(&GxL2EpLSjV3->NUB34PoU)));
  }
  C37TwhweKOR(!RAe9(GxL2EpLSjV3, hiTZwvR(&GxL2EpLSjV3->NUB34PoU)));
  C37TwhweKOR(GxL2EpLSjV3->wxyvJsZyt == qzdsHHKSA4 || DjwiqbATIApU(GxL2EpLSjV3));
  Ul2h = dJYWpZ(GxL2EpLSjV3);

  /* check 'fixedgc' list */
  for (Gq1g5 = GxL2EpLSjV3->lZ3v; Gq1g5 != qzdsHHKSA4; Gq1g5 = Gq1g5->uLFb4k1SMQYr) {
    C37TwhweKOR(Gq1g5->gfmLF8se == tgUDA && UbU9O(Gq1g5) && yXbmdJRUV1wCz(Gq1g5) == m4Dx_x1);
  }

  /* check 'allgc' list */
  cwl6jxiDOc = (rZ3GAKiSx < GxL2EpLSjV3->YBvtpV && GxL2EpLSjV3->YBvtpV <= swFokh);
  KFPPU = n_O4G_Ae(GxL2EpLSjV3, cwl6jxiDOc, 0, GxL2EpLSjV3->F5vU_wpg,
                             GxL2EpLSjV3->ZZPh0, GxL2EpLSjV3->cI5LYUM, GxL2EpLSjV3->N99dTcf_kvI3);

  /* check 'finobj' list */
  KFPPU += n_O4G_Ae(GxL2EpLSjV3, 0, 1, GxL2EpLSjV3->GBfjff4nOOh6B,
                              GxL2EpLSjV3->xKAPK, GxL2EpLSjV3->H8XSXUYVgmIAK, GxL2EpLSjV3->Whm4scXf);

  /* check 'tobefnz' list */
  for (Gq1g5 = GxL2EpLSjV3->O_saxdf79e; Gq1g5 != qzdsHHKSA4; Gq1g5 = Gq1g5->uLFb4k1SMQYr) {
    LuRGFHYhgvHx(GxL2EpLSjV3, Gq1g5, 0, s7Zitgw);
    DKsErt(GxL2EpLSjV3, Gq1g5, &KFPPU);
    C37TwhweKOR(tJHueRQ(Gq1g5));
    C37TwhweKOR(Gq1g5->gfmLF8se == GxjL || Gq1g5->gfmLF8se == VNplb6F);
  }
  if (zMeu7JNXnF2v(GxL2EpLSjV3))
    C37TwhweKOR(Ul2h == KFPPU);
  return 0;
}

/* }====================================================== */



/*
** {======================================================
** Disassembler
** =======================================================
*/


static char *OwK0Jpvra0 (hIcdmtM0 *bIf_6NS_, int d2UwF29q1PF3g, char *Khh7WZvdP) {
  char *SxajuKViuz0ZP = Khh7WZvdP;
  rcRuuqDSA Ug3WiOFRVtz = bIf_6NS_->iiK0a58EC[d2UwF29q1PF3g];
  pwwIJ4Z Gq1g5 = u4hPZcw(Ug3WiOFRVtz);
  const char *nqRl4nbsb4ute = uEqkYVoSn[Gq1g5];
  int wzEg1d = RjfMbw1l(bIf_6NS_, d2UwF29q1PF3g);
  int hDQ7q8nHqHC = (bIf_6NS_->hDQ7q8nHqHC != qzdsHHKSA4) ? bIf_6NS_->hDQ7q8nHqHC[d2UwF29q1PF3g] : 0;
  if (hDQ7q8nHqHC == T2Prw)
    Khh7WZvdP += E_y36cMEoQT(Khh7WZvdP, "(__");
  else
    Khh7WZvdP += E_y36cMEoQT(Khh7WZvdP, "(%2d", hDQ7q8nHqHC);
  Khh7WZvdP += E_y36cMEoQT(Khh7WZvdP, " - %4d) %4d - ", wzEg1d, d2UwF29q1PF3g);
  switch (TiVO(Gq1g5)) {
    case BwiAH:
      E_y36cMEoQT(Khh7WZvdP, "%-12s%4d %4d %4d%s", nqRl4nbsb4ute,
              awiJddjsRn(Ug3WiOFRVtz), ht2QsfOnqUv(Ug3WiOFRVtz), cDUXqnZj(Ug3WiOFRVtz),
              n6rGLOL8WjF9I(Ug3WiOFRVtz) ? " (k)" : "");
      break;
    case u11ekUikRgdqZ:
      E_y36cMEoQT(Khh7WZvdP, "%-12s%4d %4d", nqRl4nbsb4ute, awiJddjsRn(Ug3WiOFRVtz), VCST9NLUHbwCp(Ug3WiOFRVtz));
      break;
    case wCb_anYrS5:
      E_y36cMEoQT(Khh7WZvdP, "%-12s%4d %4d", nqRl4nbsb4ute, awiJddjsRn(Ug3WiOFRVtz), Qg1PcEix1ah(Ug3WiOFRVtz));
      break;
    case eObVA:
      E_y36cMEoQT(Khh7WZvdP, "%-12s%4d", nqRl4nbsb4ute, fNColgn(Ug3WiOFRVtz));
      break;
    case tq7_kOoE_vr9b:
      E_y36cMEoQT(Khh7WZvdP, "%-12s%4d", nqRl4nbsb4ute, hEeJBP3gX3(Ug3WiOFRVtz));
      break;
  }
  return SxajuKViuz0ZP;
}


#if 0
void bYSdsMOZ2Cs (hIcdmtM0 *L21udy6ec, int Zx4tsBq) {
  int d2UwF29q1PF3g;
  for (d2UwF29q1PF3g=0; d2UwF29q1PF3g<Zx4tsBq; d2UwF29q1PF3g++) {
    char Khh7WZvdP[100];
    wscxoCnE2("%s\n", OwK0Jpvra0(L21udy6ec, d2UwF29q1PF3g, Khh7WZvdP));
  }
  wscxoCnE2("-------\n");
}


void fHZ05fIPFiYj (hIcdmtM0 *L21udy6ec, int d2UwF29q1PF3g) {
  char Khh7WZvdP[100];
  wscxoCnE2("%s\n", OwK0Jpvra0(L21udy6ec, d2UwF29q1PF3g, Khh7WZvdP));
}
#endif


static int zwtmQq (oKhhn5 *dANGorZhNcp) {
  int d2UwF29q1PF3g;
  hIcdmtM0 *bIf_6NS_;
  UpR5K(dANGorZhNcp, BwxBNWt(dANGorZhNcp, 1) && !yxINMVh(dANGorZhNcp, 1),
                 1, "Lua function expected");
  bIf_6NS_ = osy8gRm8(nl14(dANGorZhNcp, 1));
  M82y(dANGorZhNcp);
  AQAJmhrLOSJwa(dANGorZhNcp, "maxstack", bIf_6NS_->AkES9Ea);
  AQAJmhrLOSJwa(dANGorZhNcp, "numparams", bIf_6NS_->TKhC);
  for (d2UwF29q1PF3g=0; d2UwF29q1PF3g<bIf_6NS_->DgRehOek; d2UwF29q1PF3g++) {
    char Khh7WZvdP[100];
    fkeYjCR(dANGorZhNcp, d2UwF29q1PF3g+1);
    U5Uep4tkbF(dANGorZhNcp, OwK0Jpvra0(bIf_6NS_, d2UwF29q1PF3g, Khh7WZvdP));
    LzfF_J(dANGorZhNcp, -3);
  }
  return 1;
}


static int Cx7LV (oKhhn5 *dANGorZhNcp) {
  int d2UwF29q1PF3g;
  hIcdmtM0 *bIf_6NS_;
  UpR5K(dANGorZhNcp, BwxBNWt(dANGorZhNcp, 1) && !yxINMVh(dANGorZhNcp, 1),
                 1, "Lua function expected");
  bIf_6NS_ = osy8gRm8(nl14(dANGorZhNcp, 1));
  wscxoCnE2("maxstack: %d\n", bIf_6NS_->AkES9Ea);
  wscxoCnE2("numparams: %d\n", bIf_6NS_->TKhC);
  for (d2UwF29q1PF3g=0; d2UwF29q1PF3g<bIf_6NS_->DgRehOek; d2UwF29q1PF3g++) {
    char Khh7WZvdP[100];
    wscxoCnE2("%s\n", OwK0Jpvra0(bIf_6NS_, d2UwF29q1PF3g, Khh7WZvdP));
  }
  return 0;
}


static int VUH9Ad9Ca (oKhhn5 *dANGorZhNcp) {
  hIcdmtM0 *bIf_6NS_;
  int Ug3WiOFRVtz;
  UpR5K(dANGorZhNcp, BwxBNWt(dANGorZhNcp, 1) && !yxINMVh(dANGorZhNcp, 1),
                 1, "Lua function expected");
  bIf_6NS_ = osy8gRm8(nl14(dANGorZhNcp, 1));
  sIgWVtMR(dANGorZhNcp, bIf_6NS_->hyZj5s, 0);
  for (Ug3WiOFRVtz=0; Ug3WiOFRVtz<bIf_6NS_->hyZj5s; Ug3WiOFRVtz++) {
    qBXxgkSl(dANGorZhNcp, bIf_6NS_->F6fLjE+Ug3WiOFRVtz);
    I8a7Jpvli7Xxl(dANGorZhNcp, -2, Ug3WiOFRVtz+1);
  }
  return 1;
}


static int xnBNwSqdh0 (oKhhn5 *dANGorZhNcp) {
  hIcdmtM0 *bIf_6NS_;
  int Ug3WiOFRVtz;
  UpR5K(dANGorZhNcp, BwxBNWt(dANGorZhNcp, 1) && !yxINMVh(dANGorZhNcp, 1),
                 1, "Lua function expected");
  bIf_6NS_ = osy8gRm8(nl14(dANGorZhNcp, 1));
  UpR5K(dANGorZhNcp, bIf_6NS_->eaKRwSkLuM2 != qzdsHHKSA4, 1, "function has no debug info");
  sIgWVtMR(dANGorZhNcp, 2 * bIf_6NS_->SqPjW, 0);
  for (Ug3WiOFRVtz=0; Ug3WiOFRVtz < bIf_6NS_->SqPjW; Ug3WiOFRVtz++) {
    fkeYjCR(dANGorZhNcp, bIf_6NS_->eaKRwSkLuM2[Ug3WiOFRVtz].d2UwF29q1PF3g);
    I8a7Jpvli7Xxl(dANGorZhNcp, -2, 2 * Ug3WiOFRVtz + 1);
    fkeYjCR(dANGorZhNcp, bIf_6NS_->eaKRwSkLuM2[Ug3WiOFRVtz].wzEg1d);
    I8a7Jpvli7Xxl(dANGorZhNcp, -2, 2 * Ug3WiOFRVtz + 2);
  }
  return 1;
}


static int Xe0Pd9_3w (oKhhn5 *dANGorZhNcp) {
  hIcdmtM0 *bIf_6NS_;
  int d2UwF29q1PF3g = DLI9dY50TrmnN(CqTplNG4WIp(dANGorZhNcp, 2)) - 1;
  int Ug3WiOFRVtz = 0;
  const char *nqRl4nbsb4ute;
  UpR5K(dANGorZhNcp, BwxBNWt(dANGorZhNcp, 1) && !yxINMVh(dANGorZhNcp, 1),
                 1, "Lua function expected");
  bIf_6NS_ = osy8gRm8(nl14(dANGorZhNcp, 1));
  while ((nqRl4nbsb4ute = EWk0l_aP(bIf_6NS_, ++Ug3WiOFRVtz, d2UwF29q1PF3g)) != qzdsHHKSA4)
    U5Uep4tkbF(dANGorZhNcp, nqRl4nbsb4ute);
  return Ug3WiOFRVtz-1;
}

/* }====================================================== */



static void zjYFrRX (oKhhn5 *dANGorZhNcp) {
  int Ug3WiOFRVtz;
  int sxS1yv0OWbd = Y4CW(dANGorZhNcp);
  wscxoCnE2("stack: >>\n");
  for (Ug3WiOFRVtz = 1; Ug3WiOFRVtz <= sxS1yv0OWbd; Ug3WiOFRVtz++) {
    wscxoCnE2("%3d: %s\n", Ug3WiOFRVtz, GSB5RUz(dANGorZhNcp, Ug3WiOFRVtz, qzdsHHKSA4));
    T8YUzJ0(dANGorZhNcp, 1);
  }
  wscxoCnE2("<<\n");
}


static int rVBksbg (oKhhn5 *dANGorZhNcp) {
  sIgWVtMR(dANGorZhNcp, 0, 6);
  AQAJmhrLOSJwa(dANGorZhNcp, "IS32INT", H6zFYfKabZgA);
  AQAJmhrLOSJwa(dANGorZhNcp, "MAXARG_Ax", YPT0T7jfIXx);
  AQAJmhrLOSJwa(dANGorZhNcp, "MAXARG_Bx", l2hoyF);
  AQAJmhrLOSJwa(dANGorZhNcp, "OFFSET_sBx", xhhIu_Gc9X);
  AQAJmhrLOSJwa(dANGorZhNcp, "LFPF", W1vr3aqIV8xb);
  AQAJmhrLOSJwa(dANGorZhNcp, "NUM_OPCODES", esrsPVQsJbZkb);
  return 1;
}


static int YHBj (oKhhn5 *dANGorZhNcp) {
  if (i6ps(dANGorZhNcp, 1)) {
    fkeYjCR(dANGorZhNcp, FEtY9Gx.ik3GsL);
    fkeYjCR(dANGorZhNcp, FEtY9Gx.fllG);
    fkeYjCR(dANGorZhNcp, FEtY9Gx.cRjM);
    return 3;
  }
  else if (Xrj9AK(dANGorZhNcp, 1)) {
    unsigned long WH07HSfUJ = gYyWgWC(unsigned long, CqTplNG4WIp(dANGorZhNcp, 1));
    if (WH07HSfUJ == 0) WH07HSfUJ = TQ0tjxy0q6Mom;
    FEtY9Gx.YyPROIqkrLe = WH07HSfUJ;
    return 0;
  }
  else {
    const char *HTm5wQ43ct = d5Sfbl4(dANGorZhNcp, 1);
    int Ug3WiOFRVtz;
    for (Ug3WiOFRVtz = qwxP3AlaW - 1; Ug3WiOFRVtz >= 0; Ug3WiOFRVtz--) {
      if (ZJzN(HTm5wQ43ct, bQaitc2M(Ug3WiOFRVtz)) == 0) {
        fkeYjCR(dANGorZhNcp, FEtY9Gx.IHK3wfbHIiJp[Ug3WiOFRVtz]);
        return 1;
      }
    }
    return CvLJPQOTY(dANGorZhNcp, "unknown type '%s'", HTm5wQ43ct);
  }
}


static int uU0lG8E6EfF9 (oKhhn5 *dANGorZhNcp) {
  if (i6ps(dANGorZhNcp, 1))
    FEtY9Gx.diN4o1kvJm = ~0L;
  else
    FEtY9Gx.diN4o1kvJm = CqTplNG4WIp(dANGorZhNcp, 1);
  return 0;
}


static int i0fea9wn3La (oKhhn5 *dANGorZhNcp) {
  Xo2bfLP4oZ6ct(dANGorZhNcp);
  FEtY9Gx.n2_mCqu0Ni7 = 1;
  return 0;
}


static int DOon (oKhhn5 *dANGorZhNcp) {
  if (d4f1TnRNSi(nl14(dANGorZhNcp, 1)))
    ZH98TRL = qzdsHHKSA4;
  else
    ZH98TRL = hiTZwvR(nl14(dANGorZhNcp, 1));
  return 0;
}


static int ZoVQ8Nx58 (oKhhn5 *dANGorZhNcp) {
  kxUFNdHfDo1yl *Gq1g5;
  ZEDnpQ5JyyhEG(dANGorZhNcp, 1);
  Gq1g5 = nl14(dANGorZhNcp, 1);
  if (!oGDpQT(Gq1g5))
    U5Uep4tkbF(dANGorZhNcp, "no collectable");
  else {
    e9bY73cQhQC *ADUx42QbqIy = hiTZwvR(Gq1g5);
    U5Uep4tkbF(dANGorZhNcp, RAe9(W9BtJO1VI745j(dANGorZhNcp), ADUx42QbqIy) ? "dead" :
                      sM2oiF(ADUx42QbqIy) ? "white" :
                      eFcp3enA(ADUx42QbqIy) ? "black" : "gray");
  }
  return 1;
}


static int ifi3yuc53 (oKhhn5 *dANGorZhNcp) {
  kxUFNdHfDo1yl *Gq1g5;
  ZEDnpQ5JyyhEG(dANGorZhNcp, 1);
  Gq1g5 = nl14(dANGorZhNcp, 1);
  if (!oGDpQT(Gq1g5))
    U5Uep4tkbF(dANGorZhNcp, "no collectable");
  else {
    static const char *Ai_H[] = {"new", "survival", "old0", "old1",
                                     "old", "touched1", "touched2"};
    e9bY73cQhQC *ADUx42QbqIy = hiTZwvR(Gq1g5);
    U5Uep4tkbF(dANGorZhNcp, Ai_H[yXbmdJRUV1wCz(ADUx42QbqIy)]);
  }
  return 1;
}


static int tmFwYe_13 (oKhhn5 *dANGorZhNcp) {
  kxUFNdHfDo1yl *Gq1g5;
  ZEDnpQ5JyyhEG(dANGorZhNcp, 1);
  Gq1g5 = nl14(dANGorZhNcp, 1);
  if (!oGDpQT(Gq1g5))
    wscxoCnE2("no collectable\n");
  else {
    e9bY73cQhQC *ADUx42QbqIy = hiTZwvR(Gq1g5);
    BG4lCGRl(W9BtJO1VI745j(dANGorZhNcp), ADUx42QbqIy);
    wscxoCnE2("\n");
  }
  return 0;
}


static int K15wWJih (oKhhn5 *dANGorZhNcp) {
  static const char *XNANiG[] = {
    "propagate", "atomic", "enteratomic", "sweepallgc", "sweepfinobj",
    "sweeptobefnz", "sweepend", "callfin", "pause", ""};
  static const int WQmxeIMQzb[] = {
    pVOLo4, ki1vdp2, rZ3GAKiSx, swFokh, FcIZ5D,
    ZBfp0vL, STGPLW, Cnq_B, qM7vt2Wh, -1};
  int wlc6OO = WQmxeIMQzb[UR0n(dANGorZhNcp, 1, "", XNANiG)];
  if (wlc6OO == -1) {
    U5Uep4tkbF(dANGorZhNcp, XNANiG[W9BtJO1VI745j(dANGorZhNcp)->YBvtpV]);
    return 1;
  }
  else {
    a1WmD *GxL2EpLSjV3 = W9BtJO1VI745j(dANGorZhNcp);
    if (W9BtJO1VI745j(dANGorZhNcp)->oFsU == SLwavq_L)
      CvLJPQOTY(dANGorZhNcp, "cannot change states in generational mode");
    OzVt2IX51dE(dANGorZhNcp);
    if (wlc6OO < GxL2EpLSjV3->YBvtpV) {  /* must cross 'pause'? */
      der2McpTg5b(dANGorZhNcp, ojsMvCuxyBxN(qM7vt2Wh));  /* run until pause */
    }
    der2McpTg5b(dANGorZhNcp, ojsMvCuxyBxN(wlc6OO));
    j8hck5(W9BtJO1VI745j(dANGorZhNcp)->YBvtpV == wlc6OO);
    j28agnKV1g(dANGorZhNcp);
    return 0;
  }
}


static int C4raFzdt9d0d (oKhhn5 *dANGorZhNcp) {
  if (i6ps(dANGorZhNcp, 2)) {
    UpR5K(dANGorZhNcp, GZtg(dANGorZhNcp, 1) == t5Z_5teTn7, 1, "string expected");
    fkeYjCR(dANGorZhNcp, EMooz3CohcV9(nl14(dANGorZhNcp, 1))->rIDqW81Vdk);
  }
  else {
    kxUFNdHfDo1yl *Gq1g5 = nl14(dANGorZhNcp, 1);
    vz35xTxsDS *HTm5wQ43ct;
    H6t5(dANGorZhNcp, 2, Hwij3Pu);
    HTm5wQ43ct = N75mV(nl14(dANGorZhNcp, 2));
    fkeYjCR(dANGorZhNcp, jB0hbnsEejiJ(HTm5wQ43ct, Gq1g5) - HTm5wQ43ct->DQbC);
  }
  return 1;
}


static int yS5icLA1 (oKhhn5 *dANGorZhNcp) {
  unsigned long o3IB6r3bqBpV = 0;
  fkeYjCR(dANGorZhNcp, (dANGorZhNcp->bP971Q5jVlY9.bIf_6NS_ - dANGorZhNcp->t1lfjaHcT.bIf_6NS_));
  fkeYjCR(dANGorZhNcp, S9mA5YYRQ(dANGorZhNcp));
  fkeYjCR(dANGorZhNcp, dANGorZhNcp->ihTA);
  fkeYjCR(dANGorZhNcp, dANGorZhNcp->pb0LWqKHuEw);
  fkeYjCR(dANGorZhNcp, (unsigned long)&o3IB6r3bqBpV);
  return 5;
}


static int sN9c7BYGZh3 (oKhhn5 *dANGorZhNcp) {
  const vz35xTxsDS *HTm5wQ43ct;
  int Ug3WiOFRVtz = DLI9dY50TrmnN(M8S6uvpldu3(dANGorZhNcp, 2, -1));
  unsigned int ifHCHP3F3be;
  H6t5(dANGorZhNcp, 1, Hwij3Pu);
  HTm5wQ43ct = N75mV(nl14(dANGorZhNcp, 1));
  ifHCHP3F3be = xYd8j2(HTm5wQ43ct);
  if (Ug3WiOFRVtz == -1) {
    fkeYjCR(dANGorZhNcp, ifHCHP3F3be);
    fkeYjCR(dANGorZhNcp, KhQfdru(HTm5wQ43ct));
    fkeYjCR(dANGorZhNcp, uwzbFMXwrgG(HTm5wQ43ct) ? 0 : HTm5wQ43ct->d8ejC8 - HTm5wQ43ct->DQbC);
    fkeYjCR(dANGorZhNcp, HTm5wQ43ct->ox0sZ9_Y);
    return 4;
  }
  else if ((unsigned int)Ug3WiOFRVtz < ifHCHP3F3be) {
    fkeYjCR(dANGorZhNcp, Ug3WiOFRVtz);
    qBXxgkSl(dANGorZhNcp, &HTm5wQ43ct->cx1DgEI[Ug3WiOFRVtz]);
    hzzpVGRb(dANGorZhNcp);
  }
  else if ((Ug3WiOFRVtz -= ifHCHP3F3be) < MVMJfUUhKf(HTm5wQ43ct)) {
    kxUFNdHfDo1yl F6fLjE;
    RCXkcm(dANGorZhNcp, &F6fLjE, HwmLE(HTm5wQ43ct, Ug3WiOFRVtz));
    if (!xPUTzhdd_y(l6Ump1suvf(HwmLE(HTm5wQ43ct, Ug3WiOFRVtz))) ||
        d4f1TnRNSi(&F6fLjE) ||
        Z3Nel3uheE9Rk(&F6fLjE)) {
      qBXxgkSl(dANGorZhNcp, &F6fLjE);
    }
    else
      xfyEE1L(dANGorZhNcp, "<undef>");
    qBXxgkSl(dANGorZhNcp, l6Ump1suvf(HwmLE(HTm5wQ43ct, Ug3WiOFRVtz)));
    if (AUKomBvUc83Zz(&HTm5wQ43ct->DQbC[Ug3WiOFRVtz]) != 0)
      fkeYjCR(dANGorZhNcp, AUKomBvUc83Zz(&HTm5wQ43ct->DQbC[Ug3WiOFRVtz]));
    else
      hzzpVGRb(dANGorZhNcp);
  }
  return 3;
}


static int oldCB (oKhhn5 *dANGorZhNcp) {
  gC7mOHnW *vqYAi = &W9BtJO1VI745j(dANGorZhNcp)->Ds7zDzx;
  int QMtlR = DLI9dY50TrmnN(M8S6uvpldu3(dANGorZhNcp, 1, 0)) - 1;
  if (QMtlR == -1) {
    fkeYjCR(dANGorZhNcp ,vqYAi->Zx4tsBq);
    fkeYjCR(dANGorZhNcp ,vqYAi->Em4S1Qc);
    return 2;
  }
  else if (QMtlR < vqYAi->Zx4tsBq) {
    HI3_l_KXV *ZKyAzoYB1O;
    int sxS1yv0OWbd = 0;
    for (ZKyAzoYB1O = vqYAi->rIDqW81Vdk[QMtlR]; ZKyAzoYB1O != qzdsHHKSA4; ZKyAzoYB1O = ZKyAzoYB1O->emra.XyZ_L6UZ) {
      EctI(dANGorZhNcp, dANGorZhNcp->bP971Q5jVlY9.bIf_6NS_, ZKyAzoYB1O);
      ml7Sru(dANGorZhNcp);
      sxS1yv0OWbd++;
    }
    return sxS1yv0OWbd;
  }
  else return 0;
}


static int s5YYh1HoxbH (oKhhn5 *dANGorZhNcp) {
  int QKXQ_ = Y4CW(dANGorZhNcp);
  ZEDnpQ5JyyhEG(dANGorZhNcp, 1);
  O3Od0iAjO4D(dANGorZhNcp, 1);
  fkeYjCR(dANGorZhNcp, W7C2tU(dANGorZhNcp, c8t9P08OG));
  nUwjhF(QKXQ_);  /* to avoid warnings */
  j8hck5(Y4CW(dANGorZhNcp) == QKXQ_+1);  /* +1 for result */
  return 1;
}

static int w2xdM9A_r (oKhhn5 *dANGorZhNcp) {
  int QKXQ_ = Y4CW(dANGorZhNcp);
  XNNamWH8w(dANGorZhNcp, c8t9P08OG, CqTplNG4WIp(dANGorZhNcp, 1));
  nUwjhF(QKXQ_);  /* to avoid warnings */
  j8hck5(Y4CW(dANGorZhNcp) == QKXQ_+1);
  return 1;
}

static int vHrYLv (oKhhn5 *dANGorZhNcp) {
  int QKXQ_ = Y4CW(dANGorZhNcp);
  knhXvjlB(dANGorZhNcp, c8t9P08OG, DLI9dY50TrmnN(CqTplNG4WIp(dANGorZhNcp, 1)));
  nUwjhF(QKXQ_);  /* to avoid warnings */
  j8hck5(Y4CW(dANGorZhNcp) == QKXQ_);
  return 0;
}


static int aBVw (oKhhn5 *dANGorZhNcp) {
  int sxS1yv0OWbd = DLI9dY50TrmnN(CqTplNG4WIp(dANGorZhNcp, 2));
  H6t5(dANGorZhNcp, 1, mRj0bvShMDxx);
  if (i6ps(dANGorZhNcp, 3)) {
    const char *nqRl4nbsb4ute = Sl_31k(dANGorZhNcp, 1, sxS1yv0OWbd);
    if (nqRl4nbsb4ute == qzdsHHKSA4) return 0;
    U5Uep4tkbF(dANGorZhNcp, nqRl4nbsb4ute);
    return 2;
  }
  else {
    const char *nqRl4nbsb4ute = sYSw(dANGorZhNcp, 1, sxS1yv0OWbd);
    U5Uep4tkbF(dANGorZhNcp, nqRl4nbsb4ute);
    return 1;
  }
}


static int T6ziaIm (oKhhn5 *dANGorZhNcp) {
  PIP7A Zx4tsBq = s2hj(M8S6uvpldu3(dANGorZhNcp, 1, 0));
  int Coa_CmYuCE0 = M8S6uvpldu3(dANGorZhNcp, 2, 0);
  char *bIf_6NS_ = XMXG2v(Wvy1Z(dANGorZhNcp, Zx4tsBq, Coa_CmYuCE0));
  while (Zx4tsBq--) *bIf_6NS_++ = '\0';
  return 1;
}


static int kqQH5y1n2o (oKhhn5 *dANGorZhNcp) {
  kiaG emra = CqTplNG4WIp(dANGorZhNcp, 1);
  Pq3D7dfNW72(dANGorZhNcp, Kmg0LKybFNq(s2hj(emra)));
  return 1;
}


static int CWuAj (oKhhn5 *dANGorZhNcp) {
  fkeYjCR(dANGorZhNcp, gYyWgWC(long, az06UweO0(dANGorZhNcp, 1)));
  return 1;
}


static int nwYiX (oKhhn5 *dANGorZhNcp) {
  oKhhn5 *F1cW6 = HlyYg8YUINaP(dANGorZhNcp);
  PIP7A VE6iJGqjdzk;
  const char *QMtlR = rmTFnw8A9_(dANGorZhNcp, 1, &VE6iJGqjdzk);
  int IXouX3 = V6jxcf7(F1cW6, QMtlR, VE6iJGqjdzk, QMtlR);
  if (IXouX3 == BTxEj2O71oh)
    IXouX3 = CjwwiqgP5(F1cW6, 0, 0, 0);
  fkeYjCR(dANGorZhNcp, IXouX3);
  return 1;
}


static int MwMKvvIDsMlo (oKhhn5 *dANGorZhNcp) {
  eL39Q(dANGorZhNcp, TrkrjuwSJ6w(*gYyWgWC(const double *, d5Sfbl4(dANGorZhNcp, 1))));
  return 1;
}


static int PD22M1t (oKhhn5 *dANGorZhNcp) {
  double pdqL = gYyWgWC(double, CfHT(dANGorZhNcp, 1));
  QdBl(dANGorZhNcp, XMXG2v(&pdqL), sizeof(pdqL));
  return 1;
}


static int xupq (oKhhn5 *dANGorZhNcp) {
  fkeYjCR(dANGorZhNcp, wpJYTRWrR7A1(dANGorZhNcp, 1));
  return 1;
}


static int tMoGIYC (oKhhn5 *dANGorZhNcp) {
  void *fNsyd7Ax;
  yxbPox Yv4Is = YdQIT(dANGorZhNcp, &fNsyd7Ax);
  oKhhn5 *F1cW6 = SrPTx0zm09(Yv4Is, fNsyd7Ax);
  if (F1cW6) {
    GBr1Ka6(F1cW6, aWIvuRrCLcXIt);
    Pq3D7dfNW72(dANGorZhNcp, F1cW6);
  }
  else
    hzzpVGRb(dANGorZhNcp);
  return 1;
}


static oKhhn5 *P5A9 (oKhhn5 *dANGorZhNcp) {
  oKhhn5 *F1cW6 = gYyWgWC(oKhhn5 *, az06UweO0(dANGorZhNcp, 1));
  UpR5K(dANGorZhNcp, F1cW6 != qzdsHHKSA4, 1, "state expected");
  return F1cW6;
}


static int MhuWYv7 (oKhhn5 *dANGorZhNcp) {
  static const a_YFt yNW7iKC7axv[] = {
    {U7_TxJVAq, dTvon_Pe3C},
    {"coroutine", ee9IPhUe},
    {"debug", jDjYG8K},
    {"io", MKnGUfF2},
    {"os", gRGDh},
    {"math", Y0GlDJAB},
    {"string", Gugm2nx},
    {"table", oEzC6RsbE},
    {"T", ll51kfVZS0oS},
    {qzdsHHKSA4, qzdsHHKSA4}
  };
  oKhhn5 *F1cW6 = P5A9(dANGorZhNcp);
  int Ug3WiOFRVtz;
  oo3NUkkQkZLdi(F1cW6, "package", bYBeD4mUPKPY, 0);
  j8hck5(GZtg(F1cW6, -1) == Hwij3Pu);
  /* 'requiref' should not reload module already loaded... */
  oo3NUkkQkZLdi(F1cW6, "package", qzdsHHKSA4, 1);  /* seg. fault if it reloads */
  /* ...but should return the same module */
  j8hck5(lBpGDN(F1cW6, -1, -2, jj5v2fMXn5o));
  i3r_mH(F1cW6, c8t9P08OG, ohwLfE);
  for (Ug3WiOFRVtz = 0; yNW7iKC7axv[Ug3WiOFRVtz].nqRl4nbsb4ute; Ug3WiOFRVtz++) {
    tdVtLm(F1cW6, yNW7iKC7axv[Ug3WiOFRVtz].qiUEcxF2uu);
    LlBlEdffFES(F1cW6, -2, yNW7iKC7axv[Ug3WiOFRVtz].nqRl4nbsb4ute);
  }
  return 0;
}

static int n_D1NbA (oKhhn5 *dANGorZhNcp) {
  oKhhn5 *F1cW6 = P5A9(dANGorZhNcp);
  AX7btavzNB(F1cW6);
  return 0;
}

static int Ht4mU3QXYb9 (oKhhn5 *dANGorZhNcp) {
  oKhhn5 *F1cW6 = P5A9(dANGorZhNcp);
  PIP7A iXJe_YR3Nf;
  const char *iiK0a58EC = rmTFnw8A9_(dANGorZhNcp, 2, &iXJe_YR3Nf);
  int IXouX3;
  GFXKNf4xgcLMH(F1cW6, 0);
  IXouX3 = V6jxcf7(F1cW6, iiK0a58EC, iXJe_YR3Nf, iiK0a58EC);
  if (IXouX3 == BTxEj2O71oh)
    IXouX3 = CjwwiqgP5(F1cW6, 0, s9EHMsc1fJ, 0);
  if (IXouX3 != BTxEj2O71oh) {
    hzzpVGRb(dANGorZhNcp);
    U5Uep4tkbF(dANGorZhNcp, aCBxOp(F1cW6, -1));
    fkeYjCR(dANGorZhNcp, IXouX3);
    return 3;
  }
  else {
    int Ug3WiOFRVtz = 0;
    while (!i6ps(F1cW6, ++Ug3WiOFRVtz))
      U5Uep4tkbF(dANGorZhNcp, aCBxOp(F1cW6, Ug3WiOFRVtz));
    T8YUzJ0(F1cW6, Ug3WiOFRVtz-1);
    return Ug3WiOFRVtz-1;
  }
}


static int a4CRoDYj (oKhhn5 *dANGorZhNcp) {
  unsigned int KZ4NvuQ5dz2 = (unsigned int)CqTplNG4WIp(dANGorZhNcp, 1);
  fkeYjCR(dANGorZhNcp, b6qJT(KZ4NvuQ5dz2));
  return 1;
}


struct We5qQqnlB { JNLxuUHGP wXtuEPj3; const char *Vp2WXu_VVYW; oKhhn5 *dANGorZhNcp; };

/*
** does a long-jump back to "main program".
*/
static int UN1ntiEtWRO (oKhhn5 *dANGorZhNcp) {
  struct We5qQqnlB *Qxjv9GmlqX;
  ugRf5ZGFK9yfs(dANGorZhNcp, 1);  /* open space for 'Aux' struct */
  Wb8qAi(dANGorZhNcp, c8t9P08OG, "_jmpbuf");  /* get 'Aux' struct */
  Qxjv9GmlqX = (struct We5qQqnlB *)az06UweO0(dANGorZhNcp, -1);
  T8YUzJ0(dANGorZhNcp, 1);  /* remove 'Aux' struct */
  aFoNWlK08(Qxjv9GmlqX->dANGorZhNcp, dANGorZhNcp, Qxjv9GmlqX->Vp2WXu_VVYW);  /* run optional panic code */
  hZ5RTV5lqs4(Qxjv9GmlqX->wXtuEPj3, 1);
  return 1;  /* to avoid warnings */
}

static int XKwk1X6 (oKhhn5 *dANGorZhNcp) {
  struct We5qQqnlB Qxjv9GmlqX;
  void *fNsyd7Ax;
  oKhhn5 *F1cW6;
  const char *iiK0a58EC = d5Sfbl4(dANGorZhNcp, 1);
  yxbPox Yv4Is = YdQIT(dANGorZhNcp, &fNsyd7Ax);
  Qxjv9GmlqX.Vp2WXu_VVYW = XTTiD(dANGorZhNcp, 2, "");
  Qxjv9GmlqX.dANGorZhNcp = dANGorZhNcp;
  F1cW6 = SrPTx0zm09(Yv4Is, fNsyd7Ax);  /* create new state */
  if (F1cW6 == qzdsHHKSA4) {  /* error? */
    hzzpVGRb(dANGorZhNcp);
    return 1;
  }
  GBr1Ka6(F1cW6, UN1ntiEtWRO);  /* set its panic function */
  Pq3D7dfNW72(F1cW6, &Qxjv9GmlqX);
  LlBlEdffFES(F1cW6, c8t9P08OG, "_jmpbuf");  /* store 'Aux' struct */
  if (whm9z2W7xS4P7(Qxjv9GmlqX.wXtuEPj3) == 0) {  /* set jump buffer */
    aFoNWlK08(dANGorZhNcp, F1cW6, iiK0a58EC);  /* run code unprotected */
    xfyEE1L(dANGorZhNcp, "no errors");
  }
  else {  /* error handling */
    /* move error message to original state */
    U5Uep4tkbF(dANGorZhNcp, aCBxOp(F1cW6, -1));
  }
  AX7btavzNB(F1cW6);
  return 1;
}



/*
** {====================================================================
** function to test the API with C. It interprets a kind of assembler
** language with calls to the API, so the test can be driven by Lua code
** =====================================================================
*/


static void ly_Q (oKhhn5 *dANGorZhNcp, int MgvjavXq, int FG5BSdPLq, const char *iiK0a58EC);

static const char *const FFUBIZxWbn = " \t\n,;";

static void IL9cwtI5e3Ph (const char **d2UwF29q1PF3g) {
  for (;;) {
    if (**d2UwF29q1PF3g != '\0' && nxzqp_k(FFUBIZxWbn, **d2UwF29q1PF3g)) (*d2UwF29q1PF3g)++;
    else if (**d2UwF29q1PF3g == '#') {  /* comment? */
      while (**d2UwF29q1PF3g != '\n' && **d2UwF29q1PF3g != '\0') (*d2UwF29q1PF3g)++;  /* until end-of-line */
    }
    else break;
  }
}

static int CEBoQYRf2Z (oKhhn5 *dANGorZhNcp, oKhhn5 *F1cW6, const char **d2UwF29q1PF3g) {
  int ehgeKY = 0;
  int lLbAW1bFLefLo = 1;
  IL9cwtI5e3Ph(d2UwF29q1PF3g);
  if (**d2UwF29q1PF3g == '.') {
    ehgeKY = DLI9dY50TrmnN(wpJYTRWrR7A1(F1cW6, -1));
    T8YUzJ0(F1cW6, 1);
    (*d2UwF29q1PF3g)++;
    return ehgeKY;
  }
  else if (**d2UwF29q1PF3g == '*') {
    ehgeKY = Y4CW(F1cW6);
    (*d2UwF29q1PF3g)++;
    return ehgeKY;
  }
  else if (**d2UwF29q1PF3g == '-') {
    lLbAW1bFLefLo = -1;
    (*d2UwF29q1PF3g)++;
  }
  if (!qBJ79Idor(ZAnGC0R(**d2UwF29q1PF3g)))
    CvLJPQOTY(dANGorZhNcp, "number expected (%s)", *d2UwF29q1PF3g);
  while (qBJ79Idor(ZAnGC0R(**d2UwF29q1PF3g))) ehgeKY = ehgeKY*10 + (*(*d2UwF29q1PF3g)++) - '0';
  return lLbAW1bFLefLo*ehgeKY;
}

static const char *s83Y29Y88ZJ1 (oKhhn5 *dANGorZhNcp, char *Khh7WZvdP, const char **d2UwF29q1PF3g) {
  int Ug3WiOFRVtz = 0;
  IL9cwtI5e3Ph(d2UwF29q1PF3g);
  if (**d2UwF29q1PF3g == '"' || **d2UwF29q1PF3g == '\'') {  /* quoted string? */
    int LYNerK = *(*d2UwF29q1PF3g)++;
    while (**d2UwF29q1PF3g != LYNerK) {
      if (**d2UwF29q1PF3g == '\0') CvLJPQOTY(dANGorZhNcp, "unfinished string in C script");
      Khh7WZvdP[Ug3WiOFRVtz++] = *(*d2UwF29q1PF3g)++;
    }
    (*d2UwF29q1PF3g)++;
  }
  else {
    while (**d2UwF29q1PF3g != '\0' && !nxzqp_k(FFUBIZxWbn, **d2UwF29q1PF3g))
      Khh7WZvdP[Ug3WiOFRVtz++] = *(*d2UwF29q1PF3g)++;
  }
  Khh7WZvdP[Ug3WiOFRVtz] = '\0';
  return Khh7WZvdP;
}


static int De8ihsESk_m (oKhhn5 *dANGorZhNcp, oKhhn5 *F1cW6, const char **d2UwF29q1PF3g) {
  IL9cwtI5e3Ph(d2UwF29q1PF3g);
  switch (*(*d2UwF29q1PF3g)++) {
    case 'R': return c8t9P08OG;
    case 'G': return CvLJPQOTY(dANGorZhNcp, "deprecated index 'G'");
    case 'U': return hsmk(CEBoQYRf2Z(dANGorZhNcp, F1cW6, d2UwF29q1PF3g));
    default: (*d2UwF29q1PF3g)--; return CEBoQYRf2Z(dANGorZhNcp, F1cW6, d2UwF29q1PF3g);
  }
}


static const char *const AkjwlxAk[] = {"OK", "YIELD", "ERRRUN",
    "ERRSYNTAX", vn4z0CgZDVn6, "ERRGCMM", "ERRERR"};

/*
** Avoid these stat codes from being collected, to avoid possible
** memory error when pushing them.
*/
static void w33nvqYAgh (oKhhn5 *dANGorZhNcp) {
  unsigned int Ug3WiOFRVtz;
  for (Ug3WiOFRVtz = 0; Ug3WiOFRVtz < sizeof(AkjwlxAk) / sizeof(AkjwlxAk[0]); Ug3WiOFRVtz++) {
    F98T3WTV(dANGorZhNcp, 1);
    LlBlEdffFES(dANGorZhNcp, c8t9P08OG, AkjwlxAk[Ug3WiOFRVtz]);
  }
}


#define ggA55(P9gjLrnk)	(ZJzN(P9gjLrnk, T6Vnf1Wk2EkV) == 0)

#define GETerOgvHggO		(CEBoQYRf2Z(dANGorZhNcp, F1cW6, &d2UwF29q1PF3g))
#define MAlmvNSz	(s83Y29Y88ZJ1(dANGorZhNcp, Khh7WZvdP, &d2UwF29q1PF3g))
#define QX4dvVwhSj2gU	(De8ihsESk_m(dANGorZhNcp, F1cW6, &d2UwF29q1PF3g))


static int lCWMpBgOFB8fT (oKhhn5 *dANGorZhNcp);
static int eiKI (oKhhn5 *dANGorZhNcp, int IXouX3, SG4v1b_o wOgoX69R);

/*
** arithmetic operation encoding for 'arith' instruction
** LUA_OPIDIV  -> \
** LUA_OPSHL   -> <
** LUA_OPSHR   -> >
** LUA_OPUNM   -> _
** LUA_OPBNOT  -> !
*/
static const char FBpRWOyy[] = "+-*%^/\\&|~<>_!";

static int aFoNWlK08 (oKhhn5 *dANGorZhNcp, oKhhn5 *F1cW6, const char *d2UwF29q1PF3g) {
  char Khh7WZvdP[300];
  int IXouX3 = 0;
  if (d2UwF29q1PF3g == qzdsHHKSA4) return CvLJPQOTY(dANGorZhNcp, "attempt to runC null script");
  for (;;) {
    const char *T6Vnf1Wk2EkV = MAlmvNSz;
    if ggA55("") return 0;
    else if ggA55("absindex") {
      eL39Q(F1cW6, pf2l7a_peNqO(F1cW6, QX4dvVwhSj2gU));
    }
    else if ggA55("append") {
      int HTm5wQ43ct = QX4dvVwhSj2gU;
      int Ug3WiOFRVtz = ythfaU6r(F1cW6, HTm5wQ43ct);
      I8a7Jpvli7Xxl(F1cW6, HTm5wQ43ct, Ug3WiOFRVtz + 1);
    }
    else if ggA55("arith") {
      int o4W4ei9xN;
      IL9cwtI5e3Ph(&d2UwF29q1PF3g);
      o4W4ei9xN = nxzqp_k(FBpRWOyy, *d2UwF29q1PF3g++) - FBpRWOyy;
      G2EMP44zJ6J(F1cW6, o4W4ei9xN);
    }
    else if ggA55("call") {
      int aXgOA = GETerOgvHggO;
      int ahQIc0zYOe = GETerOgvHggO;
      MIl0z4w(F1cW6, aXgOA, ahQIc0zYOe);
    }
    else if ggA55("callk") {
      int aXgOA = GETerOgvHggO;
      int ahQIc0zYOe = GETerOgvHggO;
      int Ug3WiOFRVtz = QX4dvVwhSj2gU;
      yBayc4whgnRl(F1cW6, aXgOA, ahQIc0zYOe, Ug3WiOFRVtz, eiKI);
    }
    else if ggA55("checkstack") {
      int KLmdURBX = GETerOgvHggO;
      const char *qpnIOpMLY = MAlmvNSz;
      if (*qpnIOpMLY == '\0')
        qpnIOpMLY = qzdsHHKSA4;  /* to test 'luaL_checkstack' with no message */
      gi1pjOw2(F1cW6, KLmdURBX, qpnIOpMLY);
    }
    else if ggA55("rawcheckstack") {
      int KLmdURBX = GETerOgvHggO;
      F98T3WTV(F1cW6, ugRf5ZGFK9yfs(F1cW6, KLmdURBX));
    }
    else if ggA55("compare") {
      const char *vF9TehPf = MAlmvNSz;  /* EQ, LT, or LE */
      int o4W4ei9xN = (vF9TehPf[0] == 'E') ? jj5v2fMXn5o
                               : (vF9TehPf[1] == 'T') ? FHSLz8kC6 : khR5ZQP;
      int o3IB6r3bqBpV = QX4dvVwhSj2gU;
      int Qxjv9GmlqX = QX4dvVwhSj2gU;
      F98T3WTV(F1cW6, lBpGDN(F1cW6, o3IB6r3bqBpV, Qxjv9GmlqX, o4W4ei9xN));
    }
    else if ggA55("concat") {
      Xk_jQwcX(F1cW6, GETerOgvHggO);
    }
    else if ggA55("copy") {
      int Yv4Is = QX4dvVwhSj2gU;
      RoYNSFpi8C(F1cW6, Yv4Is, QX4dvVwhSj2gU);
    }
    else if ggA55("func2num") {
      hta2nOLAW qiUEcxF2uu = lo3iM(F1cW6, QX4dvVwhSj2gU);
      eL39Q(F1cW6, s2hj(qiUEcxF2uu));
    }
    else if ggA55("getfield") {
      int HTm5wQ43ct = QX4dvVwhSj2gU;
      Wb8qAi(F1cW6, HTm5wQ43ct, MAlmvNSz);
    }
    else if ggA55("getglobal") {
      eV75(F1cW6, MAlmvNSz);
    }
    else if ggA55("getmetatable") {
      if (v18pmLI017(F1cW6, QX4dvVwhSj2gU) == 0)
        hzzpVGRb(F1cW6);
    }
    else if ggA55("gettable") {
      xQwm5aJw(F1cW6, QX4dvVwhSj2gU);
    }
    else if ggA55("gettop") {
      fkeYjCR(F1cW6, Y4CW(F1cW6));
    }
    else if ggA55("gsub") {
      int o3IB6r3bqBpV = GETerOgvHggO; int Qxjv9GmlqX = GETerOgvHggO; int KuDPjJa = GETerOgvHggO;
      ibomk5OJUX(F1cW6, aCBxOp(F1cW6, o3IB6r3bqBpV),
                    aCBxOp(F1cW6, Qxjv9GmlqX),
                    aCBxOp(F1cW6, KuDPjJa));
    }
    else if ggA55("insert") {
      B3IfvcbxdJkc(F1cW6, GETerOgvHggO);
    }
    else if ggA55("iscfunction") {
      F98T3WTV(F1cW6, yxINMVh(F1cW6, QX4dvVwhSj2gU));
    }
    else if ggA55("isfunction") {
      F98T3WTV(F1cW6, BwxBNWt(F1cW6, QX4dvVwhSj2gU));
    }
    else if ggA55("isnil") {
      F98T3WTV(F1cW6, LwhE9sZ17(F1cW6, QX4dvVwhSj2gU));
    }
    else if ggA55("isnull") {
      F98T3WTV(F1cW6, i6ps(F1cW6, QX4dvVwhSj2gU));
    }
    else if ggA55("isnumber") {
      F98T3WTV(F1cW6, Xrj9AK(F1cW6, QX4dvVwhSj2gU));
    }
    else if ggA55("isstring") {
      F98T3WTV(F1cW6, FVpZBFwW2At(F1cW6, QX4dvVwhSj2gU));
    }
    else if ggA55("istable") {
      F98T3WTV(F1cW6, VeXCb4iI(F1cW6, QX4dvVwhSj2gU));
    }
    else if ggA55("isudataval") {
      F98T3WTV(F1cW6, sdlHwmUl8rMqn(F1cW6, QX4dvVwhSj2gU));
    }
    else if ggA55("isuserdata") {
      F98T3WTV(F1cW6, Ndo0(F1cW6, QX4dvVwhSj2gU));
    }
    else if ggA55("len") {
      RUTyrk(F1cW6, QX4dvVwhSj2gU);
    }
    else if ggA55("Llen") {
      fkeYjCR(F1cW6, eIt1O(F1cW6, QX4dvVwhSj2gU));
    }
    else if ggA55("loadfile") {
      JONCBeYdu(F1cW6, d5Sfbl4(F1cW6, GETerOgvHggO));
    }
    else if ggA55("loadstring") {
      const char *QMtlR = d5Sfbl4(F1cW6, GETerOgvHggO);
      yx4dFAyN(F1cW6, QMtlR);
    }
    else if ggA55("newmetatable") {
      F98T3WTV(F1cW6, OFIfxIq3usT(F1cW6, MAlmvNSz));
    }
    else if ggA55("newtable") {
      M82y(F1cW6);
    }
    else if ggA55("newthread") {
      HlyYg8YUINaP(F1cW6);
    }
    else if ggA55("resetthread") {
      fkeYjCR(F1cW6, Kwo8ynqCF(F1cW6));  /* deprecated */
    }
    else if ggA55("newuserdata") {
      RTlOaTz7qjSYI(F1cW6, GETerOgvHggO);
    }
    else if ggA55("next") {
      p084(F1cW6, -2);
    }
    else if ggA55("objsize") {
      fkeYjCR(F1cW6, ythfaU6r(F1cW6, QX4dvVwhSj2gU));
    }
    else if ggA55("pcall") {
      int aXgOA = GETerOgvHggO;
      int ahQIc0zYOe = GETerOgvHggO;
      IXouX3 = CjwwiqgP5(F1cW6, aXgOA, ahQIc0zYOe, GETerOgvHggO);
    }
    else if ggA55("pcallk") {
      int aXgOA = GETerOgvHggO;
      int ahQIc0zYOe = GETerOgvHggO;
      int Ug3WiOFRVtz = QX4dvVwhSj2gU;
      IXouX3 = WOTOW(F1cW6, aXgOA, ahQIc0zYOe, 0, Ug3WiOFRVtz, eiKI);
    }
    else if ggA55("pop") {
      T8YUzJ0(F1cW6, GETerOgvHggO);
    }
    else if ggA55("printstack") {
      int sxS1yv0OWbd = GETerOgvHggO;
      if (sxS1yv0OWbd != 0) {
        wscxoCnE2("%s\n", GSB5RUz(F1cW6, sxS1yv0OWbd, qzdsHHKSA4));
        T8YUzJ0(F1cW6, 1);
      }
      else zjYFrRX(F1cW6);
    }
    else if ggA55("print") {
      const char *qpnIOpMLY = MAlmvNSz;
      wscxoCnE2("%s\n", qpnIOpMLY);
    }
    else if ggA55("warningC") {
      const char *qpnIOpMLY = MAlmvNSz;
      bcFgexjt(F1cW6, qpnIOpMLY, 1);
    }
    else if ggA55("warning") {
      const char *qpnIOpMLY = MAlmvNSz;
      bcFgexjt(F1cW6, qpnIOpMLY, 0);
    }
    else if ggA55("pushbool") {
      F98T3WTV(F1cW6, GETerOgvHggO);
    }
    else if ggA55("pushcclosure") {
      tBGSb(F1cW6, lCWMpBgOFB8fT, GETerOgvHggO);
    }
    else if ggA55("pushint") {
      fkeYjCR(F1cW6, GETerOgvHggO);
    }
    else if ggA55("pushnil") {
      hzzpVGRb(F1cW6);
    }
    else if ggA55("pushnum") {
      eL39Q(F1cW6, (kxjgPWxy)GETerOgvHggO);
    }
    else if ggA55("pushstatus") {
      U5Uep4tkbF(F1cW6, AkjwlxAk[IXouX3]);
    }
    else if ggA55("pushstring") {
      U5Uep4tkbF(F1cW6, MAlmvNSz);
    }
    else if ggA55("pushupvalueindex") {
      fkeYjCR(F1cW6, hsmk(GETerOgvHggO));
    }
    else if ggA55("pushvalue") {
      O3Od0iAjO4D(F1cW6, QX4dvVwhSj2gU);
    }
    else if ggA55("pushfstringI") {
      bV5S4_(F1cW6, aCBxOp(dANGorZhNcp, -2), (int)wpJYTRWrR7A1(dANGorZhNcp, -1));
    }
    else if ggA55("pushfstringS") {
      bV5S4_(F1cW6, aCBxOp(dANGorZhNcp, -2), aCBxOp(dANGorZhNcp, -1));
    }
    else if ggA55("pushfstringP") {
      bV5S4_(F1cW6, aCBxOp(dANGorZhNcp, -2), s_upvK2G44_(dANGorZhNcp, -1));
    }
    else if ggA55("rawget") {
      int HTm5wQ43ct = QX4dvVwhSj2gU;
      l8AuOw8irc(F1cW6, HTm5wQ43ct);
    }
    else if ggA55("rawgeti") {
      int HTm5wQ43ct = QX4dvVwhSj2gU;
      XNNamWH8w(F1cW6, HTm5wQ43ct, GETerOgvHggO);
    }
    else if ggA55("rawgetp") {
      int HTm5wQ43ct = QX4dvVwhSj2gU;
      K78f0(F1cW6, HTm5wQ43ct, Kmg0LKybFNq(s2hj(GETerOgvHggO)));
    }
    else if ggA55("rawset") {
      int HTm5wQ43ct = QX4dvVwhSj2gU;
      cy1hzUj(F1cW6, HTm5wQ43ct);
    }
    else if ggA55("rawseti") {
      int HTm5wQ43ct = QX4dvVwhSj2gU;
      I8a7Jpvli7Xxl(F1cW6, HTm5wQ43ct, GETerOgvHggO);
    }
    else if ggA55("rawsetp") {
      int HTm5wQ43ct = QX4dvVwhSj2gU;
      jSfjt_ZuxZ(F1cW6, HTm5wQ43ct, Kmg0LKybFNq(s2hj(GETerOgvHggO)));
    }
    else if ggA55("remove") {
      M28C6W(F1cW6, GETerOgvHggO);
    }
    else if ggA55("replace") {
      xOvDPmYZieynx(F1cW6, QX4dvVwhSj2gU);
    }
    else if ggA55("resume") {
      int Ug3WiOFRVtz = QX4dvVwhSj2gU;
      int ahQIc0zYOe;
      IXouX3 = sop_qb7u(bIDUiz2AQ(F1cW6, Ug3WiOFRVtz), dANGorZhNcp, GETerOgvHggO, &ahQIc0zYOe);
    }
    else if ggA55("traceback") {
      const char *qpnIOpMLY = MAlmvNSz;
      int QKXQ_ = GETerOgvHggO;
      knRh(F1cW6, F1cW6, qpnIOpMLY, QKXQ_);
    }
    else if ggA55("return") {
      int sxS1yv0OWbd = GETerOgvHggO;
      if (F1cW6 != dANGorZhNcp) {
        int Ug3WiOFRVtz;
        for (Ug3WiOFRVtz = 0; Ug3WiOFRVtz < sxS1yv0OWbd; Ug3WiOFRVtz++) {
          int D2kfSzUk65IK = -(sxS1yv0OWbd - Ug3WiOFRVtz);
          switch (GZtg(F1cW6, D2kfSzUk65IK)) {
            case oKP1lYwi:
              F98T3WTV(dANGorZhNcp, HpPj68yPUp9(F1cW6, D2kfSzUk65IK));
              break;
            default:
              U5Uep4tkbF(dANGorZhNcp, aCBxOp(F1cW6, D2kfSzUk65IK));
              break;
          }
        }
      }
      return sxS1yv0OWbd;
    }
    else if ggA55("rotate") {
      int Ug3WiOFRVtz = QX4dvVwhSj2gU;
      pw2ZOiayf6k(F1cW6, Ug3WiOFRVtz, GETerOgvHggO);
    }
    else if ggA55("setfield") {
      int HTm5wQ43ct = QX4dvVwhSj2gU;
      const char *QMtlR = MAlmvNSz;
      LlBlEdffFES(F1cW6, HTm5wQ43ct, QMtlR);
    }
    else if ggA55("seti") {
      int HTm5wQ43ct = QX4dvVwhSj2gU;
      NyM_3U7QFD_L(F1cW6, HTm5wQ43ct, GETerOgvHggO);
    }
    else if ggA55("setglobal") {
      const char *QMtlR = MAlmvNSz;
      QZ_KqhQywuF(F1cW6, QMtlR);
    }
    else if ggA55("sethook") {
      int MgvjavXq = GETerOgvHggO;
      int FG5BSdPLq = GETerOgvHggO;
      const char *QMtlR = MAlmvNSz;
      ly_Q(F1cW6, MgvjavXq, FG5BSdPLq, QMtlR);
    }
    else if ggA55("setmetatable") {
      int D2kfSzUk65IK = QX4dvVwhSj2gU;
      iU6TfAIzLg3n(F1cW6, D2kfSzUk65IK);
    }
    else if ggA55("settable") {
      LzfF_J(F1cW6, QX4dvVwhSj2gU);
    }
    else if ggA55("settop") {
      GFXKNf4xgcLMH(F1cW6, GETerOgvHggO);
    }
    else if ggA55("testudata") {
      int Ug3WiOFRVtz = QX4dvVwhSj2gU;
      F98T3WTV(F1cW6, MEx20VMPd(F1cW6, Ug3WiOFRVtz, MAlmvNSz) != qzdsHHKSA4);
    }
    else if ggA55("error") {
      CaxDl(F1cW6);
    }
    else if ggA55("abort") {
      kmIi();
    }
    else if ggA55("throw") {
#if GAVf_Rlr(DgEZ)
static struct Kc55UcjV { int KZ4NvuQ5dz2; } KZ4NvuQ5dz2;
      XdPdB7ak6zu99 KZ4NvuQ5dz2;
#else
      CvLJPQOTY(F1cW6, "C++");
#endif
      break;
    }
    else if ggA55("tobool") {
      F98T3WTV(F1cW6, HpPj68yPUp9(F1cW6, QX4dvVwhSj2gU));
    }
    else if ggA55("tocfunction") {
      tdVtLm(F1cW6, lo3iM(F1cW6, QX4dvVwhSj2gU));
    }
    else if ggA55("tointeger") {
      fkeYjCR(F1cW6, wpJYTRWrR7A1(F1cW6, QX4dvVwhSj2gU));
    }
    else if ggA55("tonumber") {
      eL39Q(F1cW6, WRKQV2(F1cW6, QX4dvVwhSj2gU));
    }
    else if ggA55("topointer") {
      Pq3D7dfNW72(F1cW6, Kmg0LKybFNq(s_upvK2G44_(F1cW6, QX4dvVwhSj2gU)));
    }
    else if ggA55("touserdata") {
      Pq3D7dfNW72(F1cW6, az06UweO0(F1cW6, QX4dvVwhSj2gU));
    }
    else if ggA55("tostring") {
      const char *QMtlR = aCBxOp(F1cW6, QX4dvVwhSj2gU);
      const char *P9gjLrnk = U5Uep4tkbF(F1cW6, QMtlR);
      nUwjhF(P9gjLrnk);  /* to avoid warnings */
      Tpg_Az((QMtlR == qzdsHHKSA4 && P9gjLrnk == qzdsHHKSA4) || ZJzN(QMtlR, P9gjLrnk) == 0);
    }
    else if ggA55("Ltolstring") {
      GSB5RUz(F1cW6, QX4dvVwhSj2gU, qzdsHHKSA4);
    }
    else if ggA55("type") {
      U5Uep4tkbF(F1cW6, sHPPVPQoTY1g(F1cW6, GETerOgvHggO));
    }
    else if ggA55("xmove") {
      int Yv4Is = QX4dvVwhSj2gU;
      int HTm5wQ43ct = QX4dvVwhSj2gU;
      oKhhn5 *nXU90i = (Yv4Is == 0) ? F1cW6 : bIDUiz2AQ(F1cW6, Yv4Is);
      oKhhn5 *ZKyAzoYB1O = (HTm5wQ43ct == 0) ? F1cW6 : bIDUiz2AQ(F1cW6, HTm5wQ43ct);
      int sxS1yv0OWbd = GETerOgvHggO;
      if (sxS1yv0OWbd == 0) sxS1yv0OWbd = Y4CW(nXU90i);
      sBGvaE0xy7LYt(nXU90i, ZKyAzoYB1O, sxS1yv0OWbd);
    }
    else if ggA55("isyieldable") {
      F98T3WTV(F1cW6, jwBHkh(bIDUiz2AQ(F1cW6, QX4dvVwhSj2gU)));
    }
    else if ggA55("yield") {
      return ClaI(F1cW6, GETerOgvHggO);
    }
    else if ggA55("yieldk") {
      int ahQIc0zYOe = GETerOgvHggO;
      int Ug3WiOFRVtz = QX4dvVwhSj2gU;
      return Nue_vw7V(F1cW6, ahQIc0zYOe, Ug3WiOFRVtz, eiKI);
    }
    else if ggA55("toclose") {
      jOzesJI(F1cW6, GETerOgvHggO);
    }
    else if ggA55("closeslot") {
      Wdvw6r4M(F1cW6, GETerOgvHggO);
    }
    else CvLJPQOTY(dANGorZhNcp, "unknown instruction %s", Khh7WZvdP);
  }
  return 0;
}


static int lCWMpBgOFB8fT (oKhhn5 *dANGorZhNcp) {
  oKhhn5 *F1cW6;
  const char *d2UwF29q1PF3g;
  if (Ndo0(dANGorZhNcp, 1)) {
    F1cW6 = P5A9(dANGorZhNcp);
    d2UwF29q1PF3g = d5Sfbl4(dANGorZhNcp, 2);
  }
  else if (PKvmz(dANGorZhNcp, 1)) {
    F1cW6 = bIDUiz2AQ(dANGorZhNcp, 1);
    d2UwF29q1PF3g = d5Sfbl4(dANGorZhNcp, 2);
  }
  else {
    F1cW6 = dANGorZhNcp;
    d2UwF29q1PF3g = d5Sfbl4(dANGorZhNcp, 1);
  }
  return aFoNWlK08(dANGorZhNcp, F1cW6, d2UwF29q1PF3g);
}


static int XEClM6irX (oKhhn5 *dANGorZhNcp) {
  return aFoNWlK08(dANGorZhNcp, dANGorZhNcp, aCBxOp(dANGorZhNcp, hsmk(1)));
}


static int eiKI (oKhhn5 *dANGorZhNcp, int IXouX3, SG4v1b_o wOgoX69R) {
  U5Uep4tkbF(dANGorZhNcp, AkjwlxAk[IXouX3]);
  QZ_KqhQywuF(dANGorZhNcp, "status");
  fkeYjCR(dANGorZhNcp, wOgoX69R);
  QZ_KqhQywuF(dANGorZhNcp, "ctx");
  return aFoNWlK08(dANGorZhNcp, dANGorZhNcp, aCBxOp(dANGorZhNcp, wOgoX69R));
}


static int BKu_k (oKhhn5 *dANGorZhNcp) {
  d5Sfbl4(dANGorZhNcp, 1);
  tBGSb(dANGorZhNcp, XEClM6irX, Y4CW(dANGorZhNcp));
  return 1;
}


/* }====================================================== */


/*
** {======================================================
** tests for C hooks
** =======================================================
*/

/*
** C hook that runs the C script stored in registry.C_HOOK[L]
*/
static void QKHyFAWt (oKhhn5 *dANGorZhNcp, psTUL *QpBFiwCISBn) {
  const char *aYwS31EVGIrgX;
  const char *const HDLak [] = {"call", "ret", "line", "count", "tailcall"};
  Wb8qAi(dANGorZhNcp, c8t9P08OG, "C_HOOK");
  Pq3D7dfNW72(dANGorZhNcp, dANGorZhNcp);
  xQwm5aJw(dANGorZhNcp, -2);  /* get C_HOOK[L] (script saved by sethookaux) */
  aYwS31EVGIrgX = aCBxOp(dANGorZhNcp, -1);  /* not very religious (string will be popped) */
  T8YUzJ0(dANGorZhNcp, 2);  /* remove C_HOOK and script */
  U5Uep4tkbF(dANGorZhNcp, HDLak[QpBFiwCISBn->EkSS7n4X]);  /* may be used by script */
  fkeYjCR(dANGorZhNcp, QpBFiwCISBn->yj8E90);  /* may be used by script */
  aFoNWlK08(dANGorZhNcp, dANGorZhNcp, aYwS31EVGIrgX);  /* run script from C_HOOK[L] */
}


/*
** sets 'registry.C_HOOK[L] = scpt' and sets 'Chook' as a hook
*/
static void ly_Q (oKhhn5 *dANGorZhNcp, int MgvjavXq, int FG5BSdPLq, const char *aYwS31EVGIrgX) {
  if (*aYwS31EVGIrgX == '\0') {  /* no script? */
    R8qN92rICw8e(dANGorZhNcp, qzdsHHKSA4, 0, 0);  /* turn off hooks */
    return;
  }
  Wb8qAi(dANGorZhNcp, c8t9P08OG, "C_HOOK");  /* get C_HOOK table */
  if (!VeXCb4iI(dANGorZhNcp, -1)) {  /* no hook table? */
    T8YUzJ0(dANGorZhNcp, 1);  /* remove previous value */
    M82y(dANGorZhNcp);  /* create new C_HOOK table */
    O3Od0iAjO4D(dANGorZhNcp, -1);
    LlBlEdffFES(dANGorZhNcp, c8t9P08OG, "C_HOOK");  /* register it */
  }
  Pq3D7dfNW72(dANGorZhNcp, dANGorZhNcp);
  U5Uep4tkbF(dANGorZhNcp, aYwS31EVGIrgX);
  LzfF_J(dANGorZhNcp, -3);  /* C_HOOK[L] = script */
  R8qN92rICw8e(dANGorZhNcp, QKHyFAWt, MgvjavXq, FG5BSdPLq);
}


static int eiPVaqOB5_p (oKhhn5 *dANGorZhNcp) {
  if (A1Hq(dANGorZhNcp, 1))
    R8qN92rICw8e(dANGorZhNcp, qzdsHHKSA4, 0, 0);  /* turn off hooks */
  else {
    const char *aYwS31EVGIrgX = d5Sfbl4(dANGorZhNcp, 1);
    const char *vVcpIltI = d5Sfbl4(dANGorZhNcp, 2);
    int FG5BSdPLq = DLI9dY50TrmnN(M8S6uvpldu3(dANGorZhNcp, 3, 0));
    int MgvjavXq = 0;
    if (nxzqp_k(vVcpIltI, 'c')) MgvjavXq |= YMLO65wsw;
    if (nxzqp_k(vVcpIltI, 'r')) MgvjavXq |= C7V7lSajNjS;
    if (nxzqp_k(vVcpIltI, 'l')) MgvjavXq |= k1uDFvLeKs2;
    if (FG5BSdPLq > 0) MgvjavXq |= Iqa45ls;
    ly_Q(dANGorZhNcp, MgvjavXq, FG5BSdPLq, aYwS31EVGIrgX);
  }
  return 0;
}


static int apPhN5LX_n6S3 (oKhhn5 *dANGorZhNcp) {
  int IXouX3, ahQIc0zYOe;
  oKhhn5 *s0C5KZQcpm = bIDUiz2AQ(dANGorZhNcp, 1);
  UpR5K(dANGorZhNcp, s0C5KZQcpm, 1, "coroutine expected");
  IXouX3 = sop_qb7u(s0C5KZQcpm, dANGorZhNcp, 0, &ahQIc0zYOe);
  if (IXouX3 != BTxEj2O71oh && IXouX3 != g0jmz0B0A) {
    F98T3WTV(dANGorZhNcp, 0);
    B3IfvcbxdJkc(dANGorZhNcp, -2);
    return 2;  /* return false + error message */
  }
  else {
    F98T3WTV(dANGorZhNcp, 1);
    return 1;
  }
}

/* }====================================================== */



static const struct a_YFt S_4nmuCfNoDN[] = {
  {"checkmemory", kMNwQFYT9S},
  {"closestate", n_D1NbA},
  {"d2s", PD22M1t},
  {"doonnewstack", nwYiX},
  {"doremote", Ht4mU3QXYb9},
  {"gccolor", ZoVQ8Nx58},
  {"gcage", ifi3yuc53},
  {"gcstate", K15wWJih},
  {"pobj", tmFwYe_13},
  {"getref", w2xdM9A_r},
  {"hash", C4raFzdt9d0d},
  {"log2", a4CRoDYj},
  {"limits", rVBksbg},
  {"listcode", zwtmQq},
  {"printcode", Cx7LV},
  {"listk", VUH9Ad9Ca},
  {"listabslineinfo", xnBNwSqdh0},
  {"listlocals", Xe0Pd9_3w},
  {"loadlib", MhuWYv7},
  {"checkpanic", XKwk1X6},
  {"newstate", tMoGIYC},
  {"newuserdata", T6ziaIm},
  {"num2int", xupq},
  {"pushuserdata", kqQH5y1n2o},
  {"querystr", oldCB},
  {"querytab", sN9c7BYGZh3},
  {"ref", s5YYh1HoxbH},
  {"resume", apPhN5LX_n6S3},
  {"s2d", MwMKvvIDsMlo},
  {"sethook", eiPVaqOB5_p},
  {"stacklevel", yS5icLA1},
  {"testC", lCWMpBgOFB8fT},
  {"makeCfunc", BKu_k},
  {"totalmem", YHBj},
  {"alloccount", uU0lG8E6EfF9},
  {"allocfailnext", i0fea9wn3La},
  {"trick", DOon},
  {"udataval", CWuAj},
  {"unref", vHrYLv},
  {"upvalue", aBVw},
  {qzdsHHKSA4, qzdsHHKSA4}
};


static void A3ZKGXCgX (void) {
  j8hck5(FEtY9Gx.fllG == 0);
  j8hck5(FEtY9Gx.ik3GsL == 0);
}


int ll51kfVZS0oS (oKhhn5 *dANGorZhNcp) {
  void *fNsyd7Ax;
  yxbPox Yv4Is = YdQIT(dANGorZhNcp, &fNsyd7Ax);
  GBr1Ka6(dANGorZhNcp, &aWIvuRrCLcXIt);
  sNn3k6E(dANGorZhNcp, &E1Jqc, dANGorZhNcp);
  F98T3WTV(dANGorZhNcp, 0);
  QZ_KqhQywuF(dANGorZhNcp, "_WARN");  /* _WARN = false */
  w33nvqYAgh(dANGorZhNcp);
  KdVSPt(A3ZKGXCgX);
  j8hck5(Yv4Is == NpR710XusKht && fNsyd7Ax == Kmg0LKybFNq(&FEtY9Gx));
  cp9ljht(dANGorZhNcp, Yv4Is, fNsyd7Ax);  /* exercise this function */
  D4ZZU(dANGorZhNcp, S_4nmuCfNoDN);
  return 1;
}

#endif

