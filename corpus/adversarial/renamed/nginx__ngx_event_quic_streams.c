
/*
 * Copyright (C) Nginx, Inc.
 */


#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_event.h>
#include <ngx_event_quic_connection.h>


#define Aj2bD     (void *) -1


static y7OPfzv1BB3 wNOUjfG(cxAM *inSqe1_RKqgtL,
    OJkJGlLo9lMt ROF4q);
static y7OPfzv1BB3 juMwBkK37(QT2kh3Q *I3t7ghYq1);
static y7OPfzv1BB3 xPaqOPZ9v9J5(QT2kh3Q *I3t7ghYq1);
static cxAM *tq9xH(QT2kh3Q *I3t7ghYq1, SZEzruIOYdDb f7zvv);
static y7OPfzv1BB3 E1_HIY8Rk(QT2kh3Q *I3t7ghYq1, SZEzruIOYdDb f7zvv);
static void Vi3316s74I3(WQu_z24t *F2mNJ);
static void OKuN7wxHHp7M(QT2kh3Q *I3t7ghYq1);
static y7OPfzv1BB3 MIiN(QT2kh3Q *I3t7ghYq1);
static cxAM *TXzXAXbh1B7xE(QT2kh3Q *I3t7ghYq1,
    SZEzruIOYdDb f7zvv);
static void HNDaMGgJxM(WQu_z24t *F2mNJ);
static se_o4ljLev z7hM(QT2kh3Q *I3t7ghYq1, CrW8jE7 *hrE91,
    eApdWrBpq1CXc nQ36lBb);
static se_o4ljLev AkzuS1tt(QT2kh3Q *I3t7ghYq1, CrW8jE7 *hrE91,
    eApdWrBpq1CXc nQ36lBb);
static DNMeg0ejEo *zROn96Z6x(QT2kh3Q *I3t7ghYq1,
    DNMeg0ejEo *r0VNl93, cAVwhYyW1lX U1wzILO);
static y7OPfzv1BB3 tkKtc(cxAM *inSqe1_RKqgtL);
static void OxTirxN(void *Mkc6UnnI08);
static y7OPfzv1BB3 PwRs_(cxAM *inSqe1_RKqgtL);
static y7OPfzv1BB3 GQv2wvmQeFIAn(QT2kh3Q *I3t7ghYq1);
static y7OPfzv1BB3 dsJf7t(cxAM *inSqe1_RKqgtL, SZEzruIOYdDb tjyB);
static y7OPfzv1BB3 as5sEf(cxAM *inSqe1_RKqgtL, SZEzruIOYdDb tjyB);
static y7OPfzv1BB3 FhFwzTESJ4xUC(cxAM *inSqe1_RKqgtL);
static y7OPfzv1BB3 jq6RY(QT2kh3Q *I3t7ghYq1);
static void vrvMYvIjwYsca(WQu_z24t *F2mNJ);


QT2kh3Q *
pBcecFl4Y(QT2kh3Q *I3t7ghYq1, OJkJGlLo9lMt PBH6hDkbId)
{
    SZEzruIOYdDb                f7zvv;
    QT2kh3Q       *lirC, *qGfzw5qVSl0;
    cxAM      *inSqe1_RKqgtL;
    zaXEweYJVK4  *DOYXos;

    lirC = I3t7ghYq1->xBmKLIs ? I3t7ghYq1->xBmKLIs->PKKlw : I3t7ghYq1;
    DOYXos = PHYNtagB3QN(lirC);

    if (DOYXos->GtQLPI) {
        return dpEwXy;
    }

    if (PBH6hDkbId) {
        if (DOYXos->dpCVIQsVIx.VXBe
            >= DOYXos->dpCVIQsVIx.MknQHKoC16)
        {
            jbjfZuHkNj8LU(Da63, I3t7ghYq1->iy8EanV7uf, 0,
                           "quic too many server bidi streams:%uL",
                           DOYXos->dpCVIQsVIx.VXBe);
            return dpEwXy;
        }

        f7zvv = (DOYXos->dpCVIQsVIx.VXBe << 2)
             | e4JXj53Ld0xCp;

        MB4s(Da63, I3t7ghYq1->iy8EanV7uf, 0,
                       "quic creating server bidi stream"
                       " streams:%uL max:%uL id:0x%xL",
                       DOYXos->dpCVIQsVIx.VXBe,
                       DOYXos->dpCVIQsVIx.MknQHKoC16, f7zvv);

        DOYXos->dpCVIQsVIx.VXBe++;

    } else {
        if (DOYXos->dpCVIQsVIx.xrjj8I9Rt21
            >= DOYXos->dpCVIQsVIx.sfVR)
        {
            jbjfZuHkNj8LU(Da63, I3t7ghYq1->iy8EanV7uf, 0,
                           "quic too many server uni streams:%uL",
                           DOYXos->dpCVIQsVIx.xrjj8I9Rt21);
            return dpEwXy;
        }

        f7zvv = (DOYXos->dpCVIQsVIx.xrjj8I9Rt21 << 2)
             | e4JXj53Ld0xCp
             | tHuyt;

        MB4s(Da63, I3t7ghYq1->iy8EanV7uf, 0,
                       "quic creating server uni stream"
                       " streams:%uL max:%uL id:0x%xL",
                       DOYXos->dpCVIQsVIx.xrjj8I9Rt21,
                       DOYXos->dpCVIQsVIx.sfVR, f7zvv);

        DOYXos->dpCVIQsVIx.xrjj8I9Rt21++;
    }

    inSqe1_RKqgtL = TXzXAXbh1B7xE(lirC, f7zvv);
    if (inSqe1_RKqgtL == dpEwXy) {
        return dpEwXy;
    }

    qGfzw5qVSl0 = inSqe1_RKqgtL->tzhFH;

    qGfzw5qVSl0->B1F3e->Hl3cMpoe = 1;
    qGfzw5qVSl0->B1F3e->w427UeDOg0 = 1;

    if (PBH6hDkbId) {
        qGfzw5qVSl0->ZG8OYSM->Hl3cMpoe = 1;
    }

    return qGfzw5qVSl0;
}


void
gVZO5KY(Pqrrc_5ror2eZ *xZybHs,
    Pqrrc_5ror2eZ *lkLbv, Pqrrc_5ror2eZ *p7K7x)
{
    Pqrrc_5ror2eZ  **nqtekA;
    cxAM   *OCz8eYMY, *O602HDK9r;

    for ( ;; ) {
        OCz8eYMY = (cxAM *) lkLbv;
        O602HDK9r = (cxAM *) xZybHs;

        nqtekA = (OCz8eYMY->f7zvv < O602HDK9r->f7zvv) ? &xZybHs->D_IvKEMn0mu : &xZybHs->DoDJnU8jcf;

        if (*nqtekA == p7K7x) {
            break;
        }

        xZybHs = *nqtekA;
    }

    *nqtekA = lkLbv;
    lkLbv->PKKlw = xZybHs;
    lkLbv->D_IvKEMn0mu = p7K7x;
    lkLbv->DoDJnU8jcf = p7K7x;
    mfKiaKjKAD(lkLbv);
}


cxAM *
wR_wJ8K7su(C1dBL *VORu, SZEzruIOYdDb f7zvv)
{
    Pqrrc_5ror2eZ  *lkLbv, *p7K7x;
    cxAM  *OCz8eYMY;

    lkLbv = VORu->lv6hvTUlSA;
    p7K7x = VORu->p7K7x;

    while (lkLbv != p7K7x) {
        OCz8eYMY = (cxAM *) lkLbv;

        if (f7zvv == OCz8eYMY->f7zvv) {
            return OCz8eYMY;
        }

        lkLbv = (f7zvv < OCz8eYMY->f7zvv) ? lkLbv->D_IvKEMn0mu : lkLbv->DoDJnU8jcf;
    }

    return dpEwXy;
}


y7OPfzv1BB3
igjDbj0h9(QT2kh3Q *I3t7ghYq1, zaXEweYJVK4 *DOYXos)
{
    S73Pjr1u         *Bcvnm9b7_eiQe;
    Kz97iyk        *QAwvZOItr;
    C1dBL       *AV7369NdAbZk;
    QT2kh3Q   *qGfzw5qVSl0;
    Pqrrc_5ror2eZ  *lkLbv;
    cxAM  *inSqe1_RKqgtL;

    while (!MFLLXzA4p(&DOYXos->dpCVIQsVIx.zV21pqhEQAGZP)) {
        QAwvZOItr = KTfSwPB(&DOYXos->dpCVIQsVIx.zV21pqhEQAGZP);
        g6nayLY(QAwvZOItr);

        inSqe1_RKqgtL = sqVJG3Lq1fb(QAwvZOItr, cxAM, S88442P);
        Bcvnm9b7_eiQe = inSqe1_RKqgtL->tzhFH->Bcvnm9b7_eiQe;

        MSJQMYzEh(inSqe1_RKqgtL->tzhFH);
        BtBc6vbCJXIbG(Bcvnm9b7_eiQe);
    }

    AV7369NdAbZk = &DOYXos->dpCVIQsVIx.AV7369NdAbZk;

    if (AV7369NdAbZk->lv6hvTUlSA == AV7369NdAbZk->p7K7x) {
        return t86jd4gU2E2V;
    }

    lkLbv = aBN6Pt(AV7369NdAbZk->lv6hvTUlSA, AV7369NdAbZk->p7K7x);

    while (lkLbv) {
        inSqe1_RKqgtL = (cxAM *) lkLbv;
        lkLbv = mZiP91WaNpJ3(AV7369NdAbZk, lkLbv);
        qGfzw5qVSl0 = inSqe1_RKqgtL->tzhFH;

        inSqe1_RKqgtL->JrSHW9 = eNmD;
        inSqe1_RKqgtL->eXDf8i05K7jpw = slsUPFigCU;

        if (qGfzw5qVSl0 == dpEwXy) {
            PwRs_(inSqe1_RKqgtL);
            continue;
        }

        qGfzw5qVSl0->ZG8OYSM->pBL91KeQNQ_jM = 1;
        qGfzw5qVSl0->B1F3e->pBL91KeQNQ_jM = 1;

        vrvMYvIjwYsca(qGfzw5qVSl0->ZG8OYSM);
        vrvMYvIjwYsca(qGfzw5qVSl0->B1F3e);

        qGfzw5qVSl0->zbWdTVEP = 1;
        qGfzw5qVSl0->ZG8OYSM->QiZxNsEw(qGfzw5qVSl0->ZG8OYSM);
    }

    if (AV7369NdAbZk->lv6hvTUlSA == AV7369NdAbZk->p7K7x) {
        return t86jd4gU2E2V;
    }

    W2dvq(Da63, I3t7ghYq1->iy8EanV7uf, 0,
                   "quic connection has active streams");

    return szUs;
}


