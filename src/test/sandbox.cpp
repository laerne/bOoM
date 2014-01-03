//Trivial displayer <NOT THREAD SAFE>
#include <SDL2/SDL.h>

#include <chrono>
#include <exception>
#include <iostream>
#include <vector>
#include <memory>

#include <bOoM/math2d.hpp>
#include <bOoM/aabr.hpp>
//#include <bOoM/entities/world_boundary/WorldBoundary.hpp>
#include <bOoM/Entity.hpp>
#include <bOoM/entities/balloon/Balloon.hpp>
#include <bOoM/entities/balloon/graphic.hpp>

#include <bOoMengine/SDLWindowDisplayer.hpp>

//using namespace bOoM;
using namespace bOoM;

void on_crash_exit()
{
	SDL_Quit();
}

struct Void {};
struct Void0 {};

int main(int argc, char **argv)
{
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_EVENTS ) != 0)
		std::cout << "SDL failed to initiate." << std::endl;
	atexit(on_crash_exit);
	
	std::vector<std::shared_ptr<bOoM::Entity>> starting_entities;
	//starting_entities.push_back(std::make_shared<bOoM::WorldBoundary>(bOoM::move2_id));
	//starting_entities.push_back(std::make_shared<bOoM::WorldBoundary>(bOoM::move2(bOoM::rot2_fromRadian(-CST_PI/6_r),bOoM::zero2)));
	//starting_entities.push_back(std::make_shared<bOoM::Balloon>(bOoM::circle(0_r,3_r,1_r)));
	
	//bOoM::Entity e ( bOoM::Balloon(bOoM::circle(0_r,3_r,1_r)) );
	//e.ptr->graphic__del__rendered_image(nullptr);
	//bOoM::GenericEntity<bOoM::Renderable, Void, Void0> f ( bOoM::Balloon(bOoM::circle(0_r,3_r,1_r)) );
	
	bOoM::SDLDisplayer display(
			bOoM::size_t_2(1024,512),
			bOoM::aabr( real2(-16_r,-4_r), real2(32_r,18_r) ),
			std::chrono::milliseconds(40),
			starting_entities
	);
	display.loop();


	SDL_Quit();

	return 0;
}
