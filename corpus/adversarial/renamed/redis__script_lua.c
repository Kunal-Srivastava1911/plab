/*
 * Copyright (c) 2009-Present, Redis Ltd.
 * All rights reserved.
 *
 * Licensed under your choice of the Redis Source Available License 2.0
 * (RSALv2) or the Server Side Public License v1 (SSPLv1).
 */

#include "script_lua.h"
#include "fpconv_dtoa.h"

#include "server.h"
#include "sha1.h"
#include "rand.h"
#include "cluster.h"
#include "monotonic.h"
#include "resp_parser.h"
#include "version.h"
#include <lauxlib.h>
#include <lualib.h>
#include <ctype.h>
#include <math.h>

/* Globals that are added by the Lua libraries */
static char *gkOF9g5Q[] = {
    "string",
    "cjson",
    "bit",
    "cmsgpack",
    "math",
    "table",
    "struct",
    "os",
    oiK17dDNxGhNq,
};

/* Redis Lua API globals */
static char *lCTj3[] = {
    "redis",
    "__redis__err__handler", /* error handler for eval, currently located on globals.
                                Should move to registry. */
    oiK17dDNxGhNq,
};

/* Lua builtins */
static char *T3yjg2kfYicr[] = {
    "xpcall",
    "tostring",
    "getfenv",
    "setmetatable",
    "next",
    "assert",
    "tonumber",
    "rawequal",
    "collectgarbage",
    "getmetatable",
    "rawset",
    "pcall",
    "coroutine",
    "type",
    "_G",
    "select",
    "unpack",
    "gcinfo",
    "pairs",
    "rawget",
    "loadstring",
    "ipairs",
    "_VERSION",
    "setfenv",
    "load",
    "error",
    oiK17dDNxGhNq,
};

/* Lua builtins which are not documented on the Lua documentation */
static char *ob7ADy56He5[] = {
    "newproxy",
    oiK17dDNxGhNq,
};

/* Lua builtins which are allowed on initialization but will be removed right after */
static char *UdrVZm6BAQ[] = {
    "debug", /* debug will be set to nil after the error handler will be created */
    oiK17dDNxGhNq,
};

/* Those allow lists was created from the globals that was
 * available to the user when the allow lists was first introduce.
 * Because we do not want to break backward compatibility we keep
 * all the globals. The allow lists will prevent us from accidentally
 * creating unwanted globals in the future.
 *
 * Also notice that the allow list is only checked on start time,
 * after that the global table is locked so not need to check anything.*/
static char **xq1OTe[] = {
    gkOF9g5Q,
    lCTj3,
    T3yjg2kfYicr,
    ob7ADy56He5,
    UdrVZm6BAQ,
    oiK17dDNxGhNq,
};

/* Deny list contains elements which we know we do not want to add to globals
 * and there is no need to print a warning message form them. We will print a
 * log message only if an element was added to the globals and the element is
 * not on the allow list nor on the back list. */
static char *r5z_vNq_N[] = {
    "dofile",
    "loadfile",
    "print",
    oiK17dDNxGhNq,
};

static int jvqCXd (X8PyH0GU8BCr *r7QkkXdXjgQj);
static int Kmjqqwu (X8PyH0GU8BCr *r7QkkXdXjgQj);
static void NBoijvzOZUvb8(void *R0qY, long long FVwcZoax10kF, const char *o7A9Do, KPh4MuxG ARlAf5_S);
static void GGLtLCv80eXr(void *R0qY, const char *E2kBIog, KPh4MuxG y6e1E_ze, const char *o7A9Do, KPh4MuxG ARlAf5_S);
static void J60Znz9p(void *R0qY, const char *o7A9Do, KPh4MuxG ARlAf5_S);
static void bYvf(void *R0qY, const char *o7A9Do, KPh4MuxG ARlAf5_S);
static void tOCX(void *R0qY, const char *E2kBIog, KPh4MuxG y6e1E_ze, const char *o7A9Do, KPh4MuxG ARlAf5_S);
static void a39FcaQ(void *R0qY, const char *E2kBIog, KPh4MuxG y6e1E_ze, const char *o7A9Do, KPh4MuxG ARlAf5_S);
static void gQKVhufU(struct BI5EeEnhN683 *rBSAs_zrt136, void *R0qY, KPh4MuxG y6e1E_ze, const char *o7A9Do);
static void I_u8pX(struct BI5EeEnhN683 *rBSAs_zrt136, void *R0qY, KPh4MuxG y6e1E_ze, const char *o7A9Do);
static void peswOboetA(struct BI5EeEnhN683 *rBSAs_zrt136, void *R0qY, KPh4MuxG y6e1E_ze, const char *o7A9Do);
static void e4Sq__7kIpP(void *R0qY, const char *o7A9Do, KPh4MuxG ARlAf5_S);
static void CKq8l5YfclBy(void *R0qY, int FVwcZoax10kF, const char *o7A9Do, KPh4MuxG ARlAf5_S);
static void SV7dxM(void *R0qY, double Cipntmpg, const char *o7A9Do, KPh4MuxG ARlAf5_S);
static void hOqQ(void *R0qY, const char *E2kBIog, KPh4MuxG y6e1E_ze, const char *o7A9Do, KPh4MuxG ARlAf5_S);
static void jV4cgD_WX(void *R0qY, const char *CW7soP1xT, const char *E2kBIog, KPh4MuxG y6e1E_ze, const char *o7A9Do, KPh4MuxG ARlAf5_S);
static void ZdBJTCusOU9l(struct BI5EeEnhN683 *rBSAs_zrt136, void *R0qY, KPh4MuxG y6e1E_ze, const char *o7A9Do);
static void dd3oj3(HUv4 *aLtJDMH0h, HUv4* I4BzCJij, X8PyH0GU8BCr *qv7u6nrNV71ym);

/*
 * Save the give pointer on Lua registry, used to save the Lua context and
 * function context so we can retrieve them from lua_State.
 */
void sIgCLT3(X8PyH0GU8BCr* qv7u6nrNV71ym, const char* RwudhoObh, void* HOx8cWCfI) {
    uSO0DL(qv7u6nrNV71ym, RwudhoObh);
    if (HOx8cWCfI) {
        eqtPhS(qv7u6nrNV71ym, HOx8cWCfI);
    } else {
        XwgiiV(qv7u6nrNV71ym);
    }
    G2h9B7KnKZ0m(qv7u6nrNV71ym, ngIcb895ZXWkx);
}

/*
 * Get a saved pointer from registry
 */
void* DllaG685eFJWb(X8PyH0GU8BCr* qv7u6nrNV71ym, const char* RwudhoObh) {
    uSO0DL(qv7u6nrNV71ym, RwudhoObh);
    o7kWoLFpe6(qv7u6nrNV71ym, ngIcb895ZXWkx);

    if (ce5nTyX(qv7u6nrNV71ym, -1)) {
        Z9NsBxGQ(qv7u6nrNV71ym, 1); /* pops the value */
        return oiK17dDNxGhNq;
    }
    /* must be light user data */
    T5gjLFJt2m(BkQ45w(qv7u6nrNV71ym, -1));

    void* HOx8cWCfI = (void*) B9ea(qv7u6nrNV71ym, -1);
    T5gjLFJt2m(HOx8cWCfI);

    /* pops the value */
    Z9NsBxGQ(qv7u6nrNV71ym, 1);

    return HOx8cWCfI;
}

/* ---------------------------------------------------------------------------
 * Redis reply to Lua type conversion functions.
 * ------------------------------------------------------------------------- */

/* Take a Redis reply in the Redis protocol format and convert it into a
 * Lua type. Thanks to this function, and the introduction of not connected
 * clients, it is trivial to implement the redis() lua function.
 *
 * Basically we take the arguments, execute the Redis command in the context
 * of a non connected client, then take the generated reply and convert it
 * into a suitable Lua type. With this trick the scripting feature does not
 * need the introduction of a full Redis internals API. The script
 * is like a normal client that bypasses all the slow I/O paths.
 *
 * Note: in this function we do not do any sanity check as the reply is
 * generated by Redis directly. This allows us to go faster.
 *
 * Errors are returned as a table with a single 'err' field set to the
 * error string.
 */

static const MxWqd5YThk4 HafAlsS0yW = {
    .GTxcq = bYvf,
    .acYkq1sJlg1v = GGLtLCv80eXr,
    .ktzHrzXy08UPN = J60Znz9p,
    .wPTOnZm = a39FcaQ,
    .alrRc5yXbBS = tOCX,
    .PqwsBeoiZrZU = NBoijvzOZUvb8,
    .DIT0NZI = gQKVhufU,
    .ODRwAR_S2 = peswOboetA,
    .dyH1 = I_u8pX,
    .PKCFxJGW = CKq8l5YfclBy,
    .bedci6 = SV7dxM,
    .Mo1Adu_0 = e4Sq__7kIpP,
    .rrgcakR = hOqQ,
    .bxXnOmhP = jV4cgD_WX,
    .B6wqK = ZdBJTCusOU9l,
    .LFy7OV = oiK17dDNxGhNq,
};

static void gRwOAQ(X8PyH0GU8BCr *qv7u6nrNV71ym, char* s8lxoaN7Ash) {
    BI5EeEnhN683 rBSAs_zrt136 = {.xJjMcDsRToP = s8lxoaN7Ash, .rzB_ZN = HafAlsS0yW};

    FMfRI(&rBSAs_zrt136, qv7u6nrNV71ym);
}

static void NBoijvzOZUvb8(void *R0qY, long long FVwcZoax10kF, const char *o7A9Do, KPh4MuxG ARlAf5_S) {
    j59GHM(o7A9Do);
    j59GHM(ARlAf5_S);
    if (!R0qY) {
        return;
    }

    X8PyH0GU8BCr *qv7u6nrNV71ym = R0qY;
    if (!Lmi5Dk(qv7u6nrNV71ym, 1)) {
        /* Increase the Lua stack if needed, to make sure there is enough room
         * to push elements to the stack. On failure, exit with panic. */
        NUge("lua stack limit reach when parsing redis.call reply");
    }
    EZ99aq2v(qv7u6nrNV71ym,(Fhnvfr)FVwcZoax10kF);
}

static void J60Znz9p(void *R0qY, const char *o7A9Do, KPh4MuxG ARlAf5_S) {
    j59GHM(o7A9Do);
    j59GHM(ARlAf5_S);
    if (!R0qY) {
        return;
    }

    X8PyH0GU8BCr *qv7u6nrNV71ym = R0qY;
    if (!Lmi5Dk(qv7u6nrNV71ym, 1)) {
        /* Increase the Lua stack if needed, to make sure there is enough room
         * to push elements to the stack. On failure, exit with panic. */
        NUge("lua stack limit reach when parsing redis.call reply");
    }
    u18Dc4a(qv7u6nrNV71ym,0);
}

static void bYvf(void *R0qY, const char *o7A9Do, KPh4MuxG ARlAf5_S) {
    j59GHM(o7A9Do);
    j59GHM(ARlAf5_S);
    if (!R0qY) {
        return;
    }
    X8PyH0GU8BCr *qv7u6nrNV71ym = R0qY;
    if (!Lmi5Dk(qv7u6nrNV71ym, 1)) {
        /* Increase the Lua stack if needed, to make sure there is enough room
         * to push elements to the stack. On failure, exit with panic. */
        NUge("lua stack limit reach when parsing redis.call reply");
    }
    u18Dc4a(qv7u6nrNV71ym,0);
}


