//Trivial displayer <NOT THREAD SAFE>
#include <SDL2/SDL.h>

#include <chrono>
#include <exception>
#include <iostream>
#include <vector>
#include <memory>

#include <bOoM/math2d.hpp>
#include <bOoM/aabr.hpp>
#include <bOoM/entities/world_boundary/WorldBoundary.hpp>

#include "SimpleDisplayer.hpp"
#include "CompileTimeDisplayer.hpp"

//using namespace bOoM;
using namespace visualizer;

void on_crash_exit()
{
	SDL_Quit();
}

int main(int argc, char **argv)
{
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_EVENTS ) != 0)
		std::cout << "SDL failed to initiate." << std::endl;
	atexit(on_crash_exit);
	
	std::vector<std::shared_ptr<bOoM::Entity>> starting_entities;
	starting_entities.push_back(std::make_shared<bOoM::WorldBoundary>(bOoM::move2_id));
	
	CompileTimeDisplayer display(
			bOoM::size_t_2(1024,768),
			bOoM::aabr(12.f,-16.f,-12.f,16.f),
			std::chrono::milliseconds(20),
			starting_entities
	);
	//SimpleDisplayer display( 1024, 768, std::chrono::milliseconds(20) );
	display.loop();


	SDL_Quit();

	return 0;
}
