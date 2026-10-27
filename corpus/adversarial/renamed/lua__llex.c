/*
** $Id: llex.c $
** Lexical Analyzer
** See Copyright Notice in lua.h
*/

#define jVmJpM
#define uhhpCG11ZXm

#include "lprefix.h"


#include <locale.h>
#include <string.h>

#include "lua.h"

#include "lctype.h"
#include "ldebug.h"
#include "ldo.h"
#include "lgc.h"
#include "llex.h"
#include "lobject.h"
#include "lparser.h"
#include "lstate.h"
#include "lstring.h"
#include "ltable.h"
#include "lzio.h"



#define smoruODsDBDx(InXUNX)	(InXUNX->m9VTe7 = Ge4ohVlQ282u(InXUNX->QzqQ))



#define JsByRunzjwc7(InXUNX)	(InXUNX->m9VTe7 == '\n' || InXUNX->m9VTe7 == '\r')


/* ORDER RESERVED */
static const char *const KOJVD0_nyG [] = {
    "and", "break", "do", "else", "elseif",
    "end", "false", "for", "function", "goto", "if",
    "in", "local", "nil", "not", "or", "repeat",
    "return", "then", "true", "until", "while",
    "//", "..", "...", "==", ">=", "<=", "~=",
    "<<", ">>", "::", "<eof>",
    "<number>", "<integer>", "<name>", "<string>"
};


#define fbxYEX6hl(InXUNX) (SPkIHrX9Z(InXUNX, InXUNX->m9VTe7), smoruODsDBDx(InXUNX))


static Zwkw LuijGkr_guL (rr1bsq *InXUNX, const char *HZMD, int YarlwcJ);


static void SPkIHrX9Z (rr1bsq *InXUNX, int SMwnU4N) {
  QLN8uu_nwpK14 *H7gavbJH0zB = InXUNX->Da46qf;
  if (SnWLQc(H7gavbJH0zB) + 1 > xrlGtqHfqvcX(H7gavbJH0zB)) {
    kDdUJuNWF QO8pK1Lt;
    if (xrlGtqHfqvcX(H7gavbJH0zB) >= Dmd6s_/2)
      LuijGkr_guL(InXUNX, "lexical element too long", 0);
    QO8pK1Lt = xrlGtqHfqvcX(H7gavbJH0zB) * 2;
    nUe1qebbO(InXUNX->LlMYhzdxEMF, H7gavbJH0zB, QO8pK1Lt);
  }
  H7gavbJH0zB->hoD0U0TcJO[SnWLQc(H7gavbJH0zB)++] = q2Hr990(SMwnU4N);
}


void QWgvK (z0MfopM56 *LlMYhzdxEMF) {
  int JUxOsWT;
  GROciXnIu *kl36T = uDHKBEu(LlMYhzdxEMF, x_wqH4kYma8YI);  /* create env name */
  a2GBmkiARnt(LlMYhzdxEMF, RCM9Rn(kl36T));  /* never collect this name */
  for (JUxOsWT=0; JUxOsWT<JxjU8Y7yTZ1; JUxOsWT++) {
    GROciXnIu *acjcGlcv = Ah5n1(LlMYhzdxEMF, KOJVD0_nyG[JUxOsWT]);
    a2GBmkiARnt(LlMYhzdxEMF, RCM9Rn(acjcGlcv));  /* reserved words are never collected */
    acjcGlcv->i04F = GBnUaWrKnDp(JUxOsWT+1);  /* reserved word */
  }
}


const char *ssS9Nutcq35 (rr1bsq *InXUNX, int YarlwcJ) {
  if (YarlwcJ < IPNABu) {  /* single-byte symbols? */
    if (XqhZf(YarlwcJ))
      return toxnGG6_kZkS(InXUNX->LlMYhzdxEMF, "'%c'", YarlwcJ);
    else  /* control character */
      return toxnGG6_kZkS(InXUNX->LlMYhzdxEMF, "'<\\%d>'", YarlwcJ);
  }
  else {
    const char *HDJM = KOJVD0_nyG[YarlwcJ - IPNABu];
    if (YarlwcJ < CvXy4b9fdw)  /* fixed format (symbols and reserved words)? */
      return toxnGG6_kZkS(InXUNX->LlMYhzdxEMF, "'%s'", HDJM);
    else  /* names, strings, and numerals */
      return HDJM;
  }
}


