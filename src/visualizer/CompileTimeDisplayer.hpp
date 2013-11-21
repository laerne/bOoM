#ifndef H_CompileTimeDisplayer
#define H_CompileTimeDisplayer

#include <vector>
#include <memory>
#include <bOoM/aabr.hpp>
#include <bOoM/entities/Entity.hpp>
#include <SDL2/SDL.h>

#include "SimpleDisplayer.hpp"

namespace visualizer {
using std::shared_ptr;

class CompileTimeDisplayer : public SimpleDisplayer
{
public:
	CompileTimeDisplayer( bOoM::size_t_2 window_size, bOoM::aabr const& screen_zone, std::chrono::milliseconds refresh_span, std::vector<shared_ptr<bOoM::Entity>> const& starting_entities)
		: SimpleDisplayer(window_size.x, window_size.y, refresh_span), window_size(window_size), screen_zone(screen_zone), entities(starting_entities)
	{
		sdl_screen_texture = SDL_CreateTexture(sdl_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, window_size.x, window_size.y);
		//Comment the following line if you do not wish to use transparency in the screen texture so that on can see the clear color.
		SDL_SetTextureBlendMode(sdl_screen_texture, SDL_BLENDMODE_BLEND);

	}
	~CompileTimeDisplayer()
	{
		SDL_DestroyTexture(sdl_screen_texture);
	}
protected:
	virtual void render();
	
	bOoM::size_t_2 window_size;
	bOoM::aabr screen_zone;
	std::vector< shared_ptr<bOoM::Entity> > entities;
	SDL_Texture* sdl_screen_texture;
};

//NOTE: y-axis orientation is inverted between bOoM'sphysical engine and SDL2
bOoM::aabr to_physicalCoord(bOoM::aabr const& screen_zone, bOoM::size_t_2 screen_resolution, SDL_Rect const& sdlrect);
SDL_Rect to_screenCoord(bOoM::aabr const& screen_zone, bOoM::size_t_2 screen_resolution, bOoM::aabr const& bOoMrect);


} //namespace visualizer
#endif


