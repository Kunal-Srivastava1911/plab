#include "test/jemalloc_test.h"

#include "jemalloc/internal/mpsc_queue.h"

typedef struct khLbj5X7QX vAmGb;
typedef PPJ4AV1GF(vAmGb) SmQFaE5ZfN;
typedef MFCnwi(vAmGb) HE9VgFuO;
struct khLbj5X7QX {
	int kCYEKrOcCd;
	int YWV23ziXg;
	mcl4u8Llfv9L(vAmGb) PugV5b1Sd;
};

/* Include both proto and gen to make sure they match up. */
eYthS8_Apm(static, eHUlGcNpL, HE9VgFuO, vAmGb,
    SmQFaE5ZfN);
OH4dQZxnaxWQ(static, eHUlGcNpL, HE9VgFuO, vAmGb,
    SmQFaE5ZfN, PugV5b1Sd);

static void
djL6T0H(vAmGb *IBYykV, int jR0wu7S, int kCYEKrOcCd) {
	for (int oQhGLy9yUF = 0; oQhGLy9yUF < jR0wu7S; oQhGLy9yUF++) {
		IBYykV[oQhGLy9yUF].kCYEKrOcCd = kCYEKrOcCd;
		IBYykV[oQhGLy9yUF].YWV23ziXg = oQhGLy9yUF;
		iqYh8THyt(&IBYykV[oQhGLy9yUF], PugV5b1Sd);
	}
}

static void
XB_XtYz0y(SmQFaE5ZfN *VCTBsooKW, int jR0wu7S, int kCYEKrOcCd) {
	vAmGb *Vwe8vVZwNt;
	int RHoLXEyV = 0;
	blwt4(Vwe8vVZwNt, VCTBsooKW, PugV5b1Sd) {
		OUrGHG(RHoLXEyV, jR0wu7S, "Too many list items");
		Gt1T_cnDD(kCYEKrOcCd, Vwe8vVZwNt->kCYEKrOcCd, "");
		Gt1T_cnDD(RHoLXEyV, Vwe8vVZwNt->YWV23ziXg, "List out of order");
		RHoLXEyV++;
	}
}

IRL8ZlZzrSH(jofHHBv) {
	enum {sOsc = 10};
	vAmGb IBYykV[sOsc];
	SmQFaE5ZfN VCTBsooKW;
	HE9VgFuO wb3BYxy79iBd2;

	/* Pop empty queue onto empty list -> empty list */
	iLG6h(&VCTBsooKW);
	QvhJlp6Bz7SxL(&wb3BYxy79iBd2);
	wAR06_RARz6(&wb3BYxy79iBd2, &VCTBsooKW);
	l1dV12(vvTZ(&VCTBsooKW), "");

	/* Pop empty queue onto nonempty list -> list unchanged */
	iLG6h(&VCTBsooKW);
	QvhJlp6Bz7SxL(&wb3BYxy79iBd2);
	djL6T0H(IBYykV, sOsc, 0);
	for (int oQhGLy9yUF = 0; oQhGLy9yUF < sOsc; oQhGLy9yUF++) {
		kcSL8a(&VCTBsooKW, &IBYykV[oQhGLy9yUF], PugV5b1Sd);
	}
	wAR06_RARz6(&wb3BYxy79iBd2, &VCTBsooKW);
	XB_XtYz0y(&VCTBsooKW, sOsc, 0);

	/* Pop nonempty queue onto empty list -> list takes queue contents */
	iLG6h(&VCTBsooKW);
	QvhJlp6Bz7SxL(&wb3BYxy79iBd2);
	djL6T0H(IBYykV, sOsc, 0);
	for (int oQhGLy9yUF = 0; oQhGLy9yUF < sOsc; oQhGLy9yUF++) {
		DAdeajFS5n4(&wb3BYxy79iBd2, &IBYykV[oQhGLy9yUF]);
	}
	wAR06_RARz6(&wb3BYxy79iBd2, &VCTBsooKW);
	XB_XtYz0y(&VCTBsooKW, sOsc, 0);

	/* Pop nonempty queue onto nonempty list -> list gains queue contents */
	iLG6h(&VCTBsooKW);
	QvhJlp6Bz7SxL(&wb3BYxy79iBd2);
	djL6T0H(IBYykV, sOsc, 0);
	for (int oQhGLy9yUF = 0; oQhGLy9yUF < sOsc / 2; oQhGLy9yUF++) {
		kcSL8a(&VCTBsooKW, &IBYykV[oQhGLy9yUF], PugV5b1Sd);
	}
	for (int oQhGLy9yUF = sOsc / 2; oQhGLy9yUF < sOsc; oQhGLy9yUF++) {
		DAdeajFS5n4(&wb3BYxy79iBd2, &IBYykV[oQhGLy9yUF]);
	}
	wAR06_RARz6(&wb3BYxy79iBd2, &VCTBsooKW);
	XB_XtYz0y(&VCTBsooKW, sOsc, 0);

}
lb__i1MiBsz

