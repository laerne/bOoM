#include "graphic.hpp"
#include <iostream>
namespace bOoM {
namespace graphic {

//Default behaviour of Renderable items : Do not render.
Image* Renderable::graphic__new__rendered_image(aabr const& screen_zone, size_t_2 screen_resolution, rect& result__rendered_zone, size_t& result__pitch, size_t& result__shift)
	{ return nullptr; }
void Renderable::graphic__del__rendered_image(Image* image)
	{ delete image; }

} //namespace graphic
} //namespace bOoM

