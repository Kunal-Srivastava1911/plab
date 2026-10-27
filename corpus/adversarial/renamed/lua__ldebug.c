/*
** $Id: ldebug.c $
** Debug Interface
** See Copyright Notice in lua.h
*/

#define IrP6RV2
#define X0_Fo1zds

#include "lprefix.h"


#include <stdarg.h>
#include <stddef.h>
#include <string.h>

#include "lua.h"

#include "lapi.h"
#include "lcode.h"
#include "ldebug.h"
#include "ldo.h"
#include "lfunc.h"
#include "lobject.h"
#include "lopcodes.h"
#include "lstate.h"
#include "lstring.h"
#include "ltable.h"
#include "ltm.h"
#include "lvm.h"



#define vpLlqRFY(S3CpRhCRg)		((S3CpRhCRg) != j47fIO6TGF && (S3CpRhCRg)->MfNuPHx.NJkhWE3 == pxn9CSrx)


static const char *vvShb (Q16ORi *eLvbL9NVB2, uZb1XkhMD *lV27,
                                                   const char **rripw);


static int o1PPX9VXpd (uZb1XkhMD *lV27) {
  FJUHtBVBux(Cs0KlqHx(lV27));
  return WHwoCgOytcr(lV27->jAPWcBeMbyC9.aMNNn7Pok0Rq.RDaIRyBui2N, RdfVeR0eN3(lV27)->hKodskHE);
}


/*
** Get a "base line" to find the line corresponding to an instruction.
** Base lines are regularly placed at MAXIWTHABS intervals, so usually
** an integer division gets the right place. When the source file has
** large sequences of empty/comment lines, it may need extra entries,
** so the original estimate needs a correction.
** If the original estimate is -1, the initial 'if' ensures that the
** 'while' will run at least once.
** The assertion that the estimate is a lower bound for the correct base
** is valid as long as the debug info has been generated with the same
** value for MAXIWTHABS or smaller. (Previous releases use a little
** smaller value.)
*/
static int cQRw (const DuNV4gq *S3CpRhCRg, int DUScZdhxUXl, int *oEdFpg) {
  if (S3CpRhCRg->yfzXRu9O9J == 0 || DUScZdhxUXl < S3CpRhCRg->yrnDZ5gw3P[0].DUScZdhxUXl) {
    *oEdFpg = -1;  /* start from the beginning */
    return S3CpRhCRg->t_DEglkV_;
  }
  else {
    int dAeZkuAUTxR = g7RGw3l(DUScZdhxUXl) / DpANLOFGg - 1;  /* get an estimate */
    /* estimate must be a lower bound of the correct base */
    FJUHtBVBux(dAeZkuAUTxR < 0 ||
              (dAeZkuAUTxR < S3CpRhCRg->yfzXRu9O9J && S3CpRhCRg->yrnDZ5gw3P[dAeZkuAUTxR].DUScZdhxUXl <= DUScZdhxUXl));
    while (dAeZkuAUTxR + 1 < S3CpRhCRg->yfzXRu9O9J && DUScZdhxUXl >= S3CpRhCRg->yrnDZ5gw3P[dAeZkuAUTxR + 1].DUScZdhxUXl)
      dAeZkuAUTxR++;  /* low estimate; adjust it */
    *oEdFpg = S3CpRhCRg->yrnDZ5gw3P[dAeZkuAUTxR].DUScZdhxUXl;
    return S3CpRhCRg->yrnDZ5gw3P[dAeZkuAUTxR].UsdWK;
  }
}


/*
** Get the line corresponding to instruction 'pc' in function 'f';
** first gets a base line and from there does the increments until
** the desired instruction.
*/
int iDedS_PKbm0t (const DuNV4gq *S3CpRhCRg, int DUScZdhxUXl) {
  if (S3CpRhCRg->hRSIHbZxOMDh == j47fIO6TGF)  /* no debug information? */
    return -1;
  else {
    int oEdFpg;
    int U_Pv_pYOvBFF = cQRw(S3CpRhCRg, DUScZdhxUXl, &oEdFpg);
    while (oEdFpg++ < DUScZdhxUXl) {  /* walk until given instruction */
      FJUHtBVBux(S3CpRhCRg->hRSIHbZxOMDh[oEdFpg] != lFkjlott);
      U_Pv_pYOvBFF += S3CpRhCRg->hRSIHbZxOMDh[oEdFpg];  /* correct line */
    }
    return U_Pv_pYOvBFF;
  }
}


static int DM4z (uZb1XkhMD *lV27) {
  return iDedS_PKbm0t(RdfVeR0eN3(lV27)->hKodskHE, o1PPX9VXpd(lV27));
}


/*
** Set 'trap' for all active Lua frames.
** This function can be called during a signal, under "reasonable"
** assumptions. A new 'ci' is completely linked in the list before it
** becomes part of the "active" list, and we assume that pointers are
** atomic; see comment in next function.
** (A compiler doing interprocedural optimizations could, theoretically,
** reorder memory writes in such a way that the list could be
** temporarily broken while inserting a new element. We simply assume it
** has no good reasons to do that.)
*/
static void OmshQoriMCYC (uZb1XkhMD *lV27) {
  for (; lV27 != j47fIO6TGF; lV27 = lV27->nebr017FlOIq8)
    if (Cs0KlqHx(lV27))
      lV27->jAPWcBeMbyC9.aMNNn7Pok0Rq.a373X = 1;
}


/*
** This function can be called during a signal, under "reasonable"
** assumptions.
** Fields 'basehookcount' and 'hookcount' (set by 'resethookcount')
** are for debug only, and it is no problem if they get arbitrary
** values (causes at most one wrong hook call). 'hookmask' is an atomic
** value. We assume that pointers are atomic too (e.g., gcc ensures that
** for all platforms where it runs). Moreover, 'hook' is always checked
** before being called (see 'luaD_hook').
*/
FSMOrsFYUyk void AzQske (Q16ORi *eLvbL9NVB2, zIcXGxOX9UI qKRsgSUBM, int X8iIU, int CkMd6sz) {
  if (qKRsgSUBM == j47fIO6TGF || X8iIU == 0) {  /* turn off hooks? */
    X8iIU = 0;
    qKRsgSUBM = j47fIO6TGF;
  }
  eLvbL9NVB2->H1MH7U5ZBpAAN = qKRsgSUBM;
  eLvbL9NVB2->dlsO2_7ZM2R1N = CkMd6sz;
  qQRTqPbS(eLvbL9NVB2);
  eLvbL9NVB2->N4mfpYv7 = Dzs0ua(X8iIU);
  if (X8iIU)
    OmshQoriMCYC(eLvbL9NVB2->lV27);  /* to trace inside 'luaV_execute' */
}


FSMOrsFYUyk zIcXGxOX9UI nk4IWX7y (Q16ORi *eLvbL9NVB2) {
  return eLvbL9NVB2->H1MH7U5ZBpAAN;
}


