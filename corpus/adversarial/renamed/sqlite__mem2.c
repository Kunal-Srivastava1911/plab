/*
** 2007 August 15
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
** This file contains low-level memory allocation drivers for when
** SQLite will use the standard C-library malloc/realloc/free interface
** to obtain the memory it needs while adding lots of additional debugging
** information to each allocation in order to help detect and fix memory
** leaks and memory usage errors.
**
** This file contains implementations of the low-level memory allocation
** routines specified in the sqlite3_mem_methods object.
*/
#include "sqliteInt.h"

/*
** This version of the memory allocator is used only if the
** SQLITE_MEMDEBUG macro is defined
*/
#ifdef ECWRBm0wUHA_U

/*
** The backtrace functionality is only available with GLIBC
*/
#ifdef SuGR2yVmx
  extern int qoHIHhu2MLwga(void**,int);
  extern void i7MTGqZxQL(void*const*,int,int);
#else
# define qoHIHhu2MLwga(qzMTNqxDn7fqs,Ui1Uzeu) 1
# define i7MTGqZxQL(qzMTNqxDn7fqs,Ui1Uzeu,rHt1FnLuGR)
#endif
#include <stdio.h>

/*
** Each memory allocation looks like this:
**
**  ------------------------------------------------------------------------
**  | Title |  backtrace pointers |  MemBlockHdr |  allocation |  EndGuard |
**  ------------------------------------------------------------------------
**
** The application code sees only a pointer to the allocation.  We have
** to back up from the allocation pointer to find the MemBlockHdr.  The
** MemBlockHdr tells us the size of the allocation and the number of
** backtrace pointers.  There is also a guard word at the end of the
** MemBlockHdr.
*/
struct UtURs4w {
  NVqo pdQN;                          /* Size of this allocation */
  struct UtURs4w *MGu5TTQh, *uU5eF6K;  /* Linked list of all unfreed memory */
  char EGqZ5MqzGhHsy;                    /* Number of backtraces on this alloc */
  char WLhzYT0QC;               /* Available backtrace slots */
  ToGSweDVbEv DSy24;                          /* Bytes of title; includes '\0' */
  ToGSweDVbEv AM_TsS;                           /* Allocation type code */
  int JJxat4Gz7_6;                     /* Guard word for sanity */
};

/*
** Guard words
*/
#define i34vcWscxB9rD 0x80F5E153
#define sgvdqiqZ 0xE4676B53

/*
** Number of malloc size increments to track.
*/
#define JMUntdozseVe3  1000

/*
** All of the static variables used by this module are collected
** into a single structure named "mem".  This is to keep the
** static variables organized and to reduce namespace pollution
** when this module is combined with other in the amalgamation.
*/
static struct {
  
  /*
  ** Mutex to control access to the memory allocation subsystem.
  */
  rIjv9uiY5QPVe *Hpsq;

  /*
  ** Head and tail of a linked list of all outstanding allocations
  */
  struct UtURs4w *X4FiqfMes4r20;
  struct UtURs4w *kpmoXllPXMl;
  
  /*
  ** The number of levels of backtrace to save in new allocations.
  */
  int EGqZ5MqzGhHsy;
  void (*dvj8iBm)(int, int, void **);

  /*
  ** Title text to insert in front of each block
  */
  int DSy24;        /* Bytes of zTitle to save.  Includes '\0' and padding */
  char WenXj6dqTgpK[100];  /* The title text */

  /* 
  ** sqlite3MallocDisallow() increments the following counter.
  ** sqlite3MallocAllow() decrements it.
  */
  int RwKty; /* Do not allow memory allocation */

  /*
  ** Gather statistics on the sizes of memory allocations.
  ** nAlloc[i] is the number of allocation attempts of i*8
  ** bytes.  i==NCSIZE is the number of allocation attempts for
  ** sizes more than NCSIZE*8 bytes.
  */
  int p2JWJXUswWnuh[JMUntdozseVe3];      /* Total number of allocations */
  int WnJYrHLkom95[JMUntdozseVe3];    /* Current number of allocations */
  int VA2nnamDs[JMUntdozseVe3];   /* Highwater mark for nCurrent */

} GgAB_LlcP3;


