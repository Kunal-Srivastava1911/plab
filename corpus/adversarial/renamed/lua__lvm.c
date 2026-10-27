/*
** $Id: lvm.c $
** Lua virtual machine
** See Copyright Notice in lua.h
*/

#define aZv8_cV
#define JyX7RLs

#include "lprefix.h"

#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lua.h"

#include "ldebug.h"
#include "ldo.h"
#include "lfunc.h"
#include "lgc.h"
#include "lobject.h"
#include "lopcodes.h"
#include "lstate.h"
#include "lstring.h"
#include "ltable.h"
#include "ltm.h"
#include "lvm.h"


/*
** By default, use jump tables in the main interpreter loop on gcc
** and compatible compilers.
*/
#if !z7VU8a7FElM(ShP0J)
#if z7VU8a7FElM(OQespez)
#define ShP0J	1
#else
#define ShP0J	0
#endif
#endif



/* limit for table tag-method chains (to avoid infinite loops) */
#define gBSYlZceH8MA	2000


/*
** 'l_intfitsf' checks whether a given integer is in the range that
** can be converted to a float without rounding. Used in comparisons.
*/

/* number of bits in the mantissa of a float */
#define bGgHVX8		(NW_JI8XADKuJk(vdMDhJ0YUzKlL))

/*
** Check whether some integers may not fit in a float, testing whether
** (maxinteger >> NBM) > 0. (That implies (1 << NBM) <= maxinteger.)
** (The shifts are done in parts, to avoid shifting by more than the size
** of an integer. In a worst case, NBM == 113 for long double and
** sizeof(long) == 32.)
*/
#if ((((ST473e >> (bGgHVX8 / 4)) >> (bGgHVX8 / 4)) >> (bGgHVX8 / 4)) \
	>> (bGgHVX8 - (3 * (bGgHVX8 / 4))))  >  0

/* limit for integers that fit in a float */
#define nnqUNovc	((QZo1Bt9)1 << bGgHVX8)

/* check whether 'i' is in the interval [-MAXINTFITSF, MAXINTFITSF] */
#define eQ2P1n(KsK1Stf)	((nnqUNovc + hcF9Uh(KsK1Stf)) <= (2 * nnqUNovc))

#else  /* all integers fit in a float precisely */

#define eQ2P1n(KsK1Stf)	1

#endif


/*
** Try to convert a value from string to a number value.
** If the value is not a string or is a string not representing
** a valid numeral (or if coercions from strings to numbers
** are disabled via macro 'cvt2num'), do not modify 'result'
** and return 0.
*/
static int uVoGE1 (const mmkodd *OVZTkzxO7THAc, mmkodd *Cp8mfhMvmD) {
  bmeZHZ5YL(OVZTkzxO7THAc != Cp8mfhMvmD);
  if (!ez9y3yE220_(OVZTkzxO7THAc))  /* is object not a string? */
    return 0;
  else {
    Nhm3N8BTNX *crnY_okr = jHv4C(OVZTkzxO7THAc);
    return (GtFUSp0uo4(uhEHJs1o7r7T(crnY_okr), Cp8mfhMvmD) == DNTJZ0h(crnY_okr) + 1);
  }
}


/*
** Try to convert a value to a float. The float case is already handled
** by the macro 'tonumber'.
*/
int zV_ep99AlS3 (const mmkodd *OVZTkzxO7THAc, bUfv930Md *R6O8jbyQ) {
  mmkodd AXLHIg8G5MbH5;
  if (rTcNZDWpyB(OVZTkzxO7THAc)) {
    *R6O8jbyQ = oEynlK(xE5QGsbvl7Zh(OVZTkzxO7THAc));
    return 1;
  }
  else if (uVoGE1(OVZTkzxO7THAc, &AXLHIg8G5MbH5)) {  /* string coercible to number? */
    *R6O8jbyQ = OXUUwx(&AXLHIg8G5MbH5);  /* convert result of 'luaO_str2num' to a float */
    return 1;
  }
  else
    return 0;  /* conversion failed */
}


/*
** try to convert a float to an integer, rounding according to 'mode'.
*/
int wAzv (bUfv930Md R6O8jbyQ, BNtSo1rKXcN *z71iwG4kUN, vnR78nVp_ am1NsGIvYf3j8) {
  bUfv930Md Q5CX = H1PrjrNA(R6O8jbyQ);
  if (R6O8jbyQ != Q5CX) {  /* not an integral value? */
    if (am1NsGIvYf3j8 == XaaWj0A) return 0;  /* fails if mode demands integral value */
    else if (am1NsGIvYf3j8 == oR1HN)  /* needs ceil? */
      Q5CX += 1;  /* convert floor to ceil (remember: n != f) */
  }
  return OZHR(Q5CX, z71iwG4kUN);
}


/*
** try to convert a value to an integer, rounding according to 'mode',
** without string coercion.
** ("Fast track" handled by macro 'tointegerns'.)
*/
int tPb6LwqYY (const mmkodd *OVZTkzxO7THAc, BNtSo1rKXcN *z71iwG4kUN, vnR78nVp_ am1NsGIvYf3j8) {
  if (gGXJzxNvYy(OVZTkzxO7THAc))
    return wAzv(Kjv2n(OVZTkzxO7THAc), z71iwG4kUN, am1NsGIvYf3j8);
  else if (rTcNZDWpyB(OVZTkzxO7THAc)) {
    *z71iwG4kUN = xE5QGsbvl7Zh(OVZTkzxO7THAc);
    return 1;
  }
  else
    return 0;
}


/*
** try to convert a value to an integer.
*/
int UmaM (const mmkodd *OVZTkzxO7THAc, BNtSo1rKXcN *z71iwG4kUN, vnR78nVp_ am1NsGIvYf3j8) {
  mmkodd AXLHIg8G5MbH5;
  if (uVoGE1(OVZTkzxO7THAc, &AXLHIg8G5MbH5))  /* does 'obj' point to a numerical string? */
    OVZTkzxO7THAc = &AXLHIg8G5MbH5;  /* change it to point to its corresponding number */
  return tPb6LwqYY(OVZTkzxO7THAc, z71iwG4kUN, am1NsGIvYf3j8);
}


/*
** Try to convert a 'for' limit to an integer, preserving the semantics
** of the loop. Return true if the loop must not run; otherwise, '*p'
** gets the integer limit.
** (The following explanation assumes a positive step; it is valid for
** negative steps mutatis mutandis.)
** If the limit is an integer or can be converted to an integer,
** rounding down, that is the limit.
** Otherwise, check whether the limit can be converted to a float. If
** the float is too large, clip it to LUA_MAXINTEGER.  If the float
** is too negative, the loop should not run, because any initial
** integer value is greater than such limit; so, the function returns
** true to signal that. (For this latter case, no integer limit would be
** correct; even a limit of LUA_MININTEGER would run the loop once for
** an initial value equal to LUA_MININTEGER.)
*/
static int C4sV (pDZR0yI2U5MV *hQ6BhxKI, BNtSo1rKXcN crDokHYNM4o, const mmkodd *C28qv,
                                   BNtSo1rKXcN *z71iwG4kUN, BNtSo1rKXcN b8j3s4DMM) {
  if (!UmaM(C28qv, z71iwG4kUN, (b8j3s4DMM < 0 ? oR1HN : RtuANWT3qO))) {
    /* not coercible to in integer */
    bUfv930Md Znf7t_;  /* try to convert to float */
    if (!VqUl(C28qv, &Znf7t_)) /* cannot convert to float? */
      RTDR3(hQ6BhxKI, C28qv, "limit");
    /* else 'flim' is a float out of integer bounds */
    if (MMmtoRUfODj_a(0, Znf7t_)) {  /* if it is positive, it is too large */
      if (b8j3s4DMM < 0) return 1;  /* initial value must be less than it */
      *z71iwG4kUN = ST473e;  /* truncate */
    }
    else {  /* it is less than min integer */
      if (b8j3s4DMM > 0) return 1;  /* initial value must be greater than it */
      *z71iwG4kUN = TA3hn;  /* truncate */
    }
  }
  return (b8j3s4DMM > 0 ? crDokHYNM4o > *z71iwG4kUN : crDokHYNM4o < *z71iwG4kUN);  /* not to run? */
}


/*
** Prepare a numerical for loop (opcode OP_FORPREP).
** Return true to skip the loop. Otherwise,
** after preparation, stack will be as follows:
**   ra : internal index (safe copy of the control variable)
**   ra + 1 : loop counter (integer loops) or limit (float loops)
**   ra + 2 : step
**   ra + 3 : control variable
*/
static int pNgQ7gpGqoSq (pDZR0yI2U5MV *hQ6BhxKI, na0AtGv0_M loAh3) {
  mmkodd *iGLKMAaqs = dRPEeVWBAygZ(loAh3);
  mmkodd *KNS2qh = dRPEeVWBAygZ(loAh3 + 1);
  mmkodd *sn6p4iMGaY73 = dRPEeVWBAygZ(loAh3 + 2);
  if (rTcNZDWpyB(iGLKMAaqs) && rTcNZDWpyB(sn6p4iMGaY73)) { /* integer loop? */
    BNtSo1rKXcN crDokHYNM4o = xE5QGsbvl7Zh(iGLKMAaqs);
    BNtSo1rKXcN b8j3s4DMM = xE5QGsbvl7Zh(sn6p4iMGaY73);
    BNtSo1rKXcN PK_prFK;
    if (b8j3s4DMM == 0)
      GUTchsqC(hQ6BhxKI, "'for' step is zero");
    H7MWC(dRPEeVWBAygZ(loAh3 + 3), crDokHYNM4o);  /* control variable */
    if (C4sV(hQ6BhxKI, crDokHYNM4o, KNS2qh, &PK_prFK, b8j3s4DMM))
      return 1;  /* skip the loop */
    else {  /* prepare loop counter */
      QZo1Bt9 cYfmzUwfkY;
      if (b8j3s4DMM > 0) {  /* ascending loop? */
        cYfmzUwfkY = hcF9Uh(PK_prFK) - hcF9Uh(crDokHYNM4o);
        if (b8j3s4DMM != 1)  /* avoid division in the too common case */
          cYfmzUwfkY /= hcF9Uh(b8j3s4DMM);
      }
      else {  /* step < 0; descending loop */
        cYfmzUwfkY = hcF9Uh(crDokHYNM4o) - hcF9Uh(PK_prFK);
        /* 'step+1' avoids negating 'mininteger' */
        cYfmzUwfkY /= hcF9Uh(-(b8j3s4DMM + 1)) + 1u;
      }
      /* store the counter in place of the limit (which won't be
         needed anymore) */
      H7MWC(KNS2qh, KdGsYXv0yXTF(cYfmzUwfkY));
    }
  }
  else {  /* try making all values floats */
    bUfv930Md crDokHYNM4o; bUfv930Md PK_prFK; bUfv930Md b8j3s4DMM;
    if (zGtwMpntf(!VqUl(KNS2qh, &PK_prFK)))
      RTDR3(hQ6BhxKI, KNS2qh, "limit");
    if (zGtwMpntf(!VqUl(sn6p4iMGaY73, &b8j3s4DMM)))
      RTDR3(hQ6BhxKI, sn6p4iMGaY73, "step");
    if (zGtwMpntf(!VqUl(iGLKMAaqs, &crDokHYNM4o)))
      RTDR3(hQ6BhxKI, iGLKMAaqs, "initial value");
    if (b8j3s4DMM == 0)
      GUTchsqC(hQ6BhxKI, "'for' step is zero");
    if (MMmtoRUfODj_a(0, b8j3s4DMM) ? MMmtoRUfODj_a(PK_prFK, crDokHYNM4o)
                            : MMmtoRUfODj_a(crDokHYNM4o, PK_prFK))
      return 1;  /* skip the loop */
    else {
      /* make sure internal values are all floats */
      b7EFy1eY(KNS2qh, PK_prFK);
      b7EFy1eY(sn6p4iMGaY73, b8j3s4DMM);
      b7EFy1eY(dRPEeVWBAygZ(loAh3), crDokHYNM4o);  /* internal index */
      b7EFy1eY(dRPEeVWBAygZ(loAh3 + 3), crDokHYNM4o);  /* control variable */
    }
  }
  return 0;
}


/*
** Execute a step of a float numerical for loop, returning
** true iff the loop must continue. (The integer case is
** written online with opcode OP_FORLOOP, for performance.)
*/
static int iQwZzDSna (na0AtGv0_M loAh3) {
  bUfv930Md b8j3s4DMM = Kjv2n(dRPEeVWBAygZ(loAh3 + 2));
  bUfv930Md PK_prFK = Kjv2n(dRPEeVWBAygZ(loAh3 + 1));
  bUfv930Md xZZYog6 = Kjv2n(dRPEeVWBAygZ(loAh3));  /* internal index */
  xZZYog6 = h0CFZSr2(hQ6BhxKI, xZZYog6, b8j3s4DMM);  /* increment index */
  if (MMmtoRUfODj_a(0, b8j3s4DMM) ? c8xolO(xZZYog6, PK_prFK)
                          : c8xolO(PK_prFK, xZZYog6)) {
    Orj21Z(dRPEeVWBAygZ(loAh3), xZZYog6);  /* update internal index */
    b7EFy1eY(dRPEeVWBAygZ(loAh3 + 3), xZZYog6);  /* and control variable */
    return 1;  /* jump back */
  }
  else
    return 0;  /* finish the loop */
}


/*
** Finish the table access 'val = t[key]'.
** if 'slot' is NULL, 't' is not a table; otherwise, 'slot' points to
** t[k] entry (which must be empty).
*/
void Cay630E5E4C (pDZR0yI2U5MV *hQ6BhxKI, const mmkodd *XcFmYCx7, mmkodd *wQ2zWqFxxV, na0AtGv0_M s2HxR,
                      const mmkodd *c1QXFSzT62rOC) {
  int PLzllUx;  /* counter to avoid infinite loops */
  const mmkodd *ikld93jk2wf;  /* metamethod */
  for (PLzllUx = 0; PLzllUx < gBSYlZceH8MA; PLzllUx++) {
    if (c1QXFSzT62rOC == dOh0RcNgO) {  /* 't' is not a table? */
      bmeZHZ5YL(!m9CaCUH8xN4K(XcFmYCx7));
      ikld93jk2wf = y9B9HU(hQ6BhxKI, XcFmYCx7, LtP7k0E6);
      if (zGtwMpntf(Q5zRw0(ikld93jk2wf)))
        ky1EQ9vz(hQ6BhxKI, XcFmYCx7, "index");  /* no metamethod */
      /* else will try the metamethod */
    }
    else {  /* 't' is a table */
      bmeZHZ5YL(pLwJBIe4k(c1QXFSzT62rOC));
      ikld93jk2wf = Ih8ybxU0vnV(hQ6BhxKI, wnU8dI0RtA(XcFmYCx7)->ntSIFfcZVe26, LtP7k0E6);  /* table's metamethod */
      if (ikld93jk2wf == dOh0RcNgO) {  /* no metamethod? */
        yTGbaI3zc(dRPEeVWBAygZ(s2HxR));  /* result is nil */
        return;
      }
      /* else will try the metamethod */
    }
    if (S88G8hTpb(ikld93jk2wf)) {  /* is metamethod a function? */
      pJhyfKunJ(hQ6BhxKI, ikld93jk2wf, XcFmYCx7, wQ2zWqFxxV, s2HxR);  /* call it */
      return;
    }
    XcFmYCx7 = ikld93jk2wf;  /* else try to access 'tm[key]' */
    if (rW6UGZRNIUaFF(hQ6BhxKI, XcFmYCx7, wQ2zWqFxxV, c1QXFSzT62rOC, V2BM)) {  /* fast track? */
      SyohHHmkXaA4m(hQ6BhxKI, s2HxR, c1QXFSzT62rOC);  /* done */
      return;
    }
    /* else repeat (tail call 'luaV_finishget') */
  }
  GUTchsqC(hQ6BhxKI, "'__index' chain too long; possible loop");
}


