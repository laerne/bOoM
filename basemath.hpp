#ifndef H_basemath
#define H_basemath
/*! \file basemath.hpp
 *  \brief Various basic mathematic utilities.
 */

#include <cmath>
#include <utility>
namespace bOoM {

/*! \brief Short name for a real number type.
 *
 *  The typename exists to use a real number representation easily modifiable
 *  throughout the software.
 */
typedef float real;


//!  \brief The maximum between two elements of a totally orderable type.
#ifndef MAX
#define MAX(a,b) ((a)>=(b) ? (a) : (b))
#endif

//!  \brief The minimum between two elements of a totally orderable type.
#ifndef MIN
#define MIN(a,b) ((a)<=(b) ? (a) : (b))
#endif

//!  \brief The absolute value of integer, rational or real number.
#ifndef ABS
#define ABS(x) ((x)>0 ? (x) : -(x))
#endif

//!  \brief The square of the element.
#ifndef SQ
#define SQ(x) ((x)*(x))
#endif

//!  \brief The cube of the element.
#ifndef CUBE
#define CUBE(x) ((x)*(x)*(x))
#endif

//!  \brief The constant π.
#define CST_PI 3.14159265358979323846264338327950288419716939937510582097494459f
//!  \brief The constant \f$\sqrt{2}\f$.
#define CST_SQRT2 1.41421356237309504880168872420969807856967187537694807317668f

//! \brief Float number smaller than this value are considered to be 0.
#define CST_EPSILON_ZERO 1e-6

inline bool is_too_small(real x)
{
    return ABS(x) <= CST_EPSILON_ZERO;
}


namespace eqn2 {
//! \brief The discriminant of the second degree equation.
inline real discriminant(real a2, real a1, real a0) { return SQ(a1) -4*a2*a0; }

/*! \brief Return the roots of the second degree equation.
 *
 *  - If there is no roots, a `std::pair(NAN,NAN)` is returned,
 *  - if there is only one root, a pair with twice this same root is returned,
 *  - else return the two roots in a pair.
 */
std::pair<real,real> solve(real a2, real a1, real a0);

/*! \brief Return the roots of the second degree equation.
 *
 *  It Assumes that `d` is the non-negative valid discriminant of the given equation.
 *  This function computes a square root, which is a slow operation.
 */
std::pair<real,real> solve_with_precomputed_discriminant(real a2, real a1, real a0, real d);
}

} //namespace bOoM
#endif

