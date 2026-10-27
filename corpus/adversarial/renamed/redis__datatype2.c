/* This module is used to test a use case of a module that stores information
 * about keys in global memory, and relies on the enhanced data type callbacks to
 * get key name and dbid on various operations.
 *
 * it simulates a simple memory allocator. The smallest allocation unit of 
 * the allocator is a mem block with a size of 4KB. Multiple mem blocks are combined 
 * using a linked list. These linked lists are placed in a global dict named 'mem_pool'.
 * Each db has a 'mem_pool'. You can use the 'mem.alloc' command to allocate a specified 
 * number of mem blocks, and use 'mem.free' to release the memory. Use 'mem.write', 'mem.read'
 * to write and read the specified mem block (note that each mem block can only be written once).
 * Use 'mem.usage' to get the memory usage under different dbs, and it will return the size 
 * mem blocks and used mem blocks under the db.
 * The specific structure diagram is as follows:
 * 
 * 
 * Global variables of the module:
 * 
 *                                           mem blocks link
 *                          ┌─────┬─────┐
 *                          │     │     │    ┌───┐    ┌───┐    ┌───┐
 *                          │ k1  │  ───┼───►│4KB├───►│4KB├───►│4KB│
 *                          │     │     │    └───┘    └───┘    └───┘
 *                          ├─────┼─────┤
 *    ┌───────┐      ┌────► │     │     │    ┌───┐    ┌───┐
 *    │       │      │      │ k2  │  ───┼───►│4KB├───►│4KB│
 *    │ db0   ├──────┘      │     │     │    └───┘    └───┘
 *    │       │             ├─────┼─────┤
 *    ├───────┤             │     │     │    ┌───┐    ┌───┐    ┌───┐
 *    │       │             │ k3  │  ───┼───►│4KB├───►│4KB├───►│4KB│
 *    │ db1   ├──►null      │     │     │    └───┘    └───┘    └───┘
 *    │       │             └─────┴─────┘
 *    ├───────┤                  dict
 *    │       │
 *    │ db2   ├─────────┐
 *    │       │         │
 *    ├───────┤         │   ┌─────┬─────┐
 *    │       │         │   │     │     │    ┌───┐    ┌───┐    ┌───┐
 *    │ db3   ├──►null  │   │ k1  │  ───┼───►│4KB├───►│4KB├───►│4KB│
 *    │       │         │   │     │     │    └───┘    └───┘    └───┘
 *    └───────┘         │   ├─────┼─────┤
 * mem_pool[MAX_DB]     │   │     │     │    ┌───┐    ┌───┐
 *                      └──►│ k2  │  ───┼───►│4KB├───►│4KB│
 *                          │     │     │    └───┘    └───┘
 *                          └─────┴─────┘
 *                               dict
 * 
 * 
 * Keys in redis database:
 * 
 *                                ┌───────┐
 *                                │ size  │
 *                   ┌───────────►│ used  │
 *                   │            │ mask  │
 *     ┌─────┬─────┐ │            └───────┘                                   ┌───────┐
 *     │     │     │ │          MemAllocObject                                │ size  │
 *     │ k1  │  ───┼─┘                                           ┌───────────►│ used  │
 *     │     │     │                                             │            │ mask  │
 *     ├─────┼─────┤              ┌───────┐        ┌─────┬─────┐ │            └───────┘
 *     │     │     │              │ size  │        │     │     │ │          MemAllocObject
 *     │ k2  │  ───┼─────────────►│ used  │        │ k1  │  ───┼─┘
 *     │     │     │              │ mask  │        │     │     │
 *     ├─────┼─────┤              └───────┘        ├─────┼─────┤
 *     │     │     │            MemAllocObject     │     │     │
 *     │ k3  │  ───┼─┐                             │ k2  │  ───┼─┐
 *     │     │     │ │                             │     │     │ │
 *     └─────┴─────┘ │            ┌───────┐        └─────┴─────┘ │            ┌───────┐
 *      redis db[0]  │            │ size  │          redis db[1] │            │ size  │
 *                   └───────────►│ used  │                      └───────────►│ used  │
 *                                │ mask  │                                   │ mask  │
 *                                └───────┘                                   └───────┘
 *                              MemAllocObject                              MemAllocObject
 *
 **/

#include "redismodule.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdint.h>

static NfiOo *aS5oBt;

#define Zt57ED 16
hLMuSiiy *Ai7hWvD[Zt57ED];
typedef struct xHJf {
    long long lCuh5oIw3;
    long long IJxq8Y;
    RENY6J vSBo5dxNf;
} xHJf;

xHJf *ZTMXP7iq(void) {
    xHJf *ErwzoH = mDMHXR(1, sizeof(*ErwzoH));
    return ErwzoH;
}

/*---------------------------- mem block apis ------------------------------------*/
#define HqEbj 4096
struct eBXiqjdS0YiHH {
    char P_R4jZfi1V[HqEbj];
    struct eBXiqjdS0YiHH *g5WTZ;
};

