#ifndef HEADERBoOm__basemath
#define HEADERBoOm__basemath
/*! \file basemath.hpp
 *  \brief Various basic mathematic utilities.
 */

#include <cmath>
#include <utility>
namespace bOoM {

/*! \brief Short name for a real number type.
 *
 *  The typename exists to use a real number representation easily modifiable
 *  throughout Slava Bogomthe software.
 */
typedef double real;

//! \brief real type literals, from decimal notation.
constexpr bOoM::real operator"" _r(long double const x)
	{ return static_cast<bOoM::real>(x); }
//! \brief real type literals, from integer notation.
constexpr bOoM::real operator"" _r(unsigned long long const x)
	{ return static_cast<bOoM::real>(x); }


//!  \brief The maximum between two elements of a totally orderable type.
#ifndef MAX
#define MAX(a,b) ((a)>=(b) ? (a) : (b))
#endif

//!  \brief The minimum between two elements of a totally orderable type.
#ifndef MIN
#define MIN(a,b) ((a)<=(b) ? (a) : (b))
#endif

//!  \brief Value `a` if `x<a`, `b` if `x>b` else `x`.
#ifndef CLAMP
#define CLAMP(a,x,b) MIN(b,MAX(a,x))
#endif

//!  \brief Tells wheter a real number `x` is inside interval `[a,b]`.
#ifndef WITHIN
#define WITHIN(a,x,b) ((a)<=(x)&&(x)<=(b))
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

//!  \brief The square root of an element.
//
//   This function is slow, avoid it using your math knowledge if possible.
#ifndef SQRT
#define SQRT(x) (std::sqrt(x))
#endif

#ifndef ARCCOS
#define ARCCOS(x) (std::acos(x))
#endif

#ifndef ARCSIN
#define ARCSIN(x) (std::asin(x))
#endif

#ifndef COS
#define COS(x) (std::cos(x))
#endif

#ifndef SIN
#define SIN(x) (std::sin(x))
#endif

//!  \brief The constant π.
#define CST_PI    3.1415926535897932384626433832795028841971693993751058209749_r
//!  \brief The constant \f$\sqrt{2}\f$.
#define CST_SQRT2 1.4142135623730950488016887242096980785696718753769480731767_r

//! \brief Float number smaller than this value are considered to be 0.
#define CST_EPSILON_ZERO 1e-6_r

//! \brief Test wheter a two number are close enough to be consider equals
//! after an error in computations.
constexpr bool equals_about( real x, real y, real epsilon = CST_EPSILON_ZERO )
	{ return ABS(y-x) <= epsilon; }


//! \brief Give the discriminant of the second degree equation.
inline real eqn2_discriminant(real a0, real a1, real a2) { return SQ(a1) -4*a2*a0; }

/*! \brief Return the roots of the second degree equation.
 *
 *  - If there is no roots, a `std::pair(NAN,NAN)` is returned,
 *  - if there is only one root, a pair with twice this same root is returned,
 *    The two copies may slighty differ due error in computations.
 *  - else return the two roots in a pair.
 *  
 *  \param a0 Independent term.
 *  \param a1 Coefficient of the `x` term.
 *  \param a2 Coefficient of the `x*x` term.
 *
 *  This function computes a square root, which is a slow operation.
 */
std::pair<real,real> eqn2_solve(real a0, real a1, real a2);

/*! \brief Return the roots of the second degree equation.
 *
 *  As a precondition `d` is both non-negative and the valid discriminant of the given equation.
 *  This function thus acts like eqn2_solve.
 *
 *  This function computes a square root, which is a slow operation.
 */
std::pair<real,real> eqn2_solve_with_precomputed_discriminant(real a0, real a1, real a2, real d);

} //namespace bOoM
#endif

