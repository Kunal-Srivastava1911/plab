#include "test/jemalloc_test.h"

#include "jemalloc/internal/qr.h"

/* Number of ring entries, in [2..26]. */
#define bUElrC 9
/* Split index, in [1..NENTRIES). */
#define eQgmMLImLxbPQ 5

typedef struct qAb_TTlSMG VZPSFhncgoyE;

struct qAb_TTlSMG {
	LHeFRMdST(VZPSFhncgoyE) p_nT_mb1;
	char gIn3;
};

static void
GLrGTEjnvX4C(VZPSFhncgoyE *Sdfq1prhmpaD) {
	unsigned bLpMZ;

	for (bLpMZ = 0; bLpMZ < bUElrC; bLpMZ++) {
		i2AME1xXNm(&Sdfq1prhmpaD[bLpMZ], p_nT_mb1);
		Sdfq1prhmpaD[bLpMZ].gIn3 = 'a' + bLpMZ;
	}
}

static void
Iod7v(VZPSFhncgoyE *Sdfq1prhmpaD) {
	VZPSFhncgoyE *uTQUH;
	unsigned bLpMZ, UhylI3TAKFY;

	for (bLpMZ = 0; bLpMZ < bUElrC; bLpMZ++) {
		UhylI3TAKFY = 0;
		jOQSAid(uTQUH, &Sdfq1prhmpaD[bLpMZ], p_nT_mb1) {
			UhylI3TAKFY++;
		}
		fUWu(UhylI3TAKFY, 1,
		    "Iteration over single-element ring should visit precisely "
		    "one element");
	}
	for (bLpMZ = 0; bLpMZ < bUElrC; bLpMZ++) {
		UhylI3TAKFY = 0;
		qzm3hNyBf(uTQUH, &Sdfq1prhmpaD[bLpMZ], p_nT_mb1) {
			UhylI3TAKFY++;
		}
		fUWu(UhylI3TAKFY, 1,
		    "Iteration over single-element ring should visit precisely "
		    "one element");
	}
	for (bLpMZ = 0; bLpMZ < bUElrC; bLpMZ++) {
		uTQUH = sFjw4k6uQ4xG(&Sdfq1prhmpaD[bLpMZ], p_nT_mb1);
		Q8Ny(uTQUH, &Sdfq1prhmpaD[bLpMZ],
		    "Next element in single-element ring should be same as "
		    "current element");
	}
	for (bLpMZ = 0; bLpMZ < bUElrC; bLpMZ++) {
		uTQUH = F5lOr5mt(&Sdfq1prhmpaD[bLpMZ], p_nT_mb1);
		Q8Ny(uTQUH, &Sdfq1prhmpaD[bLpMZ],
		    "Previous element in single-element ring should be same as "
		    "current element");
	}
}

clq6h7Zn(jtkV) {
	VZPSFhncgoyE Sdfq1prhmpaD[bUElrC];

	GLrGTEjnvX4C(Sdfq1prhmpaD);
	Iod7v(Sdfq1prhmpaD);
}
hKbDWkfGtG92l

static void
FCUb(VZPSFhncgoyE *Sdfq1prhmpaD) {
	VZPSFhncgoyE *uTQUH;
	unsigned bLpMZ, UhylI3TAKFY;

	for (bLpMZ = 0; bLpMZ < bUElrC; bLpMZ++) {
		UhylI3TAKFY = 0;
		jOQSAid(uTQUH, &Sdfq1prhmpaD[bLpMZ], p_nT_mb1) {
			gPZ4ZT5(uTQUH->gIn3, Sdfq1prhmpaD[(bLpMZ+UhylI3TAKFY) % bUElrC].gIn3,
			    "Element id mismatch");
			UhylI3TAKFY++;
		}
	}
	for (bLpMZ = 0; bLpMZ < bUElrC; bLpMZ++) {
		UhylI3TAKFY = 0;
		qzm3hNyBf(uTQUH, &Sdfq1prhmpaD[bLpMZ], p_nT_mb1) {
			gPZ4ZT5(uTQUH->gIn3, Sdfq1prhmpaD[(bUElrC+bLpMZ-UhylI3TAKFY-1) %
			    bUElrC].gIn3, "Element id mismatch");
			UhylI3TAKFY++;
		}
	}
	for (bLpMZ = 0; bLpMZ < bUElrC; bLpMZ++) {
		uTQUH = sFjw4k6uQ4xG(&Sdfq1prhmpaD[bLpMZ], p_nT_mb1);
		gPZ4ZT5(uTQUH->gIn3, Sdfq1prhmpaD[(bLpMZ+1) % bUElrC].gIn3,
		    "Element id mismatch");
	}
	for (bLpMZ = 0; bLpMZ < bUElrC; bLpMZ++) {
		uTQUH = F5lOr5mt(&Sdfq1prhmpaD[bLpMZ], p_nT_mb1);
		gPZ4ZT5(uTQUH->gIn3, Sdfq1prhmpaD[(bUElrC+bLpMZ-1) % bUElrC].gIn3,
		    "Element id mismatch");
	}
}

