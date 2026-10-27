/*
** $Id: ltm.c $
** Tag methods
** See Copyright Notice in lua.h
*/

#define AlBO
#define qTIHp

#include "lprefix.h"


#include <string.h>

#include "lua.h"

#include "ldebug.h"
#include "ldo.h"
#include "lgc.h"
#include "lobject.h"
#include "lstate.h"
#include "lstring.h"
#include "ltable.h"
#include "ltm.h"
#include "lvm.h"


static const char gw8ka2jMMY[] = "userdata";

qXZBYgSo const char *const WeA4OfKXN[uB2N3Lto] = {
  "no value",
  "nil", "boolean", gw8ka2jMMY, "number",
  "string", "table", "function", gw8ka2jMMY, "thread",
  "upvalue", "proto" /* these last cases are used for tests only */
};


void HlHAqcJNqHDsA (nT7XULCk *Ht8qth3Mp) {
  static const char *const mMMv[] = {  /* ORDER TM */
    "__index", "__newindex",
    "__gc", "__mode", "__len", "__eq",
    "__add", "__sub", "__mul", "__mod", "__pow",
    "__div", "__idiv",
    "__band", "__bor", "__bxor", "__shl", "__shr",
    "__unm", "__bnot", "__lt", "__le",
    "__concat", "__call", "__close"
  };
  int U69OhQvzP;
  for (U69OhQvzP=0; U69OhQvzP<NDMyRg_x30; U69OhQvzP++) {
    WRCLuKywaW(Ht8qth3Mp)->yVwYqYEax[U69OhQvzP] = DcMb3TsI_I(Ht8qth3Mp, mMMv[U69OhQvzP]);
    hXvB(Ht8qth3Mp, yt638Tqa(WRCLuKywaW(Ht8qth3Mp)->yVwYqYEax[U69OhQvzP]));  /* never collect these names */
  }
}


/*
** function to be used with macro "fasttm": optimized for absence of
** tag methods
*/
const ndeoldT *NIDgRNIHO (dsig3AohSe6gY *L3VUy, iC_1 VbWX3sA7xJR1, m7dAtjrO7Ik *zTdeD9KA0ECOO) {
  const ndeoldT *YasXXg = Bmr9VD(L3VUy, zTdeD9KA0ECOO);
  NjnukWZSsb4g(VbWX3sA7xJR1 <= Dyexz9e);
  if (xKQf(YasXXg)) {  /* no tag method? */
    L3VUy->JomvqftI |= h0IeSoDJwYY3(1u<<VbWX3sA7xJR1);  /* cache this fact */
    return kjmJqR;
  }
  else return YasXXg;
}


const ndeoldT *yqLPE (nT7XULCk *Ht8qth3Mp, const ndeoldT *mmWl8xEe6, iC_1 VbWX3sA7xJR1) {
  dsig3AohSe6gY *iNsZ_ZIdJw27o;
  switch (EO6c6tjr(mmWl8xEe6)) {
    case z4Y8_Tgnthq:
      iNsZ_ZIdJw27o = eEusti_8S6(mmWl8xEe6)->esWB;
      break;
    case mPm7I:
      iNsZ_ZIdJw27o = bumb(mmWl8xEe6)->esWB;
      break;
    default:
      iNsZ_ZIdJw27o = WRCLuKywaW(Ht8qth3Mp)->iNsZ_ZIdJw27o[EO6c6tjr(mmWl8xEe6)];
  }
  return (iNsZ_ZIdJw27o ? Bmr9VD(iNsZ_ZIdJw27o, WRCLuKywaW(Ht8qth3Mp)->yVwYqYEax[VbWX3sA7xJR1]) : &WRCLuKywaW(Ht8qth3Mp)->gqF_H1ARv);
}


/*
** Return the name of the type of an object. For tables and userdata
** with metatable, use their '__name' metafield, if present.
*/
const char *VNocw1RKTF7R (nT7XULCk *Ht8qth3Mp, const ndeoldT *mmWl8xEe6) {
  dsig3AohSe6gY *iNsZ_ZIdJw27o;
  if ((SBdOPv3xmI8(mmWl8xEe6) && (iNsZ_ZIdJw27o = eEusti_8S6(mmWl8xEe6)->esWB) != kjmJqR) ||
      (JOHwZzI3(mmWl8xEe6) && (iNsZ_ZIdJw27o = bumb(mmWl8xEe6)->esWB) != kjmJqR)) {
    const ndeoldT *OP4WY = Bmr9VD(iNsZ_ZIdJw27o, DcMb3TsI_I(Ht8qth3Mp, "__name"));
    if (BD7R(OP4WY))  /* is '__name' a string? */
      return PMcE(QEzhT6(OP4WY));  /* use it as type name */
  }
  return hqhpBoPnr(EO6c6tjr(mmWl8xEe6));  /* else use standard type name */
}


