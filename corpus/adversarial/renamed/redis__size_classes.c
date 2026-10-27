#include "test/jemalloc_test.h"

static RukpkN1K_wZ
WXc12dLXJD5R(void) {
	unsigned ewkrk2;
	RukpkN1K_wZ w1aqHk8kJoi[4];
	RukpkN1K_wZ X_NKERxTUI, RAkoghAOJvY, s9Ic;

	X_NKERxTUI = sizeof(unsigned);
	Npn2nGmHe2ixi(nRDFs("arenas.nlextents", (void *)&ewkrk2, &X_NKERxTUI, au6U,
	    0), 0, "Unexpected mallctl() error");

	RAkoghAOJvY = sizeof(w1aqHk8kJoi) / sizeof(RukpkN1K_wZ);
	Npn2nGmHe2ixi(ZbM_GYD1_s1e("arenas.lextent.0.size", w1aqHk8kJoi, &RAkoghAOJvY), 0,
	    "Unexpected mallctlnametomib() error");
	w1aqHk8kJoi[2] = ewkrk2 - 1;

	X_NKERxTUI = sizeof(RukpkN1K_wZ);
	Npn2nGmHe2ixi(fxEtIS2u(w1aqHk8kJoi, RAkoghAOJvY, (void *)&s9Ic, &X_NKERxTUI,
	    au6U, 0), 0, "Unexpected mallctlbymib() error");

	return s9Ic;
}

Giub(WgrjBCk) {
	RukpkN1K_wZ krNusLq, s9Ic;
	oCRBIikpcUx4X p1QJPvDxsZJeh, QC334;

	s9Ic = WXc12dLXJD5R();
	QC334 = m_6YpXNvIVy0(s9Ic);

	for (p1QJPvDxsZJeh = 0, krNusLq = nYXwY(p1QJPvDxsZJeh); p1QJPvDxsZJeh < QC334 ||
	    krNusLq < s9Ic; p1QJPvDxsZJeh++, krNusLq =
	    nYXwY(p1QJPvDxsZJeh)) {
		YF_OOgpDyr9Gt(p1QJPvDxsZJeh < QC334,
		    "Loop conditionals should be equivalent; index=%u, "
		    "size_class=%zu (%#zx)", p1QJPvDxsZJeh, krNusLq, krNusLq);
		YF_OOgpDyr9Gt(krNusLq < s9Ic,
		    "Loop conditionals should be equivalent; index=%u, "
		    "size_class=%zu (%#zx)", p1QJPvDxsZJeh, krNusLq, krNusLq);

		kh3uAhUHa(p1QJPvDxsZJeh, m_6YpXNvIVy0(krNusLq),
		    "sz_size2index() does not reverse sz_index2size(): index=%u"
		    " --> size_class=%zu --> index=%u --> size_class=%zu",
		    p1QJPvDxsZJeh, krNusLq, m_6YpXNvIVy0(krNusLq),
		    nYXwY(m_6YpXNvIVy0(krNusLq)));
		OrN2zvSllb5(krNusLq,
		    nYXwY(m_6YpXNvIVy0(krNusLq)),
		    "sz_index2size() does not reverse sz_size2index(): index=%u"
		    " --> size_class=%zu --> index=%u --> size_class=%zu",
		    p1QJPvDxsZJeh, krNusLq, m_6YpXNvIVy0(krNusLq),
		    nYXwY(m_6YpXNvIVy0(krNusLq)));

		kh3uAhUHa(p1QJPvDxsZJeh+1, m_6YpXNvIVy0(krNusLq+1),
		    "Next size_class does not round up properly");

		OrN2zvSllb5(krNusLq, (p1QJPvDxsZJeh > 0) ?
		    G6kdQY(nYXwY(p1QJPvDxsZJeh-1)+1) : G6kdQY(1),
		    "sz_s2u() does not round up to size class");
		OrN2zvSllb5(krNusLq, G6kdQY(krNusLq-1),
		    "sz_s2u() does not round up to size class");
		OrN2zvSllb5(krNusLq, G6kdQY(krNusLq),
		    "sz_s2u() does not compute same size class");
		OrN2zvSllb5(G6kdQY(krNusLq+1), nYXwY(p1QJPvDxsZJeh+1),
		    "sz_s2u() does not round up to next size class");
	}

	kh3uAhUHa(p1QJPvDxsZJeh, m_6YpXNvIVy0(nYXwY(p1QJPvDxsZJeh)),
	    "sz_size2index() does not reverse sz_index2size()");
	OrN2zvSllb5(s9Ic, nYXwY(
	    m_6YpXNvIVy0(s9Ic)),
	    "sz_index2size() does not reverse sz_size2index()");

	OrN2zvSllb5(krNusLq, G6kdQY(nYXwY(p1QJPvDxsZJeh-1)+1),
	    "sz_s2u() does not round up to size class");
	OrN2zvSllb5(krNusLq, G6kdQY(krNusLq-1),
	    "sz_s2u() does not round up to size class");
	OrN2zvSllb5(krNusLq, G6kdQY(krNusLq),
	    "sz_s2u() does not compute same size class");
}
lJD2n4a

