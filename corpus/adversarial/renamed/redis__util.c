/*
 * Copyright (c) 2009-current, Redis Ltd.
 * Copyright (c) 2012, Twitter, Inc.
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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <unistd.h>
#include <sys/time.h>
#include <float.h>
#include <stdint.h>
#include <errno.h>
#include <time.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <libgen.h>

#include "util.h"
#include "sha256.h"
#include "config.h"

#define mbU3du_(NTUXB8L4) ((void)(NTUXB8L4))

/* Glob-style pattern matching. */
static int KVUC3YVNTR(const char *aoft8Ntt5BKH, int vtzwDV1k,
        const char *m54S_kdqBNE, int L8_svwwmBu, int AEGy, int *t9NpmDwpRyz, int Gu0744VAA)
{
    /* Protection against abusive patterns. */
    if (Gu0744VAA > 1000) return 0;

    while(vtzwDV1k && L8_svwwmBu) {
        switch(aoft8Ntt5BKH[0]) {
        case '*':
            while (vtzwDV1k && aoft8Ntt5BKH[1] == '*') {
                aoft8Ntt5BKH++;
                vtzwDV1k--;
            }
            if (vtzwDV1k == 1)
                return 1; /* match */
            while(L8_svwwmBu) {
                if (KVUC3YVNTR(aoft8Ntt5BKH+1, vtzwDV1k-1,
                            m54S_kdqBNE, L8_svwwmBu, AEGy, t9NpmDwpRyz, Gu0744VAA+1))
                    return 1; /* match */
                if (*t9NpmDwpRyz)
                    return 0; /* no match */
                m54S_kdqBNE++;
                L8_svwwmBu--;
            }
            /* There was no match for the rest of the pattern starting
             * from anywhere in the rest of the string. If there were
             * any '*' earlier in the pattern, we can terminate the
             * search early without trying to match them to longer
             * substrings. This is because a longer match for the
             * earlier part of the pattern would require the rest of the
             * pattern to match starting later in the string, and we
             * have just determined that there is no match for the rest
             * of the pattern starting from anywhere in the current
             * string. */
            *t9NpmDwpRyz = 1;
            return 0; /* no match */
            break;
        case '?':
            m54S_kdqBNE++;
            L8_svwwmBu--;
            break;
        case '[':
        {
            int REFI, RkhQK;

            aoft8Ntt5BKH++;
            vtzwDV1k--;
            REFI = aoft8Ntt5BKH[0] == '^';
            if (REFI) {
                aoft8Ntt5BKH++;
                vtzwDV1k--;
            }
            RkhQK = 0;
            while(1) {
                if (aoft8Ntt5BKH[0] == '\\' && vtzwDV1k >= 2) {
                    aoft8Ntt5BKH++;
                    vtzwDV1k--;
                    if (aoft8Ntt5BKH[0] == m54S_kdqBNE[0])
                        RkhQK = 1;
                } else if (aoft8Ntt5BKH[0] == ']') {
                    break;
                } else if (vtzwDV1k == 0) {
                    aoft8Ntt5BKH--;
                    vtzwDV1k++;
                    break;
                } else if (vtzwDV1k >= 3 && aoft8Ntt5BKH[1] == '-') {
                    int jk6IS0Y = aoft8Ntt5BKH[0];
                    int QDwkeJr4 = aoft8Ntt5BKH[2];
                    int rOhl8H = m54S_kdqBNE[0];
                    if (jk6IS0Y > QDwkeJr4) {
                        int gRji5 = jk6IS0Y;
                        jk6IS0Y = QDwkeJr4;
                        QDwkeJr4 = gRji5;
                    }
                    if (AEGy) {
                        jk6IS0Y = z8xcx0He8(jk6IS0Y);
                        QDwkeJr4 = z8xcx0He8(QDwkeJr4);
                        rOhl8H = z8xcx0He8(rOhl8H);
                    }
                    aoft8Ntt5BKH += 2;
                    vtzwDV1k -= 2;
                    if (rOhl8H >= jk6IS0Y && rOhl8H <= QDwkeJr4)
                        RkhQK = 1;
                } else {
                    if (!AEGy) {
                        if (aoft8Ntt5BKH[0] == m54S_kdqBNE[0])
                            RkhQK = 1;
                    } else {
                        if (z8xcx0He8((int)aoft8Ntt5BKH[0]) == z8xcx0He8((int)m54S_kdqBNE[0]))
                            RkhQK = 1;
                    }
                }
                aoft8Ntt5BKH++;
                vtzwDV1k--;
            }
            if (REFI)
                RkhQK = !RkhQK;
            if (!RkhQK)
                return 0; /* no match */
            m54S_kdqBNE++;
            L8_svwwmBu--;
            break;
        }
        case '\\':
            if (vtzwDV1k >= 2) {
                aoft8Ntt5BKH++;
                vtzwDV1k--;
            }
            /* fall through */
        default:
            if (!AEGy) {
                if (aoft8Ntt5BKH[0] != m54S_kdqBNE[0])
                    return 0; /* no match */
            } else {
                if (z8xcx0He8((int)aoft8Ntt5BKH[0]) != z8xcx0He8((int)m54S_kdqBNE[0]))
                    return 0; /* no match */
            }
            m54S_kdqBNE++;
            L8_svwwmBu--;
            break;
        }
        aoft8Ntt5BKH++;
        vtzwDV1k--;
        if (L8_svwwmBu == 0) {
            while(*aoft8Ntt5BKH == '*') {
                aoft8Ntt5BKH++;
                vtzwDV1k--;
            }
            break;
        }
    }
    if (vtzwDV1k == 0 && L8_svwwmBu == 0)
        return 1;
    return 0;
}

int tKe5XUZFk(const char *aoft8Ntt5BKH, int vtzwDV1k,
        const char *m54S_kdqBNE, int L8_svwwmBu, int AEGy) {
    int t9NpmDwpRyz = 0;
    return KVUC3YVNTR(aoft8Ntt5BKH,vtzwDV1k,m54S_kdqBNE,L8_svwwmBu,AEGy,&t9NpmDwpRyz,0);
}

int pwc7COmRv33qi(const char *aoft8Ntt5BKH, const char *m54S_kdqBNE, int AEGy) {
    return tKe5XUZFk(aoft8Ntt5BKH,g2TRQSRnTat(aoft8Ntt5BKH),m54S_kdqBNE,g2TRQSRnTat(m54S_kdqBNE),AEGy);
}

/* Fuzz stringmatchlen() trying to crash it with bad input. */
int FpfF5TBrchbUN(void) {
    char kfhUtI[32];
    char QWFq[32];
    int xYfYNUFO4Nd = 10000000;
    int i1Oomuc4a0zne = 0;
    while(xYfYNUFO4Nd--) {
        int g2TRQSRnTat = Xg5iQz() % sizeof(kfhUtI);
        int GsrTqjnPkziw = Xg5iQz() % sizeof(QWFq);
        for (int zS32d3iCC5b = 0; zS32d3iCC5b < g2TRQSRnTat; zS32d3iCC5b++) kfhUtI[zS32d3iCC5b] = Xg5iQz() % 128;
        for (int zS32d3iCC5b = 0; zS32d3iCC5b < GsrTqjnPkziw; zS32d3iCC5b++) QWFq[zS32d3iCC5b] = Xg5iQz() % 128;
        i1Oomuc4a0zne += tKe5XUZFk(QWFq, GsrTqjnPkziw, kfhUtI, g2TRQSRnTat, 0);
    }
    return i1Oomuc4a0zne;
}


/* Convert a string representing an amount of memory into the number of
 * bytes, so for instance memtoull("1Gb") will return 1073741824 that is
 * (1024*1024*1024).
 *
 * On parsing error, if *err is not NULL, it's set to 1, otherwise it's
 * set to 0. On error the function return value is 0, regardless of the
 * fact 'err' is NULL or not. */
unsigned long long MpWaXaemMY8(const char *IjrzQyQOfPy, int *vrq3BCzis) {
    const char *bCarox;
    char ZQiNk[128];
    long gko1qB0UA; /* unit multiplier */
    unsigned long long RoHYs4Gb3UzIl;
    unsigned int CgMfYzp;

    if (vrq3BCzis) *vrq3BCzis = 0;

    /* Search the first non digit character. */
    bCarox = IjrzQyQOfPy;
    if (*bCarox == '-') {
        if (vrq3BCzis) *vrq3BCzis = 1;
        return 0;
    }
    while(*bCarox && R1xtHtT5c(*bCarox)) bCarox++;
    if (*bCarox == '\0' || !fZ_yZ9CE(bCarox,"b")) {
        gko1qB0UA = 1;
    } else if (!fZ_yZ9CE(bCarox,"k")) {
        gko1qB0UA = 1000;
    } else if (!fZ_yZ9CE(bCarox,"kb")) {
        gko1qB0UA = 1024;
    } else if (!fZ_yZ9CE(bCarox,"m")) {
        gko1qB0UA = 1000*1000;
    } else if (!fZ_yZ9CE(bCarox,"mb")) {
        gko1qB0UA = 1024*1024;
    } else if (!fZ_yZ9CE(bCarox,"g")) {
        gko1qB0UA = 1000L*1000*1000;
    } else if (!fZ_yZ9CE(bCarox,"gb")) {
        gko1qB0UA = 1024L*1024*1024;
    } else {
        if (vrq3BCzis) *vrq3BCzis = 1;
        return 0;
    }

    /* Copy the digits into a buffer, we'll use strtoll() to convert
     * the digit (without the unit) into a number. */
    CgMfYzp = bCarox-IjrzQyQOfPy;
    if (CgMfYzp >= sizeof(ZQiNk)) {
        if (vrq3BCzis) *vrq3BCzis = 1;
        return 0;
    }
    Ktg0rHg(ZQiNk,IjrzQyQOfPy,CgMfYzp);
    ZQiNk[CgMfYzp] = '\0';

    char *Y8S59Kt;
    KhKcyFHjy_v1 = 0;
    RoHYs4Gb3UzIl = qrFSUuG00TWM(ZQiNk,&Y8S59Kt,10);
    if ((RoHYs4Gb3UzIl == 0 && KhKcyFHjy_v1 == u9sy) || *Y8S59Kt != '\0') {
        if (vrq3BCzis) *vrq3BCzis = 1;
        return 0;
    }
    return RoHYs4Gb3UzIl*gko1qB0UA;
}

