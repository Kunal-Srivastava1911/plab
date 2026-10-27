/*
** $Id: lbaselib.c $
** Basic library
** See Copyright Notice in lua.h
*/

#define M588If
#define cWVmTAfOmSJ

#include "lprefix.h"


#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lua.h"

#include "lauxlib.h"
#include "lualib.h"


static int naPpCxj36AG (uFHW *duUWh_RZPJ) {
  int XV3QEzh = vpLZJZ(duUWh_RZPJ);  /* number of arguments */
  int ZvEuSp;
  for (ZvEuSp = 1; ZvEuSp <= XV3QEzh; ZvEuSp++) {  /* for each argument */
    cUVEmbGaKdI kCDoiAr0ru;
    const char *Fs_oAO = XarnhcsSSgFk(duUWh_RZPJ, ZvEuSp, &kCDoiAr0ru);  /* convert it to string */
    if (ZvEuSp > 1)  /* not the first element? */
      frRRikv8_g("\t", 1);  /* add a tab before it */
    frRRikv8_g(Fs_oAO, kCDoiAr0ru);  /* print it */
    j5ezPvEzC(duUWh_RZPJ, 1);  /* pop result */
  }
  Q9Zj9AbxJ();
  return 0;
}


/*
** Creates a warning with all given arguments.
** Check first for errors; otherwise an error may interrupt
** the composition of a warning, leaving it unfinished.
*/
static int H7GVw (uFHW *duUWh_RZPJ) {
  int XV3QEzh = vpLZJZ(duUWh_RZPJ);  /* number of arguments */
  int ZvEuSp;
  XKXmHo0kLMVb(duUWh_RZPJ, 1);  /* at least one argument */
  for (ZvEuSp = 2; ZvEuSp <= XV3QEzh; ZvEuSp++)
    XKXmHo0kLMVb(duUWh_RZPJ, ZvEuSp);  /* make sure all arguments are strings */
  for (ZvEuSp = 1; ZvEuSp < XV3QEzh; ZvEuSp++)  /* compose warning */
    EcMgo8fCvFb(duUWh_RZPJ, dhzMy4E_yt(duUWh_RZPJ, ZvEuSp), 1);
  EcMgo8fCvFb(duUWh_RZPJ, dhzMy4E_yt(duUWh_RZPJ, XV3QEzh), 0);  /* close warning */
  return 0;
}


#define CMC8GpFB	" \f\n\r\t\v"

static const char *LQX7hDVDTBTd (const char *Fs_oAO, int s4imyuT, A9SyclBRJp7Cv *VDrgvsFE) {
  nOmDsWQ XV3QEzh = 0;
  int B9QyR0m = 0;
  Fs_oAO += Ytqz(Fs_oAO, CMC8GpFB);  /* skip initial spaces */
  if (*Fs_oAO == '-') { Fs_oAO++; B9QyR0m = 1; }  /* handle sign */
  else if (*Fs_oAO == '+') Fs_oAO++;
  if (!J7fh1((unsigned char)*Fs_oAO))  /* no digit? */
    return pngEIl5dutaQ;
  do {
    int KhxnlgAQ = (EbDGTWsqS8Qm((unsigned char)*Fs_oAO)) ? *Fs_oAO - '0'
                   : (DoAWE((unsigned char)*Fs_oAO) - 'A') + 10;
    if (KhxnlgAQ >= s4imyuT) return pngEIl5dutaQ;  /* invalid numeral */
    XV3QEzh = XV3QEzh * s4imyuT + KhxnlgAQ;
    Fs_oAO++;
  } while (J7fh1((unsigned char)*Fs_oAO));
  Fs_oAO += Ytqz(Fs_oAO, CMC8GpFB);  /* skip trailing spaces */
  *VDrgvsFE = (A9SyclBRJp7Cv)((B9QyR0m) ? (0u - XV3QEzh) : XV3QEzh);
  return Fs_oAO;
}


