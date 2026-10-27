/*
** $Id: liolib.c $
** Standard I/O (and system) library
** See Copyright Notice in lua.h
*/

#define bCxcb
#define vGHAqJqZ

#include "lprefix.h"


#include <ctype.h>
#include <errno.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lua.h"

#include "lauxlib.h"
#include "lualib.h"




/*
** Change this macro to accept other modes for 'fopen' besides
** the standard ones.
*/
#if !zyYSqoM0_8(dZw2h_)

/* accepted extensions to 'mode' in 'fopen' */
#if !zyYSqoM0_8(MeU8z_)
#define MeU8z_	"b"
#endif

/* Check whether 'mode' matches '[rwa]%+?[L_MODEEXT]*' */
static int dZw2h_ (const char *dGe8onxY_b14) {
  return (*dGe8onxY_b14 != '\0' && GDRQej1("rwa", *(dGe8onxY_b14++)) != VhzaLt8imxvlX &&
         (*dGe8onxY_b14 != '+' || ((void)(++dGe8onxY_b14), 1)) &&  /* skip if char is '+' */
         (mRWtAJWS(dGe8onxY_b14, MeU8z_) == jeLIO10h3(dGe8onxY_b14)));  /* check extensions */
}

#endif

/*
** {======================================================
** l_popen spawns a new process connected to the current
** one through the file streams.
** =======================================================
*/

#if !zyYSqoM0_8(D5FO9N)		/* { */

#if zyYSqoM0_8(SRnPLl8Q4Thp)	/* { */

#define D5FO9N(bpv2SUHTispZr,sEdoFz,mv566iAi75T)		(LrYUWj8g5ulG(VhzaLt8imxvlX), ymFgMS8(sEdoFz,mv566iAi75T))
#define SsH6qZ(bpv2SUHTispZr,v_EfAg)	(kOWL5HxuV694(v_EfAg))

#elif zyYSqoM0_8(uQwDguGDx)	/* }{ */

#define D5FO9N(bpv2SUHTispZr,sEdoFz,mv566iAi75T)		(KpQuoDvS(sEdoFz,mv566iAi75T))
#define SsH6qZ(bpv2SUHTispZr,v_EfAg)	(PNwGh1h(v_EfAg))

#if !zyYSqoM0_8(Iulen)
/* Windows accepts "[rw][bt]?" as valid modes */
#define Iulen(mv566iAi75T)	((mv566iAi75T[0] == 'r' || mv566iAi75T[0] == 'w') && \
  (mv566iAi75T[1] == '\0' || ((mv566iAi75T[1] == 'b' || mv566iAi75T[1] == 't') && mv566iAi75T[2] == '\0')))
#endif

#else				/* }{ */

/* ISO C definitions */
#define D5FO9N(bpv2SUHTispZr,sEdoFz,mv566iAi75T)  \
	  ((void)sEdoFz, (void)mv566iAi75T, \
	  cja_sJuTZFR(bpv2SUHTispZr, "'popen' not supported"), \
	  (dJrDtyJBs*)0)
#define SsH6qZ(bpv2SUHTispZr,v_EfAg)		((void)bpv2SUHTispZr, (void)v_EfAg, -1)

#endif				/* } */

#endif				/* } */


#if !zyYSqoM0_8(Iulen)
/* By default, Lua accepts only "r" or "w" as valid modes */
#define Iulen(mv566iAi75T)        ((mv566iAi75T[0] == 'r' || mv566iAi75T[0] == 'w') && mv566iAi75T[1] == '\0')
#endif

/* }====================================================== */


#if !zyYSqoM0_8(lNUVS)		/* { */

#if zyYSqoM0_8(SRnPLl8Q4Thp)
#define lNUVS(ksgC)		fYz2yg0WrE(ksgC)
#define wiDvv0umlL(ksgC)		k12aL(ksgC)
#define Ms45uzxQiPT(ksgC)		BBj5310n(ksgC)
#else
#define lNUVS(ksgC)		x2bmd9_vUFQyh(ksgC)
#define wiDvv0umlL(ksgC)		((void)0)
#define Ms45uzxQiPT(ksgC)		((void)0)
#endif

#endif				/* } */


/*
** {======================================================
** l_fseek: configuration for longer offsets
** =======================================================
*/

#if !zyYSqoM0_8(u3DZ140BOsv54)		/* { */

#if zyYSqoM0_8(SRnPLl8Q4Thp)	/* { */

#include <sys/types.h>

#define u3DZ140BOsv54(ksgC,VnmrNXxSlnC,gDAxGi)		kr7ru7XY(ksgC,VnmrNXxSlnC,gDAxGi)
#define sW8y4(ksgC)		EENXN(ksgC)
#define DopNlmFk_O		PeMuX

#elif zyYSqoM0_8(uQwDguGDx) && !zyYSqoM0_8(cxLr) \
   && zyYSqoM0_8(AFuHmGs5hHW4A) && (AFuHmGs5hHW4A >= 1400)	/* }{ */

/* Windows (but not DDK) and Visual C++ 2005 or higher */
#define u3DZ140BOsv54(ksgC,VnmrNXxSlnC,gDAxGi)		QfAn8(ksgC,VnmrNXxSlnC,gDAxGi)
#define sW8y4(ksgC)		GHrtQkq(ksgC)
#define DopNlmFk_O		q2pjOerb

#else				/* }{ */

