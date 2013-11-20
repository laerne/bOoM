#ifndef H_aabr
#define H_aabr

#include "math2d.hpp"

namespace bOoM {

//! \brief data structure for a 2D axis-aligned bounding rectangle.
//! \relates aabr_biggest_inner_aabr
struct aabr {

	//! \brief Default constructor, it leaves fields uninitialized.
	aabr() = default;
	//! \brief Standart costructor of a axis-aligned rectangle.
	//!
	//! Its top-edge ordinate (y) is `top`, its left-edge abciss (x) is `left`,
	//! its bottom-edge ordinate is `bottom` and its right-edge ordinate is `right`.
	constexpr aabr( real top, real left, real bottom, real right )
		: bottom(bottom), left(left), right(right), top(top) {}
	//! \brief Constructor of a rectangle from the extremity points of its descending diagonal.
	//!
	//! Its top-edge ordinate (y) is `top_left.y`, its left-edge abciss
	//! (top_left.x) is `left`, its bottom-edge ordinate is `bottom_right.y` and
	//! its right-edge ordinate is `bottom_right.x`.
	constexpr aabr( real2 top_left, real2 bottom_right )
		: bottom(bottom_right.y), left(top_left.x), right(bottom_right.x), top(top_left.y) {}
	//! \brief Default copy constructor.
	constexpr aabr( aabr const& other ) = default;

	real bottom;  //! bottom edge's ordinate
	real left;    //! left edge's abciss
	real right;   //! right edge's abciss
	real top;     //! top edge's ordinate

	//! \brief returns the bottom-left vertice of the rectangle.
	real2 bottom_left() const { return real2(bottom,left); };
	//! \brief returns the bottom-right vertice of the rectangle.
	real2 bottom_right() const { return real2(bottom,right); };
	//! \brief returns the top-left vertice of the rectangle.
	real2 top_left() const { return real2(top,left); };
	//! \brief returns the top-right vertice of the rectangle.
	real2 top_right() const { return real2(top,right); };
	
	//! \brief returns the width of the rectangle.
	real width() const { return right - left; };
	//! \brief returns the height of the rectangle.
	real height() const { return top - bottom; };
	//! \brief returns a vector whose x value is the width of the rectangle and its y value is its height.
	real2 size() const { return real2(width(),height()); };
};

//! \brief returns the aabr resulting from intersecting aabr's `b1` and `b2`.
//!
//! If the intersection is empty, an incorrect aabr where `result.top < result.bottom`
//! or `result.right < result.left` is returned.
//! Wheter an intersection is possible can easily be checked beforehand using the bOoM::has_intersection() function.
inline aabr aabr_biggest_inner_aabr( aabr const& b1, aabr const& b2 )
{
	return aabr( MIN(b1.top, b2.top), 
	             MIN(b1.left,b2.left),
	             MAX(b1.bottom,b2.bottom),
	             MAX(b1.right,b2.right) );
}

} //namespace bOoM
#endif