static void GGLtLCv80eXr(void *R0qY, const char *E2kBIog, KPh4MuxG y6e1E_ze, const char *o7A9Do, KPh4MuxG ARlAf5_S) {
    j59GHM(o7A9Do);
    j59GHM(ARlAf5_S);
    if (!R0qY) {
        return;
    }

    X8PyH0GU8BCr *qv7u6nrNV71ym = R0qY;
    if (!Lmi5Dk(qv7u6nrNV71ym, 1)) {
        /* Increase the Lua stack if needed, to make sure there is enough room
         * to push elements to the stack. On failure, exit with panic. */
        NUge("lua stack limit reach when parsing redis.call reply");
    }
    DIVeD(qv7u6nrNV71ym,E2kBIog,y6e1E_ze);
}

static void tOCX(void *R0qY, const char *E2kBIog, KPh4MuxG y6e1E_ze, const char *o7A9Do, KPh4MuxG ARlAf5_S) {
    j59GHM(o7A9Do);
    j59GHM(ARlAf5_S);
    if (!R0qY) {
        return;
    }

    X8PyH0GU8BCr *qv7u6nrNV71ym = R0qY;
    if (!Lmi5Dk(qv7u6nrNV71ym, 3)) {
        /* Increase the Lua stack if needed, to make sure there is enough room
         * to push elements to the stack. On failure, exit with panic. */
        NUge("lua stack limit reach when parsing redis.call reply");
    }
    Xxx3D8_4(qv7u6nrNV71ym);
    uSO0DL(qv7u6nrNV71ym,"ok");
    DIVeD(qv7u6nrNV71ym,E2kBIog,y6e1E_ze);
    G2h9B7KnKZ0m(qv7u6nrNV71ym,-3);
}

static void a39FcaQ(void *R0qY, const char *E2kBIog, KPh4MuxG y6e1E_ze, const char *o7A9Do, KPh4MuxG ARlAf5_S) {
    j59GHM(o7A9Do);
    j59GHM(ARlAf5_S);
    if (!R0qY) {
        return;
    }

    X8PyH0GU8BCr *qv7u6nrNV71ym = R0qY;
    if (!Lmi5Dk(qv7u6nrNV71ym, 3)) {
        /* Increase the Lua stack if needed, to make sure there is enough room
         * to push elements to the stack. On failure, exit with panic. */
        NUge("lua stack limit reach when parsing redis.call reply");
    }
    MtwwP Fz7H9MRO = zjmNjr(OzOKacu4u("-"), E2kBIog, y6e1E_ze);
    T6lHa5(qv7u6nrNV71ym,Fz7H9MRO);
    /* push a field indicate to ignore updating the stats on this error
     * because it was already updated when executing the command. */
    uSO0DL(qv7u6nrNV71ym,"ignore_error_stats_update");
    u18Dc4a(qv7u6nrNV71ym, 1);
    G2h9B7KnKZ0m(qv7u6nrNV71ym,-3);
}

static void I_u8pX(struct BI5EeEnhN683 *rBSAs_zrt136, void *R0qY, KPh4MuxG y6e1E_ze, const char *o7A9Do) {
    j59GHM(o7A9Do);
    X8PyH0GU8BCr *qv7u6nrNV71ym = R0qY;
    if (qv7u6nrNV71ym) {
        if (!Lmi5Dk(qv7u6nrNV71ym, 3)) {
            /* Increase the Lua stack if needed, to make sure there is enough room
             * to push elements to the stack. On failure, exit with panic. */
            NUge("lua stack limit reach when parsing redis.call reply");
        }
        Xxx3D8_4(qv7u6nrNV71ym);
        uSO0DL(qv7u6nrNV71ym, "map");
        Xxx3D8_4(qv7u6nrNV71ym);
    }
    for (KPh4MuxG hRAkplUj = 0; hRAkplUj < y6e1E_ze; hRAkplUj++) {
        FMfRI(rBSAs_zrt136,qv7u6nrNV71ym);
        FMfRI(rBSAs_zrt136,qv7u6nrNV71ym);
        if (qv7u6nrNV71ym) G2h9B7KnKZ0m(qv7u6nrNV71ym,-3);
    }
    if (qv7u6nrNV71ym) G2h9B7KnKZ0m(qv7u6nrNV71ym,-3);
}

static void peswOboetA(struct BI5EeEnhN683 *rBSAs_zrt136, void *R0qY, KPh4MuxG y6e1E_ze, const char *o7A9Do) {
    j59GHM(o7A9Do);

    X8PyH0GU8BCr *qv7u6nrNV71ym = R0qY;
    if (qv7u6nrNV71ym) {
        if (!Lmi5Dk(qv7u6nrNV71ym, 3)) {
            /* Increase the Lua stack if needed, to make sure there is enough room
             * to push elements to the stack. On failure, exit with panic. */
            NUge("lua stack limit reach when parsing redis.call reply");
        }
        Xxx3D8_4(qv7u6nrNV71ym);
        uSO0DL(qv7u6nrNV71ym, "set");
        Xxx3D8_4(qv7u6nrNV71ym);
    }
    for (KPh4MuxG hRAkplUj = 0; hRAkplUj < y6e1E_ze; hRAkplUj++) {
        FMfRI(rBSAs_zrt136,qv7u6nrNV71ym);
        if (qv7u6nrNV71ym) {
            if (!Lmi5Dk(qv7u6nrNV71ym, 1)) {
                /* Increase the Lua stack if needed, to make sure there is enough room
                 * to push elements to the stack. On failure, exit with panic.
                 * Notice that here we need to check the stack again because the recursive
                 * call to redisProtocolToLuaType might have use the room allocated in the stack*/
                NUge("lua stack limit reach when parsing redis.call reply");
            }
            u18Dc4a(qv7u6nrNV71ym,1);
            G2h9B7KnKZ0m(qv7u6nrNV71ym,-3);
        }
    }
    if (qv7u6nrNV71ym) G2h9B7KnKZ0m(qv7u6nrNV71ym,-3);
}

static void gQKVhufU(struct BI5EeEnhN683 *rBSAs_zrt136, void *R0qY, KPh4MuxG y6e1E_ze, const char *o7A9Do) {
    j59GHM(o7A9Do);

    X8PyH0GU8BCr *qv7u6nrNV71ym = R0qY;
    if (qv7u6nrNV71ym){
        if (!Lmi5Dk(qv7u6nrNV71ym, 2)) {
            /* Increase the Lua stack if needed, to make sure there is enough room
             * to push elements to the stack. On failure, exit with panic. */
            NUge("lua stack limit reach when parsing redis.call reply");
        }
        Xxx3D8_4(qv7u6nrNV71ym);
    }
    for (KPh4MuxG hRAkplUj = 0; hRAkplUj < y6e1E_ze; hRAkplUj++) {
        if (qv7u6nrNV71ym) EZ99aq2v(qv7u6nrNV71ym,hRAkplUj+1);
        FMfRI(rBSAs_zrt136,qv7u6nrNV71ym);
        if (qv7u6nrNV71ym) G2h9B7KnKZ0m(qv7u6nrNV71ym,-3);
    }
}

static void ZdBJTCusOU9l(struct BI5EeEnhN683 *rBSAs_zrt136, void *R0qY, KPh4MuxG y6e1E_ze, const char *o7A9Do) {
    j59GHM(o7A9Do);

    /* Parse the attribute reply.
     * Currently, we do not expose the attribute to the Lua script so
     * we just need to continue parsing and ignore it (the NULL ensures that the
     * reply will be ignored). */
    for (KPh4MuxG hRAkplUj = 0; hRAkplUj < y6e1E_ze; hRAkplUj++) {
        FMfRI(rBSAs_zrt136,oiK17dDNxGhNq);
        FMfRI(rBSAs_zrt136,oiK17dDNxGhNq);
    }

    /* Parse the reply itself. */
    FMfRI(rBSAs_zrt136,R0qY);
}

static void jV4cgD_WX(void *R0qY, const char *CW7soP1xT, const char *E2kBIog, KPh4MuxG y6e1E_ze, const char *o7A9Do, KPh4MuxG ARlAf5_S) {
    j59GHM(o7A9Do);
    j59GHM(ARlAf5_S);
    if (!R0qY) {
        return;
    }

    X8PyH0GU8BCr *qv7u6nrNV71ym = R0qY;
    if (!Lmi5Dk(qv7u6nrNV71ym, 5)) {
        /* Increase the Lua stack if needed, to make sure there is enough room
         * to push elements to the stack. On failure, exit with panic. */
        NUge("lua stack limit reach when parsing redis.call reply");
    }
    Xxx3D8_4(qv7u6nrNV71ym);
    uSO0DL(qv7u6nrNV71ym,"verbatim_string");
    Xxx3D8_4(qv7u6nrNV71ym);
    uSO0DL(qv7u6nrNV71ym,"string");
    DIVeD(qv7u6nrNV71ym,E2kBIog,y6e1E_ze);
    G2h9B7KnKZ0m(qv7u6nrNV71ym,-3);
    uSO0DL(qv7u6nrNV71ym,"format");
    DIVeD(qv7u6nrNV71ym,CW7soP1xT,3);
    G2h9B7KnKZ0m(qv7u6nrNV71ym,-3);
    G2h9B7KnKZ0m(qv7u6nrNV71ym,-3);
}

static void hOqQ(void *R0qY, const char *E2kBIog, KPh4MuxG y6e1E_ze, const char *o7A9Do, KPh4MuxG ARlAf5_S) {
    j59GHM(o7A9Do);
    j59GHM(ARlAf5_S);
    if (!R0qY) {
        return;
    }

    X8PyH0GU8BCr *qv7u6nrNV71ym = R0qY;
    if (!Lmi5Dk(qv7u6nrNV71ym, 3)) {
        /* Increase the Lua stack if needed, to make sure there is enough room
         * to push elements to the stack. On failure, exit with panic. */
        NUge("lua stack limit reach when parsing redis.call reply");
    }
    Xxx3D8_4(qv7u6nrNV71ym);
    uSO0DL(qv7u6nrNV71ym,"big_number");
    DIVeD(qv7u6nrNV71ym,E2kBIog,y6e1E_ze);
    G2h9B7KnKZ0m(qv7u6nrNV71ym,-3);
}

static void e4Sq__7kIpP(void *R0qY, const char *o7A9Do, KPh4MuxG ARlAf5_S) {
    j59GHM(o7A9Do);
    j59GHM(ARlAf5_S);
    if (!R0qY) {
        return;
    }

    X8PyH0GU8BCr *qv7u6nrNV71ym = R0qY;
    if (!Lmi5Dk(qv7u6nrNV71ym, 1)) {
        /* Increase the Lua stack if needed, to make sure there is enough room
         * to push elements to the stack. On failure, exit with panic. */
        NUge("lua stack limit reach when parsing redis.call reply");
    }
    XwgiiV(qv7u6nrNV71ym);
}

