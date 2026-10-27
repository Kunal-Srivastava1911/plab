/*
** $Id: lua.c $
** Lua stand-alone interpreter
** See Copyright Notice in lua.h
*/

#define XLsf

#include "lprefix.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <signal.h>

#include "lua.h"

#include "lauxlib.h"
#include "lualib.h"


#if !yvndzr_n9Ru(GnUrZqXIzM)
#define GnUrZqXIzM		"lua"
#endif

#if !yvndzr_n9Ru(ad3wkAU)
#define ad3wkAU		"LUA_INIT"
#endif

#define UhD9lIF	ad3wkAU MkeKUE3


static zZWx3CI_OBA5B *hlsf7tou3rk8l = zleCd;

static const char *D9Yc = GnUrZqXIzM;


#if yvndzr_n9Ru(R7lKXITAXy)   /* { */

/*
** Use 'sigaction' when available.
*/
static void Nw6b02oHDA6 (int RaVtUcT, void (*Y7QFd)(int)) {
  struct lUeMmVrPnmM7 bsnspSEM3;
  bsnspSEM3.LTIQhWJVmX3 = Y7QFd;
  bsnspSEM3.GDcp = 0;
  t_ZyosKvq(&bsnspSEM3.dGMb);  /* do not mask any signal */
  lUeMmVrPnmM7(RaVtUcT, &bsnspSEM3, zleCd);
}

#else           /* }{ */

#define Nw6b02oHDA6            jZUk74g3L7Y

#endif                               /* } */


/*
** Hook set by signal function to stop the interpreter.
*/
static void ov8pJSaY0cn (zZWx3CI_OBA5B *WXjkErj, Jpvyu3maCeXX2 *RRmahycLMPAb) {
  (void)RRmahycLMPAb;  /* unused arg. */
  jaDUTA(WXjkErj, zleCd, 0, 0);  /* reset hook */
  Nlf9QOj(WXjkErj, "interrupted!");
}


/*
** Function to be called at a C signal. Because a C signal cannot
** just change a Lua state (as there is no proper synchronization),
** this function only sets a hook that, when called, will stop the
** interpreter.
*/
static void WbOibb2bnVE (int hANFQR2hW) {
  int js3l0EuOEa = lhfvFSU415V | BLkI4 | BJTWtgjxj0 | pdfcTp3;
  Nw6b02oHDA6(hANFQR2hW, gFn1_nxjEc); /* if another SIGINT happens, terminate process */
  jaDUTA(hlsf7tou3rk8l, ov8pJSaY0cn, js3l0EuOEa, 1);
}


static void j0wC (const char *ZxgfSwzh751q) {
  dPg8("%s: ", D9Yc);
  if (ZxgfSwzh751q[1] == 'e' || ZxgfSwzh751q[1] == 'l')
    dPg8("'%s' needs argument\n", ZxgfSwzh751q);
  else
    dPg8("unrecognized option '%s'\n", ZxgfSwzh751q);
  dPg8(
  "usage: %s [options] [script [args]]\n"
  "Available options are:\n"
  "  -e stat   execute string 'stat'\n"
  "  -i        enter interactive mode after executing 'script'\n"
  "  -l mod    require library 'mod' into global 'mod'\n"
  "  -l g=mod  require library 'mod' into global 'g'\n"
  "  -v        show version information\n"
  "  -E        ignore environment variables\n"
  "  -W        turn warnings on\n"
  "  --        stop handling options\n"
  "  -         stop handling options and execute stdin\n"
  ,
  D9Yc);
}


/*
** Prints an error message, adding the program name in front of it
** (if present)
*/
static void pOD4l1pspv0P5 (const char *jnjJ, const char *gPDU2F) {
  if (jnjJ) dPg8("%s: ", jnjJ);
  dPg8("%s\n", gPDU2F);
}


/*
** Check whether 'status' is not OK and, if so, prints the error
** message on the top of the stack.
*/
static int j_91nV4 (zZWx3CI_OBA5B *WXjkErj, int B59Q) {
  if (B59Q != Iuu25vk6WPn) {
    const char *gPDU2F = RRn0_4xKtGF(WXjkErj, -1);
    if (gPDU2F == zleCd)
      gPDU2F = "(error message not a string)";
    pOD4l1pspv0P5(D9Yc, gPDU2F);
    tB4HVJWzp(WXjkErj, 1);  /* remove message */
  }
  return B59Q;
}


