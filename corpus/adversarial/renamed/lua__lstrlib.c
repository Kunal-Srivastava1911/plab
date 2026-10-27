/*
** $Id: lstrlib.c $
** Standard library for string operations and pattern-matching
** See Copyright Notice in lua.h
*/

#define cGjBQKAmFU
#define eT2vWxUW

#include "lprefix.h"


#include <ctype.h>
#include <float.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lua.h"

#include "lauxlib.h"
#include "lualib.h"


/*
** maximum number of captures that a pattern can do during
** pattern-matching. This limit is arbitrary, but must fit in
** an unsigned char.
*/
#if !v0y1ukO(TxB8MtANx)
#define TxB8MtANx		32
#endif


/* macro to 'unsign' a character */
#define L1SC0eGlMOc(UJAegx)	((unsigned char)(UJAegx))


/*
** Some sizes are better limited to fit in 'int', but must also fit in
** 'size_t'. (We assume that 'lua_Integer' cannot be smaller than 'int'.)
*/
#define oWvdqtxT1fkB2	((ssrSQ)(~(ssrSQ)0))

#define d4eo1yR  \
	(sizeof(ssrSQ) < sizeof(int) ? oWvdqtxT1fkB2 : (ssrSQ)(Rojqh))




static int B_thQ (cMupEM84Rw *qZEQHE2xvGPvV) {
  ssrSQ tjT_;
  RV0qYkC8dxO9B(qZEQHE2xvGPvV, 1, &tjT_);
  uoUK3WTgIAWaZ(qZEQHE2xvGPvV, (oOSatdH)tjT_);
  return 1;
}


/*
** translate a relative initial string position
** (negative means back from end): clip result to [1, inf).
** The length of any string in Lua must fit in a lua_Integer,
** so there are no overflows in the casts.
** The inverted comparison avoids a possible overflow
** computing '-pos'.
*/
static ssrSQ smcmHEMcOm (oOSatdH ptR8GKNfjobx, ssrSQ oz3j) {
  if (ptR8GKNfjobx > 0)
    return (ssrSQ)ptR8GKNfjobx;
  else if (ptR8GKNfjobx == 0)
    return 1;
  else if (ptR8GKNfjobx < -(oOSatdH)oz3j)  /* inverted comparison */
    return 1;  /* clip to 1 */
  else return oz3j + (ssrSQ)ptR8GKNfjobx + 1;
}


/*
** Gets an optional ending string position from argument 'arg',
** with default value 'def'.
** Negative means back from end: clip result to [0, len]
*/
static ssrSQ giRgy4wfyjpP (cMupEM84Rw *qZEQHE2xvGPvV, int w5qydoLBcq, oOSatdH nmQFyB2t,
                         ssrSQ oz3j) {
  oOSatdH ptR8GKNfjobx = wR3vpjjAn6I(qZEQHE2xvGPvV, w5qydoLBcq, nmQFyB2t);
  if (ptR8GKNfjobx > (oOSatdH)oz3j)
    return oz3j;
  else if (ptR8GKNfjobx >= 0)
    return (ssrSQ)ptR8GKNfjobx;
  else if (ptR8GKNfjobx < -(oOSatdH)oz3j)
    return 0;
  else return oz3j + (ssrSQ)ptR8GKNfjobx + 1;
}


static int CFSRjc5v9 (cMupEM84Rw *qZEQHE2xvGPvV) {
  ssrSQ tjT_;
  const char *hmQWG = RV0qYkC8dxO9B(qZEQHE2xvGPvV, 1, &tjT_);
  ssrSQ H9Zn1fmi7r = smcmHEMcOm(MY8LsFOwaa(qZEQHE2xvGPvV, 2), tjT_);
  ssrSQ hrZEdqnp5Pvsu = giRgy4wfyjpP(qZEQHE2xvGPvV, 3, -1, tjT_);
  if (H9Zn1fmi7r <= hrZEdqnp5Pvsu)
    wYFtBL7C(qZEQHE2xvGPvV, hmQWG + H9Zn1fmi7r - 1, (hrZEdqnp5Pvsu - H9Zn1fmi7r) + 1);
  else VIsqprcLO(qZEQHE2xvGPvV, "");
  return 1;
}


static int YaX1AErhVR (cMupEM84Rw *qZEQHE2xvGPvV) {
  ssrSQ tjT_, FrSzPASfnw;
  LHKm PiZjbFkqqmi;
  const char *hmQWG = RV0qYkC8dxO9B(qZEQHE2xvGPvV, 1, &tjT_);
  char *pzyakia2 = Ee6g3yd(qZEQHE2xvGPvV, &PiZjbFkqqmi, tjT_);
  for (FrSzPASfnw = 0; FrSzPASfnw < tjT_; FrSzPASfnw++)
    pzyakia2[FrSzPASfnw] = hmQWG[tjT_ - FrSzPASfnw - 1];
  N7xAu2vui3z(&PiZjbFkqqmi, tjT_);
  return 1;
}


static int XhuvE9Qt (cMupEM84Rw *qZEQHE2xvGPvV) {
  ssrSQ tjT_;
  ssrSQ FrSzPASfnw;
  LHKm PiZjbFkqqmi;
  const char *hmQWG = RV0qYkC8dxO9B(qZEQHE2xvGPvV, 1, &tjT_);
  char *pzyakia2 = Ee6g3yd(qZEQHE2xvGPvV, &PiZjbFkqqmi, tjT_);
  for (FrSzPASfnw=0; FrSzPASfnw<tjT_; FrSzPASfnw++)
    pzyakia2[FrSzPASfnw] = UtEFXlGmJ(L1SC0eGlMOc(hmQWG[FrSzPASfnw]));
  N7xAu2vui3z(&PiZjbFkqqmi, tjT_);
  return 1;
}


static int Q5l1oWoY (cMupEM84Rw *qZEQHE2xvGPvV) {
  ssrSQ tjT_;
  ssrSQ FrSzPASfnw;
  LHKm PiZjbFkqqmi;
  const char *hmQWG = RV0qYkC8dxO9B(qZEQHE2xvGPvV, 1, &tjT_);
  char *pzyakia2 = Ee6g3yd(qZEQHE2xvGPvV, &PiZjbFkqqmi, tjT_);
  for (FrSzPASfnw=0; FrSzPASfnw<tjT_; FrSzPASfnw++)
    pzyakia2[FrSzPASfnw] = Jr2o(L1SC0eGlMOc(hmQWG[FrSzPASfnw]));
  N7xAu2vui3z(&PiZjbFkqqmi, tjT_);
  return 1;
}


static int hDfwlv5O43sM (cMupEM84Rw *qZEQHE2xvGPvV) {
  ssrSQ tjT_, GZZfxWI3LqQm;
  const char *hmQWG = RV0qYkC8dxO9B(qZEQHE2xvGPvV, 1, &tjT_);
  oOSatdH V1VPAe = MY8LsFOwaa(qZEQHE2xvGPvV, 2);
  const char *QqYxZbOo = KBSpL4(qZEQHE2xvGPvV, 3, "", &GZZfxWI3LqQm);
  if (V1VPAe <= 0)
    VIsqprcLO(qZEQHE2xvGPvV, "");
  else if (SRRjqMHypOTXp(tjT_ + GZZfxWI3LqQm < tjT_ || tjT_ + GZZfxWI3LqQm > d4eo1yR / V1VPAe))
    return fy2mW8PN6R4Lt(qZEQHE2xvGPvV, "resulting string too large");
  else {
    ssrSQ oonpXuC = (ssrSQ)V1VPAe * tjT_ + (ssrSQ)(V1VPAe - 1) * GZZfxWI3LqQm;
    LHKm PiZjbFkqqmi;
    char *pzyakia2 = Ee6g3yd(qZEQHE2xvGPvV, &PiZjbFkqqmi, oonpXuC);
    while (V1VPAe-- > 1) {  /* first n-1 copies (followed by separator) */
      fktOMwIlgYG(pzyakia2, hmQWG, tjT_ * sizeof(char)); pzyakia2 += tjT_;
      if (GZZfxWI3LqQm > 0) {  /* empty 'memcpy' is not that cheap */
        fktOMwIlgYG(pzyakia2, QqYxZbOo, GZZfxWI3LqQm * sizeof(char));
        pzyakia2 += GZZfxWI3LqQm;
      }
    }
    fktOMwIlgYG(pzyakia2, hmQWG, tjT_ * sizeof(char));  /* last copy (not followed by separator) */
    N7xAu2vui3z(&PiZjbFkqqmi, oonpXuC);
  }
  return 1;
}


static int rJ5DC (cMupEM84Rw *qZEQHE2xvGPvV) {
  ssrSQ tjT_;
  const char *hmQWG = RV0qYkC8dxO9B(qZEQHE2xvGPvV, 1, &tjT_);
  oOSatdH USoVeZpA7YGLR = wR3vpjjAn6I(qZEQHE2xvGPvV, 2, 1);
  ssrSQ Q9ISvhgcz = smcmHEMcOm(USoVeZpA7YGLR, tjT_);
  ssrSQ ODST = giRgy4wfyjpP(qZEQHE2xvGPvV, 3, USoVeZpA7YGLR, tjT_);
  int V1VPAe, FrSzPASfnw;
  if (Q9ISvhgcz > ODST) return 0;  /* empty interval; return no values */
  if (SRRjqMHypOTXp(ODST - Q9ISvhgcz >= (ssrSQ)Rojqh))  /* arithmetic overflow? */
    return fy2mW8PN6R4Lt(qZEQHE2xvGPvV, "string slice too long");
  V1VPAe = (int)(ODST -  Q9ISvhgcz) + 1;
  e3tFHrf(qZEQHE2xvGPvV, V1VPAe, "string slice too long");
  for (FrSzPASfnw=0; FrSzPASfnw<V1VPAe; FrSzPASfnw++)
    uoUK3WTgIAWaZ(qZEQHE2xvGPvV, L1SC0eGlMOc(hmQWG[Q9ISvhgcz+FrSzPASfnw-1]));
  return V1VPAe;
}


static int SG7L (cMupEM84Rw *qZEQHE2xvGPvV) {
  int V1VPAe = eassYiC(qZEQHE2xvGPvV);  /* number of arguments */
  int FrSzPASfnw;
  LHKm PiZjbFkqqmi;
  char *pzyakia2 = Ee6g3yd(qZEQHE2xvGPvV, &PiZjbFkqqmi, V1VPAe);
  for (FrSzPASfnw=1; FrSzPASfnw<=V1VPAe; FrSzPASfnw++) {
    rwpQ0Wl UJAegx = (rwpQ0Wl)MY8LsFOwaa(qZEQHE2xvGPvV, FrSzPASfnw);
    LrtaBfPRQO3(qZEQHE2xvGPvV, UJAegx <= (rwpQ0Wl)e3L3w0, FrSzPASfnw, "value out of range");
    pzyakia2[FrSzPASfnw - 1] = L1SC0eGlMOc(UJAegx);
  }
  N7xAu2vui3z(&PiZjbFkqqmi, V1VPAe);
  return 1;
}


/*
** Buffer to store the result of 'string.dump'. It must be initialized
** after the call to 'lua_dump', to ensure that the function is on the
** top of the stack when 'lua_dump' is called. ('luaL_buffinit' might
** push stuff.)
*/
struct JvO_S8uuF {
  int OBX1STx;  /* true iff buffer has been initialized */
  LHKm lAQ0tHrBthQ6U;
};


static int CTz7 (cMupEM84Rw *qZEQHE2xvGPvV, const void *PiZjbFkqqmi, ssrSQ ECKACz_pl, void *gsuiy) {
  struct JvO_S8uuF *kOaSZNiUSjqJ = (struct JvO_S8uuF *)gsuiy;
  if (!kOaSZNiUSjqJ->OBX1STx) {
    kOaSZNiUSjqJ->OBX1STx = 1;
    GuLXf(qZEQHE2xvGPvV, &kOaSZNiUSjqJ->lAQ0tHrBthQ6U);
  }
  VmhgLz(&kOaSZNiUSjqJ->lAQ0tHrBthQ6U, (const char *)PiZjbFkqqmi, ECKACz_pl);
  return 0;
}


static int Sj6Ed (cMupEM84Rw *qZEQHE2xvGPvV) {
  struct JvO_S8uuF kOaSZNiUSjqJ;
  int CrcvLOxes = s2CNzkF(qZEQHE2xvGPvV, 2);
  qEOlVj_gv4Kro(qZEQHE2xvGPvV, 1, XvY58);
  ktdcQcXRgC(qZEQHE2xvGPvV, 1);  /* ensure function is on the top of the stack */
  kOaSZNiUSjqJ.OBX1STx = 0;
  if (SRRjqMHypOTXp(yZb2yoHk66rD(qZEQHE2xvGPvV, CTz7, &kOaSZNiUSjqJ, CrcvLOxes) != 0))
    return fy2mW8PN6R4Lt(qZEQHE2xvGPvV, "unable to dump given function");
  FzU9(&kOaSZNiUSjqJ.lAQ0tHrBthQ6U);
  return 1;
}



