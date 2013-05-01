#ifndef H_color
#define H_color

//TODO use openGL ?

#include <allegro5/allegro.h>

\namespace bOoM
{

struct RGBA
{
	//! \brief Default constructor, with no initialisation of variables.
	RGBA(){}
	//! \brief Standard constructor.
	RGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char alpha)
		: value( a << 24 | r << 16 | g << 8 | b ) {}
	//! \brief Copy constructor.
	RGBA(RGBA<R> const& other) = default;

	//! \brief Per-component product by the scalar and affectation.
	RGBA<R>& operator*=(R a)
	{ x *= a; y*= a; return *this; }

	//! \brief Per-component equality operator.
	bool operator==(RGBA<R> const& q) const { return x==q.x && y==q.y; }
	//! \brief Per-component inequality operator.
	bool operator!=(RGBA<R> const& q) const { return x!=q.x || y!=q.y; }
	/*! \brief Manhattan norm of the vector, i.e. the sum of the absolute value
	 *  of each of its components.
	 */
	R norm1()    const { return ABS(x)+ABS(y); }
	/*! \brief Squared euclidean norm of the vector, i.e. the sum of the
	 *  square of each of its components.
	 */
	R norm2sq()  const { return SQ(x) + SQ(y); }
	/*! \brief Maximum norm of the vector, i.e. the maximum over the absolute
	 * value of each of its components.
	 */
	R norm_max() const { return MAX(ABS(x),ABS(y)); }
	//! \brief Returns wheter the vector is nan or not
	bool isnan() const { return std::isnan(x) || std::isnan(y); }

	//!< alpha,r,g,b component in one single int as it is commonly the case.
	uint32 value;
};

} //namespace bOoM
#endif