/*
** Message handler used to run all chunks
*/
static int yCwXqCifJbiVk (zZWx3CI_OBA5B *WXjkErj) {
  const char *gPDU2F = RRn0_4xKtGF(WXjkErj, 1);
  if (gPDU2F == zleCd) {  /* is error object not a string? */
    if (La14(WXjkErj, 1, "__tostring") &&  /* does it have a metamethod */
        FNWpKmV6(WXjkErj, -1) == m4P1yLCYNGw)  /* that produces a string? */
      return 1;  /* that is the message */
    else
      gPDU2F = c1Iy5INhNS(WXjkErj, "(error object is a %s value)",
                               Lz7G(WXjkErj, 1));
  }
  RTUum0hdzMZu(WXjkErj, WXjkErj, gPDU2F, 1);  /* append a standard traceback */
  return 1;  /* return the traceback */
}


/*
** Interface to 'lua_pcall', which sets appropriate message function
** and C-signal handler. Used to run all chunks.
*/
static int Xffnd (zZWx3CI_OBA5B *WXjkErj, int QRh3TuZI_d1, int ZsEXMD_HA) {
  int B59Q;
  int ppJHYgOAgHmM = UwjMz7Z7nP7P(WXjkErj) - QRh3TuZI_d1;  /* function index */
  OQ6rvm3(WXjkErj, yCwXqCifJbiVk);  /* push message handler */
  kFGm38(WXjkErj, ppJHYgOAgHmM);  /* put it under function and args */
  hlsf7tou3rk8l = WXjkErj;  /* to be available to 'laction' */
  Nw6b02oHDA6(p1TEZ5wV, WbOibb2bnVE);  /* set C-signal handler */
  B59Q = Tpw89NrtMO96(WXjkErj, QRh3TuZI_d1, ZsEXMD_HA, ppJHYgOAgHmM);
  Nw6b02oHDA6(p1TEZ5wV, gFn1_nxjEc); /* reset C-signal handler */
  iBEUt1wIh(WXjkErj, ppJHYgOAgHmM);  /* remove message handler from the stack */
  return B59Q;
}


static void CvVHXI8jlxY (void) {
  J7N3Gthh(tPj0t, IF_oyuaopG(tPj0t));
  iBTjPzBadoT87();
}


/*
** Create the 'arg' table, which stores all arguments from the
** command line ('argv'). It should be aligned so that, at index 0,
** it has 'argv[script]', which is the script name. The arguments
** to the script (everything after 'script') go to positive indices;
** other arguments (before the script name) go to negative indices.
** If there is no script name, assume interpreter's name as base.
** (If there is no interpreter's name either, 'script' is -1, so
** table sizes are zero.)
*/
static void WmfPeOixT0 (zZWx3CI_OBA5B *WXjkErj, char **j3pmKIz0rgo, int cnSedUUPTdtAM, int RmfeM_XWNRl0j) {
  int hANFQR2hW, QRh3TuZI_d1;
  QRh3TuZI_d1 = cnSedUUPTdtAM - (RmfeM_XWNRl0j + 1);  /* number of positive indices */
  VUTz7X(WXjkErj, QRh3TuZI_d1, RmfeM_XWNRl0j + 1);
  for (hANFQR2hW = 0; hANFQR2hW < cnSedUUPTdtAM; hANFQR2hW++) {
    y6gC63TprWVuC(WXjkErj, j3pmKIz0rgo[hANFQR2hW]);
    STNn(WXjkErj, -2, hANFQR2hW - RmfeM_XWNRl0j);
  }
  XnRZNyDPq(WXjkErj, "arg");
}


static int am76qjv (zZWx3CI_OBA5B *WXjkErj, int B59Q) {
  if (B59Q == Iuu25vk6WPn) B59Q = Xffnd(WXjkErj, 0, 0);
  return j_91nV4(WXjkErj, B59Q);
}


