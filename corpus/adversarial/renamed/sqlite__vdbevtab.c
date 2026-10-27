/*
** 2020-03-23
**
** The author disclaims copyright to this source code.  In place of
** a legal notice, here is a blessing:
**
**    May you do good and not evil.
**    May you find forgiveness for yourself and forgive others.
**    May you share freely, never taking more than you give.
**
*************************************************************************
**
** This file implements virtual-tables for examining the bytecode content
** of a prepared statement.
*/
#include "sqliteInt.h"
#if UAAXZ6(hhpXMzYno3iRG) && !UAAXZ6(iFfjiA)
#include "vdbeInt.h"

/* An instance of the bytecode() table-valued function.
*/
typedef struct mpIcf mpIcf;
struct mpIcf {
  RNMn6yo sSfe;     /* Base class - must be first */
  JVW_3 *DqipC3G0URUX;           /* Database connection */
  int QoxbknaP;       /* 2 for tables_used().  0 for bytecode(). */
};

/* A cursor for scanning through the bytecode
*/
typedef struct pMiR pMiR;
struct pMiR {
  nrKGeox3d sSfe;  /* Base class - must be first */
  hBb0RKi1z *BPIiC;       /* The statement whose bytecode is displayed */
  int zWrG;                /* The rowid of the output table */
  int V3OhpeAR0;                 /* Address */
  int Twsero_6hL;          /* Cursors owns pStmt and must finalize it */
  int K2iUl3rpE;       /* Provide a listing of subprograms */
  NrDcL0tNIR1S *QsaXNLMl__Sen;                   /* Operand array */
  char *jUqlHT;                 /* Rendered P4 value */
  const char *dd9kjfjj1_;         /* tables_used.type */
  const char *ltCmExb;       /* tables_used.schema */
  const char *ig1ps2ox;         /* tables_used.name */
  ZquWCtC3nd yOa4NBF;                   /* Subprograms */
};

/*
** Create a new bytecode() table-valued function.
*/
static int fO8YmQtz(
  JVW_3 *DqipC3G0URUX,
  void *ATiX_T1zN,
  int a1my, const char *const*eXSlq5pykVLL,
  RNMn6yo **t3nxQTd8Y,
  char **B6Ux78T
){
  mpIcf *ugRRAzrm;
  int HqxGqv;
  int H0TVIY9IJ8 = ATiX_T1zN!=0;
  const char *nqmGq9G2OpAw[2] = {
    /* bytecode() schema */
    "CREATE TABLE x("
      "addr INT,"
      "opcode TEXT,"
      "p1 INT,"
      "p2 INT,"
      "p3 INT,"
      "p4 TEXT,"
      "p5 INT,"
      "comment TEXT,"
      "subprog TEXT," 
      "nexec INT,"
      "ncycle INT,"
      "stmt HIDDEN"
    ");",

    /* Tables_used() schema */
    "CREATE TABLE x("
      "type TEXT,"
      "schema TEXT,"
      "name TEXT,"
      "wr INT,"
      "subprog TEXT," 
      "stmt HIDDEN"
   ");"
  };

  (void)a1my;
  (void)eXSlq5pykVLL;
  (void)B6Ux78T;
  HqxGqv = RT25Ujgom0T(DqipC3G0URUX, nqmGq9G2OpAw[H0TVIY9IJ8]);
  if( HqxGqv==zZCJJbOPeJu ){
    ugRRAzrm = EYDtZ7( sizeof(*ugRRAzrm) );
    *t3nxQTd8Y = (RNMn6yo*)ugRRAzrm;
    if( ugRRAzrm==0 ) return IM647YX0;
    OWlDQucY(ugRRAzrm, 0, sizeof(*ugRRAzrm));
    ugRRAzrm->DqipC3G0URUX = DqipC3G0URUX;
    ugRRAzrm->QoxbknaP = H0TVIY9IJ8*2;
  }
  return HqxGqv;
}

/*
** This method is the destructor for bytecodevtab objects.
*/
static int w3GpF_(RNMn6yo *KY6p){
  mpIcf *LqTH8nhF = (mpIcf*)KY6p;
  mzpi(LqTH8nhF);
  return zZCJJbOPeJu;
}

