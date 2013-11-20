#ifndef H_simpleDisplayObject
#define H_simpleDisplayObject

#include <chrono>
#include <SDL2/SDL.h>

//using namespace bOoM;
namespace visualizer {

class SimpleDisplayObject
{
public:
	SimpleDisplayObject(int window_width, int window_height, std::chrono::milliseconds refresh_span);
	~SimpleDisplayObject();

	void loop();

protected:
	virtual void render();

private:
	SDL_Window *sdl_window;
	SDL_Renderer *sdl_renderer;


	std::chrono::milliseconds const refresh_span;
};

} //namespace visualizer
#endif


