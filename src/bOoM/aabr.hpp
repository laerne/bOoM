#ifndef HEADERBoOm__aabr
#define HEADERBoOm__aabr

#include <iostream>
#include "math2d.hpp"
#include "circle.hpp"

namespace bOoM {
//TODO change rectagle to be bottom, left, width, height.
//Easier to think when reversing or for conversion.

/*! \brief data structure for a 2D axis-aligned bounding rectangle.
 *
 *  The rectangle is determined by its width and height and by the coordinate of one of its four corners.
 *  Which corner is chosen is conventionnal.
 *  In bOoM, physical rectangles (over the type `real`) uses the bottom left vertice as the reference point,
 *  while pixel coordinates for an image uses the top left verticies as the reference point.
 *  Do not forget the minus sign when convert a rectangle from a system to another.
 *  Function bOoM::to_physical_coordinates and bOoM::to_screen_coordinates helps to convert rectangle
 *  and points from a physical space to a screen space.
 *  
 * \relates aabr_biggest_inner_aabr
 */
template<typename R>
struct rectangle {

	//! \brief Default constructor, it leaves fields uninitialized.
	rectangle() = default;
	//! \brief Constructor of a rectangle from the reference vertex and the rectangle size.
	constexpr rectangle( V2<R> vertex, V2<R> size )
		: v(vertex), s(size) {}
	//! \brief Default copy constructor.
	constexpr rectangle( rectangle<R> const& other ) = default;

	V2<R> v; //! reference vertice
	V2<R> s; //! size of the rectangle, i.e. its width and height

	//! \brief The reference vertice.
	V2<R> vertex() const { return v; }
	//! \brief The abciss of reference vertice.
	R x() const { return v.x; }
	//! \brief The ordinate of reference vertice.
	R y() const { return v.y; }

	//! \brief returns the width of the rectangle.
	R width() const { return s.x; }
	//! \brief returns the height of the rectangle.
	R height() const { return s.y; }
	//! \brief returns a vector whose x value is the width of the rectangle and its y value is its height.
	V2<R> size() const { return s; }

	//! \brief returns wheter the rectangle has its right side strictly on the right of its left side and its top side
	//         strictly above its bottom side.
	bool exists() const { return width() > 0 && height() > 0 ; }
	
	//! \brief returns the height of the bottom line of the rectangle.  Defined for bOoM::rectangle<R> and bOoM::rectangle only.
	R bottom() const;
	//! \brief returns the height of the top    line of the rectangle.  Defined for bOoM::rectangle<R> and bOoM::rectangle only.
	R top() const;
	//! \brief returns the height of the left   line of the rectangle.  Defined for bOoM::rectangle<R> and bOoM::rectangle only.
	R left() const;
	//! \brief returns the height of the right  line of the rectangle.  Defined for bOoM::rectangle<R> and bOoM::rectangle only.
	R right() const;
	