static void CKq8l5YfclBy(void *R0qY, int FVwcZoax10kF, const char *o7A9Do, KPh4MuxG ARlAf5_S) {
    j59GHM(o7A9Do);
    j59GHM(ARlAf5_S);
    if (!R0qY) {
        return;
    }

    X8PyH0GU8BCr *qv7u6nrNV71ym = R0qY;
    if (!Lmi5Dk(qv7u6nrNV71ym, 1)) {
        /* Increase the Lua stack if needed, to make sure there is enough room
         * to push elements to the stack. On failure, exit with panic. */
        NUge("lua stack limit reach when parsing redis.call reply");
    }
    u18Dc4a(qv7u6nrNV71ym,FVwcZoax10kF);
}

static void SV7dxM(void *R0qY, double Cipntmpg, const char *o7A9Do, KPh4MuxG ARlAf5_S) {
    j59GHM(o7A9Do);
    j59GHM(ARlAf5_S);
    if (!R0qY) {
        return;
    }

    X8PyH0GU8BCr *qv7u6nrNV71ym = R0qY;
    if (!Lmi5Dk(qv7u6nrNV71ym, 3)) {
        /* Increase the Lua stack if needed, to make sure there is enough room
         * to push elements to the stack. On failure, exit with panic. */
        NUge("lua stack limit reach when parsing redis.call reply");
    }
    Xxx3D8_4(qv7u6nrNV71ym);
    uSO0DL(qv7u6nrNV71ym,"double");
    EZ99aq2v(qv7u6nrNV71ym,Cipntmpg);
    G2h9B7KnKZ0m(qv7u6nrNV71ym,-3);
}

/* This function is used in order to push an error on the Lua stack in the
 * format used by redis.pcall to return errors, which is a lua table
 * with an "err" field set to the error string including the error code.
 * Note that this table is never a valid reply by proper commands,
 * since the returned tables are otherwise always indexed by integers, never by strings.
 *
 * The function takes ownership on the given err_buffer. */
void T6lHa5(X8PyH0GU8BCr *qv7u6nrNV71ym, MtwwP pR6aBvh) {
    MtwwP PdURK0;
    MtwwP haJt2O1l80k40;

    /* If debugging is active and in step mode, log errors resulting from
     * Redis commands. */
    if (wCM48hrB0xAe()) {
        gPceqzF7N(FFtJEc2(B4YbM7cF_(),"<error> %s",pR6aBvh));
    }

    /* There are two possible formats for the received `error` string:
     * 1) "-CODE msg": in this case we remove the leading '-' since we don't store it as part of the lua error format.
     * 2) "msg": in this case we prepend a generic 'ERR' code since all error statuses need some error code.
     * We support format (1) so this function can reuse the error messages used in other places in redis.
     * We support format (2) so it'll be easy to pass descriptive errors to this function without worrying about format.
     */
    if (pR6aBvh[0] == '-') {
        /* derive error code from the message */
        char *Fz7H9MRO = tu2x(pR6aBvh, " ");
        if (!Fz7H9MRO) {
            PdURK0 = OzOKacu4u(pR6aBvh+1);
            haJt2O1l80k40 = OzOKacu4u("ERR");
        } else {
            *Fz7H9MRO = '\0';
            PdURK0 = OzOKacu4u(Fz7H9MRO+1);
            haJt2O1l80k40 = OzOKacu4u(pR6aBvh + 1);
        }
        jF5Zqj(pR6aBvh);
    } else {
        PdURK0 = pR6aBvh;
        haJt2O1l80k40 = OzOKacu4u("ERR");
    }
    /* Trim newline at end of string. If we reuse the ready-made Redis error objects (case 1 above) then we might
     * have a newline that needs to be trimmed. In any case the lua Redis error table shouldn't end with a newline. */
    PdURK0 = ECY9U6vkImBf(PdURK0, "\r\n");
    MtwwP AGCa = XE_o9pi9PILhw(haJt2O1l80k40, " %s", PdURK0);

    Xxx3D8_4(qv7u6nrNV71ym);
    uSO0DL(qv7u6nrNV71ym,"err");
    uSO0DL(qv7u6nrNV71ym, AGCa);
    G2h9B7KnKZ0m(qv7u6nrNV71ym,-3);

    jF5Zqj(PdURK0);
    jF5Zqj(AGCa);
}

void R8Id(X8PyH0GU8BCr *qv7u6nrNV71ym, const char *LFy7OV) {
    T6lHa5(qv7u6nrNV71ym, OzOKacu4u(LFy7OV));
}

/* In case the error set into the Lua stack by luaPushError() was generated
 * by the non-error-trapping version of redis.pcall(), which is redis.call(),
 * this function will raise the Lua error so that the execution of the
 * script will be halted. */
int BJXzQsJU01bam(X8PyH0GU8BCr *qv7u6nrNV71ym) {
    return IN4hcI02TEv(qv7u6nrNV71ym);
}


/* ---------------------------------------------------------------------------
 * Lua reply to Redis reply conversion functions.
 * ------------------------------------------------------------------------- */

/* Reply to client 'c' converting the top element in the Lua stack to a
 * Redis reply. As a side effect the element is consumed from the stack.  */
static void dd3oj3(HUv4 *aLtJDMH0h, HUv4* I4BzCJij, X8PyH0GU8BCr *qv7u6nrNV71ym) {
    int VpSRYjeUZYRYJ = vGDDS3FXf(qv7u6nrNV71ym,-1);

    if (!Lmi5Dk(qv7u6nrNV71ym, 4)) {
        /* Increase the Lua stack if needed to make sure there is enough room
         * to push 4 elements to the stack. On failure, return error.
         * Notice that we need, in the worst case, 4 elements because returning a map might
         * require push 4 elements to the Lua stack.*/
        woec(aLtJDMH0h, "reached lua stack limit");
        Z9NsBxGQ(qv7u6nrNV71ym,1); /* pop the element from the stack */
        return;
    }

    switch(VpSRYjeUZYRYJ) {
    case O1T52vaM4ex_:
        BRHj5EQDam(aLtJDMH0h,(char*)P8_HqVd8T1Vdu(qv7u6nrNV71ym,-1),d6geEY6D0r(qv7u6nrNV71ym,-1));
        break;
    case ZAorm:
        if (I4BzCJij->mGSxNFlPjv == 2)
            lZv_D7tHYo1(aLtJDMH0h,Fa5pu(qv7u6nrNV71ym,-1) ? L3wYjWfvFL8n.Ofhfcb1BWt :
                                               L3wYjWfvFL8n.riy_w5O[aLtJDMH0h->mGSxNFlPjv]);
        else
            hxaQ479fJFTsn(aLtJDMH0h,Fa5pu(qv7u6nrNV71ym,-1));
        break;
    case OeqBFsHSb:
        caS5piQJsy0SU(aLtJDMH0h,(long long)oRTwBrLS(qv7u6nrNV71ym,-1));
        break;
    case gt22JJt8hGCYY:
        /* We need to check if it is an array, an error, or a status reply.
         * Error are returned as a single element table with 'err' field.
         * Status replies are returned as single element table with 'ok'
         * field. */

        /* Handle error reply. */
        /* we took care of the stack size on function start */
        uSO0DL(qv7u6nrNV71ym,"err");
        aZoiUhGYmDl(qv7u6nrNV71ym,-2);
        VpSRYjeUZYRYJ = vGDDS3FXf(qv7u6nrNV71ym,-1);
        if (VpSRYjeUZYRYJ == O1T52vaM4ex_) {
            Z9NsBxGQ(qv7u6nrNV71ym, 1); /* pop the error message, we will use luaExtractErrorInformation to get error information */
            mpkWZCg eCDLm8ECO5 = {0};
            NDN7XI(qv7u6nrNV71ym, &eCDLm8ECO5);
            qVaBj5Pu7(aLtJDMH0h,
                                  eCDLm8ECO5.PqHZA4CO? aP3Mo8: 0,
                                  "-%s",
                                  eCDLm8ECO5.PdURK0);
            nO44K16dpOQFJ(&eCDLm8ECO5);
            Z9NsBxGQ(qv7u6nrNV71ym,1); /* pop the result table */
            return;
        }
        Z9NsBxGQ(qv7u6nrNV71ym,1); /* Discard field name pushed before. */

        /* Handle status reply. */
        uSO0DL(qv7u6nrNV71ym,"ok");
        aZoiUhGYmDl(qv7u6nrNV71ym,-2);
        VpSRYjeUZYRYJ = vGDDS3FXf(qv7u6nrNV71ym,-1);
        if (VpSRYjeUZYRYJ == O1T52vaM4ex_) {
            MtwwP tIbQ7yD = OzOKacu4u(P8_HqVd8T1Vdu(qv7u6nrNV71ym,-1));
            lVTG28PlbRqnq(tIbQ7yD,"\r\n","  ",2);
            p_VVeyc8IF(aLtJDMH0h, tIbQ7yD, GsIvP8MuRN(tIbQ7yD));
            jF5Zqj(tIbQ7yD);
            Z9NsBxGQ(qv7u6nrNV71ym,2);
            return;
        }
        Z9NsBxGQ(qv7u6nrNV71ym,1); /* Discard field name pushed before. */

        /* Handle double reply. */
        uSO0DL(qv7u6nrNV71ym,"double");
        aZoiUhGYmDl(qv7u6nrNV71ym,-2);
        VpSRYjeUZYRYJ = vGDDS3FXf(qv7u6nrNV71ym,-1);
        if (VpSRYjeUZYRYJ == OeqBFsHSb) {
            V8_mX5ka(aLtJDMH0h,oRTwBrLS(qv7u6nrNV71ym,-1));
            Z9NsBxGQ(qv7u6nrNV71ym,2);
            return;
        }
        Z9NsBxGQ(qv7u6nrNV71ym,1); /* Discard field name pushed before. */

        /* Handle big number reply. */
        uSO0DL(qv7u6nrNV71ym,"big_number");
        aZoiUhGYmDl(qv7u6nrNV71ym,-2);
        VpSRYjeUZYRYJ = vGDDS3FXf(qv7u6nrNV71ym,-1);
        if (VpSRYjeUZYRYJ == O1T52vaM4ex_) {
            MtwwP zVgan8Vut = U_ImGiBg(P8_HqVd8T1Vdu(qv7u6nrNV71ym,-1), d6geEY6D0r(qv7u6nrNV71ym,-1));
            lVTG28PlbRqnq(zVgan8Vut,"\r\n","  ",2);
            GS7SANN0hxS(aLtJDMH0h,zVgan8Vut,GsIvP8MuRN(zVgan8Vut));
            jF5Zqj(zVgan8Vut);
            Z9NsBxGQ(qv7u6nrNV71ym,2);
            return;
        }
        Z9NsBxGQ(qv7u6nrNV71ym,1); /* Discard field name pushed before. */

        /* Handle verbatim reply. */
        uSO0DL(qv7u6nrNV71ym,"verbatim_string");
        aZoiUhGYmDl(qv7u6nrNV71ym,-2);
        VpSRYjeUZYRYJ = vGDDS3FXf(qv7u6nrNV71ym,-1);
        if (VpSRYjeUZYRYJ == gt22JJt8hGCYY) {
            uSO0DL(qv7u6nrNV71ym,"format");
            aZoiUhGYmDl(qv7u6nrNV71ym,-2);
            VpSRYjeUZYRYJ = vGDDS3FXf(qv7u6nrNV71ym,-1);
            if (VpSRYjeUZYRYJ == O1T52vaM4ex_){
                char* CW7soP1xT = (char*)P8_HqVd8T1Vdu(qv7u6nrNV71ym,-1);
                uSO0DL(qv7u6nrNV71ym,"string");
                aZoiUhGYmDl(qv7u6nrNV71ym,-3);
                VpSRYjeUZYRYJ = vGDDS3FXf(qv7u6nrNV71ym,-1);
                if (VpSRYjeUZYRYJ == O1T52vaM4ex_){
                    KPh4MuxG y6e1E_ze;
                    char* E2kBIog = (char*)qoyfr9(qv7u6nrNV71ym,-1,&y6e1E_ze);
                    NXvEo_lBUjMDY(aLtJDMH0h, E2kBIog, y6e1E_ze, CW7soP1xT);
                    Z9NsBxGQ(qv7u6nrNV71ym,4);
                    return;
                }
                Z9NsBxGQ(qv7u6nrNV71ym,1);
            }
            Z9NsBxGQ(qv7u6nrNV71ym,1);
        }
        Z9NsBxGQ(qv7u6nrNV71ym,1); /* Discard field name pushed before. */

        /* Handle map reply. */
        uSO0DL(qv7u6nrNV71ym,"map");
        aZoiUhGYmDl(qv7u6nrNV71ym,-2);
        VpSRYjeUZYRYJ = vGDDS3FXf(qv7u6nrNV71ym,-1);
        if (VpSRYjeUZYRYJ == gt22JJt8hGCYY) {
            int CoyYML0H = 0;
            void *ftO2dSu4nSgSB = Zdgv(aLtJDMH0h);
            /* we took care of the stack size on function start */
            XwgiiV(qv7u6nrNV71ym); /* Use nil to start iteration. */
            while (D2PL(qv7u6nrNV71ym,-2)) {
                /* Stack now: table, key, value */
                zq2ry1ZI(qv7u6nrNV71ym,-2);        /* Dup key before consuming. */
                dd3oj3(aLtJDMH0h, I4BzCJij, qv7u6nrNV71ym); /* Return key. */
                dd3oj3(aLtJDMH0h, I4BzCJij, qv7u6nrNV71ym); /* Return value. */
                /* Stack now: table, key. */
                CoyYML0H++;
            }
            dqj2sx(aLtJDMH0h,ftO2dSu4nSgSB,CoyYML0H);
            Z9NsBxGQ(qv7u6nrNV71ym,2);
            return;
        }
        Z9NsBxGQ(qv7u6nrNV71ym,1); /* Discard field name pushed before. */

        /* Handle set reply. */
        uSO0DL(qv7u6nrNV71ym,"set");
        aZoiUhGYmDl(qv7u6nrNV71ym,-2);
        VpSRYjeUZYRYJ = vGDDS3FXf(qv7u6nrNV71ym,-1);
        if (VpSRYjeUZYRYJ == gt22JJt8hGCYY) {
            int WV4An = 0;
            void *ftO2dSu4nSgSB = Zdgv(aLtJDMH0h);
            /* we took care of the stack size on function start */
            XwgiiV(qv7u6nrNV71ym); /* Use nil to start iteration. */
            while (D2PL(qv7u6nrNV71ym,-2)) {
                /* Stack now: table, key, true */
                Z9NsBxGQ(qv7u6nrNV71ym,1);               /* Discard the boolean value. */
                zq2ry1ZI(qv7u6nrNV71ym,-1);        /* Dup key before consuming. */
                dd3oj3(aLtJDMH0h, I4BzCJij, qv7u6nrNV71ym); /* Return key. */
                /* Stack now: table, key. */
                WV4An++;
            }
            fnHg(aLtJDMH0h,ftO2dSu4nSgSB,WV4An);
            Z9NsBxGQ(qv7u6nrNV71ym,2);
            return;
        }
        Z9NsBxGQ(qv7u6nrNV71ym,1); /* Discard field name pushed before. */

        /* Handle the array reply. */
        void *ftO2dSu4nSgSB = Zdgv(aLtJDMH0h);
        int hRAkplUj = 1, jLJuN4jAwO6 = 0;
        while(1) {
            /* we took care of the stack size on function start */
            EZ99aq2v(qv7u6nrNV71ym,hRAkplUj++);
            aZoiUhGYmDl(qv7u6nrNV71ym,-2);
            VpSRYjeUZYRYJ = vGDDS3FXf(qv7u6nrNV71ym,-1);
            if (VpSRYjeUZYRYJ == NSyPHeLBK_) {
                Z9NsBxGQ(qv7u6nrNV71ym,1);
                break;
            }
            dd3oj3(aLtJDMH0h, I4BzCJij, qv7u6nrNV71ym);
            jLJuN4jAwO6++;
        }
        fWW_hvh(aLtJDMH0h,ftO2dSu4nSgSB,jLJuN4jAwO6);
        break;
    default:
        k9vPYH7EX(aLtJDMH0h);
    }
    Z9NsBxGQ(qv7u6nrNV71ym,1);
}