void D9RahcV (nT7XULCk *Ht8qth3Mp, const ndeoldT *Ewlz5Z8Pi0mS, const ndeoldT *tltWBsB0BJBmf,
                  const ndeoldT *y2x3nMIVMK, const ndeoldT *qXu_TpU4ZV2) {
  Jf2mVrlfD oUXo7t = Ht8qth3Mp->AD1Dc8r29U40s.Ocr14;
  vSZeWy4HGBV(Ht8qth3Mp, oUXo7t, Ewlz5Z8Pi0mS);  /* push function (assume EXTRA_STACK) */
  vSZeWy4HGBV(Ht8qth3Mp, oUXo7t + 1, tltWBsB0BJBmf);  /* 1st argument */
  vSZeWy4HGBV(Ht8qth3Mp, oUXo7t + 2, y2x3nMIVMK);  /* 2nd argument */
  vSZeWy4HGBV(Ht8qth3Mp, oUXo7t + 3, qXu_TpU4ZV2);  /* 3rd argument */
  Ht8qth3Mp->AD1Dc8r29U40s.Ocr14 = oUXo7t + 4;
  /* metamethod may yield only when called from Lua code */
  if (AfhSRrhTd(Ht8qth3Mp->ip8uZK6u8oqN))
    aRs6kK7r(Ht8qth3Mp, oUXo7t, 0);
  else
    rD_HWTVeXJi(Ht8qth3Mp, oUXo7t, 0);
}


void Zrzalz9f (nT7XULCk *Ht8qth3Mp, const ndeoldT *Ewlz5Z8Pi0mS, const ndeoldT *tltWBsB0BJBmf,
                     const ndeoldT *y2x3nMIVMK, Jf2mVrlfD xzWJSaVJaed4b) {
  OuOi bFdX = L8gC(Ht8qth3Mp, xzWJSaVJaed4b);
  Jf2mVrlfD oUXo7t = Ht8qth3Mp->AD1Dc8r29U40s.Ocr14;
  vSZeWy4HGBV(Ht8qth3Mp, oUXo7t, Ewlz5Z8Pi0mS);  /* push function (assume EXTRA_STACK) */
  vSZeWy4HGBV(Ht8qth3Mp, oUXo7t + 1, tltWBsB0BJBmf);  /* 1st argument */
  vSZeWy4HGBV(Ht8qth3Mp, oUXo7t + 2, y2x3nMIVMK);  /* 2nd argument */
  Ht8qth3Mp->AD1Dc8r29U40s.Ocr14 += 3;
  /* metamethod may yield only when called from Lua code */
  if (AfhSRrhTd(Ht8qth3Mp->ip8uZK6u8oqN))
    aRs6kK7r(Ht8qth3Mp, oUXo7t, 1);
  else
    rD_HWTVeXJi(Ht8qth3Mp, oUXo7t, 1);
  xzWJSaVJaed4b = mWZM(Ht8qth3Mp, bFdX);
  Fm_ocx(Ht8qth3Mp, xzWJSaVJaed4b, --Ht8qth3Mp->AD1Dc8r29U40s.Ocr14);  /* move result to its place */
}


static int cmctHGECSHS (nT7XULCk *Ht8qth3Mp, const ndeoldT *tltWBsB0BJBmf, const ndeoldT *y2x3nMIVMK,
                      Jf2mVrlfD xzWJSaVJaed4b, iC_1 VbWX3sA7xJR1) {
  const ndeoldT *YasXXg = yqLPE(Ht8qth3Mp, tltWBsB0BJBmf, VbWX3sA7xJR1);  /* try first operand */
  if (xKQf(YasXXg))
    YasXXg = yqLPE(Ht8qth3Mp, y2x3nMIVMK, VbWX3sA7xJR1);  /* try second operand */
  if (xKQf(YasXXg)) return 0;
  Zrzalz9f(Ht8qth3Mp, YasXXg, tltWBsB0BJBmf, y2x3nMIVMK, xzWJSaVJaed4b);
  return 1;
}