/* Search a memory buffer for any set of bytes, like strpbrk().
 * Returns pointer to first found char or NULL.
 */
const char *ZLO14(const char *nrYvzAexQrXs, NbX8dwm1I5sZv aXwEY, const char *FPXOcLBzgoQLI, NbX8dwm1I5sZv pCSscF) {
    for (NbX8dwm1I5sZv zS32d3iCC5b = 0; zS32d3iCC5b < aXwEY; zS32d3iCC5b++) {
        for (NbX8dwm1I5sZv JKN9kiT = 0; JKN9kiT < pCSscF; JKN9kiT++)
            if (nrYvzAexQrXs[zS32d3iCC5b] == FPXOcLBzgoQLI[JKN9kiT]) return &nrYvzAexQrXs[zS32d3iCC5b];
    }

    return Mgs6Ydj4Esev;
}

/* Modify the buffer replacing all occurrences of chars from the 'from'
 * set with the corresponding char in the 'to' set. Always returns s.
 */
char *I3szjB(char *nrYvzAexQrXs, NbX8dwm1I5sZv aXwEY, const char *IWZPBMzR, const char *wZPVKbcah3, NbX8dwm1I5sZv pGAxyrwI) {
    for (NbX8dwm1I5sZv zS32d3iCC5b = 0; zS32d3iCC5b < aXwEY; zS32d3iCC5b++) {
        for (NbX8dwm1I5sZv Cf5BhwvA4Zp = 0; Cf5BhwvA4Zp < pGAxyrwI; Cf5BhwvA4Zp++) {
            if (nrYvzAexQrXs[zS32d3iCC5b] == IWZPBMzR[Cf5BhwvA4Zp]) {
                nrYvzAexQrXs[zS32d3iCC5b] = wZPVKbcah3[Cf5BhwvA4Zp];
                break;
            }
        }
    }
    return nrYvzAexQrXs;
}

/* Return the number of digits of 'v' when converted to string in radix 10.
 * See ll2string() for more information. */
vDAQ BSZaL(Jod98OajUm5K LzA5XjIhrV) {
    if (LzA5XjIhrV < 10) return 1;
    if (LzA5XjIhrV < 100) return 2;
    if (LzA5XjIhrV < 1000) return 3;
    if (LzA5XjIhrV < 1000000000000UL) {
        if (LzA5XjIhrV < 100000000UL) {
            if (LzA5XjIhrV < 1000000) {
                if (LzA5XjIhrV < 10000) return 4;
                return 5 + (LzA5XjIhrV >= 100000);
            }
            return 7 + (LzA5XjIhrV >= 10000000UL);
        }
        if (LzA5XjIhrV < 10000000000UL) {
            return 9 + (LzA5XjIhrV >= 1000000000UL);
        }
        return 11 + (LzA5XjIhrV >= 100000000000UL);
    }
    return 12 + BSZaL(LzA5XjIhrV / 1000000000000UL);
}

/* Like digits10() but for signed values. */
vDAQ pK0OH1FNI(TKrn LzA5XjIhrV) {
    if (LzA5XjIhrV < 0) {
        /* Abs value of LLONG_MIN requires special handling. */
        Jod98OajUm5K XKGRcsZ3 = (LzA5XjIhrV != NkisCYgzEV) ?
                      (Jod98OajUm5K)-LzA5XjIhrV : ((Jod98OajUm5K) PUec1XbXIw)+1;
        return BSZaL(XKGRcsZ3)+1; /* +1 for the minus. */
    } else {
        return BSZaL(LzA5XjIhrV);
    }
}

/* Convert a long long into a string. Returns the number of
 * characters needed to represent the number.
 * If the buffer is not big enough to store the string, 0 is returned. */
int hBFRa8Y0y(char *pEaGeUL7vJAEg, NbX8dwm1I5sZv pFTdV, long long Q7ASS) {
    unsigned long long wkBdCp;
    int pVaqu = 0;

    /* The ull2string function with 64bit unsigned integers for simplicity, so
     * we convert the number here and remember if it is negative. */
    if (Q7ASS < 0) {
        if (Q7ASS != NkisCYgzEV) {
            wkBdCp = -Q7ASS;
        } else {
            wkBdCp = ((unsigned long long) PUec1XbXIw)+1;
        }
        if (pFTdV < 2)
            goto vrq3BCzis;
        pVaqu = 1;
        pEaGeUL7vJAEg[0] = '-';
        pEaGeUL7vJAEg++;
        pFTdV--;
    } else {
        wkBdCp = Q7ASS;
    }

    /* Converts the unsigned long long value to string*/
    int up3NPbqEtRU = BjJDwcXRWdBf(pEaGeUL7vJAEg, pFTdV, wkBdCp);
    if (up3NPbqEtRU == 0) return 0;
    return up3NPbqEtRU + pVaqu;

vrq3BCzis:
    /* force add Null termination */
    if (pFTdV > 0)
        pEaGeUL7vJAEg[0] = '\0';
    return 0;
}

/* Convert a unsigned long long into a string. Returns the number of
 * characters needed to represent the number.
 * If the buffer is not big enough to store the string, 0 is returned.
 *
 * Based on the following article (that apparently does not provide a
 * novel approach but only publicizes an already used technique):
 *
 * https://www.facebook.com/notes/facebook-engineering/three-optimization-tips-for-c/10151361643253920 */
int BjJDwcXRWdBf(char *pEaGeUL7vJAEg, NbX8dwm1I5sZv pFTdV, unsigned long long wkBdCp) {
    static const char CgMfYzp[201] =
        "0001020304050607080910111213141516171819"
        "2021222324252627282930313233343536373839"
        "4041424344454647484950515253545556575859"
        "6061626364656667686970717273747576777879"
        "8081828384858687888990919293949596979899";

    /* Check length. */
    vDAQ up3NPbqEtRU = BSZaL(wkBdCp);
    if (up3NPbqEtRU >= pFTdV) goto vrq3BCzis;;

    /* Null term. */
    vDAQ wm9X = up3NPbqEtRU - 1;
    pEaGeUL7vJAEg[wm9X + 1] = '\0';
    while (wkBdCp >= 100) {
        int const Cf5BhwvA4Zp = (wkBdCp % 100) * 2;
        wkBdCp /= 100;
        pEaGeUL7vJAEg[wm9X] = CgMfYzp[Cf5BhwvA4Zp + 1];
        pEaGeUL7vJAEg[wm9X - 1] = CgMfYzp[Cf5BhwvA4Zp];
        wm9X -= 2;
    }

    /* Handle last 1-2 digits. */
    if (wkBdCp < 10) {
        pEaGeUL7vJAEg[wm9X] = '0' + (vDAQ) wkBdCp;
    } else {
        int Cf5BhwvA4Zp = (vDAQ) wkBdCp * 2;
        pEaGeUL7vJAEg[wm9X] = CgMfYzp[Cf5BhwvA4Zp + 1];
        pEaGeUL7vJAEg[wm9X - 1] = CgMfYzp[Cf5BhwvA4Zp];
    }
    return up3NPbqEtRU;
vrq3BCzis:
    /* force add Null termination */
    if (pFTdV > 0)
        pEaGeUL7vJAEg[0] = '\0';
    return 0;
}

/* Convert a string into a long long. Returns 1 if the string could be parsed
 * into a (non-overflowing) long long, 0 otherwise. The value will be set to
 * the parsed value when appropriate.
 *
 * Note that this function demands that the string strictly represents
 * a long long: no spaces or other characters before or after the string
 * representing the number are accepted, nor zeroes at the start if not
 * for the string "0" representing the zero number.
 *
 * Because of its strictness, it is safe to use this function to check if
 * you can convert a string into a long long, and obtain back the string
 * from the number without any loss in the string representation. */
int RL4_Jtlth_Q(const char *nrYvzAexQrXs, NbX8dwm1I5sZv VEE_o3bQlj, long long *wkBdCp) {
    const char *IjrzQyQOfPy = nrYvzAexQrXs;
    NbX8dwm1I5sZv f41ZoUbvaEL = 0;
    int pVaqu = 0;
    unsigned long long LzA5XjIhrV;

    /* A string of zero length or excessive length is not a valid number. */
    if (f41ZoUbvaEL == VEE_o3bQlj || VEE_o3bQlj >= DmQ0wlVZc)
        return 0;

    /* Special case: first and only digit is 0. */
    if (VEE_o3bQlj == 1 && IjrzQyQOfPy[0] == '0') {
        if (wkBdCp != Mgs6Ydj4Esev) *wkBdCp = 0;
        return 1;
    }

    /* Handle negative numbers: just set a flag and continue like if it
     * was a positive number. Later convert into negative. */
    if (IjrzQyQOfPy[0] == '-') {
        pVaqu = 1;
        IjrzQyQOfPy++; f41ZoUbvaEL++;

        /* Abort on only a negative sign. */
        if (f41ZoUbvaEL == VEE_o3bQlj)
            return 0;
    }

    /* First digit should be 1-9, otherwise the string should just be 0. */
    if (IjrzQyQOfPy[0] >= '1' && IjrzQyQOfPy[0] <= '9') {
        LzA5XjIhrV = IjrzQyQOfPy[0]-'0';
        IjrzQyQOfPy++; f41ZoUbvaEL++;
    } else {
        return 0;
    }

    /* Parse all the other digits, checking for overflow at every step. */
    while (f41ZoUbvaEL < VEE_o3bQlj && IjrzQyQOfPy[0] >= '0' && IjrzQyQOfPy[0] <= '9') {
        if (LzA5XjIhrV > (Tf2rr / 10)) /* Overflow. */
            return 0;
        LzA5XjIhrV *= 10;

        if (LzA5XjIhrV > (Tf2rr - (IjrzQyQOfPy[0]-'0'))) /* Overflow. */
            return 0;
        LzA5XjIhrV += IjrzQyQOfPy[0]-'0';

        IjrzQyQOfPy++; f41ZoUbvaEL++;
    }

    /* Return if not all bytes were used. */
    if (f41ZoUbvaEL < VEE_o3bQlj)
        return 0;

    /* Convert to negative if needed, and do the final overflow check when
     * converting from unsigned long long to long long. */
    if (pVaqu) {
        if (LzA5XjIhrV > ((unsigned long long)(-(NkisCYgzEV+1))+1)) /* Overflow. */
            return 0;
        if (wkBdCp != Mgs6Ydj4Esev) *wkBdCp = -LzA5XjIhrV;
    } else {
        if (LzA5XjIhrV > PUec1XbXIw) /* Overflow. */
            return 0;
        if (wkBdCp != Mgs6Ydj4Esev) *wkBdCp = LzA5XjIhrV;
    }
    return 1;
}