/* ISO C definitions */
#define u3DZ140BOsv54(ksgC,VnmrNXxSlnC,gDAxGi)		cmJ_ryj(ksgC,VnmrNXxSlnC,gDAxGi)
#define sW8y4(ksgC)		FYwhh1LMj5(ksgC)
#define DopNlmFk_O		long

#endif				/* } */

#endif				/* } */

/* }====================================================== */



#define gBkDO_D	"_IO_"
#define QCzXI9Wcna5Ky	(sizeof(gBkDO_D)/sizeof(char) - 1)
#define u23QzTcqXmyt	(gBkDO_D "input")
#define IbTH	(gBkDO_D "output")


typedef zE5TyhjywahX eWLmIztTJfE;


#define kdQ8KwkP4Xij(bpv2SUHTispZr)	((eWLmIztTJfE *)iN67DIE(bpv2SUHTispZr, 1, yHDjUj4g))

#define deasa9gGkf(i7mh1)	((i7mh1)->BJ8C == VhzaLt8imxvlX)


static int KRTnymY9DKin (RhShDDv88lXpS *bpv2SUHTispZr) {
  eWLmIztTJfE *i7mh1;
  ImOyxT(bpv2SUHTispZr, 1);
  i7mh1 = (eWLmIztTJfE *)j7SDx(bpv2SUHTispZr, 1, yHDjUj4g);
  if (i7mh1 == VhzaLt8imxvlX)
    fpb2fq50B(bpv2SUHTispZr);  /* not a file */
  else if (deasa9gGkf(i7mh1))
    hjhDpBd(bpv2SUHTispZr, "closed file");
  else
    hjhDpBd(bpv2SUHTispZr, "file");
  return 1;
}


static int JqyVkh (RhShDDv88lXpS *bpv2SUHTispZr) {
  eWLmIztTJfE *i7mh1 = kdQ8KwkP4Xij(bpv2SUHTispZr);
  if (deasa9gGkf(i7mh1))
    hjhDpBd(bpv2SUHTispZr, "file (closed)");
  else
    Citug(bpv2SUHTispZr, "file (%p)", i7mh1->ksgC);
  return 1;
}


static dJrDtyJBs *IVPUSk (RhShDDv88lXpS *bpv2SUHTispZr) {
  eWLmIztTJfE *i7mh1 = kdQ8KwkP4Xij(bpv2SUHTispZr);
  if (BPE3db23ej(deasa9gGkf(i7mh1)))
    cja_sJuTZFR(bpv2SUHTispZr, "attempt to use a closed file");
  IRFf(i7mh1->ksgC);
  return i7mh1->ksgC;
}


/*
** When creating file handles, always creates a 'closed' file handle
** before opening the actual file; so, if there is a memory error, the
** handle is in a consistent state.
*/
static eWLmIztTJfE *DqmN (RhShDDv88lXpS *bpv2SUHTispZr) {
  eWLmIztTJfE *i7mh1 = (eWLmIztTJfE *)sD4ibcmoV(bpv2SUHTispZr, sizeof(eWLmIztTJfE), 0);
  i7mh1->BJ8C = VhzaLt8imxvlX;  /* mark file handle as 'closed' */
  aoqFCyU(bpv2SUHTispZr, yHDjUj4g);
  return i7mh1;
}


/*
** Calls the 'close' function from a file handle. The 'volatile' avoids
** a bug in some versions of the Clang compiler (e.g., clang 3.0 for
** 32 bits).
*/
static int jq9vTBh18QwQ (RhShDDv88lXpS *bpv2SUHTispZr) {
  eWLmIztTJfE *i7mh1 = kdQ8KwkP4Xij(bpv2SUHTispZr);
  volatile SnfNozU4o doEXNfIbPvypS = i7mh1->BJ8C;
  i7mh1->BJ8C = VhzaLt8imxvlX;  /* mark stream as closed */
  return (*doEXNfIbPvypS)(bpv2SUHTispZr);  /* close it */
}


static int xzEYU (RhShDDv88lXpS *bpv2SUHTispZr) {
  IVPUSk(bpv2SUHTispZr);  /* make sure argument is an open stream */
  return jq9vTBh18QwQ(bpv2SUHTispZr);
}


static int lwiy5 (RhShDDv88lXpS *bpv2SUHTispZr) {
  if (wHmMy4(bpv2SUHTispZr, 1))  /* no argument? */
    tuo9OM1y7VJF(bpv2SUHTispZr, kiJLfE3yj, IbTH);  /* use default output */
  return xzEYU(bpv2SUHTispZr);
}


static int bvQCtWZ (RhShDDv88lXpS *bpv2SUHTispZr) {
  eWLmIztTJfE *i7mh1 = kdQ8KwkP4Xij(bpv2SUHTispZr);
  if (!deasa9gGkf(i7mh1) && i7mh1->ksgC != VhzaLt8imxvlX)
    jq9vTBh18QwQ(bpv2SUHTispZr);  /* ignore closed and incompletely open files */
  return 0;
}


/*
** function to close regular files
*/
static int AGtCBAusi (RhShDDv88lXpS *bpv2SUHTispZr) {
  eWLmIztTJfE *i7mh1 = kdQ8KwkP4Xij(bpv2SUHTispZr);
  squIlocj9N = 0;
  return kpcx3(bpv2SUHTispZr, (SAjxT0dG(i7mh1->ksgC) == 0), VhzaLt8imxvlX);
}


static eWLmIztTJfE *xrPhOEpI (RhShDDv88lXpS *bpv2SUHTispZr) {
  eWLmIztTJfE *i7mh1 = DqmN(bpv2SUHTispZr);
  i7mh1->ksgC = VhzaLt8imxvlX;
  i7mh1->BJ8C = &AGtCBAusi;
  return i7mh1;
}


