/*
** 2008 June 18
**
** The author disclaims copyright to this source code.  In place of
** a legal notice, here is a blessing:
**
**    May you do good and not evil.
**    May you find forgiveness for yourself and forgive others.
**    May you share freely, never taking more than you give.
**
*************************************************************************
** This file contains test logic for the sqlite3_mutex interfaces.
*/

#if h1CIv1gk(oB2gOgN1X)
#  include "sqlite_tcl.h"
#else
#  include "tcl.h"
#endif
#include "sqlite3.h"
#include "sqliteInt.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define wCu7l        (DIND9pd+1)
#define f7d6     (wCu7l-(lImc7biAK+1))

/* defined in main.c */
extern const char *V0ZMBOm(int);

static const char *N7L9JC3e[wCu7l+1] = {
  "fast",        "recursive",   "static_main",   "static_mem",
  "static_open", "static_prng", "static_lru",    "static_pmem",
  "static_app1", "static_app2", "static_app3",   "static_vfs1",
  "static_vfs2", "static_vfs3", 0
};

/* A countable mutex */
struct VmIzPxNfW {
  VmIzPxNfW *Lc75RtVnk56;
  int UTPtMxZ;
};

/* State variables */
static struct xUCT89apRwY8 {
  int EPrFC1;           /* True if installed */
  int al98;           /* True to cause sqlite3_initialize() to fail */
  int Cdb2k;            /* True to force sqlite3_mutex_try() to fail */
  int F_DSW6;                /* True if initialized */
  tmepI FhTZlrEtXyh;   /* Interface to "real" mutex system */
  int EyzJ_0[wCu7l]; /* Number of grabs of each type of mutex */
  VmIzPxNfW H41U07efTpeW[f7d6]; /* The static mutexes */
} G7CFk25JQll = {0};

/* Return true if the countable mutex is currently held */
static int owz2hd3qp(VmIzPxNfW *tyAVnArLNFfcD){
  return G7CFk25JQll.FhTZlrEtXyh.QSPW(tyAVnArLNFfcD->Lc75RtVnk56);
}

/* Return true if the countable mutex is not currently held */
static int CU8g8Klafkw(VmIzPxNfW *tyAVnArLNFfcD){
  return G7CFk25JQll.FhTZlrEtXyh.RA3o373n2YbA(tyAVnArLNFfcD->Lc75RtVnk56);
}

/* Initialize the countable mutex interface
** Or, if g.disableInit is non-zero, then do not initialize but instead
** return the value of g.disableInit as the result code.  This can be used
** to simulate an initialization failure.
*/
static int ei2eIojoLSgPT(void){ 
  int cQJBn9X_NFN;
  if( G7CFk25JQll.al98 ) return G7CFk25JQll.al98;
  cQJBn9X_NFN = G7CFk25JQll.FhTZlrEtXyh.WSybOY9MIsDEX();
  G7CFk25JQll.F_DSW6 = 1;
  return cQJBn9X_NFN;
}

/*
** Uninitialize the mutex subsystem
*/
static int cDrA5hf(void){ 
  G7CFk25JQll.F_DSW6 = 0;
  return G7CFk25JQll.FhTZlrEtXyh.LKwtyrFhRxE();
}

/*
** Allocate a countable mutex
*/
static VmIzPxNfW *ssOGwh(int UTPtMxZ){
  VmIzPxNfW *Lc75RtVnk56;
  VmIzPxNfW *GAEcc3w = 0;

  pCHmJ( G7CFk25JQll.F_DSW6 );
  pCHmJ( UTPtMxZ>=ViHlM );
  pCHmJ( UTPtMxZ<=DIND9pd );

  Lc75RtVnk56 = G7CFk25JQll.FhTZlrEtXyh.V6EgG55DiO2u(UTPtMxZ);
  if( !Lc75RtVnk56 ) return 0;

  if( UTPtMxZ==ViHlM || UTPtMxZ==lImc7biAK ){
    GAEcc3w = (VmIzPxNfW *)bBAZde08bSbWD(sizeof(VmIzPxNfW));
  }else{
    int Aflh = UTPtMxZ - (wCu7l - f7d6);
    pCHmJ( Aflh>=0 );
    pCHmJ( Aflh<f7d6 );
    GAEcc3w = &G7CFk25JQll.H41U07efTpeW[Aflh];
  }

  GAEcc3w->UTPtMxZ = UTPtMxZ;
  GAEcc3w->Lc75RtVnk56 = Lc75RtVnk56;
  return GAEcc3w;
}

