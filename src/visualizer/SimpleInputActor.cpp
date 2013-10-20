#include "SimpleInputActor.hpp"

#include <iostream>

namespace bOoM {

SimpleInputActor::SimpleInputActor(cppa::actor_ptr const& display_actor)
	: display_actor(display_actor) {}
SimpleInputActor::~SimpleInputActor()
	{}

void SimpleInputActor::init()
{
	bool run = true;
	SDL_Event e;
	while( run && SDL_WaitEvent( &e ) == 1 )
	{
		//cppa::aout << "Received event of type " << e.type << std::endl;
		switch(e.type)
		{
			case SDL_QUIT:
			case SDL_KEYDOWN:
				run = false;
				cppa::send(display_actor, cppa::atom("die"));
				cppa::self->quit();
				break;
		}
	}
}

} //namespace bOoM

