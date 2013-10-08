#include "display.hpp"
#include <iostream>

#include <SDL2/SDL.h>

SDL_Window *sdlWindow;
SDL_Renderer *sdlRenderer;

int init_display()
{
	if( SDL_Init(SDL_INIT_VIDEO) != 0)
		return -1;
	SDL_CreateWindowAndRenderer(800, 600, SDL_WINDOW_SHOWN, &sdlWindow, &sdlRenderer);
	if( sdlWindow == NULL || sdlRenderer == NULL )
		return -2;
	atexit(SDL_Quit);

	SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 255);
	SDL_RenderClear(sdlRenderer);

  return 0;
}

int term_display()
{
	SDL_Quit();
	return 0;
}

int render_display()
{
	SDL_RenderPresent(sdlRenderer);
	return 0;
}