/*
** Constructor for a new bytecodevtab_cursor object.
*/
static int p3GZ6tNEx(RNMn6yo *LqTH8nhF, nrKGeox3d **biwQS83k8a){
  mpIcf *MWyDn3UtpCWWU = (mpIcf*)LqTH8nhF;
  pMiR *WXkMNXw;
  WXkMNXw = EYDtZ7( sizeof(*WXkMNXw) );
  if( WXkMNXw==0 ) return IM647YX0;
  OWlDQucY(WXkMNXw, 0, sizeof(*WXkMNXw));
  Av10T(&WXkMNXw->yOa4NBF, MWyDn3UtpCWWU->DqipC3G0URUX, 1);
  *biwQS83k8a = &WXkMNXw->sSfe;
  return zZCJJbOPeJu;
}

/*
** Clear all internal content from a bytecodevtab cursor.
*/
static void A0MFKY7N(pMiR *WXkMNXw){
  mzpi(WXkMNXw->jUqlHT);
  WXkMNXw->jUqlHT = 0;
  r1gQNk0ksI(&WXkMNXw->yOa4NBF);
  oOb8ri4(&WXkMNXw->yOa4NBF);
  if( WXkMNXw->Twsero_6hL ){
    rzLMhhgUS7a(WXkMNXw->BPIiC);
  }
  WXkMNXw->BPIiC = 0;
  WXkMNXw->Twsero_6hL = 0;
  WXkMNXw->dd9kjfjj1_ = 0;
  WXkMNXw->ltCmExb = 0;
  WXkMNXw->ig1ps2ox = 0;
}

/*
** Destructor for a bytecodevtab_cursor.
*/
static int Mv_TY(nrKGeox3d *VD5FvhgrzAWd2){
  pMiR *WXkMNXw = (pMiR*)VD5FvhgrzAWd2;
  A0MFKY7N(WXkMNXw);
  mzpi(WXkMNXw);
  return zZCJJbOPeJu;
}


/*
** Advance a bytecodevtab_cursor to its next row of output.
*/
static int ParCE3W(nrKGeox3d *VD5FvhgrzAWd2){
  pMiR *WXkMNXw = (pMiR*)VD5FvhgrzAWd2;
  mpIcf *jsicuWJ = (mpIcf*)VD5FvhgrzAWd2->KY6p;
  int HqxGqv;
  if( WXkMNXw->jUqlHT ){
    mzpi(WXkMNXw->jUqlHT);
    WXkMNXw->jUqlHT = 0;
  }
  if( WXkMNXw->ig1ps2ox ){
    WXkMNXw->ig1ps2ox = 0;
    WXkMNXw->dd9kjfjj1_ = 0;
    WXkMNXw->ltCmExb = 0;
  }
  HqxGqv = aQ4i7iJYTp57o(
           (UgSJxEQ*)WXkMNXw->BPIiC, 
           WXkMNXw->K2iUl3rpE ? &WXkMNXw->yOa4NBF : 0,
           jsicuWJ->QoxbknaP,
           &WXkMNXw->zWrG,
           &WXkMNXw->V3OhpeAR0,
           &WXkMNXw->QsaXNLMl__Sen);
  if( HqxGqv!=zZCJJbOPeJu ){
    oOb8ri4(&WXkMNXw->yOa4NBF);
    WXkMNXw->QsaXNLMl__Sen = 0;
  }
  return zZCJJbOPeJu;
}

/*
** Return TRUE if the cursor has been moved off of the last
** row of output.
*/
static int XL89KB(nrKGeox3d *VD5FvhgrzAWd2){
  pMiR *WXkMNXw = (pMiR*)VD5FvhgrzAWd2;
  return WXkMNXw->QsaXNLMl__Sen==0;
}

