#ifndef H_circle
#define H_circle

#include "math2d.hpp"

namespace bOoM {

//! \brief data structure for a 2D circle.
struct circle
{
	//! \brief Default constructor, it leaves fields uninitialized.
	circle() = default;
	//! \brief Standard constructor of given center and radius.
	constexpr circle( real2 center, real radius)
		: center(center), radius(radius ) {}
	//! \brief Standard constructor of center `{center_x,center_y}` and given radius.
	constexpr circle( real center_x, real center_y, real radius )
		: center(center_x, center_y), radius(radius) {}
	//! \brief Default copy constructor.
	constexpr circle( circle const& other ) = default;

	
	real2 center; //!< center of the circle
	real radius;  //!< radius of the circle, i.e. the distance between the center and the boundaries of the circle.
};

} //namespace bOoM
#endif


