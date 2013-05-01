#ifndef H_dynamic
#define H_dynamic
/*! \file dynamic.hpp
 *  \brief Define point dynamic data type.
 */

#include "math2d.hpp"
#include <iostream>

namespace bOoM {
/*! \brief A dynamic oriented point.
 *
 * It has position, velocity and acceleration as a PointDynamic, but also has
 * an orientation, a angular velocity and a angular acceleration.
 */
struct Dynamic
{
	//! \brief Standard constructor.
	Dynamic(move2 const& position
			, move2 const& velocity, move2 const& acceleration)
		: pos(position), vel(velocity) , acc(acceleration) {}
	//! Convert into a PointDynamic, "forgetting" the orientation dynamics.
	PointDynamic asPointDynamic() const
		{ return PointDynamic(pos.t,vel.t,acc.t); }
	/*! \brief Change point's position, orientation, angular speed and velocity
	 *  accordingly to its dynamics in a unit time interval.
	 */
	void step()
		{ pos.t+=vel.t; pos.r*=vel.r; vel.t+=acc.t; vel.r*=acc.r; }
	/*! \brief Change point's position, orientation, angular speed and velocity
	 *  accordingly to its dynamics in the given time interval.
	 */
	void step(real time)
	{
		pos.t+= time*vel.t; pos.r*= time*vel.r;
		vel.t+= time*acc.t; vel.r*= time*acc.r;
	}

	move2 pos; //<! \brief Position and angle.
	move2 vel; //<! \brief velocity and angular velocity in unit-per-steps.
	move2 acc; //<! \brief acceleration and angular acceleration in unit-per-step².
};

//! \brief Output a string representation of the Dynamic `dyn`.
std::ostream& operator<<(std::ostream& s, Dynamic const& dyn)
{
    s <<"(pos:" <<dyn.pos <<",vel:" <<dyn.vel <<",acc:" <<dyn.acc <<")";
    return s;
}

} //namespace bOoM
#endif