static int fZl4W8FRk (uFHW *duUWh_RZPJ) {
  if (wOuU_RBuh(duUWh_RZPJ, 2)) {  /* standard conversion? */
    if (tWFiUA1cd8f(duUWh_RZPJ, 1) == dQ0lyy) {  /* already a number? */
      CMDnAC(duUWh_RZPJ, 1);  /* yes; return it */
      return 1;
    }
    else {
      cUVEmbGaKdI kCDoiAr0ru;
      const char *Fs_oAO = z5BNEe8yLQ(duUWh_RZPJ, 1, &kCDoiAr0ru);
      if (Fs_oAO != pngEIl5dutaQ && WmeBrIKYgKG(duUWh_RZPJ, Fs_oAO) == kCDoiAr0ru + 1)
        return 1;  /* successful conversion to number */
      /* else not a number */
      bN1MnZV7(duUWh_RZPJ, 1);  /* (but there must be some parameter) */
    }
  }
  else {
    cUVEmbGaKdI kCDoiAr0ru;
    const char *Fs_oAO;
    A9SyclBRJp7Cv XV3QEzh = 0;  /* to avoid warnings */
    A9SyclBRJp7Cv s4imyuT = KS860DsNy4k(duUWh_RZPJ, 2);
    twVPNa(duUWh_RZPJ, 1, qCh9);  /* no numbers as strings */
    Fs_oAO = z5BNEe8yLQ(duUWh_RZPJ, 1, &kCDoiAr0ru);
    tP2V7JbFZJkA(duUWh_RZPJ, 2 <= s4imyuT && s4imyuT <= 36, 2, "base out of range");
    if (LQX7hDVDTBTd(Fs_oAO, (int)s4imyuT, &XV3QEzh) == Fs_oAO + kCDoiAr0ru) {
      w8w_ctnMX4F43(duUWh_RZPJ, XV3QEzh);
      return 1;
    }  /* else not a number */
  }  /* else not a number */
  ta9jwkgK(duUWh_RZPJ);  /* not a number */
  return 1;
}


static int cEB8pI6Bun (uFHW *duUWh_RZPJ) {
  int hSM4csEdH = (int)A0fUpEvcq9W(duUWh_RZPJ, 2, 1);
  CMDnAC(duUWh_RZPJ, 1);
  if (tWFiUA1cd8f(duUWh_RZPJ, 1) == qCh9 && hSM4csEdH > 0) {
    QKFS1Lgzk9Qi9(duUWh_RZPJ, hSM4csEdH);   /* add extra information */
    SlsKlhQCYP(duUWh_RZPJ, 1);
    CJ4G(duUWh_RZPJ, 2);
  }
  return tvVqKR1iJQV(duUWh_RZPJ);
}


static int Suiik_Pv (uFHW *duUWh_RZPJ) {
  bN1MnZV7(duUWh_RZPJ, 1);
  if (!Oq_o(duUWh_RZPJ, 1)) {
    f64KCB0cr(duUWh_RZPJ);
    return 1;  /* no metatable */
  }
  snJfZCj(duUWh_RZPJ, 1, "__metatable");
  return 1;  /* returns either __metatable field (if present) or metatable */
}


static int z5ImM (uFHW *duUWh_RZPJ) {
  int YvyG74gWTB_le = tWFiUA1cd8f(duUWh_RZPJ, 2);
  twVPNa(duUWh_RZPJ, 1, qGhd);
  u0lsEGC(duUWh_RZPJ, YvyG74gWTB_le == mccwcl3SN || YvyG74gWTB_le == qGhd, 2, "nil or table");
  if (O_0UD67xCtG(snJfZCj(duUWh_RZPJ, 1, "__metatable") != mccwcl3SN))
    return EIfcSeaGgci_(duUWh_RZPJ, "cannot change a protected metatable");
  CMDnAC(duUWh_RZPJ, 2);
  icN8Und(duUWh_RZPJ, 1);
  return 1;
}


static int xYr_7F36Ff (uFHW *duUWh_RZPJ) {
  bN1MnZV7(duUWh_RZPJ, 1);
  bN1MnZV7(duUWh_RZPJ, 2);
  pFXBk4(duUWh_RZPJ, TF1P7YlcSrw2(duUWh_RZPJ, 1, 2));
  return 1;
}


