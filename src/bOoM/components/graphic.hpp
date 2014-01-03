#ifndef HEADERBoOm__graphic
#define HEADERBoOm__graphic

#include <bOoM/Image.hpp>
#include <bOoM/aabr.hpp>
#include <bOoM/color.hpp>
#include <bOoM/math2d.hpp>

namespace bOoM {
namespace graphic {


template<typename D>
struct Renderable
{
	static color f_color(D& data, real2 const& q)
		{ return color::transparent; }
};


} //namespace graphic
} //namespace bOoM

#endif