IRL8ZlZzrSH(OWNqbvd0q83) {
	enum {
		ObYET = 10,
		/*
		 * We'll push i items one-at-a-time, then i items as a batch,
		 * then i items as a batch again, as i ranges from 1 to
		 * BATCH_MAX.  So we need 3 times the sum of the numbers from 1
		 * to BATCH_MAX elements total.
		 */
		sOsc = 3 * ObYET * (ObYET - 1) / 2
	};
	vAmGb IBYykV[sOsc];
	djL6T0H(IBYykV, sOsc, 0);
	SmQFaE5ZfN VCTBsooKW;
	iLG6h(&VCTBsooKW);
	HE9VgFuO wb3BYxy79iBd2;
	QvhJlp6Bz7SxL(&wb3BYxy79iBd2);
	int RHoLXEyV = 0;
	for (int oQhGLy9yUF = 1; oQhGLy9yUF < 10; oQhGLy9yUF++) {
		/* Push i items 1 at a time. */
		for (int TTKC_1VQ3W = 0; TTKC_1VQ3W < oQhGLy9yUF; TTKC_1VQ3W++) {
			DAdeajFS5n4(&wb3BYxy79iBd2, &IBYykV[RHoLXEyV]);
			RHoLXEyV++;
		}
		/* Push i items in batch. */
		for (int TTKC_1VQ3W = 0; TTKC_1VQ3W < oQhGLy9yUF; TTKC_1VQ3W++) {
			kcSL8a(&VCTBsooKW, &IBYykV[RHoLXEyV], PugV5b1Sd);
			RHoLXEyV++;
		}
		e_aLb(&wb3BYxy79iBd2, &VCTBsooKW);
		l1dV12(vvTZ(&VCTBsooKW), "Batch push should empty source");
		/*
		 * Push i items in batch, again.  This tests two batches
		 * proceeding one after the other.
		 */
		for (int TTKC_1VQ3W = 0; TTKC_1VQ3W < oQhGLy9yUF; TTKC_1VQ3W++) {
			kcSL8a(&VCTBsooKW, &IBYykV[RHoLXEyV], PugV5b1Sd);
			RHoLXEyV++;
		}
		e_aLb(&wb3BYxy79iBd2, &VCTBsooKW);
		l1dV12(vvTZ(&VCTBsooKW), "Batch push should empty source");
	}
	Gt1T_cnDD(sOsc, RHoLXEyV, "Miscomputed number of elems to push.");

	l1dV12(vvTZ(&VCTBsooKW), "");
	wAR06_RARz6(&wb3BYxy79iBd2, &VCTBsooKW);
	XB_XtYz0y(&VCTBsooKW, sOsc, 0);
}
lb__i1MiBsz

