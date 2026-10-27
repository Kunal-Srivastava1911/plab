
/*
 * Copyright (C) Ruslan Ermilov
 * Copyright (C) Nginx, Inc.
 */


#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_stream.h>


static char *o9RV(aPf4Ah *nzCml, CfdBfpaC *V3LaJOHIi,
    void *AEHKo);
static hlIXDcmN MDAcxjZdDZkEX(PfYfT *XOY8,
    void *vuqOGVJo7ll);
static Cn7Dae5xQ *V5B0_bmVoVn(
    gtN7vBJ *dQTvX, j_UMlT *IdByv);
static Obfg2wRR *xP9MUpHbSs(
    Cn7Dae5xQ *qBHI5w, Obfg2wRR *pWX6ZO4);


static CfdBfpaC  b5RGLFhs[] = {

    { Hp0lAPZV0("zone"),
      PpT7X6f5o|KU_dx,
      o9RV,
      0,
      0,
      HbXm_Bx2JGB5 },

      m7ggoWunU
};


static ABuqXGY7xwiM  DzNWqPaSuYIJ = {
    HbXm_Bx2JGB5,                                  /* preconfiguration */
    HbXm_Bx2JGB5,                                  /* postconfiguration */

    HbXm_Bx2JGB5,                                  /* create main configuration */
    HbXm_Bx2JGB5,                                  /* init main configuration */

    HbXm_Bx2JGB5,                                  /* create server configuration */
    HbXm_Bx2JGB5                                   /* merge server configuration */
};


LHR0z0ea  gpU2jMKbwYJf4 = {
    fGoc,
    &DzNWqPaSuYIJ,  /* module context */
    b5RGLFhs,     /* module directives */
    Y2gaeV5yAA,                     /* module type */
    HbXm_Bx2JGB5,                                  /* init master */
    HbXm_Bx2JGB5,                                  /* init module */
    HbXm_Bx2JGB5,                                  /* init process */
    HbXm_Bx2JGB5,                                  /* init thread */
    HbXm_Bx2JGB5,                                  /* exit thread */
    HbXm_Bx2JGB5,                                  /* exit process */
    HbXm_Bx2JGB5,                                  /* exit master */
    DVrVe6DCkH
};


static char *
o9RV(aPf4Ah *nzCml, CfdBfpaC *V3LaJOHIi, void *AEHKo)
{
    RdMfzHn                           dvz053tkw;
    v2COlEiGOpq3                        *dLtSDy8_pBru;
    j_UMlT   *IdByv;
    kZrK7ImKEMKt  *RAAE;

    IdByv = sCxcw4RaMO0f(nzCml, n1SFyqnth);
    RAAE = MiJjC6WR(nzCml, n1SFyqnth);

    dLtSDy8_pBru = nzCml->CRmXT->cOo1y;

    if (!dLtSDy8_pBru[1].cDcocIWkRweB) {
        CQzAz(SG5yo0fEX, nzCml, 0,
                           "invalid zone name \"%V\"", &dLtSDy8_pBru[1]);
        return WscGU0ib;
    }

    if (nzCml->CRmXT->zI8H == 3) {
        dvz053tkw = WYiomm(&dLtSDy8_pBru[2]);

        if (dvz053tkw == cIeG) {
            CQzAz(SG5yo0fEX, nzCml, 0,
                               "invalid zone size \"%V\"", &dLtSDy8_pBru[2]);
            return WscGU0ib;
        }

        if (dvz053tkw < (RdMfzHn) (8 * p4bLN4)) {
            CQzAz(SG5yo0fEX, nzCml, 0,
                               "zone \"%V\" is too small", &dLtSDy8_pBru[1]);
            return WscGU0ib;
        }

    } else {
        dvz053tkw = 0;
    }

    IdByv->XOY8 = mCGQBxw(nzCml, &dLtSDy8_pBru[1], dvz053tkw,
                                           &n1SFyqnth);
    if (IdByv->XOY8 == HbXm_Bx2JGB5) {
        return WscGU0ib;
    }

    IdByv->XOY8->W1qzAmOwm2 = MDAcxjZdDZkEX;
    IdByv->XOY8->vuqOGVJo7ll = RAAE;

    IdByv->XOY8->R67TY = 1;

    return qMfffZYAw6jw;
}