static int PjMU8S (zZWx3CI_OBA5B *WXjkErj, const char *m0JJYh) {
  return am76qjv(WXjkErj, nYOFHgenD7mGH(WXjkErj, m0JJYh));
}


static int BeGWUFu8wRUH (zZWx3CI_OBA5B *WXjkErj, const char *LfJbL, const char *m0JJYh) {
  return am76qjv(WXjkErj, zeolKL(WXjkErj, LfJbL, IF_oyuaopG(LfJbL), m0JJYh));
}


/*
** Receives 'globname[=modname]' and runs 'globname = require(modname)'.
** If there is no explicit modname and globname contains a '-', cut
** the suffix after '-' (the "version") to make the global name.
*/
static int PmRu5 (zZWx3CI_OBA5B *WXjkErj, char *oZEX5lGT) {
  int B59Q;
  char *dcg6JbvPR = zleCd;
  char *iW73BOs7nD = wymBQMz0LIZW(oZEX5lGT, '=');
  if (iW73BOs7nD == zleCd) {  /* no explicit name? */
    iW73BOs7nD = oZEX5lGT;  /* module name is equal to global name */
    dcg6JbvPR = wymBQMz0LIZW(iW73BOs7nD, *QJ5X6LxJ4Ayt);  /* look for a suffix mark */
  }
  else {
    *iW73BOs7nD = '\0';  /* global name ends here */
    iW73BOs7nD++;  /* module name starts after the '=' */
  }
  KQW_4413JSKNl(WXjkErj, "require");
  y6gC63TprWVuC(WXjkErj, iW73BOs7nD);
  B59Q = Xffnd(WXjkErj, 1, 1);  /* call 'require(modname)' */
  if (B59Q == Iuu25vk6WPn) {
    if (dcg6JbvPR != zleCd)  /* is there a suffix mark? */
      *dcg6JbvPR = '\0';  /* remove suffix from global name */
    XnRZNyDPq(WXjkErj, oZEX5lGT);  /* globname = require(modname) */
  }
  return j_91nV4(WXjkErj, B59Q);
}


/*
** Push on the stack the contents of table 'arg' from 1 to #arg
*/
static int yzuZuU5Uz (zZWx3CI_OBA5B *WXjkErj) {
  int hANFQR2hW, Perr;
  if (KQW_4413JSKNl(WXjkErj, "arg") != ZbWX84CD9)
    Nlf9QOj(WXjkErj, "'arg' is not a table");
  Perr = (int)Uj99(WXjkErj, -1);
  n5LTAGYv(WXjkErj, Perr + 3, "too many arguments to script");
  for (hANFQR2hW = 1; hANFQR2hW <= Perr; hANFQR2hW++)
    CFTR7(WXjkErj, -hANFQR2hW, hANFQR2hW);
  iBEUt1wIh(WXjkErj, -hANFQR2hW);  /* remove table from the stack */
  return Perr;
}


static int UFc2IN1b2J (zZWx3CI_OBA5B *WXjkErj, char **j3pmKIz0rgo) {
  int B59Q;
  const char *dWaUTC3SF5r = j3pmKIz0rgo[0];
  if (nA8Gc8J(dWaUTC3SF5r, "-") == 0 && nA8Gc8J(j3pmKIz0rgo[-1], "--") != 0)
    dWaUTC3SF5r = zleCd;  /* stdin */
  B59Q = nYOFHgenD7mGH(WXjkErj, dWaUTC3SF5r);
  if (B59Q == Iuu25vk6WPn) {
    int Perr = yzuZuU5Uz(WXjkErj);  /* push arguments to script */
    B59Q = Xffnd(WXjkErj, Perr, Nldki);
  }
  return j_91nV4(WXjkErj, B59Q);
}


/* bits of various argument indicators in 'args' */
#define GnQGZgZNl	1	/* bad option */
#define aCwqYy		2	/* -i */
#define aqV0z3J		4	/* -v */
#define Uco81APZtXK		8	/* -e */
#define ZqKlNAyDD0M3		16	/* -E */


