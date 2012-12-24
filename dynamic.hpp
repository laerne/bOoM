#ifndef H_dynamic
#define H_dynamic
/*! \file dynamic.hpp
 *  \brief Define point dynamic data type.
 */

#include "math2d.hpp"
#include <iostream>

namespace bOoM {
//! \brief A dynamic point with position, velocity and acceleration.
struct PointDynamic
{
	//! \brief Standard constructor.
	PointDynamic(real2 const& position
			, real2 const& velocity, real2 const& acceleration)
		: pos(position), vel(velocity), acc(acceleration) {}
	//! Change point's position and velocity accordingly to its dynamics.
	void step() { pos+= vel; vel+= acc; }

	real2 pos; //!< \brief Position.
	real2 vel; //!< \brief Velocity in distance-per-steps.
	real2 acc; //!< \brief Acceleration in distance-per-steps².
};

//! \brief Output a string representation of the PointDynamic `dyn`.
std::ostream& operator<<(std::ostream& s, PointDynamic const& dyn)
	{ s <<"(pos:" <<dyn.pos <<",vel:" <<dyn.vel <<",acc:" <<dyn.acc <<")";}

/*! \brief A dynamic oriented point.
 *
 * It has position, velocity and acceleration as a PointDynamic, but also has
 * an orientation, a angular velocity and a angular acceleration.
 */
struct OrientedDynamic
{
	//! \brief Standard constructor.
	OrientedDynamic(move2 const& position
			, move2 const& velocity, move2 const& acceleration)
		: pos(position), vel(velocity) , acc(acceleration) {}
	//! Convert into a PointDynamic, "forgetting" the orientation dynamics.
	PointDynamic asPointDynamic() const
		{ return PointDynamic(pos.t,vel.t,acc.t); }
	/*! \brief Change point's position, orientation, angular speed and velocity
	 *  accordingly to its dynamics.
	 */
	void step()
		{ pos.t+=vel.t; pos.r*=vel.r; vel.t+=acc.t; vel.r*=acc.r; }

	move2 pos; //<! \brief Position and angle.
	move2 vel; //<! \brief velocity and angular velocity in unit-per-steps.
	move2 acc; //<! \brief acceleration and angular acceleration in unit-per-step².
};

//! \brief Output a string representation of the OrientedDynamic `dyn`.
std::ostream& operator<<(std::ostream& s, OrientedDynamic const& dyn)
	{ s <<"(pos:" <<dyn.pos <<",vel:" <<dyn.vel <<",acc:" <<dyn.acc <<")";}

} //namespace bOoM
#endif

