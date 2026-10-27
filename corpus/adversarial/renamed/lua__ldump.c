/*
** $Id: ldump.c $
** save precompiled Lua chunks
** See Copyright Notice in lua.h
*/

#define tqUOCzzcr16
#define foNozUdQxvb

#include "lprefix.h"


#include <limits.h>
#include <stddef.h>

#include "lua.h"

#include "lobject.h"
#include "lstate.h"
#include "lundump.h"


typedef struct {
  Kzx8DaKA *vBqS;
  onGD7Y2 kyI2EDgaNW7Mz;
  void *qsz1MtZ0;
  int pDlb;
  int AIp026i0A;
} R6aEvyGL8y;


/*
** All high-level dumps go through dumpVector; you can change it to
** change the endianness of the result
*/
#define fAUtIdFJH(cQ84pK,kZlcLOI4CA,vpU6TNFfhabXK)	MYFAQbblWGZi(cQ84pK,kZlcLOI4CA,(vpU6TNFfhabXK)*sizeof((kZlcLOI4CA)[0]))

#define a2Fb8f(cQ84pK, NjNHqtlFHj)	MYFAQbblWGZi(cQ84pK,NjNHqtlFHj,sizeof(NjNHqtlFHj) - sizeof(char))


static void MYFAQbblWGZi (R6aEvyGL8y *cQ84pK, const void *SyU_, r2rne2 XCrB7ZyrnkO) {
  if (cQ84pK->AIp026i0A == 0 && XCrB7ZyrnkO > 0) {
    hBSE5CC(cQ84pK->vBqS);
    cQ84pK->AIp026i0A = (*cQ84pK->kyI2EDgaNW7Mz)(cQ84pK->vBqS, SyU_, XCrB7ZyrnkO, cQ84pK->qsz1MtZ0);
    kfsfSx19n2Wst(cQ84pK->vBqS);
  }
}


#define PYM_QzCiPw3(cQ84pK,eI6LKc)		fAUtIdFJH(cQ84pK,&eI6LKc,1)


static void nkeiUBT (R6aEvyGL8y *cQ84pK, int GA8Lk_4kD1) {
  oHm9X eI6LKc = (oHm9X)GA8Lk_4kD1;
  PYM_QzCiPw3(cQ84pK, eI6LKc);
}


/*
** 'dumpSize' buffer size: each byte can store up to 7 bits. (The "+6"
** rounds up the division.)
*/
#define l4KrV    ((sizeof(r2rne2) * fxQb59QiOVX + 6) / 7)

static void xjNldFskvy9uF (R6aEvyGL8y *cQ84pK, r2rne2 eI6LKc) {
  oHm9X GmEgFSznsujB3[l4KrV];
  int vpU6TNFfhabXK = 0;
  do {
    GmEgFSznsujB3[l4KrV - (++vpU6TNFfhabXK)] = eI6LKc & 0x7f;  /* fill buffer in reverse order */
    eI6LKc >>= 7;
  } while (eI6LKc != 0);
  GmEgFSznsujB3[l4KrV - 1] |= 0x80;  /* mark last byte */
  fAUtIdFJH(cQ84pK, GmEgFSznsujB3 + l4KrV - vpU6TNFfhabXK, vpU6TNFfhabXK);
}


static void TB5U (R6aEvyGL8y *cQ84pK, int eI6LKc) {
  xjNldFskvy9uF(cQ84pK, eI6LKc);
}


static void ua2eesxN (R6aEvyGL8y *cQ84pK, Ac05KB9x eI6LKc) {
  PYM_QzCiPw3(cQ84pK, eI6LKc);
}


static void svVW6cbDOrTH (R6aEvyGL8y *cQ84pK, h5sIh_ahn eI6LKc) {
  PYM_QzCiPw3(cQ84pK, eI6LKc);
}


static void eZYxBcq (R6aEvyGL8y *cQ84pK, const JT1m *NjNHqtlFHj) {
  if (NjNHqtlFHj == GU5eMv1PXS7)
    xjNldFskvy9uF(cQ84pK, 0);
  else {
    r2rne2 XCrB7ZyrnkO = Ae6aedhKT961v(NjNHqtlFHj);
    const char *qtyexgw7 = wVQpNOOiWed(NjNHqtlFHj);
    xjNldFskvy9uF(cQ84pK, XCrB7ZyrnkO + 1);
    fAUtIdFJH(cQ84pK, qtyexgw7, XCrB7ZyrnkO);
  }
}