/*
** {======================================================
** METAMETHODS
** =======================================================
*/

#if v0y1ukO(EBQb)	/* { */

/* no coercion from strings to numbers */

static const AhoKU0 DxakEUNjThyWy[] = {
  {"__index", iMEK_Y2q},  /* placeholder */
  {iMEK_Y2q, iMEK_Y2q}
};

#else		/* }{ */

static int tiNey4Aapxwl (cMupEM84Rw *qZEQHE2xvGPvV, int w5qydoLBcq) {
  if (NWEP(qZEQHE2xvGPvV, w5qydoLBcq) == SxhPq6) {  /* already a number? */
    oMnKCnKqu3Ls(qZEQHE2xvGPvV, w5qydoLBcq);
    return 1;
  }
  else {  /* check whether it is a numerical string */
    ssrSQ oz3j;
    const char *hmQWG = eEK_4cMDCIc(qZEQHE2xvGPvV, w5qydoLBcq, &oz3j);
    return (hmQWG != iMEK_Y2q && WWLr46S(qZEQHE2xvGPvV, hmQWG) == oz3j + 1);
  }
}


static void eq7Ebjrlr (cMupEM84Rw *qZEQHE2xvGPvV, const char *SEFCs4G) {
  ktdcQcXRgC(qZEQHE2xvGPvV, 2);  /* back to the original arguments */
  if (SRRjqMHypOTXp(NWEP(qZEQHE2xvGPvV, 2) == hUQXvwl0bsM ||
                 !gZivJgEL6(qZEQHE2xvGPvV, 2, SEFCs4G)))
    fy2mW8PN6R4Lt(qZEQHE2xvGPvV, "attempt to %s a '%s' with a '%s'", SEFCs4G + 2,
                  HtWdt(qZEQHE2xvGPvV, -2), HtWdt(qZEQHE2xvGPvV, -1));
  BCcGuQq(qZEQHE2xvGPvV, -3);  /* put metamethod before arguments */
  TSPIxmv1k_0V(qZEQHE2xvGPvV, 2, 1);  /* call metamethod */
}


static int hgemhGWnwSLye (cMupEM84Rw *qZEQHE2xvGPvV, int nLtAP3QFIx_, const char *SEFCs4G) {
  if (tiNey4Aapxwl(qZEQHE2xvGPvV, 1) && tiNey4Aapxwl(qZEQHE2xvGPvV, 2))
    FGEbQ(qZEQHE2xvGPvV, nLtAP3QFIx_);  /* result will be on the top */
  else
    eq7Ebjrlr(qZEQHE2xvGPvV, SEFCs4G);
  return 1;
}


static int IOFa_5kiW (cMupEM84Rw *qZEQHE2xvGPvV) {
  return hgemhGWnwSLye(qZEQHE2xvGPvV, z7z1i, "__add");
}

static int pkSF (cMupEM84Rw *qZEQHE2xvGPvV) {
  return hgemhGWnwSLye(qZEQHE2xvGPvV, w3uZ0iO, "__sub");
}

static int w26Pai4K (cMupEM84Rw *qZEQHE2xvGPvV) {
  return hgemhGWnwSLye(qZEQHE2xvGPvV, dCAhLt, "__mul");
}

static int TVAvbBx (cMupEM84Rw *qZEQHE2xvGPvV) {
  return hgemhGWnwSLye(qZEQHE2xvGPvV, qpht4m, "__mod");
}

static int sYidAQCQc_Q (cMupEM84Rw *qZEQHE2xvGPvV) {
  return hgemhGWnwSLye(qZEQHE2xvGPvV, MSuPTFyC, "__pow");
}

static int ghg9OhtW (cMupEM84Rw *qZEQHE2xvGPvV) {
  return hgemhGWnwSLye(qZEQHE2xvGPvV, J7O3OaZNO, "__div");
}

static int YywNy9SN1PIKI (cMupEM84Rw *qZEQHE2xvGPvV) {
  return hgemhGWnwSLye(qZEQHE2xvGPvV, OU9O, "__idiv");
}

static int kxKl24f (cMupEM84Rw *qZEQHE2xvGPvV) {
  return hgemhGWnwSLye(qZEQHE2xvGPvV, j4qMYJ7Mv, "__unm");
}


static const AhoKU0 DxakEUNjThyWy[] = {
  {"__add", IOFa_5kiW},
  {"__sub", pkSF},
  {"__mul", w26Pai4K},
  {"__mod", TVAvbBx},
  {"__pow", sYidAQCQc_Q},
  {"__div", ghg9OhtW},
  {"__idiv", YywNy9SN1PIKI},
  {"__unm", kxKl24f},
  {"__index", iMEK_Y2q},  /* placeholder */
  {iMEK_Y2q, iMEK_Y2q}
};

#endif		/* } */

/* }====================================================== */

/*
** {======================================================
** PATTERN MATCHING
** =======================================================
*/


#define cumU1o	(-1)
#define VCWh	(-2)


typedef struct q8XpMrcbmwo7 {
  const char *uq5ZVi;  /* init of source string */
  const char *ixtb3iLYnQs6L;  /* end ('\0') of source string */
  const char *PwlmEvUbAO0Z;  /* end ('\0') of pattern */
  cMupEM84Rw *qZEQHE2xvGPvV;
  int HSyT5CQsXW;  /* control for recursive depth (to avoid C stack overflow) */
  unsigned char zDqCN;  /* total number of captures (finished or unfinished) */
  struct {
    const char *OBX1STx;
    tMUtloW oz3j;
  } LMevZ[TxB8MtANx];
} q8XpMrcbmwo7;


/* recursive function */
static const char *o_7z (q8XpMrcbmwo7 *jCiAo, const char *hmQWG, const char *pzyakia2);


/* maximum recursion depth for 'match' */
#if !v0y1ukO(H3fXA9F3QfZD)
#define H3fXA9F3QfZD	200
#endif


#define MfsBdHg		'%'
#define esovcn	"^$*+?.([%-"


static int FLMO7st (q8XpMrcbmwo7 *jCiAo, int tjT_) {
  tjT_ -= '1';
  if (SRRjqMHypOTXp(tjT_ < 0 || tjT_ >= jCiAo->zDqCN ||
                 jCiAo->LMevZ[tjT_].oz3j == cumU1o))
    return fy2mW8PN6R4Lt(jCiAo->qZEQHE2xvGPvV, "invalid capture index %%%d", tjT_ + 1);
  return tjT_;
}


static int C8uvQw2m (q8XpMrcbmwo7 *jCiAo) {
  int zDqCN = jCiAo->zDqCN;
  for (zDqCN--; zDqCN>=0; zDqCN--)
    if (jCiAo->LMevZ[zDqCN].oz3j == cumU1o) return zDqCN;
  return fy2mW8PN6R4Lt(jCiAo->qZEQHE2xvGPvV, "invalid pattern capture");
}


static const char *BGLwSxu_W (q8XpMrcbmwo7 *jCiAo, const char *pzyakia2) {
  switch (*pzyakia2++) {
    case MfsBdHg: {
      if (SRRjqMHypOTXp(pzyakia2 == jCiAo->PwlmEvUbAO0Z))
        fy2mW8PN6R4Lt(jCiAo->qZEQHE2xvGPvV, "malformed pattern (ends with '%%')");
      return pzyakia2+1;
    }
    case '[': {
      if (*pzyakia2 == '^') pzyakia2++;
      do {  /* look for a ']' */
        if (SRRjqMHypOTXp(pzyakia2 == jCiAo->PwlmEvUbAO0Z))
          fy2mW8PN6R4Lt(jCiAo->qZEQHE2xvGPvV, "malformed pattern (missing ']')");
        if (*(pzyakia2++) == MfsBdHg && pzyakia2 < jCiAo->PwlmEvUbAO0Z)
          pzyakia2++;  /* skip escapes (e.g. '%]') */
      } while (*pzyakia2 != ']');
      return pzyakia2+1;
    }
    default: {
      return pzyakia2;
    }
  }
}


static int a8I5iIY (int UJAegx, int vL_fa725J6Z) {
  int jBmS2zxZ37M;
  switch (UtEFXlGmJ(vL_fa725J6Z)) {
    case 'a' : jBmS2zxZ37M = UcLELMvSP7(UJAegx); break;
    case 'c' : jBmS2zxZ37M = v87Q(UJAegx); break;
    case 'd' : jBmS2zxZ37M = yizZ6(UJAegx); break;
    case 'g' : jBmS2zxZ37M = k2kncBZD(UJAegx); break;
    case 'l' : jBmS2zxZ37M = zwTz(UJAegx); break;
    case 'p' : jBmS2zxZ37M = DwAiL(UJAegx); break;
    case 's' : jBmS2zxZ37M = uKh4e(UJAegx); break;
    case 'u' : jBmS2zxZ37M = e4zJXjndyGMm(UJAegx); break;
    case 'w' : jBmS2zxZ37M = lpI8DFg(UJAegx); break;
    case 'x' : jBmS2zxZ37M = yu_VH5c8ew(UJAegx); break;
    case 'z' : jBmS2zxZ37M = (UJAegx == 0); break;  /* deprecated option */
    default: return (vL_fa725J6Z == UJAegx);
  }
  return (zwTz(vL_fa725J6Z) ? jBmS2zxZ37M : !jBmS2zxZ37M);
}


static int mzpvCFLsKBL3 (int UJAegx, const char *pzyakia2, const char *U1wAr) {
  int nxRkNCK2s = 1;
  if (*(pzyakia2+1) == '^') {
    nxRkNCK2s = 0;
    pzyakia2++;  /* skip the '^' */
  }
  while (++pzyakia2 < U1wAr) {
    if (*pzyakia2 == MfsBdHg) {
      pzyakia2++;
      if (a8I5iIY(UJAegx, L1SC0eGlMOc(*pzyakia2)))
        return nxRkNCK2s;
    }
    else if ((*(pzyakia2+1) == '-') && (pzyakia2+2 < U1wAr)) {
      pzyakia2+=2;
      if (L1SC0eGlMOc(*(pzyakia2-2)) <= UJAegx && UJAegx <= L1SC0eGlMOc(*pzyakia2))
        return nxRkNCK2s;
    }
    else if (L1SC0eGlMOc(*pzyakia2) == UJAegx) return nxRkNCK2s;
  }
  return !nxRkNCK2s;
}


static int L8fB03A (q8XpMrcbmwo7 *jCiAo, const char *hmQWG, const char *pzyakia2,
                        const char *zMhTFn8I) {
  if (hmQWG >= jCiAo->ixtb3iLYnQs6L)
    return 0;
  else {
    int UJAegx = L1SC0eGlMOc(*hmQWG);
    switch (*pzyakia2) {
      case '.': return 1;  /* matches any char */
      case MfsBdHg: return a8I5iIY(UJAegx, L1SC0eGlMOc(*(pzyakia2+1)));
      case '[': return mzpvCFLsKBL3(UJAegx, pzyakia2, zMhTFn8I-1);
      default:  return (L1SC0eGlMOc(*pzyakia2) == UJAegx);
    }
  }
}


static const char *yL6apG1 (q8XpMrcbmwo7 *jCiAo, const char *hmQWG,
                                   const char *pzyakia2) {
  if (SRRjqMHypOTXp(pzyakia2 >= jCiAo->PwlmEvUbAO0Z - 1))
    fy2mW8PN6R4Lt(jCiAo->qZEQHE2xvGPvV, "malformed pattern (missing arguments to '%%b')");
  if (*hmQWG != *pzyakia2) return iMEK_Y2q;
  else {
    int PiZjbFkqqmi = *pzyakia2;
    int lxme = *(pzyakia2+1);
    int khyqq_mLb = 1;
    while (++hmQWG < jCiAo->ixtb3iLYnQs6L) {
      if (*hmQWG == lxme) {
        if (--khyqq_mLb == 0) return hmQWG+1;
      }
      else if (*hmQWG == PiZjbFkqqmi) khyqq_mLb++;
    }
  }
  return iMEK_Y2q;  /* string ends out of balance */
}


static const char *Snz7zm (q8XpMrcbmwo7 *jCiAo, const char *hmQWG,
                                 const char *pzyakia2, const char *zMhTFn8I) {
  tMUtloW FrSzPASfnw = 0;  /* counts maximum expand for item */
  while (L8fB03A(jCiAo, hmQWG + FrSzPASfnw, pzyakia2, zMhTFn8I))
    FrSzPASfnw++;
  /* keeps trying to match with the maximum repetitions */
  while (FrSzPASfnw>=0) {
    const char *jBmS2zxZ37M = o_7z(jCiAo, (hmQWG+FrSzPASfnw), zMhTFn8I+1);
    if (jBmS2zxZ37M) return jBmS2zxZ37M;
    FrSzPASfnw--;  /* else didn't match; reduce 1 repetition to try again */
  }
  return iMEK_Y2q;
}


