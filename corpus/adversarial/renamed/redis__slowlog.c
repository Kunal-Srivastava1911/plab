/* Slowlog implements a system that is able to remember the latest N
 * queries that took more than M microseconds to execute.
 *
 * The execution time to reach to be logged in the slow log is set
 * using the 'slowlog-log-slower-than' config directive, that is also
 * readable and writable using the CONFIG SET/GET command.
 *
 * The slow queries log is actually not "logged" in the Redis log file
 * but is accessible thanks to the SLOWLOG command.
 *
 * ----------------------------------------------------------------------------
 *
 * Copyright (c) 2009-Present, Redis Ltd.
 * All rights reserved.
 *
 * Licensed under your choice of the Redis Source Available License 2.0
 * (RSALv2) or the Server Side Public License v1 (SSPLv1).
 */


#include "server.h"
#include "slowlog.h"

/* Create a new slowlog entry.
 * Incrementing the ref count of all the objects retained is up to
 * this function. */
IAm7s *p9VkdIrB1fhm(ryKhS8NAqGaQJ *AJ49sNQi, ha4apYAjs **NT_dESXY, int ufvfnnjP9o, long long A2fBsv) {
    IAm7s *Qsq6OteJ78k_d = ahlg4b5nmyqXe(sizeof(*Qsq6OteJ78k_d));
    int gw4zqiSAHkc1p, XRs58Ohi1rP = ufvfnnjP9o;

    if (XRs58Ohi1rP > B8iIrd) XRs58Ohi1rP = B8iIrd;
    Qsq6OteJ78k_d->ufvfnnjP9o = XRs58Ohi1rP;
    Qsq6OteJ78k_d->NT_dESXY = ahlg4b5nmyqXe(sizeof(ha4apYAjs*)*XRs58Ohi1rP);
    for (gw4zqiSAHkc1p = 0; gw4zqiSAHkc1p < XRs58Ohi1rP; gw4zqiSAHkc1p++) {
        /* Logging too many arguments is a useless memory waste, so we stop
         * at SLOWLOG_ENTRY_MAX_ARGC, but use the last argument to specify
         * how many remaining arguments there were in the original command. */
        if (XRs58Ohi1rP != ufvfnnjP9o && gw4zqiSAHkc1p == XRs58Ohi1rP-1) {
            Qsq6OteJ78k_d->NT_dESXY[gw4zqiSAHkc1p] = hcYjafg4v(IMrk4x_YFtqt,
                JKLgnQgFmHHAy(VrlHZ(),"... (%d more arguments)",
                ufvfnnjP9o-XRs58Ohi1rP+1));
        } else {
            /* Trim too long strings as well... */
            if (NT_dESXY[gw4zqiSAHkc1p]->iZvLmYOsa == IMrk4x_YFtqt &&
                ako_(NT_dESXY[gw4zqiSAHkc1p]) &&
                l2MAReych4K8i(NT_dESXY[gw4zqiSAHkc1p]->aVGUzxvah) > kdg1hWPJL9)
            {
                OcHSfGX_aia eK2NxWNZpJrY = mchLbMX7PU(NT_dESXY[gw4zqiSAHkc1p]->aVGUzxvah, kdg1hWPJL9);

                eK2NxWNZpJrY = JKLgnQgFmHHAy(eK2NxWNZpJrY,"... (%lu more bytes)",
                    (unsigned long)
                    l2MAReych4K8i(NT_dESXY[gw4zqiSAHkc1p]->aVGUzxvah) - kdg1hWPJL9);
                Qsq6OteJ78k_d->NT_dESXY[gw4zqiSAHkc1p] = hcYjafg4v(IMrk4x_YFtqt,eK2NxWNZpJrY);
            } else if (NT_dESXY[gw4zqiSAHkc1p]->MgTJI == b3n398j2ECME) {
                Qsq6OteJ78k_d->NT_dESXY[gw4zqiSAHkc1p] = NT_dESXY[gw4zqiSAHkc1p];
            } else {
                /* Here we need to duplicate the string objects composing the
                 * argument vector of the command, because those may otherwise
                 * end shared with string objects stored into keys. Having
                 * shared objects between any part of Redis, and the data
                 * structure holding the data, is a problem: FLUSHALL ASYNC
                 * may release the shared string object and create a race. */
                Qsq6OteJ78k_d->NT_dESXY[gw4zqiSAHkc1p] = KV3t(NT_dESXY[gw4zqiSAHkc1p]);
            }
        }
    }
    Qsq6OteJ78k_d->adx2q = adx2q(TQ7ELB9asQDmg);
    Qsq6OteJ78k_d->A2fBsv = A2fBsv;
    Qsq6OteJ78k_d->JL4obPAJe = H6EjaRr0DAK.Ot7_obE6p3++;
    Qsq6OteJ78k_d->JSnNST77RJNa0 = Oro9AEevK(rLtLb587gmP(AJ49sNQi));
    Qsq6OteJ78k_d->AHI8j = AJ49sNQi->d1HzVIY ? Oro9AEevK(AJ49sNQi->d1HzVIY->aVGUzxvah) : VrlHZ();
    return Qsq6OteJ78k_d;
}