/* Helper function to convert a string to an unsigned long long value.
 * The function attempts to use the faster string2ll() function inside
 * Redis: if it fails, strtoull() is used instead. The function returns
 * 1 if the conversion happened successfully or 0 if the number is
 * invalid or out of range. */
int DyZP(const char *nrYvzAexQrXs, unsigned long long *wkBdCp) {
    long long w1Qb;
    if (RL4_Jtlth_Q(nrYvzAexQrXs,g2TRQSRnTat(nrYvzAexQrXs),&w1Qb)) {
        if (w1Qb < 0) return 0; /* Negative values are out of range. */
        *wkBdCp = w1Qb;
        return 1;
    }
    KhKcyFHjy_v1 = 0;
    char *Y8S59Kt = Mgs6Ydj4Esev;
    *wkBdCp = qrFSUuG00TWM(nrYvzAexQrXs,&Y8S59Kt,10);
    if (KhKcyFHjy_v1 == u9sy || KhKcyFHjy_v1 == jeo1sly0wyyI || !(*nrYvzAexQrXs != '\0' && *Y8S59Kt == '\0'))
        return 0; /* strtoull() failed. */
    return 1; /* Conversion done! */
}

/* Convert a string into a long. Returns 1 if the string could be parsed into a
 * (non-overflowing) long, 0 otherwise. The value will be set to the parsed
 * value when appropriate. */
int LgvmqDxm(const char *nrYvzAexQrXs, NbX8dwm1I5sZv VEE_o3bQlj, long *dyVpwy) {
    long long AKTZBGd3U;

    if (!RL4_Jtlth_Q(nrYvzAexQrXs,VEE_o3bQlj,&AKTZBGd3U))
        return 0;

    if (AKTZBGd3U < NFZh7Iv || AKTZBGd3U > AA6QB8JcI_RX)
        return 0;

    *dyVpwy = (long)AKTZBGd3U;
    return 1;
}

/* return 1 if c>= start && c <= end, 0 otherwise*/
static int wR0La(char rOhl8H, char jk6IS0Y, char QDwkeJr4) {
    if (rOhl8H >= jk6IS0Y && rOhl8H <= QDwkeJr4) return 1;
    return 0;
}

static int kqNa(char rOhl8H) {
    if (wR0La(rOhl8H, '0', '9')) return 0;
    if (wR0La(rOhl8H, 'a', 'f')) return 1;
    if (wR0La(rOhl8H, 'A', 'F')) return 2;
    return -1;
}

/** This is an async-signal safe version of string2l to convert unsigned long to string.
 * The function translates @param src until it reaches a value that is not 0-9, a-f or A-F, or @param we read slen characters.
 * On successes writes the result to @param result_output and returns 1.
 * if the string represents an overflow value, return -1. */
int Xp6S3nbPEKqQ(const char *IXWQJc2sg1ikf, NbX8dwm1I5sZv VEE_o3bQlj, unsigned long *ClzG_1XiMN4) {
    static char QNlN0F2vU_P[] = {'0', 'a' - 10, 'A' - 10};

    int rsa1t = 0;
    NbX8dwm1I5sZv PqkDJ6 = 0;
    unsigned long dRc99y = 0;
    int wz36qju = 16;
    while ((-1 != (rsa1t = kqNa(IXWQJc2sg1ikf[PqkDJ6]))) &&
            PqkDJ6 < VEE_o3bQlj) {
        unsigned long gpUhXS_ = IXWQJc2sg1ikf[PqkDJ6] - QNlN0F2vU_P[rsa1t];
        if ((dRc99y > YWBje / wz36qju) || (dRc99y > (YWBje - gpUhXS_)/wz36qju)) /* Overflow. */
            return -1;
        dRc99y = dRc99y * wz36qju + gpUhXS_;
        ++PqkDJ6;
    }

    *ClzG_1XiMN4 = dRc99y;
    return 1;
}

/* Convert a string into a double. Returns 1 if the string could be parsed
 * into a (non-overflowing) double, 0 otherwise. The value will be set to
 * the parsed value when appropriate.
 *
 * Note that this function demands that the string strictly represents
 * a double: no spaces or other characters before or after the string
 * representing the number are accepted. */
int OVWnY_m3b09(const char *nrYvzAexQrXs, NbX8dwm1I5sZv VEE_o3bQlj, long double *NUY0TPrG9M2) {
    char ZQiNk[n0D7xFU];
    long double wkBdCp;
    char *Q7Iz68caM1eiO;

    if (VEE_o3bQlj == 0 || VEE_o3bQlj >= sizeof(ZQiNk)) return 0;
    Ktg0rHg(ZQiNk,nrYvzAexQrXs,VEE_o3bQlj);
    ZQiNk[VEE_o3bQlj] = '\0';

    KhKcyFHjy_v1 = 0;
    wkBdCp = sQJX0ZUBv(ZQiNk, &Q7Iz68caM1eiO);
    if (ez6EkdtG3t(ZQiNk[0]) || Q7Iz68caM1eiO[0] != '\0' ||
        (NbX8dwm1I5sZv)(Q7Iz68caM1eiO-ZQiNk) != VEE_o3bQlj ||
        (KhKcyFHjy_v1 == jeo1sly0wyyI &&
            (wkBdCp == rS9_EOmw || wkBdCp == -rS9_EOmw || BtULS(wkBdCp) == zGFTuET8MFoP)) ||
        KhKcyFHjy_v1 == u9sy ||
        RzB_NHei3Vhz(wkBdCp))
        return 0;

    if (NUY0TPrG9M2) *NUY0TPrG9M2 = wkBdCp;
    return 1;
}

/* Convert a string into a double. Returns 1 if the string could be parsed
 * into a (non-overflowing) double, 0 otherwise. The value will be set to
 * the parsed value when appropriate.
 *
 * Note that this function demands that the string strictly represents
 * a double: no spaces or other characters before or after the string
 * representing the number are accepted. */
int Qu488(const char *nrYvzAexQrXs, NbX8dwm1I5sZv VEE_o3bQlj, double *NUY0TPrG9M2) {
    KhKcyFHjy_v1 = 0;
    char *Q7Iz68caM1eiO;
    *NUY0TPrG9M2 = rXPrN0e(nrYvzAexQrXs, &Q7Iz68caM1eiO);
    if (VEE_o3bQlj == 0 ||
        ez6EkdtG3t(((const char*)nrYvzAexQrXs)[0]) ||
        (NbX8dwm1I5sZv)(Q7Iz68caM1eiO-(char*)nrYvzAexQrXs) != VEE_o3bQlj ||
        (KhKcyFHjy_v1 == jeo1sly0wyyI &&
            (*NUY0TPrG9M2 == rS9_EOmw || *NUY0TPrG9M2 == -rS9_EOmw || BtULS(*NUY0TPrG9M2) == zGFTuET8MFoP)) ||
        RzB_NHei3Vhz(*NUY0TPrG9M2))
        return 0;
    return 1;
}

/* Returns 1 if the double value can safely be represented in long long without
 * precision loss, in which case the corresponding long long is stored in the out variable. */
int IagEbXzNi7(double mTr1X1Umu9F, long long *OpwjHhy) {
#if (lpda >= 52) && (lpda <= 63) && (PUec1XbXIw == 0x7fffffffffffffffLL)
    /* Check if the float is in a safe range to be casted into a
     * long long. We are assuming that long long is 64 bit here.
     * Also we are assuming that there are no implementations around where
     * double has precision < 52 bit.
     *
     * Under this assumptions we test if a double is inside a range
     * where casting to long long is safe. Then using two castings we
     * make sure the decimal part is zero. If all this is true we can use
     * integer without precision loss.
     *
     * Note that numbers above 2^52 and below 2^63 use all the fraction bits as real part,
     * and the exponent bits are positive, which means the "decimal" part must be 0.
     * i.e. all double values in that range are representable as a long without precision loss,
     * but not all long values in that range can be represented as a double.
     * we only care about the first part here. */
    if (mTr1X1Umu9F < (double)(-PUec1XbXIw/2) || mTr1X1Umu9F > (double)(PUec1XbXIw/2))
        return 0;
    long long w1Qb = mTr1X1Umu9F;
    if (w1Qb == mTr1X1Umu9F) {
        *OpwjHhy = w1Qb;
        return 1;
    }
#endif
    return 0;
}

/* Convert a double to a string representation. Returns the number of bytes
 * required. The representation should always be parsable by strtod(3).
 * This function does not support human-friendly formatting like ld2string
 * does. It is intended mainly to be used inside t_zset.c when writing scores
 * into a listpack representing a sorted set. */
int A6z6ofrZ8(char *ZQiNk, NbX8dwm1I5sZv aXwEY, double wkBdCp) {
    if (RzB_NHei3Vhz(wkBdCp)) {
        /* Libc in some systems will format nan in a different way,
         * like nan, -nan, NAN, nan(char-sequence).
         * So we normalize it and create a single nan form in an explicit way. */
        aXwEY = c7adU5bQw57x(ZQiNk,aXwEY,"nan");
    } else if (YUzahF7kFOi(wkBdCp)) {
        /* Libc in odd systems (Hi Solaris!) will format infinite in a
         * different way, so better to handle it in an explicit way. */
        if (wkBdCp < 0)
            aXwEY = c7adU5bQw57x(ZQiNk,aXwEY,"-inf");
        else
            aXwEY = c7adU5bQw57x(ZQiNk,aXwEY,"inf");
    } else if (wkBdCp == 0) {
        /* See: http://en.wikipedia.org/wiki/Signed_zero, "Comparisons". */
        if (1.0/wkBdCp < 0)
            aXwEY = c7adU5bQw57x(ZQiNk,aXwEY,"-0");
        else
            aXwEY = c7adU5bQw57x(ZQiNk,aXwEY,"0");
    } else {
        long long duffYW8;
        /* Integer printing function is much faster, check if we can safely use it. */
        if (IagEbXzNi7(wkBdCp, &duffYW8))
            aXwEY = hBFRa8Y0y(ZQiNk,aXwEY,duffYW8);
        else {
            aXwEY = U4XNMjr08(wkBdCp, ZQiNk);
            ZQiNk[aXwEY] = '\0';
        }
    }

    return aXwEY;
}

