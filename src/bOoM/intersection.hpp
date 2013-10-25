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

/**************************
 * LINE-LINE INTERSECTION *
 **************************/

//! return the value of `s` and `t` such that `p + t*v == q + s*w` holds, or return `{nan,nan}` if there is no solution.
real2 line_intersection_factors(
		real2 const& p, real2 const& v,
		real2 const& q, real2 const& w )
{
	real v_x_w= crossProduct_z(v,w);
	if( equals_about(v_x_w, 0_r) )
		return nan2;
	else
		return real2(
			crossProduct_z(w,p-q) / v_x_w ,
			crossProduct_z(v,p-q) / v_x_w );
}

bool has_line_intersection( move2 const& l1, move2 const& l2 )
{
	//ensure lines are not parallel
	return (l1.r != l2.r) && (l1.r != -l2.r);
}

/*! \brief The intersection point of two infinite lines, or return `{nan,nan}` if they are parallel.
 *
 * Lines are given by a couple of a point in the line and a direction vector.
 * The two lines here are given by `{p,v}` and `{q,w}`.
 */
bool line_intersection( move2 const& l1, move2 const& l2, real2& hitpoint, real& hitpoint_factor )
{
	if(! has_line_intersection(l1,l2) )
		return false;
	real2 const factors= line_intersection_factors( l1.t, l1.r, l2.t, l2.r );
	hitpoint_factor = factors.x;
	hitpoint= l1.t + l1.r*(factors.x);
	return true;
}

/********************************
 * SEGMENT-SEGMENT INTERSECTION *
 ********************************/
bool has_lineSegment_intersection( move2 const& l1, move2 const& l2)
{
	real2 const factors= line_intersection_factors( l1.t, l1.r, l2.t, l2.r );
	return (  WITHIN( 0.0, factors.x, 1.0) && WITHIN( 0.0, factors.x, 1.0 )  );
}

/*! \brief The intersection point of two finite line segments, or return `{nan,nan}` if they do not intersect.
 *
 * Lines are given by a couple of a point in the line and a direction vector.
 * The two lines here are given by `{p,v}` and `{q,w}`.
 * The length of the segment is the length of the direction vector.
 * In other words, the extremity of segment `{p,v}` are `p` and `p+v`.
 */
bool lineSegment_intersection( move2 const& l1, move2 const& l2, real2& hitpoint, real& hitpoint_factor )
{
	real2 const factors= line_intersection_factors( l1.t, l1.r, l2.t, l2.r );
	if(!(  WITHIN( 0.0, factors.x, 1.0) && WITHIN( 0.0, factors.x, 1.0 )  ))
		return false;
	hitpoint_factor = factors.x;
	hitpoint = l1.t + l1.r*(factors.x);
	return true;
}

/******************************
 * CIRCLE-CIRCLE INTERSECTION *
 ******************************/
bool has_intersection( circle const& c1, circle const& c2 )
	{ return( dist2sq(c1.center,c2.center) <= SQ(c1.radius+c2.radius) ); }

bool intersection( circle const& c1, circle const& c2, real2& centroid, real& mesure )
{
	if( ! has_intersection(c1,c2) )
		return false;
	// Now we consider the center of c1 to lie in (0,0) and the center of c2 to lie in (c,0).
	// where c = dist2( c1.center, c2.center )
	// In this  , the intersection point between the two circle are at (l1,h) and (l1,-h).
	// 
	// Using 3 square roots and two arcsines.
	real c = SQRT( dist2sq(c1.center,c2.center) );
	real l1 = ( dist2sq(c1.center,c2.center)+SQ(c1.radius)-SQ(c2.radius) ) / ( 2*c );
	real h = SQRT ( SQ(c1.radius) - SQ(l1) );
	real l2 = c - l1;
	//std::cout << "c = " << c << std::endl;
	//std::cout << "l1 = " << l1 << std::endl;
	//std::cout << "h = " << h << std::endl;
	//std::cout << "l2 = " << l2 << std::endl;
	
	real area1 = 2*SQ(c1.radius)*ARCSIN(h/c1.radius) - 2*l1*h ;
	real centroid1_x = ((2_r/3_r) * SQRT( SQ(c1.radius) - SQ(l1) ))/area1;
	//std::cout << "area1 = " << area1 << std::endl;
	//std::cout << "centroid1_x = " << centroid1_x << std::endl;

	real area2 = 2*SQ(c2.radius)*ARCSIN(h/c2.radius) - 2*l2*h ;
	real centroid2_x = ((-2_r/3_r) * SQRT( SQ(c2.radius) - SQ(l2) ))/area2 + c;
	//std::cout << "area2 = " << area2 << std::endl;
	//std::cout << "centroid2_x = " << centroid2_x << std::endl;

	mesure = area1 + area2;
	real local_centroid_x = (centroid1_x*area1 + centroid2_x*area2)/mesure;
	centroid =   c1.center   +   ((c2.center-c1.center)/c) * (local_centroid_x);
	return true;
}

/****************************
 * LINE-CIRCLE INTERSECTION *
 ****************************/

bool has_line_intersection( circle const& c, move2 const& line )
{
	real2 closest_point_to_center = line.t + line.r * ((c.center-line.t|line.r)/norm2sq(line.r));
	return dist2sq(  closest_point_to_center,  c.center  ) <= SQ(c.radius);
}

