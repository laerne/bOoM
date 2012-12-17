#include "basemath.hpp"

namespace bOoM {
namespace eqn2 {

std::pair<real,real> solve(real a2, real a1, real a0)
{
    real d= discriminant( a2, a1, a0 );
    if ( d >= 0 ) return solve_with_precomputed_discriminant(a2, a1, a0, d);
    else return std::make_pair( NAN, NAN );
}

std::pair<real,real> solve_with_precomputed_discriminant(real a2, real a1, real a0, real d)
{
    real double_a2= 2*a2;
    real sqrt_d= std::sqrt(d);
    real left_root=  (-a1 + sqrt_d) / (double_a2);
    real right_root= (-a1 - sqrt_d) / (double_a2);
    return std::make_pair( left_root, right_root );
}

} //namespace eqn2
} //namespace bOoM


