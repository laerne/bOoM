#ifndef H_aabr
#define H_aabr

#include "math2d.hpp"
#include "circle.hpp"

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

bool has_intersection( aabr const& r1, aabr const& r2 )
{
	return r1.right > r2.left
	    && r1.left < r2.right
	    && r1.bottom < r2.top
	    && r1.top > r2.bottom ;
}

bool has_intersection( circle const& c, aabr const& r )
{
	real2 closet_point( CLAMP(r.left,c.center.x,r.right), CLAMP(r.bottom,c.center.x,r.top) );
	return dist2sq(c.center, closet_point) <= SQ(c.radius);
}

bool has_intersection( aabr const& r, move2 const& line )
{
	//FIXME cast Rots to Vectors
	real left_intersection_point  = line_intersection( line.t, line.r, r.top_left(),     real2(0,-1_r));
	real right_intersection_point = line_intersection( line.t, line.r, r.bottom_right(), real2(0,1_r));

	return ( left_intersection_point.y < r.bottom && right_intersection_point.y >= r.bottom )
	    || ( left_intersection_point.y > r.top    && right_intersection_point.y <= r.bottom );
	
}

} //namespace bOoM
#endif


