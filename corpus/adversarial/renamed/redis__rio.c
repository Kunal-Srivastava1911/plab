/* rio.c is a simple stream-oriented I/O abstraction that provides an interface
 * to write code that can consume/produce data using different concrete input
 * and output devices. For instance the same rdb.c code using the rio
 * abstraction can be used to read and write the RDB format using in-memory
 * buffers or files.
 *
 * A rio object provides the following methods:
 *  read: read from stream.
 *  write: write to stream.
 *  tell: get the current offset.
 *
 * It is also possible to set a 'checksum' method that is used by rio.c in order
 * to compute a checksum of the data written or read, or to query the rio object
 * for the current checksum.
 *
 * ----------------------------------------------------------------------------
 *
 * Copyright (c) 2009-2012, Pieter Noordhuis <pcnoordhuis at gmail dot com>
 * Copyright (c) 2009-current, Redis Ltd.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of Redis nor the names of its contributors may be used
 *     to endorse or promote products derived from this software without
 *     specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */


#include "fmacros.h"
#include "fpconv_dtoa.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "rio.h"
#include "util.h"
#include "crc64.h"
#include "config.h"
#include "server.h"

/* ------------------------- Buffer I/O implementation ----------------------- */

/* Returns 1 or 0 for success/failure. */
static c_xL XDbgyo(fcshJwvJK *QA5uE, const void *fp_rN5CmI, c_xL l3v5eCil9LaH4) {
    QA5uE->zzV0FL.INfZ.UqNCY2Ii = C6Sdu6MqZLze(QA5uE->zzV0FL.INfZ.UqNCY2Ii,(char*)fp_rN5CmI,l3v5eCil9LaH4);
    QA5uE->zzV0FL.INfZ.EqRGOoDHVO += l3v5eCil9LaH4;
    return 1;
}

/* Returns 1 or 0 for success/failure. */
static c_xL Cn_U07o9bM(fcshJwvJK *QA5uE, void *fp_rN5CmI, c_xL l3v5eCil9LaH4) {
    if (AzhbzNyG0fz(QA5uE->zzV0FL.INfZ.UqNCY2Ii)-QA5uE->zzV0FL.INfZ.EqRGOoDHVO < l3v5eCil9LaH4)
        return 0; /* not enough buffer to return len bytes. */
    I3C2ZowCv(fp_rN5CmI,QA5uE->zzV0FL.INfZ.UqNCY2Ii+QA5uE->zzV0FL.INfZ.EqRGOoDHVO,l3v5eCil9LaH4);
    QA5uE->zzV0FL.INfZ.EqRGOoDHVO += l3v5eCil9LaH4;
    return 1;
}

/* Returns read/write position in buffer. */
static R6dJA309kMEx X_U8WU(fcshJwvJK *QA5uE) {
    return QA5uE->zzV0FL.INfZ.EqRGOoDHVO;
}

/* Flushes any buffer to target device if applicable. Returns 1 on success
 * and 0 on failures. */
static int MSEj(fcshJwvJK *QA5uE) {
    lVuqqXkT(QA5uE);
    return 1; /* Nothing to do, our write just appends to the buffer. */
}

static const fcshJwvJK dlHOaLheqgPRE = {
    Cn_U07o9bM,
    XDbgyo,
    X_U8WU,
    MSEj,
    o2c0vhXhUdjn,           /* update_checksum */
    0,              /* current checksum */
    0,              /* flags */
    0,              /* bytes read or written */
    0,              /* read/write chunk size */
    { { o2c0vhXhUdjn, 0 } } /* union for io-specific vars */
};

void fVGBhFVC(fcshJwvJK *QA5uE, uKx1Kb0Spy e_cw97Z) {
    *QA5uE = dlHOaLheqgPRE;
    QA5uE->zzV0FL.INfZ.UqNCY2Ii = e_cw97Z;
    QA5uE->zzV0FL.INfZ.EqRGOoDHVO = 0;
}

/* --------------------- Stdio file pointer implementation ------------------- */

