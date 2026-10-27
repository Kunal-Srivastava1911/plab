/*
** 2008 October 7
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
** This file contains code use to implement an in-memory rollback journal.
** The in-memory rollback journal is used to journal transactions for
** ":memory:" databases and when the journal_mode=MEMORY pragma is used.
**
** Update:  The in-memory journal is also used to temporarily cache
** smaller journals that are not critical for power-loss recovery.
** For example, statement journals that are not too big will be held
** entirely in memory, thus reducing the number of file I/O calls, and
** more importantly, reducing temporary file creation events.  If these
** journals become too large for memory, they are spilled to disk.  But
** in the common case, they are usually small and no file I/O needs to
** occur.
*/
#include "sqliteInt.h"

/* Forward references to internal structures */
typedef struct dTjS dTjS;
typedef struct Krqm9uxCCvhQ Krqm9uxCCvhQ;
typedef struct qzlwlZ7_IYDek qzlwlZ7_IYDek;

/*
** The rollback journal is composed of a linked list of these structures.
**
** The zChunk array is always at least 8 bytes in size - usually much more.
** Its actual size is stored in the MemJournal.nChunkSize variable.
*/
struct qzlwlZ7_IYDek {
  qzlwlZ7_IYDek *WE7aEnJmU;               /* Next chunk in the journal */
  sgJJ wBdR[8];                   /* Content of this chunk */
};

/*
** By default, allocate this many bytes of memory for each FileChunk object.
*/
#define gGp14NVv6WW 1024

/*
** For chunk size nChunkSize, return the number of bytes that should
** be allocated for each FileChunk structure.
*/
#define wZFSrrzSAUP(AVsUrK) (sizeof(qzlwlZ7_IYDek) + ((AVsUrK)-8))

/*
** An instance of this object serves as a cursor into the rollback journal.
** The cursor can be either for reading or writing.
*/
struct Krqm9uxCCvhQ {
  HOi7bge D9TKvZZG;          /* Offset from the beginning of the file */
  qzlwlZ7_IYDek *Z1_m;              /* Specific chunk into which cursor points */
};

/*
** This structure is a subclass of sqlite3_file. Each open memory-journal
** is an instance of this class.
*/
struct dTjS {
  const G6UnMeOeQxNS *RmsUO5; /* Parent class. MUST BE FIRST */
  int AVsUrK;                 /* In-memory chunk-size */

  int XN3mFyDfDWW;                     /* Bytes of data before flushing */
  qzlwlZ7_IYDek *mp0FN;              /* Head of in-memory chunk-list */
  Krqm9uxCCvhQ tRvQSyDL;             /* Pointer to the end of the file */
  Krqm9uxCCvhQ divwVTpT1;            /* Pointer to the end of the last xRead() */

  int M7fY75aJZhV;                      /* xOpen flags */
  OTcYnl1IZ_ *lrPR9;              /* The "real" underlying VFS */
  const char *TnTl0;           /* Name of the journal file */
};