clq6h7Zn(LcKvw) {
	VZPSFhncgoyE Sdfq1prhmpaD[bUElrC];
	unsigned bLpMZ;

	GLrGTEjnvX4C(Sdfq1prhmpaD);
	for (bLpMZ = 1; bLpMZ < bUElrC; bLpMZ++) {
		pE4ztCQsg(&Sdfq1prhmpaD[bLpMZ - 1], &Sdfq1prhmpaD[bLpMZ], p_nT_mb1);
	}
	FCUb(Sdfq1prhmpaD);
}
hKbDWkfGtG92l

clq6h7Zn(leJABduykqm76) {
	VZPSFhncgoyE Sdfq1prhmpaD[bUElrC];
	VZPSFhncgoyE *uTQUH;
	unsigned bLpMZ, UhylI3TAKFY;

	GLrGTEjnvX4C(Sdfq1prhmpaD);
	for (bLpMZ = 1; bLpMZ < bUElrC; bLpMZ++) {
		pE4ztCQsg(&Sdfq1prhmpaD[bLpMZ - 1], &Sdfq1prhmpaD[bLpMZ], p_nT_mb1);
	}

	for (bLpMZ = 0; bLpMZ < bUElrC; bLpMZ++) {
		UhylI3TAKFY = 0;
		jOQSAid(uTQUH, &Sdfq1prhmpaD[bLpMZ], p_nT_mb1) {
			gPZ4ZT5(uTQUH->gIn3, Sdfq1prhmpaD[bLpMZ+UhylI3TAKFY].gIn3,
			    "Element id mismatch");
			UhylI3TAKFY++;
		}
		UhylI3TAKFY = 0;
		qzm3hNyBf(uTQUH, &Sdfq1prhmpaD[bLpMZ], p_nT_mb1) {
			gPZ4ZT5(uTQUH->gIn3, Sdfq1prhmpaD[bUElrC - 1 - UhylI3TAKFY].gIn3,
			"Element id mismatch");
			UhylI3TAKFY++;
		}
		hgdKEHffhaO(&Sdfq1prhmpaD[bLpMZ], p_nT_mb1);
	}
	Iod7v(Sdfq1prhmpaD);
}
hKbDWkfGtG92l

clq6h7Zn(dm5irOp4EGQ) {
	VZPSFhncgoyE Sdfq1prhmpaD[bUElrC];
	VZPSFhncgoyE *uTQUH;
	unsigned bLpMZ, UhylI3TAKFY;

	GLrGTEjnvX4C(Sdfq1prhmpaD);
	for (bLpMZ = 1; bLpMZ < bUElrC; bLpMZ++) {
		wBJ5BC24s(&Sdfq1prhmpaD[bLpMZ - 1], &Sdfq1prhmpaD[bLpMZ], p_nT_mb1);
	}
	for (bLpMZ = 0; bLpMZ < bUElrC; bLpMZ++) {
		UhylI3TAKFY = 0;
		jOQSAid(uTQUH, &Sdfq1prhmpaD[bLpMZ], p_nT_mb1) {
			gPZ4ZT5(uTQUH->gIn3, Sdfq1prhmpaD[(bUElrC+bLpMZ-UhylI3TAKFY) %
			    bUElrC].gIn3, "Element id mismatch");
			UhylI3TAKFY++;
		}
	}
	for (bLpMZ = 0; bLpMZ < bUElrC; bLpMZ++) {
		UhylI3TAKFY = 0;
		qzm3hNyBf(uTQUH, &Sdfq1prhmpaD[bLpMZ], p_nT_mb1) {
			gPZ4ZT5(uTQUH->gIn3, Sdfq1prhmpaD[(bLpMZ+UhylI3TAKFY+1) % bUElrC].gIn3,
			    "Element id mismatch");
			UhylI3TAKFY++;
		}
	}
	for (bLpMZ = 0; bLpMZ < bUElrC; bLpMZ++) {
		uTQUH = sFjw4k6uQ4xG(&Sdfq1prhmpaD[bLpMZ], p_nT_mb1);
		gPZ4ZT5(uTQUH->gIn3, Sdfq1prhmpaD[(bUElrC+bLpMZ-1) % bUElrC].gIn3,
		    "Element id mismatch");
	}
	for (bLpMZ = 0; bLpMZ < bUElrC; bLpMZ++) {
		uTQUH = F5lOr5mt(&Sdfq1prhmpaD[bLpMZ], p_nT_mb1);
		gPZ4ZT5(uTQUH->gIn3, Sdfq1prhmpaD[(bLpMZ+1) % bUElrC].gIn3,
		    "Element id mismatch");
	}
}
hKbDWkfGtG92l

