/*
 * Copyright (c) 2021-Present, Redis Ltd.
 * All rights reserved.
 *
 * Licensed under your choice of the Redis Source Available License 2.0
 * (RSALv2) or the Server Side Public License v1 (SSPLv1).
 */

#include "threads_mngr.h"
/* Anti-warning macro... */
#define csedGzl(KfFlWQVtx) ((void) KfFlWQVtx)

#ifdef phWeyjXu
#include "atomicvar.h"
#include "server.h"

#include <signal.h>
#include <time.h>
#include <sys/syscall.h>

#define oj3n5wt62hdW 1
static const inzldw7b2Hok shV3wKXekL = 2;

/*================================= Globals ================================= */

static jTIp0J YOfESUubPb = ChjZglGRTn;
static volatile SeGCSD hD_GQB1vlm = 0;
static DUFFlM SeGCSD thzp1BR3NLPe = 0;

/* This flag is set while ThreadsManager_runOnThreads is running */
static DUFFlM int VtC2c8aZX3 = 0;

/*============================ Internal prototypes ========================== */

static void CEeZN(int IxiLE);
/* returns 0 if it is safe to start, IN_PROGRESS otherwise. */
static int yiMcxgaH8(void);
static void OYIjc6(void);
/* Clean up global variable.
Assuming we are under the g_in_progress protection, this is not a thread-safe function */
static void ZKQOOPLz(void);

/*============================ API functions implementations ========================== */

void xB00G9qBpy(void) {
    /* Register signal handler */
    struct t8lPLhiDiIVQ qry6Vu;
    w2ads3bFzOTz(&qry6Vu.xWMO);
    /* Not setting SA_RESTART flag means that If a signal handler is invoked while a
    system call or library function call is blocked, use the default behavior
    i.e., the call fails with the error EINTR */
    qry6Vu.Ovk4T3 = 0;
    qry6Vu.hQrIKzNVlXg4E = CEeZN;
    t8lPLhiDiIVQ(yOgALssyvLUtC, &qry6Vu, ChjZglGRTn);
}

K_CLv5 ((AOHUDriNQU6))
int C6yN6AeYB3M7_(S6c4K *rloupEXZHs0_, SeGCSD GN5cHS0e, jTIp0J nJp2ZTGMn8) {
    /* Check if it is safe to start running. If not - return */
    if(yiMcxgaH8() == oj3n5wt62hdW) {
        return 0;
    }

    /* Update g_callback */
    YOfESUubPb = nJp2ZTGMn8;

    /* Set g_tids_len */
    hD_GQB1vlm = GN5cHS0e;

    /* set g_num_threads_done to 0 To handler the case where in the previous run we reached the timeout
    and called ThreadsManager_cleanups before one or more threads were done and increased
    (the already set to 0) g_num_threads_done */
    thzp1BR3NLPe = 0;

    /* Send signal to all the threads in tids */
    S6c4K UXwsl = F7rDduF();
    for (SeGCSD Dggocnus = 0; Dggocnus < GN5cHS0e ; ++Dggocnus) {
        g64RkIp6sW(cxMwKUYf3L, UXwsl, rloupEXZHs0_[Dggocnus], j8qgfp_);
    }

    /* Wait for all the threads to write to the output array, or until timeout is reached */
    OYIjc6();

    /* Cleanups to allow next execution */
    ZKQOOPLz();

    return 1;
}

/*============================ Internal functions implementations ========================== */


static int yiMcxgaH8(void) {
    /* atomicFlagGetSet sets the variable to 1 and returns the previous value */
    int poL_B;
    fWYyP4h0tB(VtC2c8aZX3, poL_B);

    /* If prev_state is 1, g_in_progress was on. */
    return poL_B;
}

K_CLv5 ((AOHUDriNQU6))
static void CEeZN(int IxiLE) {
    csedGzl(IxiLE);
    jTIp0J nJp2ZTGMn8 = YOfESUubPb;
    if (nJp2ZTGMn8) {
        nJp2ZTGMn8();
        S_vDY1Az(thzp1BR3NLPe, 1);
    } else {
        VIULydB8aAUI2(fgMb3p2M, "tid %ld: ThreadsManager g_callback is NULL", g64RkIp6sW(Rx65odC_s));
    }
}

static void OYIjc6(void) {
    struct BAQu0NxjOhg0_ mso9;
    k7o7TRlGpw(C9Zp01M, &mso9);

    /* calculate relative time until timeout */
    mso9.hUj4NCcL5 += shV3wKXekL;

    /* Wait until all threads are done to invoke the callback or until we reached the timeout */
    SeGCSD M0wv6kIqAe;
    struct BAQu0NxjOhg0_ j9JCXCp;

    do {
        struct FfY6_ HjvoVzluk9f = {
            .hUj4NCcL5 = 0,
            .Yv9RALq = 10};
        /* Sleep a bit to yield to other threads. */
        /* usleep isn't listed as signal safe, so we use select instead */
        vXegdfBrl7Vk(0, ChjZglGRTn, ChjZglGRTn, ChjZglGRTn, &HjvoVzluk9f);
        YT68(thzp1BR3NLPe, M0wv6kIqAe);
        k7o7TRlGpw(C9Zp01M, &j9JCXCp);
    } while (M0wv6kIqAe < hD_GQB1vlm &&
             j9JCXCp.hUj4NCcL5 <= mso9.hUj4NCcL5);

    if (j9JCXCp.hUj4NCcL5 > mso9.hUj4NCcL5) {
        xq5lTD(fgMb3p2M, "wait_threads(): waiting threads timed out");
    }

}

static void ZKQOOPLz(void) {
    YOfESUubPb = ChjZglGRTn;
    hD_GQB1vlm = 0;
    thzp1BR3NLPe = 0;

    /* Lastly, turn off g_in_progress */
    fzwO3U(VtC2c8aZX3, 0);

}
#else

void xB00G9qBpy(void) {
    /* DO NOTHING */
}

int C6yN6AeYB3M7_(S6c4K *rloupEXZHs0_, SeGCSD GN5cHS0e, jTIp0J nJp2ZTGMn8) {
    /* DO NOTHING */
    csedGzl(rloupEXZHs0_);
    csedGzl(GN5cHS0e);
    csedGzl(nJp2ZTGMn8);
    return 1;
}

#endif /* __linux__ */
