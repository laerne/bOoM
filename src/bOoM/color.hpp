#ifndef H_color
#define H_color

#include <iostream>
#include <SDL2/SDL.h>
#include "basemath.hpp"

namespace bOoM
{

//typedef SDL_Color color;

typedef float colorChannel;

struct color
{
	color() {};
	explicit color( colorChannel red, colorChannel green, colorChannel blue, colorChannel alpha = 1.f )
    : r(red), g(green), b(blue), a(alpha) {}
	explicit color( uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255)
    : color( float(red)/255, float(green)/255, float(blue)/255, float(alpha)/255 ) {}
	explicit color( uint32_t rgba )
    : color( float(rgba&0xFF)/255, float((rgba>>8)&0xFF)/255, float((rgba>>16)&0xFF)/255, float(rgba>>24)/255 ) {}
	color( color const& other ) = default;
	color& operator= ( color const& other ) = default;
	explicit operator uint32_t()
    { return uint32_t(a*255)<<24 | uint32_t(b*255)<<16 | uint32_t(g*255)<<8 | uint32_t(r*255); }

	colorChannel r;
	colorChannel g;
	colorChannel b;
	colorChannel a;
	
	//! \brief Add the contribution of color `c` to color `*this`.
	//!
	//! Simply sum the two color per channel (exept alpha) and store the result to `*this`.
	color& operator+= (color const& c)
  	{ r+=c.r; g+=c.g; b+=c.b; /* *this+=c.*this; */ return *this; }
	//! \brief Filter the color `*this` with the color `c` (for example the color of *this ligth source).
	//!
	//! Simply do *this per channel (exept alpha) product.
	color& operator*= (color const& c)
  	{ r*=c.r; g*=c.g; b*=c.b; /* *this*=c.*this; */ return *this; }
	//! \brief Change luminosity of the color by factor `t`
	//
	//! Simply do *this per channel (exept alpha) product by the factor.
	color& operator*= (real t)
  	{ r*=t; g*=t; b*=t; /* *this*=t; */ return *this; }
	//! \brief Change luminosity of the color by factor `1/t`
	color& operator/= (real t)
  	{ r/=t; g/=t; b/=t; /* *this/=t; */ return *this; }
};

// approximative comparators
inline bool equals_about(color const& a, color const& b)
	{ return equals_about(a.r,b.r)
	      && equals_about(a.g,b.g)
	      && equals_about(a.b,b.b)
	      && equals_about(a.a,b.a); }
bool operator== (color const& a, color const& b)
//  { return a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a; }
	{ return equals_about(a,b); }
bool operator!= (color const& a, color const& b)
//  { return a.r != b.r || a.g != b.g || a.b != b.b || a.a != b.a; }
	{ return !equals_about(a,b); }

//TODO better handling of alpha below ??

//! \brief Add the contribution of two colors `a` and `b` together and return it in a new color.
//!
//! Simply the two colors `a` and `b` per channel (exept alpha).
color operator+ (color const& a, color const& b)
  { return color(a)+=b; }
//! \brief Filter the color `a` with the color `b` and return the result in a new color.
//!
//! Simply do a per channel (exept alpha) product.
color operator* (color const& a, color const& b)
  { return color(a)*=b; }
//! \brief Return the color with same hue and saturation but with luminosity scaled by factor `t`.
color operator* (color const& a, real t)
  { return color(a)*=t; }
//! \brief Return the color with same hue and saturation but with luminosity scaled by factor `1/t`.
color operator/ (color const& a, real t)
  { return color(a)/=t; }

colorChannel& red(color& c) { return c.r; }
colorChannel& green(color& c) { return c.g; }
colorChannel& blue(color& c) { return c.b; }
colorChannel& alpha(color& c) { return c.a; }

////! \brief Clamp color channel so that they fit in the displayable range
////!
////! Store the result in a.
//color& do_clamp(color & a)
//{
//  a.r= CLAMP(0.f, a.r, 1.f);
//  a.g= CLAMP(0.f, a.g, 1.f);
//  a.b= CLAMP(0.f, a.b, 1.f);
//  a.a= CLAMP(0.f, a.a, 1.f);
//  return *this;
//}
  
//! \brief Clamp color channel so that they fit in the displayable range.
color clamp(color const& a)
  { return color( CLAMP(0.f, a.r, 1.f), CLAMP(0.f, a.g, 1.f), CLAMP(0.f, a.b, 1.f), CLAMP(0.f, a.a, 1.f) ); }



////! \brief Complement of the color `a`.
////!
////! Store the result in a.
//color& do_complement (color & a)
//  { a.r= 1.f -a.r; a.g= 1.f -a.g; a.b= 1.f -a.b; a.a= 1.f -a.a; return *this; }

//! \brief Complement of the color `a`.
//! 
//! `a` and `complement(a)` are linked by `a + complement(a) = white`,
//! where white is the color with full intensity in each channel.
color complement (color const& a)
  { return color( 1.f -a.r, 1.f -a.g, 1.f -a.b, 1.f -a.a ); }



//! \brief basic string representation of the color.
std::ostream& operator<<(std::ostream& s, color const& c)
	{ return s <<"(r:" <<c.r <<",g:" <<c.g <<",b:" <<c.b <<",a:" <<c.a <<")"; }

namespace tone {
color const red(1.f,0.f,0.f);
color const green(0.f,1.f,0.f);
color const blue(0.f,0.f,1.f);
color const white(1.f,1.f,1.f);
color const black(0.f,0.f,0.f);
color const transparent(0.f,0.f,0.f,1.f);
} //namespace tone

} //namespace bOoM
#endif