static int m77ezhH (uFHW *duUWh_RZPJ) {
  int YvyG74gWTB_le = tWFiUA1cd8f(duUWh_RZPJ, 1);
  u0lsEGC(duUWh_RZPJ, YvyG74gWTB_le == qGhd || YvyG74gWTB_le == qCh9, 1,
                      "table or string");
  w8w_ctnMX4F43(duUWh_RZPJ, gqXWt3mmCzZ2(duUWh_RZPJ, 1));
  return 1;
}


static int cf5k (uFHW *duUWh_RZPJ) {
  twVPNa(duUWh_RZPJ, 1, qGhd);
  bN1MnZV7(duUWh_RZPJ, 2);
  CMDnAC(duUWh_RZPJ, 2);
  l8OdS(duUWh_RZPJ, 1);
  return 1;
}

static int y5Bhj1aPuv (uFHW *duUWh_RZPJ) {
  twVPNa(duUWh_RZPJ, 1, qGhd);
  bN1MnZV7(duUWh_RZPJ, 2);
  bN1MnZV7(duUWh_RZPJ, 3);
  CMDnAC(duUWh_RZPJ, 3);
  OX1oTjJiv0bFR(duUWh_RZPJ, 1);
  return 1;
}


static int fqAx (uFHW *duUWh_RZPJ, int Aei95BwSiqK) {
  if (Aei95BwSiqK == -1)
    ta9jwkgK(duUWh_RZPJ);  /* invalid call to 'lua_gc' */
  else
    mQPJg(duUWh_RZPJ, (Aei95BwSiqK == rTTyQ) ? "incremental"
                                             : "generational");
  return 1;
}


/*
** check whether call to 'lua_gc' was valid (not inside a finalizer)
*/
#define cnkY6v(WIpPiEgyYV0m) { if (WIpPiEgyYV0m == -1) break; }

static int LiIvgc9 (uFHW *duUWh_RZPJ) {
  static const char *const kKsV[] = {"stop", "restart", "collect",
    "count", "step", "setpause", "setstepmul",
    "isrunning", "generational", "incremental", pngEIl5dutaQ};
  static const int lstkh4rphYou8[] = {UEjga8YJ80p, CVWKWKL63, h_N2SumdM2,
    xjh4PgXfX, AGFSi, OuqcgTu5ADlg, he2lRg9YUh,
    JqswwJO8S4, OeNvFdHX, rTTyQ};
  int r0bNIoV = lstkh4rphYou8[toOLt7Ne2O6gL(duUWh_RZPJ, 1, "collect", kKsV)];
  switch (r0bNIoV) {
    case xjh4PgXfX: {
      int Fbe0 = EIqLZLPi(duUWh_RZPJ, r0bNIoV);
      int s2bX = EIqLZLPi(duUWh_RZPJ, UTLe_Hbw);
      cnkY6v(Fbe0);
      v4VceKg(duUWh_RZPJ, (YyujdcpPszHrj)Fbe0 + ((YyujdcpPszHrj)s2bX/1024));
      return 1;
    }
    case AGFSi: {
      int mtcW = (int)A0fUpEvcq9W(duUWh_RZPJ, 2, 0);
      int WIpPiEgyYV0m = EIqLZLPi(duUWh_RZPJ, r0bNIoV, mtcW);
      cnkY6v(WIpPiEgyYV0m);
      pFXBk4(duUWh_RZPJ, WIpPiEgyYV0m);
      return 1;
    }
    case OuqcgTu5ADlg:
    case he2lRg9YUh: {
      int ysgxitLE1Db = (int)A0fUpEvcq9W(duUWh_RZPJ, 2, 0);
      int ooyvyj9RW = EIqLZLPi(duUWh_RZPJ, r0bNIoV, ysgxitLE1Db);
      cnkY6v(ooyvyj9RW);
      w8w_ctnMX4F43(duUWh_RZPJ, ooyvyj9RW);
      return 1;
    }
    case JqswwJO8S4: {
      int WIpPiEgyYV0m = EIqLZLPi(duUWh_RZPJ, r0bNIoV);
      cnkY6v(WIpPiEgyYV0m);
      pFXBk4(duUWh_RZPJ, WIpPiEgyYV0m);
      return 1;
    }
    case OeNvFdHX: {
      int dhgb = (int)A0fUpEvcq9W(duUWh_RZPJ, 2, 0);
      int Cu9ocF8aWSYa = (int)A0fUpEvcq9W(duUWh_RZPJ, 3, 0);
      return fqAx(duUWh_RZPJ, EIqLZLPi(duUWh_RZPJ, r0bNIoV, dhgb, Cu9ocF8aWSYa));
    }
    case rTTyQ: {
      int wSnFM = (int)A0fUpEvcq9W(duUWh_RZPJ, 2, 0);
      int agCi5 = (int)A0fUpEvcq9W(duUWh_RZPJ, 3, 0);
      int hWDkitVu1LZ = (int)A0fUpEvcq9W(duUWh_RZPJ, 4, 0);
      return fqAx(duUWh_RZPJ, EIqLZLPi(duUWh_RZPJ, r0bNIoV, wSnFM, agCi5, hWDkitVu1LZ));
    }
    default: {
      int WIpPiEgyYV0m = EIqLZLPi(duUWh_RZPJ, r0bNIoV);
      cnkY6v(WIpPiEgyYV0m);
      w8w_ctnMX4F43(duUWh_RZPJ, WIpPiEgyYV0m);
      return 1;
    }
  }
  ta9jwkgK(duUWh_RZPJ);  /* invalid call (inside a finalizer) */
  return 1;
}