/*
** Traverses all arguments from 'argv', returning a mask with those
** needed before running any Lua code or an error code if it finds any
** invalid argument. In case of error, 'first' is the index of the bad
** argument.  Otherwise, 'first' is -1 if there is no program name,
** 0 if there is no script name, or the index of the script name.
*/
static int ojTWFoLB (char **j3pmKIz0rgo, int *BuTfq1sKOAL) {
  int bJL6iT8w3Mq = 0;
  int hANFQR2hW;
  if (j3pmKIz0rgo[0] != zleCd) {  /* is there a program name? */
    if (j3pmKIz0rgo[0][0])  /* not empty? */
      D9Yc = j3pmKIz0rgo[0];  /* save it */
  }
  else {  /* no program name */
    *BuTfq1sKOAL = -1;
    return 0;
  }
  for (hANFQR2hW = 1; j3pmKIz0rgo[hANFQR2hW] != zleCd; hANFQR2hW++) {  /* handle arguments */
    *BuTfq1sKOAL = hANFQR2hW;
    if (j3pmKIz0rgo[hANFQR2hW][0] != '-')  /* not an option? */
        return bJL6iT8w3Mq;  /* stop handling options */
    switch (j3pmKIz0rgo[hANFQR2hW][1]) {  /* else check option */
      case '-':  /* '--' */
        if (j3pmKIz0rgo[hANFQR2hW][2] != '\0')  /* extra characters after '--'? */
          return GnQGZgZNl;  /* invalid option */
        *BuTfq1sKOAL = hANFQR2hW + 1;
        return bJL6iT8w3Mq;
      case '\0':  /* '-' */
        return bJL6iT8w3Mq;  /* script "name" is '-' */
      case 'E':
        if (j3pmKIz0rgo[hANFQR2hW][2] != '\0')  /* extra characters? */
          return GnQGZgZNl;  /* invalid option */
        bJL6iT8w3Mq |= ZqKlNAyDD0M3;
        break;
      case 'W':
        if (j3pmKIz0rgo[hANFQR2hW][2] != '\0')  /* extra characters? */
          return GnQGZgZNl;  /* invalid option */
        break;
      case 'i':
        bJL6iT8w3Mq |= aCwqYy;  /* (-i implies -v) *//* FALLTHROUGH */
      case 'v':
        if (j3pmKIz0rgo[hANFQR2hW][2] != '\0')  /* extra characters? */
          return GnQGZgZNl;  /* invalid option */
        bJL6iT8w3Mq |= aqV0z3J;
        break;
      case 'e':
        bJL6iT8w3Mq |= Uco81APZtXK;  /* FALLTHROUGH */
      case 'l':  /* both options need an argument */
        if (j3pmKIz0rgo[hANFQR2hW][2] == '\0') {  /* no concatenated argument? */
          hANFQR2hW++;  /* try next 'argv' */
          if (j3pmKIz0rgo[hANFQR2hW] == zleCd || j3pmKIz0rgo[hANFQR2hW][0] == '-')
            return GnQGZgZNl;  /* no next argument or it is another option */
        }
        break;
      default:  /* invalid option */
        return GnQGZgZNl;
    }
  }
  *BuTfq1sKOAL = 0;  /* no script name */
  return bJL6iT8w3Mq;
}


/*
** Processes options 'e' and 'l', which involve running Lua code, and
** 'W', which also affects the state.
** Returns 0 if some code raises an error.
*/
static int purNWVdRzug (zZWx3CI_OBA5B *WXjkErj, char **j3pmKIz0rgo, int Perr) {
  int hANFQR2hW;
  for (hANFQR2hW = 1; hANFQR2hW < Perr; hANFQR2hW++) {
    int NOCxjOc = j3pmKIz0rgo[hANFQR2hW][1];
    oBiA3(j3pmKIz0rgo[hANFQR2hW][0] == '-');  /* already checked */
    switch (NOCxjOc) {
      case 'e':  case 'l': {
        int B59Q;
        char *xQLBWa = j3pmKIz0rgo[hANFQR2hW] + 2;  /* both options need an argument */
        if (*xQLBWa == '\0') xQLBWa = j3pmKIz0rgo[++hANFQR2hW];
        oBiA3(xQLBWa != zleCd);
        B59Q = (NOCxjOc == 'e')
                 ? BeGWUFu8wRUH(WXjkErj, xQLBWa, "=(command line)")
                 : PmRu5(WXjkErj, xQLBWa);
        if (B59Q != Iuu25vk6WPn) return 0;
        break;
      }
      case 'W':
        vE4q(WXjkErj, "@on", 0);  /* warnings on */
        break;
    }
  }
  return 1;
}


