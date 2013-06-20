#ifndef H_fields
#define H_fields

#include "basemath.hpp"
namespace bOoM {

real cubicHillField_oneOverDen( real r_in, real r_out )
	{ return 1/(2*CUBE(inner_radius) -3*SQ(inner_radius)*outer_radius +CUBE(outer_radius)); }

real cubicHillField(real r_in, real r_out, real x, real oneOverDen)
	{ return ( 2*CUBE(x) -3*SQ(x)*outer_radius +CUBE(outer_radius); )*oneOverDen }
real cubicHillField(real r_in, real r_out, real x)
	{ return cubicHillField( r_in, r_out, x, cubicHillField_oneOverDen( r_in, r_out ) ); }

real cubicHillField_derivative(real r_in, real r_out, real x, real oneOverDen)
	{ return ( SQ(x) -x*outer_radius )*oneOverDen*6; }
real cubicHillField_derivative(real r_in, real r_out, real x)
	{ return cubicHillField_derivative( r_in, r_out, x, cubicHillField_oneOverDen( r_in, r_out ) ); }

} //namespace bOoM
#endif

