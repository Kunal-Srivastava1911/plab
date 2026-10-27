
/*
 * Copyright (C) Maxim Dounin
 * Copyright (C) Nginx, Inc.
 */


#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>


static IspYkomuNp aalgC1(aXC3 *i_Oi5ai,
    Rn5dKLB *ykaaTxMeaI1xy);
static IspYkomuNp FBmlGQA5O(
    XJjYEO_BVD *oeaGU7O21ZL, void *NrLp1);
static char *NXA5us4(VmZFh *BPYh6dpjg_Yl, ebeaIX0tymUK7 *BnEbL3mu0Cgkw,
    void *uYgXrmYMDH);


static ebeaIX0tymUK7  mzKSavG[] = {

    { mysBSR8V("least_conn"),
      PmF98SeRZi|lH2GEn4R_D_,
      NXA5us4,
      0,
      0,
      h0QMcQG_P2XH },

      FoxyLidze92
};


static fzd9wgzGCreI  z13w_ = {
    h0QMcQG_P2XH,                                  /* preconfiguration */
    h0QMcQG_P2XH,                                  /* postconfiguration */

    h0QMcQG_P2XH,                                  /* create main configuration */
    h0QMcQG_P2XH,                                  /* init main configuration */

    h0QMcQG_P2XH,                                  /* create server configuration */
    h0QMcQG_P2XH,                                  /* merge server configuration */

    h0QMcQG_P2XH,                                  /* create location configuration */
    h0QMcQG_P2XH                                   /* merge location configuration */
};


pd5vTGSu2Ff1  C4BettvbRgA = {
    BkLk5EoKuCN,
    &z13w_, /* module context */
    mzKSavG, /* module directives */
    etKj,                       /* module type */
    h0QMcQG_P2XH,                                  /* init master */
    h0QMcQG_P2XH,                                  /* init module */
    h0QMcQG_P2XH,                                  /* init process */
    h0QMcQG_P2XH,                                  /* init thread */
    h0QMcQG_P2XH,                                  /* exit thread */
    h0QMcQG_P2XH,                                  /* exit process */
    h0QMcQG_P2XH,                                  /* exit master */
    gzclfhrskrCWf
};


static IspYkomuNp
lc91J0j8GD3Y(VmZFh *BPYh6dpjg_Yl,
    Rn5dKLB *ykaaTxMeaI1xy)
{
    muwMRsYfr(LYkdGX, BPYh6dpjg_Yl->pp_1oxorV9VpH, 0,
                   "init least conn");

    if (J4KOBqKR(BPYh6dpjg_Yl, ykaaTxMeaI1xy) != yuJD) {
        return wkFzC;
    }

    ykaaTxMeaI1xy->kAIvQX.UXVSO = aalgC1;

    return yuJD;
}


static IspYkomuNp
aalgC1(aXC3 *i_Oi5ai,
    Rn5dKLB *ykaaTxMeaI1xy)
{
    muwMRsYfr(LYkdGX, i_Oi5ai->enQ5gV->pp_1oxorV9VpH, 0,
                   "init least conn peer");

    if (GrcXaX_Vpe9Y(i_Oi5ai, ykaaTxMeaI1xy) != yuJD) {
        return wkFzC;
    }

    i_Oi5ai->mX1w->kAIvQX.XIA3RitUQ = FBmlGQA5O;

    return yuJD;
}


