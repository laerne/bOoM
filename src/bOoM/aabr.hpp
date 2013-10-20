#ifndef H_aabr
#define H_aabr

#include "math2d.hpp"

namespace bOoM {

struct aabr {

	aabr() = default;
	aabr( real top, real left, real bottom, real right )
		: bottom(bottom), left(left), right(right), top(top) {}
	aabr( real2 top_left, real2 bottom_right )
		: bottom(bottom_right.y), left(top_left.x), right(bottom_right.x), top(top_left.y) {}
	aabr( aabr const& other ) = default;

	real bottom;
	real left;
	real right;
	real top;

	real2 bottom_left() { return real2(bottom,left); };
	real2 bottom_right() { return real2(bottom,right); };
	real2 top_left() { return real2(top,left); };
	real2 top_right() { return real2(top,right); };

};

} //namespace bOoM
#endif


