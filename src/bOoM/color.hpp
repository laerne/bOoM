#ifndef H_color
#define H_color

#include <iostream>
#include <SDL2/SDL.h>
#include "basemath.hpp"

namespace bOoM
{

typedef uint8_t colorChannel;
#define COLORCHANNEL_RANGE_MIN 0x00
#define COLORCHANNEL_RANGE_MAX 0xFF

struct color
{
	color() = default;
	explicit constexpr color( colorChannel red, colorChannel green, colorChannel blue, colorChannel alpha = COLORCHANNEL_RANGE_MAX )
		: r(red), g(green), b(blue), a(alpha) {}
	static constexpr color from_rgba8888(uint32_t rgba)
	{
		return color( uint8_t(rgba>>24       ),
		              uint8_t(rgba>>16 & 0xFF),
		              uint8_t(rgba>>8  & 0xFF),
		              uint8_t(rgba     & 0xFF) );
	}
	static constexpr color from_rgbaFFFF(float red, float green, float blue, float alpha = 1.f)
	{
		return color( uint8_t( red   * 255 ),
		              uint8_t( green * 255 ),
		              uint8_t( blue  * 255 ),
		              uint8_t( alpha * 255 ) );
	}
	color( color const& other ) = default;
	color& operator= ( color const& other ) = default;
	uint32_t to_rgba8888() const
		{ return r<<24 | g<<16 | b<<8 | a ; }

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
	{
		r=uint_fast16_t(r)*c.r/COLORCHANNEL_RANGE_MAX;
		g=uint_fast16_t(g)*c.g/COLORCHANNEL_RANGE_MAX;
		b=uint_fast16_t(b)*c.b/COLORCHANNEL_RANGE_MAX;
		return *this;
	}
	//! \brief Change luminosity of the color by factor `t`
	//
	//! Simply do *this per channel (exept alpha) product by the factor.
	color& operator*= (real t)
		{ r= uint8_t( real(r)*t ); g= uint8_t( real(g)*t ); b= uint8_t( real(b)*t ); return *this; }
	//! \brief Change luminosity of the color by factor `1/t`
	color& operator/= (real t)
		{ r= uint8_t( real(r)/t ); g= uint8_t( real(g)/t ); b= uint8_t( real(b)/t ); return *this; }


	static color const red;
	static color const green;
	static color const blue;
	static color const white;
	static color const black;
	static color const transparent;
};

inline bool operator== (color const& a, color const& b)
  { return a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a; }
inline bool operator!= (color const& a, color const& b)
  { return a.r != b.r || a.g != b.g || a.b != b.b || a.a != b.a; }

//TODO better handling of alpha below ??

//! \brief Add the contribution of two colors `a` and `b` together and return it in a new color.
//!
//! Simply the two colors `a` and `b` per channel (exept alpha).
inline color operator+ (color const& a, color const& b)
  { return color(a)+=b; }
//! \brief Filter the color `a` with the color `b` and return the result in a new color.
//!
//! Simply do a per channel (exept alpha) product.
inline color operator* (color const& a, color const& b)
  { return color(a)*=b; }
//! \brief Return the color with same hue and saturation but with luminosity scaled by factor `t`.
inline color operator* (color const& a, real t)
  { return color(a)*=t; }
//! \brief Return the color with same hue and saturation but with luminosity scaled by factor `1/t`.
inline color operator/ (color const& a, real t)
  { return color(a)/=t; }

inline colorChannel& red(color& c) { return c.r; }
inline colorChannel& green(color& c) { return c.g; }
inline colorChannel& blue(color& c) { return c.b; }
inline colorChannel& alpha(color& c) { return c.a; }

//! \brief Clamp color channel so that they fit in the displayable range.
inline color clamp(color const& a)
	{ return color( CLAMP(COLORCHANNEL_RANGE_MIN, a.r, COLORCHANNEL_RANGE_MAX),
	                CLAMP(COLORCHANNEL_RANGE_MIN, a.g, COLORCHANNEL_RANGE_MAX),
	                CLAMP(COLORCHANNEL_RANGE_MIN, a.b, COLORCHANNEL_RANGE_MAX),
	                CLAMP(COLORCHANNEL_RANGE_MIN, a.a, COLORCHANNEL_RANGE_MAX) ); }

//! \brief Complement of the color `a`.
//! 
//! `a` and `complement(a)` are linked by `a + complement(a) = white`,
//! where white is the color with full intensity in each channel.
inline color complement (color const& a)
	{ return color( COLORCHANNEL_RANGE_MAX -a.r, COLORCHANNEL_RANGE_MAX -a.g, COLORCHANNEL_RANGE_MAX -a.b, COLORCHANNEL_RANGE_MAX -a.a ); }



//! \brief basic string representation of the color.
inline std::ostream& operator<<(std::ostream& s, color const& c)
	{ return s <<"#" <<int(c.r) <<"." <<int(c.g) <<"." <<int(c.b) <<"." <<int(c.a) ; }
	//{ return s <<"#" <<std::hex<<std::setfill('0')<<std::setw(2) <<int(c.r) <<std::hex<<std::setfill('0')<<std::setw(2) <<int(c.g) <<std::hex<<std::setfill('0')<<std::setw(2) <<int(c.b) <<std::hex<<std::setfill('0')<<std::setw(2) <<int(c.a) ; }

} //namespace bOoM
#endif

