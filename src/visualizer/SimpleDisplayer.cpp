#include "SimpleDisplayer.hpp"
#include <iostream>
#include <stdexcept>
#include <thread>

namespace visualizer {

SimpleDisplayer::SimpleDisplayer( bOoM::size_t_2 window_size, bOoM::aabr const& screen_zone, std::chrono::milliseconds refresh_span, std::vector<shared_ptr<bOoM::Entity>> const& starting_entities)
	: refresh_span(refresh_span), window_size(window_size), screen_zone(screen_zone), entities(starting_entities)
{
	//FIXME check return errors
	SDL_CreateWindowAndRenderer(window_size.x, window_size.y, SDL_WINDOW_SHOWN, &sdl_window, &sdl_renderer);
	if( sdl_window == NULL || sdl_renderer == NULL )
		throw std::runtime_error("SDL failed to create a window.");
	sdl_screen_texture = SDL_CreateTexture(sdl_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, window_size.x, window_size.y);
	sdl_screen_surface = SDL_CreateRGBSurface(0, window_size.x, window_size.y, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	
	//Comment the following line if you do not wish to use transparency in the screen texture so that on can see the clear color.
	SDL_SetTextureBlendMode(sdl_screen_texture, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(sdl_renderer, 0, 32, 0, 255);
}

SimpleDisplayer::~SimpleDisplayer()
{
	SDL_DestroyRenderer(sdl_renderer);
	SDL_DestroyWindow(sdl_window);
	SDL_DestroyTexture(sdl_screen_texture);
	free(sdl_screen_surface);
}

void SimpleDisplayer::loop()
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
					return; //break;
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
	std::cout << "Generation of a new image" << std::endl;

	SDL_FillRect( sdl_screen_surface, NULL, 0xFF100010 );
	if(SDL_UpdateTexture(sdl_screen_texture, NULL, sdl_screen_surface->pixels, window_size.x*4 ) < 0 )
	{
		std::cout << "Error: SDL_UpdateTexture: " << SDL_GetError() << std::endl;
	}
	
	for( shared_ptr<bOoM::Entity> e : entities )
	{
		//std::cout << "Working with a new Entity" << std::endl;
		bOoM::Image* image;
		bOoM::aabr bOoMzone;
		//if(e->new__rendered_image(screen_zone, window_size, image, bOoMzone))
		//{
		//	//std::cout <<"Generated bOoM::Image of size " <<image->width() <<"x" <<image->height() <<std::endl;
		//	//std::cout <<"Edge Pixel value example : " << std::hex << *(uint32_t*)(image->argb8888_buffer()) << std::dec << std::endl;
		//	SDL_Rect sdlzone = to_screenCoord(screen_zone, window_size, bOoMzone);
		//	if( SDL_UpdateTexture(sdl_screen_texture, &sdlzone, image->argb8888_buffer(), image->byteWidth() ) < 0)
		//		std::cout << "Error: SDL_UpdateTexture: " << SDL_GetError() << std::endl;
		//	e->del__rendered_image(image);
		//}
	}

	SDL_RenderClear(sdl_renderer);
	SDL_RenderCopy(sdl_renderer, sdl_screen_texture, NULL, NULL);
	SDL_RenderPresent(sdl_renderer);

}

bOoM::aabr to_physicalCoord(bOoM::aabr const& screen_zone, bOoM::size_t_2 screen_resolution, SDL_Rect const& sdlrect)
{
	bOoM::real2 pixel_factor;
	bOoM::aabr bOoMrect;
	
	pixel_factor.x = screen_zone.width()  / bOoM::real(screen_resolution.x);
	pixel_factor.y = screen_zone.height() / bOoM::real(screen_resolution.y);
	
	bOoMrect.left =   screen_zone.left + ( bOoM::real(sdlrect.x) * pixel_factor.x );
	bOoMrect.top =    screen_zone.top  - ( bOoM::real(sdlrect.y) * pixel_factor.y );
	bOoMrect.bottom = screen_zone.top  - ( bOoM::real(sdlrect.x+sdlrect.w) * pixel_factor.x );
	bOoMrect.right =  screen_zone.left + ( bOoM::real(sdlrect.y+sdlrect.h) * pixel_factor.y );
	return bOoMrect;
}

SDL_Rect to_screenCoord(bOoM::aabr const& screen_zone, bOoM::size_t_2 screen_resolution, bOoM::aabr const& bOoMrect)
{
	bOoM::real2 pixel_factor_inv;
	SDL_Rect sdlrect;
	
	pixel_factor_inv.x = bOoM::real(screen_resolution.x)  / screen_zone.width() ;
	pixel_factor_inv.y = bOoM::real(screen_resolution.y) / screen_zone.height();
	sdlrect.x = int( (bOoMrect.left-screen_zone.left) * pixel_factor_inv.x );
	sdlrect.y = int( (screen_zone.top-bOoMrect.top) * pixel_factor_inv.x );
	sdlrect.w = int( bOoMrect.width()  * pixel_factor_inv.x );
	sdlrect.h = int( bOoMrect.height() * pixel_factor_inv.y );
	return sdlrect;
}

} //namespace visualizer
