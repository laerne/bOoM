#include "SimpleDisplayObject.hpp"
#include <iostream>
#include <stdexcept>
#include <thread>

namespace visualizer {

SimpleDisplayObject::SimpleDisplayObject(int window_width, int window_height, std::chrono::milliseconds refresh_span)
	: refresh_span(refresh_span)
{
	SDL_CreateWindowAndRenderer(window_width, window_height, SDL_WINDOW_SHOWN, &sdl_window, &sdl_renderer);
	if( sdl_window == NULL || sdl_renderer == NULL )
		throw std::runtime_error("SDL failed to create a window.");
	SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 0, 255);
}

SimpleDisplayObject::~SimpleDisplayObject()
	{}

void SimpleDisplayObject::loop()
{
	bool looping = true;
	
	std::chrono::milliseconds remaining_span(0);
	std::chrono::steady_clock::time_point last_time;
	
	SDL_Event e;
	
	while( looping )
	{
		std::cout << "New loop" << std::endl;
		while( remaining_span > std::chrono::milliseconds(0) && SDL_PollEvent(&e) == 1)
		{
			std::cout << "Event type " << e.type << std::endl;
			switch(e.type)
			{
				case SDL_QUIT:
				case SDL_KEYDOWN:
					looping = false;
					return;
					//break;
			}
		}
		
		SDL_RenderClear(sdl_renderer);
		std::cout << "Generation of a new image" << std::endl;
		SDL_RenderPresent(sdl_renderer);
		
		std::chrono::steady_clock::time_point current_time= std::chrono::steady_clock::now();
		remaining_span = std::max( 
				refresh_span -std::chrono::duration_cast<std::chrono::milliseconds>(current_time - last_time),
				std::chrono::milliseconds(0) );
		last_time = current_time;
		
		SDL_Delay(remaining_span.count());
	}
	remaining_span = refresh_span;
}

} //namespace visualizer