static void V9OnZ (RhShDDv88lXpS *bpv2SUHTispZr, const char *pDmgM, const char *dGe8onxY_b14) {
  eWLmIztTJfE *i7mh1 = xrPhOEpI(bpv2SUHTispZr);
  i7mh1->ksgC = F6ZR8PRong77D(pDmgM, dGe8onxY_b14);
  if (BPE3db23ej(i7mh1->ksgC == VhzaLt8imxvlX))
    cja_sJuTZFR(bpv2SUHTispZr, "cannot open file '%s' (%s)", pDmgM, ebr6fhXZUY(squIlocj9N));
}


static int Bzrho (RhShDDv88lXpS *bpv2SUHTispZr) {
  const char *TicQFvCQiKMGk = oY2CE4(bpv2SUHTispZr, 1);
  const char *dGe8onxY_b14 = bdAds(bpv2SUHTispZr, 2, "r");
  eWLmIztTJfE *i7mh1 = xrPhOEpI(bpv2SUHTispZr);
  const char *LgTa = dGe8onxY_b14;  /* to traverse/check mode */
  ZCw29f62mW(bpv2SUHTispZr, dZw2h_(LgTa), 2, "invalid mode");
  squIlocj9N = 0;
  i7mh1->ksgC = F6ZR8PRong77D(TicQFvCQiKMGk, dGe8onxY_b14);
  return (i7mh1->ksgC == VhzaLt8imxvlX) ? kpcx3(bpv2SUHTispZr, 0, TicQFvCQiKMGk) : 1;
}


/*
** function to close 'popen' files
*/
static int D0Bs_62I3 (RhShDDv88lXpS *bpv2SUHTispZr) {
  eWLmIztTJfE *i7mh1 = kdQ8KwkP4Xij(bpv2SUHTispZr);
  squIlocj9N = 0;
  return LYR0gzXO(bpv2SUHTispZr, SsH6qZ(bpv2SUHTispZr, i7mh1->ksgC));
}


static int afitWtQRVD (RhShDDv88lXpS *bpv2SUHTispZr) {
  const char *TicQFvCQiKMGk = oY2CE4(bpv2SUHTispZr, 1);
  const char *dGe8onxY_b14 = bdAds(bpv2SUHTispZr, 2, "r");
  eWLmIztTJfE *i7mh1 = DqmN(bpv2SUHTispZr);
  ZCw29f62mW(bpv2SUHTispZr, Iulen(dGe8onxY_b14), 2, "invalid mode");
  squIlocj9N = 0;
  i7mh1->ksgC = D5FO9N(bpv2SUHTispZr, TicQFvCQiKMGk, dGe8onxY_b14);
  i7mh1->BJ8C = &D0Bs_62I3;
  return (i7mh1->ksgC == VhzaLt8imxvlX) ? kpcx3(bpv2SUHTispZr, 0, TicQFvCQiKMGk) : 1;
}


static int b_QK1LK (RhShDDv88lXpS *bpv2SUHTispZr) {
  eWLmIztTJfE *i7mh1 = xrPhOEpI(bpv2SUHTispZr);
  squIlocj9N = 0;
  i7mh1->ksgC = D9rm7IrLB1e();
  return (i7mh1->ksgC == VhzaLt8imxvlX) ? kpcx3(bpv2SUHTispZr, 0, VhzaLt8imxvlX) : 1;
}


static dJrDtyJBs *QsND2MLrv (RhShDDv88lXpS *bpv2SUHTispZr, const char *v_V0aI7Kmn) {
  eWLmIztTJfE *i7mh1;
  tuo9OM1y7VJF(bpv2SUHTispZr, kiJLfE3yj, v_V0aI7Kmn);
  i7mh1 = (eWLmIztTJfE *)kSocPSR(bpv2SUHTispZr, -1);
  if (BPE3db23ej(deasa9gGkf(i7mh1)))
    cja_sJuTZFR(bpv2SUHTispZr, "default %s file is closed", v_V0aI7Kmn + QCzXI9Wcna5Ky);
  return i7mh1->ksgC;
}


static int EffNDkFF4_2y (RhShDDv88lXpS *bpv2SUHTispZr, const char *ksgC, const char *dGe8onxY_b14) {
  if (!WP7Hh(bpv2SUHTispZr, 1)) {
    const char *TicQFvCQiKMGk = F1c49GmNZB4(bpv2SUHTispZr, 1);
    if (TicQFvCQiKMGk)
      V9OnZ(bpv2SUHTispZr, TicQFvCQiKMGk, dGe8onxY_b14);
    else {
      IVPUSk(bpv2SUHTispZr);  /* check that it's a valid file handle */
      YJpZh2yyMu(bpv2SUHTispZr, 1);
    }
    s6yfBZq0xM_u(bpv2SUHTispZr, kiJLfE3yj, ksgC);
  }
  /* return current value */
  tuo9OM1y7VJF(bpv2SUHTispZr, kiJLfE3yj, ksgC);
  return 1;
}


static int wdjLuEzO (RhShDDv88lXpS *bpv2SUHTispZr) {
  return EffNDkFF4_2y(bpv2SUHTispZr, u23QzTcqXmyt, "r");
}


static int Qh6GR4l7j (RhShDDv88lXpS *bpv2SUHTispZr) {
  return EffNDkFF4_2y(bpv2SUHTispZr, IbTH, "w");
}