/* ---------------------------------------------------------------------------
 * Lua redis.* functions implementations.
 * ------------------------------------------------------------------------- */
void UM2KSRdbB(bZNGQDGv **LTJ7, int plr_4QS, int Hv5NCEh);

/* Cached argv array across calls. */
static bZNGQDGv **lh7k7Oh9na = oiK17dDNxGhNq;
static int L8qU1THeDtx = 0;

/* Cache of recently used small arguments to avoid malloc calls. */
static bZNGQDGv *Uc84PhaopYxY[jmwZOeJUZb];
static KPh4MuxG KnBQxnDVldjXM[jmwZOeJUZb];

static bZNGQDGv **UrG8t(X8PyH0GU8BCr *qv7u6nrNV71ym, int *plr_4QS, int *Hv5NCEh) {
    int hRAkplUj;
    /* Require at least one argument */
    *plr_4QS = mLaJgHy(qv7u6nrNV71ym);
    if (*plr_4QS == 0) {
        R8Id(qv7u6nrNV71ym, "Please specify at least one argument for this redis lib call");
        return oiK17dDNxGhNq;
    }

    /* Build the arguments vector (reuse a cached argv from last call) */
    if (L8qU1THeDtx < *plr_4QS) {
        lh7k7Oh9na = UG_DFIpNui(lh7k7Oh9na,sizeof(bZNGQDGv*)* *plr_4QS);
        L8qU1THeDtx = *plr_4QS;
    }
    *Hv5NCEh = L8qU1THeDtx;

    for (hRAkplUj = 0; hRAkplUj < *plr_4QS; hRAkplUj++) {
        char *zGm2O_ED;
        KPh4MuxG gpNrt;
        char kjFLNM6B[64];

        if (vGDDS3FXf(qv7u6nrNV71ym,hRAkplUj+1) == OeqBFsHSb) {
            /* We can't use lua_tolstring() for number -> string conversion
             * since Lua uses a format specifier that loses precision. */
            Fhnvfr S2wJ6o = oRTwBrLS(qv7u6nrNV71ym,hRAkplUj+1);
            /* Integer printing function is much faster, check if we can safely use it.
             * Since lua_Number is not explicitly an integer or a double, we need to make an effort
             * to convert it as an integer when that's possible, since the string could later be used
             * in a context that doesn't support scientific notation (e.g. 1e9 instead of 100000000). */
            long long ZwUaJbv;
            if (Azi0yXk((double)S2wJ6o, &ZwUaJbv))
                gpNrt = lCuREvt7zUp(kjFLNM6B, sizeof(kjFLNM6B), ZwUaJbv);
            else {
                gpNrt = dhey((double)S2wJ6o, kjFLNM6B);
                kjFLNM6B[gpNrt] = '\0';
            }
            zGm2O_ED = kjFLNM6B;
        } else {
            zGm2O_ED = (char*)qoyfr9(qv7u6nrNV71ym,hRAkplUj+1,&gpNrt);
            if (zGm2O_ED == oiK17dDNxGhNq) break; /* Not a string. */
        }
        /* Try to use a cached object. */
        if (hRAkplUj < jmwZOeJUZb && Uc84PhaopYxY[hRAkplUj] &&
            KnBQxnDVldjXM[hRAkplUj] >= gpNrt)
        {
            MtwwP yEuu = Uc84PhaopYxY[hRAkplUj]->HOx8cWCfI;
            lh7k7Oh9na[hRAkplUj] = Uc84PhaopYxY[hRAkplUj];
            Uc84PhaopYxY[hRAkplUj] = oiK17dDNxGhNq;
            oAjEV(yEuu,zGm2O_ED,gpNrt+1);
            GVWZUf(yEuu, gpNrt);
        } else {
            lh7k7Oh9na[hRAkplUj] = asgtKJ(zGm2O_ED, gpNrt);
        }
    }

    /* Pop all arguments from the stack, we do not need them anymore
     * and this way we guaranty we will have room on the stack for the result. */
    Z9NsBxGQ(qv7u6nrNV71ym, *plr_4QS);

    /* Check if one of the arguments passed by the Lua script
     * is not a string or an integer (lua_isstring() return true for
     * integers as well). */
    if (hRAkplUj != *plr_4QS) {
        UM2KSRdbB(lh7k7Oh9na, hRAkplUj, L8qU1THeDtx);
        R8Id(qv7u6nrNV71ym, "Lua redis lib command arguments must be strings or integers");
        return oiK17dDNxGhNq;
    }

    return lh7k7Oh9na;
}

void UM2KSRdbB(bZNGQDGv **LTJ7, int plr_4QS, int Hv5NCEh) {
    int hRAkplUj;
    for (hRAkplUj = 0; hRAkplUj < plr_4QS; hRAkplUj++) {
        bZNGQDGv *W_NcTV = LTJ7[hRAkplUj];

        /* Try to cache the object in the lua_args_cached_objects array.
         * The object must be small, SDS-encoded, and with refcount = 1
         * (we must be the only owner) for us to cache it. */
        if (hRAkplUj < jmwZOeJUZb &&
            W_NcTV->wW0CckBfzU == 1 &&
            (W_NcTV->yk1O8 == jCwM0zM ||
             W_NcTV->yk1O8 == UDoAu) &&
            GsIvP8MuRN(W_NcTV->HOx8cWCfI) <= JCPl8fHEEWLw)
        {
            MtwwP yEuu = W_NcTV->HOx8cWCfI;
            if (Uc84PhaopYxY[hRAkplUj]) DFseCx(Uc84PhaopYxY[hRAkplUj]);
            Uc84PhaopYxY[hRAkplUj] = W_NcTV;
            KnBQxnDVldjXM[hRAkplUj] = WqmAf66U15U(yEuu);
        } else {
            DFseCx(W_NcTV);
        }
    }
    if (LTJ7 != lh7k7Oh9na || Hv5NCEh != L8qU1THeDtx) {
        /* The command changed argv, scrap the cache and start over. */
        G2kLFaj(LTJ7);
        lh7k7Oh9na = oiK17dDNxGhNq;
        L8qU1THeDtx = 0;
    }
}