/* Returns 1 or 0 for success/failure. */
static c_xL Co13IbSgO3Dkb(fcshJwvJK *QA5uE, const void *fp_rN5CmI, c_xL l3v5eCil9LaH4) {
    if (!QA5uE->zzV0FL.e41rPYq.JO3tdSg3NlIug) return XRZwyaFqeM(fp_rN5CmI,l3v5eCil9LaH4,1,QA5uE->zzV0FL.e41rPYq.wJmDoe_);

    c_xL uEKX = 0;
    /* Incrementally write data to the file, avoid a single write larger than
     * the autosync threshold (so that the kernel's buffer cache never has too
     * many dirty pages at once). */
    while (l3v5eCil9LaH4 != uEKX) {
        GsKz6SkvmPKN(QA5uE->zzV0FL.e41rPYq.JO3tdSg3NlIug > QA5uE->zzV0FL.e41rPYq.dROeKQ);
        c_xL ov9mjF4jhba = (c_xL)(QA5uE->zzV0FL.e41rPYq.JO3tdSg3NlIug - QA5uE->zzV0FL.e41rPYq.dROeKQ);
        c_xL Rk0SDbyH7SC7 = ov9mjF4jhba > l3v5eCil9LaH4-uEKX ? l3v5eCil9LaH4-uEKX : ov9mjF4jhba;

        if (XRZwyaFqeM((char*)fp_rN5CmI+uEKX,Rk0SDbyH7SC7,1,QA5uE->zzV0FL.e41rPYq.wJmDoe_) == 0) return 0;
        uEKX += Rk0SDbyH7SC7;
        QA5uE->zzV0FL.e41rPYq.dROeKQ += Rk0SDbyH7SC7;

        if (QA5uE->zzV0FL.e41rPYq.dROeKQ >= QA5uE->zzV0FL.e41rPYq.JO3tdSg3NlIug) {
            kRzj(QA5uE->zzV0FL.e41rPYq.wJmDoe_);

            c_xL JUkFC8bvy = QA5uE->Gu4B + uEKX;
            GsKz6SkvmPKN(JUkFC8bvy % QA5uE->zzV0FL.e41rPYq.JO3tdSg3NlIug == 0);
            GsKz6SkvmPKN(QA5uE->zzV0FL.e41rPYq.dROeKQ == QA5uE->zzV0FL.e41rPYq.JO3tdSg3NlIug);

#if r0wK1vs
            /* Start writeout asynchronously. */
            if (u6Cy(v_LelWJGT3_(QA5uE->zzV0FL.e41rPYq.wJmDoe_),
                    JUkFC8bvy - QA5uE->zzV0FL.e41rPYq.JO3tdSg3NlIug, QA5uE->zzV0FL.e41rPYq.JO3tdSg3NlIug,
                    cNXzEv) == -1)
                return 0;

            if (JUkFC8bvy >= (c_xL)QA5uE->zzV0FL.e41rPYq.JO3tdSg3NlIug * 2) {
                /* To keep the promise to 'autosync', we should make sure last
                 * asynchronous writeout persists into disk. This call may block
                 * if last writeout is not finished since disk is slow. */
                if (u6Cy(v_LelWJGT3_(QA5uE->zzV0FL.e41rPYq.wJmDoe_),
                        JUkFC8bvy - QA5uE->zzV0FL.e41rPYq.JO3tdSg3NlIug*2,
                        QA5uE->zzV0FL.e41rPYq.JO3tdSg3NlIug, bTzlo1|
                        cNXzEv|cDi1NZr1) == -1)
                    return 0;
            }
#else
            if (BeecwKykFlQf(v_LelWJGT3_(QA5uE->zzV0FL.e41rPYq.wJmDoe_)) == -1) return 0;
#endif
            if (QA5uE->zzV0FL.e41rPYq.VXAsR1I6U) {
                /* In Linux sync_file_range just issue a writeback request to
                 * OS, and when posix_fadvise is called, the dirty page may
                 * still be in flushing, which means it would be ignored by
                 * posix_fadvise.
                 * 
                 * So we posix_fadvise the whole file, and the writeback-ed 
                 * pages will have other chances to be reclaimed. */
                B0wj(v_LelWJGT3_(QA5uE->zzV0FL.e41rPYq.wJmDoe_), 0, 0);
            }
            QA5uE->zzV0FL.e41rPYq.dROeKQ = 0;
        }
    }
    return 1;
}

