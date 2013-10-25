#ifndef H_circle
#define H_circle

#include "math2d.hpp"

namespace bOoM {

struct circle
{
	circle() = default;
	constexpr circle( real2 center, real radius)
		: center(center), radius(radius ) {}
	constexpr circle( real center_x, real center_y, real radius )
		: center(center_x, center_y), radius(radius) {}
	constexpr circle( circle const& other ) = default;


	real2 center;
	real radius;
};

} //namespace bOoM
#endif