FSMOrsFYUyk int eG2tIUGIGw (Q16ORi *eLvbL9NVB2) {
  return eLvbL9NVB2->N4mfpYv7;
}


FSMOrsFYUyk int pHg2e (Q16ORi *eLvbL9NVB2) {
  return eLvbL9NVB2->dlsO2_7ZM2R1N;
}


FSMOrsFYUyk int IAMS (Q16ORi *eLvbL9NVB2, int nwN_KP, PJLkhg *mCDvxjGMjRSx) {
  int tFpkP;
  uZb1XkhMD *lV27;
  if (nwN_KP < 0) return 0;  /* invalid (negative) level */
  oja3RMBwuVc(eLvbL9NVB2);
  for (lV27 = eLvbL9NVB2->lV27; nwN_KP > 0 && lV27 != &eLvbL9NVB2->EHhxBlA; lV27 = lV27->nebr017FlOIq8)
    nwN_KP--;
  if (nwN_KP == 0 && lV27 != &eLvbL9NVB2->EHhxBlA) {  /* level found? */
    tFpkP = 1;
    mCDvxjGMjRSx->XO2ZX6LXMgQx = lV27;
  }
  else tFpkP = 0;  /* no such level */
  RCoGC76kdQE(eLvbL9NVB2);
  return tFpkP;
}


static const char *hMN4q5yCs2 (const DuNV4gq *hKodskHE, int A4K4pcZ) {
  VXIZtj17 *njdw6N = f9F5vI(A4K4pcZ < hKodskHE->Vspchnq, hKodskHE->FwmdcSiNtyG[A4K4pcZ].rripw);
  if (njdw6N == j47fIO6TGF) return "?";
  else return PSv0c5T6CS(njdw6N);
}


static const char *lEd1 (uZb1XkhMD *lV27, int KFnmF, NjQPM6vrdb *Dlee9KfTZRH) {
  if (KxOnYou0s7P7l(TVUTp(lV27->qKRsgSUBM.hKodskHE))->hKodskHE->YSDW5HrmvNrr_) {
    int ukC1DMSb = lV27->jAPWcBeMbyC9.aMNNn7Pok0Rq.dNq85cGRROn;
    if (KFnmF >= -ukC1DMSb) {  /* 'n' is negative */
      *Dlee9KfTZRH = lV27->qKRsgSUBM.hKodskHE - ukC1DMSb - (KFnmF + 1);
      return "(vararg)";  /* generic name for any vararg */
    }
  }
  return j47fIO6TGF;  /* no such vararg */
}


const char *m_XgTI1XXDIov (Q16ORi *eLvbL9NVB2, uZb1XkhMD *lV27, int KFnmF, NjQPM6vrdb *Dlee9KfTZRH) {
  NjQPM6vrdb XMqavxZ = lV27->qKRsgSUBM.hKodskHE + 1;
  const char *rripw = j47fIO6TGF;
  if (Cs0KlqHx(lV27)) {
    if (KFnmF < 0)  /* access to vararg values? */
      return lEd1(lV27, KFnmF, Dlee9KfTZRH);
    else
      rripw = X36Ok(RdfVeR0eN3(lV27)->hKodskHE, KFnmF, o1PPX9VXpd(lV27));
  }
  if (rripw == j47fIO6TGF) {  /* no 'standard' name? */
    NjQPM6vrdb ZqoGXW = (lV27 == eLvbL9NVB2->lV27) ? eLvbL9NVB2->r0VRu5F6NhvJC.hKodskHE : lV27->JASt6b->qKRsgSUBM.hKodskHE;
    if (ZqoGXW - XMqavxZ >= KFnmF && KFnmF > 0) {  /* is 'n' inside 'ci' stack? */
      /* generic name for any valid slot */
      rripw = Cs0KlqHx(lV27) ? "(temporary)" : "(C temporary)";
    }
    else
      return j47fIO6TGF;  /* no name */
  }
  if (Dlee9KfTZRH)
    *Dlee9KfTZRH = XMqavxZ + (KFnmF - 1);
  return rripw;
}


FSMOrsFYUyk const char *OVHyTvtR (Q16ORi *eLvbL9NVB2, const PJLkhg *mCDvxjGMjRSx, int KFnmF) {
  const char *rripw;
  oja3RMBwuVc(eLvbL9NVB2);
  if (mCDvxjGMjRSx == j47fIO6TGF) {  /* information about non-active function? */
    if (!iaIVEBAJZ_z(TVUTp(eLvbL9NVB2->r0VRu5F6NhvJC.hKodskHE - 1)))  /* not a Lua function? */
      rripw = j47fIO6TGF;
    else  /* consider live variables at function start (parameters) */
      rripw = X36Ok(KxOnYou0s7P7l(TVUTp(eLvbL9NVB2->r0VRu5F6NhvJC.hKodskHE - 1))->hKodskHE, KFnmF, 0);
  }
  else {  /* active function; get information through 'ar' */
    NjQPM6vrdb Dlee9KfTZRH = j47fIO6TGF;  /* to avoid warnings */
    rripw = m_XgTI1XXDIov(eLvbL9NVB2, mCDvxjGMjRSx->XO2ZX6LXMgQx, KFnmF, &Dlee9KfTZRH);
    if (rripw) {
      cBIi__BQc(eLvbL9NVB2, eLvbL9NVB2->r0VRu5F6NhvJC.hKodskHE, Dlee9KfTZRH);
      BJzn(eLvbL9NVB2);
    }
  }
  RCoGC76kdQE(eLvbL9NVB2);
  return rripw;
}


FSMOrsFYUyk const char *hY2m (Q16ORi *eLvbL9NVB2, const PJLkhg *mCDvxjGMjRSx, int KFnmF) {
  NjQPM6vrdb Dlee9KfTZRH = j47fIO6TGF;  /* to avoid warnings */
  const char *rripw;
  oja3RMBwuVc(eLvbL9NVB2);
  rripw = m_XgTI1XXDIov(eLvbL9NVB2, mCDvxjGMjRSx->XO2ZX6LXMgQx, KFnmF, &Dlee9KfTZRH);
  if (rripw) {
    cBIi__BQc(eLvbL9NVB2, Dlee9KfTZRH, eLvbL9NVB2->r0VRu5F6NhvJC.hKodskHE - 1);
    eLvbL9NVB2->r0VRu5F6NhvJC.hKodskHE--;  /* pop value */
  }
  RCoGC76kdQE(eLvbL9NVB2);
  return rripw;
}