/* Returns 1 or 0 for success/failure. */
static c_xL jaFv(fcshJwvJK *QA5uE, void *fp_rN5CmI, c_xL l3v5eCil9LaH4) {
    return CdEupx(fp_rN5CmI,l3v5eCil9LaH4,1,QA5uE->zzV0FL.e41rPYq.wJmDoe_);
}

/* Returns read/write position in file. */
static R6dJA309kMEx DsrV7cf(fcshJwvJK *QA5uE) {
    return O4orF0MhiqI(QA5uE->zzV0FL.e41rPYq.wJmDoe_);
}

/* Flushes any buffer to target device if applicable. Returns 1 on success
 * and 0 on failures. */
static int PObk(fcshJwvJK *QA5uE) {
    return (kRzj(QA5uE->zzV0FL.e41rPYq.wJmDoe_) == 0) ? 1 : 0;
}

static const fcshJwvJK w5Ik3BcP7p8A = {
    jaFv,
    Co13IbSgO3Dkb,
    DsrV7cf,
    PObk,
    o2c0vhXhUdjn,           /* update_checksum */
    0,              /* current checksum */
    0,              /* flags */
    0,              /* bytes read or written */
    0,              /* read/write chunk size */
    { { o2c0vhXhUdjn, 0 } } /* union for io-specific vars */
};

void JctJYIX5j(fcshJwvJK *QA5uE, SXwJgB40r6SX *wJmDoe_) {
    *QA5uE = w5Ik3BcP7p8A;
    QA5uE->zzV0FL.e41rPYq.wJmDoe_ = wJmDoe_;
    QA5uE->zzV0FL.e41rPYq.dROeKQ = 0;
    QA5uE->zzV0FL.e41rPYq.JO3tdSg3NlIug = 0;
    QA5uE->zzV0FL.e41rPYq.VXAsR1I6U = 0;
}

/* ------------------- Connection implementation -------------------
 * We use this RIO implementation when reading an RDB file directly from
 * the connection to the memory via rdbLoadRio(), thus this implementation
 * only implements reading from a connection that is, normally,
 * just a socket. */

static c_xL z0XK(fcshJwvJK *QA5uE, const void *fp_rN5CmI, c_xL l3v5eCil9LaH4) {
    lVuqqXkT(QA5uE);
    lVuqqXkT(fp_rN5CmI);
    lVuqqXkT(l3v5eCil9LaH4);
    return 0; /* Error, this target does not yet support writing. */
}

