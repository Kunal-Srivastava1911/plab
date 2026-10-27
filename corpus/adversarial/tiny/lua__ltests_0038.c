    lua_pushinteger(L, allocsizenode(t));
    lua_pushinteger(L, isdummy(t) ? 0 : t->lastfree - t->node);
    lua_pushinteger(L, t->alimit);
    return 4;
  }
  else if ((unsigned int)i < asize) {
    lua_pushinteger(L, i);
    pushobject(L, &t->array[i]);
    lua_pushnil(L);
  }
  else if ((i -= asize) < sizenode(t)) {
    TValue k;
    getnodekey(L, &k, gnode(t, i));
    if (!isempty(gval(gnode(t, i))) ||
        ttisnil(&k) ||
        ttisnumber(&k)) {
      pushobject(L, &k);
    }
    else
      lua_pushliteral(L, "<undef>");
    pushobject(L, gval(gnode(t, i)));
    if (gnext(&t->node[i]) != 0)
      lua_pushinteger(L, gnext(&t->node[i]));
    else
      lua_pushnil(L);
  }
  return 3;
}


static int string_query (lua_State *L) {
  stringtable *tb = &G(L)->strt;
  int s = cast_int(luaL_optinteger(L, 1, 0)) - 1;
  if (s == -1) {
    lua_pushinteger(L ,tb->size);
    lua_pushinteger(L ,tb->nuse);
    return 2;
  }
  else if (s < tb->size) {
