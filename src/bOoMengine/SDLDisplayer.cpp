#include "SDLDisplayer.hpp"
#include <iostream>

namespace bOoM {

SDL_Rect to_SDL_Rect( bOoM::rect const& r )
	{ return { int(r.v.x), int(r.v.y), int(r.s.x), int(r.s.y) }; }

SDLDisplayer::SDLDisplayer( bOoM::size_t_2 window_size, bOoM::aabr const& screen_zone, std::chrono::milliseconds refresh_span, std::vector<shared_ptr<bOoM::Entity>> const& starting_entities)
	: refresh_span(refresh_span), window_size(window_size), screen_zone(screen_zone), entities(starting_entities)
{
	//FIXME check return errors
	SDL_CreateWindowAndRenderer(window_size.x, window_size.y, SDL_WINDOW_SHOWN, &sdl_window, &sdl_renderer);
	if( sdl_window == NULL || sdl_renderer == NULL )
		throw std::runtime_error("SDL failed to create a window.");
	sdl_screen_texture = SDL_CreateTexture(sdl_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, window_size.x, window_size.y);
	sdl_screen_surface = SDL_CreateRGBSurface(0, //unused flags
			window_size.x, window_size.y, //dimentions
			bOoM::bit_depth(), //pixel format
			0, 0, 0, 0 //pixel masks
	);
	
	//Comment the following line if you do not wish to use transparency in the screen texture so that on can see the clear color.
	//SDL_SetTextureBlendMode(sdl_screen_texture, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 0, 255);
}

SDLDisplayer::~SDLDisplayer()
{
	SDL_DestroyRenderer(sdl_renderer);
	SDL_DestroyWindow(sdl_window);
	SDL_DestroyTexture(sdl_screen_texture);
	SDL_FreeSurface(sdl_screen_surface);
}

void SDLDisplayer::loop()
{
	bool looping = true;
	
	std::chrono::milliseconds remaining_span(0);
	std::chrono::steady_clock::time_point last_time;
	
	SDL_Event e;
	bool screenIsMoving;
	bOoM::real2 moveOriginalQixel;
	bOoM::aabr moveOriginalScreen;

	//int iters=32;
	
	while( looping )
	{
		//std::cout << "New loop" << std::endl;
		//if(--iters < 0)
		//{
		//	looping = false;
		//	break;
		//}
		while( remaining_span > std::chrono::milliseconds(0) && SDL_PollEvent(&e) == 1)
		{
			//std::cout << "Event type " << e.type << std::endl;
			switch(e.type)
			{
				case SDL_QUIT:
				case SDL_KEYDOWN:
					looping = false;
					return; //break;
				case SDL_MOUSEBUTTONDOWN:
					switch(e.button.button)
					{
						case SDL_BUTTON_LEFT:
						{
							bOoM::size_t_2 p( e.button.x, window_size.y -1 -e.button.y );
							std::cout <<"Position is " <<to_physical_coordinates(screen_zone, window_size, p) <<" in bOoM and " <<p <<" on screen." <<std::endl;
							break;
						}
						case SDL_BUTTON_RIGHT:
							screenIsMoving = true;
							moveOriginalScreen = screen_zone;
							moveOriginalQixel = to_physical_coordinates(moveOriginalScreen, window_size, bOoM::size_t_2(e.button.x,e.button.y) );
							break;
					}
					break;
				case SDL_MOUSEBUTTONUP:
					switch(e.button.button)
					{
						case SDL_BUTTON_RIGHT:
							screenIsMoving = false;
							break;
					}
					break;
				case SDL_MOUSEMOTION:
					if( screenIsMoving )
					{
						bOoM::real2 currentQixel = to_physical_coordinates(moveOriginalScreen, window_size, bOoM::size_t_2(e.button.x,e.button.y) );
						screen_zone.v = moveOriginalScreen.v + (moveOriginalQixel-currentQixel);
					}
					break;
			}
		}
		render();
		
		std::chrono::steady_clock::time_point current_time= std::chrono::steady_clock::now();
		remaining_span = std::max(
				refresh_span -std::chrono::duration_cast<std::chrono::milliseconds>(current_time - last_time),
				std::chrono::milliseconds(0) );
		last_time = current_time;
		
		SDL_Delay(remaining_span.count());

	}
	remaining_span = refresh_span;
}

void SDLDisplayer::render()
{
	//std::cout << "Generation of a new image" << std::endl;
	SDL_FillRect( sdl_screen_surface, NULL, SDL_MapRGBA(sdl_screen_surface->format,32,0,32,0) );

	for( shared_ptr<bOoM::Entity> e : entities )
	{
	}
	
	if(SDL_UpdateTexture(sdl_screen_texture, NULL, sdl_screen_surface->pixels, window_size.x*4 ) < 0 )
	{
		std::cout << "Error: SDL_UpdateTexture: " << SDL_GetError() << std::endl;
	}

	SDL_RenderClear(sdl_renderer);
	SDL_RenderCopy(sdl_renderer, sdl_screen_texture, NULL, NULL);
	SDL_RenderPresent(sdl_renderer);

}



} //namespace bOoM