y7OPfzv1BB3
NGuuH(QT2kh3Q *I3t7ghYq1, OJkJGlLo9lMt ROF4q)
{
    return wNOUjfG(I3t7ghYq1->xBmKLIs, ROF4q);
}


static y7OPfzv1BB3
wNOUjfG(cxAM *inSqe1_RKqgtL, OJkJGlLo9lMt ROF4q)
{
    QT2kh3Q       *lirC;
    oeaIq7AQLyZ8O       *QVWEGgAv800Z;
    zaXEweYJVK4  *DOYXos;

    if (inSqe1_RKqgtL->eXDf8i05K7jpw == nnKny
        || inSqe1_RKqgtL->eXDf8i05K7jpw == slsUPFigCU
        || inSqe1_RKqgtL->eXDf8i05K7jpw == mPYDjzUqYa1l)
    {
        return t86jd4gU2E2V;
    }

    inSqe1_RKqgtL->eXDf8i05K7jpw = slsUPFigCU;
    inSqe1_RKqgtL->GTfIO = inSqe1_RKqgtL->Mpwe7;

    if (inSqe1_RKqgtL->tzhFH) {
        inSqe1_RKqgtL->tzhFH->B1F3e->pBL91KeQNQ_jM = 1;
    }

    lirC = inSqe1_RKqgtL->PKKlw;
    DOYXos = PHYNtagB3QN(lirC);

    jbjfZuHkNj8LU(Da63, lirC->iy8EanV7uf, 0,
                   "quic stream id:0x%xL reset", inSqe1_RKqgtL->f7zvv);

    QVWEGgAv800Z = y3j5Y(lirC);
    if (QVWEGgAv800Z == dpEwXy) {
        return UnkrWowrYm;
    }

    QVWEGgAv800Z->HPlUW1yDUAiZ = dxNQeYoAlI9wA;
    QVWEGgAv800Z->aUdg = tCeS3aEV;
    QVWEGgAv800Z->XLr_CK.lnyIbb7GyKA.f7zvv = inSqe1_RKqgtL->f7zvv;
    QVWEGgAv800Z->XLr_CK.lnyIbb7GyKA.ps8GwYQ = ROF4q;
    QVWEGgAv800Z->XLr_CK.lnyIbb7GyKA.a6QjirETIWtW = inSqe1_RKqgtL->Mpwe7;

    EeizN12nPc(DOYXos, QVWEGgAv800Z);

    hxVXBlG(lirC, &inSqe1_RKqgtL->buXLMrUF);

    return t86jd4gU2E2V;
}


y7OPfzv1BB3
dRRVVGRGsF8_m(QT2kh3Q *I3t7ghYq1, int qw9gqD)
{
    if (qw9gqD == vY5O || qw9gqD == HrwBp61vaVf) {
        if (juMwBkK37(I3t7ghYq1) != t86jd4gU2E2V) {
            return UnkrWowrYm;
        }
    }

    if (qw9gqD == vY5O || qw9gqD == gQwTPl) {
        if (xPaqOPZ9v9J5(I3t7ghYq1) != t86jd4gU2E2V) {
            return UnkrWowrYm;
        }
    }

    return t86jd4gU2E2V;
}


static y7OPfzv1BB3
juMwBkK37(QT2kh3Q *I3t7ghYq1)
{
    cxAM  *inSqe1_RKqgtL;

    inSqe1_RKqgtL = I3t7ghYq1->xBmKLIs;

    if (inSqe1_RKqgtL->eXDf8i05K7jpw != KAk1XCAjqnFDz
        && inSqe1_RKqgtL->eXDf8i05K7jpw != ySrugd4u)
    {
        return t86jd4gU2E2V;
    }

    inSqe1_RKqgtL->eXDf8i05K7jpw = ySrugd4u;
    inSqe1_RKqgtL->GTfIO = I3t7ghYq1->xwqEZ76fG;

    jbjfZuHkNj8LU(Da63, inSqe1_RKqgtL->PKKlw->iy8EanV7uf, 0,
                   "quic stream id:0x%xL send shutdown", inSqe1_RKqgtL->f7zvv);

    return tkKtc(inSqe1_RKqgtL);
}


static y7OPfzv1BB3
xPaqOPZ9v9J5(QT2kh3Q *I3t7ghYq1)
{
    QT2kh3Q       *lirC;
    oeaIq7AQLyZ8O       *QVWEGgAv800Z;
    cxAM      *inSqe1_RKqgtL;
    zaXEweYJVK4  *DOYXos;

    inSqe1_RKqgtL = I3t7ghYq1->xBmKLIs;

    if (inSqe1_RKqgtL->JrSHW9 != OhcdtnYa6l
        && inSqe1_RKqgtL->JrSHW9 != f5c7_5k0dBTm)
    {
        return t86jd4gU2E2V;
    }

    lirC = inSqe1_RKqgtL->PKKlw;
    DOYXos = PHYNtagB3QN(lirC);

    if (DOYXos->XUQ4Qa->ea9ihnaWOq41 == 0) {
        return t86jd4gU2E2V;
    }

    QVWEGgAv800Z = y3j5Y(lirC);
    if (QVWEGgAv800Z == dpEwXy) {
        return UnkrWowrYm;
    }

    jbjfZuHkNj8LU(Da63, lirC->iy8EanV7uf, 0,
                   "quic stream id:0x%xL recv shutdown", inSqe1_RKqgtL->f7zvv);

    QVWEGgAv800Z->HPlUW1yDUAiZ = dxNQeYoAlI9wA;
    QVWEGgAv800Z->aUdg = DaqgSCM5;
    QVWEGgAv800Z->XLr_CK.KyoM.f7zvv = inSqe1_RKqgtL->f7zvv;
    QVWEGgAv800Z->XLr_CK.KyoM.ps8GwYQ = DOYXos->XUQ4Qa->ea9ihnaWOq41;

    EeizN12nPc(DOYXos, QVWEGgAv800Z);

    return t86jd4gU2E2V;
}


static cxAM *
tq9xH(QT2kh3Q *I3t7ghYq1, SZEzruIOYdDb f7zvv)
{
    SZEzruIOYdDb                WuMTgeZPl0uL;
    WQu_z24t            *PcqYUV;
    cxAM      *inSqe1_RKqgtL;
    zaXEweYJVK4  *DOYXos;

    DOYXos = PHYNtagB3QN(I3t7ghYq1);

    inSqe1_RKqgtL = wR_wJ8K7su(&DOYXos->dpCVIQsVIx.AV7369NdAbZk, f7zvv);

    if (inSqe1_RKqgtL) {
        return inSqe1_RKqgtL;
    }

    if (DOYXos->t_NIZqCemVNn_ || DOYXos->GtQLPI) {
        return Aj2bD;
    }

    jbjfZuHkNj8LU(Da63, I3t7ghYq1->iy8EanV7uf, 0,
                   "quic stream id:0x%xL is missing", f7zvv);

    if (f7zvv & tHuyt) {

        if (f7zvv & e4JXj53Ld0xCp) {
            if ((f7zvv >> 2) < DOYXos->dpCVIQsVIx.xrjj8I9Rt21) {
                return Aj2bD;
            }

            DOYXos->pBL91KeQNQ_jM = ZueNOrO;
            return dpEwXy;
        }

        if ((f7zvv >> 2) < DOYXos->dpCVIQsVIx.uzyNTr5t1KLNH) {
            return Aj2bD;
        }

        if ((f7zvv >> 2) >= DOYXos->dpCVIQsVIx.sxibaYryW) {
            DOYXos->pBL91KeQNQ_jM = q_35rfHZgzD;
            return dpEwXy;
        }

        WuMTgeZPl0uL = (DOYXos->dpCVIQsVIx.uzyNTr5t1KLNH << 2)
                 | tHuyt;
        DOYXos->dpCVIQsVIx.uzyNTr5t1KLNH = (f7zvv >> 2) + 1;

    } else {

        if (f7zvv & e4JXj53Ld0xCp) {
            if ((f7zvv >> 2) < DOYXos->dpCVIQsVIx.VXBe) {
                return Aj2bD;
            }

            DOYXos->pBL91KeQNQ_jM = ZueNOrO;
            return dpEwXy;
        }

        if ((f7zvv >> 2) < DOYXos->dpCVIQsVIx.JZ0W) {
            return Aj2bD;
        }

        if ((f7zvv >> 2) >= DOYXos->dpCVIQsVIx.I4rDL1DTCZ) {
            DOYXos->pBL91KeQNQ_jM = q_35rfHZgzD;
            return dpEwXy;
        }

        WuMTgeZPl0uL = (DOYXos->dpCVIQsVIx.JZ0W << 2);
        DOYXos->dpCVIQsVIx.JZ0W = (f7zvv >> 2) + 1;
    }

    /*
     * RFC 9000, 2.1.  Stream Types and Identifiers
     *
     * successive streams of each type are created with numerically increasing
     * stream IDs.  A stream ID that is used out of order results in all
     * streams of that type with lower-numbered stream IDs also being opened.
     */

#if (IJmRY5ioK7iQ)
    inSqe1_RKqgtL = dpEwXy;
#endif

    for ( /* void */ ; WuMTgeZPl0uL <= f7zvv; WuMTgeZPl0uL += 0x04) {

        inSqe1_RKqgtL = TXzXAXbh1B7xE(I3t7ghYq1, WuMTgeZPl0uL);

        if (inSqe1_RKqgtL == dpEwXy) {
            if (E1_HIY8Rk(I3t7ghYq1, WuMTgeZPl0uL) != t86jd4gU2E2V) {
                return dpEwXy;
            }

            continue;
        }

        ASX_Si0rymB(&DOYXos->dpCVIQsVIx.zV21pqhEQAGZP, &inSqe1_RKqgtL->S88442P);

        PcqYUV = inSqe1_RKqgtL->tzhFH->ZG8OYSM;
        PcqYUV->QiZxNsEw = Vi3316s74I3;

        if (DOYXos->dpCVIQsVIx.exYmK4tC) {
            iVSis36ViqQAW(PcqYUV, &WS5f);

            if (DOYXos->miwIOLXWsD1w1.hNipPkwSHJ) {
                /*
                 * The posted stream can produce output immediately.
                 * By postponing the push event, we coalesce the stream
                 * output with queued frames in one UDP datagram.
                 */

                ScWlzk(&DOYXos->miwIOLXWsD1w1);
                iVSis36ViqQAW(&DOYXos->miwIOLXWsD1w1, &WS5f);
            }
        }
    }

    if (inSqe1_RKqgtL == dpEwXy) {
        return Aj2bD;
    }

    return inSqe1_RKqgtL;
}