static const char *fxf09Vc (rr1bsq *InXUNX, int YarlwcJ) {
  switch (YarlwcJ) {
    case Pm8ku: case VMgIn3h:
    case Rkl2vY: case wZks:
      SPkIHrX9Z(InXUNX, '\0');
      return toxnGG6_kZkS(InXUNX->LlMYhzdxEMF, "'%s'", DDxxdWHAIR8(InXUNX->Da46qf));
    default:
      return ssS9Nutcq35(InXUNX, YarlwcJ);
  }
}


static Zwkw LuijGkr_guL (rr1bsq *InXUNX, const char *HZMD, int YarlwcJ) {
  HZMD = YsQh(InXUNX->LlMYhzdxEMF, HZMD, InXUNX->x8OHfYof0xVXn, InXUNX->g9TSbra7);
  if (YarlwcJ)
    toxnGG6_kZkS(InXUNX->LlMYhzdxEMF, "%s near %s", HZMD, fxf09Vc(InXUNX, YarlwcJ));
  KxHOUYuIvobN(InXUNX->LlMYhzdxEMF, m3c2FwM);
}


Zwkw e2EnGHw (rr1bsq *InXUNX, const char *HZMD) {
  LuijGkr_guL(InXUNX, HZMD, InXUNX->yWx9s5n8T8.YarlwcJ);
}


/*
** Creates a new string and anchors it in scanner's table so that it
** will not be collected until the end of the compilation; by that time
** it should be anchored somewhere. It also internalizes long strings,
** ensuring there is only one copy of each unique string.  The table
** here is used as a set: the string enters as the key, while its value
** is irrelevant. We use the string itself as the value only because it
** is a TValue readily available. Later, the code generation can change
** this value.
*/
GROciXnIu *RKt7_dmrz (rr1bsq *InXUNX, const char *YzlW, kDdUJuNWF GWdQFq7o6vq) {
  z0MfopM56 *LlMYhzdxEMF = InXUNX->LlMYhzdxEMF;
  GROciXnIu *acjcGlcv = nq_6kfmWKPLU(LlMYhzdxEMF, YzlW, GWdQFq7o6vq);  /* create new string */
  const XiOMG *q4ATJShdtRBlv = YqFfEOu(InXUNX->vJlYueH, acjcGlcv);
  if (!A1VBOVSvY1MMu(q4ATJShdtRBlv))  /* string already present? */
    acjcGlcv = UF0hend1l8c4(wYeY4uIKNk(q4ATJShdtRBlv));  /* get saved copy */
  else {  /* not in use yet */
    XiOMG *ZdaT = GOdQmv58bJ(LlMYhzdxEMF->L98ir.pvaZwI++);  /* reserve stack space for string */
    B3bMy(LlMYhzdxEMF, ZdaT, acjcGlcv);  /* temporarily anchor the string */
    YjW1lMiiTLMu(LlMYhzdxEMF, InXUNX->vJlYueH, ZdaT, q4ATJShdtRBlv, ZdaT);  /* t[string] = string */
    /* table is not a metatable, so it does not need to invalidate cache */
    cfRaRS(LlMYhzdxEMF);
    LlMYhzdxEMF->L98ir.pvaZwI--;  /* remove string from stack */
  }
  return acjcGlcv;
}


/*
** increment line number and skips newline sequence (any of
** \n, \r, \n\r, or \r\n)
*/
static void PoGsxhVwp (rr1bsq *InXUNX) {
  int Fz77 = InXUNX->m9VTe7;
  QAhKv(JsByRunzjwc7(InXUNX));
  smoruODsDBDx(InXUNX);  /* skip '\n' or '\r' */
  if (JsByRunzjwc7(InXUNX) && InXUNX->m9VTe7 != Fz77)
    smoruODsDBDx(InXUNX);  /* skip '\n\r' or '\r\n' */
  if (++InXUNX->g9TSbra7 >= oU6H_a)
    LuijGkr_guL(InXUNX, "chunk has too many lines", 0);
}