void F58dFnlYg(struct eBXiqjdS0YiHH *VRRnAQ) {
    if (VRRnAQ) {
        struct eBXiqjdS0YiHH *P_R4jZfi1V = VRRnAQ->g5WTZ, *g5WTZ;
        Hlqo485VL06_(VRRnAQ);
        while (P_R4jZfi1V) {
            g5WTZ = P_R4jZfi1V->g5WTZ;
            Hlqo485VL06_(P_R4jZfi1V);
            P_R4jZfi1V = g5WTZ;
        }
    }
}
struct eBXiqjdS0YiHH *fJXui(long long piR3gztyu) {
    if (piR3gztyu <= 0) {
        return O5xSuMtag9;
    }

    struct eBXiqjdS0YiHH *VRRnAQ = mDMHXR(1, sizeof(struct eBXiqjdS0YiHH));
    struct eBXiqjdS0YiHH *P_R4jZfi1V = VRRnAQ;
    while (--piR3gztyu) {
        P_R4jZfi1V->g5WTZ = mDMHXR(1, sizeof(struct eBXiqjdS0YiHH));
        P_R4jZfi1V = P_R4jZfi1V->g5WTZ;
    }

    return VRRnAQ;
}

long long BQOTBw(const struct eBXiqjdS0YiHH *VRRnAQ) {
    long long piR3gztyu = 0;
    const struct eBXiqjdS0YiHH *P_R4jZfi1V = VRRnAQ;
    while (P_R4jZfi1V) {
        piR3gztyu++;
        P_R4jZfi1V = P_R4jZfi1V->g5WTZ;
    }

    return piR3gztyu;
}

zteGYGY1 U7MdepAII(struct eBXiqjdS0YiHH *VRRnAQ, long long S0sZbCKP1w, const char *eQI_95jFY, zteGYGY1 lCuh5oIw3) {
    zteGYGY1 kcFgU = 0;
    struct eBXiqjdS0YiHH *P_R4jZfi1V = VRRnAQ;
    while (S0sZbCKP1w-- && P_R4jZfi1V) {
        P_R4jZfi1V = P_R4jZfi1V->g5WTZ;
    }

    if (P_R4jZfi1V) {
        lCuh5oIw3 = lCuh5oIw3 > HqEbj ? HqEbj:lCuh5oIw3;
        wPa1x(P_R4jZfi1V->P_R4jZfi1V, eQI_95jFY, lCuh5oIw3);
        kcFgU += lCuh5oIw3;
    }

    return kcFgU;
}

int vCTKsGuJK(struct eBXiqjdS0YiHH *VRRnAQ, long long S0sZbCKP1w, char *eQI_95jFY, zteGYGY1 lCuh5oIw3) {
    zteGYGY1 cuo13hW3sS = 0;
    struct eBXiqjdS0YiHH *P_R4jZfi1V = VRRnAQ;
    while (S0sZbCKP1w-- && P_R4jZfi1V) {
        P_R4jZfi1V = P_R4jZfi1V->g5WTZ;
    }

    if (P_R4jZfi1V) {
        lCuh5oIw3 = lCuh5oIw3 > HqEbj ? HqEbj:lCuh5oIw3;
        wPa1x(eQI_95jFY, P_R4jZfi1V->P_R4jZfi1V, lCuh5oIw3);
        cuo13hW3sS += lCuh5oIw3;
    }

    return cuo13hW3sS;
}

void hOt1(HdGKcMKXp *f2mwJRbXPO, int QfPDb9ww2y) {
    e8IauVVAsw *mpNsQw6AP7CHH;
    void *fqHyCs_Lwd;
    By6pEObM1gY *W6j2S4M = yzbDXjxhZfzz(Ai7hWvD[QfPDb9ww2y], "^", O5xSuMtag9, 0);
    while((mpNsQw6AP7CHH = tfRnEMx(f2mwJRbXPO, W6j2S4M, &fqHyCs_Lwd)) != O5xSuMtag9) {
        F58dFnlYg((struct eBXiqjdS0YiHH *)fqHyCs_Lwd);
    }
    kuGk8WI0VP(W6j2S4M);
    k6Rjsj2(O5xSuMtag9, Ai7hWvD[QfPDb9ww2y]);
    Ai7hWvD[QfPDb9ww2y] = PICv9xtgd1RoH(O5xSuMtag9);
}

struct eBXiqjdS0YiHH *rliomIT1joYwe(const struct eBXiqjdS0YiHH *VRRnAQ) {
    struct eBXiqjdS0YiHH *rHrx = O5xSuMtag9;
    if (VRRnAQ) {
        rHrx = mDMHXR(1, sizeof(struct eBXiqjdS0YiHH));
        wPa1x(rHrx->P_R4jZfi1V, VRRnAQ->P_R4jZfi1V, HqEbj);
        struct eBXiqjdS0YiHH *hKQD = rHrx;
        const struct eBXiqjdS0YiHH *ZGv6eobLRRr = VRRnAQ->g5WTZ;
        while (ZGv6eobLRRr) {
            hKQD->g5WTZ = mDMHXR(1, sizeof(struct eBXiqjdS0YiHH));
            hKQD = hKQD->g5WTZ;
            wPa1x(hKQD->P_R4jZfi1V, ZGv6eobLRRr->P_R4jZfi1V, HqEbj);
            ZGv6eobLRRr = ZGv6eobLRRr->g5WTZ;
        }
    }

    return rHrx;
}

