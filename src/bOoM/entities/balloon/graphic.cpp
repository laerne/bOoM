#ifndef H_graphic
#define H_graphic

#include <bOoM/Image.hpp>
#include <bOoM/math2d.hpp>
#include <bOoM/aabr.hpp>

#include <bOoM/entities/common/graphic.hpp>

#include "Balloon.hpp"

namespace bOoM {
namespace graphic {

template<>
Image* Renderable<Balloon>::graphic__new__rendered_image(aabr const& screen_zone, size_t_2 screen_resolution, rect& result__rendered_zone, size_t& result__pitch, size_t& result__shift)
	{ return nullptr; }
template<>
void Renderable<Balloon>::graphic__del__rendered_image(Image* image)
	{ std::cout<<"2"<<std::endl; }


} //namespace graphic
} //namespace bOoM
#endif