static int sK3WdrxjKTpPf (uFHW *duUWh_RZPJ) {
  int YvyG74gWTB_le = tWFiUA1cd8f(duUWh_RZPJ, 1);
  tP2V7JbFZJkA(duUWh_RZPJ, YvyG74gWTB_le != fmK_baS, 1, "value expected");
  mQPJg(duUWh_RZPJ, BrUrcO(duUWh_RZPJ, YvyG74gWTB_le));
  return 1;
}


static int hHBMvOnzc6y2 (uFHW *duUWh_RZPJ) {
  twVPNa(duUWh_RZPJ, 1, qGhd);
  CMDnAC(duUWh_RZPJ, 2);  /* create a 2nd argument if there isn't one */
  if (X9hnl1rMU8(duUWh_RZPJ, 1))
    return 2;
  else {
    f64KCB0cr(duUWh_RZPJ);
    return 1;
  }
}


static int Ow5S0AQRSF (uFHW *duUWh_RZPJ, int LxOgDKrBsp7ih, F0D9 Fbe0) {
  (void)duUWh_RZPJ; (void)LxOgDKrBsp7ih; (void)Fbe0;  /* unused */
  return 3;
}

static int S1u0Fu (uFHW *duUWh_RZPJ) {
  bN1MnZV7(duUWh_RZPJ, 1);
  if (snJfZCj(duUWh_RZPJ, 1, "__pairs") == mccwcl3SN) {  /* no metamethod? */
    RcMdc0WJp(duUWh_RZPJ, hHBMvOnzc6y2);  /* will return generator, */
    SlsKlhQCYP(duUWh_RZPJ, 1);  /* state, */
    f64KCB0cr(duUWh_RZPJ);  /* and initial value */
  }
  else {
    SlsKlhQCYP(duUWh_RZPJ, 1);  /* argument 'self' to metamethod */
    nsxr(duUWh_RZPJ, 1, 3, 0, Ow5S0AQRSF);  /* get 3 values from metamethod */
  }
  return 3;
}


/*
** Traversal function for 'ipairs'
*/
static int ovjN59CvcFDCm (uFHW *duUWh_RZPJ) {
  A9SyclBRJp7Cv ZvEuSp = KS860DsNy4k(duUWh_RZPJ, 2);
  ZvEuSp = rrZbxhtVnGgvK(+, ZvEuSp, 1);
  w8w_ctnMX4F43(duUWh_RZPJ, ZvEuSp);
  return (r8SVecmUr_(duUWh_RZPJ, 1, ZvEuSp) == mccwcl3SN) ? 1 : 2;
}


/*
** 'ipairs' function. Returns 'ipairsaux', given "table", 0.
** (The given "table" may not be a table.)
*/
static int Evgk (uFHW *duUWh_RZPJ) {
  bN1MnZV7(duUWh_RZPJ, 1);
  RcMdc0WJp(duUWh_RZPJ, ovjN59CvcFDCm);  /* iteration function */
  SlsKlhQCYP(duUWh_RZPJ, 1);  /* state */
  w8w_ctnMX4F43(duUWh_RZPJ, 0);  /* initial value */
  return 3;
}


