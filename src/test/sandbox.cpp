//Trivial displayer <NOT THREAD SAFE>
#include <SDL2/SDL.h>

#include <chrono>
#include <exception>
#include <iostream>
#include <vector>
#include <memory>

#include <bOoM/math2d.hpp>
#include <bOoM/aabr.hpp>
#include <bOoM/Entity.hpp>
#include <bOoM/entities/balloon/Balloon.hpp>
#include <bOoMengine/Simulator.hpp>

//using namespace bOoM;
using namespace bOoM;

void on_crash_exit()
{
	SDL_Quit();
}

int main(int argc, char **argv)
{
	return 0;
}