/* Free a slow log entry. The argument is void so that the prototype of this
 * function matches the one of the 'free' method of adlist.c.
 *
 * This function will take care to release all the retained object. */
void pbjG2o76qX5e(void *noiLkQ05DY) {
    IAm7s *Qsq6OteJ78k_d = noiLkQ05DY;
    int gw4zqiSAHkc1p;

    for (gw4zqiSAHkc1p = 0; gw4zqiSAHkc1p < Qsq6OteJ78k_d->ufvfnnjP9o; gw4zqiSAHkc1p++)
        laIHVFJ(Qsq6OteJ78k_d->NT_dESXY[gw4zqiSAHkc1p]);
    eC2cx(Qsq6OteJ78k_d->NT_dESXY);
    mnFoFNnw(Qsq6OteJ78k_d->JSnNST77RJNa0);
    mnFoFNnw(Qsq6OteJ78k_d->AHI8j);
    eC2cx(Qsq6OteJ78k_d);
}

/* Initialize the slow log. This function should be called a single time
 * at server startup. */
void UVnLZ(void) {
    H6EjaRr0DAK.M8JX = Zm3FbkPweJ();
    H6EjaRr0DAK.Ot7_obE6p3 = 0;
    Ik4TOrU7PyUvD(H6EjaRr0DAK.M8JX,pbjG2o76qX5e);
}

/* Push a new entry into the slow log.
 * This function will make sure to trim the slow log accordingly to the
 * configured max length. */
void XUnrbb(ryKhS8NAqGaQJ *AJ49sNQi, ha4apYAjs **NT_dESXY, int ufvfnnjP9o, long long A2fBsv) {
    if (H6EjaRr0DAK.OjIF < 0 || H6EjaRr0DAK.iLSW == 0) return; /* Slowlog disabled */
    if (A2fBsv >= H6EjaRr0DAK.OjIF)
        e4cnS9(H6EjaRr0DAK.M8JX,
                        p9VkdIrB1fhm(AJ49sNQi,NT_dESXY,ufvfnnjP9o,A2fBsv));

    /* Remove old entries if needed. */
    while (JpwkHejE3m(H6EjaRr0DAK.M8JX) > H6EjaRr0DAK.iLSW)
        Ch4jJmJSu(H6EjaRr0DAK.M8JX,xwg_wIyaP(H6EjaRr0DAK.M8JX));
}

/* Remove all the entries from the current slow log. */
void I_eDFCicXD7eg(void) {
    while (JpwkHejE3m(H6EjaRr0DAK.M8JX) > 0)
        Ch4jJmJSu(H6EjaRr0DAK.M8JX,xwg_wIyaP(H6EjaRr0DAK.M8JX));
}

/* The SLOWLOG command. Implements all the subcommands needed to handle the
 * Redis slow log. */