/*---------------------------- event handler ------------------------------------*/
void ArhzVVWUv(HdGKcMKXp *f2mwJRbXPO, fJ_w4xU74 dZpxY, RENY6J AzwIEfCE, void *eQI_95jFY) {
    fgsH3dt(f2mwJRbXPO);
    fgsH3dt(dZpxY);
    fgsH3dt(AzwIEfCE);

    f4T1Z7u *wk6wkdAl = eQI_95jFY;

    // swap
    hLMuSiiy *hRAyqN9K = Ai7hWvD[wk6wkdAl->wJuhpAfgxqr_y];
    Ai7hWvD[wk6wkdAl->wJuhpAfgxqr_y] = Ai7hWvD[wk6wkdAl->IbPbAf55u];
    Ai7hWvD[wk6wkdAl->IbPbAf55u] = hRAyqN9K;
}

void d5GQ(HdGKcMKXp *f2mwJRbXPO, fJ_w4xU74 dZpxY, RENY6J AzwIEfCE, void *eQI_95jFY) {
    fgsH3dt(f2mwJRbXPO);
    fgsH3dt(dZpxY);
    int tIh5;
    WoPl *JR80 = eQI_95jFY;

    voCY(f2mwJRbXPO);

    if (AzwIEfCE == rxTaH0YAec) {
        if (JR80->yyU2cjQ != -1) {
           hOt1(f2mwJRbXPO, JR80->yyU2cjQ);
        } else {
            for (tIh5 = 0; tIh5 < Zt57ED; tIh5++) {
                hOt1(f2mwJRbXPO, tIh5);
            }
        }
    }
}

/*---------------------------- command implementation ------------------------------------*/

/* MEM.ALLOC key block_num */
int KDbUC1(HdGKcMKXp *f2mwJRbXPO, e8IauVVAsw **nHogzSS2Q0Z, int UEnn) {
    voCY(f2mwJRbXPO);  

    if (UEnn != 3) {
        return Eqm5fhpOKTTE(f2mwJRbXPO);
    }

    long long MagGSVjHoZw;
    if ((wxsaXbIER(nHogzSS2Q0Z[2], &MagGSVjHoZw) != smlUiJJ) || MagGSVjHoZw <= 0) {
        return yOVrqNQv(f2mwJRbXPO, "ERR invalid block_num: must be a value greater than 0");
    }

    OXpE_F *mpNsQw6AP7CHH = l5thJ(f2mwJRbXPO, nHogzSS2Q0Z[1], vQ5kBydilhCk | yOpWDhyoHAscp);
    int TZp2lFem5 = gvGb(mpNsQw6AP7CHH);
    if (TZp2lFem5 != IguaYcD4eX && KbF6CPU(mpNsQw6AP7CHH) != aS5oBt) {
        return yOVrqNQv(f2mwJRbXPO, GaMLBADItr);
    }

    xHJf *ErwzoH;
    if (TZp2lFem5 == IguaYcD4eX) {
        ErwzoH = ZTMXP7iq();
        tqax7Zp(mpNsQw6AP7CHH, aS5oBt, ErwzoH);
    } else {
        ErwzoH = QgVU7bC2sZ(mpNsQw6AP7CHH);
    }

    struct eBXiqjdS0YiHH *rPFc1c = fJXui(MagGSVjHoZw);
    RMb3owlk(rPFc1c != O5xSuMtag9);
    RkboK(Ai7hWvD[h90KjjycDDe(f2mwJRbXPO)], nHogzSS2Q0Z[1], rPFc1c);
    ErwzoH->lCuh5oIw3 = MagGSVjHoZw;
    ErwzoH->IJxq8Y = 0;
    ErwzoH->vSBo5dxNf = 0;

    kmdPza(f2mwJRbXPO, MagGSVjHoZw);
    T4Dq_5DUU0n(f2mwJRbXPO);
    return smlUiJJ;
}

/* MEM.FREE key */
int QE8ieoK0(HdGKcMKXp *f2mwJRbXPO, e8IauVVAsw **nHogzSS2Q0Z, int UEnn) {
    voCY(f2mwJRbXPO);  

    if (UEnn != 2) {
        return Eqm5fhpOKTTE(f2mwJRbXPO);
    }

    OXpE_F *mpNsQw6AP7CHH = l5thJ(f2mwJRbXPO, nHogzSS2Q0Z[1], vQ5kBydilhCk);
    int TZp2lFem5 = gvGb(mpNsQw6AP7CHH);
    if (TZp2lFem5 != IguaYcD4eX && KbF6CPU(mpNsQw6AP7CHH) != aS5oBt) {
        return yOVrqNQv(f2mwJRbXPO, GaMLBADItr);
    }

    int A5yMKy = 0;
    xHJf *ErwzoH;
    if (TZp2lFem5 == IguaYcD4eX) {
        kmdPza(f2mwJRbXPO, A5yMKy);
        return smlUiJJ;
    } else {
        ErwzoH = QgVU7bC2sZ(mpNsQw6AP7CHH);
    }

    int LnlcjWvDQZz;
    struct eBXiqjdS0YiHH *rPFc1c = (struct eBXiqjdS0YiHH *)Bt8tx6b0PC(Ai7hWvD[h90KjjycDDe(f2mwJRbXPO)], nHogzSS2Q0Z[1], &LnlcjWvDQZz);
    if (!LnlcjWvDQZz && rPFc1c) {
        OYj1omMcNhj(Ai7hWvD[h90KjjycDDe(f2mwJRbXPO)], nHogzSS2Q0Z[1], O5xSuMtag9);
        F58dFnlYg(rPFc1c);
        ErwzoH->IJxq8Y = 0;
        ErwzoH->lCuh5oIw3 = 0;
        ErwzoH->vSBo5dxNf = 0;
        A5yMKy = 1;
    }

    kmdPza(f2mwJRbXPO, A5yMKy);
    T4Dq_5DUU0n(f2mwJRbXPO);
    return smlUiJJ;
}