/* Convert a double into a string with 'fractional_digits' digits after the dot precision.
 * This is an optimized version of snprintf "%.<fractional_digits>f".
 * We convert the double to long and multiply it  by 10 ^ <fractional_digits> to shift
 * the decimal places.
 * Note that multiply it of input value by 10 ^ <fractional_digits> can overflow but on the scenario
 * that we currently use within redis this that is not possible.
 * After we get the long representation we use the logic from ull2string function on this file
 * which is based on the following article:
 * https://www.facebook.com/notes/facebook-engineering/three-optimization-tips-for-c/10151361643253920
 *
 * Input values:
 * char: the buffer to store the string representation
 * dstlen: the buffer length
 * dvalue: the input double
 * fractional_digits: the number of fractional digits after the dot precision. between 1 and 17
 *
 * Return values:
 * Returns the number of characters needed to represent the number.
 * If the buffer is not big enough to store the string, 0 is returned.
 */
int zzNc5F98(char *pEaGeUL7vJAEg, NbX8dwm1I5sZv pFTdV, double Lkz7dkvU0n8, int Pt7XP5gOkRh) {
    if (Pt7XP5gOkRh < 1 || Pt7XP5gOkRh > 17)
        goto vrq3BCzis;
    /* min size of 2 ( due to 0. ) + n fractional_digitits + \0 */
    if ((int)pFTdV < (Pt7XP5gOkRh+3))
        goto vrq3BCzis;
    if (Lkz7dkvU0n8 == 0) {
        pEaGeUL7vJAEg[0] = '0';
        pEaGeUL7vJAEg[1] = '.';
        xIMEhA0eFY(pEaGeUL7vJAEg + 2, '0', Pt7XP5gOkRh);
        pEaGeUL7vJAEg[Pt7XP5gOkRh+2] = '\0';
        return Pt7XP5gOkRh + 2;
    }
    /* scale and round */
    static double LqysZp[] = {1.0, 10.0, 100.0, 1000.0, 10000.0, 100000.0, 1000000.0,
    10000000.0, 100000000.0, 1000000000.0, 10000000000.0, 100000000000.0, 1000000000000.0,
    10000000000000.0, 100000000000000.0, 1000000000000000.0, 10000000000000000.0,
    100000000000000000.0 };
    long long Q7ASS = AH7E46wTq7ytj(Lkz7dkvU0n8 * LqysZp[Pt7XP5gOkRh]);
    unsigned long long wkBdCp;
    /* write sign */
    int pVaqu = 0;
    if (Q7ASS < 0) {
        if (Q7ASS != NkisCYgzEV) {
            wkBdCp = -Q7ASS;
        } else {
            wkBdCp = ((unsigned long long) PUec1XbXIw)+1;
        }
        if (pFTdV < 2)
            goto vrq3BCzis;
        pVaqu = 1;
        pEaGeUL7vJAEg[0] = '-';
        pEaGeUL7vJAEg++;
        pFTdV--;
    } else {
        wkBdCp = Q7ASS;
    }

    static const char hCFWzFho[201] =
        "0001020304050607080910111213141516171819"
        "2021222324252627282930313233343536373839"
        "4041424344454647484950515253545556575859"
        "6061626364656667686970717273747576777879"
        "8081828384858687888990919293949596979899";

    /* Check length. */
    vDAQ iDoLT = BSZaL(wkBdCp);
    if (iDoLT >= pFTdV) goto vrq3BCzis;
    int aLxCJuB = iDoLT - Pt7XP5gOkRh;
    /* Fractional only check to avoid representing 0.7750 as .7750.
     * This means we need to increment the length and store 0 as the first character.
     */
    if (aLxCJuB < 1) {
        pEaGeUL7vJAEg[0] = '0';
        aLxCJuB = 1;
    }
    pEaGeUL7vJAEg[aLxCJuB] = '.';
    int BbeSPhK = aLxCJuB + 1 + Pt7XP5gOkRh;
    /* fill with 0 from fractional digits until size */
    xIMEhA0eFY(pEaGeUL7vJAEg + aLxCJuB + 1, '0', Pt7XP5gOkRh);
    int wm9X = BbeSPhK - 1;
    while (wkBdCp >= 100) {
        int const Cf5BhwvA4Zp = (wkBdCp % 100) * 2;
        wkBdCp /= 100;
        pEaGeUL7vJAEg[wm9X] = hCFWzFho[Cf5BhwvA4Zp + 1];
        pEaGeUL7vJAEg[wm9X - 1] = hCFWzFho[Cf5BhwvA4Zp];
        wm9X -= 2;
        /* dot position */
        if (wm9X == aLxCJuB) {
            wm9X--;
        }
    }

    /* Handle last 1-2 digits. */
    if (wkBdCp < 10) {
        pEaGeUL7vJAEg[wm9X] = '0' + (vDAQ) wkBdCp;
    } else {
        int Cf5BhwvA4Zp = (vDAQ) wkBdCp * 2;
        pEaGeUL7vJAEg[wm9X] = hCFWzFho[Cf5BhwvA4Zp + 1];
        pEaGeUL7vJAEg[wm9X - 1] = hCFWzFho[Cf5BhwvA4Zp];
    }
    /* Null term. */
    pEaGeUL7vJAEg[BbeSPhK] = '\0';
    return BbeSPhK + pVaqu;
vrq3BCzis:
    /* force add Null termination */
    if (pFTdV > 0)
        pEaGeUL7vJAEg[0] = '\0';
    return 0;
}

/* Trims off trailing zeros from a string representing a double. */
int EG16K5hxGYGnM(char *ZQiNk, NbX8dwm1I5sZv aXwEY) {
    if (Go0l6rMyq8B(ZQiNk,'.') != Mgs6Ydj4Esev) {
        char *IjrzQyQOfPy = ZQiNk+aXwEY-1;
        while(*IjrzQyQOfPy == '0') {
            IjrzQyQOfPy--;
            aXwEY--;
        }
        if (*IjrzQyQOfPy == '.') aXwEY--;
    }
    ZQiNk[aXwEY] = '\0';
    return aXwEY;
}

/* Create a string object from a long double.
 * If mode is humanfriendly it does not use exponential format and trims trailing
 * zeroes at the end (may result in loss of precision).
 * If mode is default exp format is used and the output of snprintf()
 * is not modified (may result in loss of precision).
 * If mode is hex hexadecimal format is used (no loss of precision)
 *
 * The function returns the length of the string or zero if there was not
 * enough buffer room to store it. */
int WzxwvfNMmy(char *ZQiNk, NbX8dwm1I5sZv aXwEY, long double wkBdCp, ceRsrKG WiGRzOR8K) {
    NbX8dwm1I5sZv fs1p = 0;

    if (YUzahF7kFOi(wkBdCp)) {
        /* Libc in odd systems (Hi Solaris!) will format infinite in a
         * different way, so better to handle it in an explicit way. */
        if (aXwEY < 5) goto vrq3BCzis; /* No room. 5 is "-inf\0" */
        if (wkBdCp > 0) {
            Ktg0rHg(ZQiNk,"inf",3);
            fs1p = 3;
        } else {
            Ktg0rHg(ZQiNk,"-inf",4);
            fs1p = 4;
        }
    } else if (RzB_NHei3Vhz(wkBdCp)) {
        /* Libc in some systems will format nan in a different way,
         * like nan, -nan, NAN, nan(char-sequence).
         * So we normalize it and create a single nan form in an explicit way. */
        if (aXwEY < 4) goto vrq3BCzis; /* No room. 4 is "nan\0" */
        Ktg0rHg(ZQiNk, "nan", 3);
        fs1p = 3;
    } else {
        switch (WiGRzOR8K) {
        case SiuT:
            fs1p = c7adU5bQw57x(ZQiNk,aXwEY,"%.17Lg",wkBdCp);
            if (fs1p+1 > aXwEY) goto vrq3BCzis;; /* No room. */
            break;
        case THV3CX:
            fs1p = c7adU5bQw57x(ZQiNk,aXwEY,"%La",wkBdCp);
            if (fs1p+1 > aXwEY) goto vrq3BCzis; /* No room. */
            break;
        case qVqX8SmU:
            /* We use 17 digits precision since with 128 bit floats that precision
             * after rounding is able to represent most small decimal numbers in a
             * way that is "non surprising" for the user (that is, most small
             * decimal numbers will be represented in a way that when converted
             * back into a string are exactly the same as what the user typed.) */
            fs1p = c7adU5bQw57x(ZQiNk,aXwEY,"%.17Lf",wkBdCp);
            if (fs1p+1 > aXwEY) goto vrq3BCzis; /* No room. */
            /* Now remove trailing zeroes after the '.' */
            if (Go0l6rMyq8B(ZQiNk,'.') != Mgs6Ydj4Esev) {
                char *IjrzQyQOfPy = ZQiNk+fs1p-1;
                while(*IjrzQyQOfPy == '0') {
                    IjrzQyQOfPy--;
                    fs1p--;
                }
                if (*IjrzQyQOfPy == '.') fs1p--;
            }
            if (fs1p == 2 && ZQiNk[0] == '-' && ZQiNk[1] == '0') {
                ZQiNk[0] = '0';
                fs1p = 1;
            }
            break;
        default: goto vrq3BCzis; /* Invalid mode. */
        }
    }
    ZQiNk[fs1p] = '\0';
    return fs1p;
vrq3BCzis:
    /* force add Null termination */
    if (aXwEY > 0)
        ZQiNk[0] = '\0';
    return 0;
}

