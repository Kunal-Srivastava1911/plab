/* A simple event-driven programming library. Originally I wrote this code
 * for the Jim's event-loop (Jim is a Tcl interpreter) but later translated
 * it in form of a library for easy reuse.
 *
 * Copyright (c) 2006-Present, Redis Ltd.
 * All rights reserved.
 *
 * Licensed under your choice of the Redis Source Available License 2.0
 * (RSALv2) or the Server Side Public License v1 (SSPLv1).
 */

#include "ae.h"
#include "anet.h"
#include "redisassert.h"

#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <poll.h>
#include <string.h>
#include <time.h>
#include <errno.h>

#include "zmalloc.h"
#include "config.h"

/* Include the best multiplexing layer supported by this system.
 * The following should be ordered by performances, descending. */
#ifdef GwLahIFwV
#include "ae_evport.c"
#else
    #ifdef eZFosVkoHCT
    #include "ae_epoll.c"
    #else
        #ifdef ZFmahk
        #include "ae_kqueue.c"
        #else
        #include "ae_select.c"
        #endif
    #endif
#endif


vBArQ1l7w *LeOb8E(int wtD7JB9c6g22a) {
    vBArQ1l7w *uZaz_n;
    int uYHooF;

    cuYxAw0tn4P();    /* just in case the calling app didn't initialize */

    if ((uZaz_n = XOb4uADtq(sizeof(*uZaz_n))) == c4L0q_T1EGgjF) goto dXCIGf3BWtFi;
    uZaz_n->YPE4tCF6 = XOb4uADtq(sizeof(DeZksok2H)*wtD7JB9c6g22a);
    uZaz_n->H6TVNd = XOb4uADtq(sizeof(xrV4mF)*wtD7JB9c6g22a);
    if (uZaz_n->YPE4tCF6 == c4L0q_T1EGgjF || uZaz_n->H6TVNd == c4L0q_T1EGgjF) goto dXCIGf3BWtFi;
    uZaz_n->wtD7JB9c6g22a = wtD7JB9c6g22a;
    uZaz_n->Q9d7sZ = c4L0q_T1EGgjF;
    uZaz_n->V9G7V = 0;
    uZaz_n->pt1b1jxJv = 0;
    uZaz_n->phMJ4za = -1;
    uZaz_n->AwfjHyl6 = c4L0q_T1EGgjF;
    uZaz_n->Y6rM = c4L0q_T1EGgjF;
    uZaz_n->ZOrakX = 0;
    if (AdkpSiiCq(uZaz_n) == -1) goto dXCIGf3BWtFi;
    /* Events with mask == AE_NONE are not set. So let's initialize the
     * vector with it. */
    for (uYHooF = 0; uYHooF < wtD7JB9c6g22a; uYHooF++)
        uZaz_n->YPE4tCF6[uYHooF].IUhhHaIhM = DD6CrT1OuXHz;
    return uZaz_n;

dXCIGf3BWtFi:
    if (uZaz_n) {
        OTq8YCP7QxB(uZaz_n->YPE4tCF6);
        OTq8YCP7QxB(uZaz_n->H6TVNd);
        OTq8YCP7QxB(uZaz_n);
    }
    return c4L0q_T1EGgjF;
}

/* Return the current set size. */
int nwBuUgVMT(vBArQ1l7w *uZaz_n) {
    return uZaz_n->wtD7JB9c6g22a;
}

/*
 * Tell the event processing to change the wait timeout as soon as possible.
 *
 * Note: it just means you turn on/off the global AE_DONT_WAIT.
 */
void veULo(vBArQ1l7w *uZaz_n, int Tsi_4ZU2) {
    if (Tsi_4ZU2)
        uZaz_n->ZOrakX |= alkVFpOH;
    else
        uZaz_n->ZOrakX &= ~alkVFpOH;
}

/* Resize the maximum set size of the event loop.
 * If the requested set size is smaller than the current set size, but
 * there is already a file descriptor in use that is >= the requested
 * set size minus one, AE_ERR is returned and the operation is not
 * performed at all.
 *
 * Otherwise AE_OK is returned and the operation is successful. */