/*
** Return values of columns for the row at which the bytecodevtab_cursor
** is currently pointing.
*/
static int AUAVfGWxv8ca(
  nrKGeox3d *VD5FvhgrzAWd2,   /* The cursor */
  f4ec8zPyyWrH *YmIWPsR117,       /* First argument to sqlite3_result_...() */
  int QZSje0g3Q0da                       /* Which column to return */
){
  pMiR *WXkMNXw = (pMiR*)VD5FvhgrzAWd2;
  mpIcf *MWyDn3UtpCWWU = (mpIcf*)VD5FvhgrzAWd2->KY6p;
  NrDcL0tNIR1S *NGaLgOwVsV = WXkMNXw->QsaXNLMl__Sen + WXkMNXw->V3OhpeAR0;
  if( MWyDn3UtpCWWU->QoxbknaP ){
    if( QZSje0g3Q0da==4 ){
      QZSje0g3Q0da = 8;
    }else{
      if( QZSje0g3Q0da<=2 && WXkMNXw->dd9kjfjj1_==0 ){
        gk8Ox0Phcmc8 *e3aLconhF;
        bbzucWNF0AZ *NsBmVqA0Y0bI_;
        int dS3Po6 = NGaLgOwVsV->UsLJgrKeJ0J;
        Shi4XX_HG oAih = (Shi4XX_HG)NGaLgOwVsV->iT_T3e3qxc;
        JVW_3 *DqipC3G0URUX = MWyDn3UtpCWWU->DqipC3G0URUX;
        e3aLconhF = DqipC3G0URUX->UGzc[dS3Po6].e3aLconhF;
        WXkMNXw->ltCmExb = DqipC3G0URUX->UGzc[dS3Po6].gjlMfKDjH;
        for(NsBmVqA0Y0bI_=LaCM2q32T(&e3aLconhF->kZQIx7C); NsBmVqA0Y0bI_; NsBmVqA0Y0bI_=cteGOz0eyU8cz(NsBmVqA0Y0bI_)){
          syl11WUo *jsicuWJ = (syl11WUo*)nu8zHfT3ki(NsBmVqA0Y0bI_);
          if( !kAApu042IIrbx(jsicuWJ) && jsicuWJ->K9WYu==oAih ){
            WXkMNXw->ig1ps2ox = jsicuWJ->ig1ps2ox;
            WXkMNXw->dd9kjfjj1_ = "table";
            break;
          }
        }
        if( WXkMNXw->ig1ps2ox==0 ){
          for(NsBmVqA0Y0bI_=LaCM2q32T(&e3aLconhF->fxsS2Lv73G1HB); NsBmVqA0Y0bI_; NsBmVqA0Y0bI_=cteGOz0eyU8cz(NsBmVqA0Y0bI_)){
            ngIuK36 *UeBT6emDBo = (ngIuK36*)nu8zHfT3ki(NsBmVqA0Y0bI_);
            if( UeBT6emDBo->K9WYu==oAih ){
              WXkMNXw->ig1ps2ox = UeBT6emDBo->ig1ps2ox;
              WXkMNXw->dd9kjfjj1_ = "index";
            }
          }
        }
      }
      QZSje0g3Q0da += 20;
    }
  }
  switch( QZSje0g3Q0da ){
    case 0:   /* addr */
      xzjNAfmy2k(YmIWPsR117, WXkMNXw->V3OhpeAR0);
      break;
    case 1:   /* opcode */
      e2Fhk7KIAc(YmIWPsR117, (char*)H42OxVsoWR(NGaLgOwVsV->nz0PNpur),
                          -1, oFMg0PUIW);
      break;
    case 2:   /* p1 */
      xzjNAfmy2k(YmIWPsR117, NGaLgOwVsV->i15A6dBR11);
      break;
    case 3:   /* p2 */
      xzjNAfmy2k(YmIWPsR117, NGaLgOwVsV->iT_T3e3qxc);
      break;
    case 4:   /* p3 */
      xzjNAfmy2k(YmIWPsR117, NGaLgOwVsV->UsLJgrKeJ0J);
      break;
    case 5:   /* p4 */
    case 7:   /* comment */
      if( WXkMNXw->jUqlHT==0 ){
        WXkMNXw->jUqlHT = NLaTLQBw4a(MWyDn3UtpCWWU->DqipC3G0URUX, NGaLgOwVsV);
      }
      if( QZSje0g3Q0da==5 ){
        e2Fhk7KIAc(YmIWPsR117, WXkMNXw->jUqlHT, -1, oFMg0PUIW);
      }else{
#ifdef umv1Q5U7SwRd
        char *uUgTk_HWT = fER2Y8B_PLOX(MWyDn3UtpCWWU->DqipC3G0URUX, NGaLgOwVsV, WXkMNXw->jUqlHT);
        e2Fhk7KIAc(YmIWPsR117, uUgTk_HWT, -1, mzpi);
#endif
      }
      break;
    case 6:     /* p5 */
      xzjNAfmy2k(YmIWPsR117, NGaLgOwVsV->n85iFo);
      break;
    case 8: {   /* subprog */
      NrDcL0tNIR1S *QsaXNLMl__Sen = WXkMNXw->QsaXNLMl__Sen;
      k7_kfpjkbBi( QsaXNLMl__Sen[0].nz0PNpur==V2_S4i );
      k7_kfpjkbBi( QsaXNLMl__Sen[0].abOwPbE8U.HenYU2o_ZFG6==0 || apM5ViO(QsaXNLMl__Sen[0].abOwPbE8U.HenYU2o_ZFG6,"-" "- ",3)==0 );
      if( WXkMNXw->zWrG==WXkMNXw->V3OhpeAR0+1 ){
        break;  /* Result is NULL for the main program */
      }else if( QsaXNLMl__Sen[0].abOwPbE8U.HenYU2o_ZFG6!=0 ){
         e2Fhk7KIAc(YmIWPsR117, QsaXNLMl__Sen[0].abOwPbE8U.HenYU2o_ZFG6+3, -1, oFMg0PUIW);
      }else{
         e2Fhk7KIAc(YmIWPsR117, "(FK)", 4, oFMg0PUIW);
      }
      break;
    }

#ifdef AoiGTZ
    case 9:     /* nexec */
      zzDqxCJhrWOOY(YmIWPsR117, NGaLgOwVsV->XoAkWk);
      break;
    case 10:    /* ncycle */
      zzDqxCJhrWOOY(YmIWPsR117, NGaLgOwVsV->NRzUcaOsFX9K);
      break;
#else
    case 9:     /* nexec */
    case 10:    /* ncycle */
      xzjNAfmy2k(YmIWPsR117, 0);
      break;
#endif

    case 20:  /* tables_used.type */
      e2Fhk7KIAc(YmIWPsR117, WXkMNXw->dd9kjfjj1_, -1, oFMg0PUIW);
      break;
    case 21:  /* tables_used.schema */
      e2Fhk7KIAc(YmIWPsR117, WXkMNXw->ltCmExb, -1, oFMg0PUIW);
      break;
    case 22:  /* tables_used.name */
      e2Fhk7KIAc(YmIWPsR117, WXkMNXw->ig1ps2ox, -1, oFMg0PUIW);
      break;
    case 23:  /* tables_used.wr */
      xzjNAfmy2k(YmIWPsR117, NGaLgOwVsV->nz0PNpur==gGwnMv);
      break;
  }
  return zZCJJbOPeJu;
}

