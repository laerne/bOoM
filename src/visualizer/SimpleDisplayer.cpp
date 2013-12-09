#include "SimpleDisplayer.hpp"
#include <bOoM/entities/Entity.hpp>
#include <iostream>
#include <stdexcept>
#include <thread>

namespace visualizer {

//Small utility to cast
SDL_Rect to_SDL_Rect( bOoM::rect const& r ) { return { static_cast<int>(r.v.x), static_cast<int>(r.v.y), static_cast<int>(r.s.x), static_cast<int>(r.s.y) }; }

SimpleDisplayer::SimpleDisplayer( bOoM::size_t_2 window_size, bOoM::aabr const& screen_zone, std::chrono::milliseconds refresh_span, std::vector<shared_ptr<bOoM::Entity>> const& starting_entities)
	: refresh_span(refresh_span), window_size(window_size), screen_zone(screen_zone), entities(starting_entities)
{
	//FIXME check return errors
	SDL_CreateWindowAndRenderer(window_size.x, window_size.y, SDL_WINDOW_SHOWN, &sdl_window, &sdl_renderer);
	if( sdl_window == NULL || sdl_renderer == NULL )
		throw std::runtime_error("SDL failed to create a window.");
	sdl_screen_texture = SDL_CreateTexture(sdl_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, window_size.x, window_size.y);
	sdl_screen_surface = SDL_CreateRGBSurface(0, //unused flags
			window_size.x, window_size.y,            //dimentions
			bOoM::Image::depth(),                    //pixel format
			0, 0, 0, 0                               //pixel masks
	);
	
	//Comment the following line if you do not wish to use transparency in the screen texture so that on can see the clear color.
	//SDL_SetTextureBlendMode(sdl_screen_texture, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 0, 255);
}

SimpleDisplayer::~SimpleDisplayer()
{
	SDL_DestroyRenderer(sdl_renderer);
	SDL_DestroyWindow(sdl_window);
	SDL_DestroyTexture(sdl_screen_texture);
	SDL_FreeSurface(sdl_screen_surface);
}

void SimpleDisplayer::loop()
{
	bool looping = true;
	
	std::chrono::milliseconds remaining_span(0);
	std::chrono::steady_clock::time_point last_time;
	
	SDL_Event e;

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
					bOoM::size_t_2 p( e.button.x, window_size.y -1 -e.button.y );
					std::cout <<"Position is " <<to_physical_coordinates(screen_zone, window_size, p) <<" in bOoM and " <<p <<" on screen." <<std::endl;
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

void SimpleDisplayer::render()
{
	//std::cout << "Generation of a new image" << std::endl;
	SDL_FillRect( sdl_screen_surface, NULL, SDL_MapRGBA(sdl_screen_surface->format,32,0,32,0) );

	
	for( shared_ptr<bOoM::Entity> e : entities )
	{
		bOoM::Image* image;
		bOoM::aabr bOoMzone;
		
		if(e->new__rendered_image(screen_zone, window_size, image, bOoMzone))
		{
			//Convert the bOoM::Image to a SDL_Surface
			SDL_Rect sdlzone = to_SDL_Rect(   to_screen_coordinates(screen_zone, window_size, bOoMzone)   );
			SDL_Surface* imageSurface = SDL_CreateRGBSurfaceFrom(
					image->rgba8888_buffer(),                                                                           //data
					image->width(), image->height(),                                                                    //dimension
					bOoM::Image::depth(), image->pitch(),                                                               //pixel format
					bOoM::Image::redMask(), bOoM::Image::greenMask(), bOoM::Image::blueMask(), bOoM::Image::alphaMask() //pixel masks
			);
			if(imageSurface == NULL)
			{
				std::cout <<"Error: SDL_CreateRGBSurfaceFrom: " <<SDL_GetError() <<std::endl;
				e->del__rendered_image(image);
				continue;
			}
			//Blit it to the screen surface
			if( SDL_BlitSurface(imageSurface, NULL, sdl_screen_surface, &sdlzone ) < 0)
				std::cout <<"Error: SDL_BlitSurface: " <<SDL_GetError() <<std::endl;
			SDL_FreeSurface(imageSurface);
			e->del__rendered_image(image);
		}
	}
	
	if(SDL_UpdateTexture(sdl_screen_texture, NULL, sdl_screen_surface->pixels, window_size.x*4 ) < 0 )
	{
		std::cout << "Error: SDL_UpdateTexture: " << SDL_GetError() << std::endl;
	}

	SDL_RenderClear(sdl_renderer);
	SDL_RenderCopy(sdl_renderer, sdl_screen_texture, NULL, NULL);
	SDL_RenderPresent(sdl_renderer);

}

} //namespace visualizer