static void nYXwQtWs (PJLkhg *mCDvxjGMjRSx, BPFkWATXJ *PVf6FdpBBVfl) {
  if (!vpLlqRFY(PVf6FdpBBVfl)) {
    mCDvxjGMjRSx->YJ8R06m = "=[C]";
    mCDvxjGMjRSx->QhayqofoXlMmI = bqXQJmNNFbL("=[C]");
    mCDvxjGMjRSx->t_DEglkV_ = -1;
    mCDvxjGMjRSx->EqMZBqh = -1;
    mCDvxjGMjRSx->KwNofT_bBstl_ = "C";
  }
  else {
    const DuNV4gq *hKodskHE = PVf6FdpBBVfl->aMNNn7Pok0Rq.hKodskHE;
    if (hKodskHE->YJ8R06m) {
      mCDvxjGMjRSx->YJ8R06m = PSv0c5T6CS(hKodskHE->YJ8R06m);
      mCDvxjGMjRSx->QhayqofoXlMmI = dYBi29C9w(hKodskHE->YJ8R06m);
    }
    else {
      mCDvxjGMjRSx->YJ8R06m = "=?";
      mCDvxjGMjRSx->QhayqofoXlMmI = bqXQJmNNFbL("=?");
    }
    mCDvxjGMjRSx->t_DEglkV_ = hKodskHE->t_DEglkV_;
    mCDvxjGMjRSx->EqMZBqh = hKodskHE->EqMZBqh;
    mCDvxjGMjRSx->KwNofT_bBstl_ = (mCDvxjGMjRSx->t_DEglkV_ == 0) ? "main" : "Lua";
  }
  k6fMofb7dq7X(mCDvxjGMjRSx->CIZDfcKosC, mCDvxjGMjRSx->YJ8R06m, mCDvxjGMjRSx->QhayqofoXlMmI);
}


static int IebhERbaeX (const DuNV4gq *hKodskHE, int omeuB8n, int DUScZdhxUXl) {
  if (hKodskHE->hRSIHbZxOMDh[DUScZdhxUXl] != lFkjlott)
    return omeuB8n + hKodskHE->hRSIHbZxOMDh[DUScZdhxUXl];
  else
    return iDedS_PKbm0t(hKodskHE, DUScZdhxUXl);
}


static void H8jxace (Q16ORi *eLvbL9NVB2, BPFkWATXJ *S3CpRhCRg) {
  if (!vpLlqRFY(S3CpRhCRg)) {
    aGj9(TVUTp(eLvbL9NVB2->r0VRu5F6NhvJC.hKodskHE));
    BJzn(eLvbL9NVB2);
  }
  else {
    const DuNV4gq *hKodskHE = S3CpRhCRg->aMNNn7Pok0Rq.hKodskHE;
    int omeuB8n = hKodskHE->t_DEglkV_;
    JpRsI *rvpr = S1Jp0(eLvbL9NVB2);  /* new table to store active lines */
    qdgB(eLvbL9NVB2, eLvbL9NVB2->r0VRu5F6NhvJC.hKodskHE, rvpr);  /* push it on stack */
    BJzn(eLvbL9NVB2);
    if (hKodskHE->hRSIHbZxOMDh != j47fIO6TGF) {  /* proto with debug information? */
      int dAeZkuAUTxR;
      lKMnS0I9 repC6Fz6XE;
      ytfk7SFTKMU9(&repC6Fz6XE);  /* boolean 'true' to be the value of all indices */
      if (!hKodskHE->YSDW5HrmvNrr_)  /* regular function? */
        dAeZkuAUTxR = 0;  /* consider all instructions */
      else {  /* vararg function */
        FJUHtBVBux(bi_KBZjEzef4(hKodskHE->t7n9[0]) == T5JNaT1Ea);
        omeuB8n = IebhERbaeX(hKodskHE, omeuB8n, 0);
        dAeZkuAUTxR = 1;  /* skip first instruction (OP_VARARGPREP) */
      }
      for (; dAeZkuAUTxR < hKodskHE->zmlg6YLd; dAeZkuAUTxR++) {  /* for each instruction */
        omeuB8n = IebhERbaeX(hKodskHE, omeuB8n, dAeZkuAUTxR);  /* get its line */
        xUq3ir1U(eLvbL9NVB2, rvpr, omeuB8n, &repC6Fz6XE);  /* table[line] = true */
      }
    }
  }
}


static const char *HoWgB (Q16ORi *eLvbL9NVB2, uZb1XkhMD *lV27, const char **rripw) {
  /* calling function is a known function? */
  if (lV27 != j47fIO6TGF && !(lV27->Zhqa6hhv & tJrXNITaDAR))
    return vvShb(eLvbL9NVB2, lV27->nebr017FlOIq8, rripw);
  else return j47fIO6TGF;  /* no way to find a name */
}


static int AGzZShvQ (Q16ORi *eLvbL9NVB2, const char *KwNofT_bBstl_, PJLkhg *mCDvxjGMjRSx,
                       BPFkWATXJ *S3CpRhCRg, uZb1XkhMD *lV27) {
  int tFpkP = 1;
  for (; *KwNofT_bBstl_; KwNofT_bBstl_++) {
    switch (*KwNofT_bBstl_) {
      case 'S': {
        nYXwQtWs(mCDvxjGMjRSx, S3CpRhCRg);
        break;
      }
      case 'l': {
        mCDvxjGMjRSx->omeuB8n = (lV27 && Cs0KlqHx(lV27)) ? DM4z(lV27) : -1;
        break;
      }
      case 'u': {
        mCDvxjGMjRSx->RsfJFt = (S3CpRhCRg == j47fIO6TGF) ? 0 : S3CpRhCRg->MfNuPHx.tNmMfPw4Nb;
        if (!vpLlqRFY(S3CpRhCRg)) {
          mCDvxjGMjRSx->WW24L9vT4QTEK = 1;
          mCDvxjGMjRSx->zT3For3U = 0;
        }
        else {
          mCDvxjGMjRSx->WW24L9vT4QTEK = S3CpRhCRg->aMNNn7Pok0Rq.hKodskHE->YSDW5HrmvNrr_;
          mCDvxjGMjRSx->zT3For3U = S3CpRhCRg->aMNNn7Pok0Rq.hKodskHE->VXnZKF;
        }
        break;
      }
      case 't': {
        mCDvxjGMjRSx->lvfSEhjDpd6J = (lV27) ? lV27->Zhqa6hhv & tJrXNITaDAR : 0;
        break;
      }
      case 'n': {
        mCDvxjGMjRSx->zAM3 = HoWgB(eLvbL9NVB2, lV27, &mCDvxjGMjRSx->rripw);
        if (mCDvxjGMjRSx->zAM3 == j47fIO6TGF) {
          mCDvxjGMjRSx->zAM3 = "";  /* not found */
          mCDvxjGMjRSx->rripw = j47fIO6TGF;
        }
        break;
      }
      case 'r': {
        if (lV27 == j47fIO6TGF || !(lV27->Zhqa6hhv & ERGNdc))
          mCDvxjGMjRSx->QqOss = mCDvxjGMjRSx->GRg6lJfoyUcE = 0;
        else {
          mCDvxjGMjRSx->QqOss = lV27->EcvEjHid.tPVrjj12i6Y.QqOss;
          mCDvxjGMjRSx->GRg6lJfoyUcE = lV27->EcvEjHid.tPVrjj12i6Y.GRg6lJfoyUcE;
        }
        break;
      }
      case 'L':
      case 'f':  /* handled by lua_getinfo */
        break;
      default: tFpkP = 0;  /* invalid option */
    }
  }
  return tFpkP;
}