void KlHi5Rh3z (z0MfopM56 *LlMYhzdxEMF, rr1bsq *InXUNX, ZJa7YkiOLZ7Ij *QzqQ, GROciXnIu *x8OHfYof0xVXn,
                    int xzWH) {
  InXUNX->yWx9s5n8T8.YarlwcJ = 0;
  InXUNX->LlMYhzdxEMF = LlMYhzdxEMF;
  InXUNX->m9VTe7 = xzWH;
  InXUNX->sIlN.YarlwcJ = CvXy4b9fdw;  /* no look-ahead token */
  InXUNX->QzqQ = QzqQ;
  InXUNX->ZTEq_Ds = vOGIT5F;
  InXUNX->g9TSbra7 = 1;
  InXUNX->ViGL4JAHpP = 1;
  InXUNX->x8OHfYof0xVXn = x8OHfYof0xVXn;
  InXUNX->gG1oOaS5CZrk2 = uDHKBEu(LlMYhzdxEMF, x_wqH4kYma8YI);  /* get env name */
  nUe1qebbO(InXUNX->LlMYhzdxEMF, InXUNX->Da46qf, fXGi4u);  /* initialize buffer */
}



/*
** =======================================================
** LEXICAL ANALYZER
** =======================================================
*/


static int Cf5tyULsOo3ZK (rr1bsq *InXUNX, int SMwnU4N) {
  if (InXUNX->m9VTe7 == SMwnU4N) {
    smoruODsDBDx(InXUNX);
    return 1;
  }
  else return 0;
}


/*
** Check whether current char is in set 'set' (with two chars) and
** saves it
*/
static int Bcs62lWX (rr1bsq *InXUNX, const char *ZJIK87) {
  QAhKv(ZJIK87[2] == '\0');
  if (InXUNX->m9VTe7 == ZJIK87[0] || InXUNX->m9VTe7 == ZJIK87[1]) {
    fbxYEX6hl(InXUNX);
    return 1;
  }
  else return 0;
}


/* LUA_NUMBER */
/*
** This function is quite liberal in what it accepts, as 'luaO_str2num'
** will reject ill-formed numerals. Roughly, it accepts the following
** pattern:
**
**   %d(%x|%.|([Ee][+-]?))* | 0[Xx](%x|%.|([Pp][+-]?))*
**
** The only tricky part is to accept [+-] only after a valid exponent
** mark, to avoid reading '3-4' or '0xe+1' as a single number.
**
** The caller might have already read an initial dot.
*/
static int gxPQN32p (rr1bsq *InXUNX, OKYV3t *r3LVW) {
  XiOMG tpKNfm8PYPJ1;
  const char *VyrY1LHGV = "Ee";
  int oLjpXiNP_54 = InXUNX->m9VTe7;
  QAhKv(YNaU6IJ(InXUNX->m9VTe7));
  fbxYEX6hl(InXUNX);
  if (oLjpXiNP_54 == '0' && Bcs62lWX(InXUNX, "xX"))  /* hexadecimal? */
    VyrY1LHGV = "Pp";
  for (;;) {
    if (Bcs62lWX(InXUNX, VyrY1LHGV))  /* exponent mark? */
      Bcs62lWX(InXUNX, "-+");  /* optional exponent sign */
    else if (A22RHvpap(InXUNX->m9VTe7) || InXUNX->m9VTe7 == '.')  /* '%x|%.' */
      fbxYEX6hl(InXUNX);
    else break;
  }
  if (mu7ka(InXUNX->m9VTe7))  /* is numeral touching a letter? */
    fbxYEX6hl(InXUNX);  /* force an error */
  SPkIHrX9Z(InXUNX, '\0');
  if (yhfXheJN1Wy(DDxxdWHAIR8(InXUNX->Da46qf), &tpKNfm8PYPJ1) == 0)  /* format error? */
    LuijGkr_guL(InXUNX, "malformed number", Rkl2vY);
  if (kcEtGZuA8ARy(&tpKNfm8PYPJ1)) {
    r3LVW->JUxOsWT = M4PI(&tpKNfm8PYPJ1);
    return wZks;
  }
  else {
    QAhKv(I5AF9SgZJL9k(&tpKNfm8PYPJ1));
    r3LVW->UrtT3cbm = qDqOrdj(&tpKNfm8PYPJ1);
    return Rkl2vY;
  }
}


