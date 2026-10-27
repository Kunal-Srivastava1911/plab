    printobj(G(L), obj);
    printf("\n");
  }
  return 0;
}


static int gc_state (lua_State *L) {
  static const char *statenames[] = {
    "propagate", "atomic", "enteratomic", "sweepallgc", "sweepfinobj",
    "sweeptobefnz", "sweepend", "callfin", "pause", ""};
  static const int states[] = {
    GCSpropagate, GCSenteratomic, GCSatomic, GCSswpallgc, GCSswpfinobj,
    GCSswptobefnz, GCSswpend, GCScallfin, GCSpause, -1};
  int option = states[luaL_checkoption(L, 1, "", statenames)];
  if (option == -1) {
    lua_pushstring(L, statenames[G(L)->gcstate]);
    return 1;
  }
  else {
    global_State *g = G(L);
    if (G(L)->gckind == KGC_GEN)
      luaL_error(L, "cannot change states in generational mode");
    lua_lock(L);
    if (option < g->gcstate) {  /* must cross 'pause'? */
      luaC_runtilstate(L, bitmask(GCSpause));  /* run until pause */
    }
    luaC_runtilstate(L, bitmask(option));
    lua_assert(G(L)->gcstate == option);
    lua_unlock(L);