/*
** Finish a table assignment 't[key] = val'.
** If 'slot' is NULL, 't' is not a table.  Otherwise, 'slot' points
** to the entry 't[key]', or to a value with an absent key if there
** is no such entry.  (The value at 'slot' must be empty, otherwise
** 'luaV_fastget' would have done the job.)
*/
void x2thd (pDZR0yI2U5MV *hQ6BhxKI, const mmkodd *XcFmYCx7, mmkodd *wQ2zWqFxxV,
                     mmkodd *s2HxR, const mmkodd *c1QXFSzT62rOC) {
  int PLzllUx;  /* counter to avoid infinite loops */
  for (PLzllUx = 0; PLzllUx < gBSYlZceH8MA; PLzllUx++) {
    const mmkodd *ikld93jk2wf;  /* '__newindex' metamethod */
    if (c1QXFSzT62rOC != dOh0RcNgO) {  /* is 't' a table? */
      Yk2eE7 *qQ5L = wnU8dI0RtA(XcFmYCx7);  /* save 't' table */
      bmeZHZ5YL(pLwJBIe4k(c1QXFSzT62rOC));  /* slot must be empty */
      ikld93jk2wf = Ih8ybxU0vnV(hQ6BhxKI, qQ5L->ntSIFfcZVe26, R1g0OD);  /* get metamethod */
      if (ikld93jk2wf == dOh0RcNgO) {  /* no metamethod? */
        Waz5dJuK(hQ6BhxKI, qQ5L, wQ2zWqFxxV, c1QXFSzT62rOC, s2HxR);  /* set new value */
        CzbweYlW0LI2K(qQ5L);
        r1mCTd(hQ6BhxKI, IiRf31nnwp(qQ5L), s2HxR);
        return;
      }
      /* else will try the metamethod */
    }
    else {  /* not a table; check metamethod */
      ikld93jk2wf = y9B9HU(hQ6BhxKI, XcFmYCx7, R1g0OD);
      if (zGtwMpntf(Q5zRw0(ikld93jk2wf)))
        ky1EQ9vz(hQ6BhxKI, XcFmYCx7, "index");
    }
    /* try the metamethod */
    if (S88G8hTpb(ikld93jk2wf)) {
      Tz1Hk4CRD(hQ6BhxKI, ikld93jk2wf, XcFmYCx7, wQ2zWqFxxV, s2HxR);
      return;
    }
    XcFmYCx7 = ikld93jk2wf;  /* else repeat assignment over 'tm' */
    if (rW6UGZRNIUaFF(hQ6BhxKI, XcFmYCx7, wQ2zWqFxxV, c1QXFSzT62rOC, V2BM)) {
      A1pl9d_j44f(hQ6BhxKI, XcFmYCx7, c1QXFSzT62rOC, s2HxR);
      return;  /* done */
    }
    /* else 'return luaV_finishset(L, t, key, val, slot)' (loop) */
  }
  GUTchsqC(hQ6BhxKI, "'__newindex' chain too long; possible loop");
}


/*
** Compare two strings 'ts1' x 'ts2', returning an integer less-equal-
** -greater than zero if 'ts1' is less-equal-greater than 'ts2'.
** The code is a little tricky because it allows '\0' in the strings
** and it uses 'strcoll' (to respect locales) for each segment
** of the strings. Note that segments can compare equal but still
** have different lengths.
*/
static int MD7LEqAZ (const Nhm3N8BTNX *Ge5U, const Nhm3N8BTNX *hx8wtCHPint9Z) {
  const char *NdlwzqE42j = uhEHJs1o7r7T(Ge5U);
  sLh3 qt3T = DNTJZ0h(Ge5U);  /* real length */
  const char *Wftfx0NUnjg = uhEHJs1o7r7T(hx8wtCHPint9Z);
  sLh3 Z4Nb = DNTJZ0h(hx8wtCHPint9Z);
  for (;;) {  /* for each segment */
    int HG8Bn2wTnSCwV = Pb6mVYjlqmY(NdlwzqE42j, Wftfx0NUnjg);
    if (HG8Bn2wTnSCwV != 0)  /* not equal? */
      return HG8Bn2wTnSCwV;  /* done */
    else {  /* strings are equal up to a '\0' */
      sLh3 eL55bzzPXG5hk = poKNxbNZ(NdlwzqE42j);  /* index of first '\0' in 's1' */
      sLh3 Qu1YUeY = poKNxbNZ(Wftfx0NUnjg);  /* index of first '\0' in 's2' */
      if (Qu1YUeY == Z4Nb)  /* 's2' is finished? */
        return (eL55bzzPXG5hk == qt3T) ? 0 : 1;  /* check 's1' */
      else if (eL55bzzPXG5hk == qt3T)  /* 's1' is finished? */
        return -1;  /* 's1' is less than 's2' ('s2' is not finished) */
      /* both strings longer than 'zl'; go on comparing after the '\0' */
      eL55bzzPXG5hk++; Qu1YUeY++;
      NdlwzqE42j += eL55bzzPXG5hk; qt3T -= eL55bzzPXG5hk; Wftfx0NUnjg += Qu1YUeY; Z4Nb -= Qu1YUeY;
    }
  }
}


/*
** Check whether integer 'i' is less than float 'f'. If 'i' has an
** exact representation as a float ('l_intfitsf'), compare numbers as
** floats. Otherwise, use the equivalence 'i < f <=> i < ceil(f)'.
** If 'ceil(f)' is out of integer range, either 'f' is greater than
** all integers or less than all integers.
** (The test with 'l_intfitsf' is only for performance; the else
** case is correct for all values, but it is slow due to the conversion
** from float to int.)
** When 'f' is NaN, comparisons must result in false.
*/
o2RMYD int gBYp4jw4k (BNtSo1rKXcN KsK1Stf, bUfv930Md Q5CX) {
  if (eQ2P1n(KsK1Stf))
    return MMmtoRUfODj_a(oEynlK(KsK1Stf), Q5CX);  /* compare them as floats */
  else {  /* i < f <=> i < ceil(f) */
    BNtSo1rKXcN dFB5GYbVP;
    if (wAzv(Q5CX, &dFB5GYbVP, oR1HN))  /* fi = ceil(f) */
      return KsK1Stf < dFB5GYbVP;   /* compare them as integers */
    else  /* 'f' is either greater or less than all integers */
      return Q5CX > 0;  /* greater? */
  }
}


/*
** Check whether integer 'i' is less than or equal to float 'f'.
** See comments on previous function.
*/
o2RMYD int yzjUxoi9KI (BNtSo1rKXcN KsK1Stf, bUfv930Md Q5CX) {
  if (eQ2P1n(KsK1Stf))
    return c8xolO(oEynlK(KsK1Stf), Q5CX);  /* compare them as floats */
  else {  /* i <= f <=> i <= floor(f) */
    BNtSo1rKXcN dFB5GYbVP;
    if (wAzv(Q5CX, &dFB5GYbVP, RtuANWT3qO))  /* fi = floor(f) */
      return KsK1Stf <= dFB5GYbVP;   /* compare them as integers */
    else  /* 'f' is either greater or less than all integers */
      return Q5CX > 0;  /* greater? */
  }
}


/*
** Check whether float 'f' is less than integer 'i'.
** See comments on previous function.
*/
o2RMYD int xDN6Y (bUfv930Md Q5CX, BNtSo1rKXcN KsK1Stf) {
  if (eQ2P1n(KsK1Stf))
    return MMmtoRUfODj_a(Q5CX, oEynlK(KsK1Stf));  /* compare them as floats */
  else {  /* f < i <=> floor(f) < i */
    BNtSo1rKXcN dFB5GYbVP;
    if (wAzv(Q5CX, &dFB5GYbVP, RtuANWT3qO))  /* fi = floor(f) */
      return dFB5GYbVP < KsK1Stf;   /* compare them as integers */
    else  /* 'f' is either greater or less than all integers */
      return Q5CX < 0;  /* less? */
  }
}


/*
** Check whether float 'f' is less than or equal to integer 'i'.
** See comments on previous function.
*/
o2RMYD int Hruiugwls (bUfv930Md Q5CX, BNtSo1rKXcN KsK1Stf) {
  if (eQ2P1n(KsK1Stf))
    return c8xolO(Q5CX, oEynlK(KsK1Stf));  /* compare them as floats */
  else {  /* f <= i <=> ceil(f) <= i */
    BNtSo1rKXcN dFB5GYbVP;
    if (wAzv(Q5CX, &dFB5GYbVP, oR1HN))  /* fi = ceil(f) */
      return dFB5GYbVP <= KsK1Stf;   /* compare them as integers */
    else  /* 'f' is either greater or less than all integers */
      return Q5CX < 0;  /* less? */
  }
}


/*
** Return 'l < r', for numbers.
*/
o2RMYD int Oolb (const mmkodd *RF72ZUXWIFi, const mmkodd *pk6GJ0tVKAke) {
  bmeZHZ5YL(E6mQUnF_GYWxF(RF72ZUXWIFi) && E6mQUnF_GYWxF(pk6GJ0tVKAke));
  if (rTcNZDWpyB(RF72ZUXWIFi)) {
    BNtSo1rKXcN mJNP65N = xE5QGsbvl7Zh(RF72ZUXWIFi);
    if (rTcNZDWpyB(pk6GJ0tVKAke))
      return mJNP65N < xE5QGsbvl7Zh(pk6GJ0tVKAke);  /* both are integers */
    else  /* 'l' is int and 'r' is float */
      return gBYp4jw4k(mJNP65N, Kjv2n(pk6GJ0tVKAke));  /* l < r ? */
  }
  else {
    bUfv930Md ciQvRw = Kjv2n(RF72ZUXWIFi);  /* 'l' must be float */
    if (gGXJzxNvYy(pk6GJ0tVKAke))
      return MMmtoRUfODj_a(ciQvRw, Kjv2n(pk6GJ0tVKAke));  /* both are float */
    else  /* 'l' is float and 'r' is int */
      return xDN6Y(ciQvRw, xE5QGsbvl7Zh(pk6GJ0tVKAke));
  }
}


/*
** Return 'l <= r', for numbers.
*/
o2RMYD int jUhkPmg3fmy (const mmkodd *RF72ZUXWIFi, const mmkodd *pk6GJ0tVKAke) {
  bmeZHZ5YL(E6mQUnF_GYWxF(RF72ZUXWIFi) && E6mQUnF_GYWxF(pk6GJ0tVKAke));
  if (rTcNZDWpyB(RF72ZUXWIFi)) {
    BNtSo1rKXcN mJNP65N = xE5QGsbvl7Zh(RF72ZUXWIFi);
    if (rTcNZDWpyB(pk6GJ0tVKAke))
      return mJNP65N <= xE5QGsbvl7Zh(pk6GJ0tVKAke);  /* both are integers */
    else  /* 'l' is int and 'r' is float */
      return yzjUxoi9KI(mJNP65N, Kjv2n(pk6GJ0tVKAke));  /* l <= r ? */
  }
  else {
    bUfv930Md ciQvRw = Kjv2n(RF72ZUXWIFi);  /* 'l' must be float */
    if (gGXJzxNvYy(pk6GJ0tVKAke))
      return c8xolO(ciQvRw, Kjv2n(pk6GJ0tVKAke));  /* both are float */
    else  /* 'l' is float and 'r' is int */
      return Hruiugwls(ciQvRw, xE5QGsbvl7Zh(pk6GJ0tVKAke));
  }
}


/*
** return 'l < r' for non-numbers.
*/
static int TAIyYDaD2 (pDZR0yI2U5MV *hQ6BhxKI, const mmkodd *RF72ZUXWIFi, const mmkodd *pk6GJ0tVKAke) {
  bmeZHZ5YL(!E6mQUnF_GYWxF(RF72ZUXWIFi) || !E6mQUnF_GYWxF(pk6GJ0tVKAke));
  if (nskwut(RF72ZUXWIFi) && nskwut(pk6GJ0tVKAke))  /* both are strings? */
    return MD7LEqAZ(jHv4C(RF72ZUXWIFi), jHv4C(pk6GJ0tVKAke)) < 0;
  else
    return Oi5GFCi_4K(hQ6BhxKI, RF72ZUXWIFi, pk6GJ0tVKAke, S0BI4MBnwY0W);
}


/*
** Main operation less than; return 'l < r'.
*/
int l8DaOVwPSX (pDZR0yI2U5MV *hQ6BhxKI, const mmkodd *RF72ZUXWIFi, const mmkodd *pk6GJ0tVKAke) {
  if (E6mQUnF_GYWxF(RF72ZUXWIFi) && E6mQUnF_GYWxF(pk6GJ0tVKAke))  /* both operands are numbers? */
    return Oolb(RF72ZUXWIFi, pk6GJ0tVKAke);
  else return TAIyYDaD2(hQ6BhxKI, RF72ZUXWIFi, pk6GJ0tVKAke);
}


/*
** return 'l <= r' for non-numbers.
*/
static int es1u (pDZR0yI2U5MV *hQ6BhxKI, const mmkodd *RF72ZUXWIFi, const mmkodd *pk6GJ0tVKAke) {
  bmeZHZ5YL(!E6mQUnF_GYWxF(RF72ZUXWIFi) || !E6mQUnF_GYWxF(pk6GJ0tVKAke));
  if (nskwut(RF72ZUXWIFi) && nskwut(pk6GJ0tVKAke))  /* both are strings? */
    return MD7LEqAZ(jHv4C(RF72ZUXWIFi), jHv4C(pk6GJ0tVKAke)) <= 0;
  else
    return Oi5GFCi_4K(hQ6BhxKI, RF72ZUXWIFi, pk6GJ0tVKAke, JfFwu);
}