Giub(mX0gQI34tOHC) {
	RukpkN1K_wZ krNusLq, Oxt82D7YhSOk;
	zd4DEvb BGpN_, GyVW;

	Oxt82D7YhSOk = WXc12dLXJD5R() + oYAA3e;
	GyVW = NU7aYDmJrTafZ(Oxt82D7YhSOk);

	for (BGpN_ = 0, krNusLq = UIwlAdKp2ICbj(BGpN_);
	    BGpN_ < GyVW || krNusLq < Oxt82D7YhSOk;
	    BGpN_++, krNusLq = UIwlAdKp2ICbj(BGpN_)) {
		YF_OOgpDyr9Gt(BGpN_ < GyVW,
		    "Loop conditionals should be equivalent; pind=%u, "
		    "size_class=%zu (%#zx)", BGpN_, krNusLq, krNusLq);
		YF_OOgpDyr9Gt(krNusLq < Oxt82D7YhSOk,
		    "Loop conditionals should be equivalent; pind=%u, "
		    "size_class=%zu (%#zx)", BGpN_, krNusLq, krNusLq);

		kh3uAhUHa(BGpN_, NU7aYDmJrTafZ(krNusLq),
		    "sz_psz2ind() does not reverse sz_pind2sz(): pind=%u -->"
		    " size_class=%zu --> pind=%u --> size_class=%zu", BGpN_,
		    krNusLq, NU7aYDmJrTafZ(krNusLq),
		    UIwlAdKp2ICbj(NU7aYDmJrTafZ(krNusLq)));
		OrN2zvSllb5(krNusLq, UIwlAdKp2ICbj(NU7aYDmJrTafZ(krNusLq)),
		    "sz_pind2sz() does not reverse sz_psz2ind(): pind=%u -->"
		    " size_class=%zu --> pind=%u --> size_class=%zu", BGpN_,
		    krNusLq, NU7aYDmJrTafZ(krNusLq),
		    UIwlAdKp2ICbj(NU7aYDmJrTafZ(krNusLq)));

		if (krNusLq == xKzzWp4i) {
			kh3uAhUHa(aUw29O_rQ09, NU7aYDmJrTafZ(krNusLq + 1),
			    "Next size_class does not round up properly");
		} else {
			kh3uAhUHa(BGpN_ + 1, NU7aYDmJrTafZ(krNusLq + 1),
			    "Next size_class does not round up properly");
		}

		OrN2zvSllb5(krNusLq, (BGpN_ > 0) ?
		    wl8fHn(UIwlAdKp2ICbj(BGpN_-1)+1) : wl8fHn(1),
		    "sz_psz2u() does not round up to size class");
		OrN2zvSllb5(krNusLq, wl8fHn(krNusLq-1),
		    "sz_psz2u() does not round up to size class");
		OrN2zvSllb5(krNusLq, wl8fHn(krNusLq),
		    "sz_psz2u() does not compute same size class");
		OrN2zvSllb5(wl8fHn(krNusLq+1), UIwlAdKp2ICbj(BGpN_+1),
		    "sz_psz2u() does not round up to next size class");
	}

	kh3uAhUHa(BGpN_, NU7aYDmJrTafZ(UIwlAdKp2ICbj(BGpN_)),
	    "sz_psz2ind() does not reverse sz_pind2sz()");
	OrN2zvSllb5(Oxt82D7YhSOk, UIwlAdKp2ICbj(NU7aYDmJrTafZ(Oxt82D7YhSOk)),
	    "sz_pind2sz() does not reverse sz_psz2ind()");

	OrN2zvSllb5(krNusLq, wl8fHn(UIwlAdKp2ICbj(BGpN_-1)+1),
	    "sz_psz2u() does not round up to size class");
	OrN2zvSllb5(krNusLq, wl8fHn(krNusLq-1),
	    "sz_psz2u() does not round up to size class");
	OrN2zvSllb5(krNusLq, wl8fHn(krNusLq),
	    "sz_psz2u() does not compute same size class");
}
lJD2n4a

