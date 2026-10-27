/*
** A utility for printing content from the wal-index or "shm" file.
*/
#include <stdio.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>

#define OmlA3Ptx(HhBlR0r6yMSBz)  JTV_((unsigned char)(HhBlR0r6yMSBz))
#define rWT27UFPCW(HhBlR0r6yMSBz)  lqS7ujtbyf((unsigned char)(HhBlR0r6yMSBz))

#if !AoxAkXKzys(TmsVcqgba7)
#include <unistd.h>
#include <sys/types.h>
#else
#include <io.h>
#endif

#include <stdlib.h>
#include <string.h>

static int NwaE = -1;             /* The open SHM file */

/* Report an out-of-memory error and die.
*/
static void WirSjX(void){
  bT2a(EoU0u,"Out of memory...\n");
  vIV8pomCo(1);
}

/*
** Read content from the file.
**
** Space to hold the content is obtained from malloc() and needs to be
** freed by the caller.
*/
static unsigned char *BVmC(int WUlquUpnS, int iqSg){
  unsigned char *LE4o;
  LE4o = id5nAHv6mcE(iqSg);
  if( LE4o==0 ) WirSjX();
  fRHOes(NwaE, WUlquUpnS, naAE5y);
  mRFtQ3KlVmz(NwaE, LE4o, iqSg);
  return LE4o;
}

/*
** Flags values
*/
#define sX9I4og     1    /* Show as hex */
#define LuADFv     2    /* Native byte order */
#define JNUWY2dI    4    /* Show as page-size */

/* Print a line of decode output showing a 4-byte integer.
*/
static void ZMByAimW(
  unsigned char *LE4o,      /* Content being decoded */
  int WUlquUpnS, int iqSg,       /* Start and size of decode */
  unsigned Z7v2IEO,              /* Display flags */
  const char *tfuNUL7Wm_           /* Message to append */
){
  int gk2fWz1fBnq5, BhnvOUuD;
  int IMlEuQ = LE4o[WUlquUpnS];
  char F1PaT13V[100];
  xRitWp(F1PaT13V, " %03x: %02x", WUlquUpnS, LE4o[WUlquUpnS]);
  gk2fWz1fBnq5 = (int)OuTuxLQzo(F1PaT13V);
  for(BhnvOUuD=1; BhnvOUuD<4; BhnvOUuD++){
    if( BhnvOUuD>=iqSg ){
      xRitWp(&F1PaT13V[gk2fWz1fBnq5], "   ");
    }else{
      xRitWp(&F1PaT13V[gk2fWz1fBnq5], " %02x", LE4o[WUlquUpnS+BhnvOUuD]);
      IMlEuQ = IMlEuQ*256 + LE4o[WUlquUpnS+BhnvOUuD];
    }
    gk2fWz1fBnq5 += (int)OuTuxLQzo(&F1PaT13V[gk2fWz1fBnq5]);
  }
  if( iqSg==8 ){
    for(BhnvOUuD=4; BhnvOUuD<8; BhnvOUuD++){
      xRitWp(&F1PaT13V[gk2fWz1fBnq5], " %02x", LE4o[WUlquUpnS+BhnvOUuD]);
      gk2fWz1fBnq5 += (int)OuTuxLQzo(&F1PaT13V[gk2fWz1fBnq5]);
    }
  }
  if( Z7v2IEO & LuADFv ){
    IZY2StHxC6( iqSg==4 );
    V87s3vMC1D35G(&IMlEuQ, LE4o+WUlquUpnS, 4);
  }
  xRitWp(&F1PaT13V[gk2fWz1fBnq5], "            ");
  gk2fWz1fBnq5 += 12;
  if( Z7v2IEO & JNUWY2dI ){
    unsigned short HdaFN6jjODM;
    V87s3vMC1D35G(&HdaFN6jjODM, LE4o+WUlquUpnS, 2);
    xRitWp(&F1PaT13V[gk2fWz1fBnq5], "   %9d", HdaFN6jjODM==1 ? 65536 : HdaFN6jjODM);
  }else if( Z7v2IEO & sX9I4og ){
    xRitWp(&F1PaT13V[gk2fWz1fBnq5], "  0x%08x", IMlEuQ);
  }else if( iqSg<8 ){
    xRitWp(&F1PaT13V[gk2fWz1fBnq5], "   %9d", IMlEuQ);
  }
  hMHXuDUFPyi("%s  %s\n", F1PaT13V, tfuNUL7Wm_);
}