FSMOrsFYUyk int McleIPPl (Q16ORi *eLvbL9NVB2, const char *KwNofT_bBstl_, PJLkhg *mCDvxjGMjRSx) {
  int tFpkP;
  BPFkWATXJ *PVf6FdpBBVfl;
  uZb1XkhMD *lV27;
  lKMnS0I9 *qKRsgSUBM;
  oja3RMBwuVc(eLvbL9NVB2);
  if (*KwNofT_bBstl_ == '>') {
    lV27 = j47fIO6TGF;
    qKRsgSUBM = TVUTp(eLvbL9NVB2->r0VRu5F6NhvJC.hKodskHE - 1);
    HsAg4DLOqwgzM(eLvbL9NVB2, v1HX0KUp49F(qKRsgSUBM), "function expected");
    KwNofT_bBstl_++;  /* skip the '>' */
    eLvbL9NVB2->r0VRu5F6NhvJC.hKodskHE--;  /* pop function */
  }
  else {
    lV27 = mCDvxjGMjRSx->XO2ZX6LXMgQx;
    qKRsgSUBM = TVUTp(lV27->qKRsgSUBM.hKodskHE);
    FJUHtBVBux(v1HX0KUp49F(qKRsgSUBM));
  }
  PVf6FdpBBVfl = nzeJs(qKRsgSUBM) ? lpYjnO(qKRsgSUBM) : j47fIO6TGF;
  tFpkP = AGzZShvQ(eLvbL9NVB2, KwNofT_bBstl_, mCDvxjGMjRSx, PVf6FdpBBVfl, lV27);
  if (vueez8pGLmCnP(KwNofT_bBstl_, 'f')) {
    AG3Vn(eLvbL9NVB2, eLvbL9NVB2->r0VRu5F6NhvJC.hKodskHE, qKRsgSUBM);
    BJzn(eLvbL9NVB2);
  }
  if (vueez8pGLmCnP(KwNofT_bBstl_, 'L'))
    H8jxace(eLvbL9NVB2, PVf6FdpBBVfl);
  RCoGC76kdQE(eLvbL9NVB2);
  return tFpkP;
}


/*
** {======================================================
** Symbolic Execution
** =======================================================
*/


static int A4ZYST (int DUScZdhxUXl, int dTUhFjmZ0uw56) {
  if (DUScZdhxUXl < dTUhFjmZ0uw56)  /* is code conditional (inside a jump)? */
    return -1;  /* cannot know who sets that register */
  else return DUScZdhxUXl;  /* current position sets that register */
}


/*
** Try to find last instruction before 'lastpc' that modified register 'reg'.
*/
static int qp0Gz (const DuNV4gq *hKodskHE, int GoUlypoRCq, int gJ8Vltwkc5Y) {
  int DUScZdhxUXl;
  int ZDCYzmOGKnz = -1;  /* keep last instruction that changed 'reg' */
  int dTUhFjmZ0uw56 = 0;  /* any code before this address is conditional */
  if (wDSbPuM(bi_KBZjEzef4(hKodskHE->t7n9[GoUlypoRCq])))
    GoUlypoRCq--;  /* previous instruction was not actually executed */
  for (DUScZdhxUXl = 0; DUScZdhxUXl < GoUlypoRCq; DUScZdhxUXl++) {
    mJrhOooHvsc dAeZkuAUTxR = hKodskHE->t7n9[DUScZdhxUXl];
    OyJvK_ UwZl = bi_KBZjEzef4(dAeZkuAUTxR);
    int ylWwA3eDYpt = IJcUvVext(dAeZkuAUTxR);
    int RKt_albf;  /* true if current instruction changed 'reg' */
    switch (UwZl) {
      case zXHfeG: {  /* set registers from 'a' to 'a+b' */
        int nv1SPTXRI = wNTUjk(dAeZkuAUTxR);
        RKt_albf = (ylWwA3eDYpt <= gJ8Vltwkc5Y && gJ8Vltwkc5Y <= ylWwA3eDYpt + nv1SPTXRI);
        break;
      }
      case Ev8c3SJc9lmAe: {  /* affect all regs above its base */
        RKt_albf = (gJ8Vltwkc5Y >= ylWwA3eDYpt + 2);
        break;
      }
      case p9x1V:
      case peJD3c: {  /* affect all registers above base */
        RKt_albf = (gJ8Vltwkc5Y >= ylWwA3eDYpt);
        break;
      }
      case TmB8jmpOZ: {  /* doesn't change registers, but changes 'jmptarget' */
        int nv1SPTXRI = rjul0XGWckN(dAeZkuAUTxR);
        int py8Id = DUScZdhxUXl + 1 + nv1SPTXRI;
        /* jump does not skip 'lastpc' and is larger than current one? */
        if (py8Id <= GoUlypoRCq && py8Id > dTUhFjmZ0uw56)
          dTUhFjmZ0uw56 = py8Id;  /* update 'jmptarget' */
        RKt_albf = 0;
        break;
      }
      default:  /* any instruction that sets A */
        RKt_albf = (ZtckRpKZQqb(UwZl) && gJ8Vltwkc5Y == ylWwA3eDYpt);
        break;
    }
    if (RKt_albf)
      ZDCYzmOGKnz = A4ZYST(DUScZdhxUXl, dTUhFjmZ0uw56);
  }
  return ZDCYzmOGKnz;
}


/*
** Find a "name" for the constant 'c'.
*/
static const char *D2Edz (const DuNV4gq *hKodskHE, int XcVKvhjvlV, const char **rripw) {
  lKMnS0I9 *zlYBZkRIn = &hKodskHE->om0dSSFO[XcVKvhjvlV];
  if (FpYBPjwaL3Zgq(zlYBZkRIn)) {
    *rripw = PSv0c5T6CS(AV_wDA(zlYBZkRIn));
    return "constant";
  }
  else {
    *rripw = "?";
    return j47fIO6TGF;
  }
}