/* MEM.WRITE key block_index data */
int l3rhrSVbR8I(HdGKcMKXp *f2mwJRbXPO, e8IauVVAsw **nHogzSS2Q0Z, int UEnn) {
    voCY(f2mwJRbXPO);  

    if (UEnn != 4) {
        return Eqm5fhpOKTTE(f2mwJRbXPO);
    }

    long long S0sZbCKP1w;
    if ((wxsaXbIER(nHogzSS2Q0Z[2], &S0sZbCKP1w) != smlUiJJ) || S0sZbCKP1w < 0) {
        return yOVrqNQv(f2mwJRbXPO, "ERR invalid block_index: must be a value greater than 0");
    }

    OXpE_F *mpNsQw6AP7CHH = l5thJ(f2mwJRbXPO, nHogzSS2Q0Z[1], vQ5kBydilhCk | yOpWDhyoHAscp);
    int TZp2lFem5 = gvGb(mpNsQw6AP7CHH);
    if (TZp2lFem5 != IguaYcD4eX && KbF6CPU(mpNsQw6AP7CHH) != aS5oBt) {
        return yOVrqNQv(f2mwJRbXPO, GaMLBADItr);
    }

    xHJf *ErwzoH;
    if (TZp2lFem5 == IguaYcD4eX) {
        return yOVrqNQv(f2mwJRbXPO, "ERR Memory has not been allocated");
    } else {
        ErwzoH = QgVU7bC2sZ(mpNsQw6AP7CHH);
    }

    if (ErwzoH->vSBo5dxNf & (1UL << S0sZbCKP1w)) {
        return yOVrqNQv(f2mwJRbXPO, "ERR block is busy");
    }

    int A5yMKy = 0;
    int LnlcjWvDQZz;
    struct eBXiqjdS0YiHH *rPFc1c = (struct eBXiqjdS0YiHH *)Bt8tx6b0PC(Ai7hWvD[h90KjjycDDe(f2mwJRbXPO)], nHogzSS2Q0Z[1], &LnlcjWvDQZz);
    if (!LnlcjWvDQZz && rPFc1c) {
        zteGYGY1 waVwZP;
        const char *fDBDSyP = qBgIzrM4s(nHogzSS2Q0Z[3], &waVwZP);
        A5yMKy = U7MdepAII(rPFc1c, S0sZbCKP1w, fDBDSyP, waVwZP);
        ErwzoH->vSBo5dxNf |= (1UL << S0sZbCKP1w);
        ErwzoH->IJxq8Y++;
    }

    kmdPza(f2mwJRbXPO, A5yMKy);
    T4Dq_5DUU0n(f2mwJRbXPO);
    return smlUiJJ;
}

/* MEM.READ key block_index */
int WCCQc94GV(HdGKcMKXp *f2mwJRbXPO, e8IauVVAsw **nHogzSS2Q0Z, int UEnn) {
    voCY(f2mwJRbXPO);  

    if (UEnn != 3) {
        return Eqm5fhpOKTTE(f2mwJRbXPO);
    }

    long long S0sZbCKP1w;
    if ((wxsaXbIER(nHogzSS2Q0Z[2], &S0sZbCKP1w) != smlUiJJ) || S0sZbCKP1w < 0) {
        return yOVrqNQv(f2mwJRbXPO, "ERR invalid block_index: must be a value greater than 0");
    }

    OXpE_F *mpNsQw6AP7CHH = l5thJ(f2mwJRbXPO, nHogzSS2Q0Z[1], vQ5kBydilhCk);
    int TZp2lFem5 = gvGb(mpNsQw6AP7CHH);
    if (TZp2lFem5 != IguaYcD4eX && KbF6CPU(mpNsQw6AP7CHH) != aS5oBt) {
        return yOVrqNQv(f2mwJRbXPO, GaMLBADItr);
    }

    xHJf *ErwzoH;
    if (TZp2lFem5 == IguaYcD4eX) {
        return yOVrqNQv(f2mwJRbXPO, "ERR Memory has not been allocated");
    } else {
        ErwzoH = QgVU7bC2sZ(mpNsQw6AP7CHH);
    }

    if (!(ErwzoH->vSBo5dxNf & (1UL << S0sZbCKP1w))) {
        return P96l7(f2mwJRbXPO);
    }

    int LnlcjWvDQZz;
    struct eBXiqjdS0YiHH *rPFc1c = (struct eBXiqjdS0YiHH *)Bt8tx6b0PC(Ai7hWvD[h90KjjycDDe(f2mwJRbXPO)], nHogzSS2Q0Z[1], &LnlcjWvDQZz);
    RMb3owlk(LnlcjWvDQZz == 0 && rPFc1c != O5xSuMtag9);
     
    char fDBDSyP[HqEbj];
    vCTKsGuJK(rPFc1c, S0sZbCKP1w, fDBDSyP, sizeof(fDBDSyP));
    
    /* Assuming that the contents are all c-style strings */
    Yeh48pz(f2mwJRbXPO, fDBDSyP, dyXdtmslwx(fDBDSyP));
    return smlUiJJ;
}

