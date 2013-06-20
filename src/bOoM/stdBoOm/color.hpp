#ifndef H_color
#define H_color

#include <basemath.hpp>

namespace bOoM
{

typedef float colorChannel;

struct color
{
	color() {};
	explicit color( colorChannel red, colorChannel green, colorChannel blue, colorChannel alpha = 1.0f )
    : r(red), g(green), b(blue), a(alpha) {}
	explicit color( uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha )
    : color( float(red)/255, float(green)/255, float(blue)/255, float(alpha)/255 ) {}
	explicit color( uint32_t rgba )
    : color( rgba&0xFF, (rgba>>8)&0xFF, (rgba>>16)&0xFF, (rgba>>24) ) {}
	color( color const& other ) = default;
	operator= ( color const& other ) = default;
	explicit operator uint32_t()
    { return a<<24 | b<<16 | g<<8 | r; }

	colorChannel r;
	colorChannel g;
	colorChannel b;
	colorChannel a;
}


//! \brief assigns the value of a to b;
//color& operator= (color & a, real b);

bool operator== (color const& a, color const& b)
  { return a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a; }
bool operator!= (color const& a, color const& b);
  { return a.r != b.r || a.g != b.g || a.b != b.b || a.a != b.a; }

//! \brief Sum the two color `a` and `b` per channel.
color& operator+= (color & a, color const& b)
  { a.r+=b.r; a.g+=b.g; a.b+=b.b; a.a+=b.a; }
//! \brief Sum the two color `a` and `b` per channel.
color operator+ (color const& a, color const& b)
  { return color(a)+=b; }

//! \brief Short writing for `a += (-b)`.
color& operator-= (color & a, color const& b)
  { a.r-=b.r; a.g-=b.g; a.b-=b.b; a.a-=b.a; }
//! \brief Short writing for `a + (-b)`.
color operator- (color const& a, color const& b)
  { return color(a)-=b; }

//! \brief Filter the ligth of a by the light of b.
//!
//! Simply do a per-component product.
color& operator*= (color & a, color const& b)
  { a.r*=b.r; a.g*=b.g; a.b*=b.b; a.a*=b.a; }
//! \brief Give the color of a double filter with the ligth of a by the light of b.
//!
//! Simply do a per-component product.
color operator* (color const& a, color const& b);
  { return color(a)*=b; }
color& operator*= (color & a, real t)
  { a.r*=t; a.g*=t; a.b*=t; a.a*=t; }
color operator* (color const& a, real t)
  { return color(a)*=t; }
color& operator/= (color & a, real t)
  { a.r/=t; a.g/=t; a.b/=t; a.a/=t; }
color operator/ (color const& a, real t)
  { return color(a)/=t; }

//#define red(c) ((c).red)
colorChannel& red(color& c) { return c.r; }
colorChannel& green(color& c) { return c.r; }
colorChannel& blue(color& c) { return c.r; }
colorChannel& alpha(color& c) { return c.r; }

//! \brief Clamp color channel so that they fit in the displayable range
//!
//! Store the result in a.
color& do_clamp(color & a)
{
  a.r= CLAMP(0f, a.r, 1f);
  a.g= CLAMP(0f, a.g, 1f);
  a.b= CLAMP(0f, a.b, 1f);
  a.a= CLAMP(0f, a.a, 1f);
  return *this;
}
  
//! \brief Clamp color channel so that they fit in the displayable range.
color clamp(color const& a)
  { return color( CLAMP(0f, a.r, 1f), CLAMP(0f, a.g, 1f), CLAMP(0f, a.b, 1f), CLAMP(0f, a.a, 1f) ); }

//! \brief Complement of the color `a`.
//!
//! Store the result in a.
color& do_complement (color & a)
  { a.r= 1f -a.r; a.g= 1f -a.g; a.b= 1f -a.b; a.a= 1f -a.a; return *this; }
//! \brief Complement of the color `a`.
//! 
//! `a` and `complement(a)` are linked by `a + complement(a) = white`,
//! where white is the color with full intensity in each channel.
color complement (color const& a)
  { return color( 1f -a.r, 1f -a.g, 1f -a.b, 1f -a.a ); }

} //namespace bOoM
#endif