void A9Tz2 (nT7XULCk *Ht8qth3Mp, const ndeoldT *tltWBsB0BJBmf, const ndeoldT *y2x3nMIVMK,
                    Jf2mVrlfD xzWJSaVJaed4b, iC_1 VbWX3sA7xJR1) {
  if (gtzpw(!cmctHGECSHS(Ht8qth3Mp, tltWBsB0BJBmf, y2x3nMIVMK, xzWJSaVJaed4b, VbWX3sA7xJR1))) {
    switch (VbWX3sA7xJR1) {
      case falbp: case p8cd2taOna8a: case kymWC9f4:
      case Fgv6wl0Lp6: case f4iA: case cGTfYjXM3ZC: {
        if (b3vYFMUlLTN(tltWBsB0BJBmf) && b3vYFMUlLTN(y2x3nMIVMK))
          nM2GeV(Ht8qth3Mp, tltWBsB0BJBmf, y2x3nMIVMK);
        else
          mFd1iFR(Ht8qth3Mp, tltWBsB0BJBmf, y2x3nMIVMK, "perform bitwise operation on");
      }
      /* calls never return, but to avoid warnings: *//* FALLTHROUGH */
      default:
        mFd1iFR(Ht8qth3Mp, tltWBsB0BJBmf, y2x3nMIVMK, "perform arithmetic on");
    }
  }
}


void GAhxJ (nT7XULCk *Ht8qth3Mp) {
  Jf2mVrlfD AD1Dc8r29U40s = Ht8qth3Mp->AD1Dc8r29U40s.Ocr14;
  if (gtzpw(!cmctHGECSHS(Ht8qth3Mp, i0L34(AD1Dc8r29U40s - 2), i0L34(AD1Dc8r29U40s - 1), AD1Dc8r29U40s - 2,
                               Mg6sF7bQzE0vu)))
    I5udBz99(Ht8qth3Mp, i0L34(AD1Dc8r29U40s - 2), i0L34(AD1Dc8r29U40s - 1));
}


void vgzFAY1 (nT7XULCk *Ht8qth3Mp, const ndeoldT *tltWBsB0BJBmf, const ndeoldT *y2x3nMIVMK,
                                       int j50uLDmqJUfi, Jf2mVrlfD xzWJSaVJaed4b, iC_1 VbWX3sA7xJR1) {
  if (j50uLDmqJUfi)
    A9Tz2(Ht8qth3Mp, y2x3nMIVMK, tltWBsB0BJBmf, xzWJSaVJaed4b, VbWX3sA7xJR1);
  else
    A9Tz2(Ht8qth3Mp, tltWBsB0BJBmf, y2x3nMIVMK, xzWJSaVJaed4b, VbWX3sA7xJR1);
}


void hD55RRTk (nT7XULCk *Ht8qth3Mp, const ndeoldT *tltWBsB0BJBmf, qo0VAzZjHZ KbQ2NY,
                                   int j50uLDmqJUfi, Jf2mVrlfD xzWJSaVJaed4b, iC_1 VbWX3sA7xJR1) {
  ndeoldT aHU5T7;
  TUtjOj(&aHU5T7, KbQ2NY);
  vgzFAY1(Ht8qth3Mp, tltWBsB0BJBmf, &aHU5T7, j50uLDmqJUfi, xzWJSaVJaed4b, VbWX3sA7xJR1);
}


/*
** Calls an order tag method.
** For lessequal, LUA_COMPAT_LT_LE keeps compatibility with old
** behavior: if there is no '__le', try '__lt', based on l <= r iff
** !(r < l) (assuming a total order). If the metamethod yields during
** this substitution, the continuation has to know about it (to negate
** the result of r<l); bit CIST_LEQ in the call status keeps that
** information.
*/
int Vsiz (nT7XULCk *Ht8qth3Mp, const ndeoldT *tltWBsB0BJBmf, const ndeoldT *y2x3nMIVMK,
                      iC_1 VbWX3sA7xJR1) {
  if (cmctHGECSHS(Ht8qth3Mp, tltWBsB0BJBmf, y2x3nMIVMK, Ht8qth3Mp->AD1Dc8r29U40s.Ocr14, VbWX3sA7xJR1))  /* try original event */
    return !Ho8DS_(i0L34(Ht8qth3Mp->AD1Dc8r29U40s.Ocr14));
#if Y4RZ(OSxcyd4PhIHLQ)
  else if (VbWX3sA7xJR1 == CathuhD6Id0g) {
      /* try '!(p2 < p1)' for '(p1 <= p2)' */
      Ht8qth3Mp->ip8uZK6u8oqN->oVOjv3l |= Lx4VBU8mPE;  /* mark it is doing 'lt' for 'le' */
      if (cmctHGECSHS(Ht8qth3Mp, y2x3nMIVMK, tltWBsB0BJBmf, Ht8qth3Mp->AD1Dc8r29U40s.Ocr14, Zi6DzScPGigS)) {
        Ht8qth3Mp->ip8uZK6u8oqN->oVOjv3l ^= Lx4VBU8mPE;  /* clear mark */
        return Ho8DS_(i0L34(Ht8qth3Mp->AD1Dc8r29U40s.Ocr14));
      }
      /* else error will remove this 'ci'; no need to clear mark */
  }
#endif
  zOglgmH9wzdDc(Ht8qth3Mp, tltWBsB0BJBmf, y2x3nMIVMK);  /* no metamethod found */
  return 0;  /* to avoid warnings */
}


