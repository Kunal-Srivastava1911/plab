  luaL_argcheck(L, L1 != NULL, 1, "state expected");
  return L1;
}


static int loadlib (lua_State *L) {
  static const luaL_Reg libs[] = {
    {LUA_GNAME, luaopen_base},
    {"coroutine", luaopen_coroutine},
    {"debug", luaopen_debug},
    {"io", luaopen_io},
    {"os", luaopen_os},
    {"math", luaopen_math},
    {"string", luaopen_string},
    {"table", luaopen_table},
    {"T", luaB_opentests},
    {NULL, NULL}
  };
  lua_State *L1 = getstate(L);
  int i;
  luaL_requiref(L1, "package", luaopen_package, 0);
  lua_assert(lua_type(L1, -1) == LUA_TTABLE);
  /* 'requiref' should not reload module already loaded... */
  luaL_requiref(L1, "package", NULL, 1);  /* seg. fault if it reloads */
  /* ...but should return the same module */
  lua_assert(lua_compare(L1, -1, -2, LUA_OPEQ));
  luaL_getsubtable(L1, LUA_REGISTRYINDEX, LUA_PRELOAD_TABLE);
  for (i = 0; libs[i].name; i++) {
    lua_pushcfunction(L1, libs[i].func);