static int JPbHUv (uFHW *duUWh_RZPJ, int LxOgDKrBsp7ih, int OVN2dp3y3p) {
  if (xsB0jQAG(LxOgDKrBsp7ih == U9QTDihnd)) {
    if (OVN2dp3y3p != 0) {  /* 'env' parameter? */
      SlsKlhQCYP(duUWh_RZPJ, OVN2dp3y3p);  /* environment for loaded function */
      if (!gBY6PWhAD(duUWh_RZPJ, -2, 1))  /* set it as 1st upvalue */
        j5ezPvEzC(duUWh_RZPJ, 1);  /* remove 'env' if not used by previous call */
    }
    return 1;
  }
  else {  /* error (message is on top of the stack) */
    ta9jwkgK(duUWh_RZPJ);
    vavTjAv6fV(duUWh_RZPJ, -2);  /* put before error message */
    return 2;  /* return fail plus error message */
  }
}


static int dopPOBKQMPz (uFHW *duUWh_RZPJ) {
  const char *mHztJimE8 = Hv0IV3ns2i(duUWh_RZPJ, 1, pngEIl5dutaQ);
  const char *vY1xzcXRnX2 = Hv0IV3ns2i(duUWh_RZPJ, 2, pngEIl5dutaQ);
  int LA33Sc78 = (!nF4jU9(duUWh_RZPJ, 3) ? 3 : 0);  /* 'env' index or 0 if no 'env' */
  int LxOgDKrBsp7ih = y2RepgEIuOFe5(duUWh_RZPJ, mHztJimE8, vY1xzcXRnX2);
  return JPbHUv(duUWh_RZPJ, LxOgDKrBsp7ih, LA33Sc78);
}


/*
** {======================================================
** Generic Read function
** =======================================================
*/


/*
** reserved slot, above all arguments, to hold a copy of the returned
** string to avoid it being collected while parsed. 'load' has four
** optional arguments (chunk, source name, mode, and environment).
*/
#define qkqN	5


/*
** Reader for generic 'load' function: 'lua_load' uses the
** stack for internal stuff, so the reader cannot change the
** stack top. Instead, it keeps its resulting string in a
** reserved slot inside the stack.
*/
static const char *IGrFH (uFHW *duUWh_RZPJ, void *vPkZX8ZVR, cUVEmbGaKdI *XHv7mM) {
  (void)(vPkZX8ZVR);  /* not used */
  L_G_Nm7Tl(duUWh_RZPJ, 2, "too many nested functions");
  SlsKlhQCYP(duUWh_RZPJ, 1);  /* get function */
  yNWngd(duUWh_RZPJ, 0, 1);  /* call it */
  if (vgQeCL_aTiDF2(duUWh_RZPJ, -1)) {
    j5ezPvEzC(duUWh_RZPJ, 1);  /* pop result */
    *XHv7mM = 0;
    return pngEIl5dutaQ;
  }
  else if (O_0UD67xCtG(!jf6Akfr4q(duUWh_RZPJ, -1)))
    EIfcSeaGgci_(duUWh_RZPJ, "reader function must return a string");
  gor15nSZS1(duUWh_RZPJ, qkqN);  /* save string in reserved slot */
  return z5BNEe8yLQ(duUWh_RZPJ, qkqN, XHv7mM);
}