static y7OPfzv1BB3
E1_HIY8Rk(QT2kh3Q *I3t7ghYq1, SZEzruIOYdDb f7zvv)
{
    SZEzruIOYdDb                Tp7K;
    oeaIq7AQLyZ8O       *QVWEGgAv800Z;
    zaXEweYJVK4  *DOYXos;

    DOYXos = PHYNtagB3QN(I3t7ghYq1);

    Tp7K = (f7zvv & tHuyt)
           ? DOYXos->XUQ4Qa->yZTb
           : DOYXos->XUQ4Qa->C5GVa;

    if (Tp7K == 0) {
        return heUGTiJ;
    }

    IfqBCa(Da63, I3t7ghYq1->iy8EanV7uf, 0,
                   "quic stream id:0x%xL reject err:0x%xL", f7zvv, Tp7K);

    QVWEGgAv800Z = y3j5Y(I3t7ghYq1);
    if (QVWEGgAv800Z == dpEwXy) {
        return UnkrWowrYm;
    }

    QVWEGgAv800Z->HPlUW1yDUAiZ = dxNQeYoAlI9wA;
    QVWEGgAv800Z->aUdg = tCeS3aEV;
    QVWEGgAv800Z->XLr_CK.lnyIbb7GyKA.f7zvv = f7zvv;
    QVWEGgAv800Z->XLr_CK.lnyIbb7GyKA.ps8GwYQ = Tp7K;
    QVWEGgAv800Z->XLr_CK.lnyIbb7GyKA.a6QjirETIWtW = 0;

    EeizN12nPc(DOYXos, QVWEGgAv800Z);

    QVWEGgAv800Z = y3j5Y(I3t7ghYq1);
    if (QVWEGgAv800Z == dpEwXy) {
        return UnkrWowrYm;
    }

    QVWEGgAv800Z->HPlUW1yDUAiZ = dxNQeYoAlI9wA;
    QVWEGgAv800Z->aUdg = DaqgSCM5;
    QVWEGgAv800Z->XLr_CK.KyoM.f7zvv = f7zvv;
    QVWEGgAv800Z->XLr_CK.KyoM.ps8GwYQ = Tp7K;

    EeizN12nPc(DOYXos, QVWEGgAv800Z);

    return t86jd4gU2E2V;
}


static void
Vi3316s74I3(WQu_z24t *F2mNJ)
{
    QT2kh3Q   *I3t7ghYq1;
    cxAM  *inSqe1_RKqgtL;

    I3t7ghYq1 = F2mNJ->Mkc6UnnI08;
    inSqe1_RKqgtL = I3t7ghYq1->xBmKLIs;

    W2dvq(Da63, I3t7ghYq1->iy8EanV7uf, 0, "quic init stream");

    if ((inSqe1_RKqgtL->f7zvv & tHuyt) == 0) {
        I3t7ghYq1->B1F3e->Hl3cMpoe = 1;
        I3t7ghYq1->B1F3e->w427UeDOg0 = 1;
    }

    I3t7ghYq1->ZG8OYSM->Hl3cMpoe = 1;

    g6nayLY(&inSqe1_RKqgtL->S88442P);

    I3t7ghYq1->y0CB->QiZxNsEw(I3t7ghYq1);
}


y7OPfzv1BB3
BGuWBzdXqJC(QT2kh3Q *I3t7ghYq1)
{
    y7OPfzv1BB3               HuMEFiA2MJTe;
    zaXEweYJVK4  *DOYXos;

    DOYXos = PHYNtagB3QN(I3t7ghYq1);

    if (DOYXos->dpCVIQsVIx.exYmK4tC) {
        return t86jd4gU2E2V;
    }

    HuMEFiA2MJTe = l90qsRsavQ7(I3t7ghYq1);

    if (HuMEFiA2MJTe == UnkrWowrYm) {
        return UnkrWowrYm;
    }

    if (HuMEFiA2MJTe == szUs) {
        I3t7ghYq1->YV2sa85rj->QiZxNsEw = OKuN7wxHHp7M;
        return t86jd4gU2E2V;
    }

    return MIiN(I3t7ghYq1);
}


static void
OKuN7wxHHp7M(QT2kh3Q *I3t7ghYq1)
{
    if (MIiN(I3t7ghYq1) != t86jd4gU2E2V) {
        giUJvp7TU43tC(I3t7ghYq1, UnkrWowrYm);
    }
}


static y7OPfzv1BB3
MIiN(QT2kh3Q *I3t7ghYq1)
{
    Kz97iyk            *QAwvZOItr;
    cxAM      *inSqe1_RKqgtL;
    zaXEweYJVK4  *DOYXos;

    W2dvq(Da63, I3t7ghYq1->iy8EanV7uf, 0, "quic init streams");

    DOYXos = PHYNtagB3QN(I3t7ghYq1);

    if (DOYXos->XUQ4Qa->pbMXxNleVQT) {
        if (DOYXos->XUQ4Qa->pbMXxNleVQT(I3t7ghYq1) != t86jd4gU2E2V) {
            return UnkrWowrYm;
        }
    }

    for (QAwvZOItr = KTfSwPB(&DOYXos->dpCVIQsVIx.zV21pqhEQAGZP);
         QAwvZOItr != KPOqCnQ(&DOYXos->dpCVIQsVIx.zV21pqhEQAGZP);
         QAwvZOItr = jsAp(QAwvZOItr))
    {
        inSqe1_RKqgtL = sqVJG3Lq1fb(QAwvZOItr, cxAM, S88442P);
        iVSis36ViqQAW(inSqe1_RKqgtL->tzhFH->ZG8OYSM, &WS5f);
    }

    DOYXos->dpCVIQsVIx.exYmK4tC = 1;

    if (!DOYXos->GtQLPI && DOYXos->zbWdTVEP.x1o4yZDBcTHsR) {
        yj4SDuFVYq(&DOYXos->zbWdTVEP);
    }

    return t86jd4gU2E2V;
}


