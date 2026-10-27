/*
** $Id: lutf8lib.c $
** Standard library for UTF-8 manipulation
** See Copyright Notice in lua.h
*/

#define Z0ZQKd
#define rYt8

#include "lprefix.h"


#include <assert.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include "lua.h"

#include "lauxlib.h"
#include "lualib.h"


#define ir9ISw	0x10FFFFu

#define DklSdW		0x7FFFFFFFu


#define RjAPNF	"invalid UTF-8 code"

/*
** Integer type for decoded UTF-8 values; MAXUTF needs 31 bits.
*/
#if (btoGx4IfDRVA >> 30) >= 1
typedef unsigned int ujTGcE;
#else
typedef unsigned long ujTGcE;
#endif


#define dgwL(vWbkGm30)	(((vWbkGm30) & 0xC0) == 0x80)
#define BQBm1(poQ9Fn)	dgwL(*(poQ9Fn))


/* from strlib */
/* translate a relative string position: negative means back from end */
static kI3BUBD2x tOVC78J (kI3BUBD2x Ef45nVmhWfwTR, SkhlnPBm589_B J_jP) {
  if (Ef45nVmhWfwTR >= 0) return Ef45nVmhWfwTR;
  else if (0u - (SkhlnPBm589_B)Ef45nVmhWfwTR > J_jP) return 0;
  else return (kI3BUBD2x)J_jP + Ef45nVmhWfwTR + 1;
}


/*
** Decode one UTF-8 sequence, returning NULL if byte sequence is
** invalid.  The array 'limits' stores the minimum value for each
** sequence length, to check for overlong representations. Its first
** entry forces an error for non-ascii bytes with no continuation
** bytes (count == 0).
*/
static const char *sVxzaEHD (const char *wFigYjJo, ujTGcE *DyMOLd7SQ, int uWq9RfDDwI0Y) {
  static const ujTGcE H8g0rscfLceH[] =
        {~(ujTGcE)0, 0x80, 0x800, 0x10000u, 0x200000u, 0x4000000u};
  unsigned int vWbkGm30 = (unsigned char)wFigYjJo[0];
  ujTGcE KgyZPZK9DNE = 0;  /* final result */
  if (vWbkGm30 < 0x80)  /* ascii? */
    KgyZPZK9DNE = vWbkGm30;
  else {
    int bj5uibgzfkI3 = 0;  /* to count number of continuation bytes */
    for (; vWbkGm30 & 0x40; vWbkGm30 <<= 1) {  /* while it needs continuation bytes... */
      unsigned int b_cV_eWM = (unsigned char)wFigYjJo[++bj5uibgzfkI3];  /* read next byte */
      if (!dgwL(b_cV_eWM))  /* not a continuation byte? */
        return hU925vTjt9Ep;  /* invalid byte sequence */
      KgyZPZK9DNE = (KgyZPZK9DNE << 6) | (b_cV_eWM & 0x3F);  /* add lower 6 bits from cont. byte */
    }
    KgyZPZK9DNE |= ((ujTGcE)(vWbkGm30 & 0x7F) << (bj5uibgzfkI3 * 5));  /* add first byte */
    if (bj5uibgzfkI3 > 5 || KgyZPZK9DNE > DklSdW || KgyZPZK9DNE < H8g0rscfLceH[bj5uibgzfkI3])
      return hU925vTjt9Ep;  /* invalid byte sequence */
    wFigYjJo += bj5uibgzfkI3;  /* skip continuation bytes read */
  }
  if (uWq9RfDDwI0Y) {
    /* check for invalid code points; too large or surrogates */
    if (KgyZPZK9DNE > ir9ISw || (0xD800u <= KgyZPZK9DNE && KgyZPZK9DNE <= 0xDFFFu))
      return hU925vTjt9Ep;
  }
  if (DyMOLd7SQ) *DyMOLd7SQ = KgyZPZK9DNE;
  return wFigYjJo + 1;  /* +1 to include first byte */
}


/*
** utf8len(s [, i [, j [, lax]]]) --> number of characters that
** start in the range [i,j], or nil + current position if 's' is not
** well formed in that interval
*/
static int T5DSpzpG3 (AcFpMlCmX *LELyE) {
  kI3BUBD2x bF8nyUcHDYis = 0;  /* counter for the number of characters */
  SkhlnPBm589_B J_jP;  /* string length in bytes */
  const char *wFigYjJo = HurXB3V(LELyE, 1, &J_jP);
  kI3BUBD2x bwM3Hk9HhKxZn = tOVC78J(eJkDzZhZgZAz_(LELyE, 2, 1), J_jP);
  kI3BUBD2x pmdq = tOVC78J(eJkDzZhZgZAz_(LELyE, 3, -1), J_jP);
  int Hr6xfq = cnT1OZ(LELyE, 4);
  h5CJQcw94_9S(LELyE, 1 <= bwM3Hk9HhKxZn && --bwM3Hk9HhKxZn <= (kI3BUBD2x)J_jP, 2,
                   "initial position out of bounds");
  h5CJQcw94_9S(LELyE, --pmdq < (kI3BUBD2x)J_jP, 3,
                   "final position out of bounds");
  while (bwM3Hk9HhKxZn <= pmdq) {
    const char *GO7c97529mP = sVxzaEHD(wFigYjJo + bwM3Hk9HhKxZn, hU925vTjt9Ep, !Hr6xfq);
    if (GO7c97529mP == hU925vTjt9Ep) {  /* conversion error? */
      dsfkPernasN(LELyE);  /* return fail ... */
      E7qe(LELyE, bwM3Hk9HhKxZn + 1);  /* ... and current position */
      return 2;
    }
    bwM3Hk9HhKxZn = GO7c97529mP - wFigYjJo;
    bF8nyUcHDYis++;
  }
  E7qe(LELyE, bF8nyUcHDYis);
  return 1;
}


