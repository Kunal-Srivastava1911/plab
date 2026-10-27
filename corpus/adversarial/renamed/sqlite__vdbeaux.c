/*
** 2003 September 6
**
** The author disclaims copyright to this source code.  In place of
** a legal notice, here is a blessing:
**
**    May you do good and not evil.
**    May you find forgiveness for yourself and forgive others.
**    May you share freely, never taking more than you give.
**
*************************************************************************
** This file contains code used for creating, destroying, and populating
** a VDBE (or an "sqlite3_stmt" as it is known to the outside world.)
*/
#include "sqliteInt.h"
#include "vdbeInt.h"

/* Forward references */
static void J9kIPsaPv(MEeQFpE4DzbZ *pLMJg2Xd, r_0_hpT *vPar9lD);
static void hOukOg4s95gVn(MEeQFpE4DzbZ *, mHYCosji8c *, int);

/*
** Create a new virtual database engine.
*/
Y4zzrBxD4OXTO *mNEV54xWRs(MSufNwYJMUIW *CZswHrqPXTX){
  MEeQFpE4DzbZ *pLMJg2Xd = CZswHrqPXTX->pLMJg2Xd;
  Y4zzrBxD4OXTO *RWdNEx2WUIO8x;
  RWdNEx2WUIO8x = j4Bew(pLMJg2Xd, sizeof(Y4zzrBxD4OXTO) );
  if( RWdNEx2WUIO8x==0 ) return 0;
  gDRc26rrZnG_(&RWdNEx2WUIO8x->V7Y0VHDmd1Xf, 0, sizeof(Y4zzrBxD4OXTO)-jU3cE1zA(Y4zzrBxD4OXTO,V7Y0VHDmd1Xf));
  RWdNEx2WUIO8x->pLMJg2Xd = pLMJg2Xd;
  if( pLMJg2Xd->FDcUAbRU ){
    pLMJg2Xd->FDcUAbRU->qanFC = &RWdNEx2WUIO8x->KELn;
  }
  RWdNEx2WUIO8x->KELn = pLMJg2Xd->FDcUAbRU;
  RWdNEx2WUIO8x->qanFC = &pLMJg2Xd->FDcUAbRU;
  pLMJg2Xd->FDcUAbRU = RWdNEx2WUIO8x;
  f5IeCeK0e1W( RWdNEx2WUIO8x->C19t==w_rp1wwh );
  RWdNEx2WUIO8x->CZswHrqPXTX = CZswHrqPXTX;
  CZswHrqPXTX->FDcUAbRU = RWdNEx2WUIO8x;
  f5IeCeK0e1W( CZswHrqPXTX->sQYt2==0 );
  f5IeCeK0e1W( CZswHrqPXTX->SMlQQFbV==0 );
  f5IeCeK0e1W( RWdNEx2WUIO8x->crK7AlNP_f6==0 );
  f5IeCeK0e1W( CZswHrqPXTX->YbLEhxQ==0 );
  dwg4lJSc(RWdNEx2WUIO8x, EXKa_CQA, 0, 1);
  return RWdNEx2WUIO8x;
}

/*
** Return the Parse object that owns a Vdbe object.
*/
MSufNwYJMUIW *DAucAM(Y4zzrBxD4OXTO *RWdNEx2WUIO8x){
  return RWdNEx2WUIO8x->CZswHrqPXTX;
}

/*
** Change the error string stored in Vdbe.zErrMsg
*/
void haAKYIBsgAl(Y4zzrBxD4OXTO *RWdNEx2WUIO8x, const char *Zm6_Sj, ...){
  WTdlzRsWXwU lYmDMW9;
  UXHgfYQ(RWdNEx2WUIO8x->pLMJg2Xd, RWdNEx2WUIO8x->C9BnRQApGBXmM);
  CpjAzX(lYmDMW9, Zm6_Sj);
  RWdNEx2WUIO8x->C9BnRQApGBXmM = SRrx7cWPh4(RWdNEx2WUIO8x->pLMJg2Xd, Zm6_Sj, lYmDMW9);
  LZ9p(lYmDMW9);
}

/*
** Remember the SQL string for a prepared statement.
*/
void IDbcA3VmGsu0H(Y4zzrBxD4OXTO *RWdNEx2WUIO8x, const char *mrgekw0xj, int AS0ycVs, qHh5JW AUS9xq8fh){
  if( RWdNEx2WUIO8x==0 ) return;
  RWdNEx2WUIO8x->AUS9xq8fh = AUS9xq8fh;
  if( (AUS9xq8fh & dQky)==0 ){
    RWdNEx2WUIO8x->jhBEOz = 0;
  }
  f5IeCeK0e1W( RWdNEx2WUIO8x->W1REkwE==0 );
  RWdNEx2WUIO8x->W1REkwE = oS7U3U(RWdNEx2WUIO8x->pLMJg2Xd, mrgekw0xj, AS0ycVs);
}

#ifdef f2AUQe1
/*
** Add a new element to the Vdbe->pDblStr list.
*/
void FZN1EkootH(MEeQFpE4DzbZ *pLMJg2Xd, Y4zzrBxD4OXTO *RWdNEx2WUIO8x, const char *mrgekw0xj){
  if( RWdNEx2WUIO8x ){
    int AS0ycVs = cdWRz96EMqfU(mrgekw0xj);
    maKTiN *NKDvPH3DL4Dw = j4Bew(pLMJg2Xd,
                            sizeof(*NKDvPH3DL4Dw)+AS0ycVs+1-sizeof(NKDvPH3DL4Dw->mrgekw0xj));
    if( NKDvPH3DL4Dw ){
      NKDvPH3DL4Dw->Ir2qFTMJvd = RWdNEx2WUIO8x->NNZletnEKt;
      RWdNEx2WUIO8x->NNZletnEKt = NKDvPH3DL4Dw;
      u1hm9A(NKDvPH3DL4Dw->mrgekw0xj, mrgekw0xj, AS0ycVs+1);
    }
  }
}
#endif

#ifdef f2AUQe1
/*
** zId of length nId is a double-quoted identifier.  Check to see if
** that identifier is really used as a string literal.
*/
int sWOR7(
  Y4zzrBxD4OXTO *FDcUAbRU,            /* The prepared statement */
  const char *Hrr6         /* The double-quoted identifier, already dequoted */
){
  maKTiN *NKDvPH3DL4Dw;
  f5IeCeK0e1W( Hrr6!=0 );
  if( FDcUAbRU->NNZletnEKt==0 ) return 0;
  for(NKDvPH3DL4Dw=FDcUAbRU->NNZletnEKt; NKDvPH3DL4Dw; NKDvPH3DL4Dw=NKDvPH3DL4Dw->Ir2qFTMJvd){
    if( wTd5D(Hrr6, NKDvPH3DL4Dw->mrgekw0xj)==0 ) return 1;
  }
  return 0;
}
#endif

/*
** Swap byte-code between two VDBE structures.
**
** This happens after pB was previously run and returned
** SQLITE_SCHEMA.  The statement was then reprepared in pA.
** This routine transfers the new bytecode in pA over to pB
** so that pB can be run again.  The old pB byte code is
** moved back to pA so that it will be cleaned up when pA is
** finalized.
*/
void r5rBOEnmup(Y4zzrBxD4OXTO *zdmP9_tt2yl, Y4zzrBxD4OXTO *YnMwMs){
  Y4zzrBxD4OXTO PvxDSqJVOjze, *syxgbk6S7u4y, **RjKC_7ATkb;
  char *kTe9cEtWB;
  f5IeCeK0e1W( zdmP9_tt2yl->pLMJg2Xd==YnMwMs->pLMJg2Xd );
  PvxDSqJVOjze = *zdmP9_tt2yl;
  *zdmP9_tt2yl = *YnMwMs;
  *YnMwMs = PvxDSqJVOjze;
  syxgbk6S7u4y = zdmP9_tt2yl->KELn;
  zdmP9_tt2yl->KELn = YnMwMs->KELn;
  YnMwMs->KELn = syxgbk6S7u4y;
  RjKC_7ATkb = zdmP9_tt2yl->qanFC;
  zdmP9_tt2yl->qanFC = YnMwMs->qanFC;
  YnMwMs->qanFC = RjKC_7ATkb;
  kTe9cEtWB = zdmP9_tt2yl->W1REkwE;
  zdmP9_tt2yl->W1REkwE = YnMwMs->W1REkwE;
  YnMwMs->W1REkwE = kTe9cEtWB;
#ifdef f2AUQe1
  kTe9cEtWB = zdmP9_tt2yl->aC5kY;
  zdmP9_tt2yl->aC5kY = YnMwMs->aC5kY;
  YnMwMs->aC5kY = kTe9cEtWB;
#endif
  YnMwMs->jhBEOz = zdmP9_tt2yl->jhBEOz;
  YnMwMs->AUS9xq8fh = zdmP9_tt2yl->AUS9xq8fh;
  u1hm9A(YnMwMs->IXdMk4ebq0V, zdmP9_tt2yl->IXdMk4ebq0V, sizeof(YnMwMs->IXdMk4ebq0V));
  YnMwMs->IXdMk4ebq0V[gBKm_J0]++;
}

/*
** Resize the Vdbe.aOp array so that it is at least nOp elements larger
** than its current size. nOp is guaranteed to be less than or equal
** to 1024/sizeof(Op).
**
** If an out-of-memory error occurs while resizing the array, return
** SQLITE_NOMEM. In this case Vdbe.aOp and Vdbe.nOpAlloc remain
** unchanged (this is so that any opcodes already allocated can be
** correctly deallocated along with the rest of the Vdbe).
*/
static int fXw2urqqeI4(Y4zzrBxD4OXTO *HB_T1jBCLdNzN, int rtaUFjmY){
  kqPOQZYA16d *UdjreBdSSGOa;
  MSufNwYJMUIW *RWdNEx2WUIO8x = HB_T1jBCLdNzN->CZswHrqPXTX;

  /* The SQLITE_TEST_REALLOC_STRESS compile-time option is designed to force
  ** more frequent reallocs and hence provide more opportunities for
  ** simulated OOM faults.  SQLITE_TEST_REALLOC_STRESS is generally used
  ** during testing only.  With SQLITE_TEST_REALLOC_STRESS grow the op array
  ** by the minimum* amount required until the size reaches 512.  Normal
  ** operation (without SQLITE_TEST_REALLOC_STRESS) is to double the current
  ** size of the op array or add 1KB of space, whichever is smaller. */
#ifdef mJe7
  OfeosV3WSPC jg5QOJE = (HB_T1jBCLdNzN->crK7AlNP_f6>=512 ? 2*(OfeosV3WSPC)HB_T1jBCLdNzN->crK7AlNP_f6
                        : (OfeosV3WSPC)HB_T1jBCLdNzN->crK7AlNP_f6+rtaUFjmY);
#else
  OfeosV3WSPC jg5QOJE = (HB_T1jBCLdNzN->crK7AlNP_f6 ? 2*(OfeosV3WSPC)HB_T1jBCLdNzN->crK7AlNP_f6
                        : (OfeosV3WSPC)(1024/sizeof(mHYCosji8c)));
  yhypAvj(rtaUFjmY);
#endif

  /* Ensure that the size of a VDBE does not grow too large */
  if( jg5QOJE > RWdNEx2WUIO8x->pLMJg2Xd->LtZbXKxMlz0J[WwYHiDbhz] ){
    I_fGWFjD(RWdNEx2WUIO8x->pLMJg2Xd);
    return ccKsEfbei4;
  }

  f5IeCeK0e1W( rtaUFjmY<=(int)(1024/sizeof(mHYCosji8c)) );
  f5IeCeK0e1W( jg5QOJE>=(HB_T1jBCLdNzN->crK7AlNP_f6+rtaUFjmY) );
  UdjreBdSSGOa = nhUctWhr(RWdNEx2WUIO8x->pLMJg2Xd, HB_T1jBCLdNzN->V7Y0VHDmd1Xf, jg5QOJE*sizeof(mHYCosji8c));
  if( UdjreBdSSGOa ){
    RWdNEx2WUIO8x->YbLEhxQ = J_08J4r4_ti(RWdNEx2WUIO8x->pLMJg2Xd, UdjreBdSSGOa);
    HB_T1jBCLdNzN->crK7AlNP_f6 = RWdNEx2WUIO8x->YbLEhxQ/sizeof(mHYCosji8c);
    HB_T1jBCLdNzN->V7Y0VHDmd1Xf = UdjreBdSSGOa;
  }
  return (UdjreBdSSGOa ? odQX7vL : gbOccFBhQR);
}

#ifdef iteB65TL5L
/* This routine is just a convenient place to set a breakpoint that will
** fire after each opcode is inserted and displayed using
** "PRAGMA vdbe_addoptrace=on".  Parameters "pc" (program counter) and
** pOp are available to make the breakpoint conditional.
**
** Other useful labels for breakpoints include:
**   test_trace_breakpoint(pc,pOp)
**   sqlite3CorruptError(lineno)
**   sqlite3MisuseError(lineno)
**   sqlite3CantopenError(lineno)
*/
static void iXhSC64(int Ee05M7jDx_, mHYCosji8c *BYPQ){
  static WuWa4iT AS0ycVs = 0;
  (void)Ee05M7jDx_;
  (void)BYPQ;
  AS0ycVs++;
  if( AS0ycVs==qXB8pRdNkZ ) GY0UA9QT8_y7(); /* so that n is used, preventing a warning */
}
#endif

/*
** Slow paths for sqlite3VdbeAddOp3() and sqlite3VdbeAddOp4Int() for the
** unusual case when we need to increase the size of the Vdbe.aOp[] array
** before adding the new opcode.
*/
static XmVnyUQh int bMB3TU(Y4zzrBxD4OXTO *RWdNEx2WUIO8x, int odStgZ, int mB_5hYOV5K, int pPP2V5, int BTBDVdeO3P){
  f5IeCeK0e1W( RWdNEx2WUIO8x->crK7AlNP_f6<=RWdNEx2WUIO8x->rtaUFjmY );
  if( fXw2urqqeI4(RWdNEx2WUIO8x, 1) ) return 1;
  f5IeCeK0e1W( RWdNEx2WUIO8x->crK7AlNP_f6>RWdNEx2WUIO8x->rtaUFjmY );
  return sNmXi5z1R8n5(RWdNEx2WUIO8x, odStgZ, mB_5hYOV5K, pPP2V5, BTBDVdeO3P);
}
static XmVnyUQh int OFBV_x(
  Y4zzrBxD4OXTO *RWdNEx2WUIO8x,            /* Add the opcode to this VM */
  int odStgZ,             /* The new opcode */
  int mB_5hYOV5K,             /* The P1 operand */
  int pPP2V5,             /* The P2 operand */
  int BTBDVdeO3P,             /* The P3 operand */
  int vO1m9d              /* The P4 operand as an integer */
){
  int JPWY = sNmXi5z1R8n5(RWdNEx2WUIO8x, odStgZ, mB_5hYOV5K, pPP2V5, BTBDVdeO3P);
  if( RWdNEx2WUIO8x->pLMJg2Xd->mi4oOCmRVN_h==0 ){
    kqPOQZYA16d *BYPQ = &RWdNEx2WUIO8x->V7Y0VHDmd1Xf[JPWY];
    BYPQ->ZP4P_QR4oE = KUJARfJ_9I;
    BYPQ->vO1m9d.Pyy0l6xD = vO1m9d;
  }
  return JPWY;
}


/*
** Add a new instruction to the list of instructions current in the
** VDBE.  Return the address of the new instruction.
**
** Parameters:
**
**    p               Pointer to the VDBE
**
**    op              The opcode for this instruction
**
**    p1, p2, p3, p4  Operands
*/
int Ku8cbll7CJ6HU(Y4zzrBxD4OXTO *RWdNEx2WUIO8x, int odStgZ){
  return sNmXi5z1R8n5(RWdNEx2WUIO8x, odStgZ, 0, 0, 0);
}
int xTgHCTr(Y4zzrBxD4OXTO *RWdNEx2WUIO8x, int odStgZ, int mB_5hYOV5K){
  return sNmXi5z1R8n5(RWdNEx2WUIO8x, odStgZ, mB_5hYOV5K, 0, 0);
}
int dwg4lJSc(Y4zzrBxD4OXTO *RWdNEx2WUIO8x, int odStgZ, int mB_5hYOV5K, int pPP2V5){
  return sNmXi5z1R8n5(RWdNEx2WUIO8x, odStgZ, mB_5hYOV5K, pPP2V5, 0);
}
int sNmXi5z1R8n5(Y4zzrBxD4OXTO *RWdNEx2WUIO8x, int odStgZ, int mB_5hYOV5K, int pPP2V5, int BTBDVdeO3P){
  int Pyy0l6xD;
  kqPOQZYA16d *BYPQ;

  Pyy0l6xD = RWdNEx2WUIO8x->rtaUFjmY;
  f5IeCeK0e1W( RWdNEx2WUIO8x->C19t==w_rp1wwh );
  f5IeCeK0e1W( odStgZ>=0 && odStgZ<0xff );
  if( RWdNEx2WUIO8x->crK7AlNP_f6<=Pyy0l6xD ){
    return bMB3TU(RWdNEx2WUIO8x, odStgZ, mB_5hYOV5K, pPP2V5, BTBDVdeO3P);
  }
  f5IeCeK0e1W( RWdNEx2WUIO8x->V7Y0VHDmd1Xf!=0 );
  RWdNEx2WUIO8x->rtaUFjmY++;
  BYPQ = &RWdNEx2WUIO8x->V7Y0VHDmd1Xf[Pyy0l6xD];
  f5IeCeK0e1W( BYPQ!=0 );
  BYPQ->KMcyPZbh = (qHh5JW)odStgZ;
  BYPQ->I4yL = 0;
  BYPQ->mB_5hYOV5K = mB_5hYOV5K;
  BYPQ->pPP2V5 = pPP2V5;
  BYPQ->BTBDVdeO3P = BTBDVdeO3P;
  BYPQ->vO1m9d.RWdNEx2WUIO8x = 0;
  BYPQ->ZP4P_QR4oE = bcIYtAfjheQ;

  /* Replicate this logic in sqlite3VdbeAddOp4Int()
  ** vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv   */
#ifdef faD_O9XSX
  BYPQ->PihbEOgZ = 0;
#endif
#if pZX7GD4OTcuV(ghoW) || pZX7GD4OTcuV(fsSLSO_wyCxfR)
  BYPQ->GtnbWK = 0;
  BYPQ->UKXyt_q = 0;
#endif
#ifdef iteB65TL5L
  if( RWdNEx2WUIO8x->pLMJg2Xd->MRNoo5HiPBk7 & Gc4yIjlq ){
    QA1Dfk_5egTE9(0, Pyy0l6xD, &RWdNEx2WUIO8x->V7Y0VHDmd1Xf[Pyy0l6xD]);
    iXhSC64(Pyy0l6xD, &RWdNEx2WUIO8x->V7Y0VHDmd1Xf[Pyy0l6xD]);
  }
#endif
#ifdef xGeFUI6
  BYPQ->BzSu7o = 0;
#endif
  /* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
  ** Replicate in sqlite3VdbeAddOp4Int() */

  return Pyy0l6xD;
}
int VOPHtgobTt(
  Y4zzrBxD4OXTO *RWdNEx2WUIO8x,            /* Add the opcode to this VM */
  int odStgZ,             /* The new opcode */
  int mB_5hYOV5K,             /* The P1 operand */
  int pPP2V5,             /* The P2 operand */
  int BTBDVdeO3P,             /* The P3 operand */
  int vO1m9d              /* The P4 operand as an integer */
){
  int Pyy0l6xD;
  kqPOQZYA16d *BYPQ;

  Pyy0l6xD = RWdNEx2WUIO8x->rtaUFjmY;
  if( RWdNEx2WUIO8x->crK7AlNP_f6<=Pyy0l6xD ){
    return OFBV_x(RWdNEx2WUIO8x, odStgZ, mB_5hYOV5K, pPP2V5, BTBDVdeO3P, vO1m9d);
  }
  RWdNEx2WUIO8x->rtaUFjmY++;
  BYPQ = &RWdNEx2WUIO8x->V7Y0VHDmd1Xf[Pyy0l6xD];
  f5IeCeK0e1W( BYPQ!=0 );
  BYPQ->KMcyPZbh = (qHh5JW)odStgZ;
  BYPQ->I4yL = 0;
  BYPQ->mB_5hYOV5K = mB_5hYOV5K;
  BYPQ->pPP2V5 = pPP2V5;
  BYPQ->BTBDVdeO3P = BTBDVdeO3P;
  BYPQ->vO1m9d.Pyy0l6xD = vO1m9d;
  BYPQ->ZP4P_QR4oE = KUJARfJ_9I;

  /* Replicate this logic in sqlite3VdbeAddOp3()
  ** vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv   */
#ifdef faD_O9XSX
  BYPQ->PihbEOgZ = 0;
#endif
#if pZX7GD4OTcuV(ghoW) || pZX7GD4OTcuV(fsSLSO_wyCxfR)
  BYPQ->GtnbWK = 0;
  BYPQ->UKXyt_q = 0;
#endif
#ifdef iteB65TL5L
  if( RWdNEx2WUIO8x->pLMJg2Xd->MRNoo5HiPBk7 & Gc4yIjlq ){
    QA1Dfk_5egTE9(0, Pyy0l6xD, &RWdNEx2WUIO8x->V7Y0VHDmd1Xf[Pyy0l6xD]);
    iXhSC64(Pyy0l6xD, &RWdNEx2WUIO8x->V7Y0VHDmd1Xf[Pyy0l6xD]);
  }
#endif
#ifdef xGeFUI6
  BYPQ->BzSu7o = 0;
#endif
  /* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
  ** Replicate in sqlite3VdbeAddOp3() */

  return Pyy0l6xD;
}

/* Generate code for an unconditional jump to instruction iDest
*/
int IJPWRWXGjBy(Y4zzrBxD4OXTO *RWdNEx2WUIO8x, int dozV_ncZ_Yd){
  return sNmXi5z1R8n5(RWdNEx2WUIO8x, G3AhjxME, 0, dozV_ncZ_Yd, 0);
}

/* Generate code to cause the string zStr to be loaded into
** register iDest
*/
int KILtU(Y4zzrBxD4OXTO *RWdNEx2WUIO8x, int dozV_ncZ_Yd, const char *G1JO1qgB4D){
  return gQe9mLCRpdMr0(RWdNEx2WUIO8x, TgoWB, 0, dozV_ncZ_Yd, 0, G1JO1qgB4D, 0);
}

/*
** Generate code that initializes multiple registers to string or integer
** constants.  The registers begin with iDest and increase consecutively.
** One register is initialized for each characgter in zTypes[].  For each
** "s" character in zTypes[], the register is a string if the argument is
** not NULL, or OP_Null if the value is a null pointer.  For each "i" character
** in zTypes[], the register is initialized to an integer.
**
** If the input string does not end with "X" then an OP_ResultRow instruction
** is generated for the values inserted.
*/
void UVnwl42LpldP1(Y4zzrBxD4OXTO *RWdNEx2WUIO8x, int dozV_ncZ_Yd, const char *hLjj9vvrsz, ...){
  WTdlzRsWXwU lYmDMW9;
  int Pyy0l6xD;
  char Wydjdw_pm6;
  CpjAzX(lYmDMW9, hLjj9vvrsz);
  for(Pyy0l6xD=0; (Wydjdw_pm6 = hLjj9vvrsz[Pyy0l6xD])!=0; Pyy0l6xD++){
    if( Wydjdw_pm6=='s' ){
      const char *mrgekw0xj = BK7PRlx3Xsq(lYmDMW9, const char*);
      gQe9mLCRpdMr0(RWdNEx2WUIO8x, mrgekw0xj==0 ? dR5o_PnwT : TgoWB, 0, dozV_ncZ_Yd+Pyy0l6xD, 0, mrgekw0xj, 0);
    }else if( Wydjdw_pm6=='i' ){
      dwg4lJSc(RWdNEx2WUIO8x, q3vXRMuAw8oEW, BK7PRlx3Xsq(lYmDMW9, int), dozV_ncZ_Yd+Pyy0l6xD);
    }else{
      goto aIYpBFXnqI;
    }
  }
  dwg4lJSc(RWdNEx2WUIO8x, yfSB6_a, dozV_ncZ_Yd, Pyy0l6xD);
aIYpBFXnqI:
  LZ9p(lYmDMW9);
}

/*
** Add an opcode that includes the p4 value as a pointer.
*/
int gQe9mLCRpdMr0(
  Y4zzrBxD4OXTO *RWdNEx2WUIO8x,            /* Add the opcode to this VM */
  int odStgZ,             /* The new opcode */
  int mB_5hYOV5K,             /* The P1 operand */
  int pPP2V5,             /* The P2 operand */
  int BTBDVdeO3P,             /* The P3 operand */
  const char *JrmG5OAto30B,    /* The P4 operand */
  int ZP4P_QR4oE          /* P4 operand type */
){
  int JPWY = sNmXi5z1R8n5(RWdNEx2WUIO8x, odStgZ, mB_5hYOV5K, pPP2V5, BTBDVdeO3P);
  AyAMrl5QsX(RWdNEx2WUIO8x, JPWY, JrmG5OAto30B, ZP4P_QR4oE);
  return JPWY;
}

/*
** Add an OP_Function or OP_PureFunc opcode.
**
** The eCallCtx argument is information (typically taken from Expr.op2)
** that describes the calling context of the function.  0 means a general
** function call.  NC_IsCheck means called by a check constraint,
** NC_IdxExpr means called as part of an index expression.  NC_PartIdx
** means in the WHERE clause of a partial index.  NC_GenCol means called
** while computing a generated column value.  0 is the usual case.
*/
int tskwJqhND(
  MSufNwYJMUIW *CZswHrqPXTX,        /* Parsing context */
  int mB_5hYOV5K,               /* Constant argument mask */
  int pPP2V5,               /* First argument register */
  int BTBDVdeO3P,               /* Register into which results are written */
  int WL_eiS,             /* Number of argument */
  const r_0_hpT *pOpnI3oMVnGn, /* The function to be invoked */
  int kwx_R          /* Calling context */
){
  Y4zzrBxD4OXTO *HB_T1jBCLdNzN = CZswHrqPXTX->FDcUAbRU;
  int jCneFxRQnw;
  int JPWY;
  DWQQ4Hi8 *KMDC3A_94J;
  f5IeCeK0e1W( HB_T1jBCLdNzN );
  jCneFxRQnw = sizeof(*KMDC3A_94J) + (WL_eiS-1)*sizeof(EPdZvOoD0Wseb*);
  KMDC3A_94J = j4Bew(CZswHrqPXTX->pLMJg2Xd, jCneFxRQnw);
  if( KMDC3A_94J==0 ){
    f5IeCeK0e1W( CZswHrqPXTX->pLMJg2Xd->mi4oOCmRVN_h );
    J9kIPsaPv(CZswHrqPXTX->pLMJg2Xd, (r_0_hpT*)pOpnI3oMVnGn);
    return 0;
  }
  KMDC3A_94J->IBMjGt5hp = 0;
  KMDC3A_94J->pOpnI3oMVnGn = (r_0_hpT*)pOpnI3oMVnGn;
  KMDC3A_94J->FDcUAbRU = 0;
  KMDC3A_94J->OAlk0 = 0;
  KMDC3A_94J->LQeaBUw = WL_eiS;
  KMDC3A_94J->Fz1Fyirahk = crHZR55(HB_T1jBCLdNzN);
  JPWY = gQe9mLCRpdMr0(HB_T1jBCLdNzN, kwx_R ? s9LjXi53Xo : Us7_agR,
                           mB_5hYOV5K, pPP2V5, BTBDVdeO3P, (char*)KMDC3A_94J, H5QvOmDMVC1Eh);
  WKe_X9SULH(HB_T1jBCLdNzN, kwx_R & tjNQxaWrFtKt);
  y1ze2(CZswHrqPXTX);
  return JPWY;
}

/*
** Add an opcode that includes the p4 value with a P4_INT64 or
** P4_REAL type.
*/
int LtJLch(
  Y4zzrBxD4OXTO *RWdNEx2WUIO8x,            /* Add the opcode to this VM */
  int odStgZ,             /* The new opcode */
  int mB_5hYOV5K,             /* The P1 operand */
  int pPP2V5,             /* The P2 operand */
  int BTBDVdeO3P,             /* The P3 operand */
  const qHh5JW *JrmG5OAto30B,      /* The P4 operand */
  int ZP4P_QR4oE          /* P4 operand type */
){
  char *FXs_xwF = j4Bew(sA2ZhL(RWdNEx2WUIO8x), 8);
  if( FXs_xwF ) u1hm9A(FXs_xwF, JrmG5OAto30B, 8);
  return gQe9mLCRpdMr0(RWdNEx2WUIO8x, odStgZ, mB_5hYOV5K, pPP2V5, BTBDVdeO3P, FXs_xwF, ZP4P_QR4oE);
}

#ifndef r5Oia2csX9Q2n
/*
** Return the address of the current EXPLAIN QUERY PLAN baseline.
** 0 means "none".
*/
int Ulf3YcQW(MSufNwYJMUIW *CZswHrqPXTX){
  kqPOQZYA16d *BYPQ;
  if( CZswHrqPXTX->FxctWLg1rBXzM==0 ) return 0;
  BYPQ = lz2h(CZswHrqPXTX->FDcUAbRU, CZswHrqPXTX->FxctWLg1rBXzM);
  return BYPQ->pPP2V5;
}

/*
** Set a debugger breakpoint on the following routine in order to
** monitor the EXPLAIN QUERY PLAN code generation.
*/
#if pZX7GD4OTcuV(iteB65TL5L)
void CWnVx3UOR(const char *Hh5gZqJkxE0z, const char *qfM3ShD1JiIFQ){
  (void)Hh5gZqJkxE0z;
  (void)qfM3ShD1JiIFQ;
}
#endif

/*
** Add a new OP_Explain opcode.
**
** If the bPush flag is true, then make this opcode the parent for
** subsequent Explains until sqlite3VdbeExplainPop() is called.
*/
int mmMWqV6ER(MSufNwYJMUIW *CZswHrqPXTX, qHh5JW zofykHKh, const char *wUZIHd, ...){
  int JPWY = 0;
#if !pZX7GD4OTcuV(iteB65TL5L)
  /* Always include the OP_Explain opcodes if SQLITE_DEBUG is defined.
  ** But omit them (for performance) during production builds */
  if( CZswHrqPXTX->Iq7PbEyhO==2 || dSqqw(CZswHrqPXTX->pLMJg2Xd) )
#endif
  {
    char *MTaRmd7WLo;
    Y4zzrBxD4OXTO *HB_T1jBCLdNzN;
    WTdlzRsWXwU lYmDMW9;
    int qN9HuWCx;
    CpjAzX(lYmDMW9, wUZIHd);
    MTaRmd7WLo = SRrx7cWPh4(CZswHrqPXTX->pLMJg2Xd, wUZIHd, lYmDMW9);
    LZ9p(lYmDMW9);
    HB_T1jBCLdNzN = CZswHrqPXTX->FDcUAbRU;
    qN9HuWCx = HB_T1jBCLdNzN->rtaUFjmY;
    JPWY = gQe9mLCRpdMr0(HB_T1jBCLdNzN, WLqXtjk5Ez, qN9HuWCx, CZswHrqPXTX->FxctWLg1rBXzM, 0,
                      MTaRmd7WLo, fWFW);
    CWnVx3UOR(zofykHKh?"PUSH":"", aADK8XR(HB_T1jBCLdNzN)->vO1m9d.mrgekw0xj);
    if( zofykHKh){
      CZswHrqPXTX->FxctWLg1rBXzM = qN9HuWCx;
    }
    SCY6(HB_T1jBCLdNzN, qN9HuWCx, -1, -1, 0, 0);
  }
  return JPWY;
}

/*
** Pop the EXPLAIN QUERY PLAN stack one level.
*/
void XFFpzo1GZ1(MSufNwYJMUIW *CZswHrqPXTX){
  CWnVx3UOR("POP", 0);
  CZswHrqPXTX->FxctWLg1rBXzM = Ulf3YcQW(CZswHrqPXTX);
}
#endif /* SQLITE_OMIT_EXPLAIN */

/*
** Add an OP_ParseSchema opcode.  This routine is broken out from
** sqlite3VdbeAddOp4() since it needs to also needs to mark all btrees
** as having been used.
**
** The zWhere string must have been obtained from sqlite3_malloc().
** This routine will take ownership of the allocated memory.
*/
void ZucyK_ivuau2(Y4zzrBxD4OXTO *RWdNEx2WUIO8x, int S0HsMPysOKx, char *q2YrnkbmyI, k1VeKpK I4yL){
  int fg6dGr;
  gQe9mLCRpdMr0(RWdNEx2WUIO8x, ERXzWEi3X, S0HsMPysOKx, 0, 0, q2YrnkbmyI, fWFW);
  WKe_X9SULH(RWdNEx2WUIO8x, I4yL);
  for(fg6dGr=0; fg6dGr<RWdNEx2WUIO8x->pLMJg2Xd->rAyJ; fg6dGr++) Tm1i9hlV8(RWdNEx2WUIO8x, fg6dGr);
  y1ze2(RWdNEx2WUIO8x->CZswHrqPXTX);
}

/* Insert the end of a co-routine
*/
void YvahPgZcg(Y4zzrBxD4OXTO *HB_T1jBCLdNzN, int KlS8Ca){
  xTgHCTr(HB_T1jBCLdNzN, QMHRIEI, KlS8Ca);

  /* Clear the temporary register cache, thereby ensuring that each
  ** co-routine has its own independent set of registers, because co-routines
  ** might expect their registers to be preserved across an OP_Yield, and
  ** that could cause problems if two or more co-routines are using the same
  ** temporary register.
  */
  HB_T1jBCLdNzN->CZswHrqPXTX->HQVQuUYCg = 0;
  HB_T1jBCLdNzN->CZswHrqPXTX->R6KIJ1 = 0;
}

/*
** Create a new symbolic label for an instruction that has yet to be
** coded.  The symbolic label is really just a negative number.  The
** label can be used as the P2 value of an operation.  Later, when
** the label is resolved to a specific address, the VDBE will scan
** through its operation list and change all values of P2 which match
** the label into the resolved address.
**
** The VDBE knows that a P2 value is a label because labels are
** always negative and P2 values are suppose to be non-negative.
** Hence, a negative P2 value is a label that has yet to be resolved.
** (Later:) This is only true for opcodes that have the OPFLG_JUMP
** property.
**
** Variable usage notes:
**
**     Parse.aLabel[x]     Stores the address that the x-th label resolves
**                         into.  For testing (SQLITE_DEBUG), unresolved
**                         labels stores -1, but that is not required.
**     Parse.nLabelAlloc   Number of slots allocated to Parse.aLabel[]
**     Parse.nLabel        The *negative* of the number of labels that have
**                         been issued.  The negative is stored because
**                         that gives a performance improvement over storing
**                         the equivalent positive value.
*/
int K6i4lsCHxbDIe(MSufNwYJMUIW *CZswHrqPXTX){
  return --CZswHrqPXTX->SMlQQFbV;
}

/*
** Resolve label "x" to be the address of the next instruction to
** be inserted.  The parameter "x" must have been obtained from
** a prior call to sqlite3VdbeMakeLabel().
*/
static XmVnyUQh void U0dsxbc5OovCS(MSufNwYJMUIW *RWdNEx2WUIO8x, Y4zzrBxD4OXTO *HB_T1jBCLdNzN, int fg6dGr){
  int YuB1EM8o = 10 - RWdNEx2WUIO8x->SMlQQFbV;
  RWdNEx2WUIO8x->sQYt2 = AhaGmR(RWdNEx2WUIO8x->pLMJg2Xd, RWdNEx2WUIO8x->sQYt2,
                     YuB1EM8o*sizeof(RWdNEx2WUIO8x->sQYt2[0]));
  if( RWdNEx2WUIO8x->sQYt2==0 ){
    RWdNEx2WUIO8x->eUn7HSS = 0;
  }else{
#ifdef iteB65TL5L
    int Pyy0l6xD;
    for(Pyy0l6xD=RWdNEx2WUIO8x->eUn7HSS; Pyy0l6xD<YuB1EM8o; Pyy0l6xD++) RWdNEx2WUIO8x->sQYt2[Pyy0l6xD] = -1;
#endif
    if( YuB1EM8o>=100 && (YuB1EM8o/100)>(RWdNEx2WUIO8x->eUn7HSS/100) ){
      An7qVj24L0x(RWdNEx2WUIO8x);
    }
    RWdNEx2WUIO8x->eUn7HSS = YuB1EM8o;
    RWdNEx2WUIO8x->sQYt2[fg6dGr] = HB_T1jBCLdNzN->rtaUFjmY;
  }
}
void fZQREYli9T(Y4zzrBxD4OXTO *HB_T1jBCLdNzN, int zCVq){
  MSufNwYJMUIW *RWdNEx2WUIO8x = HB_T1jBCLdNzN->CZswHrqPXTX;
  int fg6dGr = O2sY(zCVq);
  f5IeCeK0e1W( HB_T1jBCLdNzN->C19t==w_rp1wwh );
  f5IeCeK0e1W( fg6dGr<-RWdNEx2WUIO8x->SMlQQFbV );
  f5IeCeK0e1W( fg6dGr>=0 );
#ifdef iteB65TL5L
  if( RWdNEx2WUIO8x->pLMJg2Xd->MRNoo5HiPBk7 & Gc4yIjlq ){
    FNEgs("RESOLVE LABEL %d to %d\n", zCVq, HB_T1jBCLdNzN->rtaUFjmY);
  }
#endif
  if( RWdNEx2WUIO8x->eUn7HSS + RWdNEx2WUIO8x->SMlQQFbV < 0 ){
    U0dsxbc5OovCS(RWdNEx2WUIO8x,HB_T1jBCLdNzN,fg6dGr);
  }else{
    f5IeCeK0e1W( RWdNEx2WUIO8x->sQYt2[fg6dGr]==(-1) ); /* Labels may only be resolved once */
    RWdNEx2WUIO8x->sQYt2[fg6dGr] = HB_T1jBCLdNzN->rtaUFjmY;
  }
}

/*
** Mark the VDBE as one that can only be run one time.
*/
void h3jLw(Y4zzrBxD4OXTO *RWdNEx2WUIO8x){
  dwg4lJSc(RWdNEx2WUIO8x, Na3OpJft8OQ, 1, 1);
}

/*
** Mark the VDBE as one that can be run multiple times.
*/
void HmHQbQeB(Y4zzrBxD4OXTO *RWdNEx2WUIO8x){
  int Pyy0l6xD;
  for(Pyy0l6xD=1; GVDI(Pyy0l6xD<RWdNEx2WUIO8x->rtaUFjmY); Pyy0l6xD++){
    if( GVDI(RWdNEx2WUIO8x->V7Y0VHDmd1Xf[Pyy0l6xD].KMcyPZbh==Na3OpJft8OQ) ){
      RWdNEx2WUIO8x->V7Y0VHDmd1Xf[1].KMcyPZbh = bMgvT4hVOBV;
      break;
    }
  }
}