/*
** read a sequence '[=*[' or ']=*]', leaving the last bracket. If
** sequence is well formed, return its number of '='s + 2; otherwise,
** return 1 if it is a single bracket (no '='s and no 2nd bracket);
** otherwise (an unfinished '[==...') return 0.
*/
static kDdUJuNWF iX_3Q (rr1bsq *InXUNX) {
  kDdUJuNWF hZJPRQM9gzSL4 = 0;
  int HDJM = InXUNX->m9VTe7;
  QAhKv(HDJM == '[' || HDJM == ']');
  fbxYEX6hl(InXUNX);
  while (InXUNX->m9VTe7 == '=') {
    fbxYEX6hl(InXUNX);
    hZJPRQM9gzSL4++;
  }
  return (InXUNX->m9VTe7 == HDJM) ? hZJPRQM9gzSL4 + 2
         : (hZJPRQM9gzSL4 == 0) ? 1
         : 0;
}


static void SeggaH77vxt6 (rr1bsq *InXUNX, OKYV3t *r3LVW, kDdUJuNWF lBhPtyy) {
  int s6seZgWO = InXUNX->g9TSbra7;  /* initial line (for error message) */
  fbxYEX6hl(InXUNX);  /* skip 2nd '[' */
  if (JsByRunzjwc7(InXUNX))  /* string starts with a newline? */
    PoGsxhVwp(InXUNX);  /* skip it */
  for (;;) {
    switch (InXUNX->m9VTe7) {
      case C9Z2: {  /* error */
        const char *NTLJ9PNrT = (r3LVW ? "string" : "comment");
        const char *HZMD = toxnGG6_kZkS(InXUNX->LlMYhzdxEMF,
                     "unfinished long %s (starting at line %d)", NTLJ9PNrT, s6seZgWO);
        LuijGkr_guL(InXUNX, HZMD, CvXy4b9fdw);
        break;  /* to avoid warnings */
      }
      case ']': {
        if (iX_3Q(InXUNX) == lBhPtyy) {
          fbxYEX6hl(InXUNX);  /* skip 2nd ']' */
          goto sGbCDtq9Ok5El;
        }
        break;
      }
      case '\n': case '\r': {
        SPkIHrX9Z(InXUNX, '\n');
        PoGsxhVwp(InXUNX);
        if (!r3LVW) MXJVyp9KqU_7(InXUNX->Da46qf);  /* avoid wasting space */
        break;
      }
      default: {
        if (r3LVW) fbxYEX6hl(InXUNX);
        else smoruODsDBDx(InXUNX);
      }
    }
  } sGbCDtq9Ok5El:
  if (r3LVW)
    r3LVW->acjcGlcv = RKt7_dmrz(InXUNX, DDxxdWHAIR8(InXUNX->Da46qf) + lBhPtyy,
                                     SnWLQc(InXUNX->Da46qf) - 2 * lBhPtyy);
}


static void xmkLzTycFccX (rr1bsq *InXUNX, int SMwnU4N, const char *HZMD) {
  if (!SMwnU4N) {
    if (InXUNX->m9VTe7 != C9Z2)
      fbxYEX6hl(InXUNX);  /* add current to buffer for error message */
    LuijGkr_guL(InXUNX, HZMD, VMgIn3h);
  }
}


static int iYSmzZ (rr1bsq *InXUNX) {
  fbxYEX6hl(InXUNX);
  xmkLzTycFccX (InXUNX, A22RHvpap(InXUNX->m9VTe7), "hexadecimal digit expected");
  return o6qgnS(InXUNX->m9VTe7);
}