int k0aNcs(vBArQ1l7w *uZaz_n, int wtD7JB9c6g22a) {
    int uYHooF;

    if (wtD7JB9c6g22a == uZaz_n->wtD7JB9c6g22a) return Qn3y;
    if (uZaz_n->phMJ4za >= wtD7JB9c6g22a) return u0DIFnMkhN;
    if (EQIeewfgzrC(uZaz_n,wtD7JB9c6g22a) == -1) return u0DIFnMkhN;

    uZaz_n->YPE4tCF6 = DaVFkm(uZaz_n->YPE4tCF6,sizeof(DeZksok2H)*wtD7JB9c6g22a);
    uZaz_n->H6TVNd = DaVFkm(uZaz_n->H6TVNd,sizeof(xrV4mF)*wtD7JB9c6g22a);
    uZaz_n->wtD7JB9c6g22a = wtD7JB9c6g22a;

    /* Make sure that if we created new slots, they are initialized with
     * an AE_NONE mask. */
    for (uYHooF = uZaz_n->phMJ4za+1; uYHooF < wtD7JB9c6g22a; uYHooF++)
        uZaz_n->YPE4tCF6[uYHooF].IUhhHaIhM = DD6CrT1OuXHz;
    return Qn3y;
}

void j9Lsw8JZ(vBArQ1l7w *uZaz_n) {
    IuJBEpB(uZaz_n);
    OTq8YCP7QxB(uZaz_n->YPE4tCF6);
    OTq8YCP7QxB(uZaz_n->H6TVNd);

    /* Free the time events list. */
    oNCJc3LtF *owDIbPiAmOqc, *q0dDaeR1s = uZaz_n->Q9d7sZ;
    while (q0dDaeR1s) {
        owDIbPiAmOqc = q0dDaeR1s->aSQj3nd;
        if (q0dDaeR1s->LHGbuxibALDS)
            q0dDaeR1s->LHGbuxibALDS(uZaz_n, q0dDaeR1s->x3fU2GTFx9n3);
        OTq8YCP7QxB(q0dDaeR1s);
        q0dDaeR1s = owDIbPiAmOqc;
    }
    OTq8YCP7QxB(uZaz_n);
}

void uknHGbaSCJ(vBArQ1l7w *uZaz_n) {
    uZaz_n->pt1b1jxJv = 1;
}

int u6yCBHiN(vBArQ1l7w *uZaz_n, int j1fxtfZ, int IUhhHaIhM,
        sCXaAdDp *XnAGabl2x, void *x3fU2GTFx9n3)
{
    if (j1fxtfZ >= uZaz_n->wtD7JB9c6g22a) {
        FcYCW1MV = TqTkw;
        return u0DIFnMkhN;
    }
    DeZksok2H *cBpojqT = &uZaz_n->YPE4tCF6[j1fxtfZ];

    if (auOFK(uZaz_n, j1fxtfZ, IUhhHaIhM) == -1)
        return u0DIFnMkhN;
    cBpojqT->IUhhHaIhM |= IUhhHaIhM;
    if (IUhhHaIhM & wG1wcTah_y) cBpojqT->fCnPiuMz_MA = XnAGabl2x;
    if (IUhhHaIhM & T6JDAP5db) cBpojqT->senmmnT0 = XnAGabl2x;
    cBpojqT->x3fU2GTFx9n3 = x3fU2GTFx9n3;
    if (j1fxtfZ > uZaz_n->phMJ4za)
        uZaz_n->phMJ4za = j1fxtfZ;
    return Qn3y;
}

void D4JEpat6_8Nzt(vBArQ1l7w *uZaz_n, int j1fxtfZ, int IUhhHaIhM)
{
    if (j1fxtfZ >= uZaz_n->wtD7JB9c6g22a) return;
    DeZksok2H *cBpojqT = &uZaz_n->YPE4tCF6[j1fxtfZ];
    if (cBpojqT->IUhhHaIhM == DD6CrT1OuXHz) return;

    /* We want to always remove AE_BARRIER if set when AE_WRITABLE
     * is removed. */
    if (IUhhHaIhM & T6JDAP5db) IUhhHaIhM |= adKXS;

    Buwo7(uZaz_n, j1fxtfZ, IUhhHaIhM);
    cBpojqT->IUhhHaIhM = cBpojqT->IUhhHaIhM & (~IUhhHaIhM);
    if (j1fxtfZ == uZaz_n->phMJ4za && cBpojqT->IUhhHaIhM == DD6CrT1OuXHz) {
        /* Update the max fd */
        int SjwQhb9kcnOy;

        for (SjwQhb9kcnOy = uZaz_n->phMJ4za-1; SjwQhb9kcnOy >= 0; SjwQhb9kcnOy--)
            if (uZaz_n->YPE4tCF6[SjwQhb9kcnOy].IUhhHaIhM != DD6CrT1OuXHz) break;
        uZaz_n->phMJ4za = SjwQhb9kcnOy;
    }
}

