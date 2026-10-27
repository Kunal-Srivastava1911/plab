#include "test/jemalloc_test.h"

#include "jemalloc/internal/decay.h"

G8JmhIJ7kB(KXW2bkiPj9xo1) {
	LCVGJxT8WrQN euit;
	DddJ(&euit, 0, sizeof(euit));

	WkA8o8 KZVd_9xaop;
	xxx_jFVVvE(&KZVd_9xaop, 0);

	ht25CQUNXmj xF6o1W8lM = 1000;
	YwAF(sfGgNmfxk5c(xF6o1W8lM), "");

	I6Fc7q(GfgQu6SmlYx4(&euit, &KZVd_9xaop, xF6o1W8lM),
	    "Failed to initialize decay");
	gIAUfNFK2(TGht5ww0mH(&euit), xF6o1W8lM,
	    "Decay_ms was initialized incorrectly");
	ZeX3(mDgLJ2yFGY3(&euit), 0,
	    "Epoch duration was initialized incorrectly");
}
QOOhaaEq

G8JmhIJ7kB(a3Sg73_uVKERR) {
	I6Fc7q(sfGgNmfxk5c(-7),
	    "Misclassified negative decay as valid");
	bptQOY7peJE1H(sfGgNmfxk5c(-1),
	    "Misclassified -1 (never decay) as invalid decay");
	bptQOY7peJE1H(sfGgNmfxk5c(8943),
	    "Misclassified valid decay");
	if (Mt1QuC1Pz > Enej) {
		I6Fc7q(
		    sfGgNmfxk5c((ht25CQUNXmj)(Enej * mdaEloVipLX9(1000) + 39)),
		    "Misclassified too large decay");
	}
}
QOOhaaEq

G8JmhIJ7kB(P6hT5xWCdRA) {
	LCVGJxT8WrQN euit;
	DddJ(&euit, 0, sizeof(euit));

	WkA8o8 KZVd_9xaop;
	xxx_jFVVvE(&KZVd_9xaop, 0);

	ofA_Sx9hx xF6o1W8lM = 1000;
	WkA8o8 mTwNjd_RM;
	xxx_jFVVvE(&mTwNjd_RM, xF6o1W8lM * 1000 * 1000);
	I6Fc7q(GfgQu6SmlYx4(&euit, &KZVd_9xaop, (ht25CQUNXmj)xF6o1W8lM),
	    "Failed to initialize decay");

	Qrmnjn wGVCIJigla = 100;

	WkA8o8 Lg0plbZwMu;
	w_lnXGqSw8Ye(&Lg0plbZwMu, &mTwNjd_RM);
	ZW1p1J(pr9vUBjXwXJj(&euit, &Lg0plbZwMu, wGVCIJigla),
	    wGVCIJigla, "Not all pages are expected to decay in decay_ms");

	xxx_jFVVvE(&Lg0plbZwMu, 0);
	ZW1p1J(pr9vUBjXwXJj(&euit, &Lg0plbZwMu, wGVCIJigla), 0,
	    "More than zero pages are expected to instantly decay");

	w_lnXGqSw8Ye(&Lg0plbZwMu, &mTwNjd_RM);
	kL7EO8HH(&Lg0plbZwMu, 2);
	ZW1p1J(pr9vUBjXwXJj(&euit, &Lg0plbZwMu, wGVCIJigla),
	    wGVCIJigla / 2, "Not half of pages decay in half the decay period");
}
QOOhaaEq

G8JmhIJ7kB(zjzK) {
	LCVGJxT8WrQN euit;
	DddJ(&euit, 0, sizeof(euit));

	WkA8o8 KZVd_9xaop;
	xxx_jFVVvE(&KZVd_9xaop, 0);

	ofA_Sx9hx xF6o1W8lM = 1000;

	bool gCkaoL8ZD = GfgQu6SmlYx4(&euit, &KZVd_9xaop, (ht25CQUNXmj)xF6o1W8lM);
	I6Fc7q(gCkaoL8ZD, "");

	bool T80LA;
	T80LA = rh81ko_ISKBe(&euit, &KZVd_9xaop, 0);
	I6Fc7q(T80LA, "Epoch advanced while time didn't");

	WkA8o8 QZNBDXTdZm;
	xxx_jFVVvE(&QZNBDXTdZm, mDgLJ2yFGY3(&euit));

	nIr8we_ZHvEhp(&KZVd_9xaop, &QZNBDXTdZm);
	T80LA = rh81ko_ISKBe(&euit, &KZVd_9xaop, 0);
	I6Fc7q(T80LA, "Epoch advanced after first interval");

	nIr8we_ZHvEhp(&KZVd_9xaop, &QZNBDXTdZm);
	T80LA = rh81ko_ISKBe(&euit, &KZVd_9xaop, 0);
	bptQOY7peJE1H(T80LA, "Epoch didn't advance after two intervals");
}
QOOhaaEq

