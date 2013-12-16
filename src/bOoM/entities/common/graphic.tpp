//implementation of templates in "graphic.hpp"
#include <iostream>
namespace bOoM {
namespace graphic {

//Default behaviour of Renderable items : Do not render.
template<typename DATA>
Image* Renderable<DATA>::graphic__new__rendered_image(aabr const& screen_zone, size_t_2 screen_resolution, rect& result__rendered_zone, size_t& result__pitch, size_t& result__shift)
	{ return nullptr; }
template<typename DATA>
void Renderable<DATA>::graphic__del__rendered_image(Image* image)
//	{ delete image; }
	{ std::cout<<"1"<<std::endl; }

} //namespace graphic
} //namespace bOoM

