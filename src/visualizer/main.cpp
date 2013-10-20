//Trivial displayer <NOT THREAD SAFE>
#include <cppa/cppa.hpp>
#include <SDL2/SDL.h>

#include <chrono>
#include <exception>
#include <iostream>

#include "SimpleDisplayActor.hpp"
#include "SimpleInputActor.hpp"

using namespace bOoM;

void on_crash_exit()
{
	cppa::shutdown();
	SDL_Quit();
}

int main(int argc, char **argv){
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_EVENTS ) != 0)
		cppa::aout << "SDL failed to initiate." << std::endl;
	atexit(on_crash_exit);

	cppa::actor_ptr a_display = cppa::spawn<SimpleDisplayActor>( 1024, 768, std::chrono::milliseconds(100) );
	cppa::actor_ptr a_keyboardManager = cppa::spawn<SimpleInputActor, cppa::detached>( cppa::self );
	
	/*********************************************************************************************************************
	
	SDL_Window *sdl_window;
	SDL_Renderer *sdl_renderer;
	
	std::chrono::steady_clock::duration refresh_span = std::chrono::milliseconds(100);
	std::chrono::steady_clock::duration remaining_span(0);
	std::chrono::steady_clock::time_point last_time;
	
	SDL_CreateWindowAndRenderer(1024, 768, SDL_WINDOW_SHOWN, &sdl_window, &sdl_renderer);
	if( sdl_window == NULL || sdl_renderer == NULL )
		throw std::runtime_error("SDL failed to create a window.");
	SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 0, 255);
	
	while(true);
	(
		cppa::on( cppa::atom("renderOK"), cppa::arg_match ) >> [&]()
		{
			std::chrono::steady_clock::time_point current_time= std::chrono::steady_clock::now();
			remaining_span = current_time - last_time;
			last_time = current_time;
		},
		cppa::on( cppa::atom("die") ) >> [&]()
		{
			cppa::self->quit();
		},
		cppa::after( std::chrono::duration_cast<std::chrono::milliseconds>(remaining_span) ) >> [&]()
		{
			SDL_RenderClear(sdl_renderer);
			//cppa::aout << "requested to generate a new image" << std::endl;
			SDL_RenderPresent(sdl_renderer);
			//reset remaining span
			remaining_span = refresh_span;
		}
	);
	
	/*********************************************************************************************************************/

	cppa::await_all_others_done();
	cppa::shutdown();
	SDL_Quit();

	return 0;
}