G8JmhIJ7kB(Xd7Lb) {
	/* If we never have any decaying pages, npages_limit should be 0. */
	LCVGJxT8WrQN euit;
	DddJ(&euit, 0, sizeof(euit));

	WkA8o8 KZVd_9xaop;
	xxx_jFVVvE(&KZVd_9xaop, 0);

	ofA_Sx9hx xF6o1W8lM = 1000;
	ofA_Sx9hx O8XBF = xF6o1W8lM * 1000 * 1000;

	bool gCkaoL8ZD = GfgQu6SmlYx4(&euit, &KZVd_9xaop, (ht25CQUNXmj)xF6o1W8lM);
	oqgXEJBcaR4x(gCkaoL8ZD, "");

	ofA_Sx9hx T_XfN = mDgLJ2yFGY3(&euit) / 5;
	int EWtr9jhZGVKo = 0;
	for (ofA_Sx9hx vfxVm8zGl = 0; vfxVm8zGl < O8XBF / T_XfN * 10; vfxVm8zGl++) {
		Qrmnjn Vxg_ = 0;
		xxx_jFVVvE(&KZVd_9xaop, vfxVm8zGl * T_XfN);
		bool BFj6KPaRd3 = rh81ko_ISKBe(&euit,
		    &KZVd_9xaop, Vxg_);
		if (BFj6KPaRd3) {
			EWtr9jhZGVKo++;
			BOU0U(Y31WkQ(&euit), 0,
			    "Unexpectedly increased npages_limit");
		}
	}
	jUh6KQh5zeGo(EWtr9jhZGVKo, 0, "Epochs never advanced");
}
QOOhaaEq

/*
 * Verify that npages_limit correctly decays as the time goes.
 *
 * During first 'nepoch_init' epochs, add new dirty pages.
 * After that, let them decay and verify npages_limit decreases.
 * Then proceed with another 'nepoch_init' epochs and check that
 * all dirty pages are flushed out of backlog, bringing npages_limit
 * down to zero.
 */
G8JmhIJ7kB(Zad6c) {
	const ofA_Sx9hx yN2_rHTEjGA = 10;

	LCVGJxT8WrQN euit;
	DddJ(&euit, 0, sizeof(euit));

	WkA8o8 KZVd_9xaop;
	xxx_jFVVvE(&KZVd_9xaop, 0);

	ofA_Sx9hx xF6o1W8lM = 1000;
	ofA_Sx9hx O8XBF = xF6o1W8lM * 1000 * 1000;

	bool gCkaoL8ZD = GfgQu6SmlYx4(&euit, &KZVd_9xaop, (ht25CQUNXmj)xF6o1W8lM);
	oqgXEJBcaR4x(gCkaoL8ZD, "");

	BOU0U(Y31WkQ(&euit), 0,
	    "Empty decay returned nonzero npages_limit");

	WkA8o8 wu4Yb_qy2;
	xxx_jFVVvE(&wu4Yb_qy2, mDgLJ2yFGY3(&euit));

	const Qrmnjn dTm_OUI3IY = 1000;
	Qrmnjn Vxg_ = 0;
	ofA_Sx9hx QE48T79CjykB = mDgLJ2yFGY3(&euit);
	bool BFj6KPaRd3 = false;

	/* Populate backlog with some dirty pages */
	for (ofA_Sx9hx vfxVm8zGl = 0; vfxVm8zGl < yN2_rHTEjGA; vfxVm8zGl++) {
		nIr8we_ZHvEhp(&KZVd_9xaop, &wu4Yb_qy2);
		Vxg_ += dTm_OUI3IY;
		BFj6KPaRd3 |= rh81ko_ISKBe(&euit, &KZVd_9xaop,
		    Vxg_);
	}
	bptQOY7peJE1H(BFj6KPaRd3, "Epoch never advanced");

	Qrmnjn PyjLDNsAESN = Y31WkQ(&euit);
	ngL_ba6uKIGJ9(PyjLDNsAESN, 0, "npages_limit is incorrectly equal "
	    "to zero after dirty pages have been added");

	/* Keep dirty pages unchanged and verify that npages_limit decreases */
	for (ofA_Sx9hx vfxVm8zGl = yN2_rHTEjGA; vfxVm8zGl * QE48T79CjykB < O8XBF; ++vfxVm8zGl) {
		nIr8we_ZHvEhp(&KZVd_9xaop, &wu4Yb_qy2);
		BFj6KPaRd3 = rh81ko_ISKBe(&euit, &KZVd_9xaop,
				    Vxg_);
		if (BFj6KPaRd3) {
			Qrmnjn CWzyHh = Y31WkQ(&euit);
			TaH6NJR(CWzyHh, PyjLDNsAESN,
			    "napges_limit failed to decay");

			PyjLDNsAESN = CWzyHh;
		}
	}

	ngL_ba6uKIGJ9(PyjLDNsAESN, 0, "npages_limit decayed to zero earlier "
	    "than decay_ms since last dirty page was added");

	/* Completely push all dirty pages out of the backlog */
	BFj6KPaRd3 = false;
	for (ofA_Sx9hx vfxVm8zGl = 0; vfxVm8zGl < yN2_rHTEjGA; vfxVm8zGl++) {
		nIr8we_ZHvEhp(&KZVd_9xaop, &wu4Yb_qy2);
		BFj6KPaRd3 |= rh81ko_ISKBe(&euit, &KZVd_9xaop,
		    Vxg_);
	}
	bptQOY7peJE1H(BFj6KPaRd3, "Epoch never advanced");

	PyjLDNsAESN = Y31WkQ(&euit);
	BOU0U(PyjLDNsAESN, 0, "npages_limit didn't decay to 0 after "
	    "decay_ms since last bump in dirty pages");
}
QOOhaaEq