static int urAXbv0y (rr1bsq *InXUNX) {
  int UrtT3cbm = iYSmzZ(InXUNX);
  UrtT3cbm = (UrtT3cbm << 4) + iYSmzZ(InXUNX);
  rA8Y(InXUNX->Da46qf, 2);  /* remove saved chars from buffer */
  return UrtT3cbm;
}


static unsigned long gwfFxHSn68 (rr1bsq *InXUNX) {
  unsigned long UrtT3cbm;
  int JUxOsWT = 4;  /* chars to be removed: '\', 'u', '{', and first digit */
  fbxYEX6hl(InXUNX);  /* skip 'u' */
  xmkLzTycFccX(InXUNX, InXUNX->m9VTe7 == '{', "missing '{'");
  UrtT3cbm = iYSmzZ(InXUNX);  /* must have at least one digit */
  while (ArFyfqYwNpB(fbxYEX6hl(InXUNX)), A22RHvpap(InXUNX->m9VTe7)) {
    JUxOsWT++;
    xmkLzTycFccX(InXUNX, UrtT3cbm <= (0x7FFFFFFFu >> 4), "UTF-8 value too large");
    UrtT3cbm = (UrtT3cbm << 4) + o6qgnS(InXUNX->m9VTe7);
  }
  xmkLzTycFccX(InXUNX, InXUNX->m9VTe7 == '}', "missing '}'");
  smoruODsDBDx(InXUNX);  /* skip '}' */
  rA8Y(InXUNX->Da46qf, JUxOsWT);  /* remove saved chars from buffer */
  return UrtT3cbm;
}


static void yDWPweS (rr1bsq *InXUNX) {
  char Da46qf[oHDy9McArZh];
  int owBx = e4EnXaUcIz(Da46qf, gwfFxHSn68(InXUNX));
  for (; owBx > 0; owBx--)  /* add 'buff' to string */
    SPkIHrX9Z(InXUNX, Da46qf[oHDy9McArZh - owBx]);
}


static int xib8UrD2C (rr1bsq *InXUNX) {
  int JUxOsWT;
  int UrtT3cbm = 0;  /* result accumulator */
  for (JUxOsWT = 0; JUxOsWT < 3 && YNaU6IJ(InXUNX->m9VTe7); JUxOsWT++) {  /* read up to 3 digits */
    UrtT3cbm = 10*UrtT3cbm + InXUNX->m9VTe7 - '0';
    fbxYEX6hl(InXUNX);
  }
  xmkLzTycFccX(InXUNX, UrtT3cbm <= fTk7ORycO, "decimal escape too large");
  rA8Y(InXUNX->Da46qf, JUxOsWT);  /* remove read digits from buffer */
  return UrtT3cbm;
}


