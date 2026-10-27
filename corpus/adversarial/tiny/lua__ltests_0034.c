  else if (lua_isnumber(L, 1)) {
    unsigned long limit = cast(unsigned long, luaL_checkinteger(L, 1));
    if (limit == 0) limit = ULONG_MAX;
    l_memcontrol.memlimit = limit;
    return 0;
  }
  else {
    const char *t = luaL_checkstring(L, 1);
    int i;
    for (i = LUA_NUMTAGS - 1; i >= 0; i--) {
      if (strcmp(t, ttypename(i)) == 0) {
        lua_pushinteger(L, l_memcontrol.objcount[i]);
        return 1;
      }
    }
    return luaL_error(L, "unknown type '%s'", t);
  }
}


static int alloc_count (lua_State *L) {
  if (lua_isnone(L, 1))
    l_memcontrol.countlimit = ~0L;
  else
    l_memcontrol.countlimit = luaL_checkinteger(L, 1);
  return 0;
}


static int alloc_failnext (lua_State *L) {
  UNUSED(L);
  l_memcontrol.failnext = 1;
  return 0;
}


static int settrick (lua_State *L) {
  if (ttisnil(obj_at(L, 1)))
    l_Trick = NULL;
  else
    l_Trick = gcvalue(obj_at(L, 1));
  return 0;
}


static int gc_color (lua_State *L) {
