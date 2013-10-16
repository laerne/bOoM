#ifndef H_world
#define H_world
namespace bOoM {

struct World {
	Vector<Entity*> entities;
	AtomicClock clock;
};

} //namespace bOoM
#endif