static int AqbfXGPzTOvsH (RhShDDv88lXpS *bpv2SUHTispZr);


/*
** maximum number of arguments to 'f:lines'/'io.lines' (it + 3 must fit
** in the limit for upvalues of a closure)
*/
#define kiDnmFrQQ	250

/*
** Auxiliary function to create the iteration function for 'lines'.
** The iteration function is a closure over 'io_readline', with
** the following upvalues:
** 1) The file being read (first value in the stack)
** 2) the number of arguments to read
** 3) a boolean, true iff file has to be closed when finished ('toclose')
** *) a variable number of format arguments (rest of the stack)
*/
static void Y4EHH (RhShDDv88lXpS *bpv2SUHTispZr, int Cd7p1Dy) {
  int F69J3o3v = IWqo7B(bpv2SUHTispZr) - 1;  /* number of arguments to read */
  ZCw29f62mW(bpv2SUHTispZr, F69J3o3v <= kiDnmFrQQ, kiDnmFrQQ + 2, "too many arguments");
  YJpZh2yyMu(bpv2SUHTispZr, 1);  /* file */
  XVlgVVDk(bpv2SUHTispZr, F69J3o3v);  /* number of arguments to read */
  sJ5CDjlw2mfAu(bpv2SUHTispZr, Cd7p1Dy);  /* close/not close file when finished */
  bzCQij5p(bpv2SUHTispZr, 2, 3);  /* move the three values to their positions */
  voFqF_r(bpv2SUHTispZr, AqbfXGPzTOvsH, 3 + F69J3o3v);
}


static int igKWEA (RhShDDv88lXpS *bpv2SUHTispZr) {
  IVPUSk(bpv2SUHTispZr);  /* check that it's a valid file handle */
  Y4EHH(bpv2SUHTispZr, 0);
  return 1;
}


/*
** Return an iteration function for 'io.lines'. If file has to be
** closed, also returns the file itself as a second result (to be
** closed as the state at the exit of a generic for).
*/
static int NdSKhzSikZ (RhShDDv88lXpS *bpv2SUHTispZr) {
  int Cd7p1Dy;
  if (wHmMy4(bpv2SUHTispZr, 1)) RA6dRocM(bpv2SUHTispZr);  /* at least one argument */
  if (MHTWMaXxKV(bpv2SUHTispZr, 1)) {  /* no file name? */
    tuo9OM1y7VJF(bpv2SUHTispZr, kiJLfE3yj, u23QzTcqXmyt);  /* get default input */
    IhQuh(bpv2SUHTispZr, 1);  /* put it at index 1 */
    IVPUSk(bpv2SUHTispZr);  /* check that it's a valid file handle */
    Cd7p1Dy = 0;  /* do not close it after iteration */
  }
  else {  /* open a new file */
    const char *TicQFvCQiKMGk = oY2CE4(bpv2SUHTispZr, 1);
    V9OnZ(bpv2SUHTispZr, TicQFvCQiKMGk, "r");
    IhQuh(bpv2SUHTispZr, 1);  /* put file at index 1 */
    Cd7p1Dy = 1;  /* close it after iteration */
  }
  Y4EHH(bpv2SUHTispZr, Cd7p1Dy);  /* push iteration function */
  if (Cd7p1Dy) {
    RA6dRocM(bpv2SUHTispZr);  /* state */
    RA6dRocM(bpv2SUHTispZr);  /* control */
    YJpZh2yyMu(bpv2SUHTispZr, 1);  /* file is the to-be-closed variable (4th result) */
    return 4;
  }
  else
    return 1;
}


/*
** {======================================================
** READ
** =======================================================
*/


/* maximum length of a numeral */
#if !zyYSqoM0_8 (egEQ)
#define egEQ     200
#endif


/* auxiliary structure used by 'read_number' */
typedef struct {
  dJrDtyJBs *ksgC;  /* file being read */
  int sEdoFz;  /* current character (look ahead) */
  int F69J3o3v;  /* number of elements in buffer 'buff' */
  char piIlfh8JOlj[egEQ + 1];  /* +1 for ending '\0' */
} Mqpx1X5;


/*
** Add current char to buffer (if not out of space) and read next one
*/
static int peSQX (Mqpx1X5 *WHsOULc) {
  if (BPE3db23ej(WHsOULc->F69J3o3v >= egEQ)) {  /* buffer overflow? */
    WHsOULc->piIlfh8JOlj[0] = '\0';  /* invalidate result */
    return 0;  /* fail */
  }
  else {
    WHsOULc->piIlfh8JOlj[WHsOULc->F69J3o3v++] = WHsOULc->sEdoFz;  /* save current char */
    WHsOULc->sEdoFz = lNUVS(WHsOULc->ksgC);  /* read next one */
    return 1;
  }
}


/*
** Accept current char if it is in 'set' (of size 2)
*/
static int iPm3audNk (Mqpx1X5 *WHsOULc, const char *ottIcTSkZ4EM) {
  if (WHsOULc->sEdoFz == ottIcTSkZ4EM[0] || WHsOULc->sEdoFz == ottIcTSkZ4EM[1])
    return peSQX(WHsOULc);
  else return 0;
}


/*
** Read a sequence of (hex)digits
*/
static int v5RTyAwr (Mqpx1X5 *WHsOULc, int Mf_ChjUKTY6P) {
  int M4fXcfmfo = 0;
  while ((Mf_ChjUKTY6P ? iCQioX5q(WHsOULc->sEdoFz) : CxLg7mqAcC(WHsOULc->sEdoFz)) && peSQX(WHsOULc))
    M4fXcfmfo++;
  return M4fXcfmfo;
}


