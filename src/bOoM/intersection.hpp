#ifndef H_intersection
#define H_intersection
/*! \file
 *  \brief Provides basic method to compute the intersection of basic real 2D shapes.
 */

#include <tuple>
#include "math2d.hpp"
#include "aabr.hpp"
#include "circle.hpp"
namespace bOoM {

/**************************
 *                        *
 *  STATIC INTERSECTIONS  *
 *                        *
 **************************/

/**************************
 * LINE-LINE INTERSECTION *
 **************************/

//! return the value of `s` and `t` such that `p + t*v == q + s*w` holds, or return `{nan,nan}` if there is no solution.
inline real2 line_intersection_factors(
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

/*! \brief Tells wheter the two given lines are sequent.
 *
 *  Note the line are given as a transformation move of the x-axis.
 */
inline bool has_line_intersection( move2 const& l1, move2 const& l2 )
	{ return ( l1.r.y/l1.r.x != l2.r.y/l2.r.x ); }

/*! \brief Tells wheter two line cross each other.
 *
 * If the line cross each other, the intersection point is stored in `hitpoint`.
 * Besides, `hitpoint_factor` is set such that :
 * ```
 *  l2.t + l2.r*hitpoint_factor = hitpoint
 * ```
 */
bool line_intersection( move2 const& l1, move2 const& l2, real2& hitpoint, real& hitpoint_factor );

/*! \brief Tells wheter two line cross each other.
 *
 * If the line cross each other, the intersection point is stored in `hitpoint`.
 * Besides, `hitpoint_factor1` and \a `hitpoint_factor2` are set such that :
 * ```
 *  l1.t + l1.r*hitpoint_factor1 = hitpoint
 *  l2.t + l2.r*hitpoint_factor2 = hitpoint
 * ```
 */
bool line_intersection( move2 const& l1, move2 const& l2, real2& hitpoint, real& hitpoint_factor1, real& hitpoint_factor2 );

/********************************
 * SEGMENT-SEGMENT INTERSECTION *
 ********************************/
inline bool has_lineSegment_intersection( move2 const& l1, move2 const& l2)
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
inline bool lineSegment_intersection( move2 const& l1, move2 const& l2, real2& hitpoint, real& hitpoint_factor )
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
inline bool has_intersection( circle const& c1, circle const& c2 )
	{ return( dist2sq(c1.center,c2.center) <= SQ(c1.radius+c2.radius) ); }

bool intersection( circle const& c1, circle const& c2, real2& centroid, real& mesure );

/****************************
 * LINE-CIRCLE INTERSECTION *
 ****************************/

//! \brief Tells wheter there is an intersection between a line and a circle.
//! \retval `true` if there is an intersection, `false` else.
inline bool has_line_intersection( circle const& c, move2 const& line )
{
	real2 closest_point_to_center = line.t + line.r * ((c.center-line.t|line.r)/norm2sq(line.r));
	return dist2sq(  closest_point_to_center,  c.center  ) <= SQ(c.radius);
}

/*! \brief computes the intersection between a line and a circle.
 * 
 *  \retval `true` if an intersection occurred, `false` else.
 *  
 *  Beside the input circle `c` and input line `line`, the function requires two arguments by reference for outputting where exactly the intersection occurs.
 *  \param hitpoint Position of the _first_ hit between the line and the circle.  The direction of the line is the direction of vector `line.r`.
 *  The position of `line.t` on the line doesn't affect the result.
 *
 *  \param hitpoint_factor Factor `f` such that at the end of the function
 *  ``` hitpoint == line.t + hitpoint_factor*line.r ```
 * \relates bOoM::circle
 */
bool line_intersection( circle const& c, move2 const& line, real2 & hitpoint, real & hitpoint_factor );

/**************************
 * AABR-AABR INTERSECTION *
 **************************/
inline bool has_intersection( aabr const& r1, aabr const& r2 )
{
	return r1.right > r2.left
	    && r1.left < r2.right
	    && r1.bottom < r2.top
	    && r1.top > r2.bottom ;
}

bool intersection( aabr const& r1, aabr const& r2, real2& centroid, real& mesure );

/**************************
 * LINE-AABR INTERSECTION *
 **************************/
 
//! \brief Tells wheter there is an intersection between a line and a axis-aligned rectangle.
//! \retval `true` if there is an intersection, `false` else.
bool has_intersection( aabr const& r, move2 const& line );

/*! \brief computes the intersection between a line and a axis-aligned rectangle.
 * 
 *  \retval `true` if an intersection occurred, `false` else.
 *  
 *  Beside the input rectangle `r` and input line `line`, the function requires two arguments by reference for outputting where exactly the intersection occurs.
 *  The position of `line.t` on the line doesn't affect the result.
 *
 *  \param hitpoint Position of the _first_ hit between the line and the rectangle.  The direction of the line is the direction of vector `line.r`.
 *  \param hitpoint_factor Factor `f` such that at the end of the function
 *  ``` hitpoint == line.t + hitpoint_factor*line.r ```
 *  
 * \relates bOoM::aabr
 */
bool line_intersection( aabr const& r, move2 const& line, real2& hitpoint, real& hitpoint_factor );

/*! \brief computes the intersection between a line and a axis-aligned rectangle.
 * 
 *  \retval `true` if an intersection occurred, `false` else.
 *  
 *  Beside the input rectangle `r` and input line `line`, the function requires four arguments by reference for
 *  outputting where exactly the intersection occurs.
 *  
 *  \param hitpoint1 Position of the _first_ hit between the line and the rectangle.  The direction of the line is the
 *         direction of vector `line.r`.
 *  \param hitpoint1_factor Factor `f` such that at the end of the function
 *  ``` hitpoint1 == line.t + hitpoint1_factor*line.r ```
 *  
 *  \param hitpoint2 Position of the _first_ hit between the line and the rectangle.  The direction of the line is the
 *         direction of vector `line.r`.
 *  \param hitpoint2_factor Factor `f` such that at the end of the function
 *  ``` hitpoint2 == line.t + hitpoint2_factor*line.r ```
 *  
 *  The exact position of `line.t` on the line doesn't affect the result.
 * \relates bOoM::aabr
 */
bool line_intersection( aabr const& r, move2 const& line,
		real2& hitpoint1, real& hitpoint1_factor, real2& hitpoint2, real& hitpoint2_factor );
		

/****************************
 * CIRCLE-AABR INTERSECTION *
 ****************************/
//! \brief Tells wheter there is an intersection between a circle and a axis-aligned rectangle.
//! \retval `true` if there is an intersection, `false` else.
inline bool has_intersection( circle const& c, aabr const& r )
{
	real2 closest_point( CLAMP(r.left,c.center.x,r.right), CLAMP(r.bottom,c.center.x,r.top) );
	return dist2sq(c.center, closest_point) <= SQ(c.radius);
}

/***************************
 *                         *
 *  DYNAMIC INTERSECTIONS  *
 *                         *
 ***************************/

/******************************
 * CIRCLE-CIRCLE INTERSECTION *
 ******************************/
//! \brief The contact point of two moving balls. The time of contact is stored in `t`.
bool dynamic_intersection( circle const& c1, circle const& c2,
		real2 const& v, real2 const& w, real2& contact_point, real2& contact_factor );

} //namespace bOoM


//TODO: capsule shape around segment line intersection.
//real2 capsule_intersection(
//		real2 const p, real2 const v, real const r_p,
//		real2 const q, real2 const w, real const r_q, real &t );

#endif