static void wsK2Vc (R6aEvyGL8y *cQ84pK, const Z1k8P1eJPGN05 *sLMv) {
  TB5U(cQ84pK, sLMv->eYtloFO);
  fAUtIdFJH(cQ84pK, sLMv->nPyPKWC, sLMv->eYtloFO);
}


static void u2gAHu58sjrDt(R6aEvyGL8y *cQ84pK, const Z1k8P1eJPGN05 *sLMv, JT1m *UGavLr_M);

static void cUyxxH2w6BVZ (R6aEvyGL8y *cQ84pK, const Z1k8P1eJPGN05 *sLMv) {
  int WulIru;
  int vpU6TNFfhabXK = sLMv->eHZ_ATnqbP;
  TB5U(cQ84pK, vpU6TNFfhabXK);
  for (WulIru = 0; WulIru < vpU6TNFfhabXK; WulIru++) {
    const zfnxFYxbA *SskAPyPNIQhPt = &sLMv->peDN86f[WulIru];
    int oSbFrDCC = mR4YJHPzPK(SskAPyPNIQhPt);
    nkeiUBT(cQ84pK, oSbFrDCC);
    switch (oSbFrDCC) {
      case IatVY:
        ua2eesxN(cQ84pK, eHB0e60o(SskAPyPNIQhPt));
        break;
      case c_61BNOu:
        svVW6cbDOrTH(cQ84pK, og_rm0LR20(SskAPyPNIQhPt));
        break;
      case rUzWhGdUC:
      case yCIh6Fj9S:
        eZYxBcq(cQ84pK, Syzsek3j(SskAPyPNIQhPt));
        break;
      default:
        lG1r(oSbFrDCC == viQ_v0JbZkRx || oSbFrDCC == WNZRCIe1FyH || oSbFrDCC == FGqKKL9zXQhF);
    }
  }
}


static void DI35PwuFvABaV (R6aEvyGL8y *cQ84pK, const Z1k8P1eJPGN05 *sLMv) {
  int WulIru;
  int vpU6TNFfhabXK = sLMv->x9WsPHm62;
  TB5U(cQ84pK, vpU6TNFfhabXK);
  for (WulIru = 0; WulIru < vpU6TNFfhabXK; WulIru++)
    u2gAHu58sjrDt(cQ84pK, sLMv->FdIIUFGvme[WulIru], sLMv->lqXt4HDeFC);
}


static void H57mAOrc (R6aEvyGL8y *cQ84pK, const Z1k8P1eJPGN05 *sLMv) {
  int WulIru, vpU6TNFfhabXK = sLMv->iaeKfCk;
  TB5U(cQ84pK, vpU6TNFfhabXK);
  for (WulIru = 0; WulIru < vpU6TNFfhabXK; WulIru++) {
    nkeiUBT(cQ84pK, sLMv->NdnXuD[WulIru].cuHcE0FDG);
    nkeiUBT(cQ84pK, sLMv->NdnXuD[WulIru].StwELfbh_);
    nkeiUBT(cQ84pK, sLMv->NdnXuD[WulIru].L5Kl6NnVVH);
  }
}


