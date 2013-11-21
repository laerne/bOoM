#ifndef H_simpleDisplayer
#define H_simpleDisplayer

#include <chrono>
#include <SDL2/SDL.h>

//using namespace bOoM;
namespace visualizer {

class SimpleDisplayer
{
public:
	SimpleDisplayer(int window_width, int window_height, std::chrono::milliseconds refresh_span);
	virtual ~SimpleDisplayer();

	void loop();

protected:
	virtual void render();

	SDL_Window *sdl_window;
	SDL_Renderer *sdl_renderer;

	std::chrono::milliseconds const refresh_span;
};

} //namespace visualizer
#endif


