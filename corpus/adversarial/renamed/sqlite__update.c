/*
** 2001 September 15
**
** The author disclaims copyright to this source code.  In place of
** a legal notice, here is a blessing:
**
**    May you do good and not evil.
**    May you find forgiveness for yourself and forgive others.
**    May you share freely, never taking more than you give.
**
*************************************************************************
** This file contains C code routines that are called by the parser
** to handle UPDATE statements.
*/
#include "sqliteInt.h"

#ifndef uwEiL
/* Forward declaration */
static void BUo4(
  bpe5rP2ReAl48 *er3GO2,       /* The parsing context */
  YXHw_ *JIKG0,       /* The virtual table to be modified */
  gd_2KBv1V *BvAx6uJKKYDb,         /* The virtual table */
  XNL0CTTc7o7h *nRzeBk,  /* The columns to change in the UPDATE statement */
  GA3mR5g0pzo *VjPg,    /* Expression used to recompute the rowid */
  int *vqlW_di7j1,          /* Mapping from columns of pTab to entries in pChanges */
  GA3mR5g0pzo *a87EzByroTtw,        /* WHERE clause of the UPDATE statement */
  int GMqbKgv00oub          /* ON CONFLICT strategy */
);
#endif /* SQLITE_OMIT_VIRTUALTABLE */

/*
** The most recently coded instruction was an OP_Column to retrieve the
** i-th column of table pTab. This routine sets the P4 parameter of the
** OP_Column to the default value, if any.
**
** The default value of a column is specified by a DEFAULT clause in the
** column definition. This was either supplied by the user when the table
** was created, or added later to the table definition by an ALTER TABLE
** command. If the latter, then the row-records in the table btree on disk
** may not contain a value for the column and the default value, taken
** from the P4 parameter of the OP_Column instruction, is returned instead.
** If the former, then all row-records are guaranteed to include a value
** for the column and the P4 value is not required.
**
** Column definitions created by an ALTER TABLE command may only have
** literal default values specified: a number, null or a string. (If a more
** complicated default expression value was provided, it is evaluated
** when the ALTER TABLE is executed and one of the literal values written
** into the sqlite_schema table.)
**
** Therefore, the P4 parameter is only required if the default value for
** the column is a literal number, string or null. The sqlite3ValueFromExpr()
** function is capable of transforming these types of expressions into
** sqlite3_value objects.
**
** If column as REAL affinity and the table is an ordinary b-tree table
** (not a virtual table) then the value might have been stored as an
** integer.  In that case, add an OP_RealAffinity opcode to make sure
** it has been converted into REAL.
*/
void zNkwF8(BCD5GL *Tqu4rVzcNe_L, gd_2KBv1V *BvAx6uJKKYDb, int pYhdBYyu, int DcXkK6IPn){
  xIy8x4 *m7Q3;
  lZlEaido1C( BvAx6uJKKYDb!=0 );
  lZlEaido1C( BvAx6uJKKYDb->cvxjc>pYhdBYyu );
  m7Q3 = &BvAx6uJKKYDb->PXCh1YPlYG8[pYhdBYyu];
  if( m7Q3->e2lILP ){
    GK7Q4Rq__82 *aih_iQhGeR = 0;
    ypp5c0ABe xXhkUF4w = eHCvFSfYO(XYYNxtb1l8Okf(Tqu4rVzcNe_L));
    lZlEaido1C( !x3uBYV5(BvAx6uJKKYDb) );
    eGmVewvU_m((Tqu4rVzcNe_L, "%s.%s", BvAx6uJKKYDb->ZUF5, m7Q3->tEmLCm507));
    lZlEaido1C( pYhdBYyu<BvAx6uJKKYDb->cvxjc );
    TJbaf5q(XYYNxtb1l8Okf(Tqu4rVzcNe_L),
                         upKZ6(BvAx6uJKKYDb,m7Q3), xXhkUF4w,
                         m7Q3->wBF2P, &aih_iQhGeR);
    if( aih_iQhGeR ){
      si7Xp9l(Tqu4rVzcNe_L, aih_iQhGeR, vGSNLT8o5ht);
    }
  }
#ifndef w7RvnPUReNx
  if( m7Q3->wBF2P==Dldhcs4054 && !KaHu7ow73cLw9(BvAx6uJKKYDb) ){
    iiGBdkW(Tqu4rVzcNe_L, I_j5TumOGiQaX, DcXkK6IPn);
  }
#endif
}

/*
** Check to see if column iCol of index pIdx references any of the
** columns defined by aXRef and chngRowid.  Return true if it does
** and false if not.  This is an optimization.  False-positives are a
** performance degradation, but false-negatives can result in a corrupt
** index and incorrect answers.
**
** aXRef[j] will be non-negative if column j of the original table is
** being updated.  chngRowid will be true if the rowid of the table is
** being updated.
*/
static int bYkmPTnJY(
  bpXPO *hzr1XWU65uMUQ,      /* The index to check */
  int UCCLvIYCno_,         /* Which column of the index to check */
  int *vqlW_di7j1,       /* aXRef[j]>=0 if column j is being updated */
  int z4x3Rs4CB     /* true if the rowid is being updated */
){
  XCV1 drHoQ = hzr1XWU65uMUQ->CgbDaAYw7NQKF[UCCLvIYCno_];
  lZlEaido1C( drHoQ!=BUyPbxYCn ); /* Cannot index rowid */
  if( drHoQ>=0 ){
    return vqlW_di7j1[drHoQ]>=0;
  }
  lZlEaido1C( drHoQ==zKikMu );
  lZlEaido1C( hzr1XWU65uMUQ->LD8frLv6W0!=0 );
  lZlEaido1C( hzr1XWU65uMUQ->LD8frLv6W0->cmay2IaHVGA9[UCCLvIYCno_].pNnYNaSqZGNO!=0 );
  return GFjYNxi7c(hzr1XWU65uMUQ->LD8frLv6W0->cmay2IaHVGA9[UCCLvIYCno_].pNnYNaSqZGNO,
                                            vqlW_di7j1,z4x3Rs4CB);
}

/*
** Check to see if index pIdx is a partial index whose conditional
** expression might change values due to an UPDATE.  Return true if
** the index is subject to change and false if the index is guaranteed
** to be unchanged.  This is an optimization.  False-positives are a
** performance degradation, but false-negatives can result in a corrupt
** index and incorrect answers.
**
** aXRef[j] will be non-negative if column j of the original table is
** being updated.  chngRowid will be true if the rowid of the table is
** being updated.
*/
static int xOrPm(
  bpXPO *hzr1XWU65uMUQ,      /* The index to check */
  int *vqlW_di7j1,       /* aXRef[j]>=0 if column j is being updated */
  int z4x3Rs4CB     /* true if the rowid is being updated */
){
  if( hzr1XWU65uMUQ->ibqyZRlhsZUC==0 ) return 0;
  return GFjYNxi7c(hzr1XWU65uMUQ->ibqyZRlhsZUC,
                                            vqlW_di7j1, z4x3Rs4CB);
}

/*
** Allocate and return a pointer to an expression of type TK_ROW with
** Expr.iColumn set to value (iCol+1). The resolver will modify the
** expression to be a TK_COLUMN reading column iCol of the first
** table in the source-list (pSrc->a[0]).
*/
static GA3mR5g0pzo *IhTTR6PC(bpe5rP2ReAl48 *er3GO2, int UCCLvIYCno_){
  GA3mR5g0pzo *wFt43vH8cP = cYSjIJiJ(er3GO2, fFjy9MVjDpheb, 0, 0);
  if( wFt43vH8cP ) wFt43vH8cP->w3mLvkIcI = UCCLvIYCno_+1;
  return wFt43vH8cP;
}