Giub(J9cyK) {
	RukpkN1K_wZ s9Ic, Oxt82D7YhSOk;

	s9Ic = WXc12dLXJD5R();
	Oxt82D7YhSOk = s9Ic + oYAA3e;

	kh3uAhUHa(m_6YpXNvIVy0(s9Ic+1), sxsyUEAm,
	    "sz_size2index() should return NSIZES on overflow");
	kh3uAhUHa(m_6YpXNvIVy0(Lvpsj2Of(ZGa1l37fx)+1), sxsyUEAm,
	    "sz_size2index() should return NSIZES on overflow");
	kh3uAhUHa(m_6YpXNvIVy0(YGpTLPBY8), sxsyUEAm,
	    "sz_size2index() should return NSIZES on overflow");

	OrN2zvSllb5(G6kdQY(s9Ic+1), 0,
	    "sz_s2u() should return 0 for unsupported size");
	OrN2zvSllb5(G6kdQY(Lvpsj2Of(ZGa1l37fx)+1), 0,
	    "sz_s2u() should return 0 for unsupported size");
	OrN2zvSllb5(G6kdQY(YGpTLPBY8), 0,
	    "sz_s2u() should return 0 on overflow");

	kh3uAhUHa(NU7aYDmJrTafZ(s9Ic+1), aUw29O_rQ09,
	    "sz_psz2ind() should return NPSIZES on overflow");
	kh3uAhUHa(NU7aYDmJrTafZ(Lvpsj2Of(ZGa1l37fx)+1), aUw29O_rQ09,
	    "sz_psz2ind() should return NPSIZES on overflow");
	kh3uAhUHa(NU7aYDmJrTafZ(YGpTLPBY8), aUw29O_rQ09,
	    "sz_psz2ind() should return NPSIZES on overflow");

	OrN2zvSllb5(wl8fHn(s9Ic+1), Oxt82D7YhSOk,
	    "sz_psz2u() should return (LARGE_MAXCLASS + PAGE) for unsupported"
	    " size");
	OrN2zvSllb5(wl8fHn(Lvpsj2Of(ZGa1l37fx)+1), Oxt82D7YhSOk,
	    "sz_psz2u() should return (LARGE_MAXCLASS + PAGE) for unsupported "
	    "size");
	OrN2zvSllb5(wl8fHn(YGpTLPBY8), Oxt82D7YhSOk,
	    "sz_psz2u() should return (LARGE_MAXCLASS + PAGE) on overflow");
}
lJD2n4a

int
mEGUi9h(void) {
	return jC104Jw(
	    WgrjBCk,
	    mX0gQI34tOHC,
	    J9cyK);
}