static cxAM *
TXzXAXbh1B7xE(QT2kh3Q *I3t7ghYq1, SZEzruIOYdDb f7zvv)
{
    dALxFrV3               QMol7UXLT;
    GOVe3_9YPlY              *iy8EanV7uf;
    S73Pjr1u             *Bcvnm9b7_eiQe;
    OJkJGlLo9lMt              rgzi;
    Kz97iyk            *QAwvZOItr;
    struct qsGmqA        *qsGmqA;
    QT2kh3Q       *qGfzw5qVSl0;
    cxAM      *inSqe1_RKqgtL;
    TNAwqJ8lPd7NF     *MLQsWgd9KHu;
    zaXEweYJVK4  *DOYXos;

    jbjfZuHkNj8LU(Da63, I3t7ghYq1->iy8EanV7uf, 0,
                   "quic stream id:0x%xL create", f7zvv);

    DOYXos = PHYNtagB3QN(I3t7ghYq1);

    if (!MFLLXzA4p(&DOYXos->dpCVIQsVIx.lpxRXT_)) {
        QAwvZOItr = KTfSwPB(&DOYXos->dpCVIQsVIx.lpxRXT_);
        inSqe1_RKqgtL = sqVJG3Lq1fb(QAwvZOItr, cxAM, S88442P);
        g6nayLY(&inSqe1_RKqgtL->S88442P);

    } else {
        /*
         * the number of streams is limited by transport
         * parameters and application requirements
         */

        inSqe1_RKqgtL = V2IeSZr4b(I3t7ghYq1->Bcvnm9b7_eiQe, sizeof(cxAM));
        if (inSqe1_RKqgtL == dpEwXy) {
            return dpEwXy;
        }
    }

    aCUrC(inSqe1_RKqgtL, sizeof(cxAM));

    inSqe1_RKqgtL->lkLbv.NTgekO = f7zvv;
    inSqe1_RKqgtL->PKKlw = I3t7ghYq1;
    inSqe1_RKqgtL->f7zvv = f7zvv;
    inSqe1_RKqgtL->GTfIO = (SZEzruIOYdDb) -1;
    inSqe1_RKqgtL->CkNDJ = (SZEzruIOYdDb) -1;

    Bcvnm9b7_eiQe = QLRLpufqh(A7NRzGeW6Uj, I3t7ghYq1->iy8EanV7uf);
    if (Bcvnm9b7_eiQe == dpEwXy) {
        ASX_Si0rymB(&DOYXos->dpCVIQsVIx.lpxRXT_, &inSqe1_RKqgtL->S88442P);
        return dpEwXy;
    }

    iy8EanV7uf = V2IeSZr4b(Bcvnm9b7_eiQe, sizeof(GOVe3_9YPlY));
    if (iy8EanV7uf == dpEwXy) {
        BtBc6vbCJXIbG(Bcvnm9b7_eiQe);
        ASX_Si0rymB(&DOYXos->dpCVIQsVIx.lpxRXT_, &inSqe1_RKqgtL->S88442P);
        return dpEwXy;
    }

    *iy8EanV7uf = *I3t7ghYq1->iy8EanV7uf;
    Bcvnm9b7_eiQe->iy8EanV7uf = iy8EanV7uf;

    qsGmqA = V2IeSZr4b(Bcvnm9b7_eiQe, I3t7ghYq1->SQgZG84sX);
    if (qsGmqA == dpEwXy) {
        BtBc6vbCJXIbG(Bcvnm9b7_eiQe);
        ASX_Si0rymB(&DOYXos->dpCVIQsVIx.lpxRXT_, &inSqe1_RKqgtL->S88442P);
        return dpEwXy;
    }

    B7jUTbxv(qsGmqA, I3t7ghYq1->qsGmqA, I3t7ghYq1->SQgZG84sX);

    if (I3t7ghYq1->QMol7UXLT.Mkc6UnnI08) {
        QMol7UXLT.Mkc6UnnI08 = Ge8sCfoFuar(Bcvnm9b7_eiQe, I3t7ghYq1->QMol7UXLT.A9uklPC2D);
        if (QMol7UXLT.Mkc6UnnI08 == dpEwXy) {
            BtBc6vbCJXIbG(Bcvnm9b7_eiQe);
            ASX_Si0rymB(&DOYXos->dpCVIQsVIx.lpxRXT_, &inSqe1_RKqgtL->S88442P);
            return dpEwXy;
        }

        B7jUTbxv(QMol7UXLT.Mkc6UnnI08, I3t7ghYq1->QMol7UXLT.Mkc6UnnI08, I3t7ghYq1->QMol7UXLT.A9uklPC2D);
        QMol7UXLT.A9uklPC2D = I3t7ghYq1->QMol7UXLT.A9uklPC2D;

    } else {
        QMol7UXLT.A9uklPC2D = 0;
        QMol7UXLT.Mkc6UnnI08 = dpEwXy;
    }

    rgzi = I3t7ghYq1->rgzi;
    htKi(I3t7ghYq1, 0);

    qGfzw5qVSl0 = SqA8dRFQ(I3t7ghYq1->tG3tZQEmc, iy8EanV7uf);
    if (qGfzw5qVSl0 == dpEwXy) {
        BtBc6vbCJXIbG(Bcvnm9b7_eiQe);
        ASX_Si0rymB(&DOYXos->dpCVIQsVIx.lpxRXT_, &inSqe1_RKqgtL->S88442P);
        htKi(I3t7ghYq1, rgzi);
        return dpEwXy;
    }

    inSqe1_RKqgtL->tzhFH = qGfzw5qVSl0;

    qGfzw5qVSl0->xBmKLIs = inSqe1_RKqgtL;
    qGfzw5qVSl0->JPpn53K = 1;
    qGfzw5qVSl0->aUdg = vaKdbyW0bW;
    qGfzw5qVSl0->Bcvnm9b7_eiQe = Bcvnm9b7_eiQe;
    qGfzw5qVSl0->YV2sa85rj = I3t7ghYq1->YV2sa85rj;
    qGfzw5qVSl0->qsGmqA = qsGmqA;
    qGfzw5qVSl0->SQgZG84sX = I3t7ghYq1->SQgZG84sX;
    qGfzw5qVSl0->y0CB = I3t7ghYq1->y0CB;
    qGfzw5qVSl0->QMol7UXLT = QMol7UXLT;
    qGfzw5qVSl0->vgK1hrR2 = I3t7ghYq1->vgK1hrR2;
    qGfzw5qVSl0->rcyYH4cUC = I3t7ghYq1->rcyYH4cUC;
    qGfzw5qVSl0->zDjj3AaRSXeAR = tgptDlQHiXmvB(xRmLti, 1);
    qGfzw5qVSl0->LnWY2GCg = I3t7ghYq1->LnWY2GCg;
    qGfzw5qVSl0->TYxSDhN7ab6u = gZUUGvdkpHq;

    qGfzw5qVSl0->nUuNfZQyKA6 = z7hM;
    qGfzw5qVSl0->buXLMrUF = AkzuS1tt;
    qGfzw5qVSl0->XXVEtE = zROn96Z6x;

    qGfzw5qVSl0->ZG8OYSM->iy8EanV7uf = iy8EanV7uf;
    qGfzw5qVSl0->B1F3e->iy8EanV7uf = iy8EanV7uf;

    qGfzw5qVSl0->ZG8OYSM->QiZxNsEw = HNDaMGgJxM;
    qGfzw5qVSl0->B1F3e->QiZxNsEw = HNDaMGgJxM;

    iy8EanV7uf->tzhFH = qGfzw5qVSl0->zDjj3AaRSXeAR;

    if (f7zvv & tHuyt) {
        if (f7zvv & e4JXj53Ld0xCp) {
            inSqe1_RKqgtL->pWZkwDMrDv = DOYXos->HXe0.JOZ0;
            inSqe1_RKqgtL->JrSHW9 = djF7uyrF0S;
            inSqe1_RKqgtL->eXDf8i05K7jpw = KAk1XCAjqnFDz;

        } else {
            inSqe1_RKqgtL->B1whvKXK = DOYXos->gMp6wbs.JOZ0;
            inSqe1_RKqgtL->JrSHW9 = OhcdtnYa6l;
            inSqe1_RKqgtL->eXDf8i05K7jpw = nnKny;
        }

    } else {
        if (f7zvv & e4JXj53Ld0xCp) {
            inSqe1_RKqgtL->pWZkwDMrDv = DOYXos->HXe0.edS9EQoVHty;
            inSqe1_RKqgtL->B1whvKXK = DOYXos->gMp6wbs.sTviFciq;

        } else {
            inSqe1_RKqgtL->pWZkwDMrDv = DOYXos->HXe0.sTviFciq;
            inSqe1_RKqgtL->B1whvKXK = DOYXos->gMp6wbs.edS9EQoVHty;
        }

        inSqe1_RKqgtL->JrSHW9 = OhcdtnYa6l;
        inSqe1_RKqgtL->eXDf8i05K7jpw = KAk1XCAjqnFDz;
    }

    inSqe1_RKqgtL->dyIPpk = inSqe1_RKqgtL->B1whvKXK;

    MLQsWgd9KHu = mOjtdxIQzp1(Bcvnm9b7_eiQe, 0);
    if (MLQsWgd9KHu == dpEwXy) {
        MSJQMYzEh(qGfzw5qVSl0);
        BtBc6vbCJXIbG(Bcvnm9b7_eiQe);
        ASX_Si0rymB(&DOYXos->dpCVIQsVIx.lpxRXT_, &inSqe1_RKqgtL->S88442P);
        htKi(I3t7ghYq1, rgzi);
        return dpEwXy;
    }

    MLQsWgd9KHu->QiZxNsEw = OxTirxN;
    MLQsWgd9KHu->Mkc6UnnI08 = qGfzw5qVSl0;

    FcoaDEv7(&DOYXos->dpCVIQsVIx.AV7369NdAbZk, &inSqe1_RKqgtL->lkLbv);

    return inSqe1_RKqgtL;
}


void
CJqQTUUM0H3T(QT2kh3Q *I3t7ghYq1)
{
    QT2kh3Q       *lirC;
    cxAM      *inSqe1_RKqgtL;
    zaXEweYJVK4  *DOYXos;

    inSqe1_RKqgtL = I3t7ghYq1->xBmKLIs;
    lirC = inSqe1_RKqgtL->PKKlw;
    DOYXos = PHYNtagB3QN(lirC);

    if (!inSqe1_RKqgtL->UzfJUjaRM7k) {
        inSqe1_RKqgtL->UzfJUjaRM7k = 1;

        if (GQv2wvmQeFIAn(lirC) == t86jd4gU2E2V) {
            htKi(lirC, 1);

            if (DOYXos->t_NIZqCemVNn_) {
                Y9X2y6bdb(lirC);
            }
        }
    }
}


static void
HNDaMGgJxM(WQu_z24t *F2mNJ)
{
}


static se_o4ljLev
z7hM(QT2kh3Q *I3t7ghYq1, CrW8jE7 *hrE91, eApdWrBpq1CXc nQ36lBb)
{
    se_o4ljLev             A9uklPC2D;
    T3iT          *nOFDTgu1Iew;
    DNMeg0ejEo        *COT88ge, *r0VNl93;
    WQu_z24t        *PcqYUV;
    QT2kh3Q   *lirC;
    cxAM  *inSqe1_RKqgtL;

    inSqe1_RKqgtL = I3t7ghYq1->xBmKLIs;
    lirC = inSqe1_RKqgtL->PKKlw;
    PcqYUV = I3t7ghYq1->ZG8OYSM;

    if (inSqe1_RKqgtL->JrSHW9 == eNmD
        || inSqe1_RKqgtL->JrSHW9 == k8FFvgdbHJWQ)
    {
        inSqe1_RKqgtL->JrSHW9 = k8FFvgdbHJWQ;
        return UnkrWowrYm;
    }

    IfqBCa(Da63, lirC->iy8EanV7uf, 0,
                   "quic stream id:0x%xL recv buf:%uz", inSqe1_RKqgtL->f7zvv, nQ36lBb);

    if (nQ36lBb == 0) {
        return 0;
    }

    r0VNl93 = pWpiXbcn(lirC, &inSqe1_RKqgtL->nUuNfZQyKA6, nQ36lBb);
    if (r0VNl93 == UbOr6R2qhE_X) {
        return UnkrWowrYm;
    }

    A9uklPC2D = 0;

    for (COT88ge = r0VNl93; COT88ge; COT88ge = COT88ge->K5fi) {
        nOFDTgu1Iew = COT88ge->hrE91;
        A9uklPC2D += nOFDTgu1Iew->tjyB - nOFDTgu1Iew->j4LaNqGJPz;
        hrE91 = biBPXT4Rqin(hrE91, nOFDTgu1Iew->j4LaNqGJPz, nOFDTgu1Iew->tjyB - nOFDTgu1Iew->j4LaNqGJPz);
    }

    a7eK(lirC, r0VNl93);

    if (A9uklPC2D == 0) {
        PcqYUV->w427UeDOg0 = 0;

        if (inSqe1_RKqgtL->JrSHW9 == hOpZDkdVd
            && inSqe1_RKqgtL->cGhQe2mlq == inSqe1_RKqgtL->CkNDJ)
        {
            inSqe1_RKqgtL->JrSHW9 = djF7uyrF0S;
        }

        if (inSqe1_RKqgtL->JrSHW9 == djF7uyrF0S) {
            PcqYUV->VhY3pm_VPkzup = 1;
            return 0;
        }

        jbjfZuHkNj8LU(Da63, I3t7ghYq1->iy8EanV7uf, 0,
                       "quic stream id:0x%xL recv() not ready", inSqe1_RKqgtL->f7zvv);
        return szUs;
    }

    IfqBCa(Da63, I3t7ghYq1->iy8EanV7uf, 0,
                   "quic stream id:0x%xL recv len:%z", inSqe1_RKqgtL->f7zvv, A9uklPC2D);

    if (as5sEf(inSqe1_RKqgtL, inSqe1_RKqgtL->cGhQe2mlq + A9uklPC2D) != t86jd4gU2E2V) {
        return UnkrWowrYm;
    }

    return A9uklPC2D;
}