//By convention, return the closest hit of the line on the shape.
bool line_intersection( circle const& c, move2 const& line, real2 & hitpoint, real & hitpoint_factor )
{
	if( !has_line_intersection(c,line) )
		return false;
	//Again, we move the problem in a easier coordinate system.
	//The new system is such that its origin is the center of the circle and it
	//is such that its the input line is parallel to the x-axis.

	//transformation to the new coordinate system.
	//move2 uncentered_circle_and_unhorizontal_line(line.r/SQRT(norm2sq(line.r)),c.center);
	move2 uncentered_circle_and_unhorizontal_line(line.r,c.center);
	real2 horizontal_t = inverse(uncentered_circle_and_unhorizontal_line).map( line.t );
	//std::cout << "uncentered_circle_and_unhorizontal_line = " << uncentered_circle_and_unhorizontal_line << std::endl;
	//std::cout << "inverse( ... ) = " << inverse(uncentered_circle_and_unhorizontal_line) << std::endl;
	//std::cout << "horizontal_t = " << horizontal_t << std::endl;

	
	//solution to the problem.
	real2 local_solution(   -SQRT( (1_r/norm2sq(line.r))*SQ(c.radius) - SQ(horizontal_t.y) ), horizontal_t.y   );
	hitpoint_factor = local_solution.x - horizontal_t.x;
	//std::cout << "local_solution = " << local_solution << std::endl;
	//std::cout << "hitpoint_factor = " << hitpoint_factor << std::endl;
	
	//transformation to the original coordinate system.
	hitpoint = uncentered_circle_and_unhorizontal_line.map( local_solution );
	//std::cout << "hitpoint = " << hitpoint << std::endl;
	return true;
}

/**************************
 * AABR-AABR INTERSECTION *
 **************************/
bool has_intersection( aabr const& r1, aabr const& r2 )
{
	return r1.right > r2.left
	    && r1.left < r2.right
	    && r1.bottom < r2.top
	    && r1.top > r2.bottom ;
}

bool intersection( aabr const& r1, aabr const& r2, real2& centroid, real& mesure )
{
	if( ! has_intersection(r1,r2) )
		return false;
	aabr inner_r = aabr_biggest_inner_aabr(r1,r2);
	centroid = inner_r.bottom_left() +(inner_r.size()) *0.5_r;
	mesure = inner_r.width() *inner_r.height();
	return true;
}

/**************************
 * LINE-AABR INTERSECTION *
 **************************/
bool has_intersection( aabr const& r, move2 const& line )
{
	real2 left_hitpoint, right_hitpoint;
	real useless;
	
	line_intersection( line, move2(r.top_left(),real2(0,-1_r)),   left_hitpoint,  useless);
	line_intersection( line, move2(r.top_right(), real2(0,-1_r)), right_hitpoint, useless);

	return ( left_hitpoint.y < r.bottom && right_hitpoint.y >= r.bottom )
	    || ( left_hitpoint.y > r.top    && right_hitpoint.y <= r.top );
}

/****************************
 * CIRCLE-AABR INTERSECTION *
 ****************************/
bool has_intersection( circle const& c, aabr const& r )
{
	real2 closet_point( CLAMP(r.left,c.center.x,r.right), CLAMP(r.bottom,c.center.x,r.top) );
	return dist2sq(c.center, closet_point) <= SQ(c.radius);
}



} //namespace bOoM

////! \brief The contact point of two moving balls. The time of contact is stored in `t`.
//real2 ball_intersection(
//		real2 const p, real2 const v, real const r_p,
//		real2 const q, real2 const w, real const r_q, real &t );
//
////! \brief The contact point of two moving balls.
//inline real2 ball_intersection(
//		real2 const p, real2 const v, real const r_p,
//		real2 const q, real2 const w, real const r_q)
//{
//	real thisVariableIsUselessInEveryPossibleWay;
//	return ball_intersection(p,v,r_p,q,w,r_q, thisVariableIsUselessInEveryPossibleWay);
//}
//
////! \brief The contact point of two moving balls if a collision occurs before `time_limit`.
//inline real2 ball_intersection_before(
//		real2 const p, real2 const v, real const r_p,
//		real2 const q, real2 const w, real const r_q,
//		real time_limit )
//{
//	real t;
//	real2 intersection= ball_intersection(p,v,r_p,q,w,r_q, t);
//	if( t < time_limit )
//		return nan2;
//	else
//		return intersection;
//}
//
////! \brief The contact point of two moving balls if a collision occurs before `std::get<1>(time_interval)` and after `std::get<0>(time_interval)`.
//inline real2 ball_intersection_within(
//		real2 const p, real2 const v, real const r_p,
//		real2 const q, real2 const w, real const r_q,
//		std::pair<real,real> time_interval )
//{
//	real t;
//	real2 intersection= ball_intersection(p,v,r_p,q,w,r_q, t);
//	if(t < std::get<0>(time_interval) || t > std::get<0>(time_interval) )
//		return nan2;
//	else
//		return intersection;
//}

//TODO: capsule shape around segment line intersection.
//real2 capsule_intersection(
//		real2 const p, real2 const v, real const r_p,
//		real2 const q, real2 const w, real const r_q, real &t );

#endif