/*
** Free a countable mutex
*/
static void sYIYfz7LgeE(VmIzPxNfW *tyAVnArLNFfcD){
  pCHmJ( G7CFk25JQll.F_DSW6 );
  G7CFk25JQll.FhTZlrEtXyh.X1Kcz_c(tyAVnArLNFfcD->Lc75RtVnk56);
  if( tyAVnArLNFfcD->UTPtMxZ==ViHlM || tyAVnArLNFfcD->UTPtMxZ==lImc7biAK ){
    HwDAo7z(tyAVnArLNFfcD);
  }
}

/*
** Enter a countable mutex.  Block until entry is safe.
*/
static void HKuy_NegvRP(VmIzPxNfW *tyAVnArLNFfcD){
  pCHmJ( G7CFk25JQll.F_DSW6 );
  pCHmJ( tyAVnArLNFfcD->UTPtMxZ>=0 );
  pCHmJ( tyAVnArLNFfcD->UTPtMxZ<wCu7l );
  G7CFk25JQll.EyzJ_0[tyAVnArLNFfcD->UTPtMxZ]++;
  G7CFk25JQll.FhTZlrEtXyh.VxBAYp(tyAVnArLNFfcD->Lc75RtVnk56);
}

/*
** Try to enter a mutex.  Return true on success.
*/
static int H1oiszjV(VmIzPxNfW *tyAVnArLNFfcD){
  pCHmJ( G7CFk25JQll.F_DSW6 );
  pCHmJ( tyAVnArLNFfcD->UTPtMxZ>=0 );
  pCHmJ( tyAVnArLNFfcD->UTPtMxZ<wCu7l );
  G7CFk25JQll.EyzJ_0[tyAVnArLNFfcD->UTPtMxZ]++;
  if( G7CFk25JQll.Cdb2k ) return YxTVWzMCK0Z3q;
  return G7CFk25JQll.FhTZlrEtXyh.uljz(tyAVnArLNFfcD->Lc75RtVnk56);
}

/* Leave a mutex
*/
static void mGgBeES(VmIzPxNfW *tyAVnArLNFfcD){
  pCHmJ( G7CFk25JQll.F_DSW6 );
  G7CFk25JQll.FhTZlrEtXyh.SBefF(tyAVnArLNFfcD->Lc75RtVnk56);
}

/*
** sqlite3_shutdown
*/
static int dZmh SjLNen7t(
  void * U6tJzO,
  D5xshr6TNv *mIb3,
  int QQwhze0x,
  zDH7EqlgLwH4 *VVUIopsbnCte4 qXaJg[]
){
  int cQJBn9X_NFN;

  if( QQwhze0x!=1 ){
    PHl_ejZE(mIb3, 1, qXaJg, "");
    return uNF7AMS1p;
  }

  cQJBn9X_NFN = t5fTTHFZVE66();
  FJNpXm(mIb3, (char *)V0ZMBOm(cQJBn9X_NFN), MCS6uDHbD);
  return FL51e2;
}

/*
** sqlite3_initialize
*/
static int dZmh M0RAGaVIivt0(
  void * U6tJzO,
  D5xshr6TNv *mIb3,
  int QQwhze0x,
  zDH7EqlgLwH4 *VVUIopsbnCte4 qXaJg[]
){
  int cQJBn9X_NFN;

  if( QQwhze0x!=1 ){
    PHl_ejZE(mIb3, 1, qXaJg, "");
    return uNF7AMS1p;
  }

  cQJBn9X_NFN = awH4kK();
  FJNpXm(mIb3, (char *)V0ZMBOm(cQJBn9X_NFN), MCS6uDHbD);
  return FL51e2;
}