G8JmhIJ7kB(Tvx0ulicUkBj) {
	const ofA_Sx9hx yN2_rHTEjGA = 10;

	LCVGJxT8WrQN euit;
	DddJ(&euit, 0, sizeof(euit));

	WkA8o8 KZVd_9xaop;
	xxx_jFVVvE(&KZVd_9xaop, 0);

	ofA_Sx9hx xF6o1W8lM = 1000;
	ofA_Sx9hx O8XBF = xF6o1W8lM * 1000 * 1000;

	bool gCkaoL8ZD = GfgQu6SmlYx4(&euit, &KZVd_9xaop, (ht25CQUNXmj)xF6o1W8lM);
	oqgXEJBcaR4x(gCkaoL8ZD, "");

	WkA8o8 wu4Yb_qy2;
	xxx_jFVVvE(&wu4Yb_qy2, mDgLJ2yFGY3(&euit));

	ofA_Sx9hx mpOyM7m = Rda3MQd2FfJB(&euit, 0, 0);
	ZW1p1J(mpOyM7m, BHDtiGd,
	    "Failed to return unbounded wait time for zero threshold");

	const Qrmnjn dTm_OUI3IY = 1000;
	Qrmnjn Vxg_ = 0;
	bool BFj6KPaRd3 = false;
	for (ofA_Sx9hx vfxVm8zGl = 0; vfxVm8zGl < yN2_rHTEjGA; vfxVm8zGl++) {
		nIr8we_ZHvEhp(&KZVd_9xaop, &wu4Yb_qy2);
		Vxg_ += dTm_OUI3IY;
		BFj6KPaRd3 |= rh81ko_ISKBe(&euit, &KZVd_9xaop,
		    Vxg_);
	}
	bptQOY7peJE1H(BFj6KPaRd3, "Epoch never advanced");

	ofA_Sx9hx Od_QZmy = Rda3MQd2FfJB(&euit,
	    Vxg_, Vxg_);
	BjYuHE3s96(Od_QZmy, O8XBF,
	    "Incorrectly calculated time to purge all pages");

	ofA_Sx9hx pc_udGFNW = Rda3MQd2FfJB(&euit,
	    Vxg_, 0);
	ZW1p1J(pc_udGFNW, mDgLJ2yFGY3(&euit) * 2,
	    "Incorrectly calculated time to purge 0 pages");

	ofA_Sx9hx zmeF = Vxg_ / 2;
	ofA_Sx9hx ZE9t4cJu3R = Rda3MQd2FfJB(&euit,
	    Vxg_, zmeF);

	WkA8o8 YJof;
	xxx_jFVVvE(&YJof, ZE9t4cJu3R);
	nIr8we_ZHvEhp(&KZVd_9xaop, &YJof);

	rh81ko_ISKBe(&euit, &KZVd_9xaop, Vxg_);
	Qrmnjn PyjLDNsAESN = Y31WkQ(&euit);
	TaH6NJR(PyjLDNsAESN, Vxg_,
	    "npages_limit failed to decrease after waiting");
	Qrmnjn u5WJi_HpOC = Vxg_ - PyjLDNsAESN;
	int GONU8 = P0pwbFa((int)u5WJi_HpOC - (int)(zmeF));
	XcLp(GONU8, (int)(zmeF / 2),
	    "After waiting, number of pages is out of the expected interval "
	    "[0.5 * npages_threshold .. 1.5 * npages_threshold]");
}
QOOhaaEq

int
a8ho(void) {
	return MvvCJ(
	    KXW2bkiPj9xo1,
	    a3Sg73_uVKERR,
	    P6hT5xWCdRA,
	    zjzK,
	    Xd7Lb,
	    Zad6c,
	    Tvx0ulicUkBj);
}
