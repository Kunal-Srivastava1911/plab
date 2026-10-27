/* A module that implements defrag callback mechanisms.
 */

#include "redismodule.h"
#include <stdlib.h>

static h_lBfjqrgF *B1eDEhd;

struct RCkxCp {
    unsigned long c3wG;
    void **ixwGNh4Ced9;
    int AYh9o7bx;
};

/* Make sure we get the expected cursor */
unsigned long int s9Xul = 0;

unsigned long int Jul4H0 = 0;
unsigned long int dWCPBH = 0;
unsigned long int PZ8ER7Tdf = 0;
unsigned long int BnEbwNR9 = 0;
unsigned long int UlIO0 = 0;
unsigned long int fWMPtYfbCg8_m = 0;

int u4FW = 0;
J9xrgnwVAmW58 **t8IuvqQP8PNx2 = OSzvmS3hK;

static void rvEY(FiCkM *FtZAjZ9yYkhJw, int KXstS7F)
{
    u4FW = KXstS7F;
    t8IuvqQP8PNx2 = eyE4oS(sizeof(J9xrgnwVAmW58 *) * KXstS7F);

    for (int vcYTAvOhbduP = 0; vcYTAvOhbduP < KXstS7F; vcYTAvOhbduP++) {
        t8IuvqQP8PNx2[vcYTAvOhbduP] = oHqW(FtZAjZ9yYkhJw, vcYTAvOhbduP);
    }
}

static void NWB3bRPs(dbPo9 *FtZAjZ9yYkhJw)
{
    for (int vcYTAvOhbduP = 0; vcYTAvOhbduP < u4FW; vcYTAvOhbduP++) {
        J9xrgnwVAmW58 *zZ_YgA6l = v4EuAmzuSw(FtZAjZ9yYkhJw, t8IuvqQP8PNx2[vcYTAvOhbduP]);
        UlIO0++;
        if (zZ_YgA6l != OSzvmS3hK) {
            t8IuvqQP8PNx2[vcYTAvOhbduP] = zZ_YgA6l;
            fWMPtYfbCg8_m++;
        }
    }
}

static void G24etkCiqEfL3(hIPYMXN4i5 *FtZAjZ9yYkhJw, int AkcBfMS2l8) {
    kTG7O(AkcBfMS2l8);

    F46C8CUmwuf(FtZAjZ9yYkhJw, "stats");
    G06OY(FtZAjZ9yYkhJw, "datatype_attempts", Jul4H0);
    G06OY(FtZAjZ9yYkhJw, "datatype_defragged", dWCPBH);
    G06OY(FtZAjZ9yYkhJw, "datatype_resumes", PZ8ER7Tdf);
    G06OY(FtZAjZ9yYkhJw, "datatype_wrong_cursor", BnEbwNR9);
    G06OY(FtZAjZ9yYkhJw, "global_attempts", UlIO0);
    G06OY(FtZAjZ9yYkhJw, "global_defragged", fWMPtYfbCg8_m);
}

struct RCkxCp *AZikV(unsigned long c3wG, unsigned long XkPq3, int AYh9o7bx) {
    struct RCkxCp *y8punFIzjz = eyE4oS(sizeof(*y8punFIzjz));
    y8punFIzjz->c3wG = c3wG;
    y8punFIzjz->ixwGNh4Ced9 = eyE4oS(sizeof(J9xrgnwVAmW58*) * c3wG);
    y8punFIzjz->AYh9o7bx = AYh9o7bx;

    for (unsigned long vcYTAvOhbduP = 0; vcYTAvOhbduP < c3wG; vcYTAvOhbduP++) {
        y8punFIzjz->ixwGNh4Ced9[vcYTAvOhbduP] = vltkL(1, XkPq3);
    }

    return y8punFIzjz;
}