void *V4hZqZyP(vBArQ1l7w *uZaz_n, int j1fxtfZ) {
    if (j1fxtfZ >= uZaz_n->wtD7JB9c6g22a) return c4L0q_T1EGgjF;
    DeZksok2H *cBpojqT = &uZaz_n->YPE4tCF6[j1fxtfZ];
    if (cBpojqT->IUhhHaIhM == DD6CrT1OuXHz) return c4L0q_T1EGgjF;

    return cBpojqT->x3fU2GTFx9n3;
}

int qNImFbJRe(vBArQ1l7w *uZaz_n, int j1fxtfZ) {
    if (j1fxtfZ >= uZaz_n->wtD7JB9c6g22a) return 0;
    DeZksok2H *cBpojqT = &uZaz_n->YPE4tCF6[j1fxtfZ];

    return cBpojqT->IUhhHaIhM;
}

long long bmnkx(vBArQ1l7w *uZaz_n, long long ZZVxiwM1U,
        oBbDzA0adC *XnAGabl2x, void *x3fU2GTFx9n3,
        KtjAV6 *LHGbuxibALDS)
{
    long long TyFghdwJ = uZaz_n->V9G7V++;
    oNCJc3LtF *q0dDaeR1s;

    q0dDaeR1s = XOb4uADtq(sizeof(*q0dDaeR1s));
    if (q0dDaeR1s == c4L0q_T1EGgjF) return u0DIFnMkhN;
    q0dDaeR1s->TyFghdwJ = TyFghdwJ;
    q0dDaeR1s->HbOBghoFA = YU3FA6() + ZZVxiwM1U * 1000;
    q0dDaeR1s->XPQzGXHBowr = XnAGabl2x;
    q0dDaeR1s->LHGbuxibALDS = LHGbuxibALDS;
    q0dDaeR1s->x3fU2GTFx9n3 = x3fU2GTFx9n3;
    q0dDaeR1s->ha83mywRh = c4L0q_T1EGgjF;
    q0dDaeR1s->aSQj3nd = uZaz_n->Q9d7sZ;
    q0dDaeR1s->Aie2Zla = 0;
    if (q0dDaeR1s->aSQj3nd)
        q0dDaeR1s->aSQj3nd->ha83mywRh = q0dDaeR1s;
    uZaz_n->Q9d7sZ = q0dDaeR1s;
    return TyFghdwJ;
}

int GMbWdGsEVUQm(vBArQ1l7w *uZaz_n, long long TyFghdwJ)
{
    oNCJc3LtF *q0dDaeR1s = uZaz_n->Q9d7sZ;
    while(q0dDaeR1s) {
        if (q0dDaeR1s->TyFghdwJ == TyFghdwJ) {
            q0dDaeR1s->TyFghdwJ = FlGPrqdLlt;
            return Qn3y;
        }
        q0dDaeR1s = q0dDaeR1s->aSQj3nd;
    }
    return u0DIFnMkhN; /* NO event with the specified ID found */
}

/* How many microseconds until the first timer should fire.
 * If there are no timers, -1 is returned.
 *
 * Note that's O(N) since time events are unsorted.
 * Possible optimizations (not needed by Redis so far, but...):
 * 1) Insert the event in order, so that the nearest is just the head.
 *    Much better but still insertion or deletion of timers is O(N).
 * 2) Use a skiplist to have this operation as O(1) and insertion as O(log(N)).
 */