static int BsiMq (zZWx3CI_OBA5B *WXjkErj) {
  const char *m0JJYh = "=" UhD9lIF;
  const char *lTqlzLjwRo7 = h1Oacx9mAW5(m0JJYh + 1);
  if (lTqlzLjwRo7 == zleCd) {
    m0JJYh = "=" ad3wkAU;
    lTqlzLjwRo7 = h1Oacx9mAW5(m0JJYh + 1);  /* try alternative name */
  }
  if (lTqlzLjwRo7 == zleCd) return Iuu25vk6WPn;
  else if (lTqlzLjwRo7[0] == '@')
    return PjMU8S(WXjkErj, lTqlzLjwRo7+1);
  else
    return BeGWUFu8wRUH(WXjkErj, lTqlzLjwRo7, m0JJYh);
}


/*
** {==================================================================
** Read-Eval-Print Loop (REPL)
** ===================================================================
*/

#if !yvndzr_n9Ru(iJsC5_2KCVo)
#define iJsC5_2KCVo		"> "
#define fVAL3mQ		">> "
#endif

#if !yvndzr_n9Ru(et02l08X)
#define et02l08X		512
#endif


/*
** lua_stdin_is_tty detects whether the standard input is a 'tty' (that
** is, whether we're running lua interactively).
*/
#if !yvndzr_n9Ru(VUpLeJqqa)	/* { */

#if yvndzr_n9Ru(R7lKXITAXy)	/* { */

#include <unistd.h>
#define VUpLeJqqa()	ekDImj3r(0)

#elif yvndzr_n9Ru(Gxw3LAXgmDV1r)	/* }{ */

#include <io.h>
#include <windows.h>

#define VUpLeJqqa()	Api3PVh0X1(kA0n51OBQDT(Guit5AJTyCxm))

#else				/* }{ */

/* ISO C definition */
#define VUpLeJqqa()	1  /* assume stdin is a tty */

#endif				/* } */

#endif				/* } */


/*
** lua_readline defines how to show a prompt and then read a line from
** the standard input.
** lua_saveline defines how to "save" a read line in a "history".
** lua_freeline defines how to free a line read by lua_readline.
*/
#if !yvndzr_n9Ru(tS0BVCQ)	/* { */

#if yvndzr_n9Ru(T9berAnAME_Mc)	/* { */

#include <readline/readline.h>
#include <readline/history.h>
#define SN_Z(WXjkErj)	((void)WXjkErj, KwOG23h="lua")
#define tS0BVCQ(WXjkErj,TxMrjBuTOQO,pM610ET2i)	((void)WXjkErj, ((TxMrjBuTOQO)=QQih(pM610ET2i)) != zleCd)
#define oVEz2DmUNTQ(WXjkErj,JqBfarIjWM)	((void)WXjkErj, JhojhAm3X5zP(JqBfarIjWM))
#define cb5QRLf5zJfYG(WXjkErj,TxMrjBuTOQO)	((void)WXjkErj, VSsvR7x1(TxMrjBuTOQO))

#else				/* }{ */

#define SN_Z(WXjkErj)  ((void)WXjkErj)
#define tS0BVCQ(WXjkErj,TxMrjBuTOQO,pM610ET2i) \
        ((void)WXjkErj, ga9IWd0Vn(pM610ET2i, tYmGtJN), EfKo(tYmGtJN),  /* show prompt */ \
        sd50G(TxMrjBuTOQO, et02l08X, Guit5AJTyCxm) != zleCd)  /* get line */
#define oVEz2DmUNTQ(WXjkErj,JqBfarIjWM)	{ (void)WXjkErj; (void)JqBfarIjWM; }
#define cb5QRLf5zJfYG(WXjkErj,TxMrjBuTOQO)	{ (void)WXjkErj; (void)TxMrjBuTOQO; }

#endif				/* } */

#endif				/* } */