/*
** Read data from the in-memory journal file.  This is the implementation
** of the sqlite3_vfs.xRead method.
*/
static int KKSD(
  FCNS70EsYojWf *ZsHl7CvTRyB0,    /* The journal file from which to read */
  void *uzCsG2X3tBgx,            /* Put the results here */
  int DYAN,              /* Number of bytes to read */
  wLBJ Xs8rCSYWQz     /* Begin reading at this offset */
){
  dTjS *QpyxWhwj7Lq = (dTjS *)ZsHl7CvTRyB0;
  sgJJ *CJrmzS0 = uzCsG2X3tBgx;
  int sG8Ahk = DYAN;
  int AKDl;
  qzlwlZ7_IYDek *Z1_m;

  if( (DYAN+Xs8rCSYWQz)>QpyxWhwj7Lq->tRvQSyDL.D9TKvZZG ){
    return BLfOu9rXmICwu;
  }
  F4Hwdp01RW7g( QpyxWhwj7Lq->divwVTpT1.D9TKvZZG==0 || QpyxWhwj7Lq->divwVTpT1.Z1_m!=0 );
  if( QpyxWhwj7Lq->divwVTpT1.D9TKvZZG!=Xs8rCSYWQz || Xs8rCSYWQz==0 ){
    HOi7bge HDvog4bYK = 0;
    for(Z1_m=QpyxWhwj7Lq->mp0FN; 
        iFMssV(Z1_m) && (HDvog4bYK+QpyxWhwj7Lq->AVsUrK)<=Xs8rCSYWQz;
        Z1_m=Z1_m->WE7aEnJmU
    ){
      HDvog4bYK += QpyxWhwj7Lq->AVsUrK;
    }
  }else{
    Z1_m = QpyxWhwj7Lq->divwVTpT1.Z1_m;
    F4Hwdp01RW7g( Z1_m!=0 );
  }

  AKDl = (int)(Xs8rCSYWQz%QpyxWhwj7Lq->AVsUrK);
  do {
    int qPIrgRDAy = QpyxWhwj7Lq->AVsUrK - AKDl;
    int Am4gF0o4FWZO = me1xDB(sG8Ahk, (QpyxWhwj7Lq->AVsUrK - AKDl));
    IjLot(CJrmzS0, (sgJJ*)Z1_m->wBdR + AKDl, Am4gF0o4FWZO);
    CJrmzS0 += Am4gF0o4FWZO;
    sG8Ahk -= qPIrgRDAy;
    AKDl = 0;
  } while( sG8Ahk>=0 && (Z1_m=Z1_m->WE7aEnJmU)!=0 && sG8Ahk>0 );
  QpyxWhwj7Lq->divwVTpT1.D9TKvZZG = Z1_m ? Xs8rCSYWQz+DYAN : 0;
  QpyxWhwj7Lq->divwVTpT1.Z1_m = Z1_m;

  return dGxf4afKSLmg;
}

/*
** Free the list of FileChunk structures headed at MemJournal.pFirst.
*/
static void Vl1W(qzlwlZ7_IYDek *mp0FN){
  qzlwlZ7_IYDek *ECrIXIGAB;
  qzlwlZ7_IYDek *WE7aEnJmU;
  for(ECrIXIGAB=mp0FN; ECrIXIGAB; ECrIXIGAB=WE7aEnJmU){
    WE7aEnJmU = ECrIXIGAB->WE7aEnJmU;
    GiGsKEP(ECrIXIGAB);
  } 
}

/*
** Flush the contents of memory to a real file on disk.
*/
static int zh0nj(dTjS *QpyxWhwj7Lq){
  int daBV9I;
  FCNS70EsYojWf *oDyESi78KTn = (FCNS70EsYojWf*)QpyxWhwj7Lq;
  dTjS T6mbOAfaQN1 = *QpyxWhwj7Lq;

  zlVI(QpyxWhwj7Lq, 0, sizeof(dTjS));
  daBV9I = OUi_qcl2CI9C(T6mbOAfaQN1.lrPR9, T6mbOAfaQN1.TnTl0, oDyESi78KTn, T6mbOAfaQN1.M7fY75aJZhV, 0);
  if( daBV9I==dGxf4afKSLmg ){
    int EYwz = T6mbOAfaQN1.AVsUrK;
    mQULQatS8QY HDvog4bYK = 0;
    qzlwlZ7_IYDek *ECrIXIGAB;
    for(ECrIXIGAB=T6mbOAfaQN1.mp0FN; ECrIXIGAB; ECrIXIGAB=ECrIXIGAB->WE7aEnJmU){
      if( HDvog4bYK + EYwz > T6mbOAfaQN1.tRvQSyDL.D9TKvZZG ){
        EYwz = T6mbOAfaQN1.tRvQSyDL.D9TKvZZG - HDvog4bYK;
      }
      daBV9I = AQubc(oDyESi78KTn, (sgJJ*)ECrIXIGAB->wBdR, EYwz, HDvog4bYK);
      if( daBV9I ) break;
      HDvog4bYK += EYwz;
    }
    if( daBV9I==dGxf4afKSLmg ){
      /* No error has occurred. Free the in-memory buffers. */
      Vl1W(T6mbOAfaQN1.mp0FN);
    }
  }
  if( daBV9I!=dGxf4afKSLmg ){
    /* If an error occurred while creating or writing to the file, restore
    ** the original before returning. This way, SQLite uses the in-memory
    ** journal data to roll back changes made to the internal page-cache
    ** before this function was called.  */
    LFUaiqKpH(oDyESi78KTn);
    *QpyxWhwj7Lq = T6mbOAfaQN1;
  }
  return daBV9I;
}


/* Forward reference */
static int bnXY(FCNS70EsYojWf *ZsHl7CvTRyB0, wLBJ I7Tt);