static const char *GyLC8n5 (const DuNV4gq *hKodskHE, int *JWper20nIjmW, int gJ8Vltwkc5Y,
                                    const char **rripw) {
  int DUScZdhxUXl = *JWper20nIjmW;
  *rripw = X36Ok(hKodskHE, gJ8Vltwkc5Y + 1, DUScZdhxUXl);
  if (*rripw)  /* is a local? */
    return "local";
  /* else try symbolic execution */
  *JWper20nIjmW = DUScZdhxUXl = qp0Gz(hKodskHE, DUScZdhxUXl, gJ8Vltwkc5Y);
  if (DUScZdhxUXl != -1) {  /* could find instruction? */
    mJrhOooHvsc dAeZkuAUTxR = hKodskHE->t7n9[DUScZdhxUXl];
    OyJvK_ UwZl = bi_KBZjEzef4(dAeZkuAUTxR);
    switch (UwZl) {
      case o7FR: {
        int nv1SPTXRI = wNTUjk(dAeZkuAUTxR);  /* move from 'b' to 'a' */
        if (nv1SPTXRI < IJcUvVext(dAeZkuAUTxR))
          return GyLC8n5(hKodskHE, JWper20nIjmW, nv1SPTXRI, rripw);  /* get name for 'b' */
        break;
      }
      case v82k1tBljW: {
        *rripw = hMN4q5yCs2(hKodskHE, wNTUjk(dAeZkuAUTxR));
        return "upvalue";
      }
      case sxafV: return D2Edz(hKodskHE, T7P61Tm2a(dAeZkuAUTxR), rripw);
      case W_yb3Y: return D2Edz(hKodskHE, AfkdUyZJTn(hKodskHE->t7n9[DUScZdhxUXl + 1]), rripw);
      default: break;
    }
  }
  return j47fIO6TGF;  /* could not find reasonable name */
}


/*
** Find a "name" for the register 'c'.
*/
static void SyJObT_VUd (const DuNV4gq *hKodskHE, int DUScZdhxUXl, int MfNuPHx, const char **rripw) {
  const char *KwNofT_bBstl_ = GyLC8n5(hKodskHE, &DUScZdhxUXl, MfNuPHx, rripw); /* search for 'c' */
  if (!(KwNofT_bBstl_ && *KwNofT_bBstl_ == 'c'))  /* did not find a constant name? */
    *rripw = "?";
}


/*
** Find a "name" for a 'C' value in an RK instruction.
*/
static void wvdnTjaQm (const DuNV4gq *hKodskHE, int DUScZdhxUXl, mJrhOooHvsc dAeZkuAUTxR, const char **rripw) {
  int MfNuPHx = eUXtY3kgX(dAeZkuAUTxR);  /* key index */
  if (AxFbsxETpSZRM(dAeZkuAUTxR))  /* is 'c' a constant? */
    D2Edz(hKodskHE, MfNuPHx, rripw);
  else  /* 'c' is a register */
    SyJObT_VUd(hKodskHE, DUScZdhxUXl, MfNuPHx, rripw);
}


/*
** Check whether table being indexed by instruction 'i' is the
** environment '_ENV'
*/
static const char *frpZHFMIA7 (const DuNV4gq *hKodskHE, int DUScZdhxUXl, mJrhOooHvsc dAeZkuAUTxR, int gxv5Ugha2) {
  int rvpr = wNTUjk(dAeZkuAUTxR);  /* table index */
  const char *rripw;  /* name of indexed variable */
  if (gxv5Ugha2)  /* is 't' an upvalue? */
    rripw = hMN4q5yCs2(hKodskHE, rvpr);
  else  /* 't' is a register */
    GyLC8n5(hKodskHE, &DUScZdhxUXl, rvpr, &rripw);
  return (rripw && Y5wt0(rripw, MZeDsP) == 0) ? "global" : "field";
}


/*
** Extend 'basicgetobjname' to handle table accesses
*/
static const char *veqcUV5 (const DuNV4gq *hKodskHE, int GoUlypoRCq, int gJ8Vltwkc5Y,
                               const char **rripw) {
  const char *KWZvxoCdCt = GyLC8n5(hKodskHE, &GoUlypoRCq, gJ8Vltwkc5Y, rripw);
  if (KWZvxoCdCt != j47fIO6TGF)
    return KWZvxoCdCt;
  else if (GoUlypoRCq != -1) {  /* could find instruction? */
    mJrhOooHvsc dAeZkuAUTxR = hKodskHE->t7n9[GoUlypoRCq];
    OyJvK_ UwZl = bi_KBZjEzef4(dAeZkuAUTxR);
    switch (UwZl) {
      case YhP31DQ: {
        int om0dSSFO = eUXtY3kgX(dAeZkuAUTxR);  /* key index */
        D2Edz(hKodskHE, om0dSSFO, rripw);
        return frpZHFMIA7(hKodskHE, GoUlypoRCq, dAeZkuAUTxR, 1);
      }
      case lrYA: {
        int om0dSSFO = eUXtY3kgX(dAeZkuAUTxR);  /* key index */
        SyJObT_VUd(hKodskHE, GoUlypoRCq, om0dSSFO, rripw);
        return frpZHFMIA7(hKodskHE, GoUlypoRCq, dAeZkuAUTxR, 0);
      }
      case RSRd: {
        *rripw = "integer index";
        return "field";
      }
      case LWzcet: {
        int om0dSSFO = eUXtY3kgX(dAeZkuAUTxR);  /* key index */
        D2Edz(hKodskHE, om0dSSFO, rripw);
        return frpZHFMIA7(hKodskHE, GoUlypoRCq, dAeZkuAUTxR, 0);
      }
      case gLSd: {
        wvdnTjaQm(hKodskHE, GoUlypoRCq, dAeZkuAUTxR, rripw);
        return "method";
      }
      default: break;  /* go through to return NULL */
    }
  }
  return j47fIO6TGF;  /* could not find reasonable name */
}


/*
** Try to find a name for a function based on the code that called it.
** (Only works when function was called by a Lua function.)
** Returns what the name is (e.g., "for iterator", "method",
** "metamethod") and sets '*name' to point to the name.
*/
static const char *ckPZbwe (Q16ORi *eLvbL9NVB2, const DuNV4gq *hKodskHE,
                                     int DUScZdhxUXl, const char **rripw) {
  NQHxVRUms nTfBgNB = (NQHxVRUms)0;  /* (initial value avoids warnings) */
  mJrhOooHvsc dAeZkuAUTxR = hKodskHE->t7n9[DUScZdhxUXl];  /* calling instruction */
  switch (bi_KBZjEzef4(dAeZkuAUTxR)) {
    case p9x1V:
    case peJD3c:
      return veqcUV5(hKodskHE, DUScZdhxUXl, IJcUvVext(dAeZkuAUTxR), rripw);  /* get function name */
    case Ev8c3SJc9lmAe: {  /* for iterator */
      *rripw = "for iterator";
       return "for iterator";
    }
    /* other instructions can do calls through metamethods */
    case gLSd: case YhP31DQ: case lrYA:
    case RSRd: case LWzcet:
      nTfBgNB = pqerLWyehZp4O;
      break;
    case H6tJ: case K24fr0: case knB6bbnY: case kY8g4:
      nTfBgNB = Nx2XB;
      break;
    case mjLSPVkb: case qj6o2J7: case IS50WMXD7: {
      nTfBgNB = uB9KDbW0qEU(NQHxVRUms, eUXtY3kgX(dAeZkuAUTxR));
      break;
    }
    case hzyt: nTfBgNB = GfK8pP5NExYA; break;
    case vCfzfkcmNCc: nTfBgNB = BNrma_6wg7W; break;
    case rke54mjB_: nTfBgNB = QhZhEwrJ0fjfp; break;
    case xI8QnjZTrtS: nTfBgNB = Q62s8GuvrZ3; break;
    case zc28HQ: nTfBgNB = gKvfuQoJSlD; break;
    /* no cases for OP_EQI and OP_EQK, as they don't call metamethods */
    case ictDx05oO0: case dvRioI: case gzac8qPB_Xk: nTfBgNB = RaK8G2abSYWn; break;
    case COFNH: case Viphfvglb7: case Edq6PrzH4B_: nTfBgNB = WGDV4ac_; break;
    case GykrXaid: case YWvhvtVNbpp: nTfBgNB = xTxCoIS; break;
    default:
      return j47fIO6TGF;  /* cannot find a reasonable name */
  }
  *rripw = E_P7IGQSKQ(QhZwnfYnvMsH(eLvbL9NVB2)->oHGC3CxZjyT[nTfBgNB]) + 2;
  return "metamethod";
}