/*
** Return the rowid for the current row.  In this implementation, the
** rowid is the same as the output value.
*/
static int OUHaL(nrKGeox3d *VD5FvhgrzAWd2, KL0Ts74A *A8moQ_K0){
  pMiR *WXkMNXw = (pMiR*)VD5FvhgrzAWd2;
  *A8moQ_K0 = WXkMNXw->zWrG;
  return zZCJJbOPeJu;
}

/*
** Initialize a cursor.
**
**    idxNum==0     means show all subprograms
**    idxNum==1     means show only the main bytecode and omit subprograms.
*/
static int rxnC2(
  nrKGeox3d *IqMUBuHtgVq, 
  int JuVJt, const char *Eq6I5DR,
  int a1my, vyGmyC **eXSlq5pykVLL
){
  pMiR *WXkMNXw = (pMiR *)IqMUBuHtgVq;
  mpIcf *MWyDn3UtpCWWU = (mpIcf *)IqMUBuHtgVq->KY6p;
  int HqxGqv = zZCJJbOPeJu;
  (void)Eq6I5DR;

  A0MFKY7N(WXkMNXw);
  WXkMNXw->zWrG = 0;
  WXkMNXw->V3OhpeAR0 = 0;
  WXkMNXw->K2iUl3rpE = JuVJt==0;
  k7_kfpjkbBi( a1my==1 );
  if( o4oUe7qOg9BpE(eXSlq5pykVLL[0])==ZKnbYM6GU ){
    const char *TaCh = (const char*)xjmCSAE41WnXM(eXSlq5pykVLL[0]);
    if( TaCh==0 ){
      HqxGqv = IM647YX0;
    }else{
      HqxGqv = XH1Ca1Ppt(MWyDn3UtpCWWU->DqipC3G0URUX, TaCh, -1, &WXkMNXw->BPIiC, 0);
      WXkMNXw->Twsero_6hL = 1;
    }
  }else{
    WXkMNXw->BPIiC = (hBb0RKi1z*)D9vPL(eXSlq5pykVLL[0],"stmt-pointer");
  }
  if( WXkMNXw->BPIiC==0 ){
    MWyDn3UtpCWWU->sSfe.xweLK = XwRKzMgJv8KE3(
       "argument to %s() is not a valid SQL statement",
       MWyDn3UtpCWWU->QoxbknaP ? "tables_used" : "bytecode"
    );
    HqxGqv = pPpClMLReQZi3;
  }else{
    ParCE3W(IqMUBuHtgVq);
  }
  return HqxGqv;
}