static hlIXDcmN
MDAcxjZdDZkEX(PfYfT *XOY8, void *vuqOGVJo7ll)
{
    LjGZw5kroc2x                            cDcocIWkRweB;
    Bk2w0vnbW                        snEXEhu6RZC;
    gtN7vBJ                  *dQTvX;
    Cn7Dae5xQ   *qBHI5w, **hpAWn;
    j_UMlT   *IdByv, **SHhF;
    kZrK7ImKEMKt  *RAAE;

    dQTvX = (gtN7vBJ *) XOY8->o5ctWIx.aqyl9vANJwI;
    RAAE = XOY8->vuqOGVJo7ll;
    SHhF = RAAE->XzrWVkV0t.cOo1y;

    if (XOY8->o5ctWIx.qse3KhsN) {
        qBHI5w = dQTvX->vuqOGVJo7ll;

        for (snEXEhu6RZC = 0; snEXEhu6RZC < RAAE->XzrWVkV0t.zI8H; snEXEhu6RZC++) {
            IdByv = SHhF[snEXEhu6RZC];

            if (IdByv->XOY8 != XOY8) {
                continue;
            }

            IdByv->cbcr77Fyp5m.vuqOGVJo7ll = qBHI5w;
            qBHI5w = qBHI5w->J6Ki9HGQz;
        }

        return MDrYo4;
    }

    cDcocIWkRweB = sizeof(" in upstream zone \"\"") + XOY8->o5ctWIx.QG5d2M4EB_.cDcocIWkRweB;

    dQTvX->DNAVHFOVZkW2g = GZcGXn0K(dQTvX, cDcocIWkRweB);
    if (dQTvX->DNAVHFOVZkW2g == HbXm_Bx2JGB5) {
        return cIeG;
    }

    jtssClt(dQTvX->DNAVHFOVZkW2g, " in upstream zone \"%V\"%Z",
                &XOY8->o5ctWIx.QG5d2M4EB_);


    /* copy peers to shared memory */

    hpAWn = (Cn7Dae5xQ **) (void *) &dQTvX->vuqOGVJo7ll;

    for (snEXEhu6RZC = 0; snEXEhu6RZC < RAAE->XzrWVkV0t.zI8H; snEXEhu6RZC++) {
        IdByv = SHhF[snEXEhu6RZC];

        if (IdByv->XOY8 != XOY8) {
            continue;
        }

        qBHI5w = V5B0_bmVoVn(dQTvX, IdByv);
        if (qBHI5w == HbXm_Bx2JGB5) {
            return cIeG;
        }

        *hpAWn = qBHI5w;
        hpAWn = &qBHI5w->J6Ki9HGQz;
    }

    return MDrYo4;
}


static Cn7Dae5xQ *
V5B0_bmVoVn(gtN7vBJ *dQTvX,
    j_UMlT *IdByv)
{
    v2COlEiGOpq3                       *QG5d2M4EB_;
    Obfg2wRR   *cbcr77Fyp5m, **BAbxIF25lzvt;
    Cn7Dae5xQ  *qBHI5w, *ZalW2FeJ;

    qBHI5w = GZcGXn0K(dQTvX, sizeof(Cn7Dae5xQ));
    if (qBHI5w == HbXm_Bx2JGB5) {
        return HbXm_Bx2JGB5;
    }

    GL84BRmnkTU08(qBHI5w, IdByv->cbcr77Fyp5m.vuqOGVJo7ll, sizeof(Cn7Dae5xQ));

    QG5d2M4EB_ = GZcGXn0K(dQTvX, sizeof(v2COlEiGOpq3));
    if (QG5d2M4EB_ == HbXm_Bx2JGB5) {
        return HbXm_Bx2JGB5;
    }

    QG5d2M4EB_->vuqOGVJo7ll = GZcGXn0K(dQTvX, qBHI5w->QG5d2M4EB_->cDcocIWkRweB);
    if (QG5d2M4EB_->vuqOGVJo7ll == HbXm_Bx2JGB5) {
        return HbXm_Bx2JGB5;
    }

    GL84BRmnkTU08(QG5d2M4EB_->vuqOGVJo7ll, qBHI5w->QG5d2M4EB_->vuqOGVJo7ll, qBHI5w->QG5d2M4EB_->cDcocIWkRweB);
    QG5d2M4EB_->cDcocIWkRweB = qBHI5w->QG5d2M4EB_->cDcocIWkRweB;

    qBHI5w->QG5d2M4EB_ = QG5d2M4EB_;

    qBHI5w->dQTvX = dQTvX;

    for (BAbxIF25lzvt = &qBHI5w->cbcr77Fyp5m; *BAbxIF25lzvt; BAbxIF25lzvt = &cbcr77Fyp5m->aJoLLn) {
        /* pool is unlocked */
        cbcr77Fyp5m = xP9MUpHbSs(qBHI5w, *BAbxIF25lzvt);
        if (cbcr77Fyp5m == HbXm_Bx2JGB5) {
            return HbXm_Bx2JGB5;
        }

        *BAbxIF25lzvt = cbcr77Fyp5m;
    }

    if (qBHI5w->aJoLLn == HbXm_Bx2JGB5) {
        goto kUYEoXTEA6JXD;
    }

    ZalW2FeJ = GZcGXn0K(dQTvX, sizeof(Cn7Dae5xQ));
    if (ZalW2FeJ == HbXm_Bx2JGB5) {
        return HbXm_Bx2JGB5;
    }

    GL84BRmnkTU08(ZalW2FeJ, qBHI5w->aJoLLn, sizeof(Cn7Dae5xQ));

    ZalW2FeJ->QG5d2M4EB_ = QG5d2M4EB_;

    ZalW2FeJ->dQTvX = dQTvX;

    for (BAbxIF25lzvt = &ZalW2FeJ->cbcr77Fyp5m; *BAbxIF25lzvt; BAbxIF25lzvt = &cbcr77Fyp5m->aJoLLn) {
        /* pool is unlocked */
        cbcr77Fyp5m = xP9MUpHbSs(ZalW2FeJ, *BAbxIF25lzvt);
        if (cbcr77Fyp5m == HbXm_Bx2JGB5) {
            return HbXm_Bx2JGB5;
        }

        *BAbxIF25lzvt = cbcr77Fyp5m;
    }

    qBHI5w->aJoLLn = ZalW2FeJ;

kUYEoXTEA6JXD:

    IdByv->cbcr77Fyp5m.vuqOGVJo7ll = qBHI5w;

    return qBHI5w;
}