/*
** Try to find a name for a function based on how it was called.
*/
static const char *vvShb (Q16ORi *eLvbL9NVB2, uZb1XkhMD *lV27,
                                                   const char **rripw) {
  if (lV27->Zhqa6hhv & uky8BP86Ap) {  /* was it called inside a hook? */
    *rripw = "?";
    return "hook";
  }
  else if (lV27->Zhqa6hhv & iHYcl) {  /* was it called as a finalizer? */
    *rripw = "__gc";
    return "metamethod";  /* report it as such */
  }
  else if (Cs0KlqHx(lV27))
    return ckPZbwe(eLvbL9NVB2, RdfVeR0eN3(lV27)->hKodskHE, o1PPX9VXpd(lV27), rripw);
  else
    return j47fIO6TGF;
}

/* }====================================================== */



/*
** Check whether pointer 'o' points to some value in the stack frame of
** the current function and, if so, returns its index.  Because 'o' may
** not point to a value in this stack, we cannot compare it with the
** region boundaries (undefined behavior in ISO C).
*/
static int dH3INc (uZb1XkhMD *lV27, const lKMnS0I9 *iTzwS1rQHCLfD) {
  int Dlee9KfTZRH;
  NjQPM6vrdb XMqavxZ = lV27->qKRsgSUBM.hKodskHE + 1;
  for (Dlee9KfTZRH = 0; XMqavxZ + Dlee9KfTZRH < lV27->r0VRu5F6NhvJC.hKodskHE; Dlee9KfTZRH++) {
    if (iTzwS1rQHCLfD == TVUTp(XMqavxZ + Dlee9KfTZRH))
      return Dlee9KfTZRH;
  }
  return -1;  /* not found */
}


/*
** Checks whether value 'o' came from an upvalue. (That can only happen
** with instructions OP_GETTABUP/OP_SETTABUP, which operate directly on
** upvalues.)
*/
static const char *hIw_z1K3S (uZb1XkhMD *lV27, const lKMnS0I9 *iTzwS1rQHCLfD,
                                 const char **rripw) {
  GES3_MiG *MfNuPHx = RdfVeR0eN3(lV27);
  int dAeZkuAUTxR;
  for (dAeZkuAUTxR = 0; dAeZkuAUTxR < MfNuPHx->tNmMfPw4Nb; dAeZkuAUTxR++) {
    if (MfNuPHx->l6lJ[dAeZkuAUTxR]->repC6Fz6XE.hKodskHE == iTzwS1rQHCLfD) {
      *rripw = hMN4q5yCs2(MfNuPHx->hKodskHE, dAeZkuAUTxR);
      return "upvalue";
    }
  }
  return j47fIO6TGF;
}


static const char *wnMjqQHt (Q16ORi *eLvbL9NVB2, const char *KWZvxoCdCt,
                                                const char *rripw) {
  if (KWZvxoCdCt == j47fIO6TGF)
    return "";  /* no information */
  else
    return dKaJ0l9aGyi2x(eLvbL9NVB2, " (%s '%s')", KWZvxoCdCt, rripw);
}

/*
** Build a string with a "description" for the value 'o', such as
** "variable 'x'" or "upvalue 'y'".
*/
static const char *jWw7A (Q16ORi *eLvbL9NVB2, const lKMnS0I9 *iTzwS1rQHCLfD) {
  uZb1XkhMD *lV27 = eLvbL9NVB2->lV27;
  const char *rripw = j47fIO6TGF;  /* to avoid warnings */
  const char *KWZvxoCdCt = j47fIO6TGF;
  if (Cs0KlqHx(lV27)) {
    KWZvxoCdCt = hIw_z1K3S(lV27, iTzwS1rQHCLfD, &rripw);  /* check whether 'o' is an upvalue */
    if (!KWZvxoCdCt) {  /* not an upvalue? */
      int gJ8Vltwkc5Y = dH3INc(lV27, iTzwS1rQHCLfD);  /* try a register */
      if (gJ8Vltwkc5Y >= 0)  /* is 'o' a register? */
        KWZvxoCdCt = veqcUV5(RdfVeR0eN3(lV27)->hKodskHE, o1PPX9VXpd(lV27), gJ8Vltwkc5Y, &rripw);
    }
  }
  return wnMjqQHt(eLvbL9NVB2, KWZvxoCdCt, rripw);
}


/*
** Raise a type error
*/
static uHOUvZ8eqVw uRVgZ (Q16ORi *eLvbL9NVB2, const lKMnS0I9 *iTzwS1rQHCLfD, const char *UwZl,
                          const char *xHJood) {
  const char *rvpr = XqSO0V7JuSVV(eLvbL9NVB2, iTzwS1rQHCLfD);
  w0b7D(eLvbL9NVB2, "attempt to %s a %s value%s", UwZl, rvpr, xHJood);
}


/*
** Raise a type error with "standard" information about the faulty
** object 'o' (using 'varinfo').
*/
uHOUvZ8eqVw FCJf (Q16ORi *eLvbL9NVB2, const lKMnS0I9 *iTzwS1rQHCLfD, const char *UwZl) {
  uRVgZ(eLvbL9NVB2, iTzwS1rQHCLfD, UwZl, jWw7A(eLvbL9NVB2, iTzwS1rQHCLfD));
}