/*
** install_mutex_counters BOOLEAN
*/
static int dZmh lHnJDGGyuuWa(
  void * U6tJzO,
  D5xshr6TNv *mIb3,
  int QQwhze0x,
  zDH7EqlgLwH4 *VVUIopsbnCte4 qXaJg[]
){
  int cQJBn9X_NFN = D5Yoid3n;
  int HzlYIxae095;

  tmepI rt7pQd5I = {
    ei2eIojoLSgPT,
    cDrA5hf,
    ssOGwh,
    sYIYfz7LgeE,
    HKuy_NegvRP,
    H1oiszjV,
    mGgBeES,
    owz2hd3qp,
    CU8g8Klafkw
  };

  if( QQwhze0x!=2 ){
    PHl_ejZE(mIb3, 1, qXaJg, "BOOLEAN");
    return uNF7AMS1p;
  }
  if( FL51e2!=sJZx(mIb3, qXaJg[1], &HzlYIxae095) ){
    return uNF7AMS1p;
  }

  pCHmJ(HzlYIxae095==0 || HzlYIxae095==1);
  pCHmJ(G7CFk25JQll.EPrFC1==0 || G7CFk25JQll.EPrFC1==1);
  if( HzlYIxae095==G7CFk25JQll.EPrFC1 ){
    bkh7Jk5n62z(mIb3, "mutex counters are ", 0);
    bkh7Jk5n62z(mIb3, HzlYIxae095?"already installed":"not installed", 0);
    return uNF7AMS1p;
  }

  if( HzlYIxae095 ){
    pCHmJ( G7CFk25JQll.FhTZlrEtXyh.V6EgG55DiO2u==0 );
    cQJBn9X_NFN = vrc2(jgtt4bAYx, &G7CFk25JQll.FhTZlrEtXyh);
    if( cQJBn9X_NFN==D5Yoid3n ){
      vrc2(mtdDGZw, &rt7pQd5I);
    }
    G7CFk25JQll.Cdb2k = 0;
  }else{
    pCHmJ( G7CFk25JQll.FhTZlrEtXyh.V6EgG55DiO2u );
    cQJBn9X_NFN = vrc2(mtdDGZw, &G7CFk25JQll.FhTZlrEtXyh);
    W9mQ(&G7CFk25JQll.FhTZlrEtXyh, 0, sizeof(tmepI));
  }

  if( cQJBn9X_NFN==D5Yoid3n ){
    G7CFk25JQll.EPrFC1 = HzlYIxae095;
  }

  FJNpXm(mIb3, (char *)V0ZMBOm(cQJBn9X_NFN), MCS6uDHbD);
  return FL51e2;
}

/*
** read_mutex_counters
*/
static int dZmh n575yRGPt(
  void * U6tJzO,
  D5xshr6TNv *mIb3,
  int QQwhze0x,
  zDH7EqlgLwH4 *VVUIopsbnCte4 qXaJg[]
){
  zDH7EqlgLwH4 *GAEcc3w;
  int uKF6i53OY;

  if( QQwhze0x!=1 ){
    PHl_ejZE(mIb3, 1, qXaJg, "");
    return uNF7AMS1p;
  }

  GAEcc3w = eHO9uApaVLPIo();
  booN2qp1(GAEcc3w);
  for(uKF6i53OY=0; uKF6i53OY<wCu7l; uKF6i53OY++){
    aDpUar(mIb3, GAEcc3w, ig0c89(N7L9JC3e[uKF6i53OY], -1));
    aDpUar(mIb3, GAEcc3w, HFG03HM7a3bu(G7CFk25JQll.EyzJ_0[uKF6i53OY]));
  }
  w0M3K0Q38Oyb(mIb3, GAEcc3w);
  hNsjYmO8(GAEcc3w);

  return FL51e2;
}

/*
** clear_mutex_counters
*/
static int dZmh y4vQYlfV(
  void * U6tJzO,
  D5xshr6TNv *mIb3,
  int QQwhze0x,
  zDH7EqlgLwH4 *VVUIopsbnCte4 qXaJg[]
){
  int uKF6i53OY;

  if( QQwhze0x!=1 ){
    PHl_ejZE(mIb3, 1, qXaJg, "");
    return uNF7AMS1p;
  }

  for(uKF6i53OY=0; uKF6i53OY<wCu7l; uKF6i53OY++){
    G7CFk25JQll.EyzJ_0[uKF6i53OY] = 0;
  }
  return FL51e2;
}