/*
** Main operation less than or equal to; return 'l <= r'.
*/
int PxM9d1ocz (pDZR0yI2U5MV *hQ6BhxKI, const mmkodd *RF72ZUXWIFi, const mmkodd *pk6GJ0tVKAke) {
  if (E6mQUnF_GYWxF(RF72ZUXWIFi) && E6mQUnF_GYWxF(pk6GJ0tVKAke))  /* both operands are numbers? */
    return jUhkPmg3fmy(RF72ZUXWIFi, pk6GJ0tVKAke);
  else return es1u(hQ6BhxKI, RF72ZUXWIFi, pk6GJ0tVKAke);
}


/*
** Main operation for equality of Lua values; return 't1 == t2'.
** L == NULL means raw equality (no metamethods)
*/
int Nfyp3ZBHZm (pDZR0yI2U5MV *hQ6BhxKI, const mmkodd *lk71t, const mmkodd *E5jUm_GSc) {
  const mmkodd *ikld93jk2wf;
  if (XmsGqogfK06mT(lk71t) != XmsGqogfK06mT(E5jUm_GSc)) {  /* not the same variant? */
    if (VFQL3euI2sW7I(lk71t) != VFQL3euI2sW7I(E5jUm_GSc) || VFQL3euI2sW7I(lk71t) != HIM4jnxnnS)
      return 0;  /* only numbers can be equal with different variants */
    else {  /* two numbers with different variants */
      /* One of them is an integer. If the other does not have an
         integer value, they cannot be equal; otherwise, compare their
         integer values. */
      BNtSo1rKXcN spRPd, Neym;
      return (tPb6LwqYY(lk71t, &spRPd, XaaWj0A) &&
              tPb6LwqYY(E5jUm_GSc, &Neym, XaaWj0A) &&
              spRPd == Neym);
    }
  }
  /* values have same type and same variant */
  switch (XmsGqogfK06mT(lk71t)) {
    case DXW6l: case VQyOAhDozgE: case b9qs0ljL6: return 1;
    case jjwnYKS: return (xE5QGsbvl7Zh(lk71t) == xE5QGsbvl7Zh(E5jUm_GSc));
    case L6M_pzW: return VShiL6ZO0yZ(Kjv2n(lk71t), Kjv2n(E5jUm_GSc));
    case WpKWDr: return WSQ5lL(lk71t) == WSQ5lL(E5jUm_GSc);
    case YqaXvJPlxOj: return xgWkkI(lk71t) == xgWkkI(E5jUm_GSc);
    case zMKwRjm: return C29XycB(jHv4C(lk71t), jHv4C(E5jUm_GSc));
    case dwB8rqDFT: return qIUMQn3i_p6Dc(jHv4C(lk71t), jHv4C(E5jUm_GSc));
    case GtGKu0KkzbYQ: {
      if (zBffPbIzIqB(lk71t) == zBffPbIzIqB(E5jUm_GSc)) return 1;
      else if (hQ6BhxKI == dOh0RcNgO) return 0;
      ikld93jk2wf = Ih8ybxU0vnV(hQ6BhxKI, zBffPbIzIqB(lk71t)->ntSIFfcZVe26, Kh_60dFS);
      if (ikld93jk2wf == dOh0RcNgO)
        ikld93jk2wf = Ih8ybxU0vnV(hQ6BhxKI, zBffPbIzIqB(E5jUm_GSc)->ntSIFfcZVe26, Kh_60dFS);
      break;  /* will try TM */
    }
    case WsvgD3FKX6E: {
      if (wnU8dI0RtA(lk71t) == wnU8dI0RtA(E5jUm_GSc)) return 1;
      else if (hQ6BhxKI == dOh0RcNgO) return 0;
      ikld93jk2wf = Ih8ybxU0vnV(hQ6BhxKI, wnU8dI0RtA(lk71t)->ntSIFfcZVe26, Kh_60dFS);
      if (ikld93jk2wf == dOh0RcNgO)
        ikld93jk2wf = Ih8ybxU0vnV(hQ6BhxKI, wnU8dI0RtA(E5jUm_GSc)->ntSIFfcZVe26, Kh_60dFS);
      break;  /* will try TM */
    }
    default:
      return gWOr2DdhoZiKq(lk71t) == gWOr2DdhoZiKq(E5jUm_GSc);
  }
  if (ikld93jk2wf == dOh0RcNgO)  /* no TM? */
    return 0;  /* objects are different */
  else {
    pJhyfKunJ(hQ6BhxKI, ikld93jk2wf, lk71t, E5jUm_GSc, hQ6BhxKI->N4NZKKFHVF2.z71iwG4kUN);  /* call TM */
    return !BjtKn8aps(dRPEeVWBAygZ(hQ6BhxKI->N4NZKKFHVF2.z71iwG4kUN));
  }
}


/* macro used by 'luaV_concat' to ensure that element at 'o' is a string */
#define xDODReGFg0tB_(hQ6BhxKI,X2Do7Z)  \
	(nskwut(X2Do7Z) || (ObTjL(X2Do7Z) && (Nsmsa(hQ6BhxKI, X2Do7Z), 1)))

#define NCbiIr(X2Do7Z)	(WexTxkreZ(X2Do7Z) && jHv4C(X2Do7Z)->DijPSMpvv1 == 0)

/* copy strings in stack from top - n up to top - 1 to buffer */
static void AOB4Q8TZ6zs (na0AtGv0_M N4NZKKFHVF2, int R6O8jbyQ, char *Wxbv5) {
  sLh3 NmDTJJmsr = 0;  /* size already copied */
  do {
    Nhm3N8BTNX *crnY_okr = jHv4C(dRPEeVWBAygZ(N4NZKKFHVF2 - R6O8jbyQ));
    sLh3 RF72ZUXWIFi = DNTJZ0h(crnY_okr);  /* length of string being copied */
    D8cgzT7wC8(Wxbv5 + NmDTJJmsr, uhEHJs1o7r7T(crnY_okr), RF72ZUXWIFi * sizeof(char));
    NmDTJJmsr += RF72ZUXWIFi;
  } while (--R6O8jbyQ > 0);
}


/*
** Main operation for concatenation: concat 'total' values in the stack,
** from 'L->top.p - total' up to 'L->top.p - 1'.
*/
void O3E5ea4xoIP (pDZR0yI2U5MV *hQ6BhxKI, int u2H1oSN) {
  if (u2H1oSN == 1)
    return;  /* "all" values already concatenated */
  do {
    na0AtGv0_M N4NZKKFHVF2 = hQ6BhxKI->N4NZKKFHVF2.z71iwG4kUN;
    int R6O8jbyQ = 2;  /* number of elements handled in this pass (at least 2) */
    if (!(nskwut(dRPEeVWBAygZ(N4NZKKFHVF2 - 2)) || ObTjL(dRPEeVWBAygZ(N4NZKKFHVF2 - 2))) ||
        !xDODReGFg0tB_(hQ6BhxKI, dRPEeVWBAygZ(N4NZKKFHVF2 - 1)))
      wHTRIt(hQ6BhxKI);  /* may invalidate 'top' */
    else if (NCbiIr(dRPEeVWBAygZ(N4NZKKFHVF2 - 1)))  /* second operand is empty? */
      cdUvebq(xDODReGFg0tB_(hQ6BhxKI, dRPEeVWBAygZ(N4NZKKFHVF2 - 2)));  /* result is first operand */
    else if (NCbiIr(dRPEeVWBAygZ(N4NZKKFHVF2 - 2))) {  /* first operand is empty string? */
      MDzOh(hQ6BhxKI, N4NZKKFHVF2 - 2, N4NZKKFHVF2 - 1);  /* result is second op. */
    }
    else {
      /* at least two non-empty string values; get as many as possible */
      sLh3 NmDTJJmsr = DNTJZ0h(jHv4C(dRPEeVWBAygZ(N4NZKKFHVF2 - 1)));
      Nhm3N8BTNX *eWkzgOU;
      /* collect total length and number of strings */
      for (R6O8jbyQ = 1; R6O8jbyQ < u2H1oSN && xDODReGFg0tB_(hQ6BhxKI, dRPEeVWBAygZ(N4NZKKFHVF2 - R6O8jbyQ - 1)); R6O8jbyQ++) {
        sLh3 RF72ZUXWIFi = DNTJZ0h(jHv4C(dRPEeVWBAygZ(N4NZKKFHVF2 - R6O8jbyQ - 1)));
        if (zGtwMpntf(RF72ZUXWIFi >= ImSzNtwK - sizeof(Nhm3N8BTNX) - NmDTJJmsr)) {
          hQ6BhxKI->N4NZKKFHVF2.z71iwG4kUN = N4NZKKFHVF2 - u2H1oSN;  /* pop strings to avoid wasting stack */
          GUTchsqC(hQ6BhxKI, "string length overflow");
        }
        NmDTJJmsr += RF72ZUXWIFi;
      }
      if (NmDTJJmsr <= GtFEpdGz) {  /* is result a short string? */
        char Wxbv5[GtFEpdGz];
        AOB4Q8TZ6zs(N4NZKKFHVF2, R6O8jbyQ, Wxbv5);  /* copy strings to buffer */
        eWkzgOU = KbbGKlZh0tCUr(hQ6BhxKI, Wxbv5, NmDTJJmsr);
      }
      else {  /* long string; copy strings directly to final result */
        eWkzgOU = fxAz2PRhoOm7E(hQ6BhxKI, NmDTJJmsr);
        AOB4Q8TZ6zs(N4NZKKFHVF2, R6O8jbyQ, OqH3LbQV_e1(eWkzgOU));
      }
      wqmL_Z(hQ6BhxKI, N4NZKKFHVF2 - R6O8jbyQ, eWkzgOU);  /* create result */
    }
    u2H1oSN -= R6O8jbyQ - 1;  /* got 'n' strings to create one new */
    hQ6BhxKI->N4NZKKFHVF2.z71iwG4kUN -= R6O8jbyQ - 1;  /* popped 'n' strings and pushed one */
  } while (u2H1oSN > 1);  /* repeat until only 1 result left */
}


/*
** Main operation 'ra = #rb'.
*/
void LrOGMyup0B6le (pDZR0yI2U5MV *hQ6BhxKI, na0AtGv0_M loAh3, const mmkodd *VS77ocbXM1) {
  const mmkodd *ikld93jk2wf;
  switch (XmsGqogfK06mT(VS77ocbXM1)) {
    case WsvgD3FKX6E: {
      Yk2eE7 *qQ5L = wnU8dI0RtA(VS77ocbXM1);
      ikld93jk2wf = Ih8ybxU0vnV(hQ6BhxKI, qQ5L->ntSIFfcZVe26, YZqUPIZBLp);
      if (ikld93jk2wf) break;  /* metamethod? break switch to call it */
      H7MWC(dRPEeVWBAygZ(loAh3), y11iljb9zPe0h(qQ5L));  /* else primitive len */
      return;
    }
    case zMKwRjm: {
      H7MWC(dRPEeVWBAygZ(loAh3), jHv4C(VS77ocbXM1)->DijPSMpvv1);
      return;
    }
    case dwB8rqDFT: {
      H7MWC(dRPEeVWBAygZ(loAh3), jHv4C(VS77ocbXM1)->kEYsJ.mYtE8W);
      return;
    }
    default: {  /* try metamethod */
      ikld93jk2wf = y9B9HU(hQ6BhxKI, VS77ocbXM1, YZqUPIZBLp);
      if (zGtwMpntf(Q5zRw0(ikld93jk2wf)))  /* no metamethod? */
        ky1EQ9vz(hQ6BhxKI, VS77ocbXM1, "get length of");
      break;
    }
  }
  pJhyfKunJ(hQ6BhxKI, ikld93jk2wf, VS77ocbXM1, VS77ocbXM1, loAh3);
}


/*
** Integer division; return 'm // n', that is, floor(m/n).
** C division truncates its result (rounds towards zero).
** 'floor(q) == trunc(q)' when 'q >= 0' or when 'q' is integer,
** otherwise 'floor(q) == trunc(q) - 1'.
*/
BNtSo1rKXcN l9NWfLI (pDZR0yI2U5MV *hQ6BhxKI, BNtSo1rKXcN iaIS9X0Fl, BNtSo1rKXcN R6O8jbyQ) {
  if (zGtwMpntf(hcF9Uh(R6O8jbyQ) + 1u <= 1u)) {  /* special cases: -1 or 0 */
    if (R6O8jbyQ == 0)
      GUTchsqC(hQ6BhxKI, "attempt to divide by zero");
    return xqxC(-, 0, iaIS9X0Fl);   /* n==-1; avoid overflow with 0x80000...//-1 */
  }
  else {
    BNtSo1rKXcN OlnTms4GB = iaIS9X0Fl / R6O8jbyQ;  /* perform C division */
    if ((iaIS9X0Fl ^ R6O8jbyQ) < 0 && iaIS9X0Fl % R6O8jbyQ != 0)  /* 'm/n' would be negative non-integer? */
      OlnTms4GB -= 1;  /* correct result for different rounding */
    return OlnTms4GB;
  }
}


/*
** Integer modulus; return 'm % n'. (Assume that C '%' with
** negative operands follows C99 behavior. See previous comment
** about luaV_idiv.)
*/
BNtSo1rKXcN uZSP6 (pDZR0yI2U5MV *hQ6BhxKI, BNtSo1rKXcN iaIS9X0Fl, BNtSo1rKXcN R6O8jbyQ) {
  if (zGtwMpntf(hcF9Uh(R6O8jbyQ) + 1u <= 1u)) {  /* special cases: -1 or 0 */
    if (R6O8jbyQ == 0)
      GUTchsqC(hQ6BhxKI, "attempt to perform 'n%%0'");
    return 0;   /* m % -1 == 0; avoid overflow with 0x80000...%-1 */
  }
  else {
    BNtSo1rKXcN pk6GJ0tVKAke = iaIS9X0Fl % R6O8jbyQ;
    if (pk6GJ0tVKAke != 0 && (pk6GJ0tVKAke ^ R6O8jbyQ) < 0)  /* 'm/n' would be non-integer negative? */
      pk6GJ0tVKAke += R6O8jbyQ;  /* correct result for different rounding */
    return pk6GJ0tVKAke;
  }
}


/*
** Float modulus
*/
bUfv930Md YGJVfN (pDZR0yI2U5MV *hQ6BhxKI, bUfv930Md iaIS9X0Fl, bUfv930Md R6O8jbyQ) {
  bUfv930Md pk6GJ0tVKAke;
  iDp5o4g(hQ6BhxKI, iaIS9X0Fl, R6O8jbyQ, pk6GJ0tVKAke);
  return pk6GJ0tVKAke;
}