/*
** Assuming both the pLimit and pOrderBy parameters are NULL, this function
** generates VM code to run the query:
**
**   SELECT <other-columns>, pChanges FROM pTabList WHERE pWhere
**
** and write the results to the ephemeral table already opened as cursor
** iEph. None of pChanges, pTabList or pWhere are modified or consumed by
** this function, they must be deleted by the caller.
**
** Or, if pLimit and pOrderBy are not NULL, and pTab is not a view:
**
**   SELECT <other-columns>, pChanges FROM pTabList
**   WHERE pWhere
**   GROUP BY <other-columns>
**   ORDER BY pOrderBy LIMIT pLimit
**
** If pTab is a view, the GROUP BY clause is omitted.
**
** Exactly how results are written to table iEph, and exactly what
** the <other-columns> in the query above are is determined by the type
** of table pTabList->a[0].pTab.
**
** If the table is a WITHOUT ROWID table, then argument pPk must be its
** PRIMARY KEY. In this case <other-columns> are the primary key columns
** of the table, in order. The results of the query are written to ephemeral
** table iEph as index keys, using OP_IdxInsert.
**
** If the table is actually a view, then <other-columns> are all columns of
** the view. The results are written to the ephemeral table iEph as records
** with automatically assigned integer keys.
**
** If the table is a virtual or ordinary intkey table, then <other-columns>
** is its rowid. For a virtual table, the results are written to iEph as
** records with automatically assigned integer keys For intkey tables, the
** rowid value in <other-columns> is used as the integer key, and the
** remaining fields make up the table record.
*/
static void qBar28i9(
  bpe5rP2ReAl48 *er3GO2,                  /* Parse context */
  int PF0LjDjU6N,                       /* Cursor for open eph. table */
  bpXPO *Pggk00vv5XCX,                     /* PK if table 0 is WITHOUT ROWID */
  XNL0CTTc7o7h *nRzeBk,             /* List of expressions to return */
  YXHw_ *thvftlaY9K2Er,              /* List of tables to select from */
  GA3mR5g0pzo *a87EzByroTtw,                   /* WHERE clause for query */
  XNL0CTTc7o7h *dhxRm,             /* ORDER BY clause */
  GA3mR5g0pzo *Jq37ek10dAC                    /* LIMIT clause */
){
  int pYhdBYyu;
  LdT1UHHim je4nKO2;
  QS_GkD *otdzO = 0;
  XNL0CTTc7o7h *cE615w3lN9i = 0;
  XNL0CTTc7o7h *QmPcctVJE8yDj = 0;
  GA3mR5g0pzo *FDDZTa = 0;
  XNL0CTTc7o7h *jph7TZM = 0;
  Z1TrQ *WG1Q6F71KTpj = er3GO2->WG1Q6F71KTpj;
  gd_2KBv1V *BvAx6uJKKYDb = thvftlaY9K2Er->cmay2IaHVGA9[0].BvAx6uJKKYDb;
  YXHw_ *JIKG0;
  GA3mR5g0pzo *N3eqDPYA;
  int o_xlKGThS;

#ifdef D4cOSBUH9xH
  if( dhxRm && Jq37ek10dAC==0 ) {
    EByNB(er3GO2, "ORDER BY without LIMIT on UPDATE");
    return;
  }
  jph7TZM = cfOGKHaTovnzu(WG1Q6F71KTpj, dhxRm, 0);
  FDDZTa = M8RyeT(WG1Q6F71KTpj, Jq37ek10dAC, 0);
#else
  ZMyTNqw6X(dhxRm);
  ZMyTNqw6X(Jq37ek10dAC);
#endif

  JIKG0 = jElivI(WG1Q6F71KTpj, thvftlaY9K2Er, 0);
  N3eqDPYA = M8RyeT(WG1Q6F71KTpj, a87EzByroTtw, 0);

  lZlEaido1C( thvftlaY9K2Er->VRSfv3ytWpjw>1 );
  if( JIKG0 ){
    lZlEaido1C( JIKG0->cmay2IaHVGA9[0].KyT9JR7.WuM4IWeOM );
    JIKG0->cmay2IaHVGA9[0].KcrtZfPuMdym = -1;
    JIKG0->cmay2IaHVGA9[0].BvAx6uJKKYDb->G6lur--;
    JIKG0->cmay2IaHVGA9[0].BvAx6uJKKYDb = 0;
  }
  if( Pggk00vv5XCX ){
    for(pYhdBYyu=0; pYhdBYyu<Pggk00vv5XCX->pq7vO0; pYhdBYyu++){
      GA3mR5g0pzo *K6Y9q7 = IhTTR6PC(er3GO2, Pggk00vv5XCX->CgbDaAYw7NQKF[pYhdBYyu]);
#ifdef D4cOSBUH9xH
      if( Jq37ek10dAC ){
        QmPcctVJE8yDj = FEtvxYs(er3GO2, QmPcctVJE8yDj, M8RyeT(WG1Q6F71KTpj, K6Y9q7, 0));
      }
#endif
      cE615w3lN9i = FEtvxYs(er3GO2, cE615w3lN9i, K6Y9q7);
    }
    o_xlKGThS = KaHu7ow73cLw9(BvAx6uJKKYDb) ? SlFEX1 : UWo2vu4Ytin5o;
  }else if( x3uBYV5(BvAx6uJKKYDb) ){
    for(pYhdBYyu=0; pYhdBYyu<BvAx6uJKKYDb->cvxjc; pYhdBYyu++){
      cE615w3lN9i = FEtvxYs(er3GO2, cE615w3lN9i, IhTTR6PC(er3GO2, pYhdBYyu));
    }
    o_xlKGThS = SlFEX1;
  }else{
    o_xlKGThS = KaHu7ow73cLw9(BvAx6uJKKYDb) ? SlFEX1 : UWo2vu4Ytin5o;
    cE615w3lN9i = FEtvxYs(er3GO2, 0, cYSjIJiJ(er3GO2,fFjy9MVjDpheb,0,0));
#ifdef D4cOSBUH9xH
    if( Jq37ek10dAC ){
      QmPcctVJE8yDj = FEtvxYs(er3GO2, 0, cYSjIJiJ(er3GO2,fFjy9MVjDpheb,0,0));
    }
#endif
  }
  lZlEaido1C( nRzeBk!=0 || er3GO2->WG1Q6F71KTpj->s7qG );
  if( nRzeBk ){
    for(pYhdBYyu=0; pYhdBYyu<nRzeBk->M60hAKPqh; pYhdBYyu++){
      cE615w3lN9i = FEtvxYs(er3GO2, cE615w3lN9i,
          M8RyeT(WG1Q6F71KTpj, nRzeBk->cmay2IaHVGA9[pYhdBYyu].pNnYNaSqZGNO, 0)
      );
    }
  }
  otdzO = u8IHJY4yZ(er3GO2, cE615w3lN9i,
      JIKG0, N3eqDPYA, QmPcctVJE8yDj, 0, jph7TZM,
      G_7d|VTIexMVLzXLEX|yg5CpJDzu, FDDZTa
  );
  if( otdzO ) otdzO->mu9bcJq |= OVmj;
  RYFZLZIXlZHM7(&je4nKO2, o_xlKGThS, PF0LjDjU6N);
  je4nKO2.daC6 = (Pggk00vv5XCX ? Pggk00vv5XCX->pq7vO0 : -1);
  l2e2(er3GO2, otdzO, &je4nKO2);
  ZwHLtJ(WG1Q6F71KTpj, otdzO);
}