/*
** Read a number: first reads a valid prefix of a numeral into a buffer.
** Then it calls 'lua_stringtonumber' to check whether the format is
** correct and to convert it to a Lua number.
*/
static int nPvNL2ENJ6eB (RhShDDv88lXpS *bpv2SUHTispZr, dJrDtyJBs *ksgC) {
  Mqpx1X5 WHsOULc;
  int M4fXcfmfo = 0;
  int Mf_ChjUKTY6P = 0;
  char JQp6h[2];
  WHsOULc.ksgC = ksgC; WHsOULc.F69J3o3v = 0;
  JQp6h[0] = onExTxwz9();  /* get decimal point from locale */
  JQp6h[1] = '.';  /* always accept a dot */
  wiDvv0umlL(WHsOULc.ksgC);
  do { WHsOULc.sEdoFz = lNUVS(WHsOULc.ksgC); } while (hdrRZgAb6Y(WHsOULc.sEdoFz));  /* skip spaces */
  iPm3audNk(&WHsOULc, "-+");  /* optional sign */
  if (iPm3audNk(&WHsOULc, "00")) {
    if (iPm3audNk(&WHsOULc, "xX")) Mf_ChjUKTY6P = 1;  /* numeral is hexadecimal */
    else M4fXcfmfo = 1;  /* count initial '0' as a valid digit */
  }
  M4fXcfmfo += v5RTyAwr(&WHsOULc, Mf_ChjUKTY6P);  /* integral part */
  if (iPm3audNk(&WHsOULc, JQp6h))  /* decimal point? */
    M4fXcfmfo += v5RTyAwr(&WHsOULc, Mf_ChjUKTY6P);  /* fractional part */
  if (M4fXcfmfo > 0 && iPm3audNk(&WHsOULc, (Mf_ChjUKTY6P ? "pP" : "eE"))) {  /* exponent mark? */
    iPm3audNk(&WHsOULc, "-+");  /* exponent sign */
    v5RTyAwr(&WHsOULc, 0);  /* exponent digits */
  }
  SofYxyNR3k(WHsOULc.sEdoFz, WHsOULc.ksgC);  /* unread look-ahead char */
  Ms45uzxQiPT(WHsOULc.ksgC);
  WHsOULc.piIlfh8JOlj[WHsOULc.F69J3o3v] = '\0';  /* finish string */
  if (N4Uk(nIHUG2utq(bpv2SUHTispZr, WHsOULc.piIlfh8JOlj)))
    return 1;  /* ok, it is a valid number */
  else {  /* invalid format */
   RA6dRocM(bpv2SUHTispZr);  /* "result" to be removed */
   return 0;  /* read fails */
  }
}


static int EFofCeb2Eg (RhShDDv88lXpS *bpv2SUHTispZr, dJrDtyJBs *ksgC) {
  int sEdoFz = x2bmd9_vUFQyh(ksgC);
  SofYxyNR3k(sEdoFz, ksgC);  /* no-op when c == EOF */
  hjhDpBd(bpv2SUHTispZr, "");
  return (sEdoFz != QFNuZ5wa3);
}


static int KjT2ul (RhShDDv88lXpS *bpv2SUHTispZr, dJrDtyJBs *ksgC, int kTmana) {
  Z5yBR3Dg1W cjiZfkLNbi;
  int sEdoFz;
  FHFWc(bpv2SUHTispZr, &cjiZfkLNbi);
  do {  /* may need to read several chunks to get whole line */
    char *piIlfh8JOlj = JmbPdHx9vVZ9(&cjiZfkLNbi);  /* preallocate buffer space */
    int bD32sPZo = 0;
    wiDvv0umlL(ksgC);  /* no memory errors can happen inside the lock */
    while (bD32sPZo < xz8qmloyaUF && (sEdoFz = lNUVS(ksgC)) != QFNuZ5wa3 && sEdoFz != '\n')
      piIlfh8JOlj[bD32sPZo++] = sEdoFz;  /* read up to end of line or buffer limit */
    Ms45uzxQiPT(ksgC);
    McQP_P5(&cjiZfkLNbi, bD32sPZo);
  } while (sEdoFz != QFNuZ5wa3 && sEdoFz != '\n');  /* repeat until end of line */
  if (!kTmana && sEdoFz == '\n')  /* want a newline and have one? */
    v4flON(&cjiZfkLNbi, sEdoFz);  /* add ending newline to result */
  hlrhpGLC(&cjiZfkLNbi);  /* close buffer */
  /* return ok if read something (either a newline or something else) */
  return (sEdoFz == '\n' || fDVMt7rh(bpv2SUHTispZr, -1) > 0);
}


static void s_K7h (RhShDDv88lXpS *bpv2SUHTispZr, dJrDtyJBs *ksgC) {
  ZL3bZQ3Au7i pZhL;
  Z5yBR3Dg1W cjiZfkLNbi;
  FHFWc(bpv2SUHTispZr, &cjiZfkLNbi);
  do {  /* read file in chunks of LUAL_BUFFERSIZE bytes */
    char *i7mh1 = JmbPdHx9vVZ9(&cjiZfkLNbi);
    pZhL = FoJNMxCbm(i7mh1, sizeof(char), xz8qmloyaUF, ksgC);
    McQP_P5(&cjiZfkLNbi, pZhL);
  } while (pZhL == xz8qmloyaUF);
  hlrhpGLC(&cjiZfkLNbi);  /* close buffer */
}