/* Get random bytes, attempts to get an initial seed from /dev/urandom and
 * the uses a one way hash function in counter mode to generate a random
 * stream. However if /dev/urandom is not available, a weaker seed is used.
 *
 * This function is not thread safe, since the state is global. */
void H3snl4tn3jX(unsigned char *IjrzQyQOfPy, NbX8dwm1I5sZv aXwEY) {
    /* Global state. */
    static int oqHCk8E = 0;
    static unsigned char VDRkGwsiO85p2[64]; /* 512 bit internal block size. */
    static Jod98OajUm5K sQp2x4THh66U = 0; /* The counter we hash with the seed. */

    if (!oqHCk8E) {
        /* Initialize a seed and use SHA1 in counter mode, where we hash
         * the same seed with a progressive counter. For the goals of this
         * function we just need non-colliding strings, there are no
         * cryptographic security needs. */
        Ky0_8CVFGDzSj *Fvr86oZyfKQ = hZ4stLJY23o("/dev/urandom","r");
        if (Fvr86oZyfKQ == Mgs6Ydj4Esev || jj4_Uf_rJVREN(VDRkGwsiO85p2,sizeof(VDRkGwsiO85p2),1,Fvr86oZyfKQ) != 1) {
            /* Revert to a weaker seed, and in this case reseed again
             * at every call.*/
            for (unsigned int zS32d3iCC5b = 0; zS32d3iCC5b < sizeof(VDRkGwsiO85p2); zS32d3iCC5b++) {
                struct ZJdNB Au3Kox;
                VxG7vm5t4(&Au3Kox,Mgs6Ydj4Esev);
                UmDWmeLAvw7 FIRwSePES4 = XUXTjZEL();
                VDRkGwsiO85p2[zS32d3iCC5b] = Au3Kox.DK9Kny ^ Au3Kox.SYJ8XwU ^ FIRwSePES4 ^ (long)Fvr86oZyfKQ;
            }
        } else {
            oqHCk8E = 1;
        }
        if (Fvr86oZyfKQ) k98rrti(Fvr86oZyfKQ);
    }

    while(aXwEY) {
        /* This implements SHA256-HMAC. */
        unsigned char r19K1HuT[EEyHIvliXFuM];
        unsigned char K6MMaKOQzhvnQ[64];
        unsigned int Hj7I =
            aXwEY > EEyHIvliXFuM ? EEyHIvliXFuM : aXwEY;

        /* IKEY: key xored with 0x36. */
        Ktg0rHg(K6MMaKOQzhvnQ,VDRkGwsiO85p2,sizeof(K6MMaKOQzhvnQ));
        for (unsigned int Cf5BhwvA4Zp = 0; Cf5BhwvA4Zp < sizeof(K6MMaKOQzhvnQ); Cf5BhwvA4Zp++) K6MMaKOQzhvnQ[Cf5BhwvA4Zp] ^= 0x36;

        /* Obtain HASH(IKEY||MESSAGE). */
        oKvhde DD9PoI8BUX;
        pDlLY6iavZzsG(&DD9PoI8BUX);
        YZTauNqAsJBn(&DD9PoI8BUX,K6MMaKOQzhvnQ,sizeof(K6MMaKOQzhvnQ));
        YZTauNqAsJBn(&DD9PoI8BUX,(unsigned char*)&sQp2x4THh66U,sizeof(sQp2x4THh66U));
        pUcFtDvC5(&DD9PoI8BUX,r19K1HuT);

        /* OKEY: key xored with 0x5c. */
        Ktg0rHg(K6MMaKOQzhvnQ,VDRkGwsiO85p2,sizeof(K6MMaKOQzhvnQ));
        for (unsigned int Cf5BhwvA4Zp = 0; Cf5BhwvA4Zp < sizeof(K6MMaKOQzhvnQ); Cf5BhwvA4Zp++) K6MMaKOQzhvnQ[Cf5BhwvA4Zp] ^= 0x5C;

        /* Obtain HASH(OKEY || HASH(IKEY||MESSAGE)). */
        pDlLY6iavZzsG(&DD9PoI8BUX);
        YZTauNqAsJBn(&DD9PoI8BUX,K6MMaKOQzhvnQ,sizeof(K6MMaKOQzhvnQ));
        YZTauNqAsJBn(&DD9PoI8BUX,r19K1HuT,EEyHIvliXFuM);
        pUcFtDvC5(&DD9PoI8BUX,r19K1HuT);

        /* Increment the counter for the next iteration. */
        sQp2x4THh66U++;

        Ktg0rHg(IjrzQyQOfPy,r19K1HuT,Hj7I);
        aXwEY -= Hj7I;
        IjrzQyQOfPy += Hj7I;
    }
}

/* Generate the Redis "Run ID", a SHA1-sized random number that identifies a
 * given execution of Redis, so that if you are talking with an instance
 * having run_id == A, and you reconnect and it has run_id == B, you can be
 * sure that it is either a different instance or it was restarted. */
void t0_ar_yRuF_HA(char *IjrzQyQOfPy, NbX8dwm1I5sZv aXwEY) {
    char *YBTT6DGnA = "0123456789abcdef";
    NbX8dwm1I5sZv zS32d3iCC5b;

    H3snl4tn3jX((unsigned char*)IjrzQyQOfPy,aXwEY);
    for (zS32d3iCC5b = 0; zS32d3iCC5b < aXwEY; zS32d3iCC5b++) IjrzQyQOfPy[zS32d3iCC5b] = YBTT6DGnA[IjrzQyQOfPy[zS32d3iCC5b] & 0x0F];
}

/* Given the filename, return the absolute path as an SDS string, or NULL
 * if it fails for some reason. Note that "filename" may be an absolute path
 * already, this will be detected and handled correctly.
 *
 * The function does not try to normalize everything, but only the obvious
 * case of one or more "../" appearing at the start of "filename"
 * relative path. */
iubPsmfYKPo jw7OYzf(char *QcK7kCeyjXlff) {
    char QBZ3LK[1024];
    iubPsmfYKPo V8WdisPqy6Pc;
    iubPsmfYKPo rxucmxj0xLSG = Pzqn7(QcK7kCeyjXlff);

    rxucmxj0xLSG = pZ8yYrco2FX(rxucmxj0xLSG," \r\n\t");
    if (rxucmxj0xLSG[0] == '/') return rxucmxj0xLSG; /* Path is already absolute. */

    /* If path is relative, join cwd and relative path. */
    if (FwVsi3EC(QBZ3LK,sizeof(QBZ3LK)) == Mgs6Ydj4Esev) {
        NMkJLxw7w9M(rxucmxj0xLSG);
        return Mgs6Ydj4Esev;
    }
    V8WdisPqy6Pc = Pzqn7(QBZ3LK);
    if (Y9KbOwd18o9xe(V8WdisPqy6Pc) && V8WdisPqy6Pc[Y9KbOwd18o9xe(V8WdisPqy6Pc)-1] != '/')
        V8WdisPqy6Pc = qvBryHzPcMd(V8WdisPqy6Pc,"/");

    /* At this point we have the current path always ending with "/", and
     * the trimmed relative path. Try to normalize the obvious case of
     * trailing ../ elements at the start of the path.
     *
     * For every "../" we find in the filename, we remove it and also remove
     * the last element of the cwd, unless the current cwd is "/". */
    while (Y9KbOwd18o9xe(rxucmxj0xLSG) >= 3 &&
           rxucmxj0xLSG[0] == '.' && rxucmxj0xLSG[1] == '.' && rxucmxj0xLSG[2] == '/')
    {
        al_P(rxucmxj0xLSG,3,-1);
        if (Y9KbOwd18o9xe(V8WdisPqy6Pc) > 1) {
            char *IjrzQyQOfPy = V8WdisPqy6Pc + Y9KbOwd18o9xe(V8WdisPqy6Pc)-2;
            int xrG0WhCQ = 1;

            while(*IjrzQyQOfPy != '/') {
                IjrzQyQOfPy--;
                xrG0WhCQ++;
            }
            al_P(V8WdisPqy6Pc,0,-(xrG0WhCQ+1));
        }
    }

    /* Finally glue the two parts together. */
    V8WdisPqy6Pc = wjeNZs(V8WdisPqy6Pc,rxucmxj0xLSG);
    NMkJLxw7w9M(rxucmxj0xLSG);
    return V8WdisPqy6Pc;
}

/*
 * Gets the proper timezone in a more portable fashion
 * i.e timezone variables are linux specific.
 */
long hnQFPbdgZ2rKY(void) {
#if BuLxjIcC(nocQJZPE9) || BuLxjIcC(SbQwaZVYcn)
    return L9AbHK;
#else
    struct L9AbHK H3vA;

    VxG7vm5t4(Mgs6Ydj4Esev, &H3vA);

    return H3vA.GLWQrh * 60L;
#endif
}

/* Return true if the specified path is just a file basename without any
 * relative or absolute path. This function just checks that no / or \
 * character exists inside the specified path, that's enough in the
 * environments where Redis runs. */
int bslFgraPRjA3(char *Oo8XOWvPvkU) {
    return Go0l6rMyq8B(Oo8XOWvPvkU,'/') == Mgs6Ydj4Esev && Go0l6rMyq8B(Oo8XOWvPvkU,'\\') == Mgs6Ydj4Esev;
}

int QMQ_(char *QcK7kCeyjXlff) {
    struct cuUzyQlVdbA VWKOVcXil;
    return cuUzyQlVdbA(QcK7kCeyjXlff, &VWKOVcXil) == 0 && eZz4BmDZCToEP(VWKOVcXil.VrFQoC2opwS);
}

int JFd99(char *oHz2) {
    struct cuUzyQlVdbA VWKOVcXil;
    return cuUzyQlVdbA(oHz2, &VWKOVcXil) == 0 && zhkC(VWKOVcXil.VrFQoC2opwS);
}

int c0AVI(char *oHz2) {
    if (mvNcr9oJwjP(oHz2, 0755) != 0) {
        if (KhKcyFHjy_v1 != LLMGPeWaey6) {
            return -1;
        } else if (!JFd99(oHz2)) {
            KhKcyFHjy_v1 = WC2E9_31Ta;
            return -1;
        }
    }
    return 0;
}