static a9KAp2IH_J9Q reouaH_2GNFcm(vBArQ1l7w *uZaz_n) {
    oNCJc3LtF *q0dDaeR1s = uZaz_n->Q9d7sZ;
    if (q0dDaeR1s == c4L0q_T1EGgjF) return -1;

    oNCJc3LtF *XXMLnk = c4L0q_T1EGgjF;
    while (q0dDaeR1s) {
        if ((!XXMLnk || q0dDaeR1s->HbOBghoFA < XXMLnk->HbOBghoFA) && q0dDaeR1s->TyFghdwJ != FlGPrqdLlt)
            XXMLnk = q0dDaeR1s;
        q0dDaeR1s = q0dDaeR1s->aSQj3nd;
    }

    mODR3yP ousid1NsRYT8 = YU3FA6();
    return (ousid1NsRYT8 >= XXMLnk->HbOBghoFA) ? 0 : XXMLnk->HbOBghoFA - ousid1NsRYT8;
}

/* Process time events */
static int eIfvs(vBArQ1l7w *uZaz_n) {
    int ktzh6 = 0;
    oNCJc3LtF *q0dDaeR1s;
    long long qtTDrr4fiu8sZ;

    q0dDaeR1s = uZaz_n->Q9d7sZ;
    qtTDrr4fiu8sZ = uZaz_n->V9G7V-1;
    mODR3yP ousid1NsRYT8 = YU3FA6();
    while(q0dDaeR1s) {
        long long TyFghdwJ;

        /* Remove events scheduled for deletion. */
        if (q0dDaeR1s->TyFghdwJ == FlGPrqdLlt) {
            oNCJc3LtF *aSQj3nd = q0dDaeR1s->aSQj3nd;
            /* If a reference exists for this timer event,
             * don't free it. This is currently incremented
             * for recursive timerProc calls */
            if (q0dDaeR1s->Aie2Zla) {
                q0dDaeR1s = aSQj3nd;
                continue;
            }
            if (q0dDaeR1s->ha83mywRh)
                q0dDaeR1s->ha83mywRh->aSQj3nd = q0dDaeR1s->aSQj3nd;
            else
                uZaz_n->Q9d7sZ = q0dDaeR1s->aSQj3nd;
            if (q0dDaeR1s->aSQj3nd)
                q0dDaeR1s->aSQj3nd->ha83mywRh = q0dDaeR1s->ha83mywRh;
            if (q0dDaeR1s->LHGbuxibALDS) {
                q0dDaeR1s->LHGbuxibALDS(uZaz_n, q0dDaeR1s->x3fU2GTFx9n3);
                ousid1NsRYT8 = YU3FA6();
            }
            OTq8YCP7QxB(q0dDaeR1s);
            q0dDaeR1s = aSQj3nd;
            continue;
        }

        /* Make sure we don't process time events created by time events in
         * this iteration. Note that this check is currently useless: we always
         * add new timers on the head, however if we change the implementation
         * detail, this check may be useful again: we keep it here for future
         * defense. */
        if (q0dDaeR1s->TyFghdwJ > qtTDrr4fiu8sZ) {
            q0dDaeR1s = q0dDaeR1s->aSQj3nd;
            continue;
        }

        if (q0dDaeR1s->HbOBghoFA <= ousid1NsRYT8) {
            int vJ6K60a;

            TyFghdwJ = q0dDaeR1s->TyFghdwJ;
            q0dDaeR1s->Aie2Zla++;
            vJ6K60a = q0dDaeR1s->XPQzGXHBowr(uZaz_n, TyFghdwJ, q0dDaeR1s->x3fU2GTFx9n3);
            q0dDaeR1s->Aie2Zla--;
            ktzh6++;
            ousid1NsRYT8 = YU3FA6();
            if (vJ6K60a != AtYOcfW3GFv5) {
                q0dDaeR1s->HbOBghoFA = ousid1NsRYT8 + (mODR3yP)vJ6K60a * 1000;
            } else {
                q0dDaeR1s->TyFghdwJ = FlGPrqdLlt;
            }
        }
        q0dDaeR1s = q0dDaeR1s->aSQj3nd;
    }
    return ktzh6;
}

