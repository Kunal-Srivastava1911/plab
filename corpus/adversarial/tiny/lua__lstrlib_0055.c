    state->init = 1;
    luaL_buffinit(L, &state->B);
  }
  luaL_addlstring(&state->B, (const char *)b, size);
  return 0;
}


static int str_dump (lua_State *L) {
  struct str_Writer state;
  int strip = lua_toboolean(L, 2);
  luaL_checktype(L, 1, LUA_TFUNCTION);
  lua_settop(L, 1);  /* ensure function is on the top of the stack */
  state.init = 0;
  if (l_unlikely(lua_dump(L, writer, &state, strip) != 0))
    return luaL_error(L, "unable to dump given function");
  luaL_pushresult(&state.B);
  return 1;
}



/*
** {======================================================
** METAMETHODS
** =======================================================
*/

#if defined(LUA_NOCVTS2N)	/* { */

/* no coercion from strings to numbers */

static const luaL_Reg stringmetamethods[] = {
  {"__index", NULL},  /* placeholder */
  {NULL, NULL}
};

#else		/* }{ */

static int tonum (lua_State *L, int arg) {
