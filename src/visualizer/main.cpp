//Trivial displayer <NOT THREAD SAFE>
#include <cppa/cppa.hpp>
#include <SDL2/SDL.h>

#include <chrono>
#include <exception>
#include <iostream>

#include "SimpleDisplayActor.hpp"
#include "SimpleInputActor.hpp"

using namespace bOoM;

void on_crash_exit()
{
	cppa::shutdown();
	SDL_Quit();
}

int main(int argc, char **argv){
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_EVENTS ) != 0)
		cppa::aout << "SDL failed to initiate." << std::endl;
	atexit(on_crash_exit);

	cppa::actor_ptr a_display = cppa::spawn<SimpleDisplayActor>( 600, 800, std::chrono::milliseconds(100) );
	cppa::actor_ptr a_keyboardManager = cppa::spawn<SimpleInputActor>( a_display );
	//cppa::actor_ptr a = cppa::spawn<StupidelySimpleActorWithConstructor>(2);

	cppa::await_all_others_done();
	cppa::shutdown();
	SDL_Quit();

	return 0;
}