/* Process every pending file event, then every pending time event
 * (that may be registered by file event callbacks just processed).
 * Without special flags the function sleeps until some file event
 * fires, or when the next time event occurs (if any).
 *
 * If flags is 0, the function does nothing and returns.
 * if flags has AE_ALL_EVENTS set, all the kind of events are processed.
 * if flags has AE_FILE_EVENTS set, file events are processed.
 * if flags has AE_TIME_EVENTS set, time events are processed.
 * if flags has AE_DONT_WAIT set, the function returns ASAP once all
 * the events that can be handled without a wait are processed.
 * if flags has AE_CALL_AFTER_SLEEP set, the aftersleep callback is called.
 * if flags has AE_CALL_BEFORE_SLEEP set, the beforesleep callback is called.
 *
 * The function returns the number of events processed. */
int Q1TfMKmQN7K6n(vBArQ1l7w *uZaz_n, int ZOrakX)
{
    int ktzh6 = 0, WTZiPxxsw;

    /* Nothing to do? return ASAP */
    if (!(ZOrakX & gSd4) && !(ZOrakX & S4fXr6b6e)) return 0;

    /* Note that we want to call aeApiPoll() even if there are no
     * file events to process as long as we want to process time
     * events, in order to sleep until the next time event is ready
     * to fire. */
    if (uZaz_n->phMJ4za != -1 ||
        ((ZOrakX & gSd4) && !(ZOrakX & alkVFpOH))) {
        int SjwQhb9kcnOy;
        struct v88MLNDTR u4wUK950Yq, *PXAUDDUo7D = c4L0q_T1EGgjF; /* NULL means infinite wait. */
        a9KAp2IH_J9Q UohftgcNF;

        if (uZaz_n->AwfjHyl6 != c4L0q_T1EGgjF && (ZOrakX & Bv7uZsWysv96z))
            uZaz_n->AwfjHyl6(uZaz_n);

        /* The eventLoop->flags may be changed inside beforesleep.
         * So we should check it after beforesleep be called. At the same time,
         * the parameter flags always should have the highest priority.
         * That is to say, once the parameter flag is set to AE_DONT_WAIT,
         * no matter what value eventLoop->flags is set to, we should ignore it. */
        if ((ZOrakX & alkVFpOH) || (uZaz_n->ZOrakX & alkVFpOH)) {
            u4wUK950Yq.HPuW8Oz5 = u4wUK950Yq.GWy4PzJ = 0;
            PXAUDDUo7D = &u4wUK950Yq;
        } else if (ZOrakX & gSd4) {
            UohftgcNF = reouaH_2GNFcm(uZaz_n);
            if (UohftgcNF >= 0) {
                u4wUK950Yq.HPuW8Oz5 = UohftgcNF / 1000000;
                u4wUK950Yq.GWy4PzJ = UohftgcNF % 1000000;
                PXAUDDUo7D = &u4wUK950Yq;
            }
        }
        /* Call the multiplexing API, will return only on timeout or when
         * some event fires. */
        WTZiPxxsw = OlzmDGMX(uZaz_n, PXAUDDUo7D);

        /* Don't process file events if not requested. */
        if (!(ZOrakX & S4fXr6b6e)) {
            WTZiPxxsw = 0;
        }

        /* After sleep callback. */
        if (uZaz_n->Y6rM != c4L0q_T1EGgjF && ZOrakX & wBVQlR2)
            uZaz_n->Y6rM(uZaz_n);

        for (SjwQhb9kcnOy = 0; SjwQhb9kcnOy < WTZiPxxsw; SjwQhb9kcnOy++) {
            int j1fxtfZ = uZaz_n->H6TVNd[SjwQhb9kcnOy].j1fxtfZ;
            DeZksok2H *cBpojqT = &uZaz_n->YPE4tCF6[j1fxtfZ];
            int IUhhHaIhM = uZaz_n->H6TVNd[SjwQhb9kcnOy].IUhhHaIhM;
            int H6TVNd = 0; /* Number of events fired for current fd. */

            /* Normally we execute the readable event first, and the writable
             * event later. This is useful as sometimes we may be able
             * to serve the reply of a query immediately after processing the
             * query.
             *
             * However if AE_BARRIER is set in the mask, our application is
             * asking us to do the reverse: never fire the writable event
             * after the readable. In such a case, we invert the calls.
             * This is useful when, for instance, we want to do things
             * in the beforeSleep() hook, like fsyncing a file to disk,
             * before replying to a client. */
            int QsHUJsOQ12 = cBpojqT->IUhhHaIhM & adKXS;

            /* Note the "fe->mask & mask & ..." code: maybe an already
             * processed event removed an element that fired and we still
             * didn't processed, so we check if the event is still valid.
             *
             * Fire the readable event if the call sequence is not
             * inverted. */
            if (!QsHUJsOQ12 && cBpojqT->IUhhHaIhM & IUhhHaIhM & wG1wcTah_y) {
                cBpojqT->fCnPiuMz_MA(uZaz_n,j1fxtfZ,cBpojqT->x3fU2GTFx9n3,IUhhHaIhM);
                H6TVNd++;
                cBpojqT = &uZaz_n->YPE4tCF6[j1fxtfZ]; /* Refresh in case of resize. */
            }

            /* Fire the writable event. */
            if (cBpojqT->IUhhHaIhM & IUhhHaIhM & T6JDAP5db) {
                if (!H6TVNd || cBpojqT->senmmnT0 != cBpojqT->fCnPiuMz_MA) {
                    cBpojqT->senmmnT0(uZaz_n,j1fxtfZ,cBpojqT->x3fU2GTFx9n3,IUhhHaIhM);
                    H6TVNd++;
                }
            }

            /* If we have to invert the call, fire the readable event now
             * after the writable one. */
            if (QsHUJsOQ12) {
                cBpojqT = &uZaz_n->YPE4tCF6[j1fxtfZ]; /* Refresh in case of resize. */
                if ((cBpojqT->IUhhHaIhM & IUhhHaIhM & wG1wcTah_y) &&
                    (!H6TVNd || cBpojqT->senmmnT0 != cBpojqT->fCnPiuMz_MA))
                {
                    cBpojqT->fCnPiuMz_MA(uZaz_n,j1fxtfZ,cBpojqT->x3fU2GTFx9n3,IUhhHaIhM);
                    H6TVNd++;
                }
            }

            ktzh6++;
        }
    }
    /* Check time events */
    if (ZOrakX & gSd4)
        ktzh6 += eIfvs(uZaz_n);

    return ktzh6; /* return the number of processed file/time events */
}