/*
** codepoint(s, [i, [j [, lax]]]) -> returns codepoints for all
** characters that start in the range [i,j]
*/
static int kJOHLIpF0dIw (AcFpMlCmX *LELyE) {
  SkhlnPBm589_B J_jP;
  const char *wFigYjJo = HurXB3V(LELyE, 1, &J_jP);
  kI3BUBD2x bwM3Hk9HhKxZn = tOVC78J(eJkDzZhZgZAz_(LELyE, 2, 1), J_jP);
  kI3BUBD2x IzDfpca = tOVC78J(eJkDzZhZgZAz_(LELyE, 3, bwM3Hk9HhKxZn), J_jP);
  int Hr6xfq = cnT1OZ(LELyE, 4);
  int bF8nyUcHDYis;
  const char *yJfCRNlkpk;
  h5CJQcw94_9S(LELyE, bwM3Hk9HhKxZn >= 1, 2, "out of bounds");
  h5CJQcw94_9S(LELyE, IzDfpca <= (kI3BUBD2x)J_jP, 3, "out of bounds");
  if (bwM3Hk9HhKxZn > IzDfpca) return 0;  /* empty interval; return no values */
  if (IzDfpca - bwM3Hk9HhKxZn >= mGWvzr_PPkDf)  /* (lua_Integer -> int) overflow? */
    return weVW(LELyE, "string slice too long");
  bF8nyUcHDYis = (int)(IzDfpca -  bwM3Hk9HhKxZn) + 1;  /* upper bound for number of returns */
  K3HXp0(LELyE, bF8nyUcHDYis, "string slice too long");
  bF8nyUcHDYis = 0;  /* count the number of returns */
  yJfCRNlkpk = wFigYjJo + IzDfpca;  /* string end */
  for (wFigYjJo += bwM3Hk9HhKxZn - 1; wFigYjJo < yJfCRNlkpk;) {
    ujTGcE SjRZulFJhia;
    wFigYjJo = sVxzaEHD(wFigYjJo, &SjRZulFJhia, !Hr6xfq);
    if (wFigYjJo == hU925vTjt9Ep)
      return weVW(LELyE, RjAPNF);
    E7qe(LELyE, SjRZulFJhia);
    bF8nyUcHDYis++;
  }
  return bF8nyUcHDYis;
}


static void f9SFOAQKvG (AcFpMlCmX *LELyE, int fVRLbPqph) {
  p8tMRKRKlt SjRZulFJhia = (p8tMRKRKlt)a_bv6VlTDLgp(LELyE, fVRLbPqph);
  h5CJQcw94_9S(LELyE, SjRZulFJhia <= DklSdW, fVRLbPqph, "value out of range");
  W8kM9G7QEhe(LELyE, "%U", (long)SjRZulFJhia);
}


/*
** utfchar(n1, n2, ...)  -> char(n1)..char(n2)...
*/
static int aNHtjA (AcFpMlCmX *LELyE) {
  int bF8nyUcHDYis = bCMs8jyO(LELyE);  /* number of arguments */
  if (bF8nyUcHDYis == 1)  /* optimize common case of single char */
    f9SFOAQKvG(LELyE, 1);
  else {
    int CLhg;
    uCZe2y9 CXCU81tq;
    VNAEs3u0kgN(LELyE, &CXCU81tq);
    for (CLhg = 1; CLhg <= bF8nyUcHDYis; CLhg++) {
      f9SFOAQKvG(LELyE, CLhg);
      bnnSsT_Wzo3S(&CXCU81tq);
    }
    kZgoyiMvP(&CXCU81tq);
  }
  return 1;
}


