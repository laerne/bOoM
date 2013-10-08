#ifndef H_solid
#define H_solid
namespace bOoM {

struct Solid
{
	real2 center_of_mass;
	real2 velocity;
	real2 acceleration;

	real2 tmptest__radius;

/* PSEUDO-CODE : main loop
*****
* 1 *
*****
while software_is_running:
	time_step = 10_ms
	while time_step > 0 && agent.has_msg()
		msg = agent.poll()
		handle(msg)
		time_step -= time_to_compute
	if time_step > 0:
		msg = agent.receive( wait_max = time_step )
		if( msg != NULL )
			handle( msg )
	move_entity()
	check_collision()
	if(has_collision)
		set_acceleration_vectors()
*****
* 2 *
*****
	  
 */
};

} //namespace bOoM
#endif


