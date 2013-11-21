#ifndef H_colorf
#define H_colorf

#include <iostream>
#include <SDL2/SDL.h>
#include "basemath.hpp"

namespace bOoM
{

typedef float colorfChannel;
#define COLORFCHANNEL_RANGE_MIN 0.0f
#define COLORFCHANNEL_RANGE_MAX 1.0f

struct colorf
{
	colorf() = default;
	explicit constexpr colorf( colorfChannel red, colorfChannel green, colorfChannel blue, colorfChannel alpha = COLORFCHANNEL_RANGE_MAX )
    : a(alpha), r(red), g(green), b(blue) {}
	static constexpr color from_argb8888(uint32_t argb)
	{
		return color( float(argb>>16 & 0xFF)/255,
		              float(argb>>8  & 0xFF)/255,
		              float(argb     & 0xFF)/255,
		              float(argb>>24       )/255 );
	}
	static constexpr color from_rgbaFFFF(float red, float green, float blue, float alpha = COLORFCHANNEL_RANGE_MAX)
		{ return color( red, green, blue, alpha ); }
	colorf( colorf const& other ) = default;
	colorf& operator= ( colorf const& other ) = default;
	uint32_t to_argb8888() const
    { return uint32_t(a*255)<<24 | uint32_t(r*255)<<16 | uint32_t(g*255)<<8 | uint32_t(b*255); }

	colorfChannel a;
	colorfChannel r;
	colorfChannel g;
	colorfChannel b;
	
	//! \brief Add the contribution of colorf `c` to colorf `*this`.
	//!
	//! Simply sum the two colorf per channel (exept alpha) and store the result to `*this`.
	colorf& operator+= (colorf const& c)
  	{ r+=c.r; g+=c.g; b+=c.b; /* *this+=c.*this; */ return *this; }
	//! \brief Filter the colorf `*this` with the colorf `c` (for example the colorf of *this ligth source).
	//!
	//! Simply do *this per channel (exept alpha) product.
	colorf& operator*= (colorf const& c)
  	{ r*=c.r; g*=c.g; b*=c.b; /* *this*=c.*this; */ return *this; }
	//! \brief Change luminosity of the colorf by factor `t`
	//
	//! Simply do *this per channel (exept alpha) product by the factor.
	colorf& operator*= (real t)
  	{ r*=t; g*=t; b*=t; /* *this*=t; */ return *this; }
	//! \brief Change luminosity of the colorf by factor `1/t`
	colorf& operator/= (real t)
  	{ r/=t; g/=t; b/=t; /* *this/=t; */ return *this; }
  	
	static colorf const red;
	static colorf const green;
	static colorf const blue;
	static colorf const white;
	static colorf const black;
	static colorf const transparent;
};

// approximative comparators
inline bool equals_about(colorf const& a, colorf const& b, real epsilon = CST_EPSILON_ZERO )
	{ return equals_about(a.r,b.r,epsilon)
	      && equals_about(a.g,b.g,epsilon)
	      && equals_about(a.b,b.b,epsilon)
	      && equals_about(a.a,b.a,epsilon); }
inline bool operator== (colorf const& a, colorf const& b)
//  { return a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a; }
	{ return equals_about(a,b); }
inline bool operator!= (colorf const& a, colorf const& b)
//  { return a.r != b.r || a.g != b.g || a.b != b.b || a.a != b.a; }
	{ return !equals_about(a,b); }

//TODO better handling of alpha below ??

//! \brief Add the contribution of two colorfs `a` and `b` together and return it in a new colorf.
//!
//! Simply the two colorfs `a` and `b` per channel (exept alpha).
inline colorf operator+ (colorf const& a, colorf const& b)
  { return colorf(a)+=b; }
//! \brief Filter the colorf `a` with the colorf `b` and return the result in a new colorf.
//!
//! Simply do a per channel (exept alpha) product.
inline colorf operator* (colorf const& a, colorf const& b)
  { return colorf(a)*=b; }
//! \brief Return the colorf with same hue and saturation but with luminosity scaled by factor `t`.
inline colorf operator* (colorf const& a, real t)
  { return colorf(a)*=t; }
//! \brief Return the colorf with same hue and saturation but with luminosity scaled by factor `1/t`.
inline colorf operator/ (colorf const& a, real t)
  { return colorf(a)/=t; }

inline colorfChannel& red(colorf& c) { return c.r; }
inline colorfChannel& green(colorf& c) { return c.g; }
inline colorfChannel& blue(colorf& c) { return c.b; }
inline colorfChannel& alpha(colorf& c) { return c.a; }

////! \brief Clamp colorf channel so that they fit in the displayable range
////!
////! Store the result in a.
//colorf& do_clamp(colorf & a)
//{
//  a.r= CLAMP(COLORFCHANNEL_RANGE_MIN, a.r, COLORFCHANNEL_RANGE_MAX);
//  a.g= CLAMP(COLORFCHANNEL_RANGE_MIN, a.g, COLORFCHANNEL_RANGE_MAX);
//  a.b= CLAMP(COLORFCHANNEL_RANGE_MIN, a.b, COLORFCHANNEL_RANGE_MAX);
//  a.a= CLAMP(COLORFCHANNEL_RANGE_MIN, a.a, COLORFCHANNEL_RANGE_MAX);
//  return *this;
//}
  
//! \brief Clamp colorf channel so that they fit in the displayable range.
inline colorf clamp(colorf const& a)
	{ return colorf( CLAMP(COLORCHANNEL_RANGE_MIN, a.r, COLORCHANNEL_RANGE_MAX),
	                 CLAMP(COLORCHANNEL_RANGE_MIN, a.g, COLORCHANNEL_RANGE_MAX),
	                 CLAMP(COLORCHANNEL_RANGE_MIN, a.b, COLORCHANNEL_RANGE_MAX),
	                 CLAMP(COLORCHANNEL_RANGE_MIN, a.a, COLORCHANNEL_RANGE_MAX) ); }

//! \brief Complement of the colorf `a`.
//! 
//! `a` and `complement(a)` are linked by `a + complement(a) = white`,
//! where white is the colorf with full intensity in each channel.
inline colorf complement (colorf const& a)
  { return colorf( COLORFCHANNEL_RANGE_MAX -a.r, COLORFCHANNEL_RANGE_MAX -a.g, COLORFCHANNEL_RANGE_MAX -a.b, COLORFCHANNEL_RANGE_MAX -a.a ); }



//! \brief basic string representation of the colorf.
inline std::ostream& operator<<(std::ostream& s, colorf const& c)
	{ return s <<"#{r:" <<c.r <<",g:" <<c.g <<",b:" <<c.b <<",a:" <<c.a <<"}"; }

} //namespace bOoM
#endif

