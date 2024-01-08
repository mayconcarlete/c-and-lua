#include <stdio.h>
#include <stdlib.h>

#include "../lib/lua/src/lua.h"
#include "../lib/lua/src/lualib.h"
#include "../lib/lua/src/lauxlib.h"

#define LUA_FILE_PATH "./scripts/01-init.lua"


int Init_Game(lua_State* L){
    lua_pushnumber(L, 2);

    return 1;
}


int main(){
    lua_State* L = luaL_newstate();

    lua_pushcfunction(L, Init_Game);
    lua_setglobal(L, "init_game");


    luaL_dofile(L, LUA_FILE_PATH);
    
    lua_getglobal(L, "init");
    lua_isnumber(L, -1);

    printf("Valor init: %d\n", (int)lua_tonumber(L, -1));


    lua_close(L);
    return 0;
}