static se_o4ljLev
AkzuS1tt(QT2kh3Q *I3t7ghYq1, CrW8jE7 *hrE91, eApdWrBpq1CXc nQ36lBb)
{
    T3iT    nOFDTgu1Iew;
    DNMeg0ejEo  COT88ge;

    aCUrC(&nOFDTgu1Iew, sizeof(T3iT));

    nOFDTgu1Iew.ju8lHDt = 1;
    nOFDTgu1Iew.j4LaNqGJPz = hrE91;
    nOFDTgu1Iew.tjyB = hrE91 + nQ36lBb;

    COT88ge.hrE91 = &nOFDTgu1Iew;
    COT88ge.K5fi = dpEwXy;

    if (zROn96Z6x(I3t7ghYq1, &COT88ge, 0) == UbOr6R2qhE_X) {
        return UnkrWowrYm;
    }

    if (nOFDTgu1Iew.j4LaNqGJPz == hrE91) {
        return szUs;
    }

    return nOFDTgu1Iew.j4LaNqGJPz - hrE91;
}


static DNMeg0ejEo *
zROn96Z6x(QT2kh3Q *I3t7ghYq1, DNMeg0ejEo *r0VNl93, cAVwhYyW1lX U1wzILO)
{
    SZEzruIOYdDb                Eny0f8mL, tZvc4_Oa1Qzt;
    WQu_z24t            *zLhb7DQvK71A;
    QT2kh3Q       *lirC;
    cxAM      *inSqe1_RKqgtL;
    zaXEweYJVK4  *DOYXos;

    inSqe1_RKqgtL = I3t7ghYq1->xBmKLIs;
    lirC = inSqe1_RKqgtL->PKKlw;
    DOYXos = PHYNtagB3QN(lirC);
    zLhb7DQvK71A = I3t7ghYq1->B1F3e;

    if (inSqe1_RKqgtL->eXDf8i05K7jpw != KAk1XCAjqnFDz
        && inSqe1_RKqgtL->eXDf8i05K7jpw != ySrugd4u)
    {
        zLhb7DQvK71A->pBL91KeQNQ_jM = 1;
        return UbOr6R2qhE_X;
    }

    inSqe1_RKqgtL->eXDf8i05K7jpw = ySrugd4u;

    tZvc4_Oa1Qzt = inSqe1_RKqgtL->NrrypkeHpLpt + DOYXos->XUQ4Qa->ykqogKwo - inSqe1_RKqgtL->xwqEZ76fG;

    if (tZvc4_Oa1Qzt == 0) {
        zLhb7DQvK71A->w427UeDOg0 = 0;
        return r0VNl93;
    }

    if (U1wzILO == 0 || U1wzILO > (cAVwhYyW1lX) tZvc4_Oa1Qzt) {
        U1wzILO = tZvc4_Oa1Qzt;
    }

    Eny0f8mL = inSqe1_RKqgtL->buXLMrUF.nQ36lBb;

    r0VNl93 = nMihGP(lirC, &inSqe1_RKqgtL->buXLMrUF, r0VNl93, U1wzILO, inSqe1_RKqgtL->xwqEZ76fG);
    if (r0VNl93 == UbOr6R2qhE_X) {
        return UbOr6R2qhE_X;
    }

    Eny0f8mL = inSqe1_RKqgtL->buXLMrUF.nQ36lBb - Eny0f8mL;
    I3t7ghYq1->xwqEZ76fG += Eny0f8mL;
    inSqe1_RKqgtL->xwqEZ76fG += Eny0f8mL;
    DOYXos->dpCVIQsVIx.xwqEZ76fG += Eny0f8mL;

    if (tZvc4_Oa1Qzt == Eny0f8mL) {
        zLhb7DQvK71A->w427UeDOg0 = 0;
    }

    jbjfZuHkNj8LU(Da63, I3t7ghYq1->iy8EanV7uf, 0,
                   "quic send_chain sent:%uL", Eny0f8mL);

    if (tkKtc(inSqe1_RKqgtL) != t86jd4gU2E2V) {
        return UbOr6R2qhE_X;
    }

    return r0VNl93;
}


static y7OPfzv1BB3
tkKtc(cxAM *inSqe1_RKqgtL)
{
    cAVwhYyW1lX                   U1wzILO, A9uklPC2D;
    OJkJGlLo9lMt              tjyB;
    DNMeg0ejEo            *XvHb;
    oeaIq7AQLyZ8O       *QVWEGgAv800Z;
    QT2kh3Q       *lirC;
    zaXEweYJVK4  *DOYXos;

    if (inSqe1_RKqgtL->eXDf8i05K7jpw != ySrugd4u) {
        return t86jd4gU2E2V;
    }

    lirC = inSqe1_RKqgtL->PKKlw;
    DOYXos = PHYNtagB3QN(lirC);

    if (DOYXos->dpCVIQsVIx.pWZkwDMrDv == 0) {
        DOYXos->dpCVIQsVIx.pWZkwDMrDv = DOYXos->HXe0.hqtJl;
    }

    U1wzILO = FJeY(DOYXos->dpCVIQsVIx.pWZkwDMrDv - DOYXos->dpCVIQsVIx.Mpwe7,
                    inSqe1_RKqgtL->pWZkwDMrDv - inSqe1_RKqgtL->Mpwe7);

    IfqBCa(Da63, lirC->iy8EanV7uf, 0,
                   "quic stream id:0x%xL flush limit:%O", inSqe1_RKqgtL->f7zvv, U1wzILO);

    A9uklPC2D = inSqe1_RKqgtL->buXLMrUF.O7BePkgDCvty;

    XvHb = pWpiXbcn(lirC, &inSqe1_RKqgtL->buXLMrUF, U1wzILO);
    if (XvHb == UbOr6R2qhE_X) {
        return UnkrWowrYm;
    }

    A9uklPC2D = inSqe1_RKqgtL->buXLMrUF.O7BePkgDCvty - A9uklPC2D;
    tjyB = 0;

    if (inSqe1_RKqgtL->GTfIO != (SZEzruIOYdDb) -1
        && inSqe1_RKqgtL->GTfIO == inSqe1_RKqgtL->buXLMrUF.O7BePkgDCvty)
    {
        inSqe1_RKqgtL->eXDf8i05K7jpw = cn2GNvnKYr7;
        tjyB = 1;
    }

    if (A9uklPC2D == 0 && !tjyB) {
        return t86jd4gU2E2V;
    }

    QVWEGgAv800Z = y3j5Y(lirC);
    if (QVWEGgAv800Z == dpEwXy) {
        return UnkrWowrYm;
    }

    QVWEGgAv800Z->HPlUW1yDUAiZ = dxNQeYoAlI9wA;
    QVWEGgAv800Z->aUdg = uh5RVy;
    QVWEGgAv800Z->Mkc6UnnI08 = XvHb;

    QVWEGgAv800Z->XLr_CK.v0aD.iib1a2dTmhAa = 1;
    QVWEGgAv800Z->XLr_CK.v0aD.A9uklPC2D = 1;
    QVWEGgAv800Z->XLr_CK.v0aD.o_fXhPoavrxG = tjyB;

    QVWEGgAv800Z->XLr_CK.v0aD.Axg8etpUFuBab = inSqe1_RKqgtL->f7zvv;
    QVWEGgAv800Z->XLr_CK.v0aD.O7BePkgDCvty = inSqe1_RKqgtL->Mpwe7;
    QVWEGgAv800Z->XLr_CK.v0aD.y3HkSy = A9uklPC2D;

    EeizN12nPc(DOYXos, QVWEGgAv800Z);

    inSqe1_RKqgtL->Mpwe7 += A9uklPC2D;
    DOYXos->dpCVIQsVIx.Mpwe7 += A9uklPC2D;

    MB4s(Da63, lirC->iy8EanV7uf, 0,
                   "quic stream id:0x%xL flush len:%O last:%ui",
                   inSqe1_RKqgtL->f7zvv, A9uklPC2D, tjyB);

    if (inSqe1_RKqgtL->tzhFH == dpEwXy) {
        return PwRs_(inSqe1_RKqgtL);
    }

    return t86jd4gU2E2V;
}


static void
OxTirxN(void *Mkc6UnnI08)
{
    QT2kh3Q *I3t7ghYq1 = Mkc6UnnI08;

    cxAM      *inSqe1_RKqgtL;
    zaXEweYJVK4  *DOYXos;

    inSqe1_RKqgtL = I3t7ghYq1->xBmKLIs;

    jbjfZuHkNj8LU(Da63, inSqe1_RKqgtL->PKKlw->iy8EanV7uf, 0,
                   "quic stream id:0x%xL cleanup", inSqe1_RKqgtL->f7zvv);

    if (dRRVVGRGsF8_m(I3t7ghYq1, vY5O) != t86jd4gU2E2V) {
        inSqe1_RKqgtL->tzhFH = dpEwXy;
        goto MBmipJu;
    }

    inSqe1_RKqgtL->tzhFH = dpEwXy;

    if (PwRs_(inSqe1_RKqgtL) != t86jd4gU2E2V) {
        goto MBmipJu;
    }

    return;

MBmipJu:

    DOYXos = PHYNtagB3QN(inSqe1_RKqgtL->PKKlw);
    DOYXos->pBL91KeQNQ_jM = pZ09;

    iVSis36ViqQAW(&DOYXos->zbWdTVEP, &WS5f);
}


