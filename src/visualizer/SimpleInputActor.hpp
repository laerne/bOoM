#ifndef H_SimpleInputActor
#define H_SimpleInputActor

#include <cppa/cppa.hpp>
#include <SDL2/SDL.h>

namespace visualizer {
struct SimpleInputActor : public cppa::event_based_actor {
	SimpleInputActor(cppa::actor_ptr const& display_actor);
	virtual ~SimpleInputActor();
	void init();

	cppa::actor_ptr display_actor;
};

} //namespace visualizer
#endif