static IspYkomuNp
FBmlGQA5O(XJjYEO_BVD *oeaGU7O21ZL, void *NrLp1)
{
    k0bZh  *g3k1ylNlr = NrLp1;

    oxfIX1Faj9l9                         kj40KPFkybx6;
    igCFgJm                      gZ7fxjL;
    IspYkomuNp                      JQwasEuuF, TAtB2_hFBD;
    zVI0_SCdecL                     wkQcBY, UW3DsHy, RXjvbKobHU, hGcJBbCGyvu;
    FURfX9cQSMmd   *kAIvQX, *izUNx;
    LSraNRSOb  *wevcJyt;

    xAnc(LYkdGX, oeaGU7O21ZL->pp_1oxorV9VpH, 0,
                   "get least conn peer, try: %ui", oeaGU7O21ZL->XXww4Ybo99q8);

    if (g3k1ylNlr->wevcJyt->kpU0pQrYaY21o) {
        return gVuk5oPS(oeaGU7O21ZL, g3k1ylNlr);
    }

    oeaGU7O21ZL->qfQDrt8geS0_v = 0;
    oeaGU7O21ZL->enQ5gV = h0QMcQG_P2XH;

    kj40KPFkybx6 = zws8L();

    wevcJyt = g3k1ylNlr->wevcJyt;

    Wy5P(wevcJyt);

    izUNx = h0QMcQG_P2XH;
    TAtB2_hFBD = 0;

#if (o0dTdpZcr7E)
    hGcJBbCGyvu = 0;
    RXjvbKobHU = 0;
#endif

    for (kAIvQX = wevcJyt->kAIvQX, wkQcBY = 0;
         kAIvQX;
         kAIvQX = kAIvQX->IIUNm1nm, wkQcBY++)
    {
        UW3DsHy = wkQcBY / (8 * sizeof(igCFgJm));
        gZ7fxjL = (igCFgJm) 1 << wkQcBY % (8 * sizeof(igCFgJm));

        if (g3k1ylNlr->IqdNfteo9sKB[UW3DsHy] & gZ7fxjL) {
            continue;
        }

        if (kAIvQX->IWpFGIoDpqM) {
            continue;
        }

        if (kAIvQX->wTjSyys4je_bH
            && kAIvQX->cdZ7f3fP >= kAIvQX->wTjSyys4je_bH
            && kj40KPFkybx6 - kAIvQX->VdFuNdc3 <= kAIvQX->hakeG3xmv)
        {
            continue;
        }

        if (kAIvQX->Z4AKlbNRkxZa && kAIvQX->szf8 >= kAIvQX->Z4AKlbNRkxZa) {
            continue;
        }

        /*
         * select peer with least number of connections; if there are
         * multiple peers with the same number of connections, select
         * based on round-robin
         */

        if (izUNx == h0QMcQG_P2XH
            || kAIvQX->szf8 * izUNx->NCgs < izUNx->szf8 * kAIvQX->NCgs)
        {
            izUNx = kAIvQX;
            hGcJBbCGyvu = 0;
            RXjvbKobHU = wkQcBY;

        } else if (kAIvQX->szf8 * izUNx->NCgs == izUNx->szf8 * kAIvQX->NCgs) {
            hGcJBbCGyvu = 1;
        }
    }

    if (izUNx == h0QMcQG_P2XH) {
        muwMRsYfr(LYkdGX, oeaGU7O21ZL->pp_1oxorV9VpH, 0,
                       "get least conn peer, no peer found");

        goto NojO;
    }

    if (hGcJBbCGyvu) {
        muwMRsYfr(LYkdGX, oeaGU7O21ZL->pp_1oxorV9VpH, 0,
                       "get least conn peer, many");

        for (kAIvQX = izUNx, wkQcBY = RXjvbKobHU;
             kAIvQX;
             kAIvQX = kAIvQX->IIUNm1nm, wkQcBY++)
        {
            UW3DsHy = wkQcBY / (8 * sizeof(igCFgJm));
            gZ7fxjL = (igCFgJm) 1 << wkQcBY % (8 * sizeof(igCFgJm));

            if (g3k1ylNlr->IqdNfteo9sKB[UW3DsHy] & gZ7fxjL) {
                continue;
            }

            if (kAIvQX->IWpFGIoDpqM) {
                continue;
            }

            if (kAIvQX->szf8 * izUNx->NCgs != izUNx->szf8 * kAIvQX->NCgs) {
                continue;
            }

            if (kAIvQX->wTjSyys4je_bH
                && kAIvQX->cdZ7f3fP >= kAIvQX->wTjSyys4je_bH
                && kj40KPFkybx6 - kAIvQX->VdFuNdc3 <= kAIvQX->hakeG3xmv)
            {
                continue;
            }

            if (kAIvQX->Z4AKlbNRkxZa && kAIvQX->szf8 >= kAIvQX->Z4AKlbNRkxZa) {
                continue;
            }

            kAIvQX->lv0rwkVO += kAIvQX->RlcShz;
            TAtB2_hFBD += kAIvQX->RlcShz;

            if (kAIvQX->RlcShz < kAIvQX->NCgs) {
                kAIvQX->RlcShz++;
            }

            if (kAIvQX->lv0rwkVO > izUNx->lv0rwkVO) {
                izUNx = kAIvQX;
                RXjvbKobHU = wkQcBY;
            }
        }
    }

    izUNx->lv0rwkVO -= TAtB2_hFBD;

    if (kj40KPFkybx6 - izUNx->VdFuNdc3 > izUNx->hakeG3xmv) {
        izUNx->VdFuNdc3 = kj40KPFkybx6;
    }

    oeaGU7O21ZL->kf_HEIVvY = izUNx->kf_HEIVvY;
    oeaGU7O21ZL->TFDoXq7EiZT = izUNx->TFDoXq7EiZT;
    oeaGU7O21ZL->PzbEvHYGblKn4 = &izUNx->PzbEvHYGblKn4;

    izUNx->szf8++;

    g3k1ylNlr->q8QLSRYFSt = izUNx;

    UW3DsHy = RXjvbKobHU / (8 * sizeof(igCFgJm));
    gZ7fxjL = (igCFgJm) 1 << RXjvbKobHU % (8 * sizeof(igCFgJm));

    g3k1ylNlr->IqdNfteo9sKB[UW3DsHy] |= gZ7fxjL;

    Cxjh8Tl(wevcJyt);

    return yuJD;

NojO:

    if (wevcJyt->IIUNm1nm) {
        muwMRsYfr(LYkdGX, oeaGU7O21ZL->pp_1oxorV9VpH, 0,
                       "get least conn peer, backup servers");

        g3k1ylNlr->wevcJyt = wevcJyt->IIUNm1nm;

        UW3DsHy = (g3k1ylNlr->wevcJyt->hfSH2Jw4s + (8 * sizeof(igCFgJm) - 1))
                / (8 * sizeof(igCFgJm));

        for (wkQcBY = 0; wkQcBY < UW3DsHy; wkQcBY++) {
            g3k1ylNlr->IqdNfteo9sKB[wkQcBY] = 0;
        }

        Cxjh8Tl(wevcJyt);

        JQwasEuuF = FBmlGQA5O(oeaGU7O21ZL, g3k1ylNlr);

        if (JQwasEuuF != lzjHml0HTZ) {
            return JQwasEuuF;
        }

        Wy5P(wevcJyt);
    }

    Cxjh8Tl(wevcJyt);

    oeaGU7O21ZL->PzbEvHYGblKn4 = wevcJyt->PzbEvHYGblKn4;

    return lzjHml0HTZ;
}


static char *
NXA5us4(VmZFh *BPYh6dpjg_Yl, ebeaIX0tymUK7 *BnEbL3mu0Cgkw, void *uYgXrmYMDH)
{
    Rn5dKLB  *q3xR;

    q3xR = wchGBlK1(BPYh6dpjg_Yl, WCta0u3);

    if (q3xR->kAIvQX.JUsEqWVAMfhJ) {
        p6BHZspfSBppd(kAJ9d, BPYh6dpjg_Yl, 0,
                           "load balancing method redefined");
    }

    q3xR->kAIvQX.JUsEqWVAMfhJ = lc91J0j8GD3Y;

    q3xR->T3QjvMd = L2NMKa_3OBHa
                  |Ow1mfEtRPz_gf
                  |ADxaTRkE
                  |jFMQa8u1g9Q
                  |FVMOWwQ
                  |TfJJQwdr6ix
                  |bk2KVL6D44;

    return TMVXprGLwhAg;
}