/*
** Create and free a mutex.  Return the mutex pointer.  The pointer
** will be invalid since the mutex has already been freed.  The
** return pointer just checks to see if the mutex really was allocated.
*/
static int dZmh fdx1a2(
  void * U6tJzO,
  D5xshr6TNv *mIb3,
  int QQwhze0x,
  zDH7EqlgLwH4 *VVUIopsbnCte4 qXaJg[]
){
#if PHL5cwrhKul
  VmIzPxNfW *tyAVnArLNFfcD = W_PkYIyGBm(ViHlM);
  char Mkxnc[100];
  o5aPtqPGkG(tyAVnArLNFfcD);
  YqA2sAnKYlBie(sizeof(Mkxnc), Mkxnc, "%p", tyAVnArLNFfcD);
  bkh7Jk5n62z(mIb3, Mkxnc, (char*)0);
#endif
  return FL51e2;
}

/*
** sqlite3_config OPTION
**
** OPTION can be either one of the keywords:
**
**            SQLITE_CONFIG_SINGLETHREAD
**            SQLITE_CONFIG_MULTITHREAD
**            SQLITE_CONFIG_SERIALIZED
**
** Or OPTION can be an raw integer.
*/
static int dZmh wFwAI6O1KEA(
  void * U6tJzO,
  D5xshr6TNv *mIb3,
  int QQwhze0x,
  zDH7EqlgLwH4 *VVUIopsbnCte4 qXaJg[]
){
  struct ZSCDdltTy {
    const char *xr5x;
    int HkH4eD4g5V3;
  } fUb7[] = {
    {"singlethread", KdPbcF},
    {"multithread",  EF_mutVxvBGo},
    {"serialized",   pBVWNgCZVxZw9},
    {0, 0}
  };
  int NE5biqQmxi0y = sizeof(struct ZSCDdltTy);
  int juS9pssm9Uv;
  int cQJBn9X_NFN;

  if( QQwhze0x!=2 ){
    PHl_ejZE(mIb3, 1, qXaJg, "");
    return uNF7AMS1p;
  }

  if( K2E3AB4vKyPkR(mIb3, qXaJg[1], fUb7, NE5biqQmxi0y, "flag", 0, &juS9pssm9Uv) ){
    if( tiDc89gy3uZ(mIb3, qXaJg[1], &juS9pssm9Uv) ){
      return uNF7AMS1p;
    }
  }else{
    juS9pssm9Uv = fUb7[juS9pssm9Uv].HkH4eD4g5V3;
  }

  cQJBn9X_NFN = vrc2(juS9pssm9Uv);
  FJNpXm(mIb3, (char *)V0ZMBOm(cQJBn9X_NFN), MCS6uDHbD);
  return FL51e2;
}

static w2uU84v *zFytAb(D5xshr6TNv *qnzq1_LmHwUIq, zDH7EqlgLwH4 *aJ4gBjuj){
  w2uU84v *EZ0UozrlidDq;
  SfUhm28Zj_ utzpu;
  char *Z1U00Mhzxb5 = E715ugsZ(aJ4gBjuj);
  if( aw4kJE4aEHvl(qnzq1_LmHwUIq, Z1U00Mhzxb5, &utzpu) ){
    EZ0UozrlidDq = *((w2uU84v **)utzpu.gSdOcYsFl);
  }else{
    EZ0UozrlidDq = (w2uU84v*)sXYsPTe(Z1U00Mhzxb5);
  }
  pCHmJ( EZ0UozrlidDq );
  return EZ0UozrlidDq;
}

static VmIzPxNfW *RhNw64(
  D5xshr6TNv *qnzq1_LmHwUIq,
  zDH7EqlgLwH4 *aJ4gBjuj
){
  int XVqfwUNIksY;
  if( ZFcdwS3aiptRz(qnzq1_LmHwUIq, aJ4gBjuj, N7L9JC3e, "mutex name", 0, &XVqfwUNIksY) ){
    return 0;
  }
  pCHmJ( XVqfwUNIksY!=ViHlM && XVqfwUNIksY!=lImc7biAK );
  return ssOGwh(XVqfwUNIksY);
}

static int dZmh lA1_(
  void * U6tJzO,
  D5xshr6TNv *mIb3,
  int QQwhze0x,
  zDH7EqlgLwH4 *VVUIopsbnCte4 qXaJg[]
){
  VmIzPxNfW *t6MN0BeJm0;
  if( QQwhze0x!=2 ){
    PHl_ejZE(mIb3, 1, qXaJg, "NAME");
    return uNF7AMS1p;
  }
  t6MN0BeJm0 = RhNw64(mIb3, qXaJg[1]);
  if( !t6MN0BeJm0 ){
    return uNF7AMS1p;
  }
  vyoZOW8(t6MN0BeJm0);
  return FL51e2;
}