/*
** Write data to the file.
*/
static int oWsGlTca(
  FCNS70EsYojWf *ZsHl7CvTRyB0,    /* The journal file into which to write */
  const void *uzCsG2X3tBgx,      /* Take data to be written from here */
  int DYAN,              /* Number of bytes to write */
  wLBJ Xs8rCSYWQz     /* Begin writing at this offset into the file */
){
  dTjS *QpyxWhwj7Lq = (dTjS *)ZsHl7CvTRyB0;
  int nED7psJVg1Q = DYAN;
  sgJJ *NdLXP1hGAU = (sgJJ *)uzCsG2X3tBgx;

  /* If the file should be created now, create it and write the new data
  ** into the file on disk. */
  if( QpyxWhwj7Lq->XN3mFyDfDWW>0 && (DYAN+Xs8rCSYWQz)>QpyxWhwj7Lq->XN3mFyDfDWW ){
    int daBV9I = zh0nj(QpyxWhwj7Lq);
    if( daBV9I==dGxf4afKSLmg ){
      daBV9I = AQubc(ZsHl7CvTRyB0, uzCsG2X3tBgx, DYAN, Xs8rCSYWQz);
    }
    return daBV9I;
  }

  /* If the contents of this write should be stored in memory */
  else{
    /* An in-memory journal file should only ever be appended to. Random
    ** access writes are not required. The only exception to this is when
    ** the in-memory journal is being used by a connection using the
    ** atomic-write optimization. In this case the first 28 bytes of the
    ** journal file may be written as part of committing the transaction. */
    F4Hwdp01RW7g( Xs8rCSYWQz<=QpyxWhwj7Lq->tRvQSyDL.D9TKvZZG );
    if( Xs8rCSYWQz>0 && Xs8rCSYWQz!=QpyxWhwj7Lq->tRvQSyDL.D9TKvZZG ){
      bnXY(ZsHl7CvTRyB0, Xs8rCSYWQz);
    }
    if( Xs8rCSYWQz==0 && QpyxWhwj7Lq->mp0FN ){
      F4Hwdp01RW7g( QpyxWhwj7Lq->AVsUrK>DYAN );
      IjLot((sgJJ*)QpyxWhwj7Lq->mp0FN->wBdR, uzCsG2X3tBgx, DYAN);
    }else{
      while( nED7psJVg1Q>0 ){
        qzlwlZ7_IYDek *Z1_m = QpyxWhwj7Lq->tRvQSyDL.Z1_m;
        int AKDl = (int)(QpyxWhwj7Lq->tRvQSyDL.D9TKvZZG%QpyxWhwj7Lq->AVsUrK);
        int qPIrgRDAy = me1xDB(nED7psJVg1Q, QpyxWhwj7Lq->AVsUrK - AKDl);

        F4Hwdp01RW7g( Z1_m!=0 || AKDl==0 );
        if( AKDl==0 ){
          /* New chunk is required to extend the file. */
          qzlwlZ7_IYDek *nZP8vr6 = p5G_UkY(wZFSrrzSAUP(QpyxWhwj7Lq->AVsUrK));
          if( !nZP8vr6 ){
            return kaZSeLaIqHaO;
          }
          nZP8vr6->WE7aEnJmU = 0;
          if( Z1_m ){
            F4Hwdp01RW7g( QpyxWhwj7Lq->mp0FN );
            Z1_m->WE7aEnJmU = nZP8vr6;
          }else{
            F4Hwdp01RW7g( !QpyxWhwj7Lq->mp0FN );
            QpyxWhwj7Lq->mp0FN = nZP8vr6;
          }
          Z1_m = QpyxWhwj7Lq->tRvQSyDL.Z1_m = nZP8vr6;
        }

        F4Hwdp01RW7g( Z1_m!=0 );
        IjLot((sgJJ*)Z1_m->wBdR + AKDl, NdLXP1hGAU, qPIrgRDAy);
        NdLXP1hGAU += qPIrgRDAy;
        nED7psJVg1Q -= qPIrgRDAy;
        QpyxWhwj7Lq->tRvQSyDL.D9TKvZZG += qPIrgRDAy;
      }
    }
  }

  return dGxf4afKSLmg;
}