/* number of bits in an integer */
#define AyL4eK	udCRXfAt(sizeof(BNtSo1rKXcN) * YRoY3Fu7d5N7)


/*
** Shift left operation. (Shift right just negates 'y'.)
*/
BNtSo1rKXcN CTIuaOnHUZ (BNtSo1rKXcN PwpCR5PT6e2b, BNtSo1rKXcN tFYYFQCmgL) {
  if (tFYYFQCmgL < 0) {  /* shift right? */
    if (tFYYFQCmgL <= -AyL4eK) return 0;
    else return xqxC(>>, PwpCR5PT6e2b, -tFYYFQCmgL);
  }
  else {  /* shift left */
    if (tFYYFQCmgL >= AyL4eK) return 0;
    else return xqxC(<<, PwpCR5PT6e2b, tFYYFQCmgL);
  }
}


/*
** create a new Lua closure, push it in the stack, and initialize
** its upvalues.
*/
static void Ukhp479gyXxhv (pDZR0yI2U5MV *hQ6BhxKI, voRDkmc *z71iwG4kUN, ct62ZDxsLmX **S9j3hBP, na0AtGv0_M Wv4svkLK,
                         na0AtGv0_M loAh3) {
  int XAbKW = z71iwG4kUN->CuCMXDEXlhZ;
  yhNR6 *hcE958JW3 = z71iwG4kUN->tJhhao9d;
  int KsK1Stf;
  Cm5tegG *NYym0jylfax7a = E7DfFwPY0JG39(hQ6BhxKI, XAbKW);
  NYym0jylfax7a->z71iwG4kUN = z71iwG4kUN;
  e_3M(hQ6BhxKI, loAh3, NYym0jylfax7a);  /* anchor new closure in stack */
  for (KsK1Stf = 0; KsK1Stf < XAbKW; KsK1Stf++) {  /* fill in its upvalues */
    if (hcE958JW3[KsK1Stf].T67b)  /* upvalue refers to local variable? */
      NYym0jylfax7a->yw5ayV8N4[KsK1Stf] = kU9go5jsQylZ(hQ6BhxKI, Wv4svkLK + hcE958JW3[KsK1Stf].xZZYog6);
    else  /* get upvalue from enclosing function */
      NYym0jylfax7a->yw5ayV8N4[KsK1Stf] = S9j3hBP[hcE958JW3[KsK1Stf].xZZYog6];
    xtR3Yh(hQ6BhxKI, NYym0jylfax7a, NYym0jylfax7a->yw5ayV8N4[KsK1Stf]);
  }
}


/*
** finish execution of an opcode interrupted by a yield
*/
void CMEjpeJSI14 (pDZR0yI2U5MV *hQ6BhxKI) {
  b3wFV *rcB6Iscy = hQ6BhxKI->rcB6Iscy;
  na0AtGv0_M Wv4svkLK = rcB6Iscy->jAov1dj.z71iwG4kUN + 1;
  pGae ai8iF5k = *(rcB6Iscy->kEYsJ.RF72ZUXWIFi.TR9Ucs - 1);  /* interrupted instruction */
  LO8W Lc5FOaPcPuY = DwaGEycz4v(ai8iF5k);
  switch (Lc5FOaPcPuY) {  /* finish its execution */
    case CU1Y82J: case hHqE_YHyYXXE: case Tg2yLZqa: {
      MDzOh(hQ6BhxKI, Wv4svkLK + g5GaVjjdmlxGK(*(rcB6Iscy->kEYsJ.RF72ZUXWIFi.TR9Ucs - 2)), --hQ6BhxKI->N4NZKKFHVF2.z71iwG4kUN);
      break;
    }
    case PDIgUQW2Kan: case M1qzv7: case KoFVshj:
    case AENNgFNN3: case fCdRl: case twdxeOQtUv6ZD:
    case x1wgIOyi5fe: case kkcpPTTykrv: {
      MDzOh(hQ6BhxKI, Wv4svkLK + g5GaVjjdmlxGK(ai8iF5k), --hQ6BhxKI->N4NZKKFHVF2.z71iwG4kUN);
      break;
    }
    case Ilaka: case UhaCTl:
    case hsuBZKdLKX4v2: case Ej8mmGkeUz:
    case Wwg1uma: case WqZcQR:
    case XA7jImYBw8: {  /* note that 'OP_EQI'/'OP_EQK' cannot yield */
      int vFSf = !BjtKn8aps(dRPEeVWBAygZ(hQ6BhxKI->N4NZKKFHVF2.z71iwG4kUN - 1));
      hQ6BhxKI->N4NZKKFHVF2.z71iwG4kUN--;
#if z7VU8a7FElM(e_uOK61Ui)
      if (rcB6Iscy->amkqpYHeWJCS & Y3hsGy5LQ0zr) {  /* "<=" using "<" instead? */
        rcB6Iscy->amkqpYHeWJCS ^= Y3hsGy5LQ0zr;  /* clear mark */
        vFSf = !vFSf;  /* negate result */
      }
#endif
      bmeZHZ5YL(DwaGEycz4v(*rcB6Iscy->kEYsJ.RF72ZUXWIFi.TR9Ucs) == iOe2);
      if (vFSf != ZTL5SN0eDA(ai8iF5k))  /* condition failed? */
        rcB6Iscy->kEYsJ.RF72ZUXWIFi.TR9Ucs++;  /* skip jump instruction */
      break;
    }
    case qxaIYQuLyAv: {
      na0AtGv0_M N4NZKKFHVF2 = hQ6BhxKI->N4NZKKFHVF2.z71iwG4kUN - 1;  /* top when 'luaT_tryconcatTM' was called */
      int Vt3gklIYlx = g5GaVjjdmlxGK(ai8iF5k);      /* first element to concatenate */
      int u2H1oSN = udCRXfAt(N4NZKKFHVF2 - 1 - (Wv4svkLK + Vt3gklIYlx));  /* yet to concatenate */
      MDzOh(hQ6BhxKI, N4NZKKFHVF2 - 2, N4NZKKFHVF2);  /* put TM result in proper position */
      hQ6BhxKI->N4NZKKFHVF2.z71iwG4kUN = N4NZKKFHVF2 - 1;  /* top is one after last element (at top-2) */
      O3E5ea4xoIP(hQ6BhxKI, u2H1oSN);  /* concat them (may yield again) */
      break;
    }
    case L1XBI8fvbs4: {  /* yielded closing variables */
      rcB6Iscy->kEYsJ.RF72ZUXWIFi.TR9Ucs--;  /* repeat instruction to close other vars. */
      break;
    }
    case QI2QSExRD: {  /* yielded closing variables */
      na0AtGv0_M loAh3 = Wv4svkLK + g5GaVjjdmlxGK(ai8iF5k);
      /* adjust top to signal correct number of returns, in case the
         return is "up to top" ('isIT') */
      hQ6BhxKI->N4NZKKFHVF2.z71iwG4kUN = loAh3 + rcB6Iscy->QtZ6e.PyVgbXR;
      /* repeat instruction to close other vars. and complete the return */
      rcB6Iscy->kEYsJ.RF72ZUXWIFi.TR9Ucs--;
      break;
    }
    default: {
      /* only these other opcodes can yield */
      bmeZHZ5YL(Lc5FOaPcPuY == ZUOLrvPTwmTY || Lc5FOaPcPuY == QWDz ||
           Lc5FOaPcPuY == GarU1U || Lc5FOaPcPuY == DtPxe || Lc5FOaPcPuY == o0OPCSFQK ||
           Lc5FOaPcPuY == kaDyy5 || Lc5FOaPcPuY == NMnQjbIR7U_OO);
      break;
    }
  }
}




/*
** {==================================================================
** Macros for arithmetic/bitwise/comparison opcodes in 'luaV_execute'
** ===================================================================
*/

#define nTR_Bz(hQ6BhxKI,Vt3gklIYlx,dF52pOlLbm0kY)	xqxC(+, Vt3gklIYlx, dF52pOlLbm0kY)
#define AxHoxe(hQ6BhxKI,Vt3gklIYlx,dF52pOlLbm0kY)	xqxC(-, Vt3gklIYlx, dF52pOlLbm0kY)
#define MzhNbGn4X(hQ6BhxKI,Vt3gklIYlx,dF52pOlLbm0kY)	xqxC(*, Vt3gklIYlx, dF52pOlLbm0kY)
#define MqIk5vGZPQLv(Vt3gklIYlx,dF52pOlLbm0kY)	xqxC(&, Vt3gklIYlx, dF52pOlLbm0kY)
#define OqGWK9WP(Vt3gklIYlx,dF52pOlLbm0kY)	xqxC(|, Vt3gklIYlx, dF52pOlLbm0kY)
#define voJZ5yHOeAqI(Vt3gklIYlx,dF52pOlLbm0kY)	xqxC(^, Vt3gklIYlx, dF52pOlLbm0kY)

#define ev5SG7Pi92vy(Vt3gklIYlx,dF52pOlLbm0kY)	(Vt3gklIYlx < dF52pOlLbm0kY)
#define MHwMnmIQ9bSl9(Vt3gklIYlx,dF52pOlLbm0kY)	(Vt3gklIYlx <= dF52pOlLbm0kY)
#define l7GSRyVPytDH(Vt3gklIYlx,dF52pOlLbm0kY)	(Vt3gklIYlx > dF52pOlLbm0kY)
#define xCqfFIMLbW(Vt3gklIYlx,dF52pOlLbm0kY)	(Vt3gklIYlx >= dF52pOlLbm0kY)


/*
** Arithmetic operations with immediate operands. 'iop' is the integer
** operation, 'fop' is the float operation.
*/
#define kwnsefT(hQ6BhxKI,hIhZg9,YWGP5Ef1) {  \
  na0AtGv0_M loAh3 = K8S6RUO(KsK1Stf); \
  mmkodd *AJtLA = aRrMTI25h3G(KsK1Stf);  \
  int of5PdvEwesxAF = XHm6WcW6Rte(KsK1Stf);  \
  if (rTcNZDWpyB(AJtLA)) {  \
    BNtSo1rKXcN dONMoyWQbC = xE5QGsbvl7Zh(AJtLA);  \
    etnzw9Klu++; H7MWC(dRPEeVWBAygZ(loAh3), hIhZg9(hQ6BhxKI, dONMoyWQbC, of5PdvEwesxAF));  \
  }  \
  else if (gGXJzxNvYy(AJtLA)) {  \
    bUfv930Md DAPqQw9On = Kjv2n(AJtLA);  \
    bUfv930Md VPQi = oEynlK(of5PdvEwesxAF);  \
    etnzw9Klu++; b7EFy1eY(dRPEeVWBAygZ(loAh3), YWGP5Ef1(hQ6BhxKI, DAPqQw9On, VPQi)); \
  }}


/*
** Auxiliary function for arithmetic operations over floats and others
** with two register operands.
*/
#define Jr5J(hQ6BhxKI,AJtLA,VPtcIGtXctUBF,YWGP5Ef1) {  \
  bUfv930Md FiyiOV19Xnr; bUfv930Md Dg223tMHyUr;  \
  if (GWOTZYDw4l(AJtLA, FiyiOV19Xnr) && GWOTZYDw4l(VPtcIGtXctUBF, Dg223tMHyUr)) {  \
    etnzw9Klu++; b7EFy1eY(dRPEeVWBAygZ(loAh3), YWGP5Ef1(hQ6BhxKI, FiyiOV19Xnr, Dg223tMHyUr));  \
  }}


/*
** Arithmetic operations over floats and others with register operands.
*/
#define owwt3kl(hQ6BhxKI,YWGP5Ef1) {  \
  na0AtGv0_M loAh3 = K8S6RUO(KsK1Stf); \
  mmkodd *AJtLA = aRrMTI25h3G(KsK1Stf);  \
  mmkodd *VPtcIGtXctUBF = zfkKDi(KsK1Stf);  \
  Jr5J(hQ6BhxKI, AJtLA, VPtcIGtXctUBF, YWGP5Ef1); }


/*
** Arithmetic operations with K operands for floats.
*/
#define h8Il(hQ6BhxKI,YWGP5Ef1) {  \
  na0AtGv0_M loAh3 = K8S6RUO(KsK1Stf); \
  mmkodd *AJtLA = aRrMTI25h3G(KsK1Stf);  \
  mmkodd *VPtcIGtXctUBF = AnhoR(KsK1Stf); bmeZHZ5YL(E6mQUnF_GYWxF(VPtcIGtXctUBF));  \
  Jr5J(hQ6BhxKI, AJtLA, VPtcIGtXctUBF, YWGP5Ef1); }


/*
** Arithmetic operations over integers and floats.
*/
#define hnLf04YZtV(hQ6BhxKI,AJtLA,VPtcIGtXctUBF,hIhZg9,YWGP5Ef1) {  \
  na0AtGv0_M loAh3 = K8S6RUO(KsK1Stf); \
  if (rTcNZDWpyB(AJtLA) && rTcNZDWpyB(VPtcIGtXctUBF)) {  \
    BNtSo1rKXcN spRPd = xE5QGsbvl7Zh(AJtLA); BNtSo1rKXcN Neym = xE5QGsbvl7Zh(VPtcIGtXctUBF);  \
    etnzw9Klu++; H7MWC(dRPEeVWBAygZ(loAh3), hIhZg9(hQ6BhxKI, spRPd, Neym));  \
  }  \
  else Jr5J(hQ6BhxKI, AJtLA, VPtcIGtXctUBF, YWGP5Ef1); }


/*
** Arithmetic operations with register operands.
*/
#define KRHBywlvJ(hQ6BhxKI,hIhZg9,YWGP5Ef1) {  \
  mmkodd *AJtLA = aRrMTI25h3G(KsK1Stf);  \
  mmkodd *VPtcIGtXctUBF = zfkKDi(KsK1Stf);  \
  hnLf04YZtV(hQ6BhxKI, AJtLA, VPtcIGtXctUBF, hIhZg9, YWGP5Ef1); }


/*
** Arithmetic operations with K operands.
*/
#define bT3Nxl93(hQ6BhxKI,hIhZg9,YWGP5Ef1) {  \
  mmkodd *AJtLA = aRrMTI25h3G(KsK1Stf);  \
  mmkodd *VPtcIGtXctUBF = AnhoR(KsK1Stf); bmeZHZ5YL(E6mQUnF_GYWxF(VPtcIGtXctUBF));  \
  hnLf04YZtV(hQ6BhxKI, AJtLA, VPtcIGtXctUBF, hIhZg9, YWGP5Ef1); }