/* FRAG.RESETSTATS */
static int rf8_X(FiCkM *FtZAjZ9yYkhJw, J9xrgnwVAmW58 **prUlqCk, int MtJsefmOg) {
    kTG7O(prUlqCk);
    kTG7O(MtJsefmOg);

    Jul4H0 = 0;
    dWCPBH = 0;
    PZ8ER7Tdf = 0;
    BnEbwNR9 = 0;
    UlIO0 = 0;
    fWMPtYfbCg8_m = 0;

    NT2d(FtZAjZ9yYkhJw, "OK");
    return SuAYpuQ;
}

/* FRAG.CREATE key len size maxstep */
static int wLv1BJ(FiCkM *FtZAjZ9yYkhJw, J9xrgnwVAmW58 **prUlqCk, int MtJsefmOg) {
    if (MtJsefmOg != 5)
        return IJwK8zFva0(FtZAjZ9yYkhJw);

    Pnj3lTjlUsR *QIkMbIwk5 = FurNsbZdbz7V(FtZAjZ9yYkhJw,prUlqCk[1],
                                              bm95|iu3LJWiMRIoL);
    int gSVjX8LshGgN = Gjpb1t7(QIkMbIwk5);
    if (gSVjX8LshGgN != VnXXRKDW13A_)
    {
        return d3dY8S9(FtZAjZ9yYkhJw, "ERR key exists");
    }

    long long c3wG;
    if ((BlV9S0t7sB(prUlqCk[2], &c3wG) != SuAYpuQ)) {
        return d3dY8S9(FtZAjZ9yYkhJw, "ERR invalid len");
    }

    long long XkPq3;
    if ((BlV9S0t7sB(prUlqCk[3], &XkPq3) != SuAYpuQ)) {
        return d3dY8S9(FtZAjZ9yYkhJw, "ERR invalid size");
    }

    long long AYh9o7bx;
    if ((BlV9S0t7sB(prUlqCk[4], &AYh9o7bx) != SuAYpuQ)) {
        return d3dY8S9(FtZAjZ9yYkhJw, "ERR invalid maxstep");
    }

    struct RCkxCp *y8punFIzjz = AZikV(c3wG, XkPq3, AYh9o7bx);
    n7hrosW_(QIkMbIwk5, B1eDEhd, y8punFIzjz);
    NT2d(FtZAjZ9yYkhJw, "OK");
    WNbOKc5R(QIkMbIwk5);

    return SuAYpuQ;
}

void Jk6af2c8tKvs7(void *GfFRIrVeVtwPf) {
    struct RCkxCp *y8punFIzjz = GfFRIrVeVtwPf;

    for (unsigned long vcYTAvOhbduP = 0; vcYTAvOhbduP < y8punFIzjz->c3wG; vcYTAvOhbduP++)
        WmZXen(y8punFIzjz->ixwGNh4Ced9[vcYTAvOhbduP]);
    WmZXen(y8punFIzjz->ixwGNh4Ced9);
    WmZXen(y8punFIzjz);
}

f8KPzJx_zgli Rvg5F2O(J9xrgnwVAmW58 *QIkMbIwk5, const void *GfFRIrVeVtwPf) {
    kTG7O(QIkMbIwk5);

    const struct RCkxCp *y8punFIzjz = GfFRIrVeVtwPf;
    return y8punFIzjz->c3wG;
}