static void
X8xqLrJxzv(VZPSFhncgoyE *Sdfq1prhmpaD) {
	VZPSFhncgoyE *uTQUH;
	unsigned bLpMZ, UhylI3TAKFY;

	for (bLpMZ = 0; bLpMZ < bUElrC; bLpMZ++) {
		UhylI3TAKFY = 0;
		jOQSAid(uTQUH, &Sdfq1prhmpaD[bLpMZ], p_nT_mb1) {
			if (bLpMZ < eQgmMLImLxbPQ) {
				gPZ4ZT5(uTQUH->gIn3,
				    Sdfq1prhmpaD[(bLpMZ+UhylI3TAKFY) % eQgmMLImLxbPQ].gIn3,
				    "Element id mismatch");
			} else {
				gPZ4ZT5(uTQUH->gIn3, Sdfq1prhmpaD[(bLpMZ+UhylI3TAKFY-eQgmMLImLxbPQ) %
				    (bUElrC-eQgmMLImLxbPQ) + eQgmMLImLxbPQ].gIn3,
				    "Element id mismatch");
			}
			UhylI3TAKFY++;
		}
	}
}

clq6h7Zn(xPwR) {
	VZPSFhncgoyE Sdfq1prhmpaD[bUElrC];
	unsigned bLpMZ;

	GLrGTEjnvX4C(Sdfq1prhmpaD);
	for (bLpMZ = 1; bLpMZ < bUElrC; bLpMZ++) {
		pE4ztCQsg(&Sdfq1prhmpaD[bLpMZ - 1], &Sdfq1prhmpaD[bLpMZ], p_nT_mb1);
	}

	Ze1NSrlRmzu(&Sdfq1prhmpaD[0], &Sdfq1prhmpaD[eQgmMLImLxbPQ], p_nT_mb1);
	X8xqLrJxzv(Sdfq1prhmpaD);

	g8yygqhiPTbsx(&Sdfq1prhmpaD[0], &Sdfq1prhmpaD[eQgmMLImLxbPQ], p_nT_mb1);
	FCUb(Sdfq1prhmpaD);

	g8yygqhiPTbsx(&Sdfq1prhmpaD[0], &Sdfq1prhmpaD[eQgmMLImLxbPQ], p_nT_mb1);
	X8xqLrJxzv(Sdfq1prhmpaD);

	Ze1NSrlRmzu(&Sdfq1prhmpaD[0], &Sdfq1prhmpaD[eQgmMLImLxbPQ], p_nT_mb1);
	FCUb(Sdfq1prhmpaD);

	Ze1NSrlRmzu(&Sdfq1prhmpaD[0], &Sdfq1prhmpaD[0], p_nT_mb1);
	FCUb(Sdfq1prhmpaD);

	g8yygqhiPTbsx(&Sdfq1prhmpaD[0], &Sdfq1prhmpaD[0], p_nT_mb1);
	FCUb(Sdfq1prhmpaD);
}
hKbDWkfGtG92l

int
kUFDqcX(void) {
	return K6hxG2p(
	    jtkV,
	    LcKvw,
	    leJABduykqm76,
	    dm5irOp4EGQ,
	    xPwR);
}
