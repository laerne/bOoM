#ifndef H_math2d
#define H_math2d
/*! \file math2d.hpp
 *  \brief Define two-dimensional vector space data types.
 *
 * The scalars can be in any template mathematical ring `R`.
 * Thus our vector space type is actually a _module_ data type.
 *
 * The files also provides helper `struct`s for rotation and orientation
 * preserving isometries (as a composition of a rotation and a translation).
 */

#include <iostream>
#include "basemath.hpp"
namespace bOoM {

/*! \brief Two-dimensional vector structure.
 *
 * Attributes are public :
 * no need to use boilerplate code with accessor and mutators.
 */
template<typename R>
struct V2
{
	//! \brief Default constructor, with no initialisation of variables.
	constexpr V2(){}
	//! \brief Standard constructor.
	constexpr V2(R const& x, R const& y) : x(x), y(y) {}
	//! \brief Copy constructor.
	constexpr V2(V2<R> const& q) = default;
	//! \brief Per-component affectation operator.
	V2<R>& operator= (V2<R> const& q) = default;
	//! \brief Per-component sum and affectation.
	V2<R>& operator+=(V2<R> const& q) { x += q.x; y+= q.y; return *this; }
	//! \brief Per-component difference and affectation.
	V2<R>& operator-=(V2<R> const& q) { x -= q.x; y-= q.y; return *this; }
	//! \brief Per-component product by the scalar and affectation.
	V2<R>& operator*=(R const& a) { x *= a; y*= a; return *this; }
	//! \brief Per-component product by the inverse scalar and affectation.
	V2<R>& operator/=(R const& a) { x /= a; y/= a; return *this; }
	//! \brief Identity operator : return a copy of self.
	V2<R>  operator+ () const         { return V2( x, y); }
	//! \brief Opposite operator : return a new vector with opposite values.
	V2<R>  operator- () const         { return V2(-x,-y); }
	//! \brief Per-component equality operator.
	bool operator==(V2<R> const& q) const { return x==q.x && y==q.y; }
	//! \brief Per-component inequality operator.
	bool operator!=(V2<R> const& q) const { return x!=q.x || y!=q.y; }
	//! \brief If R is castable to M, then this casts V2<R> to V2<M> component-wise.
	template<typename M>
	operator V2<M>() { return V2<M>( (M)x, (M)y ); }

