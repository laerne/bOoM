#include "SimpleDisplayActor.hpp"
#include <stdexcept>

namespace visualizer {

SimpleDisplayActor::SimpleDisplayActor(int window_width, int window_height, std::chrono::steady_clock::duration refresh_span)
	: w(window_width), h(window_height),
	refresh_span(refresh_span), remaining_span(0), last_time() //by default last_time is initialized to epoch
	{}

SimpleDisplayActor::~SimpleDisplayActor()
	{}

void SimpleDisplayActor::recompute_remaining_span()
{
	std::chrono::steady_clock::time_point current_time= std::chrono::steady_clock::now();
	remaining_span = current_time - last_time;
	last_time = current_time;
}

void SimpleDisplayActor::generate_image()
{
	SDL_RenderClear(sdl_renderer);
	//cppa::aout << "requested to generate a new image" << std::endl;
	SDL_RenderPresent(sdl_renderer);
}


void SimpleDisplayActor::create_windowAndRenderer()
{
	SDL_CreateWindowAndRenderer(w, h, SDL_WINDOW_SHOWN, &sdl_window, &sdl_renderer);
	if( sdl_window == NULL || sdl_renderer == NULL )
		throw std::runtime_error("SDL failed to create a window.");
	SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 0, 255);
}

void SimpleDisplayActor::handle_messages()
{
	cppa::become (
		cppa::on( cppa::atom("renderOK"), cppa::arg_match ) >> [=]()
		{
			recompute_remaining_span();
		},
		cppa::on( cppa::atom("die") ) >> [=]()
		{
			cppa::self->quit();
		},
		cppa::after( std::chrono::duration_cast<std::chrono::milliseconds>(remaining_span) ) >> [=]()
		{
			generate_image();
			//reset remaining span
			remaining_span = refresh_span;
		}
	);
}

} //namespace visualizer