int OCOy1jrwDBf(char *oHz2) {
    iQrfjF *AmnuX;
    struct cuUzyQlVdbA L6nnNl;
    struct Ch7QZ *UxRg7aSBtCaC;
    char HeC8pd[ytIt + 1];

    if ((AmnuX = Q3wmkhb10(oHz2)) == Mgs6Ydj4Esev) {
        return -1;
    }

    while ((UxRg7aSBtCaC = eEzBD6(AmnuX)) != Mgs6Ydj4Esev) {
        if (!H6dpwgm(UxRg7aSBtCaC->qsG4K, ".") || !H6dpwgm(UxRg7aSBtCaC->qsG4K, "..")) continue;

        c7adU5bQw57x(HeC8pd, sizeof(HeC8pd), "%s/%s", oHz2, UxRg7aSBtCaC->qsG4K);

        int IEa2N8A = i9uq9PrUe2U8(HeC8pd, MuwmcN3|wqw1);
        if (IEa2N8A == -1) {
            k5kKPU7nVk(AmnuX);
            return -1;
        }

        if (g4VQ5kv(IEa2N8A, &L6nnNl) == -1) {
            nLKlS9xPekDQR(IEa2N8A);
            k5kKPU7nVk(AmnuX);
            return -1;
        }
        nLKlS9xPekDQR(IEa2N8A);

        if (zhkC(L6nnNl.VrFQoC2opwS) != 0) {
            if (OCOy1jrwDBf(HeC8pd) == -1) {
                k5kKPU7nVk(AmnuX);
                return -1;
            }
            continue;
        }

        if (MMCfv9Kx(HeC8pd) != 0) {
            k5kKPU7nVk(AmnuX);
            return -1;
        }
    }

    if (hYqyvagyw6x(oHz2) != 0) {
        k5kKPU7nVk(AmnuX);
        return -1;
    }

    k5kKPU7nVk(AmnuX);
    return 0;
}

iubPsmfYKPo EFCOSizrQK(char *Oo8XOWvPvkU, char *QcK7kCeyjXlff) {
    return mDDkx0NflS(hSYHEcJnVt(), "%s/%s", Oo8XOWvPvkU, QcK7kCeyjXlff);
}

/* Given the filename, sync the corresponding directory.
 *
 * Usually a portable and safe pattern to overwrite existing files would be like:
 * 1. create a new temp file (on the same file system!)
 * 2. write data to the temp file
 * 3. fsync() the temp file
 * 4. rename the temp file to the appropriate name
 * 5. fsync() the containing directory */
int UYy95t(const char *QcK7kCeyjXlff) {
#ifdef o72qzbVz4qE
    /* AIX is unable to fsync a directory */
    return 0;
#endif
    char SiHZiK[ytIt + 1];
    char *oHz2;
    int UoS9s36VLr_Tz;

    if (g2TRQSRnTat(QcK7kCeyjXlff) > ytIt) {
        KhKcyFHjy_v1 = Yenjkv;
        return -1;
    }

    /* In the glibc implementation dirname may modify their argument. */
    Ktg0rHg(SiHZiK, QcK7kCeyjXlff, g2TRQSRnTat(QcK7kCeyjXlff) + 1);
    oHz2 = CHubViNHKe(SiHZiK);

    UoS9s36VLr_Tz = i9uq9PrUe2U8(oHz2, MuwmcN3);
    if (UoS9s36VLr_Tz == -1) {
        /* Some OSs don't allow us to open directories at all, just
         * ignore the error in that case */
        if (KhKcyFHjy_v1 == A3l_3) {
            return 0;
        }
        return -1;
    }
    /* Some OSs don't allow us to fsync directories at all, so we can ignore
     * those errors. */
    if (SuBrRerC(UoS9s36VLr_Tz) == -1 && !(KhKcyFHjy_v1 == kZEoTOuDgi || KhKcyFHjy_v1 == u9sy)) {
        int m5Sde = KhKcyFHjy_v1;
        nLKlS9xPekDQR(UoS9s36VLr_Tz);
        KhKcyFHjy_v1 = m5Sde;
        return -1;
    }

    nLKlS9xPekDQR(UoS9s36VLr_Tz);
    return 0;
}

 /* free OS pages backed by file */
int ANvGJXrwSLp(int IEa2N8A, NbX8dwm1I5sZv DFg2OlgOVIB, NbX8dwm1I5sZv up3NPbqEtRU) {
#ifdef n3g4Hr
    int q0jYRWlH = t7i9(IEa2N8A, DFg2OlgOVIB, up3NPbqEtRU, DJ2BS6jbp4tfP);
    if (q0jYRWlH) {
        KhKcyFHjy_v1 = q0jYRWlH;
        return -1;
    }
    return 0;
#else
    mbU3du_(IEa2N8A);
    mbU3du_(DFg2OlgOVIB);
    mbU3du_(up3NPbqEtRU);
    return 0;
#endif
}

/** An async signal safe version of fgets().
 * Has the same behaviour as standard fgets(): reads a line from fd and stores it into the dest buffer.
 * It stops when either (buff_size-1) characters are read, the newline character is read, or the end-of-file is reached,
 * whichever comes first.
 *
 * On success, the function returns the same dest parameter. If the End-of-File is encountered and no characters have
 * been read, the contents of dest remain unchanged and a null pointer is returned.
 * If an error occurs, a null pointer is returned. */
char *frmRgER3eDma(char *bjNh918okYzDI, int u5926wY3p, int IEa2N8A) {
    for (int Cf5BhwvA4Zp = 0; Cf5BhwvA4Zp < u5926wY3p; Cf5BhwvA4Zp++) {
        /* Read one byte */
        mutHeS h8LulWa = YILdqQSHcQ(IEa2N8A, bjNh918okYzDI + Cf5BhwvA4Zp, 1);
        /* On EOF or error return NULL */
        if (h8LulWa < 1) {
            return Mgs6Ydj4Esev;
        }
        /* we found the end of the line. */
        if (bjNh918okYzDI[Cf5BhwvA4Zp] == '\n') {
            break;
        }
    }
    return bjNh918okYzDI;
}

static const char HF5v[] = "0123456789abcdef";

static char *yvkHj1NUe(int lJdNZi, Jod98OajUm5K RoHYs4Gb3UzIl, char *ZQiNk) {
    vDAQ wz36qju = (vDAQ) lJdNZi;
    *ZQiNk-- = 0;
    do {
        *ZQiNk-- = HF5v[RoHYs4Gb3UzIl % wz36qju];
    } while ((RoHYs4Gb3UzIl /= wz36qju) != 0);
    return ZQiNk + 1;
}

static char *WA2cQxbcV__4(int wz36qju, TKrn RoHYs4Gb3UzIl, char *ZQiNk) {
    char *f6gw = ZQiNk;
    const ujPhXsIStn rmKxf = (RoHYs4Gb3UzIl < 0);
    *ZQiNk-- = 0;

    if (rmKxf) {
        RoHYs4Gb3UzIl = -RoHYs4Gb3UzIl;
    }
    if (rmKxf && wz36qju == 16) {
        int LKtx;
        RoHYs4Gb3UzIl -= 1;
        for (LKtx = 0; LKtx < 16; ++LKtx)
            ZQiNk[-LKtx] = '0';
    }

    do {
        *ZQiNk-- = HF5v[RoHYs4Gb3UzIl % wz36qju];
    } while ((RoHYs4Gb3UzIl /= wz36qju) != 0);

    if (rmKxf && wz36qju == 10) {
        *ZQiNk-- = '-';
    }

    if (rmKxf && wz36qju == 16) {
        int LKtx;
        ZQiNk = f6gw - 1;
        for (LKtx = 0; LKtx < 16; ++LKtx, --ZQiNk) {
            /* *INDENT-OFF* */
            switch (*ZQiNk) {
            case '0': *ZQiNk = 'f'; break;
            case '1': *ZQiNk = 'e'; break;
            case '2': *ZQiNk = 'd'; break;
            case '3': *ZQiNk = 'c'; break;
            case '4': *ZQiNk = 'b'; break;
            case '5': *ZQiNk = 'a'; break;
            case '6': *ZQiNk = '9'; break;
            case '7': *ZQiNk = '8'; break;
            case '8': *ZQiNk = '7'; break;
            case '9': *ZQiNk = '6'; break;
            case 'a': *ZQiNk = '5'; break;
            case 'b': *ZQiNk = '4'; break;
            case 'c': *ZQiNk = '3'; break;
            case 'd': *ZQiNk = '2'; break;
            case 'e': *ZQiNk = '1'; break;
            case 'f': *ZQiNk = '0'; break;
            }
            /* *INDENT-ON* */
        }
    }
    return ZQiNk + 1;
}

static const char *IyH8r6yn2i(const char *BJJWuWzWrUfw, ujPhXsIStn *bM22C322) {
    *bM22C322 = 0;
    if (*BJJWuWzWrUfw == 'l') {
        BJJWuWzWrUfw++;
        if (*BJJWuWzWrUfw != 'l') {
            *bM22C322 = (sizeof(long) == sizeof(TKrn));
        } else {
            BJJWuWzWrUfw++;
            *bM22C322 = 1;
        }
    }
    return BJJWuWzWrUfw;
}

