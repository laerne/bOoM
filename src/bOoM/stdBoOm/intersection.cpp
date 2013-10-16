#include <bOoM/intersection.hpp>

namespace bOoM {

real2 ball_intersection(
		real2 const p, real2 const v, real const r_p,
		real2 const q, real2 const w, real const r_q, real& t )
{
	real2 p_q = p-q;
	real2 v_w = v-w;
	real r = r_p+r_q;

	real c0= norm2sq(p_q)-SQ(r);
	real c1= 2*(p_q|v_w);
	real c2= norm2sq(v_w);
	real delta= eqn2_discriminant( c0, c1, c2 );
	if ( delta < 0 )
	{
		t=NAN;
		return nan2;
	}
	auto ts = eqn2_solve_with_precomputed_discriminant( c0, c1, c2, delta );
	t = MIN( std::get<0>(ts), std::get<1>(ts) );
	return (  (p+(v*t))*r_p + (q+(w*t))*r_q  )/r;
}

} //namespace bOoM