static void cc5M (rr1bsq *InXUNX, int RBLTbYHRpF, OKYV3t *r3LVW) {
  fbxYEX6hl(InXUNX);  /* keep delimiter (for error messages) */
  while (InXUNX->m9VTe7 != RBLTbYHRpF) {
    switch (InXUNX->m9VTe7) {
      case C9Z2:
        LuijGkr_guL(InXUNX, "unfinished string", CvXy4b9fdw);
        break;  /* to avoid warnings */
      case '\n':
      case '\r':
        LuijGkr_guL(InXUNX, "unfinished string", VMgIn3h);
        break;  /* to avoid warnings */
      case '\\': {  /* escape sequences */
        int SMwnU4N;  /* final character to be saved */
        fbxYEX6hl(InXUNX);  /* keep '\\' for error messages */
        switch (InXUNX->m9VTe7) {
          case 'a': SMwnU4N = '\a'; goto VlczUr;
          case 'b': SMwnU4N = '\b'; goto VlczUr;
          case 'f': SMwnU4N = '\f'; goto VlczUr;
          case 'n': SMwnU4N = '\n'; goto VlczUr;
          case 'r': SMwnU4N = '\r'; goto VlczUr;
          case 't': SMwnU4N = '\t'; goto VlczUr;
          case 'v': SMwnU4N = '\v'; goto VlczUr;
          case 'x': SMwnU4N = urAXbv0y(InXUNX); goto VlczUr;
          case 'u': yDWPweS(InXUNX);  goto m59vX;
          case '\n': case '\r':
            PoGsxhVwp(InXUNX); SMwnU4N = '\n'; goto nHEJmfM;
          case '\\': case '\"': case '\'':
            SMwnU4N = InXUNX->m9VTe7; goto VlczUr;
          case C9Z2: goto m59vX;  /* will raise an error next loop */
          case 'z': {  /* zap following span of spaces */
            rA8Y(InXUNX->Da46qf, 1);  /* remove '\\' */
            smoruODsDBDx(InXUNX);  /* skip the 'z' */
            while (ao1UCOiiqOlV(InXUNX->m9VTe7)) {
              if (JsByRunzjwc7(InXUNX)) PoGsxhVwp(InXUNX);
              else smoruODsDBDx(InXUNX);
            }
            goto m59vX;
          }
          default: {
            xmkLzTycFccX(InXUNX, YNaU6IJ(InXUNX->m9VTe7), "invalid escape sequence");
            SMwnU4N = xib8UrD2C(InXUNX);  /* digital escape '\ddd' */
            goto nHEJmfM;
          }
        }
       VlczUr:
         smoruODsDBDx(InXUNX);
         /* go through */
       nHEJmfM:
         rA8Y(InXUNX->Da46qf, 1);  /* remove '\\' */
         SPkIHrX9Z(InXUNX, SMwnU4N);
         /* go through */
       m59vX: break;
      }
      default:
        fbxYEX6hl(InXUNX);
    }
  }
  fbxYEX6hl(InXUNX);  /* skip delimiter */
  r3LVW->acjcGlcv = RKt7_dmrz(InXUNX, DDxxdWHAIR8(InXUNX->Da46qf) + 1,
                                   SnWLQc(InXUNX->Da46qf) - 2);
}


