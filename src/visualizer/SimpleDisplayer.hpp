#ifndef H_simpleDisplayer
#define H_simpleDisplayer

#include <chrono>
#include <vector>
#include <memory>
#include <bOoM/aabr.hpp>
#include <bOoM/entities/Entity.hpp>
#include <SDL2/SDL.h>

//using namespace bOoM;
namespace visualizer {
using std::shared_ptr;

class SimpleDisplayer
{
public:
	SimpleDisplayer(
			bOoM::size_t_2 window_size,
			bOoM::aabr const& screen_zone,
			std::chrono::milliseconds refresh_span,
			std::vector<shared_ptr<bOoM::Entity>> const& starting_entities);
	virtual ~SimpleDisplayer();

	void loop();

protected:
	virtual void render();
	
	std::chrono::milliseconds const refresh_span;

	SDL_Window *sdl_window;
	SDL_Renderer *sdl_renderer;
	SDL_Texture* sdl_screen_texture;
	SDL_Surface* sdl_screen_surface;
	
	bOoM::size_t_2 window_size;
	bOoM::aabr screen_zone;

	std::vector< shared_ptr<bOoM::Entity> > entities;
};

} //namespace visualizer
#endif