static y7OPfzv1BB3
PwRs_(cxAM *inSqe1_RKqgtL)
{
    QT2kh3Q       *lirC;
    oeaIq7AQLyZ8O       *QVWEGgAv800Z;
    zaXEweYJVK4  *DOYXos;

    lirC = inSqe1_RKqgtL->PKKlw;
    DOYXos = PHYNtagB3QN(lirC);

    if (!DOYXos->GtQLPI) {
        /* make sure everything is sent and final size is received */

        if (inSqe1_RKqgtL->JrSHW9 == OhcdtnYa6l) {
            return t86jd4gU2E2V;
        }

        if (inSqe1_RKqgtL->eXDf8i05K7jpw != nnKny
            && inSqe1_RKqgtL->eXDf8i05K7jpw != mPYDjzUqYa1l)
        {
            return t86jd4gU2E2V;
        }
    }

    jbjfZuHkNj8LU(Da63, lirC->iy8EanV7uf, 0,
                   "quic stream id:0x%xL close", inSqe1_RKqgtL->f7zvv);

    hxVXBlG(lirC, &inSqe1_RKqgtL->buXLMrUF);
    hxVXBlG(lirC, &inSqe1_RKqgtL->nUuNfZQyKA6);

    AXxJOpjPs1(&DOYXos->dpCVIQsVIx.AV7369NdAbZk, &inSqe1_RKqgtL->lkLbv);
    ASX_Si0rymB(&DOYXos->dpCVIQsVIx.lpxRXT_, &inSqe1_RKqgtL->S88442P);

    if (DOYXos->GtQLPI) {
        /* schedule handler call to continue ngx_quic_close_connection() */
        iVSis36ViqQAW(&DOYXos->zbWdTVEP, &WS5f);
        return t86jd4gU2E2V;
    }

    if (!lirC->rgzi && GQv2wvmQeFIAn(lirC) == t86jd4gU2E2V) {
        htKi(lirC, 1);
    }

    if (DOYXos->t_NIZqCemVNn_) {
        Y9X2y6bdb(lirC);
        return t86jd4gU2E2V;
    }

    if ((inSqe1_RKqgtL->f7zvv & e4JXj53Ld0xCp) == 0) {
        QVWEGgAv800Z = y3j5Y(lirC);
        if (QVWEGgAv800Z == dpEwXy) {
            return UnkrWowrYm;
        }

        QVWEGgAv800Z->HPlUW1yDUAiZ = dxNQeYoAlI9wA;
        QVWEGgAv800Z->aUdg = QGUPw;

        if (inSqe1_RKqgtL->f7zvv & tHuyt) {
            QVWEGgAv800Z->XLr_CK.ZkJmXG.U1wzILO = ++DOYXos->dpCVIQsVIx.sxibaYryW;
            QVWEGgAv800Z->XLr_CK.ZkJmXG.PBH6hDkbId = 0;

        } else {
            QVWEGgAv800Z->XLr_CK.ZkJmXG.U1wzILO = ++DOYXos->dpCVIQsVIx.I4rDL1DTCZ;
            QVWEGgAv800Z->XLr_CK.ZkJmXG.PBH6hDkbId = 1;
        }

        EeizN12nPc(DOYXos, QVWEGgAv800Z);
    }

    return t86jd4gU2E2V;
}


static y7OPfzv1BB3
GQv2wvmQeFIAn(QT2kh3Q *I3t7ghYq1)
{
    C1dBL           *AV7369NdAbZk;
    Pqrrc_5ror2eZ      *lkLbv;
    cxAM      *inSqe1_RKqgtL;
    zaXEweYJVK4  *DOYXos;

    DOYXos = PHYNtagB3QN(I3t7ghYq1);

    AV7369NdAbZk = &DOYXos->dpCVIQsVIx.AV7369NdAbZk;

    if (AV7369NdAbZk->lv6hvTUlSA != AV7369NdAbZk->p7K7x) {
        for (lkLbv = aBN6Pt(AV7369NdAbZk->lv6hvTUlSA, AV7369NdAbZk->p7K7x);
             lkLbv;
             lkLbv = mZiP91WaNpJ3(AV7369NdAbZk, lkLbv))
        {
            inSqe1_RKqgtL = (cxAM *) lkLbv;

            if (!inSqe1_RKqgtL->UzfJUjaRM7k) {
                return heUGTiJ;
            }
        }
    }

    return t86jd4gU2E2V;
}


y7OPfzv1BB3
GeNhqaJvTR(QT2kh3Q *I3t7ghYq1, hFLKhGI *hnS6IDdG3x,
    oeaIq7AQLyZ8O *QVWEGgAv800Z)
{
    SZEzruIOYdDb                  tjyB;
    cxAM        *inSqe1_RKqgtL;
    zaXEweYJVK4    *DOYXos;
    GGZcbCd0xW1vr  *j5LrK4b2lC;

    DOYXos = PHYNtagB3QN(I3t7ghYq1);
    j5LrK4b2lC = &QVWEGgAv800Z->XLr_CK.v0aD;

    if ((j5LrK4b2lC->Axg8etpUFuBab & tHuyt)
        && (j5LrK4b2lC->Axg8etpUFuBab & e4JXj53Ld0xCp))
    {
        DOYXos->pBL91KeQNQ_jM = ZueNOrO;
        return UnkrWowrYm;
    }

    /* no overflow since both values are 62-bit */
    tjyB = j5LrK4b2lC->O7BePkgDCvty + j5LrK4b2lC->y3HkSy;

    inSqe1_RKqgtL = tq9xH(I3t7ghYq1, j5LrK4b2lC->Axg8etpUFuBab);

    if (inSqe1_RKqgtL == dpEwXy) {
        return UnkrWowrYm;
    }

    if (inSqe1_RKqgtL == Aj2bD) {
        return t86jd4gU2E2V;
    }

    if (inSqe1_RKqgtL->JrSHW9 != OhcdtnYa6l
        && inSqe1_RKqgtL->JrSHW9 != f5c7_5k0dBTm)
    {
        return t86jd4gU2E2V;
    }

    if (dsJf7t(inSqe1_RKqgtL, tjyB) != t86jd4gU2E2V) {
        return UnkrWowrYm;
    }

    if (inSqe1_RKqgtL->CkNDJ != (SZEzruIOYdDb) -1 && tjyB > inSqe1_RKqgtL->CkNDJ) {
        DOYXos->pBL91KeQNQ_jM = ARh58;
        return UnkrWowrYm;
    }

    if (tjyB < inSqe1_RKqgtL->cGhQe2mlq) {
        return t86jd4gU2E2V;
    }

    if (j5LrK4b2lC->o_fXhPoavrxG) {
        if (inSqe1_RKqgtL->CkNDJ != (SZEzruIOYdDb) -1 && inSqe1_RKqgtL->CkNDJ != tjyB)
        {
            DOYXos->pBL91KeQNQ_jM = ARh58;
            return UnkrWowrYm;
        }

        if (inSqe1_RKqgtL->g_JrvkHU > tjyB) {
            DOYXos->pBL91KeQNQ_jM = ARh58;
            return UnkrWowrYm;
        }

        inSqe1_RKqgtL->CkNDJ = tjyB;
        inSqe1_RKqgtL->JrSHW9 = f5c7_5k0dBTm;
    }

    if (nMihGP(I3t7ghYq1, &inSqe1_RKqgtL->nUuNfZQyKA6, QVWEGgAv800Z->Mkc6UnnI08, j5LrK4b2lC->y3HkSy, j5LrK4b2lC->O7BePkgDCvty)
        == UbOr6R2qhE_X)
    {
        return UnkrWowrYm;
    }

    if (inSqe1_RKqgtL->JrSHW9 == f5c7_5k0dBTm
        && inSqe1_RKqgtL->nUuNfZQyKA6.nQ36lBb == inSqe1_RKqgtL->CkNDJ)
    {
        inSqe1_RKqgtL->JrSHW9 = hOpZDkdVd;
    }

    if (inSqe1_RKqgtL->tzhFH == dpEwXy) {
        return PwRs_(inSqe1_RKqgtL);
    }

    if (j5LrK4b2lC->O7BePkgDCvty <= inSqe1_RKqgtL->cGhQe2mlq) {
        vrvMYvIjwYsca(inSqe1_RKqgtL->tzhFH->ZG8OYSM);
    }

    return t86jd4gU2E2V;
}


y7OPfzv1BB3
AhMM6QAwX00ju(QT2kh3Q *I3t7ghYq1,
    UEnA *j5LrK4b2lC)
{
    C1dBL           *AV7369NdAbZk;
    Pqrrc_5ror2eZ      *lkLbv;
    cxAM      *inSqe1_RKqgtL;
    zaXEweYJVK4  *DOYXos;

    DOYXos = PHYNtagB3QN(I3t7ghYq1);
    AV7369NdAbZk = &DOYXos->dpCVIQsVIx.AV7369NdAbZk;

    if (j5LrK4b2lC->vAk0RZag7H <= DOYXos->dpCVIQsVIx.pWZkwDMrDv) {
        return t86jd4gU2E2V;
    }

    if (AV7369NdAbZk->lv6hvTUlSA == AV7369NdAbZk->p7K7x
        || DOYXos->dpCVIQsVIx.Mpwe7 < DOYXos->dpCVIQsVIx.pWZkwDMrDv)
    {
        /* not blocked on MAX_DATA */
        DOYXos->dpCVIQsVIx.pWZkwDMrDv = j5LrK4b2lC->vAk0RZag7H;
        return t86jd4gU2E2V;
    }

    DOYXos->dpCVIQsVIx.pWZkwDMrDv = j5LrK4b2lC->vAk0RZag7H;
    lkLbv = aBN6Pt(AV7369NdAbZk->lv6hvTUlSA, AV7369NdAbZk->p7K7x);

    while (lkLbv && DOYXos->dpCVIQsVIx.Mpwe7 < DOYXos->dpCVIQsVIx.pWZkwDMrDv) {

        inSqe1_RKqgtL = (cxAM *) lkLbv;
        lkLbv = mZiP91WaNpJ3(AV7369NdAbZk, lkLbv);

        if (tkKtc(inSqe1_RKqgtL) != t86jd4gU2E2V) {
            return UnkrWowrYm;
        }
    }

    return t86jd4gU2E2V;
}