/*
** Process an UPDATE statement.
**
**   UPDATE OR IGNORE tbl SET a=b, c=d FROM tbl2... WHERE e<5 AND f NOT NULL;
**          \_______/ \_/     \______/      \_____/       \________________/
**           onError   |      pChanges         |                pWhere
**                     \_______________________/
**                               pTabList
*/
void vfTKETP3(
  bpe5rP2ReAl48 *er3GO2,         /* The parser context */
  YXHw_ *thvftlaY9K2Er,     /* The table in which we should change things */
  XNL0CTTc7o7h *nRzeBk,    /* Things to be changed */
  GA3mR5g0pzo *a87EzByroTtw,          /* The WHERE clause.  May be null */
  int GMqbKgv00oub,           /* How to handle constraint errors */
  XNL0CTTc7o7h *dhxRm,    /* ORDER BY clause. May be null */
  GA3mR5g0pzo *Jq37ek10dAC,          /* LIMIT clause. May be null */
  sW9Cqw *Yd9t        /* ON CONFLICT clause, or null */
){
  int pYhdBYyu, h52L6NQOVZi, GMOXt;           /* Loop counters */
  gd_2KBv1V *BvAx6uJKKYDb;           /* The table to be updated */
  int xQ3AcUcqn = 0;       /* VDBE instruction address of the start of the loop */
  EvAn3KRZHa *r2sIl = 0; /* Information about the WHERE clause */
  BCD5GL *Tqu4rVzcNe_L;               /* The virtual database engine */
  bpXPO *hzr1XWU65uMUQ;           /* For looping over indices */
  bpXPO *Pggk00vv5XCX;            /* The PRIMARY KEY index for WITHOUT ROWID tables */
  int LXqULl;              /* Number of indices that need updating */
  int erZJ0x6q8etzL;           /* Total number of indexes */
  int o2tEGLltzJ5;          /* Base cursor number */
  int LjCAwc;          /* Cursor for the canonical data btree */
  int WmMWe1q;           /* Cursor for the first index */
  Z1TrQ *WG1Q6F71KTpj;           /* The database structure */
  int *Y8OO = 0;      /* Registers for to each index and the main table */
  int *vqlW_di7j1 = 0;        /* aXRef[i] is the index in pChanges->a[] of the
                         ** an expression for the i-th column of the table.
                         ** aXRef[i]==-1 if the i-th column is not changed. */
  ypp5c0ABe *fpikk;           /* 1 for tables and indices to be opened */
  ypp5c0ABe XdtnkTpwuWo4y;             /* PRIMARY KEY changed in a WITHOUT ROWID table */
  ypp5c0ABe z4x3Rs4CB;          /* Rowid changed in a normal table */
  ypp5c0ABe GYsY7;            /* Either chngPk or chngRowid */
  GA3mR5g0pzo *VjPg = 0;  /* Expression defining the new record number */
  int u_oZ = -1;   /* Index of "rowid=" (or IPK) assignment in pChanges */
  xItYEz e8SOlYXQdlR;  /* The authorization context */
  QToniWsnVe sbdh_QXzyRtwo;       /* The name-context to resolve expressions in */
  int YWuEjSU8i9EUi;               /* Database containing the table being updated */
  int VBhb;          /* ONEPASS_XXX value from where.c */
  int abmh_EN_FqT43;             /* True if foreign key processing is required */
  int Le9P_;        /* Jump here to break out of UPDATE loop */
  int xH7J;     /* Jump here to continue next step of UPDATE loop */
  int brDZkRw;             /* Flags for sqlite3WhereBegin() */

#ifndef XPnqtxnu_z
  int GC1A0vhFfObGG;            /* True when updating a view (INSTEAD OF trigger) */
  xkak *I4MjU4;     /* List of triggers on pTab, if required */
  int AnxDkcNgC6b;             /* Mask of TRIGGER_BEFORE|TRIGGER_AFTER */
#endif
  int TmhvPP;           /* Mask of NEW.* columns accessed by BEFORE triggers */
  int PF0LjDjU6N = 0;          /* Ephemeral table holding all primary key values */
  int JTmEuwueS1lg7 = 0;          /* Number of elements in regKey for WITHOUT ROWID */
  int zNDCZwU[2];   /* The write cursors opened by WHERE_ONEPASS */
  int e_f2Edz = 0;      /* Address of OP_OpenEphemeral */
  int Jy8uJHwLq0xF = 0;           /* First of nPk cells holding PRIMARY KEY value */
  XCV1 t2_9IMgLiK9 = 0;           /* Number of components of the PRIMARY KEY */
  int tWoI2VJM8a = 0;      /* True if REPLACE conflict resolution might happen */
  int lsAYSoG2MrV = 1;   /* The OP_FinishSeek opcode is needed */
  int wE8VgKDihQTC = 0;   /* If there is a FROM, pChanges->nExpr, else 0 */

  /* Register Allocations */
  int mxiY7umcKR = 0;   /* A count of rows changed */
  int AqSuN6rLak6v = 0;   /* The old rowid */
  int mchSDpdA = 0;   /* The new rowid */
  int et1lwN5i7d1 = 0;        /* Content of the NEW.* table in triggers */
  int G4zkDY = 0;        /* Content of OLD.* table in triggers */
  int Qgla = 0;     /* Rowset of rows to be updated */
  int UJb5 = 0;        /* composite PRIMARY KEY value */

  OL_ZcTKy(&e8SOlYXQdlR, 0, sizeof(e8SOlYXQdlR));
  WG1Q6F71KTpj = er3GO2->WG1Q6F71KTpj;
  lZlEaido1C( WG1Q6F71KTpj->er3GO2==er3GO2 );
  if( er3GO2->KGebeb ){
    goto M4aST5loSbout;
  }
  lZlEaido1C( WG1Q6F71KTpj->s7qG==0 );

  /* Locate the table which we want to update.
  */
  BvAx6uJKKYDb = vuPc9acyz(er3GO2, thvftlaY9K2Er);
  if( BvAx6uJKKYDb==0 ) goto M4aST5loSbout;
  YWuEjSU8i9EUi = g_SzW7RX13x(er3GO2->WG1Q6F71KTpj, BvAx6uJKKYDb->WNLXSympZq8);

  /* Figure out if we have any triggers and if the table being
  ** updated is a view.
  */
#ifndef XPnqtxnu_z
  I4MjU4 = x7Pv(er3GO2, BvAx6uJKKYDb, EHCtrIqty, nRzeBk, &AnxDkcNgC6b);
  GC1A0vhFfObGG = x3uBYV5(BvAx6uJKKYDb);
  lZlEaido1C( I4MjU4 || AnxDkcNgC6b==0 );
#else
# define I4MjU4 0
# define GC1A0vhFfObGG 0
# define AnxDkcNgC6b 0
#endif
#ifdef Gjn50VD
# undef GC1A0vhFfObGG
# define GC1A0vhFfObGG 0
#endif

#if ubsugFq
  if( ZhXtR & 0x10000 ){
    pcrsVt(0, "In sqlite3Update() at %s:%d", ZZ4X4zoz5N, eDOeQm21zyhN);
    iR2Hf6FdIPqS(er3GO2->Bao901, thvftlaY9K2Er, nRzeBk, a87EzByroTtw,
                          GMqbKgv00oub, dhxRm, Jq37ek10dAC, Yd9t, I4MjU4);
  }
#endif

  /* If there was a FROM clause, set nChangeFrom to the number of expressions
  ** in the change-list. Otherwise, set it to 0. There cannot be a FROM
  ** clause if this function is being called to generate code for part of
  ** an UPSERT statement.  */
  wE8VgKDihQTC = (thvftlaY9K2Er->VRSfv3ytWpjw>1) ? nRzeBk->M60hAKPqh : 0;
  lZlEaido1C( wE8VgKDihQTC==0 || Yd9t==0 );

#ifdef D4cOSBUH9xH
  if( !GC1A0vhFfObGG && wE8VgKDihQTC==0 ){
    a87EzByroTtw = hr_Qlh(
        er3GO2, thvftlaY9K2Er, a87EzByroTtw, dhxRm, Jq37ek10dAC, "UPDATE"
    );
    dhxRm = 0;
    Jq37ek10dAC = 0;
  }
#endif

  if( Hs20YM(er3GO2, BvAx6uJKKYDb) ){
    goto M4aST5loSbout;
  }
  if( NGZwxES6(er3GO2, BvAx6uJKKYDb, I4MjU4) ){
    goto M4aST5loSbout;
  }

  /* Allocate a cursors for the main database table and for all indices.
  ** The index cursors might not be used, but if they are used they
  ** need to occur right after the database cursor.  So go ahead and
  ** allocate enough space, just in case.
  */
  o2tEGLltzJ5 = LjCAwc = er3GO2->DzW_xD4J++;
  WmMWe1q = LjCAwc+1;
  Pggk00vv5XCX = YJ83(BvAx6uJKKYDb) ? 0 : WuJN(BvAx6uJKKYDb);
  SBxcedMYePMG1( Pggk00vv5XCX!=0 && Pggk00vv5XCX!=BvAx6uJKKYDb->DkmUK );
  for(LXqULl=0, hzr1XWU65uMUQ=BvAx6uJKKYDb->DkmUK; hzr1XWU65uMUQ; hzr1XWU65uMUQ=hzr1XWU65uMUQ->F1RyY2rTMj, LXqULl++){
    if( Pggk00vv5XCX==hzr1XWU65uMUQ ){
      LjCAwc = er3GO2->DzW_xD4J;
    }
    er3GO2->DzW_xD4J++;
  }
  if( Yd9t ){
    /* On an UPSERT, reuse the same cursors already opened by INSERT */
    LjCAwc = Yd9t->LjCAwc;
    WmMWe1q = Yd9t->WmMWe1q;
    er3GO2->DzW_xD4J = o2tEGLltzJ5;
  }
  thvftlaY9K2Er->cmay2IaHVGA9[0].KcrtZfPuMdym = LjCAwc;

  /* Allocate space for aXRef[], aRegIdx[], and aToOpen[].
  ** Initialize aXRef[] and aToOpen[] to their default values.
  */
  vqlW_di7j1 = RAWlpchV9(WG1Q6F71KTpj, sizeof(int) * (BvAx6uJKKYDb->cvxjc+LXqULl+1) + LXqULl+2 );
  if( vqlW_di7j1==0 ) goto M4aST5loSbout;
  Y8OO = vqlW_di7j1+BvAx6uJKKYDb->cvxjc;
  fpikk = (ypp5c0ABe*)(Y8OO+LXqULl+1);
  OL_ZcTKy(fpikk, 1, LXqULl+1);
  fpikk[LXqULl+1] = 0;
  for(pYhdBYyu=0; pYhdBYyu<BvAx6uJKKYDb->cvxjc; pYhdBYyu++) vqlW_di7j1[pYhdBYyu] = -1;

  /* Initialize the name-context */
  OL_ZcTKy(&sbdh_QXzyRtwo, 0, sizeof(sbdh_QXzyRtwo));
  sbdh_QXzyRtwo.er3GO2 = er3GO2;
  sbdh_QXzyRtwo.BRuXeYJQta = thvftlaY9K2Er;
  sbdh_QXzyRtwo.ilzIF.Yd9t = Yd9t;
  sbdh_QXzyRtwo.DV0IUWo3nk = cohitZ5;

  /* Begin generating code. */
  Tqu4rVzcNe_L = rE9KP3w(er3GO2);
  if( Tqu4rVzcNe_L==0 ) goto M4aST5loSbout;

  /* Resolve the column names in all the expressions of the
  ** of the UPDATE statement.  Also find the column index
  ** for each column to be updated in the pChanges array.  For each
  ** column to be updated, make sure we have authorization to change
  ** that column.
  */
  z4x3Rs4CB = XdtnkTpwuWo4y = 0;
  for(pYhdBYyu=0; pYhdBYyu<nRzeBk->M60hAKPqh; pYhdBYyu++){
    ypp5c0ABe AqoD796 = G93mjx_WHCf(nRzeBk->cmay2IaHVGA9[pYhdBYyu].jCT6IEGpLBp);
    /* If this is an UPDATE with a FROM clause, do not resolve expressions
    ** here. The call to sqlite3Select() below will do that. */
    if( wE8VgKDihQTC==0 && fHMyI5UB(&sbdh_QXzyRtwo, nRzeBk->cmay2IaHVGA9[pYhdBYyu].pNnYNaSqZGNO) ){
      goto M4aST5loSbout;
    }
    for(h52L6NQOVZi=0; h52L6NQOVZi<BvAx6uJKKYDb->cvxjc; h52L6NQOVZi++){
      if( BvAx6uJKKYDb->PXCh1YPlYG8[h52L6NQOVZi].np6JgSEqIz==AqoD796
       && vMxu(BvAx6uJKKYDb->PXCh1YPlYG8[h52L6NQOVZi].tEmLCm507, nRzeBk->cmay2IaHVGA9[pYhdBYyu].jCT6IEGpLBp)==0
      ){
        if( h52L6NQOVZi==BvAx6uJKKYDb->oe2Kus12s ){
          z4x3Rs4CB = 1;
          VjPg = nRzeBk->cmay2IaHVGA9[pYhdBYyu].pNnYNaSqZGNO;
          u_oZ = pYhdBYyu;
        }else if( Pggk00vv5XCX && (BvAx6uJKKYDb->PXCh1YPlYG8[h52L6NQOVZi].boa4gB7gRVw14 & ljfE8)!=0 ){
          XdtnkTpwuWo4y = 1;
        }
#ifndef aGjLcXc3J
        else if( BvAx6uJKKYDb->PXCh1YPlYG8[h52L6NQOVZi].boa4gB7gRVw14 & RIOM ){
          SBxcedMYePMG1( BvAx6uJKKYDb->PXCh1YPlYG8[h52L6NQOVZi].boa4gB7gRVw14 & YCgHQAVQEXY );
          SBxcedMYePMG1( BvAx6uJKKYDb->PXCh1YPlYG8[h52L6NQOVZi].boa4gB7gRVw14 & aOZRrjau7hls );
          EByNB(er3GO2,
             "cannot UPDATE generated column \"%s\"",
             BvAx6uJKKYDb->PXCh1YPlYG8[h52L6NQOVZi].tEmLCm507);
          goto M4aST5loSbout;
        }
#endif
        vqlW_di7j1[h52L6NQOVZi] = pYhdBYyu;
        break;
      }
    }
    if( h52L6NQOVZi>=BvAx6uJKKYDb->cvxjc ){
      if( Pggk00vv5XCX==0 && MCvP0FW0emzZf(nRzeBk->cmay2IaHVGA9[pYhdBYyu].jCT6IEGpLBp) ){
        h52L6NQOVZi = -1;
        z4x3Rs4CB = 1;
        VjPg = nRzeBk->cmay2IaHVGA9[pYhdBYyu].pNnYNaSqZGNO;
        u_oZ = pYhdBYyu;
      }else{
        EByNB(er3GO2, "no such column: %s", nRzeBk->cmay2IaHVGA9[pYhdBYyu].jCT6IEGpLBp);
        er3GO2->vbtaUOI5 = 1;
        goto M4aST5loSbout;
      }
    }
#ifndef R7yERkZfoD
    {
      int OZPiFdm;
      OZPiFdm = sCj32Ez(er3GO2, W01DASkE, BvAx6uJKKYDb->ZUF5,
                            h52L6NQOVZi<0 ? "ROWID" : BvAx6uJKKYDb->PXCh1YPlYG8[h52L6NQOVZi].tEmLCm507,
                            WG1Q6F71KTpj->cwqrTo[YWuEjSU8i9EUi].o9CSzBrdb9);
      if( OZPiFdm==H5s7Iv5JOIBl ){
        goto M4aST5loSbout;
      }else if( OZPiFdm==SxsSrHz6 ){
        vqlW_di7j1[h52L6NQOVZi] = -1;
      }
    }
#endif
  }
  lZlEaido1C( (z4x3Rs4CB & XdtnkTpwuWo4y)==0 );
  lZlEaido1C( z4x3Rs4CB==0 || z4x3Rs4CB==1 );
  lZlEaido1C( XdtnkTpwuWo4y==0 || XdtnkTpwuWo4y==1 );
  GYsY7 = z4x3Rs4CB + XdtnkTpwuWo4y;

#ifndef aGjLcXc3J
  /* Mark generated columns as changing if their generator expressions
  ** reference any changing column.  The actual aXRef[] value for
  ** generated expressions is not used, other than to check to see that it
  ** is non-negative, so the value of aXRef[] for generated columns can be
  ** set to any non-negative number.  We use 99999 so that the value is
  ** obvious when looking at aXRef[] in a symbolic debugger.
  */
  if( BvAx6uJKKYDb->zHrnFwWnI & YTpTANC6 ){
    int dodKMqKSR_;
    SBxcedMYePMG1( BvAx6uJKKYDb->zHrnFwWnI & VU6VGTW4 );
    SBxcedMYePMG1( BvAx6uJKKYDb->zHrnFwWnI & B319SQVT );
    do{
      dodKMqKSR_ = 0;
      for(pYhdBYyu=0; pYhdBYyu<BvAx6uJKKYDb->cvxjc; pYhdBYyu++){
        if( vqlW_di7j1[pYhdBYyu]>=0 ) continue;
        if( (BvAx6uJKKYDb->PXCh1YPlYG8[pYhdBYyu].boa4gB7gRVw14 & RIOM)==0 ) continue;
        if( GFjYNxi7c(
                upKZ6(BvAx6uJKKYDb, &BvAx6uJKKYDb->PXCh1YPlYG8[pYhdBYyu]),
                 vqlW_di7j1, z4x3Rs4CB)
        ){
          vqlW_di7j1[pYhdBYyu] = 99999;
          dodKMqKSR_ = 1;
        }
      }
    }while( dodKMqKSR_ );
  }
#endif

  /* The SET expressions are not actually used inside the WHERE loop.
  ** So reset the colUsed mask. Unless this is a virtual table. In that
  ** case, set all bits of the colUsed mask (to ensure that the virtual
  ** table implementation makes all columns available).
  */
  thvftlaY9K2Er->cmay2IaHVGA9[0].ZHCvs = KaHu7ow73cLw9(BvAx6uJKKYDb) ? OzcC : 0;

  abmh_EN_FqT43 = w_IpyL7WWPB6(er3GO2, BvAx6uJKKYDb, vqlW_di7j1, GYsY7);

  /* There is one entry in the aRegIdx[] array for each index on the table
  ** being updated.  Fill in aRegIdx[] with a register number that will hold
  ** the key for accessing each index.
  */
  if( GMqbKgv00oub==O8R1 ) tWoI2VJM8a = 1;
  for(erZJ0x6q8etzL=0, hzr1XWU65uMUQ=BvAx6uJKKYDb->DkmUK; hzr1XWU65uMUQ; hzr1XWU65uMUQ=hzr1XWU65uMUQ->F1RyY2rTMj, erZJ0x6q8etzL++){
    int HE7EI;
    if( GYsY7 || abmh_EN_FqT43>1 || hzr1XWU65uMUQ==Pggk00vv5XCX
     || xOrPm(hzr1XWU65uMUQ,vqlW_di7j1,z4x3Rs4CB)
    ){
      HE7EI = ++er3GO2->RXv6;
      er3GO2->RXv6 += hzr1XWU65uMUQ->rer9SZcZH;
    }else{
      HE7EI = 0;
      for(pYhdBYyu=0; pYhdBYyu<hzr1XWU65uMUQ->pq7vO0; pYhdBYyu++){
        if( bYkmPTnJY(hzr1XWU65uMUQ, pYhdBYyu, vqlW_di7j1, z4x3Rs4CB) ){
          HE7EI = ++er3GO2->RXv6;
          er3GO2->RXv6 += hzr1XWU65uMUQ->rer9SZcZH;
          if( GMqbKgv00oub==iJ7LQ && hzr1XWU65uMUQ->GMqbKgv00oub==O8R1 ){
            tWoI2VJM8a = 1;
          }
          break;
        }
      }
    }
    if( HE7EI==0 ) fpikk[erZJ0x6q8etzL+1] = 0;
    Y8OO[erZJ0x6q8etzL] = HE7EI;
  }
  Y8OO[erZJ0x6q8etzL] = ++er3GO2->RXv6;  /* Register storing the table record */
  if( tWoI2VJM8a ){
    /* If REPLACE conflict resolution might be invoked, open cursors on all
    ** indexes in case they are needed to delete records.  */
    OL_ZcTKy(fpikk, 1, LXqULl+1);
  }

  if( er3GO2->wBeZQ3sjzlA3O==0 ) Jglmuq0kp(Tqu4rVzcNe_L);
  GivD(er3GO2, I4MjU4 || abmh_EN_FqT43, YWuEjSU8i9EUi);

  /* Allocate required registers. */
  if( !KaHu7ow73cLw9(BvAx6uJKKYDb) ){
    /* For now, regRowSet and aRegIdx[nAllIdx] share the same register.
    ** If regRowSet turns out to be needed, then aRegIdx[nAllIdx] will be
    ** reallocated.  aRegIdx[nAllIdx] is the register in which the main
    ** table record is written.  regRowSet holds the RowSet for the
    ** two-pass update algorithm. */
    lZlEaido1C( Y8OO[erZJ0x6q8etzL]==er3GO2->RXv6 );
    Qgla = Y8OO[erZJ0x6q8etzL];
    AqSuN6rLak6v = mchSDpdA = ++er3GO2->RXv6;
    if( XdtnkTpwuWo4y || I4MjU4 || abmh_EN_FqT43 ){
      G4zkDY = er3GO2->RXv6 + 1;
      er3GO2->RXv6 += BvAx6uJKKYDb->cvxjc;
    }
    if( GYsY7 || I4MjU4 || abmh_EN_FqT43 ){
      mchSDpdA = ++er3GO2->RXv6;
    }
    et1lwN5i7d1 = er3GO2->RXv6 + 1;
    er3GO2->RXv6 += BvAx6uJKKYDb->cvxjc;
  }

  /* Start the view context. */
  if( GC1A0vhFfObGG ){
    roJFViCaBDUki(er3GO2, &e8SOlYXQdlR, BvAx6uJKKYDb->ZUF5);
  }

  /* If we are trying to update a view, realize that view into
  ** an ephemeral table.
  */
#if !yHJGJ46hXCW(Gjn50VD) && !yHJGJ46hXCW(XPnqtxnu_z)
  if( wE8VgKDihQTC==0 && GC1A0vhFfObGG ){
    MxrhytRvg5Pd(er3GO2, BvAx6uJKKYDb,
        a87EzByroTtw, dhxRm, Jq37ek10dAC, LjCAwc
    );
    dhxRm = 0;
    Jq37ek10dAC = 0;
  }
#endif

  /* Resolve the column names in all the expressions in the
  ** WHERE clause.
  */
  if( wE8VgKDihQTC==0 && fHMyI5UB(&sbdh_QXzyRtwo, a87EzByroTtw) ){
    goto M4aST5loSbout;
  }

#ifndef uwEiL
  /* Virtual tables must be handled separately */
  if( KaHu7ow73cLw9(BvAx6uJKKYDb) ){
    BUo4(er3GO2, thvftlaY9K2Er, BvAx6uJKKYDb, nRzeBk, VjPg, vqlW_di7j1,
                       a87EzByroTtw, GMqbKgv00oub);
    goto M4aST5loSbout;
  }
#endif

  /* Jump to labelBreak to abandon further processing of this UPDATE */
  xH7J = Le9P_ = r5keSropqH02(er3GO2);

  /* Not an UPSERT.  Normal processing.  Begin by
  ** initialize the count of updated rows */
  if( (WG1Q6F71KTpj->brDZkRw&Ql3D2bX4)!=0
   && !er3GO2->UiHcjxcXI
   && !er3GO2->wBeZQ3sjzlA3O
   && !er3GO2->jkzS3RBETq8GV
   && Yd9t==0
  ){
    mxiY7umcKR = ++er3GO2->RXv6;
    kE84_A5MPI(Tqu4rVzcNe_L, dB_iKW_s, 0, mxiY7umcKR);
  }

  if( wE8VgKDihQTC==0 && YJ83(BvAx6uJKKYDb) ){
    qP6Kf(Tqu4rVzcNe_L, cJ85SdfX5IQ, 0, Qgla, AqSuN6rLak6v);
    PF0LjDjU6N = er3GO2->DzW_xD4J++;
    e_f2Edz = qP6Kf(Tqu4rVzcNe_L, EkPXdsUX0c, PF0LjDjU6N, 0, Qgla);
  }else{
    lZlEaido1C( Pggk00vv5XCX!=0 || YJ83(BvAx6uJKKYDb) );
    t2_9IMgLiK9 = Pggk00vv5XCX ? Pggk00vv5XCX->pq7vO0 : 0;
    Jy8uJHwLq0xF = er3GO2->RXv6+1;
    er3GO2->RXv6 += t2_9IMgLiK9;
    er3GO2->RXv6 += wE8VgKDihQTC;
    UJb5 = ++er3GO2->RXv6;
    if( Yd9t==0 ){
      int U9Cow = t2_9IMgLiK9 + wE8VgKDihQTC + (GC1A0vhFfObGG ? BvAx6uJKKYDb->cvxjc : 0);
      PF0LjDjU6N = er3GO2->DzW_xD4J++;
      if( Pggk00vv5XCX ) qP6Kf(Tqu4rVzcNe_L, cJ85SdfX5IQ, 0, Jy8uJHwLq0xF, Jy8uJHwLq0xF+t2_9IMgLiK9-1);
      e_f2Edz = kE84_A5MPI(Tqu4rVzcNe_L, EkPXdsUX0c, PF0LjDjU6N, U9Cow);
      if( Pggk00vv5XCX ){
        AN95xz *p8jbWZ = vE8jk(er3GO2, Pggk00vv5XCX);
        if( p8jbWZ ){
          p8jbWZ->rdCnkujG2TN7 = U9Cow;
          si7Xp9l(Tqu4rVzcNe_L, p8jbWZ, DDXt1gHzZ);
        }
      }
      if( wE8VgKDihQTC ){
        qBar28i9(
            er3GO2, PF0LjDjU6N, Pggk00vv5XCX, nRzeBk, thvftlaY9K2Er, a87EzByroTtw, dhxRm, Jq37ek10dAC
        );
#ifndef pO8bHH8RVY
        if( GC1A0vhFfObGG ) LjCAwc = PF0LjDjU6N;
#endif
      }
    }
  }

  if( wE8VgKDihQTC ){
    J3FyGBP(er3GO2);
    VBhb = YgcTsmsHMgDf;
    JTmEuwueS1lg7 = t2_9IMgLiK9;
    UJb5 = Jy8uJHwLq0xF;
  }else{
    if( Yd9t ){
      /* If this is an UPSERT, then all cursors have already been opened by
      ** the outer INSERT and the data cursor should be pointing at the row
      ** that is to be updated.  So bypass the code that searches for the
      ** row(s) to be updated.
      */
      r2sIl = 0;
      VBhb = Dh39Ske;
      VSFszZsw5x(er3GO2, a87EzByroTtw, Le9P_, CRU5NZ);
      lsAYSoG2MrV = 0;
    }else{
      /* Begin the database scan.
      **
      ** Do not consider a single-pass strategy for a multi-row update if
      ** there is anything that might disrupt the cursor being used to do
      ** the UPDATE:
      **   (1) This is a nested UPDATE
      **   (2) There are triggers
      **   (3) There are FOREIGN KEY constraints
      **   (4) There are REPLACE conflict handlers
      **   (5) There are subqueries in the WHERE clause
      */
      brDZkRw = PJMHkydfg;
      if( !er3GO2->wBeZQ3sjzlA3O
       && !I4MjU4
       && !abmh_EN_FqT43
       && !GYsY7
       && !tWoI2VJM8a
       && (a87EzByroTtw==0 || !uM5J54(a87EzByroTtw, tfuP))
      ){
        brDZkRw |= fnxnzlApI;
      }
      r2sIl = wrXDUc_xFg(er3GO2, thvftlaY9K2Er, a87EzByroTtw,0,0,0,brDZkRw,WmMWe1q);
      if( r2sIl==0 ) goto M4aST5loSbout;

      /* A one-pass strategy that might update more than one row may not
      ** be used if any column of the index used for the scan is being
      ** updated. Otherwise, if there is an index on "b", statements like
      ** the following could create an infinite loop:
      **
      **   UPDATE t1 SET b=b+1 WHERE b>?
      **
      ** Fall back to ONEPASS_OFF if where.c has selected a ONEPASS_MULTI
      ** strategy that uses an index for which one or more columns are being
      ** updated.  */
      VBhb = Hnk6TGrx9P2(r2sIl, zNDCZwU);
      lsAYSoG2MrV = YvYcX(r2sIl);
      if( VBhb!=Dh39Ske ){
        J3FyGBP(er3GO2);
        if( VBhb==Cix6kRDTk ){
          int PE__6v = zNDCZwU[1];
          if( PE__6v>=0 && PE__6v!=LjCAwc && fpikk[PE__6v-o2tEGLltzJ5] ){
            VBhb = YgcTsmsHMgDf;
          }
          lZlEaido1C( PE__6v!=LjCAwc || !YJ83(BvAx6uJKKYDb) );
        }
      }
    }

    if( YJ83(BvAx6uJKKYDb) ){
      /* Read the rowid of the current row of the WHERE scan. In ONEPASS_OFF
      ** mode, write the rowid into the FIFO. In either of the one-pass modes,
      ** leave it in register regOldRowid.  */
      kE84_A5MPI(Tqu4rVzcNe_L, BJZHZZo9jhz, LjCAwc, AqSuN6rLak6v);
      if( VBhb==YgcTsmsHMgDf ){
        Y8OO[erZJ0x6q8etzL] = ++er3GO2->RXv6;
        qP6Kf(Tqu4rVzcNe_L, QY3uN1P, PF0LjDjU6N, Qgla, AqSuN6rLak6v);
      }else{
        if( cYZVyl4(e_f2Edz) ) W_8Dvks(Tqu4rVzcNe_L, e_f2Edz);
      }
    }else{
      /* Read the PK of the current row into an array of registers. In
      ** ONEPASS_OFF mode, serialize the array into a record and store it in
      ** the ephemeral table. Or, in ONEPASS_SINGLE or MULTI mode, change
      ** the OP_OpenEphemeral instruction to a Noop (the ephemeral table
      ** is not required) and leave the PK fields in the array of registers.  */
      for(pYhdBYyu=0; pYhdBYyu<t2_9IMgLiK9; pYhdBYyu++){
        lZlEaido1C( Pggk00vv5XCX->CgbDaAYw7NQKF[pYhdBYyu]>=0 );
        WxOf_FNt(Tqu4rVzcNe_L, BvAx6uJKKYDb, LjCAwc,
                                        Pggk00vv5XCX->CgbDaAYw7NQKF[pYhdBYyu], Jy8uJHwLq0xF+pYhdBYyu);
      }
      if( VBhb ){
        if( e_f2Edz ) W_8Dvks(Tqu4rVzcNe_L, e_f2Edz);
        JTmEuwueS1lg7 = t2_9IMgLiK9;
        UJb5 = Jy8uJHwLq0xF;
      }else{
        Ry234T(Tqu4rVzcNe_L, ykvNm3Jxq69XX, Jy8uJHwLq0xF, t2_9IMgLiK9, UJb5,
                          GTLbHC1aW(WG1Q6F71KTpj, Pggk00vv5XCX), t2_9IMgLiK9);
        SsZc1YKd(Tqu4rVzcNe_L, ntc1pitCJJO, PF0LjDjU6N, UJb5, Jy8uJHwLq0xF, t2_9IMgLiK9);
      }
    }
  }

  if( Yd9t==0 ){
    if( wE8VgKDihQTC==0 && VBhb!=Cix6kRDTk ){
      MgYgpv(r2sIl);
    }

    if( !GC1A0vhFfObGG ){
      int HrX2wWPx = 0;
      int qWwxVBrQU9ET = 0;
      int IDSjHXN5Q2h6K = 0;

      /* Open every index that needs updating. */
      if( VBhb!=YgcTsmsHMgDf ){
        if( zNDCZwU[0]>=0 ) fpikk[zNDCZwU[0]-o2tEGLltzJ5] = 0;
        if( zNDCZwU[1]>=0 ) fpikk[zNDCZwU[1]-o2tEGLltzJ5] = 0;
      }

      if( VBhb==Cix6kRDTk && (LXqULl-(zNDCZwU[1]>=0))>0 ){
        HrX2wWPx = zyFrP(Tqu4rVzcNe_L, WtFLvr4fF); gBUuOCcZ0(Tqu4rVzcNe_L);
      }
      bGJmM0BqOjA6(er3GO2, BvAx6uJKKYDb, jPIk4RqaA, 0, o2tEGLltzJ5,
                                 fpikk, &qWwxVBrQU9ET, &IDSjHXN5Q2h6K);
      if( HrX2wWPx ){
        wx8cy3wVMF(Tqu4rVzcNe_L, HrX2wWPx);
      }
    }

    /* Top of the update loop */
    if( VBhb!=YgcTsmsHMgDf ){
      if( zNDCZwU[0]!=LjCAwc
       && zNDCZwU[1]!=LjCAwc
#ifdef b9mLVxm
       && !GC1A0vhFfObGG
#endif
      ){
        lZlEaido1C( Pggk00vv5XCX );
        SsZc1YKd(Tqu4rVzcNe_L, N97HCYIN7, LjCAwc, Le9P_, UJb5,JTmEuwueS1lg7);
        gBUuOCcZ0(Tqu4rVzcNe_L);
      }
      if( VBhb!=Dh39Ske ){
        xH7J = r5keSropqH02(er3GO2);
      }
      kE84_A5MPI(Tqu4rVzcNe_L, cffApa, Pggk00vv5XCX ? UJb5 : AqSuN6rLak6v, Le9P_);
      bxfCVO(Tqu4rVzcNe_L, Pggk00vv5XCX==0);
      bxfCVO(Tqu4rVzcNe_L, Pggk00vv5XCX!=0);
    }else if( Pggk00vv5XCX || wE8VgKDihQTC ){
      xH7J = r5keSropqH02(er3GO2);
      kE84_A5MPI(Tqu4rVzcNe_L, L9tsd7YK, PF0LjDjU6N, Le9P_); gBUuOCcZ0(Tqu4rVzcNe_L);
      xQ3AcUcqn = ZJcy(Tqu4rVzcNe_L);
      if( wE8VgKDihQTC ){
        if( !GC1A0vhFfObGG ){
          if( Pggk00vv5XCX ){
            for(pYhdBYyu=0; pYhdBYyu<t2_9IMgLiK9; pYhdBYyu++){
              qP6Kf(Tqu4rVzcNe_L, qfCLm, PF0LjDjU6N, pYhdBYyu, Jy8uJHwLq0xF+pYhdBYyu);
            }
            SsZc1YKd(
                Tqu4rVzcNe_L, N97HCYIN7, LjCAwc, xH7J, Jy8uJHwLq0xF, t2_9IMgLiK9
            ); gBUuOCcZ0(Tqu4rVzcNe_L);
          }else{
            kE84_A5MPI(Tqu4rVzcNe_L, BJZHZZo9jhz, PF0LjDjU6N, AqSuN6rLak6v);
            qP6Kf(
                Tqu4rVzcNe_L, KY7yfVWG6p6c, LjCAwc, xH7J, AqSuN6rLak6v
            ); gBUuOCcZ0(Tqu4rVzcNe_L);
          }
        }
      }else{
        kE84_A5MPI(Tqu4rVzcNe_L, inne09DRAf6, PF0LjDjU6N, UJb5);
        SsZc1YKd(Tqu4rVzcNe_L, N97HCYIN7, LjCAwc, xH7J, UJb5,0);
        gBUuOCcZ0(Tqu4rVzcNe_L);
      }
    }else{
      kE84_A5MPI(Tqu4rVzcNe_L, L9tsd7YK, PF0LjDjU6N, Le9P_); gBUuOCcZ0(Tqu4rVzcNe_L);
      xH7J = r5keSropqH02(er3GO2);
      xQ3AcUcqn = kE84_A5MPI(Tqu4rVzcNe_L, BJZHZZo9jhz, PF0LjDjU6N, AqSuN6rLak6v);
      gBUuOCcZ0(Tqu4rVzcNe_L);
      qP6Kf(Tqu4rVzcNe_L, KY7yfVWG6p6c, LjCAwc, xH7J, AqSuN6rLak6v);
      gBUuOCcZ0(Tqu4rVzcNe_L);
    }
  }

  /* If the rowid value will change, set register regNewRowid to
  ** contain the new value. If the rowid is not being modified,
  ** then regNewRowid is the same register as regOldRowid, which is
  ** already populated.  */
  lZlEaido1C( GYsY7 || I4MjU4 || abmh_EN_FqT43 || AqSuN6rLak6v==mchSDpdA );
  if( z4x3Rs4CB ){
    lZlEaido1C( u_oZ>=0 );
    if( wE8VgKDihQTC==0 ){
      B4KRrB0P8sSb(er3GO2, VjPg, mchSDpdA);
    }else{
      qP6Kf(Tqu4rVzcNe_L, qfCLm, PF0LjDjU6N, u_oZ, mchSDpdA);
    }
    iiGBdkW(Tqu4rVzcNe_L, N0VBAcMbhh, mchSDpdA); gBUuOCcZ0(Tqu4rVzcNe_L);
  }

  /* Compute the old pre-UPDATE content of the row being changed, if that
  ** information is needed */
  if( XdtnkTpwuWo4y || abmh_EN_FqT43 || I4MjU4 ){
    XdJE relO = (abmh_EN_FqT43 ? JRsH(er3GO2, BvAx6uJKKYDb) : 0);
    relO |= wZvt(er3GO2,
        I4MjU4, nRzeBk, 0, PtjBBH4Uu|MCzaRaTH62V, BvAx6uJKKYDb, GMqbKgv00oub
    );
    for(pYhdBYyu=0; pYhdBYyu<BvAx6uJKKYDb->cvxjc; pYhdBYyu++){
      XdJE boa4gB7gRVw14 = BvAx6uJKKYDb->PXCh1YPlYG8[pYhdBYyu].boa4gB7gRVw14;
      GMOXt = UImkf_(BvAx6uJKKYDb, pYhdBYyu) + G4zkDY;
      if( relO==0xffffffff
       || (pYhdBYyu<32 && (relO & LnEIHHBuo9U(pYhdBYyu))!=0)
       || (boa4gB7gRVw14 & ljfE8)!=0
      ){
        SBxcedMYePMG1(  relO!=0xffffffff && pYhdBYyu==31 );
        WxOf_FNt(Tqu4rVzcNe_L, BvAx6uJKKYDb, LjCAwc, pYhdBYyu, GMOXt);
      }else{
        kE84_A5MPI(Tqu4rVzcNe_L, cJ85SdfX5IQ, 0, GMOXt);
      }
    }
    if( z4x3Rs4CB==0 && Pggk00vv5XCX==0 ){
#ifdef b9mLVxm
      if( GC1A0vhFfObGG ) kE84_A5MPI(Tqu4rVzcNe_L, cJ85SdfX5IQ, 0, AqSuN6rLak6v);
#endif
      kE84_A5MPI(Tqu4rVzcNe_L, fADpH0S, AqSuN6rLak6v, mchSDpdA);
    }
  }

  /* Populate the array of registers beginning at regNew with the new
  ** row data. This array is used to check constants, create the new
  ** table and index records, and as the values for any new.* references
  ** made by triggers.
  **
  ** If there are one or more BEFORE triggers, then do not populate the
  ** registers associated with columns that are (a) not modified by
  ** this UPDATE statement and (b) not accessed by new.* references. The
  ** values for registers not modified by the UPDATE must be reloaded from
  ** the database after the BEFORE triggers are fired anyway (as the trigger
  ** may have modified them). So not loading those that are not going to
  ** be used eliminates some redundant opcodes.
  */
  TmhvPP = wZvt(
      er3GO2, I4MjU4, nRzeBk, 1, PtjBBH4Uu, BvAx6uJKKYDb, GMqbKgv00oub
  );
  for(pYhdBYyu=0, GMOXt=et1lwN5i7d1; pYhdBYyu<BvAx6uJKKYDb->cvxjc; pYhdBYyu++, GMOXt++){
    if( pYhdBYyu==BvAx6uJKKYDb->oe2Kus12s ){
      kE84_A5MPI(Tqu4rVzcNe_L, cJ85SdfX5IQ, 0, GMOXt);
    }else if( (BvAx6uJKKYDb->PXCh1YPlYG8[pYhdBYyu].boa4gB7gRVw14 & RIOM)!=0 ){
      if( BvAx6uJKKYDb->PXCh1YPlYG8[pYhdBYyu].boa4gB7gRVw14 & YCgHQAVQEXY ) GMOXt--;
    }else{
      h52L6NQOVZi = vqlW_di7j1[pYhdBYyu];
      if( h52L6NQOVZi>=0 ){
        if( wE8VgKDihQTC ){
          int U6g75rHYEd = (GC1A0vhFfObGG ? BvAx6uJKKYDb->cvxjc : t2_9IMgLiK9);
          lZlEaido1C( VBhb==YgcTsmsHMgDf );
          qP6Kf(Tqu4rVzcNe_L, qfCLm, PF0LjDjU6N, U6g75rHYEd+h52L6NQOVZi, GMOXt);
        }else{
          B4KRrB0P8sSb(er3GO2, nRzeBk->cmay2IaHVGA9[h52L6NQOVZi].pNnYNaSqZGNO, GMOXt);
        }
      }else if( 0==(AnxDkcNgC6b&PtjBBH4Uu) || pYhdBYyu>31 || (TmhvPP & LnEIHHBuo9U(pYhdBYyu)) ){
        /* This branch loads the value of a column that will not be changed
        ** into a register. This is done if there are no BEFORE triggers, or
        ** if there are one or more BEFORE triggers that use this value via
        ** a new.* reference in a trigger program.
        */
        SBxcedMYePMG1( pYhdBYyu==31 );
        SBxcedMYePMG1( pYhdBYyu==32 );
        WxOf_FNt(Tqu4rVzcNe_L, BvAx6uJKKYDb, LjCAwc, pYhdBYyu, GMOXt);
        lsAYSoG2MrV = 0;
      }else{
        kE84_A5MPI(Tqu4rVzcNe_L, cJ85SdfX5IQ, 0, GMOXt);
      }
    }
  }
#ifndef aGjLcXc3J
  if( BvAx6uJKKYDb->zHrnFwWnI & YTpTANC6 ){
    SBxcedMYePMG1( BvAx6uJKKYDb->zHrnFwWnI & VU6VGTW4 );
    SBxcedMYePMG1( BvAx6uJKKYDb->zHrnFwWnI & B319SQVT );
    k_JR1D3dXYC(er3GO2, et1lwN5i7d1, BvAx6uJKKYDb);
  }
#endif

  /* Fire any BEFORE UPDATE triggers. This happens before constraints are
  ** verified. One could argue that this is wrong.
  */
  if( AnxDkcNgC6b&PtjBBH4Uu ){
    VnRjw5OF(Tqu4rVzcNe_L, BvAx6uJKKYDb, et1lwN5i7d1);
    qXUPPiHOa(er3GO2, I4MjU4, EHCtrIqty, nRzeBk,
        PtjBBH4Uu, BvAx6uJKKYDb, AqSuN6rLak6v, GMqbKgv00oub, xH7J);

    if( !GC1A0vhFfObGG ){
      /* The row-trigger may have deleted the row being updated. In this
      ** case, jump to the next row. No updates or AFTER triggers are
      ** required. This behavior - what happens when the row being updated
      ** is deleted or renamed by a BEFORE trigger - is left undefined in the
      ** documentation.
      */
      if( Pggk00vv5XCX ){
        SsZc1YKd(Tqu4rVzcNe_L, N97HCYIN7,LjCAwc,xH7J,UJb5,JTmEuwueS1lg7);
        gBUuOCcZ0(Tqu4rVzcNe_L);
      }else{
        qP6Kf(Tqu4rVzcNe_L, KY7yfVWG6p6c, LjCAwc, xH7J,AqSuN6rLak6v);
        gBUuOCcZ0(Tqu4rVzcNe_L);
      }

      /* After-BEFORE-trigger-reload-loop:
      ** If it did not delete it, the BEFORE trigger may still have modified
      ** some of the columns of the row being updated. Load the values for
      ** all columns not modified by the update statement into their registers
      ** in case this has happened. Only unmodified columns are reloaded.
      ** The values computed for modified columns use the values before the
      ** BEFORE trigger runs.  See test case trigger1-18.0 (added 2018-04-26)
      ** for an example.
      */
      for(pYhdBYyu=0, GMOXt=et1lwN5i7d1; pYhdBYyu<BvAx6uJKKYDb->cvxjc; pYhdBYyu++, GMOXt++){
        if( BvAx6uJKKYDb->PXCh1YPlYG8[pYhdBYyu].boa4gB7gRVw14 & RIOM ){
          if( BvAx6uJKKYDb->PXCh1YPlYG8[pYhdBYyu].boa4gB7gRVw14 & YCgHQAVQEXY ) GMOXt--;
        }else if( vqlW_di7j1[pYhdBYyu]<0 && pYhdBYyu!=BvAx6uJKKYDb->oe2Kus12s ){
          WxOf_FNt(Tqu4rVzcNe_L, BvAx6uJKKYDb, LjCAwc, pYhdBYyu, GMOXt);
        }
      }
#ifndef aGjLcXc3J
      if( BvAx6uJKKYDb->zHrnFwWnI & YTpTANC6 ){
        SBxcedMYePMG1( BvAx6uJKKYDb->zHrnFwWnI & VU6VGTW4 );
        SBxcedMYePMG1( BvAx6uJKKYDb->zHrnFwWnI & B319SQVT );
        k_JR1D3dXYC(er3GO2, et1lwN5i7d1, BvAx6uJKKYDb);
      }
#endif
    }
  }

  if( !GC1A0vhFfObGG ){
    /* Do constraint checks. */
    lZlEaido1C( AqSuN6rLak6v>0 );
    ThOJVj2sNf(er3GO2, BvAx6uJKKYDb, Y8OO, LjCAwc, WmMWe1q,
        mchSDpdA, AqSuN6rLak6v, GYsY7, GMqbKgv00oub, xH7J, &tWoI2VJM8a,
        vqlW_di7j1, 0);

    /* If REPLACE conflict handling may have been used, or if the PK of the
    ** row is changing, then the GenerateConstraintChecks() above may have
    ** moved cursor iDataCur. Reseek it. */
    if( tWoI2VJM8a || GYsY7 ){
      if( Pggk00vv5XCX ){
        SsZc1YKd(Tqu4rVzcNe_L, N97HCYIN7,LjCAwc,xH7J,UJb5,JTmEuwueS1lg7);
      }else{
        qP6Kf(Tqu4rVzcNe_L, KY7yfVWG6p6c, LjCAwc, xH7J,AqSuN6rLak6v);
      }
      gBUuOCcZ0(Tqu4rVzcNe_L);
    }

    /* Do FK constraint checks. */
    if( abmh_EN_FqT43 ){
      pDQl(er3GO2, BvAx6uJKKYDb, AqSuN6rLak6v, 0, vqlW_di7j1, GYsY7);
    }

    /* Delete the index entries associated with the current record.  */
    Vpde(er3GO2, BvAx6uJKKYDb, LjCAwc, WmMWe1q, Y8OO, -1);

    /* We must run the OP_FinishSeek opcode to resolve a prior
    ** OP_DeferredSeek if there is any possibility that there have been
    ** no OP_Column opcodes since the OP_DeferredSeek was issued.  But
    ** we want to avoid the OP_FinishSeek if possible, as running it
    ** costs CPU cycles. */
    if( lsAYSoG2MrV ){
      iiGBdkW(Tqu4rVzcNe_L, GR3E5xId, LjCAwc);
    }

    /* If changing the rowid value, or if there are foreign key constraints
    ** to process, delete the old record. Otherwise, add a noop OP_Delete
    ** to invoke the pre-update hook.
    **
    ** That (regNew==regnewRowid+1) is true is also important for the
    ** pre-update hook. If the caller invokes preupdate_new(), the returned
    ** value is copied from memory cell (regNewRowid+1+iCol), where iCol
    ** is the column index supplied by the user.
    */
    lZlEaido1C( et1lwN5i7d1==mchSDpdA+1 );
#ifdef nQFsjuWxNJhl0
    qP6Kf(Tqu4rVzcNe_L, twNz3, LjCAwc,
        fL57mslK4 | ((abmh_EN_FqT43>1 || GYsY7) ? 0 : xT0eun8),
        mchSDpdA
    );
    if( VBhb==Cix6kRDTk ){
      lZlEaido1C( abmh_EN_FqT43==0 && GYsY7==0 );
      K4_NK(Tqu4rVzcNe_L, SQDJxJtXv1czJ);
    }
    if( !er3GO2->wBeZQ3sjzlA3O ){
      si7Xp9l(Tqu4rVzcNe_L, BvAx6uJKKYDb, TA9P6O86hRfIf);
    }
#else
    if( abmh_EN_FqT43>1 || GYsY7 ){
      kE84_A5MPI(Tqu4rVzcNe_L, twNz3, LjCAwc, 0);
    }
#endif

    if( abmh_EN_FqT43 ){
      pDQl(er3GO2, BvAx6uJKKYDb, 0, mchSDpdA, vqlW_di7j1, GYsY7);
    }

    /* Insert the new index entries and the new record. */
    DUMx(
        er3GO2, BvAx6uJKKYDb, LjCAwc, WmMWe1q, mchSDpdA, Y8OO,
        fL57mslK4 | (VBhb==Cix6kRDTk ? SQDJxJtXv1czJ : 0),
        0, 0
    );

    /* Do any ON CASCADE, SET NULL or SET DEFAULT operations required to
    ** handle rows (possibly in other tables) that refer via a foreign key
    ** to the row just updated. */
    if( abmh_EN_FqT43 ){
      jX7K8va0E(er3GO2, BvAx6uJKKYDb, nRzeBk, AqSuN6rLak6v, vqlW_di7j1, GYsY7);
    }
  }

  /* Increment the row counter
  */
  if( mxiY7umcKR ){
    kE84_A5MPI(Tqu4rVzcNe_L, rgzWt0, mxiY7umcKR, 1);
  }

  if( I4MjU4 ){
    qXUPPiHOa(er3GO2, I4MjU4, EHCtrIqty, nRzeBk,
        MCzaRaTH62V, BvAx6uJKKYDb, AqSuN6rLak6v, GMqbKgv00oub, xH7J);
  }

  /* Repeat the above with the next record to be updated, until
  ** all record selected by the WHERE clause have been updated.
  */
  if( VBhb==Dh39Ske ){
    /* Nothing to do at end-of-loop for a single-pass */
  }else if( VBhb==Cix6kRDTk ){
    z4TpUM(Tqu4rVzcNe_L, xH7J);
    MgYgpv(r2sIl);
  }else{
    z4TpUM(Tqu4rVzcNe_L, xH7J);
    kE84_A5MPI(Tqu4rVzcNe_L, jKpiFCS0XkHiU, PF0LjDjU6N, xQ3AcUcqn); gBUuOCcZ0(Tqu4rVzcNe_L);
  }
  z4TpUM(Tqu4rVzcNe_L, Le9P_);

  /* Update the sqlite_sequence table by storing the content of the
  ** maximum rowid counter values recorded while inserting into
  ** autoincrement tables.
  */
  if( er3GO2->wBeZQ3sjzlA3O==0 && er3GO2->UiHcjxcXI==0 && Yd9t==0 ){
    ocZ1Uc3b8yciT(er3GO2);
  }

  /*
  ** Return the number of rows that were changed, if we are tracking
  ** that information.
  */
  if( mxiY7umcKR ){
    Fj7K6US(Tqu4rVzcNe_L, mxiY7umcKR, "rows updated");
  }

M4aST5loSbout:
  QOasfj(&e8SOlYXQdlR);
  jzfEx(WG1Q6F71KTpj, vqlW_di7j1); /* Also frees aRegIdx[] and aToOpen[] */
  fSEkPNN(WG1Q6F71KTpj, thvftlaY9K2Er);
  fFbPhLijd(WG1Q6F71KTpj, nRzeBk);
  dBzJemq(WG1Q6F71KTpj, a87EzByroTtw);
#if yHJGJ46hXCW(D4cOSBUH9xH)
  fFbPhLijd(WG1Q6F71KTpj, dhxRm);
  dBzJemq(WG1Q6F71KTpj, Jq37ek10dAC);
#endif
  return;
}
/* Make sure "isView" and other macros defined above are undefined. Otherwise
** they may interfere with compilation of other functions in this file
** (or in another file, if this file becomes part of the amalgamation).  */
#ifdef GC1A0vhFfObGG
 #undef GC1A0vhFfObGG