static int ULKR2NuTKyv_q (uFHW *duUWh_RZPJ) {
  int LxOgDKrBsp7ih;
  cUVEmbGaKdI kCDoiAr0ru;
  const char *Fs_oAO = z5BNEe8yLQ(duUWh_RZPJ, 1, &kCDoiAr0ru);
  const char *vY1xzcXRnX2 = Hv0IV3ns2i(duUWh_RZPJ, 3, "bt");
  int LA33Sc78 = (!nF4jU9(duUWh_RZPJ, 4) ? 4 : 0);  /* 'env' index or 0 if no 'env' */
  if (Fs_oAO != pngEIl5dutaQ) {  /* loading a string? */
    const char *j79cxu5rJL = Hv0IV3ns2i(duUWh_RZPJ, 2, Fs_oAO);
    LxOgDKrBsp7ih = WGArOjioO(duUWh_RZPJ, Fs_oAO, kCDoiAr0ru, j79cxu5rJL, vY1xzcXRnX2);
  }
  else {  /* loading from a reader function */
    const char *j79cxu5rJL = Hv0IV3ns2i(duUWh_RZPJ, 2, "=(load)");
    twVPNa(duUWh_RZPJ, 1, ygARZlvHKyUy);
    CMDnAC(duUWh_RZPJ, qkqN);  /* create reserved slot */
    LxOgDKrBsp7ih = ULTuXa7D(duUWh_RZPJ, IGrFH, pngEIl5dutaQ, j79cxu5rJL, vY1xzcXRnX2);
  }
  return JPbHUv(duUWh_RZPJ, LxOgDKrBsp7ih, LA33Sc78);
}

/* }====================================================== */


static int nxpUt (uFHW *duUWh_RZPJ, int YpyZIzozVVDT5, F0D9 ddBthDpP8wKB) {
  (void)YpyZIzozVVDT5;  (void)ddBthDpP8wKB;  /* only to match 'lua_Kfunction' prototype */
  return vpLZJZ(duUWh_RZPJ) - 1;
}


static int Gwjy1THh (uFHW *duUWh_RZPJ) {
  const char *mHztJimE8 = Hv0IV3ns2i(duUWh_RZPJ, 1, pngEIl5dutaQ);
  CMDnAC(duUWh_RZPJ, 1);
  if (O_0UD67xCtG(JUfib7BQreNE(duUWh_RZPJ, mHztJimE8) != U9QTDihnd))
    return tvVqKR1iJQV(duUWh_RZPJ);
  nsxr(duUWh_RZPJ, 0, X_gba, 0, nxpUt);
  return nxpUt(duUWh_RZPJ, 0, 0);
}


static int Sj50rKbcD (uFHW *duUWh_RZPJ) {
  if (xsB0jQAG(XhqU5jMpb(duUWh_RZPJ, 1)))  /* condition is true? */
    return vpLZJZ(duUWh_RZPJ);  /* return all arguments */
  else {  /* error */
    bN1MnZV7(duUWh_RZPJ, 1);  /* there must be a condition */
    l5sfaJatduFWs(duUWh_RZPJ, 1);  /* remove it */
    s7Q_HybF(duUWh_RZPJ, "assertion failed!");  /* default message */
    CMDnAC(duUWh_RZPJ, 1);  /* leave only message (default if no other one) */
    return cEB8pI6Bun(duUWh_RZPJ);  /* call 'error' */
  }
}


static int LyrzD (uFHW *duUWh_RZPJ) {
  int XV3QEzh = vpLZJZ(duUWh_RZPJ);
  if (tWFiUA1cd8f(duUWh_RZPJ, 1) == qCh9 && *dhzMy4E_yt(duUWh_RZPJ, 1) == '#') {
    w8w_ctnMX4F43(duUWh_RZPJ, XV3QEzh-1);
    return 1;
  }
  else {
    A9SyclBRJp7Cv ZvEuSp = KS860DsNy4k(duUWh_RZPJ, 1);
    if (ZvEuSp < 0) ZvEuSp = XV3QEzh + ZvEuSp;
    else if (ZvEuSp > XV3QEzh) ZvEuSp = XV3QEzh;
    tP2V7JbFZJkA(duUWh_RZPJ, 1 <= ZvEuSp, 1, "index out of range");
    return XV3QEzh - (int)ZvEuSp;
  }
}


/*
** Continuation function for 'pcall' and 'xpcall'. Both functions
** already pushed a 'true' before doing the call, so in case of success
** 'finishpcall' only has to return everything in the stack minus
** 'extra' values (where 'extra' is exactly the number of items to be
** ignored).
*/
static int XogH4rxpVSUS (uFHW *duUWh_RZPJ, int LxOgDKrBsp7ih, F0D9 ruo7a) {
  if (O_0UD67xCtG(LxOgDKrBsp7ih != U9QTDihnd && LxOgDKrBsp7ih != vttfOl)) {  /* error? */
    pFXBk4(duUWh_RZPJ, 0);  /* first result (false) */
    SlsKlhQCYP(duUWh_RZPJ, -2);  /* error message */
    return 2;  /* return false, msg */
  }
  else
    return vpLZJZ(duUWh_RZPJ) - (int)ruo7a;  /* return all results */
}