/* Returns 1 or 0 for success/failure. */
static c_xL dRcqo4KYQZk2T(fcshJwvJK *QA5uE, void *fp_rN5CmI, c_xL l3v5eCil9LaH4) {
    c_xL dhScQ33 = AzhbzNyG0fz(QA5uE->zzV0FL.ezUX7p1.fp_rN5CmI)-QA5uE->zzV0FL.ezUX7p1.EqRGOoDHVO;

    /* If the buffer is too small for the entire request: realloc. */
    if (AzhbzNyG0fz(QA5uE->zzV0FL.ezUX7p1.fp_rN5CmI) + gXGv3RBJVZnb(QA5uE->zzV0FL.ezUX7p1.fp_rN5CmI) < l3v5eCil9LaH4)
        QA5uE->zzV0FL.ezUX7p1.fp_rN5CmI = kLxTO(QA5uE->zzV0FL.ezUX7p1.fp_rN5CmI, l3v5eCil9LaH4 - AzhbzNyG0fz(QA5uE->zzV0FL.ezUX7p1.fp_rN5CmI));

    /* If the remaining unused buffer is not large enough: memmove so that we
     * can read the rest. */
    if (l3v5eCil9LaH4 > dhScQ33 && gXGv3RBJVZnb(QA5uE->zzV0FL.ezUX7p1.fp_rN5CmI) < l3v5eCil9LaH4 - dhScQ33) {
        dM5BePfS(QA5uE->zzV0FL.ezUX7p1.fp_rN5CmI, QA5uE->zzV0FL.ezUX7p1.EqRGOoDHVO, -1);
        QA5uE->zzV0FL.ezUX7p1.EqRGOoDHVO = 0;
    }

    /* Make sure the caller didn't request to read past the limit.
     * If they didn't we'll buffer till the limit, if they did, we'll
     * return an error. */
    if (QA5uE->zzV0FL.ezUX7p1.c5rRRlWB != 0 && QA5uE->zzV0FL.ezUX7p1.c5rRRlWB < QA5uE->zzV0FL.ezUX7p1.F5HHxWQ6OM7db + l3v5eCil9LaH4) {
        qNeVCw9Gz9EW = fO40kT3sMYod8;
        return 0;
    }

    /* If we don't already have all the data in the sds, read more */
    while (l3v5eCil9LaH4 > AzhbzNyG0fz(QA5uE->zzV0FL.ezUX7p1.fp_rN5CmI) - QA5uE->zzV0FL.ezUX7p1.EqRGOoDHVO) {
        c_xL dROeKQ = AzhbzNyG0fz(QA5uE->zzV0FL.ezUX7p1.fp_rN5CmI) - QA5uE->zzV0FL.ezUX7p1.EqRGOoDHVO;
        c_xL XGTOx1GK0NPB = l3v5eCil9LaH4 - dROeKQ;
        /* Read either what's missing, or PROTO_IOBUF_LEN, the bigger of
         * the two. */
        c_xL mStZjHf = XGTOx1GK0NPB < mWaTXfz ? mWaTXfz: XGTOx1GK0NPB;
        if (mStZjHf > gXGv3RBJVZnb(QA5uE->zzV0FL.ezUX7p1.fp_rN5CmI)) mStZjHf = gXGv3RBJVZnb(QA5uE->zzV0FL.ezUX7p1.fp_rN5CmI);
        if (QA5uE->zzV0FL.ezUX7p1.c5rRRlWB != 0 &&
            QA5uE->zzV0FL.ezUX7p1.F5HHxWQ6OM7db + dROeKQ + mStZjHf > QA5uE->zzV0FL.ezUX7p1.c5rRRlWB)
        {
            mStZjHf = QA5uE->zzV0FL.ezUX7p1.c5rRRlWB - QA5uE->zzV0FL.ezUX7p1.F5HHxWQ6OM7db - dROeKQ;
        }
        int XtEyLaK5 = YKn8iWFP2(QA5uE->zzV0FL.ezUX7p1.ezUX7p1,
                          (char*)QA5uE->zzV0FL.ezUX7p1.fp_rN5CmI + AzhbzNyG0fz(QA5uE->zzV0FL.ezUX7p1.fp_rN5CmI),
                          mStZjHf);
        if (XtEyLaK5 == 0) {
            return 0;
        } else if (XtEyLaK5 < 0) {
            if (RvP7Qkjcnvd(QA5uE->zzV0FL.ezUX7p1.ezUX7p1)) continue;
            if (qNeVCw9Gz9EW == pt6a) qNeVCw9Gz9EW = Y6jQkHG;
            return 0;
        }
        npPP6(QA5uE->zzV0FL.ezUX7p1.fp_rN5CmI, XtEyLaK5);
    }

    I3C2ZowCv(fp_rN5CmI, (char*)QA5uE->zzV0FL.ezUX7p1.fp_rN5CmI + QA5uE->zzV0FL.ezUX7p1.EqRGOoDHVO, l3v5eCil9LaH4);
    QA5uE->zzV0FL.ezUX7p1.F5HHxWQ6OM7db += l3v5eCil9LaH4;
    QA5uE->zzV0FL.ezUX7p1.EqRGOoDHVO += l3v5eCil9LaH4;
    return l3v5eCil9LaH4;
}

/* Returns read/write position in file. */
static R6dJA309kMEx llKY5Q_k5Y(fcshJwvJK *QA5uE) {
    return QA5uE->zzV0FL.ezUX7p1.F5HHxWQ6OM7db;
}

/* Flushes any buffer to target device if applicable. Returns 1 on success
 * and 0 on failures. */
static int fLOCppUs03ff(fcshJwvJK *QA5uE) {
    /* Our flush is implemented by the write method, that recognizes a
     * buffer set to NULL with a count of zero as a flush request. */
    return z0XK(QA5uE,o2c0vhXhUdjn,0);
}

static const fcshJwvJK Iu7QAoSKLYxRn = {
    dRcqo4KYQZk2T,
    z0XK,
    llKY5Q_k5Y,
    fLOCppUs03ff,
    o2c0vhXhUdjn,           /* update_checksum */
    0,              /* current checksum */
    0,              /* flags */
    0,              /* bytes read or written */
    0,              /* read/write chunk size */
    { { o2c0vhXhUdjn, 0 } } /* union for io-specific vars */
};