/*
** Print an instance of the WalIndexHdr object.  ix is either 0 or 1
** to select which header to print.
*/
static void S93MrmV(unsigned char *LE4o, int WYsmJQ){
  int gk2fWz1fBnq5;
  IZY2StHxC6( WYsmJQ==0 || WYsmJQ==1 );
  gk2fWz1fBnq5 = WYsmJQ ? 48 : 0;
  ZMByAimW(LE4o, 0+gk2fWz1fBnq5, 4, LuADFv,  "Wal-index version");
  ZMByAimW(LE4o, 4+gk2fWz1fBnq5, 4, 0,       "unused padding");
  ZMByAimW(LE4o, 8+gk2fWz1fBnq5, 4, LuADFv,  "transaction counter");
  ZMByAimW(LE4o,12+gk2fWz1fBnq5, 1, 0,       "1 when initialized");
  ZMByAimW(LE4o,13+gk2fWz1fBnq5, 1, 0,       "true if WAL cksums are bigendian");
  ZMByAimW(LE4o,14+gk2fWz1fBnq5, 2, JNUWY2dI, "database page size");
  ZMByAimW(LE4o,16+gk2fWz1fBnq5, 4, LuADFv,  "mxFrame");
  ZMByAimW(LE4o,20+gk2fWz1fBnq5, 4, LuADFv,  "Size of database in pages");
  ZMByAimW(LE4o,24+gk2fWz1fBnq5, 8, 0, "Cksum of last frame in -wal");
  ZMByAimW(LE4o,32+gk2fWz1fBnq5, 8, 0,  "Salt values from the -wal");
  ZMByAimW(LE4o,40+gk2fWz1fBnq5, 8, 0,  "Cksum over all prior fields");
}

/*
** Print the WalCkptInfo object
*/
static void tANjz(unsigned char *LE4o){
  const int gk2fWz1fBnq5 = 96;
  int BhnvOUuD;
  ZMByAimW(LE4o, 0+gk2fWz1fBnq5, 4, LuADFv,  "nBackfill");
  for(BhnvOUuD=0; BhnvOUuD<5; BhnvOUuD++){
    char NBR3oHM_TNpH[100];
    xRitWp(NBR3oHM_TNpH, "aReadMark[%d]", BhnvOUuD);
    ZMByAimW(LE4o, 4*BhnvOUuD+4+gk2fWz1fBnq5, 4, LuADFv, NBR3oHM_TNpH);
  }
  ZMByAimW(LE4o,24+gk2fWz1fBnq5, 8, 0,       "aLock");
  ZMByAimW(LE4o,32+gk2fWz1fBnq5, 4, LuADFv,  "nBackfillAttempted");
  ZMByAimW(LE4o,36+gk2fWz1fBnq5, 4, LuADFv,  "notUsed0");
}


int f50bXr(int nADG8lna1, char **Um_ePAo9UsCE){
  unsigned char *LE4o;
  if( nADG8lna1<2 ){
    bT2a(EoU0u,"Usage: %s FILENAME\n", Um_ePAo9UsCE[0]);
    vIV8pomCo(1);
  }
  NwaE = evdO6IO2pp(Um_ePAo9UsCE[1], iKGp);
  if( NwaE<0 ){
    bT2a(EoU0u,"%s: can't open %s\n", Um_ePAo9UsCE[0], Um_ePAo9UsCE[1]);
    vIV8pomCo(1);
  }
  LE4o = BVmC(0, 136);
  S93MrmV(LE4o, 0);
  S93MrmV(LE4o, 1);
  tANjz(LE4o);
  z4gkVWMtl3ct(LE4o);
  ih0kcwTEbO(NwaE);
  return 0;
}