#ifdef iteB65TL5L /* sqlite3AssertMayAbort() logic */

/*
** The following type and function are used to iterate through all opcodes
** in a Vdbe main program and each of the sub-programs (triggers) it may
** invoke directly or indirectly. It should be used as follows:
**
**   Op *pOp;
**   VdbeOpIter sIter;
**
**   memset(&sIter, 0, sizeof(sIter));
**   sIter.v = v;                            // v is of type Vdbe*
**   while( (pOp = opIterNext(&sIter)) ){
**     // Do something with pOp
**   }
**   sqlite3DbFree(v->db, sIter.apSub);
**
*/
typedef struct pV73n4SyWyqY pV73n4SyWyqY;
struct pV73n4SyWyqY {
  Y4zzrBxD4OXTO *HB_T1jBCLdNzN;                   /* Vdbe to iterate through the opcodes of */
  RnzBAc3QE **HOlrZBYT5UB;        /* Array of subprograms */
  int DQQwikf4SSVd5;                  /* Number of entries in apSub */
  int XDkNrt1dS1Dt;                 /* Address of next instruction to return */
  int MjoKlbIHa;                  /* 0 = main program, 1 = first sub-program etc. */
};
static mHYCosji8c *T8qLKusw(pV73n4SyWyqY *RWdNEx2WUIO8x){
  Y4zzrBxD4OXTO *HB_T1jBCLdNzN = RWdNEx2WUIO8x->HB_T1jBCLdNzN;
  mHYCosji8c *FC4wG28Zic072 = 0;
  mHYCosji8c *V7Y0VHDmd1Xf;
  int rtaUFjmY;

  if( RWdNEx2WUIO8x->MjoKlbIHa<=RWdNEx2WUIO8x->DQQwikf4SSVd5 ){

    if( RWdNEx2WUIO8x->MjoKlbIHa==0 ){
      V7Y0VHDmd1Xf = HB_T1jBCLdNzN->V7Y0VHDmd1Xf;
      rtaUFjmY = HB_T1jBCLdNzN->rtaUFjmY;
    }else{
      V7Y0VHDmd1Xf = RWdNEx2WUIO8x->HOlrZBYT5UB[RWdNEx2WUIO8x->MjoKlbIHa-1]->V7Y0VHDmd1Xf;
      rtaUFjmY = RWdNEx2WUIO8x->HOlrZBYT5UB[RWdNEx2WUIO8x->MjoKlbIHa-1]->rtaUFjmY;
    }
    f5IeCeK0e1W( RWdNEx2WUIO8x->XDkNrt1dS1Dt<rtaUFjmY );

    FC4wG28Zic072 = &V7Y0VHDmd1Xf[RWdNEx2WUIO8x->XDkNrt1dS1Dt];
    RWdNEx2WUIO8x->XDkNrt1dS1Dt++;
    if( RWdNEx2WUIO8x->XDkNrt1dS1Dt==rtaUFjmY ){
      RWdNEx2WUIO8x->MjoKlbIHa++;
      RWdNEx2WUIO8x->XDkNrt1dS1Dt = 0;
    }
 
    if( FC4wG28Zic072->ZP4P_QR4oE==JbYHBRv ){
      int jCneFxRQnw = (RWdNEx2WUIO8x->DQQwikf4SSVd5+1)*sizeof(RnzBAc3QE*);
      int fg6dGr;
      for(fg6dGr=0; fg6dGr<RWdNEx2WUIO8x->DQQwikf4SSVd5; fg6dGr++){
        if( RWdNEx2WUIO8x->HOlrZBYT5UB[fg6dGr]==FC4wG28Zic072->vO1m9d.IbbDoqgyL ) break;
      }
      if( fg6dGr==RWdNEx2WUIO8x->DQQwikf4SSVd5 ){
        RWdNEx2WUIO8x->HOlrZBYT5UB = AhaGmR(HB_T1jBCLdNzN->pLMJg2Xd, RWdNEx2WUIO8x->HOlrZBYT5UB, jCneFxRQnw);
        if( !RWdNEx2WUIO8x->HOlrZBYT5UB ){
          FC4wG28Zic072 = 0;
        }else{
          RWdNEx2WUIO8x->HOlrZBYT5UB[RWdNEx2WUIO8x->DQQwikf4SSVd5++] = FC4wG28Zic072->vO1m9d.IbbDoqgyL;
        }
      }
    }
  }

  return FC4wG28Zic072;
}

/*
** Check if the program stored in the VM associated with pParse may
** throw an ABORT exception (causing the statement, but not entire transaction
** to be rolled back). This condition is true if the main program or any
** sub-programs contains any of the following:
**
**   *  OP_Halt with P1=SQLITE_CONSTRAINT and P2=OE_Abort.
**   *  OP_HaltIfNull with P1=SQLITE_CONSTRAINT and P2=OE_Abort.
**   *  OP_Destroy
**   *  OP_VUpdate
**   *  OP_VCreate
**   *  OP_VRename
**   *  OP_FkCounter with P2==0 (immediate foreign key constraint)
**   *  OP_CreateBtree/BTREE_INTKEY and OP_InitCoroutine
**      (for CREATE TABLE AS SELECT ...)
**
** Then check that the value of Parse.mayAbort is true if an
** ABORT may be thrown, or false otherwise. Return true if it does
** match, or false otherwise. This function is intended to be used as
** part of an assert statement in the compiler. Similar to:
**
**   assert( sqlite3VdbeAssertMayAbort(pParse->pVdbe, pParse->mayAbort) );
*/
int iBFLcKvU(Y4zzrBxD4OXTO *HB_T1jBCLdNzN, int zOHH6Y096Svr1){
  int hdnO2K = 0;
  int pmbPuAsY2l = 0;
  int ZFMzWYkc = 0;
  int lRtwW9t_V = 0;
  int QyQSZl = 0;
  mHYCosji8c *BYPQ;
  pV73n4SyWyqY a920Ox;

  if( HB_T1jBCLdNzN==0 ) return 0;
  gDRc26rrZnG_(&a920Ox, 0, sizeof(a920Ox));
  a920Ox.HB_T1jBCLdNzN = HB_T1jBCLdNzN;

  while( (BYPQ = T8qLKusw(&a920Ox))!=0 ){
    int KMcyPZbh = BYPQ->KMcyPZbh;
    if( KMcyPZbh==EkPyfmUiClB || KMcyPZbh==WEhsd || KMcyPZbh==HTOsBy6_
     || KMcyPZbh==L2bVIRsNuEq
     || KMcyPZbh==U8uM0jwP0
     || KMcyPZbh==ERXzWEi3X
     || KMcyPZbh==Us7_agR || KMcyPZbh==s9LjXi53Xo
     || ((KMcyPZbh==dlzIE || KMcyPZbh==Sm10ME)
      && ((BYPQ->mB_5hYOV5K)!=odQX7vL && BYPQ->pPP2V5==wdf01))
    ){
      hdnO2K = 1;
      break;
    }
    if( KMcyPZbh==x90H7oukFbw && BYPQ->BTBDVdeO3P==k_dHgx13jr ) ZFMzWYkc = 1;
    if( zOHH6Y096Svr1 ){
      /* hasCreateIndex may also be set for some DELETE statements that use
      ** OP_Clear. So this routine may end up returning true in the case
      ** where a "DELETE FROM tbl" has a statement-journal but does not
      ** require one. This is not so bad - it is an inefficiency, not a bug. */
      if( KMcyPZbh==x90H7oukFbw && BYPQ->BTBDVdeO3P==icA5V9XTsNM8_ ) lRtwW9t_V = 1;
      if( KMcyPZbh==V8bFEc ) lRtwW9t_V = 1;
    }
    if( KMcyPZbh==dBaAOiNDck0 ) QyQSZl = 1;
#ifndef XRP4IAu
    if( KMcyPZbh==SA62ek && BYPQ->mB_5hYOV5K==0 && BYPQ->pPP2V5==1 ){
      pmbPuAsY2l = 1;
    }
#endif
  }
  UXHgfYQ(HB_T1jBCLdNzN->pLMJg2Xd, a920Ox.HOlrZBYT5UB);

  /* Return true if hasAbort==mayAbort. Or if a malloc failure occurred.
  ** If malloc failed, then the while() loop above may not have iterated
  ** through all opcodes and hasAbort may be set incorrectly. Return
  ** true for this case to prevent the assert() in the callers frame
  ** from failing.  */
  return ( HB_T1jBCLdNzN->pLMJg2Xd->mi4oOCmRVN_h || hdnO2K==zOHH6Y096Svr1 || pmbPuAsY2l
        || (ZFMzWYkc && QyQSZl) || lRtwW9t_V
  );
}
#endif /* SQLITE_DEBUG - the sqlite3AssertMayAbort() function */

#ifdef iteB65TL5L
/*
** Increment the nWrite counter in the VDBE if the cursor is not an
** ephemeral cursor, or if the cursor argument is NULL.
*/
void TCOb5jgI(Y4zzrBxD4OXTO *RWdNEx2WUIO8x, Jmdb *SEIR9fLw_9){
  if( SEIR9fLw_9==0
   || (SEIR9fLw_9->lhtEl9aC9MU!=SOgiV
       && SEIR9fLw_9->lhtEl9aC9MU!=iIh1
       && !SEIR9fLw_9->UB9gbhuKc)
  ){
    RWdNEx2WUIO8x->dbNLlMD9rkKX++;
  }
}
#endif

#ifdef iteB65TL5L
/*
** Assert if an Abort at this point in time might result in a corrupt
** database.
*/
void O2lcuCzxOsI4j(Y4zzrBxD4OXTO *RWdNEx2WUIO8x){
  f5IeCeK0e1W( RWdNEx2WUIO8x->dbNLlMD9rkKX==0 || RWdNEx2WUIO8x->Sw32GUoVJzP4 );
}
#endif

/*
** This routine is called after all opcodes have been inserted.  It loops
** through all the opcodes and fixes up some details.
**
** (1) For each jump instruction with a negative P2 value (a label)
**     resolve the P2 value to an actual address.
**
** (2) Compute the maximum number of arguments used by any SQL function
**     and store that value in *pMaxFuncArgs.
**
** (3) Update the Vdbe.readOnly and Vdbe.bIsReader flags to accurately
**     indicate what the prepared statement actually does.
**
** (4) (discontinued)
**
** (5) Reclaim the memory allocated for storing labels.
**
** This routine will only function correctly if the mkopcodeh.tcl generator
** script numbers the opcodes correctly.  Changes to this routine must be
** coordinated with changes to mkopcodeh.tcl.
*/
static void MDNdD1BZG5m_(Y4zzrBxD4OXTO *RWdNEx2WUIO8x, int *Rx6VyJjp){
  int qBoh = *Rx6VyJjp;
  mHYCosji8c *BYPQ;
  MSufNwYJMUIW *CZswHrqPXTX = RWdNEx2WUIO8x->CZswHrqPXTX;
  int *sQYt2 = CZswHrqPXTX->sQYt2;

  f5IeCeK0e1W( CZswHrqPXTX->pLMJg2Xd->mi4oOCmRVN_h==0 ); /* tag-20230419-1 */
  RWdNEx2WUIO8x->tdY9qH = 1;
  RWdNEx2WUIO8x->Ha4sUMJqgGECn = 0;
  BYPQ = &RWdNEx2WUIO8x->V7Y0VHDmd1Xf[RWdNEx2WUIO8x->rtaUFjmY-1];
  f5IeCeK0e1W( RWdNEx2WUIO8x->V7Y0VHDmd1Xf[0].KMcyPZbh==EXKa_CQA );
  while( 1 /* Loop terminates when it reaches the OP_Init opcode */ ){
    /* Only JUMP opcodes and the short list of special opcodes in the switch
    ** below need to be considered.  The mkopcodeh.tcl generator script groups
    ** all these opcodes together near the front of the opcode list.  Skip
    ** any opcode that does not need processing by virtual of the fact that
    ** it is larger than SQLITE_MX_JUMP_OPCODE, as a performance optimization.
    */
    if( BYPQ->KMcyPZbh<=blAsKT2 ){
      /* NOTE: Be sure to update mkopcodeh.tcl when adding or removing
      ** cases from this switch! */
      switch( BYPQ->KMcyPZbh ){
        case gctt_B0SsKQE: {
          if( BYPQ->pPP2V5!=0 ) RWdNEx2WUIO8x->tdY9qH = 0;
          /* no break */ qvwPzbDMHn9UZ
        }
        case VtX39qYe07Z:
        case RgiI9KtJ5I2: {
          RWdNEx2WUIO8x->Ha4sUMJqgGECn = 1;
          break;
        }
#ifndef YC5TwfZUG
        case jlxa:
#endif
        case TE3B7nZeTb7i:
        case RVpGqgJ: {
          RWdNEx2WUIO8x->tdY9qH = 0;
          RWdNEx2WUIO8x->Ha4sUMJqgGECn = 1;
          break;
        }
        case EXKa_CQA: {
          f5IeCeK0e1W( BYPQ->pPP2V5>=0 );
          goto vV2ScXqb6;
        }
#ifndef uRsBKByRR
        case WEhsd: {
          if( BYPQ->pPP2V5>qBoh ) qBoh = BYPQ->pPP2V5;
          break;
        }
        case i8Lw2nUxwEJ2: {
          int AS0ycVs;
          f5IeCeK0e1W( (BYPQ - RWdNEx2WUIO8x->V7Y0VHDmd1Xf) >= 3 );
          f5IeCeK0e1W( BYPQ[-1].KMcyPZbh==q3vXRMuAw8oEW );
          AS0ycVs = BYPQ[-1].mB_5hYOV5K;
          if( AS0ycVs>qBoh ) qBoh = AS0ycVs;
          /* Fall through into the default case */
          /* no break */ qvwPzbDMHn9UZ
        }
#endif
        default: {
          if( BYPQ->pPP2V5<0 ){
            /* The mkopcodeh.tcl script has so arranged things that the only
            ** non-jump opcodes less than SQLITE_MX_JUMP_CODE are guaranteed to
            ** have non-negative values for P2. */
            f5IeCeK0e1W( (BCRQ[BYPQ->KMcyPZbh] & axAu5Mv1_TQ)!=0 );
            f5IeCeK0e1W( O2sY(BYPQ->pPP2V5)<-CZswHrqPXTX->SMlQQFbV );
            f5IeCeK0e1W( sQYt2!=0 );  /* True because of tag-20230419-1 */
            BYPQ->pPP2V5 = sQYt2[O2sY(BYPQ->pPP2V5)];
          }

          /* OPFLG_JUMP opcodes never have P2==0, though OPFLG_JUMP0 opcodes
          ** might */
          f5IeCeK0e1W( BYPQ->pPP2V5>0 
                  || (BCRQ[BYPQ->KMcyPZbh] & SB_B0)!=0 );

          /* Jumps never go off the end of the bytecode array */
          f5IeCeK0e1W( BYPQ->pPP2V5<RWdNEx2WUIO8x->rtaUFjmY
                  || (BCRQ[BYPQ->KMcyPZbh] & axAu5Mv1_TQ)==0 );
          break;
        }
      }
      /* The mkopcodeh.tcl script has so arranged things that the only
      ** non-jump opcodes less than SQLITE_MX_JUMP_CODE are guaranteed to
      ** have non-negative values for P2. */
      f5IeCeK0e1W( (BCRQ[BYPQ->KMcyPZbh]&axAu5Mv1_TQ)==0 || BYPQ->pPP2V5>=0);
    }
    f5IeCeK0e1W( BYPQ>RWdNEx2WUIO8x->V7Y0VHDmd1Xf );   
    BYPQ--;
  }
vV2ScXqb6:
  if( sQYt2 ){
    CTQ2V30yU(RWdNEx2WUIO8x->pLMJg2Xd, CZswHrqPXTX->sQYt2);
    CZswHrqPXTX->sQYt2 = 0;
  }
  CZswHrqPXTX->SMlQQFbV = 0;
  *Rx6VyJjp = qBoh;
  f5IeCeK0e1W( RWdNEx2WUIO8x->Ha4sUMJqgGECn!=0 || kgp4z0VrkC(RWdNEx2WUIO8x->tP8VR_wprd) );
}

#ifdef iteB65TL5L
/*
** Check to see if a subroutine contains a jump to a location outside of
** the subroutine.  If a jump outside the subroutine is detected, add code
** that will cause the program to halt with an error message.
**
** The subroutine consists of opcodes between iFirst and iLast.  Jumps to
** locations within the subroutine are acceptable.  iRetReg is a register
** that contains the return address.  Jumps to outside the range of iFirst
** through iLast are also acceptable as long as the jump destination is
** an OP_Return to iReturnAddr.
**
** A jump to an unresolved label means that the jump destination will be
** beyond the current address.  That is normally a jump to an early
** termination and is consider acceptable.
**
** This routine only runs during debug builds.  The purpose is (of course)
** to detect invalid escapes out of a subroutine.  The OP_Halt opcode
** is generated rather than an assert() or other error, so that ".eqp full"
** will still work to show the original bytecode, to aid in debugging.
*/
void AfRNUS62p(
  Y4zzrBxD4OXTO *HB_T1jBCLdNzN,          /* The byte-code program under construction */
  int GsmpQ,       /* First opcode of the subroutine */
  int hEACrZpwGsF99,        /* Last opcode of the subroutine */
  int ex0FuTS       /* Subroutine return address register */
){
  kqPOQZYA16d *BYPQ;
  MSufNwYJMUIW *CZswHrqPXTX;
  int Pyy0l6xD;
  xteu3Vbffih *voaowtTVI = 0;
  f5IeCeK0e1W( HB_T1jBCLdNzN!=0 );
  CZswHrqPXTX = HB_T1jBCLdNzN->CZswHrqPXTX;
  f5IeCeK0e1W( CZswHrqPXTX!=0 );
  if( CZswHrqPXTX->yewcXFREO ) return;
  f5IeCeK0e1W( hEACrZpwGsF99>=GsmpQ );
  f5IeCeK0e1W( hEACrZpwGsF99<HB_T1jBCLdNzN->rtaUFjmY );
  BYPQ = &HB_T1jBCLdNzN->V7Y0VHDmd1Xf[GsmpQ];
  for(Pyy0l6xD=GsmpQ; Pyy0l6xD<=hEACrZpwGsF99; Pyy0l6xD++, BYPQ++){
    if( (BCRQ[BYPQ->KMcyPZbh] & axAu5Mv1_TQ)!=0 ){
      int dozV_ncZ_Yd = BYPQ->pPP2V5;   /* Jump destination */
      if( dozV_ncZ_Yd==0 ) continue;
      if( BYPQ->KMcyPZbh==QSv2P5Y ) continue;
      if( BYPQ->BTBDVdeO3P==20230325 && BYPQ->KMcyPZbh==XJ_uFz ){
        /* This is a deliberately taken illegal branch.  tag-20230325-2 */
        continue;
      }
      if( dozV_ncZ_Yd<0 ){
        int fg6dGr = O2sY(dozV_ncZ_Yd);
        f5IeCeK0e1W( fg6dGr>=0 );
        if( fg6dGr>=-CZswHrqPXTX->SMlQQFbV || CZswHrqPXTX->sQYt2[fg6dGr]<0 ){
          continue;
        }
        dozV_ncZ_Yd = CZswHrqPXTX->sQYt2[fg6dGr];
      }
      if( dozV_ncZ_Yd<GsmpQ || dozV_ncZ_Yd>hEACrZpwGsF99 ){
        int fg6dGr = dozV_ncZ_Yd;
        for(; fg6dGr<HB_T1jBCLdNzN->rtaUFjmY; fg6dGr++){
          kqPOQZYA16d *Mu1mdpP = &HB_T1jBCLdNzN->V7Y0VHDmd1Xf[fg6dGr];
          if( Mu1mdpP->KMcyPZbh==FRbHY5wYd ){
            if( Mu1mdpP->mB_5hYOV5K==ex0FuTS ) break;
            continue;
          }
          if( Mu1mdpP->KMcyPZbh==bMgvT4hVOBV ) continue;
          if( Mu1mdpP->KMcyPZbh==WLqXtjk5Ez ) continue;
          if( voaowtTVI==0 ){
            voaowtTVI = D9zBWR1(0);
          }else{
            ovRYXDh(voaowtTVI, 1, '\n');
          }
          xsxqlh10JTjYJ(voaowtTVI,
              "Opcode at %d jumps to %d which is outside the "
              "subroutine at %d..%d",
              Pyy0l6xD, dozV_ncZ_Yd, GsmpQ, hEACrZpwGsF99);
          break;
        }
      }
    }
  }
  if( voaowtTVI ){
    char *rVCpze_yXWrC = uGiwLMchJRm(voaowtTVI);
    gQe9mLCRpdMr0(HB_T1jBCLdNzN, dlzIE, NVcfo, wdf01, 0, rVCpze_yXWrC, 0);
    CMhAT(rVCpze_yXWrC);
    y1ze2(CZswHrqPXTX);
  }
}
#endif /* SQLITE_DEBUG */

/*
** Return the address of the next instruction to be inserted.
*/
int crHZR55(Y4zzrBxD4OXTO *RWdNEx2WUIO8x){
  f5IeCeK0e1W( RWdNEx2WUIO8x->C19t==w_rp1wwh );
  return RWdNEx2WUIO8x->rtaUFjmY;
}

/*
** Verify that at least N opcode slots are available in p without
** having to malloc for more space (except when compiled using
** SQLITE_TEST_REALLOC_STRESS).  This interface is used during testing
** to verify that certain calls to sqlite3VdbeAddOpList() can never
** fail due to a OOM fault and hence that the return value from
** sqlite3VdbeAddOpList() will always be non-NULL.
*/
#if pZX7GD4OTcuV(iteB65TL5L) && !pZX7GD4OTcuV(mJe7)
void LKcZiTvMFQg7k(Y4zzrBxD4OXTO *RWdNEx2WUIO8x, int YLqByqgGKPr){
  f5IeCeK0e1W( RWdNEx2WUIO8x->rtaUFjmY + YLqByqgGKPr <= RWdNEx2WUIO8x->crK7AlNP_f6 );
}
#endif

/*
** Verify that the VM passed as the only argument does not contain
** an OP_ResultRow opcode. Fail an assert() if it does. This is used
** by code in pragma.c to ensure that the implementation of certain
** pragmas comports with the flags specified in the mkpragmatab.tcl
** script.
*/
#if pZX7GD4OTcuV(iteB65TL5L) && !pZX7GD4OTcuV(mJe7)
void dAMfr(Y4zzrBxD4OXTO *RWdNEx2WUIO8x){
  int Pyy0l6xD;
  for(Pyy0l6xD=0; Pyy0l6xD<RWdNEx2WUIO8x->rtaUFjmY; Pyy0l6xD++){
    f5IeCeK0e1W( RWdNEx2WUIO8x->V7Y0VHDmd1Xf[Pyy0l6xD].KMcyPZbh!=yfSB6_a );
  }
}
#endif

/*
** Generate code (a single OP_Abortable opcode) that will
** verify that the VDBE program can safely call Abort in the current
** context.
*/
#if pZX7GD4OTcuV(iteB65TL5L)
void Y2TYdv0LHnG1_(Y4zzrBxD4OXTO *RWdNEx2WUIO8x, int lcI9GP){
  if( lcI9GP==wdf01 ) Ku8cbll7CJ6HU(RWdNEx2WUIO8x, CA_ZYtWniZTu);
}
#endif

/*
** This function returns a pointer to the array of opcodes associated with
** the Vdbe passed as the first argument. It is the callers responsibility
** to arrange for the returned array to be eventually freed using the
** vdbeFreeOpArray() function.
**
** Before returning, *pnOp is set to the number of entries in the returned
** array. Also, *pnMaxArg is set to the larger of its current value and
** the number of entries in the Vdbe.apArg[] array required to execute the
** returned program.
*/
kqPOQZYA16d *seWy(Y4zzrBxD4OXTO *RWdNEx2WUIO8x, int *ANN45feXV, int *Zycjahg){
  kqPOQZYA16d *V7Y0VHDmd1Xf = RWdNEx2WUIO8x->V7Y0VHDmd1Xf;
  f5IeCeK0e1W( V7Y0VHDmd1Xf && !RWdNEx2WUIO8x->pLMJg2Xd->mi4oOCmRVN_h );

  /* Check that sqlite3VdbeUsesBtree() was not called on this VM */
  f5IeCeK0e1W( kgp4z0VrkC(RWdNEx2WUIO8x->tP8VR_wprd) );

  MDNdD1BZG5m_(RWdNEx2WUIO8x, Zycjahg);
  *ANN45feXV = RWdNEx2WUIO8x->rtaUFjmY;
  RWdNEx2WUIO8x->V7Y0VHDmd1Xf = 0;
  return V7Y0VHDmd1Xf;
}

/*
** Add a whole list of operations to the operation stack.  Return a
** pointer to the first operation inserted.
**
** Non-zero P2 arguments to jump instructions are automatically adjusted
** so that the jump target is relative to the first operation inserted.
*/
kqPOQZYA16d *CnAKwNJwsAjE(
  Y4zzrBxD4OXTO *RWdNEx2WUIO8x,                     /* Add opcodes to the prepared statement */
  int rtaUFjmY,                     /* Number of opcodes to add */
  xOrTrnaBPwmr const *V7Y0VHDmd1Xf,       /* The opcodes to be added */
  int JoRRjN55ia                  /* Source-file line number of first opcode */
){
  int Pyy0l6xD;
  kqPOQZYA16d *IBMjGt5hp, *aWgKA_B8va;
  f5IeCeK0e1W( rtaUFjmY>0 );
  f5IeCeK0e1W( RWdNEx2WUIO8x->C19t==w_rp1wwh );
  if( RWdNEx2WUIO8x->rtaUFjmY + rtaUFjmY > RWdNEx2WUIO8x->crK7AlNP_f6 && fXw2urqqeI4(RWdNEx2WUIO8x, rtaUFjmY) ){
    return 0;
  }
  aWgKA_B8va = IBMjGt5hp = &RWdNEx2WUIO8x->V7Y0VHDmd1Xf[RWdNEx2WUIO8x->rtaUFjmY];
  for(Pyy0l6xD=0; Pyy0l6xD<rtaUFjmY; Pyy0l6xD++, V7Y0VHDmd1Xf++, IBMjGt5hp++){
    IBMjGt5hp->KMcyPZbh = V7Y0VHDmd1Xf->KMcyPZbh;
    IBMjGt5hp->mB_5hYOV5K = V7Y0VHDmd1Xf->mB_5hYOV5K;
    IBMjGt5hp->pPP2V5 = V7Y0VHDmd1Xf->pPP2V5;
    f5IeCeK0e1W( V7Y0VHDmd1Xf->pPP2V5>=0 );
    if( (BCRQ[V7Y0VHDmd1Xf->KMcyPZbh] & axAu5Mv1_TQ)!=0 && V7Y0VHDmd1Xf->pPP2V5>0 ){
      IBMjGt5hp->pPP2V5 += RWdNEx2WUIO8x->rtaUFjmY;
    }
    IBMjGt5hp->BTBDVdeO3P = V7Y0VHDmd1Xf->BTBDVdeO3P;
    IBMjGt5hp->ZP4P_QR4oE = bcIYtAfjheQ;
    IBMjGt5hp->vO1m9d.RWdNEx2WUIO8x = 0;
    IBMjGt5hp->I4yL = 0;
#ifdef faD_O9XSX
    IBMjGt5hp->PihbEOgZ = 0;
#endif
#ifdef xGeFUI6
    IBMjGt5hp->BzSu7o = JoRRjN55ia+Pyy0l6xD;
#else
    (void)JoRRjN55ia;
#endif
#ifdef iteB65TL5L
    if( RWdNEx2WUIO8x->pLMJg2Xd->MRNoo5HiPBk7 & Gc4yIjlq ){
      QA1Dfk_5egTE9(0, Pyy0l6xD+RWdNEx2WUIO8x->rtaUFjmY, &RWdNEx2WUIO8x->V7Y0VHDmd1Xf[Pyy0l6xD+RWdNEx2WUIO8x->rtaUFjmY]);
    }
#endif
  }
  RWdNEx2WUIO8x->rtaUFjmY += rtaUFjmY;
  return aWgKA_B8va;
}

#if pZX7GD4OTcuV(ghoW)
/*
** Add an entry to the array of counters managed by sqlite3_stmt_scanstatus().
*/
void SCY6(
  Y4zzrBxD4OXTO *RWdNEx2WUIO8x,                        /* VM to add scanstatus() to */
  int FxctWLg1rBXzM,                /* Address of OP_Explain (or 0) */
  int KUEo2Hh7qsJ,                   /* Address of loop counter */
  int a33FX8wM,                  /* Address of rows visited counter */
  DQQDEBCzoKT jmYBz_p,                    /* Estimated number of output rows */
  const char *wxojaeqHwik               /* Name of table or index being scanned */
){
  if( dSqqw(RWdNEx2WUIO8x->pLMJg2Xd) ){
    OfeosV3WSPC jCneFxRQnw = (RWdNEx2WUIO8x->UWhyJpoUVsV+1) * sizeof(wPLmC9NeqM);
    wPLmC9NeqM *epSqE;
    epSqE = (wPLmC9NeqM*)nhUctWhr(RWdNEx2WUIO8x->pLMJg2Xd, RWdNEx2WUIO8x->DGFG4az, jCneFxRQnw);
    if( epSqE ){
      wPLmC9NeqM *UdjreBdSSGOa = &epSqE[RWdNEx2WUIO8x->UWhyJpoUVsV++];
      gDRc26rrZnG_(UdjreBdSSGOa, 0, sizeof(wPLmC9NeqM));
      UdjreBdSSGOa->FxctWLg1rBXzM = FxctWLg1rBXzM;
      UdjreBdSSGOa->KUEo2Hh7qsJ = KUEo2Hh7qsJ;
      UdjreBdSSGOa->a33FX8wM = a33FX8wM;
      UdjreBdSSGOa->jmYBz_p = jmYBz_p;
      UdjreBdSSGOa->wxojaeqHwik = FmfCMc4yu8(RWdNEx2WUIO8x->pLMJg2Xd, wxojaeqHwik);
      RWdNEx2WUIO8x->DGFG4az = epSqE;
    }
  }
}

/*
** Add the range of instructions from addrStart to addrEnd (inclusive) to
** the set of those corresponding to the sqlite3_stmt_scanstatus() counters
** associated with the OP_Explain instruction at addrExplain. The
** sum of the sqlite3Hwtime() values for each of these instructions
** will be returned for SQLITE_SCANSTAT_NCYCLE requests.
*/
void cKwsUrZ(
  Y4zzrBxD4OXTO *RWdNEx2WUIO8x,
  int FxctWLg1rBXzM,
  int uZW_tUYaD5jA,
  int oQbr6KiUWAE
){
  if( dSqqw(RWdNEx2WUIO8x->pLMJg2Xd) ){
    wPLmC9NeqM *KZaW2Zs1qH = 0;
    int Fofiz5Dmlfsbf;
    for(Fofiz5Dmlfsbf=RWdNEx2WUIO8x->UWhyJpoUVsV-1; Fofiz5Dmlfsbf>=0; Fofiz5Dmlfsbf--){
      KZaW2Zs1qH = &RWdNEx2WUIO8x->DGFG4az[Fofiz5Dmlfsbf];
      if( KZaW2Zs1qH->FxctWLg1rBXzM==FxctWLg1rBXzM ) break;
      KZaW2Zs1qH = 0;
    }
    if( KZaW2Zs1qH ){
      if( oQbr6KiUWAE<0 ) oQbr6KiUWAE = crHZR55(RWdNEx2WUIO8x)-1;
      for(Fofiz5Dmlfsbf=0; Fofiz5Dmlfsbf<fnUxVZQFAvJ3S(KZaW2Zs1qH->AReWsrphXi); Fofiz5Dmlfsbf+=2){
        if( KZaW2Zs1qH->AReWsrphXi[Fofiz5Dmlfsbf]==0 ){
          KZaW2Zs1qH->AReWsrphXi[Fofiz5Dmlfsbf] = uZW_tUYaD5jA;
          KZaW2Zs1qH->AReWsrphXi[Fofiz5Dmlfsbf+1] = oQbr6KiUWAE;
          break;
        }
      }
    }
  }
}

/*
** Set the addresses for the SQLITE_SCANSTAT_NLOOP and SQLITE_SCANSTAT_NROW
** counters for the query element associated with the OP_Explain at
** addrExplain.
*/
void ENAQ_(
  Y4zzrBxD4OXTO *RWdNEx2WUIO8x,
  int FxctWLg1rBXzM,
  int KUEo2Hh7qsJ,
  int a33FX8wM
){
  if( dSqqw(RWdNEx2WUIO8x->pLMJg2Xd) ){
    wPLmC9NeqM *KZaW2Zs1qH = 0;
    int Fofiz5Dmlfsbf;
    for(Fofiz5Dmlfsbf=RWdNEx2WUIO8x->UWhyJpoUVsV-1; Fofiz5Dmlfsbf>=0; Fofiz5Dmlfsbf--){
      KZaW2Zs1qH = &RWdNEx2WUIO8x->DGFG4az[Fofiz5Dmlfsbf];
      if( KZaW2Zs1qH->FxctWLg1rBXzM==FxctWLg1rBXzM ) break;
      KZaW2Zs1qH = 0;
    }
    if( KZaW2Zs1qH ){
      if( KUEo2Hh7qsJ>0 ) KZaW2Zs1qH->KUEo2Hh7qsJ = KUEo2Hh7qsJ;
      if( a33FX8wM>0 ) KZaW2Zs1qH->a33FX8wM = a33FX8wM;
    }
  }
}
#endif /* defined(SQLITE_ENABLE_STMT_SCANSTATUS) */


/*
** Change the value of the opcode, or P1, P2, P3, or P5 operands
** for a specific instruction.
*/
void hBfEWb59G7T(Y4zzrBxD4OXTO *RWdNEx2WUIO8x, int JPWY, qHh5JW LwqOgMYq85er){
  f5IeCeK0e1W( JPWY>=0 );
  lz2h(RWdNEx2WUIO8x,JPWY)->KMcyPZbh = LwqOgMYq85er;
}
void LNu0(Y4zzrBxD4OXTO *RWdNEx2WUIO8x, int JPWY, int gjqIvJ2MxdYg){
  f5IeCeK0e1W( JPWY>=0 );
  lz2h(RWdNEx2WUIO8x,JPWY)->mB_5hYOV5K = gjqIvJ2MxdYg;
}
void gC9Q8wR(Y4zzrBxD4OXTO *RWdNEx2WUIO8x, int JPWY, int gjqIvJ2MxdYg){
  f5IeCeK0e1W( JPWY>=0 || RWdNEx2WUIO8x->pLMJg2Xd->mi4oOCmRVN_h );
  lz2h(RWdNEx2WUIO8x,JPWY)->pPP2V5 = gjqIvJ2MxdYg;
}
void BgaPFT(Y4zzrBxD4OXTO *RWdNEx2WUIO8x, int JPWY, int gjqIvJ2MxdYg){
  f5IeCeK0e1W( JPWY>=0 );
  lz2h(RWdNEx2WUIO8x,JPWY)->BTBDVdeO3P = gjqIvJ2MxdYg;
}
void WKe_X9SULH(Y4zzrBxD4OXTO *RWdNEx2WUIO8x, k1VeKpK I4yL){
  f5IeCeK0e1W( RWdNEx2WUIO8x->rtaUFjmY>0 || RWdNEx2WUIO8x->pLMJg2Xd->mi4oOCmRVN_h );
  if( RWdNEx2WUIO8x->rtaUFjmY>0 ) RWdNEx2WUIO8x->V7Y0VHDmd1Xf[RWdNEx2WUIO8x->rtaUFjmY-1].I4yL = I4yL;
}

/*
** If the previous opcode is an OP_Column that delivers results
** into register iDest, then add the OPFLAG_TYPEOFARG flag to that
** opcode.
*/
void JQY8ojwerzN(Y4zzrBxD4OXTO *RWdNEx2WUIO8x, int dozV_ncZ_Yd){
  kqPOQZYA16d *BYPQ = aADK8XR(RWdNEx2WUIO8x);
  if( BYPQ->BTBDVdeO3P==dozV_ncZ_Yd && BYPQ->KMcyPZbh==b2JP ){
    BYPQ->I4yL |= XVIZ7;
  }
}

/*
** Change the P2 operand of instruction addr so that it points to
** the address of the next instruction to be coded.
*/
void B3sq2sFtb(Y4zzrBxD4OXTO *RWdNEx2WUIO8x, int JPWY){
  gC9Q8wR(RWdNEx2WUIO8x, JPWY, RWdNEx2WUIO8x->rtaUFjmY);
}

/*
** Change the P2 operand of the jump instruction at addr so that
** the jump lands on the next opcode.  Or if the jump instruction was
** the previous opcode (and is thus a no-op) then simply back up
** the next instruction counter by one slot so that the jump is
** overwritten by the next inserted opcode.
**
** This routine is an optimization of sqlite3VdbeJumpHere() that
** strives to omit useless byte-code like this:
**
**        7   Once 0 8 0
**        8   ...
*/
void g5pw(Y4zzrBxD4OXTO *RWdNEx2WUIO8x, int JPWY){
  if( JPWY==RWdNEx2WUIO8x->rtaUFjmY-1 ){
    f5IeCeK0e1W( RWdNEx2WUIO8x->V7Y0VHDmd1Xf[JPWY].KMcyPZbh==jCz4W3ao3Xa0H
         || RWdNEx2WUIO8x->V7Y0VHDmd1Xf[JPWY].KMcyPZbh==PkqMkKPn_nAn
         || RWdNEx2WUIO8x->V7Y0VHDmd1Xf[JPWY].KMcyPZbh==KkpUT3 );
    f5IeCeK0e1W( RWdNEx2WUIO8x->V7Y0VHDmd1Xf[JPWY].ZP4P_QR4oE==0 );
#ifdef xGeFUI6
    aADK8XR(RWdNEx2WUIO8x)->BzSu7o = 0;  /* Erase VdbeCoverage() macros */
#endif
    RWdNEx2WUIO8x->rtaUFjmY--;
  }else{
    gC9Q8wR(RWdNEx2WUIO8x, JPWY, RWdNEx2WUIO8x->rtaUFjmY);
  }
}


/*
** If the input FuncDef structure is ephemeral, then free it.  If
** the FuncDef is not ephemeral, then do nothing.
*/
static void J9kIPsaPv(MEeQFpE4DzbZ *pLMJg2Xd, r_0_hpT *vPar9lD){
  f5IeCeK0e1W( pLMJg2Xd!=0 );
  if( (vPar9lD->TPP6ZDZCV & wATsn35w_)!=0 ){
    CTQ2V30yU(pLMJg2Xd, vPar9lD);
  }
}