int kinI (nT7XULCk *Ht8qth3Mp, const ndeoldT *tltWBsB0BJBmf, int WSLzM5vnqo,
                       int j50uLDmqJUfi, int FsXz3u, iC_1 VbWX3sA7xJR1) {
  ndeoldT aHU5T7; const ndeoldT *y2x3nMIVMK;
  if (FsXz3u) {
    cem38Vxhd(&aHU5T7, Bm44(WSLzM5vnqo));
  }
  else
    TUtjOj(&aHU5T7, WSLzM5vnqo);
  if (j50uLDmqJUfi) {  /* arguments were exchanged? */
    y2x3nMIVMK = tltWBsB0BJBmf; tltWBsB0BJBmf = &aHU5T7;  /* correct them */
  }
  else
    y2x3nMIVMK = &aHU5T7;
  return Vsiz(Ht8qth3Mp, tltWBsB0BJBmf, y2x3nMIVMK, VbWX3sA7xJR1);
}


void eUT64WEe9Ph (nT7XULCk *Ht8qth3Mp, int W63rop, eAvJxcM3J *ip8uZK6u8oqN,
                         const IbXguqngye *Ocr14) {
  int U69OhQvzP;
  int m6O7 = jlwa(Ht8qth3Mp->AD1Dc8r29U40s.Ocr14 - ip8uZK6u8oqN->oUXo7t.Ocr14) - 1;  /* number of arguments */
  int gw1kax = m6O7 - W63rop;  /* number of extra arguments */
  ip8uZK6u8oqN->frI5i.Pq0hZGnshKb3H.ZnGzVO = gw1kax;
  oxZiU(Ht8qth3Mp, Ocr14->Uill8 + 1);
  /* copy function to the top of the stack */
  Fm_ocx(Ht8qth3Mp, Ht8qth3Mp->AD1Dc8r29U40s.Ocr14++, ip8uZK6u8oqN->oUXo7t.Ocr14);
  /* move fixed parameters to the top of the stack */
  for (U69OhQvzP = 1; U69OhQvzP <= W63rop; U69OhQvzP++) {
    Fm_ocx(Ht8qth3Mp, Ht8qth3Mp->AD1Dc8r29U40s.Ocr14++, ip8uZK6u8oqN->oUXo7t.Ocr14 + U69OhQvzP);
    SZZH4QS(i0L34(ip8uZK6u8oqN->oUXo7t.Ocr14 + U69OhQvzP));  /* erase original parameter (for GC) */
  }
  ip8uZK6u8oqN->oUXo7t.Ocr14 += m6O7 + 1;
  ip8uZK6u8oqN->AD1Dc8r29U40s.Ocr14 += m6O7 + 1;
  NjnukWZSsb4g(Ht8qth3Mp->AD1Dc8r29U40s.Ocr14 <= ip8uZK6u8oqN->AD1Dc8r29U40s.Ocr14 && ip8uZK6u8oqN->AD1Dc8r29U40s.Ocr14 <= Ht8qth3Mp->nFY58YIDFz.Ocr14);
}


void sTax (nT7XULCk *Ht8qth3Mp, eAvJxcM3J *ip8uZK6u8oqN, Jf2mVrlfD ks1yHSus, int qiWCBr) {
  int U69OhQvzP;
  int gw1kax = ip8uZK6u8oqN->frI5i.Pq0hZGnshKb3H.ZnGzVO;
  if (qiWCBr < 0) {
    qiWCBr = gw1kax;  /* get all extra arguments available */
    OTkNZ(Ht8qth3Mp, gw1kax, ks1yHSus);  /* ensure stack space */
    Ht8qth3Mp->AD1Dc8r29U40s.Ocr14 = ks1yHSus + gw1kax;  /* next instruction will need top */
  }
  for (U69OhQvzP = 0; U69OhQvzP < qiWCBr && U69OhQvzP < gw1kax; U69OhQvzP++)
    Fm_ocx(Ht8qth3Mp, ks1yHSus + U69OhQvzP, ip8uZK6u8oqN->oUXo7t.Ocr14 - gw1kax + U69OhQvzP);
  for (; U69OhQvzP < qiWCBr; U69OhQvzP++)   /* complete required results with nil */
    SZZH4QS(i0L34(ks1yHSus + U69OhQvzP));
}