#endif
#ifdef I4MjU4
 #undef I4MjU4
#endif

#ifndef uwEiL
/*
** Generate code for an UPDATE of a virtual table.
**
** There are two possible strategies - the default and the special
** "onepass" strategy. Onepass is only used if the virtual table
** implementation indicates that pWhere may match at most one row.
**
** The default strategy is to create an ephemeral table that contains
** for each row to be changed:
**
**   (A)  The original rowid of that row.
**   (B)  The revised rowid for the row.
**   (C)  The content of every column in the row.
**
** Then loop through the contents of this ephemeral table executing a
** VUpdate for each row. When finished, drop the ephemeral table.
**
** The "onepass" strategy does not use an ephemeral table. Instead, it
** stores the same values (A, B and C above) in a register array and
** makes a single invocation of VUpdate.
*/
static void BUo4(
  bpe5rP2ReAl48 *er3GO2,       /* The parsing context */
  YXHw_ *JIKG0,       /* The virtual table to be modified */
  gd_2KBv1V *BvAx6uJKKYDb,         /* The virtual table */
  XNL0CTTc7o7h *nRzeBk,  /* The columns to change in the UPDATE statement */
  GA3mR5g0pzo *POGVp,        /* Expression used to recompute the rowid */
  int *vqlW_di7j1,          /* Mapping from columns of pTab to entries in pChanges */
  GA3mR5g0pzo *a87EzByroTtw,        /* WHERE clause of the UPDATE statement */
  int GMqbKgv00oub          /* ON CONFLICT strategy */
){
  BCD5GL *Tqu4rVzcNe_L = er3GO2->xsuX3y6gb;  /* Virtual machine under construction */
  int xCwwCglwLqKf;             /* Table holding the result of the SELECT */
  int pYhdBYyu;                    /* Loop counter */
  Z1TrQ *WG1Q6F71KTpj = er3GO2->WG1Q6F71KTpj; /* Database connection */
  const char *DpmCW = (const char*)vXhc8avQzIvZ(WG1Q6F71KTpj, BvAx6uJKKYDb);
  EvAn3KRZHa *r2sIl = 0;
  int CMwCMI3kqo = 2 + BvAx6uJKKYDb->cvxjc;      /* Number of arguments to VUpdate */
  int Hb_bk1sBr;                     /* First register in VUpdate arg array */
  int EGrWHr5GQ_z42;                     /* Register in which to assemble record */
  int A_2mMUWusUHf1;                   /* Register for ephemeral table rowid */
  int aDYEsR1i = JIKG0->cmay2IaHVGA9[0].KcrtZfPuMdym;  /* Cursor used for virtual table scan */
  int Rl_oIHRYwxvg[2];                  /* Unused arg for sqlite3WhereOkOnePass() */
  int VBhb;                   /* True to use onepass strategy */
  int noSH;                       /* Address of OP_OpenEphemeral */

  /* Allocate nArg registers in which to gather the arguments for VUpdate. Then
  ** create and open the ephemeral table in which the records created from
  ** these arguments will be temporarily stored. */
  lZlEaido1C( Tqu4rVzcNe_L );
  xCwwCglwLqKf = er3GO2->DzW_xD4J++;
  noSH= kE84_A5MPI(Tqu4rVzcNe_L, EkPXdsUX0c, xCwwCglwLqKf, CMwCMI3kqo);
  Hb_bk1sBr = er3GO2->RXv6 + 1;
  er3GO2->RXv6 += CMwCMI3kqo;
  if( JIKG0->VRSfv3ytWpjw>1 ){
    bpXPO *Pggk00vv5XCX = 0;
    GA3mR5g0pzo *tA0hhhSoPIqC;
    XNL0CTTc7o7h *cE615w3lN9i;
    if( YJ83(BvAx6uJKKYDb) ){
      if( POGVp ){
        tA0hhhSoPIqC = M8RyeT(WG1Q6F71KTpj, POGVp, 0);
      }else{
        tA0hhhSoPIqC = cYSjIJiJ(er3GO2, fFjy9MVjDpheb, 0, 0);
      }
    }else{
      XCV1 Jy8uJHwLq0xF;      /* PRIMARY KEY column */
      Pggk00vv5XCX = WuJN(BvAx6uJKKYDb);
      lZlEaido1C( Pggk00vv5XCX!=0 );
      lZlEaido1C( Pggk00vv5XCX->pq7vO0==1 );
      Jy8uJHwLq0xF = Pggk00vv5XCX->CgbDaAYw7NQKF[0];
      if( vqlW_di7j1[Jy8uJHwLq0xF]>=0 ){
        tA0hhhSoPIqC = M8RyeT(WG1Q6F71KTpj, nRzeBk->cmay2IaHVGA9[vqlW_di7j1[Jy8uJHwLq0xF]].pNnYNaSqZGNO, 0);
      }else{
        tA0hhhSoPIqC = IhTTR6PC(er3GO2, Jy8uJHwLq0xF);
      }
    }
    cE615w3lN9i = FEtvxYs(er3GO2, 0, tA0hhhSoPIqC);

    for(pYhdBYyu=0; pYhdBYyu<BvAx6uJKKYDb->cvxjc; pYhdBYyu++){
      if( vqlW_di7j1[pYhdBYyu]>=0 ){
        cE615w3lN9i = FEtvxYs(er3GO2, cE615w3lN9i,
          M8RyeT(WG1Q6F71KTpj, nRzeBk->cmay2IaHVGA9[vqlW_di7j1[pYhdBYyu]].pNnYNaSqZGNO, 0)
        );
      }else{
        GA3mR5g0pzo *WS8XC = IhTTR6PC(er3GO2, pYhdBYyu);
        if( WS8XC ) WS8XC->aN0FJWf = J4RImVpJz;
        cE615w3lN9i = FEtvxYs(er3GO2, cE615w3lN9i, WS8XC);
      }
    }

    qBar28i9(er3GO2, xCwwCglwLqKf, Pggk00vv5XCX, cE615w3lN9i, JIKG0, a87EzByroTtw, 0, 0);
    fFbPhLijd(WG1Q6F71KTpj, cE615w3lN9i);
    VBhb = YgcTsmsHMgDf;
  }else{
    EGrWHr5GQ_z42 = ++er3GO2->RXv6;
    A_2mMUWusUHf1 = ++er3GO2->RXv6;

    /* Start scanning the virtual table */
    r2sIl = wrXDUc_xFg(
        er3GO2, JIKG0, a87EzByroTtw, 0, 0, 0, PJMHkydfg, 0
    );
    if( r2sIl==0 ) return;

    /* Populate the argument registers. */
    for(pYhdBYyu=0; pYhdBYyu<BvAx6uJKKYDb->cvxjc; pYhdBYyu++){
      lZlEaido1C( (BvAx6uJKKYDb->PXCh1YPlYG8[pYhdBYyu].boa4gB7gRVw14 & RIOM)==0 );
      if( vqlW_di7j1[pYhdBYyu]>=0 ){
        B4KRrB0P8sSb(er3GO2, nRzeBk->cmay2IaHVGA9[vqlW_di7j1[pYhdBYyu]].pNnYNaSqZGNO, Hb_bk1sBr+2+pYhdBYyu);
      }else{
        qP6Kf(Tqu4rVzcNe_L, NKyYmW, aDYEsR1i, pYhdBYyu, Hb_bk1sBr+2+pYhdBYyu);
        K4_NK(Tqu4rVzcNe_L, J4RImVpJz);/* For sqlite3_vtab_nochange() */
      }
    }
    if( YJ83(BvAx6uJKKYDb) ){
      kE84_A5MPI(Tqu4rVzcNe_L, BJZHZZo9jhz, aDYEsR1i, Hb_bk1sBr);
      if( POGVp ){
        B4KRrB0P8sSb(er3GO2, POGVp, Hb_bk1sBr+1);
      }else{
        kE84_A5MPI(Tqu4rVzcNe_L, BJZHZZo9jhz, aDYEsR1i, Hb_bk1sBr+1);
      }
    }else{
      bpXPO *Pggk00vv5XCX;   /* PRIMARY KEY index */
      XCV1 Jy8uJHwLq0xF;      /* PRIMARY KEY column */
      Pggk00vv5XCX = WuJN(BvAx6uJKKYDb);
      lZlEaido1C( Pggk00vv5XCX!=0 );
      lZlEaido1C( Pggk00vv5XCX->pq7vO0==1 );
      Jy8uJHwLq0xF = Pggk00vv5XCX->CgbDaAYw7NQKF[0];
      qP6Kf(Tqu4rVzcNe_L, NKyYmW, aDYEsR1i, Jy8uJHwLq0xF, Hb_bk1sBr);
      kE84_A5MPI(Tqu4rVzcNe_L, J7WLN4, Hb_bk1sBr+2+Jy8uJHwLq0xF, Hb_bk1sBr+1);
    }

    VBhb = Hnk6TGrx9P2(r2sIl, Rl_oIHRYwxvg);

    /* There is no ONEPASS_MULTI on virtual tables */
    lZlEaido1C( VBhb==YgcTsmsHMgDf || VBhb==Dh39Ske );

    if( VBhb ){
      /* If using the onepass strategy, no-op out the OP_OpenEphemeral coded
      ** above. */
      W_8Dvks(Tqu4rVzcNe_L, noSH);
      iiGBdkW(Tqu4rVzcNe_L, lMMn2bhHUQ, aDYEsR1i);
    }else{
      /* Create a record from the argument register contents and insert it into
      ** the ephemeral table. */
      J3FyGBP(er3GO2);
      qP6Kf(Tqu4rVzcNe_L, ykvNm3Jxq69XX, Hb_bk1sBr, CMwCMI3kqo, EGrWHr5GQ_z42);
#if yHJGJ46hXCW(JShM0gr) && !yHJGJ46hXCW(dWiUxQm)
      /* Signal an assert() within OP_MakeRecord that it is allowed to
      ** accept no-change records with serial_type 10 */
      K4_NK(Tqu4rVzcNe_L, gqP0u2w32Ml);
#endif
      kE84_A5MPI(Tqu4rVzcNe_L, xqAm072QffT, xCwwCglwLqKf, A_2mMUWusUHf1);
      qP6Kf(Tqu4rVzcNe_L, QY3uN1P, xCwwCglwLqKf, EGrWHr5GQ_z42, A_2mMUWusUHf1);
    }
  }


  if( VBhb==YgcTsmsHMgDf ){
    /* End the virtual table scan */
    if( JIKG0->VRSfv3ytWpjw==1 ){
      MgYgpv(r2sIl);
    }

    /* Begin scanning through the ephemeral table. */
    noSH = iiGBdkW(Tqu4rVzcNe_L, L9tsd7YK, xCwwCglwLqKf); gBUuOCcZ0(Tqu4rVzcNe_L);

    /* Extract arguments from the current row of the ephemeral table and
    ** invoke the VUpdate method.  */
    for(pYhdBYyu=0; pYhdBYyu<CMwCMI3kqo; pYhdBYyu++){
      qP6Kf(Tqu4rVzcNe_L, qfCLm, xCwwCglwLqKf, pYhdBYyu, Hb_bk1sBr+pYhdBYyu);
    }
  }
  hzNHGoQ(er3GO2, BvAx6uJKKYDb);
  Ry234T(Tqu4rVzcNe_L, z4OWca, 0, CMwCMI3kqo, Hb_bk1sBr, DpmCW, pQOjXKa);
  K4_NK(Tqu4rVzcNe_L, GMqbKgv00oub==iJ7LQ ? yuaJ3 : GMqbKgv00oub);
  Y5uGzu0mOmib(er3GO2);

  /* End of the ephemeral table scan. Or, if using the onepass strategy,
  ** jump to here if the scan visited zero rows. */
  if( VBhb==YgcTsmsHMgDf ){
    kE84_A5MPI(Tqu4rVzcNe_L, jKpiFCS0XkHiU, xCwwCglwLqKf, noSH+1); gBUuOCcZ0(Tqu4rVzcNe_L);
    cbjjqxtoF4RGA(Tqu4rVzcNe_L, noSH);
    kE84_A5MPI(Tqu4rVzcNe_L, lMMn2bhHUQ, xCwwCglwLqKf, 0);
  }else{
    MgYgpv(r2sIl);
  }
}
#endif /* SQLITE_OMIT_VIRTUALTABLE */