/*
** Delete a P4 value if necessary.
*/
static XmVnyUQh void HWJee_pld3m9s(MEeQFpE4DzbZ *pLMJg2Xd, oi4q2s5KcMX9Y *RWdNEx2WUIO8x){
  if( RWdNEx2WUIO8x->N3A21Ra4MY24m ) UXHgfYQ(pLMJg2Xd, RWdNEx2WUIO8x->DH15);
  CTQ2V30yU(pLMJg2Xd, RWdNEx2WUIO8x);
}
static XmVnyUQh void gixvrAignn(MEeQFpE4DzbZ *pLMJg2Xd, DWQQ4Hi8 *RWdNEx2WUIO8x){
  f5IeCeK0e1W( pLMJg2Xd!=0 );
  J9kIPsaPv(pLMJg2Xd, RWdNEx2WUIO8x->pOpnI3oMVnGn);
  CTQ2V30yU(pLMJg2Xd, RWdNEx2WUIO8x);
}
static void Yqs3Ss02pZV(MEeQFpE4DzbZ *pLMJg2Xd, int ZP4P_QR4oE, void *vO1m9d){
  f5IeCeK0e1W( pLMJg2Xd );
  switch( ZP4P_QR4oE ){
    case H5QvOmDMVC1Eh: {
      gixvrAignn(pLMJg2Xd, (DWQQ4Hi8*)vO1m9d);
      break;
    }
    case H0OpYaT8P:
    case PuWoCY:
    case fWFW:
    case pc36yfwL: {
      if( vO1m9d ) CTQ2V30yU(pLMJg2Xd, vO1m9d);
      break;
    }
    case OALG4pjXX: {
      if( pLMJg2Xd->mMBxdHckzgHIl==0 ) nQg0oG((Yen3v7sHJ_Gb*)vO1m9d);
      break;
    }
#ifdef DWSSZmoaM
    case LS2RGg: {
      vVYRCGHrz(pLMJg2Xd, (n29LzVguZ6CV*)vO1m9d);
      break;
    }
#endif
    case fWjT: {
      J9kIPsaPv(pLMJg2Xd, (r_0_hpT*)vO1m9d);
      break;
    }
    case FrqQiM: {
      if( pLMJg2Xd->mMBxdHckzgHIl==0 ){
        hcEpW1hxga0R((EPdZvOoD0Wseb*)vO1m9d);
      }else{
        HWJee_pld3m9s(pLMJg2Xd, (oi4q2s5KcMX9Y*)vO1m9d);
      }
      break;
    }
    case PtQbWJ7b6 : {
      if( pLMJg2Xd->mMBxdHckzgHIl==0 ) onpNpe6EufhP((szc_QE2VngTx *)vO1m9d);
      break;
    }
    case t3ZeSJEtTMB: {
      if( pLMJg2Xd->mMBxdHckzgHIl==0 ) lqGzbT(pLMJg2Xd, (rMWp94Q*)vO1m9d);
      break;
    }
  }
}

/*
** Free the space allocated for aOp and any p4 values allocated for the
** opcodes contained within. If aOp is not NULL it is assumed to contain
** nOp entries.
*/
static void hOukOg4s95gVn(MEeQFpE4DzbZ *pLMJg2Xd, mHYCosji8c *V7Y0VHDmd1Xf, int rtaUFjmY){
  f5IeCeK0e1W( rtaUFjmY>=0 );
  f5IeCeK0e1W( pLMJg2Xd!=0 );
  if( V7Y0VHDmd1Xf ){
    mHYCosji8c *BYPQ = &V7Y0VHDmd1Xf[rtaUFjmY-1];
    while(1){  /* Exit via break */
      if( BYPQ->ZP4P_QR4oE <= QHTTY7FdjXo ) Yqs3Ss02pZV(pLMJg2Xd, BYPQ->ZP4P_QR4oE, BYPQ->vO1m9d.RWdNEx2WUIO8x);
#ifdef faD_O9XSX
      UXHgfYQ(pLMJg2Xd, BYPQ->PihbEOgZ);
#endif    
      if( BYPQ==V7Y0VHDmd1Xf ) break;
      BYPQ--;
    }
    CTQ2V30yU(pLMJg2Xd, V7Y0VHDmd1Xf);
  }
}

/*
** Link the SubProgram object passed as the second argument into the linked
** list at Vdbe.pSubProgram. This list is used to delete all sub-program
** objects when the VM is no longer required.
*/
void a_KWnP0L7mhL7(Y4zzrBxD4OXTO *FDcUAbRU, RnzBAc3QE *RWdNEx2WUIO8x){
  RWdNEx2WUIO8x->Vete4ig = FDcUAbRU->IbbDoqgyL;
  FDcUAbRU->IbbDoqgyL = RWdNEx2WUIO8x;
}

/*
** Return true if the given Vdbe has any SubPrograms.
*/
int EzL9pAg5Qr(Y4zzrBxD4OXTO *FDcUAbRU){
  return FDcUAbRU->IbbDoqgyL!=0;
}

/*
** Change the opcode at addr into OP_Noop
*/
int XFhQ(Y4zzrBxD4OXTO *RWdNEx2WUIO8x, int JPWY){
  kqPOQZYA16d *BYPQ;
  if( RWdNEx2WUIO8x->pLMJg2Xd->mi4oOCmRVN_h ) return 0;
  f5IeCeK0e1W( JPWY>=0 && JPWY<RWdNEx2WUIO8x->rtaUFjmY );
  BYPQ = &RWdNEx2WUIO8x->V7Y0VHDmd1Xf[JPWY];
  Yqs3Ss02pZV(RWdNEx2WUIO8x->pLMJg2Xd, BYPQ->ZP4P_QR4oE, BYPQ->vO1m9d.RWdNEx2WUIO8x);
  BYPQ->ZP4P_QR4oE = bcIYtAfjheQ;
  BYPQ->vO1m9d.mrgekw0xj = 0;
  BYPQ->KMcyPZbh = bMgvT4hVOBV;
  return 1;
}

/*
** If the last opcode is "op" and it is not a jump destination,
** then remove it.  Return true if and only if an opcode was removed.
*/
int W3QxQNDyPKpdA(Y4zzrBxD4OXTO *RWdNEx2WUIO8x, qHh5JW odStgZ){
  if( RWdNEx2WUIO8x->rtaUFjmY>0 && RWdNEx2WUIO8x->V7Y0VHDmd1Xf[RWdNEx2WUIO8x->rtaUFjmY-1].KMcyPZbh==odStgZ ){
    return XFhQ(RWdNEx2WUIO8x, RWdNEx2WUIO8x->rtaUFjmY-1);
  }else{
    return 0;
  }
}

#ifdef iteB65TL5L
/*
** Generate an OP_ReleaseReg opcode to indicate that a range of
** registers, except any identified by mask, are no longer in use.
*/
void CgkVNSlXGn(
  MSufNwYJMUIW *CZswHrqPXTX,       /* Parsing context */
  int GsmpQ,          /* Index of first register to be released */
  int YLqByqgGKPr,               /* Number of registers to release */
  JamYDTpy Y1cyytKp,            /* Mask of registers to NOT release */
  int abptj        /* If true, mark registers as undefined */
){
  if( YLqByqgGKPr==0 || qcvWjyI7pgD8W(CZswHrqPXTX->pLMJg2Xd, AgI086I) ) return;
  f5IeCeK0e1W( CZswHrqPXTX->FDcUAbRU );
  f5IeCeK0e1W( GsmpQ>=1 );
  f5IeCeK0e1W( GsmpQ+YLqByqgGKPr-1<=CZswHrqPXTX->Om1f );
  if( YLqByqgGKPr<=31 && Y1cyytKp!=0 ){
    while( YLqByqgGKPr>0 && (Y1cyytKp&1)!=0 ){
      Y1cyytKp >>= 1;
      GsmpQ++;
      YLqByqgGKPr--;
    }
    while( YLqByqgGKPr>0 && YLqByqgGKPr<=32 && (Y1cyytKp & YIml(YLqByqgGKPr-1))!=0 ){
      Y1cyytKp &= ~YIml(YLqByqgGKPr-1);
      YLqByqgGKPr--;
    }
  }
  if( YLqByqgGKPr>0 ){
    sNmXi5z1R8n5(CZswHrqPXTX->FDcUAbRU, Z_oY0_2, GsmpQ, YLqByqgGKPr, *(int*)&Y1cyytKp);
    if( abptj ) WKe_X9SULH(CZswHrqPXTX->FDcUAbRU, 1);
  }
}
#endif /* SQLITE_DEBUG */

/*
** Change the value of the P4 operand for a specific instruction.
** This routine is useful when a large program is loaded from a
** static array using sqlite3VdbeAddOpList but we want to make a
** few minor changes to the program.
**
** If n>=0 then the P4 operand is dynamic, meaning that a copy of
** the string is made into memory obtained from sqlite3_malloc().
** A value of n==0 means copy bytes of zP4 up to and including the
** first null byte.  If n>0 then copy n+1 bytes of zP4.
**
** Other values of n (P4_STATIC, P4_COLLSEQ etc.) indicate that zP4 points
** to a string or structure that is guaranteed to exist for the lifetime of
** the Vdbe. In these cases we can just copy the pointer.
**
** If addr<0 then change P4 on the most recently inserted instruction.
*/
static void XmVnyUQh fSKBarRaNu(
  Y4zzrBxD4OXTO *RWdNEx2WUIO8x,
  mHYCosji8c *BYPQ,
  const char *JrmG5OAto30B,
  int AS0ycVs
){
  if( BYPQ->ZP4P_QR4oE ){
    f5IeCeK0e1W( BYPQ->ZP4P_QR4oE > QHTTY7FdjXo );
    BYPQ->ZP4P_QR4oE = 0;
    BYPQ->vO1m9d.RWdNEx2WUIO8x = 0;
  }
  if( AS0ycVs<0 ){
    AyAMrl5QsX(RWdNEx2WUIO8x, (int)(BYPQ - RWdNEx2WUIO8x->V7Y0VHDmd1Xf), JrmG5OAto30B, AS0ycVs);
  }else{
    if( AS0ycVs==0 ) AS0ycVs = cdWRz96EMqfU(JrmG5OAto30B);
    BYPQ->vO1m9d.mrgekw0xj = oS7U3U(RWdNEx2WUIO8x->pLMJg2Xd, JrmG5OAto30B, AS0ycVs);
    BYPQ->ZP4P_QR4oE = fWFW;
  }
}
void AyAMrl5QsX(Y4zzrBxD4OXTO *RWdNEx2WUIO8x, int JPWY, const char *JrmG5OAto30B, int AS0ycVs){
  mHYCosji8c *BYPQ;
  MEeQFpE4DzbZ *pLMJg2Xd;
  f5IeCeK0e1W( RWdNEx2WUIO8x!=0 );
  pLMJg2Xd = RWdNEx2WUIO8x->pLMJg2Xd;
  f5IeCeK0e1W( RWdNEx2WUIO8x->C19t==w_rp1wwh );
  f5IeCeK0e1W( RWdNEx2WUIO8x->V7Y0VHDmd1Xf!=0 || pLMJg2Xd->mi4oOCmRVN_h );
  if( pLMJg2Xd->mi4oOCmRVN_h ){
    if( AS0ycVs!=PtQbWJ7b6 ) Yqs3Ss02pZV(pLMJg2Xd, AS0ycVs, (void*)*(char**)&JrmG5OAto30B);
    return;
  }
  f5IeCeK0e1W( RWdNEx2WUIO8x->rtaUFjmY>0 );
  f5IeCeK0e1W( JPWY<RWdNEx2WUIO8x->rtaUFjmY );
  if( JPWY<0 ){
    JPWY = RWdNEx2WUIO8x->rtaUFjmY - 1;
  }
  BYPQ = &RWdNEx2WUIO8x->V7Y0VHDmd1Xf[JPWY];
  if( AS0ycVs>=0 || BYPQ->ZP4P_QR4oE ){
    fSKBarRaNu(RWdNEx2WUIO8x, BYPQ, JrmG5OAto30B, AS0ycVs);
    return;
  }
  if( AS0ycVs==KUJARfJ_9I ){
    /* Note: this cast is safe, because the origin data point was an int
    ** that was cast to a (const char *). */
    BYPQ->vO1m9d.Pyy0l6xD = NM8FnDbPNE(JrmG5OAto30B);
    BYPQ->ZP4P_QR4oE = KUJARfJ_9I;
  }else if( JrmG5OAto30B!=0 ){
    f5IeCeK0e1W( AS0ycVs<0 );
    BYPQ->vO1m9d.RWdNEx2WUIO8x = (void*)JrmG5OAto30B;
    BYPQ->ZP4P_QR4oE = (signed char)AS0ycVs;
    if( AS0ycVs==PtQbWJ7b6 ) vpZAoh2p((szc_QE2VngTx*)JrmG5OAto30B);
  }
}

/*
** Change the P4 operand of the most recently coded instruction
** to the value defined by the arguments.  This is a high-speed
** version of sqlite3VdbeChangeP4().
**
** The P4 operand must not have been previously defined.  And the new
** P4 must not be P4_INT32.  Use sqlite3VdbeChangeP4() in either of
** those cases.
*/
void bLuCoa6OY67da(Y4zzrBxD4OXTO *RWdNEx2WUIO8x, void *nw6feoZ3Jx, int AS0ycVs){
  kqPOQZYA16d *BYPQ;
  f5IeCeK0e1W( AS0ycVs!=KUJARfJ_9I && AS0ycVs!=PtQbWJ7b6 );
  f5IeCeK0e1W( AS0ycVs<=0 );
  if( RWdNEx2WUIO8x->pLMJg2Xd->mi4oOCmRVN_h ){
    Yqs3Ss02pZV(RWdNEx2WUIO8x->pLMJg2Xd, AS0ycVs, nw6feoZ3Jx);
  }else{
    f5IeCeK0e1W( nw6feoZ3Jx!=0 || AS0ycVs==fWFW );
    f5IeCeK0e1W( RWdNEx2WUIO8x->rtaUFjmY>0 );
    BYPQ = &RWdNEx2WUIO8x->V7Y0VHDmd1Xf[RWdNEx2WUIO8x->rtaUFjmY-1];
    f5IeCeK0e1W( BYPQ->ZP4P_QR4oE==bcIYtAfjheQ );
    BYPQ->ZP4P_QR4oE = AS0ycVs;
    BYPQ->vO1m9d.RWdNEx2WUIO8x = nw6feoZ3Jx;
  }
}

/*
** Set the P4 on the most recently added opcode to the KeyInfo for the
** index given.
*/
void UzNQ(MSufNwYJMUIW *CZswHrqPXTX, ESeAccJ39k *SZQVP7LvN){
  Y4zzrBxD4OXTO *HB_T1jBCLdNzN = CZswHrqPXTX->FDcUAbRU;
  Yen3v7sHJ_Gb *N0B0w0pr1Cz;
  f5IeCeK0e1W( HB_T1jBCLdNzN!=0 );
  f5IeCeK0e1W( SZQVP7LvN!=0 );
  N0B0w0pr1Cz = wSqVgIxcQo(CZswHrqPXTX, SZQVP7LvN);
  if( N0B0w0pr1Cz ) bLuCoa6OY67da(HB_T1jBCLdNzN, N0B0w0pr1Cz, OALG4pjXX);
}

#ifdef faD_O9XSX
/*
** Change the comment on the most recently coded instruction.  Or
** insert a No-op and add the comment to that new instruction.  This
** makes the code easier to read during debugging.  None of this happens
** in a production build.
*/
static void nFr7(Y4zzrBxD4OXTO *RWdNEx2WUIO8x, const char *Zm6_Sj, WTdlzRsWXwU lYmDMW9){
  f5IeCeK0e1W( RWdNEx2WUIO8x->rtaUFjmY>0 || RWdNEx2WUIO8x->V7Y0VHDmd1Xf==0 );
  f5IeCeK0e1W( RWdNEx2WUIO8x->V7Y0VHDmd1Xf==0 || RWdNEx2WUIO8x->V7Y0VHDmd1Xf[RWdNEx2WUIO8x->rtaUFjmY-1].PihbEOgZ==0 || RWdNEx2WUIO8x->CZswHrqPXTX->yewcXFREO>0 );
  if( RWdNEx2WUIO8x->rtaUFjmY ){
    f5IeCeK0e1W( RWdNEx2WUIO8x->V7Y0VHDmd1Xf );
    UXHgfYQ(RWdNEx2WUIO8x->pLMJg2Xd, RWdNEx2WUIO8x->V7Y0VHDmd1Xf[RWdNEx2WUIO8x->rtaUFjmY-1].PihbEOgZ);
    RWdNEx2WUIO8x->V7Y0VHDmd1Xf[RWdNEx2WUIO8x->rtaUFjmY-1].PihbEOgZ = SRrx7cWPh4(RWdNEx2WUIO8x->pLMJg2Xd, Zm6_Sj, lYmDMW9);
  }
}
void ahF4hM2Eh(Y4zzrBxD4OXTO *RWdNEx2WUIO8x, const char *Zm6_Sj, ...){
  WTdlzRsWXwU lYmDMW9;
  if( RWdNEx2WUIO8x ){
    CpjAzX(lYmDMW9, Zm6_Sj);
    nFr7(RWdNEx2WUIO8x, Zm6_Sj, lYmDMW9);
    LZ9p(lYmDMW9);
  }
}
void h685e3M(Y4zzrBxD4OXTO *RWdNEx2WUIO8x, const char *Zm6_Sj, ...){
  WTdlzRsWXwU lYmDMW9;
  if( RWdNEx2WUIO8x ){
    Ku8cbll7CJ6HU(RWdNEx2WUIO8x, bMgvT4hVOBV);
    CpjAzX(lYmDMW9, Zm6_Sj);
    nFr7(RWdNEx2WUIO8x, Zm6_Sj, lYmDMW9);
    LZ9p(lYmDMW9);
  }
}
#endif  /* NDEBUG */

#ifdef xGeFUI6
/*
** Set the value if the iSrcLine field for the previously coded instruction.
*/
void INfMPF(Y4zzrBxD4OXTO *HB_T1jBCLdNzN, int XqzD){
  aADK8XR(HB_T1jBCLdNzN)->BzSu7o = XqzD;
}
#endif /* SQLITE_VDBE_COVERAGE */

/*
** Return the opcode for a given address.  The address must be non-negative.
** See sqlite3VdbeGetLastOp() to get the most recently added opcode.
**
** If a memory allocation error has occurred prior to the calling of this
** routine, then a pointer to a dummy VdbeOp will be returned.  That opcode
** is readable but not writable, though it is cast to a writable value.
** The return of a dummy opcode allows the call to continue functioning
** after an OOM fault without having to check to see if the return from
** this routine is a valid pointer.  But because the dummy.opcode is 0,
** dummy will never be written to.  This is verified by code inspection and
** by running with Valgrind.
*/
kqPOQZYA16d *lz2h(Y4zzrBxD4OXTO *RWdNEx2WUIO8x, int JPWY){
  /* C89 specifies that the constant "dummy" will be initialized to all
  ** zeros, which is correct.  MSVC generates a warning, nevertheless. */
  static kqPOQZYA16d l6fntSbAF5;  /* Ignore the MSVC warning about no initializer */
  f5IeCeK0e1W( RWdNEx2WUIO8x->C19t==w_rp1wwh );
  f5IeCeK0e1W( (JPWY>=0 && JPWY<RWdNEx2WUIO8x->rtaUFjmY) || RWdNEx2WUIO8x->pLMJg2Xd->mi4oOCmRVN_h );
  if( RWdNEx2WUIO8x->pLMJg2Xd->mi4oOCmRVN_h ){
    return (kqPOQZYA16d*)&l6fntSbAF5;
  }else{
    return &RWdNEx2WUIO8x->V7Y0VHDmd1Xf[JPWY];
  }
}

/* Return the most recently added opcode
*/
kqPOQZYA16d *aADK8XR(Y4zzrBxD4OXTO *RWdNEx2WUIO8x){
  return lz2h(RWdNEx2WUIO8x, RWdNEx2WUIO8x->rtaUFjmY - 1);
}

#if pZX7GD4OTcuV(faD_O9XSX)
/*
** Return an integer value for one of the parameters to the opcode pOp
** determined by character c.
*/
static int EjTxA6OphXk0(char Wydjdw_pm6, const mHYCosji8c *BYPQ){
  if( Wydjdw_pm6=='1' ) return BYPQ->mB_5hYOV5K;
  if( Wydjdw_pm6=='2' ) return BYPQ->pPP2V5;
  if( Wydjdw_pm6=='3' ) return BYPQ->BTBDVdeO3P;
  if( Wydjdw_pm6=='4' ) return BYPQ->vO1m9d.Pyy0l6xD;
  return BYPQ->I4yL;
}

/*
** Compute a string for the "comment" field of a VDBE opcode listing.
**
** The Synopsis: field in comments in the vdbe.c source file gets converted
** to an extra string that is appended to the sqlite3OpcodeName().  In the
** absence of other comments, this synopsis becomes the comment on the opcode.
** Some translation occurs:
**
**       "PX"      ->  "r[X]"
**       "PX@PY"   ->  "r[X..X+Y-1]"  or "r[x]" if y is 0 or 1
**       "PX@PY+1" ->  "r[X..X+Y]"    or "r[x]" if y is 0
**       "PY..PY"  ->  "r[X..Y]"      or "r[x]" if y<=x
*/
char *uPa2XJzUAcRsC(
  MEeQFpE4DzbZ *pLMJg2Xd,       /* Optional - Oom error reporting only */
  const mHYCosji8c *BYPQ,     /* The opcode to be commented */
  const char *JrmG5OAto30B    /* Previously obtained value for P4 */
){
  const char *Oqk6yKv;
  const char *kJptLVDW;
  int prbnJ7NDV;
  int Fofiz5Dmlfsbf;
  char at2wtY[50];
  MoDoD zCVq;

  S6pEEnk9kx(&zCVq, 0, 0, 0, RJD6O);
  Oqk6yKv = wZgtGf(BYPQ->KMcyPZbh);
  prbnJ7NDV = cdWRz96EMqfU(Oqk6yKv);
  if( Oqk6yKv[prbnJ7NDV+1] ){
    int IrnX = 0;
    char Wydjdw_pm6;
    kJptLVDW = Oqk6yKv + prbnJ7NDV + 1;
    if( pWPXXIq7(kJptLVDW,"IF ",3)==0 ){
      xyTnraEFT(sizeof(at2wtY), at2wtY, "if %s goto P2", kJptLVDW+3);
      kJptLVDW = at2wtY;
    }
    for(Fofiz5Dmlfsbf=0; (Wydjdw_pm6 = kJptLVDW[Fofiz5Dmlfsbf])!=0; Fofiz5Dmlfsbf++){
      if( Wydjdw_pm6=='P' ){
        Wydjdw_pm6 = kJptLVDW[++Fofiz5Dmlfsbf];
        if( Wydjdw_pm6=='4' ){
          JHjFY(&zCVq, JrmG5OAto30B);
        }else if( Wydjdw_pm6=='X' ){
          if( BYPQ->PihbEOgZ && BYPQ->PihbEOgZ[0] ){
            JHjFY(&zCVq, BYPQ->PihbEOgZ);
            IrnX = 1;
            break;
          }
        }else{
          int PYIK7IfGiwFYz = EjTxA6OphXk0(Wydjdw_pm6, BYPQ);
          int ImFLUcfz;
          if( pWPXXIq7(kJptLVDW+Fofiz5Dmlfsbf+1, "@P", 2)==0 ){
            Fofiz5Dmlfsbf += 3;
            ImFLUcfz = EjTxA6OphXk0(kJptLVDW[Fofiz5Dmlfsbf], BYPQ);
            if( pWPXXIq7(kJptLVDW+Fofiz5Dmlfsbf+1,"+1",2)==0 ){
              Fofiz5Dmlfsbf += 2;
              ImFLUcfz++;
            }
            if( ImFLUcfz<2 ){
              xsxqlh10JTjYJ(&zCVq, "%d", PYIK7IfGiwFYz);
            }else{
              xsxqlh10JTjYJ(&zCVq, "%d..%d", PYIK7IfGiwFYz, PYIK7IfGiwFYz+ImFLUcfz-1);
            }
          }else if( pWPXXIq7(kJptLVDW+Fofiz5Dmlfsbf+1, "@NP", 3)==0 ){
            DWQQ4Hi8 *KMDC3A_94J = BYPQ->vO1m9d.KMDC3A_94J;
            if( BYPQ->ZP4P_QR4oE!=H5QvOmDMVC1Eh || KMDC3A_94J->LQeaBUw==1 ){
              xsxqlh10JTjYJ(&zCVq, "%d", PYIK7IfGiwFYz);
            }else if( KMDC3A_94J->LQeaBUw>1 ){
              xsxqlh10JTjYJ(&zCVq, "%d..%d", PYIK7IfGiwFYz, PYIK7IfGiwFYz+KMDC3A_94J->LQeaBUw-1);
            }else if( zCVq.VlKlP0wKW==0 ){
              f5IeCeK0e1W( zCVq.ZxlwTjICooQX>2 );
              zCVq.ZxlwTjICooQX -= 2;
              Fofiz5Dmlfsbf++;
            }
            Fofiz5Dmlfsbf += 3;
          }else{
            xsxqlh10JTjYJ(&zCVq, "%d", PYIK7IfGiwFYz);
            if( pWPXXIq7(kJptLVDW+Fofiz5Dmlfsbf+1, "..P3", 4)==0 && BYPQ->BTBDVdeO3P==0 ){
              Fofiz5Dmlfsbf += 4;
            }
          }
        }
      }else{
        ovRYXDh(&zCVq, 1, Wydjdw_pm6);
      }
    }
    if( !IrnX && BYPQ->PihbEOgZ ){
      xsxqlh10JTjYJ(&zCVq, "; %s", BYPQ->PihbEOgZ);
    }
  }else if( BYPQ->PihbEOgZ ){
    JHjFY(&zCVq, BYPQ->PihbEOgZ);
  }
  if( (zCVq.VlKlP0wKW & ccKsEfbei4)!=0 && pLMJg2Xd!=0 ){
    I_fGWFjD(pLMJg2Xd);
  }
  return x3hxsq2(&zCVq);
}
#endif /* SQLITE_ENABLE_EXPLAIN_COMMENTS */

#if o_p5uW31_1rs && pZX7GD4OTcuV(DWSSZmoaM)
/*
** Translate the P4.pExpr value for an OP_CursorHint opcode into text
** that can be displayed in the P4 column of EXPLAIN output.
*/
static void YQ6ESMCpG(MoDoD *RWdNEx2WUIO8x, n29LzVguZ6CV *fRIR8Z){
  const char *tr4ckeFh4PeoR = 0;
  switch( fRIR8Z->odStgZ ){
    case s42B3TR:
      f5IeCeK0e1W( !V8X4JSnShu(fRIR8Z, YOZw) );
      xsxqlh10JTjYJ(RWdNEx2WUIO8x, "%Q", fRIR8Z->r43Pj.DGNY);
      break;
    case Om7rJiiAl3:
      xsxqlh10JTjYJ(RWdNEx2WUIO8x, "%d", fRIR8Z->r43Pj.AbNVl9oGow2G);
      break;
    case z3wLDUA:
      xsxqlh10JTjYJ(RWdNEx2WUIO8x, "NULL");
      break;
    case qizx_KrVFuFCa: {
      xsxqlh10JTjYJ(RWdNEx2WUIO8x, "r[%d]", fRIR8Z->x10NhVu);
      break;
    }
    case Nic7J4JW: {
      if( fRIR8Z->BjkRcXigP7<0 ){
        xsxqlh10JTjYJ(RWdNEx2WUIO8x, "rowid");
      }else{
        xsxqlh10JTjYJ(RWdNEx2WUIO8x, "c%d", (int)fRIR8Z->BjkRcXigP7);
      }
      break;
    }
    case is67OBt7tjQv:      tr4ckeFh4PeoR = "LT";      break;
    case WlKDNfcg6kb_C:      tr4ckeFh4PeoR = "LE";      break;
    case fWbjVB:      tr4ckeFh4PeoR = "GT";      break;
    case JQ_weMsSi_kW:      tr4ckeFh4PeoR = "GE";      break;
    case AIuyl:      tr4ckeFh4PeoR = "NE";      break;
    case X9f6:      tr4ckeFh4PeoR = "EQ";      break;
    case LfW0Wt6r:      tr4ckeFh4PeoR = "IS";      break;
    case aWIpvDZjd:   tr4ckeFh4PeoR = "ISNOT";   break;
    case O1yixUi1:     tr4ckeFh4PeoR = "AND";     break;
    case ppQmqEcx:      tr4ckeFh4PeoR = "OR";      break;
    case iwNE5I:    tr4ckeFh4PeoR = "ADD";     break;
    case MkZ6Thms4lPy:    tr4ckeFh4PeoR = "MUL";     break;
    case OeQizOmLq:   tr4ckeFh4PeoR = "SUB";     break;
    case VKej:     tr4ckeFh4PeoR = "REM";     break;
    case TyN21g:  tr4ckeFh4PeoR = "BITAND";  break;
    case vSZvPeQ:   tr4ckeFh4PeoR = "BITOR";   break;
    case AXq4i0Afw6K:   tr4ckeFh4PeoR = "DIV";     break;
    case b45coEHaa:  tr4ckeFh4PeoR = "LSHIFT";  break;
    case ror1FgSoxK_V:  tr4ckeFh4PeoR = "RSHIFT";  break;
    case xG5S_UKEflNr:  tr4ckeFh4PeoR = "CONCAT";  break;
    case dzz0b:  tr4ckeFh4PeoR = "MINUS";   break;
    case aMw3p82R:   tr4ckeFh4PeoR = "PLUS";    break;
    case FCWsUS4ugFBV:  tr4ckeFh4PeoR = "BITNOT";  break;
    case rxLEcRtasgLUE:     tr4ckeFh4PeoR = "NOT";     break;
    case Op_8spQltpe:  tr4ckeFh4PeoR = "ISNULL";  break;
    case OH5Vy9Fpifd0: tr4ckeFh4PeoR = "NOTNULL"; break;

    default:
      xsxqlh10JTjYJ(RWdNEx2WUIO8x, "%s", "expr");
      break;
  }

  if( tr4ckeFh4PeoR ){
    xsxqlh10JTjYJ(RWdNEx2WUIO8x, "%s(", tr4ckeFh4PeoR);
    YQ6ESMCpG(RWdNEx2WUIO8x, fRIR8Z->sa18be);
    if( fRIR8Z->evV2rFyDG_bgY ){
      GgAm8IxLy3k(RWdNEx2WUIO8x, ",", 1);
      YQ6ESMCpG(RWdNEx2WUIO8x, fRIR8Z->evV2rFyDG_bgY);
    }
    GgAm8IxLy3k(RWdNEx2WUIO8x, ")", 1);
  }
}
#endif /* VDBE_DISPLAY_P4 && defined(SQLITE_ENABLE_CURSOR_HINTS) */


#if o_p5uW31_1rs
/*
** Compute a string that describes the P4 parameter for an opcode.
** Use zTemp for any required temporary buffer space.
*/
char *kDaR08PC(MEeQFpE4DzbZ *pLMJg2Xd, mHYCosji8c *BYPQ){
  char *JrmG5OAto30B = 0;
  MoDoD zCVq;

  S6pEEnk9kx(&zCVq, 0, 0, 0, RJD6O);
  switch( BYPQ->ZP4P_QR4oE ){
    case OALG4pjXX: {
      int fg6dGr;
      Yen3v7sHJ_Gb *N0B0w0pr1Cz = BYPQ->vO1m9d.N0B0w0pr1Cz;
      f5IeCeK0e1W( N0B0w0pr1Cz->iIxU!=0 );
      xsxqlh10JTjYJ(&zCVq, "k(%d", N0B0w0pr1Cz->tr0jn);
      for(fg6dGr=0; fg6dGr<N0B0w0pr1Cz->tr0jn; fg6dGr++){
        ri6hxZ *VrQRc7aD = N0B0w0pr1Cz->izMnyxj_sW9X[fg6dGr];
        const char *hubTGWf = VrQRc7aD ? VrQRc7aD->wxojaeqHwik : "";
        if( wTd5D(hubTGWf, "BINARY")==0 ) hubTGWf = "B";
        xsxqlh10JTjYJ(&zCVq, ",%s%s%s",
               (N0B0w0pr1Cz->iIxU[fg6dGr] & HZ5O) ? "-" : "",
               (N0B0w0pr1Cz->iIxU[fg6dGr] & Ndk748d98M2)? "N." : "",
               hubTGWf);
      }
      GgAm8IxLy3k(&zCVq, ")", 1);
      break;
    }
#ifdef DWSSZmoaM
    case LS2RGg: {
      YQ6ESMCpG(&zCVq, BYPQ->vO1m9d.fRIR8Z);
      break;
    }
#endif
    case UbsxsZY: {
      static const char *const fjgyHC[] = {"?", "8", "16LE", "16BE"};
      ri6hxZ *VrQRc7aD = BYPQ->vO1m9d.VrQRc7aD;
      f5IeCeK0e1W( VrQRc7aD->Tc4R1<4 );
      xsxqlh10JTjYJ(&zCVq, "%.18s-%s", VrQRc7aD->wxojaeqHwik,
                          fjgyHC[VrQRc7aD->Tc4R1]);
      break;
    }
    case fWjT: {
      r_0_hpT *vPar9lD = BYPQ->vO1m9d.pOpnI3oMVnGn;
      xsxqlh10JTjYJ(&zCVq, "%s(%d)", vPar9lD->wxojaeqHwik, vPar9lD->WL_eiS);
      break;
    }
    case H5QvOmDMVC1Eh: {
      r_0_hpT *vPar9lD = BYPQ->vO1m9d.KMDC3A_94J->pOpnI3oMVnGn;
      xsxqlh10JTjYJ(&zCVq, "%s(%d)", vPar9lD->wxojaeqHwik, vPar9lD->WL_eiS);
      break;
    }
    case PuWoCY: {
      xsxqlh10JTjYJ(&zCVq, "%lld", *BYPQ->vO1m9d.yv05);
      break;
    }
    case KUJARfJ_9I: {
      xsxqlh10JTjYJ(&zCVq, "%d", BYPQ->vO1m9d.Pyy0l6xD);
      break;
    }
    case H0OpYaT8P: {
      xsxqlh10JTjYJ(&zCVq, "%.16g", *BYPQ->vO1m9d.heUFzq);
      break;
    }
    case FrqQiM: {
      oi4q2s5KcMX9Y *ZAHT = BYPQ->vO1m9d.ZAHT;
      if( ZAHT->MRNoo5HiPBk7 & caIIAbkg ){
        JrmG5OAto30B = ZAHT->mrgekw0xj;
      }else if( ZAHT->MRNoo5HiPBk7 & (qN6FC41ULkGDO|tbmTzwycmDB) ){
        xsxqlh10JTjYJ(&zCVq, "%lld", ZAHT->r43Pj.Pyy0l6xD);
      }else if( ZAHT->MRNoo5HiPBk7 & ITDPS ){
        xsxqlh10JTjYJ(&zCVq, "%.16g", ZAHT->r43Pj.uNdS8p26k);
      }else if( ZAHT->MRNoo5HiPBk7 & NIJTPrY3UI ){
        JrmG5OAto30B = "NULL";
      }else{
        f5IeCeK0e1W( ZAHT->MRNoo5HiPBk7 & GrDQtTd );
        JrmG5OAto30B = "(blob)";
      }
      break;
    }
#ifndef uRsBKByRR
    case PtQbWJ7b6: {
      QMJ6_wa *X4AIzAFQeHOW = BYPQ->vO1m9d.X4AIzAFQeHOW->X4AIzAFQeHOW;
      xsxqlh10JTjYJ(&zCVq, "vtab:%p", X4AIzAFQeHOW);
      break;
    }
#endif
    case pc36yfwL: {
      JamYDTpy Pyy0l6xD;
      JamYDTpy *kAFEdYMa8Cy = BYPQ->vO1m9d.kAFEdYMa8Cy;
      JamYDTpy AS0ycVs = kAFEdYMa8Cy[0];   /* The first element of an INTARRAY is always the
                       ** count of the number of elements to follow */
      for(Pyy0l6xD=1; Pyy0l6xD<=AS0ycVs; Pyy0l6xD++){
        xsxqlh10JTjYJ(&zCVq, "%c%u", (Pyy0l6xD==1 ? '[' : ','), kAFEdYMa8Cy[Pyy0l6xD]);
      }
      GgAm8IxLy3k(&zCVq, "]", 1);
      break;
    }
    case JbYHBRv: {
      JrmG5OAto30B = "program";
      break;
    }
    case MG9wQkCYJBJ: {
      JrmG5OAto30B = BYPQ->vO1m9d.rLBZ1vZbk->wxojaeqHwik;
      break;
    }
    default: {
      JrmG5OAto30B = BYPQ->vO1m9d.mrgekw0xj;
    }
  }
  if( JrmG5OAto30B ) JHjFY(&zCVq, JrmG5OAto30B);
  if( (zCVq.VlKlP0wKW & ccKsEfbei4)!=0 ){
    I_fGWFjD(pLMJg2Xd);
  }
  return x3hxsq2(&zCVq);
}
#endif /* VDBE_DISPLAY_P4 */

/*
** Declare to the Vdbe that the BTree object at db->aDb[i] is used.
**
** The prepared statements need to know in advance the complete set of
** attached databases that will be use.  A mask of these databases
** is maintained in p->btreeMask.  The p->lockMask value is the subset of
** p->btreeMask of databases that will require a lock.
*/
void Tm1i9hlV8(Y4zzrBxD4OXTO *RWdNEx2WUIO8x, int Pyy0l6xD){
  f5IeCeK0e1W( Pyy0l6xD>=0 && Pyy0l6xD<RWdNEx2WUIO8x->pLMJg2Xd->rAyJ && Pyy0l6xD<(int)sizeof(crYwpJ6eca)*8 );
  f5IeCeK0e1W( Pyy0l6xD<(int)sizeof(RWdNEx2WUIO8x->tP8VR_wprd)*8 );
  kEp7qAhDKbb(RWdNEx2WUIO8x->tP8VR_wprd, Pyy0l6xD);
  if( Pyy0l6xD!=1 && UK04Am(RWdNEx2WUIO8x->pLMJg2Xd->cFohRY2vCC[Pyy0l6xD].UEF9V) ){
    kEp7qAhDKbb(RWdNEx2WUIO8x->DVna4Ahs0wi, Pyy0l6xD);
  }
}