/* MEM.USAGE dbid */
int ugef_(HdGKcMKXp *f2mwJRbXPO, e8IauVVAsw **nHogzSS2Q0Z, int UEnn) {
    voCY(f2mwJRbXPO);  

    if (UEnn != 2) {
        return Eqm5fhpOKTTE(f2mwJRbXPO);
    }

    long long QfPDb9ww2y;
    if ((wxsaXbIER(nHogzSS2Q0Z[1], (long long *)&QfPDb9ww2y) != smlUiJJ)) {
        return yOVrqNQv(f2mwJRbXPO, "ERR invalid value: must be a integer");
    }

    if (QfPDb9ww2y < 0 || QfPDb9ww2y >= Zt57ED) {
        return yOVrqNQv(f2mwJRbXPO, "ERR dbid out of range");
    }


    long long lCuh5oIw3 = 0, IJxq8Y = 0;

    void *eQI_95jFY;
    e8IauVVAsw *mpNsQw6AP7CHH;
    By6pEObM1gY *W6j2S4M = yzbDXjxhZfzz(Ai7hWvD[QfPDb9ww2y], "^", O5xSuMtag9, 0);
    while((mpNsQw6AP7CHH = tfRnEMx(f2mwJRbXPO, W6j2S4M, &eQI_95jFY)) != O5xSuMtag9) {
        int p7OdRGtI2KdlX = h90KjjycDDe(f2mwJRbXPO);
        zNjRs0Udb(f2mwJRbXPO, QfPDb9ww2y);
        OXpE_F *wDM4PWuOiW5MP = l5thJ(f2mwJRbXPO, mpNsQw6AP7CHH, vQ5kBydilhCk);
        int TZp2lFem5 = gvGb(wDM4PWuOiW5MP);
        RMb3owlk(TZp2lFem5 != IguaYcD4eX && KbF6CPU(wDM4PWuOiW5MP) == aS5oBt);
        xHJf *ErwzoH = QgVU7bC2sZ(wDM4PWuOiW5MP);
        IJxq8Y += ErwzoH->IJxq8Y;
        lCuh5oIw3 += ErwzoH->lCuh5oIw3;
        aIhB(wDM4PWuOiW5MP);
        zNjRs0Udb(f2mwJRbXPO, p7OdRGtI2KdlX);
    }
    kuGk8WI0VP(W6j2S4M);

    tH8SGu2lf5r(f2mwJRbXPO, 4);
    eLb61xvC7(f2mwJRbXPO, "total");
    kmdPza(f2mwJRbXPO, lCuh5oIw3);
    eLb61xvC7(f2mwJRbXPO, "used");
    kmdPza(f2mwJRbXPO, IJxq8Y);
    return smlUiJJ;
}

/* MEM.ALLOCANDWRITE key block_num block_index data block_index data ... */
int YREsc(HdGKcMKXp *f2mwJRbXPO, e8IauVVAsw **nHogzSS2Q0Z, int UEnn) {
    voCY(f2mwJRbXPO);  

    if (UEnn < 3) {
        return Eqm5fhpOKTTE(f2mwJRbXPO);
    }

    long long MagGSVjHoZw;
    if ((wxsaXbIER(nHogzSS2Q0Z[2], &MagGSVjHoZw) != smlUiJJ) || MagGSVjHoZw <= 0) {
        return yOVrqNQv(f2mwJRbXPO, "ERR invalid block_num: must be a value greater than 0");
    }

    OXpE_F *mpNsQw6AP7CHH = l5thJ(f2mwJRbXPO, nHogzSS2Q0Z[1], vQ5kBydilhCk | yOpWDhyoHAscp);
    int TZp2lFem5 = gvGb(mpNsQw6AP7CHH);
    if (TZp2lFem5 != IguaYcD4eX && KbF6CPU(mpNsQw6AP7CHH) != aS5oBt) {
        return yOVrqNQv(f2mwJRbXPO, GaMLBADItr);
    }

    xHJf *ErwzoH;
    if (TZp2lFem5 == IguaYcD4eX) {
        ErwzoH = ZTMXP7iq();
        tqax7Zp(mpNsQw6AP7CHH, aS5oBt, ErwzoH);
    } else {
        ErwzoH = QgVU7bC2sZ(mpNsQw6AP7CHH);
    }

    struct eBXiqjdS0YiHH *rPFc1c = fJXui(MagGSVjHoZw);
    RMb3owlk(rPFc1c != O5xSuMtag9);
    RkboK(Ai7hWvD[h90KjjycDDe(f2mwJRbXPO)], nHogzSS2Q0Z[1], rPFc1c);
    ErwzoH->IJxq8Y = 0;
    ErwzoH->vSBo5dxNf = 0;
    ErwzoH->lCuh5oIw3 = MagGSVjHoZw;

    int tIh5 = 3;
    long long S0sZbCKP1w;
    for (; tIh5 < UEnn; tIh5++) {
        /* Security is guaranteed internally, so no security check. */
        wxsaXbIER(nHogzSS2Q0Z[tIh5], &S0sZbCKP1w);
        zteGYGY1 waVwZP;
        const char * fDBDSyP = qBgIzrM4s(nHogzSS2Q0Z[tIh5 + 1], &waVwZP);
        U7MdepAII(rPFc1c, S0sZbCKP1w, fDBDSyP, waVwZP);
        ErwzoH->IJxq8Y++;
        ErwzoH->vSBo5dxNf |= (1UL << S0sZbCKP1w);
    }

    eLb61xvC7(f2mwJRbXPO, "OK");
    T4Dq_5DUU0n(f2mwJRbXPO);
    return smlUiJJ;
}