static int MaNn(X8PyH0GU8BCr *qv7u6nrNV71ym, int Qvd5jJW7J) {
    int hRAkplUj;
    tpIit3Efe7* om4ctdIT = DllaG685eFJWb(qv7u6nrNV71ym, c_StnQzmHk1x);
    T5gjLFJt2m(om4ctdIT); /* Only supported inside script invocation */
    MtwwP SCp1 = oiK17dDNxGhNq;
    HUv4* aLtJDMH0h = om4ctdIT->aLtJDMH0h;
    MtwwP s8lxoaN7Ash;

    aLtJDMH0h->LTJ7 = UrG8t(qv7u6nrNV71ym, &aLtJDMH0h->plr_4QS, &aLtJDMH0h->Hv5NCEh);
    if (aLtJDMH0h->LTJ7 == oiK17dDNxGhNq) {
        return Qvd5jJW7J ? BJXzQsJU01bam(qv7u6nrNV71ym) : 1;
    }

    static int Y7dl = 0;   /* Recursive calls detection. */

    /* By using Lua debug hooks it is possible to trigger a recursive call
     * to luaRedisGenericCommand(), which normally should never happen.
     * To make this function reentrant is futile and makes it slower, but
     * we should at least detect such a misuse, and abort. */
    if (Y7dl) {
        char *g2h5guwsTJNHK =
                "luaRedisGenericCommand() recursive call detected. "
                "Are you doing funny stuff with Lua debug hooks?";
        AL2BiJBGOT(gKfWDSa9a,"%s",g2h5guwsTJNHK);
        R8Id(qv7u6nrNV71ym,g2h5guwsTJNHK);
        return 1;
    }
    Y7dl++;

    /* Log the command if debugging is active. */
    if (wCM48hrB0xAe()) {
        MtwwP sO2bgAeEzH5 = OzOKacu4u("<redis>");
        for (hRAkplUj = 0; hRAkplUj < aLtJDMH0h->plr_4QS; hRAkplUj++) {
            if (hRAkplUj == 10) {
                sO2bgAeEzH5 = FFtJEc2(sO2bgAeEzH5," ... (%d more)",
                    aLtJDMH0h->plr_4QS-hRAkplUj-1);
                break;
            } else {
                sO2bgAeEzH5 = zjmNjr(sO2bgAeEzH5," ",1);
                sO2bgAeEzH5 = o55nrE04baxDK(sO2bgAeEzH5,aLtJDMH0h->LTJ7[hRAkplUj]->HOx8cWCfI);
            }
        }
        gPceqzF7N(sO2bgAeEzH5);
    }

    SaS9o(om4ctdIT, &SCp1);
    if (SCp1) {
        R8Id(qv7u6nrNV71ym, SCp1);
        jF5Zqj(SCp1);
        /* push a field indicate to ignore updating the stats on this error
         * because it was already updated when executing the command. */
        uSO0DL(qv7u6nrNV71ym,"ignore_error_stats_update");
        u18Dc4a(qv7u6nrNV71ym, 1);
        G2h9B7KnKZ0m(qv7u6nrNV71ym,-3);
        goto SjHeQ;
    }

    /* Convert the result of the Redis command into a suitable Lua type.
     * The first thing we need is to create a single string from the client
     * output buffers. */
    if (YIdlPHC4vdtVB(aLtJDMH0h->s8lxoaN7Ash) == 0 && (KPh4MuxG)aLtJDMH0h->k8E8klbC < aLtJDMH0h->M6fkXQD1gqzTo) {
        /* This is a fast path for the common case of a reply inside the
         * client static buffer. Don't create an SDS string but just use
         * the client buffer directly. */
        aLtJDMH0h->wbwCT7U[aLtJDMH0h->k8E8klbC] = '\0';
        s8lxoaN7Ash = aLtJDMH0h->wbwCT7U;
        aLtJDMH0h->k8E8klbC = 0;
    } else {
        s8lxoaN7Ash = U_ImGiBg(aLtJDMH0h->wbwCT7U,aLtJDMH0h->k8E8klbC);
        aLtJDMH0h->k8E8klbC = 0;
        while(YIdlPHC4vdtVB(aLtJDMH0h->s8lxoaN7Ash)) {
            GJ4myC1vavS *W_NcTV = O9yQG6gQRX3c(lDIe(aLtJDMH0h->s8lxoaN7Ash));

            s8lxoaN7Ash = zjmNjr(s8lxoaN7Ash,W_NcTV->wbwCT7U,W_NcTV->JYMgr6KZjWZHM);
            zpnAlU(aLtJDMH0h->s8lxoaN7Ash,lDIe(aLtJDMH0h->s8lxoaN7Ash));
        }
    }
    if (Qvd5jJW7J && s8lxoaN7Ash[0] != '-') Qvd5jJW7J = 0;
    gRwOAQ(qv7u6nrNV71ym,s8lxoaN7Ash);

    /* If the debugger is active, log the reply from Redis. */
    if (wCM48hrB0xAe())
        JRzpkX8og2(s8lxoaN7Ash);

    if (s8lxoaN7Ash != aLtJDMH0h->wbwCT7U) jF5Zqj(s8lxoaN7Ash);
    aLtJDMH0h->nP1d2sapw = 0;

SjHeQ:
    /* Clean up. Command code may have changed argv/argc so we use the
     * argv/argc of the client instead of the local variables. */
    UM2KSRdbB(aLtJDMH0h->LTJ7, aLtJDMH0h->plr_4QS, aLtJDMH0h->Hv5NCEh);
    aLtJDMH0h->plr_4QS = aLtJDMH0h->Hv5NCEh = 0;
    aLtJDMH0h->TmVQFIQb_S = oiK17dDNxGhNq;
    aLtJDMH0h->LTJ7 = oiK17dDNxGhNq;
    M7aWe8ThGT9(aLtJDMH0h);
    Y7dl--;

    if (Qvd5jJW7J) {
        /* If we are here we should have an error in the stack, in the
         * form of a table with an "err" field. Extract the string to
         * return the plain error. */
        return BJXzQsJU01bam(qv7u6nrNV71ym);
    }
    return 1;
}

/* Our implementation to lua pcall.
 * We need this implementation for backward
 * comparability with older Redis versions.
 *
 * On Redis 7, the error object is a table,
 * compare to older version where the error
 * object is a string. To keep backward
 * comparability we catch the table object
 * and just return the error message. */
static int eADJlL3iAClTc(X8PyH0GU8BCr *qv7u6nrNV71ym) {
    int plr_4QS = mLaJgHy(qv7u6nrNV71ym);
    u18Dc4a(qv7u6nrNV71ym, 1); /* result place holder */
    oHT_YbgmcI(qv7u6nrNV71ym, 1);
    if (AK2Vo(qv7u6nrNV71ym, plr_4QS - 1, spBme4AEpCPry, 0)) {
        /* Error */
        vW0vr5g6t(qv7u6nrNV71ym, 1); /* remove the result place holder, now we have room for at least one element */
        if (MZVWb0JoA9f(qv7u6nrNV71ym, -1)) {
            HqO0t4X8(qv7u6nrNV71ym, -1, "err");
            if (sDAYbfOJrcKq(qv7u6nrNV71ym, -1)) {
                h7NBE1l(qv7u6nrNV71ym, -2); /* replace the error message with the table */
            }
        }
        u18Dc4a(qv7u6nrNV71ym, 0); /* push result */
        oHT_YbgmcI(qv7u6nrNV71ym, 1);
    }
    return mLaJgHy(qv7u6nrNV71ym);

}

/* redis.call() */
static int KBg6X4YQxOsp(X8PyH0GU8BCr *qv7u6nrNV71ym) {
    return MaNn(qv7u6nrNV71ym,1);
}

/* redis.pcall() */
static int fNQJUFO1n43n(X8PyH0GU8BCr *qv7u6nrNV71ym) {
    return MaNn(qv7u6nrNV71ym,0);
}

/* This adds redis.sha1hex(string) to Lua scripts using the same hashing
 * function used for sha1ing lua scripts. */
static int OSwd(X8PyH0GU8BCr *qv7u6nrNV71ym) {
    int plr_4QS = mLaJgHy(qv7u6nrNV71ym);
    char y2ykgwF[41];
    KPh4MuxG y6e1E_ze;
    char *yEuu;

    if (plr_4QS != 1) {
        R8Id(qv7u6nrNV71ym, "wrong number of arguments");
        return BJXzQsJU01bam(qv7u6nrNV71ym);
    }

    yEuu = (char*)qoyfr9(qv7u6nrNV71ym,1,&y6e1E_ze);
    chQkAvn(y2ykgwF,yEuu,y6e1E_ze);
    uSO0DL(qv7u6nrNV71ym,y2ykgwF);
    return 1;
}

/* Returns a table with a single field 'field' set to the string value
 * passed as argument. This helper function is handy when returning
 * a Redis Protocol error or status reply from Lua:
 *
 * return redis.error_reply("ERR Some Error")
 * return redis.status_reply("ERR Some Error")
 */
static int lqkSjKMsvw(X8PyH0GU8BCr *qv7u6nrNV71ym, char *jqcVtM) {
    if (mLaJgHy(qv7u6nrNV71ym) != 1 || vGDDS3FXf(qv7u6nrNV71ym,-1) != O1T52vaM4ex_) {
        R8Id(qv7u6nrNV71ym, "wrong number or type of arguments");
        return 1;
    }

    Xxx3D8_4(qv7u6nrNV71ym);
    uSO0DL(qv7u6nrNV71ym, jqcVtM);
    zq2ry1ZI(qv7u6nrNV71ym, -3);
    G2h9B7KnKZ0m(qv7u6nrNV71ym, -3);
    return 1;
}

/* redis.error_reply() */
static int MBOa(X8PyH0GU8BCr *qv7u6nrNV71ym) {
    if (mLaJgHy(qv7u6nrNV71ym) != 1 || vGDDS3FXf(qv7u6nrNV71ym,-1) != O1T52vaM4ex_) {
        R8Id(qv7u6nrNV71ym, "wrong number or type of arguments");
        return 1;
    }

    /* add '-' if not exists */
    const char *SCp1 = P8_HqVd8T1Vdu(qv7u6nrNV71ym, -1);
    MtwwP SpbJ5ZUc = oiK17dDNxGhNq;
    if (SCp1[0] != '-') {
        SpbJ5ZUc = XE_o9pi9PILhw(B4YbM7cF_(), "-%s", SCp1);
    } else {
        SpbJ5ZUc = OzOKacu4u(SCp1);
    }
    T6lHa5(qv7u6nrNV71ym, SpbJ5ZUc);
    return 1;
}

/* redis.status_reply() */
static int sDveg(X8PyH0GU8BCr *qv7u6nrNV71ym) {
    return lqkSjKMsvw(qv7u6nrNV71ym,"ok");
}

/* redis.set_repl()
 *
 * Set the propagation of write commands executed in the context of the
 * script to on/off for AOF and slaves. */
static int aFIClGYLm(X8PyH0GU8BCr *qv7u6nrNV71ym) {
    int EaXj0F4T, plr_4QS = mLaJgHy(qv7u6nrNV71ym);

    tpIit3Efe7* om4ctdIT = DllaG685eFJWb(qv7u6nrNV71ym, c_StnQzmHk1x);
    T5gjLFJt2m(om4ctdIT); /* Only supported inside script invocation */

    if (plr_4QS != 1) {
        R8Id(qv7u6nrNV71ym, "redis.set_repl() requires one argument.");
         return BJXzQsJU01bam(qv7u6nrNV71ym);
    }

    EaXj0F4T = oRTwBrLS(qv7u6nrNV71ym,-1);
    if ((EaXj0F4T & ~(XhcI476|huxzLF_1bH5G)) != 0) {
        R8Id(qv7u6nrNV71ym, "Invalid replication flags. Use REPL_AOF, REPL_REPLICA, REPL_ALL or REPL_NONE.");
        return BJXzQsJU01bam(qv7u6nrNV71ym);
    }

    Rfn_cR(om4ctdIT, EaXj0F4T);
    return 0;
}