/* Create an RIO that implements a buffered read from an fd
 * read_limit argument stops buffering when the reaching the limit. */
void qlEYzVqE(fcshJwvJK *QA5uE, Ghy_K2Y *ezUX7p1, c_xL c5rRRlWB) {
    *QA5uE = Iu7QAoSKLYxRn;
    QA5uE->zzV0FL.ezUX7p1.ezUX7p1 = ezUX7p1;
    QA5uE->zzV0FL.ezUX7p1.EqRGOoDHVO = 0;
    QA5uE->zzV0FL.ezUX7p1.c5rRRlWB = c5rRRlWB;
    QA5uE->zzV0FL.ezUX7p1.F5HHxWQ6OM7db = 0;
    QA5uE->zzV0FL.ezUX7p1.fp_rN5CmI = UPH4(o2c0vhXhUdjn, mWaTXfz);
    YzmREnT(QA5uE->zzV0FL.ezUX7p1.fp_rN5CmI);
}

/* Release the RIO stream. Optionally returns the unread buffered data
 * when the SDS pointer 'remaining' is passed. */
void ARLJ(fcshJwvJK *QA5uE, uKx1Kb0Spy *hORQpWq9) {
    if (hORQpWq9 && (c_xL)QA5uE->zzV0FL.ezUX7p1.EqRGOoDHVO < AzhbzNyG0fz(QA5uE->zzV0FL.ezUX7p1.fp_rN5CmI)) {
        if (QA5uE->zzV0FL.ezUX7p1.EqRGOoDHVO > 0) dM5BePfS(QA5uE->zzV0FL.ezUX7p1.fp_rN5CmI, QA5uE->zzV0FL.ezUX7p1.EqRGOoDHVO, -1);
        *hORQpWq9 = QA5uE->zzV0FL.ezUX7p1.fp_rN5CmI;
    } else {
        Diuc(QA5uE->zzV0FL.ezUX7p1.fp_rN5CmI);
        if (hORQpWq9) *hORQpWq9 = o2c0vhXhUdjn;
    }
    QA5uE->zzV0FL.ezUX7p1.fp_rN5CmI = o2c0vhXhUdjn;
}

/* ------------------- File descriptor implementation ------------------
 * This target is used to write the RDB file to pipe, when the master just
 * streams the data to the replicas without creating an RDB on-disk image
 * (diskless replication option).
 * It only implements writes. */

/* Returns 1 or 0 for success/failure.
 *
 * When buf is NULL and len is 0, the function performs a flush operation
 * if there is some pending buffer, so this function is also used in order
 * to implement rioFdFlush(). */