/*
** Bitwise operations with constant operand.
*/
#define wXwxN8(hQ6BhxKI,Lc5FOaPcPuY) {  \
  na0AtGv0_M loAh3 = K8S6RUO(KsK1Stf); \
  mmkodd *AJtLA = aRrMTI25h3G(KsK1Stf);  \
  mmkodd *VPtcIGtXctUBF = AnhoR(KsK1Stf);  \
  BNtSo1rKXcN spRPd;  \
  BNtSo1rKXcN Neym = xE5QGsbvl7Zh(VPtcIGtXctUBF);  \
  if (j_mNyBlg(AJtLA, &spRPd)) {  \
    etnzw9Klu++; H7MWC(dRPEeVWBAygZ(loAh3), Lc5FOaPcPuY(spRPd, Neym));  \
  }}


/*
** Bitwise operations with register operands.
*/
#define mRNMtu_8vy8(hQ6BhxKI,Lc5FOaPcPuY) {  \
  na0AtGv0_M loAh3 = K8S6RUO(KsK1Stf); \
  mmkodd *AJtLA = aRrMTI25h3G(KsK1Stf);  \
  mmkodd *VPtcIGtXctUBF = zfkKDi(KsK1Stf);  \
  BNtSo1rKXcN spRPd; BNtSo1rKXcN Neym;  \
  if (j_mNyBlg(AJtLA, &spRPd) && j_mNyBlg(VPtcIGtXctUBF, &Neym)) {  \
    etnzw9Klu++; H7MWC(dRPEeVWBAygZ(loAh3), Lc5FOaPcPuY(spRPd, Neym));  \
  }}


/*
** Order operations with register operands. 'opn' actually works
** for all numbers, but the fast track improves performance for
** integers.
*/
#define Ibs9JdH5GP(hQ6BhxKI,pMXNnFpVcxIC7,cUIZyBPmk4,Qvxt1) {  \
  na0AtGv0_M loAh3 = K8S6RUO(KsK1Stf); \
  int TyJS9;  \
  mmkodd *VS77ocbXM1 = aRrMTI25h3G(KsK1Stf);  \
  if (rTcNZDWpyB(dRPEeVWBAygZ(loAh3)) && rTcNZDWpyB(VS77ocbXM1)) {  \
    BNtSo1rKXcN Dmg2N = xE5QGsbvl7Zh(dRPEeVWBAygZ(loAh3));  \
    BNtSo1rKXcN YuMEtRb = xE5QGsbvl7Zh(VS77ocbXM1);  \
    TyJS9 = pMXNnFpVcxIC7(Dmg2N, YuMEtRb);  \
  }  \
  else if (E6mQUnF_GYWxF(dRPEeVWBAygZ(loAh3)) && E6mQUnF_GYWxF(VS77ocbXM1))  \
    TyJS9 = cUIZyBPmk4(dRPEeVWBAygZ(loAh3), VS77ocbXM1);  \
  else  \
    ILkIE(TyJS9 = Qvxt1(hQ6BhxKI, dRPEeVWBAygZ(loAh3), VS77ocbXM1));  \
  lRSeTSRz(); }


/*
** Order operations with immediate operand. (Immediate operand is
** always small enough to have an exact representation as a float.)
*/
#define vmMT(hQ6BhxKI,pMXNnFpVcxIC7,H6qB,tKJD,ikld93jk2wf) {  \
  na0AtGv0_M loAh3 = K8S6RUO(KsK1Stf); \
  int TyJS9;  \
  int y9FFF6Vhn = bQLGd(KsK1Stf);  \
  if (rTcNZDWpyB(dRPEeVWBAygZ(loAh3)))  \
    TyJS9 = pMXNnFpVcxIC7(xE5QGsbvl7Zh(dRPEeVWBAygZ(loAh3)), y9FFF6Vhn);  \
  else if (gGXJzxNvYy(dRPEeVWBAygZ(loAh3))) {  \
    bUfv930Md XcvkS3YKQY = Kjv2n(dRPEeVWBAygZ(loAh3));  \
    bUfv930Md oX13 = oEynlK(y9FFF6Vhn);  \
    TyJS9 = H6qB(XcvkS3YKQY, oX13);  \
  }  \
  else {  \
    int CguId = nIYjjkLKEnn(KsK1Stf);  \
    ILkIE(TyJS9 = OajSUhT4fEKIB(hQ6BhxKI, dRPEeVWBAygZ(loAh3), y9FFF6Vhn, tKJD, CguId, ikld93jk2wf));  \
  }  \
  lRSeTSRz(); }

/* }================================================================== */


/*
** {==================================================================
** Function 'luaV_execute': main interpreter loop
** ===================================================================
*/

/*
** some macros for common tasks in 'luaV_execute'
*/


#define K8S6RUO(KsK1Stf)	(Wv4svkLK+g5GaVjjdmlxGK(KsK1Stf))
#define qXiuy(KsK1Stf)	(Wv4svkLK+OSowW(KsK1Stf))
#define aRrMTI25h3G(KsK1Stf)	dRPEeVWBAygZ(qXiuy(KsK1Stf))
#define qURdLAN(KsK1Stf)	(K_k8eAwMw+OSowW(KsK1Stf))
#define cpgGX8_MqZ3(KsK1Stf)	(Wv4svkLK+nIYjjkLKEnn(KsK1Stf))
#define zfkKDi(KsK1Stf)	dRPEeVWBAygZ(cpgGX8_MqZ3(KsK1Stf))
#define AnhoR(KsK1Stf)	(K_k8eAwMw+nIYjjkLKEnn(KsK1Stf))
#define hGXxq1e1elZh(KsK1Stf)	((AGl2_XrlE24(KsK1Stf)) ? K_k8eAwMw + nIYjjkLKEnn(KsK1Stf) : dRPEeVWBAygZ(Wv4svkLK + nIYjjkLKEnn(KsK1Stf)))



#define MnHt(rcB6Iscy)  (JL71GGh7iX = rcB6Iscy->kEYsJ.RF72ZUXWIFi.JL71GGh7iX)

#define LNpb_hU8DJpJ(rcB6Iscy)	(Wv4svkLK = rcB6Iscy->jAov1dj.z71iwG4kUN + 1)


#define g7PZPk7HxG(rcB6Iscy)  \
	{ if (zGtwMpntf(JL71GGh7iX)) { LNpb_hU8DJpJ(rcB6Iscy); loAh3 = K8S6RUO(KsK1Stf); } }


/*
** Execute a jump instruction. The 'updatetrap' allows signals to stop
** tight loops. (Without it, the local copy of 'trap' could never change.)
*/
#define EpN9N7_pyGz(rcB6Iscy,KsK1Stf,F35sH)	{ etnzw9Klu += uPYH(KsK1Stf) + F35sH; MnHt(rcB6Iscy); }


/* for test instructions, execute the jump instruction that follows it */
#define I1j_G(rcB6Iscy)	{ pGae rpoEMmVvH = *etnzw9Klu; EpN9N7_pyGz(rcB6Iscy, rpoEMmVvH, 1); }

/*
** do a conditional jump: skip next instruction if 'cond' is not what
** was expected (parameter 'k'), else do next instruction, which must
** be a jump.
*/
#define lRSeTSRz()	if (TyJS9 != ZTL5SN0eDA(KsK1Stf)) etnzw9Klu++; else I1j_G(rcB6Iscy);


/*
** Correct global 'pc'.
*/
#define svxRSyZDa(hQ6BhxKI)	(rcB6Iscy->kEYsJ.RF72ZUXWIFi.TR9Ucs = etnzw9Klu)


/*
** Whenever code can raise errors, the global 'pc' and the global
** 'top' must be correct to report occasional errors.
*/
#define u_MH5x(hQ6BhxKI,rcB6Iscy)		(svxRSyZDa(hQ6BhxKI), hQ6BhxKI->N4NZKKFHVF2.z71iwG4kUN = rcB6Iscy->N4NZKKFHVF2.z71iwG4kUN)


/*
** Protect code that, in general, can raise errors, reallocate the
** stack, and change the hooks.
*/
#define ILkIE(a5nn)  (u_MH5x(hQ6BhxKI,rcB6Iscy), (a5nn), MnHt(rcB6Iscy))

/* special version that does not change the top */
#define nK0xZy(a5nn)  (svxRSyZDa(hQ6BhxKI), (a5nn), MnHt(rcB6Iscy))

/*
** Protect code that can only raise errors. (That is, it cannot change
** the stack or hooks.)
*/
#define iitxltBo(a5nn)  (u_MH5x(hQ6BhxKI,rcB6Iscy), (a5nn))

/* 'c' is the limit of live values in the stack */
#define fprvE5(hQ6BhxKI,MOutALTL)  \
	{ NcL8sjFnuoUi(hQ6BhxKI, (svxRSyZDa(hQ6BhxKI), hQ6BhxKI->N4NZKKFHVF2.z71iwG4kUN = (MOutALTL)), \
                         MnHt(rcB6Iscy)); \
           O83K(hQ6BhxKI); }


/* fetch an instruction and prepare its execution */
#define H1ZYso25l7S()	{ \
  if (zGtwMpntf(JL71GGh7iX)) {  /* stack reallocation or hooks? */ \
    JL71GGh7iX = UHT0FKni(hQ6BhxKI, etnzw9Klu);  /* handle hooks */ \
    LNpb_hU8DJpJ(rcB6Iscy);  /* correct stack */ \
  } \
  KsK1Stf = *(etnzw9Klu++); \
}

#define evIo2RR3NB6(X2Do7Z)	switch(X2Do7Z)
#define hKFhT(RF72ZUXWIFi)	case RF72ZUXWIFi:
#define tA5_Uq		break


