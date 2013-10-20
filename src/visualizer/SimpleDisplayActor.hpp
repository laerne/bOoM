#ifndef H_SimpleDisplayActor
#define H_SimpleDisplayActor

#include <SDL2/SDL.h>
#include <chrono>
#include <unordered_map>

namespace visualizer {

struct SimpleDisplayActor : public cppa::event_based_actor
{
	SimpleDisplayActor() = delete;
	SimpleDisplayActor(int window_width, int window_height, std::chrono::steady_clock::duration refresh_span);
	SimpleDisplayActor(SimpleDisplayActor const& other) = delete;
	virtual ~SimpleDisplayActor();

	void recompute_remaining_span();
	void generate_image();

	/* libcppa reqires this function to spawn an actor */
	void init()
	{
		create_windowAndRenderer();
		handle_messages(); 
	}
	void create_windowAndRenderer();
	void handle_messages();

	int w,h;

	SDL_Window *sdl_window;
	SDL_Renderer *sdl_renderer;

	std::chrono::steady_clock::duration const refresh_span;
	std::chrono::steady_clock::duration remaining_span;
	std::chrono::steady_clock::time_point last_time;
};

} //namespace visualizer

#endif
 