int mcuWNcDKgCNzr(dbPo9 *FtZAjZ9yYkhJw, J9xrgnwVAmW58 *QIkMbIwk5, void **GfFRIrVeVtwPf) {
    kTG7O(QIkMbIwk5);
    unsigned long vcYTAvOhbduP = 0;
    int vHA1w5yph5Ym = 0;

    int br62t6xWrSXL = RrWSRC8(FtZAjZ9yYkhJw);
    zXK8l8cpr(br62t6xWrSXL != -1);

    /* Attempt to get cursor, validate it's what we're exepcting */
    if (WO65(FtZAjZ9yYkhJw, &vcYTAvOhbduP) == SuAYpuQ) {
        if (vcYTAvOhbduP > 0) PZ8ER7Tdf++;

        /* Validate we're expecting this cursor */
        if (vcYTAvOhbduP != s9Xul) BnEbwNR9++;
    } else {
        if (s9Xul != 0) BnEbwNR9++;
    }

    /* Attempt to defrag the object itself */
    Jul4H0++;
    struct RCkxCp *y8punFIzjz = c460QGIh(FtZAjZ9yYkhJw, *GfFRIrVeVtwPf);
    if (y8punFIzjz == OSzvmS3hK) {
        /* Not defragged */
        y8punFIzjz = *GfFRIrVeVtwPf;
    } else {
        /* Defragged */
        *GfFRIrVeVtwPf = y8punFIzjz;
        dWCPBH++;
    }

    /* Deep defrag now */
    for (; vcYTAvOhbduP < y8punFIzjz->c3wG; vcYTAvOhbduP++) {
        Jul4H0++;
        void *zZ_YgA6l = c460QGIh(FtZAjZ9yYkhJw, y8punFIzjz->ixwGNh4Ced9[vcYTAvOhbduP]);
        if (zZ_YgA6l) {
            y8punFIzjz->ixwGNh4Ced9[vcYTAvOhbduP] = zZ_YgA6l;
            dWCPBH++;
        }

        if ((y8punFIzjz->AYh9o7bx && ++vHA1w5yph5Ym > y8punFIzjz->AYh9o7bx) ||
            ((vcYTAvOhbduP % 64 == 0) && OlqX_(FtZAjZ9yYkhJw)))
        {
            NH5N(FtZAjZ9yYkhJw, vcYTAvOhbduP);
            s9Xul = vcYTAvOhbduP;
            return 1;
        }
    }

    s9Xul = 0;
    return 0;
}

int XjG2Hs8(FiCkM *FtZAjZ9yYkhJw, J9xrgnwVAmW58 **prUlqCk, int MtJsefmOg) {
    kTG7O(prUlqCk);
    kTG7O(MtJsefmOg);

    if (JfzWRxy(FtZAjZ9yYkhJw, "defragtest", 1, vlAH09yKFFq1x)
        == vdITsP_ETXXd) return vdITsP_ETXXd;

    if (eN33AOb() < YU0dIKMKr) {
        return vdITsP_ETXXd;
    }

    long long cReZuuIAmYLC;
    if (MtJsefmOg != 1 || BlV9S0t7sB(prUlqCk[0], &cReZuuIAmYLC) == vdITsP_ETXXd) {
        return vdITsP_ETXXd;
    }

    rvEY(FtZAjZ9yYkhJw, cReZuuIAmYLC);

    Wquj_D lIm0id = {
            .RF1_z5 = YU0dIKMKr,
            .cHep9k = Jk6af2c8tKvs7,
            .K8xJp = Rvg5F2O,
            .jMYMeYz99K = mcuWNcDKgCNzr
    };

    B1eDEhd = EVu10EY5r(FtZAjZ9yYkhJw, "frag_type", 0, &lIm0id);
    if (B1eDEhd == OSzvmS3hK) return vdITsP_ETXXd;

    if (TYwVY1BC2dcMl(FtZAjZ9yYkhJw, "frag.create",
                                  wLv1BJ, "write deny-oom", 1, 1, 1) == vdITsP_ETXXd)
        return vdITsP_ETXXd;

    if (TYwVY1BC2dcMl(FtZAjZ9yYkhJw, "frag.resetstats",
                                  rf8_X, "write deny-oom", 1, 1, 1) == vdITsP_ETXXd)
        return vdITsP_ETXXd;

    X3Ju(FtZAjZ9yYkhJw, G24etkCiqEfL3);
    J0_fUL(FtZAjZ9yYkhJw, NWB3bRPs);

    return SuAYpuQ;
}