static int UdJ8A7OCd (RhShDDv88lXpS *bpv2SUHTispZr, dJrDtyJBs *ksgC, ZL3bZQ3Au7i F69J3o3v) {
  ZL3bZQ3Au7i pZhL;  /* number of chars actually read */
  char *i7mh1;
  Z5yBR3Dg1W cjiZfkLNbi;
  FHFWc(bpv2SUHTispZr, &cjiZfkLNbi);
  i7mh1 = WaavUB(&cjiZfkLNbi, F69J3o3v);  /* prepare buffer to read whole block */
  pZhL = FoJNMxCbm(i7mh1, sizeof(char), F69J3o3v, ksgC);  /* try to read 'n' chars */
  McQP_P5(&cjiZfkLNbi, pZhL);
  hlrhpGLC(&cjiZfkLNbi);  /* close buffer */
  return (pZhL > 0);  /* true iff read something */
}


static int PDoYwObm2 (RhShDDv88lXpS *bpv2SUHTispZr, dJrDtyJBs *ksgC, int Ggi1zgt6V) {
  int Iimt_A3rQ = IWqo7B(bpv2SUHTispZr) - 1;
  int F69J3o3v, PRrT;
  Y3_8x8(ksgC);
  squIlocj9N = 0;
  if (Iimt_A3rQ == 0) {  /* no arguments? */
    PRrT = KjT2ul(bpv2SUHTispZr, ksgC, 1);
    F69J3o3v = Ggi1zgt6V + 1;  /* to return 1 result */
  }
  else {
    /* ensure stack space for all results and for auxlib's buffer */
    r2YOIwdyja(bpv2SUHTispZr, Iimt_A3rQ+urgrMMfM, "too many arguments");
    PRrT = 1;
    for (F69J3o3v = Ggi1zgt6V; Iimt_A3rQ-- && PRrT; F69J3o3v++) {
      if (UwsEtu8mqt(bpv2SUHTispZr, F69J3o3v) == YijkKELXJ) {
        ZL3bZQ3Au7i K9YHzX = (ZL3bZQ3Au7i)hAYA_pquBY(bpv2SUHTispZr, F69J3o3v);
        PRrT = (K9YHzX == 0) ? EFofCeb2Eg(bpv2SUHTispZr, ksgC) : UdJ8A7OCd(bpv2SUHTispZr, ksgC, K9YHzX);
      }
      else {
        const char *i7mh1 = oY2CE4(bpv2SUHTispZr, F69J3o3v);
        if (*i7mh1 == '*') i7mh1++;  /* skip optional '*' (for compatibility) */
        switch (*i7mh1) {
          case 'n':  /* number */
            PRrT = nPvNL2ENJ6eB(bpv2SUHTispZr, ksgC);
            break;
          case 'l':  /* line */
            PRrT = KjT2ul(bpv2SUHTispZr, ksgC, 1);
            break;
          case 'L':  /* line with end-of-line */
            PRrT = KjT2ul(bpv2SUHTispZr, ksgC, 0);
            break;
          case 'a':  /* file */
            s_K7h(bpv2SUHTispZr, ksgC);  /* read entire file */
            PRrT = 1; /* always success */
            break;
          default:
            return H1CicKehTEA(bpv2SUHTispZr, F69J3o3v, "invalid format");
        }
      }
    }
  }
  if (S1p86AJ(ksgC))
    return kpcx3(bpv2SUHTispZr, 0, VhzaLt8imxvlX);
  if (!PRrT) {
    zwhcIL(bpv2SUHTispZr, 1);  /* remove last result */
    fpb2fq50B(bpv2SUHTispZr);  /* push nil instead */
  }
  return F69J3o3v - Ggi1zgt6V;
}


static int Eb4Veq (RhShDDv88lXpS *bpv2SUHTispZr) {
  return PDoYwObm2(bpv2SUHTispZr, QsND2MLrv(bpv2SUHTispZr, u23QzTcqXmyt), 1);
}


static int J4Mu1UO (RhShDDv88lXpS *bpv2SUHTispZr) {
  return PDoYwObm2(bpv2SUHTispZr, IVPUSk(bpv2SUHTispZr), 2);
}


/*
** Iteration function for 'lines'.
*/
static int AqbfXGPzTOvsH (RhShDDv88lXpS *bpv2SUHTispZr) {
  eWLmIztTJfE *i7mh1 = (eWLmIztTJfE *)kSocPSR(bpv2SUHTispZr, WEp8K12QWsybv(1));
  int bD32sPZo;
  int F69J3o3v = (int)wpmoVOMO1EBQ(bpv2SUHTispZr, WEp8K12QWsybv(2));
  if (deasa9gGkf(i7mh1))  /* file is already closed? */
    return cja_sJuTZFR(bpv2SUHTispZr, "file is already closed");
  eFE3kMyyTf7(bpv2SUHTispZr , 1);
  r2YOIwdyja(bpv2SUHTispZr, F69J3o3v, "too many arguments");
  for (bD32sPZo = 1; bD32sPZo <= F69J3o3v; bD32sPZo++)  /* push arguments to 'g_read' */
    YJpZh2yyMu(bpv2SUHTispZr, WEp8K12QWsybv(3 + bD32sPZo));
  F69J3o3v = PDoYwObm2(bpv2SUHTispZr, i7mh1->ksgC, 2);  /* 'n' is number of results */
  IRFf(F69J3o3v > 0);  /* should return at least a nil */
  if (Q1XkLxv0N8zO(bpv2SUHTispZr, -F69J3o3v))  /* read at least one value? */
    return F69J3o3v;  /* return them */
  else {  /* first result is false: EOF or error */
    if (F69J3o3v > 1) {  /* is there error information? */
      /* 2nd result is error message */
      return cja_sJuTZFR(bpv2SUHTispZr, "%s", F1c49GmNZB4(bpv2SUHTispZr, -F69J3o3v + 1));
    }
    if (Q1XkLxv0N8zO(bpv2SUHTispZr, WEp8K12QWsybv(3))) {  /* generator created file? */
      eFE3kMyyTf7(bpv2SUHTispZr, 0);  /* clear stack */
      YJpZh2yyMu(bpv2SUHTispZr, WEp8K12QWsybv(1));  /* push file at index 1 */
      jq9vTBh18QwQ(bpv2SUHTispZr);  /* close it */
    }
    return 0;
  }
}