#if !pZX7GD4OTcuV(wK1F9)
/*
** If SQLite is compiled to support shared-cache mode and to be threadsafe,
** this routine obtains the mutex associated with each BtShared structure
** that may be accessed by the VM passed as an argument. In doing so it also
** sets the BtShared.db member of each of the BtShared structures, ensuring
** that the correct busy-handler callback is invoked if required.
**
** If SQLite is not threadsafe but does support shared-cache mode, then
** sqlite3BtreeEnter() is invoked to set the BtShared.db variables
** of all of BtShared structures accessible via the database handle
** associated with the VM.
**
** If SQLite is not threadsafe and does not support shared-cache mode, this
** function is a no-op.
**
** The p->btreeMask field is a bitmask of all btrees that the prepared
** statement p will ever use.  Let N be the number of bits in p->btreeMask
** corresponding to btrees that use shared cache.  Then the runtime of
** this routine is N*N.  But as N is rarely more than 1, this should not
** be a problem.
*/
void hhQVOl(Y4zzrBxD4OXTO *RWdNEx2WUIO8x){
  int Pyy0l6xD;
  MEeQFpE4DzbZ *pLMJg2Xd;
  fk84lvhDoqo *cFohRY2vCC;
  int rAyJ;
  if( kgp4z0VrkC(RWdNEx2WUIO8x->DVna4Ahs0wi) ) return;  /* The common case */
  pLMJg2Xd = RWdNEx2WUIO8x->pLMJg2Xd;
  cFohRY2vCC = pLMJg2Xd->cFohRY2vCC;
  rAyJ = pLMJg2Xd->rAyJ;
  for(Pyy0l6xD=0; Pyy0l6xD<rAyJ; Pyy0l6xD++){
    if( Pyy0l6xD!=1 && qLZN8jfVvIZj(RWdNEx2WUIO8x->DVna4Ahs0wi,Pyy0l6xD) && GVDI(cFohRY2vCC[Pyy0l6xD].UEF9V!=0) ){
      mRYwkevtc3M8(cFohRY2vCC[Pyy0l6xD].UEF9V);
    }
  }
}
#endif

#if !pZX7GD4OTcuV(wK1F9) && mgEgOL7>0
/*
** Unlock all of the btrees previously locked by a call to sqlite3VdbeEnter().
*/
static XmVnyUQh void CiG4D(Y4zzrBxD4OXTO *RWdNEx2WUIO8x){
  int Pyy0l6xD;
  MEeQFpE4DzbZ *pLMJg2Xd;
  fk84lvhDoqo *cFohRY2vCC;
  int rAyJ;
  pLMJg2Xd = RWdNEx2WUIO8x->pLMJg2Xd;
  cFohRY2vCC = pLMJg2Xd->cFohRY2vCC;
  rAyJ = pLMJg2Xd->rAyJ;
  for(Pyy0l6xD=0; Pyy0l6xD<rAyJ; Pyy0l6xD++){
    if( Pyy0l6xD!=1 && qLZN8jfVvIZj(RWdNEx2WUIO8x->DVna4Ahs0wi,Pyy0l6xD) && GVDI(cFohRY2vCC[Pyy0l6xD].UEF9V!=0) ){
      G1gToGBXbxIv9(cFohRY2vCC[Pyy0l6xD].UEF9V);
    }
  }
}
void ac8keF7W(Y4zzrBxD4OXTO *RWdNEx2WUIO8x){
  if( kgp4z0VrkC(RWdNEx2WUIO8x->DVna4Ahs0wi) ) return;  /* The common case */
  CiG4D(RWdNEx2WUIO8x);
}
#endif

#if pZX7GD4OTcuV(fsSLSO_wyCxfR) || pZX7GD4OTcuV(iteB65TL5L)
/*
** Print a single opcode.  This routine is used for debugging only.
*/
void QA1Dfk_5egTE9(f3lOW1Ra0n *IBMjGt5hp, int Ee05M7jDx_, kqPOQZYA16d *BYPQ){
  char *JrmG5OAto30B;
  char *EQx73w;
  MEeQFpE4DzbZ DP_0EBjzIK;
  static const char *eW0UCfzKNDESi = "%4d %-13s %4d %4d %4d %-13s %.2X %s\n";
  if( IBMjGt5hp==0 ) IBMjGt5hp = dtduqvj;
  O8TGutpxUeP1O();
  DP_0EBjzIK.mi4oOCmRVN_h = 1;
  JrmG5OAto30B = kDaR08PC(&DP_0EBjzIK, BYPQ);
#ifdef faD_O9XSX
  EQx73w = uPa2XJzUAcRsC(0, BYPQ, JrmG5OAto30B);
#else
  EQx73w = 0;
#endif
  /* NB:  The sqlite3OpcodeName() function is implemented by code created
  ** by the mkopcodeh.awk and mkopcodec.awk scripts which extract the
  ** information from the vdbe.c source text */
  qSrTahY7cdaX(IBMjGt5hp, eW0UCfzKNDESi, Ee05M7jDx_,
      wZgtGf(BYPQ->KMcyPZbh), BYPQ->mB_5hYOV5K, BYPQ->pPP2V5, BYPQ->BTBDVdeO3P,
      JrmG5OAto30B ? JrmG5OAto30B : "", BYPQ->I4yL,
      EQx73w ? EQx73w : ""
  );
  sAOUh6(IBMjGt5hp);
  CMhAT(JrmG5OAto30B);
  CMhAT(EQx73w);
  iLnX71QEMOnG();
}
#endif

/*
** Initialize an array of N Mem element.
**
** This is a high-runner, so only those fields that really do need to
** be initialized are set.  The Mem structure is organized so that
** the fields that get initialized are nearby and hopefully on the same
** cache line.
**
**    Mem.flags = flags
**    Mem.db = db
**    Mem.szMalloc = 0
**
** All other fields of Mem can safely remain uninitialized for now.  They
** will be initialized before use.
*/
static void JSqiudvcT33(oi4q2s5KcMX9Y *RWdNEx2WUIO8x, int YLqByqgGKPr, MEeQFpE4DzbZ *pLMJg2Xd, k1VeKpK MRNoo5HiPBk7){
  if( YLqByqgGKPr>0 ){
    do{
      RWdNEx2WUIO8x->MRNoo5HiPBk7 = MRNoo5HiPBk7;
      RWdNEx2WUIO8x->pLMJg2Xd = pLMJg2Xd;
      RWdNEx2WUIO8x->N3A21Ra4MY24m = 0;
#ifdef iteB65TL5L
      RWdNEx2WUIO8x->b8MaB = 0;
#endif
      RWdNEx2WUIO8x++;
    }while( (--YLqByqgGKPr)>0 );
  }
}

/*
** Release auxiliary memory held in an array of N Mem elements.
**
** After this routine returns, all Mem elements in the array will still
** be valid.  Those Mem elements that were not holding auxiliary resources
** will be unchanged.  Mem elements which had something freed will be
** set to MEM_Undefined.
*/
static void C4w0fxT16GXQr(oi4q2s5KcMX9Y *RWdNEx2WUIO8x, int YLqByqgGKPr){
  if( RWdNEx2WUIO8x && YLqByqgGKPr ){
    oi4q2s5KcMX9Y *nP3O0Y5lOeP = &RWdNEx2WUIO8x[YLqByqgGKPr];
    MEeQFpE4DzbZ *pLMJg2Xd = RWdNEx2WUIO8x->pLMJg2Xd;
    if( pLMJg2Xd->mMBxdHckzgHIl ){
      do{
        if( RWdNEx2WUIO8x->N3A21Ra4MY24m ) UXHgfYQ(pLMJg2Xd, RWdNEx2WUIO8x->DH15);
      }while( (++RWdNEx2WUIO8x)<nP3O0Y5lOeP );
      return;
    }
    do{
      f5IeCeK0e1W( (&RWdNEx2WUIO8x[1])==nP3O0Y5lOeP || RWdNEx2WUIO8x[0].pLMJg2Xd==RWdNEx2WUIO8x[1].pLMJg2Xd );
      f5IeCeK0e1W( Padq1s(RWdNEx2WUIO8x) );

      /* This block is really an inlined version of sqlite3VdbeMemRelease()
      ** that takes advantage of the fact that the memory cell value is
      ** being set to NULL after releasing any dynamic resources.
      **
      ** The justification for duplicating code is that according to
      ** callgrind, this causes a certain test case to hit the CPU 4.7
      ** percent less (x86 linux, gcc version 4.1.2, -O6) than if
      ** sqlite3MemRelease() were called from here. With -O2, this jumps
      ** to 6.6 percent. The test case is inserting 1000 rows into a table
      ** with no indexes using a single prepared INSERT statement, bind()
      ** and reset(). Inserts are grouped into a transaction.
      */
      gwlDS2AhlE3Xe( RWdNEx2WUIO8x->MRNoo5HiPBk7 & r5aK29G );
      gwlDS2AhlE3Xe( RWdNEx2WUIO8x->MRNoo5HiPBk7 & tJpW );
      if( RWdNEx2WUIO8x->MRNoo5HiPBk7&(r5aK29G|tJpW) ){
        gwlDS2AhlE3Xe( (RWdNEx2WUIO8x->MRNoo5HiPBk7 & tJpW)!=0 && RWdNEx2WUIO8x->oSHN6==HBFPDd );
        bFVk(RWdNEx2WUIO8x);
        RWdNEx2WUIO8x->MRNoo5HiPBk7 = eNZ5apG;
      }else if( RWdNEx2WUIO8x->N3A21Ra4MY24m ){
        CTQ2V30yU(pLMJg2Xd, RWdNEx2WUIO8x->DH15);
        RWdNEx2WUIO8x->N3A21Ra4MY24m = 0;
        RWdNEx2WUIO8x->MRNoo5HiPBk7 = eNZ5apG;
      }
#ifdef iteB65TL5L
      else{
        RWdNEx2WUIO8x->MRNoo5HiPBk7 = eNZ5apG;
      }
#endif
    }while( (++RWdNEx2WUIO8x)<nP3O0Y5lOeP );
  }
}

#ifdef iteB65TL5L
/*
** Verify that pFrame is a valid VdbeFrame pointer.  Return true if it is
** and false if something is wrong.
**
** This routine is intended for use inside of assert() statements only.
*/
int DcMr(Duojq *W11REIvF){
  if( W11REIvF->O3UQvmF!=PTQiCniT ) return 0;
  return 1;
}
#endif


/*
** This is a destructor on a Mem object (which is really an sqlite3_value)
** that deletes the Frame object that is attached to it as a blob.
**
** This routine does not delete the Frame right away.  It merely adds the
** frame to a list of frames to be deleted when the Vdbe halts.
*/
void HBFPDd(void *eHUmAkGIL){
  Duojq *W11REIvF = (Duojq*)eHUmAkGIL;
  f5IeCeK0e1W( DcMr(W11REIvF) );
  W11REIvF->TmMom = W11REIvF->HB_T1jBCLdNzN->REUPzb;
  W11REIvF->HB_T1jBCLdNzN->REUPzb = W11REIvF;
}

#if pZX7GD4OTcuV(BEHHsj) || !pZX7GD4OTcuV(r5Oia2csX9Q2n)
/*
** Locate the next opcode to be displayed in EXPLAIN or EXPLAIN
** QUERY PLAN output.
**
** Return SQLITE_ROW on success.  Return SQLITE_DONE if there are no
** more opcodes to be displayed.
*/
int WeoT01rpD1gS0(
  Y4zzrBxD4OXTO *RWdNEx2WUIO8x,         /* The statement being explained */
  oi4q2s5KcMX9Y *c7Jyu,       /* Storage for keeping track of subprogram nesting */
  int pTCJwP,       /* 0: normal.  1: EQP.  2:  TablesUsed */
  int *Sa55f3N,       /* IN/OUT: Current rowid.  Overwritten with next rowid */
  int *PT2aKC,     /* OUT: Write index into (*paOp)[] here */
  mHYCosji8c **f5C3exQ        /* OUT: Write the opcode array here */
){
  int lJuEp;                            /* Stop when row count reaches this */
  int DQQwikf4SSVd5 = 0;                        /* Number of sub-vdbes seen so far */
  RnzBAc3QE **HOlrZBYT5UB = 0;              /* Array of sub-vdbes */
  int Pyy0l6xD;                               /* Next instruction address */
  int YPgcEHzPuCIF = odQX7vL;                  /* Result code */
  mHYCosji8c *V7Y0VHDmd1Xf = 0;                         /* Opcode array */
  int sXlZnsCmnob;                             /* Rowid.  Copy of value in *piPc */

  /* When the number of output rows reaches nRow, that means the
  ** listing has finished and sqlite3_step() should return SQLITE_DONE.
  ** nRow is the sum of the number of rows in the main program, plus
  ** the sum of the number of rows in all trigger subprograms encountered
  ** so far.  The nRow value will increase as new trigger subprograms are
  ** encountered, but p->pc will eventually catch up to nRow.
  */
  lJuEp = RWdNEx2WUIO8x->rtaUFjmY;
  if( c7Jyu!=0 ){
    if( c7Jyu->MRNoo5HiPBk7&GrDQtTd ){
      /* pSub is initiallly NULL.  It is initialized to a BLOB by
      ** the P4_SUBPROGRAM processing logic below */
      DQQwikf4SSVd5 = c7Jyu->AS0ycVs/sizeof(Y4zzrBxD4OXTO*);
      HOlrZBYT5UB = (RnzBAc3QE **)c7Jyu->mrgekw0xj;
    }
    for(Pyy0l6xD=0; Pyy0l6xD<DQQwikf4SSVd5; Pyy0l6xD++){
      lJuEp += HOlrZBYT5UB[Pyy0l6xD]->rtaUFjmY;
    }
  }
  sXlZnsCmnob = *Sa55f3N;
  while(1){  /* Loop exits via break */
    Pyy0l6xD = sXlZnsCmnob++;
    if( Pyy0l6xD>=lJuEp ){
      RWdNEx2WUIO8x->YPgcEHzPuCIF = odQX7vL;
      YPgcEHzPuCIF = i5VlL;
      break;
    }
    if( Pyy0l6xD<RWdNEx2WUIO8x->rtaUFjmY ){
      /* The rowid is small enough that we are still in the
      ** main program. */
      V7Y0VHDmd1Xf = RWdNEx2WUIO8x->V7Y0VHDmd1Xf;
    }else{
      /* We are currently listing subprograms.  Figure out which one and
      ** pick up the appropriate opcode. */
      int fg6dGr;
      Pyy0l6xD -= RWdNEx2WUIO8x->rtaUFjmY;
      f5IeCeK0e1W( HOlrZBYT5UB!=0 );
      f5IeCeK0e1W( DQQwikf4SSVd5>0 );
      for(fg6dGr=0; Pyy0l6xD>=HOlrZBYT5UB[fg6dGr]->rtaUFjmY; fg6dGr++){
        Pyy0l6xD -= HOlrZBYT5UB[fg6dGr]->rtaUFjmY;
        f5IeCeK0e1W( Pyy0l6xD<HOlrZBYT5UB[fg6dGr]->rtaUFjmY || fg6dGr+1<DQQwikf4SSVd5 );
      }
      V7Y0VHDmd1Xf = HOlrZBYT5UB[fg6dGr]->V7Y0VHDmd1Xf;
    }

    /* When an OP_Program opcode is encounter (the only opcode that has
    ** a P4_SUBPROGRAM argument), expand the size of the array of subprograms
    ** kept in p->aMem[9].z to hold the new program - assuming this subprogram
    ** has not already been seen.
    */
    if( c7Jyu!=0 && V7Y0VHDmd1Xf[Pyy0l6xD].ZP4P_QR4oE==JbYHBRv ){
      int jCneFxRQnw = (DQQwikf4SSVd5+1)*sizeof(RnzBAc3QE*);
      int fg6dGr;
      for(fg6dGr=0; fg6dGr<DQQwikf4SSVd5; fg6dGr++){
        if( HOlrZBYT5UB[fg6dGr]==V7Y0VHDmd1Xf[Pyy0l6xD].vO1m9d.IbbDoqgyL ) break;
      }
      if( fg6dGr==DQQwikf4SSVd5 ){
        RWdNEx2WUIO8x->YPgcEHzPuCIF = QlH41(c7Jyu, jCneFxRQnw, DQQwikf4SSVd5!=0);
        if( RWdNEx2WUIO8x->YPgcEHzPuCIF!=odQX7vL ){
          YPgcEHzPuCIF = Xcvmwgu;
          break;
        }
        HOlrZBYT5UB = (RnzBAc3QE **)c7Jyu->mrgekw0xj;
        HOlrZBYT5UB[DQQwikf4SSVd5++] = V7Y0VHDmd1Xf[Pyy0l6xD].vO1m9d.IbbDoqgyL;
        LFjS5F(c7Jyu, GrDQtTd);
        c7Jyu->AS0ycVs = DQQwikf4SSVd5*sizeof(RnzBAc3QE*);
        lJuEp += V7Y0VHDmd1Xf[Pyy0l6xD].vO1m9d.IbbDoqgyL->rtaUFjmY;
      }
    }
    if( pTCJwP==0 ) break;
#ifdef BEHHsj
    if( pTCJwP==2 ){
      mHYCosji8c *BYPQ = V7Y0VHDmd1Xf + Pyy0l6xD;
      if( BYPQ->KMcyPZbh==ybjgdOh0ziD ) break;
      if( BYPQ->KMcyPZbh==nDSyZbgHe && (BYPQ->I4yL & FZRBJT31SB_ij)==0 ) break;
      if( BYPQ->KMcyPZbh==WuC2_oW3z ) break;     
    }else
#endif
    {
      f5IeCeK0e1W( pTCJwP==1 );
      if( V7Y0VHDmd1Xf[Pyy0l6xD].KMcyPZbh==WLqXtjk5Ez ) break;
      if( V7Y0VHDmd1Xf[Pyy0l6xD].KMcyPZbh==EXKa_CQA && sXlZnsCmnob>1 ) break;
    }
  }
  *Sa55f3N = sXlZnsCmnob;
  *PT2aKC = Pyy0l6xD;
  *f5C3exQ = V7Y0VHDmd1Xf;
  return YPgcEHzPuCIF;
}
#endif /* SQLITE_ENABLE_BYTECODE_VTAB || !SQLITE_OMIT_EXPLAIN */


/*
** Delete a VdbeFrame object and its contents. VdbeFrame objects are
** allocated by the OP_Program opcode in sqlite3VdbeExec().
*/
void Z99qs(Duojq *RWdNEx2WUIO8x){
  int Pyy0l6xD;
  oi4q2s5KcMX9Y *CSO_5 = dAxN(RWdNEx2WUIO8x);
  Jmdb **L5eY = (Jmdb **)&CSO_5[RWdNEx2WUIO8x->lfB3A];
  f5IeCeK0e1W( DcMr(RWdNEx2WUIO8x) );
  for(Pyy0l6xD=0; Pyy0l6xD<RWdNEx2WUIO8x->n_n6ZvvPFC; Pyy0l6xD++){
    if( L5eY[Pyy0l6xD] ) ZBTHkvRhsedIn(RWdNEx2WUIO8x->HB_T1jBCLdNzN, L5eY[Pyy0l6xD]);
  }
  C4w0fxT16GXQr(CSO_5, RWdNEx2WUIO8x->lfB3A);
  Ay89(RWdNEx2WUIO8x->HB_T1jBCLdNzN->pLMJg2Xd, &RWdNEx2WUIO8x->n0sFb4U0UGaX, -1, 0);
  UXHgfYQ(RWdNEx2WUIO8x->HB_T1jBCLdNzN->pLMJg2Xd, RWdNEx2WUIO8x);
}

#ifndef r5Oia2csX9Q2n
/*
** Give a listing of the program in the virtual machine.
**
** The interface is the same as sqlite3VdbeExec().  But instead of
** running the code, it invokes the callback once for each instruction.
** This feature is used to implement "EXPLAIN".
**
** When p->explain==1, each instruction is listed.  When
** p->explain==2, only OP_Explain instructions are listed and these
** are shown in a different format.  p->explain==2 is used to implement
** EXPLAIN QUERY PLAN.
** 2018-04-24:  In p->explain==2 mode, the OP_Init opcodes of triggers
** are also shown, so that the boundaries between the main program and
** each trigger are clear.
**
** When p->explain==1, first the main program is listed, then each of
** the trigger subprograms are listed one by one.
*/
int vwoB(
  Y4zzrBxD4OXTO *RWdNEx2WUIO8x                   /* The VDBE */
){
  oi4q2s5KcMX9Y *c7Jyu = 0;                       /* Memory cell hold array of subprogs */
  MEeQFpE4DzbZ *pLMJg2Xd = RWdNEx2WUIO8x->pLMJg2Xd;                 /* The database connection */
  int Pyy0l6xD;                               /* Loop counter */
  int YPgcEHzPuCIF = odQX7vL;                  /* Return code */
  oi4q2s5KcMX9Y *ZAHT = &RWdNEx2WUIO8x->CSO_5[1];             /* First Mem of result set */
  int aVk8IlIil2v = (RWdNEx2WUIO8x->Iq7PbEyhO==1 || (pLMJg2Xd->MRNoo5HiPBk7 & mUCWmwUICkE)!=0);
  mHYCosji8c *V7Y0VHDmd1Xf;                             /* Array of opcodes */
  mHYCosji8c *BYPQ;                             /* Current opcode */

  f5IeCeK0e1W( RWdNEx2WUIO8x->Iq7PbEyhO );
  f5IeCeK0e1W( RWdNEx2WUIO8x->C19t==aaNsbqAVumJ );
  f5IeCeK0e1W( RWdNEx2WUIO8x->YPgcEHzPuCIF==odQX7vL || RWdNEx2WUIO8x->YPgcEHzPuCIF==SDNGPshgqu || RWdNEx2WUIO8x->YPgcEHzPuCIF==ccKsEfbei4 );

  /* Even though this opcode does not use dynamic strings for
  ** the result, result columns may become dynamic if the user calls
  ** sqlite3_column_text16(), causing a translation to UTF-16 encoding.
  */
  C4w0fxT16GXQr(ZAHT, 8);

  if( RWdNEx2WUIO8x->YPgcEHzPuCIF==ccKsEfbei4 ){
    /* This happens if a malloc() inside a call to sqlite3_column_text() or
    ** sqlite3_column_text16() failed.  */
    I_fGWFjD(pLMJg2Xd);
    return Xcvmwgu;
  }

  if( aVk8IlIil2v ){
    /* The first 8 memory cells are used for the result set.  So we will
    ** commandeer the 9th cell to use as storage for an array of pointers
    ** to trigger subprograms.  The VDBE is guaranteed to have at least 9
    ** cells.  */
    f5IeCeK0e1W( RWdNEx2WUIO8x->Om1f>9 );
    c7Jyu = &RWdNEx2WUIO8x->CSO_5[9];
  }else{
    c7Jyu = 0;
  }

  /* Figure out which opcode is next to display */
  YPgcEHzPuCIF = WeoT01rpD1gS0(RWdNEx2WUIO8x, c7Jyu, RWdNEx2WUIO8x->Iq7PbEyhO==2, &RWdNEx2WUIO8x->Ee05M7jDx_, &Pyy0l6xD, &V7Y0VHDmd1Xf);

  if( YPgcEHzPuCIF==odQX7vL ){
    BYPQ = V7Y0VHDmd1Xf + Pyy0l6xD;
    if( EBBP3N(&pLMJg2Xd->Y0evIT_y_kz9.s6r5L) ){
      RWdNEx2WUIO8x->YPgcEHzPuCIF = FBHQ;
      YPgcEHzPuCIF = Xcvmwgu;
      haAKYIBsgAl(RWdNEx2WUIO8x, dFDl(RWdNEx2WUIO8x->YPgcEHzPuCIF));
    }else{
      char *JrmG5OAto30B = kDaR08PC(pLMJg2Xd, BYPQ);
      if( RWdNEx2WUIO8x->Iq7PbEyhO==2 ){
        or4F(ZAHT, BYPQ->mB_5hYOV5K);
        or4F(ZAHT+1, BYPQ->pPP2V5);
        or4F(ZAHT+2, BYPQ->BTBDVdeO3P);
        VH1pEzb(ZAHT+3, JrmG5OAto30B, -1, XaWPmn7sUsHo4, CMhAT);
        f5IeCeK0e1W( RWdNEx2WUIO8x->U70ZTovLy==4 );
      }else{
        or4F(ZAHT+0, Pyy0l6xD);
        VH1pEzb(ZAHT+1, (char*)wZgtGf(BYPQ->KMcyPZbh),
                             -1, XaWPmn7sUsHo4, tvjGCKDaEP);
        or4F(ZAHT+2, BYPQ->mB_5hYOV5K);
        or4F(ZAHT+3, BYPQ->pPP2V5);
        or4F(ZAHT+4, BYPQ->BTBDVdeO3P);
        /* pMem+5 for p4 is done last */
        or4F(ZAHT+6, BYPQ->I4yL);
#ifdef faD_O9XSX
        {
          char *EQx73w = uPa2XJzUAcRsC(pLMJg2Xd, BYPQ, JrmG5OAto30B);
          VH1pEzb(ZAHT+7, EQx73w, -1, XaWPmn7sUsHo4, CMhAT);
        }
#else
        mPpWxtg4C(ZAHT+7);
#endif
        VH1pEzb(ZAHT+5, JrmG5OAto30B, -1, XaWPmn7sUsHo4, CMhAT);
        f5IeCeK0e1W( RWdNEx2WUIO8x->U70ZTovLy==8 );
      }
      RWdNEx2WUIO8x->iS3t7tw2Bjx = ZAHT;
      if( pLMJg2Xd->mi4oOCmRVN_h ){
        RWdNEx2WUIO8x->YPgcEHzPuCIF = ccKsEfbei4;
        YPgcEHzPuCIF = Xcvmwgu;
      }else{
        RWdNEx2WUIO8x->YPgcEHzPuCIF = odQX7vL;
        YPgcEHzPuCIF = VNFhaiJG8Vi3l;
      }
    }
  }
  return YPgcEHzPuCIF;
}
#endif /* SQLITE_OMIT_EXPLAIN */

#ifdef iteB65TL5L
/*
** Print the SQL that was used to generate a VDBE program.
*/
void gWEF(Y4zzrBxD4OXTO *RWdNEx2WUIO8x){
  const char *mrgekw0xj = 0;
  if( RWdNEx2WUIO8x->W1REkwE ){
    mrgekw0xj = RWdNEx2WUIO8x->W1REkwE;
  }else if( RWdNEx2WUIO8x->rtaUFjmY>=1 ){
    const kqPOQZYA16d *BYPQ = &RWdNEx2WUIO8x->V7Y0VHDmd1Xf[0];
    if( BYPQ->KMcyPZbh==EXKa_CQA && BYPQ->vO1m9d.mrgekw0xj!=0 ){
      mrgekw0xj = BYPQ->vO1m9d.mrgekw0xj;
      while( SwXrqLkdwNTM(*mrgekw0xj) ) mrgekw0xj++;
    }
  }
  if( mrgekw0xj ) FNEgs("SQL: [%s]\n", mrgekw0xj);
}
#endif

#if !pZX7GD4OTcuV(v_awKz2Smz) && pZX7GD4OTcuV(J8H30SdBWI1oW)
/*
** Print an IOTRACE message showing SQL content.
*/
void bTTJJNgz6DyJl(Y4zzrBxD4OXTO *RWdNEx2WUIO8x){
  int rtaUFjmY = RWdNEx2WUIO8x->rtaUFjmY;
  kqPOQZYA16d *BYPQ;
  if( Ys7mZvZx6ZaU2==0 ) return;
  if( rtaUFjmY<1 ) return;
  BYPQ = &RWdNEx2WUIO8x->V7Y0VHDmd1Xf[0];
  if( BYPQ->KMcyPZbh==EXKa_CQA && BYPQ->vO1m9d.mrgekw0xj!=0 ){
    int Pyy0l6xD, fg6dGr;
    char mrgekw0xj[1000];
    xyTnraEFT(sizeof(mrgekw0xj), mrgekw0xj, "%s", BYPQ->vO1m9d.mrgekw0xj);
    for(Pyy0l6xD=0; SwXrqLkdwNTM(mrgekw0xj[Pyy0l6xD]); Pyy0l6xD++){}
    for(fg6dGr=0; mrgekw0xj[Pyy0l6xD]; Pyy0l6xD++){
      if( SwXrqLkdwNTM(mrgekw0xj[Pyy0l6xD]) ){
        if( mrgekw0xj[Pyy0l6xD-1]!=' ' ){
          mrgekw0xj[fg6dGr++] = ' ';
        }
      }else{
        mrgekw0xj[fg6dGr++] = mrgekw0xj[Pyy0l6xD];
      }
    }
    mrgekw0xj[fg6dGr] = 0;
    Ys7mZvZx6ZaU2("SQL %s\n", mrgekw0xj);
  }
}
#endif /* !SQLITE_OMIT_TRACE && SQLITE_ENABLE_IOTRACE */

/* An instance of this object describes bulk memory available for use
** by subcomponents of a prepared statement.  Space is allocated out
** of a ReusableSpace object by the allocSpace() routine below.
*/
struct i0pP5vpLCH7 {
  qHh5JW *DjLsMRzR4CJ;            /* Available memory */
  OfeosV3WSPC gxehPXW;   /* Bytes of available memory */
  OfeosV3WSPC mdVThonePIrAq; /* Total bytes that could not be allocated */
};

/* Try to allocate nByte bytes of 8-byte aligned bulk memory for pBuf
** from the ReusableSpace object.  Return a pointer to the allocated
** memory on success.  If insufficient memory is available in the
** ReusableSpace object, increase the ReusableSpace.nNeeded
** value by the amount needed and return NULL.
**
** If pBuf is not initially NULL, that means that the memory has already
** been allocated by a prior call to this routine, so just return a copy
** of pBuf and leave ReusableSpace unchanged.
**
** This allocator is employed to repurpose unused slots at the end of the
** opcode array of prepared state for other memory needs of the prepared
** statement.
*/
static void *K726(
  struct i0pP5vpLCH7 *RWdNEx2WUIO8x,  /* Bulk memory available for allocation */
  void *xI4oyHA,               /* Pointer to a prior allocation */
  OfeosV3WSPC jCneFxRQnw       /* Bytes of memory needed. */
){
  f5IeCeK0e1W( UbnT4(RWdNEx2WUIO8x->DjLsMRzR4CJ) );
  if( xI4oyHA==0 ){
    jCneFxRQnw = c7n37T(jCneFxRQnw);
    if( jCneFxRQnw <= RWdNEx2WUIO8x->gxehPXW ){
      RWdNEx2WUIO8x->gxehPXW -= jCneFxRQnw;
      xI4oyHA = &RWdNEx2WUIO8x->DjLsMRzR4CJ[RWdNEx2WUIO8x->gxehPXW];
    }else{
      RWdNEx2WUIO8x->mdVThonePIrAq += jCneFxRQnw;
    }
  }
  f5IeCeK0e1W( UbnT4(xI4oyHA) );
  return xI4oyHA;
}

/*
** Rewind the VDBE back to the beginning in preparation for
** running it.
*/
void fJDPengPa(Y4zzrBxD4OXTO *RWdNEx2WUIO8x){
#if pZX7GD4OTcuV(iteB65TL5L)
  int Pyy0l6xD;
#endif
  f5IeCeK0e1W( RWdNEx2WUIO8x!=0 );
  f5IeCeK0e1W( RWdNEx2WUIO8x->C19t==w_rp1wwh
       || RWdNEx2WUIO8x->C19t==v1s7
       || RWdNEx2WUIO8x->C19t==uCr0O83sgOI );

  /* There should be at least one opcode.
  */
  f5IeCeK0e1W( RWdNEx2WUIO8x->rtaUFjmY>0 );

  RWdNEx2WUIO8x->C19t = v1s7;

#ifdef iteB65TL5L
  for(Pyy0l6xD=0; Pyy0l6xD<RWdNEx2WUIO8x->Om1f; Pyy0l6xD++){
    f5IeCeK0e1W( RWdNEx2WUIO8x->CSO_5[Pyy0l6xD].pLMJg2Xd==RWdNEx2WUIO8x->pLMJg2Xd );
  }
#endif
  RWdNEx2WUIO8x->Ee05M7jDx_ = -1;
  RWdNEx2WUIO8x->YPgcEHzPuCIF = odQX7vL;
  RWdNEx2WUIO8x->nc8VDQwv = wdf01;
  RWdNEx2WUIO8x->SnFm = 0;
  RWdNEx2WUIO8x->MUbB3t = 1;
  RWdNEx2WUIO8x->mz3Zz_JyooBP = 255;
  RWdNEx2WUIO8x->WRXmlSkV = 0;
  RWdNEx2WUIO8x->X98o5OdZ7Do7 = 0;
#ifdef fsSLSO_wyCxfR
  for(Pyy0l6xD=0; Pyy0l6xD<RWdNEx2WUIO8x->rtaUFjmY; Pyy0l6xD++){
    RWdNEx2WUIO8x->V7Y0VHDmd1Xf[Pyy0l6xD].GtnbWK = 0;
    RWdNEx2WUIO8x->V7Y0VHDmd1Xf[Pyy0l6xD].UKXyt_q = 0;
  }
#endif
}

/*
** Prepare a virtual machine for execution for the first time after
** creating the virtual machine.  This involves things such
** as allocating registers and initializing the program counter.
** After the VDBE has be prepped, it can be executed by one or more
** calls to sqlite3VdbeExec(). 
**
** This function may be called exactly once on each virtual machine.
** After this routine is called the VM has been "packaged" and is ready
** to run.  After this routine is called, further calls to
** sqlite3VdbeAddOp() functions are prohibited.  This routine disconnects
** the Vdbe from the Parse object that helped generate it so that the
** the Vdbe becomes an independent entity and the Parse object can be
** destroyed.
**
** Use the sqlite3VdbeRewind() procedure to restore a virtual machine back
** to its initial state after it has been run.
*/
void Br62K1mrR5h(
  Y4zzrBxD4OXTO *RWdNEx2WUIO8x,                       /* The VDBE */
  MSufNwYJMUIW *CZswHrqPXTX                  /* Parsing context */
){
  MEeQFpE4DzbZ *pLMJg2Xd;                   /* The database connection */
  int u5EP6Pex2vAp;                      /* Number of parameters */
  int Om1f;                      /* Number of VM memory registers */
  int UdjSsCqdOX;                   /* Number of cursors required */
  int WL_eiS;                      /* Number of arguments in subprograms */
  int AS0ycVs;                         /* Loop counter */
  struct i0pP5vpLCH7 zCVq;        /* Reusable bulk memory */

  f5IeCeK0e1W( RWdNEx2WUIO8x!=0 );
  f5IeCeK0e1W( RWdNEx2WUIO8x->rtaUFjmY>0 );
  f5IeCeK0e1W( CZswHrqPXTX!=0 );
  f5IeCeK0e1W( RWdNEx2WUIO8x->C19t==w_rp1wwh );
  f5IeCeK0e1W( CZswHrqPXTX==RWdNEx2WUIO8x->CZswHrqPXTX );
  RWdNEx2WUIO8x->E2ONFI4w8YJV = CZswHrqPXTX->E2ONFI4w8YJV;
  CZswHrqPXTX->E2ONFI4w8YJV =  0;
  pLMJg2Xd = RWdNEx2WUIO8x->pLMJg2Xd;
  f5IeCeK0e1W( pLMJg2Xd->mi4oOCmRVN_h==0 );
  u5EP6Pex2vAp = CZswHrqPXTX->u5EP6Pex2vAp;
  Om1f = CZswHrqPXTX->Om1f;
  UdjSsCqdOX = CZswHrqPXTX->IsOA;
  WL_eiS = CZswHrqPXTX->HIlDTEZpIB;
 
  /* Each cursor uses a memory cell.  The first cursor (cursor 0) can
  ** use aMem[0] which is not otherwise used by the VDBE program.  Allocate
  ** space at the end of aMem[] for cursors 1 and greater.
  ** See also: allocateCursor().
  */
  Om1f += UdjSsCqdOX;
  if( UdjSsCqdOX==0 && Om1f>0 ) Om1f++;  /* Space for aMem[0] even if not used */

  /* Figure out how much reusable memory is available at the end of the
  ** opcode array.  This extra memory will be reallocated for other elements
  ** of the prepared statement.
  */
  AS0ycVs = c7n37T(sizeof(mHYCosji8c)*RWdNEx2WUIO8x->rtaUFjmY);             /* Bytes of opcode memory used */
  zCVq.DjLsMRzR4CJ = &((qHh5JW*)RWdNEx2WUIO8x->V7Y0VHDmd1Xf)[AS0ycVs];               /* Unused opcode memory */
  f5IeCeK0e1W( UbnT4(zCVq.DjLsMRzR4CJ) );
  zCVq.gxehPXW = UE3Ayz(CZswHrqPXTX->YbLEhxQ - AS0ycVs);  /* Bytes of unused memory */
  f5IeCeK0e1W( zCVq.gxehPXW>=0 );
  f5IeCeK0e1W( UbnT4(&zCVq.DjLsMRzR4CJ[zCVq.gxehPXW]) );

  MDNdD1BZG5m_(RWdNEx2WUIO8x, &WL_eiS);
  RWdNEx2WUIO8x->Sw32GUoVJzP4 = (qHh5JW)(CZswHrqPXTX->bUtLjtydFbp2 && CZswHrqPXTX->zOHH6Y096Svr1);
  if( CZswHrqPXTX->Iq7PbEyhO ){
    if( Om1f<10 ) Om1f = 10;
    RWdNEx2WUIO8x->Iq7PbEyhO = CZswHrqPXTX->Iq7PbEyhO;
    RWdNEx2WUIO8x->U70ZTovLy = 12 - 4*RWdNEx2WUIO8x->Iq7PbEyhO;
  }
  RWdNEx2WUIO8x->VYYUN2ZWE6 = 0;

  /* Memory for registers, parameters, cursor, etc, is allocated in one or two
  ** passes.  On the first pass, we try to reuse unused memory at the
  ** end of the opcode array.  If we are unable to satisfy all memory
  ** requirements by reusing the opcode array tail, then the second
  ** pass will fill in the remainder using a fresh memory allocation. 
  **
  ** This two-pass approach that reuses as much memory as possible from
  ** the leftover memory at the end of the opcode array.  This can significantly
  ** reduce the amount of memory held by a prepared statement.
  */
  zCVq.mdVThonePIrAq = 0;
  RWdNEx2WUIO8x->CSO_5 = K726(&zCVq, 0, Om1f*sizeof(oi4q2s5KcMX9Y));
  RWdNEx2WUIO8x->dHLFi0U0rI5oH = K726(&zCVq, 0, u5EP6Pex2vAp*sizeof(oi4q2s5KcMX9Y));
  RWdNEx2WUIO8x->U5F84M0GJmeUI = K726(&zCVq, 0, WL_eiS*sizeof(oi4q2s5KcMX9Y*));
  RWdNEx2WUIO8x->L5eY = K726(&zCVq, 0, UdjSsCqdOX*sizeof(Jmdb*));
  if( zCVq.mdVThonePIrAq ){
    zCVq.DjLsMRzR4CJ = RWdNEx2WUIO8x->YJxTyv = j4Bew(pLMJg2Xd, zCVq.mdVThonePIrAq);
    zCVq.gxehPXW = zCVq.mdVThonePIrAq;
    if( !pLMJg2Xd->mi4oOCmRVN_h ){
      RWdNEx2WUIO8x->CSO_5 = K726(&zCVq, RWdNEx2WUIO8x->CSO_5, Om1f*sizeof(oi4q2s5KcMX9Y));
      RWdNEx2WUIO8x->dHLFi0U0rI5oH = K726(&zCVq, RWdNEx2WUIO8x->dHLFi0U0rI5oH, u5EP6Pex2vAp*sizeof(oi4q2s5KcMX9Y));
      RWdNEx2WUIO8x->U5F84M0GJmeUI = K726(&zCVq, RWdNEx2WUIO8x->U5F84M0GJmeUI, WL_eiS*sizeof(oi4q2s5KcMX9Y*));
      RWdNEx2WUIO8x->L5eY = K726(&zCVq, RWdNEx2WUIO8x->L5eY, UdjSsCqdOX*sizeof(Jmdb*));
    }
  }

  if( pLMJg2Xd->mi4oOCmRVN_h ){
    RWdNEx2WUIO8x->u5EP6Pex2vAp = 0;
    RWdNEx2WUIO8x->UdjSsCqdOX = 0;
    RWdNEx2WUIO8x->Om1f = 0;
  }else{
    RWdNEx2WUIO8x->UdjSsCqdOX = UdjSsCqdOX;
    RWdNEx2WUIO8x->u5EP6Pex2vAp = (K4rntCvKBezAL)u5EP6Pex2vAp;
    JSqiudvcT33(RWdNEx2WUIO8x->dHLFi0U0rI5oH, u5EP6Pex2vAp, pLMJg2Xd, NIJTPrY3UI);
    RWdNEx2WUIO8x->Om1f = Om1f;
    JSqiudvcT33(RWdNEx2WUIO8x->CSO_5, Om1f, pLMJg2Xd, eNZ5apG);
    gDRc26rrZnG_(RWdNEx2WUIO8x->L5eY, 0, UdjSsCqdOX*sizeof(Jmdb*));
  }
  fJDPengPa(RWdNEx2WUIO8x);
}