void ejZPEA9k1 (pDZR0yI2U5MV *hQ6BhxKI, b3wFV *rcB6Iscy) {
  Cm5tegG *O981wbXvaCjG;
  mmkodd *K_k8eAwMw;
  na0AtGv0_M Wv4svkLK;
  const pGae *etnzw9Klu;
  int JL71GGh7iX;
#if ShP0J
#include "ljumptab.h"
#endif
 HN_hrSQ:
  JL71GGh7iX = hQ6BhxKI->mf0zmlGBnPyia;
 ITmb6qcI:  /* trap already set */
  O981wbXvaCjG = j81PHALP44b(rcB6Iscy);
  K_k8eAwMw = O981wbXvaCjG->z71iwG4kUN->K_k8eAwMw;
  etnzw9Klu = rcB6Iscy->kEYsJ.RF72ZUXWIFi.TR9Ucs;
  if (zGtwMpntf(JL71GGh7iX))
    JL71GGh7iX = JFcF(hQ6BhxKI);
  Wv4svkLK = rcB6Iscy->jAov1dj.z71iwG4kUN + 1;
  /* main loop of interpreter */
  for (;;) {
    pGae KsK1Stf;  /* instruction being executed */
    H1ZYso25l7S();
    #if 0
      /* low-level line tracing for debugging Lua */
      BYGHNj("line: %d\n", LOwRi77u(O981wbXvaCjG->z71iwG4kUN, SqUX4Zb(etnzw9Klu, O981wbXvaCjG->z71iwG4kUN)));
    #endif
    bmeZHZ5YL(Wv4svkLK == rcB6Iscy->jAov1dj.z71iwG4kUN + 1);
    bmeZHZ5YL(Wv4svkLK <= hQ6BhxKI->N4NZKKFHVF2.z71iwG4kUN && hQ6BhxKI->N4NZKKFHVF2.z71iwG4kUN <= hQ6BhxKI->Y9sDEQzLKv8.z71iwG4kUN);
    /* invalidate top for instructions not expecting it */
    bmeZHZ5YL(eIu51AV5RiX3K(KsK1Stf) || (cdUvebq(hQ6BhxKI->N4NZKKFHVF2.z71iwG4kUN = Wv4svkLK), 1));
    evIo2RR3NB6 (DwaGEycz4v(KsK1Stf)) {
      hKFhT(obFUhcluKW4Y) {
        na0AtGv0_M loAh3 = K8S6RUO(KsK1Stf);
        MDzOh(hQ6BhxKI, loAh3, qXiuy(KsK1Stf));
        tA5_Uq;
      }
      hKFhT(mp8qRnMH7Pcf) {
        na0AtGv0_M loAh3 = K8S6RUO(KsK1Stf);
        BNtSo1rKXcN dF52pOlLbm0kY = jUCqc(KsK1Stf);
        H7MWC(dRPEeVWBAygZ(loAh3), dF52pOlLbm0kY);
        tA5_Uq;
      }
      hKFhT(CFhhCg) {
        na0AtGv0_M loAh3 = K8S6RUO(KsK1Stf);
        int dF52pOlLbm0kY = jUCqc(KsK1Stf);
        b7EFy1eY(dRPEeVWBAygZ(loAh3), oEynlK(dF52pOlLbm0kY));
        tA5_Uq;
      }
      hKFhT(MbTqiXtF2A6p_) {
        na0AtGv0_M loAh3 = K8S6RUO(KsK1Stf);
        mmkodd *VS77ocbXM1 = K_k8eAwMw + eqOtpS5J4GVq(KsK1Stf);
        SyohHHmkXaA4m(hQ6BhxKI, loAh3, VS77ocbXM1);
        tA5_Uq;
      }
      hKFhT(sT8mC6) {
        na0AtGv0_M loAh3 = K8S6RUO(KsK1Stf);
        mmkodd *VS77ocbXM1;
        VS77ocbXM1 = K_k8eAwMw + XLaTHoL(*etnzw9Klu); etnzw9Klu++;
        SyohHHmkXaA4m(hQ6BhxKI, loAh3, VS77ocbXM1);
        tA5_Uq;
      }
      hKFhT(gKc89yH64gk) {
        na0AtGv0_M loAh3 = K8S6RUO(KsK1Stf);
        LIXazM9ISo(dRPEeVWBAygZ(loAh3));
        tA5_Uq;
      }
      hKFhT(v6WRqK533) {
        na0AtGv0_M loAh3 = K8S6RUO(KsK1Stf);
        LIXazM9ISo(dRPEeVWBAygZ(loAh3));
        etnzw9Klu++;  /* skip next instruction */
        tA5_Uq;
      }
      hKFhT(MUGWGjnTlRSl) {
        na0AtGv0_M loAh3 = K8S6RUO(KsK1Stf);
        gUzDtl7(dRPEeVWBAygZ(loAh3));
        tA5_Uq;
      }
      hKFhT(AUDuoZo88) {
        na0AtGv0_M loAh3 = K8S6RUO(KsK1Stf);
        int dF52pOlLbm0kY = OSowW(KsK1Stf);
        do {
          yTGbaI3zc(dRPEeVWBAygZ(loAh3++));
        } while (dF52pOlLbm0kY--);
        tA5_Uq;
      }
      hKFhT(pO2lIjAcFLOM) {
        na0AtGv0_M loAh3 = K8S6RUO(KsK1Stf);
        int dF52pOlLbm0kY = OSowW(KsK1Stf);
        SyohHHmkXaA4m(hQ6BhxKI, loAh3, O981wbXvaCjG->yw5ayV8N4[dF52pOlLbm0kY]->AXLHIg8G5MbH5.z71iwG4kUN);
        tA5_Uq;
      }
      hKFhT(sX8lgnI432O8n) {
        na0AtGv0_M loAh3 = K8S6RUO(KsK1Stf);
        ct62ZDxsLmX *hcE958JW3 = O981wbXvaCjG->yw5ayV8N4[OSowW(KsK1Stf)];
        plkHvpuJnQ9D(hQ6BhxKI, hcE958JW3->AXLHIg8G5MbH5.z71iwG4kUN, dRPEeVWBAygZ(loAh3));
        r_yMlqv4lL(hQ6BhxKI, hcE958JW3, dRPEeVWBAygZ(loAh3));
        tA5_Uq;
      }
      hKFhT(AENNgFNN3) {
        na0AtGv0_M loAh3 = K8S6RUO(KsK1Stf);
        const mmkodd *c1QXFSzT62rOC;
        mmkodd *PZqkxPC0EB2 = O981wbXvaCjG->yw5ayV8N4[OSowW(KsK1Stf)]->AXLHIg8G5MbH5.z71iwG4kUN;
        mmkodd *GQXwr4 = AnhoR(KsK1Stf);
        Nhm3N8BTNX *wQ2zWqFxxV = jHv4C(GQXwr4);  /* key must be a short string */
        if (rW6UGZRNIUaFF(hQ6BhxKI, PZqkxPC0EB2, wQ2zWqFxxV, c1QXFSzT62rOC, eE6cgD)) {
          SyohHHmkXaA4m(hQ6BhxKI, loAh3, c1QXFSzT62rOC);
        }
        else
          ILkIE(Cay630E5E4C(hQ6BhxKI, PZqkxPC0EB2, GQXwr4, loAh3, c1QXFSzT62rOC));
        tA5_Uq;
      }
      hKFhT(fCdRl) {
        na0AtGv0_M loAh3 = K8S6RUO(KsK1Stf);
        const mmkodd *c1QXFSzT62rOC;
        mmkodd *VS77ocbXM1 = aRrMTI25h3G(KsK1Stf);
        mmkodd *GQXwr4 = zfkKDi(KsK1Stf);
        QZo1Bt9 R6O8jbyQ;
        if (rTcNZDWpyB(GQXwr4)  /* fast track for integers? */
            ? (cdUvebq(R6O8jbyQ = xE5QGsbvl7Zh(GQXwr4)), PRvl9CirWVw(hQ6BhxKI, VS77ocbXM1, R6O8jbyQ, c1QXFSzT62rOC))
            : rW6UGZRNIUaFF(hQ6BhxKI, VS77ocbXM1, GQXwr4, c1QXFSzT62rOC, V2BM)) {
          SyohHHmkXaA4m(hQ6BhxKI, loAh3, c1QXFSzT62rOC);
        }
        else
          ILkIE(Cay630E5E4C(hQ6BhxKI, VS77ocbXM1, GQXwr4, loAh3, c1QXFSzT62rOC));
        tA5_Uq;
      }
      hKFhT(twdxeOQtUv6ZD) {
        na0AtGv0_M loAh3 = K8S6RUO(KsK1Stf);
        const mmkodd *c1QXFSzT62rOC;
        mmkodd *VS77ocbXM1 = aRrMTI25h3G(KsK1Stf);
        int MOutALTL = nIYjjkLKEnn(KsK1Stf);
        if (PRvl9CirWVw(hQ6BhxKI, VS77ocbXM1, MOutALTL, c1QXFSzT62rOC)) {
          SyohHHmkXaA4m(hQ6BhxKI, loAh3, c1QXFSzT62rOC);
        }
        else {
          mmkodd wQ2zWqFxxV;
          H7MWC(&wQ2zWqFxxV, MOutALTL);
          ILkIE(Cay630E5E4C(hQ6BhxKI, VS77ocbXM1, &wQ2zWqFxxV, loAh3, c1QXFSzT62rOC));
        }
        tA5_Uq;
      }
      hKFhT(x1wgIOyi5fe) {
        na0AtGv0_M loAh3 = K8S6RUO(KsK1Stf);
        const mmkodd *c1QXFSzT62rOC;
        mmkodd *VS77ocbXM1 = aRrMTI25h3G(KsK1Stf);
        mmkodd *GQXwr4 = AnhoR(KsK1Stf);
        Nhm3N8BTNX *wQ2zWqFxxV = jHv4C(GQXwr4);  /* key must be a short string */
        if (rW6UGZRNIUaFF(hQ6BhxKI, VS77ocbXM1, wQ2zWqFxxV, c1QXFSzT62rOC, eE6cgD)) {
          SyohHHmkXaA4m(hQ6BhxKI, loAh3, c1QXFSzT62rOC);
        }
        else
          ILkIE(Cay630E5E4C(hQ6BhxKI, VS77ocbXM1, GQXwr4, loAh3, c1QXFSzT62rOC));
        tA5_Uq;
      }
      hKFhT(DtPxe) {
        const mmkodd *c1QXFSzT62rOC;
        mmkodd *PZqkxPC0EB2 = O981wbXvaCjG->yw5ayV8N4[g5GaVjjdmlxGK(KsK1Stf)]->AXLHIg8G5MbH5.z71iwG4kUN;
        mmkodd *VS77ocbXM1 = qURdLAN(KsK1Stf);
        mmkodd *GQXwr4 = hGXxq1e1elZh(KsK1Stf);
        Nhm3N8BTNX *wQ2zWqFxxV = jHv4C(VS77ocbXM1);  /* key must be a short string */
        if (rW6UGZRNIUaFF(hQ6BhxKI, PZqkxPC0EB2, wQ2zWqFxxV, c1QXFSzT62rOC, eE6cgD)) {
          A1pl9d_j44f(hQ6BhxKI, PZqkxPC0EB2, c1QXFSzT62rOC, GQXwr4);
        }
        else
          ILkIE(x2thd(hQ6BhxKI, PZqkxPC0EB2, VS77ocbXM1, GQXwr4, c1QXFSzT62rOC));
        tA5_Uq;
      }
      hKFhT(o0OPCSFQK) {
        na0AtGv0_M loAh3 = K8S6RUO(KsK1Stf);
        const mmkodd *c1QXFSzT62rOC;
        mmkodd *VS77ocbXM1 = aRrMTI25h3G(KsK1Stf);  /* key (table is in 'ra') */
        mmkodd *GQXwr4 = hGXxq1e1elZh(KsK1Stf);  /* value */
        QZo1Bt9 R6O8jbyQ;
        if (rTcNZDWpyB(VS77ocbXM1)  /* fast track for integers? */
            ? (cdUvebq(R6O8jbyQ = xE5QGsbvl7Zh(VS77ocbXM1)), PRvl9CirWVw(hQ6BhxKI, dRPEeVWBAygZ(loAh3), R6O8jbyQ, c1QXFSzT62rOC))
            : rW6UGZRNIUaFF(hQ6BhxKI, dRPEeVWBAygZ(loAh3), VS77ocbXM1, c1QXFSzT62rOC, V2BM)) {
          A1pl9d_j44f(hQ6BhxKI, dRPEeVWBAygZ(loAh3), c1QXFSzT62rOC, GQXwr4);
        }
        else
          ILkIE(x2thd(hQ6BhxKI, dRPEeVWBAygZ(loAh3), VS77ocbXM1, GQXwr4, c1QXFSzT62rOC));
        tA5_Uq;
      }
      hKFhT(kaDyy5) {
        na0AtGv0_M loAh3 = K8S6RUO(KsK1Stf);
        const mmkodd *c1QXFSzT62rOC;
        int MOutALTL = OSowW(KsK1Stf);
        mmkodd *GQXwr4 = hGXxq1e1elZh(KsK1Stf);
        if (PRvl9CirWVw(hQ6BhxKI, dRPEeVWBAygZ(loAh3), MOutALTL, c1QXFSzT62rOC)) {
          A1pl9d_j44f(hQ6BhxKI, dRPEeVWBAygZ(loAh3), c1QXFSzT62rOC, GQXwr4);
        }
        else {
          mmkodd wQ2zWqFxxV;
          H7MWC(&wQ2zWqFxxV, MOutALTL);
          ILkIE(x2thd(hQ6BhxKI, dRPEeVWBAygZ(loAh3), &wQ2zWqFxxV, GQXwr4, c1QXFSzT62rOC));
        }
        tA5_Uq;
      }
      hKFhT(NMnQjbIR7U_OO) {
        na0AtGv0_M loAh3 = K8S6RUO(KsK1Stf);
        const mmkodd *c1QXFSzT62rOC;
        mmkodd *VS77ocbXM1 = qURdLAN(KsK1Stf);
        mmkodd *GQXwr4 = hGXxq1e1elZh(KsK1Stf);
        Nhm3N8BTNX *wQ2zWqFxxV = jHv4C(VS77ocbXM1);  /* key must be a short string */
        if (rW6UGZRNIUaFF(hQ6BhxKI, dRPEeVWBAygZ(loAh3), wQ2zWqFxxV, c1QXFSzT62rOC, eE6cgD)) {
          A1pl9d_j44f(hQ6BhxKI, dRPEeVWBAygZ(loAh3), c1QXFSzT62rOC, GQXwr4);
        }
        else
          ILkIE(x2thd(hQ6BhxKI, dRPEeVWBAygZ(loAh3), VS77ocbXM1, GQXwr4, c1QXFSzT62rOC));
        tA5_Uq;
      }
      hKFhT(LWA0) {
        na0AtGv0_M loAh3 = K8S6RUO(KsK1Stf);
        int dF52pOlLbm0kY = OSowW(KsK1Stf);  /* log2(hash size) + 1 */
        int MOutALTL = nIYjjkLKEnn(KsK1Stf);  /* array size */
        Yk2eE7 *XcFmYCx7;
        if (dF52pOlLbm0kY > 0)
          dF52pOlLbm0kY = 1 << (dF52pOlLbm0kY - 1);  /* size is 2^(b - 1) */
        bmeZHZ5YL((!AGl2_XrlE24(KsK1Stf)) == (XLaTHoL(*etnzw9Klu) == 0));
        if (AGl2_XrlE24(KsK1Stf))  /* non-zero extra argument? */
          MOutALTL += XLaTHoL(*etnzw9Klu) * (xjpdhpIvjydJS + 1);  /* add it to size */
        etnzw9Klu++;  /* skip extra argument */
        hQ6BhxKI->N4NZKKFHVF2.z71iwG4kUN = loAh3 + 1;  /* correct top in case of emergency GC */
        XcFmYCx7 = Akm8w_6Fbys(hQ6BhxKI);  /* memory allocation */
        Uj8DORTgJYraT(hQ6BhxKI, loAh3, XcFmYCx7);
        if (dF52pOlLbm0kY != 0 || MOutALTL != 0)
          gG7rgrtJ(hQ6BhxKI, XcFmYCx7, MOutALTL, dF52pOlLbm0kY);  /* idem */
        fprvE5(hQ6BhxKI, loAh3 + 1);
        tA5_Uq;
      }
      hKFhT(kkcpPTTykrv) {
        na0AtGv0_M loAh3 = K8S6RUO(KsK1Stf);
        const mmkodd *c1QXFSzT62rOC;
        mmkodd *VS77ocbXM1 = aRrMTI25h3G(KsK1Stf);
        mmkodd *GQXwr4 = hGXxq1e1elZh(KsK1Stf);
        Nhm3N8BTNX *wQ2zWqFxxV = jHv4C(GQXwr4);  /* key must be a string */
        SyohHHmkXaA4m(hQ6BhxKI, loAh3 + 1, VS77ocbXM1);
        if (rW6UGZRNIUaFF(hQ6BhxKI, VS77ocbXM1, wQ2zWqFxxV, c1QXFSzT62rOC, c_QqzaeWSKm)) {
          SyohHHmkXaA4m(hQ6BhxKI, loAh3, c1QXFSzT62rOC);
        }
        else
          ILkIE(Cay630E5E4C(hQ6BhxKI, VS77ocbXM1, GQXwr4, loAh3, c1QXFSzT62rOC));
        tA5_Uq;
      }
      hKFhT(HVv5tJvqMMR_f) {
        kwnsefT(hQ6BhxKI, nTR_Bz, h0CFZSr2);
        tA5_Uq;
      }
      hKFhT(ziWH) {
        bT3Nxl93(hQ6BhxKI, nTR_Bz, h0CFZSr2);
        tA5_Uq;
      }
      hKFhT(sTFwVesseo) {
        bT3Nxl93(hQ6BhxKI, AxHoxe, z84QBT5o);
        tA5_Uq;
      }
      hKFhT(kKz971h) {
        bT3Nxl93(hQ6BhxKI, MzhNbGn4X, P9SKDEA54PuO);
        tA5_Uq;
      }
      hKFhT(cRZWRZ) {
        u_MH5x(hQ6BhxKI, rcB6Iscy);  /* in case of division by 0 */
        bT3Nxl93(hQ6BhxKI, uZSP6, YGJVfN);
        tA5_Uq;
      }
      hKFhT(xlfaUuYe) {
        h8Il(hQ6BhxKI, RoFztex);
        tA5_Uq;
      }
      hKFhT(ZdIU) {
        h8Il(hQ6BhxKI, XvPfi2WUCu);
        tA5_Uq;
      }
      hKFhT(wOfdxLVV) {
        u_MH5x(hQ6BhxKI, rcB6Iscy);  /* in case of division by 0 */
        bT3Nxl93(hQ6BhxKI, l9NWfLI, AnSFsxJ8D);
        tA5_Uq;
      }
      hKFhT(n6DAb) {
        wXwxN8(hQ6BhxKI, MqIk5vGZPQLv);
        tA5_Uq;
      }
      hKFhT(ep5Pa) {
        wXwxN8(hQ6BhxKI, OqGWK9WP);
        tA5_Uq;
      }
      hKFhT(cWkXYrRCViS1) {
        wXwxN8(hQ6BhxKI, voJZ5yHOeAqI);
        tA5_Uq;
      }
      hKFhT(NG_mW8jV4v) {
        na0AtGv0_M loAh3 = K8S6RUO(KsK1Stf);
        mmkodd *VS77ocbXM1 = aRrMTI25h3G(KsK1Stf);
        int dGxD7hakgiD = XHm6WcW6Rte(KsK1Stf);
        BNtSo1rKXcN YuMEtRb;
        if (j_mNyBlg(VS77ocbXM1, &YuMEtRb)) {
          etnzw9Klu++; H7MWC(dRPEeVWBAygZ(loAh3), CTIuaOnHUZ(YuMEtRb, -dGxD7hakgiD));
        }
        tA5_Uq;
      }
      hKFhT(pDtF712) {
        na0AtGv0_M loAh3 = K8S6RUO(KsK1Stf);
        mmkodd *VS77ocbXM1 = aRrMTI25h3G(KsK1Stf);
        int dGxD7hakgiD = XHm6WcW6Rte(KsK1Stf);
        BNtSo1rKXcN YuMEtRb;
        if (j_mNyBlg(VS77ocbXM1, &YuMEtRb)) {
          etnzw9Klu++; H7MWC(dRPEeVWBAygZ(loAh3), CTIuaOnHUZ(dGxD7hakgiD, YuMEtRb));
        }
        tA5_Uq;
      }
      hKFhT(lU9Tyeanm2M8H) {
        KRHBywlvJ(hQ6BhxKI, nTR_Bz, h0CFZSr2);
        tA5_Uq;
      }
      hKFhT(agXigi7C) {
        KRHBywlvJ(hQ6BhxKI, AxHoxe, z84QBT5o);
        tA5_Uq;
      }
      hKFhT(AX2MQ) {
        KRHBywlvJ(hQ6BhxKI, MzhNbGn4X, P9SKDEA54PuO);
        tA5_Uq;
      }
      hKFhT(MxZFt8cBxwY7j) {
        u_MH5x(hQ6BhxKI, rcB6Iscy);  /* in case of division by 0 */
        KRHBywlvJ(hQ6BhxKI, uZSP6, YGJVfN);
        tA5_Uq;
      }
      hKFhT(zYc64ffe_z) {
        owwt3kl(hQ6BhxKI, RoFztex);
        tA5_Uq;
      }
      hKFhT(Y43xeLMTaab) {  /* float division (always with floats) */
        owwt3kl(hQ6BhxKI, XvPfi2WUCu);
        tA5_Uq;
      }
      hKFhT(nrJB1KXsz) {  /* floor division */
        u_MH5x(hQ6BhxKI, rcB6Iscy);  /* in case of division by 0 */
        KRHBywlvJ(hQ6BhxKI, l9NWfLI, AnSFsxJ8D);
        tA5_Uq;
      }
      hKFhT(uJ8Ty) {
        mRNMtu_8vy8(hQ6BhxKI, MqIk5vGZPQLv);
        tA5_Uq;
      }
      hKFhT(QtWEZvToWO5) {
        mRNMtu_8vy8(hQ6BhxKI, OqGWK9WP);
        tA5_Uq;
      }
      hKFhT(lXRZ5PUvhaEqJ) {
        mRNMtu_8vy8(hQ6BhxKI, voJZ5yHOeAqI);
        tA5_Uq;
      }
      hKFhT(ouxlJWuqw) {
        mRNMtu_8vy8(hQ6BhxKI, MuCyoxd);
        tA5_Uq;
      }
      hKFhT(hijtCoU) {
        mRNMtu_8vy8(hQ6BhxKI, CTIuaOnHUZ);
        tA5_Uq;
      }
      hKFhT(CU1Y82J) {
        na0AtGv0_M loAh3 = K8S6RUO(KsK1Stf);
        pGae il647JDaHRX = *(etnzw9Klu - 2);  /* original arith. expression */
        mmkodd *VS77ocbXM1 = aRrMTI25h3G(KsK1Stf);
        ePjTcxo8bU ikld93jk2wf = (ePjTcxo8bU)nIYjjkLKEnn(KsK1Stf);
        na0AtGv0_M Cp8mfhMvmD = K8S6RUO(il647JDaHRX);
        bmeZHZ5YL(lU9Tyeanm2M8H <= DwaGEycz4v(il647JDaHRX) && DwaGEycz4v(il647JDaHRX) <= ouxlJWuqw);
        ILkIE(nICRU3okLzc(hQ6BhxKI, dRPEeVWBAygZ(loAh3), VS77ocbXM1, Cp8mfhMvmD, ikld93jk2wf));
        tA5_Uq;
      }
      hKFhT(hHqE_YHyYXXE) {
        na0AtGv0_M loAh3 = K8S6RUO(KsK1Stf);
        pGae il647JDaHRX = *(etnzw9Klu - 2);  /* original arith. expression */
        int of5PdvEwesxAF = bQLGd(KsK1Stf);
        ePjTcxo8bU ikld93jk2wf = (ePjTcxo8bU)nIYjjkLKEnn(KsK1Stf);
        int c9wOVB = ZTL5SN0eDA(KsK1Stf);
        na0AtGv0_M Cp8mfhMvmD = K8S6RUO(il647JDaHRX);
        ILkIE(gzmEuk(hQ6BhxKI, dRPEeVWBAygZ(loAh3), of5PdvEwesxAF, c9wOVB, Cp8mfhMvmD, ikld93jk2wf));
        tA5_Uq;
      }
      hKFhT(Tg2yLZqa) {
        na0AtGv0_M loAh3 = K8S6RUO(KsK1Stf);
        pGae il647JDaHRX = *(etnzw9Klu - 2);  /* original arith. expression */
        mmkodd *of5PdvEwesxAF = qURdLAN(KsK1Stf);
        ePjTcxo8bU ikld93jk2wf = (ePjTcxo8bU)nIYjjkLKEnn(KsK1Stf);
        int c9wOVB = ZTL5SN0eDA(KsK1Stf);
        na0AtGv0_M Cp8mfhMvmD = K8S6RUO(il647JDaHRX);
        ILkIE(W1Ywiq(hQ6BhxKI, dRPEeVWBAygZ(loAh3), of5PdvEwesxAF, c9wOVB, Cp8mfhMvmD, ikld93jk2wf));
        tA5_Uq;
      }
      hKFhT(PDIgUQW2Kan) {
        na0AtGv0_M loAh3 = K8S6RUO(KsK1Stf);
        mmkodd *VS77ocbXM1 = aRrMTI25h3G(KsK1Stf);
        bUfv930Md DAPqQw9On;
        if (rTcNZDWpyB(VS77ocbXM1)) {
          BNtSo1rKXcN YuMEtRb = xE5QGsbvl7Zh(VS77ocbXM1);
          H7MWC(dRPEeVWBAygZ(loAh3), xqxC(-, 0, YuMEtRb));
        }
        else if (GWOTZYDw4l(VS77ocbXM1, DAPqQw9On)) {
          b7EFy1eY(dRPEeVWBAygZ(loAh3), ag4e(hQ6BhxKI, DAPqQw9On));
        }
        else
          ILkIE(nICRU3okLzc(hQ6BhxKI, VS77ocbXM1, VS77ocbXM1, loAh3, hPepbin6yNw));
        tA5_Uq;
      }
      hKFhT(M1qzv7) {
        na0AtGv0_M loAh3 = K8S6RUO(KsK1Stf);
        mmkodd *VS77ocbXM1 = aRrMTI25h3G(KsK1Stf);
        BNtSo1rKXcN YuMEtRb;
        if (j_mNyBlg(VS77ocbXM1, &YuMEtRb)) {
          H7MWC(dRPEeVWBAygZ(loAh3), xqxC(^, ~hcF9Uh(0), YuMEtRb));
        }
        else
          ILkIE(nICRU3okLzc(hQ6BhxKI, VS77ocbXM1, VS77ocbXM1, loAh3, koC9176Ry));
        tA5_Uq;
      }
      hKFhT(dfg20_i77Uk3v) {
        na0AtGv0_M loAh3 = K8S6RUO(KsK1Stf);
        mmkodd *VS77ocbXM1 = aRrMTI25h3G(KsK1Stf);
        if (BjtKn8aps(VS77ocbXM1))
          gUzDtl7(dRPEeVWBAygZ(loAh3));
        else
          LIXazM9ISo(dRPEeVWBAygZ(loAh3));
        tA5_Uq;
      }
      hKFhT(KoFVshj) {
        na0AtGv0_M loAh3 = K8S6RUO(KsK1Stf);
        ILkIE(LrOGMyup0B6le(hQ6BhxKI, loAh3, aRrMTI25h3G(KsK1Stf)));
        tA5_Uq;
      }
      hKFhT(qxaIYQuLyAv) {
        na0AtGv0_M loAh3 = K8S6RUO(KsK1Stf);
        int R6O8jbyQ = OSowW(KsK1Stf);  /* number of elements to concatenate */
        hQ6BhxKI->N4NZKKFHVF2.z71iwG4kUN = loAh3 + R6O8jbyQ;  /* mark the end of concat operands */
        nK0xZy(O3E5ea4xoIP(hQ6BhxKI, R6O8jbyQ));
        fprvE5(hQ6BhxKI, hQ6BhxKI->N4NZKKFHVF2.z71iwG4kUN); /* 'luaV_concat' ensures correct top */
        tA5_Uq;
      }
      hKFhT(L1XBI8fvbs4) {
        na0AtGv0_M loAh3 = K8S6RUO(KsK1Stf);
        ILkIE(sp0iU(hQ6BhxKI, loAh3, rhjyXkaeTVqx, 1));
        tA5_Uq;
      }
      hKFhT(oio8IO) {
        na0AtGv0_M loAh3 = K8S6RUO(KsK1Stf);
        /* create new to-be-closed upvalue */
        iitxltBo(cd3H(hQ6BhxKI, loAh3));
        tA5_Uq;
      }
      hKFhT(iOe2) {
        EpN9N7_pyGz(rcB6Iscy, KsK1Stf, 0);
        tA5_Uq;
      }
      hKFhT(XA7jImYBw8) {
        na0AtGv0_M loAh3 = K8S6RUO(KsK1Stf);
        int TyJS9;
        mmkodd *VS77ocbXM1 = aRrMTI25h3G(KsK1Stf);
        ILkIE(TyJS9 = Nfyp3ZBHZm(hQ6BhxKI, dRPEeVWBAygZ(loAh3), VS77ocbXM1));
        lRSeTSRz();
        tA5_Uq;
      }
      hKFhT(Ilaka) {
        Ibs9JdH5GP(hQ6BhxKI, ev5SG7Pi92vy, Oolb, TAIyYDaD2);
        tA5_Uq;
      }
      hKFhT(UhaCTl) {
        Ibs9JdH5GP(hQ6BhxKI, MHwMnmIQ9bSl9, jUhkPmg3fmy, es1u);
        tA5_Uq;
      }
      hKFhT(QgM3NZ) {
        na0AtGv0_M loAh3 = K8S6RUO(KsK1Stf);
        mmkodd *VS77ocbXM1 = qURdLAN(KsK1Stf);
        /* basic types do not use '__eq'; we can use raw equality */
        int TyJS9 = lmccdXpvWpn(dRPEeVWBAygZ(loAh3), VS77ocbXM1);
        lRSeTSRz();
        tA5_Uq;
      }
      hKFhT(cwdqyRyJ3sz) {
        na0AtGv0_M loAh3 = K8S6RUO(KsK1Stf);
        int TyJS9;
        int y9FFF6Vhn = bQLGd(KsK1Stf);
        if (rTcNZDWpyB(dRPEeVWBAygZ(loAh3)))
          TyJS9 = (xE5QGsbvl7Zh(dRPEeVWBAygZ(loAh3)) == y9FFF6Vhn);
        else if (gGXJzxNvYy(dRPEeVWBAygZ(loAh3)))
          TyJS9 = VShiL6ZO0yZ(Kjv2n(dRPEeVWBAygZ(loAh3)), oEynlK(y9FFF6Vhn));
        else
          TyJS9 = 0;  /* other types cannot be equal to a number */
        lRSeTSRz();
        tA5_Uq;
      }
      hKFhT(hsuBZKdLKX4v2) {
        vmMT(hQ6BhxKI, ev5SG7Pi92vy, MMmtoRUfODj_a, 0, S0BI4MBnwY0W);
        tA5_Uq;
      }
      hKFhT(Ej8mmGkeUz) {
        vmMT(hQ6BhxKI, MHwMnmIQ9bSl9, c8xolO, 0, JfFwu);
        tA5_Uq;
      }
      hKFhT(Wwg1uma) {
        vmMT(hQ6BhxKI, l7GSRyVPytDH, S1XzuaHUI, 1, S0BI4MBnwY0W);
        tA5_Uq;
      }
      hKFhT(WqZcQR) {
        vmMT(hQ6BhxKI, xCqfFIMLbW, ZwXGA, 1, JfFwu);
        tA5_Uq;
      }
      hKFhT(kBc1wd2s_) {
        na0AtGv0_M loAh3 = K8S6RUO(KsK1Stf);
        int TyJS9 = !BjtKn8aps(dRPEeVWBAygZ(loAh3));
        lRSeTSRz();
        tA5_Uq;
      }
      hKFhT(JEUwUO6) {
        na0AtGv0_M loAh3 = K8S6RUO(KsK1Stf);
        mmkodd *VS77ocbXM1 = aRrMTI25h3G(KsK1Stf);
        if (BjtKn8aps(VS77ocbXM1) == ZTL5SN0eDA(KsK1Stf))
          etnzw9Klu++;
        else {
          SyohHHmkXaA4m(hQ6BhxKI, loAh3, VS77ocbXM1);
          I1j_G(rcB6Iscy);
        }
        tA5_Uq;
      }
      hKFhT(QWDz) {
        na0AtGv0_M loAh3 = K8S6RUO(KsK1Stf);
        b3wFV *WKAiY5Zu;
        int dF52pOlLbm0kY = OSowW(KsK1Stf);
        int NsWfVUXcWQUs = nIYjjkLKEnn(KsK1Stf) - 1;
        if (dF52pOlLbm0kY != 0)  /* fixed number of arguments? */
          hQ6BhxKI->N4NZKKFHVF2.z71iwG4kUN = loAh3 + dF52pOlLbm0kY;  /* top signals number of arguments */
        /* else previous instruction set top */
        svxRSyZDa(hQ6BhxKI);  /* in case of errors */
        if ((WKAiY5Zu = rqqnhHrDalM(hQ6BhxKI, loAh3, NsWfVUXcWQUs)) == dOh0RcNgO)
          MnHt(rcB6Iscy);  /* C call; nothing else to be done */
        else {  /* Lua call: run function in this same C frame */
          rcB6Iscy = WKAiY5Zu;
          goto HN_hrSQ;
        }
        tA5_Uq;
      }
      hKFhT(GarU1U) {
        na0AtGv0_M loAh3 = K8S6RUO(KsK1Stf);
        int dF52pOlLbm0kY = OSowW(KsK1Stf);  /* number of arguments + 1 (function) */
        int R6O8jbyQ;  /* number of results when calling a C function */
        int M5dUFD = nIYjjkLKEnn(KsK1Stf);
        /* delta is virtual 'func' - real 'func' (vararg functions) */
        int dCqPkn = (M5dUFD) ? rcB6Iscy->kEYsJ.RF72ZUXWIFi.BdZfgcC9PEF + M5dUFD : 0;
        if (dF52pOlLbm0kY != 0)
          hQ6BhxKI->N4NZKKFHVF2.z71iwG4kUN = loAh3 + dF52pOlLbm0kY;
        else  /* previous instruction set top */
          dF52pOlLbm0kY = udCRXfAt(hQ6BhxKI->N4NZKKFHVF2.z71iwG4kUN - loAh3);
        svxRSyZDa(rcB6Iscy);  /* several calls here can raise errors */
        if (AGl2_XrlE24(KsK1Stf)) {
          WPLh859NVqb(hQ6BhxKI, Wv4svkLK);  /* close upvalues from current call */
          bmeZHZ5YL(hQ6BhxKI->y21HfB7_2YxW.z71iwG4kUN < Wv4svkLK);  /* no pending tbc variables */
          bmeZHZ5YL(Wv4svkLK == rcB6Iscy->jAov1dj.z71iwG4kUN + 1);
        }
        if ((R6O8jbyQ = InR4QxlOph(hQ6BhxKI, rcB6Iscy, loAh3, dF52pOlLbm0kY, dCqPkn)) < 0)  /* Lua function? */
          goto HN_hrSQ;  /* execute the callee */
        else {  /* C function? */
          rcB6Iscy->jAov1dj.z71iwG4kUN -= dCqPkn;  /* restore 'func' (if vararg) */
          TzxkcPPI(hQ6BhxKI, rcB6Iscy, R6O8jbyQ);  /* finish caller */
          MnHt(rcB6Iscy);  /* 'luaD_poscall' can change hooks */
          goto idjE;  /* caller returns after the tail call */
        }
      }
      hKFhT(QI2QSExRD) {
        na0AtGv0_M loAh3 = K8S6RUO(KsK1Stf);
        int R6O8jbyQ = OSowW(KsK1Stf) - 1;  /* number of results */
        int M5dUFD = nIYjjkLKEnn(KsK1Stf);
        if (R6O8jbyQ < 0)  /* not fixed? */
          R6O8jbyQ = udCRXfAt(hQ6BhxKI->N4NZKKFHVF2.z71iwG4kUN - loAh3);  /* get what is available */
        svxRSyZDa(rcB6Iscy);
        if (AGl2_XrlE24(KsK1Stf)) {  /* may there be open upvalues? */
          rcB6Iscy->QtZ6e.PyVgbXR = R6O8jbyQ;  /* save number of returns */
          if (hQ6BhxKI->N4NZKKFHVF2.z71iwG4kUN < rcB6Iscy->N4NZKKFHVF2.z71iwG4kUN)
            hQ6BhxKI->N4NZKKFHVF2.z71iwG4kUN = rcB6Iscy->N4NZKKFHVF2.z71iwG4kUN;
          sp0iU(hQ6BhxKI, Wv4svkLK, eUVAiLmn9z3, 1);
          MnHt(rcB6Iscy);
          g7PZPk7HxG(rcB6Iscy);
        }
        if (M5dUFD)  /* vararg function? */
          rcB6Iscy->jAov1dj.z71iwG4kUN -= rcB6Iscy->kEYsJ.RF72ZUXWIFi.BdZfgcC9PEF + M5dUFD;
        hQ6BhxKI->N4NZKKFHVF2.z71iwG4kUN = loAh3 + R6O8jbyQ;  /* set call for 'luaD_poscall' */
        TzxkcPPI(hQ6BhxKI, rcB6Iscy, R6O8jbyQ);
        MnHt(rcB6Iscy);  /* 'luaD_poscall' can change hooks */
        goto idjE;
      }
      hKFhT(BN3hAZsce1pbP) {
        if (zGtwMpntf(hQ6BhxKI->mf0zmlGBnPyia)) {
          na0AtGv0_M loAh3 = K8S6RUO(KsK1Stf);
          hQ6BhxKI->N4NZKKFHVF2.z71iwG4kUN = loAh3;
          svxRSyZDa(rcB6Iscy);
          TzxkcPPI(hQ6BhxKI, rcB6Iscy, 0);  /* no hurry... */
          JL71GGh7iX = 1;
        }
        else {  /* do the 'poscall' here */
          int PyVgbXR;
          hQ6BhxKI->rcB6Iscy = rcB6Iscy->eY1OxeOB;  /* back to caller */
          hQ6BhxKI->N4NZKKFHVF2.z71iwG4kUN = Wv4svkLK - 1;
          for (PyVgbXR = rcB6Iscy->NsWfVUXcWQUs; zGtwMpntf(PyVgbXR > 0); PyVgbXR--)
            yTGbaI3zc(dRPEeVWBAygZ(hQ6BhxKI->N4NZKKFHVF2.z71iwG4kUN++));  /* all results are nil */
        }
        goto idjE;
      }
      hKFhT(CSUaa68) {
        if (zGtwMpntf(hQ6BhxKI->mf0zmlGBnPyia)) {
          na0AtGv0_M loAh3 = K8S6RUO(KsK1Stf);
          hQ6BhxKI->N4NZKKFHVF2.z71iwG4kUN = loAh3 + 1;
          svxRSyZDa(rcB6Iscy);
          TzxkcPPI(hQ6BhxKI, rcB6Iscy, 1);  /* no hurry... */
          JL71GGh7iX = 1;
        }
        else {  /* do the 'poscall' here */
          int PyVgbXR = rcB6Iscy->NsWfVUXcWQUs;
          hQ6BhxKI->rcB6Iscy = rcB6Iscy->eY1OxeOB;  /* back to caller */
          if (PyVgbXR == 0)
            hQ6BhxKI->N4NZKKFHVF2.z71iwG4kUN = Wv4svkLK - 1;  /* asked for no results */
          else {
            na0AtGv0_M loAh3 = K8S6RUO(KsK1Stf);
            MDzOh(hQ6BhxKI, Wv4svkLK - 1, loAh3);  /* at least this result */
            hQ6BhxKI->N4NZKKFHVF2.z71iwG4kUN = Wv4svkLK;
            for (; zGtwMpntf(PyVgbXR > 1); PyVgbXR--)
              yTGbaI3zc(dRPEeVWBAygZ(hQ6BhxKI->N4NZKKFHVF2.z71iwG4kUN++));  /* complete missing results */
          }
        }
       idjE:  /* return from a Lua function */
        if (rcB6Iscy->amkqpYHeWJCS & A7ZJmK)
          return;  /* end this frame */
        else {
          rcB6Iscy = rcB6Iscy->eY1OxeOB;
          goto ITmb6qcI;  /* continue running caller in this frame */
        }
      }
      hKFhT(U3Ss6Uy) {
        na0AtGv0_M loAh3 = K8S6RUO(KsK1Stf);
        if (rTcNZDWpyB(dRPEeVWBAygZ(loAh3 + 2))) {  /* integer loop? */
          QZo1Bt9 cYfmzUwfkY = hcF9Uh(xE5QGsbvl7Zh(dRPEeVWBAygZ(loAh3 + 1)));
          if (cYfmzUwfkY > 0) {  /* still more iterations? */
            BNtSo1rKXcN b8j3s4DMM = xE5QGsbvl7Zh(dRPEeVWBAygZ(loAh3 + 2));
            BNtSo1rKXcN xZZYog6 = xE5QGsbvl7Zh(dRPEeVWBAygZ(loAh3));  /* internal index */
            nwKhb(dRPEeVWBAygZ(loAh3 + 1), cYfmzUwfkY - 1);  /* update counter */
            xZZYog6 = xqxC(+, xZZYog6, b8j3s4DMM);  /* add step to index */
            nwKhb(dRPEeVWBAygZ(loAh3), xZZYog6);  /* update internal index */
            H7MWC(dRPEeVWBAygZ(loAh3 + 3), xZZYog6);  /* and control variable */
            etnzw9Klu -= eqOtpS5J4GVq(KsK1Stf);  /* jump back */
          }
        }
        else if (iQwZzDSna(loAh3))  /* float loop */
          etnzw9Klu -= eqOtpS5J4GVq(KsK1Stf);  /* jump back */
        MnHt(rcB6Iscy);  /* allows a signal to break the loop */
        tA5_Uq;
      }
      hKFhT(rK1PJuBrTm) {
        na0AtGv0_M loAh3 = K8S6RUO(KsK1Stf);
        u_MH5x(hQ6BhxKI, rcB6Iscy);  /* in case of errors */
        if (pNgQ7gpGqoSq(hQ6BhxKI, loAh3))
          etnzw9Klu += eqOtpS5J4GVq(KsK1Stf) + 1;  /* skip the loop */
        tA5_Uq;
      }
      hKFhT(gzrGsTw) {
       na0AtGv0_M loAh3 = K8S6RUO(KsK1Stf);
        /* create to-be-closed upvalue (if needed) */
        iitxltBo(cd3H(hQ6BhxKI, loAh3 + 3));
        etnzw9Klu += eqOtpS5J4GVq(KsK1Stf);
        KsK1Stf = *(etnzw9Klu++);  /* go to next instruction */
        bmeZHZ5YL(DwaGEycz4v(KsK1Stf) == ZUOLrvPTwmTY && loAh3 == K8S6RUO(KsK1Stf));
        goto EmVwbNZYlWy;
      }
      hKFhT(ZUOLrvPTwmTY) {
       EmVwbNZYlWy: {
        na0AtGv0_M loAh3 = K8S6RUO(KsK1Stf);
        /* 'ra' has the iterator function, 'ra + 1' has the state,
           'ra + 2' has the control variable, and 'ra + 3' has the
           to-be-closed variable. The call will use the stack after
           these values (starting at 'ra + 4')
        */
        /* push function, state, and control variable */
        D8cgzT7wC8(loAh3 + 4, loAh3, 3 * sizeof(*loAh3));
        hQ6BhxKI->N4NZKKFHVF2.z71iwG4kUN = loAh3 + 4 + 3;
        nK0xZy(odXUY6mf(hQ6BhxKI, loAh3 + 4, nIYjjkLKEnn(KsK1Stf)));  /* do the call */
        g7PZPk7HxG(rcB6Iscy);  /* stack may have changed */
        KsK1Stf = *(etnzw9Klu++);  /* go to next instruction */
        bmeZHZ5YL(DwaGEycz4v(KsK1Stf) == ykVCaH3Q && loAh3 == K8S6RUO(KsK1Stf));
        goto JFaeEyX;
      }}
      hKFhT(ykVCaH3Q) {
       JFaeEyX: {
        na0AtGv0_M loAh3 = K8S6RUO(KsK1Stf);
        if (!rjrbajC9(dRPEeVWBAygZ(loAh3 + 4))) {  /* continue loop? */
          MDzOh(hQ6BhxKI, loAh3 + 2, loAh3 + 4);  /* save control variable */
          etnzw9Klu -= eqOtpS5J4GVq(KsK1Stf);  /* jump back */
        }
        tA5_Uq;
      }}
      hKFhT(NPpMuxBYMl) {
        na0AtGv0_M loAh3 = K8S6RUO(KsK1Stf);
        int R6O8jbyQ = OSowW(KsK1Stf);
        unsigned int GwYb = nIYjjkLKEnn(KsK1Stf);
        Yk2eE7 *qQ5L = wnU8dI0RtA(dRPEeVWBAygZ(loAh3));
        if (R6O8jbyQ == 0)
          R6O8jbyQ = udCRXfAt(hQ6BhxKI->N4NZKKFHVF2.z71iwG4kUN - loAh3) - 1;  /* get up to the top */
        else
          hQ6BhxKI->N4NZKKFHVF2.z71iwG4kUN = rcB6Iscy->N4NZKKFHVF2.z71iwG4kUN;  /* correct top in case of emergency GC */
        GwYb += R6O8jbyQ;
        if (AGl2_XrlE24(KsK1Stf)) {
          GwYb += XLaTHoL(*etnzw9Klu) * (xjpdhpIvjydJS + 1);
          etnzw9Klu++;
        }
        if (GwYb > pC4gJg(qQ5L))  /* needs more space? */
          KemzGLCBcyq5B(hQ6BhxKI, qQ5L, GwYb);  /* preallocate it at once */
        for (; R6O8jbyQ > 0; R6O8jbyQ--) {
          mmkodd *s2HxR = dRPEeVWBAygZ(loAh3 + R6O8jbyQ);
          cr9Q2sP(hQ6BhxKI, &qQ5L->nfatoB5d[GwYb - 1], s2HxR);
          GwYb--;
          r1mCTd(hQ6BhxKI, IiRf31nnwp(qQ5L), s2HxR);
        }
        tA5_Uq;
      }
      hKFhT(B5jBYBb5_NTu) {
        na0AtGv0_M loAh3 = K8S6RUO(KsK1Stf);
        voRDkmc *z71iwG4kUN = O981wbXvaCjG->z71iwG4kUN->z71iwG4kUN[eqOtpS5J4GVq(KsK1Stf)];
        iitxltBo(Ukhp479gyXxhv(hQ6BhxKI, z71iwG4kUN, O981wbXvaCjG->yw5ayV8N4, Wv4svkLK, loAh3));
        fprvE5(hQ6BhxKI, loAh3 + 1);
        tA5_Uq;
      }
      hKFhT(yndqD3) {
        na0AtGv0_M loAh3 = K8S6RUO(KsK1Stf);
        int R6O8jbyQ = nIYjjkLKEnn(KsK1Stf) - 1;  /* required results */
        ILkIE(CeyKXRtvrUql(hQ6BhxKI, rcB6Iscy, loAh3, R6O8jbyQ));
        tA5_Uq;
      }
      hKFhT(A__h) {
        nK0xZy(dyj877P7KZ(hQ6BhxKI, g5GaVjjdmlxGK(KsK1Stf), rcB6Iscy, O981wbXvaCjG->z71iwG4kUN));
        if (zGtwMpntf(JL71GGh7iX)) {  /* previous "Protect" updated trap */
          jsr1zplqlaG86(hQ6BhxKI, rcB6Iscy);
          hQ6BhxKI->Opdsat50YdG0 = 1;  /* next opcode will be seen as a "new" line */
        }
        LNpb_hU8DJpJ(rcB6Iscy);  /* function has new base after adjustment */
        tA5_Uq;
      }
      hKFhT(wx56eYU) {
        bmeZHZ5YL(0);
        tA5_Uq;
      }
    }
  }
}

/* }================================================================== */