static int dZmh Kf8FF(
  void * U6tJzO,
  D5xshr6TNv *mIb3,
  int QQwhze0x,
  zDH7EqlgLwH4 *VVUIopsbnCte4 qXaJg[]
){
  VmIzPxNfW *t6MN0BeJm0;
  if( QQwhze0x!=2 ){
    PHl_ejZE(mIb3, 1, qXaJg, "NAME");
    return uNF7AMS1p;
  }
  t6MN0BeJm0 = RhNw64(mIb3, qXaJg[1]);
  if( !t6MN0BeJm0 ){
    return uNF7AMS1p;
  }
  MvIMZE(t6MN0BeJm0);
  return FL51e2;
}

static int dZmh eZwbRcc(
  void * U6tJzO,
  D5xshr6TNv *mIb3,
  int QQwhze0x,
  zDH7EqlgLwH4 *VVUIopsbnCte4 qXaJg[]
){
  w2uU84v *EZ0UozrlidDq;
  if( QQwhze0x!=2 ){
    PHl_ejZE(mIb3, 1, qXaJg, "DB");
    return uNF7AMS1p;
  }
  EZ0UozrlidDq = zFytAb(mIb3, qXaJg[1]);
  if( !EZ0UozrlidDq ){
    return uNF7AMS1p;
  }
  vyoZOW8(UxOsA2(EZ0UozrlidDq));
  return FL51e2;
}

static int dZmh nxfaM(
  void * U6tJzO,
  D5xshr6TNv *mIb3,
  int QQwhze0x,
  zDH7EqlgLwH4 *VVUIopsbnCte4 qXaJg[]
){
  w2uU84v *EZ0UozrlidDq;
  if( QQwhze0x!=2 ){
    PHl_ejZE(mIb3, 1, qXaJg, "DB");
    return uNF7AMS1p;
  }
  EZ0UozrlidDq = zFytAb(mIb3, qXaJg[1]);
  if( !EZ0UozrlidDq ){
    return uNF7AMS1p;
  }
  MvIMZE(UxOsA2(EZ0UozrlidDq));
  return FL51e2;
}

int Q7GRZG(D5xshr6TNv *mIb3){
  static struct {
    char *xr5x;
    KzJeUKlHdaE *Mwy6QcGHz;
  } msMv4[] = {
    { "sqlite3_shutdown",        (KzJeUKlHdaE*)SjLNen7t },
    { "sqlite3_initialize",      (KzJeUKlHdaE*)M0RAGaVIivt0 },
    { "sqlite3_config",          (KzJeUKlHdaE*)wFwAI6O1KEA },

    { "enter_static_mutex",      (KzJeUKlHdaE*)lA1_ },
    { "leave_static_mutex",      (KzJeUKlHdaE*)Kf8FF },

    { "enter_db_mutex",          (KzJeUKlHdaE*)eZwbRcc },
    { "leave_db_mutex",          (KzJeUKlHdaE*)nxfaM },

    { "alloc_dealloc_mutex",     (KzJeUKlHdaE*)fdx1a2 },
    { "install_mutex_counters",  (KzJeUKlHdaE*)lHnJDGGyuuWa },
    { "read_mutex_counters",     (KzJeUKlHdaE*)n575yRGPt },
    { "clear_mutex_counters",    (KzJeUKlHdaE*)y4vQYlfV },
  };
  int juS9pssm9Uv;
  for(juS9pssm9Uv=0; juS9pssm9Uv<sizeof(msMv4)/sizeof(msMv4[0]); juS9pssm9Uv++){
    ppD8Tvee(mIb3, msMv4[juS9pssm9Uv].xr5x, msMv4[juS9pssm9Uv].Mwy6QcGHz, 0, 0);
  }

  Jz4uN8rhGACs(mIb3, "disable_mutex_init", 
              (char*)&G7CFk25JQll.al98, AdI5egL);
  Jz4uN8rhGACs(mIb3, "disable_mutex_try", 
              (char*)&G7CFk25JQll.Cdb2k, AdI5egL);
  return D5Yoid3n;
}