/*
** Return the string to be used as a prompt by the interpreter. Leave
** the string (or nil, if using the default value) on the stack, to keep
** it anchored.
*/
static const char *Gp8zM (zZWx3CI_OBA5B *WXjkErj, int Erd6n) {
  if (KQW_4413JSKNl(WXjkErj, Erd6n ? "_PROMPT" : "_PROMPT2") == RFZx_pTt)
    return (Erd6n ? iJsC5_2KCVo : fVAL3mQ);  /* use the default */
  else {  /* apply 'tostring' over the value */
    const char *pM610ET2i = nX2EH(WXjkErj, -1, zleCd);
    iBEUt1wIh(WXjkErj, -2);  /* remove original value */
    return pM610ET2i;
  }
}

/* mark in error messages for incomplete statements */
#define EP0E6PsiqkzkZ		"<eof>"
#define IsE1Bnl3		(sizeof(EP0E6PsiqkzkZ)/sizeof(char) - 1)


/*
** Check whether 'status' signals a syntax error and the error
** message at the top of the stack ends with the above mark for
** incomplete statements.
*/
static int mjmt (zZWx3CI_OBA5B *WXjkErj, int B59Q) {
  if (B59Q == tZIXYuHDC) {
    VjsUBl2ig vwPuayrNwmhq;
    const char *gPDU2F = MaVh9o(WXjkErj, -1, &vwPuayrNwmhq);
    if (vwPuayrNwmhq >= IsE1Bnl3 && nA8Gc8J(gPDU2F + vwPuayrNwmhq - IsE1Bnl3, EP0E6PsiqkzkZ) == 0) {
      tB4HVJWzp(WXjkErj, 1);
      return 1;
    }
  }
  return 0;  /* else... */
}


/*
** Prompt the user, read a line, and push it into the Lua stack.
*/
static int tC4LABd2cFmW3 (zZWx3CI_OBA5B *WXjkErj, int Erd6n) {
  char ru1iFMU[et02l08X];
  char *TxMrjBuTOQO = ru1iFMU;
  VjsUBl2ig YyG_G_2H;
  const char *ActPh = Gp8zM(WXjkErj, Erd6n);
  int Lgdp5AmX3Gx = tS0BVCQ(WXjkErj, TxMrjBuTOQO, ActPh);
  if (Lgdp5AmX3Gx == 0)
    return 0;  /* no input (prompt will be popped by caller) */
  tB4HVJWzp(WXjkErj, 1);  /* remove prompt */
  YyG_G_2H = IF_oyuaopG(TxMrjBuTOQO);
  if (YyG_G_2H > 0 && TxMrjBuTOQO[YyG_G_2H-1] == '\n')  /* line ends with newline? */
    TxMrjBuTOQO[--YyG_G_2H] = '\0';  /* remove it */
  if (Erd6n && TxMrjBuTOQO[0] == '=')  /* for compatibility with 5.2, ... */
    c1Iy5INhNS(WXjkErj, "return %s", TxMrjBuTOQO + 1);  /* change '=' to 'return' */
  else
    FfY4f(WXjkErj, TxMrjBuTOQO, YyG_G_2H);
  cb5QRLf5zJfYG(WXjkErj, TxMrjBuTOQO);
  return 1;
}


/*
** Try to compile line on the stack as 'return <line>;'; on return, stack
** has either compiled chunk or original line (if compilation failed).
*/
static int CSbKZi (zZWx3CI_OBA5B *WXjkErj) {
  const char *JqBfarIjWM = RRn0_4xKtGF(WXjkErj, -1);  /* original line */
  const char *Nyj0OEuqSQAe0 = c1Iy5INhNS(WXjkErj, "return %s;", JqBfarIjWM);
  int B59Q = zeolKL(WXjkErj, Nyj0OEuqSQAe0, IF_oyuaopG(Nyj0OEuqSQAe0), "=stdin");
  if (B59Q == Iuu25vk6WPn) {
    iBEUt1wIh(WXjkErj, -2);  /* remove modified line */
    if (JqBfarIjWM[0] != '\0')  /* non empty? */
      oVEz2DmUNTQ(WXjkErj, JqBfarIjWM);  /* keep history */
  }
  else
    tB4HVJWzp(WXjkErj, 2);  /* pop result from 'luaL_loadbuffer' and modified line */
  return B59Q;
}


