//Trivial displayer <NOT THREAD SAFE>
#include <cppa/cppa.hpp>
#include <SDL2/SDL.h>

#include <chrono>
#include <exception>
#include <iostream>

#include "SimpleDisplayObject.hpp"
//#include "SimpleDisplayActor.hpp"
//#include "SimpleInputActor.hpp"

//using namespace bOoM;
using namespace visualizer;

void on_crash_exit()
{
	cppa::shutdown();
	SDL_Quit();
}

int main(int argc, char **argv)
{
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_EVENTS ) != 0)
		cppa::aout << "SDL failed to initiate." << std::endl;
	atexit(on_crash_exit);

	//cppa::actor_ptr a_display = cppa::spawn<SimpleDisplayActor>( 1024, 768, std::chrono::milliseconds(100) );
	//cppa::actor_ptr a_keyboardManager = cppa::spawn<SimpleInputActor, cppa::detached>( cppa::self );
	
	//cppa::await_all_others_done();
	//cppa::shutdown();

	SimpleDisplayObject display( 1024, 768, std::chrono::milliseconds(20) );
	display.loop();


	SDL_Quit();

	return 0;
}