static int YgEOW (uFHW *duUWh_RZPJ) {
  int LxOgDKrBsp7ih;
  bN1MnZV7(duUWh_RZPJ, 1);
  pFXBk4(duUWh_RZPJ, 1);  /* first result if no errors */
  vavTjAv6fV(duUWh_RZPJ, 1);  /* put it in place */
  LxOgDKrBsp7ih = axurvILj(duUWh_RZPJ, vpLZJZ(duUWh_RZPJ) - 2, X_gba, 0, 0, XogH4rxpVSUS);
  return XogH4rxpVSUS(duUWh_RZPJ, LxOgDKrBsp7ih, 0);
}


/*
** Do a protected call with error handling. After 'lua_rotate', the
** stack will have <f, err, true, f, [args...]>; so, the function passes
** 2 to 'finishpcall' to skip the 2 first values when returning results.
*/
static int skRc (uFHW *duUWh_RZPJ) {
  int LxOgDKrBsp7ih;
  int XV3QEzh = vpLZJZ(duUWh_RZPJ);
  twVPNa(duUWh_RZPJ, 2, ygARZlvHKyUy);  /* check error function */
  pFXBk4(duUWh_RZPJ, 1);  /* first result */
  SlsKlhQCYP(duUWh_RZPJ, 1);  /* function */
  AIF9MOae(duUWh_RZPJ, 3, 2);  /* move them below function's arguments */
  LxOgDKrBsp7ih = axurvILj(duUWh_RZPJ, XV3QEzh - 2, X_gba, 2, 2, XogH4rxpVSUS);
  return XogH4rxpVSUS(duUWh_RZPJ, LxOgDKrBsp7ih, 2);
}


static int iugR1 (uFHW *duUWh_RZPJ) {
  bN1MnZV7(duUWh_RZPJ, 1);
  XarnhcsSSgFk(duUWh_RZPJ, 1, pngEIl5dutaQ);
  return 1;
}


static const E_2INDOR3 RqGyWqdlZzEhJ[] = {
  {"assert", Sj50rKbcD},
  {"collectgarbage", LiIvgc9},
  {"dofile", Gwjy1THh},
  {"error", cEB8pI6Bun},
  {"getmetatable", Suiik_Pv},
  {"ipairs", Evgk},
  {"loadfile", dopPOBKQMPz},
  {"load", ULKR2NuTKyv_q},
  {"next", hHBMvOnzc6y2},
  {"pairs", S1u0Fu},
  {"pcall", YgEOW},
  {"print", naPpCxj36AG},
  {"warn", H7GVw},
  {"rawequal", xYr_7F36Ff},
  {"rawlen", m77ezhH},
  {"rawget", cf5k},
  {"rawset", y5Bhj1aPuv},
  {"select", LyrzD},
  {"setmetatable", z5ImM},
  {"tonumber", fZl4W8FRk},
  {"tostring", iugR1},
  {"type", sK3WdrxjKTpPf},
  {"xpcall", skRc},
  /* placeholders */
  {Jq_fOB4H92, pngEIl5dutaQ},
  {"_VERSION", pngEIl5dutaQ},
  {pngEIl5dutaQ, pngEIl5dutaQ}
};


MBLVTboc9 int rGNNfMFLvfc (uFHW *duUWh_RZPJ) {
  /* open lib into global table */
  UwrA(duUWh_RZPJ);
  M4JZz7v_I(duUWh_RZPJ, RqGyWqdlZzEhJ, 0);
  /* set global _G */
  SlsKlhQCYP(duUWh_RZPJ, -1);
  RSzfKwFm(duUWh_RZPJ, -2, Jq_fOB4H92);
  /* set global _VERSION */
  s7Q_HybF(duUWh_RZPJ, HgmjDHum);
  RSzfKwFm(duUWh_RZPJ, -2, "_VERSION");
  return 1;
}