	R x;//!< abscissa.
	R y;//!< ordinate.
};

//! \brief Vector sum operator.
//! \relates bOoM::V2
template<typename R>
V2<R> operator+(V2<R> const& p, V2<R> const& q)
	{ return V2<R>(p)+=q; }

//! \brief Vector difference operator.
//! \relates bOoM::V2
template<typename R>
V2<R> operator-(V2<R> const& p, V2<R> const& q)
	{ return V2<R>(p)-=q; }

//! \brief Vector scale operator.
//! \relates bOoM::V2
template<typename R>
V2<R> operator*(V2<R> const& p, R const& a)
	{ return V2<R>(p)*=a; }

//! \brief Vector inverse scale operator, over a field `F`.
//! \relates bOoM::V2
template<typename F>
V2<F> operator/(V2<F> const& p, F const& a)
	{ return V2<F>(p)/=a; }

//! \brief Dot product operator : return the dot product of this vector and `q`.
//!
//! For readability, the expression should be enclosed in parentheses : `(p|q)`.
//! \relates bOoM::V2
template<typename R>
R operator| (V2<R> const& p, V2<R> const& q)
	{ return p.x*q.x + p.y*q.y; }

//! \brief Dot product operator.  Equivalent to V2::operator| .
//! \relates bOoM::V2
template<typename R>
R dotProduct(V2<R> const& p, V2<R> const& q)
	{ return p.x*q.x + p.y*q.y; }

//! \brief Norm of the vector obtained by a cross product operation.
//! \relates bOoM::V2
template<typename R>
R crossProduct_z(V2<R> const& p, V2<R> const& q)
	{ return p.x*q.y - p.y*q.x; }

//! \brief Output a string representation of a two-dimensional vector.
//! \relates bOoM::V2
template<typename R>
std::ostream& operator<<(std::ostream& s, V2<R> const& p)
	{ s <<"(" << p.x <<"," << p.y <<")"; return s; }
	
//! \brief Manhattan norm of the vector, i.e. the sum of the absolute value
//  of each of its components.
//! \relates bOoM::V2
template<typename R>
R norm1(V2<R> const& p)
	{ return ABS(p.x)+ABS(p.y); }
//! \brief Manhattan distance of two vectors. \sa norm1().
//! \relates bOoM::V2
template<typename R>
R dist1(V2<R> const& p, V2<R> const& q)
	{ return norm1(q-p); }

//! \brief Squared euclidean norm of the vector, i.e. the sum of the
//  square of each of its components.
//! \relates bOoM::V2
template<typename R>
R norm2sq(V2<R> const& p)
	{ return SQ(p.x)+SQ(p.y); }
//! \brief Squared euclidean distance of two vectors. \sa norm2sq().
//! \relates bOoM::V2
template<typename R>
R dist2sq(V2<R> const& p, V2<R> const& q)
	{ return norm2sq(q-p); }

//! \brief Maximum norm of the vector, i.e. the maximum over the absolute
// value of each of its components.
//! \relates bOoM::V2
template<typename R>
R norm_max(V2<R> const& p)
	{ return MAX(ABS(p.x),ABS(p.y)); }
//! \brief Maximum distance of two vectors. \sa norm_max().
//! \relates bOoM::V2
template<typename R>
R dist_max(V2<R> const& p, V2<R> const& q)
	{ return norm_max(q-p); }

//! \brief Right orthogonal vector of `p`.
//! \relates bOoM::V2
template<typename R>
V2<R> rightOrthogonal(V2<R> const& p)
	{ return V2<R>( p.y, -p.x ); }
//! \brief Left orthogonal vector of `p`.
//! \relates bOoM::V2
template<typename R>
V2<R> leftOrthogonal(V2<R> const& p)
	{ return V2<R>( -p.y, p.x ); }

//! \brief Returns wheter the vector is nan or not
//! \relates bOoM::V2
template<typename R>
bool isnan(V2<R> const& p)
	{ return std::isnan(p.x) || std::isnan(p.y); }



//! \brief Return the image point of the application on `p` of rotation specified by vector `r`.
//! \relates bOoM::V2
//! \see rotations.hpp
template<typename R>
V2<R> rot2_map(V2<R> const& r, V2<R> const& p)
	{ return V2<R>(  p.x*r.x-p.y*r.y,  p.x*r.y+p.y*r.x  ); }

/*! \brief Rotation (specified by a vector) composition and affectation.  Can
 * be viewed as a matrix product.
 *
 * Since it involves only two-dimensional rotations (and possibly scale
 * operations), the composition is commutative.
 * \relates bOoM::V2
 */
template<typename R>
V2<R>& rot2_mult_inplace(V2<R> & r1, V2<R> const& r2)
{
	R const cos = r1.x;
	r1.x= r1.x*r2.x - r1.y*r2.y;
	r1.y= r1.y*r2.x + cos*r2.y;
	return r1;
}
//! \brief Rotation (specified by a vector) composition.
//! \relates bOoM::V2
template<typename R>
V2<R> rot2_mult(V2<R> copy, V2<R> const& r)
	{ return rot2_mult_inplace(copy,r); }
	
//! \brief Return the inverse rotation.
//! \relates bOoM::V2
template<typename R>
V2<R> rot2_inverse(V2<R> const& r) { return V2<R>(r.x, -r.y)/=norm2sq(r); }
//TODO bypass the above division when norm of r is 1.

/*! \brief Two-dimensional moves, i.e. orientation-preserving isometries.
 *
 * A Move is expressed as the composition of a rotation and then a translation.
 */
template<typename R>
struct Move2
{
	//! \brief Default constructor, with no initialisation of variables.
	//
	constexpr Move2(){}
	//! \brief Standard constructor.
	constexpr Move2(V2<R> const& rotation, V2<R> const& translation)
		: r(rotation), t(translation) {}
	//! \brief Copy constructor.
	constexpr Move2(Move2<R> const& mv) = default;
	//! \brief Per-component affectation operator.
	Move2<R>& operator=(Move2<R> const& mv) = default;
	//! \brief Per-component equality operator.
	bool operator==(Move2<R> const& mv) const { return r==mv.r && t==mv.t; }
	//! \brief Per-component inequality operator.
	bool operator!=(Move2<R> const& mv) const { return r!=mv.r || t!=mv.t; }
	//! \brief Return the image point of the application of this move on `p`.
	V2<R> map(V2<R> const& p) const { return rot2_map(r,p) += t; }
	//! \brief Assign `this`∘`mv` to this move.
	//!
	//! Note that move composition is not commutative.
	Move2<R>& precompose(Move2<R> const& mv)
		{ t=map(mv.t);  rot2_mult_inplace(r,mv.r); return *this; }
	//! \brief If R is castable to M, then this cast Move2<R> to Move2<M> component-wise.
	template<typename M>
	operator Move2<M>() { return Move2<M>( (V2<M>)r, (V2<M>)t ); }

