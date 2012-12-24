#include "basemath.hpp"

namespace bOoM {

std::pair<real,real> eqn2_solve(real a2, real a1, real a0)
{
	real d= eqn2_discriminant( a2, a1, a0 );
	if ( d >= 0 ) return eqn2_solve_with_precomputed_discriminant(a2, a1, a0, d);
	else return { NAN, NAN };
}

std::pair<real,real> eqn2_solve_with_precomputed_discriminant(real a2, real a1, real a0, real d)
{
	real twice_a2= 2*a2;
	real sqrt_d= std::sqrt(d);
	real left_root=  (-a1 + sqrt_d) / (twice_a2);
	real right_root= (-a1 - sqrt_d) / (twice_a2);
	return { left_root, right_root };
}

} //namespace bOoM