/* redis.acl_check_cmd()
 *
 * Checks ACL permissions for given command for the current user. */
static int eoY1VLWcBvcUv(X8PyH0GU8BCr *qv7u6nrNV71ym) {
    tpIit3Efe7* om4ctdIT = DllaG685eFJWb(qv7u6nrNV71ym, c_StnQzmHk1x);
    T5gjLFJt2m(om4ctdIT); /* Only supported inside script invocation */
    int Qvd5jJW7J = 0;

    int plr_4QS, Hv5NCEh;
    bZNGQDGv **LTJ7 = UrG8t(qv7u6nrNV71ym, &plr_4QS, &Hv5NCEh);

    /* Require at least one argument */
    if (LTJ7 == oiK17dDNxGhNq) return BJXzQsJU01bam(qv7u6nrNV71ym);

    /* Find command */
    struct SW2nf8 *Wb301mVNzB;
    if ((Wb301mVNzB = tQaX_3m(LTJ7, plr_4QS)) == oiK17dDNxGhNq) {
        R8Id(qv7u6nrNV71ym, "Invalid command passed to redis.acl_check_cmd()");
        Qvd5jJW7J = 1;
    } else {
        int mWb_vsq9YC56;
        if (oCvnwtDXJKEt(om4ctdIT->FCKcCR_->TmVQFIQb_S, Wb301mVNzB, LTJ7, plr_4QS, &mWb_vsq9YC56) != Qvv8zkfa) {
            u18Dc4a(qv7u6nrNV71ym, 0);
        } else {
            u18Dc4a(qv7u6nrNV71ym, 1);
        }
    }

    UM2KSRdbB(LTJ7, plr_4QS, Hv5NCEh);
    if (Qvd5jJW7J)
        return BJXzQsJU01bam(qv7u6nrNV71ym);
    else
        return 1;
}


/* redis.log() */
static int vMUubcuvyY4_(X8PyH0GU8BCr *qv7u6nrNV71ym) {
    int hRAkplUj, plr_4QS = mLaJgHy(qv7u6nrNV71ym);
    int JgxANl7sFP1C;
    MtwwP ucJC;

    if (plr_4QS < 2) {
        R8Id(qv7u6nrNV71ym, "redis.log() requires two arguments or more.");
        return BJXzQsJU01bam(qv7u6nrNV71ym);
    } else if (!cnQnwYPGUnd(qv7u6nrNV71ym,-plr_4QS)) {
        R8Id(qv7u6nrNV71ym, "First argument must be a number (log level).");
        return BJXzQsJU01bam(qv7u6nrNV71ym);
    }
    JgxANl7sFP1C = oRTwBrLS(qv7u6nrNV71ym,-plr_4QS);
    if (JgxANl7sFP1C < Gc4BA6h9w || JgxANl7sFP1C > gKfWDSa9a) {
        R8Id(qv7u6nrNV71ym, "Invalid log level.");
        return BJXzQsJU01bam(qv7u6nrNV71ym);
    }
    if (JgxANl7sFP1C < WTex.n2bvHch) return 0;

    /* Glue together all the arguments */
    ucJC = B4YbM7cF_();
    for (hRAkplUj = 1; hRAkplUj < plr_4QS; hRAkplUj++) {
        KPh4MuxG y6e1E_ze;
        char *yEuu;

        yEuu = (char*)qoyfr9(qv7u6nrNV71ym,(-plr_4QS)+hRAkplUj,&y6e1E_ze);
        if (yEuu) {
            if (hRAkplUj != 1) ucJC = zjmNjr(ucJC," ",1);
            ucJC = zjmNjr(ucJC,yEuu,y6e1E_ze);
        }
    }
    xJoU9U(JgxANl7sFP1C,ucJC);
    jF5Zqj(ucJC);
    return 0;
}

/* redis.setresp() */
static int RKFC39C5(X8PyH0GU8BCr *qv7u6nrNV71ym) {
    tpIit3Efe7* om4ctdIT = DllaG685eFJWb(qv7u6nrNV71ym, c_StnQzmHk1x);
    T5gjLFJt2m(om4ctdIT); /* Only supported inside script invocation */
    int plr_4QS = mLaJgHy(qv7u6nrNV71ym);

    if (plr_4QS != 1) {
        R8Id(qv7u6nrNV71ym, "redis.setresp() requires one argument.");
        return BJXzQsJU01bam(qv7u6nrNV71ym);
    }

    int mGSxNFlPjv = oRTwBrLS(qv7u6nrNV71ym,-plr_4QS);
    if (mGSxNFlPjv != 2 && mGSxNFlPjv != 3) {
        R8Id(qv7u6nrNV71ym, "RESP version must be 2 or 3.");
        return BJXzQsJU01bam(qv7u6nrNV71ym);
    }
    hmK1oKk3gOJW(om4ctdIT, mGSxNFlPjv);
    return 0;
}

/* ---------------------------------------------------------------------------
 * Lua engine initialization and reset.
 * ------------------------------------------------------------------------- */

static void eU2DS5F(X8PyH0GU8BCr *qv7u6nrNV71ym, const char *AX1g6pcOI_, twJyflV cZHi) {
  Fb7wOVmaTocm(qv7u6nrNV71ym, cZHi);
  uSO0DL(qv7u6nrNV71ym, AX1g6pcOI_);
  rfBL2A2GFU8Za(qv7u6nrNV71ym, 1, 0);
}

Hlss9 int (DC9f4miBzQP) (X8PyH0GU8BCr *r7QkkXdXjgQj);
Hlss9 int (FhXYp0ZPJJc) (X8PyH0GU8BCr *r7QkkXdXjgQj);
Hlss9 int (QJVYWzHJnK9d) (X8PyH0GU8BCr *r7QkkXdXjgQj);
Hlss9 int (aUKmQNXx1) (X8PyH0GU8BCr *r7QkkXdXjgQj);

static void XhPlG7(X8PyH0GU8BCr *qv7u6nrNV71ym) {
    eU2DS5F(qv7u6nrNV71ym, "", ObNzuVSsQM);
    eU2DS5F(qv7u6nrNV71ym, lPAo0kO2bD5, gr2_fe3);
    eU2DS5F(qv7u6nrNV71ym, KeEIoP, C2cz9pF);
    eU2DS5F(qv7u6nrNV71ym, WGt6JcKoFfT, BTxR_R);
    eU2DS5F(qv7u6nrNV71ym, udmmZektn5Yn, MkDwUS4yaXp);
    eU2DS5F(qv7u6nrNV71ym, g1iTm3, JpxlEOIVD58x);
    eU2DS5F(qv7u6nrNV71ym, "cjson", DC9f4miBzQP);
    eU2DS5F(qv7u6nrNV71ym, "struct", FhXYp0ZPJJc);
    eU2DS5F(qv7u6nrNV71ym, "cmsgpack", QJVYWzHJnK9d);
    eU2DS5F(qv7u6nrNV71ym, "bit", aUKmQNXx1);

#if 0 /* Stuff that we don't load currently, for sandboxing concerns. */
    eU2DS5F(qv7u6nrNV71ym, Twslp_, jmHHQVtSNefp);
#endif
}

/* Return sds of the string value located on stack at the given index.
 * Return NULL if the value is not a string. */
MtwwP rfjZ(X8PyH0GU8BCr *qv7u6nrNV71ym, int TckImqiKhOig) {
    if (!sDAYbfOJrcKq(qv7u6nrNV71ym, TckImqiKhOig)) {
        return oiK17dDNxGhNq;
    }

    KPh4MuxG y6e1E_ze;
    const char *E2kBIog = qoyfr9(qv7u6nrNV71ym, TckImqiKhOig, &y6e1E_ze);
    MtwwP MFv0ZGo = U_ImGiBg(E2kBIog, y6e1E_ze);
    return MFv0ZGo;
}

static int Kw3rqdDy0d(X8PyH0GU8BCr *qv7u6nrNV71ym) {
    int plr_4QS = mLaJgHy(qv7u6nrNV71ym);
    if (plr_4QS != 2) {
        AL2BiJBGOT(gKfWDSa9a, "malicious code trying to call luaProtectedTableError with wrong arguments");
        u5GZ(qv7u6nrNV71ym, "Wrong number of arguments to luaProtectedTableError");
    }
    if (!sDAYbfOJrcKq(qv7u6nrNV71ym, -1) && !cnQnwYPGUnd(qv7u6nrNV71ym, -1)) {
        u5GZ(qv7u6nrNV71ym, "Second argument to luaProtectedTableError must be a string or number");
    }
    const char *oNNCtk = P8_HqVd8T1Vdu(qv7u6nrNV71ym, -1);
    u5GZ(qv7u6nrNV71ym, "Script attempted to access nonexistent global variable '%s'", oNNCtk);
    return 0;
}

/* Set a special metatable on the table on the top of the stack.
 * The metatable will raise an error if the user tries to fetch
 * an un-existing value.
 *
 * The function assumes the Lua stack have a least enough
 * space to push 2 element, its up to the caller to verify
 * this before calling this function. */
void gMEaJ(X8PyH0GU8BCr *qv7u6nrNV71ym) {
    Xxx3D8_4(qv7u6nrNV71ym); /* push metatable */
    Fb7wOVmaTocm(qv7u6nrNV71ym, Kw3rqdDy0d); /* push get error handler */
    XjwcmbQpO(qv7u6nrNV71ym, -2, "__index");
    hoYEFqYv(qv7u6nrNV71ym, -2);
}

static int iWmtLVRHJad(X8PyH0GU8BCr *qv7u6nrNV71ym) {
    int plr_4QS = mLaJgHy(qv7u6nrNV71ym);
    if (plr_4QS != 3) {
        AL2BiJBGOT(gKfWDSa9a, "malicious code trying to call luaNewIndexAllowList with wrong arguments");
        u5GZ(qv7u6nrNV71ym, "Wrong number of arguments to luaNewIndexAllowList");
    }
    if (!MZVWb0JoA9f(qv7u6nrNV71ym, -3)) {
        u5GZ(qv7u6nrNV71ym, "first argument to luaNewIndexAllowList must be a table");
    }
    if (!sDAYbfOJrcKq(qv7u6nrNV71ym, -2) && !cnQnwYPGUnd(qv7u6nrNV71ym, -2)) {
        u5GZ(qv7u6nrNV71ym, "Second argument to luaNewIndexAllowList must be a string or number");
    }
    const char *oNNCtk = P8_HqVd8T1Vdu(qv7u6nrNV71ym, -2);
    /* check if the key is in our allow list */

    char ***lTjtF4x = xq1OTe;
    for (; *lTjtF4x ; ++lTjtF4x){
        char **aLtJDMH0h = *lTjtF4x;
        for (; *aLtJDMH0h ; ++aLtJDMH0h) {
            if (xZv4Q6N(*aLtJDMH0h, oNNCtk) == 0) {
                break;
            }
        }
        if (*aLtJDMH0h) {
            break;
        }
    }
    if (!*lTjtF4x) {
        /* Search the value on the back list, if its there we know that it was removed
         * on purpose and there is no need to print a warning. */
        char **aLtJDMH0h = r5z_vNq_N;
        for ( ; *aLtJDMH0h ; ++aLtJDMH0h) {
            if (xZv4Q6N(*aLtJDMH0h, oNNCtk) == 0) {
                break;
            }
        }
        if (!*aLtJDMH0h) {
            AL2BiJBGOT(gKfWDSa9a, "A key '%s' was added to Lua globals which is not on the globals allow list nor listed on the deny list.", oNNCtk);
        }
    } else {
        ZFtx(qv7u6nrNV71ym, -3);
    }
    return 0;
}

