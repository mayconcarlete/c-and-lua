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

void calling_lua_function(void){
  lua_State* L = luaL_newstate();
  if(luaL_dofile(L, "./scripts/pitagoras.lua") != LUA_OK){
    luaL_error(L, "Error: %s \n", lua_tostring(L, -1));
  } // get and parse pitagoras file if its ok proceed
  lua_getglobal(L, "pitagoras"); // get the global variable pitagoras and push to stack
  if(lua_isfunction(L, -1)){ // make sure that the top value on stack is a function
    lua_pushnumber(L, 3); // first function argument
    lua_pushnumber(L, 4); // second function argument
    const int num_of_arguments = 2;
    const int num_of_returns = 1;
    // esse zero como ultimo argumento é referente a tratativas de erro.
    if(lua_pcall(L, num_of_arguments, num_of_returns, 0) != LUA_OK){ // call the function
      // log the error
    } else{
    lua_Number pitagoras_result = lua_tonumber(L, -1); // get the result from the stack
    printf("Resultado de pitagoras é: %.2f", (float)pitagoras_result);
    }
  }
  lua_close(L);
}

int native_pitagoras(lua_State* L){
  lua_Number b = lua_tonumber(L, -1); // b first because its on top of the stack
  lua_Number a = lua_tonumber(L, -2); // a the second item from the stack

  lua_Number result = a*a + b*b;
  lua_pushnumber(L, result);
  return 1; // how manu values the function is returning as result to the stack
}

void calling_c_function_from_lua(void){
  lua_State* L = luaL_newstate();

  lua_pushcfunction(L, native_pitagoras);
  lua_setglobal(L, "native_pitagoras"); // expose the name of the function to lua script.

  luaL_dofile(L, "./scripts/pitagoras-c-native.lua"); // load the lua file
  lua_getglobal(L, "pitagoras"); // get the desired function to execute

  if(lua_isfunction(L, -1)){ // check if is a function
    lua_pushnumber(L, 3); // 1st function argument
    lua_pushnumber(L, 4); // 2nd function argument

    const int NUM_ARGS = 2;
    const int NUM_RETURNS = 1;
    lua_pcall(L, NUM_ARGS, NUM_RETURNS, 0); // call the function
    lua_Number pitagoras_result = lua_tonumber(L, -1);

    printf("Native pitagoras result: %.2f\n", (float)pitagoras_result);
  }
  lua_close(L);
}

int main(int argc, char **argv){
  // lua_example_dofile();
  // lua_example_get_var();
  // lua_stack_example();
  // calling_lua_function();
  calling_c_function_from_lua();
  return 0;
}