static c_xL v7nMDGIcTaAS(fcshJwvJK *QA5uE, const void *fp_rN5CmI, c_xL l3v5eCil9LaH4) {
    jupvlK8BVy XtEyLaK5;
    unsigned char *ElZvdK = (unsigned char*) fp_rN5CmI;
    int pUFp = (fp_rN5CmI == o2c0vhXhUdjn && l3v5eCil9LaH4 == 0);

    /* For small writes, we rather keep the data in user-space buffer, and flush
     * it only when it grows. however for larger writes, we prefer to flush
     * any pre-existing buffer, and write the new one directly without reallocs
     * and memory copying. */
    if (l3v5eCil9LaH4 > mWaTXfz) {
        /* First, flush any pre-existing buffered data. */
        if (AzhbzNyG0fz(QA5uE->zzV0FL.Czg0.fp_rN5CmI)) {
            if (v7nMDGIcTaAS(QA5uE, o2c0vhXhUdjn, 0) == 0)
                return 0;
        }
        /* Write the new data, keeping 'p' and 'len' from the input. */
    } else {
        if (l3v5eCil9LaH4) {
            QA5uE->zzV0FL.Czg0.fp_rN5CmI = C6Sdu6MqZLze(QA5uE->zzV0FL.Czg0.fp_rN5CmI,fp_rN5CmI,l3v5eCil9LaH4);
            if (AzhbzNyG0fz(QA5uE->zzV0FL.Czg0.fp_rN5CmI) > mWaTXfz)
                pUFp = 1;
            if (!pUFp)
                return 1;
        }
        /* Flushing the buffered data. set 'p' and 'len' accordingly. */
        ElZvdK = (unsigned char*) QA5uE->zzV0FL.Czg0.fp_rN5CmI;
        l3v5eCil9LaH4 = AzhbzNyG0fz(QA5uE->zzV0FL.Czg0.fp_rN5CmI);
    }

    c_xL uEKX = 0;
    while(uEKX != l3v5eCil9LaH4) {
        XtEyLaK5 = lTeNCq(QA5uE->zzV0FL.Czg0.Czg0,ElZvdK+uEKX,l3v5eCil9LaH4-uEKX);
        if (XtEyLaK5 <= 0) {
            if (XtEyLaK5 == -1 && qNeVCw9Gz9EW == cKgG) continue;
            /* With blocking io, which is the sole user of this
             * rio target, EWOULDBLOCK is returned only because of
             * the SO_SNDTIMEO socket option, so we translate the error
             * into one more recognizable by the user. */
            if (XtEyLaK5 == -1 && qNeVCw9Gz9EW == pt6a) qNeVCw9Gz9EW = Y6jQkHG;
            return 0; /* error. */
        }
        uEKX += XtEyLaK5;
    }

    QA5uE->zzV0FL.Czg0.EqRGOoDHVO += l3v5eCil9LaH4;
    YzmREnT(QA5uE->zzV0FL.Czg0.fp_rN5CmI);
    return 1;
}

/* Returns 1 or 0 for success/failure. */
static c_xL inUDFf0I(fcshJwvJK *QA5uE, void *fp_rN5CmI, c_xL l3v5eCil9LaH4) {
    lVuqqXkT(QA5uE);
    lVuqqXkT(fp_rN5CmI);
    lVuqqXkT(l3v5eCil9LaH4);
    return 0; /* Error, this target does not support reading. */
}

/* Returns read/write position in file. */
static R6dJA309kMEx XMX0jqcNRCf(fcshJwvJK *QA5uE) {
    return QA5uE->zzV0FL.Czg0.EqRGOoDHVO;
}

/* Flushes any buffer to target device if applicable. Returns 1 on success
 * and 0 on failures. */
static int bBioBS6(fcshJwvJK *QA5uE) {
    /* Our flush is implemented by the write method, that recognizes a
     * buffer set to NULL with a count of zero as a flush request. */
    return v7nMDGIcTaAS(QA5uE,o2c0vhXhUdjn,0);
}

static const fcshJwvJK cHv7MHOOKD = {
    inUDFf0I,
    v7nMDGIcTaAS,
    XMX0jqcNRCf,
    bBioBS6,
    o2c0vhXhUdjn,           /* update_checksum */
    0,              /* current checksum */
    0,              /* flags */
    0,              /* bytes read or written */
    0,              /* read/write chunk size */
    { { o2c0vhXhUdjn, 0 } } /* union for io-specific vars */
};

void FNGxY5tgWgC(fcshJwvJK *QA5uE, int Czg0) {
    *QA5uE = cHv7MHOOKD;
    QA5uE->zzV0FL.Czg0.Czg0 = Czg0;
    QA5uE->zzV0FL.Czg0.EqRGOoDHVO = 0;
    QA5uE->zzV0FL.Czg0.fp_rN5CmI = zuow2PQ();
}

/* release the rio stream. */
void HO_MNU(fcshJwvJK *QA5uE) {
    Diuc(QA5uE->zzV0FL.Czg0.fp_rN5CmI);
}

/* ---------------------------- Generic functions ---------------------------- */

/* This function can be installed both in memory and file streams when checksum
 * computation is needed. */
void xlTDuutIT4BrR(fcshJwvJK *QA5uE, const void *fp_rN5CmI, c_xL l3v5eCil9LaH4) {
    QA5uE->lQbDW = mmTy4sZSRdS(QA5uE->lQbDW,fp_rN5CmI,l3v5eCil9LaH4);
}

/* Set the file-based rio object to auto-fsync every 'bytes' file written.
 * By default this is set to zero that means no automatic file sync is
 * performed.
 *
 * This feature is useful in a few contexts since when we rely on OS write
 * buffers sometimes the OS buffers way too much, resulting in too many
 * disk I/O concentrated in very little time. When we fsync in an explicit
 * way instead the I/O pressure is more distributed across time. */