/* Set a metatable with '__newindex' function that verify that
 * the new index appears on our globals while list.
 *
 * The metatable is set on the table which located on the top
 * of the stack.
 */
void VytAerApnMd(X8PyH0GU8BCr *qv7u6nrNV71ym) {
    Xxx3D8_4(qv7u6nrNV71ym); /* push metatable */
    Fb7wOVmaTocm(qv7u6nrNV71ym, iWmtLVRHJad); /* push get error handler */
    XjwcmbQpO(qv7u6nrNV71ym, -2, "__newindex");
    hoYEFqYv(qv7u6nrNV71ym, -2);
}

/* Set the readonly flag on the table located on the top of the stack
 * and recursively call this function on each table located on the original
 * table.  Also, recursively call this function on the metatables.*/
void gq61WU4N3WI8(X8PyH0GU8BCr *qv7u6nrNV71ym) {
    /* This protect us from a loop in case we already visited the table
     * For example, globals has '_G' key which is pointing back to globals. */
    if (q0H5s_Az9D4rB(qv7u6nrNV71ym, -1)) {
        return;
    }

    /* protect the current table */
    db95LzwuT1_(qv7u6nrNV71ym, -1, 1);

    Lmi5Dk(qv7u6nrNV71ym, 2);
    XwgiiV(qv7u6nrNV71ym); /* Use nil to start iteration. */
    while (D2PL(qv7u6nrNV71ym,-2)) {
        /* Stack now: table, key, value */
        if (MZVWb0JoA9f(qv7u6nrNV71ym, -1)) {
            gq61WU4N3WI8(qv7u6nrNV71ym);
        }
        Z9NsBxGQ(qv7u6nrNV71ym, 1);
    }

    /* protect the metatable if exists */
    if (zWsk8VQ7wgs(qv7u6nrNV71ym, -1)) {
        gq61WU4N3WI8(qv7u6nrNV71ym);
        Z9NsBxGQ(qv7u6nrNV71ym, 1); /* pop the metatable */
    }
}

void jRgW(X8PyH0GU8BCr* qv7u6nrNV71ym) {
    uSO0DL(qv7u6nrNV71ym,"REDIS_VERSION_NUM");
    EZ99aq2v(qv7u6nrNV71ym,E86K3kbrv);
    G2h9B7KnKZ0m(qv7u6nrNV71ym,-3);

    uSO0DL(qv7u6nrNV71ym,"REDIS_VERSION");
    uSO0DL(qv7u6nrNV71ym,prFnY4WqRCaaf);
    G2h9B7KnKZ0m(qv7u6nrNV71ym,-3);
}

void LoYk(X8PyH0GU8BCr* qv7u6nrNV71ym) {
    /* redis.log and log levels. */
    uSO0DL(qv7u6nrNV71ym,"log");
    Fb7wOVmaTocm(qv7u6nrNV71ym,vMUubcuvyY4_);
    G2h9B7KnKZ0m(qv7u6nrNV71ym,-3);

    uSO0DL(qv7u6nrNV71ym,"LOG_DEBUG");
    EZ99aq2v(qv7u6nrNV71ym,Gc4BA6h9w);
    G2h9B7KnKZ0m(qv7u6nrNV71ym,-3);

    uSO0DL(qv7u6nrNV71ym,"LOG_VERBOSE");
    EZ99aq2v(qv7u6nrNV71ym,IZTs2kke62_vq);
    G2h9B7KnKZ0m(qv7u6nrNV71ym,-3);

    uSO0DL(qv7u6nrNV71ym,"LOG_NOTICE");
    EZ99aq2v(qv7u6nrNV71ym,Ib5Dt4F);
    G2h9B7KnKZ0m(qv7u6nrNV71ym,-3);

    uSO0DL(qv7u6nrNV71ym,"LOG_WARNING");
    EZ99aq2v(qv7u6nrNV71ym,gKfWDSa9a);
    G2h9B7KnKZ0m(qv7u6nrNV71ym,-3);
}

void wQFR(X8PyH0GU8BCr* qv7u6nrNV71ym) {
    zq2ry1ZI(qv7u6nrNV71ym, Lc_R8sqd5sxv);
    VytAerApnMd(qv7u6nrNV71ym);
    Z9NsBxGQ(qv7u6nrNV71ym, 1);

    XhPlG7(qv7u6nrNV71ym);

    Fb7wOVmaTocm(qv7u6nrNV71ym,eADJlL3iAClTc);
    inTwP6cD(qv7u6nrNV71ym, "pcall");

    /* Register the redis commands table and fields */
    Xxx3D8_4(qv7u6nrNV71ym);

    /* redis.call */
    uSO0DL(qv7u6nrNV71ym,"call");
    Fb7wOVmaTocm(qv7u6nrNV71ym,KBg6X4YQxOsp);
    G2h9B7KnKZ0m(qv7u6nrNV71ym,-3);

    /* redis.pcall */
    uSO0DL(qv7u6nrNV71ym,"pcall");
    Fb7wOVmaTocm(qv7u6nrNV71ym,fNQJUFO1n43n);
    G2h9B7KnKZ0m(qv7u6nrNV71ym,-3);

    LoYk(qv7u6nrNV71ym);

    jRgW(qv7u6nrNV71ym);

    /* redis.setresp */
    uSO0DL(qv7u6nrNV71ym,"setresp");
    Fb7wOVmaTocm(qv7u6nrNV71ym,RKFC39C5);
    G2h9B7KnKZ0m(qv7u6nrNV71ym,-3);

    /* redis.sha1hex */
    uSO0DL(qv7u6nrNV71ym, "sha1hex");
    Fb7wOVmaTocm(qv7u6nrNV71ym, OSwd);
    G2h9B7KnKZ0m(qv7u6nrNV71ym, -3);

    /* redis.error_reply and redis.status_reply */
    uSO0DL(qv7u6nrNV71ym, "error_reply");
    Fb7wOVmaTocm(qv7u6nrNV71ym, MBOa);
    G2h9B7KnKZ0m(qv7u6nrNV71ym, -3);
    uSO0DL(qv7u6nrNV71ym, "status_reply");
    Fb7wOVmaTocm(qv7u6nrNV71ym, sDveg);
    G2h9B7KnKZ0m(qv7u6nrNV71ym, -3);

    /* redis.set_repl and associated flags. */
    uSO0DL(qv7u6nrNV71ym,"set_repl");
    Fb7wOVmaTocm(qv7u6nrNV71ym,aFIClGYLm);
    G2h9B7KnKZ0m(qv7u6nrNV71ym,-3);

    uSO0DL(qv7u6nrNV71ym,"REPL_NONE");
    EZ99aq2v(qv7u6nrNV71ym,mhbjZrUeUxMk);
    G2h9B7KnKZ0m(qv7u6nrNV71ym,-3);

    uSO0DL(qv7u6nrNV71ym,"REPL_AOF");
    EZ99aq2v(qv7u6nrNV71ym,XhcI476);
    G2h9B7KnKZ0m(qv7u6nrNV71ym,-3);

    uSO0DL(qv7u6nrNV71ym,"REPL_SLAVE");
    EZ99aq2v(qv7u6nrNV71ym,huxzLF_1bH5G);
    G2h9B7KnKZ0m(qv7u6nrNV71ym,-3);

    uSO0DL(qv7u6nrNV71ym,"REPL_REPLICA");
    EZ99aq2v(qv7u6nrNV71ym,huxzLF_1bH5G);
    G2h9B7KnKZ0m(qv7u6nrNV71ym,-3);

    uSO0DL(qv7u6nrNV71ym,"REPL_ALL");
    EZ99aq2v(qv7u6nrNV71ym,XhcI476|huxzLF_1bH5G);
    G2h9B7KnKZ0m(qv7u6nrNV71ym,-3);

    /* redis.acl_check_cmd */
    uSO0DL(qv7u6nrNV71ym,"acl_check_cmd");
    Fb7wOVmaTocm(qv7u6nrNV71ym,eoY1VLWcBvcUv);
    G2h9B7KnKZ0m(qv7u6nrNV71ym,-3);

    /* Finally set the table as 'redis' global var. */
    inTwP6cD(qv7u6nrNV71ym,PF6M1G33ldZ);

    /* Replace math.random and math.randomseed with our implementations. */
    foyyjzL0Ji(qv7u6nrNV71ym,"math");

    uSO0DL(qv7u6nrNV71ym,"random");
    Fb7wOVmaTocm(qv7u6nrNV71ym,jvqCXd);
    G2h9B7KnKZ0m(qv7u6nrNV71ym,-3);

    uSO0DL(qv7u6nrNV71ym,"randomseed");
    Fb7wOVmaTocm(qv7u6nrNV71ym,Kmjqqwu);
    G2h9B7KnKZ0m(qv7u6nrNV71ym,-3);

    inTwP6cD(qv7u6nrNV71ym,"math");
}

/* Set an array of Redis String Objects as a Lua array (table) stored into a
 * global variable. */
static void vj4Yq(X8PyH0GU8BCr *qv7u6nrNV71ym, bZNGQDGv **EbFS2, int QypqvhBJTUrDc) {
    int hRAkplUj;

    Xxx3D8_4(qv7u6nrNV71ym);
    for (hRAkplUj = 0; hRAkplUj < QypqvhBJTUrDc; hRAkplUj++) {
        DIVeD(qv7u6nrNV71ym,(char*)EbFS2[hRAkplUj]->HOx8cWCfI,GsIvP8MuRN(EbFS2[hRAkplUj]->HOx8cWCfI));
        qOGNoz(qv7u6nrNV71ym,-2,hRAkplUj+1);
    }
}

/* ---------------------------------------------------------------------------
 * Redis provided math.random
 * ------------------------------------------------------------------------- */

/* We replace math.random() with our implementation that is not affected
 * by specific libc random() implementations and will output the same sequence
 * (for the same seed) in every arch. */

/* The following implementation is the one shipped with Lua itself but with
 * rand() replaced by redisLrand48(). */