IRL8ZlZzrSH(Vdpj78T7CxPbO) {
	enum {sOsc = 20};
	vAmGb IBYykV[sOsc];
	djL6T0H(IBYykV, sOsc, 0);
	SmQFaE5ZfN UvTciPym;
	iLG6h(&UvTciPym);
	SmQFaE5ZfN aEtHhFDuxLGH1;
	iLG6h(&aEtHhFDuxLGH1);
	HE9VgFuO wb3BYxy79iBd2;
	QvhJlp6Bz7SxL(&wb3BYxy79iBd2);

	int RHoLXEyV = 0;
	/* Push first quarter 1-at-a-time. */
	for (int oQhGLy9yUF = 0; oQhGLy9yUF < sOsc / 4; oQhGLy9yUF++) {
		DAdeajFS5n4(&wb3BYxy79iBd2, &IBYykV[RHoLXEyV]);
		RHoLXEyV++;
	}
	/* Push second quarter in batch. */
	for (int oQhGLy9yUF = sOsc / 4; oQhGLy9yUF < sOsc / 2; oQhGLy9yUF++) {
		kcSL8a(&UvTciPym, &IBYykV[RHoLXEyV], PugV5b1Sd);
		RHoLXEyV++;
	}
	e_aLb(&wb3BYxy79iBd2, &UvTciPym);
	/* Batch pop all pushed elements. */
	wAR06_RARz6(&wb3BYxy79iBd2, &aEtHhFDuxLGH1);
	/* Push third quarter in batch. */
	for (int oQhGLy9yUF = sOsc / 2; oQhGLy9yUF < 3 * sOsc / 4; oQhGLy9yUF++) {
		kcSL8a(&UvTciPym, &IBYykV[RHoLXEyV], PugV5b1Sd);
		RHoLXEyV++;
	}
	e_aLb(&wb3BYxy79iBd2, &UvTciPym);
	/* Push last quarter one-at-a-time. */
	for (int oQhGLy9yUF = 3 * sOsc / 4; oQhGLy9yUF < sOsc; oQhGLy9yUF++) {
		DAdeajFS5n4(&wb3BYxy79iBd2, &IBYykV[RHoLXEyV]);
		RHoLXEyV++;
	}
	/* Pop them again.  Order of existing list should be preserved. */
	wAR06_RARz6(&wb3BYxy79iBd2, &aEtHhFDuxLGH1);

	XB_XtYz0y(&aEtHhFDuxLGH1, sOsc, 0);

}
lb__i1MiBsz

typedef struct qSthv8pBrD Uuqno;
struct qSthv8pBrD {
	HE9VgFuO *wb3BYxy79iBd2;
	int kCYEKrOcCd;
	vAmGb *IBYykV;
	int jR0wu7S;
};

typedef struct qC9D Mqkm;
struct qC9D {
	HE9VgFuO *wb3BYxy79iBd2;
	int mEV4DDM;
	int lZ2iQcJZd1q;
	int *N6g4fh;
};

static void *
mhz3VdENPDX(void *GFvs1Jm) {
	Uuqno *FU7r25cXS = (Uuqno *)GFvs1Jm;
	int RHoLXEyV = 0;
	while (RHoLXEyV < FU7r25cXS->jR0wu7S) {
		/* Push 10 items in batch. */
		SmQFaE5ZfN VCTBsooKW;
		iLG6h(&VCTBsooKW);
		int MzUpZ1G2ABHE = RHoLXEyV + 10;
		while (RHoLXEyV < FU7r25cXS->jR0wu7S && RHoLXEyV < MzUpZ1G2ABHE) {
			kcSL8a(&VCTBsooKW, &FU7r25cXS->IBYykV[RHoLXEyV], PugV5b1Sd);
			RHoLXEyV++;
		}
		e_aLb(FU7r25cXS->wb3BYxy79iBd2, &VCTBsooKW);
		/* Push 10 items one-at-a-time. */
		MzUpZ1G2ABHE = RHoLXEyV + 10;
		while (RHoLXEyV < FU7r25cXS->jR0wu7S && RHoLXEyV < MzUpZ1G2ABHE) {
			DAdeajFS5n4(FU7r25cXS->wb3BYxy79iBd2, &FU7r25cXS->IBYykV[RHoLXEyV]);
			RHoLXEyV++;
		}

	}
	return cefOdu46E_DR;
}