/*
** Raise an error for calling a non-callable object. Try to find a name
** for the object based on how it was called ('funcnamefromcall'); if it
** cannot get a name there, try 'varinfo'.
*/
uHOUvZ8eqVw akamh9g4 (Q16ORi *eLvbL9NVB2, const lKMnS0I9 *iTzwS1rQHCLfD) {
  uZb1XkhMD *lV27 = eLvbL9NVB2->lV27;
  const char *rripw = j47fIO6TGF;  /* to avoid warnings */
  const char *KWZvxoCdCt = vvShb(eLvbL9NVB2, lV27, &rripw);
  const char *xHJood = KWZvxoCdCt ? wnMjqQHt(eLvbL9NVB2, KWZvxoCdCt, rripw) : jWw7A(eLvbL9NVB2, iTzwS1rQHCLfD);
  uRVgZ(eLvbL9NVB2, iTzwS1rQHCLfD, "call", xHJood);
}


uHOUvZ8eqVw nVxL8cNhA (Q16ORi *eLvbL9NVB2, const lKMnS0I9 *iTzwS1rQHCLfD, const char *KwNofT_bBstl_) {
  w0b7D(eLvbL9NVB2, "bad 'for' %s (number expected, got %s)",
                   KwNofT_bBstl_, XqSO0V7JuSVV(eLvbL9NVB2, iTzwS1rQHCLfD));
}


uHOUvZ8eqVw s831oP_ (Q16ORi *eLvbL9NVB2, const lKMnS0I9 *dApznL, const lKMnS0I9 *NvE2QMaDHUAD) {
  if (FpYBPjwaL3Zgq(dApznL) || MJG00m9BDy1z8(dApznL)) dApznL = NvE2QMaDHUAD;
  FCJf(eLvbL9NVB2, dApznL, "concatenate");
}


uHOUvZ8eqVw Y9InqGY (Q16ORi *eLvbL9NVB2, const lKMnS0I9 *dApznL,
                         const lKMnS0I9 *NvE2QMaDHUAD, const char *R4844) {
  if (!ZNqniIWqj9dk(dApznL))  /* first operand is wrong? */
    NvE2QMaDHUAD = dApznL;  /* now second is wrong */
  FCJf(eLvbL9NVB2, NvE2QMaDHUAD, R4844);
}


/*
** Error when both values are convertible to numbers, but not to integers
*/
uHOUvZ8eqVw qPBvJju52X6 (Q16ORi *eLvbL9NVB2, const lKMnS0I9 *dApznL, const lKMnS0I9 *NvE2QMaDHUAD) {
  ld2K5rUsGfbbm qaQGuJqqGdW5;
  if (!M_91Ch7(dApznL, &qaQGuJqqGdW5, mtG3Xd_vKd))
    NvE2QMaDHUAD = dApznL;
  w0b7D(eLvbL9NVB2, "number%s has no integer representation", jWw7A(eLvbL9NVB2, NvE2QMaDHUAD));
}


uHOUvZ8eqVw YDa6l5MifxKA4 (Q16ORi *eLvbL9NVB2, const lKMnS0I9 *dApznL, const lKMnS0I9 *NvE2QMaDHUAD) {
  const char *JpgzPNQVWhG2 = XqSO0V7JuSVV(eLvbL9NVB2, dApznL);
  const char *J2YZsy3lryr = XqSO0V7JuSVV(eLvbL9NVB2, NvE2QMaDHUAD);
  if (Y5wt0(JpgzPNQVWhG2, J2YZsy3lryr) == 0)
    w0b7D(eLvbL9NVB2, "attempt to compare two %s values", JpgzPNQVWhG2);
  else
    w0b7D(eLvbL9NVB2, "attempt to compare %s with %s", JpgzPNQVWhG2, J2YZsy3lryr);
}


/* add src:line information to 'msg' */
const char *LpX1Cm6s (Q16ORi *eLvbL9NVB2, const char *R4844, VXIZtj17 *vJAU5b,
                                        int UsdWK) {
  char jGpDh[FhNqbg24AIQS];
  if (vJAU5b)
    k6fMofb7dq7X(jGpDh, PSv0c5T6CS(vJAU5b), dYBi29C9w(vJAU5b));
  else {  /* no source available; use "?" instead */
    jGpDh[0] = '?'; jGpDh[1] = '\0';
  }
  return dKaJ0l9aGyi2x(eLvbL9NVB2, "%s:%d: %s", jGpDh, UsdWK, R4844);
}


uHOUvZ8eqVw VBBfA5Ct3lqN (Q16ORi *eLvbL9NVB2) {
  if (eLvbL9NVB2->lnIcP != 0) {  /* is there an error handling function? */
    NjQPM6vrdb lnIcP = hgRKYJZSMaUnV(eLvbL9NVB2, eLvbL9NVB2->lnIcP);
    FJUHtBVBux(v1HX0KUp49F(TVUTp(lnIcP)));
    cBIi__BQc(eLvbL9NVB2, eLvbL9NVB2->r0VRu5F6NhvJC.hKodskHE, eLvbL9NVB2->r0VRu5F6NhvJC.hKodskHE - 1);  /* move argument */
    cBIi__BQc(eLvbL9NVB2, eLvbL9NVB2->r0VRu5F6NhvJC.hKodskHE - 1, lnIcP);  /* push function */
    eLvbL9NVB2->r0VRu5F6NhvJC.hKodskHE++;  /* assume EXTRA_STACK */
    xSobWE_q(eLvbL9NVB2, eLvbL9NVB2->r0VRu5F6NhvJC.hKodskHE - 2, 1);  /* call it */
  }
  r4NfYgrojq(eLvbL9NVB2, cQ5Plnd);
}


uHOUvZ8eqVw w0b7D (Q16ORi *eLvbL9NVB2, const char *JFlbF, ...) {
  uZb1XkhMD *lV27 = eLvbL9NVB2->lV27;
  const char *R4844;
  lnHhAl0EKHi31 Cwg8JZm6;
  cRUYJ_PvKo6sB(eLvbL9NVB2);  /* error message uses memory */
  mTmbr87jIJZy(Cwg8JZm6, JFlbF);
  R4844 = OyGpRvfW2W(eLvbL9NVB2, JFlbF, Cwg8JZm6);  /* format message */
  oykhA0i(Cwg8JZm6);
  if (Cs0KlqHx(lV27)) {  /* if Lua function, add source:line information */
    LpX1Cm6s(eLvbL9NVB2, R4844, RdfVeR0eN3(lV27)->hKodskHE->YJ8R06m, DM4z(lV27));
    cBIi__BQc(eLvbL9NVB2, eLvbL9NVB2->r0VRu5F6NhvJC.hKodskHE - 2, eLvbL9NVB2->r0VRu5F6NhvJC.hKodskHE - 1);  /* remove 'msg' */
    eLvbL9NVB2->r0VRu5F6NhvJC.hKodskHE--;
  }
  VBBfA5Ct3lqN(eLvbL9NVB2);
}