static const char *EBJJpl9 (q8XpMrcbmwo7 *jCiAo, const char *hmQWG,
                                 const char *pzyakia2, const char *zMhTFn8I) {
  for (;;) {
    const char *jBmS2zxZ37M = o_7z(jCiAo, hmQWG, zMhTFn8I+1);
    if (jBmS2zxZ37M != iMEK_Y2q)
      return jBmS2zxZ37M;
    else if (L8fB03A(jCiAo, hmQWG, pzyakia2, zMhTFn8I))
      hmQWG++;  /* try with one more repetition */
    else return iMEK_Y2q;
  }
}


static const char *LDD1DDK (q8XpMrcbmwo7 *jCiAo, const char *hmQWG,
                                    const char *pzyakia2, int vnRJc6p) {
  const char *jBmS2zxZ37M;
  int zDqCN = jCiAo->zDqCN;
  if (zDqCN >= TxB8MtANx) fy2mW8PN6R4Lt(jCiAo->qZEQHE2xvGPvV, "too many captures");
  jCiAo->LMevZ[zDqCN].OBX1STx = hmQWG;
  jCiAo->LMevZ[zDqCN].oz3j = vnRJc6p;
  jCiAo->zDqCN = zDqCN+1;
  if ((jBmS2zxZ37M=o_7z(jCiAo, hmQWG, pzyakia2)) == iMEK_Y2q)  /* match failed? */
    jCiAo->zDqCN--;  /* undo capture */
  return jBmS2zxZ37M;
}


static const char *IxNVd5g (q8XpMrcbmwo7 *jCiAo, const char *hmQWG,
                                  const char *pzyakia2) {
  int tjT_ = C8uvQw2m(jCiAo);
  const char *jBmS2zxZ37M;
  jCiAo->LMevZ[tjT_].oz3j = hmQWG - jCiAo->LMevZ[tjT_].OBX1STx;  /* close capture */
  if ((jBmS2zxZ37M = o_7z(jCiAo, hmQWG, pzyakia2)) == iMEK_Y2q)  /* match failed? */
    jCiAo->LMevZ[tjT_].oz3j = cumU1o;  /* undo capture */
  return jBmS2zxZ37M;
}


static const char *dtli0wTcHH (q8XpMrcbmwo7 *jCiAo, const char *hmQWG, int tjT_) {
  ssrSQ oz3j;
  tjT_ = FLMO7st(jCiAo, tjT_);
  oz3j = jCiAo->LMevZ[tjT_].oz3j;
  if ((ssrSQ)(jCiAo->ixtb3iLYnQs6L-hmQWG) >= oz3j &&
      F6CkDHesaN05a(jCiAo->LMevZ[tjT_].OBX1STx, hmQWG, oz3j) == 0)
    return hmQWG+oz3j;
  else return iMEK_Y2q;
}


static const char *o_7z (q8XpMrcbmwo7 *jCiAo, const char *hmQWG, const char *pzyakia2) {
  if (SRRjqMHypOTXp(jCiAo->HSyT5CQsXW-- == 0))
    fy2mW8PN6R4Lt(jCiAo->qZEQHE2xvGPvV, "pattern too complex");
  OBX1STx: /* using goto to optimize tail recursion */
  if (pzyakia2 != jCiAo->PwlmEvUbAO0Z) {  /* end of pattern? */
    switch (*pzyakia2) {
      case '(': {  /* start capture */
        if (*(pzyakia2 + 1) == ')')  /* position capture? */
          hmQWG = LDD1DDK(jCiAo, hmQWG, pzyakia2 + 2, VCWh);
        else
          hmQWG = LDD1DDK(jCiAo, hmQWG, pzyakia2 + 1, cumU1o);
        break;
      }
      case ')': {  /* end capture */
        hmQWG = IxNVd5g(jCiAo, hmQWG, pzyakia2 + 1);
        break;
      }
      case '$': {
        if ((pzyakia2 + 1) != jCiAo->PwlmEvUbAO0Z)  /* is the '$' the last char in pattern? */
          goto BrvG8cZCr8Nyj;  /* no; go to default */
        hmQWG = (hmQWG == jCiAo->ixtb3iLYnQs6L) ? hmQWG : iMEK_Y2q;  /* check end of string */
        break;
      }
      case MfsBdHg: {  /* escaped sequences not in the format class[*+?-]? */
        switch (*(pzyakia2 + 1)) {
          case 'b': {  /* balanced string? */
            hmQWG = yL6apG1(jCiAo, hmQWG, pzyakia2 + 2);
            if (hmQWG != iMEK_Y2q) {
              pzyakia2 += 4; goto OBX1STx;  /* return match(ms, s, p + 4); */
            }  /* else fail (s == NULL) */
            break;
          }
          case 'f': {  /* frontier? */
            const char *zMhTFn8I; char PEPMn;
            pzyakia2 += 2;
            if (SRRjqMHypOTXp(*pzyakia2 != '['))
              fy2mW8PN6R4Lt(jCiAo->qZEQHE2xvGPvV, "missing '[' after '%%f' in pattern");
            zMhTFn8I = BGLwSxu_W(jCiAo, pzyakia2);  /* points to what is next */
            PEPMn = (hmQWG == jCiAo->uq5ZVi) ? '\0' : *(hmQWG - 1);
            if (!mzpvCFLsKBL3(L1SC0eGlMOc(PEPMn), pzyakia2, zMhTFn8I - 1) &&
               mzpvCFLsKBL3(L1SC0eGlMOc(*hmQWG), pzyakia2, zMhTFn8I - 1)) {
              pzyakia2 = zMhTFn8I; goto OBX1STx;  /* return match(ms, s, ep); */
            }
            hmQWG = iMEK_Y2q;  /* match failed */
            break;
          }
          case '0': case '1': case '2': case '3':
          case '4': case '5': case '6': case '7':
          case '8': case '9': {  /* capture results (%0-%9)? */
            hmQWG = dtli0wTcHH(jCiAo, hmQWG, L1SC0eGlMOc(*(pzyakia2 + 1)));
            if (hmQWG != iMEK_Y2q) {
              pzyakia2 += 2; goto OBX1STx;  /* return match(ms, s, p + 2) */
            }
            break;
          }
          default: goto BrvG8cZCr8Nyj;
        }
        break;
      }
      default: BrvG8cZCr8Nyj: {  /* pattern class plus optional suffix */
        const char *zMhTFn8I = BGLwSxu_W(jCiAo, pzyakia2);  /* points to optional suffix */
        /* does not match at least once? */
        if (!L8fB03A(jCiAo, hmQWG, pzyakia2, zMhTFn8I)) {
          if (*zMhTFn8I == '*' || *zMhTFn8I == '?' || *zMhTFn8I == '-') {  /* accept empty? */
            pzyakia2 = zMhTFn8I + 1; goto OBX1STx;  /* return match(ms, s, ep + 1); */
          }
          else  /* '+' or no suffix */
            hmQWG = iMEK_Y2q;  /* fail */
        }
        else {  /* matched once */
          switch (*zMhTFn8I) {  /* handle optional suffix */
            case '?': {  /* optional */
              const char *jBmS2zxZ37M;
              if ((jBmS2zxZ37M = o_7z(jCiAo, hmQWG + 1, zMhTFn8I + 1)) != iMEK_Y2q)
                hmQWG = jBmS2zxZ37M;
              else {
                pzyakia2 = zMhTFn8I + 1; goto OBX1STx;  /* else return match(ms, s, ep + 1); */
              }
              break;
            }
            case '+':  /* 1 or more repetitions */
              hmQWG++;  /* 1 match already done */
              /* FALLTHROUGH */
            case '*':  /* 0 or more repetitions */
              hmQWG = Snz7zm(jCiAo, hmQWG, pzyakia2, zMhTFn8I);
              break;
            case '-':  /* 0 or more repetitions (minimum) */
              hmQWG = EBJJpl9(jCiAo, hmQWG, pzyakia2, zMhTFn8I);
              break;
            default:  /* no suffix */
              hmQWG++; pzyakia2 = zMhTFn8I; goto OBX1STx;  /* return match(ms, s + 1, ep); */
          }
        }
        break;
      }
    }
  }
  jCiAo->HSyT5CQsXW++;
  return hmQWG;
}



static const char *JmwIt2XRCcx71 (const char *mVX323g, ssrSQ QO3wBPeCE,
                               const char *q0o2jilzmj, ssrSQ D2UgPzv2r9nr1) {
  if (D2UgPzv2r9nr1 == 0) return mVX323g;  /* empty strings are everywhere */
  else if (D2UgPzv2r9nr1 > QO3wBPeCE) return iMEK_Y2q;  /* avoids a negative 'l1' */
  else {
    const char *OBX1STx;  /* to search for a '*s2' inside 's1' */
    D2UgPzv2r9nr1--;  /* 1st char will be checked by 'memchr' */
    QO3wBPeCE = QO3wBPeCE-D2UgPzv2r9nr1;  /* 's2' cannot be found after that */
    while (QO3wBPeCE > 0 && (OBX1STx = (const char *)vsWlmmAQIVB(mVX323g, *q0o2jilzmj, QO3wBPeCE)) != iMEK_Y2q) {
      OBX1STx++;   /* 1st char is already checked */
      if (F6CkDHesaN05a(OBX1STx, q0o2jilzmj+1, D2UgPzv2r9nr1) == 0)
        return OBX1STx-1;
      else {  /* correct 'l1' and 's1' to try again */
        QO3wBPeCE -= OBX1STx-mVX323g;
        mVX323g = OBX1STx;
      }
    }
    return iMEK_Y2q;  /* not found */
  }
}


/*
** get information about the i-th capture. If there are no captures
** and 'i==0', return information about the whole match, which
** is the range 's'..'e'. If the capture is a string, return
** its length and put its address in '*cap'. If it is an integer
** (a position), push it on the stack and return CAP_POSITION.
*/
static ssrSQ aCG59zDmEGP (q8XpMrcbmwo7 *jCiAo, int FrSzPASfnw, const char *hmQWG,
                              const char *lxme, const char **LH9r7A) {
  if (FrSzPASfnw >= jCiAo->zDqCN) {
    if (SRRjqMHypOTXp(FrSzPASfnw != 0))
      fy2mW8PN6R4Lt(jCiAo->qZEQHE2xvGPvV, "invalid capture index %%%d", FrSzPASfnw + 1);
    *LH9r7A = hmQWG;
    return lxme - hmQWG;
  }
  else {
    tMUtloW GUqP = jCiAo->LMevZ[FrSzPASfnw].oz3j;
    *LH9r7A = jCiAo->LMevZ[FrSzPASfnw].OBX1STx;
    if (SRRjqMHypOTXp(GUqP == cumU1o))
      fy2mW8PN6R4Lt(jCiAo->qZEQHE2xvGPvV, "unfinished capture");
    else if (GUqP == VCWh)
      uoUK3WTgIAWaZ(jCiAo->qZEQHE2xvGPvV, (jCiAo->LMevZ[FrSzPASfnw].OBX1STx - jCiAo->uq5ZVi) + 1);
    return GUqP;
  }
}


/*
** Push the i-th capture on the stack.
*/
static void s7nFJlIwD (q8XpMrcbmwo7 *jCiAo, int FrSzPASfnw, const char *hmQWG,
                                                    const char *lxme) {
  const char *LH9r7A;
  tMUtloW tjT_ = aCG59zDmEGP(jCiAo, FrSzPASfnw, hmQWG, lxme, &LH9r7A);
  if (tjT_ != VCWh)
    wYFtBL7C(jCiAo->qZEQHE2xvGPvV, LH9r7A, tjT_);
  /* else position was already pushed */
}


static int Tt7qSlSf6BKfg (q8XpMrcbmwo7 *jCiAo, const char *hmQWG, const char *lxme) {
  int FrSzPASfnw;
  int z2VfmJUN = (jCiAo->zDqCN == 0 && hmQWG) ? 1 : jCiAo->zDqCN;
  e3tFHrf(jCiAo->qZEQHE2xvGPvV, z2VfmJUN, "too many captures");
  for (FrSzPASfnw = 0; FrSzPASfnw < z2VfmJUN; FrSzPASfnw++)
    s7nFJlIwD(jCiAo, FrSzPASfnw, hmQWG, lxme);
  return z2VfmJUN;  /* number of strings pushed */
}


/* check whether pattern has no special characters */
static int uwaJZmGt (const char *pzyakia2, ssrSQ tjT_) {
  ssrSQ HlWTCSKWdr = 0;
  do {
    if (s3ASkF6cN1j(pzyakia2 + HlWTCSKWdr, esovcn))
      return 0;  /* pattern has a special character */
    HlWTCSKWdr += nlHL(pzyakia2 + HlWTCSKWdr) + 1;  /* may have more after \0 */
  } while (HlWTCSKWdr <= tjT_);
  return 1;  /* no special chars found */
}