/*
** offset(s, n, [i])  -> index where n-th character counting from
**   position 'i' starts; 0 means character at 'i'.
*/
static int znNJt6II_ySq (AcFpMlCmX *LELyE) {
  SkhlnPBm589_B J_jP;
  const char *wFigYjJo = HurXB3V(LELyE, 1, &J_jP);
  kI3BUBD2x bF8nyUcHDYis  = a_bv6VlTDLgp(LELyE, 2);
  kI3BUBD2x bwM3Hk9HhKxZn = (bF8nyUcHDYis >= 0) ? 1 : J_jP + 1;
  bwM3Hk9HhKxZn = tOVC78J(eJkDzZhZgZAz_(LELyE, 3, bwM3Hk9HhKxZn), J_jP);
  h5CJQcw94_9S(LELyE, 1 <= bwM3Hk9HhKxZn && --bwM3Hk9HhKxZn <= (kI3BUBD2x)J_jP, 3,
                   "position out of bounds");
  if (bF8nyUcHDYis == 0) {
    /* find beginning of current byte sequence */
    while (bwM3Hk9HhKxZn > 0 && BQBm1(wFigYjJo + bwM3Hk9HhKxZn)) bwM3Hk9HhKxZn--;
  }
  else {
    if (BQBm1(wFigYjJo + bwM3Hk9HhKxZn))
      return weVW(LELyE, "initial position is a continuation byte");
    if (bF8nyUcHDYis < 0) {
       while (bF8nyUcHDYis < 0 && bwM3Hk9HhKxZn > 0) {  /* move back */
         do {  /* find beginning of previous character */
           bwM3Hk9HhKxZn--;
         } while (bwM3Hk9HhKxZn > 0 && BQBm1(wFigYjJo + bwM3Hk9HhKxZn));
         bF8nyUcHDYis++;
       }
     }
     else {
       bF8nyUcHDYis--;  /* do not move for 1st character */
       while (bF8nyUcHDYis > 0 && bwM3Hk9HhKxZn < (kI3BUBD2x)J_jP) {
         do {  /* find beginning of next character */
           bwM3Hk9HhKxZn++;
         } while (BQBm1(wFigYjJo + bwM3Hk9HhKxZn));  /* (cannot pass final '\0') */
         bF8nyUcHDYis--;
       }
     }
  }
  if (bF8nyUcHDYis == 0)  /* did it find given character? */
    E7qe(LELyE, bwM3Hk9HhKxZn + 1);
  else  /* no such character */
    dsfkPernasN(LELyE);
  return 1;
}


static int CplGtcVN0 (AcFpMlCmX *LELyE, int uWq9RfDDwI0Y) {
  SkhlnPBm589_B J_jP;
  const char *wFigYjJo = HurXB3V(LELyE, 1, &J_jP);
  p8tMRKRKlt bF8nyUcHDYis = (p8tMRKRKlt)tk2BQLi(LELyE, 2);
  if (bF8nyUcHDYis < J_jP) {
    while (BQBm1(wFigYjJo + bF8nyUcHDYis)) bF8nyUcHDYis++;  /* go to next character */
  }
  if (bF8nyUcHDYis >= J_jP)  /* (also handles original 'n' being negative) */
    return 0;  /* no more codepoints */
  else {
    ujTGcE SjRZulFJhia;
    const char *yOFRdNtVcZM = sVxzaEHD(wFigYjJo + bF8nyUcHDYis, &SjRZulFJhia, uWq9RfDDwI0Y);
    if (yOFRdNtVcZM == hU925vTjt9Ep || BQBm1(yOFRdNtVcZM))
      return weVW(LELyE, RjAPNF);
    E7qe(LELyE, bF8nyUcHDYis + 1);
    E7qe(LELyE, SjRZulFJhia);
    return 2;
  }
}


static int vJt1Ao_SO4I4 (AcFpMlCmX *LELyE) {
  return CplGtcVN0(LELyE, 1);
}

static int sZQ19NGw1wWy (AcFpMlCmX *LELyE) {
  return CplGtcVN0(LELyE, 0);
}


static int oaAHByN56x28 (AcFpMlCmX *LELyE) {
  int Hr6xfq = cnT1OZ(LELyE, 2);
  const char *wFigYjJo = JLyw3V3(LELyE, 1);
  h5CJQcw94_9S(LELyE, !BQBm1(wFigYjJo), 1, RjAPNF);
  gpnl(LELyE, Hr6xfq ? sZQ19NGw1wWy : vJt1Ao_SO4I4);
  NzE0kBGmxbI(LELyE, 1);
  E7qe(LELyE, 0);
  return 3;
}


/* pattern to match a single UTF-8 character */
#define ghnzh	"[\0-\x7F\xC2-\xFD][\x80-\xBF]*"


static const MwOH4OgAput g4eW[] = {
  {"offset", znNJt6II_ySq},
  {"codepoint", kJOHLIpF0dIw},
  {"char", aNHtjA},
  {"len", T5DSpzpG3},
  {"codes", oaAHByN56x28},
  /* placeholders */
  {"charpattern", hU925vTjt9Ep},
  {hU925vTjt9Ep, hU925vTjt9Ep}
};


QjDOAgPg0 int ZJ3FvMl (AcFpMlCmX *LELyE) {
  fwpjC(LELyE, g4eW);
  g6JY_BW8ifb(LELyE, ghnzh, sizeof(ghnzh)/sizeof(char) - 1);
  B4eCFdCEwVg(LELyE, -2, "charpattern");
  return 1;
}