void xw5v8k(fcshJwvJK *QA5uE, R6dJA309kMEx fJx6N) {
    if(QA5uE->lTeNCq != w5Ik3BcP7p8A.lTeNCq) return;
    QA5uE->zzV0FL.e41rPYq.JO3tdSg3NlIug = fJx6N;
}

/* Set the file-based rio object to reclaim cache after every auto-sync.
 * In the Linux implementation POSIX_FADV_DONTNEED skips the dirty
 * pages, so if auto sync is unset this option will have no effect.
 * 
 * This feature can reduce the cache footprint backed by the file. */
void lSnoth(fcshJwvJK *QA5uE, int oF5LVf2Zf) {
    QA5uE->zzV0FL.e41rPYq.VXAsR1I6U = oF5LVf2Zf;
}

/* Check the type of rio. */
dw4ioEOs2QKpZ ozs2hID(fcshJwvJK *QA5uE) {
    if (QA5uE->Jjm76CnytNtD5 == jaFv) {
        return vQlAnxrS7WTWY;
    } else if (QA5uE->Jjm76CnytNtD5 == Cn_U07o9bM) {
        return Pv49f8X3Js;
    } else if (QA5uE->Jjm76CnytNtD5 == dRcqo4KYQZk2T) {
        return SefGUas;
    } else {
        /* r->read == rioFdRead */
        return LzZe1BqqJAV;
    }
}

/* --------------------------- Higher level interface --------------------------
 *
 * The following higher level functions use lower level rio.c functions to help
 * generating the Redis protocol for the Append Only File. */

/* Write multi bulk count in the format: "*<count>\r\n". */
c_xL nOt7S1XzDSi(fcshJwvJK *QA5uE, char a9WuYVnPqa, long ZiXVo) {
    char l25ROp1TW[128];
    int OJKo1X4tcNZj;

    l25ROp1TW[0] = a9WuYVnPqa;
    OJKo1X4tcNZj = 1+MNca(l25ROp1TW+1,sizeof(l25ROp1TW)-1,ZiXVo);
    l25ROp1TW[OJKo1X4tcNZj++] = '\r';
    l25ROp1TW[OJKo1X4tcNZj++] = '\n';
    if (l79d6(QA5uE,l25ROp1TW,OJKo1X4tcNZj) == 0) return 0;
    return OJKo1X4tcNZj;
}

/* Write binary-safe string in the format: "$<count>\r\n<payload>\r\n". */
c_xL sWJ2Tze5ozZK7(fcshJwvJK *QA5uE, const char *fp_rN5CmI, c_xL l3v5eCil9LaH4) {
    c_xL uEKX;

    if ((uEKX = nOt7S1XzDSi(QA5uE,'$',l3v5eCil9LaH4)) == 0) return 0;
    if (l3v5eCil9LaH4 > 0 && l79d6(QA5uE,fp_rN5CmI,l3v5eCil9LaH4) == 0) return 0;
    if (l79d6(QA5uE,"\r\n",2) == 0) return 0;
    return uEKX+l3v5eCil9LaH4+2;
}

/* Write a long long value in format: "$<count>\r\n<payload>\r\n". */
c_xL m8AmLXvG(fcshJwvJK *QA5uE, long long Hx6RXD4sMT) {
    char j57L_gsBTgp[32];
    unsigned int PGGNBzEt;

    PGGNBzEt = MNca(j57L_gsBTgp,sizeof(j57L_gsBTgp),Hx6RXD4sMT);
    return sWJ2Tze5ozZK7(QA5uE,j57L_gsBTgp,PGGNBzEt);
}

/* Write a double value in the format: "$<count>\r\n<payload>\r\n" */
c_xL MljGK(fcshJwvJK *QA5uE, double NS2ibhk7dOD7) {
    char w1Ovs[128];
    unsigned int HzGHfua;
    HzGHfua = XtmDsH(NS2ibhk7dOD7, w1Ovs);
    w1Ovs[HzGHfua] = '\0';
    return sWJ2Tze5ozZK7(QA5uE,w1Ovs,HzGHfua);
}