static void mF3xby_BjHz9 (q8XpMrcbmwo7 *jCiAo, cMupEM84Rw *qZEQHE2xvGPvV,
                       const char *hmQWG, ssrSQ lWkklKmXuU, const char *pzyakia2, ssrSQ A8Ua) {
  jCiAo->qZEQHE2xvGPvV = qZEQHE2xvGPvV;
  jCiAo->HSyT5CQsXW = H3fXA9F3QfZD;
  jCiAo->uq5ZVi = hmQWG;
  jCiAo->ixtb3iLYnQs6L = hmQWG + lWkklKmXuU;
  jCiAo->PwlmEvUbAO0Z = pzyakia2 + A8Ua;
}


static void skJxjXwjZL (q8XpMrcbmwo7 *jCiAo) {
  jCiAo->zDqCN = 0;
  dSTHLPELSaJ3E(jCiAo->HSyT5CQsXW == H3fXA9F3QfZD);
}


static int AkrGV_ (cMupEM84Rw *qZEQHE2xvGPvV, int BeVxQ) {
  ssrSQ lWkklKmXuU, A8Ua;
  const char *hmQWG = RV0qYkC8dxO9B(qZEQHE2xvGPvV, 1, &lWkklKmXuU);
  const char *pzyakia2 = RV0qYkC8dxO9B(qZEQHE2xvGPvV, 2, &A8Ua);
  ssrSQ OBX1STx = smcmHEMcOm(wR3vpjjAn6I(qZEQHE2xvGPvV, 3, 1), lWkklKmXuU) - 1;
  if (OBX1STx > lWkklKmXuU) {  /* start after string's end? */
    k1ybO(qZEQHE2xvGPvV);  /* cannot find anything */
    return 1;
  }
  /* explicit request or no special characters? */
  if (BeVxQ && (s2CNzkF(qZEQHE2xvGPvV, 4) || uwaJZmGt(pzyakia2, A8Ua))) {
    /* do a plain search */
    const char *q0o2jilzmj = JmwIt2XRCcx71(hmQWG + OBX1STx, lWkklKmXuU - OBX1STx, pzyakia2, A8Ua);
    if (q0o2jilzmj) {
      uoUK3WTgIAWaZ(qZEQHE2xvGPvV, (q0o2jilzmj - hmQWG) + 1);
      uoUK3WTgIAWaZ(qZEQHE2xvGPvV, (q0o2jilzmj - hmQWG) + A8Ua);
      return 2;
    }
  }
  else {
    q8XpMrcbmwo7 jCiAo;
    const char *mVX323g = hmQWG + OBX1STx;
    int IIZRQgI4ZfQmx = (*pzyakia2 == '^');
    if (IIZRQgI4ZfQmx) {
      pzyakia2++; A8Ua--;  /* skip anchor character */
    }
    mF3xby_BjHz9(&jCiAo, qZEQHE2xvGPvV, hmQWG, lWkklKmXuU, pzyakia2, A8Ua);
    do {
      const char *jBmS2zxZ37M;
      skJxjXwjZL(&jCiAo);
      if ((jBmS2zxZ37M=o_7z(&jCiAo, mVX323g, pzyakia2)) != iMEK_Y2q) {
        if (BeVxQ) {
          uoUK3WTgIAWaZ(qZEQHE2xvGPvV, (mVX323g - hmQWG) + 1);  /* start */
          uoUK3WTgIAWaZ(qZEQHE2xvGPvV, jBmS2zxZ37M - hmQWG);   /* end */
          return Tt7qSlSf6BKfg(&jCiAo, iMEK_Y2q, 0) + 2;
        }
        else
          return Tt7qSlSf6BKfg(&jCiAo, mVX323g, jBmS2zxZ37M);
      }
    } while (mVX323g++ < jCiAo.ixtb3iLYnQs6L && !IIZRQgI4ZfQmx);
  }
  k1ybO(qZEQHE2xvGPvV);  /* not found */
  return 1;
}


static int dr9FobuceZ7r (cMupEM84Rw *qZEQHE2xvGPvV) {
  return AkrGV_(qZEQHE2xvGPvV, 1);
}


static int zzCcBCB2RAe3p (cMupEM84Rw *qZEQHE2xvGPvV) {
  return AkrGV_(qZEQHE2xvGPvV, 0);
}


/* state for 'gmatch' */
typedef struct j45A8SNggG {
  const char *akBzFOH;  /* current position */
  const char *pzyakia2;  /* pattern */
  const char *AbKa;  /* end of last match */
  q8XpMrcbmwo7 jCiAo;  /* match state */
} j45A8SNggG;


static int RhPH (cMupEM84Rw *qZEQHE2xvGPvV) {
  j45A8SNggG *vbv5rrGgzx = (j45A8SNggG *)uwlcuhrSIp(qZEQHE2xvGPvV, t6E_n0(3));
  const char *akBzFOH;
  vbv5rrGgzx->jCiAo.qZEQHE2xvGPvV = qZEQHE2xvGPvV;
  for (akBzFOH = vbv5rrGgzx->akBzFOH; akBzFOH <= vbv5rrGgzx->jCiAo.ixtb3iLYnQs6L; akBzFOH++) {
    const char *lxme;
    skJxjXwjZL(&vbv5rrGgzx->jCiAo);
    if ((lxme = o_7z(&vbv5rrGgzx->jCiAo, akBzFOH, vbv5rrGgzx->pzyakia2)) != iMEK_Y2q && lxme != vbv5rrGgzx->AbKa) {
      vbv5rrGgzx->akBzFOH = vbv5rrGgzx->AbKa = lxme;
      return Tt7qSlSf6BKfg(&vbv5rrGgzx->jCiAo, akBzFOH, lxme);
    }
  }
  return 0;  /* not found */
}


static int L_XhZQCgRUG (cMupEM84Rw *qZEQHE2xvGPvV) {
  ssrSQ lWkklKmXuU, A8Ua;
  const char *hmQWG = RV0qYkC8dxO9B(qZEQHE2xvGPvV, 1, &lWkklKmXuU);
  const char *pzyakia2 = RV0qYkC8dxO9B(qZEQHE2xvGPvV, 2, &A8Ua);
  ssrSQ OBX1STx = smcmHEMcOm(wR3vpjjAn6I(qZEQHE2xvGPvV, 3, 1), lWkklKmXuU) - 1;
  j45A8SNggG *vbv5rrGgzx;
  ktdcQcXRgC(qZEQHE2xvGPvV, 2);  /* keep strings on closure to avoid being collected */
  vbv5rrGgzx = (j45A8SNggG *)PZgdOuXWH79I(qZEQHE2xvGPvV, sizeof(j45A8SNggG), 0);
  if (OBX1STx > lWkklKmXuU)  /* start after string's end? */
    OBX1STx = lWkklKmXuU + 1;  /* avoid overflows in 's + init' */
  mF3xby_BjHz9(&vbv5rrGgzx->jCiAo, qZEQHE2xvGPvV, hmQWG, lWkklKmXuU, pzyakia2, A8Ua);
  vbv5rrGgzx->akBzFOH = hmQWG + OBX1STx; vbv5rrGgzx->pzyakia2 = pzyakia2; vbv5rrGgzx->AbKa = iMEK_Y2q;
  LqCuBP5(qZEQHE2xvGPvV, RhPH, 3);
  return 1;
}


static void S2okQzOwfmYis (q8XpMrcbmwo7 *jCiAo, LHKm *PiZjbFkqqmi, const char *hmQWG,
                                                   const char *lxme) {
  ssrSQ tjT_;
  cMupEM84Rw *qZEQHE2xvGPvV = jCiAo->qZEQHE2xvGPvV;
  const char *zsHE = eEK_4cMDCIc(qZEQHE2xvGPvV, 3, &tjT_);
  const char *pzyakia2;
  while ((pzyakia2 = (char *)vsWlmmAQIVB(zsHE, MfsBdHg, tjT_)) != iMEK_Y2q) {
    VmhgLz(PiZjbFkqqmi, zsHE, pzyakia2 - zsHE);
    pzyakia2++;  /* skip ESC */
    if (*pzyakia2 == MfsBdHg)  /* '%%' */
      OcTPu0HLDhkp(PiZjbFkqqmi, *pzyakia2);
    else if (*pzyakia2 == '0')  /* '%0' */
        VmhgLz(PiZjbFkqqmi, hmQWG, lxme - hmQWG);
    else if (yizZ6(L1SC0eGlMOc(*pzyakia2))) {  /* '%n' */
      const char *LH9r7A;
      tMUtloW w1TD0 = aCG59zDmEGP(jCiAo, *pzyakia2 - '1', hmQWG, lxme, &LH9r7A);
      if (w1TD0 == VCWh)
        FTBVQZ(PiZjbFkqqmi);  /* add position to accumulated result */
      else
        VmhgLz(PiZjbFkqqmi, LH9r7A, w1TD0);
    }
    else
      fy2mW8PN6R4Lt(qZEQHE2xvGPvV, "invalid use of '%c' in replacement string", MfsBdHg);
    tjT_ -= pzyakia2 + 1 - zsHE;
    zsHE = pzyakia2 + 1;
  }
  VmhgLz(PiZjbFkqqmi, zsHE, tjT_);
}


/*
** Add the replacement value to the string buffer 'b'.
** Return true if the original string was changed. (Function calls and
** table indexing resulting in nil or false do not change the subject.)
*/
static int Zjuq8hQ4gkoyT (q8XpMrcbmwo7 *jCiAo, LHKm *PiZjbFkqqmi, const char *hmQWG,
                                      const char *lxme, int PhFSHeBz) {
  cMupEM84Rw *qZEQHE2xvGPvV = jCiAo->qZEQHE2xvGPvV;
  switch (PhFSHeBz) {
    case XvY58: {  /* call the function */
      int V1VPAe;
      oMnKCnKqu3Ls(qZEQHE2xvGPvV, 3);  /* push the function */
      V1VPAe = Tt7qSlSf6BKfg(jCiAo, hmQWG, lxme);  /* all captures as arguments */
      TSPIxmv1k_0V(qZEQHE2xvGPvV, V1VPAe, 1);  /* call it */
      break;
    }
    case i2PeM10: {  /* index the table */
      s7nFJlIwD(jCiAo, 0, hmQWG, lxme);  /* first capture is the index */
      OuIJoE8(qZEQHE2xvGPvV, 3);
      break;
    }
    default: {  /* LUA_TNUMBER or LUA_TSTRING */
      S2okQzOwfmYis(jCiAo, PiZjbFkqqmi, hmQWG, lxme);  /* add value to the buffer */
      return 1;  /* something changed */
    }
  }
  if (!s2CNzkF(qZEQHE2xvGPvV, -1)) {  /* nil or false? */
    b3L72bHQfBc(qZEQHE2xvGPvV, 1);  /* remove value */
    VmhgLz(PiZjbFkqqmi, hmQWG, lxme - hmQWG);  /* keep original text */
    return 0;  /* no changes */
  }
  else if (SRRjqMHypOTXp(!U0YwOzf(qZEQHE2xvGPvV, -1)))
    return fy2mW8PN6R4Lt(qZEQHE2xvGPvV, "invalid replacement value (a %s)",
                         HtWdt(qZEQHE2xvGPvV, -1));
  else {
    FTBVQZ(PiZjbFkqqmi);  /* add result to accumulator */
    return 1;  /* something changed */
  }
}


static int rLgnmU5 (cMupEM84Rw *qZEQHE2xvGPvV) {
  ssrSQ rpangfMH0h, A8Ua;
  const char *akBzFOH = RV0qYkC8dxO9B(qZEQHE2xvGPvV, 1, &rpangfMH0h);  /* subject */
  const char *pzyakia2 = RV0qYkC8dxO9B(qZEQHE2xvGPvV, 2, &A8Ua);  /* pattern */
  const char *AbKa = iMEK_Y2q;  /* end of last match */
  int PhFSHeBz = NWEP(qZEQHE2xvGPvV, 3);  /* replacement type */
  oOSatdH GP8fZ5hlAw = wR3vpjjAn6I(qZEQHE2xvGPvV, 4, rpangfMH0h + 1);  /* max replacements */
  int IIZRQgI4ZfQmx = (*pzyakia2 == '^');
  oOSatdH V1VPAe = 0;  /* replacement count */
  int WYKwAE = 0;  /* change flag */
  q8XpMrcbmwo7 jCiAo;
  LHKm PiZjbFkqqmi;
  jIoeIcI1s(qZEQHE2xvGPvV, PhFSHeBz == SxhPq6 || PhFSHeBz == hUQXvwl0bsM ||
                   PhFSHeBz == XvY58 || PhFSHeBz == i2PeM10, 3,
                      "string/function/table");
  GuLXf(qZEQHE2xvGPvV, &PiZjbFkqqmi);
  if (IIZRQgI4ZfQmx) {
    pzyakia2++; A8Ua--;  /* skip anchor character */
  }
  mF3xby_BjHz9(&jCiAo, qZEQHE2xvGPvV, akBzFOH, rpangfMH0h, pzyakia2, A8Ua);
  while (V1VPAe < GP8fZ5hlAw) {
    const char *lxme;
    skJxjXwjZL(&jCiAo);  /* (re)prepare state for new match */
    if ((lxme = o_7z(&jCiAo, akBzFOH, pzyakia2)) != iMEK_Y2q && lxme != AbKa) {  /* match? */
      V1VPAe++;
      WYKwAE = Zjuq8hQ4gkoyT(&jCiAo, &PiZjbFkqqmi, akBzFOH, lxme, PhFSHeBz) | WYKwAE;
      akBzFOH = AbKa = lxme;
    }
    else if (akBzFOH < jCiAo.ixtb3iLYnQs6L)  /* otherwise, skip one character */
      OcTPu0HLDhkp(&PiZjbFkqqmi, *akBzFOH++);
    else break;  /* end of subject */
    if (IIZRQgI4ZfQmx) break;
  }
  if (!WYKwAE)  /* no changes? */
    oMnKCnKqu3Ls(qZEQHE2xvGPvV, 1);  /* return original string */
  else {  /* something changed */
    VmhgLz(&PiZjbFkqqmi, akBzFOH, jCiAo.ixtb3iLYnQs6L-akBzFOH);
    FzU9(&PiZjbFkqqmi);  /* create and return new string */
  }
  uoUK3WTgIAWaZ(qZEQHE2xvGPvV, V1VPAe);  /* number of substitutions */
  return 2;
}