/*
** Close a VDBE cursor and release all the resources that cursor
** happens to hold.
*/
void PkuRshOsKdMv6(Y4zzrBxD4OXTO *RWdNEx2WUIO8x, Jmdb *D3ndTFOF13Vmu){
  if( D3ndTFOF13Vmu ) ZBTHkvRhsedIn(RWdNEx2WUIO8x,D3ndTFOF13Vmu);
}
static XmVnyUQh void DCXdyqtSd(Y4zzrBxD4OXTO *RWdNEx2WUIO8x, Jmdb *D3ndTFOF13Vmu){
  p_MIg *VgnUpSZaZbE = D3ndTFOF13Vmu->VgnUpSZaZbE;
  f5IeCeK0e1W( D3ndTFOF13Vmu->ZU44Hk );
  D3ndTFOF13Vmu->ZU44Hk = 0;
  D3ndTFOF13Vmu->VgnUpSZaZbE = 0;
  if( VgnUpSZaZbE->l18qFD8d ){
    mcokH(VgnUpSZaZbE->l18qFD8d);
    VgnUpSZaZbE->l18qFD8d = 0;
  }
  UXHgfYQ(RWdNEx2WUIO8x->pLMJg2Xd, VgnUpSZaZbE);
  ZBTHkvRhsedIn(RWdNEx2WUIO8x, D3ndTFOF13Vmu);
}
void ZBTHkvRhsedIn(Y4zzrBxD4OXTO *RWdNEx2WUIO8x, Jmdb *D3ndTFOF13Vmu){
  if( D3ndTFOF13Vmu->ZU44Hk ){
    DCXdyqtSd(RWdNEx2WUIO8x, D3ndTFOF13Vmu);
    return;
  }
  switch( D3ndTFOF13Vmu->lhtEl9aC9MU ){
    case SOgiV: {
      k274W7JN(RWdNEx2WUIO8x->pLMJg2Xd, D3ndTFOF13Vmu);
      break;
    }
    case lqUt: {
      f5IeCeK0e1W( D3ndTFOF13Vmu->b75S0uIj_5z.qtSltNrcEx!=0 );
      fUqq(D3ndTFOF13Vmu->b75S0uIj_5z.qtSltNrcEx);
      break;
    }
#ifndef uRsBKByRR
    case lYorH: {
      Ip9l1HJz_csZK *r0PB2U2dDYy = D3ndTFOF13Vmu->b75S0uIj_5z.r0PB2U2dDYy;
      const eoWm4 *ZF8fkhPIhZlo = r0PB2U2dDYy->X4AIzAFQeHOW->ZF8fkhPIhZlo;
      f5IeCeK0e1W( r0PB2U2dDYy->X4AIzAFQeHOW->TqtPrW>0 );
      r0PB2U2dDYy->X4AIzAFQeHOW->TqtPrW--;
      ZF8fkhPIhZlo->FM8mJ1x2d8L(r0PB2U2dDYy);
      break;
    }
#endif
  }
}

/*
** Close all cursors in the current frame.
*/
static void aF__uQA3dzS(Y4zzrBxD4OXTO *RWdNEx2WUIO8x){
  int Pyy0l6xD;
  for(Pyy0l6xD=0; Pyy0l6xD<RWdNEx2WUIO8x->UdjSsCqdOX; Pyy0l6xD++){
    Jmdb *SEIR9fLw_9 = RWdNEx2WUIO8x->L5eY[Pyy0l6xD];
    if( SEIR9fLw_9 ){
      ZBTHkvRhsedIn(RWdNEx2WUIO8x, SEIR9fLw_9);
      RWdNEx2WUIO8x->L5eY[Pyy0l6xD] = 0;
    }
  }
}

/*
** Copy the values stored in the VdbeFrame structure to its Vdbe. This
** is used, for example, when a trigger sub-program is halted to restore
** control to the main program.
*/
int TtEvV(Duojq *W11REIvF){
  Y4zzrBxD4OXTO *HB_T1jBCLdNzN = W11REIvF->HB_T1jBCLdNzN;
  aF__uQA3dzS(HB_T1jBCLdNzN);
  HB_T1jBCLdNzN->V7Y0VHDmd1Xf = W11REIvF->V7Y0VHDmd1Xf;
  HB_T1jBCLdNzN->rtaUFjmY = W11REIvF->rtaUFjmY;
  HB_T1jBCLdNzN->CSO_5 = W11REIvF->CSO_5;
  HB_T1jBCLdNzN->Om1f = W11REIvF->Om1f;
  HB_T1jBCLdNzN->L5eY = W11REIvF->L5eY;
  HB_T1jBCLdNzN->UdjSsCqdOX = W11REIvF->UdjSsCqdOX;
  HB_T1jBCLdNzN->pLMJg2Xd->VN96j7No = W11REIvF->VN96j7No;
  HB_T1jBCLdNzN->SnFm = W11REIvF->SnFm;
  HB_T1jBCLdNzN->pLMJg2Xd->SnFm = W11REIvF->S4mO;
  Ay89(HB_T1jBCLdNzN->pLMJg2Xd, &HB_T1jBCLdNzN->n0sFb4U0UGaX, -1, 0);
  HB_T1jBCLdNzN->n0sFb4U0UGaX = W11REIvF->n0sFb4U0UGaX;
  W11REIvF->n0sFb4U0UGaX = 0;
  return W11REIvF->Ee05M7jDx_;
}

/*
** Close all cursors.
**
** Also release any dynamic memory held by the VM in the Vdbe.aMem memory
** cell array. This is necessary as the memory cell array may contain
** pointers to VdbeFrame objects, which may in turn contain pointers to
** open cursors.
*/
static void WQUk0(Y4zzrBxD4OXTO *RWdNEx2WUIO8x){
  if( RWdNEx2WUIO8x->W11REIvF ){
    Duojq *W11REIvF;
    for(W11REIvF=RWdNEx2WUIO8x->W11REIvF; W11REIvF->TmMom; W11REIvF=W11REIvF->TmMom);
    TtEvV(W11REIvF);
    RWdNEx2WUIO8x->W11REIvF = 0;
    RWdNEx2WUIO8x->gOolTRT = 0;
  }
  f5IeCeK0e1W( RWdNEx2WUIO8x->gOolTRT==0 );
  aF__uQA3dzS(RWdNEx2WUIO8x);
  C4w0fxT16GXQr(RWdNEx2WUIO8x->CSO_5, RWdNEx2WUIO8x->Om1f);
  while( RWdNEx2WUIO8x->REUPzb ){
    Duojq *t2nMtT = RWdNEx2WUIO8x->REUPzb;
    RWdNEx2WUIO8x->REUPzb = t2nMtT->TmMom;
    Z99qs(t2nMtT);
  }

  /* Delete any auxdata allocations made by the VM */
  if( RWdNEx2WUIO8x->n0sFb4U0UGaX ) Ay89(RWdNEx2WUIO8x->pLMJg2Xd, &RWdNEx2WUIO8x->n0sFb4U0UGaX, -1, 0);
  f5IeCeK0e1W( RWdNEx2WUIO8x->n0sFb4U0UGaX==0 );
}

/*
** Set the number of result columns that will be returned by this SQL
** statement. This is now set at compile time, rather than during
** execution of the vdbe program so that sqlite3_column_count() can
** be called on an SQL statement before sqlite3_step().
*/
void LCmwy7CzRUTbm(Y4zzrBxD4OXTO *RWdNEx2WUIO8x, int U70ZTovLy){
  int AS0ycVs;
  MEeQFpE4DzbZ *pLMJg2Xd = RWdNEx2WUIO8x->pLMJg2Xd;

  if( RWdNEx2WUIO8x->waWG ){
    C4w0fxT16GXQr(RWdNEx2WUIO8x->XCYp, RWdNEx2WUIO8x->waWG*IlYFtUVZ);
    UXHgfYQ(pLMJg2Xd, RWdNEx2WUIO8x->XCYp);
  }
  AS0ycVs = U70ZTovLy*IlYFtUVZ;
  RWdNEx2WUIO8x->U70ZTovLy = RWdNEx2WUIO8x->waWG = (k1VeKpK)U70ZTovLy;
  RWdNEx2WUIO8x->XCYp = (oi4q2s5KcMX9Y*)j4Bew(pLMJg2Xd, sizeof(oi4q2s5KcMX9Y)*AS0ycVs );
  if( RWdNEx2WUIO8x->XCYp==0 ) return;
  JSqiudvcT33(RWdNEx2WUIO8x->XCYp, AS0ycVs, pLMJg2Xd, NIJTPrY3UI);
}

/*
** Set the name of the idx'th column to be returned by the SQL statement.
** zName must be a pointer to a nul terminated string.
**
** This call must be made after a call to sqlite3VdbeSetNumCols().
**
** The final parameter, xDel, must be one of SQLITE_DYNAMIC, SQLITE_STATIC
** or SQLITE_TRANSIENT. If it is SQLITE_DYNAMIC, then the buffer pointed
** to by zName will be freed by sqlite3DbFree() when the vdbe is destroyed.
*/
int fO4gK5Sxro(
  Y4zzrBxD4OXTO *RWdNEx2WUIO8x,                         /* Vdbe being configured */
  int wrlhjKL_,                         /* Index of column zName applies to */
  int LhBf,                         /* One of the COLNAME_* constants */
  const char *wxojaeqHwik,               /* Pointer to buffer containing name */
  void (*oSHN6)(void*)              /* Memory management strategy for zName */
){
  int YPgcEHzPuCIF;
  oi4q2s5KcMX9Y *mNck;
  f5IeCeK0e1W( wrlhjKL_<RWdNEx2WUIO8x->waWG );
  f5IeCeK0e1W( LhBf<IlYFtUVZ );
  if( RWdNEx2WUIO8x->pLMJg2Xd->mi4oOCmRVN_h ){
    f5IeCeK0e1W( !wxojaeqHwik || oSHN6!=VTEyGaJ4 );
    return gbOccFBhQR;
  }
  f5IeCeK0e1W( RWdNEx2WUIO8x->XCYp!=0 );
  mNck = &(RWdNEx2WUIO8x->XCYp[wrlhjKL_+LhBf*RWdNEx2WUIO8x->waWG]);
  YPgcEHzPuCIF = VH1pEzb(mNck, wxojaeqHwik, -1, XaWPmn7sUsHo4, oSHN6);
  f5IeCeK0e1W( YPgcEHzPuCIF!=0 || !wxojaeqHwik || (mNck->MRNoo5HiPBk7&alF3obv)!=0 );
  return YPgcEHzPuCIF;
}

/*
** A read or write transaction may or may not be active on database handle
** db. If a transaction is active, commit it. If there is a
** write-transaction spanning more than one database file, this routine
** takes care of the super-journal trickery.
*/
static int KyWQVHQrB(MEeQFpE4DzbZ *pLMJg2Xd, Y4zzrBxD4OXTO *RWdNEx2WUIO8x){
  int Pyy0l6xD;
  int aq__uFP8Lff5C = 0;  /* Number of databases with an active write-transaction
                   ** that are candidates for a two-phase commit using a
                   ** super-journal */
  int YPgcEHzPuCIF = odQX7vL;
  int qOlWr = 0;

#ifdef uRsBKByRR
  /* With this option, sqlite3VtabSync() is defined to be simply
  ** SQLITE_OK so p is not used.
  */
  yhypAvj(RWdNEx2WUIO8x);
#endif

  /* Before doing anything else, call the xSync() callback for any
  ** virtual module tables written in this transaction. This has to
  ** be done before determining whether a super-journal file is
  ** required, as an xSync() callback may add an attached database
  ** to the transaction.
  */
  YPgcEHzPuCIF = hpPKK(pLMJg2Xd, RWdNEx2WUIO8x);

  /* This loop determines (a) if the commit hook should be invoked and
  ** (b) how many database files have open write transactions, not
  ** including the temp database. (b) is important because if more than
  ** one database file has an open write transaction, a super-journal
  ** file is required for an atomic commit.
  */
  for(Pyy0l6xD=0; YPgcEHzPuCIF==odQX7vL && Pyy0l6xD<pLMJg2Xd->rAyJ; Pyy0l6xD++){
    UAgP *UEF9V = pLMJg2Xd->cFohRY2vCC[Pyy0l6xD].UEF9V;
    if( SltXbyIzCS(UEF9V)==xwlya8 ){
      /* Whether or not a database might need a super-journal depends upon
      ** its journal mode (among other things).  This matrix determines which
      ** journal modes use a super-journal and which do not */
      static const qHh5JW deYQbSHmLU9[] = {
        /* DELETE   */  1,
        /* PERSIST   */ 1,
        /* OFF       */ 0,
        /* TRUNCATE  */ 1,
        /* MEMORY    */ 0,
        /* WAL       */ 0
      };
      v2W4TKzHKi6_ *zwmb;   /* Pager associated with pBt */
      qOlWr = 1;
      mRYwkevtc3M8(UEF9V);
      zwmb = frhnDL(UEF9V);
      if( pLMJg2Xd->cFohRY2vCC[Pyy0l6xD].IJbhal01!=Xmdqj2RQ
       && deYQbSHmLU9[ekoWctTllr0Jg(zwmb)]
       && u40twS3bL(zwmb)==0
      ){
        f5IeCeK0e1W( Pyy0l6xD!=1 );
        aq__uFP8Lff5C++;
      }
      YPgcEHzPuCIF = wZHsGIZ3x_jDW(zwmb);
      G1gToGBXbxIv9(UEF9V);
    }
  }
  if( YPgcEHzPuCIF!=odQX7vL ){
    return YPgcEHzPuCIF;
  }

  /* If there are any write-transactions at all, invoke the commit hook */
  if( qOlWr && pLMJg2Xd->YiBnuyhivg ){
    YPgcEHzPuCIF = pLMJg2Xd->YiBnuyhivg(pLMJg2Xd->F4peU);
    if( YPgcEHzPuCIF ){
      return MBE25;
    }
  }

  /* The simple case - no more than one database file (not counting the
  ** TEMP database) has a transaction active.   There is no need for the
  ** super-journal.
  **
  ** If the return value of sqlite3BtreeGetFilename() is a zero length
  ** string, it means the main database is :memory: or a temp file.  In
  ** that case we do not support atomic multi-file commits, so use the
  ** simple case then too.
  */
  if( 0==cdWRz96EMqfU(uhhKChWcX(pLMJg2Xd->cFohRY2vCC[0].UEF9V))
   || aq__uFP8Lff5C<=1
  ){
    for(Pyy0l6xD=0; YPgcEHzPuCIF==odQX7vL && Pyy0l6xD<pLMJg2Xd->rAyJ; Pyy0l6xD++){
      UAgP *UEF9V = pLMJg2Xd->cFohRY2vCC[Pyy0l6xD].UEF9V;
      if( UEF9V ){
        YPgcEHzPuCIF = hLwW0bSByzg(UEF9V, 0);
      }
    }

    /* Do the commit only if all databases successfully complete phase 1.
    ** If one of the BtreeCommitPhaseOne() calls fails, this indicates an
    ** IO error while deleting or truncating a journal file. It is unlikely,
    ** but could happen. In this case abandon processing and return the error.
    */
    for(Pyy0l6xD=0; YPgcEHzPuCIF==odQX7vL && Pyy0l6xD<pLMJg2Xd->rAyJ; Pyy0l6xD++){
      UAgP *UEF9V = pLMJg2Xd->cFohRY2vCC[Pyy0l6xD].UEF9V;
      if( UEF9V ){
        YPgcEHzPuCIF = mC2Pd(UEF9V, 0);
      }
    }
    if( YPgcEHzPuCIF==odQX7vL ){
      izc88l(pLMJg2Xd);
    }
  }

  /* The complex case - There is a multi-file write-transaction active.
  ** This requires a super-journal file to ensure the transaction is
  ** committed atomically.
  */
#ifndef XIn_34giHqSff
  else{
    LhH2 *QOEfQvM = pLMJg2Xd->QOEfQvM;
    char *a9qG = 0;   /* File-name for the super-journal */
    char const *LDxu5GGq0b = uhhKChWcX(pLMJg2Xd->cFohRY2vCC[0].UEF9V);
    SijlCwosu3r *ygp3kCU6jUfbp = 0;
    XBJDNN3j Kca_mH5a0 = 0;
    int E6VmXbBADn7;
    int F49o = 0;
    int Eqv0bZJGCj;

    /* Select a super-journal file name */
    Eqv0bZJGCj = cdWRz96EMqfU(LDxu5GGq0b);
    a9qG = RU8v(pLMJg2Xd, "%.4c%s%.16c", 0,LDxu5GGq0b,0);
    if( a9qG==0 ) return gbOccFBhQR;
    a9qG += 4;
    do {
      JamYDTpy MBY5;
      if( F49o ){
        if( F49o>100 ){
          QTmrdsHS4WQxa(Uk_5c8mc, "MJ delete: %s", a9qG);
          YB2C(QOEfQvM, a9qG, 0);
          break;
        }else if( F49o==1 ){
          QTmrdsHS4WQxa(Uk_5c8mc, "MJ collide: %s", a9qG);
        }
      }
      F49o++;
      L1R7e2K(sizeof(MBY5), &MBY5);
      xyTnraEFT(13, &a9qG[Eqv0bZJGCj], "-mj%06X9%02X",
                               (MBY5>>8)&0xffffff, MBY5&0xff);
      /* The antipenultimate character of the super-journal name must
      ** be "9" to avoid name collisions when using 8+3 filenames. */
      f5IeCeK0e1W( a9qG[cdWRz96EMqfU(a9qG)-3]=='9' );
      NMfqFV3oq(LDxu5GGq0b, a9qG);
      YPgcEHzPuCIF = CnVypE(QOEfQvM, a9qG, qUl9Hb2n, &E6VmXbBADn7);
    }while( YPgcEHzPuCIF==odQX7vL && E6VmXbBADn7 );
    if( YPgcEHzPuCIF==odQX7vL ){
      /* Open the super-journal. */
      YPgcEHzPuCIF = Itof(QOEfQvM, a9qG, &ygp3kCU6jUfbp,
          pmiNLbl2WI8|etm4BisnVpwn|
          hkigP|KjZJHIYtN, 0
      );
    }
    if( YPgcEHzPuCIF!=odQX7vL ){
      UXHgfYQ(pLMJg2Xd, a9qG-4);
      return YPgcEHzPuCIF;
    }

    /* Write the name of each database file in the transaction into the new
    ** super-journal file. If an error occurs at this point close
    ** and delete the super-journal file. All the individual journal files
    ** still have 'null' as the super-journal pointer, so they will roll
    ** back independently if a failure occurs.
    */
    for(Pyy0l6xD=0; Pyy0l6xD<pLMJg2Xd->rAyJ; Pyy0l6xD++){
      UAgP *UEF9V = pLMJg2Xd->cFohRY2vCC[Pyy0l6xD].UEF9V;
      if( SltXbyIzCS(UEF9V)==xwlya8 ){
        char const *afK8Cpu = rwXH(UEF9V);
        if( afK8Cpu==0 ){
          continue;  /* Ignore TEMP and :memory: databases */
        }
        f5IeCeK0e1W( afK8Cpu[0]!=0 );
        YPgcEHzPuCIF = PhWOyJF00Wf(ygp3kCU6jUfbp, afK8Cpu, cdWRz96EMqfU(afK8Cpu)+1,Kca_mH5a0);
        Kca_mH5a0 += cdWRz96EMqfU(afK8Cpu)+1;
        if( YPgcEHzPuCIF!=odQX7vL ){
          XjvGzyhy4S7l(ygp3kCU6jUfbp);
          YB2C(QOEfQvM, a9qG, 0);
          UXHgfYQ(pLMJg2Xd, a9qG-4);
          return YPgcEHzPuCIF;
        }
      }
    }

    /* Sync the super-journal file. If the IOCAP_SEQUENTIAL device
    ** flag is set this is not required.
    */
    if( 0==(TbRm(ygp3kCU6jUfbp)&biNsC_)
     && odQX7vL!=(YPgcEHzPuCIF = DvMT8(ygp3kCU6jUfbp, UG8siTTKLqXVa))
    ){
      XjvGzyhy4S7l(ygp3kCU6jUfbp);
      YB2C(QOEfQvM, a9qG, 0);
      UXHgfYQ(pLMJg2Xd, a9qG-4);
      return YPgcEHzPuCIF;
    }

    /* Sync all the db files involved in the transaction. The same call
    ** sets the super-journal pointer in each individual journal. If
    ** an error occurs here, do not delete the super-journal file.
    **
    ** If the error occurs during the first call to
    ** sqlite3BtreeCommitPhaseOne(), then there is a chance that the
    ** super-journal file will be orphaned. But we cannot delete it,
    ** in case the super-journal file name was written into the journal
    ** file before the failure occurred.
    */
    for(Pyy0l6xD=0; YPgcEHzPuCIF==odQX7vL && Pyy0l6xD<pLMJg2Xd->rAyJ; Pyy0l6xD++){
      UAgP *UEF9V = pLMJg2Xd->cFohRY2vCC[Pyy0l6xD].UEF9V;
      if( UEF9V ){
        YPgcEHzPuCIF = hLwW0bSByzg(UEF9V, a9qG);
      }
    }
    XjvGzyhy4S7l(ygp3kCU6jUfbp);
    f5IeCeK0e1W( YPgcEHzPuCIF!=SDNGPshgqu );
    if( YPgcEHzPuCIF!=odQX7vL ){
      UXHgfYQ(pLMJg2Xd, a9qG-4);
      return YPgcEHzPuCIF;
    }

    /* Delete the super-journal file. This commits the transaction. After
    ** doing this the directory is synced again before any individual
    ** transaction files are deleted.
    */
    YPgcEHzPuCIF = YB2C(QOEfQvM, a9qG, 1);
    UXHgfYQ(pLMJg2Xd, a9qG-4);
    a9qG = 0;
    if( YPgcEHzPuCIF ){
      return YPgcEHzPuCIF;
    }

    /* All files and directories have already been synced, so the following
    ** calls to sqlite3BtreeCommitPhaseTwo() are only closing files and
    ** deleting or truncating journals. If something goes wrong while
    ** this is happening we don't really care. The integrity of the
    ** transaction is already guaranteed, but some stray 'cold' journals
    ** may be lying around. Returning an error code won't help matters.
    */
    RUjfRgdGuQD_c();
    O8TGutpxUeP1O();
    for(Pyy0l6xD=0; Pyy0l6xD<pLMJg2Xd->rAyJ; Pyy0l6xD++){
      UAgP *UEF9V = pLMJg2Xd->cFohRY2vCC[Pyy0l6xD].UEF9V;
      if( UEF9V ){
        mC2Pd(UEF9V, 1);
      }
    }
    iLnX71QEMOnG();
    CoyEPUcER0();

    izc88l(pLMJg2Xd);
  }
#endif

  return YPgcEHzPuCIF;
}

/*
** This routine checks that the sqlite3.nVdbeActive count variable
** matches the number of vdbe's in the list sqlite3.pVdbe that are
** currently active. An assertion fails if the two counts do not match.
** This is an internal self-check only - it is not an essential processing
** step.
**
** This is a no-op if NDEBUG is defined.
*/
#ifndef xy9M
static void du8ui2y(MEeQFpE4DzbZ *pLMJg2Xd){
  Y4zzrBxD4OXTO *RWdNEx2WUIO8x;
  int T7n1 = 0;
  int dbNLlMD9rkKX = 0;
  int VeSAy = 0;
  RWdNEx2WUIO8x = pLMJg2Xd->FDcUAbRU;
  while( RWdNEx2WUIO8x ){
    if( PwpUjqCg1CH((Rb306*)RWdNEx2WUIO8x) ){
      T7n1++;
      if( RWdNEx2WUIO8x->tdY9qH==0 ) dbNLlMD9rkKX++;
      if( RWdNEx2WUIO8x->Ha4sUMJqgGECn ) VeSAy++;
    }
    RWdNEx2WUIO8x = RWdNEx2WUIO8x->KELn;
  }
  f5IeCeK0e1W( T7n1==pLMJg2Xd->j4fkatn );
  f5IeCeK0e1W( dbNLlMD9rkKX==pLMJg2Xd->nR5IZrc55O );
  f5IeCeK0e1W( VeSAy==pLMJg2Xd->pbSLb );
}
#else
#define du8ui2y(zCVq)
#endif

/*
** If the Vdbe passed as the first argument opened a statement-transaction,
** close it now. Argument eOp must be either SAVEPOINT_ROLLBACK or
** SAVEPOINT_RELEASE. If it is SAVEPOINT_ROLLBACK, then the statement
** transaction is rolled back. If eOp is SAVEPOINT_RELEASE, then the
** statement transaction is committed.
**
** If an IO error occurs, an SQLITE_IOERR_XXX error code is returned.
** Otherwise SQLITE_OK.
*/
static XmVnyUQh int ixSo81s(Y4zzrBxD4OXTO *RWdNEx2WUIO8x, int imgBJeMf9NDc_){
  MEeQFpE4DzbZ *const pLMJg2Xd = RWdNEx2WUIO8x->pLMJg2Xd;
  int YPgcEHzPuCIF = odQX7vL;
  int Pyy0l6xD;
  const int kE9z2Hc = RWdNEx2WUIO8x->WRXmlSkV-1;

  f5IeCeK0e1W( imgBJeMf9NDc_==qBsWE || imgBJeMf9NDc_==BV1xboM9_);
  f5IeCeK0e1W( pLMJg2Xd->Cy2ov>0 );
  f5IeCeK0e1W( RWdNEx2WUIO8x->WRXmlSkV==(pLMJg2Xd->Cy2ov+pLMJg2Xd->ylTB2GaJcdSi) );

  for(Pyy0l6xD=0; Pyy0l6xD<pLMJg2Xd->rAyJ; Pyy0l6xD++){
    int u2DhPp = odQX7vL;
    UAgP *UEF9V = pLMJg2Xd->cFohRY2vCC[Pyy0l6xD].UEF9V;
    if( UEF9V ){
      if( imgBJeMf9NDc_==qBsWE ){
        u2DhPp = IscWy(UEF9V, qBsWE, kE9z2Hc);
      }
      if( u2DhPp==odQX7vL ){
        u2DhPp = IscWy(UEF9V, BV1xboM9_, kE9z2Hc);
      }
      if( YPgcEHzPuCIF==odQX7vL ){
        YPgcEHzPuCIF = u2DhPp;
      }
    }
  }
  pLMJg2Xd->Cy2ov--;
  RWdNEx2WUIO8x->WRXmlSkV = 0;

  if( YPgcEHzPuCIF==odQX7vL ){
    if( imgBJeMf9NDc_==qBsWE ){
      YPgcEHzPuCIF = BUca2WIyqC5(pLMJg2Xd, qBsWE, kE9z2Hc);
    }
    if( YPgcEHzPuCIF==odQX7vL ){
      YPgcEHzPuCIF = BUca2WIyqC5(pLMJg2Xd, BV1xboM9_, kE9z2Hc);
    }
  }

  /* If the statement transaction is being rolled back, also restore the
  ** database handles deferred constraint counter to the value it had when
  ** the statement transaction was opened.  */
  if( imgBJeMf9NDc_==qBsWE ){
    pLMJg2Xd->vb2yw41K = RWdNEx2WUIO8x->McPY8NhafzThn;
    pLMJg2Xd->MNnNeROkQZys = RWdNEx2WUIO8x->s5BhAjedD;
  }
  return YPgcEHzPuCIF;
}
int vFuwm(Y4zzrBxD4OXTO *RWdNEx2WUIO8x, int imgBJeMf9NDc_){
  if( RWdNEx2WUIO8x->pLMJg2Xd->Cy2ov && RWdNEx2WUIO8x->WRXmlSkV ){
    return ixSo81s(RWdNEx2WUIO8x, imgBJeMf9NDc_);
  }
  return odQX7vL;
}


/*
** This function is called when a transaction opened by the database
** handle associated with the VM passed as an argument is about to be
** committed. If there are outstanding deferred foreign key constraint
** violations, return SQLITE_ERROR. Otherwise, SQLITE_OK.
**
** If there are outstanding FK violations and this function returns
** SQLITE_ERROR, set the result of the VM to SQLITE_CONSTRAINT_FOREIGNKEY
** and write an error message to it. Then return SQLITE_ERROR.
*/
#ifndef XRP4IAu
int QCBjL3A(Y4zzrBxD4OXTO *RWdNEx2WUIO8x, int rLfokPd9A){
  MEeQFpE4DzbZ *pLMJg2Xd = RWdNEx2WUIO8x->pLMJg2Xd;
  if( (rLfokPd9A && (pLMJg2Xd->vb2yw41K+pLMJg2Xd->MNnNeROkQZys)>0)
   || (!rLfokPd9A && RWdNEx2WUIO8x->X98o5OdZ7Do7>0)
  ){
    RWdNEx2WUIO8x->YPgcEHzPuCIF = ToBn;
    RWdNEx2WUIO8x->nc8VDQwv = wdf01;
    haAKYIBsgAl(RWdNEx2WUIO8x, "FOREIGN KEY constraint failed");
    if( (RWdNEx2WUIO8x->AUS9xq8fh & dQky)==0 ) return Xcvmwgu;
    return ToBn;
  }
  return odQX7vL;
}
#endif

/*
** This routine is called the when a VDBE tries to halt.  If the VDBE
** has made changes and is in autocommit mode, then commit those
** changes.  If a rollback is needed, then do the rollback.
**
** This routine is the only way to move the sqlite3eOpenState of a VM from
** SQLITE_STATE_RUN to SQLITE_STATE_HALT.  It is harmless to
** call this on a VM that is in the SQLITE_STATE_HALT state.
**
** Return an error code.  If the commit could not complete because of
** lock contention, return SQLITE_BUSY.  If SQLITE_BUSY is returned, it
** means the close did not happen and needs to be repeated.
*/
int PSJUgMs(Y4zzrBxD4OXTO *RWdNEx2WUIO8x){
  int YPgcEHzPuCIF;                         /* Used to store transient return codes */
  MEeQFpE4DzbZ *pLMJg2Xd = RWdNEx2WUIO8x->pLMJg2Xd;

  /* This function contains the logic that determines if a statement or
  ** transaction will be committed or rolled back as a result of the
  ** execution of this virtual machine.
  **
  ** If any of the following errors occur:
  **
  **     SQLITE_NOMEM
  **     SQLITE_IOERR
  **     SQLITE_FULL
  **     SQLITE_INTERRUPT
  **
  ** Then the internal cache might have been left in an inconsistent
  ** state.  We need to rollback the statement transaction, if there is
  ** one, or the complete transaction if there is no statement transaction.
  */

  f5IeCeK0e1W( RWdNEx2WUIO8x->C19t==aaNsbqAVumJ );
  if( pLMJg2Xd->mi4oOCmRVN_h ){
    RWdNEx2WUIO8x->YPgcEHzPuCIF = gbOccFBhQR;
  }
  WQUk0(RWdNEx2WUIO8x);
  du8ui2y(pLMJg2Xd);

  /* No commit or rollback needed if the program never started or if the
  ** SQL statement does not read or write a database file.  */
  if( RWdNEx2WUIO8x->Ha4sUMJqgGECn ){
    int zyzSx4VjTUzrC;   /* Primary error code from p->rc */
    int OGmJUk1d067Z = 0;
    int xgJ5DPUxI;            /* Set to true if a 'special' error */

    /* Lock all btrees used by the statement */
    hhQVOl(RWdNEx2WUIO8x);

    /* Check for one of the special errors */
    if( RWdNEx2WUIO8x->YPgcEHzPuCIF ){
      zyzSx4VjTUzrC = RWdNEx2WUIO8x->YPgcEHzPuCIF & 0xff;
      xgJ5DPUxI = zyzSx4VjTUzrC==ccKsEfbei4
                    || zyzSx4VjTUzrC==vTOzAeSNHEaL
                    || zyzSx4VjTUzrC==FBHQ
                    || zyzSx4VjTUzrC==Uk_5c8mc;
    }else{
      zyzSx4VjTUzrC = xgJ5DPUxI = 0;
    }
    if( xgJ5DPUxI ){
      /* If the query was read-only and the error code is SQLITE_INTERRUPT,
      ** no rollback is necessary. Otherwise, at least a savepoint
      ** transaction must be rolled back to restore the database to a
      ** consistent state.
      **
      ** Even if the statement is read-only, it is important to perform
      ** a statement or transaction rollback operation. If the error
      ** occurred while writing to the journal, sub-journal or database
      ** file as part of an effort to free up cache space (see function
      ** pagerStress() in pager.c), the rollback is required to restore
      ** the pager to a consistent state.
      */
      if( !RWdNEx2WUIO8x->tdY9qH || zyzSx4VjTUzrC!=FBHQ ){
        if( (zyzSx4VjTUzrC==ccKsEfbei4 || zyzSx4VjTUzrC==Uk_5c8mc) && RWdNEx2WUIO8x->Sw32GUoVJzP4 ){
          OGmJUk1d067Z = qBsWE;
        }else{
          /* We are forced to roll back the active transaction. Before doing
          ** so, abort any other statements this handle currently has active.
          */
          Yrb0yuWzN(pLMJg2Xd, NhLZ);
          Kbv4n(pLMJg2Xd);
          pLMJg2Xd->wIoX1OrrDF = 1;
          RWdNEx2WUIO8x->SnFm = 0;
        }
      }
    }

    /* Check for immediate foreign key violations. */
    if( RWdNEx2WUIO8x->YPgcEHzPuCIF==odQX7vL || (RWdNEx2WUIO8x->nc8VDQwv==PZC7L && !xgJ5DPUxI) ){
      (void)QCBjL3A(RWdNEx2WUIO8x, 0);
    }

    /* If the auto-commit flag is set and this is the only active writer
    ** VM, then we do either a commit or rollback of the current transaction.
    **
    ** Note: This block also runs if one of the special errors handled
    ** above has occurred.
    */
    if( !g0_Mpk30(pLMJg2Xd)
     && pLMJg2Xd->wIoX1OrrDF
     && pLMJg2Xd->nR5IZrc55O==(RWdNEx2WUIO8x->tdY9qH==0)
    ){
      if( RWdNEx2WUIO8x->YPgcEHzPuCIF==odQX7vL || (RWdNEx2WUIO8x->nc8VDQwv==PZC7L && !xgJ5DPUxI) ){
        YPgcEHzPuCIF = QCBjL3A(RWdNEx2WUIO8x, 1);
        if( YPgcEHzPuCIF!=odQX7vL ){
          if( pxiMloLqF(RWdNEx2WUIO8x->tdY9qH) ){
            ac8keF7W(RWdNEx2WUIO8x);
            return Xcvmwgu;
          }
          YPgcEHzPuCIF = ToBn;
        }else if( pLMJg2Xd->MRNoo5HiPBk7 & o7ZGTw2 ){
          YPgcEHzPuCIF = vHwawZDAoSq;
          pLMJg2Xd->MRNoo5HiPBk7 &= ~o7ZGTw2;
        }else{
          /* The auto-commit flag is true, the vdbe program was successful
          ** or hit an 'OR FAIL' constraint and there are no deferred foreign
          ** key constraints to hold up the transaction. This means a commit
          ** is required. */
          YPgcEHzPuCIF = KyWQVHQrB(pLMJg2Xd, RWdNEx2WUIO8x);
        }
        if( YPgcEHzPuCIF==SDNGPshgqu && RWdNEx2WUIO8x->tdY9qH ){
          ac8keF7W(RWdNEx2WUIO8x);
          return SDNGPshgqu;
        }else if( YPgcEHzPuCIF!=odQX7vL ){
          BgIK8nhPnQ(pLMJg2Xd, YPgcEHzPuCIF);
          RWdNEx2WUIO8x->YPgcEHzPuCIF = YPgcEHzPuCIF;
          Yrb0yuWzN(pLMJg2Xd, odQX7vL);
          RWdNEx2WUIO8x->SnFm = 0;
        }else{
          pLMJg2Xd->vb2yw41K = 0;
          pLMJg2Xd->MNnNeROkQZys = 0;
          pLMJg2Xd->MRNoo5HiPBk7 &= ~(WuWa4iT)WrKDH;
          gb7WB8RgBcVV(pLMJg2Xd);
        }
      }else if( RWdNEx2WUIO8x->YPgcEHzPuCIF==Yheie4 && pLMJg2Xd->j4fkatn>1 ){
        RWdNEx2WUIO8x->SnFm = 0;
      }else{
        Yrb0yuWzN(pLMJg2Xd, odQX7vL);
        RWdNEx2WUIO8x->SnFm = 0;
      }
      pLMJg2Xd->Cy2ov = 0;
    }else if( OGmJUk1d067Z==0 ){
      if( RWdNEx2WUIO8x->YPgcEHzPuCIF==odQX7vL || RWdNEx2WUIO8x->nc8VDQwv==PZC7L ){
        OGmJUk1d067Z = BV1xboM9_;
      }else if( RWdNEx2WUIO8x->nc8VDQwv==wdf01 ){
        OGmJUk1d067Z = qBsWE;
      }else{
        Yrb0yuWzN(pLMJg2Xd, NhLZ);
        Kbv4n(pLMJg2Xd);
        pLMJg2Xd->wIoX1OrrDF = 1;
        RWdNEx2WUIO8x->SnFm = 0;
      }
    }
 
    /* If eStatementOp is non-zero, then a statement transaction needs to
    ** be committed or rolled back. Call sqlite3VdbeCloseStatement() to
    ** do so. If this operation returns an error, and the current statement
    ** error code is SQLITE_OK or SQLITE_CONSTRAINT, then promote the
    ** current statement error code.
    */
    if( OGmJUk1d067Z ){
      YPgcEHzPuCIF = vFuwm(RWdNEx2WUIO8x, OGmJUk1d067Z);
      if( YPgcEHzPuCIF ){
        if( RWdNEx2WUIO8x->YPgcEHzPuCIF==odQX7vL || (RWdNEx2WUIO8x->YPgcEHzPuCIF&0xff)==j04D6OSH3 ){
          RWdNEx2WUIO8x->YPgcEHzPuCIF = YPgcEHzPuCIF;
          UXHgfYQ(pLMJg2Xd, RWdNEx2WUIO8x->C9BnRQApGBXmM);
          RWdNEx2WUIO8x->C9BnRQApGBXmM = 0;
        }
        Yrb0yuWzN(pLMJg2Xd, NhLZ);
        Kbv4n(pLMJg2Xd);
        pLMJg2Xd->wIoX1OrrDF = 1;
        RWdNEx2WUIO8x->SnFm = 0;
      }
    }
 
    /* If this was an INSERT, UPDATE or DELETE and no statement transaction
    ** has been rolled back, update the database connection change-counter.
    */
    if( RWdNEx2WUIO8x->X4Sux4es2f ){
      if( OGmJUk1d067Z!=qBsWE ){
        BbHtoz(pLMJg2Xd, RWdNEx2WUIO8x->SnFm);
      }else{
        BbHtoz(pLMJg2Xd, 0);
      }
      RWdNEx2WUIO8x->SnFm = 0;
    }

    /* Release the locks */
    ac8keF7W(RWdNEx2WUIO8x);
  }

  /* We have successfully halted and closed the VM.  Record this fact. */
  pLMJg2Xd->j4fkatn--;
  if( !RWdNEx2WUIO8x->tdY9qH ) pLMJg2Xd->nR5IZrc55O--;
  if( RWdNEx2WUIO8x->Ha4sUMJqgGECn ) pLMJg2Xd->pbSLb--;
  f5IeCeK0e1W( pLMJg2Xd->j4fkatn>=pLMJg2Xd->pbSLb );
  f5IeCeK0e1W( pLMJg2Xd->pbSLb>=pLMJg2Xd->nR5IZrc55O );
  f5IeCeK0e1W( pLMJg2Xd->nR5IZrc55O>=0 );
  RWdNEx2WUIO8x->C19t = uCr0O83sgOI;
  du8ui2y(pLMJg2Xd);
  if( pLMJg2Xd->mi4oOCmRVN_h ){
    RWdNEx2WUIO8x->YPgcEHzPuCIF = gbOccFBhQR;
  }

  /* If the auto-commit flag is set to true, then any locks that were held
  ** by connection db have now been released. Call sqlite3ConnectionUnlocked()
  ** to invoke any required unlock-notify callbacks.
  */
  if( pLMJg2Xd->wIoX1OrrDF ){
    PrCHGGeEkv(pLMJg2Xd);
  }

  f5IeCeK0e1W( pLMJg2Xd->j4fkatn>0 || pLMJg2Xd->wIoX1OrrDF==0 || pLMJg2Xd->Cy2ov==0 );
  return (RWdNEx2WUIO8x->YPgcEHzPuCIF==SDNGPshgqu ? SDNGPshgqu : odQX7vL);
}


