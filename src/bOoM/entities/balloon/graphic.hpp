#ifndef H_balloon_graphic
#define H_balloon_graphic

#include <bOoM/entities/Entity.hpp>
#include <bOoM/entities/common/graphic.hpp>
#include "Balloon.hpp"

namespace bOoM {

template<>
struct ComponentImplementation<Balloon, graphic::Renderable> : ComponentWithData<Balloon, graphic::Renderable>
{
	virtual void   graphic__del__rendered_image(graphic::Image* image);
};

} //namespace bOoM
#endif