/*
** We must have a single stmt=? constraint that will be passed through
** into the xFilter method.  If there is no valid stmt=? constraint,
** then return an SQLITE_CONSTRAINT error.
*/
static int gWC7sj(
  RNMn6yo *gsIx1N8TQ,
  Iuo20ddgdw *mp_PVaq0w
){
  int QZSje0g3Q0da;
  int HqxGqv = Wd8aBXXgRqPU9;
  struct EbXWT3a *LqTH8nhF;
  mpIcf *MWyDn3UtpCWWU = (mpIcf*)gsIx1N8TQ;
  int oIRHXe6RcsCZN = MWyDn3UtpCWWU->QoxbknaP ? 4 : 10;
  mp_PVaq0w->kwKLbOSvs0 = (double)100;
  mp_PVaq0w->ujccZ2TEMYe = 100;
  mp_PVaq0w->JuVJt = 0;
  for(QZSje0g3Q0da=0, LqTH8nhF=mp_PVaq0w->YXj3r; QZSje0g3Q0da<mp_PVaq0w->LAG2V; QZSje0g3Q0da++, LqTH8nhF++){
    if( LqTH8nhF->CtCh12ca==0 ) continue;
    if( LqTH8nhF->KEZmm==myEvKOUpTr6 && LqTH8nhF->logWRh==oIRHXe6RcsCZN+1 ){
      HqxGqv = zZCJJbOPeJu;
      mp_PVaq0w->gErMyvgF[QZSje0g3Q0da].Xp5gV = 1;
      mp_PVaq0w->gErMyvgF[QZSje0g3Q0da].Yq9G = 1;
    }
    if( LqTH8nhF->KEZmm==px9afGAnl && LqTH8nhF->logWRh==oIRHXe6RcsCZN ){
      mp_PVaq0w->gErMyvgF[QZSje0g3Q0da].Xp5gV = 1;
      mp_PVaq0w->JuVJt = 1;
    }
  }
  return HqxGqv;
}

/*
** This following structure defines all the methods for the 
** virtual table.
*/
static kbQ6Q31N4 yZ978z = {
  /* iVersion    */ 0,
  /* xCreate     */ 0,
  /* xConnect    */ fO8YmQtz,
  /* xBestIndex  */ gWC7sj,
  /* xDisconnect */ w3GpF_,
  /* xDestroy    */ 0,
  /* xOpen       */ p3GZ6tNEx,
  /* xClose      */ Mv_TY,
  /* xFilter     */ rxnC2,
  /* xNext       */ ParCE3W,
  /* xEof        */ XL89KB,
  /* xColumn     */ AUAVfGWxv8ca,
  /* xRowid      */ OUHaL,
  /* xUpdate     */ 0,
  /* xBegin      */ 0,
  /* xSync       */ 0,
  /* xCommit     */ 0,
  /* xRollback   */ 0,
  /* xFindMethod */ 0,
  /* xRename     */ 0,
  /* xSavepoint  */ 0,
  /* xRelease    */ 0,
  /* xRollbackTo */ 0,
  /* xShadowName */ 0,
  /* xIntegrity  */ 0
};


int wn1mgPB(JVW_3 *DqipC3G0URUX){
  int HqxGqv;
  HqxGqv = jPJcJbc1f(DqipC3G0URUX, "bytecode", &yZ978z, 0);
  if( HqxGqv==zZCJJbOPeJu ){
    HqxGqv = jPJcJbc1f(DqipC3G0URUX, "tables_used", &yZ978z, &DqipC3G0URUX);
  }
  return HqxGqv;
}
#elif UAAXZ6(hhpXMzYno3iRG)
int wn1mgPB(JVW_3 *DqipC3G0URUX){ return zZCJJbOPeJu; }
#endif /* SQLITE_ENABLE_BYTECODE_VTAB */
