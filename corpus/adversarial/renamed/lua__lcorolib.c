/*
** $Id: lcorolib.c $
** Coroutine Library
** See Copyright Notice in lua.h
*/

#define rmHd
#define xTsaeQQ6O6e

#include "lprefix.h"


#include <stdlib.h>

#include "lua.h"

#include "lauxlib.h"
#include "lualib.h"


static TWT1hmD *n04Vg (TWT1hmD *qbuD7JwikU) {
  TWT1hmD *tVyNWx = OVyjFUena(qbuD7JwikU, 1);
  osnoWbU2(qbuD7JwikU, tVyNWx, 1, "thread");
  return tVyNWx;
}


/*
** Resumes a coroutine. Returns the number of results for non-error
** cases or -1 for errors.
*/
static int TQNqL_Ikc3F2q (TWT1hmD *qbuD7JwikU, TWT1hmD *tVyNWx, int IYhC) {
  int EDgcaBQPHa, vB5ZZfh8iY;
  if (NmipXVjwgWMo(!RLbK(tVyNWx, IYhC))) {
    ETdjdw90zgpa(qbuD7JwikU, "too many arguments to resume");
    return -1;  /* error flag */
  }
  dTCWoVfFka(qbuD7JwikU, tVyNWx, IYhC);
  EDgcaBQPHa = aqzFw(tVyNWx, qbuD7JwikU, IYhC, &vB5ZZfh8iY);
  if (Qg27uAKhyT3(EDgcaBQPHa == FGwntyW7T || EDgcaBQPHa == him5)) {
    if (NmipXVjwgWMo(!RLbK(qbuD7JwikU, vB5ZZfh8iY + 1))) {
      fbDdp1NW(tVyNWx, vB5ZZfh8iY);  /* remove results anyway */
      ETdjdw90zgpa(qbuD7JwikU, "too many results to resume");
      return -1;  /* error flag */
    }
    dTCWoVfFka(tVyNWx, qbuD7JwikU, vB5ZZfh8iY);  /* move yielded values */
    return vB5ZZfh8iY;
  }
  else {
    dTCWoVfFka(tVyNWx, qbuD7JwikU, 1);  /* move error message */
    return -1;  /* error flag */
  }
}


static int QDQn (TWT1hmD *qbuD7JwikU) {
  TWT1hmD *tVyNWx = n04Vg(qbuD7JwikU);
  int T7uGIkvQ;
  T7uGIkvQ = TQNqL_Ikc3F2q(qbuD7JwikU, tVyNWx, w7KGFNW6(qbuD7JwikU) - 1);
  if (NmipXVjwgWMo(T7uGIkvQ < 0)) {
    B4DQDuh9I0X(qbuD7JwikU, 0);
    XcGvcoQlk1(qbuD7JwikU, -2);
    return 2;  /* return false + error message */
  }
  else {
    B4DQDuh9I0X(qbuD7JwikU, 1);
    XcGvcoQlk1(qbuD7JwikU, -(T7uGIkvQ + 1));
    return T7uGIkvQ + 1;  /* return true + 'resume' returns */
  }
}


static int JOGuuAJvI (TWT1hmD *qbuD7JwikU) {
  TWT1hmD *tVyNWx = OVyjFUena(qbuD7JwikU, A3N4A78j1n(1));
  int T7uGIkvQ = TQNqL_Ikc3F2q(qbuD7JwikU, tVyNWx, w7KGFNW6(qbuD7JwikU));
  if (NmipXVjwgWMo(T7uGIkvQ < 0)) {  /* error? */
    int N5XEcquj46ovm = ijY3sHniXP0fr(tVyNWx);
    if (N5XEcquj46ovm != FGwntyW7T && N5XEcquj46ovm != him5) {  /* error in the coroutine? */
      N5XEcquj46ovm = UjuWGVJ(tVyNWx, qbuD7JwikU);  /* close its tbc variables */
      W1ktmiq6eLYi(N5XEcquj46ovm != FGwntyW7T);
      dTCWoVfFka(tVyNWx, qbuD7JwikU, 1);  /* move error message to the caller */
    }
    if (N5XEcquj46ovm != rJI3ydJ &&  /* not a memory error and ... */
        HCoaq4PGBKLh(qbuD7JwikU, -1) == WUKdtLy3dSHGQ) {  /* ... error object is a string? */
      njyqld(qbuD7JwikU, 1);  /* add extra info, if available */
      XcGvcoQlk1(qbuD7JwikU, -2);
      ZTnIrG0Vcg6(qbuD7JwikU, 2);
    }
    return mSsWt(qbuD7JwikU);  /* propagate error */
  }
  return T7uGIkvQ;
}