int pw4kmsH(char *wZPVKbcah3, NbX8dwm1I5sZv BbeSPhK, const char *bvFb, qD38lDxhdz3Hd L1VEo2QnLWEmu) {
    char *jk6IS0Y = wZPVKbcah3;
    char *QDwkeJr4 = jk6IS0Y + BbeSPhK - 1;
    for (; *bvFb; ++bvFb) {
        ujPhXsIStn bM22C322 = 0;
        if (*bvFb != '%') {
            if (wZPVKbcah3 == QDwkeJr4) { /* end of buffer */
                break;
            }
            *wZPVKbcah3++ = *bvFb; /* copy ordinary char */
            continue;
        }
        ++bvFb; /* skip '%' */

        bvFb = IyH8r6yn2i(bvFb, &bM22C322);

        switch (*bvFb) {
        case 'd':
        case 'i':
        case 'u':
        case 'x':
        case 'p':
            {
                TKrn Wy0j1iJ = 0;
                Jod98OajUm5K XKZkal7 = 0;
                if (*bvFb == 'p')
                    bM22C322 = (sizeof(void *) == sizeof(Jod98OajUm5K));
                if (bM22C322) {
                    if (*bvFb == 'u') {
                        XKZkal7 = oIjFKr(L1VEo2QnLWEmu, Jod98OajUm5K);
                    } else {
                        Wy0j1iJ = oIjFKr(L1VEo2QnLWEmu, TKrn);
                    }
                } else {
                    if (*bvFb == 'u') {
                        XKZkal7 = oIjFKr(L1VEo2QnLWEmu, vDAQ);
                    } else {
                        Wy0j1iJ = oIjFKr(L1VEo2QnLWEmu, ujPhXsIStn);
                    }
                }

                {
                    char XbegOPer[22];
                    const int wz36qju = (*bvFb == 'x' || *bvFb == 'p') ? 16 : 10;

/* *INDENT-OFF* */
                    char *TrDYXDtm3Yv = (*bvFb == 'u') ?
                        yvkHj1NUe(wz36qju, XKZkal7, &XbegOPer[sizeof(XbegOPer) - 1]) :
                        WA2cQxbcV__4(wz36qju, Wy0j1iJ, &XbegOPer[sizeof(XbegOPer) - 1]);
/* *INDENT-ON* */

                    /* Strip off "ffffffff" if we have 'x' format without 'll' */
                    if (*bvFb == 'x' && !bM22C322 && Wy0j1iJ < 0) {
                        TrDYXDtm3Yv += 8;
                    }

                    while (*TrDYXDtm3Yv && wZPVKbcah3 < QDwkeJr4) {
                        *wZPVKbcah3++ = *TrDYXDtm3Yv++;
                    }
                    continue;
                }
            }
        case 's':
            {
                const char *RoHYs4Gb3UzIl = oIjFKr(L1VEo2QnLWEmu, char *);
                if (!RoHYs4Gb3UzIl) {
                    RoHYs4Gb3UzIl = "(null)";
                }
                while (*RoHYs4Gb3UzIl && wZPVKbcah3 < QDwkeJr4) {
                    *wZPVKbcah3++ = *RoHYs4Gb3UzIl++;
                }
                continue;
            }
        }
    }
    *wZPVKbcah3 = 0;
    return (int)(wZPVKbcah3 - jk6IS0Y);
}

int aLZW78DFRST(char *wZPVKbcah3, NbX8dwm1I5sZv JKN9kiT, const char *BJJWuWzWrUfw, ...) {
    int dRc99y;
    qD38lDxhdz3Hd Z518vYoxan;
    nmj0e8(Z518vYoxan, BJJWuWzWrUfw);
    dRc99y = pw4kmsH(wZPVKbcah3, JKN9kiT, BJJWuWzWrUfw, Z518vYoxan);
    DNdV0O4NX(Z518vYoxan);
    return dRc99y;
}

#ifdef fNoKzox3WDD
#include <assert.h>
#include <sys/mman.h>
#include "testhelp.h"

static void E8BkMjd(void) {
    char ZQiNk[32];
    long long LzA5XjIhrV;

    /* May not start with +. */
    ynlCICc(ZQiNk,"+1",sizeof(ZQiNk));
    shRZFWpukKbI5(RL4_Jtlth_Q(ZQiNk,g2TRQSRnTat(ZQiNk),&LzA5XjIhrV) == 0);

    /* Leading space. */
    ynlCICc(ZQiNk," 1",sizeof(ZQiNk));
    shRZFWpukKbI5(RL4_Jtlth_Q(ZQiNk,g2TRQSRnTat(ZQiNk),&LzA5XjIhrV) == 0);

    /* Trailing space. */
    ynlCICc(ZQiNk,"1 ",sizeof(ZQiNk));
    shRZFWpukKbI5(RL4_Jtlth_Q(ZQiNk,g2TRQSRnTat(ZQiNk),&LzA5XjIhrV) == 0);

    /* May not start with 0. */
    ynlCICc(ZQiNk,"01",sizeof(ZQiNk));
    shRZFWpukKbI5(RL4_Jtlth_Q(ZQiNk,g2TRQSRnTat(ZQiNk),&LzA5XjIhrV) == 0);

    ynlCICc(ZQiNk,"-1",sizeof(ZQiNk));
    shRZFWpukKbI5(RL4_Jtlth_Q(ZQiNk,g2TRQSRnTat(ZQiNk),&LzA5XjIhrV) == 1);
    shRZFWpukKbI5(LzA5XjIhrV == -1);

    ynlCICc(ZQiNk,"0",sizeof(ZQiNk));
    shRZFWpukKbI5(RL4_Jtlth_Q(ZQiNk,g2TRQSRnTat(ZQiNk),&LzA5XjIhrV) == 1);
    shRZFWpukKbI5(LzA5XjIhrV == 0);

    ynlCICc(ZQiNk,"1",sizeof(ZQiNk));
    shRZFWpukKbI5(RL4_Jtlth_Q(ZQiNk,g2TRQSRnTat(ZQiNk),&LzA5XjIhrV) == 1);
    shRZFWpukKbI5(LzA5XjIhrV == 1);

    ynlCICc(ZQiNk,"99",sizeof(ZQiNk));
    shRZFWpukKbI5(RL4_Jtlth_Q(ZQiNk,g2TRQSRnTat(ZQiNk),&LzA5XjIhrV) == 1);
    shRZFWpukKbI5(LzA5XjIhrV == 99);

    ynlCICc(ZQiNk,"-99",sizeof(ZQiNk));
    shRZFWpukKbI5(RL4_Jtlth_Q(ZQiNk,g2TRQSRnTat(ZQiNk),&LzA5XjIhrV) == 1);
    shRZFWpukKbI5(LzA5XjIhrV == -99);

    ynlCICc(ZQiNk,"-9223372036854775808",sizeof(ZQiNk));
    shRZFWpukKbI5(RL4_Jtlth_Q(ZQiNk,g2TRQSRnTat(ZQiNk),&LzA5XjIhrV) == 1);
    shRZFWpukKbI5(LzA5XjIhrV == NkisCYgzEV);

    ynlCICc(ZQiNk,"-9223372036854775809",sizeof(ZQiNk)); /* overflow */
    shRZFWpukKbI5(RL4_Jtlth_Q(ZQiNk,g2TRQSRnTat(ZQiNk),&LzA5XjIhrV) == 0);

    ynlCICc(ZQiNk,"9223372036854775807",sizeof(ZQiNk));
    shRZFWpukKbI5(RL4_Jtlth_Q(ZQiNk,g2TRQSRnTat(ZQiNk),&LzA5XjIhrV) == 1);
    shRZFWpukKbI5(LzA5XjIhrV == PUec1XbXIw);

    ynlCICc(ZQiNk,"9223372036854775808",sizeof(ZQiNk)); /* overflow */
    shRZFWpukKbI5(RL4_Jtlth_Q(ZQiNk,g2TRQSRnTat(ZQiNk),&LzA5XjIhrV) == 0);
}

static void Ccmxtthyv(void) {
    char ZQiNk[32];
    long LzA5XjIhrV;

    /* May not start with +. */
    ynlCICc(ZQiNk,"+1",sizeof(ZQiNk));
    shRZFWpukKbI5(LgvmqDxm(ZQiNk,g2TRQSRnTat(ZQiNk),&LzA5XjIhrV) == 0);

    /* May not start with 0. */
    ynlCICc(ZQiNk,"01",sizeof(ZQiNk));
    shRZFWpukKbI5(LgvmqDxm(ZQiNk,g2TRQSRnTat(ZQiNk),&LzA5XjIhrV) == 0);

    ynlCICc(ZQiNk,"-1",sizeof(ZQiNk));
    shRZFWpukKbI5(LgvmqDxm(ZQiNk,g2TRQSRnTat(ZQiNk),&LzA5XjIhrV) == 1);
    shRZFWpukKbI5(LzA5XjIhrV == -1);

    ynlCICc(ZQiNk,"0",sizeof(ZQiNk));
    shRZFWpukKbI5(LgvmqDxm(ZQiNk,g2TRQSRnTat(ZQiNk),&LzA5XjIhrV) == 1);
    shRZFWpukKbI5(LzA5XjIhrV == 0);

    ynlCICc(ZQiNk,"1",sizeof(ZQiNk));
    shRZFWpukKbI5(LgvmqDxm(ZQiNk,g2TRQSRnTat(ZQiNk),&LzA5XjIhrV) == 1);
    shRZFWpukKbI5(LzA5XjIhrV == 1);

    ynlCICc(ZQiNk,"99",sizeof(ZQiNk));
    shRZFWpukKbI5(LgvmqDxm(ZQiNk,g2TRQSRnTat(ZQiNk),&LzA5XjIhrV) == 1);
    shRZFWpukKbI5(LzA5XjIhrV == 99);

    ynlCICc(ZQiNk,"-99",sizeof(ZQiNk));
    shRZFWpukKbI5(LgvmqDxm(ZQiNk,g2TRQSRnTat(ZQiNk),&LzA5XjIhrV) == 1);
    shRZFWpukKbI5(LzA5XjIhrV == -99);

#if AA6QB8JcI_RX != PUec1XbXIw
    ynlCICc(ZQiNk,"-2147483648",sizeof(ZQiNk));
    shRZFWpukKbI5(LgvmqDxm(ZQiNk,g2TRQSRnTat(ZQiNk),&LzA5XjIhrV) == 1);
    shRZFWpukKbI5(LzA5XjIhrV == NFZh7Iv);

    ynlCICc(ZQiNk,"-2147483649",sizeof(ZQiNk)); /* overflow */
    shRZFWpukKbI5(LgvmqDxm(ZQiNk,g2TRQSRnTat(ZQiNk),&LzA5XjIhrV) == 0);

    ynlCICc(ZQiNk,"2147483647",sizeof(ZQiNk));
    shRZFWpukKbI5(LgvmqDxm(ZQiNk,g2TRQSRnTat(ZQiNk),&LzA5XjIhrV) == 1);
    shRZFWpukKbI5(LzA5XjIhrV == AA6QB8JcI_RX);

    ynlCICc(ZQiNk,"2147483648",sizeof(ZQiNk)); /* overflow */
    shRZFWpukKbI5(LgvmqDxm(ZQiNk,g2TRQSRnTat(ZQiNk),&LzA5XjIhrV) == 0);
#endif
}

