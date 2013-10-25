#ifndef H_aabr
#define H_aabr

#include "math2d.hpp"

namespace bOoM {

struct aabr {

	aabr() = default;
	constexpr aabr( real top, real left, real bottom, real right )
		: bottom(bottom), left(left), right(right), top(top) {}
	constexpr aabr( real2 top_left, real2 bottom_right )
		: bottom(bottom_right.y), left(top_left.x), right(bottom_right.x), top(top_left.y) {}
	constexpr aabr( aabr const& other ) = default;

	real bottom;
	real left;
	real right;
	real top;

	real2 bottom_left() const { return real2(bottom,left); };
	real2 bottom_right() const { return real2(bottom,right); };
	real2 top_left() const { return real2(top,left); };
	real2 top_right() const { return real2(top,right); };
	
	real width() const { return right - left; };
	real height() const { return top - bottom; };
	real2 size() const { return real2(width(),height()); };
};

aabr aabr_biggest_inner_aabr( aabr const& b1, aabr const& b2 )
{
	return aabr( MIN(b1.top, b2.top), 
	             MIN(b1.left,b2.left),
	             MAX(b1.bottom,b2.bottom),
	             MAX(b1.right,b2.right) );
}

} //namespace bOoM
#endif