/*
** Truncate the in-memory file.
*/
static int bnXY(FCNS70EsYojWf *ZsHl7CvTRyB0, wLBJ I7Tt){
  dTjS *QpyxWhwj7Lq = (dTjS *)ZsHl7CvTRyB0;
  F4Hwdp01RW7g( QpyxWhwj7Lq->tRvQSyDL.Z1_m==0 || QpyxWhwj7Lq->tRvQSyDL.Z1_m->WE7aEnJmU==0 );
  if( I7Tt<QpyxWhwj7Lq->tRvQSyDL.D9TKvZZG ){
    qzlwlZ7_IYDek *ECrIXIGAB = 0;
    if( I7Tt==0 ){
      Vl1W(QpyxWhwj7Lq->mp0FN);
      QpyxWhwj7Lq->mp0FN = 0;
    }else{
      mQULQatS8QY HDvog4bYK = QpyxWhwj7Lq->AVsUrK;
      for(ECrIXIGAB=QpyxWhwj7Lq->mp0FN; iFMssV(ECrIXIGAB) && HDvog4bYK<I7Tt; ECrIXIGAB=ECrIXIGAB->WE7aEnJmU){
        HDvog4bYK += QpyxWhwj7Lq->AVsUrK;
      }
      if( iFMssV(ECrIXIGAB) ){
        Vl1W(ECrIXIGAB->WE7aEnJmU);
        ECrIXIGAB->WE7aEnJmU = 0;
      }
    }

    QpyxWhwj7Lq->tRvQSyDL.Z1_m = ECrIXIGAB;
    QpyxWhwj7Lq->tRvQSyDL.D9TKvZZG = I7Tt;
    QpyxWhwj7Lq->divwVTpT1.Z1_m = 0;
    QpyxWhwj7Lq->divwVTpT1.D9TKvZZG = 0;
  }
  return dGxf4afKSLmg;
}

/*
** Close the file.
*/
static int wNoPy4CD(FCNS70EsYojWf *ZsHl7CvTRyB0){
  dTjS *QpyxWhwj7Lq = (dTjS *)ZsHl7CvTRyB0;
  Vl1W(QpyxWhwj7Lq->mp0FN);
  return dGxf4afKSLmg;
}

/*
** Sync the file.
**
** If the real file has been created, call its xSync method. Otherwise, 
** syncing an in-memory journal is a no-op. 
*/
static int dWt7EHZUOuI(FCNS70EsYojWf *ZsHl7CvTRyB0, int M7fY75aJZhV){
  kg7Mq(ZsHl7CvTRyB0, M7fY75aJZhV);
  return dGxf4afKSLmg;
}

/*
** Query the size of the file in bytes.
*/
static int sA08rW2zShaFe(FCNS70EsYojWf *ZsHl7CvTRyB0, wLBJ *pg8Zj){
  dTjS *QpyxWhwj7Lq = (dTjS *)ZsHl7CvTRyB0;
  *pg8Zj = (wLBJ) QpyxWhwj7Lq->tRvQSyDL.D9TKvZZG;
  return dGxf4afKSLmg;
}

/*
** Table of methods for MemJournal sqlite3_file object.
*/
static const struct G6UnMeOeQxNS WEYRpPod = {
  1,                /* iVersion */
  wNoPy4CD,     /* xClose */
  KKSD,      /* xRead */
  oWsGlTca,     /* xWrite */
  bnXY,  /* xTruncate */
  dWt7EHZUOuI,      /* xSync */
  sA08rW2zShaFe,  /* xFileSize */
  0,                /* xLock */
  0,                /* xUnlock */
  0,                /* xCheckReservedLock */
  0,                /* xFileControl */
  0,                /* xSectorSize */
  0,                /* xDeviceCharacteristics */
  0,                /* xShmMap */
  0,                /* xShmLock */
  0,                /* xShmBarrier */
  0,                /* xShmUnmap */
  0,                /* xFetch */
  0                 /* xUnfetch */
};

