#include <bOoM/basemath.hpp>

namespace bOoM {

std::pair<real,real> eqn2_solve(real a0, real a1, real a2)
{
	real d= eqn2_discriminant( a0, a1, a2 );
	if ( d >= 0 ) return eqn2_solve_with_precomputed_discriminant(a0, a1, a2, d);
	else return { NAN, NAN };
}

std::pair<real,real> eqn2_solve_with_precomputed_discriminant(real a0, real a1, real a2, real d)
{
	real twice_a2= 2*a2;
	real sqrt_d= SQRT(d);
	real left_root=  (-a1 + sqrt_d) / (twice_a2);
	real right_root= (-a1 - sqrt_d) / (twice_a2);
	return { left_root, right_root };
}

} //namespace bOoM