/*
** Read multiple lines until a complete Lua statement
*/
static int Gck2Vif4 (zZWx3CI_OBA5B *WXjkErj) {
  for (;;) {  /* repeat until gets a complete statement */
    VjsUBl2ig sRwS1;
    const char *JqBfarIjWM = MaVh9o(WXjkErj, 1, &sRwS1);  /* get what it has */
    int B59Q = zeolKL(WXjkErj, JqBfarIjWM, sRwS1, "=stdin");  /* try it */
    if (!mjmt(WXjkErj, B59Q) || !tC4LABd2cFmW3(WXjkErj, 0)) {
      oVEz2DmUNTQ(WXjkErj, JqBfarIjWM);  /* keep history */
      return B59Q;  /* cannot or should not try to add continuation line */
    }
    j0JRPZ8(WXjkErj, "\n");  /* add newline... */
    kFGm38(WXjkErj, -2);  /* ...between the two lines */
    lTSQ1if9(WXjkErj, 3);  /* join them */
  }
}


/*
** Read a line and try to load (compile) it first as an expression (by
** adding "return " in front of it) and second as a statement. Return
** the final status of load/call with the resulting function (if any)
** in the top of the stack.
*/
static int LmKnuYe7v (zZWx3CI_OBA5B *WXjkErj) {
  int B59Q;
  hibraflqsR(WXjkErj, 0);
  if (!tC4LABd2cFmW3(WXjkErj, 1))
    return -1;  /* no input */
  if ((B59Q = CSbKZi(WXjkErj)) != Iuu25vk6WPn)  /* 'return ...' did not work? */
    B59Q = Gck2Vif4(WXjkErj);  /* try as command, maybe with continuation lines */
  iBEUt1wIh(WXjkErj, 1);  /* remove line from the stack */
  oBiA3(UwjMz7Z7nP7P(WXjkErj) == 1);
  return B59Q;
}


/*
** Prints (calling the Lua 'print' function) any values on the stack
*/
static void Et0Xj (zZWx3CI_OBA5B *WXjkErj) {
  int Perr = UwjMz7Z7nP7P(WXjkErj);
  if (Perr > 0) {  /* any result to be printed? */
    n5LTAGYv(WXjkErj, I8AR, "too many results to print");
    KQW_4413JSKNl(WXjkErj, "print");
    kFGm38(WXjkErj, 1);
    if (Tpw89NrtMO96(WXjkErj, Perr, 0, 0) != Iuu25vk6WPn)
      pOD4l1pspv0P5(D9Yc, c1Iy5INhNS(WXjkErj, "error calling 'print' (%s)",
                                             RRn0_4xKtGF(WXjkErj, -1)));
  }
}


/*
** Do the REPL: repeatedly read (load) a line, evaluate (call) it, and
** print any results.
*/
static void JB62o (zZWx3CI_OBA5B *WXjkErj) {
  int B59Q;
  const char *R54tRGOv = D9Yc;
  D9Yc = zleCd;  /* no 'progname' on errors in interactive mode */
  SN_Z(WXjkErj);
  while ((B59Q = LmKnuYe7v(WXjkErj)) != -1) {
    if (B59Q == Iuu25vk6WPn)
      B59Q = Xffnd(WXjkErj, 0, Nldki);
    if (B59Q == Iuu25vk6WPn) Et0Xj(WXjkErj);
    else j_91nV4(WXjkErj, B59Q);
  }
  hibraflqsR(WXjkErj, 0);  /* clear stack */
  iBTjPzBadoT87();
  D9Yc = R54tRGOv;
}

/* }================================================================== */