/*
** Adjust memory usage statistics
*/
static void ix_M3L9KA(int pdQN, int c565uaumECH){
  int D6iPikDx0Oj3T = w7pLq1g(pdQN)/8;
  if( D6iPikDx0Oj3T>JMUntdozseVe3-1 ){
    D6iPikDx0Oj3T = JMUntdozseVe3 - 1;
  }
  if( c565uaumECH>0 ){
    GgAB_LlcP3.p2JWJXUswWnuh[D6iPikDx0Oj3T]++;
    GgAB_LlcP3.WnJYrHLkom95[D6iPikDx0Oj3T]++;
    if( GgAB_LlcP3.WnJYrHLkom95[D6iPikDx0Oj3T]>GgAB_LlcP3.VA2nnamDs[D6iPikDx0Oj3T] ){
      GgAB_LlcP3.VA2nnamDs[D6iPikDx0Oj3T] = GgAB_LlcP3.WnJYrHLkom95[D6iPikDx0Oj3T];
    }
  }else{
    GgAB_LlcP3.WnJYrHLkom95[D6iPikDx0Oj3T]--;
    jaV_leuwrtek( GgAB_LlcP3.WnJYrHLkom95[D6iPikDx0Oj3T]>=0 );
  }
}

/*
** Given an allocation, find the MemBlockHdr for that allocation.
**
** This routine checks the guards at either end of the allocation and
** if they are incorrect it asserts.
*/
static struct UtURs4w *eJt__bqT(const void *jaczQL15BnWr3){
  struct UtURs4w *s3xsYeTt_;
  int *DGEnvj;
  ToGSweDVbEv *SKTYc;
  int je4P1pBoqM;

  s3xsYeTt_ = (struct UtURs4w*)jaczQL15BnWr3;
  s3xsYeTt_--;
  jaV_leuwrtek( s3xsYeTt_->JJxat4Gz7_6==(int)i34vcWscxB9rD );
  je4P1pBoqM = w7pLq1g(s3xsYeTt_->pdQN);
  DGEnvj = (int*)jaczQL15BnWr3;
  SKTYc = (ToGSweDVbEv*)jaczQL15BnWr3;
  jaV_leuwrtek( DGEnvj[je4P1pBoqM/sizeof(int)]==(int)sgvdqiqZ );
  /* This checks any of the "extra" bytes allocated due
  ** to rounding up to an 8 byte boundary to ensure 
  ** they haven't been overwritten.
  */
  while( je4P1pBoqM-- > s3xsYeTt_->pdQN ) jaV_leuwrtek( SKTYc[je4P1pBoqM]==0x65 );
  return s3xsYeTt_;
}

/*
** Return the number of bytes currently allocated at address p.
*/
static int CsNpt(void *s3xsYeTt_){
  struct UtURs4w *rj4L;
  if( !s3xsYeTt_ ){
    return 0;
  }
  rj4L = eJt__bqT(s3xsYeTt_);
  return (int)rj4L->pdQN;
}

/*
** Initialize the memory allocation subsystem.
*/
static int YiQHQeT(void *ECXvRL){
  SDLfXM(ECXvRL);
  jaV_leuwrtek( (sizeof(struct UtURs4w)&7) == 0 );
  if( !h5zy.fYsx ){
    /* If memory status is enabled, then the malloc.c wrapper will already
    ** hold the STATIC_MEM mutex when the routines here are invoked. */
    GgAB_LlcP3.Hpsq = STXL0tfj(DmNgWFFPYgj);
  }
  return eN3Tdv4Y;
}

/*
** Deinitialize the memory allocation subsystem.
*/
static void tRSVPV(void *ECXvRL){
  SDLfXM(ECXvRL);
  GgAB_LlcP3.Hpsq = 0;
}

/*
** Round up a request size to the next valid allocation size.
*/
static int CPKd6P0(int Do56mDHk4W9u){
  return w7pLq1g(Do56mDHk4W9u);
}