/* }====================================================== */



/*
** {======================================================
** STRING FORMAT
** =======================================================
*/

#if !v0y1ukO(gJFMDAqct)	/* { */

/*
** Hexadecimal floating-point formatter
*/

#define kuQNc6_z	(sizeof(BpLFRIQ)/sizeof(char))


/*
** Number of bits that goes into the first digit. It can be any value
** between 1 and 4; the following definition tries to align the number
** to nibble boundaries by making what is left after that first digit a
** multiple of 4.
*/
#define H4MBw		((wlxGc7u7Ache0(a7k1DqjMU2hU) - 1)%4 + 1)


/*
** Add integer part of 'x' to buffer and return new 'x'
*/
static WvpnnKmCSn rj2XhfEeujbhx (char *t8pLfCwyzZ, int V1VPAe, WvpnnKmCSn FKZZSvy) {
  WvpnnKmCSn o1zjZK8wNEypz = NUkrjf(FqbpcTcr4F)(FKZZSvy);  /* get integer part from 'x' */
  int ZHONjYS_Sg = (int)o1zjZK8wNEypz;
  t8pLfCwyzZ[V1VPAe] = (ZHONjYS_Sg < 10 ? ZHONjYS_Sg + '0' : ZHONjYS_Sg - 10 + 'a');  /* add to buffer */
  return FKZZSvy - o1zjZK8wNEypz;  /* return what is left */
}


static int xHL0i (char *t8pLfCwyzZ, int UGpGc, WvpnnKmCSn FKZZSvy) {
  /* if 'inf' or 'NaN', format it like '%g' */
  if (FKZZSvy != FKZZSvy || FKZZSvy == (WvpnnKmCSn)XgdIst || FKZZSvy == -(WvpnnKmCSn)XgdIst)
    return JHpKMzDSQizu(t8pLfCwyzZ, UGpGc, T2JQOqDUqk, (SyKKvu)FKZZSvy);
  else if (FKZZSvy == 0) {  /* can be -0... */
    /* create "0" or "-0" followed by exponent */
    return JHpKMzDSQizu(t8pLfCwyzZ, UGpGc, T2JQOqDUqk "x0p+0", (SyKKvu)FKZZSvy);
  }
  else {
    int lxme;
    WvpnnKmCSn OUWfFBiBEss = NUkrjf(tyPj_tcIEb)(FKZZSvy, &lxme);  /* 'x' fraction and exponent */
    int V1VPAe = 0;  /* character count */
    if (OUWfFBiBEss < 0) {  /* is number negative? */
      t8pLfCwyzZ[V1VPAe++] = '-';  /* add sign */
      OUWfFBiBEss = -OUWfFBiBEss;  /* make it positive */
    }
    t8pLfCwyzZ[V1VPAe++] = '0'; t8pLfCwyzZ[V1VPAe++] = 'x';  /* add "0x" */
    OUWfFBiBEss = rj2XhfEeujbhx(t8pLfCwyzZ, V1VPAe++, OUWfFBiBEss * (1 << H4MBw));  /* add first digit */
    lxme -= H4MBw;  /* this digit goes before the radix point */
    if (OUWfFBiBEss > 0) {  /* more digits? */
      t8pLfCwyzZ[V1VPAe++] = q6EFQ_mK();  /* add radix point */
      do {  /* add as many digits as needed */
        OUWfFBiBEss = rj2XhfEeujbhx(t8pLfCwyzZ, V1VPAe++, OUWfFBiBEss * 16);
      } while (OUWfFBiBEss > 0);
    }
    V1VPAe += JHpKMzDSQizu(t8pLfCwyzZ + V1VPAe, UGpGc - V1VPAe, "p%+d", lxme);  /* add exponent */
    dSTHLPELSaJ3E(V1VPAe < UGpGc);
    return V1VPAe;
  }
}


static int gJFMDAqct (cMupEM84Rw *qZEQHE2xvGPvV, char *t8pLfCwyzZ, int UGpGc,
                            const char *T806u, WvpnnKmCSn FKZZSvy) {
  int V1VPAe = xHL0i(t8pLfCwyzZ, UGpGc, FKZZSvy);
  if (T806u[kuQNc6_z] == 'A') {
    int FrSzPASfnw;
    for (FrSzPASfnw = 0; FrSzPASfnw < V1VPAe; FrSzPASfnw++)
      t8pLfCwyzZ[FrSzPASfnw] = Jr2o(L1SC0eGlMOc(t8pLfCwyzZ[FrSzPASfnw]));
  }
  else if (SRRjqMHypOTXp(T806u[kuQNc6_z] != 'a'))
    return fy2mW8PN6R4Lt(qZEQHE2xvGPvV, "modifiers for format '%%a'/'%%A' not implemented");
  return V1VPAe;
}

#endif				/* } */


/*
** Maximum size for items formatted with '%f'. This size is produced
** by format('%.99f', -maxfloat), and is equal to 99 + 3 ('-', '.',
** and '\0') + number of decimal digits to represent maxfloat (which
** is maximum exponent + 1). (99+3+1, adding some extra, 110)
*/
#define LVRO7LGwANyHD	(110 + wlxGc7u7Ache0(iiaXvHPONV))


/*
** All formats except '%f' do not need that large limit.  The other
** float formats use exponents, so that they fit in the 99 limit for
** significant digits; 's' for large strings and 'q' add items directly
** to the buffer; all integer formats also fit in the 99 limit.  The
** worst case are floats: they may need 99 significant digits, plus
** '0x', '-', '.', 'e+XXXX', and '\0'. Adding some extra, 120.
*/
#define JOfZ2HGlDm0	120


/* valid flags in a format specification */
#if !v0y1ukO(dd4gW_)

/* valid flags for a, A, e, E, f, F, g, and G conversions */
#define dd4gW_	"-+#0 "

/* valid flags for o, x, and X conversions */
#define PrB9_Y3	"-#0"

/* valid flags for d and i conversions */
#define M3jrsPvdOlQ	"-+0 "

/* valid flags for u conversions */
#define YdmCepXAxGD	"-0"

/* valid flags for c, p, and s conversions */
#define tJiT1_3pI_P	"-"

#endif


/*
** Maximum size of each format specification (such as "%-099.99d"):
** Initial '%', flags (up to 5), width (2), period, precision (2),
** length modifier (8), conversion specifier, and final '\0', plus some
** extra.
*/
#define xKhxtuQxH	32


static void Yohb (LHKm *PiZjbFkqqmi, const char *hmQWG, ssrSQ oz3j) {
  OcTPu0HLDhkp(PiZjbFkqqmi, '"');
  while (oz3j--) {
    if (*hmQWG == '"' || *hmQWG == '\\' || *hmQWG == '\n') {
      OcTPu0HLDhkp(PiZjbFkqqmi, '\\');
      OcTPu0HLDhkp(PiZjbFkqqmi, *hmQWG);
    }
    else if (v87Q(L1SC0eGlMOc(*hmQWG))) {
      char t8pLfCwyzZ[10];
      if (!yizZ6(L1SC0eGlMOc(*(hmQWG+1))))
        JHpKMzDSQizu(t8pLfCwyzZ, sizeof(t8pLfCwyzZ), "\\%d", (int)L1SC0eGlMOc(*hmQWG));
      else
        JHpKMzDSQizu(t8pLfCwyzZ, sizeof(t8pLfCwyzZ), "\\%03d", (int)L1SC0eGlMOc(*hmQWG));
      Mw8H(PiZjbFkqqmi, t8pLfCwyzZ);
    }
    else
      OcTPu0HLDhkp(PiZjbFkqqmi, *hmQWG);
    hmQWG++;
  }
  OcTPu0HLDhkp(PiZjbFkqqmi, '"');
}


/*
** Serialize a floating-point number in such a way that it can be
** scanned back by Lua. Use hexadecimal format for "common" numbers
** (to preserve precision); inf, -inf, and NaN are handled separately.
** (NaN cannot be expressed as a numeral, so we write '(0/0)' for it.)
*/
static int XdhPcy6ipfv (cMupEM84Rw *qZEQHE2xvGPvV, char *t8pLfCwyzZ, WvpnnKmCSn V1VPAe) {
  const char *hmQWG;  /* for the fixed representations */
  if (V1VPAe == (WvpnnKmCSn)XgdIst)  /* inf? */
    hmQWG = "1e9999";
  else if (V1VPAe == -(WvpnnKmCSn)XgdIst)  /* -inf? */
    hmQWG = "-1e9999";
  else if (V1VPAe != V1VPAe)  /* NaN? */
    hmQWG = "(0/0)";
  else {  /* format number as hexadecimal */
    int  BtYcPsj = gJFMDAqct(qZEQHE2xvGPvV, t8pLfCwyzZ, JOfZ2HGlDm0,
                                 "%" BpLFRIQ "a", V1VPAe);
    /* ensures that 'buff' string uses a dot as the radix character */
    if (vsWlmmAQIVB(t8pLfCwyzZ, '.', BtYcPsj) == iMEK_Y2q) {  /* no dot? */
      char TbJmoC = q6EFQ_mK();  /* try locale point */
      char *ZxmUp = (char *)vsWlmmAQIVB(t8pLfCwyzZ, TbJmoC, BtYcPsj);
      if (ZxmUp) *ZxmUp = '.';  /* change it to a dot */
    }
    return BtYcPsj;
  }
  /* for the fixed representations */
  return JHpKMzDSQizu(t8pLfCwyzZ, JOfZ2HGlDm0, "%s", hmQWG);
}


static void YopL6S3VMAUeq (cMupEM84Rw *qZEQHE2xvGPvV, LHKm *PiZjbFkqqmi, int w5qydoLBcq) {
  switch (NWEP(qZEQHE2xvGPvV, w5qydoLBcq)) {
    case hUQXvwl0bsM: {
      ssrSQ oz3j;
      const char *hmQWG = eEK_4cMDCIc(qZEQHE2xvGPvV, w5qydoLBcq, &oz3j);
      Yohb(PiZjbFkqqmi, hmQWG, oz3j);
      break;
    }
    case SxhPq6: {
      char *t8pLfCwyzZ = C8lnqIsM3fY(PiZjbFkqqmi, JOfZ2HGlDm0);
      int BtYcPsj;
      if (!nAzPW(qZEQHE2xvGPvV, w5qydoLBcq))  /* float? */
        BtYcPsj = XdhPcy6ipfv(qZEQHE2xvGPvV, t8pLfCwyzZ, L4au(qZEQHE2xvGPvV, w5qydoLBcq));
      else {  /* integers */
        oOSatdH V1VPAe = wfNvfN(qZEQHE2xvGPvV, w5qydoLBcq);
        const char *kWGtpBPg = (V1VPAe == n0isb5)  /* corner case? */
                           ? "0x%" uEFzUP "x"  /* use hex */
                           : KRvwedvog4b;  /* else use default format */
        BtYcPsj = JHpKMzDSQizu(t8pLfCwyzZ, JOfZ2HGlDm0, kWGtpBPg, (dl8P9i2gd)V1VPAe);
      }
      NfPjKmvcUNU7(PiZjbFkqqmi, BtYcPsj);
      break;
    }
    case ZcFiR3hptTYdh: case pM5fzo4wBATKO: {
      am5NL_(qZEQHE2xvGPvV, w5qydoLBcq, iMEK_Y2q);
      FTBVQZ(PiZjbFkqqmi);
      break;
    }
    default: {
      cCnN0sX(qZEQHE2xvGPvV, w5qydoLBcq, "value has no literal form");
    }
  }
}


static const char *swLnf (const char *hmQWG) {
  if (yizZ6(L1SC0eGlMOc(*hmQWG))) {
    hmQWG++;
    if (yizZ6(L1SC0eGlMOc(*hmQWG))) hmQWG++;  /* (2 digits at most) */
  }
  return hmQWG;
}