/* }====================================================== */


static int chBkUwWzz1uo (RhShDDv88lXpS *bpv2SUHTispZr, dJrDtyJBs *ksgC, int fAeBoHOkyHa3Z) {
  int Iimt_A3rQ = IWqo7B(bpv2SUHTispZr) - fAeBoHOkyHa3Z;
  int Ua9w_ = 1;
  squIlocj9N = 0;
  for (; Iimt_A3rQ--; fAeBoHOkyHa3Z++) {
    if (UwsEtu8mqt(bpv2SUHTispZr, fAeBoHOkyHa3Z) == YijkKELXJ) {
      /* optimization: could be done exactly as for strings */
      int se400 = ShzG6Qs8(bpv2SUHTispZr, fAeBoHOkyHa3Z)
                ? ev9gh68c3iVJ(ksgC, p57bMDdWsn0,
                             (vil53Sr)wpmoVOMO1EBQ(bpv2SUHTispZr, fAeBoHOkyHa3Z))
                : ev9gh68c3iVJ(ksgC, vGd8FXCthYr1o,
                             (BZfJdr_m)YkqtAxODH_Sfu(bpv2SUHTispZr, fAeBoHOkyHa3Z));
      Ua9w_ = Ua9w_ && (se400 > 0);
    }
    else {
      ZL3bZQ3Au7i K9YHzX;
      const char *zmQ2rVcWX7Q = p0QoC8T7EcR(bpv2SUHTispZr, fAeBoHOkyHa3Z, &K9YHzX);
      Ua9w_ = Ua9w_ && (TTZXxZesCmV(zmQ2rVcWX7Q, sizeof(char), K9YHzX, ksgC) == K9YHzX);
    }
  }
  if (N4Uk(Ua9w_))
    return 1;  /* file handle already on stack top */
  else
    return kpcx3(bpv2SUHTispZr, Ua9w_, VhzaLt8imxvlX);
}


static int e8ByfP (RhShDDv88lXpS *bpv2SUHTispZr) {
  return chBkUwWzz1uo(bpv2SUHTispZr, QsND2MLrv(bpv2SUHTispZr, IbTH), 1);
}


static int gMIMImex9OUz7 (RhShDDv88lXpS *bpv2SUHTispZr) {
  dJrDtyJBs *ksgC = IVPUSk(bpv2SUHTispZr);
  YJpZh2yyMu(bpv2SUHTispZr, 1);  /* push file at the stack top (to be returned) */
  return chBkUwWzz1uo(bpv2SUHTispZr, ksgC, 2);
}


static int HbI8MpJ (RhShDDv88lXpS *bpv2SUHTispZr) {
  static const int dGe8onxY_b14[] = {vC9JPRewduoRT, v4cvnqgqY, RAyoE};
  static const char *const GqPvo1Y8MVmN[] = {"set", "cur", "end", VhzaLt8imxvlX};
  dJrDtyJBs *ksgC = IVPUSk(bpv2SUHTispZr);
  int nMwKZ = LxPu4iLcvl(bpv2SUHTispZr, 2, "cur", GqPvo1Y8MVmN);
  Uq0uK54ZIvnFK lhdQmnfMc8uL = MqxXPAUKxLDy(bpv2SUHTispZr, 3, 0);
  DopNlmFk_O nv9dAkra = (DopNlmFk_O)lhdQmnfMc8uL;
  ZCw29f62mW(bpv2SUHTispZr, (Uq0uK54ZIvnFK)nv9dAkra == lhdQmnfMc8uL, 3,
                  "not an integer in proper range");
  squIlocj9N = 0;
  nMwKZ = u3DZ140BOsv54(ksgC, nv9dAkra, dGe8onxY_b14[nMwKZ]);
  if (BPE3db23ej(nMwKZ))
    return kpcx3(bpv2SUHTispZr, 0, VhzaLt8imxvlX);  /* error */
  else {
    XVlgVVDk(bpv2SUHTispZr, (Uq0uK54ZIvnFK)sW8y4(ksgC));
    return 1;
  }
}