/*
** Each VDBE holds the result of the most recent sqlite3_step() call
** in p->rc.  This routine sets that result back to SQLITE_OK.
*/
void PKHgbDF8Zorn(Y4zzrBxD4OXTO *RWdNEx2WUIO8x){
  RWdNEx2WUIO8x->YPgcEHzPuCIF = odQX7vL;
}

/*
** Copy the error code and error message belonging to the VDBE passed
** as the first argument to its database handle (so that they will be
** returned by calls to sqlite3_errcode() and sqlite3_errmsg()).
**
** This function does not clear the VDBE error code or message, just
** copies them to the database handle.
*/
int SET9J(Y4zzrBxD4OXTO *RWdNEx2WUIO8x){
  MEeQFpE4DzbZ *pLMJg2Xd = RWdNEx2WUIO8x->pLMJg2Xd;
  int YPgcEHzPuCIF = RWdNEx2WUIO8x->YPgcEHzPuCIF;
  if( RWdNEx2WUIO8x->C9BnRQApGBXmM ){
    pLMJg2Xd->HiwP9++;
    O8TGutpxUeP1O();
    if( pLMJg2Xd->voaowtTVI==0 ) pLMJg2Xd->voaowtTVI = dOh1_CQF9ZJWo(pLMJg2Xd);
    H3z9JDDl7(pLMJg2Xd->voaowtTVI, -1, RWdNEx2WUIO8x->C9BnRQApGBXmM, XaWPmn7sUsHo4, JeSyy6LYlI8ul);
    iLnX71QEMOnG();
    pLMJg2Xd->HiwP9--;
  }else if( pLMJg2Xd->voaowtTVI ){
    YuGNloDC(pLMJg2Xd->voaowtTVI);
  }
  pLMJg2Xd->Zr03AqCCJT = YPgcEHzPuCIF;
  pLMJg2Xd->LPB4T3tA2LYda = -1;
  return YPgcEHzPuCIF;
}

#ifdef bolu
/*
** If an SQLITE_CONFIG_SQLLOG hook is registered and the VM has been run,
** invoke it.
*/
static void Vofw5g6HSK(Y4zzrBxD4OXTO *HB_T1jBCLdNzN){
  if( kJrDNNfol.XECJaPcq && HB_T1jBCLdNzN->YPgcEHzPuCIF==odQX7vL && HB_T1jBCLdNzN->W1REkwE && HB_T1jBCLdNzN->Ee05M7jDx_>=0 ){
    char *Org67Rs = e_SoPtZE(HB_T1jBCLdNzN, HB_T1jBCLdNzN->W1REkwE);
    f5IeCeK0e1W( HB_T1jBCLdNzN->pLMJg2Xd->EKhDxTDNgU.ANQ07iQodqX8==0 );
    if( Org67Rs ){
      kJrDNNfol.XECJaPcq(
          kJrDNNfol.LN9k2Iq3, HB_T1jBCLdNzN->pLMJg2Xd, Org67Rs, 1
      );
      UXHgfYQ(HB_T1jBCLdNzN->pLMJg2Xd, Org67Rs);
    }
  }
}
#else
# define Vofw5g6HSK(zCVq)
#endif

/*
** Clean up a VDBE after execution but do not delete the VDBE just yet.
** Write any error messages into *pzErrMsg.  Return the result code.
**
** After this routine is run, the VDBE should be ready to be executed
** again.
**
** To look at it another way, this routine resets the state of the
** virtual machine from VDBE_RUN_STATE or VDBE_HALT_STATE back to
** VDBE_READY_STATE.
*/
int QYTy_8YGuWTS(Y4zzrBxD4OXTO *RWdNEx2WUIO8x){
#if pZX7GD4OTcuV(iteB65TL5L) || pZX7GD4OTcuV(fsSLSO_wyCxfR)
  int Pyy0l6xD;
#endif

  MEeQFpE4DzbZ *pLMJg2Xd;
  pLMJg2Xd = RWdNEx2WUIO8x->pLMJg2Xd;

  /* If the VM did not run to completion or if it encountered an
  ** error, then it might not have been halted properly.  So halt
  ** it now.
  */
  if( RWdNEx2WUIO8x->C19t==aaNsbqAVumJ ) PSJUgMs(RWdNEx2WUIO8x);

  /* If the VDBE has been run even partially, then transfer the error code
  ** and error message from the VDBE into the main database structure.  But
  ** if the VDBE has just been set to run but has not actually executed any
  ** instructions yet, leave the main database error information unchanged.
  */
  if( RWdNEx2WUIO8x->Ee05M7jDx_>=0 ){
    Vofw5g6HSK(RWdNEx2WUIO8x);
    if( pLMJg2Xd->voaowtTVI || RWdNEx2WUIO8x->C9BnRQApGBXmM ){
      SET9J(RWdNEx2WUIO8x);
    }else{
      pLMJg2Xd->Zr03AqCCJT = RWdNEx2WUIO8x->YPgcEHzPuCIF;
    }
  }

  /* Reset register contents and reclaim error message memory.
  */
#ifdef iteB65TL5L
  /* Execute assert() statements to ensure that the Vdbe.apCsr[] and
  ** Vdbe.aMem[] arrays have already been cleaned up.  */
  if( RWdNEx2WUIO8x->L5eY ) for(Pyy0l6xD=0; Pyy0l6xD<RWdNEx2WUIO8x->UdjSsCqdOX; Pyy0l6xD++) f5IeCeK0e1W( RWdNEx2WUIO8x->L5eY[Pyy0l6xD]==0 );
  if( RWdNEx2WUIO8x->CSO_5 ){
    for(Pyy0l6xD=0; Pyy0l6xD<RWdNEx2WUIO8x->Om1f; Pyy0l6xD++) f5IeCeK0e1W( RWdNEx2WUIO8x->CSO_5[Pyy0l6xD].MRNoo5HiPBk7==eNZ5apG );
  }
#endif
  if( RWdNEx2WUIO8x->C9BnRQApGBXmM ){
    UXHgfYQ(pLMJg2Xd, RWdNEx2WUIO8x->C9BnRQApGBXmM);
    RWdNEx2WUIO8x->C9BnRQApGBXmM = 0;
  }
  RWdNEx2WUIO8x->iS3t7tw2Bjx = 0;
#ifdef iteB65TL5L
  RWdNEx2WUIO8x->dbNLlMD9rkKX = 0;
#endif

  /* Save profiling information from this VDBE run.
  */
#ifdef fsSLSO_wyCxfR
  {
    f3lOW1Ra0n *F3XmL1 = lMAKD("vdbe_profile.out", "a");
    if( F3XmL1 ){
      qSrTahY7cdaX(F3XmL1, "---- ");
      for(Pyy0l6xD=0; Pyy0l6xD<RWdNEx2WUIO8x->rtaUFjmY; Pyy0l6xD++){
        qSrTahY7cdaX(F3XmL1, "%02x", RWdNEx2WUIO8x->V7Y0VHDmd1Xf[Pyy0l6xD].KMcyPZbh);
      }
      qSrTahY7cdaX(F3XmL1, "\n");
      if( RWdNEx2WUIO8x->W1REkwE ){
        char Wydjdw_pm6, Ee05M7jDx_ = 0;
        qSrTahY7cdaX(F3XmL1, "-- ");
        for(Pyy0l6xD=0; (Wydjdw_pm6 = RWdNEx2WUIO8x->W1REkwE[Pyy0l6xD])!=0; Pyy0l6xD++){
          if( Ee05M7jDx_=='\n' ) qSrTahY7cdaX(F3XmL1, "-- ");
          VyCeIlqkYM(Wydjdw_pm6, F3XmL1);
          Ee05M7jDx_ = Wydjdw_pm6;
        }
        if( Ee05M7jDx_!='\n' ) qSrTahY7cdaX(F3XmL1, "\n");
      }
      for(Pyy0l6xD=0; Pyy0l6xD<RWdNEx2WUIO8x->rtaUFjmY; Pyy0l6xD++){
        char k8zkGFBGUi5[100];
        XBJDNN3j T7n1 = RWdNEx2WUIO8x->V7Y0VHDmd1Xf[Pyy0l6xD].GtnbWK;
        XBJDNN3j U7mDTtdjxm13C = RWdNEx2WUIO8x->V7Y0VHDmd1Xf[Pyy0l6xD].UKXyt_q;
        xyTnraEFT(sizeof(k8zkGFBGUi5), k8zkGFBGUi5, "%6u %12llu %8llu ",
           T7n1,
           U7mDTtdjxm13C,
           T7n1>0 ? U7mDTtdjxm13C/T7n1 : 0
        );
        qSrTahY7cdaX(F3XmL1, "%s", k8zkGFBGUi5);
        QA1Dfk_5egTE9(F3XmL1, Pyy0l6xD, &RWdNEx2WUIO8x->V7Y0VHDmd1Xf[Pyy0l6xD]);
      }
      FObjWTgkF(F3XmL1);
    }
  }
#endif
  return RWdNEx2WUIO8x->YPgcEHzPuCIF & pLMJg2Xd->eQZsvx_h6m0ld;
}

/*
** Clean up and delete a VDBE after execution.  Return an integer which is
** the result code.  Write any error message text into *pzErrMsg.
*/
int Btws(Y4zzrBxD4OXTO *RWdNEx2WUIO8x){
  int YPgcEHzPuCIF = odQX7vL;
  f5IeCeK0e1W( aaNsbqAVumJ>v1s7 );
  f5IeCeK0e1W( uCr0O83sgOI>v1s7 );
  f5IeCeK0e1W( w_rp1wwh<v1s7 );
  if( RWdNEx2WUIO8x->C19t>=v1s7 ){
    YPgcEHzPuCIF = QYTy_8YGuWTS(RWdNEx2WUIO8x);
    f5IeCeK0e1W( (YPgcEHzPuCIF & RWdNEx2WUIO8x->pLMJg2Xd->eQZsvx_h6m0ld)==YPgcEHzPuCIF );
  }
  W69h4Wi5x(RWdNEx2WUIO8x);
  return YPgcEHzPuCIF;
}

/*
** If parameter iOp is less than zero, then invoke the destructor for
** all auxiliary data pointers currently cached by the VM passed as
** the first argument.
**
** Or, if iOp is greater than or equal to zero, then the destructor is
** only invoked for those auxiliary data pointers created by the user
** function invoked by the OP_Function opcode at instruction iOp of
** VM pVdbe, and only then if:
**
**    * the associated function parameter is the 32nd or later (counting
**      from left to right), or
**
**    * the corresponding bit in argument mask is clear (where the first
**      function parameter corresponds to bit 0 etc.).
*/
void Ay89(MEeQFpE4DzbZ *pLMJg2Xd, pzqzJKyke8 **wHAzfRnrL2pNc, int Fz1Fyirahk, int Y1cyytKp){
  while( *wHAzfRnrL2pNc ){
    pzqzJKyke8 *BPNVtG = *wHAzfRnrL2pNc;
    if( (Fz1Fyirahk<0)
     || (BPNVtG->BTdhSG36r==Fz1Fyirahk
          && BPNVtG->qof1Uy9zdwM>=0
          && (BPNVtG->qof1Uy9zdwM>31 || !(Y1cyytKp & YIml(BPNVtG->qof1Uy9zdwM))))
    ){
      gwlDS2AhlE3Xe( BPNVtG->qof1Uy9zdwM==31 );
      if( BPNVtG->H3dE6Y ){
        BPNVtG->H3dE6Y(BPNVtG->BPNVtG);
      }
      *wHAzfRnrL2pNc = BPNVtG->tXHRG;
      UXHgfYQ(pLMJg2Xd, BPNVtG);
    }else{
      wHAzfRnrL2pNc= &BPNVtG->tXHRG;
    }
  }
}

/*
** Free all memory associated with the Vdbe passed as the second argument,
** except for object itself, which is preserved.
**
** The difference between this function and sqlite3VdbeDelete() is that
** VdbeDelete() also unlinks the Vdbe from the list of VMs associated with
** the database connection and frees the object itself.
*/
static void XI6dXS7VhV(MEeQFpE4DzbZ *pLMJg2Xd, Y4zzrBxD4OXTO *RWdNEx2WUIO8x){
  RnzBAc3QE *c7Jyu, *Vete4ig;
  f5IeCeK0e1W( pLMJg2Xd!=0 );
  f5IeCeK0e1W( RWdNEx2WUIO8x->pLMJg2Xd==0 || RWdNEx2WUIO8x->pLMJg2Xd==pLMJg2Xd );
  if( RWdNEx2WUIO8x->XCYp ){
    C4w0fxT16GXQr(RWdNEx2WUIO8x->XCYp, RWdNEx2WUIO8x->waWG*IlYFtUVZ);
    CTQ2V30yU(pLMJg2Xd, RWdNEx2WUIO8x->XCYp);
  }
  for(c7Jyu=RWdNEx2WUIO8x->IbbDoqgyL; c7Jyu; c7Jyu=Vete4ig){
    Vete4ig = c7Jyu->Vete4ig;
    hOukOg4s95gVn(pLMJg2Xd, c7Jyu->V7Y0VHDmd1Xf, c7Jyu->rtaUFjmY);
    UXHgfYQ(pLMJg2Xd, c7Jyu);
  }
  if( RWdNEx2WUIO8x->C19t!=w_rp1wwh ){
    C4w0fxT16GXQr(RWdNEx2WUIO8x->dHLFi0U0rI5oH, RWdNEx2WUIO8x->u5EP6Pex2vAp);
    if( RWdNEx2WUIO8x->E2ONFI4w8YJV ) CTQ2V30yU(pLMJg2Xd, RWdNEx2WUIO8x->E2ONFI4w8YJV);
    if( RWdNEx2WUIO8x->YJxTyv ) CTQ2V30yU(pLMJg2Xd, RWdNEx2WUIO8x->YJxTyv);
  }
  hOukOg4s95gVn(pLMJg2Xd, RWdNEx2WUIO8x->V7Y0VHDmd1Xf, RWdNEx2WUIO8x->rtaUFjmY);
  if( RWdNEx2WUIO8x->W1REkwE ) CTQ2V30yU(pLMJg2Xd, RWdNEx2WUIO8x->W1REkwE);
#ifdef f2AUQe1
  UXHgfYQ(pLMJg2Xd, RWdNEx2WUIO8x->aC5kY);
  {
    maKTiN *qzomzhmcNYkl, *ULzanMWFX;
    for(qzomzhmcNYkl=RWdNEx2WUIO8x->NNZletnEKt; qzomzhmcNYkl; qzomzhmcNYkl=ULzanMWFX){
      ULzanMWFX = qzomzhmcNYkl->Ir2qFTMJvd;
      UXHgfYQ(pLMJg2Xd, qzomzhmcNYkl);
    }
  }
#endif
#ifdef ghoW
  {
    int Pyy0l6xD;
    for(Pyy0l6xD=0; Pyy0l6xD<RWdNEx2WUIO8x->UWhyJpoUVsV; Pyy0l6xD++){
      UXHgfYQ(pLMJg2Xd, RWdNEx2WUIO8x->DGFG4az[Pyy0l6xD].wxojaeqHwik);
    }
    UXHgfYQ(pLMJg2Xd, RWdNEx2WUIO8x->DGFG4az);
  }
#endif
}

/*
** Delete an entire VDBE.
*/
void W69h4Wi5x(Y4zzrBxD4OXTO *RWdNEx2WUIO8x){
  MEeQFpE4DzbZ *pLMJg2Xd;

  f5IeCeK0e1W( RWdNEx2WUIO8x!=0 );
  pLMJg2Xd = RWdNEx2WUIO8x->pLMJg2Xd;
  f5IeCeK0e1W( pLMJg2Xd!=0 );
  f5IeCeK0e1W( FmX9So3cuLy(pLMJg2Xd->XXRvk3u4f6u) );
  XI6dXS7VhV(pLMJg2Xd, RWdNEx2WUIO8x);
  if( pLMJg2Xd->mMBxdHckzgHIl==0 ){
    f5IeCeK0e1W( RWdNEx2WUIO8x->qanFC!=0 );
    *RWdNEx2WUIO8x->qanFC = RWdNEx2WUIO8x->KELn;
    if( RWdNEx2WUIO8x->KELn ){
      RWdNEx2WUIO8x->KELn->qanFC = RWdNEx2WUIO8x->qanFC;
    }
  }
  CTQ2V30yU(pLMJg2Xd, RWdNEx2WUIO8x);
}

/*
** The cursor "p" has a pending seek operation that has not yet been
** carried out.  Seek the cursor now.  If an error occurs, return
** the appropriate error code.
*/
int XmVnyUQh AYZXYq7Q5quqZ(Jmdb *RWdNEx2WUIO8x){
  int E6VmXbBADn7, YPgcEHzPuCIF;
#ifdef GMdQZFH_V4yU8
  extern int RKbjTgRrM2hI;
#endif
  f5IeCeK0e1W( RWdNEx2WUIO8x->yEnQz );
  f5IeCeK0e1W( RWdNEx2WUIO8x->KcmFbYP6Gu8N );
  f5IeCeK0e1W( RWdNEx2WUIO8x->lhtEl9aC9MU==lqUt );
  YPgcEHzPuCIF = ZSVCI6T01Jc(RWdNEx2WUIO8x->b75S0uIj_5z.qtSltNrcEx, RWdNEx2WUIO8x->rxTm, 0, &E6VmXbBADn7);
  if( YPgcEHzPuCIF ) return YPgcEHzPuCIF;
  if( E6VmXbBADn7!=0 ) return mVXrATk9;
#ifdef GMdQZFH_V4yU8
  RKbjTgRrM2hI++;
#endif
  RWdNEx2WUIO8x->yEnQz = 0;
  RWdNEx2WUIO8x->TRYts = BxOEhw;
  return odQX7vL;
}

/*
** Something has moved cursor "p" out of place.  Maybe the row it was
** pointed to was deleted out from under it.  Or maybe the btree was
** rebalanced.  Whatever the cause, try to restore "p" to the place it
** is supposed to be pointing.  If the row was deleted out from under the
** cursor, set the cursor to point to a NULL row.
*/
int XmVnyUQh JQMyACoF(Jmdb *RWdNEx2WUIO8x){
  int xQ7JhrK3TeqO8, YPgcEHzPuCIF;
  f5IeCeK0e1W( RWdNEx2WUIO8x->lhtEl9aC9MU==lqUt );
  f5IeCeK0e1W( RWdNEx2WUIO8x->b75S0uIj_5z.qtSltNrcEx!=0 );
  f5IeCeK0e1W( ezbB(RWdNEx2WUIO8x->b75S0uIj_5z.qtSltNrcEx) );
  YPgcEHzPuCIF = KqqkOxLqt(RWdNEx2WUIO8x->b75S0uIj_5z.qtSltNrcEx, &xQ7JhrK3TeqO8);
  RWdNEx2WUIO8x->TRYts = BxOEhw;
  if( xQ7JhrK3TeqO8 ) RWdNEx2WUIO8x->Az59nrK = 1;
  return YPgcEHzPuCIF;
}

/*
** Check to ensure that the cursor is valid.  Restore the cursor
** if need be.  Return any I/O error from the restore operation.
*/
int DiTIilu8m(Jmdb *RWdNEx2WUIO8x){
  f5IeCeK0e1W( RWdNEx2WUIO8x->lhtEl9aC9MU==lqUt || uQL6(RWdNEx2WUIO8x) );
  if( ezbB(RWdNEx2WUIO8x->b75S0uIj_5z.qtSltNrcEx) ){
    return JQMyACoF(RWdNEx2WUIO8x);
  }
  return odQX7vL;
}

/*
** The following functions:
**
** sqlite3VdbeSerialType()
** sqlite3VdbeSerialTypeLen()
** sqlite3VdbeSerialLen()
** sqlite3VdbeSerialPut()  <--- in-lined into OP_MakeRecord as of 2022-04-02
** sqlite3VdbeSerialGet()
**
** encapsulate the code that serializes values for storage in SQLite
** data and index records. Each serialized value consists of a
** 'serial-type' and a blob of data. The serial type is an 8-byte unsigned
** integer, stored as a varint.
**
** In an SQLite index record, the serial type is stored directly before
** the blob of data that it corresponds to. In a table record, all serial
** types are stored at the start of the record, and the blobs of data at
** the end. Hence these functions allow the caller to handle the
** serial-type and data blob separately.
**
** The following table describes the various storage classes for data:
**
**   serial type        bytes of data      type
**   --------------     ---------------    ---------------
**      0                     0            NULL
**      1                     1            signed integer
**      2                     2            signed integer
**      3                     3            signed integer
**      4                     4            signed integer
**      5                     6            signed integer
**      6                     8            signed integer
**      7                     8            IEEE float
**      8                     0            Integer constant 0
**      9                     0            Integer constant 1
**     10,11                               reserved for expansion
**    N>=12 and even       (N-12)/2        BLOB
**    N>=13 and odd        (N-13)/2        text
**
** The 8 and 9 types were added in 3.3.0, file format 4.  Prior versions
** of SQLite will not understand those serial types.
*/

#if 0 /* Inlined into the OP_MakeRecord opcode */
/*
** Return the serial-type for the value stored in pMem.
**
** This routine might convert a large MEM_IntReal value into MEM_Real.
**
** 2019-07-11:  The primary user of this subroutine was the OP_MakeRecord
** opcode in the byte-code engine.  But by moving this routine in-line, we
** can omit some redundant tests and make that opcode a lot faster.  So
** this routine is now only used by the STAT3 logic and STAT3 support has
** ended.  The code is kept here for historical reference only.
*/
JamYDTpy eteReglg6lL(oi4q2s5KcMX9Y *ZAHT, int ImtyP, JamYDTpy *hdV2nsYQc5fq){
  int MRNoo5HiPBk7 = ZAHT->MRNoo5HiPBk7;
  JamYDTpy AS0ycVs;

  f5IeCeK0e1W( hdV2nsYQc5fq!=0 );
  if( MRNoo5HiPBk7&NIJTPrY3UI ){
    *hdV2nsYQc5fq = 0;
    return 0;
  }
  if( MRNoo5HiPBk7&(qN6FC41ULkGDO|tbmTzwycmDB) ){
    /* Figure out whether to use 1, 2, 4, 6 or 8 bytes. */
#   define lasAPyL2SwTq8 ((((XBJDNN3j)0x00008000)<<32)-1)
    XBJDNN3j Pyy0l6xD = ZAHT->r43Pj.Pyy0l6xD;
    WuWa4iT r43Pj;
    gwlDS2AhlE3Xe( MRNoo5HiPBk7 & qN6FC41ULkGDO );
    gwlDS2AhlE3Xe( MRNoo5HiPBk7 & tbmTzwycmDB );
    if( Pyy0l6xD<0 ){
      r43Pj = ~Pyy0l6xD;
    }else{
      r43Pj = Pyy0l6xD;
    }
    if( r43Pj<=127 ){
      if( (Pyy0l6xD&1)==Pyy0l6xD && ImtyP>=4 ){
        *hdV2nsYQc5fq = 0;
        return 8+(JamYDTpy)r43Pj;
      }else{
        *hdV2nsYQc5fq = 1;
        return 1;
      }
    }
    if( r43Pj<=32767 ){ *hdV2nsYQc5fq = 2; return 2; }
    if( r43Pj<=8388607 ){ *hdV2nsYQc5fq = 3; return 3; }
    if( r43Pj<=2147483647 ){ *hdV2nsYQc5fq = 4; return 4; }
    if( r43Pj<=lasAPyL2SwTq8 ){ *hdV2nsYQc5fq = 6; return 5; }
    *hdV2nsYQc5fq = 8;
    if( MRNoo5HiPBk7&tbmTzwycmDB ){
      /* If the value is IntReal and is going to take up 8 bytes to store
      ** as an integer, then we might as well make it an 8-byte floating
      ** point value */
      ZAHT->r43Pj.uNdS8p26k = (double)ZAHT->r43Pj.Pyy0l6xD;
      ZAHT->MRNoo5HiPBk7 &= ~tbmTzwycmDB;
      ZAHT->MRNoo5HiPBk7 |= ITDPS;
      return 7;
    }
    return 6;
  }
  if( MRNoo5HiPBk7&ITDPS ){
    *hdV2nsYQc5fq = 8;
    return 7;
  }
  f5IeCeK0e1W( ZAHT->pLMJg2Xd->mi4oOCmRVN_h || MRNoo5HiPBk7&(caIIAbkg|GrDQtTd) );
  f5IeCeK0e1W( ZAHT->AS0ycVs>=0 );
  AS0ycVs = (JamYDTpy)ZAHT->AS0ycVs;
  if( MRNoo5HiPBk7 & LYov5I ){
    AS0ycVs += ZAHT->r43Pj.oSkdrwZWp;
  }
  *hdV2nsYQc5fq = AS0ycVs;
  return ((AS0ycVs*2) + 12 + ((MRNoo5HiPBk7&caIIAbkg)!=0));
}
#endif /* inlined into OP_MakeRecord */

/*
** The sizes for serial types less than 128
*/
const qHh5JW OQD9[128] = {
        /*  0   1   2   3   4   5   6   7   8   9 */  
/*   0 */   0,  1,  2,  3,  4,  6,  8,  8,  0,  0,
/*  10 */   0,  0,  0,  0,  1,  1,  2,  2,  3,  3,
/*  20 */   4,  4,  5,  5,  6,  6,  7,  7,  8,  8,
/*  30 */   9,  9, 10, 10, 11, 11, 12, 12, 13, 13,
/*  40 */  14, 14, 15, 15, 16, 16, 17, 17, 18, 18,
/*  50 */  19, 19, 20, 20, 21, 21, 22, 22, 23, 23,
/*  60 */  24, 24, 25, 25, 26, 26, 27, 27, 28, 28,
/*  70 */  29, 29, 30, 30, 31, 31, 32, 32, 33, 33,
/*  80 */  34, 34, 35, 35, 36, 36, 37, 37, 38, 38,
/*  90 */  39, 39, 40, 40, 41, 41, 42, 42, 43, 43,
/* 100 */  44, 44, 45, 45, 46, 46, 47, 47, 48, 48,
/* 110 */  49, 49, 50, 50, 51, 51, 52, 52, 53, 53,
/* 120 */  54, 54, 55, 55, 56, 56, 57, 57
};

/*
** Return the length of the data corresponding to the supplied serial-type.
*/
JamYDTpy NI158jGWh(JamYDTpy nvQLph){
  if( nvQLph>=128 ){
    return (nvQLph-12)/2;
  }else{
    f5IeCeK0e1W( nvQLph<12
            || OQD9[nvQLph]==(nvQLph - 12)/2 );
    return OQD9[nvQLph];
  }
}
qHh5JW da_fli(qHh5JW nvQLph){
  f5IeCeK0e1W( nvQLph<128 );
  return OQD9[nvQLph]; 
}

/*
** If we are on an architecture with mixed-endian floating
** points (ex: ARM7) then swap the lower 4 bytes with the
** upper 4 bytes.  Return the result.
**
** For most architectures, this is a no-op.
**
** (later):  It is reported to me that the mixed-endian problem
** on ARM7 is an issue with GCC, not with the ARM7 chip.  It seems
** that early versions of GCC stored the two words of a 64-bit
** float in the wrong order.  And that error has been propagated
** ever since.  The blame is not necessarily with GCC, though.
** GCC might have just copying the problem from a prior compiler.
** I am also told that newer versions of GCC that follow a different
** ABI get the byte order right.
**
** Developers using SQLite on an ARM7 should compile and run their
** application using -DSQLITE_DEBUG=1 at least once.  With DEBUG
** enabled, some asserts below will ensure that the byte order of
** floating point values is correct.
**
** (2007-08-30)  Frank van Vugt has studied this problem closely
** and has send his findings to the SQLite developers.  Frank
** writes that some Linux kernels offer floating point hardware
** emulation that uses only 32-bit mantissas instead of a full
** 48-bits as required by the IEEE standard.  (This is the
** CONFIG_FPE_FASTFPE option.)  On such systems, floating point
** byte swapping becomes very complicated.  To avoid problems,
** the necessary byte swapping is carried out using a 64-bit integer
** rather than a 64-bit float.  Frank assures us that the code here
** works for him.  We, the developers, have no way to independently
** verify this, but Frank seems to know what he is talking about
** so we trust him.
*/
#ifdef MIP7OH2sN
WuWa4iT kz7UxOGBhtY(WuWa4iT idID9QzA){
  union {
    WuWa4iT uNdS8p26k;
    JamYDTpy Pyy0l6xD[2];
  } r43Pj;
  JamYDTpy OdFaNyxUnD;

  r43Pj.uNdS8p26k = idID9QzA;
  OdFaNyxUnD = r43Pj.Pyy0l6xD[0];
  r43Pj.Pyy0l6xD[0] = r43Pj.Pyy0l6xD[1];
  r43Pj.Pyy0l6xD[1] = OdFaNyxUnD;
  return r43Pj.uNdS8p26k;
}
#endif /* SQLITE_MIXED_ENDIAN_64BIT_FLOAT */


/* Input "x" is a sequence of unsigned characters that represent a
** big-endian integer.  Return the equivalent native integer
*/
#define ys0BGI(zCVq)    ((ekF1)(zCVq)[0])
#define fIlGE(zCVq)    (256*(ekF1)((zCVq)[0])|(zCVq)[1])
#define RPMiG9zcPWTS(zCVq)  (65536*(ekF1)((zCVq)[0])|((zCVq)[1]<<8)|(zCVq)[2])
#define lNwn(zCVq)  (((JamYDTpy)(zCVq)[0]<<24)|((zCVq)[1]<<16)|((zCVq)[2]<<8)|(zCVq)[3])
#define GoOl(zCVq) (16777216*(ekF1)((zCVq)[0])|((zCVq)[1]<<16)|((zCVq)[2]<<8)|(zCVq)[3])

/*
** Deserialize the data blob pointed to by buf as serial type serial_type
** and store the result in pMem.
**
** This function is implemented as two separate routines for performance.
** The few cases that require local variables are broken out into a separate
** routine so that in most cases the overhead of moving the stack pointer
** is avoided.
*/
static void LSqNYiJWr(
  const unsigned char *UhnoLDBCF,     /* Buffer to deserialize from */
  JamYDTpy nvQLph,              /* Serial type to deserialize */
  oi4q2s5KcMX9Y *ZAHT                     /* Memory cell to write value into */
){
  WuWa4iT zCVq = lNwn(UhnoLDBCF);
  JamYDTpy V2NN0qsOZKw = lNwn(UhnoLDBCF+4);
  zCVq = (zCVq<<32) + V2NN0qsOZKw;
  if( nvQLph==6 ){
    /* EVIDENCE-OF: R-29851-52272 Value is a big-endian 64-bit
    ** twos-complement integer. */
    ZAHT->r43Pj.Pyy0l6xD = *(XBJDNN3j*)&zCVq;
    ZAHT->MRNoo5HiPBk7 = qN6FC41ULkGDO;
    gwlDS2AhlE3Xe( ZAHT->r43Pj.Pyy0l6xD<0 );
  }else{
    /* EVIDENCE-OF: R-57343-49114 Value is a big-endian IEEE 754-2008 64-bit
    ** floating point number. */
#if !pZX7GD4OTcuV(xy9M) && !pZX7GD4OTcuV(g6YcJJNxvUx)
    /* Verify that integers and floating point values use the same
    ** byte order.  Or, that if SQLITE_MIXED_ENDIAN_64BIT_FLOAT is
    ** defined that 64-bit floating point values really are mixed
    ** endian.
    */
    static const WuWa4iT jZiGYMAaOw9W = ((WuWa4iT)0x3ff00000)<<32;
    static const double rDYc = 1.0;
    WuWa4iT Lbw_D8WFb = jZiGYMAaOw9W;
    hfV12pmpfDnXg(Lbw_D8WFb);
    f5IeCeK0e1W( sizeof(rDYc)==sizeof(Lbw_D8WFb) && zUuN(&rDYc, &Lbw_D8WFb, sizeof(rDYc))==0 );
#endif
    f5IeCeK0e1W( sizeof(zCVq)==8 && sizeof(ZAHT->r43Pj.uNdS8p26k)==8 );
    hfV12pmpfDnXg(zCVq);
    u1hm9A(&ZAHT->r43Pj.uNdS8p26k, &zCVq, sizeof(zCVq));
    ZAHT->MRNoo5HiPBk7 = hgBfocEM2(zCVq) ? NIJTPrY3UI : ITDPS;
  }
}
static int MjkcH33(
  const unsigned char *UhnoLDBCF,     /* Buffer to deserialize from */
  oi4q2s5KcMX9Y *ZAHT                     /* Memory cell to write value into */
){
  WuWa4iT zCVq = lNwn(UhnoLDBCF);
  JamYDTpy V2NN0qsOZKw = lNwn(UhnoLDBCF+4);
  zCVq = (zCVq<<32) + V2NN0qsOZKw;
  f5IeCeK0e1W( sizeof(zCVq)==8 && sizeof(ZAHT->r43Pj.uNdS8p26k)==8 );
  hfV12pmpfDnXg(zCVq);
  u1hm9A(&ZAHT->r43Pj.uNdS8p26k, &zCVq, sizeof(zCVq));
  if( hgBfocEM2(zCVq) ){
    ZAHT->MRNoo5HiPBk7 = NIJTPrY3UI;
    return 1;
  }
  ZAHT->MRNoo5HiPBk7 = ITDPS;
  return 0;
}
void WKkx9Vx9(
  const unsigned char *UhnoLDBCF,     /* Buffer to deserialize from */
  JamYDTpy nvQLph,              /* Serial type to deserialize */
  oi4q2s5KcMX9Y *ZAHT                     /* Memory cell to write value into */
){
  switch( nvQLph ){
    case 10: { /* Internal use only: NULL with virtual table
               ** UPDATE no-change flag set */
      ZAHT->MRNoo5HiPBk7 = NIJTPrY3UI|LYov5I;
      ZAHT->AS0ycVs = 0;
      ZAHT->r43Pj.oSkdrwZWp = 0;
      return;
    }
    case 11:   /* Reserved for future use */
    case 0: {  /* Null */
      /* EVIDENCE-OF: R-24078-09375 Value is a NULL. */
      ZAHT->MRNoo5HiPBk7 = NIJTPrY3UI;
      return;
    }
    case 1: {
      /* EVIDENCE-OF: R-44885-25196 Value is an 8-bit twos-complement
      ** integer. */
      ZAHT->r43Pj.Pyy0l6xD = ys0BGI(UhnoLDBCF);
      ZAHT->MRNoo5HiPBk7 = qN6FC41ULkGDO;
      gwlDS2AhlE3Xe( ZAHT->r43Pj.Pyy0l6xD<0 );
      return;
    }
    case 2: { /* 2-byte signed integer */
      /* EVIDENCE-OF: R-49794-35026 Value is a big-endian 16-bit
      ** twos-complement integer. */
      ZAHT->r43Pj.Pyy0l6xD = fIlGE(UhnoLDBCF);
      ZAHT->MRNoo5HiPBk7 = qN6FC41ULkGDO;
      gwlDS2AhlE3Xe( ZAHT->r43Pj.Pyy0l6xD<0 );
      return;
    }
    case 3: { /* 3-byte signed integer */
      /* EVIDENCE-OF: R-37839-54301 Value is a big-endian 24-bit
      ** twos-complement integer. */
      ZAHT->r43Pj.Pyy0l6xD = RPMiG9zcPWTS(UhnoLDBCF);
      ZAHT->MRNoo5HiPBk7 = qN6FC41ULkGDO;
      gwlDS2AhlE3Xe( ZAHT->r43Pj.Pyy0l6xD<0 );
      return;
    }
    case 4: { /* 4-byte signed integer */
      /* EVIDENCE-OF: R-01849-26079 Value is a big-endian 32-bit
      ** twos-complement integer. */
      ZAHT->r43Pj.Pyy0l6xD = GoOl(UhnoLDBCF);
#ifdef AXR6eX
      /* Work around a sign-extension bug in the HP compiler for HP/UX */
      if( UhnoLDBCF[0]&0x80 ) ZAHT->r43Pj.Pyy0l6xD |= 0xffffffff80000000LL;
#endif
      ZAHT->MRNoo5HiPBk7 = qN6FC41ULkGDO;
      gwlDS2AhlE3Xe( ZAHT->r43Pj.Pyy0l6xD<0 );
      return;
    }
    case 5: { /* 6-byte signed integer */
      /* EVIDENCE-OF: R-50385-09674 Value is a big-endian 48-bit
      ** twos-complement integer. */
      ZAHT->r43Pj.Pyy0l6xD = lNwn(UhnoLDBCF+2) + (((XBJDNN3j)1)<<32)*fIlGE(UhnoLDBCF);
      ZAHT->MRNoo5HiPBk7 = qN6FC41ULkGDO;
      gwlDS2AhlE3Xe( ZAHT->r43Pj.Pyy0l6xD<0 );
      return;
    }
    case 6:   /* 8-byte signed integer */
    case 7: { /* IEEE floating point */
      /* These use local variables, so do them in a separate routine
      ** to avoid having to move the frame pointer in the common case */
      LSqNYiJWr(UhnoLDBCF,nvQLph,ZAHT);
      return;
    }
    case 8:    /* Integer 0 */
    case 9: {  /* Integer 1 */
      /* EVIDENCE-OF: R-12976-22893 Value is the integer 0. */
      /* EVIDENCE-OF: R-18143-12121 Value is the integer 1. */
      ZAHT->r43Pj.Pyy0l6xD = nvQLph-8;
      ZAHT->MRNoo5HiPBk7 = qN6FC41ULkGDO;
      return;
    }
    default: {
      /* EVIDENCE-OF: R-14606-31564 Value is a BLOB that is (N-12)/2 bytes in
      ** length.
      ** EVIDENCE-OF: R-28401-00140 Value is a string in the text encoding and
      ** (N-13)/2 bytes in length. */
      static const k1VeKpK WFk4EGvAv8[] = { GrDQtTd|hu94vgEoB, caIIAbkg|hu94vgEoB };
      ZAHT->mrgekw0xj = (char *)UhnoLDBCF;
      ZAHT->AS0ycVs = (nvQLph-12)/2;
      ZAHT->MRNoo5HiPBk7 = WFk4EGvAv8[nvQLph&1];
      return;
    }
  }
  return;
}
/*
** This routine is used to allocate sufficient space for an UnpackedRecord
** structure large enough to be used with sqlite3VdbeRecordUnpack() if
** the first argument is a pointer to KeyInfo structure pKeyInfo.
**
** The space is either allocated using sqlite3DbMallocRaw() or from within
** the unaligned buffer passed via the second and third arguments (presumably
** stack space). If the former, then *ppFree is set to a pointer that should
** be eventually freed by the caller using sqlite3DbFree(). Or, if the
** allocation comes from the pSpace/szSpace buffer, *ppFree is set to NULL
** before returning.
**
** If an OOM error occurs, NULL is returned.
*/
Byn9mdCAjUkY9 *DYdSw3ShX7(
  Yen3v7sHJ_Gb *N0B0w0pr1Cz               /* Description of the record */
){
  Byn9mdCAjUkY9 *RWdNEx2WUIO8x;              /* Unpacked record to return */
  int jCneFxRQnw;                      /* Number of bytes required for *p */
  jCneFxRQnw = c7n37T(sizeof(Byn9mdCAjUkY9)) + sizeof(oi4q2s5KcMX9Y)*(N0B0w0pr1Cz->tr0jn+1);
  RWdNEx2WUIO8x = (Byn9mdCAjUkY9 *)F0BPC(N0B0w0pr1Cz->pLMJg2Xd, jCneFxRQnw);
  if( !RWdNEx2WUIO8x ) return 0;
  RWdNEx2WUIO8x->CSO_5 = (oi4q2s5KcMX9Y*)&((char*)RWdNEx2WUIO8x)[c7n37T(sizeof(Byn9mdCAjUkY9))];
  f5IeCeK0e1W( N0B0w0pr1Cz->iIxU!=0 );
  RWdNEx2WUIO8x->N0B0w0pr1Cz = N0B0w0pr1Cz;
  RWdNEx2WUIO8x->FRi83T = N0B0w0pr1Cz->tr0jn + 1;
  return RWdNEx2WUIO8x;
}

