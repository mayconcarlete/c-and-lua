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

void call_lua_function(){
  lua_State* L = luaL_newstate();
  
  if(luaL_dofile(L, "./scripts/sum.lua") != LUA_OK){
    printf("Error reading the file!\n");
  }

  lua_getglobal(L, "sum");


  if(lua_isfunction(L, -1)){
  // push the parameters of the function sum to the stack
  lua_pushnumber(L, 2);
  lua_pushnumber(L, 3);

  const int NUM_ARGS = 2;
  const int NUM_RETURNS = 1;

      lua_pcall(L, NUM_ARGS, NUM_RETURNS, 0);
      lua_Number response = lua_tonumber(L, -1);

      printf("The result of the function is: %d\n", (int)response);
  }

  lua_close(L);
}

int sum_from_c(lua_State* L){
  lua_Number num1 = lua_tonumber(L, -1);
  lua_Number num2 = lua_tonumber(L, -2);

  printf("Valor 1: %d\n", (int)num1);
  printf("Valor 2: %d\n", (int)num2);

  lua_pushnumber(L, (int)num1 + (int)num2); // push the sum to the stack ;

  return 1; // inform the quantity of values being pushed to the stack;
}

void call_c_function_from_lua(){
  lua_State* L = luaL_newstate(); 
  lua_pushcfunction(L, sum_from_c); // push the function to the stack;
  lua_setglobal(L, "sum_c"); // (register the function) the name of sum_from_c on global to be used on lua file;

  // execute sum-c file calling sum function
  if(luaL_dofile(L, "./scripts/sum-c.lua") != LUA_OK){
    printf("Error reading the file\n");
  }
  lua_getglobal(L, "Sum");

  if(lua_isfunction(L, -1)){
    lua_pcall(L, 0, 1, 0);
    lua_Number num = lua_tonumber(L, -1);

    printf("Valor: %d\n", (int)num);
  }

  lua_close(L);
}

int main(){

  call_c_function_from_lua();

  return 0;
}