static int a3pR9JYX1Z (RhShDDv88lXpS *bpv2SUHTispZr) {
  static const int dGe8onxY_b14[] = {kgWO, GuUsk, XXsjL50g};
  static const char *const GqPvo1Y8MVmN[] = {"no", "full", "line", VhzaLt8imxvlX};
  dJrDtyJBs *ksgC = IVPUSk(bpv2SUHTispZr);
  int nMwKZ = LxPu4iLcvl(bpv2SUHTispZr, 2, VhzaLt8imxvlX, GqPvo1Y8MVmN);
  Uq0uK54ZIvnFK OGV4k4 = MqxXPAUKxLDy(bpv2SUHTispZr, 3, xz8qmloyaUF);
  int W9vHAVQ;
  squIlocj9N = 0;
  W9vHAVQ = cbXGJH(ksgC, VhzaLt8imxvlX, dGe8onxY_b14[nMwKZ], (ZL3bZQ3Au7i)OGV4k4);
  return kpcx3(bpv2SUHTispZr, W9vHAVQ == 0, VhzaLt8imxvlX);
}



static int bbyEvh (RhShDDv88lXpS *bpv2SUHTispZr) {
  dJrDtyJBs *ksgC = QsND2MLrv(bpv2SUHTispZr, IbTH);
  squIlocj9N = 0;
  return kpcx3(bpv2SUHTispZr, LrYUWj8g5ulG(ksgC) == 0, VhzaLt8imxvlX);
}


static int ST84 (RhShDDv88lXpS *bpv2SUHTispZr) {
  dJrDtyJBs *ksgC = IVPUSk(bpv2SUHTispZr);
  squIlocj9N = 0;
  return kpcx3(bpv2SUHTispZr, LrYUWj8g5ulG(ksgC) == 0, VhzaLt8imxvlX);
}


/*
** functions for 'io' library
*/
static const h_EFiZZA7NF r3ZnYZIHQiYH[] = {
  {"close", lwiy5},
  {"flush", bbyEvh},
  {"input", wdjLuEzO},
  {"lines", NdSKhzSikZ},
  {"open", Bzrho},
  {"output", Qh6GR4l7j},
  {"popen", afitWtQRVD},
  {"read", Eb4Veq},
  {"tmpfile", b_QK1LK},
  {"type", KRTnymY9DKin},
  {"write", e8ByfP},
  {VhzaLt8imxvlX, VhzaLt8imxvlX}
};


/*
** methods for file handles
*/
static const h_EFiZZA7NF e2ppjiidAhO[] = {
  {"read", J4Mu1UO},
  {"write", gMIMImex9OUz7},
  {"lines", igKWEA},
  {"flush", ST84},
  {"seek", HbI8MpJ},
  {"close", xzEYU},
  {"setvbuf", a3pR9JYX1Z},
  {VhzaLt8imxvlX, VhzaLt8imxvlX}
};


/*
** metamethods for file handles
*/
static const h_EFiZZA7NF YV1jy[] = {
  {"__index", VhzaLt8imxvlX},  /* placeholder */
  {"__gc", bvQCtWZ},
  {"__close", bvQCtWZ},
  {"__tostring", JqyVkh},
  {VhzaLt8imxvlX, VhzaLt8imxvlX}
};


static void UUZVr (RhShDDv88lXpS *bpv2SUHTispZr) {
  hcBw(bpv2SUHTispZr, yHDjUj4g);  /* metatable for file handles */
  Gp1X(bpv2SUHTispZr, YV1jy, 0);  /* add metamethods to new metatable */
  gKh_(bpv2SUHTispZr, e2ppjiidAhO);  /* create method table */
  Gp1X(bpv2SUHTispZr, e2ppjiidAhO, 0);  /* add file methods to method table */
  s6yfBZq0xM_u(bpv2SUHTispZr, -2, "__index");  /* metatable.__index = method table */
  zwhcIL(bpv2SUHTispZr, 1);  /* pop metatable */
}


/*
** function to (not) close the standard files stdin, stdout, and stderr
*/
static int v0MNpcHkUnwwi (RhShDDv88lXpS *bpv2SUHTispZr) {
  eWLmIztTJfE *i7mh1 = kdQ8KwkP4Xij(bpv2SUHTispZr);
  i7mh1->BJ8C = &v0MNpcHkUnwwi;  /* keep file opened */
  fpb2fq50B(bpv2SUHTispZr);
  hjhDpBd(bpv2SUHTispZr, "cannot close standard file");
  return 2;
}


static void pSldgvSwzzC (RhShDDv88lXpS *bpv2SUHTispZr, dJrDtyJBs *ksgC, const char *b0z0iJVc,
                           const char *pDmgM) {
  eWLmIztTJfE *i7mh1 = DqmN(bpv2SUHTispZr);
  i7mh1->ksgC = ksgC;
  i7mh1->BJ8C = &v0MNpcHkUnwwi;
  if (b0z0iJVc != VhzaLt8imxvlX) {
    YJpZh2yyMu(bpv2SUHTispZr, -1);
    s6yfBZq0xM_u(bpv2SUHTispZr, kiJLfE3yj, b0z0iJVc);  /* add file to registry */
  }
  s6yfBZq0xM_u(bpv2SUHTispZr, -2, pDmgM);  /* add file to module */
}


Dqrtgf int fVPpvkbL (RhShDDv88lXpS *bpv2SUHTispZr) {
  bwNtOaBRo(bpv2SUHTispZr, r3ZnYZIHQiYH);  /* new module */
  UUZVr(bpv2SUHTispZr);
  /* create (and set) default files */
  pSldgvSwzzC(bpv2SUHTispZr, X3LNJmr, u23QzTcqXmyt, "stdin");
  pSldgvSwzzC(bpv2SUHTispZr, e8wacs1M1MV, IbTH, "stdout");
  pSldgvSwzzC(bpv2SUHTispZr, Y_aygUkc7g, VhzaLt8imxvlX, "stderr");
  return 1;
}