/*
** Given the nKey-byte encoding of a record in pKey[], populate the
** UnpackedRecord structure indicated by the fourth argument with the
** contents of the decoded record.
*/
void y5nwbEKAW0y(
  Yen3v7sHJ_Gb *N0B0w0pr1Cz,     /* Information about the record format */
  int v4U6UE,              /* Size of the binary record */
  const void *iSrbtrwTQI,      /* The binary record */
  Byn9mdCAjUkY9 *RWdNEx2WUIO8x      /* Populate this structure before returning. */
){
  const unsigned char *sR9oM7XAZ = (const unsigned char *)iSrbtrwTQI;
  JamYDTpy OT2QNFt;
  JamYDTpy wrlhjKL_;                        /* Offset in aKey[] to read from */
  k1VeKpK r43Pj;                          /* Unsigned loop counter */
  JamYDTpy dVY8BONXMY;
  oi4q2s5KcMX9Y *ZAHT = RWdNEx2WUIO8x->CSO_5;

  RWdNEx2WUIO8x->MhFnYCyMziO = 0;
  f5IeCeK0e1W( UbnT4(ZAHT) );
  wrlhjKL_ = S2kGTVNXuvs(sR9oM7XAZ, dVY8BONXMY);
  OT2QNFt = dVY8BONXMY;
  r43Pj = 0;
  while( wrlhjKL_<dVY8BONXMY && OT2QNFt<=(JamYDTpy)v4U6UE ){
    JamYDTpy nvQLph;

    wrlhjKL_ += S2kGTVNXuvs(&sR9oM7XAZ[wrlhjKL_], nvQLph);
    ZAHT->Tc4R1 = N0B0w0pr1Cz->Tc4R1;
    ZAHT->pLMJg2Xd = N0B0w0pr1Cz->pLMJg2Xd;
    /* pMem->flags = 0; // sqlite3VdbeSerialGet() will set this for us */
    ZAHT->N3A21Ra4MY24m = 0;
    ZAHT->mrgekw0xj = 0;
    WKkx9Vx9(&sR9oM7XAZ[OT2QNFt], nvQLph, ZAHT);
    OT2QNFt += NI158jGWh(nvQLph);
    ZAHT++;
    if( (++r43Pj)>=RWdNEx2WUIO8x->FRi83T ) break;
  }
  if( OT2QNFt>(JamYDTpy)v4U6UE && r43Pj ){
    f5IeCeK0e1W( ih1YL );
    /* In a corrupt record entry, the last pMem might have been set up using
    ** uninitialized memory. Overwrite its value with NULL, to prevent
    ** warnings from MSAN. */
    mPpWxtg4C(ZAHT-1);
  }
  f5IeCeK0e1W( r43Pj<=N0B0w0pr1Cz->tr0jn + 1 );
  RWdNEx2WUIO8x->FRi83T = r43Pj;
}

#ifdef iteB65TL5L
/*
** This function compares two index or table record keys in the same way
** as the sqlite3VdbeRecordCompare() routine. Unlike VdbeRecordCompare(),
** this function deserializes and compares values using the
** sqlite3VdbeSerialGet() and sqlite3MemCompare() functions. It is used
** in assert() statements to ensure that the optimized code in
** sqlite3VdbeRecordCompare() returns results with these two primitives.
**
** Return true if the result of comparison is equivalent to desiredResult.
** Return false if there is a disagreement.
*/
static int kiq86cF2b(
  int GwAxac_NG, const void *HFeOU, /* Left key */
  const Byn9mdCAjUkY9 *t8EU, /* Right key */
  int rpmFh_dSyrSSl             /* Correct answer */
){
  JamYDTpy WuLRESmsSj;            /* Offset into aKey[] of next data element */
  JamYDTpy gMsz;          /* Offset into aKey[] of next header element */
  JamYDTpy zI_N5t27;        /* Number of bytes in header */
  int Pyy0l6xD = 0;
  int YPgcEHzPuCIF = 0;
  const unsigned char *Yn2R5CEn = (const unsigned char *)HFeOU;
  Yen3v7sHJ_Gb *N0B0w0pr1Cz;
  oi4q2s5KcMX9Y bBByAg;

  N0B0w0pr1Cz = t8EU->N0B0w0pr1Cz;
  if( N0B0w0pr1Cz->pLMJg2Xd==0 ) return 1;
  bBByAg.Tc4R1 = N0B0w0pr1Cz->Tc4R1;
  bBByAg.pLMJg2Xd = N0B0w0pr1Cz->pLMJg2Xd;
  /* mem1.flags = 0;  // Will be initialized by sqlite3VdbeSerialGet() */
  GHCxb3ljLpK( bBByAg.N3A21Ra4MY24m = 0; ) /* Only needed by assert() statements */

  /* Compilers may complain that mem1.u.i is potentially uninitialized.
  ** We could initialize it, as shown here, to silence those complaints.
  ** But in fact, mem1.u.i will never actually be used uninitialized, and doing
  ** the unnecessary initialization has a measurable negative performance
  ** impact, since this routine is a very high runner.  And so, we choose
  ** to ignore the compiler warnings and leave this variable uninitialized.
  */
  /*  mem1.u.i = 0;  // not needed, here to silence compiler warning */
 
  gMsz = S2kGTVNXuvs(Yn2R5CEn, zI_N5t27);
  if( zI_N5t27>98307 ) return vHwawZDAoSq;
  WuLRESmsSj = zI_N5t27;
  f5IeCeK0e1W( N0B0w0pr1Cz->Xn4s88sqBM>=t8EU->FRi83T || ih1YL );
  f5IeCeK0e1W( N0B0w0pr1Cz->iIxU!=0 );
  f5IeCeK0e1W( N0B0w0pr1Cz->tr0jn>0 );
  f5IeCeK0e1W( gMsz<=zI_N5t27 || ih1YL );
  do{
    JamYDTpy EmGANaJcaAhd;

    /* Read the serial types for the next element in each key. */
    gMsz += S2kGTVNXuvs( Yn2R5CEn+gMsz, EmGANaJcaAhd );

    /* Verify that there is enough key space remaining to avoid
    ** a buffer overread.  The "d1+serial_type1+2" subexpression will
    ** always be greater than or equal to the amount of required key space.
    ** Use that approximation to avoid the more expensive call to
    ** sqlite3VdbeSerialTypeLen() in the common case.
    */
    if( WuLRESmsSj+(WuWa4iT)EmGANaJcaAhd+2>(WuWa4iT)GwAxac_NG
     && WuLRESmsSj+(WuWa4iT)NI158jGWh(EmGANaJcaAhd)>(WuWa4iT)GwAxac_NG
    ){
      if( EmGANaJcaAhd>=1
       && EmGANaJcaAhd<=7
       && WuLRESmsSj+(WuWa4iT)NI158jGWh(EmGANaJcaAhd)<=(WuWa4iT)GwAxac_NG+8
       && ih1YL
      ){
        return 1;  /* corrupt record not detected by
                   ** sqlite3VdbeRecordCompareWithSkip().  Return true
                   ** to avoid firing the assert() */
      }
      break;
    }

    /* Extract the values to be compared.
    */
    WKkx9Vx9(&Yn2R5CEn[WuLRESmsSj], EmGANaJcaAhd, &bBByAg);
    WuLRESmsSj += NI158jGWh(EmGANaJcaAhd);

    /* Do the comparison
    */
    YPgcEHzPuCIF = Z_Yasn(&bBByAg, &t8EU->CSO_5[Pyy0l6xD],
                           N0B0w0pr1Cz->Xn4s88sqBM>Pyy0l6xD ? N0B0w0pr1Cz->izMnyxj_sW9X[Pyy0l6xD] : 0);
    if( YPgcEHzPuCIF!=0 ){
      f5IeCeK0e1W( bBByAg.N3A21Ra4MY24m==0 );  /* See comment below */
      if( (N0B0w0pr1Cz->iIxU[Pyy0l6xD] & Ndk748d98M2)
       && ((bBByAg.MRNoo5HiPBk7 & NIJTPrY3UI) || (t8EU->CSO_5[Pyy0l6xD].MRNoo5HiPBk7 & NIJTPrY3UI))
      ){
        YPgcEHzPuCIF = -YPgcEHzPuCIF;
      }
      if( N0B0w0pr1Cz->iIxU[Pyy0l6xD] & HZ5O ){
        YPgcEHzPuCIF = -YPgcEHzPuCIF;  /* Invert the result for DESC sort order. */
      }
      goto p1MMYwUsj;
    }
    Pyy0l6xD++;
  }while( gMsz<zI_N5t27 && Pyy0l6xD<t8EU->FRi83T );

  /* No memory allocation is ever used on mem1.  Prove this using
  ** the following assert().  If the assert() fails, it indicates a
  ** memory leak and a need to call sqlite3VdbeMemRelease(&mem1).
  */
  f5IeCeK0e1W( bBByAg.N3A21Ra4MY24m==0 );

  /* rc==0 here means that one of the keys ran out of fields and
  ** all the fields up to that point were equal. Return the default_rc
  ** value.  */
  YPgcEHzPuCIF = t8EU->MhFnYCyMziO;

p1MMYwUsj:
  if( rpmFh_dSyrSSl==0 && YPgcEHzPuCIF==0 ) return 1;
  if( rpmFh_dSyrSSl<0 && YPgcEHzPuCIF<0 ) return 1;
  if( rpmFh_dSyrSSl>0 && YPgcEHzPuCIF>0 ) return 1;
  if( ih1YL ) return 1;
  if( N0B0w0pr1Cz->pLMJg2Xd->mi4oOCmRVN_h ) return 1;
  return 0;
}
#endif

#ifdef iteB65TL5L
/*
** Count the number of fields (a.k.a. columns) in the record given by
** pKey,nKey.  The verify that this count is less than or equal to the
** limit given by pKeyInfo->nAllField.
**
** If this constraint is not satisfied, it means that the high-speed
** vdbeRecordCompareInt() and vdbeRecordCompareString() routines will
** not work correctly.  If this assert() ever fires, it probably means
** that the KeyInfo.nKeyField or KeyInfo.nAllField values were computed
** incorrectly.
*/
static void esd59bKNUZ2eS(
  int v4U6UE, const void *iSrbtrwTQI,   /* The record to verify */
  const Yen3v7sHJ_Gb *N0B0w0pr1Cz       /* Compare size with this KeyInfo */
){
  int FRi83T = 0;
  JamYDTpy dVY8BONXMY;
  JamYDTpy wrlhjKL_;
  JamYDTpy sk3H5SPdbUhIA;
  const unsigned char *sR9oM7XAZ = (const unsigned char*)iSrbtrwTQI;

  if( ih1YL ) return;
  wrlhjKL_ = S2kGTVNXuvs(sR9oM7XAZ, dVY8BONXMY);
  f5IeCeK0e1W( v4U6UE>=0 );
  f5IeCeK0e1W( dVY8BONXMY<=(JamYDTpy)v4U6UE );
  while( wrlhjKL_<dVY8BONXMY ){
    wrlhjKL_ += S2kGTVNXuvs(sR9oM7XAZ+wrlhjKL_, sk3H5SPdbUhIA);
    FRi83T++;
  }
  f5IeCeK0e1W( FRi83T <= N0B0w0pr1Cz->Xn4s88sqBM );
}
#else
# define esd59bKNUZ2eS(jc6C62OFe_,aJnMy,Mywj4u)
#endif

/*
** Both *pMem1 and *pMem2 contain string values. Compare the two values
** using the collation sequence pColl. As usual, return a negative , zero
** or positive value if *pMem1 is less than, equal to or greater than
** *pMem2, respectively. Similar in spirit to "rc = (*pMem1) - (*pMem2);".
*/
static int m2tVim3ZpJ8p(
  const oi4q2s5KcMX9Y *PN2RtK54O,
  const oi4q2s5KcMX9Y *PYczlBkfwugLK,
  const ri6hxZ *VrQRc7aD,
  qHh5JW *ugmdHBftbIUZ                      /* If an OOM occurs, set to SQLITE_NOMEM */
){
  if( PN2RtK54O->Tc4R1==VrQRc7aD->Tc4R1 ){
    /* The strings are already in the correct encoding.  Call the
     ** comparison function directly */
    return VrQRc7aD->abtfHpHvm(VrQRc7aD->cvzsQCs0v3qX,PN2RtK54O->AS0ycVs,PN2RtK54O->mrgekw0xj,PYczlBkfwugLK->AS0ycVs,PYczlBkfwugLK->mrgekw0xj);
  }else{
    int YPgcEHzPuCIF;
    const void *PYIK7IfGiwFYz, *ImFLUcfz;
    oi4q2s5KcMX9Y I7Y7hiEM6cJ;
    oi4q2s5KcMX9Y mMpZ;
    fTNaHo(&I7Y7hiEM6cJ, PN2RtK54O->pLMJg2Xd, NIJTPrY3UI);
    fTNaHo(&mMpZ, PN2RtK54O->pLMJg2Xd, NIJTPrY3UI);
    hIjYdxkCox(&I7Y7hiEM6cJ, PN2RtK54O, hu94vgEoB);
    hIjYdxkCox(&mMpZ, PYczlBkfwugLK, hu94vgEoB);
    PYIK7IfGiwFYz = wT8R6Rk((EPdZvOoD0Wseb*)&I7Y7hiEM6cJ, VrQRc7aD->Tc4R1);
    ImFLUcfz = wT8R6Rk((EPdZvOoD0Wseb*)&mMpZ, VrQRc7aD->Tc4R1);
    if( (PYIK7IfGiwFYz==0 || ImFLUcfz==0) ){
      if( ugmdHBftbIUZ ) *ugmdHBftbIUZ = gbOccFBhQR;
      YPgcEHzPuCIF = 0;
    }else{
      YPgcEHzPuCIF = VrQRc7aD->abtfHpHvm(VrQRc7aD->cvzsQCs0v3qX, I7Y7hiEM6cJ.AS0ycVs, PYIK7IfGiwFYz, mMpZ.AS0ycVs, ImFLUcfz);
    }
    fU3PFeqj(&I7Y7hiEM6cJ);
    fU3PFeqj(&mMpZ);
    return YPgcEHzPuCIF;
  }
}

/*
** The input pBlob is guaranteed to be a Blob that is not marked
** with MEM_Zero.  Return true if it could be a zero-blob.
*/
static int ibdiel(const char *mrgekw0xj, int AS0ycVs){
  int Pyy0l6xD;
  for(Pyy0l6xD=0; Pyy0l6xD<AS0ycVs; Pyy0l6xD++){
    if( mrgekw0xj[Pyy0l6xD] ) return 0;
  }
  return 1;
}

/*
** Compare two blobs.  Return negative, zero, or positive if the first
** is less than, equal to, or greater than the second, respectively.
** If one blob is a prefix of the other, then the shorter is the lessor.
*/
XmVnyUQh int mPzsJMbMR(const oi4q2s5KcMX9Y *Pqxi3, const oi4q2s5KcMX9Y *zuVgw1DCPFb){
  int Wydjdw_pm6;
  int rx8erlt4N = Pqxi3->AS0ycVs;
  int jifY = zuVgw1DCPFb->AS0ycVs;

  /* It is possible to have a Blob value that has some non-zero content
  ** followed by zero content.  But that only comes up for Blobs formed
  ** by the OP_MakeRecord opcode, and such Blobs never get passed into
  ** sqlite3MemCompare(). */
  f5IeCeK0e1W( (Pqxi3->MRNoo5HiPBk7 & LYov5I)==0 || rx8erlt4N==0 );
  f5IeCeK0e1W( (zuVgw1DCPFb->MRNoo5HiPBk7 & LYov5I)==0 || jifY==0 );

  if( (Pqxi3->MRNoo5HiPBk7|zuVgw1DCPFb->MRNoo5HiPBk7) & LYov5I ){
    if( Pqxi3->MRNoo5HiPBk7 & zuVgw1DCPFb->MRNoo5HiPBk7 & LYov5I ){
      return Pqxi3->r43Pj.oSkdrwZWp - zuVgw1DCPFb->r43Pj.oSkdrwZWp;
    }else if( Pqxi3->MRNoo5HiPBk7 & LYov5I ){
      if( !ibdiel(zuVgw1DCPFb->mrgekw0xj, zuVgw1DCPFb->AS0ycVs) ) return -1;
      return Pqxi3->r43Pj.oSkdrwZWp - jifY;
    }else{
      if( !ibdiel(Pqxi3->mrgekw0xj, Pqxi3->AS0ycVs) ) return +1;
      return rx8erlt4N - zuVgw1DCPFb->r43Pj.oSkdrwZWp;
    }
  }
  Wydjdw_pm6 = zUuN(Pqxi3->mrgekw0xj, zuVgw1DCPFb->mrgekw0xj, rx8erlt4N>jifY ? jifY : rx8erlt4N);
  if( Wydjdw_pm6 ) return Wydjdw_pm6;
  return rx8erlt4N - jifY;
}

/* The following two functions are used only within testcase() to prove
** test coverage.  These functions do no exist for production builds.
** We must use separate SQLITE_NOINLINE functions here, since otherwise
** optimizer code movement causes gcov to become very confused.
*/
#if  pZX7GD4OTcuV(JSHhBaD) || pZX7GD4OTcuV(iteB65TL5L)
static int XmVnyUQh Ahy8(double xNcGjo, double a8pTnQIIAQ){ return xNcGjo<a8pTnQIIAQ; }
static int XmVnyUQh pNcs_YnEjlYN(double xNcGjo, double a8pTnQIIAQ){ return xNcGjo==a8pTnQIIAQ; }
#endif

/*
** Do a comparison between a 64-bit signed integer and a 64-bit floating-point
** number.  Return negative, zero, or positive if the first (i64) is less than,
** equal to, or greater than the second (double).
*/
int U9Fu8PTZJ(XBJDNN3j Pyy0l6xD, double uNdS8p26k){
  if( gzm98jAdQpwj0(uNdS8p26k) ){
    /* SQLite considers NaN to be a NULL. And all integer values are greater
    ** than NULL */
    return 1;
  }
  if( MnntHColr.noF2cG ){
    VCkia1P zCVq = (VCkia1P)Pyy0l6xD;
    gwlDS2AhlE3Xe( zCVq<uNdS8p26k );
    gwlDS2AhlE3Xe( zCVq>uNdS8p26k );
    gwlDS2AhlE3Xe( zCVq==uNdS8p26k );
    return (zCVq<uNdS8p26k) ? -1 : (zCVq>uNdS8p26k);
  }else{
    XBJDNN3j V2NN0qsOZKw;
    if( uNdS8p26k<-9223372036854775808.0 ) return +1;
    if( uNdS8p26k>=9223372036854775808.0 ) return -1;
    V2NN0qsOZKw = (XBJDNN3j)uNdS8p26k;
    if( Pyy0l6xD<V2NN0qsOZKw ) return -1;
    if( Pyy0l6xD>V2NN0qsOZKw ) return +1;
    gwlDS2AhlE3Xe( Ahy8(((double)Pyy0l6xD),uNdS8p26k) );
    gwlDS2AhlE3Xe( Ahy8(uNdS8p26k,((double)Pyy0l6xD)) );
    gwlDS2AhlE3Xe( pNcs_YnEjlYN(uNdS8p26k,((double)Pyy0l6xD)) );
    return (((double)Pyy0l6xD)<uNdS8p26k) ? -1 : (((double)Pyy0l6xD)>uNdS8p26k);
  }
}

/*
** Compare the values contained by the two memory cells, returning
** negative, zero or positive if pMem1 is less than, equal to, or greater
** than pMem2. Sorting order is NULL's first, followed by numbers (integers
** and reals) sorted numerically, followed by text ordered by the collating
** sequence pColl and finally blob's ordered by memcmp().
**
** Two NULL values are considered equal by this function.
*/
int Z_Yasn(const oi4q2s5KcMX9Y *PN2RtK54O, const oi4q2s5KcMX9Y *PYczlBkfwugLK, const ri6hxZ *VrQRc7aD){
  int USO4c4QhG3r, qxhb9pA;
  int b_gMatLOufyV;

  USO4c4QhG3r = PN2RtK54O->MRNoo5HiPBk7;
  qxhb9pA = PYczlBkfwugLK->MRNoo5HiPBk7;
  b_gMatLOufyV = USO4c4QhG3r|qxhb9pA;
  f5IeCeK0e1W( !nflu2lGZrnYI(PN2RtK54O) && !nflu2lGZrnYI(PYczlBkfwugLK) );

  /* If one value is NULL, it is less than the other. If both values
  ** are NULL, return 0.
  */
  if( b_gMatLOufyV&NIJTPrY3UI ){
    return (qxhb9pA&NIJTPrY3UI) - (USO4c4QhG3r&NIJTPrY3UI);
  }

  /* At least one of the two values is a number
  */
  if( b_gMatLOufyV&(qN6FC41ULkGDO|ITDPS|tbmTzwycmDB) ){
    gwlDS2AhlE3Xe( b_gMatLOufyV & qN6FC41ULkGDO );
    gwlDS2AhlE3Xe( b_gMatLOufyV & ITDPS );
    gwlDS2AhlE3Xe( b_gMatLOufyV & tbmTzwycmDB );
    if( (USO4c4QhG3r & qxhb9pA & (qN6FC41ULkGDO|tbmTzwycmDB))!=0 ){
      gwlDS2AhlE3Xe( USO4c4QhG3r & qxhb9pA & qN6FC41ULkGDO );
      gwlDS2AhlE3Xe( USO4c4QhG3r & qxhb9pA & tbmTzwycmDB );
      if( PN2RtK54O->r43Pj.Pyy0l6xD < PYczlBkfwugLK->r43Pj.Pyy0l6xD ) return -1;
      if( PN2RtK54O->r43Pj.Pyy0l6xD > PYczlBkfwugLK->r43Pj.Pyy0l6xD ) return +1;
      return 0;
    }
    if( (USO4c4QhG3r & qxhb9pA & ITDPS)!=0 ){
      if( PN2RtK54O->r43Pj.uNdS8p26k < PYczlBkfwugLK->r43Pj.uNdS8p26k ) return -1;
      if( PN2RtK54O->r43Pj.uNdS8p26k > PYczlBkfwugLK->r43Pj.uNdS8p26k ) return +1;
      return 0;
    }
    if( (USO4c4QhG3r&(qN6FC41ULkGDO|tbmTzwycmDB))!=0 ){
      gwlDS2AhlE3Xe( USO4c4QhG3r & qN6FC41ULkGDO );
      gwlDS2AhlE3Xe( USO4c4QhG3r & tbmTzwycmDB );
      if( (qxhb9pA&ITDPS)!=0 ){
        return U9Fu8PTZJ(PN2RtK54O->r43Pj.Pyy0l6xD, PYczlBkfwugLK->r43Pj.uNdS8p26k);
      }else if( (qxhb9pA&(qN6FC41ULkGDO|tbmTzwycmDB))!=0 ){
        if( PN2RtK54O->r43Pj.Pyy0l6xD < PYczlBkfwugLK->r43Pj.Pyy0l6xD ) return -1;
        if( PN2RtK54O->r43Pj.Pyy0l6xD > PYczlBkfwugLK->r43Pj.Pyy0l6xD ) return +1;
        return 0;
      }else{
        return -1;
      }
    }
    if( (USO4c4QhG3r&ITDPS)!=0 ){
      if( (qxhb9pA&(qN6FC41ULkGDO|tbmTzwycmDB))!=0 ){
        gwlDS2AhlE3Xe( qxhb9pA & qN6FC41ULkGDO );
        gwlDS2AhlE3Xe( qxhb9pA & tbmTzwycmDB );
        return -U9Fu8PTZJ(PYczlBkfwugLK->r43Pj.Pyy0l6xD, PN2RtK54O->r43Pj.uNdS8p26k);
      }else{
        return -1;
      }
    }
    return +1;
  }

  /* If one value is a string and the other is a blob, the string is less.
  ** If both are strings, compare using the collating functions.
  */
  if( b_gMatLOufyV&caIIAbkg ){
    if( (USO4c4QhG3r & caIIAbkg)==0 ){
      return 1;
    }
    if( (qxhb9pA & caIIAbkg)==0 ){
      return -1;
    }

    f5IeCeK0e1W( PN2RtK54O->Tc4R1==PYczlBkfwugLK->Tc4R1 || PN2RtK54O->pLMJg2Xd->mi4oOCmRVN_h );
    f5IeCeK0e1W( PN2RtK54O->Tc4R1==XaWPmn7sUsHo4 ||
            PN2RtK54O->Tc4R1==q6cx4iDcV4TF || PN2RtK54O->Tc4R1==ej5le0pA );

    /* The collation sequence must be defined at this point, even if
    ** the user deletes the collation sequence after the vdbe program is
    ** compiled (this was not always the case).
    */
    f5IeCeK0e1W( !VrQRc7aD || VrQRc7aD->abtfHpHvm );

    if( VrQRc7aD ){
      return m2tVim3ZpJ8p(PN2RtK54O, PYczlBkfwugLK, VrQRc7aD, 0);
    }
    /* If a NULL pointer was passed as the collate function, fall through
    ** to the blob case and use memcmp().  */
  }

  /* Both values must be blobs.  Compare using memcmp().  */
  return mPzsJMbMR(PN2RtK54O, PYczlBkfwugLK);
}


/*
** The first argument passed to this function is a serial-type that
** corresponds to an integer - all values between 1 and 9 inclusive
** except 7. The second points to a buffer containing an integer value
** serialized according to serial_type. This function deserializes
** and returns the value.
*/
static XBJDNN3j FjrA3NjmyswC(JamYDTpy nvQLph, const qHh5JW *sR9oM7XAZ){
  JamYDTpy V2NN0qsOZKw;
  f5IeCeK0e1W( ih1YL || (nvQLph>=1 && nvQLph<=9 && nvQLph!=7) );
  switch( nvQLph ){
    case 0:
    case 1:
      gwlDS2AhlE3Xe( sR9oM7XAZ[0]&0x80 );
      return ys0BGI(sR9oM7XAZ);
    case 2:
      gwlDS2AhlE3Xe( sR9oM7XAZ[0]&0x80 );
      return fIlGE(sR9oM7XAZ);
    case 3:
      gwlDS2AhlE3Xe( sR9oM7XAZ[0]&0x80 );
      return RPMiG9zcPWTS(sR9oM7XAZ);
    case 4: {
      gwlDS2AhlE3Xe( sR9oM7XAZ[0]&0x80 );
      V2NN0qsOZKw = lNwn(sR9oM7XAZ);
      return (XBJDNN3j)*(int*)&V2NN0qsOZKw;
    }
    case 5: {
      gwlDS2AhlE3Xe( sR9oM7XAZ[0]&0x80 );
      return lNwn(sR9oM7XAZ+2) + (((XBJDNN3j)1)<<32)*fIlGE(sR9oM7XAZ);
    }
    case 6: {
      WuWa4iT zCVq = lNwn(sR9oM7XAZ);
      gwlDS2AhlE3Xe( sR9oM7XAZ[0]&0x80 );
      zCVq = (zCVq<<32) | lNwn(sR9oM7XAZ+4);
      return (XBJDNN3j)*(XBJDNN3j*)&zCVq;
    }
  }

  return (nvQLph - 8);
}

/*
** This function compares the two table rows or index records
** specified by {nKey1, pKey1} and pPKey2.  It returns a negative, zero
** or positive integer if key1 is less than, equal to or
** greater than key2.  The {nKey1, pKey1} key must be a blob
** created by the OP_MakeRecord opcode of the VDBE.  The pPKey2
** key must be a parsed key such as obtained from
** sqlite3VdbeParseRecord.
**
** If argument bSkip is non-zero, it is assumed that the caller has already
** determined that the first fields of the keys are equal.
**
** Key1 and Key2 do not have to contain the same number of fields. If all
** fields that appear in both keys are equal, then pPKey2->default_rc is
** returned.
**
** If database corruption is discovered, set pPKey2->errCode to
** SQLITE_CORRUPT and return 0. If an OOM error is encountered,
** pPKey2->errCode is set to SQLITE_NOMEM and, if it is not NULL, the
** malloc-failed flag set on database handle (pPKey2->pKeyInfo->db).
*/
int zX9Vhd(
  int GwAxac_NG, const void *HFeOU,   /* Left key */
  Byn9mdCAjUkY9 *t8EU,         /* Right key */
  int S3rb80rFEC3CU                       /* If true, skip the first field */
){
  JamYDTpy WuLRESmsSj;                         /* Offset into aKey[] of next data element */
  int Pyy0l6xD;                          /* Index of next field to compare */
  JamYDTpy zI_N5t27;                     /* Size of record header in bytes */
  JamYDTpy gMsz;                       /* Offset of first type in header */
  int YPgcEHzPuCIF = 0;                     /* Return value */
  oi4q2s5KcMX9Y *TF7jh = t8EU->CSO_5;       /* Next field of pPKey2 to compare */
  Yen3v7sHJ_Gb *N0B0w0pr1Cz;
  const unsigned char *Yn2R5CEn = (const unsigned char *)HFeOU;
  oi4q2s5KcMX9Y bBByAg;

  /* If bSkip is true, then the caller has already determined that the first
  ** two elements in the keys are equal. Fix the various stack variables so
  ** that this routine begins comparing at the second field. */
  if( S3rb80rFEC3CU ){
    JamYDTpy acozL4d4 = Yn2R5CEn[1];
    if( acozL4d4<0x80 ){
      gMsz = 2;
    }else{
      gMsz = 1 + JXF0(&Yn2R5CEn[1], &acozL4d4);
    }
    zI_N5t27 = Yn2R5CEn[0];
    WuLRESmsSj = zI_N5t27 + NI158jGWh(acozL4d4);
    Pyy0l6xD = 1;
    TF7jh++;
  }else{
    if( (zI_N5t27 = Yn2R5CEn[0])<0x80 ){
      gMsz = 1;
    }else{
      gMsz = JXF0(Yn2R5CEn, &zI_N5t27);
    }
    WuLRESmsSj = zI_N5t27;
    Pyy0l6xD = 0;
  }
  if( WuLRESmsSj>(unsigned)GwAxac_NG ){
    t8EU->Zr03AqCCJT = (qHh5JW)mVXrATk9;
    return 0;  /* Corruption */
  }

  GHCxb3ljLpK( bBByAg.N3A21Ra4MY24m = 0; ) /* Only needed by assert() statements */
  f5IeCeK0e1W( t8EU->N0B0w0pr1Cz->Xn4s88sqBM>=t8EU->FRi83T
       || ih1YL );
  f5IeCeK0e1W( t8EU->N0B0w0pr1Cz->iIxU!=0 );
  f5IeCeK0e1W( t8EU->N0B0w0pr1Cz->tr0jn>0 );
  f5IeCeK0e1W( gMsz<=zI_N5t27 || ih1YL );
  while( 1 /*exit-by-break*/ ){
    JamYDTpy nvQLph;

    /* RHS is an integer */
    if( TF7jh->MRNoo5HiPBk7 & (qN6FC41ULkGDO|tbmTzwycmDB) ){
      gwlDS2AhlE3Xe( TF7jh->MRNoo5HiPBk7 & qN6FC41ULkGDO );
      gwlDS2AhlE3Xe( TF7jh->MRNoo5HiPBk7 & tbmTzwycmDB );
      nvQLph = Yn2R5CEn[gMsz];
      gwlDS2AhlE3Xe( nvQLph==12 );
      if( nvQLph>=10 ){
        YPgcEHzPuCIF = nvQLph==10 ? -1 : +1;
      }else if( nvQLph==0 ){
        YPgcEHzPuCIF = -1;
      }else if( nvQLph==7 ){
        MjkcH33(&Yn2R5CEn[WuLRESmsSj], &bBByAg);
        YPgcEHzPuCIF = -U9Fu8PTZJ(TF7jh->r43Pj.Pyy0l6xD, bBByAg.r43Pj.uNdS8p26k);
      }else{
        XBJDNN3j xVQZjk5Q = FjrA3NjmyswC(nvQLph, &Yn2R5CEn[WuLRESmsSj]);
        XBJDNN3j g8Pg = TF7jh->r43Pj.Pyy0l6xD;
        if( xVQZjk5Q<g8Pg ){
          YPgcEHzPuCIF = -1;
        }else if( xVQZjk5Q>g8Pg ){
          YPgcEHzPuCIF = +1;
        }
      }
    }

    /* RHS is real */
    else if( TF7jh->MRNoo5HiPBk7 & ITDPS ){
      nvQLph = Yn2R5CEn[gMsz];
      if( nvQLph>=10 ){
        /* Serial types 12 or greater are strings and blobs (greater than
        ** numbers). Types 10 and 11 are currently "reserved for future
        ** use", so it doesn't really matter what the results of comparing
        ** them to numeric values are.  */
        YPgcEHzPuCIF = nvQLph==10 ? -1 : +1;
      }else if( nvQLph==0 ){
        YPgcEHzPuCIF = -1;
      }else{
        if( nvQLph==7 ){
          if( MjkcH33(&Yn2R5CEn[WuLRESmsSj], &bBByAg) ){
            YPgcEHzPuCIF = -1;  /* mem1 is a NaN */
          }else if( bBByAg.r43Pj.uNdS8p26k<TF7jh->r43Pj.uNdS8p26k ){
            YPgcEHzPuCIF = -1;
          }else if( bBByAg.r43Pj.uNdS8p26k>TF7jh->r43Pj.uNdS8p26k ){
            YPgcEHzPuCIF = +1;
          }else{
            f5IeCeK0e1W( YPgcEHzPuCIF==0 );
          }
        }else{
          WKkx9Vx9(&Yn2R5CEn[WuLRESmsSj], nvQLph, &bBByAg);
          YPgcEHzPuCIF = U9Fu8PTZJ(bBByAg.r43Pj.Pyy0l6xD, TF7jh->r43Pj.uNdS8p26k);
        }
      }
    }

    /* RHS is a string */
    else if( TF7jh->MRNoo5HiPBk7 & caIIAbkg ){
      XgqDenD9BwGi(&Yn2R5CEn[gMsz], nvQLph);
      gwlDS2AhlE3Xe( nvQLph==12 );
      if( nvQLph<12 ){
        YPgcEHzPuCIF = -1;
      }else if( !(nvQLph & 0x01) ){
        YPgcEHzPuCIF = +1;
      }else{
        bBByAg.AS0ycVs = (nvQLph - 12) / 2;
        gwlDS2AhlE3Xe( (WuLRESmsSj+bBByAg.AS0ycVs)==(unsigned)GwAxac_NG );
        gwlDS2AhlE3Xe( (WuLRESmsSj+bBByAg.AS0ycVs+1)==(unsigned)GwAxac_NG );
        if( (WuLRESmsSj+bBByAg.AS0ycVs) > (unsigned)GwAxac_NG
         || (N0B0w0pr1Cz = t8EU->N0B0w0pr1Cz)->Xn4s88sqBM<=Pyy0l6xD
        ){
          t8EU->Zr03AqCCJT = (qHh5JW)mVXrATk9;
          return 0;                /* Corruption */
        }else if( N0B0w0pr1Cz->izMnyxj_sW9X[Pyy0l6xD] ){
          bBByAg.Tc4R1 = N0B0w0pr1Cz->Tc4R1;
          bBByAg.pLMJg2Xd = N0B0w0pr1Cz->pLMJg2Xd;
          bBByAg.MRNoo5HiPBk7 = caIIAbkg;
          bBByAg.mrgekw0xj = (char*)&Yn2R5CEn[WuLRESmsSj];
          YPgcEHzPuCIF = m2tVim3ZpJ8p(
              &bBByAg, TF7jh, N0B0w0pr1Cz->izMnyxj_sW9X[Pyy0l6xD], &t8EU->Zr03AqCCJT
          );
        }else{
          int w7N9 = I5rGi4ze(bBByAg.AS0ycVs, TF7jh->AS0ycVs);
          YPgcEHzPuCIF = zUuN(&Yn2R5CEn[WuLRESmsSj], TF7jh->mrgekw0xj, w7N9);
          if( YPgcEHzPuCIF==0 ) YPgcEHzPuCIF = bBByAg.AS0ycVs - TF7jh->AS0ycVs;
        }
      }
    }

    /* RHS is a blob */
    else if( TF7jh->MRNoo5HiPBk7 & GrDQtTd ){
      f5IeCeK0e1W( (TF7jh->MRNoo5HiPBk7 & LYov5I)==0 || TF7jh->AS0ycVs==0 );
      XgqDenD9BwGi(&Yn2R5CEn[gMsz], nvQLph);
      gwlDS2AhlE3Xe( nvQLph==12 );
      if( nvQLph<12 || (nvQLph & 0x01) ){
        YPgcEHzPuCIF = -1;
      }else{
        int A5iww9P = (nvQLph - 12) / 2;
        gwlDS2AhlE3Xe( (WuLRESmsSj+A5iww9P)==(unsigned)GwAxac_NG );
        gwlDS2AhlE3Xe( (WuLRESmsSj+A5iww9P+1)==(unsigned)GwAxac_NG );
        if( (WuLRESmsSj+A5iww9P) > (unsigned)GwAxac_NG ){
          t8EU->Zr03AqCCJT = (qHh5JW)mVXrATk9;
          return 0;                /* Corruption */
        }else if( TF7jh->MRNoo5HiPBk7 & LYov5I ){
          if( !ibdiel((const char*)&Yn2R5CEn[WuLRESmsSj],A5iww9P) ){
            YPgcEHzPuCIF = 1;
          }else{
            YPgcEHzPuCIF = A5iww9P - TF7jh->r43Pj.oSkdrwZWp;
          }
        }else{
          int w7N9 = I5rGi4ze(A5iww9P, TF7jh->AS0ycVs);
          YPgcEHzPuCIF = zUuN(&Yn2R5CEn[WuLRESmsSj], TF7jh->mrgekw0xj, w7N9);
          if( YPgcEHzPuCIF==0 ) YPgcEHzPuCIF = A5iww9P - TF7jh->AS0ycVs;
        }
      }
    }

    /* RHS is null */
    else{
      nvQLph = Yn2R5CEn[gMsz];
      if( nvQLph==0
       || nvQLph==10
       || (nvQLph==7 && MjkcH33(&Yn2R5CEn[WuLRESmsSj], &bBByAg)!=0)
      ){
        f5IeCeK0e1W( YPgcEHzPuCIF==0 );
      }else{
        YPgcEHzPuCIF = 1;
      }
    }

    if( YPgcEHzPuCIF!=0 ){
      int j8Tl5Dkgb = t8EU->N0B0w0pr1Cz->iIxU[Pyy0l6xD];
      if( j8Tl5Dkgb ){
        if( (j8Tl5Dkgb & Ndk748d98M2)==0
         || ((j8Tl5Dkgb & HZ5O)
           !=(nvQLph==0 || (TF7jh->MRNoo5HiPBk7&NIJTPrY3UI)))
        ){
          YPgcEHzPuCIF = -YPgcEHzPuCIF;
        }
      }
      f5IeCeK0e1W( kiq86cF2b(GwAxac_NG, HFeOU, t8EU, YPgcEHzPuCIF) );
      f5IeCeK0e1W( bBByAg.N3A21Ra4MY24m==0 );  /* See comment below */
      return YPgcEHzPuCIF;
    }

    Pyy0l6xD++;
    if( Pyy0l6xD==t8EU->FRi83T ) break;
    TF7jh++;
    WuLRESmsSj += NI158jGWh(nvQLph);
    if( WuLRESmsSj>(unsigned)GwAxac_NG ) break;
    gMsz += ksKJ(nvQLph);
    if( gMsz>=(unsigned)zI_N5t27 ){
      t8EU->Zr03AqCCJT = (qHh5JW)mVXrATk9;
      return 0;  /* Corrupt index */
    }
  }

  /* No memory allocation is ever used on mem1.  Prove this using
  ** the following assert().  If the assert() fails, it indicates a
  ** memory leak and a need to call sqlite3VdbeMemRelease(&mem1).  */
  f5IeCeK0e1W( bBByAg.N3A21Ra4MY24m==0 );

  /* rc==0 here means that one or both of the keys ran out of fields and
  ** all the fields up to that point were equal. Return the default_rc
  ** value.  */
  f5IeCeK0e1W( ih1YL
       || kiq86cF2b(GwAxac_NG, HFeOU, t8EU, t8EU->MhFnYCyMziO)
       || t8EU->N0B0w0pr1Cz->pLMJg2Xd->mi4oOCmRVN_h
  );
  t8EU->pq3ttUv = 1;
  return t8EU->MhFnYCyMziO;
}
int QF01TRHspO9(
  int GwAxac_NG, const void *HFeOU,   /* Left key */
  Byn9mdCAjUkY9 *t8EU          /* Right key */
){
  return zX9Vhd(GwAxac_NG, HFeOU, t8EU, 0);
}


