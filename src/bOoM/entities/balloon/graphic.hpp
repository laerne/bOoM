#ifndef HEADERBALLOON_graphic
#define HEADERBALLOON_graphic

#include <bOoM/GenericEntity.hpp>
#include <bOoM/components/graphic.hpp>
#include "Balloon.hpp"

namespace bOoM {
namespace graphic {

template<>
color f_color(balloon const& data, real2 const& q)
	{ return color::red; }

} //namespace graphic
} //namespace bOoM
#endif