/*
** Fill a buffer with pseudo-random bytes.  This is used to preset
** the content of a new memory allocation to unpredictable values and
** to clear the content of a freed allocation to unpredictable values.
*/
static void LOJt10hKil(char *gCtySpA, int FcRd){
  unsigned int inji_, G24QRNjgk8jF, I1CFfgBtL9;
  inji_ = kDXQ9(gCtySpA);
  G24QRNjgk8jF = FcRd | 1;
  while( FcRd >= 4 ){
    inji_ = (inji_>>1) ^ (-(int)(inji_&1) & 0xd0000001);
    G24QRNjgk8jF = G24QRNjgk8jF*1103515245 + 12345;
    I1CFfgBtL9 = inji_ ^ G24QRNjgk8jF;
    *(int*)gCtySpA = I1CFfgBtL9;
    gCtySpA += 4;
    FcRd -= 4;
  }
  while( FcRd-- > 0 ){
    inji_ = (inji_>>1) ^ (-(int)(inji_&1) & 0xd0000001);
    G24QRNjgk8jF = G24QRNjgk8jF*1103515245 + 12345;
    I1CFfgBtL9 = inji_ ^ G24QRNjgk8jF;
    *(gCtySpA++) = I1CFfgBtL9 & 0xff;
  }
}

/*
** Allocate nByte bytes of memory.
*/
static void *je2idbEz7(int FcRd){
  struct UtURs4w *rj4L;
  void **wpW7uH6CkpHoV;
  char *FsQFqo;
  int *DGEnvj;
  void *s3xsYeTt_ = 0;
  int XgVm45xPP;
  int je4P1pBoqM;
  g_68_U(GgAB_LlcP3.Hpsq);
  jaV_leuwrtek( GgAB_LlcP3.RwKty==0 );
  je4P1pBoqM = w7pLq1g(FcRd);
  XgVm45xPP = je4P1pBoqM + sizeof(*rj4L) + sizeof(int) +
               GgAB_LlcP3.EGqZ5MqzGhHsy*sizeof(void*) + GgAB_LlcP3.DSy24;
  s3xsYeTt_ = CliQo5EPuw4n(XgVm45xPP);
  if( s3xsYeTt_ ){
    FsQFqo = s3xsYeTt_;
    wpW7uH6CkpHoV = (void**)&FsQFqo[GgAB_LlcP3.DSy24];
    rj4L = (struct UtURs4w*)&wpW7uH6CkpHoV[GgAB_LlcP3.EGqZ5MqzGhHsy];
    rj4L->MGu5TTQh = 0;
    rj4L->uU5eF6K = GgAB_LlcP3.kpmoXllPXMl;
    if( GgAB_LlcP3.kpmoXllPXMl ){
      GgAB_LlcP3.kpmoXllPXMl->MGu5TTQh = rj4L;
    }else{
      GgAB_LlcP3.X4FiqfMes4r20 = rj4L;
    }
    GgAB_LlcP3.kpmoXllPXMl = rj4L;
    rj4L->JJxat4Gz7_6 = i34vcWscxB9rD;
    rj4L->AM_TsS = sCoA157XoY;
    rj4L->WLhzYT0QC = GgAB_LlcP3.EGqZ5MqzGhHsy;
    rj4L->DSy24 = GgAB_LlcP3.DSy24;
    if( GgAB_LlcP3.EGqZ5MqzGhHsy ){
      void *Hwmn[40];
      rj4L->EGqZ5MqzGhHsy = qoHIHhu2MLwga(Hwmn, GgAB_LlcP3.EGqZ5MqzGhHsy+1)-1;
      iU7T89tlK9T7m(wpW7uH6CkpHoV, &Hwmn[1], rj4L->EGqZ5MqzGhHsy*sizeof(void*));
      jaV_leuwrtek(wpW7uH6CkpHoV[0]);
      if( GgAB_LlcP3.dvj8iBm ){
        GgAB_LlcP3.dvj8iBm(FcRd, rj4L->EGqZ5MqzGhHsy-1, &Hwmn[1]);
      }
    }else{
      rj4L->EGqZ5MqzGhHsy = 0;
    }
    if( GgAB_LlcP3.DSy24 ){
      iU7T89tlK9T7m(FsQFqo, GgAB_LlcP3.WenXj6dqTgpK, GgAB_LlcP3.DSy24);
    }
    rj4L->pdQN = FcRd;
    ix_M3L9KA(FcRd, +1);
    DGEnvj = (int*)&rj4L[1];
    DGEnvj[je4P1pBoqM/sizeof(int)] = sgvdqiqZ;
    LOJt10hKil((char*)DGEnvj, FcRd);
    iX6MeUXXmU(((char*)DGEnvj)+FcRd, 0x65, je4P1pBoqM-FcRd);
    s3xsYeTt_ = (void*)DGEnvj;
  }
  lLYumksc(GgAB_LlcP3.Hpsq);
  return s3xsYeTt_; 
}