/*
** Check whether new instruction 'newpc' is in a different line from
** previous instruction 'oldpc'. More often than not, 'newpc' is only
** one or a few instructions after 'oldpc' (it must be after, see
** caller), so try to avoid calling 'luaG_getfuncline'. If they are
** too far apart, there is a good chance of a ABSLINEINFO in the way,
** so it goes directly to 'luaG_getfuncline'.
*/
static int E2AWoF0EwLFI (const DuNV4gq *hKodskHE, int tu_YSGdV2, int Wux0BWdIrniU) {
  if (hKodskHE->hRSIHbZxOMDh == j47fIO6TGF)  /* no debug information? */
    return 0;
  if (Wux0BWdIrniU - tu_YSGdV2 < DpANLOFGg / 2) {  /* not too far apart? */
    int vfA__9_n8Hhy = 0;  /* line difference */
    int DUScZdhxUXl = tu_YSGdV2;
    for (;;) {
      int hRSIHbZxOMDh = hKodskHE->hRSIHbZxOMDh[++DUScZdhxUXl];
      if (hRSIHbZxOMDh == lFkjlott)
        break;  /* cannot compute delta; fall through */
      vfA__9_n8Hhy += hRSIHbZxOMDh;
      if (DUScZdhxUXl == Wux0BWdIrniU)
        return (vfA__9_n8Hhy != 0);  /* delta computed successfully */
    }
  }
  /* either instructions are too far apart or there is an absolute line
     info in the way; compute line difference explicitly */
  return (iDedS_PKbm0t(hKodskHE, tu_YSGdV2) != iDedS_PKbm0t(hKodskHE, Wux0BWdIrniU));
}


/*
** Traces Lua calls. If code is running the first instruction of a function,
** and function is not vararg, and it is not coming from an yield,
** calls 'luaD_hookcall'. (Vararg functions will call 'luaD_hookcall'
** after adjusting its variable arguments; otherwise, they could call
** a line/count hook before the call hook. Functions coming from
** an yield already called 'luaD_hookcall' before yielding.)
*/
int gOqvwwCK (Q16ORi *eLvbL9NVB2) {
  uZb1XkhMD *lV27 = eLvbL9NVB2->lV27;
  DuNV4gq *hKodskHE = RdfVeR0eN3(lV27)->hKodskHE;
  lV27->jAPWcBeMbyC9.aMNNn7Pok0Rq.a373X = 1;  /* ensure hooks will be checked */
  if (lV27->jAPWcBeMbyC9.aMNNn7Pok0Rq.RDaIRyBui2N == hKodskHE->t7n9) {  /* first instruction (not resuming)? */
    if (hKodskHE->YSDW5HrmvNrr_)
      return 0;  /* hooks will start at VARARGPREP instruction */
    else if (!(lV27->Zhqa6hhv & m8xY))  /* not yieded? */
      rVEQFP8DtO(eLvbL9NVB2, lV27);  /* check 'call' hook */
  }
  return 1;  /* keep 'trap' on */
}


/*
** Traces the execution of a Lua function. Called before the execution
** of each opcode, when debug is on. 'L->oldpc' stores the last
** instruction traced, to detect line changes. When entering a new
** function, 'npci' will be zero and will test as a new line whatever
** the value of 'oldpc'.  Some exceptional conditions may return to
** a function without setting 'oldpc'. In that case, 'oldpc' may be
** invalid; if so, use zero as a valid value. (A wrong but valid 'oldpc'
** at most causes an extra call to a line hook.)
** This function is not "Protected" when called, so it should correct
** 'L->top.p' before calling anything that can run the GC.
*/
int edmNCjYiieLp (Q16ORi *eLvbL9NVB2, const mJrhOooHvsc *DUScZdhxUXl) {
  uZb1XkhMD *lV27 = eLvbL9NVB2->lV27;
  zgxkW3rj X8iIU = eLvbL9NVB2->N4mfpYv7;
  const DuNV4gq *hKodskHE = RdfVeR0eN3(lV27)->hKodskHE;
  int onrec85Ljdtl;
  if (!(X8iIU & (f3o_ | pctTy2C3kcx))) {  /* no hooks? */
    lV27->jAPWcBeMbyC9.aMNNn7Pok0Rq.a373X = 0;  /* don't need to stop again */
    return 0;  /* turn off 'trap' */
  }
  DUScZdhxUXl++;  /* reference is always next instruction */
  lV27->jAPWcBeMbyC9.aMNNn7Pok0Rq.RDaIRyBui2N = DUScZdhxUXl;  /* save 'pc' */
  onrec85Ljdtl = (X8iIU & pctTy2C3kcx) && (--eLvbL9NVB2->Aab7AlY9RSRe == 0);
  if (onrec85Ljdtl)
    qQRTqPbS(eLvbL9NVB2);  /* reset count */
  else if (!(X8iIU & f3o_))
    return 1;  /* no line hook and count != 0; nothing to be done now */
  if (lV27->Zhqa6hhv & m8xY) {  /* hook yielded last time? */
    lV27->Zhqa6hhv &= ~m8xY;  /* erase mark */
    return 1;  /* do not call hook again (VM yielded, so it did not move) */
  }
  if (!F8K9HN(*(lV27->jAPWcBeMbyC9.aMNNn7Pok0Rq.RDaIRyBui2N - 1)))  /* top not being used? */
    eLvbL9NVB2->r0VRu5F6NhvJC.hKodskHE = lV27->r0VRu5F6NhvJC.hKodskHE;  /* correct top */
  if (onrec85Ljdtl)
    lw6yQtxK1HqZ(eLvbL9NVB2, bkLg3jW, -1, 0, 0);  /* call count hook */
  if (X8iIU & f3o_) {
    /* 'L->oldpc' may be invalid; use zero in this case */
    int tu_YSGdV2 = (eLvbL9NVB2->tu_YSGdV2 < hKodskHE->C72cvbOVEuBn) ? eLvbL9NVB2->tu_YSGdV2 : 0;
    int NTmmVtN = WHwoCgOytcr(DUScZdhxUXl, hKodskHE);
    if (NTmmVtN <= tu_YSGdV2 ||  /* call hook when jump back (loop), */
        E2AWoF0EwLFI(hKodskHE, tu_YSGdV2, NTmmVtN)) {  /* or when enter new line */
      int YSLeJWmbazXI = iDedS_PKbm0t(hKodskHE, NTmmVtN);
      lw6yQtxK1HqZ(eLvbL9NVB2, DuN63XexT, YSLeJWmbazXI, 0, 0);  /* call line hook */
    }
    eLvbL9NVB2->tu_YSGdV2 = NTmmVtN;  /* 'pc' of last call to line hook */
  }
  if (eLvbL9NVB2->tFpkP == SuBWEG_oexhz) {  /* did hook yield? */
    if (onrec85Ljdtl)
      eLvbL9NVB2->Aab7AlY9RSRe = 1;  /* undo decrement to zero */
    lV27->Zhqa6hhv |= m8xY;  /* mark that it yielded */
    r4NfYgrojq(eLvbL9NVB2, SuBWEG_oexhz);
  }
  return 1;  /* keep 'trap' on */
}