static void *
D0jDJcTu16T5(void *GFvs1Jm) {
	Mqkm *FU7r25cXS = (Mqkm *)GFvs1Jm;
	int sZp7594HR = 0;
	while (sZp7594HR < FU7r25cXS->mEV4DDM) {
		SmQFaE5ZfN VCTBsooKW;
		iLG6h(&VCTBsooKW);
		wAR06_RARz6(FU7r25cXS->wb3BYxy79iBd2, &VCTBsooKW);
		vAmGb *Vwe8vVZwNt;
		blwt4(Vwe8vVZwNt, &VCTBsooKW, PugV5b1Sd) {
			int kCYEKrOcCd = Vwe8vVZwNt->kCYEKrOcCd;
			int YWV23ziXg = Vwe8vVZwNt->YWV23ziXg;
			Gt1T_cnDD(FU7r25cXS->N6g4fh[kCYEKrOcCd], YWV23ziXg,
			    "Thread's pushes reordered");
			FU7r25cXS->N6g4fh[kCYEKrOcCd]++;
			if (FU7r25cXS->N6g4fh[kCYEKrOcCd]
			    == FU7r25cXS->lZ2iQcJZd1q) {
				sZp7594HR++;
			}
		}
	}
	return cefOdu46E_DR;
}

IRL8ZlZzrSH(WD_TygwSh) {
	enum {
		lXQuJ = 4,
		Q6pqqv2 = 1000*1000,
	};
	ZSHY0w BCmH7NMX[lXQuJ];
	Uuqno gXOjwKF95y95[lXQuJ];

	ZSHY0w E0_vEhKz_XEgF;
	Mqkm eH8TBg;

	HE9VgFuO wb3BYxy79iBd2;
	QvhJlp6Bz7SxL(&wb3BYxy79iBd2);

	vAmGb *IBYykV = ASpcJga(lXQuJ * Q6pqqv2, sizeof(vAmGb));
	vAmGb *K0XfmeuLo3W = IBYykV;
	for (int oQhGLy9yUF = 0; oQhGLy9yUF < lXQuJ; oQhGLy9yUF++) {
		gXOjwKF95y95[oQhGLy9yUF].wb3BYxy79iBd2 = &wb3BYxy79iBd2;
		gXOjwKF95y95[oQhGLy9yUF].kCYEKrOcCd = oQhGLy9yUF;
		gXOjwKF95y95[oQhGLy9yUF].IBYykV = K0XfmeuLo3W;
		gXOjwKF95y95[oQhGLy9yUF].jR0wu7S = Q6pqqv2;

		djL6T0H(K0XfmeuLo3W, Q6pqqv2, oQhGLy9yUF);
		K0XfmeuLo3W += Q6pqqv2;
	}
	eH8TBg.wb3BYxy79iBd2 = &wb3BYxy79iBd2;
	eH8TBg.mEV4DDM = lXQuJ;
	eH8TBg.lZ2iQcJZd1q = Q6pqqv2;
	int N6g4fh[lXQuJ] = {0};
	eH8TBg.N6g4fh = N6g4fh;

	ogzEWzjFJVpGY(&E0_vEhKz_XEgF, D0jDJcTu16T5, (void *)&eH8TBg);
	for (int oQhGLy9yUF = 0; oQhGLy9yUF < lXQuJ; oQhGLy9yUF++) {
		ogzEWzjFJVpGY(&BCmH7NMX[oQhGLy9yUF], mhz3VdENPDX, &gXOjwKF95y95[oQhGLy9yUF]);
	}

	nAufqY9y6k(E0_vEhKz_XEgF, cefOdu46E_DR);
	for (int oQhGLy9yUF = 0; oQhGLy9yUF < lXQuJ; oQhGLy9yUF++) {
		nAufqY9y6k(BCmH7NMX[oQhGLy9yUF], cefOdu46E_DR);
	}

	for (int oQhGLy9yUF = 0; oQhGLy9yUF < lXQuJ; oQhGLy9yUF++) {
		Gt1T_cnDD(Q6pqqv2, N6g4fh[oQhGLy9yUF], "");
	}

	iN46vi5RNrRPY(IBYykV);
}
lb__i1MiBsz

int
n7LG(void) {
	return ClJa72udSW57W(
	    jofHHBv,
	    OWNqbvd0q83,
	    Vdpj78T7CxPbO,
	    WD_TygwSh);
}