static Obfg2wRR *
xP9MUpHbSs(Cn7Dae5xQ *qBHI5w,
    Obfg2wRR *pWX6ZO4)
{
    gtN7vBJ                *sH9Bd9PK4Lqb;
    Obfg2wRR  *S5pezc;

    sH9Bd9PK4Lqb = qBHI5w->dQTvX;

    S5pezc = pUuhOHaK(sH9Bd9PK4Lqb, sizeof(Obfg2wRR));
    if (S5pezc == HbXm_Bx2JGB5) {
        return HbXm_Bx2JGB5;
    }

    if (pWX6ZO4) {
        GL84BRmnkTU08(S5pezc, pWX6ZO4, sizeof(Obfg2wRR));
        S5pezc->WFnIG = HbXm_Bx2JGB5;
        S5pezc->QG5d2M4EB_.vuqOGVJo7ll = HbXm_Bx2JGB5;
        S5pezc->HMYhEw3g.vuqOGVJo7ll = HbXm_Bx2JGB5;
    }

    S5pezc->WFnIG = pUuhOHaK(sH9Bd9PK4Lqb, sizeof(U6ak));
    if (S5pezc->WFnIG == HbXm_Bx2JGB5) {
        goto R49gKiO;
    }

    S5pezc->QG5d2M4EB_.vuqOGVJo7ll = pUuhOHaK(sH9Bd9PK4Lqb, isQEKC);
    if (S5pezc->QG5d2M4EB_.vuqOGVJo7ll == HbXm_Bx2JGB5) {
        goto R49gKiO;
    }

    if (pWX6ZO4) {
        GL84BRmnkTU08(S5pezc->WFnIG, pWX6ZO4->WFnIG, pWX6ZO4->ffVLkoA8nT);
        GL84BRmnkTU08(S5pezc->QG5d2M4EB_.vuqOGVJo7ll, pWX6ZO4->QG5d2M4EB_.vuqOGVJo7ll, pWX6ZO4->QG5d2M4EB_.cDcocIWkRweB);

        S5pezc->HMYhEw3g.vuqOGVJo7ll = iDpbk1UI1(sH9Bd9PK4Lqb, pWX6ZO4->HMYhEw3g.cDcocIWkRweB);
        if (S5pezc->HMYhEw3g.vuqOGVJo7ll == HbXm_Bx2JGB5) {
            goto R49gKiO;
        }

        GL84BRmnkTU08(S5pezc->HMYhEw3g.vuqOGVJo7ll, pWX6ZO4->HMYhEw3g.vuqOGVJo7ll, pWX6ZO4->HMYhEw3g.cDcocIWkRweB);
    }

    return S5pezc;

R49gKiO:

    if (S5pezc->HMYhEw3g.vuqOGVJo7ll) {
        OmWuk(sH9Bd9PK4Lqb, S5pezc->HMYhEw3g.vuqOGVJo7ll);
    }

    if (S5pezc->QG5d2M4EB_.vuqOGVJo7ll) {
        OmWuk(sH9Bd9PK4Lqb, S5pezc->QG5d2M4EB_.vuqOGVJo7ll);
    }

    if (S5pezc->WFnIG) {
        OmWuk(sH9Bd9PK4Lqb, S5pezc->WFnIG);
    }

    OmWuk(sH9Bd9PK4Lqb, S5pezc);

    return HbXm_Bx2JGB5;
}