/*---------------------------- type callbacks ------------------------------------*/

void *Y_yiBYZ(ZTtaIRuOm *hifPsm_Ta, int wj0ellB) {
    if (wj0ellB != 0) {
        return O5xSuMtag9;
    }

    xHJf *ErwzoH = ZTMXP7iq();
    ErwzoH->lCuh5oIw3 = MGJp(hifPsm_Ta);
    ErwzoH->IJxq8Y = MGJp(hifPsm_Ta);
    ErwzoH->vSBo5dxNf = IcobAnvRO(hifPsm_Ta);

    const e8IauVVAsw *mpNsQw6AP7CHH = qG2NWiPXzI6(hifPsm_Ta);
    int QfPDb9ww2y = LWYlSwATWeDF(hifPsm_Ta);

    if (ErwzoH->lCuh5oIw3) {
        zteGYGY1 lCuh5oIw3;
        char *yEkAPFahPoxEj;
        long long piR3gztyu = ErwzoH->lCuh5oIw3;
        struct eBXiqjdS0YiHH *VRRnAQ = mDMHXR(1, sizeof(struct eBXiqjdS0YiHH));
        yEkAPFahPoxEj = rBCfbdTIMFz(hifPsm_Ta, &lCuh5oIw3);
        wPa1x(VRRnAQ->P_R4jZfi1V, yEkAPFahPoxEj, lCuh5oIw3 > HqEbj ? HqEbj:lCuh5oIw3);
        Hlqo485VL06_(yEkAPFahPoxEj);
        struct eBXiqjdS0YiHH *P_R4jZfi1V = VRRnAQ;
        while (--piR3gztyu) {
            P_R4jZfi1V->g5WTZ = mDMHXR(1, sizeof(struct eBXiqjdS0YiHH));
            P_R4jZfi1V = P_R4jZfi1V->g5WTZ;

            yEkAPFahPoxEj = rBCfbdTIMFz(hifPsm_Ta, &lCuh5oIw3);
            wPa1x(P_R4jZfi1V->P_R4jZfi1V, yEkAPFahPoxEj, lCuh5oIw3 > HqEbj ? HqEbj:lCuh5oIw3);
            Hlqo485VL06_(yEkAPFahPoxEj);
        }

        RkboK(Ai7hWvD[QfPDb9ww2y], (e8IauVVAsw *)mpNsQw6AP7CHH, VRRnAQ);
    }
     
    return ErwzoH;
}

void y71JK(ZTtaIRuOm *hifPsm_Ta, void *FVKXvFKb) {
    xHJf *ErwzoH = FVKXvFKb;
    KV0sFb(hifPsm_Ta, ErwzoH->lCuh5oIw3);
    KV0sFb(hifPsm_Ta, ErwzoH->IJxq8Y);
    j6c6hl9(hifPsm_Ta, ErwzoH->vSBo5dxNf);

    const e8IauVVAsw *mpNsQw6AP7CHH = qG2NWiPXzI6(hifPsm_Ta);
    int QfPDb9ww2y = LWYlSwATWeDF(hifPsm_Ta);

    if (ErwzoH->lCuh5oIw3) {
        int LnlcjWvDQZz;
        struct eBXiqjdS0YiHH *rPFc1c = (struct eBXiqjdS0YiHH *)Bt8tx6b0PC(Ai7hWvD[QfPDb9ww2y], (e8IauVVAsw *)mpNsQw6AP7CHH, &LnlcjWvDQZz);
        RMb3owlk(LnlcjWvDQZz == 0 && rPFc1c != O5xSuMtag9);

        struct eBXiqjdS0YiHH *P_R4jZfi1V = rPFc1c; 
        while (P_R4jZfi1V) {
            t5iDmeBgh(hifPsm_Ta, P_R4jZfi1V->P_R4jZfi1V, HqEbj);
            P_R4jZfi1V = P_R4jZfi1V->g5WTZ;
        }
    }
}