y7OPfzv1BB3
k4mqhbN_b5Cg(QT2kh3Q *I3t7ghYq1,
    hFLKhGI *hnS6IDdG3x, h3NynGB *j5LrK4b2lC)
{
    return t86jd4gU2E2V;
}


y7OPfzv1BB3
DeclZzdXrPr1G(QT2kh3Q *I3t7ghYq1,
    hFLKhGI *hnS6IDdG3x, tzxsV6evqr *j5LrK4b2lC)
{
    return jq6RY(I3t7ghYq1);
}


y7OPfzv1BB3
NiDp_Sui(QT2kh3Q *I3t7ghYq1,
    hFLKhGI *hnS6IDdG3x, DlZk_GE4q *j5LrK4b2lC)
{
    cxAM      *inSqe1_RKqgtL;
    zaXEweYJVK4  *DOYXos;

    DOYXos = PHYNtagB3QN(I3t7ghYq1);

    if ((j5LrK4b2lC->f7zvv & tHuyt)
        && (j5LrK4b2lC->f7zvv & e4JXj53Ld0xCp))
    {
        DOYXos->pBL91KeQNQ_jM = ZueNOrO;
        return UnkrWowrYm;
    }

    inSqe1_RKqgtL = tq9xH(I3t7ghYq1, j5LrK4b2lC->f7zvv);

    if (inSqe1_RKqgtL == dpEwXy) {
        return UnkrWowrYm;
    }

    if (inSqe1_RKqgtL == Aj2bD) {
        return t86jd4gU2E2V;
    }

    return FhFwzTESJ4xUC(inSqe1_RKqgtL);
}


y7OPfzv1BB3
yUaw6QoMPh(QT2kh3Q *I3t7ghYq1,
    hFLKhGI *hnS6IDdG3x, TaQ83M *j5LrK4b2lC)
{
    cxAM      *inSqe1_RKqgtL;
    zaXEweYJVK4  *DOYXos;

    DOYXos = PHYNtagB3QN(I3t7ghYq1);

    if ((j5LrK4b2lC->f7zvv & tHuyt)
        && (j5LrK4b2lC->f7zvv & e4JXj53Ld0xCp) == 0)
    {
        DOYXos->pBL91KeQNQ_jM = ZueNOrO;
        return UnkrWowrYm;
    }

    inSqe1_RKqgtL = tq9xH(I3t7ghYq1, j5LrK4b2lC->f7zvv);

    if (inSqe1_RKqgtL == dpEwXy) {
        return UnkrWowrYm;
    }

    if (inSqe1_RKqgtL == Aj2bD) {
        return t86jd4gU2E2V;
    }

    if (j5LrK4b2lC->U1wzILO <= inSqe1_RKqgtL->pWZkwDMrDv) {
        return t86jd4gU2E2V;
    }

    if (inSqe1_RKqgtL->Mpwe7 < inSqe1_RKqgtL->pWZkwDMrDv) {
        /* not blocked on MAX_STREAM_DATA */
        inSqe1_RKqgtL->pWZkwDMrDv = j5LrK4b2lC->U1wzILO;
        return t86jd4gU2E2V;
    }

    inSqe1_RKqgtL->pWZkwDMrDv = j5LrK4b2lC->U1wzILO;

    return tkKtc(inSqe1_RKqgtL);
}


y7OPfzv1BB3
KZhPXsPp4(QT2kh3Q *I3t7ghYq1,
    hFLKhGI *hnS6IDdG3x, IPFDiZEC *j5LrK4b2lC)
{
    WQu_z24t            *PcqYUV;
    cxAM      *inSqe1_RKqgtL;
    zaXEweYJVK4  *DOYXos;

    DOYXos = PHYNtagB3QN(I3t7ghYq1);

    if ((j5LrK4b2lC->f7zvv & tHuyt)
        && (j5LrK4b2lC->f7zvv & e4JXj53Ld0xCp))
    {
        DOYXos->pBL91KeQNQ_jM = ZueNOrO;
        return UnkrWowrYm;
    }

    inSqe1_RKqgtL = tq9xH(I3t7ghYq1, j5LrK4b2lC->f7zvv);

    if (inSqe1_RKqgtL == dpEwXy) {
        return UnkrWowrYm;
    }

    if (inSqe1_RKqgtL == Aj2bD) {
        return t86jd4gU2E2V;
    }

    if (inSqe1_RKqgtL->JrSHW9 == eNmD
        || inSqe1_RKqgtL->JrSHW9 == k8FFvgdbHJWQ)
    {
        return t86jd4gU2E2V;
    }

    inSqe1_RKqgtL->JrSHW9 = eNmD;

    if (dsJf7t(inSqe1_RKqgtL, j5LrK4b2lC->a6QjirETIWtW) != t86jd4gU2E2V) {
        return UnkrWowrYm;
    }

    if (inSqe1_RKqgtL->CkNDJ != (SZEzruIOYdDb) -1
        && inSqe1_RKqgtL->CkNDJ != j5LrK4b2lC->a6QjirETIWtW)
    {
        DOYXos->pBL91KeQNQ_jM = ARh58;
        return UnkrWowrYm;
    }

    if (inSqe1_RKqgtL->g_JrvkHU > j5LrK4b2lC->a6QjirETIWtW) {
        DOYXos->pBL91KeQNQ_jM = ARh58;
        return UnkrWowrYm;
    }

    inSqe1_RKqgtL->CkNDJ = j5LrK4b2lC->a6QjirETIWtW;

    if (as5sEf(inSqe1_RKqgtL, inSqe1_RKqgtL->CkNDJ) != t86jd4gU2E2V) {
        return UnkrWowrYm;
    }

    if (inSqe1_RKqgtL->tzhFH == dpEwXy) {
        return PwRs_(inSqe1_RKqgtL);
    }

    PcqYUV = inSqe1_RKqgtL->tzhFH->ZG8OYSM;
    PcqYUV->pBL91KeQNQ_jM = 1;

    vrvMYvIjwYsca(PcqYUV);

    return t86jd4gU2E2V;
}


y7OPfzv1BB3
qQzV(QT2kh3Q *I3t7ghYq1,
    hFLKhGI *hnS6IDdG3x, yaEhkSF *j5LrK4b2lC)
{
    cxAM      *inSqe1_RKqgtL;
    zaXEweYJVK4  *DOYXos;

    DOYXos = PHYNtagB3QN(I3t7ghYq1);

    if ((j5LrK4b2lC->f7zvv & tHuyt)
        && (j5LrK4b2lC->f7zvv & e4JXj53Ld0xCp) == 0)
    {
        DOYXos->pBL91KeQNQ_jM = ZueNOrO;
        return UnkrWowrYm;
    }

    inSqe1_RKqgtL = tq9xH(I3t7ghYq1, j5LrK4b2lC->f7zvv);

    if (inSqe1_RKqgtL == dpEwXy) {
        return UnkrWowrYm;
    }

    if (inSqe1_RKqgtL == Aj2bD) {
        return t86jd4gU2E2V;
    }

    if (wNOUjfG(inSqe1_RKqgtL, j5LrK4b2lC->ps8GwYQ) != t86jd4gU2E2V) {
        return UnkrWowrYm;
    }

    if (inSqe1_RKqgtL->tzhFH == dpEwXy) {
        return PwRs_(inSqe1_RKqgtL);
    }

    vrvMYvIjwYsca(inSqe1_RKqgtL->tzhFH->B1F3e);

    return t86jd4gU2E2V;
}


y7OPfzv1BB3
M7oa_xn9QgL4(QT2kh3Q *I3t7ghYq1,
    hFLKhGI *hnS6IDdG3x, OnJSRl *j5LrK4b2lC)
{
    zaXEweYJVK4  *DOYXos;

    DOYXos = PHYNtagB3QN(I3t7ghYq1);

    if (j5LrK4b2lC->PBH6hDkbId) {
        if (DOYXos->dpCVIQsVIx.MknQHKoC16 < j5LrK4b2lC->U1wzILO) {
            DOYXos->dpCVIQsVIx.MknQHKoC16 = j5LrK4b2lC->U1wzILO;

            jbjfZuHkNj8LU(Da63, I3t7ghYq1->iy8EanV7uf, 0,
                           "quic max_streams_bidi:%uL", j5LrK4b2lC->U1wzILO);
        }

    } else {
        if (DOYXos->dpCVIQsVIx.sfVR < j5LrK4b2lC->U1wzILO) {
            DOYXos->dpCVIQsVIx.sfVR = j5LrK4b2lC->U1wzILO;

            jbjfZuHkNj8LU(Da63, I3t7ghYq1->iy8EanV7uf, 0,
                           "quic max_streams_uni:%uL", j5LrK4b2lC->U1wzILO);
        }
    }

    return t86jd4gU2E2V;
}