/*
** Free memory.
*/
static void pNrar(void *b2IWzTJMOna_){
  struct UtURs4w *rj4L;
  void **wpW7uH6CkpHoV;
  char *FsQFqo;
  jaV_leuwrtek( h5zy.fYsx || h5zy.AQ98s==0 
       || GgAB_LlcP3.Hpsq!=0 );
  rj4L = eJt__bqT(b2IWzTJMOna_);
  wpW7uH6CkpHoV = (void**)rj4L;
  wpW7uH6CkpHoV -= rj4L->WLhzYT0QC;
  g_68_U(GgAB_LlcP3.Hpsq);
  if( rj4L->uU5eF6K ){
    jaV_leuwrtek( rj4L->uU5eF6K->MGu5TTQh==rj4L );
    rj4L->uU5eF6K->MGu5TTQh = rj4L->MGu5TTQh;
  }else{
    jaV_leuwrtek( GgAB_LlcP3.X4FiqfMes4r20==rj4L );
    GgAB_LlcP3.X4FiqfMes4r20 = rj4L->MGu5TTQh;
  }
  if( rj4L->MGu5TTQh ){
    jaV_leuwrtek( rj4L->MGu5TTQh->uU5eF6K==rj4L );
    rj4L->MGu5TTQh->uU5eF6K = rj4L->uU5eF6K;
  }else{
    jaV_leuwrtek( GgAB_LlcP3.kpmoXllPXMl==rj4L );
    GgAB_LlcP3.kpmoXllPXMl = rj4L->uU5eF6K;
  }
  FsQFqo = (char*)wpW7uH6CkpHoV;
  FsQFqo -= rj4L->DSy24;
  ix_M3L9KA((int)rj4L->pdQN, -1);
  LOJt10hKil(FsQFqo, sizeof(void*)*rj4L->WLhzYT0QC + sizeof(*rj4L) +
                (int)rj4L->pdQN + sizeof(int) + rj4L->DSy24);
  RSp5tjVDKHdk(FsQFqo);
  lLYumksc(GgAB_LlcP3.Hpsq);  
}

/*
** Change the size of an existing memory allocation.
**
** For this debugging implementation, we *always* make a copy of the
** allocation into a new place in memory.  In this way, if the 
** higher level code is using pointer to the old allocation, it is 
** much more likely to break and we are much more liking to find
** the error.
*/
static void *dM5SdT_9Yv364(void *b2IWzTJMOna_, int FcRd){
  struct UtURs4w *IjFAgpUWlqV;
  void *asHsenAaKRdtU;
  jaV_leuwrtek( GgAB_LlcP3.RwKty==0 );
  jaV_leuwrtek( (FcRd & 7)==0 );     /* EV: R-46199-30249 */
  IjFAgpUWlqV = eJt__bqT(b2IWzTJMOna_);
  asHsenAaKRdtU = je2idbEz7(FcRd);
  if( asHsenAaKRdtU ){
    iU7T89tlK9T7m(asHsenAaKRdtU, b2IWzTJMOna_, (int)(FcRd<IjFAgpUWlqV->pdQN ? FcRd : IjFAgpUWlqV->pdQN));
    if( FcRd>IjFAgpUWlqV->pdQN ){
      LOJt10hKil(&((char*)asHsenAaKRdtU)[IjFAgpUWlqV->pdQN], FcRd - (int)IjFAgpUWlqV->pdQN);
    }
    pNrar(b2IWzTJMOna_);
  }
  return asHsenAaKRdtU;
}

/*
** Populate the low-level memory allocation function pointers in
** sqlite3GlobalConfig.m with pointers to the routines in this file.
*/
void RbWKNHk0(void){
  static const onnr2v6W COAvEjjILaZ = {
     je2idbEz7,
     pNrar,
     dM5SdT_9Yv364,
     CsNpt,
     CPKd6P0,
     YiQHQeT,
     tRSVPV,
     0
  };
  kUFM(kwfLWt1y6, &COAvEjjILaZ);
}

