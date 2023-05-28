#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "../lib/lua/src/lua.h"
#include "../lib/lua/src/lualib.h"
#include "../lib/lua/src/lauxlib.h"

#define FALSE 0
#define TRUE 1
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 640


SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
int is_running = FALSE;

int initialize_window(void){
  if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
    fprintf(stderr, "Erro initializing SDL. \n");
    return FALSE;
  }
  window = SDL_CreateWindow(
    "Minha janela",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    WINDOW_WIDTH,
    WINDOW_HEIGHT,
    SDL_WINDOW_RESIZABLE
  );

  if(!window){
    fprintf(stderr, "Error creating SDL. \n");
    return FALSE;
  }
  renderer = SDL_CreateRenderer(
    window,
    -1,
    0
  );
  if(!renderer){
    fprintf(stderr, "Error creating renderer. \n");
    return FALSE;
  }
  return TRUE;
}

void process_input(void){
  SDL_Event event;
  SDL_PollEvent(&event);
  switch (event.type)
  {
  case SDL_QUIT: {
    is_running = FALSE;
    break;
  }
  case SDL_KEYDOWN:{
    if(event.key.keysym.sym == SDLK_ESCAPE){
      is_running = FALSE;
    }
  }

  default:
    break;
  }
}

void update(void){

}

void render(void){

}

void destroy_window(void){
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

int main(int argc, char *argv[]){
  is_running = initialize_window();
  printf("False: %d\n", is_running);
  while(is_running){
    process_input();
    update();
    render();
  }
  destroy_window();
  return 0;
}