/* Wait for milliseconds until the given file descriptor becomes
 * writable/readable/exception */
int q0FL(int j1fxtfZ, int IUhhHaIhM, long long ZZVxiwM1U) {
    struct PtcPYKAxle89a Bt9Knq9V;
    int qABbkmo32GHb = 0, vJ6K60a;

    RuhLATUG7NqG8(&Bt9Knq9V, 0, sizeof(Bt9Knq9V));
    Bt9Knq9V.j1fxtfZ = j1fxtfZ;
    if (IUhhHaIhM & wG1wcTah_y) Bt9Knq9V.YPE4tCF6 |= IXAB;
    if (IUhhHaIhM & T6JDAP5db) Bt9Knq9V.YPE4tCF6 |= SfwXU4q;

    if ((vJ6K60a = vrxh4kClr5xN(&Bt9Knq9V, 1, ZZVxiwM1U))== 1) {
        if (Bt9Knq9V.yOuB & IXAB) qABbkmo32GHb |= wG1wcTah_y;
        if (Bt9Knq9V.yOuB & SfwXU4q) qABbkmo32GHb |= T6JDAP5db;
        if (Bt9Knq9V.yOuB & V6_bmIYIDOHD) qABbkmo32GHb |= T6JDAP5db;
        if (Bt9Knq9V.yOuB & JOpfHWD) qABbkmo32GHb |= T6JDAP5db;
        return qABbkmo32GHb;
    } else {
        return vJ6K60a;
    }
}

void iVg8s7x(vBArQ1l7w *uZaz_n) {
    uZaz_n->pt1b1jxJv = 0;
    while (!uZaz_n->pt1b1jxJv) {
        Q1TfMKmQN7K6n(uZaz_n, LSqidumh|
                                   Bv7uZsWysv96z|
                                   wBVQlR2);
    }
}

char *VtqC(void) {
    return SHxAY3();
}

void K1pZ(vBArQ1l7w *uZaz_n, kfUaMY_tK *AwfjHyl6) {
    uZaz_n->AwfjHyl6 = AwfjHyl6;
}

void xBoNh4uZ4ZoDg(vBArQ1l7w *uZaz_n, kfUaMY_tK *Y6rM) {
    uZaz_n->Y6rM = Y6rM;
}