/* 
** Open a journal file. 
**
** The behaviour of the journal file depends on the value of parameter 
** nSpill. If nSpill is 0, then the journal file is always create and 
** accessed using the underlying VFS. If nSpill is less than zero, then
** all content is always stored in main-memory. Finally, if nSpill is a
** positive value, then the journal file is initially created in-memory
** but may be flushed to disk later on. In this case the journal file is
** flushed to disk either when it grows larger than nSpill bytes in size,
** or when sqlite3JournalCreate() is called.
*/
int xDEzTQJfzGbU2(
  OTcYnl1IZ_ *lrPR9,         /* The VFS to use for actual file I/O */
  const char *iIq8iejdTgvTL,         /* Name of the journal file */
  FCNS70EsYojWf *ZsHl7CvTRyB0,        /* Preallocated, blank file handle */
  int M7fY75aJZhV,                 /* Opening flags */
  int XN3mFyDfDWW                 /* Bytes buffered before opening the file */
){
  dTjS *QpyxWhwj7Lq = (dTjS*)ZsHl7CvTRyB0;

  F4Hwdp01RW7g( iIq8iejdTgvTL || XN3mFyDfDWW<0 || (M7fY75aJZhV & oIuFS73rc) );

  /* Zero the file-handle object. If nSpill was passed zero, initialize
  ** it using the sqlite3OsOpen() function of the underlying VFS. In this
  ** case none of the code in this module is executed as a result of calls
  ** made on the journal file-handle.  */
  zlVI(QpyxWhwj7Lq, 0, sizeof(dTjS));
  if( XN3mFyDfDWW==0 ){
    return OUi_qcl2CI9C(lrPR9, iIq8iejdTgvTL, ZsHl7CvTRyB0, M7fY75aJZhV, 0);
  }

  if( XN3mFyDfDWW>0 ){
    QpyxWhwj7Lq->AVsUrK = XN3mFyDfDWW;
  }else{
    QpyxWhwj7Lq->AVsUrK = 8 + gGp14NVv6WW - sizeof(qzlwlZ7_IYDek);
    F4Hwdp01RW7g( gGp14NVv6WW==wZFSrrzSAUP(QpyxWhwj7Lq->AVsUrK) );
  }

  ZsHl7CvTRyB0->aaWPb = (const G6UnMeOeQxNS*)&WEYRpPod;
  QpyxWhwj7Lq->XN3mFyDfDWW = XN3mFyDfDWW;
  QpyxWhwj7Lq->M7fY75aJZhV = M7fY75aJZhV;
  QpyxWhwj7Lq->TnTl0 = iIq8iejdTgvTL;
  QpyxWhwj7Lq->lrPR9 = lrPR9;
  return dGxf4afKSLmg;
}

/*
** Open an in-memory journal file.
*/
void Refb7(FCNS70EsYojWf *ZsHl7CvTRyB0){
  xDEzTQJfzGbU2(0, 0, ZsHl7CvTRyB0, 0, -1);
}

#if s2h3jvtiuka(XQ2p6hO_ogFuY) \
 || s2h3jvtiuka(knoD1)
/*
** If the argument p points to a MemJournal structure that is not an 
** in-memory-only journal file (i.e. is one that was opened with a +ve
** nSpill parameter or as SQLITE_OPEN_MAIN_JOURNAL), and the underlying 
** file has not yet been created, create it now.
*/
int t9wFMSL(FCNS70EsYojWf *ZsHl7CvTRyB0){
  int daBV9I = dGxf4afKSLmg;
  dTjS *QpyxWhwj7Lq = (dTjS*)ZsHl7CvTRyB0;
  if( ZsHl7CvTRyB0->aaWPb==&WEYRpPod && (
#ifdef XQ2p6hO_ogFuY
     QpyxWhwj7Lq->XN3mFyDfDWW>0
#else
     /* While this appears to not be possible without ATOMIC_WRITE, the
     ** paths are complex, so it seems prudent to leave the test in as
     ** a NEVER(), in case our analysis is subtly flawed. */
     HOUXKV7k5BSn(QpyxWhwj7Lq->XN3mFyDfDWW>0)
#endif
#ifdef knoD1
     || (QpyxWhwj7Lq->M7fY75aJZhV & uRrOvqzT6sOlA)
#endif
  )){
    daBV9I = zh0nj(QpyxWhwj7Lq);
  }
  return daBV9I;
}
#endif

/*
** The file-handle passed as the only argument is open on a journal file.
** Return true if this "journal file" is currently stored in heap memory,
** or false otherwise.
*/
int UEz_(FCNS70EsYojWf *QpyxWhwj7Lq){
  return QpyxWhwj7Lq->aaWPb==&WEYRpPod;
}

/* 
** Return the number of bytes required to store a JournalFile that uses vfs
** pVfs to create the underlying on-disk files.
*/
int JNbQ(OTcYnl1IZ_ *lrPR9){
  return t8lmsnoKyvP1m(lrPR9->VatX, (int)sizeof(dTjS));
}
