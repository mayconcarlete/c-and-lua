#include <stdlib.h>
#include <stdio.h>

#include "../lib/lua/src/lua.h"
#include "../lib/lua/src/lualib.h"
#include "../lib/lua/src/lauxlib.h"


typedef struct {
  int id;
  int signature;
}Entity;

typedef struct {
  int entityCounter;
  int listSize;
  Entity* listOfEntities;
} EntityManager;


EntityManager* Create_Entity_Manager(){
   EntityManager* this = (EntityManager*)calloc(1, sizeof(EntityManager));
   this->entityCounter = 0;
   this->listSize = 1;
   this->listOfEntities = (Entity*)calloc(this->listSize, sizeof(Entity));

   return this;
}

Entity* Add_Entity_By_Manager(EntityManager* entityManager, int id, int signature){
    entityManager->listOfEntities[entityManager->entityCounter].id = id;
    entityManager->listOfEntities[entityManager->entityCounter].signature = signature;
    entityManager->entityCounter++;
    return &entityManager->listOfEntities[entityManager->entityCounter];
}

int Add_Entity(lua_State* L){
  printf("Entrei aqui!\n");
  EntityManager* entityManager = (EntityManager*)lua_touserdata(L, lua_upvalueindex(1));
  lua_Number id = lua_tonumber(L, -2);
  lua_Number signature = lua_tonumber(L, -1);
  Entity* entity;
  entity = Add_Entity_By_Manager(entityManager, (int)id, (int)signature);
  
  printf("Entity Added id: %d - signature: %d\n", entity->id, entity->signature);

  return 0;
}


int main(){
  EntityManager* entityManager = Create_Entity_Manager();

  lua_State* L = luaL_newstate();

  lua_pushlightuserdata(L, entityManager);
  lua_pushcclosure(L, Add_Entity, 1);
  lua_setglobal(L, "Add_Entity");
  luaL_dofile(L, "./scripts/11-lua-classes.lua");

  lua_getglobal(L, "test");

  if(lua_isfunction(L, -1)){
    printf("Aqui ainda vai\n");
    lua_pcall(L, 0, 0, 0);
  }

  printf("Entity Counter: %d - List Size: %d\n", entityManager->entityCounter,entityManager->listSize );
  printf("Valores em entity manager: id: %d - signature: %d\n", entityManager->listOfEntities[0].id, entityManager->listOfEntities[0].signature);
  free(entityManager->listOfEntities);
  free(entityManager);
  lua_close(L);
  return 0;
}