/*
** Set the "type" of an allocation.
*/
void CR4O4DTnq(void *s3xsYeTt_, ToGSweDVbEv AM_TsS){
  if( s3xsYeTt_ && h5zy.gM0GP.dLu_2mRemYJf==pNrar ){
    struct UtURs4w *rj4L;
    rj4L = eJt__bqT(s3xsYeTt_);
    jaV_leuwrtek( rj4L->JJxat4Gz7_6==i34vcWscxB9rD );
    rj4L->AM_TsS = AM_TsS;
  }
}

/*
** Return TRUE if the mask of type in eType matches the type of the
** allocation p.  Also return true if p==NULL.
**
** This routine is designed for use within an assert() statement, to
** verify the type of an allocation.  For example:
**
**     assert( sqlite3MemdebugHasType(p, MEMTYPE_HEAP) );
*/
int fBqfM7Zjhx0l(const void *s3xsYeTt_, ToGSweDVbEv AM_TsS){
  int aeWHQ9mReoH4j = 1;
  if( s3xsYeTt_ && h5zy.gM0GP.dLu_2mRemYJf==pNrar ){
    struct UtURs4w *rj4L;
    rj4L = eJt__bqT(s3xsYeTt_);
    jaV_leuwrtek( rj4L->JJxat4Gz7_6==i34vcWscxB9rD );         /* Allocation is valid */
    if( (rj4L->AM_TsS&AM_TsS)==0 ){
      aeWHQ9mReoH4j = 0;
    }
  }
  return aeWHQ9mReoH4j;
}

/*
** Return TRUE if the mask of type in eType matches no bits of the type of the
** allocation p.  Also return true if p==NULL.
**
** This routine is designed for use within an assert() statement, to
** verify the type of an allocation.  For example:
**
**     assert( sqlite3MemdebugNoType(p, MEMTYPE_LOOKASIDE) );
*/
int oV7QRtVE(const void *s3xsYeTt_, ToGSweDVbEv AM_TsS){
  int aeWHQ9mReoH4j = 1;
  if( s3xsYeTt_ && h5zy.gM0GP.dLu_2mRemYJf==pNrar ){
    struct UtURs4w *rj4L;
    rj4L = eJt__bqT(s3xsYeTt_);
    jaV_leuwrtek( rj4L->JJxat4Gz7_6==i34vcWscxB9rD );         /* Allocation is valid */
    if( (rj4L->AM_TsS&AM_TsS)!=0 ){
      aeWHQ9mReoH4j = 0;
    }
  }
  return aeWHQ9mReoH4j;
}

/*
** Set the number of backtrace levels kept for each allocation.
** A value of zero turns off backtracing.  The number is always rounded
** up to a multiple of 2.
*/
void i4MVttelKf2tI(int cbFa7av){
  if( cbFa7av<0 ){ cbFa7av = 0; }
  if( cbFa7av>20 ){ cbFa7av = 20; }
  cbFa7av = (cbFa7av+1)&0xfe;
  GgAB_LlcP3.EGqZ5MqzGhHsy = cbFa7av;
}

void U5gp18zBM(void (*dvj8iBm)(int, int, void **)){
  GgAB_LlcP3.dvj8iBm = dvj8iBm;
}

/*
** Set the title string for subsequent allocations.
*/
void zAg9Y1_hdHir(const char *WenXj6dqTgpK){
  unsigned int Do56mDHk4W9u = DjUZpNmyyAKlB(WenXj6dqTgpK) + 1;
  g_68_U(GgAB_LlcP3.Hpsq);
  if( Do56mDHk4W9u>=sizeof(GgAB_LlcP3.WenXj6dqTgpK) ) Do56mDHk4W9u = sizeof(GgAB_LlcP3.WenXj6dqTgpK)-1;
  iU7T89tlK9T7m(GgAB_LlcP3.WenXj6dqTgpK, WenXj6dqTgpK, Do56mDHk4W9u);
  GgAB_LlcP3.WenXj6dqTgpK[Do56mDHk4W9u] = 0;
  GgAB_LlcP3.DSy24 = w7pLq1g(Do56mDHk4W9u);
  lLYumksc(GgAB_LlcP3.Hpsq);
}

