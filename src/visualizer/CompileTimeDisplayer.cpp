#include "CompileTimeDisplayer.hpp"
#include <bOoM/Image.hpp>

namespace visualizer {
using namespace bOoM;

void CompileTimeDisplayer::render()
{
	std::cout << "Generation of a new image" << std::endl;

	SDL_Surface* s = SDL_CreateRGBSurface(0, window_size.x, window_size.y, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	SDL_FillRect( s, NULL, 0x00000000 );
	if(SDL_UpdateTexture(sdl_screen_texture, NULL, s->pixels, window_size.x*4 ) < 0 )
	{
		std::cout << "Error: SDL_UpdateTexture: " << SDL_GetError() << std::endl;
	}
	
	for( shared_ptr<bOoM::Entity> e : entities )
	{
		//std::cout << "Working with a new Entity" << std::endl;
		Image* image;
		aabr bOoMzone;
		if(e->new__rendered_image(screen_zone, window_size, image, bOoMzone))
		{
			std::cout <<"Generated Image of size " <<image->width() <<"x" <<image->height() <<std::endl;
			std::cout <<"Edge Pixel value example : " << std::hex << *(uint32_t*)(image->argb8888_buffer()) << std::dec << std::endl;
			SDL_Rect sdlzone = to_screenCoord(screen_zone, window_size, bOoMzone);
			if( SDL_UpdateTexture(sdl_screen_texture, &sdlzone, image->argb8888_buffer(), image->byteWidth() ) < 0)
				std::cout << "Error: SDL_UpdateTexture: " << SDL_GetError() << std::endl;
			e->del__rendered_image(image);
		}
	}

	SDL_RenderClear(sdl_renderer);
	SDL_RenderCopy(sdl_renderer, sdl_screen_texture, NULL, NULL);
	SDL_RenderPresent(sdl_renderer);

	free(s);
}

bOoM::aabr to_physicalCoord(bOoM::aabr const& screen_zone, bOoM::size_t_2 screen_resolution, SDL_Rect const& sdlrect)
{
	real2 pixel_factor;
	bOoM::aabr bOoMrect;
	
	pixel_factor.x = screen_zone.width()  / real(screen_resolution.x);
	pixel_factor.y = screen_zone.height() / real(screen_resolution.y);
	
	bOoMrect.left =   screen_zone.left + ( real(sdlrect.x) * pixel_factor.x );
	bOoMrect.top =    screen_zone.top  - ( real(sdlrect.y) * pixel_factor.y );
	bOoMrect.bottom = screen_zone.top  - ( real(sdlrect.x+sdlrect.w) * pixel_factor.x );
	bOoMrect.right =  screen_zone.left + ( real(sdlrect.y+sdlrect.h) * pixel_factor.y );
	return bOoMrect;
}

SDL_Rect to_screenCoord(bOoM::aabr const& screen_zone, bOoM::size_t_2 screen_resolution, bOoM::aabr const& bOoMrect)
{
	real2 pixel_factor_inv;
	SDL_Rect sdlrect;
	
	pixel_factor_inv.x = real(screen_resolution.x)  / screen_zone.width() ;
	pixel_factor_inv.y = real(screen_resolution.y) / screen_zone.height();
	sdlrect.x = int( (bOoMrect.left-screen_zone.left) * pixel_factor_inv.x );
	sdlrect.y = int( (screen_zone.top-bOoMrect.top) * pixel_factor_inv.x );
	sdlrect.w = int( bOoMrect.width()  * pixel_factor_inv.x );
	sdlrect.h = int( bOoMrect.height() * pixel_factor_inv.y );
	return sdlrect;
}

} //namespace visualizer