static int jvqCXd (X8PyH0GU8BCr *r7QkkXdXjgQj) {
  /* the `%' avoids the (rare) case of r==1, and is needed also because on
     some systems (SunOS!) `rand()' may return a value larger than RAND_MAX */
  Fhnvfr xxtkyLi = (Fhnvfr)(UCsQdw()%Lsv8KJJ3cm) /
                                (Fhnvfr)Lsv8KJJ3cm;
  switch (mLaJgHy(r7QkkXdXjgQj)) {  /* check number of arguments */
    case 0: {  /* no arguments */
      EZ99aq2v(r7QkkXdXjgQj, xxtkyLi);  /* Number between 0 and 1 */
      break;
    }
    case 1: {  /* only upper limit */
      int Dht2hh = oLYjgB9(r7QkkXdXjgQj, 1);
      HLb0RtoNIim(r7QkkXdXjgQj, 1<=Dht2hh, 1, "interval is empty");
      EZ99aq2v(r7QkkXdXjgQj, JIr_fT(xxtkyLi*Dht2hh)+1);  /* int between 1 and `u' */
      break;
    }
    case 2: {  /* lower and upper limits */
      int RuqR518F = oLYjgB9(r7QkkXdXjgQj, 1);
      int Dht2hh = oLYjgB9(r7QkkXdXjgQj, 2);
      HLb0RtoNIim(r7QkkXdXjgQj, RuqR518F<=Dht2hh, 2, "interval is empty");
      EZ99aq2v(r7QkkXdXjgQj, JIr_fT(xxtkyLi*(Dht2hh-RuqR518F+1))+RuqR518F);  /* int between `l' and `u' */
      break;
    }
    default: return u5GZ(r7QkkXdXjgQj, "wrong number of arguments");
  }
  return 1;
}

static int Kmjqqwu (X8PyH0GU8BCr *r7QkkXdXjgQj) {
  ub4N1TowIJ(oLYjgB9(r7QkkXdXjgQj, 1));
  return 0;
}

/* This is the Lua script "count" hook that we use to detect scripts timeout. */
static void RVAfOov(X8PyH0GU8BCr *qv7u6nrNV71ym, DWi0V7EsB *xli6CRRv3i) {
    j59GHM(xli6CRRv3i);
    tpIit3Efe7* om4ctdIT = DllaG685eFJWb(qv7u6nrNV71ym, c_StnQzmHk1x);
    T5gjLFJt2m(om4ctdIT); /* Only supported inside script invocation */
    if (VrYq8p(om4ctdIT) == YALkSMHn0) {
        AL2BiJBGOT(Ib5Dt4F,"Lua script killed by user with SCRIPT KILL.");

        /*
         * Set the hook to invoke all the time so the user
         * will not be able to catch the error with pcall and invoke
         * pcall again which will prevent the script from ever been killed
         */
        K1x7zlMsE_(qv7u6nrNV71ym, RVAfOov, ZApwuir, 0);

        R8Id(qv7u6nrNV71ym,"Script killed by user with SCRIPT KILL...");
        BJXzQsJU01bam(qv7u6nrNV71ym);
    }
}

void nO44K16dpOQFJ(mpkWZCg *eCDLm8ECO5) {
    if (eCDLm8ECO5->PdURK0) jF5Zqj(eCDLm8ECO5->PdURK0);
    if (eCDLm8ECO5->UeUwDOChpI) jF5Zqj(eCDLm8ECO5->UeUwDOChpI);
    if (eCDLm8ECO5->qElQBgNEp) jF5Zqj(eCDLm8ECO5->qElQBgNEp);
}

void NDN7XI(X8PyH0GU8BCr *qv7u6nrNV71ym, mpkWZCg *eCDLm8ECO5) {
    if (sDAYbfOJrcKq(qv7u6nrNV71ym, -1)) {
        eCDLm8ECO5->PdURK0 = XE_o9pi9PILhw(B4YbM7cF_(), "ERR %s", P8_HqVd8T1Vdu(qv7u6nrNV71ym, -1));
        eCDLm8ECO5->qElQBgNEp = oiK17dDNxGhNq;
        eCDLm8ECO5->UeUwDOChpI = oiK17dDNxGhNq;
        eCDLm8ECO5->PqHZA4CO = 0;
        return;
    }

    HqO0t4X8(qv7u6nrNV71ym, -1, "err");
    if (sDAYbfOJrcKq(qv7u6nrNV71ym, -1)) {
        eCDLm8ECO5->PdURK0 = OzOKacu4u(P8_HqVd8T1Vdu(qv7u6nrNV71ym, -1));
    }
    Z9NsBxGQ(qv7u6nrNV71ym, 1);

    HqO0t4X8(qv7u6nrNV71ym, -1, "source");
    if (sDAYbfOJrcKq(qv7u6nrNV71ym, -1)) {
        eCDLm8ECO5->UeUwDOChpI = OzOKacu4u(P8_HqVd8T1Vdu(qv7u6nrNV71ym, -1));
    }
    Z9NsBxGQ(qv7u6nrNV71ym, 1);

    HqO0t4X8(qv7u6nrNV71ym, -1, "line");
    if (sDAYbfOJrcKq(qv7u6nrNV71ym, -1)) {
        eCDLm8ECO5->qElQBgNEp = OzOKacu4u(P8_HqVd8T1Vdu(qv7u6nrNV71ym, -1));
    }
    Z9NsBxGQ(qv7u6nrNV71ym, 1);

    HqO0t4X8(qv7u6nrNV71ym, -1, "ignore_error_stats_update");
    if (A_VJ(qv7u6nrNV71ym, -1)) {
        eCDLm8ECO5->PqHZA4CO = Fa5pu(qv7u6nrNV71ym, -1);
    }
    Z9NsBxGQ(qv7u6nrNV71ym, 1);
}

void E58kLc7r(tpIit3Efe7* UU9WvIJCen3J, X8PyH0GU8BCr *qv7u6nrNV71ym, bZNGQDGv** U415hR0wnLm, KPh4MuxG SSny, bZNGQDGv** VHrG, KPh4MuxG DTCLay, int gyJB7cMRri) {
    HUv4* aLtJDMH0h = UU9WvIJCen3J->FCKcCR_;
    int zfqZFi8eInFS = 0;

    /* We must set it before we set the Lua hook, theoretically the
     * Lua hook might be called wheneven we run any Lua instruction
     * such as 'luaSetGlobalArray' and we want the run_ctx to be available
     * each time the Lua hook is invoked. */
    sIgCLT3(qv7u6nrNV71ym, c_StnQzmHk1x, UU9WvIJCen3J);

    if (WTex.BGvDfPEGp76ZM > 0 && !gyJB7cMRri) {
        K1x7zlMsE_(qv7u6nrNV71ym,RVAfOov,XL8r4cG,100000);
        zfqZFi8eInFS = 1;
    } else if (gyJB7cMRri) {
        K1x7zlMsE_(qv7u6nrNV71ym,HCR5DjgyC55Iq,ZApwuir|XL8r4cG,100000);
        zfqZFi8eInFS = 1;
    }

    /* Populate the argv and keys table accordingly to the arguments that
     * EVAL received. */
    vj4Yq(qv7u6nrNV71ym,U415hR0wnLm,SSny);
    /* On eval, keys and arguments are globals. */
    if (UU9WvIJCen3J->EaXj0F4T & dnj9zMJ17897n){
        /* open global protection to set KEYS */
        db95LzwuT1_(qv7u6nrNV71ym, Lc_R8sqd5sxv, 0);
        inTwP6cD(qv7u6nrNV71ym,"KEYS");
        db95LzwuT1_(qv7u6nrNV71ym, Lc_R8sqd5sxv, 1);
    }
    vj4Yq(qv7u6nrNV71ym,VHrG,DTCLay);
    if (UU9WvIJCen3J->EaXj0F4T & dnj9zMJ17897n){
        /* open global protection to set ARGV */
        db95LzwuT1_(qv7u6nrNV71ym, Lc_R8sqd5sxv, 0);
        inTwP6cD(qv7u6nrNV71ym,"ARGV");
        db95LzwuT1_(qv7u6nrNV71ym, Lc_R8sqd5sxv, 1);
    }

    /* At this point whether this script was never seen before or if it was
     * already defined, we can call it.
     * On eval mode, we have zero arguments and expect a single return value.
     * In addition the error handler is located on position -2 on the Lua stack.
     * On function mode, we pass 2 arguments (the keys and args tables),
     * and the error handler is located on position -4 (stack: error_handler, callback, keys, args) */
    int SCp1;
    if (UU9WvIJCen3J->EaXj0F4T & dnj9zMJ17897n) {
        SCp1 = AK2Vo(qv7u6nrNV71ym,0,1,-2);
    } else {
        SCp1 = AK2Vo(qv7u6nrNV71ym,2,1,-4);
    }

    if (SCp1) {
        /* Error object is a table of the following format:
         * {err='<error msg>', source='<source file>', line=<line>}
         * We can construct the error message from this information */
        if (!MZVWb0JoA9f(qv7u6nrNV71ym, -1)) {
            const char *PdURK0 = "execution failure";
            if (sDAYbfOJrcKq(qv7u6nrNV71ym, -1)) {
                PdURK0 = P8_HqVd8T1Vdu(qv7u6nrNV71ym, -1);
            }
            mzSqHo5(aLtJDMH0h,"Error running script %s, %.100s\n", UU9WvIJCen3J->vrdE, PdURK0);
        } else {
            mpkWZCg eCDLm8ECO5 = {0};
            MtwwP AGCa = B4YbM7cF_();
            NDN7XI(qv7u6nrNV71ym, &eCDLm8ECO5);
            AGCa = XE_o9pi9PILhw(AGCa, "-%s",
                                  eCDLm8ECO5.PdURK0);
            if (eCDLm8ECO5.qElQBgNEp && eCDLm8ECO5.UeUwDOChpI) {
                AGCa = XE_o9pi9PILhw(AGCa, " script: %s, on %s:%s.",
                                      UU9WvIJCen3J->vrdE,
                                      eCDLm8ECO5.UeUwDOChpI,
                                      eCDLm8ECO5.qElQBgNEp);
            }
            tlbgU(aLtJDMH0h, AGCa, eCDLm8ECO5.PqHZA4CO? aP3Mo8 : 0);
            nO44K16dpOQFJ(&eCDLm8ECO5);
        }
        Z9NsBxGQ(qv7u6nrNV71ym,1); /* Consume the Lua error */
    } else {
        /* On success convert the Lua return value into Redis protocol, and
         * send it to * the client. */
        dd3oj3(aLtJDMH0h, UU9WvIJCen3J->aLtJDMH0h, qv7u6nrNV71ym); /* Convert and consume the reply. */
    }

    /* Perform some cleanup that we need to do both on error and success. */
    if (zfqZFi8eInFS) K1x7zlMsE_(qv7u6nrNV71ym,oiK17dDNxGhNq,0,0); /* Disable hook */

    /* remove run_ctx from registry, its only applicable for the current script. */
    sIgCLT3(qv7u6nrNV71ym, c_StnQzmHk1x, oiK17dDNxGhNq);
}

unsigned long PmUm8Y(X8PyH0GU8BCr *qv7u6nrNV71ym) {
    return Mqm8Bx2l(qv7u6nrNV71ym, j7K64U1Z, 0) * 1024LL;
}

/* Call the Lua garbage collector from time to time to avoid a
 * full cycle performed by Lua, which adds too latency.
 *
 * The call is performed every LUA_GC_CYCLE_PERIOD executed commands
 * (and for LUA_GC_CYCLE_PERIOD collection steps) because calling it
 * for every command uses too much CPU.
 * 
 * Each script VM / State (Eval and Functions) maintains its own unique `gc_count`
 * to control GC independently. */
#define thjI 50
void xAGogWckerWL(X8PyH0GU8BCr *qv7u6nrNV71ym, int *RZhFAjgH) {
    (*RZhFAjgH)++;
    if (*RZhFAjgH >= thjI) {
        Mqm8Bx2l(qv7u6nrNV71ym, QWaadZ3viC6J, thjI);
        *RZhFAjgH = 0;
    }
}