/*
** Check whether a conversion specification is valid. When called,
** first character in 'form' must be '%' and last character must
** be a valid conversion specifier. 'flags' are the accepted flags;
** 'precision' signals whether to accept a precision.
*/
static void LA0JIdH8 (cMupEM84Rw *qZEQHE2xvGPvV, const char *lCwklZk_PqXA, const char *fg591cNLSsTru,
                                       int meVYCavW) {
  const char *DSCn_0WKsw = lCwklZk_PqXA + 1;  /* skip '%' */
  DSCn_0WKsw += LX_C(DSCn_0WKsw, fg591cNLSsTru);  /* skip flags */
  if (*DSCn_0WKsw != '0') {  /* a width cannot start with '0' */
    DSCn_0WKsw = swLnf(DSCn_0WKsw);  /* skip width */
    if (*DSCn_0WKsw == '.' && meVYCavW) {
      DSCn_0WKsw++;
      DSCn_0WKsw = swLnf(DSCn_0WKsw);  /* skip precision */
    }
  }
  if (!UcLELMvSP7(L1SC0eGlMOc(*DSCn_0WKsw)))  /* did not go to the end? */
    fy2mW8PN6R4Lt(qZEQHE2xvGPvV, "invalid conversion specification: '%s'", lCwklZk_PqXA);
}


/*
** Get a conversion specification and copy it to 'form'.
** Return the address of its last character.
*/
static const char *sTDea_ (cMupEM84Rw *qZEQHE2xvGPvV, const char *iBL4,
                                            char *lCwklZk_PqXA) {
  /* spans flags, width, and precision ('0' is included as a flag) */
  ssrSQ oz3j = LX_C(iBL4, dd4gW_ "123456789.");
  oz3j++;  /* adds following character (should be the specifier) */
  /* still needs space for '%', '\0', plus a length modifier */
  if (oz3j >= xKhxtuQxH - 10)
    fy2mW8PN6R4Lt(qZEQHE2xvGPvV, "invalid format (too long)");
  *(lCwklZk_PqXA++) = '%';
  fktOMwIlgYG(lCwklZk_PqXA, iBL4, oz3j * sizeof(char));
  *(lCwklZk_PqXA + oz3j) = '\0';
  return iBL4 + oz3j - 1;
}


/*
** add length modifier into formats
*/
static void RoLhH3t (char *lCwklZk_PqXA, const char *DwWxA) {
  ssrSQ tjT_ = nlHL(lCwklZk_PqXA);
  ssrSQ R6UZvR5iArEh = nlHL(DwWxA);
  char DSCn_0WKsw = lCwklZk_PqXA[tjT_ - 1];
  hko06TcAMW(lCwklZk_PqXA + tjT_ - 1, DwWxA);
  lCwklZk_PqXA[tjT_ + R6UZvR5iArEh - 1] = DSCn_0WKsw;
  lCwklZk_PqXA[tjT_ + R6UZvR5iArEh] = '\0';
}


static int VjWrpi9i0lu_v (cMupEM84Rw *qZEQHE2xvGPvV) {
  int skVa3B = eassYiC(qZEQHE2xvGPvV);
  int w5qydoLBcq = 1;
  ssrSQ Daors5qEPP;
  const char *iBL4 = RV0qYkC8dxO9B(qZEQHE2xvGPvV, w5qydoLBcq, &Daors5qEPP);
  const char *cHI6r_NEUm = iBL4+Daors5qEPP;
  const char *fg591cNLSsTru;
  LHKm PiZjbFkqqmi;
  GuLXf(qZEQHE2xvGPvV, &PiZjbFkqqmi);
  while (iBL4 < cHI6r_NEUm) {
    if (*iBL4 != MfsBdHg)
      OcTPu0HLDhkp(&PiZjbFkqqmi, *iBL4++);
    else if (*++iBL4 == MfsBdHg)
      OcTPu0HLDhkp(&PiZjbFkqqmi, *iBL4++);  /* %% */
    else { /* format item */
      char lCwklZk_PqXA[xKhxtuQxH];  /* to store the format ('%...') */
      int osq1 = JOfZ2HGlDm0;  /* maximum length for the result */
      char *t8pLfCwyzZ = C8lnqIsM3fY(&PiZjbFkqqmi, osq1);  /* to put result */
      int BtYcPsj = 0;  /* number of bytes in result */
      if (++w5qydoLBcq > skVa3B)
        return cCnN0sX(qZEQHE2xvGPvV, w5qydoLBcq, "no value");
      iBL4 = sTDea_(qZEQHE2xvGPvV, iBL4, lCwklZk_PqXA);
      switch (*iBL4++) {
        case 'c': {
          LA0JIdH8(qZEQHE2xvGPvV, lCwklZk_PqXA, tJiT1_3pI_P, 0);
          BtYcPsj = JHpKMzDSQizu(t8pLfCwyzZ, osq1, lCwklZk_PqXA, (int)MY8LsFOwaa(qZEQHE2xvGPvV, w5qydoLBcq));
          break;
        }
        case 'd': case 'i':
          fg591cNLSsTru = M3jrsPvdOlQ;
          goto lgU54RosWd;
        case 'u':
          fg591cNLSsTru = YdmCepXAxGD;
          goto lgU54RosWd;
        case 'o': case 'x': case 'X':
          fg591cNLSsTru = PrB9_Y3;
         lgU54RosWd: {
          oOSatdH V1VPAe = MY8LsFOwaa(qZEQHE2xvGPvV, w5qydoLBcq);
          LA0JIdH8(qZEQHE2xvGPvV, lCwklZk_PqXA, fg591cNLSsTru, 1);
          RoLhH3t(lCwklZk_PqXA, uEFzUP);
          BtYcPsj = JHpKMzDSQizu(t8pLfCwyzZ, osq1, lCwklZk_PqXA, (dl8P9i2gd)V1VPAe);
          break;
        }
        case 'a': case 'A':
          LA0JIdH8(qZEQHE2xvGPvV, lCwklZk_PqXA, dd4gW_, 1);
          RoLhH3t(lCwklZk_PqXA, BpLFRIQ);
          BtYcPsj = gJFMDAqct(qZEQHE2xvGPvV, t8pLfCwyzZ, osq1, lCwklZk_PqXA,
                                  C0V7TKgQo7o(qZEQHE2xvGPvV, w5qydoLBcq));
          break;
        case 'f':
          osq1 = LVRO7LGwANyHD;  /* extra space for '%f' */
          t8pLfCwyzZ = C8lnqIsM3fY(&PiZjbFkqqmi, osq1);
          /* FALLTHROUGH */
        case 'e': case 'E': case 'g': case 'G': {
          WvpnnKmCSn V1VPAe = C0V7TKgQo7o(qZEQHE2xvGPvV, w5qydoLBcq);
          LA0JIdH8(qZEQHE2xvGPvV, lCwklZk_PqXA, dd4gW_, 1);
          RoLhH3t(lCwklZk_PqXA, BpLFRIQ);
          BtYcPsj = JHpKMzDSQizu(t8pLfCwyzZ, osq1, lCwklZk_PqXA, (SyKKvu)V1VPAe);
          break;
        }
        case 'p': {
          const void *pzyakia2 = AehcR(qZEQHE2xvGPvV, w5qydoLBcq);
          LA0JIdH8(qZEQHE2xvGPvV, lCwklZk_PqXA, tJiT1_3pI_P, 0);
          if (pzyakia2 == iMEK_Y2q) {  /* avoid calling 'printf' with argument NULL */
            pzyakia2 = "(null)";  /* result */
            lCwklZk_PqXA[nlHL(lCwklZk_PqXA) - 1] = 's';  /* format it as a string */
          }
          BtYcPsj = JHpKMzDSQizu(t8pLfCwyzZ, osq1, lCwklZk_PqXA, pzyakia2);
          break;
        }
        case 'q': {
          if (lCwklZk_PqXA[2] != '\0')  /* modifiers? */
            return fy2mW8PN6R4Lt(qZEQHE2xvGPvV, "specifier '%%q' cannot have modifiers");
          YopL6S3VMAUeq(qZEQHE2xvGPvV, &PiZjbFkqqmi, w5qydoLBcq);
          break;
        }
        case 's': {
          ssrSQ tjT_;
          const char *hmQWG = am5NL_(qZEQHE2xvGPvV, w5qydoLBcq, &tjT_);
          if (lCwklZk_PqXA[2] == '\0')  /* no modifiers? */
            FTBVQZ(&PiZjbFkqqmi);  /* keep entire string */
          else {
            LrtaBfPRQO3(qZEQHE2xvGPvV, tjT_ == nlHL(hmQWG), w5qydoLBcq, "string contains zeros");
            LA0JIdH8(qZEQHE2xvGPvV, lCwklZk_PqXA, tJiT1_3pI_P, 1);
            if (hlgh6hv_nQuiW(lCwklZk_PqXA, '.') == iMEK_Y2q && tjT_ >= 100) {
              /* no precision and string is too long to be formatted */
              FTBVQZ(&PiZjbFkqqmi);  /* keep entire string */
            }
            else {  /* format the string into 'buff' */
              BtYcPsj = JHpKMzDSQizu(t8pLfCwyzZ, osq1, lCwklZk_PqXA, hmQWG);
              b3L72bHQfBc(qZEQHE2xvGPvV, 1);  /* remove result from 'luaL_tolstring' */
            }
          }
          break;
        }
        default: {  /* also treat cases 'pnLlh' */
          return fy2mW8PN6R4Lt(qZEQHE2xvGPvV, "invalid conversion '%s' to 'format'", lCwklZk_PqXA);
        }
      }
      dSTHLPELSaJ3E(BtYcPsj < osq1);
      NfPjKmvcUNU7(&PiZjbFkqqmi, BtYcPsj);
    }
  }
  FzU9(&PiZjbFkqqmi);
  return 1;
}

/* }====================================================== */


/*
** {======================================================
** PACK/UNPACK
** =======================================================
*/


/* value used for padding */
#if !v0y1ukO(Hr3bCQUbD7f)
#define Hr3bCQUbD7f		0x00
#endif

/* maximum size for the binary representation of an integer */
#define Gb7JVgxkeVuD	16

/* number of bits in a character */
#define bbpDA6YMcwBzL	QfPctr4ta2

/* mask for one character (NB 1's) */
#define iLFqTGr	((1 << bbpDA6YMcwBzL) - 1)

/* size of a lua_Integer */
#define k7Rig4	((int)sizeof(oOSatdH))


/* dummy union to get native endianness */
static const union {
  int uDjEclhLFu;
  char hhxUohOdfrw_;  /* true iff machine is little endian */
} rJF4 = {1};


/*
** information to pack/unpack stuff
*/
typedef struct FcKQ67iux4 {
  cMupEM84Rw *qZEQHE2xvGPvV;
  int NEGMb9i;
  int Dz6LNxVk;
} FcKQ67iux4;


/*
** options for pack/unpack
*/
typedef enum N6a3XI {
  ZfwYVfIf7,		/* signed integers */
  HMXb4s,	/* unsigned integers */
  ZOvTQqcdmPcE,	/* single-precision floating-point numbers */
  ETJa50S7Tv,	/* Lua "native" floating-point numbers */
  ePaf0KJ,	/* double-precision floating-point numbers */
  dZA_hlvWn,	/* fixed-length strings */
  i_rAiFI8f0mye,	/* strings with prefixed length */
  CjTlmtEal,	/* zero-terminated strings */
  Tm7EpU,	/* padding */
  asjKTC,	/* padding for alignment */
  raLM		/* no-op (configuration or spaces) */
} N6a3XI;


/*
** Read an integer numeral from string 'fmt' or return 'df' if
** there is no numeral
*/
static int oJjK (int UJAegx) { return '0' <= UJAegx && UJAegx <= '9'; }

static int VsISEQRJlYq (const char **T806u, int ZTbjprzRsdsyq) {
  if (!oJjK(**T806u))  /* no number? */
    return ZTbjprzRsdsyq;  /* return default value */
  else {
    int uDkzGPE1Kt3gK = 0;
    do {
      uDkzGPE1Kt3gK = uDkzGPE1Kt3gK*10 + (*((*T806u)++) - '0');
    } while (oJjK(**T806u) && uDkzGPE1Kt3gK <= ((int)d4eo1yR - 9)/10);
    return uDkzGPE1Kt3gK;
  }
}


/*
** Read an integer numeral and raises an error if it is larger
** than the maximum size for integers.
*/
static int R2mueF (FcKQ67iux4 *UFN1uQ, const char **T806u, int ZTbjprzRsdsyq) {
  int UGpGc = VsISEQRJlYq(T806u, ZTbjprzRsdsyq);
  if (SRRjqMHypOTXp(UGpGc > Gb7JVgxkeVuD || UGpGc <= 0))
    return fy2mW8PN6R4Lt(UFN1uQ->qZEQHE2xvGPvV, "integral size (%d) out of limits [1,%d]",
                            UGpGc, Gb7JVgxkeVuD);
  return UGpGc;
}


