#ifndef H_intersection
#define H_intersection

#include <tuple>
#include "math2d.hpp"

namespace bOoM {

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

inline real2 line_intersection(
		real2 const p, real2 const v,
		real2 const q, real2 const w )
{
	real2 const factors= line_intersection_factors( p, v, q, w );
	return p + v*(factors.x);
}

inline real2 pointed_vector_intersection(
		real2 const p, real2 const v,
		real2 const q, real2 const w )
{
	real2 const factors= line_intersection_factors( p, v, q, w );
	if(  WITHIN( 0.0, factors.x, 1.0) && WITHIN( 0.0, factors.x, 1.0 )  )
		return p + v*(factors.x);
	else
		return nan2;
}

real2 ball_intersection(
		real2 const p, real2 const v, real const r_p,
		real2 const q, real2 const w, real const r_q, real &t );
inline real2 ball_intersection(
		real2 const p, real2 const v, real const r_p,
		real2 const q, real2 const w, real const r_q)
{
	real thisVariableIsUselessInEveryPossibleWay;
	return ball_intersection(p,v,r_p,q,w,r_q, thisVariableIsUselessInEveryPossibleWay);
}

inline real2 ball_intersection_interval(
		real2 const p, real2 const v, real const r_p,
		real2 const q, real2 const w, real const r_q,
		std::pair<real,real> time_interval )
{
	real t;
	real2 intersection= ball_intersection(p,v,r_p,q,w,r_q, t);
	if(std::isnan(t) || t < std::get<0>(time_interval) || t > std::get<0>(time_interval) )
		return nan2;
	else
		return intersection;
}


} //namespace bOoM

#endif

