#ifndef H_intersection
#define H_intersection
/*! \file intersection.hpp
 *  \brief Provides basic method to compute the intersection of basic shapes.
 *
 * Unlike functions in \file math2d.hpp , all scalar are of the `real` type.
 * Basic shapes are provided with its parameters as arguments and do have a dedicated structure.
 */

#include <tuple>
#include "math2d.hpp"
#include "aabr.hpp"
#include "circle.hpp"
namespace bOoM {

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

bool has_intersection( circle const& c1, circl const& c2 )
	{ return( dist2sq(c1.center,c2.center) <= SQ(c1.radius+c2.radius) ); }

bool has_intersection( circle const& c, move2 const& line )
{
	//real cry_over_crx = c.radius.y / c.radius.x;
	//real x2_factor = 1 + SQ(cry_over_crx);
	//real x1_factor = 2 *( c.center.x
	//                    - line.t.x*SQ(cry_over_crx)
	//                    + line.t.y*cry_over_crx
	//                    - c.center.y * cry_over_crx
	//                    );
	//real x0_factor = SQ(c.center.x)
	//               + SQ(c.center.y)
	//               + SQ(line.t.y)
	//               + SQ(line.t.x)*SQ(cry_over_crx)
	//               - 2* line.t.x * line.t.y * cry_over_crx
	//               - 2* line.t.y * c.center.y
	//               + 2* line.t.x * cry_over_crx * c.center.y ;
	//return eqn2_discriminant(x2_factor, x1_factor, x0_factor) >= 0_r;
	return (c.center|line.t) / norm2( line.t ) <= c.radius ;
}


//! return the value of `s` and `t` such that `p + t*v == q + s*w` holds, or return `{nan,nan}` if there is no solution.
inline real2 line_intersection_factors(
		real2 const p, real2 const v,
		real2 const q, real2 const w )
{
	real v_x_w= crossProduct_z(v,w);
	if( is_too_small(v_x_w) )
		return nan2;
	else
		return real2(
			crossProduct_z(w,p-q) / v_x_w ,
			crossProduct_z(v,p-q) / v_x_w );
}

/*! \brief The intersection point of two infinite lines, or return `{nan,nan}` if they are parallel.
 *
 * Lines are given by a couple of a point in the line and a direction vector.
 * The two lines here are given by `{p,v}` and `{q,w}`.
 */
inline real2 line_intersection(
		real2 const p, real2 const v,
		real2 const q, real2 const w )
{
	real2 const factors= line_intersection_factors( p, v, q, w );
	return p + v*(factors.x);
}

/*! \brief The intersection point of two finite line segments, or return `{nan,nan}` if they do not intersect.
 *
 * Lines are given by a couple of a point in the line and a direction vector.
 * The two lines here are given by `{p,v}` and `{q,w}`.
 * The length of the segment is the length of the direction vector.
 * In other words, the extremity of segment `{p,v}` are `p` and `p+v`.
 */
inline real2 lineSegment_intersection(
		real2 const p, real2 const v,
		real2 const q, real2 const w )
{
	real2 const factors= line_intersection_factors( p, v, q, w );
	if(  WITHIN( 0.0, factors.x, 1.0) && WITHIN( 0.0, factors.x, 1.0 )  )
		return p + v*(factors.x);
	else
		return nan2;
}

//! \brief The contact point of two moving balls. The time of contact is stored in `t`.
real2 ball_intersection(
		real2 const p, real2 const v, real const r_p,
		real2 const q, real2 const w, real const r_q, real &t );

//! \brief The contact point of two moving balls.
inline real2 ball_intersection(
		real2 const p, real2 const v, real const r_p,
		real2 const q, real2 const w, real const r_q)
{
	real thisVariableIsUselessInEveryPossibleWay;
	return ball_intersection(p,v,r_p,q,w,r_q, thisVariableIsUselessInEveryPossibleWay);
}

//! \brief The contact point of two moving balls if a collision occurs before `time_limit`.
inline real2 ball_intersection_before(
		real2 const p, real2 const v, real const r_p,
		real2 const q, real2 const w, real const r_q,
		real time_limit )
{
	real t;
	real2 intersection= ball_intersection(p,v,r_p,q,w,r_q, t);
	if( t < time_limit )
		return nan2;
	else
		return intersection;
}

//! \brief The contact point of two moving balls if a collision occurs before `std::get<1>(time_interval)` and after `std::get<0>(time_interval)`.
inline real2 ball_intersection_within(
		real2 const p, real2 const v, real const r_p,
		real2 const q, real2 const w, real const r_q,
		std::pair<real,real> time_interval )
{
	real t;
	real2 intersection= ball_intersection(p,v,r_p,q,w,r_q, t);
	if(t < std::get<0>(time_interval) || t > std::get<0>(time_interval) )
		return nan2;
	else
		return intersection;
}

//TODO: capsule shape around segment line intersection.
//real2 capsule_intersection(
//		real2 const p, real2 const v, real const r_p,
//		real2 const q, real2 const w, real const r_q, real &t );


} //namespace bOoM

#endif

