#include <stdio.h>
#include "../lib/lua/src/lua.h"
#include "../lib/lua/src/lualib.h"
#include "../lib/lua/src/lauxlib.h"

void lua_example_dofile(void){
  /**
   * @brief call a lua file.
   *
   */
  lua_State* L = luaL_newstate();
  luaL_openlibs(L);
  luaL_dofile(L, "./scripts/myscript.lua");
  lua_close(L);
}

void lua_example_get_var(void){
  lua_State* L = luaL_newstate();
  luaL_dostring(L, "some_var = 486");
  lua_getglobal(L, "some_var");
  lua_Number some_var_in_c = lua_tonumber(L, -1);
  printf("The value of some var in C: %d \n", (int)some_var_in_c);
  lua_close(L);
}

void lua_stack_example(void){
  lua_State* L = luaL_newstate();
  lua_pushnumber(L, 100);
  lua_pushnumber(L, 200);
  lua_pushnumber(L, 300);

  lua_Number element;
  element = lua_tonumber(L, -1);
  printf("The last added element in pos 3 is %d: \n", (int)element);
  lua_remove(L, 2);
  element = lua_tonumber(L, 2);
  printf("The last added element in pos 2 is %d: \n", (int)element);
  lua_close(L);
}

int main(int argc, char **argv){
  // lua_example_dofile();
  // lua_example_get_var();
  // lua_stack_example();
  return 0;
}