/*
** Initialize Header
*/
static void yASIY (cMupEM84Rw *qZEQHE2xvGPvV, FcKQ67iux4 *UFN1uQ) {
  UFN1uQ->qZEQHE2xvGPvV = qZEQHE2xvGPvV;
  UFN1uQ->NEGMb9i = rJF4.hhxUohOdfrw_;
  UFN1uQ->Dz6LNxVk = 1;
}


/*
** Read and classify next option. 'size' is filled with option's size.
*/
static N6a3XI QvB3TS8XecDoR (FcKQ67iux4 *UFN1uQ, const char **T806u, int *ECKACz_pl) {
  /* dummy structure to get native alignment requirements */
  struct rQzAfRa5bmzr { char UJAegx; union { w6Xts0Q; } zY5G4kWnrTwTw; };
  int VpSJi58RY4 = *((*T806u)++);
  *ECKACz_pl = 0;  /* default */
  switch (VpSJi58RY4) {
    case 'b': *ECKACz_pl = sizeof(char); return ZfwYVfIf7;
    case 'B': *ECKACz_pl = sizeof(char); return HMXb4s;
    case 'h': *ECKACz_pl = sizeof(short); return ZfwYVfIf7;
    case 'H': *ECKACz_pl = sizeof(short); return HMXb4s;
    case 'l': *ECKACz_pl = sizeof(long); return ZfwYVfIf7;
    case 'L': *ECKACz_pl = sizeof(long); return HMXb4s;
    case 'j': *ECKACz_pl = sizeof(oOSatdH); return ZfwYVfIf7;
    case 'J': *ECKACz_pl = sizeof(oOSatdH); return HMXb4s;
    case 'T': *ECKACz_pl = sizeof(ssrSQ); return HMXb4s;
    case 'f': *ECKACz_pl = sizeof(float); return ZOvTQqcdmPcE;
    case 'n': *ECKACz_pl = sizeof(WvpnnKmCSn); return ETJa50S7Tv;
    case 'd': *ECKACz_pl = sizeof(double); return ePaf0KJ;
    case 'i': *ECKACz_pl = R2mueF(UFN1uQ, T806u, sizeof(int)); return ZfwYVfIf7;
    case 'I': *ECKACz_pl = R2mueF(UFN1uQ, T806u, sizeof(int)); return HMXb4s;
    case 's': *ECKACz_pl = R2mueF(UFN1uQ, T806u, sizeof(ssrSQ)); return i_rAiFI8f0mye;
    case 'c':
      *ECKACz_pl = VsISEQRJlYq(T806u, -1);
      if (SRRjqMHypOTXp(*ECKACz_pl == -1))
        fy2mW8PN6R4Lt(UFN1uQ->qZEQHE2xvGPvV, "missing size for format option 'c'");
      return dZA_hlvWn;
    case 'z': return CjTlmtEal;
    case 'x': *ECKACz_pl = 1; return Tm7EpU;
    case 'X': return asjKTC;
    case ' ': break;
    case '<': UFN1uQ->NEGMb9i = 1; break;
    case '>': UFN1uQ->NEGMb9i = 0; break;
    case '=': UFN1uQ->NEGMb9i = rJF4.hhxUohOdfrw_; break;
    case '!': {
      const int Dz6LNxVk = wcZrA0VU(struct rQzAfRa5bmzr, zY5G4kWnrTwTw);
      UFN1uQ->Dz6LNxVk = R2mueF(UFN1uQ, T806u, Dz6LNxVk);
      break;
    }
    default: fy2mW8PN6R4Lt(UFN1uQ->qZEQHE2xvGPvV, "invalid format option '%c'", VpSJi58RY4);
  }
  return raLM;
}


/*
** Read, classify, and fill other details about the next option.
** 'psize' is filled with option's size, 'notoalign' with its
** alignment requirements.
** Local variable 'size' gets the size to be aligned. (Kpadal option
** always gets its full alignment, other options are limited by
** the maximum alignment ('maxalign'). Kchar option needs no alignment
** despite its size.
*/
static N6a3XI jRaO4k (FcKQ67iux4 *UFN1uQ, ssrSQ qtADP,
                           const char **T806u, int *vTvbLToKq40f, int *fJHgCXq_n8) {
  N6a3XI VpSJi58RY4 = QvB3TS8XecDoR(UFN1uQ, T806u, vTvbLToKq40f);
  int KwHKEfulavXc = *vTvbLToKq40f;  /* usually, alignment follows size */
  if (VpSJi58RY4 == asjKTC) {  /* 'X' gets alignment from following option */
    if (**T806u == '\0' || QvB3TS8XecDoR(UFN1uQ, T806u, &KwHKEfulavXc) == dZA_hlvWn || KwHKEfulavXc == 0)
      cCnN0sX(UFN1uQ->qZEQHE2xvGPvV, 1, "invalid next option for option 'X'");
  }
  if (KwHKEfulavXc <= 1 || VpSJi58RY4 == dZA_hlvWn)  /* need no alignment? */
    *fJHgCXq_n8 = 0;
  else {
    if (KwHKEfulavXc > UFN1uQ->Dz6LNxVk)  /* enforce maximum alignment */
      KwHKEfulavXc = UFN1uQ->Dz6LNxVk;
    if (SRRjqMHypOTXp((KwHKEfulavXc & (KwHKEfulavXc - 1)) != 0))  /* not a power of 2? */
      cCnN0sX(UFN1uQ->qZEQHE2xvGPvV, 1, "format asks for alignment not power of 2");
    *fJHgCXq_n8 = (KwHKEfulavXc - (int)(qtADP & (KwHKEfulavXc - 1))) & (KwHKEfulavXc - 1);
  }
  return VpSJi58RY4;
}


/*
** Pack integer 'n' with 'size' bytes and 'islittle' endianness.
** The final 'if' handles the case when 'size' is larger than
** the size of a Lua integer, correcting the extra sign-extension
** bytes if necessary (by default they would be zeros).
*/
static void hP5MyI9sAp9 (LHKm *PiZjbFkqqmi, rwpQ0Wl V1VPAe,
                     int NEGMb9i, int ECKACz_pl, int qM_ycEWjdZ) {
  char *t8pLfCwyzZ = C8lnqIsM3fY(PiZjbFkqqmi, ECKACz_pl);
  int FrSzPASfnw;
  t8pLfCwyzZ[NEGMb9i ? 0 : ECKACz_pl - 1] = (char)(V1VPAe & iLFqTGr);  /* first byte */
  for (FrSzPASfnw = 1; FrSzPASfnw < ECKACz_pl; FrSzPASfnw++) {
    V1VPAe >>= bbpDA6YMcwBzL;
    t8pLfCwyzZ[NEGMb9i ? FrSzPASfnw : ECKACz_pl - 1 - FrSzPASfnw] = (char)(V1VPAe & iLFqTGr);
  }
  if (qM_ycEWjdZ && ECKACz_pl > k7Rig4) {  /* negative number need sign extension? */
    for (FrSzPASfnw = k7Rig4; FrSzPASfnw < ECKACz_pl; FrSzPASfnw++)  /* correct extra bytes */
      t8pLfCwyzZ[NEGMb9i ? FrSzPASfnw : ECKACz_pl - 1 - FrSzPASfnw] = (char)iLFqTGr;
  }
  NfPjKmvcUNU7(PiZjbFkqqmi, ECKACz_pl);  /* add result to buffer */
}


/*
** Copy 'size' bytes from 'src' to 'dest', correcting endianness if
** given 'islittle' is different from native endianness.
*/
static void hIRCFmZ8Gw (char *k0TD, const char *akBzFOH,
                            int ECKACz_pl, int NEGMb9i) {
  if (NEGMb9i == rJF4.hhxUohOdfrw_)
    fktOMwIlgYG(k0TD, akBzFOH, ECKACz_pl);
  else {
    k0TD += ECKACz_pl - 1;
    while (ECKACz_pl-- != 0)
      *(k0TD--) = *(akBzFOH++);
  }
}


static int SxwIuf (cMupEM84Rw *qZEQHE2xvGPvV) {
  LHKm PiZjbFkqqmi;
  FcKQ67iux4 UFN1uQ;
  const char *T806u = BFos57A8(qZEQHE2xvGPvV, 1);  /* format string */
  int w5qydoLBcq = 1;  /* current argument to pack */
  ssrSQ qtADP = 0;  /* accumulate total size of result */
  yASIY(qZEQHE2xvGPvV, &UFN1uQ);
  k7D4v66MwkDVd(qZEQHE2xvGPvV);  /* mark to separate arguments from string buffer */
  GuLXf(qZEQHE2xvGPvV, &PiZjbFkqqmi);
  while (*T806u != '\0') {
    int ECKACz_pl, fJHgCXq_n8;
    N6a3XI VpSJi58RY4 = jRaO4k(&UFN1uQ, qtADP, &T806u, &ECKACz_pl, &fJHgCXq_n8);
    qtADP += fJHgCXq_n8 + ECKACz_pl;
    while (fJHgCXq_n8-- > 0)
     OcTPu0HLDhkp(&PiZjbFkqqmi, Hr3bCQUbD7f);  /* fill alignment */
    w5qydoLBcq++;
    switch (VpSJi58RY4) {
      case ZfwYVfIf7: {  /* signed integers */
        oOSatdH V1VPAe = MY8LsFOwaa(qZEQHE2xvGPvV, w5qydoLBcq);
        if (ECKACz_pl < k7Rig4) {  /* need overflow check? */
          oOSatdH uez1ngbbx = (oOSatdH)1 << ((ECKACz_pl * bbpDA6YMcwBzL) - 1);
          LrtaBfPRQO3(qZEQHE2xvGPvV, -uez1ngbbx <= V1VPAe && V1VPAe < uez1ngbbx, w5qydoLBcq, "integer overflow");
        }
        hP5MyI9sAp9(&PiZjbFkqqmi, (rwpQ0Wl)V1VPAe, UFN1uQ.NEGMb9i, ECKACz_pl, (V1VPAe < 0));
        break;
      }
      case HMXb4s: {  /* unsigned integers */
        oOSatdH V1VPAe = MY8LsFOwaa(qZEQHE2xvGPvV, w5qydoLBcq);
        if (ECKACz_pl < k7Rig4)  /* need overflow check? */
          LrtaBfPRQO3(qZEQHE2xvGPvV, (rwpQ0Wl)V1VPAe < ((rwpQ0Wl)1 << (ECKACz_pl * bbpDA6YMcwBzL)),
                           w5qydoLBcq, "unsigned overflow");
        hP5MyI9sAp9(&PiZjbFkqqmi, (rwpQ0Wl)V1VPAe, UFN1uQ.NEGMb9i, ECKACz_pl, 0);
        break;
      }
      case ZOvTQqcdmPcE: {  /* C float */
        float qS7frkcRZdO = (float)C0V7TKgQo7o(qZEQHE2xvGPvV, w5qydoLBcq);  /* get argument */
        char *t8pLfCwyzZ = C8lnqIsM3fY(&PiZjbFkqqmi, sizeof(qS7frkcRZdO));
        /* move 'f' to final result, correcting endianness if needed */
        hIRCFmZ8Gw(t8pLfCwyzZ, (char *)&qS7frkcRZdO, sizeof(qS7frkcRZdO), UFN1uQ.NEGMb9i);
        NfPjKmvcUNU7(&PiZjbFkqqmi, ECKACz_pl);
        break;
      }
      case ETJa50S7Tv: {  /* Lua float */
        WvpnnKmCSn qS7frkcRZdO = C0V7TKgQo7o(qZEQHE2xvGPvV, w5qydoLBcq);  /* get argument */
        char *t8pLfCwyzZ = C8lnqIsM3fY(&PiZjbFkqqmi, sizeof(qS7frkcRZdO));
        /* move 'f' to final result, correcting endianness if needed */
        hIRCFmZ8Gw(t8pLfCwyzZ, (char *)&qS7frkcRZdO, sizeof(qS7frkcRZdO), UFN1uQ.NEGMb9i);
        NfPjKmvcUNU7(&PiZjbFkqqmi, ECKACz_pl);
        break;
      }
      case ePaf0KJ: {  /* C double */
        double qS7frkcRZdO = (double)C0V7TKgQo7o(qZEQHE2xvGPvV, w5qydoLBcq);  /* get argument */
        char *t8pLfCwyzZ = C8lnqIsM3fY(&PiZjbFkqqmi, sizeof(qS7frkcRZdO));
        /* move 'f' to final result, correcting endianness if needed */
        hIRCFmZ8Gw(t8pLfCwyzZ, (char *)&qS7frkcRZdO, sizeof(qS7frkcRZdO), UFN1uQ.NEGMb9i);
        NfPjKmvcUNU7(&PiZjbFkqqmi, ECKACz_pl);
        break;
      }
      case dZA_hlvWn: {  /* fixed-size string */
        ssrSQ oz3j;
        const char *hmQWG = RV0qYkC8dxO9B(qZEQHE2xvGPvV, w5qydoLBcq, &oz3j);
        LrtaBfPRQO3(qZEQHE2xvGPvV, oz3j <= (ssrSQ)ECKACz_pl, w5qydoLBcq,
                         "string longer than given size");
        VmhgLz(&PiZjbFkqqmi, hmQWG, oz3j);  /* add string */
        while (oz3j++ < (ssrSQ)ECKACz_pl)  /* pad extra space */
          OcTPu0HLDhkp(&PiZjbFkqqmi, Hr3bCQUbD7f);
        break;
      }
      case i_rAiFI8f0mye: {  /* strings with length count */
        ssrSQ oz3j;
        const char *hmQWG = RV0qYkC8dxO9B(qZEQHE2xvGPvV, w5qydoLBcq, &oz3j);
        LrtaBfPRQO3(qZEQHE2xvGPvV, ECKACz_pl >= (int)sizeof(ssrSQ) ||
                         oz3j < ((ssrSQ)1 << (ECKACz_pl * bbpDA6YMcwBzL)),
                         w5qydoLBcq, "string length does not fit in given size");
        hP5MyI9sAp9(&PiZjbFkqqmi, (rwpQ0Wl)oz3j, UFN1uQ.NEGMb9i, ECKACz_pl, 0);  /* pack length */
        VmhgLz(&PiZjbFkqqmi, hmQWG, oz3j);
        qtADP += oz3j;
        break;
      }
      case CjTlmtEal: {  /* zero-terminated string */
        ssrSQ oz3j;
        const char *hmQWG = RV0qYkC8dxO9B(qZEQHE2xvGPvV, w5qydoLBcq, &oz3j);
        LrtaBfPRQO3(qZEQHE2xvGPvV, nlHL(hmQWG) == oz3j, w5qydoLBcq, "string contains zeros");
        VmhgLz(&PiZjbFkqqmi, hmQWG, oz3j);
        OcTPu0HLDhkp(&PiZjbFkqqmi, '\0');  /* add zero at the end */
        qtADP += oz3j + 1;
        break;
      }
      case Tm7EpU: OcTPu0HLDhkp(&PiZjbFkqqmi, Hr3bCQUbD7f);  /* FALLTHROUGH */
      case asjKTC: case raLM:
        w5qydoLBcq--;  /* undo increment */
        break;
    }
  }
  FzU9(&PiZjbFkqqmi);
  return 1;
}


