#ifndef H_solid
#define H_solid
namespace bOoM {

class Solid : event_based_actor
{
public:
	Solid(real2 initial_origin, real2 initial_velocity = zero2, real2 initial_acceleration = zero2, real tmptest__radius)
		: origin(initial_origin), centerOfMass(zero2),
		velocity(initial_velocity), acceleration(initial_acceleration),
		tmptest__radius(tmptest__radius)
	{}
	Solid(Solid const& other) = delete; //delete until we implement a clean copy constructor.

	virtual void init();
private:
	int render(ScreenProperties const& bufferType, ScreenBuffer& buffer);

	behavior idle = (
		on(RENDER, arg_match) >> [=](ScreenProperties const& bufferType, ScreenBuffer & buffer)
		{
			render(bufferType, buffer);
			//TODO failure test
			reply(DID_RENDER);
		};
	);

	real2 origin;
	real2 centerOfMass;
	real2 velocity;
	real2 acceleration;

	real2 tmptest__radius;
};

} //namespace bOoM
#endif