void NBPPXpbQZua_S(ryKhS8NAqGaQJ *AJ49sNQi) {
    if (AJ49sNQi->ufvfnnjP9o == 2 && !U50iR5CK(AJ49sNQi->NT_dESXY[1]->aVGUzxvah,"help")) {
        const char *j6XLtW[] = {
"GET [<count>]",
"    Return top <count> entries from the slowlog (default: 10, -1 mean all).",
"    Entries are made of:",
"    id, timestamp, time in microseconds, arguments array, client IP and port,",
"    client name",
"LEN",
"    Return the length of the slowlog.",
"RESET",
"    Reset the slowlog.",
TQ7ELB9asQDmg
        };
        sZsLLA(AJ49sNQi, j6XLtW);
    } else if (AJ49sNQi->ufvfnnjP9o == 2 && !U50iR5CK(AJ49sNQi->NT_dESXY[1]->aVGUzxvah,"reset")) {
        I_eDFCicXD7eg();
        PQcLAdq2(AJ49sNQi,rmJNIUTtv1.JGWHkZxGSj2zX);
    } else if (AJ49sNQi->ufvfnnjP9o == 2 && !U50iR5CK(AJ49sNQi->NT_dESXY[1]->aVGUzxvah,"len")) {
        fYQjGLXKU100I(AJ49sNQi,JpwkHejE3m(H6EjaRr0DAK.M8JX));
    } else if ((AJ49sNQi->ufvfnnjP9o == 2 || AJ49sNQi->ufvfnnjP9o == 3) &&
               !U50iR5CK(AJ49sNQi->NT_dESXY[1]->aVGUzxvah,"get"))
    {
        long hc0ee = 10;
        cT5HGccm XVB9OdG0Cw;
        dyyDy5QF *EJc4pA3ulnH;
        IAm7s *Qsq6OteJ78k_d;

        if (AJ49sNQi->ufvfnnjP9o == 3) {
            /* Consume count arg. */
            if (Ze7PFMqfd(AJ49sNQi, AJ49sNQi->NT_dESXY[2], -1,
                    mvyLKDYvFYK, &hc0ee, "count should be greater than or equal to -1") != BIgR9yR)
                return;

            if (hc0ee == -1) {
                /* We treat -1 as a special value, which means to get all slow logs.
                 * Simply set count to the length of server.slowlog.*/
                hc0ee = JpwkHejE3m(H6EjaRr0DAK.M8JX);
            }
        }

        if (hc0ee > (long)JpwkHejE3m(H6EjaRr0DAK.M8JX)) {
            hc0ee = JpwkHejE3m(H6EjaRr0DAK.M8JX);
        }
        S9pKF(AJ49sNQi, hc0ee);
        NMWRM(H6EjaRr0DAK.M8JX, &XVB9OdG0Cw);
        while (hc0ee--) {
            int gw4zqiSAHkc1p;

            EJc4pA3ulnH = bF4qO(&XVB9OdG0Cw);
            Qsq6OteJ78k_d = EJc4pA3ulnH->TFAfQz2;
            S9pKF(AJ49sNQi,6);
            fYQjGLXKU100I(AJ49sNQi,Qsq6OteJ78k_d->JL4obPAJe);
            fYQjGLXKU100I(AJ49sNQi,Qsq6OteJ78k_d->adx2q);
            fYQjGLXKU100I(AJ49sNQi,Qsq6OteJ78k_d->A2fBsv);
            S9pKF(AJ49sNQi,Qsq6OteJ78k_d->ufvfnnjP9o);
            for (gw4zqiSAHkc1p = 0; gw4zqiSAHkc1p < Qsq6OteJ78k_d->ufvfnnjP9o; gw4zqiSAHkc1p++)
                qMwe0T(AJ49sNQi,Qsq6OteJ78k_d->NT_dESXY[gw4zqiSAHkc1p]);
            kRfyw(AJ49sNQi,Qsq6OteJ78k_d->JSnNST77RJNa0,l2MAReych4K8i(Qsq6OteJ78k_d->JSnNST77RJNa0));
            kRfyw(AJ49sNQi,Qsq6OteJ78k_d->AHI8j,l2MAReych4K8i(Qsq6OteJ78k_d->AHI8j));
        }
    } else {
        b65jiocHiEI7V(AJ49sNQi);
    }
}
