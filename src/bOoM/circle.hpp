#ifndef H_circle
#define H_circle

#include "math2d.hpp"

namespace bOoM {

struct circle
{
	circle() = default;
	circle( real2 center, real radius)
		: center(center), radius(radius ) {}
	circle( real center_x, real center_y, real radius )
		: center(center_x, center_y), radius(radius) {}
	circle( circle const& other ) = default;


	real2 center;
	real radius;
};

} //namespace bOoM
#endif