	//! \brief returns the bottom-left vertice of the rectangle.  Defined for bOoM::rectangle<R> and bOoM::rectangle only.
	V2<R> bottom_left() const  { return real2( left(), bottom() ); }
	//! \brief returns the bottom-right vertice of the rectangle. Defined for bOoM::rectangle<R> and bOoM::rectangle only.
	V2<R> bottom_right() const { return real2( right(), bottom() ); } 
	//! \brief returns the top-left vertice of the rectangle.     Defined for bOoM::rectangle<R> and bOoM::rectangle only.
	V2<R> top_left() const     { return real2( left(), top() ); } 
	//! \brief returns the top-right vertice of the rectangle.    Defined for bOoM::rectangle<R> and bOoM::rectangle only.
	V2<R> top_right() const    { return real2( right(), top() ); }
};



//! \brief returns the aabr resulting from intersecting aabr's `b1` and `b2`.
//!
//! If the intersection is empty, an incorrect aabr where `result.top < result.bottom`
//! or `result.right < result.left` is returned.
//! Wheter an intersection is possible can easily be checked beforehand using the bOoM::has_intersection() function.
template<typename R>
inline rectangle<R> rectangle_intersection( rectangle<R> const& b1, rectangle<R> const& b2 )
{
	real2 bottom_left = V2<R>( MAX(b1.left(),b2.left()),   MAX(b1.bottom(), b2.bottom()) );
	real2 top_right =   V2<R>( MIN(b1.right(),b2.right()), MIN(b1.top(), b2.top()) );
	return rectangle<R>( bottom_left, top_right - bottom_left );
}

template<typename R>
inline std::ostream& operator<<(std::ostream& s, rectangle<R> const& r)
	{ return s <<"(v:" <<r.v <<",s:" <<r.s <<")"; }

//!< A physical axis-aligned rectangle.  Its reference point `v` is its bottom left vertice.
typedef rectangle<real>   aabr;
//!< A screen axis-aligned rectangle.  Its reference point `v` is its top left vertice.
typedef rectangle<size_t> rect;


//! \brief returns the height of the bottom line of the rectangle.
template<> inline real aabr::bottom() const { return v.y; }
//! \brief returns the height of the top    line of the rectangle.
template<> inline real aabr::top() const    { return v.y + s.y; }
//! \brief returns the height of the left   line of the rectangle.
template<> inline real aabr::left() const   { return v.x; }
//! \brief returns the height of the right  line of the rectangle.
template<> inline real aabr::right() const  { return v.x + s.x; }



//! \brief returns the height of the bottom line of the rectangle.
template<> inline size_t rect::bottom() const { return v.y + s.y; }
//! \brief returns the height of the top    line of the rectangle.
template<> inline size_t rect::top() const    { return v.y; }
//! \brief returns the height of the left   line of the rectangle.
template<> inline size_t rect::left() const   { return v.x; }
//! \brief returns the height of the right  line of the rectangle.
template<> inline size_t rect::right() const  { return v.x + s.x; }



inline aabr aabr_intersection( aabr b1, aabr b2 ) { return rectangle_intersection<real>  (b1,b2); }
inline rect rect_intersection( rect b1, rect b2 ) { return rectangle_intersection<size_t>(b1,b2); }


/************************************
 * Converting between aabr and rect *
 ************************************/
 
//! \brief Computes the x/y scaling factor from the screen rectangle (with origin at 0,0) to the physical rectangle.
real2    to_physical_coordinates_factor (aabr const& screen_zone, size_t_2 screen_resolution);
//! \brief Convert the screen subarea delimited by `pixelRect` from the screen of resolution `screen_resolution`,
//!        into the corresponding physical subarea of physical area `screen_zone`,
//!        where `screen_resolution`, viewed as a rectangle of origin `(0,0)`, is expected to be mapped to `screen_zone`
//!        and conversely.
aabr     to_physical_coordinates (aabr const& screen_zone, size_t_2 const screen_resolution, rect const& pixelRect, real2 const& precomputedFactor);
real2    to_physical_coordinates (aabr const& screen_zone, size_t_2 const screen_resolution, size_t_2 const pixel, real2 const& precomputedFactor);
inline aabr     to_physical_coordinates (aabr const& screen_zone, size_t_2 const screen_resolution, rect const& pixelRect)
	{ return to_physical_coordinates(screen_zone, screen_resolution, pixelRect, to_physical_coordinates_factor(screen_zone, screen_resolution) );}
inline real2    to_physical_coordinates (aabr const& screen_zone, size_t_2 const screen_resolution, size_t_2 const pixel)
	{ return to_physical_coordinates(screen_zone, screen_resolution, pixel, to_physical_coordinates_factor(screen_zone, screen_resolution) );}

//! \brief Computes the x/y scaling factor from the physical rectangle to the screen rectangle (with origin at 0,0).
real2    to_screen_coordinates_factor   (aabr const& screen_zone, size_t_2 screen_resolution);
//! \brief Convert the area delimited by `pixelRect` into an actual screen subarea (in pixels) of a screen of resolution `screen_resolution`,
//!        where `screen_resolution`, viewed as a rectangle of origin `(0,0)`, is expected to be mapped to `screen_zone`
//!        and conversely.
rect     to_screen_coordinates   (aabr const& screen_zone, size_t_2 const screen_resolution, aabr const& physRect, real2 const& precomputedFactor);
size_t_2 to_screen_coordinates   (aabr const& screen_zone, size_t_2 const screen_resolution, real2 const physPoint, real2 const& precomputedFactor);
inline rect     to_screen_coordinates   (aabr const& screen_zone, size_t_2 const screen_resolution, aabr const& physRect)
	{ return to_screen_coordinates(screen_zone, screen_resolution, physRect, to_screen_coordinates_factor(screen_zone, screen_resolution) );}
inline size_t_2 to_screen_coordinates   (aabr const& screen_zone, size_t_2 const screen_resolution, real2 const physPoint)
	{ return to_screen_coordinates(screen_zone, screen_resolution, physPoint, to_screen_coordinates_factor(screen_zone, screen_resolution) );}



/*********************************
 * AABR of mathematical entities *
 *********************************/
 
/*! \brief Computes the smallest aabr such containing the segment obtained by restricting the line to the area
 * delimited by the rectangle `r`.
 * 
 * \param r A rectangle.
 * \param line A line, represented as the transformation of the `x`-axis.  In other words `line.r` is the rotation matrix of
 * the angle between the line and the `x`-axis and `line.t` is the origin of the line.
 * \param res__aabr  Select the aabr such two of its vertices are the intersection points between `line` and `r`.
 * \return `true` if there is an intersection between `r` and `line`, `false` else.
 * If the function returns `false`, `res__aabr` is unmodified.
 */
bool aabr_smallest_subaabr_containing_line( aabr const& r, move2 const& line, aabr& res__aabr);
//! \brief Returns the smallest aabr containing the given aabr, i.e. itself.
inline aabr aabr_of(aabr const& r)
	{ return r; }
//! \brief Returns the smallest aabr containing the given circle.
inline aabr aabr_of(circle const& c)
	{ real2 r2(c.radius,c.radius); return aabr( c.center-r2, r2*2_r ); }


} //namespace bOoM
#endif