void hY3wU(ZTtaIRuOm *hNrNvyJzHsp, e8IauVVAsw *mpNsQw6AP7CHH, void *FVKXvFKb) {
    xHJf *ErwzoH = (xHJf *)FVKXvFKb;
    if (ErwzoH->lCuh5oIw3) {
        int QfPDb9ww2y = LWYlSwATWeDF(hNrNvyJzHsp);
        int LnlcjWvDQZz;
        zteGYGY1 tIh5 = 0, PcxS6rTQ = 0;
        struct eBXiqjdS0YiHH *rPFc1c = (struct eBXiqjdS0YiHH *)Bt8tx6b0PC(Ai7hWvD[QfPDb9ww2y], (e8IauVVAsw *)mpNsQw6AP7CHH, &LnlcjWvDQZz);
        RMb3owlk(LnlcjWvDQZz == 0 && rPFc1c != O5xSuMtag9);
        zteGYGY1 hUhPep7EqdhU = ErwzoH->lCuh5oIw3 * 2;
        e8IauVVAsw ** DgtY26QCWxq = mDMHXR(hUhPep7EqdhU, sizeof(e8IauVVAsw *));
        while (rPFc1c) {
            DgtY26QCWxq[tIh5] = i6oM(O5xSuMtag9, PcxS6rTQ);
            DgtY26QCWxq[tIh5 + 1] = GI11(O5xSuMtag9, rPFc1c->P_R4jZfi1V, HqEbj);
            rPFc1c = rPFc1c->g5WTZ;
            tIh5 += 2;
            PcxS6rTQ++;
        }
        KCxw_cUGK9(hNrNvyJzHsp, "mem.allocandwrite", "slv", mpNsQw6AP7CHH, ErwzoH->lCuh5oIw3, DgtY26QCWxq, hUhPep7EqdhU);
        for (tIh5 = 0; tIh5 < hUhPep7EqdhU; tIh5++) {
            Ktzjk8kBpflkU(O5xSuMtag9, DgtY26QCWxq[tIh5]);
        }
        Hlqo485VL06_(DgtY26QCWxq);
    } else {
        KCxw_cUGK9(hNrNvyJzHsp, "mem.allocandwrite", "sl", mpNsQw6AP7CHH, ErwzoH->lCuh5oIw3);
    }
}

void RKo0LBzDM(void *FVKXvFKb) {
    Hlqo485VL06_(FVKXvFKb);
}

void jbMeA(e8IauVVAsw *mpNsQw6AP7CHH, const void *FVKXvFKb) {
    fgsH3dt(mpNsQw6AP7CHH);
    fgsH3dt(FVKXvFKb);

    /* When unlink and unlink2 exist at the same time, we will only call unlink2. */
    RMb3owlk(0);
}

void cDzEZAGRp(YqoHe2Nj9g4 *f2mwJRbXPO, const void *FVKXvFKb) {
    xHJf *ErwzoH = (xHJf *)FVKXvFKb;

    const e8IauVVAsw *mpNsQw6AP7CHH = kDjCJC37(f2mwJRbXPO);
    int QfPDb9ww2y = FaRXb_z(f2mwJRbXPO);
    
    if (ErwzoH->lCuh5oIw3) {
        void *zOnN9J;
        OYj1omMcNhj(Ai7hWvD[QfPDb9ww2y], (e8IauVVAsw *)mpNsQw6AP7CHH, &zOnN9J);
        RMb3owlk(zOnN9J != O5xSuMtag9);
        F58dFnlYg((struct eBXiqjdS0YiHH *)zOnN9J);
    }
}

void cNexToK3sqYfp(JY6EeBSHD_ *pDT9FbD, void *FVKXvFKb) {
    xHJf *ErwzoH = (xHJf *)FVKXvFKb;
    ubspBWZ2J4Khw(pDT9FbD, ErwzoH->lCuh5oIw3);
    ubspBWZ2J4Khw(pDT9FbD, ErwzoH->IJxq8Y);
    ubspBWZ2J4Khw(pDT9FbD, ErwzoH->vSBo5dxNf);

    int QfPDb9ww2y = MnoY(pDT9FbD);
    const e8IauVVAsw *mpNsQw6AP7CHH = lTUjqgem6UC(pDT9FbD);
    
    if (ErwzoH->lCuh5oIw3) {
        int LnlcjWvDQZz;
        struct eBXiqjdS0YiHH *rPFc1c = (struct eBXiqjdS0YiHH *)Bt8tx6b0PC(Ai7hWvD[QfPDb9ww2y], (e8IauVVAsw *)mpNsQw6AP7CHH, &LnlcjWvDQZz);
        RMb3owlk(LnlcjWvDQZz == 0 && rPFc1c != O5xSuMtag9);

        struct eBXiqjdS0YiHH *P_R4jZfi1V = rPFc1c;
        while (P_R4jZfi1V) {
            S1kRKC(pDT9FbD, (const char *)P_R4jZfi1V->P_R4jZfi1V, HqEbj);
            P_R4jZfi1V = P_R4jZfi1V->g5WTZ;
        }
    }
}

