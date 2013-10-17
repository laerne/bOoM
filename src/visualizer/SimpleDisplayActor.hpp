#ifndef H_SimpleDisplayActor
#define H_SimpleDisplayActor

#include <cppa/cppa.hpp>
#include <SDL2/SDL.h>
#include <chrono>

namespace bOoM {

struct SimpleDisplayActor : public cppa::event_based_actor
{
	SimpleDisplayActor() = delete;
	SimpleDisplayActor(int window_width, int window_height, std::chrono::steady_clock::duration refresh_span);
	SimpleDisplayActor(SimpleDisplayActor const& other) = delete;
	virtual ~SimpleDisplayActor();

	void recompute_remaining_span();
	void generate_image();

	/* libcppa reqires this function to spawn an actor */
	void init() { handle_messages(); }
	void handle_messages();


	SDL_Window *sdl_window;
	SDL_Renderer *sdl_renderer;

	//std::unordered_map< cppa::actorptr, SDL_Texture* > object_images;

	std::chrono::steady_clock::duration const refresh_span;
	std::chrono::steady_clock::duration remaining_span;
	std::chrono::steady_clock::time_point last_time;
};

} //namespace bOoM

#endif
 