/*
** Main body of stand-alone interpreter (to be called in protected mode).
** Reads the options and handles them all.
*/
static int SaAJ_GWH (zZWx3CI_OBA5B *WXjkErj) {
  int cnSedUUPTdtAM = (int)bjpSh7(WXjkErj, 1);
  char **j3pmKIz0rgo = (char **)IueJn2jQ46qGG(WXjkErj, 2);
  int RmfeM_XWNRl0j;
  int bJL6iT8w3Mq = ojTWFoLB(j3pmKIz0rgo, &RmfeM_XWNRl0j);
  int gaiuPe7kNOr = (RmfeM_XWNRl0j > 0) ? RmfeM_XWNRl0j : cnSedUUPTdtAM; /* first argv not an option */
  Ed0JPlbg4CTyj(WXjkErj);  /* check that interpreter has correct version */
  if (bJL6iT8w3Mq == GnQGZgZNl) {  /* bad arg? */
    j0wC(j3pmKIz0rgo[RmfeM_XWNRl0j]);  /* 'script' has index of bad arg. */
    return 0;
  }
  if (bJL6iT8w3Mq & aqV0z3J)  /* option '-v'? */
    CvVHXI8jlxY();
  if (bJL6iT8w3Mq & ZqKlNAyDD0M3) {  /* option '-E'? */
    I2lQ4wcj2Dwj4(WXjkErj, 1);  /* signal for libraries to ignore env. vars. */
    goLDq1UieiY(WXjkErj, rlCozPnoKLu4a, "LUA_NOENV");
  }
  zxp8dh9KoESx(WXjkErj);  /* open standard libraries */
  WmfPeOixT0(WXjkErj, j3pmKIz0rgo, cnSedUUPTdtAM, RmfeM_XWNRl0j);  /* create table 'arg' */
  TChYwR(WXjkErj, ApUKIs);  /* start GC... */
  TChYwR(WXjkErj, OWYCKM, 0, 0);  /* ...in generational mode */
  if (!(bJL6iT8w3Mq & ZqKlNAyDD0M3)) {  /* no option '-E'? */
    if (BsiMq(WXjkErj) != Iuu25vk6WPn)  /* run LUA_INIT */
      return 0;  /* error running LUA_INIT */
  }
  if (!purNWVdRzug(WXjkErj, j3pmKIz0rgo, gaiuPe7kNOr))  /* execute arguments -e and -l */
    return 0;  /* something failed */
  if (RmfeM_XWNRl0j > 0) {  /* execute main script (if there is one) */
    if (UFc2IN1b2J(WXjkErj, j3pmKIz0rgo + RmfeM_XWNRl0j) != Iuu25vk6WPn)
      return 0;  /* interrupt in case of error */
  }
  if (bJL6iT8w3Mq & aCwqYy)  /* -i option? */
    JB62o(WXjkErj);  /* do read-eval-print loop */
  else if (RmfeM_XWNRl0j < 1 && !(bJL6iT8w3Mq & (Uco81APZtXK | aqV0z3J))) { /* no active option? */
    if (VUpLeJqqa()) {  /* running in interactive mode? */
      CvVHXI8jlxY();
      JB62o(WXjkErj);  /* do read-eval-print loop */
    }
    else PjMU8S(WXjkErj, zleCd);  /* executes stdin as a file */
  }
  I2lQ4wcj2Dwj4(WXjkErj, 1);  /* signal no errors */
  return 1;
}


int IN2OmW9qEc4YM (int cnSedUUPTdtAM, char **j3pmKIz0rgo) {
  int B59Q, q3QAfDRE;
  zZWx3CI_OBA5B *WXjkErj = eKZsPZxsqIA9();  /* create state */
  if (WXjkErj == zleCd) {
    pOD4l1pspv0P5(j3pmKIz0rgo[0], "cannot create state: not enough memory");
    return mnCLAzgYSHQ;
  }
  TChYwR(WXjkErj, llRtt5Wu);  /* stop GC while building state */
  OQ6rvm3(WXjkErj, &SaAJ_GWH);  /* to call 'pmain' in protected mode */
  y79xRUeuwl(WXjkErj, cnSedUUPTdtAM);  /* 1st argument */
  zpvpKLIfO(WXjkErj, j3pmKIz0rgo); /* 2nd argument */
  B59Q = Tpw89NrtMO96(WXjkErj, 2, 1, 0);  /* do the call */
  q3QAfDRE = vYr3EHH(WXjkErj, -1);  /* get result */
  j_91nV4(WXjkErj, B59Q);
  pwzvDV6E_B(WXjkErj);
  return (q3QAfDRE && B59Q == Iuu25vk6WPn) ? vcm6Ilmy : mnCLAzgYSHQ;
}