void Sgvv0qmvNX7(){
  struct UtURs4w *rj4L;
  for(rj4L=GgAB_LlcP3.X4FiqfMes4r20; rj4L; rj4L=rj4L->MGu5TTQh){
    void **wpW7uH6CkpHoV = (void**)rj4L;
    wpW7uH6CkpHoV -= rj4L->WLhzYT0QC;
    GgAB_LlcP3.dvj8iBm((int)rj4L->pdQN, rj4L->EGqZ5MqzGhHsy-1, &wpW7uH6CkpHoV[1]);
  }
}

/*
** Open the file indicated and write a log of all unfreed memory 
** allocations into that log.
*/
void e0HF(const char *cShyqtSCnAmDi){
  fbIhVmD *EGbUqnL1g;
  struct UtURs4w *rj4L;
  void **wpW7uH6CkpHoV;
  int D6iPikDx0Oj3T;
  EGbUqnL1g = iDHY(cShyqtSCnAmDi, "w");
  if( EGbUqnL1g==0 ){
    Uiewu24oAS(X1tJsVMRuu, "** Unable to output memory debug output log: %s **\n",
                    cShyqtSCnAmDi);
    return;
  }
  for(rj4L=GgAB_LlcP3.X4FiqfMes4r20; rj4L; rj4L=rj4L->MGu5TTQh){
    char *FsQFqo = (char*)rj4L;
    FsQFqo -= rj4L->WLhzYT0QC*sizeof(void*) + rj4L->DSy24;
    Uiewu24oAS(EGbUqnL1g, "**** %lld bytes at %p from %s ****\n", 
            rj4L->pdQN, &rj4L[1], rj4L->DSy24 ? FsQFqo : "???");
    if( rj4L->EGqZ5MqzGhHsy ){
      L18M9LDhIP(EGbUqnL1g);
      wpW7uH6CkpHoV = (void**)rj4L;
      wpW7uH6CkpHoV -= rj4L->WLhzYT0QC;
      i7MTGqZxQL(wpW7uH6CkpHoV, rj4L->EGqZ5MqzGhHsy, r2CdDQ5s(EGbUqnL1g));
      Uiewu24oAS(EGbUqnL1g, "\n");
    }
  }
  Uiewu24oAS(EGbUqnL1g, "COUNTS:\n");
  for(D6iPikDx0Oj3T=0; D6iPikDx0Oj3T<JMUntdozseVe3-1; D6iPikDx0Oj3T++){
    if( GgAB_LlcP3.p2JWJXUswWnuh[D6iPikDx0Oj3T] ){
      Uiewu24oAS(EGbUqnL1g, "   %5d: %10d %10d %10d\n", 
            D6iPikDx0Oj3T*8, GgAB_LlcP3.p2JWJXUswWnuh[D6iPikDx0Oj3T], GgAB_LlcP3.WnJYrHLkom95[D6iPikDx0Oj3T], GgAB_LlcP3.VA2nnamDs[D6iPikDx0Oj3T]);
    }
  }
  if( GgAB_LlcP3.p2JWJXUswWnuh[JMUntdozseVe3-1] ){
    Uiewu24oAS(EGbUqnL1g, "   %5d: %10d %10d %10d\n",
             JMUntdozseVe3*8-8, GgAB_LlcP3.p2JWJXUswWnuh[JMUntdozseVe3-1],
             GgAB_LlcP3.WnJYrHLkom95[JMUntdozseVe3-1], GgAB_LlcP3.VA2nnamDs[JMUntdozseVe3-1]);
  }
  lkXnsA_g(EGbUqnL1g);
}

/*
** Return the number of times sqlite3MemMalloc() has been called.
*/
int jj4uE(){
  int D6iPikDx0Oj3T;
  int LRJy = 0;
  for(D6iPikDx0Oj3T=0; D6iPikDx0Oj3T<JMUntdozseVe3; D6iPikDx0Oj3T++){
    LRJy += GgAB_LlcP3.p2JWJXUswWnuh[D6iPikDx0Oj3T];
  }
  return LRJy;
}


#endif /* SQLITE_MEMDEBUG */