/*
** This function is an optimized version of sqlite3VdbeRecordCompare()
** that (a) the first field of pPKey2 is an integer, and (b) the
** size-of-header varint at the start of (pKey1/nKey1) fits in a single
** byte (i.e. is less than 128).
**
** To avoid concerns about buffer overreads, this routine is only used
** on schemas where the maximum valid header size is 63 bytes or less.
*/
static int LDHHncJT(
  int GwAxac_NG, const void *HFeOU, /* Left key */
  Byn9mdCAjUkY9 *t8EU        /* Right key */
){
  const qHh5JW *sR9oM7XAZ = &((const qHh5JW*)HFeOU)[*(const qHh5JW*)HFeOU & 0x3F];
  int nvQLph = ((const qHh5JW*)HFeOU)[1];
  int E6VmXbBADn7;
  JamYDTpy V2NN0qsOZKw;
  WuWa4iT zCVq;
  XBJDNN3j HB_T1jBCLdNzN;
  XBJDNN3j xVQZjk5Q;

  esd59bKNUZ2eS(GwAxac_NG, HFeOU, t8EU->N0B0w0pr1Cz);
  f5IeCeK0e1W( (*(qHh5JW*)HFeOU)<=0x3F || ih1YL );
  switch( nvQLph ){
    case 1: { /* 1-byte signed integer */
      xVQZjk5Q = ys0BGI(sR9oM7XAZ);
      gwlDS2AhlE3Xe( xVQZjk5Q<0 );
      break;
    }
    case 2: { /* 2-byte signed integer */
      xVQZjk5Q = fIlGE(sR9oM7XAZ);
      gwlDS2AhlE3Xe( xVQZjk5Q<0 );
      break;
    }
    case 3: { /* 3-byte signed integer */
      xVQZjk5Q = RPMiG9zcPWTS(sR9oM7XAZ);
      gwlDS2AhlE3Xe( xVQZjk5Q<0 );
      break;
    }
    case 4: { /* 4-byte signed integer */
      V2NN0qsOZKw = lNwn(sR9oM7XAZ);
      xVQZjk5Q = (XBJDNN3j)*(int*)&V2NN0qsOZKw;
      gwlDS2AhlE3Xe( xVQZjk5Q<0 );
      break;
    }
    case 5: { /* 6-byte signed integer */
      xVQZjk5Q = lNwn(sR9oM7XAZ+2) + (((XBJDNN3j)1)<<32)*fIlGE(sR9oM7XAZ);
      gwlDS2AhlE3Xe( xVQZjk5Q<0 );
      break;
    }
    case 6: { /* 8-byte signed integer */
      zCVq = lNwn(sR9oM7XAZ);
      zCVq = (zCVq<<32) | lNwn(sR9oM7XAZ+4);
      xVQZjk5Q = *(XBJDNN3j*)&zCVq;
      gwlDS2AhlE3Xe( xVQZjk5Q<0 );
      break;
    }
    case 8:
      xVQZjk5Q = 0;
      break;
    case 9:
      xVQZjk5Q = 1;
      break;

    /* This case could be removed without changing the results of running
    ** this code. Including it causes gcc to generate a faster switch
    ** statement (since the range of switch targets now starts at zero and
    ** is contiguous) but does not cause any duplicate code to be generated
    ** (as gcc is clever enough to combine the two like cases). Other
    ** compilers might be similar.  */
    case 0: case 7:
      return QF01TRHspO9(GwAxac_NG, HFeOU, t8EU);

    default:
      return QF01TRHspO9(GwAxac_NG, HFeOU, t8EU);
  }

  f5IeCeK0e1W( t8EU->r43Pj.Pyy0l6xD == t8EU->CSO_5[0].r43Pj.Pyy0l6xD );
  HB_T1jBCLdNzN = t8EU->r43Pj.Pyy0l6xD;
  if( HB_T1jBCLdNzN>xVQZjk5Q ){
    E6VmXbBADn7 = t8EU->rDYc;
  }else if( HB_T1jBCLdNzN<xVQZjk5Q ){
    E6VmXbBADn7 = t8EU->BfGt;
  }else if( t8EU->FRi83T>1 ){
    /* The first fields of the two keys are equal. Compare the trailing
    ** fields.  */
    E6VmXbBADn7 = zX9Vhd(GwAxac_NG, HFeOU, t8EU, 1);
  }else{
    /* The first fields of the two keys are equal and there are no trailing
    ** fields. Return pPKey2->default_rc in this case. */
    E6VmXbBADn7 = t8EU->MhFnYCyMziO;
    t8EU->pq3ttUv = 1;
  }

  f5IeCeK0e1W( kiq86cF2b(GwAxac_NG, HFeOU, t8EU, E6VmXbBADn7) );
  return E6VmXbBADn7;
}

/*
** This function is an optimized version of sqlite3VdbeRecordCompare()
** that (a) the first field of pPKey2 is a string, that (b) the first field
** uses the collation sequence BINARY and (c) that the size-of-header varint
** at the start of (pKey1/nKey1) fits in a single byte.
*/
static int zsbLZ4JcP(
  int GwAxac_NG, const void *HFeOU, /* Left key */
  Byn9mdCAjUkY9 *t8EU        /* Right key */
){
  const qHh5JW *Yn2R5CEn = (const qHh5JW*)HFeOU;
  int nvQLph;
  int E6VmXbBADn7;

  f5IeCeK0e1W( t8EU->CSO_5[0].MRNoo5HiPBk7 & caIIAbkg );
  f5IeCeK0e1W( t8EU->CSO_5[0].AS0ycVs == t8EU->AS0ycVs );
  f5IeCeK0e1W( t8EU->CSO_5[0].mrgekw0xj == t8EU->r43Pj.mrgekw0xj );
  esd59bKNUZ2eS(GwAxac_NG, HFeOU, t8EU->N0B0w0pr1Cz);
  nvQLph = (signed char)(Yn2R5CEn[1]);

Pxb9MO9J:
  if( nvQLph<12 ){
    if( nvQLph<0 ){
      JXF0(&Yn2R5CEn[1], (JamYDTpy*)&nvQLph);
      if( nvQLph>=12 ) goto Pxb9MO9J;
      f5IeCeK0e1W( ih1YL );
    }
    E6VmXbBADn7 = t8EU->rDYc;      /* (pKey1/nKey1) is a number or a null */
  }else if( !(nvQLph & 0x01) ){
    E6VmXbBADn7 = t8EU->BfGt;      /* (pKey1/nKey1) is a blob */
  }else{
    int w7N9;
    int A5iww9P;
    int dVY8BONXMY = Yn2R5CEn[0];

    A5iww9P = (nvQLph-12) / 2;
    if( (dVY8BONXMY + A5iww9P) > GwAxac_NG ){
      t8EU->Zr03AqCCJT = (qHh5JW)mVXrATk9;
      return 0;    /* Corruption */
    }
    w7N9 = I5rGi4ze( t8EU->AS0ycVs, A5iww9P );
    E6VmXbBADn7 = zUuN(&Yn2R5CEn[dVY8BONXMY], t8EU->r43Pj.mrgekw0xj, w7N9);

    if( E6VmXbBADn7>0 ){
      E6VmXbBADn7 = t8EU->BfGt;
    }else if( E6VmXbBADn7<0 ){
      E6VmXbBADn7 = t8EU->rDYc;
    }else{
      E6VmXbBADn7 = A5iww9P - t8EU->AS0ycVs;
      if( E6VmXbBADn7==0 ){
        if( t8EU->FRi83T>1 ){
          E6VmXbBADn7 = zX9Vhd(GwAxac_NG, HFeOU, t8EU, 1);
        }else{
          E6VmXbBADn7 = t8EU->MhFnYCyMziO;
          t8EU->pq3ttUv = 1;
        }
      }else if( E6VmXbBADn7>0 ){
        E6VmXbBADn7 = t8EU->BfGt;
      }else{
        E6VmXbBADn7 = t8EU->rDYc;
      }
    }
  }

  f5IeCeK0e1W( kiq86cF2b(GwAxac_NG, HFeOU, t8EU, E6VmXbBADn7)
       || ih1YL
       || t8EU->N0B0w0pr1Cz->pLMJg2Xd->mi4oOCmRVN_h
  );
  return E6VmXbBADn7;
}

/*
** Return a pointer to an sqlite3VdbeRecordCompare() compatible function
** suitable for comparing serialized records to the unpacked record passed
** as the only argument.
*/
sSp1vmBc AfDBZLWa2EQ(Byn9mdCAjUkY9 *RWdNEx2WUIO8x){
  /* varintRecordCompareInt() and varintRecordCompareString() both assume
  ** that the size-of-header varint that occurs at the start of each record
  ** fits in a single byte (i.e. is 127 or less). varintRecordCompareInt()
  ** also assumes that it is safe to overread a buffer by at least the
  ** maximum possible legal header size plus 8 bytes. Because there is
  ** guaranteed to be at least 74 (but not 136) bytes of padding following each
  ** buffer passed to varintRecordCompareInt() this makes it convenient to
  ** limit the size of the header to 64 bytes in cases where the first field
  ** is an integer.
  **
  ** The easiest way to enforce this limit is to consider only records with
  ** 13 fields or less. If the first field is an integer, the maximum legal
  ** header size is (12*5 + 1 + 1) bytes.  */
  if( RWdNEx2WUIO8x->N0B0w0pr1Cz->Xn4s88sqBM<=13 ){
    int MRNoo5HiPBk7 = RWdNEx2WUIO8x->CSO_5[0].MRNoo5HiPBk7;
    if( RWdNEx2WUIO8x->N0B0w0pr1Cz->iIxU[0] ){
      if( RWdNEx2WUIO8x->N0B0w0pr1Cz->iIxU[0] & Ndk748d98M2 ){
        return QF01TRHspO9;
      }
      RWdNEx2WUIO8x->rDYc = 1;
      RWdNEx2WUIO8x->BfGt = -1;
    }else{
      RWdNEx2WUIO8x->rDYc = -1;
      RWdNEx2WUIO8x->BfGt = 1;
    }
    if( (MRNoo5HiPBk7 & qN6FC41ULkGDO) ){
      RWdNEx2WUIO8x->r43Pj.Pyy0l6xD = RWdNEx2WUIO8x->CSO_5[0].r43Pj.Pyy0l6xD;
      return LDHHncJT;
    }
    gwlDS2AhlE3Xe( MRNoo5HiPBk7 & ITDPS );
    gwlDS2AhlE3Xe( MRNoo5HiPBk7 & NIJTPrY3UI );
    gwlDS2AhlE3Xe( MRNoo5HiPBk7 & GrDQtTd );
    if( (MRNoo5HiPBk7 & (ITDPS|tbmTzwycmDB|NIJTPrY3UI|GrDQtTd))==0
     && RWdNEx2WUIO8x->N0B0w0pr1Cz->izMnyxj_sW9X[0]==0
    ){
      f5IeCeK0e1W( MRNoo5HiPBk7 & caIIAbkg );
      RWdNEx2WUIO8x->r43Pj.mrgekw0xj = RWdNEx2WUIO8x->CSO_5[0].mrgekw0xj;
      RWdNEx2WUIO8x->AS0ycVs = RWdNEx2WUIO8x->CSO_5[0].AS0ycVs;
      return zsbLZ4JcP;
    }
  }

  return QF01TRHspO9;
}

/*
** pCur points at an index entry created using the OP_MakeRecord opcode.
** Read the rowid (the last field in the record) and store it in *rowid.
** Return SQLITE_OK if everything works, or an error code otherwise.
**
** pCur might be pointing to text obtained from a corrupt database file.
** So the content cannot be trusted.  Do appropriate checks on the content.
*/
int jVYWZcJBJmoJ(MEeQFpE4DzbZ *pLMJg2Xd, f5Sqror *FlTA8c6, XBJDNN3j *XQI8eroRS){
  XBJDNN3j HWcgIng = 0;
  int YPgcEHzPuCIF;
  JamYDTpy dVY8BONXMY;        /* Size of the header */
  JamYDTpy x12bJ;    /* Serial type of the rowid */
  JamYDTpy gLHZQ8QCaz;     /* Size of the rowid */
  oi4q2s5KcMX9Y R9Yq4FcE, HB_T1jBCLdNzN;

  /* Get the size of the index entry.  Only indices entries of less
  ** than 2GiB are support - anything large must be database corruption.
  ** Any corruption is detected in sqlite3BtreeParseCellPtr(), though, so
  ** this code can safely assume that nCellKey is 32-bits 
  */
  f5IeCeK0e1W( E1ys(FlTA8c6) );
  HWcgIng = P42CAIAm(FlTA8c6);
  f5IeCeK0e1W( (HWcgIng & fKRnlXHk)==(WuWa4iT)HWcgIng );

  /* Read in the complete content of the index entry */
  fTNaHo(&R9Yq4FcE, pLMJg2Xd, 0);
  YPgcEHzPuCIF = yIpp(FlTA8c6, (JamYDTpy)HWcgIng, &R9Yq4FcE);
  if( YPgcEHzPuCIF ){
    return YPgcEHzPuCIF;
  }

  /* The index entry must begin with a header size */
  XgqDenD9BwGi((qHh5JW*)R9Yq4FcE.mrgekw0xj, dVY8BONXMY);
  gwlDS2AhlE3Xe( dVY8BONXMY==3 );
  gwlDS2AhlE3Xe( dVY8BONXMY==(JamYDTpy)R9Yq4FcE.AS0ycVs );
  gwlDS2AhlE3Xe( dVY8BONXMY>0x7fffffff );
  f5IeCeK0e1W( R9Yq4FcE.AS0ycVs>=0 );
  if( xLPdjfWv(dVY8BONXMY<3 || dVY8BONXMY>(unsigned)R9Yq4FcE.AS0ycVs) ){
    goto ZAumR;
  }

  /* The last field of the index should be an integer - the ROWID.
  ** Verify that the last entry really is an integer. */
  XgqDenD9BwGi((qHh5JW*)&R9Yq4FcE.mrgekw0xj[dVY8BONXMY-1], x12bJ);
  gwlDS2AhlE3Xe( x12bJ==1 );
  gwlDS2AhlE3Xe( x12bJ==2 );
  gwlDS2AhlE3Xe( x12bJ==3 );
  gwlDS2AhlE3Xe( x12bJ==4 );
  gwlDS2AhlE3Xe( x12bJ==5 );
  gwlDS2AhlE3Xe( x12bJ==6 );
  gwlDS2AhlE3Xe( x12bJ==8 );
  gwlDS2AhlE3Xe( x12bJ==9 );
  if( xLPdjfWv(x12bJ<1 || x12bJ>9 || x12bJ==7) ){
    goto ZAumR;
  }
  gLHZQ8QCaz = OQD9[x12bJ];
  gwlDS2AhlE3Xe( (JamYDTpy)R9Yq4FcE.AS0ycVs==dVY8BONXMY+gLHZQ8QCaz );
  if( xLPdjfWv((JamYDTpy)R9Yq4FcE.AS0ycVs<dVY8BONXMY+gLHZQ8QCaz) ){
    goto ZAumR;
  }

  /* Fetch the integer off the end of the index record */
  WKkx9Vx9((qHh5JW*)&R9Yq4FcE.mrgekw0xj[R9Yq4FcE.AS0ycVs-gLHZQ8QCaz], x12bJ, &HB_T1jBCLdNzN);
  *XQI8eroRS = HB_T1jBCLdNzN.r43Pj.Pyy0l6xD;
  fU3PFeqj(&R9Yq4FcE);
  return odQX7vL;

  /* Jump here if database corruption is detected after m has been
  ** allocated.  Free the m object and return SQLITE_CORRUPT. */
ZAumR:
  gwlDS2AhlE3Xe( R9Yq4FcE.N3A21Ra4MY24m!=0 );
  fU3PFeqj(&R9Yq4FcE);
  return mVXrATk9;
}

/*
** Compare the key of the index entry that cursor pC is pointing to against
** the key string in pUnpacked.  Write into *pRes a number
** that is negative, zero, or positive if pC is less than, equal to,
** or greater than pUnpacked.  Return SQLITE_OK on success.
**
** pUnpacked is either created without a rowid or is truncated so that it
** omits the rowid at the end.  The rowid at the end of the index entry
** is ignored as well.  Hence, this routine only compares the prefixes
** of the keys prior to the final rowid, not the entire key.
*/
int YMN01a528MC(
  MEeQFpE4DzbZ *pLMJg2Xd,                     /* Database connection */
  Jmdb *SEIR9fLw_9,                  /* The cursor to compare against */
  Byn9mdCAjUkY9 *VXTd64MGhz7,       /* Unpacked version of key */
  int *E6VmXbBADn7                         /* Write the comparison result here */
){
  XBJDNN3j HWcgIng = 0;
  int YPgcEHzPuCIF;
  f5Sqror *FlTA8c6;
  oi4q2s5KcMX9Y R9Yq4FcE;

  f5IeCeK0e1W( SEIR9fLw_9->lhtEl9aC9MU==lqUt );
  FlTA8c6 = SEIR9fLw_9->b75S0uIj_5z.qtSltNrcEx;
  f5IeCeK0e1W( E1ys(FlTA8c6) );
  HWcgIng = P42CAIAm(FlTA8c6);
  /* nCellKey will always be between 0 and 0xffffffff because of the way
  ** that btreeParseCellPtr() and sqlite3GetVarint32() are implemented */
  if( HWcgIng<=0 || HWcgIng>0x7fffffff ){
    *E6VmXbBADn7 = 0;
    return mVXrATk9;
  }
  fTNaHo(&R9Yq4FcE, pLMJg2Xd, 0);
  YPgcEHzPuCIF = yIpp(FlTA8c6, (JamYDTpy)HWcgIng, &R9Yq4FcE);
  if( YPgcEHzPuCIF ){
    return YPgcEHzPuCIF;
  }
  *E6VmXbBADn7 = zX9Vhd(R9Yq4FcE.AS0ycVs, R9Yq4FcE.mrgekw0xj, VXTd64MGhz7, 0);
  fU3PFeqj(&R9Yq4FcE);
  return odQX7vL;
}

/*
** This routine sets the value to be returned by subsequent calls to
** sqlite3_changes() on the database handle 'db'.
*/
void BbHtoz(MEeQFpE4DzbZ *pLMJg2Xd, XBJDNN3j SnFm){
  f5IeCeK0e1W( FmX9So3cuLy(pLMJg2Xd->XXRvk3u4f6u) );
  pLMJg2Xd->SnFm = SnFm;
  pLMJg2Xd->rxg_fv += SnFm;
}

/*
** Set a flag in the vdbe to update the change counter when it is finalised
** or reset.
*/
void iX9CXu(Y4zzrBxD4OXTO *HB_T1jBCLdNzN){
  HB_T1jBCLdNzN->X4Sux4es2f = 1;
}

/*
** Mark every prepared statement associated with a database connection
** as expired.
**
** An expired statement means that recompilation of the statement is
** recommend.  Statements expire when things happen that make their
** programs obsolete.  Removing user-defined functions or collating
** sequences, or changing an authorization function are the types of
** things that make prepared statements obsolete.
**
** If iCode is 1, then expiration is advisory.  The statement should
** be reprepared before being restarted, but if it is already running
** it is allowed to run to completion.
**
** Internally, this function just sets the Vdbe.expired flag on all
** prepared statements.  The flag is set to 1 for an immediate expiration
** and set to 2 for an advisory expiration.
*/
void Gh6Gl_1GWJT(MEeQFpE4DzbZ *pLMJg2Xd, int HG6OOsP){
  Y4zzrBxD4OXTO *RWdNEx2WUIO8x;
  for(RWdNEx2WUIO8x = pLMJg2Xd->FDcUAbRU; RWdNEx2WUIO8x; RWdNEx2WUIO8x=RWdNEx2WUIO8x->KELn){
    RWdNEx2WUIO8x->VYYUN2ZWE6 = HG6OOsP+1;
  }
}

/*
** Return the database associated with the Vdbe.
*/
MEeQFpE4DzbZ *sA2ZhL(Y4zzrBxD4OXTO *HB_T1jBCLdNzN){
  return HB_T1jBCLdNzN->pLMJg2Xd;
}

/*
** Return the SQLITE_PREPARE flags for a Vdbe.
*/
qHh5JW MqwNsjcje5wpV(Y4zzrBxD4OXTO *HB_T1jBCLdNzN){
  return HB_T1jBCLdNzN->AUS9xq8fh;
}

/*
** Return a pointer to an sqlite3_value structure containing the value bound
** parameter iVar of VM v. Except, if the value is an SQL NULL, return
** 0 instead. Unless it is NULL, apply affinity aff (one of the SQLITE_AFF_*
** constants) to the value before returning it.
**
** The returned value must be freed by the caller using sqlite3ValueFree().
*/
EPdZvOoD0Wseb *PMdo0sVCGR(Y4zzrBxD4OXTO *HB_T1jBCLdNzN, int Fah1, qHh5JW KosPq3){
  f5IeCeK0e1W( Fah1>0 );
  if( HB_T1jBCLdNzN ){
    oi4q2s5KcMX9Y *ZAHT = &HB_T1jBCLdNzN->dHLFi0U0rI5oH[Fah1-1];
    f5IeCeK0e1W( (HB_T1jBCLdNzN->pLMJg2Xd->MRNoo5HiPBk7 & qqoOB)==0 
         || (HB_T1jBCLdNzN->pLMJg2Xd->UQwLL7zq7p & RY2dcyU9)!=0 );
    if( 0==(ZAHT->MRNoo5HiPBk7 & NIJTPrY3UI) ){
      EPdZvOoD0Wseb *FC4wG28Zic072 = dOh1_CQF9ZJWo(HB_T1jBCLdNzN->pLMJg2Xd);
      if( FC4wG28Zic072 ){
        KvpDdpHYay4L((oi4q2s5KcMX9Y *)FC4wG28Zic072, ZAHT);
        wEL3N6v(FC4wG28Zic072, KosPq3, XaWPmn7sUsHo4);
      }
      return FC4wG28Zic072;
    }
  }
  return 0;
}

/*
** Configure SQL variable iVar so that binding a new value to it signals
** to sqlite3_reoptimize() that re-preparing the statement may result
** in a better query plan.
*/
void C21MX6Lf6s(Y4zzrBxD4OXTO *HB_T1jBCLdNzN, int Fah1){
  f5IeCeK0e1W( Fah1>0 );
  f5IeCeK0e1W( (HB_T1jBCLdNzN->pLMJg2Xd->MRNoo5HiPBk7 & qqoOB)==0 
       || (HB_T1jBCLdNzN->pLMJg2Xd->UQwLL7zq7p & RY2dcyU9)!=0 );
  if( Fah1>=32 ){
    HB_T1jBCLdNzN->jhBEOz |= 0x80000000;
  }else{
    HB_T1jBCLdNzN->jhBEOz |= ((JamYDTpy)1 << (Fah1-1));
  }
}

/*
** Cause a function to throw an error if it was call from OP_PureFunc
** rather than OP_Function.
**
** OP_PureFunc means that the function must be deterministic, and should
** throw an error if it is given inputs that would make it non-deterministic.
** This routine is invoked by date/time functions that use non-deterministic
** features such as 'now'.
*/
int gL8Yr4swG6bm(DWQQ4Hi8 *KMDC3A_94J){
  const kqPOQZYA16d *BYPQ;
#ifdef K5H8my
  if( KMDC3A_94J->FDcUAbRU==0 ) return 1;
#endif
  BYPQ = KMDC3A_94J->FDcUAbRU->V7Y0VHDmd1Xf + KMDC3A_94J->Fz1Fyirahk;
  if( BYPQ->KMcyPZbh==s9LjXi53Xo ){
    const char *dStb179mEC;
    char *MTaRmd7WLo;
    if( BYPQ->I4yL & QjdEZssQ ){
      dStb179mEC = "a CHECK constraint";
    }else if( BYPQ->I4yL & bF9Lv ){
      dStb179mEC = "a generated column";
    }else{
      dStb179mEC = "an index";
    }
    MTaRmd7WLo = G0mMoA("non-deterministic use of %s() in %s",
                           KMDC3A_94J->pOpnI3oMVnGn->wxojaeqHwik, dStb179mEC);
    e_5fWI1KvFFvH(KMDC3A_94J, MTaRmd7WLo, -1);
    CMhAT(MTaRmd7WLo);
    return 0;
  }
  return 1;
}

#if pZX7GD4OTcuV(DWSSZmoaM) && pZX7GD4OTcuV(iteB65TL5L)
/*
** This Walker callback is used to help verify that calls to
** sqlite3BtreeCursorHint() with opcode BTREE_HINT_RANGE have
** byte-code register values correctly initialized.
*/
int mqIJOLl(n3jMhcbQnX *cTVKTb4OAAJcK, n29LzVguZ6CV *fRIR8Z){
  if( fRIR8Z->odStgZ==qizx_KrVFuFCa ){
    f5IeCeK0e1W( (cTVKTb4OAAJcK->r43Pj.CSO_5[fRIR8Z->x10NhVu].MRNoo5HiPBk7 & eNZ5apG)==0 );
  }
  return Kdd2sgxnD8;
}
#endif /* SQLITE_ENABLE_CURSOR_HINTS && SQLITE_DEBUG */

#ifndef uRsBKByRR
/*
** Transfer error message text from an sqlite3_vtab.zErrMsg (text stored
** in memory obtained from sqlite3_malloc) into a Vdbe.zErrMsg (text stored
** in memory obtained from sqlite3DbMalloc).
*/
void UXL19i(Y4zzrBxD4OXTO *RWdNEx2WUIO8x, QMJ6_wa *X4AIzAFQeHOW){
  if( X4AIzAFQeHOW->C9BnRQApGBXmM ){
    MEeQFpE4DzbZ *pLMJg2Xd = RWdNEx2WUIO8x->pLMJg2Xd;
    UXHgfYQ(pLMJg2Xd, RWdNEx2WUIO8x->C9BnRQApGBXmM);
    RWdNEx2WUIO8x->C9BnRQApGBXmM = FmfCMc4yu8(pLMJg2Xd, X4AIzAFQeHOW->C9BnRQApGBXmM);
    CMhAT(X4AIzAFQeHOW->C9BnRQApGBXmM);
    X4AIzAFQeHOW->C9BnRQApGBXmM = 0;
  }
}
#endif /* SQLITE_OMIT_VIRTUALTABLE */

#ifdef lg4arP7GQdU

/*
** If the second argument is not NULL, release any allocations associated
** with the memory cells in the p->aMem[] array. Also free the UnpackedRecord
** structure itself, using sqlite3DbFree().
**
** This function is used to free UnpackedRecord structures allocated by
** the vdbeUnpackRecord() function found in vdbeapi.c.
*/
static void OWLz5Hs(MEeQFpE4DzbZ *pLMJg2Xd, int FRi83T, Byn9mdCAjUkY9 *RWdNEx2WUIO8x){
  f5IeCeK0e1W( pLMJg2Xd!=0 );
  if( RWdNEx2WUIO8x ){
    int Pyy0l6xD;
    for(Pyy0l6xD=0; Pyy0l6xD<FRi83T; Pyy0l6xD++){
      oi4q2s5KcMX9Y *ZAHT = &RWdNEx2WUIO8x->CSO_5[Pyy0l6xD];
      if( ZAHT->DH15 ) fU3PFeqj(ZAHT);
    }
    CTQ2V30yU(pLMJg2Xd, RWdNEx2WUIO8x);
  }
}
#endif /* SQLITE_ENABLE_PREUPDATE_HOOK */

#ifdef lg4arP7GQdU
/*
** Invoke the pre-update hook. If this is an UPDATE or DELETE pre-update call,
** then cursor passed as the second argument should point to the row about
** to be update or deleted. If the application calls sqlite3_preupdate_old(),
** the required value will be read from the row the cursor points to.
*/
void hEj2tDCzz1(
  Y4zzrBxD4OXTO *HB_T1jBCLdNzN,                        /* Vdbe pre-update hook is invoked by */
  Jmdb *OvLn,               /* Cursor to grab old.* values from */
  int odStgZ,                         /* SQLITE_INSERT, UPDATE or DELETE */
  const char *WVcszg5,                /* Database name */
  rMWp94Q *rLBZ1vZbk,                    /* Modified table */
  XBJDNN3j ijzdmym,                      /* Initial key value */
  int tcbLDpjkih9,                       /* Register for new.* record */
  int NuGo
){
  MEeQFpE4DzbZ *pLMJg2Xd = HB_T1jBCLdNzN->pLMJg2Xd;
  XBJDNN3j fbI2wSDI;
  M0g8p3 amFxu;
  const char *FVom9uU8A6D = rLBZ1vZbk->wxojaeqHwik;
  static const qHh5JW N5ZsRG84JY5G = 0;
#ifdef iteB65TL5L
  int jHpovE7wKMg;
  if( rLBZ1vZbk->VzFw & V02kuh ){
    jHpovE7wKMg = zn8Y31mU7T(rLBZ1vZbk)->HBqtjEUYvM7;
  }else if( rLBZ1vZbk->VzFw & H0KA3H ){
    jHpovE7wKMg = rLBZ1vZbk->t8boruHg7Sk0;
  }else{
    jHpovE7wKMg = rLBZ1vZbk->qlgg0ucg;
  }
#endif

  f5IeCeK0e1W( pLMJg2Xd->ps2nc3k58fS==0 );
  gDRc26rrZnG_(&amFxu, 0, sizeof(M0g8p3));
  if( QLgrUszO(rLBZ1vZbk)==0 ){
    ijzdmym = fbI2wSDI = 0;
    amFxu.vGuZ8Osd8B3S = zn8Y31mU7T(rLBZ1vZbk);
  }else{
    if( odStgZ==WHN9Wvr8zr ){
      fbI2wSDI = HB_T1jBCLdNzN->CSO_5[tcbLDpjkih9].r43Pj.Pyy0l6xD;
    }else{
      fbI2wSDI = ijzdmym;
    }
  }

  f5IeCeK0e1W( OvLn!=0 );
  f5IeCeK0e1W( OvLn->lhtEl9aC9MU==lqUt );
  f5IeCeK0e1W( OvLn->FRi83T==jHpovE7wKMg
       || (OvLn->FRi83T==jHpovE7wKMg+1 && odStgZ==UPqpNS4Jxed && tcbLDpjkih9==-1)
  );

  amFxu.HB_T1jBCLdNzN = HB_T1jBCLdNzN;
  amFxu.OvLn = OvLn;
  amFxu.odStgZ = odStgZ;
  amFxu.MzAOj = tcbLDpjkih9;
  amFxu.UKL1.pLMJg2Xd = pLMJg2Xd;
  amFxu.UKL1.Tc4R1 = vf18t4l8c6q(pLMJg2Xd);
  amFxu.UKL1.tr0jn = rLBZ1vZbk->qlgg0ucg;
  amFxu.UKL1.iIxU = (qHh5JW*)&N5ZsRG84JY5G;
  amFxu.ijzdmym = ijzdmym;
  amFxu.fbI2wSDI = fbI2wSDI;
  amFxu.rLBZ1vZbk = rLBZ1vZbk;
  amFxu.NuGo = NuGo;

  pLMJg2Xd->ps2nc3k58fS = &amFxu;
  pLMJg2Xd->bY44dnip(pLMJg2Xd->j1uLT65W, pLMJg2Xd, odStgZ, WVcszg5, FVom9uU8A6D, ijzdmym, fbI2wSDI);
  pLMJg2Xd->ps2nc3k58fS = 0;
  UXHgfYQ(pLMJg2Xd, amFxu.C2gltdMfs);
  OWLz5Hs(pLMJg2Xd, amFxu.UKL1.tr0jn+1, amFxu.VXTd64MGhz7);
  OWLz5Hs(pLMJg2Xd, amFxu.UKL1.tr0jn+1, amFxu.LhlQenMs1g);
  if( amFxu.epSqE ){
    int Pyy0l6xD;
    for(Pyy0l6xD=0; Pyy0l6xD<OvLn->FRi83T; Pyy0l6xD++){
      bFVk(&amFxu.epSqE[Pyy0l6xD]);
    }
    CTQ2V30yU(pLMJg2Xd, amFxu.epSqE);
  }
}
#endif /* SQLITE_ENABLE_PREUPDATE_HOOK */