static int Ji1a (cMupEM84Rw *qZEQHE2xvGPvV) {
  FcKQ67iux4 UFN1uQ;
  const char *T806u = BFos57A8(qZEQHE2xvGPvV, 1);  /* format string */
  ssrSQ qtADP = 0;  /* accumulate total size of result */
  yASIY(qZEQHE2xvGPvV, &UFN1uQ);
  while (*T806u != '\0') {
    int ECKACz_pl, fJHgCXq_n8;
    N6a3XI VpSJi58RY4 = jRaO4k(&UFN1uQ, qtADP, &T806u, &ECKACz_pl, &fJHgCXq_n8);
    LrtaBfPRQO3(qZEQHE2xvGPvV, VpSJi58RY4 != i_rAiFI8f0mye && VpSJi58RY4 != CjTlmtEal, 1,
                     "variable-length format");
    ECKACz_pl += fJHgCXq_n8;  /* total space used by option */
    LrtaBfPRQO3(qZEQHE2xvGPvV, qtADP <= d4eo1yR - ECKACz_pl, 1,
                     "format result too large");
    qtADP += ECKACz_pl;
  }
  uoUK3WTgIAWaZ(qZEQHE2xvGPvV, (oOSatdH)qtADP);
  return 1;
}


/*
** Unpack an integer with 'size' bytes and 'islittle' endianness.
** If size is smaller than the size of a Lua integer and integer
** is signed, must do sign extension (propagating the sign to the
** higher bits); if size is larger than the size of a Lua integer,
** it must check the unread bytes to see whether they do not cause an
** overflow.
*/
static oOSatdH XVvzZu (cMupEM84Rw *qZEQHE2xvGPvV, const char *BLhRqRTD21Bix,
                              int NEGMb9i, int ECKACz_pl, int g7E4M_z) {
  rwpQ0Wl jBmS2zxZ37M = 0;
  int FrSzPASfnw;
  int FU16U = (ECKACz_pl  <= k7Rig4) ? ECKACz_pl : k7Rig4;
  for (FrSzPASfnw = FU16U - 1; FrSzPASfnw >= 0; FrSzPASfnw--) {
    jBmS2zxZ37M <<= bbpDA6YMcwBzL;
    jBmS2zxZ37M |= (rwpQ0Wl)(unsigned char)BLhRqRTD21Bix[NEGMb9i ? FrSzPASfnw : ECKACz_pl - 1 - FrSzPASfnw];
  }
  if (ECKACz_pl < k7Rig4) {  /* real size smaller than lua_Integer? */
    if (g7E4M_z) {  /* needs sign extension? */
      rwpQ0Wl eyydWXOChNIXF = (rwpQ0Wl)1 << (ECKACz_pl*bbpDA6YMcwBzL - 1);
      jBmS2zxZ37M = ((jBmS2zxZ37M ^ eyydWXOChNIXF) - eyydWXOChNIXF);  /* do sign extension */
    }
  }
  else if (ECKACz_pl > k7Rig4) {  /* must check unread bytes */
    int eyydWXOChNIXF = (!g7E4M_z || (oOSatdH)jBmS2zxZ37M >= 0) ? 0 : iLFqTGr;
    for (FrSzPASfnw = FU16U; FrSzPASfnw < ECKACz_pl; FrSzPASfnw++) {
      if (SRRjqMHypOTXp((unsigned char)BLhRqRTD21Bix[NEGMb9i ? FrSzPASfnw : ECKACz_pl - 1 - FrSzPASfnw] != eyydWXOChNIXF))
        fy2mW8PN6R4Lt(qZEQHE2xvGPvV, "%d-byte integer does not fit into Lua Integer", ECKACz_pl);
    }
  }
  return (oOSatdH)jBmS2zxZ37M;
}


static int szYLI1Gf (cMupEM84Rw *qZEQHE2xvGPvV) {
  FcKQ67iux4 UFN1uQ;
  const char *T806u = BFos57A8(qZEQHE2xvGPvV, 1);
  ssrSQ T293;
  const char *IJVGipDzP = RV0qYkC8dxO9B(qZEQHE2xvGPvV, 2, &T293);
  ssrSQ ptR8GKNfjobx = smcmHEMcOm(wR3vpjjAn6I(qZEQHE2xvGPvV, 3, 1), T293) - 1;
  int V1VPAe = 0;  /* number of results */
  LrtaBfPRQO3(qZEQHE2xvGPvV, ptR8GKNfjobx <= T293, 3, "initial position out of string");
  yASIY(qZEQHE2xvGPvV, &UFN1uQ);
  while (*T806u != '\0') {
    int ECKACz_pl, fJHgCXq_n8;
    N6a3XI VpSJi58RY4 = jRaO4k(&UFN1uQ, ptR8GKNfjobx, &T806u, &ECKACz_pl, &fJHgCXq_n8);
    LrtaBfPRQO3(qZEQHE2xvGPvV, (ssrSQ)fJHgCXq_n8 + ECKACz_pl <= T293 - ptR8GKNfjobx, 2,
                    "data string too short");
    ptR8GKNfjobx += fJHgCXq_n8;  /* skip alignment */
    /* stack space for item + next position */
    e3tFHrf(qZEQHE2xvGPvV, 2, "too many results");
    V1VPAe++;
    switch (VpSJi58RY4) {
      case ZfwYVfIf7:
      case HMXb4s: {
        oOSatdH jBmS2zxZ37M = XVvzZu(qZEQHE2xvGPvV, IJVGipDzP + ptR8GKNfjobx, UFN1uQ.NEGMb9i, ECKACz_pl,
                                       (VpSJi58RY4 == ZfwYVfIf7));
        uoUK3WTgIAWaZ(qZEQHE2xvGPvV, jBmS2zxZ37M);
        break;
      }
      case ZOvTQqcdmPcE: {
        float qS7frkcRZdO;
        hIRCFmZ8Gw((char *)&qS7frkcRZdO, IJVGipDzP + ptR8GKNfjobx, sizeof(qS7frkcRZdO), UFN1uQ.NEGMb9i);
        GKxnbCRo(qZEQHE2xvGPvV, (WvpnnKmCSn)qS7frkcRZdO);
        break;
      }
      case ETJa50S7Tv: {
        WvpnnKmCSn qS7frkcRZdO;
        hIRCFmZ8Gw((char *)&qS7frkcRZdO, IJVGipDzP + ptR8GKNfjobx, sizeof(qS7frkcRZdO), UFN1uQ.NEGMb9i);
        GKxnbCRo(qZEQHE2xvGPvV, qS7frkcRZdO);
        break;
      }
      case ePaf0KJ: {
        double qS7frkcRZdO;
        hIRCFmZ8Gw((char *)&qS7frkcRZdO, IJVGipDzP + ptR8GKNfjobx, sizeof(qS7frkcRZdO), UFN1uQ.NEGMb9i);
        GKxnbCRo(qZEQHE2xvGPvV, (WvpnnKmCSn)qS7frkcRZdO);
        break;
      }
      case dZA_hlvWn: {
        wYFtBL7C(qZEQHE2xvGPvV, IJVGipDzP + ptR8GKNfjobx, ECKACz_pl);
        break;
      }
      case i_rAiFI8f0mye: {
        ssrSQ oz3j = (ssrSQ)XVvzZu(qZEQHE2xvGPvV, IJVGipDzP + ptR8GKNfjobx, UFN1uQ.NEGMb9i, ECKACz_pl, 0);
        LrtaBfPRQO3(qZEQHE2xvGPvV, oz3j <= T293 - ptR8GKNfjobx - ECKACz_pl, 2, "data string too short");
        wYFtBL7C(qZEQHE2xvGPvV, IJVGipDzP + ptR8GKNfjobx + ECKACz_pl, oz3j);
        ptR8GKNfjobx += oz3j;  /* skip string */
        break;
      }
      case CjTlmtEal: {
        ssrSQ oz3j = nlHL(IJVGipDzP + ptR8GKNfjobx);
        LrtaBfPRQO3(qZEQHE2xvGPvV, ptR8GKNfjobx + oz3j < T293, 2,
                         "unfinished string for format 'z'");
        wYFtBL7C(qZEQHE2xvGPvV, IJVGipDzP + ptR8GKNfjobx, oz3j);
        ptR8GKNfjobx += oz3j + 1;  /* skip string plus final '\0' */
        break;
      }
      case asjKTC: case Tm7EpU: case raLM:
        V1VPAe--;  /* undo increment */
        break;
    }
    ptR8GKNfjobx += ECKACz_pl;
  }
  uoUK3WTgIAWaZ(qZEQHE2xvGPvV, ptR8GKNfjobx + 1);  /* next position */
  return V1VPAe + 1;
}

/* }====================================================== */


static const AhoKU0 uIsLhr[] = {
  {"byte", rJ5DC},
  {"char", SG7L},
  {"dump", Sj6Ed},
  {"find", dr9FobuceZ7r},
  {"format", VjWrpi9i0lu_v},
  {"gmatch", L_XhZQCgRUG},
  {"gsub", rLgnmU5},
  {"len", B_thQ},
  {"lower", XhuvE9Qt},
  {"match", zzCcBCB2RAe3p},
  {"rep", hDfwlv5O43sM},
  {"reverse", YaX1AErhVR},
  {"sub", CFSRjc5v9},
  {"upper", Q5l1oWoY},
  {"pack", SxwIuf},
  {"packsize", Ji1a},
  {"unpack", szYLI1Gf},
  {iMEK_Y2q, iMEK_Y2q}
};


static void BLFhEdOlbV (cMupEM84Rw *qZEQHE2xvGPvV) {
  /* table to be metatable for strings */
  hKQ3Zv(qZEQHE2xvGPvV, DxakEUNjThyWy);
  gEy_v(qZEQHE2xvGPvV, DxakEUNjThyWy, 0);
  VIsqprcLO(qZEQHE2xvGPvV, "");  /* dummy string */
  oMnKCnKqu3Ls(qZEQHE2xvGPvV, -2);  /* copy table */
  Qd3xmGG4pb(qZEQHE2xvGPvV, -2);  /* set table as metatable for strings */
  b3L72bHQfBc(qZEQHE2xvGPvV, 1);  /* pop dummy string */
  oMnKCnKqu3Ls(qZEQHE2xvGPvV, -2);  /* get string library */
  V1FCxVXv0x(qZEQHE2xvGPvV, -2, "__index");  /* metatable.__index = string */
  b3L72bHQfBc(qZEQHE2xvGPvV, 1);  /* pop metatable */
}


/*
** Open string library
*/
boLSY7ld int KMkbGsjSu (cMupEM84Rw *qZEQHE2xvGPvV) {
  fsPME(qZEQHE2xvGPvV, uIsLhr);
  BLFhEdOlbV(qZEQHE2xvGPvV);
  return 1;
}