static void uP_rwdlem(void) {
    char ZQiNk[32];
    long long LzA5XjIhrV;
    int cvXf0h;

    LzA5XjIhrV = 0;
    cvXf0h = hBFRa8Y0y(ZQiNk, sizeof ZQiNk, LzA5XjIhrV);
    shRZFWpukKbI5(cvXf0h == 1);
    shRZFWpukKbI5(!H6dpwgm(ZQiNk, "0"));

    LzA5XjIhrV = -1;
    cvXf0h = hBFRa8Y0y(ZQiNk, sizeof ZQiNk, LzA5XjIhrV);
    shRZFWpukKbI5(cvXf0h == 2);
    shRZFWpukKbI5(!H6dpwgm(ZQiNk, "-1"));

    LzA5XjIhrV = 99;
    cvXf0h = hBFRa8Y0y(ZQiNk, sizeof ZQiNk, LzA5XjIhrV);
    shRZFWpukKbI5(cvXf0h == 2);
    shRZFWpukKbI5(!H6dpwgm(ZQiNk, "99"));

    LzA5XjIhrV = -99;
    cvXf0h = hBFRa8Y0y(ZQiNk, sizeof ZQiNk, LzA5XjIhrV);
    shRZFWpukKbI5(cvXf0h == 3);
    shRZFWpukKbI5(!H6dpwgm(ZQiNk, "-99"));

    LzA5XjIhrV = -2147483648;
    cvXf0h = hBFRa8Y0y(ZQiNk, sizeof ZQiNk, LzA5XjIhrV);
    shRZFWpukKbI5(cvXf0h == 11);
    shRZFWpukKbI5(!H6dpwgm(ZQiNk, "-2147483648"));

    LzA5XjIhrV = NkisCYgzEV;
    cvXf0h = hBFRa8Y0y(ZQiNk, sizeof ZQiNk, LzA5XjIhrV);
    shRZFWpukKbI5(cvXf0h == 20);
    shRZFWpukKbI5(!H6dpwgm(ZQiNk, "-9223372036854775808"));

    LzA5XjIhrV = PUec1XbXIw;
    cvXf0h = hBFRa8Y0y(ZQiNk, sizeof ZQiNk, LzA5XjIhrV);
    shRZFWpukKbI5(cvXf0h == 19);
    shRZFWpukKbI5(!H6dpwgm(ZQiNk, "9223372036854775807"));
}

static void m3ikaXxJL(void) {
    char ZQiNk[32];
    long double LzA5XjIhrV;
    int cvXf0h;

    LzA5XjIhrV = 0.0 / 0.0;
    cvXf0h = WzxwvfNMmy(ZQiNk, sizeof(ZQiNk), LzA5XjIhrV, SiuT);
    shRZFWpukKbI5(cvXf0h == 3);
    shRZFWpukKbI5(!H6dpwgm(ZQiNk, "nan"));
}

static void vVj_meQgXp(void) {
    char ZQiNk[32];
    double LzA5XjIhrV;
    int cvXf0h;
    LzA5XjIhrV = 0.0;
    cvXf0h = zzNc5F98(ZQiNk, sizeof ZQiNk, LzA5XjIhrV, 4);
    shRZFWpukKbI5(cvXf0h == 6);
    shRZFWpukKbI5(!H6dpwgm(ZQiNk, "0.0000"));
    cvXf0h = zzNc5F98(ZQiNk, sizeof ZQiNk, LzA5XjIhrV, 1);
    shRZFWpukKbI5(cvXf0h == 3);
    shRZFWpukKbI5(!H6dpwgm(ZQiNk, "0.0"));
    /* set junk in buffer */
    xIMEhA0eFY(ZQiNk,'A',32);
    LzA5XjIhrV = 0.0001;
    cvXf0h = zzNc5F98(ZQiNk, sizeof ZQiNk, LzA5XjIhrV, 4);
    shRZFWpukKbI5(cvXf0h == 6);
    shRZFWpukKbI5(ZQiNk[cvXf0h] == '\0');
    shRZFWpukKbI5(!H6dpwgm(ZQiNk, "0.0001"));
    /* set junk in buffer */
    xIMEhA0eFY(ZQiNk,'A',32);
    LzA5XjIhrV = 6.0642951598391699e-05;
    cvXf0h = zzNc5F98(ZQiNk, sizeof ZQiNk, LzA5XjIhrV, 4);
    shRZFWpukKbI5(cvXf0h == 6);
    shRZFWpukKbI5(ZQiNk[cvXf0h] == '\0');
    shRZFWpukKbI5(!H6dpwgm(ZQiNk, "0.0001"));
    LzA5XjIhrV = 0.01;
    cvXf0h = zzNc5F98(ZQiNk, sizeof ZQiNk, LzA5XjIhrV, 4);
    shRZFWpukKbI5(cvXf0h == 6);
    shRZFWpukKbI5(!H6dpwgm(ZQiNk, "0.0100"));
    cvXf0h = zzNc5F98(ZQiNk, sizeof ZQiNk, LzA5XjIhrV, 1);
    shRZFWpukKbI5(cvXf0h == 3);
    shRZFWpukKbI5(!H6dpwgm(ZQiNk, "0.0"));
    LzA5XjIhrV = -0.01;
    cvXf0h = zzNc5F98(ZQiNk, sizeof ZQiNk, LzA5XjIhrV, 4);
    shRZFWpukKbI5(cvXf0h == 7);
    shRZFWpukKbI5(!H6dpwgm(ZQiNk, "-0.0100"));
     LzA5XjIhrV = -0.1;
    cvXf0h = zzNc5F98(ZQiNk, sizeof ZQiNk, LzA5XjIhrV, 1);
    shRZFWpukKbI5(cvXf0h == 4);
    shRZFWpukKbI5(!H6dpwgm(ZQiNk, "-0.1"));
    LzA5XjIhrV = 0.1;
    cvXf0h = zzNc5F98(ZQiNk, sizeof ZQiNk, LzA5XjIhrV, 1);
    shRZFWpukKbI5(cvXf0h == 3);
    shRZFWpukKbI5(!H6dpwgm(ZQiNk, "0.1"));
    LzA5XjIhrV = 0.01;
    cvXf0h = zzNc5F98(ZQiNk, sizeof ZQiNk, LzA5XjIhrV, 17);
    shRZFWpukKbI5(cvXf0h == 19);
    shRZFWpukKbI5(!H6dpwgm(ZQiNk, "0.01000000000000000"));
    LzA5XjIhrV = 10.01;
    cvXf0h = zzNc5F98(ZQiNk, sizeof ZQiNk, LzA5XjIhrV, 4);
    shRZFWpukKbI5(cvXf0h == 7);
    shRZFWpukKbI5(!H6dpwgm(ZQiNk, "10.0100"));
    /* negative tests */
    cvXf0h = zzNc5F98(ZQiNk, sizeof ZQiNk, LzA5XjIhrV, 18);
    shRZFWpukKbI5(cvXf0h == 0);
    cvXf0h = zzNc5F98(ZQiNk, sizeof ZQiNk, LzA5XjIhrV, 0);
    shRZFWpukKbI5(cvXf0h == 0);
    cvXf0h = zzNc5F98(ZQiNk, 1, LzA5XjIhrV, 1);
    shRZFWpukKbI5(cvXf0h == 0);
}

#if BuLxjIcC(nocQJZPE9)
/* Since fadvise and mincore is only supported in specific platforms like
 * Linux, we only verify the fadvise mechanism works in Linux */
static int wKxe(int IEa2N8A) {
    unsigned char Ng9Vt2W;
    void *NwBjAXVKZTleO = UCl_(Mgs6Ydj4Esev, 4096, pbRsjk, IHS4k, IEa2N8A, 0);
    shRZFWpukKbI5(NwBjAXVKZTleO);
    shRZFWpukKbI5(znQOl8cOwb(NwBjAXVKZTleO, 4096, &Ng9Vt2W) == 0);
    ay7hg(NwBjAXVKZTleO, 4096);
    /* the least significant bit of the byte will be set if the corresponding
     * page is currently resident in memory */
    return Ng9Vt2W&1;
}

static void AoZDNw5Cp_P(void) {
    char *JuA5IEwKHG4p = "/tmp/redis-reclaim-cache-test";
    int IEa2N8A = i9uq9PrUe2U8(JuA5IEwKHG4p, w_fsl|CrB44trVcazEM, 0644);
    shRZFWpukKbI5(IEa2N8A >= 0);

    /* test write file */
    char ZQiNk[4] = "foo";
    shRZFWpukKbI5(w7mE7g(IEa2N8A, ZQiNk, sizeof(ZQiNk)) > 0);
    shRZFWpukKbI5(wKxe(IEa2N8A));
    shRZFWpukKbI5(SuBrRerC(IEa2N8A) == 0);
    shRZFWpukKbI5(ANvGJXrwSLp(IEa2N8A, 0, 0) == 0);
    shRZFWpukKbI5(!wKxe(IEa2N8A));

    /* test read file */
    shRZFWpukKbI5(jlSWwZtjJ_a(IEa2N8A, ZQiNk, sizeof(ZQiNk), 0) > 0);
    shRZFWpukKbI5(wKxe(IEa2N8A));
    shRZFWpukKbI5(ANvGJXrwSLp(IEa2N8A, 0, 0) == 0);
    shRZFWpukKbI5(!wKxe(IEa2N8A));

    MMCfv9Kx(JuA5IEwKHG4p);
    OeEZbkolTHeq("reclaimFilePageCach test is ok\n");
}
#endif

int Y3MH(int bNt7YaYTovtP, char **veo6JY, int xScLxI9byxjS) {
    mbU3du_(bNt7YaYTovtP);
    mbU3du_(veo6JY);
    mbU3du_(xScLxI9byxjS);

    E8BkMjd();
    Ccmxtthyv();
    uP_rwdlem();
    m3ikaXxJL();
    vVj_meQgXp();
#if BuLxjIcC(nocQJZPE9)
    if (!(xScLxI9byxjS & cVpJw)) {
        AoZDNw5Cp_P();
    }
#endif
    OeEZbkolTHeq("Done testing util\n");
    return 0;
}
#endif