void *zmoG(YqoHe2Nj9g4 *f2mwJRbXPO, const void *FVKXvFKb) {
    const xHJf *cCQcY = FVKXvFKb;
    xHJf *L83hO = ZTMXP7iq();
    L83hO->lCuh5oIw3 = cCQcY->lCuh5oIw3;
    L83hO->IJxq8Y = cCQcY->IJxq8Y;
    L83hO->vSBo5dxNf = cCQcY->vSBo5dxNf;

    int LTgiHqdT5p = FaRXb_z(f2mwJRbXPO);
    int ory8F6awo = a8vkDeBnqF(f2mwJRbXPO);
    const e8IauVVAsw *sxGLd = kDjCJC37(f2mwJRbXPO);
    const e8IauVVAsw *mg63dW = xovEoxA(f2mwJRbXPO);

    if (cCQcY->lCuh5oIw3) {
        int LnlcjWvDQZz;
        struct eBXiqjdS0YiHH *CZBfV = (struct eBXiqjdS0YiHH *)Bt8tx6b0PC(Ai7hWvD[LTgiHqdT5p], (e8IauVVAsw *)sxGLd, &LnlcjWvDQZz);
        RMb3owlk(LnlcjWvDQZz == 0 && CZBfV != O5xSuMtag9);
        struct eBXiqjdS0YiHH *fA2_0ZnZq0 = rliomIT1joYwe(CZBfV);
        RMb3owlk(fA2_0ZnZq0 != O5xSuMtag9);
        RkboK(Ai7hWvD[ory8F6awo], (e8IauVVAsw *)mg63dW, fA2_0ZnZq0);
    }   

    return L83hO;
}

zteGYGY1 SUhA(YqoHe2Nj9g4 *f2mwJRbXPO, const void *FVKXvFKb, zteGYGY1 eCMAwAYO) {
    fgsH3dt(f2mwJRbXPO);
    fgsH3dt(eCMAwAYO);
    RENY6J lCuh5oIw3 = 0;
    xHJf *ErwzoH = (xHJf *)FVKXvFKb;

    lCuh5oIw3 += sizeof(*ErwzoH);
    lCuh5oIw3 += ErwzoH->lCuh5oIw3 * sizeof(struct eBXiqjdS0YiHH);

    return lCuh5oIw3;
}

zteGYGY1 ImoWzKRtVq9lE(YqoHe2Nj9g4 *f2mwJRbXPO, const void *FVKXvFKb) {
    fgsH3dt(f2mwJRbXPO);
    xHJf *ErwzoH = (xHJf *)FVKXvFKb;
    return ErwzoH->lCuh5oIw3;
}

int ephgP2rF(HdGKcMKXp *f2mwJRbXPO, e8IauVVAsw **nHogzSS2Q0Z, int UEnn) {
    fgsH3dt(nHogzSS2Q0Z);
    fgsH3dt(UEnn);

    if (wSfciZMg(f2mwJRbXPO, "datatype2", 1,N5Dd) == W7TwHW0) {
        return W7TwHW0;
    }

    zJMEIIsS6I UK3H7NT = {
        .XA5BKgMlddh = dy9t9DD,
        .jHlmAT = Y_yiBYZ,
        .vam0 = y71JK,
        .pIz3Ct_CXs = hY3wU,
        .VTAGlPVX802RA = RKo0LBzDM,
        .REr5ND1t6Xtf = cNexToK3sqYfp,
        .qkpeL3wx_ = jbMeA,
        // .defrag = MemAllocDefrag, // Tested in defragtest.c
        .QlTG = cDzEZAGRp,
        .PNP_aKlL = zmoG,
        .X0woD0 = SUhA,
        .Svr_xnFC = ImoWzKRtVq9lE,
    };

    aS5oBt = KQc0Hq2(f2mwJRbXPO, "mem_alloc", 0, &UK3H7NT);
    if (aS5oBt == O5xSuMtag9) {
        return W7TwHW0;
    }

    if (lTOOi(f2mwJRbXPO, "mem.alloc", KDbUC1, "write deny-oom", 1, 1, 1) == W7TwHW0) {
        return W7TwHW0;
    }

    if (lTOOi(f2mwJRbXPO, "mem.free", QE8ieoK0, "write deny-oom", 1, 1, 1) == W7TwHW0) {
        return W7TwHW0;
    }

    if (lTOOi(f2mwJRbXPO, "mem.write", l3rhrSVbR8I, "write deny-oom", 1, 1, 1) == W7TwHW0) {
        return W7TwHW0;
    }

    if (lTOOi(f2mwJRbXPO, "mem.read", WCCQc94GV, "readonly", 1, 1, 1) == W7TwHW0) {
        return W7TwHW0;
    }

    if (lTOOi(f2mwJRbXPO, "mem.usage", ugef_, "readonly", 1, 1, 1) == W7TwHW0) {
        return W7TwHW0;
    }

    /* used for internal aof rewrite */
    if (lTOOi(f2mwJRbXPO, "mem.allocandwrite", YREsc, "write deny-oom", 1, 1, 1) == W7TwHW0) {
        return W7TwHW0;
    }

    for(int tIh5 = 0; tIh5 < Zt57ED; tIh5++){
        Ai7hWvD[tIh5] = PICv9xtgd1RoH(O5xSuMtag9);
    }

    JBiRLL(f2mwJRbXPO, Vnf4VyVXqEY, d5GQ);
    JBiRLL(f2mwJRbXPO, ndeTF8, ArhzVVWUv);
  
    return smlUiJJ;
}