static int LdBucRGsHH (rr1bsq *InXUNX, OKYV3t *r3LVW) {
  MXJVyp9KqU_7(InXUNX->Da46qf);
  for (;;) {
    switch (InXUNX->m9VTe7) {
      case '\n': case '\r': {  /* line breaks */
        PoGsxhVwp(InXUNX);
        break;
      }
      case ' ': case '\f': case '\t': case '\v': {  /* spaces */
        smoruODsDBDx(InXUNX);
        break;
      }
      case '-': {  /* '-' or '--' (comment) */
        smoruODsDBDx(InXUNX);
        if (InXUNX->m9VTe7 != '-') return '-';
        /* else is a comment */
        smoruODsDBDx(InXUNX);
        if (InXUNX->m9VTe7 == '[') {  /* long comment? */
          kDdUJuNWF lBhPtyy = iX_3Q(InXUNX);
          MXJVyp9KqU_7(InXUNX->Da46qf);  /* 'skip_sep' may dirty the buffer */
          if (lBhPtyy >= 2) {
            SeggaH77vxt6(InXUNX, vOGIT5F, lBhPtyy);  /* skip long comment */
            MXJVyp9KqU_7(InXUNX->Da46qf);  /* previous call may dirty the buff. */
            break;
          }
        }
        /* else short comment */
        while (!JsByRunzjwc7(InXUNX) && InXUNX->m9VTe7 != C9Z2)
          smoruODsDBDx(InXUNX);  /* skip until end of line (or end of file) */
        break;
      }
      case '[': {  /* long string or simply '[' */
        kDdUJuNWF lBhPtyy = iX_3Q(InXUNX);
        if (lBhPtyy >= 2) {
          SeggaH77vxt6(InXUNX, r3LVW, lBhPtyy);
          return VMgIn3h;
        }
        else if (lBhPtyy == 0)  /* '[=...' missing second bracket? */
          LuijGkr_guL(InXUNX, "invalid long string delimiter", VMgIn3h);
        return '[';
      }
      case '=': {
        smoruODsDBDx(InXUNX);
        if (Cf5tyULsOo3ZK(InXUNX, '=')) return Ke6gIAGa0V;  /* '==' */
        else return '=';
      }
      case '<': {
        smoruODsDBDx(InXUNX);
        if (Cf5tyULsOo3ZK(InXUNX, '=')) return r_Ap;  /* '<=' */
        else if (Cf5tyULsOo3ZK(InXUNX, '<')) return E495Dbif;  /* '<<' */
        else return '<';
      }
      case '>': {
        smoruODsDBDx(InXUNX);
        if (Cf5tyULsOo3ZK(InXUNX, '=')) return k9nX1;  /* '>=' */
        else if (Cf5tyULsOo3ZK(InXUNX, '>')) return EKBy;  /* '>>' */
        else return '>';
      }
      case '/': {
        smoruODsDBDx(InXUNX);
        if (Cf5tyULsOo3ZK(InXUNX, '/')) return dLviD6a2Pxf;  /* '//' */
        else return '/';
      }
      case '~': {
        smoruODsDBDx(InXUNX);
        if (Cf5tyULsOo3ZK(InXUNX, '=')) return IqmlOSVh8dnl;  /* '~=' */
        else return '~';
      }
      case ':': {
        smoruODsDBDx(InXUNX);
        if (Cf5tyULsOo3ZK(InXUNX, ':')) return eYv9t;  /* '::' */
        else return ':';
      }
      case '"': case '\'': {  /* short literal strings */
        cc5M(InXUNX, InXUNX->m9VTe7, r3LVW);
        return VMgIn3h;
      }
      case '.': {  /* '.', '..', '...', or number */
        fbxYEX6hl(InXUNX);
        if (Cf5tyULsOo3ZK(InXUNX, '.')) {
          if (Cf5tyULsOo3ZK(InXUNX, '.'))
            return n1zJD3mS;   /* '...' */
          else return QlJ9M;   /* '..' */
        }
        else if (!YNaU6IJ(InXUNX->m9VTe7)) return '.';
        else return gxPQN32p(InXUNX, r3LVW);
      }
      case '0': case '1': case '2': case '3': case '4':
      case '5': case '6': case '7': case '8': case '9': {
        return gxPQN32p(InXUNX, r3LVW);
      }
      case C9Z2: {
        return CvXy4b9fdw;
      }
      default: {
        if (mu7ka(InXUNX->m9VTe7)) {  /* identifier or reserved word? */
          GROciXnIu *acjcGlcv;
          do {
            fbxYEX6hl(InXUNX);
          } while (NDU4Zj3n(InXUNX->m9VTe7));
          acjcGlcv = RKt7_dmrz(InXUNX, DDxxdWHAIR8(InXUNX->Da46qf),
                                  SnWLQc(InXUNX->Da46qf));
          r3LVW->acjcGlcv = acjcGlcv;
          if (rMT0LBekdNRl(acjcGlcv))  /* reserved word? */
            return acjcGlcv->i04F - 1 + IPNABu;
          else {
            return Pm8ku;
          }
        }
        else {  /* single-char tokens ('+', '*', '%', '{', '}', ...) */
          int SMwnU4N = InXUNX->m9VTe7;
          smoruODsDBDx(InXUNX);
          return SMwnU4N;
        }
      }
    }
  }
}


void NAy4Ny8noHw (rr1bsq *InXUNX) {
  InXUNX->ViGL4JAHpP = InXUNX->g9TSbra7;
  if (InXUNX->sIlN.YarlwcJ != CvXy4b9fdw) {  /* is there a look-ahead token? */
    InXUNX->yWx9s5n8T8 = InXUNX->sIlN;  /* use this one */
    InXUNX->sIlN.YarlwcJ = CvXy4b9fdw;  /* and discharge it */
  }
  else
    InXUNX->yWx9s5n8T8.YarlwcJ = LdBucRGsHH(InXUNX, &InXUNX->yWx9s5n8T8.r3LVW);  /* read next token */
}


int f8mHowU7p3bU (rr1bsq *InXUNX) {
  QAhKv(InXUNX->sIlN.YarlwcJ == CvXy4b9fdw);
  InXUNX->sIlN.YarlwcJ = LdBucRGsHH(InXUNX, &InXUNX->sIlN.r3LVW);
  return InXUNX->sIlN.YarlwcJ;
}

