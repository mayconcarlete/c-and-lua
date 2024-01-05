#include <stdio.h>
#include <stdlib.h>

#include "../lib/lua/src/lua.h"
#include "../lib/lua/src/lualib.h"
#include "../lib/lua/src/lauxlib.h"


void add_variable_to_lua_global(){
// pass a new variable with value 42 to lua gloabal state;
  lua_State* L = luaL_newstate();

  luaL_dostring(L, "x = 42");

  lua_getglobal(L, "x");

  lua_Number num = lua_tonumber(L, 1);
  printf("Number is: %d\n", (int)num);

  int sizeStack = lua_gettop(L);
  printf("Size of the stack: %d\n", sizeStack);

  lua_close(L);
}

void push_number_to_lua_stack(){
// push the number 42, 52, 62 to the stack;
  lua_State*L = luaL_newstate();

  lua_pushnumber(L, 42);
  lua_pushnumber(L, 52);
  lua_pushnumber(L, 62);

  // stack
  lua_Number a = lua_tonumber(L, -1); // 62
  lua_Number b = lua_tonumber(L, -2); // 52
  lua_Number c = lua_tonumber(L, -3); // 42

  printf("a: %d b: %d c: %d\n",(int)a, (int)b, (int)c);
  
  int stackSize = lua_gettop(L);
  printf("Stack size: %d\n", stackSize);
  
  lua_close(L);
}

int main(){



  return 0;
}