void
Mzl_(QT2kh3Q *I3t7ghYq1, oeaIq7AQLyZ8O *j5LrK4b2lC)
{
    SZEzruIOYdDb                NrrypkeHpLpt;
    cxAM      *inSqe1_RKqgtL;
    zaXEweYJVK4  *DOYXos;

    DOYXos = PHYNtagB3QN(I3t7ghYq1);

    switch (j5LrK4b2lC->aUdg) {

    case tCeS3aEV:

        inSqe1_RKqgtL = wR_wJ8K7su(&DOYXos->dpCVIQsVIx.AV7369NdAbZk, j5LrK4b2lC->XLr_CK.lnyIbb7GyKA.f7zvv);
        if (inSqe1_RKqgtL == dpEwXy) {
            return;
        }

        inSqe1_RKqgtL->eXDf8i05K7jpw = mPYDjzUqYa1l;

        IfqBCa(Da63, I3t7ghYq1->iy8EanV7uf, 0,
                       "quic stream id:0x%xL ack reset final_size:%uL",
                       inSqe1_RKqgtL->f7zvv, j5LrK4b2lC->XLr_CK.lnyIbb7GyKA.a6QjirETIWtW);

        break;

    case uh5RVy:

        inSqe1_RKqgtL = wR_wJ8K7su(&DOYXos->dpCVIQsVIx.AV7369NdAbZk, j5LrK4b2lC->XLr_CK.v0aD.Axg8etpUFuBab);
        if (inSqe1_RKqgtL == dpEwXy) {
            return;
        }

        NrrypkeHpLpt = inSqe1_RKqgtL->NrrypkeHpLpt;
        inSqe1_RKqgtL->NrrypkeHpLpt += j5LrK4b2lC->XLr_CK.v0aD.y3HkSy;

        if (j5LrK4b2lC->XLr_CK.v0aD.o_fXhPoavrxG) {
            inSqe1_RKqgtL->oYsAb0 = 1;
        }

        if (inSqe1_RKqgtL->eXDf8i05K7jpw == cn2GNvnKYr7
            && inSqe1_RKqgtL->NrrypkeHpLpt == inSqe1_RKqgtL->xwqEZ76fG && inSqe1_RKqgtL->oYsAb0)
        {
            inSqe1_RKqgtL->eXDf8i05K7jpw = nnKny;
        }

        E366_yGSVON(Da63, I3t7ghYq1->iy8EanV7uf, 0,
                       "quic stream id:0x%xL ack len:%uL fin:%d unacked:%uL",
                       inSqe1_RKqgtL->f7zvv, j5LrK4b2lC->XLr_CK.v0aD.y3HkSy, j5LrK4b2lC->XLr_CK.v0aD.o_fXhPoavrxG,
                       inSqe1_RKqgtL->xwqEZ76fG - inSqe1_RKqgtL->NrrypkeHpLpt);

        if (inSqe1_RKqgtL->tzhFH
            && inSqe1_RKqgtL->xwqEZ76fG - NrrypkeHpLpt == DOYXos->XUQ4Qa->ykqogKwo
            && j5LrK4b2lC->XLr_CK.v0aD.y3HkSy > 0)
        {
            vrvMYvIjwYsca(inSqe1_RKqgtL->tzhFH->B1F3e);
        }

        break;

    default:
        return;
    }

    if (inSqe1_RKqgtL->tzhFH == dpEwXy) {
        PwRs_(inSqe1_RKqgtL);
    }
}


static y7OPfzv1BB3
dsJf7t(cxAM *inSqe1_RKqgtL, SZEzruIOYdDb tjyB)
{
    SZEzruIOYdDb                A9uklPC2D;
    QT2kh3Q       *lirC;
    zaXEweYJVK4  *DOYXos;

    lirC = inSqe1_RKqgtL->PKKlw;
    DOYXos = PHYNtagB3QN(lirC);

    if (tjyB <= inSqe1_RKqgtL->g_JrvkHU) {
        return t86jd4gU2E2V;
    }

    A9uklPC2D = tjyB - inSqe1_RKqgtL->g_JrvkHU;

    gaBasW(Da63, lirC->iy8EanV7uf, 0,
                   "quic stream id:0x%xL flow control msd:%uL/%uL md:%uL/%uL",
                   inSqe1_RKqgtL->f7zvv, tjyB, inSqe1_RKqgtL->B1whvKXK, DOYXos->dpCVIQsVIx.g_JrvkHU + A9uklPC2D,
                   DOYXos->dpCVIQsVIx.B1whvKXK);

    inSqe1_RKqgtL->g_JrvkHU += A9uklPC2D;

    if (inSqe1_RKqgtL->JrSHW9 == OhcdtnYa6l
        && inSqe1_RKqgtL->g_JrvkHU > inSqe1_RKqgtL->B1whvKXK)
    {
        DOYXos->pBL91KeQNQ_jM = jRA0tdn;
        return UnkrWowrYm;
    }

    DOYXos->dpCVIQsVIx.g_JrvkHU += A9uklPC2D;

    if (DOYXos->dpCVIQsVIx.g_JrvkHU > DOYXos->dpCVIQsVIx.B1whvKXK) {
        DOYXos->pBL91KeQNQ_jM = jRA0tdn;
        return UnkrWowrYm;
    }

    return t86jd4gU2E2V;
}


static y7OPfzv1BB3
as5sEf(cxAM *inSqe1_RKqgtL, SZEzruIOYdDb tjyB)
{
    SZEzruIOYdDb                A9uklPC2D;
    QT2kh3Q       *lirC;
    zaXEweYJVK4  *DOYXos;

    lirC = inSqe1_RKqgtL->PKKlw;
    DOYXos = PHYNtagB3QN(lirC);

    if (tjyB <= inSqe1_RKqgtL->cGhQe2mlq) {
        return t86jd4gU2E2V;
    }

    A9uklPC2D = tjyB - inSqe1_RKqgtL->cGhQe2mlq;

    IfqBCa(Da63, lirC->iy8EanV7uf, 0,
                   "quic stream id:0x%xL flow update %uL", inSqe1_RKqgtL->f7zvv, tjyB);

    inSqe1_RKqgtL->cGhQe2mlq += A9uklPC2D;

    if (inSqe1_RKqgtL->B1whvKXK <= inSqe1_RKqgtL->cGhQe2mlq + inSqe1_RKqgtL->dyIPpk / 2) {
        if (FhFwzTESJ4xUC(inSqe1_RKqgtL) != t86jd4gU2E2V) {
            return UnkrWowrYm;
        }
    }

    DOYXos->dpCVIQsVIx.cGhQe2mlq += A9uklPC2D;

    if (DOYXos->dpCVIQsVIx.B1whvKXK
        <= DOYXos->dpCVIQsVIx.cGhQe2mlq + DOYXos->dpCVIQsVIx.dyIPpk / 2)
    {
        if (jq6RY(lirC) != t86jd4gU2E2V) {
            return UnkrWowrYm;
        }
    }

    return t86jd4gU2E2V;
}


static y7OPfzv1BB3
FhFwzTESJ4xUC(cxAM *inSqe1_RKqgtL)
{
    SZEzruIOYdDb                B1whvKXK;
    QT2kh3Q       *lirC;
    oeaIq7AQLyZ8O       *QVWEGgAv800Z;
    zaXEweYJVK4  *DOYXos;

    lirC = inSqe1_RKqgtL->PKKlw;
    DOYXos = PHYNtagB3QN(lirC);

    if (inSqe1_RKqgtL->JrSHW9 != OhcdtnYa6l) {
        return t86jd4gU2E2V;
    }

    B1whvKXK = inSqe1_RKqgtL->cGhQe2mlq + inSqe1_RKqgtL->dyIPpk;

    if (inSqe1_RKqgtL->B1whvKXK == B1whvKXK) {
        return t86jd4gU2E2V;
    }

    inSqe1_RKqgtL->B1whvKXK = B1whvKXK;

    IfqBCa(Da63, lirC->iy8EanV7uf, 0,
                   "quic stream id:0x%xL flow update msd:%uL",
                   inSqe1_RKqgtL->f7zvv, inSqe1_RKqgtL->B1whvKXK);

    QVWEGgAv800Z = y3j5Y(lirC);
    if (QVWEGgAv800Z == dpEwXy) {
        return UnkrWowrYm;
    }

    QVWEGgAv800Z->HPlUW1yDUAiZ = dxNQeYoAlI9wA;
    QVWEGgAv800Z->aUdg = bTa44pHEMlD;
    QVWEGgAv800Z->XLr_CK.ZoHu_6bU.f7zvv = inSqe1_RKqgtL->f7zvv;
    QVWEGgAv800Z->XLr_CK.ZoHu_6bU.U1wzILO = inSqe1_RKqgtL->B1whvKXK;

    EeizN12nPc(DOYXos, QVWEGgAv800Z);

    return t86jd4gU2E2V;
}


static y7OPfzv1BB3
jq6RY(QT2kh3Q *I3t7ghYq1)
{
    SZEzruIOYdDb                B1whvKXK;
    oeaIq7AQLyZ8O       *QVWEGgAv800Z;
    zaXEweYJVK4  *DOYXos;

    DOYXos = PHYNtagB3QN(I3t7ghYq1);

    B1whvKXK = DOYXos->dpCVIQsVIx.cGhQe2mlq + DOYXos->dpCVIQsVIx.dyIPpk;

    if (DOYXos->dpCVIQsVIx.B1whvKXK == B1whvKXK) {
        return t86jd4gU2E2V;
    }

    DOYXos->dpCVIQsVIx.B1whvKXK = B1whvKXK;

    jbjfZuHkNj8LU(Da63, I3t7ghYq1->iy8EanV7uf, 0,
                   "quic flow update md:%uL", DOYXos->dpCVIQsVIx.B1whvKXK);

    QVWEGgAv800Z = y3j5Y(I3t7ghYq1);
    if (QVWEGgAv800Z == dpEwXy) {
        return UnkrWowrYm;
    }

    QVWEGgAv800Z->HPlUW1yDUAiZ = dxNQeYoAlI9wA;
    QVWEGgAv800Z->aUdg = C0C_;
    QVWEGgAv800Z->XLr_CK.vAk0RZag7H.vAk0RZag7H = DOYXos->dpCVIQsVIx.B1whvKXK;

    EeizN12nPc(DOYXos, QVWEGgAv800Z);

    return t86jd4gU2E2V;
}


static void
vrvMYvIjwYsca(WQu_z24t *F2mNJ)
{
    F2mNJ->w427UeDOg0 = 1;

    if (F2mNJ->Hl3cMpoe) {
        iVSis36ViqQAW(F2mNJ, &WS5f);
    }
}