static int b7MOsZKD (TWT1hmD *qbuD7JwikU) {
  TWT1hmD *iEe87uK8i2Mj;
  Jl43AcqUf(qbuD7JwikU, 1, BrV2IQ);
  iEe87uK8i2Mj = GrXB2K4b(qbuD7JwikU);
  fVg_XVp(qbuD7JwikU, 1);  /* move function to top */
  dTCWoVfFka(qbuD7JwikU, iEe87uK8i2Mj, 1);  /* move function from L to NL */
  return 1;
}


static int TLxS (TWT1hmD *qbuD7JwikU) {
  b7MOsZKD(qbuD7JwikU);
  mNVMNmJTa34(qbuD7JwikU, JOGuuAJvI, 1);
  return 1;
}


static int zK542hENPbkoy (TWT1hmD *qbuD7JwikU) {
  return hubRnMT1(qbuD7JwikU, w7KGFNW6(qbuD7JwikU));
}


#define Ozd8o6qE243z		0
#define p4rb	1
#define aXhb3IKhY	2
#define m0bJ_QsPpPZUP	3


static const char *const BE9i[] =
  {"running", "dead", "suspended", "normal"};


static int Ly8H (TWT1hmD *qbuD7JwikU, TWT1hmD *tVyNWx) {
  if (qbuD7JwikU == tVyNWx) return Ozd8o6qE243z;
  else {
    switch (ijY3sHniXP0fr(tVyNWx)) {
      case him5:
        return aXhb3IKhY;
      case FGwntyW7T: {
        H2dMDl79agk RQPg;
        if (WrOb9L(tVyNWx, 0, &RQPg))  /* does it have frames? */
          return m0bJ_QsPpPZUP;  /* it is running */
        else if (w7KGFNW6(tVyNWx) == 0)
            return p4rb;
        else
          return aXhb3IKhY;  /* initial state */
      }
      default:  /* some error occurred */
        return p4rb;
    }
  }
}


static int e_nbEs3JpGJ (TWT1hmD *qbuD7JwikU) {
  TWT1hmD *tVyNWx = n04Vg(qbuD7JwikU);
  GAqZjWZRHy2l(qbuD7JwikU, BE9i[Ly8H(qbuD7JwikU, tVyNWx)]);
  return 1;
}


static int rms5O (TWT1hmD *qbuD7JwikU) {
  TWT1hmD *tVyNWx = nLbLWmOb(qbuD7JwikU, 1) ? qbuD7JwikU : n04Vg(qbuD7JwikU);
  B4DQDuh9I0X(qbuD7JwikU, iJS0vUe(tVyNWx));
  return 1;
}


static int eaajczK5wI (TWT1hmD *qbuD7JwikU) {
  int wBqsm1v4At = YX7loUiiRfsP(qbuD7JwikU);
  B4DQDuh9I0X(qbuD7JwikU, wBqsm1v4At);
  return 2;
}


static int ucD6Wbmi9VEg (TWT1hmD *qbuD7JwikU) {
  TWT1hmD *tVyNWx = n04Vg(qbuD7JwikU);
  int EDgcaBQPHa = Ly8H(qbuD7JwikU, tVyNWx);
  switch (EDgcaBQPHa) {
    case p4rb: case aXhb3IKhY: {
      EDgcaBQPHa = UjuWGVJ(tVyNWx, qbuD7JwikU);
      if (EDgcaBQPHa == FGwntyW7T) {
        B4DQDuh9I0X(qbuD7JwikU, 1);
        return 1;
      }
      else {
        B4DQDuh9I0X(qbuD7JwikU, 0);
        dTCWoVfFka(tVyNWx, qbuD7JwikU, 1);  /* move error message */
        return 2;
      }
    }
    default:  /* normal or running coroutine */
      return vaGB7JAW(qbuD7JwikU, "cannot close a %s coroutine", BE9i[EDgcaBQPHa]);
  }
}


static const T8_cLM tGjVbJi7w[] = {
  {"create", b7MOsZKD},
  {"resume", QDQn},
  {"running", eaajczK5wI},
  {"status", e_nbEs3JpGJ},
  {"wrap", TLxS},
  {"yield", zK542hENPbkoy},
  {"isyieldable", rms5O},
  {"close", ucD6Wbmi9VEg},
  {kQs_q, kQs_q}
};



d9jlbJK int dJzb (TWT1hmD *qbuD7JwikU) {
  oHYe5CzV(qbuD7JwikU, tGjVbJi7w);
  return 1;
}