	V2<R> r; //!< Rotation component.
	V2<R> t; //!< Translation component.
};

//! Return a new move representing the composition of `m1` and `m2`.
//!
//! Note that move composition is not commutative.
//! \relates bOoM::Move2
template<typename R>
Move2<R> compose(Move2<R> const& m2, Move2<R> const& m1)
	{ return Move2<R>(m2).precompose(m1); }
//! \brief Output a string representation of the move.
//! \relates bOoM::Move2
template<typename R>
std::ostream& operator<<(std::ostream& s, Move2<R> const& mv)
	{ s <<"(r:" <<mv.r <<",t:" << mv.t <<")"; return s; }
//! \brief Return the inverse move of `mv`
//! \relates bOoM::Move2
template<typename R>
Move2<R>  inverse(Move2<R> const& mv)
	{ const V2<R> r_inv= rot2_inverse(mv.r); return Move2<R>(r_inv, -rot2_map(r_inv, mv.t)); }

//shortcuts
//! Equivalent to `mv.map(p)` .
//! \relates bOoM::Move2
template<typename R>
V2<R> operator>>(V2<R> const& p, Move2<R> const& mv) { return mv.map(p); }
//! Equivalent to `p= mv.map(p)` .
//! \relates bOoM::Move2
template<typename R>
V2<R>& operator>>=(V2<R>& p, Move2<R> const& mv) { return p = mv.map(p); }



// Common data types
typedef V2<real> real2; //!< Euclidean plane vector.
typedef Move2<real> move2; //!< Euclidean plane move.
typedef V2<std::size_t> size_t_2; //! Two-dimentional index/size.

// Usefull constants
real2 constexpr zero2(0,0); //!< Constant to the null vector.
real2 constexpr rot2_id(1.f,0.f); //!< Constant to the identity rotation.
move2 constexpr move2_id(rot2_id, zero2); //!< Constant to the identity move.
real2 constexpr nan2(NAN,NAN); //!< Constant to an non-existant vector.


// approximative comparators
inline bool equals_about(real2 const& p, real2 const& q)
	{ return equals_about(p.x,q.x) && equals_about(p.y,q.y); }
inline bool equals_about(move2 const& a, move2 const& b)
	{ return equals_about(a.t,b.t) && equals_about(a.r,b.r); }

// real angle utilities
//! \brief Return a new real rotation object from `angle`, in radians.
inline real2 rot2_fromRadian(real angle)
	{ return real2(COS(angle), SIN(angle)); }
//! \brief Return approximatively the angle in degrees between `p` and `(1,0)`.
//!
//! Tests suggests that the maximum error can rise up to four degrees.
real approxDeg4(real2 const& p);
//! \brief Return approximatively the angle in degrees between `p` and `(1,0)`.
//!
//! The function is a bit slower than \ref approx_angle4, but it is more precise :
//! its errors never go over 1 degree.
real approxDeg8(real2 const& p);

} //namespace bOoM
#endif

