#ifndef H_aabr
#define H_aabr

#include <iostream>
#include "math2d.hpp"
#include "circle.hpp"

namespace bOoM {
//TODO change rectagle to be bottom, left, width, height.
//Easier to think when reversing or for conversion.

//! \brief data structure for a 2D axis-aligned bounding rectangle.
//! \relates aabr_biggest_inner_aabr
template<typename R>
struct rectangle {

	//! \brief Default constructor, it leaves fields uninitialized.
	rectangle() = default;
	//! \brief Standart costructor of a axis-aligned rectangle.
	//!
	//! Its top-edge ordinate (y) is `top`, its left-edge abciss (x) is `left`,
	//! its bottom-edge ordinate is `bottom` and its right-edge ordinate is `right`.
	constexpr rectangle( R top, R left, R bottom, R right )
		: bottom(bottom), left(left), right(right), top(top) {}
	//! \brief Constructor of a rectangle from the extremity points of its descending diagonal.
	//!
	//! Its top-edge ordinate (y) is `top_left.y`, its left-edge abciss
	//! (top_left.x) is `left`, its bottom-edge ordinate is `bottom_right.y` and
	//! its right-edge ordinate is `bottom_right.x`.
	constexpr rectangle( V2<R> top_left, V2<R> bottom_right )
		: bottom(bottom_right.y), left(top_left.x), right(bottom_right.x), top(top_left.y) {}
	//! \brief Default copy constructor.
	constexpr rectangle( rectangle<R> const& other ) = default;

	R bottom;  //! bottom edge's ordinate
	R left;    //! left edge's abciss
	R right;   //! right edge's abciss
	R top;     //! top edge's ordinate

	//! \brief returns the bottom-left vertice of the rectangle.
	V2<R> bottom_left() const { return V2<R>(bottom,left); };
	//! \brief returns the bottom-right vertice of the rectangle.
	V2<R> bottom_right() const { return V2<R>(bottom,right); };
	//! \brief returns the top-left vertice of the rectangle.
	V2<R> top_left() const { return V2<R>(top,left); };
	//! \brief returns the top-right vertice of the rectangle.
	V2<R> top_right() const { return V2<R>(top,right); };
	
	//! \brief returns the width of the rectangle.
	R width() const { return right - left; };
	//! \brief returns the height of the rectangle.
	R height() const { return top - bottom; };
	//! \brief returns a vector whose x value is the width of the rectangle and its y value is its height.
	V2<R> size() const { return V2<R>(width(),height()); };

	//! \brief returns wheter the rectangle has its right side strictly on the right of its left side and its top side
	//         strictly above its bottom side.
	bool exists() const { return width() > 0 && height() > 0 ; }
};

typedef rectangle<real> aabr;

//! \brief returns the aabr resulting from intersecting aabr's `b1` and `b2`.
//!
//! If the intersection is empty, an incorrect aabr where `result.top < result.bottom`
//! or `result.right < result.left` is returned.
//! Wheter an intersection is possible can easily be checked beforehand using the bOoM::has_intersection() function.
template<typename R>
inline rectangle<R> rectangle_intersection( rectangle<R> const& b1, rectangle<R> const& b2 )
{
	return rectangle<R>( MIN(b1.top, b2.top), 
	                     MAX(b1.left,b2.left),
	                     MAX(b1.bottom,b2.bottom),
	                     MIN(b1.right,b2.right) );
}
inline aabr aabr_intersection( aabr b1, aabr b2 ) { return rectangle_intersection<real>(b1,b2); }

template<typename R>
inline std::ostream& operator<<(std::ostream& s, rectangle<R> const& r)
	{ return s <<"(t:" << r.top <<",r:" << r.right <<",b:" << r.bottom <<",l:" << r.left <<")"; }

/*********************************
 * AABR of mathematical entities *
 *********************************/
bool aabr_smallest_subaabr_containing_line( aabr const& r, move2 const& line, aabr& res__aabr);
inline aabr aabr_of(aabr const& r)
	{ return r; }
inline aabr aabr_of(circle const& c)
	{ return aabr( c.center.y+c.radius, c.center.x-c.radius, c.center.y-c.radius, c.center.x+c.radius ); }


} //namespace bOoM
#endif


