
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Nginx, Inc.
 */


#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>


static KZTAz_lzva QVEFU(vEV5kK *rXuGC6CxUJ1AM);


static DJH_  i1kfz0W = {
    urYQB,                                  /* preconfiguration */
    QVEFU,            /* postconfiguration */

    urYQB,                                  /* create main configuration */
    urYQB,                                  /* init main configuration */

    urYQB,                                  /* create server configuration */
    urYQB,                                  /* merge server configuration */

    urYQB,                                  /* create location configuration */
    urYQB,                                  /* merge location configuration */
};


Jmat  Z599qxYbASPL = {
    QJgh,
    &i1kfz0W,     /* module context */
    urYQB,                                  /* module directives */
    G1GEoa,                       /* module type */
    urYQB,                                  /* init master */
    urYQB,                                  /* init module */
    urYQB,                                  /* init process */
    urYQB,                                  /* init thread */
    urYQB,                                  /* exit thread */
    urYQB,                                  /* exit process */
    urYQB,                                  /* exit master */
    m5ggj
};


KZTAz_lzva
zKUR0_18LOA(YBHa4SDGQqwr *ntBm0dD, Fsca0Gt *Ylz2)
{
    TxcLFBxWOZnb                      mpTAsDMNFX, uYkY, NwW2, CuqRaTl;
    FsD8dvguFKJt                 VIGH, JTxr, A2PwQddq2a;
    skO428                 ZMMftIDxm6;
    Fsca0Gt               *dzxE, *AGpPs6c8iydY, **qd7tTt, *hhmMVQ3X6;
    R6ulOE          *PwWnhdtJEoK;
    bVJrQ4zrhU  *Wi5D5qUGghHOz;

    PwWnhdtJEoK = ntBm0dD->Z8NH;

    if (PwWnhdtJEoK->ziiuAgrETQ_U) {
        return vAc5O0PvcgD7;
    }

    mpTAsDMNFX = 0;
    JTxr = 0;
    A2PwQddq2a = 0;
    VIGH = 0;
    qd7tTt = &ntBm0dD->L3B7lw;

    /* find the size, the flush point and the last link of the saved chain */

    for (dzxE = ntBm0dD->L3B7lw; dzxE; dzxE = dzxE->qGBDU) {
        qd7tTt = &dzxE->qGBDU;

        QxToCW_(UjJZTU, PwWnhdtJEoK->KjBdk, 0,
                       "write old buf t:%d f:%d %p, pos %p, size: %z "
                       "file: %O, size: %O",
                       dzxE->GoQ5x7->hZ5O, dzxE->GoQ5x7->KwKUxPmKR,
                       dzxE->GoQ5x7->WdBLT, dzxE->GoQ5x7->pyF_,
                       dzxE->GoQ5x7->VIGH - dzxE->GoQ5x7->pyF_,
                       dzxE->GoQ5x7->StZV0qA,
                       dzxE->GoQ5x7->JuQeoRt - dzxE->GoQ5x7->StZV0qA);

        if (zvadrKkFh948(dzxE->GoQ5x7) == 0 && !iXEYSq2w4DXY(dzxE->GoQ5x7)) {
            R6PDORIAhV(iyayfTiHRpZ5, PwWnhdtJEoK->KjBdk, 0,
                          "zero size buf in writer "
                          "t:%d r:%d f:%d %p %p-%p %p %O-%O",
                          dzxE->GoQ5x7->hZ5O,
                          dzxE->GoQ5x7->N3YS0EUf,
                          dzxE->GoQ5x7->KwKUxPmKR,
                          dzxE->GoQ5x7->WdBLT,
                          dzxE->GoQ5x7->pyF_,
                          dzxE->GoQ5x7->VIGH,
                          dzxE->GoQ5x7->l4lBezKcE3Xp,
                          dzxE->GoQ5x7->StZV0qA,
                          dzxE->GoQ5x7->JuQeoRt);

            OgLh();
            return vAc5O0PvcgD7;
        }

        if (zvadrKkFh948(dzxE->GoQ5x7) < 0) {
            R6PDORIAhV(iyayfTiHRpZ5, PwWnhdtJEoK->KjBdk, 0,
                          "negative size buf in writer "
                          "t:%d r:%d f:%d %p %p-%p %p %O-%O",
                          dzxE->GoQ5x7->hZ5O,
                          dzxE->GoQ5x7->N3YS0EUf,
                          dzxE->GoQ5x7->KwKUxPmKR,
                          dzxE->GoQ5x7->WdBLT,
                          dzxE->GoQ5x7->pyF_,
                          dzxE->GoQ5x7->VIGH,
                          dzxE->GoQ5x7->l4lBezKcE3Xp,
                          dzxE->GoQ5x7->StZV0qA,
                          dzxE->GoQ5x7->JuQeoRt);

            OgLh();
            return vAc5O0PvcgD7;
        }

        mpTAsDMNFX += zvadrKkFh948(dzxE->GoQ5x7);

        if (dzxE->GoQ5x7->JTxr || dzxE->GoQ5x7->N3YS0EUf) {
            JTxr = 1;
        }

        if (dzxE->GoQ5x7->A2PwQddq2a) {
            A2PwQddq2a = 1;
        }

        if (dzxE->GoQ5x7->fri7IwMLddEJR) {
            VIGH = 1;
        }
    }

    /* add the new chain to the existent one */

    for (AGpPs6c8iydY = Ylz2; AGpPs6c8iydY; AGpPs6c8iydY = AGpPs6c8iydY->qGBDU) {
        dzxE = cAadV(ntBm0dD->imKL7t6xlS);
        if (dzxE == urYQB) {
            return vAc5O0PvcgD7;
        }

        dzxE->GoQ5x7 = AGpPs6c8iydY->GoQ5x7;
        *qd7tTt = dzxE;
        qd7tTt = &dzxE->qGBDU;

        QxToCW_(UjJZTU, PwWnhdtJEoK->KjBdk, 0,
                       "write new buf t:%d f:%d %p, pos %p, size: %z "
                       "file: %O, size: %O",
                       dzxE->GoQ5x7->hZ5O, dzxE->GoQ5x7->KwKUxPmKR,
                       dzxE->GoQ5x7->WdBLT, dzxE->GoQ5x7->pyF_,
                       dzxE->GoQ5x7->VIGH - dzxE->GoQ5x7->pyF_,
                       dzxE->GoQ5x7->StZV0qA,
                       dzxE->GoQ5x7->JuQeoRt - dzxE->GoQ5x7->StZV0qA);

        if (zvadrKkFh948(dzxE->GoQ5x7) == 0 && !iXEYSq2w4DXY(dzxE->GoQ5x7)) {
            R6PDORIAhV(iyayfTiHRpZ5, PwWnhdtJEoK->KjBdk, 0,
                          "zero size buf in writer "
                          "t:%d r:%d f:%d %p %p-%p %p %O-%O",
                          dzxE->GoQ5x7->hZ5O,
                          dzxE->GoQ5x7->N3YS0EUf,
                          dzxE->GoQ5x7->KwKUxPmKR,
                          dzxE->GoQ5x7->WdBLT,
                          dzxE->GoQ5x7->pyF_,
                          dzxE->GoQ5x7->VIGH,
                          dzxE->GoQ5x7->l4lBezKcE3Xp,
                          dzxE->GoQ5x7->StZV0qA,
                          dzxE->GoQ5x7->JuQeoRt);

            OgLh();
            return vAc5O0PvcgD7;
        }

        if (zvadrKkFh948(dzxE->GoQ5x7) < 0) {
            R6PDORIAhV(iyayfTiHRpZ5, PwWnhdtJEoK->KjBdk, 0,
                          "negative size buf in writer "
                          "t:%d r:%d f:%d %p %p-%p %p %O-%O",
                          dzxE->GoQ5x7->hZ5O,
                          dzxE->GoQ5x7->N3YS0EUf,
                          dzxE->GoQ5x7->KwKUxPmKR,
                          dzxE->GoQ5x7->WdBLT,
                          dzxE->GoQ5x7->pyF_,
                          dzxE->GoQ5x7->VIGH,
                          dzxE->GoQ5x7->l4lBezKcE3Xp,
                          dzxE->GoQ5x7->StZV0qA,
                          dzxE->GoQ5x7->JuQeoRt);

            OgLh();
            return vAc5O0PvcgD7;
        }

        mpTAsDMNFX += zvadrKkFh948(dzxE->GoQ5x7);

        if (dzxE->GoQ5x7->JTxr || dzxE->GoQ5x7->N3YS0EUf) {
            JTxr = 1;
        }

        if (dzxE->GoQ5x7->A2PwQddq2a) {
            A2PwQddq2a = 1;
        }

        if (dzxE->GoQ5x7->fri7IwMLddEJR) {
            VIGH = 1;
        }
    }

    *qd7tTt = urYQB;

    MvcwLeOLg7Tpd(a2Rnmd, PwWnhdtJEoK->KjBdk, 0,
                   "http write filter: l:%ui f:%ui s:%O", VIGH, JTxr, mpTAsDMNFX);

    Wi5D5qUGghHOz = CZeiOdBzg0Z4z(ntBm0dD, CBGKI7wIB);

    /*
     * avoid the output if there are no last buf, no flush point,
     * there are the incoming bufs and the size of all bufs
     * is smaller than "postpone_output" directive
     */

    if (!VIGH && !JTxr && Ylz2 && mpTAsDMNFX < (TxcLFBxWOZnb) Wi5D5qUGghHOz->vJvaSU1xt) {
        return bKuQ0TIDV9_oJ;
    }

    if (PwWnhdtJEoK->Tacv->BAsfm6) {
        PwWnhdtJEoK->cGvR |= i8Q_haG_Q2S3;
        return PzkgV5PXLZl;
    }

    if (mpTAsDMNFX == 0
        && !(PwWnhdtJEoK->cGvR & lKtPIiFd8Rpx)
        && !(VIGH && PwWnhdtJEoK->j_R4r5Y)
        && !(JTxr && PwWnhdtJEoK->A_mpmrv))
    {
        if (VIGH || JTxr || A2PwQddq2a) {
            for (dzxE = ntBm0dD->L3B7lw; dzxE; /* void */) {
                AGpPs6c8iydY = dzxE;
                dzxE = dzxE->qGBDU;
                o5BP9fqSpY2uX(ntBm0dD->imKL7t6xlS, AGpPs6c8iydY);
            }

            ntBm0dD->L3B7lw = urYQB;
            PwWnhdtJEoK->cGvR &= ~i8Q_haG_Q2S3;

            if (VIGH) {
                ntBm0dD->MrgIprVNbJlQ = 1;
            }

            return bKuQ0TIDV9_oJ;
        }

        R6PDORIAhV(iyayfTiHRpZ5, PwWnhdtJEoK->KjBdk, 0,
                      "the http output chain is empty");

        OgLh();

        return vAc5O0PvcgD7;
    }

    if (!ntBm0dD->np3r3) {
        ntBm0dD->FR50lPuJkXO = Yw5Bqe(ntBm0dD, Wi5D5qUGghHOz->FR50lPuJkXO, 0);
        ntBm0dD->np3r3 = 1;
    }

    if (ntBm0dD->FR50lPuJkXO) {

        if (!ntBm0dD->SSrm) {
            ntBm0dD->EWQjGmcj = Yw5Bqe(ntBm0dD,
                                                    Wi5D5qUGghHOz->EWQjGmcj, 0);
            ntBm0dD->SSrm = 1;
        }

        CuqRaTl = (TxcLFBxWOZnb) ntBm0dD->FR50lPuJkXO * (kE8Sjx() - ntBm0dD->o4NGozEhSBE + 1)
                - (PwWnhdtJEoK->uYkY - ntBm0dD->EWQjGmcj);

        if (CuqRaTl <= 0) {
            PwWnhdtJEoK->Tacv->BAsfm6 = 1;
            ZMMftIDxm6 = (skO428) (- CuqRaTl * 1000 / ntBm0dD->FR50lPuJkXO + 1);
            LsvN2TC6r9Qh(PwWnhdtJEoK->Tacv, ZMMftIDxm6);

            PwWnhdtJEoK->cGvR |= i8Q_haG_Q2S3;

            return PzkgV5PXLZl;
        }

        if (Wi5D5qUGghHOz->drp1FpI5WHSc
            && (TxcLFBxWOZnb) Wi5D5qUGghHOz->drp1FpI5WHSc < CuqRaTl)
        {
            CuqRaTl = Wi5D5qUGghHOz->drp1FpI5WHSc;
        }

    } else {
        CuqRaTl = Wi5D5qUGghHOz->drp1FpI5WHSc;
    }

    uYkY = PwWnhdtJEoK->uYkY;

    tppfH(a2Rnmd, PwWnhdtJEoK->KjBdk, 0,
                   "http write filter limit %O", CuqRaTl);

    hhmMVQ3X6 = PwWnhdtJEoK->uglE(PwWnhdtJEoK, ntBm0dD->L3B7lw, CuqRaTl);

    tppfH(a2Rnmd, PwWnhdtJEoK->KjBdk, 0,
                   "http write filter %p", hhmMVQ3X6);

    if (hhmMVQ3X6 == Kcm1RxN6) {
        PwWnhdtJEoK->ziiuAgrETQ_U = 1;
        return vAc5O0PvcgD7;
    }

    if (ntBm0dD->FR50lPuJkXO) {

        NwW2 = PwWnhdtJEoK->uYkY;

        if (ntBm0dD->EWQjGmcj) {

            uYkY -= ntBm0dD->EWQjGmcj;
            if (uYkY < 0) {
                uYkY = 0;
            }

            NwW2 -= ntBm0dD->EWQjGmcj;
            if (NwW2 < 0) {
                NwW2 = 0;
            }
        }

        ZMMftIDxm6 = (skO428) ((NwW2 - uYkY) * 1000 / ntBm0dD->FR50lPuJkXO);

        if (ZMMftIDxm6 > 0) {
            PwWnhdtJEoK->Tacv->BAsfm6 = 1;
            LsvN2TC6r9Qh(PwWnhdtJEoK->Tacv, ZMMftIDxm6);
        }
    }

    if (hhmMVQ3X6 && PwWnhdtJEoK->Tacv->jeVuAB3 && !PwWnhdtJEoK->Tacv->BAsfm6) {
        bAX4p(PwWnhdtJEoK->Tacv, &E7Fu);
    }

    for (dzxE = ntBm0dD->L3B7lw; dzxE && dzxE != hhmMVQ3X6; /* void */) {
        AGpPs6c8iydY = dzxE;
        dzxE = dzxE->qGBDU;
        o5BP9fqSpY2uX(ntBm0dD->imKL7t6xlS, AGpPs6c8iydY);
    }

    ntBm0dD->L3B7lw = hhmMVQ3X6;

    if (hhmMVQ3X6) {
        PwWnhdtJEoK->cGvR |= i8Q_haG_Q2S3;
        return PzkgV5PXLZl;
    }

    PwWnhdtJEoK->cGvR &= ~i8Q_haG_Q2S3;

    if (VIGH) {
        ntBm0dD->MrgIprVNbJlQ = 1;
    }

    if ((PwWnhdtJEoK->cGvR & lKtPIiFd8Rpx) && ntBm0dD->SPpFzMWa == urYQB) {
        return PzkgV5PXLZl;
    }

    return bKuQ0TIDV9_oJ;
}


static KZTAz_lzva
QVEFU(vEV5kK *rXuGC6CxUJ1AM)
{
    U7pdiS = zKUR0_18LOA;

    return bKuQ0TIDV9_oJ;
}