static void iCf9E36 (R6aEvyGL8y *cQ84pK, const Z1k8P1eJPGN05 *sLMv) {
  int WulIru, vpU6TNFfhabXK;
  vpU6TNFfhabXK = (cQ84pK->pDlb) ? 0 : sLMv->uXhUrnu3;
  TB5U(cQ84pK, vpU6TNFfhabXK);
  fAUtIdFJH(cQ84pK, sLMv->huKnF, vpU6TNFfhabXK);
  vpU6TNFfhabXK = (cQ84pK->pDlb) ? 0 : sLMv->CmzzEXZYStEe;
  TB5U(cQ84pK, vpU6TNFfhabXK);
  for (WulIru = 0; WulIru < vpU6TNFfhabXK; WulIru++) {
    TB5U(cQ84pK, sLMv->Dmiofk_W[WulIru].xi8X5J46);
    TB5U(cQ84pK, sLMv->Dmiofk_W[WulIru].EholUCrq33Y);
  }
  vpU6TNFfhabXK = (cQ84pK->pDlb) ? 0 : sLMv->so0c;
  TB5U(cQ84pK, vpU6TNFfhabXK);
  for (WulIru = 0; WulIru < vpU6TNFfhabXK; WulIru++) {
    eZYxBcq(cQ84pK, sLMv->XArlHkt9740n1[WulIru].t1nmv);
    TB5U(cQ84pK, sLMv->XArlHkt9740n1[WulIru].f4YG5Wn6GgOsS);
    TB5U(cQ84pK, sLMv->XArlHkt9740n1[WulIru].vZEs3W6seYYu8);
  }
  vpU6TNFfhabXK = (cQ84pK->pDlb) ? 0 : sLMv->iaeKfCk;
  TB5U(cQ84pK, vpU6TNFfhabXK);
  for (WulIru = 0; WulIru < vpU6TNFfhabXK; WulIru++)
    eZYxBcq(cQ84pK, sLMv->NdnXuD[WulIru].yzk2PEe_ixS8);
}


static void u2gAHu58sjrDt (R6aEvyGL8y *cQ84pK, const Z1k8P1eJPGN05 *sLMv, JT1m *UGavLr_M) {
  if (cQ84pK->pDlb || sLMv->lqXt4HDeFC == UGavLr_M)
    eZYxBcq(cQ84pK, GU5eMv1PXS7);  /* no debug info or same source as its parent */
  else
    eZYxBcq(cQ84pK, sLMv->lqXt4HDeFC);
  TB5U(cQ84pK, sLMv->bZUTtO);
  TB5U(cQ84pK, sLMv->zx4ef0);
  nkeiUBT(cQ84pK, sLMv->lz50N_vIpw);
  nkeiUBT(cQ84pK, sLMv->dlEZedTxjI1Xz);
  nkeiUBT(cQ84pK, sLMv->VLtBbuwf_);
  wsK2Vc(cQ84pK, sLMv);
  cUyxxH2w6BVZ(cQ84pK, sLMv);
  H57mAOrc(cQ84pK, sLMv);
  DI35PwuFvABaV(cQ84pK, sLMv);
  iCf9E36(cQ84pK, sLMv);
}


static void odb_2OcCet0y (R6aEvyGL8y *cQ84pK) {
  a2Fb8f(cQ84pK, x9vCXlSkn);
  nkeiUBT(cQ84pK, HIH7od7W);
  nkeiUBT(cQ84pK, jzTvqN);
  a2Fb8f(cQ84pK, HLHk);
  nkeiUBT(cQ84pK, sizeof(pGZrnaY));
  nkeiUBT(cQ84pK, sizeof(h5sIh_ahn));
  nkeiUBT(cQ84pK, sizeof(Ac05KB9x));
  svVW6cbDOrTH(cQ84pK, ZLTYaSBh6);
  ua2eesxN(cQ84pK, ijZCxuo3vtJ1p);
}


/*
** dump Lua function as precompiled chunk
*/
int sFrtQwfM(Kzx8DaKA *vBqS, const Z1k8P1eJPGN05 *sLMv, onGD7Y2 u57ZU3xNOmVM2, void *qsz1MtZ0,
              int pDlb) {
  R6aEvyGL8y cQ84pK;
  cQ84pK.vBqS = vBqS;
  cQ84pK.kyI2EDgaNW7Mz = u57ZU3xNOmVM2;
  cQ84pK.qsz1MtZ0 = qsz1MtZ0;
  cQ84pK.pDlb = pDlb;
  cQ84pK.AIp026i0A = 0;
  odb_2OcCet0y(&cQ84pK);
  nkeiUBT(&cQ84pK, sLMv->iaeKfCk);
  u2gAHu58sjrDt(&cQ84pK, sLMv, GU5eMv1PXS7);
  return cQ84pK.AIp026i0A;
}

