#ifndef HEADERBALLOON_graphic
#define HEADERBALLOON_graphic

#include <bOoM/GenericEntity.hpp>
#include <bOoM/components/graphic.hpp>
#include "Balloon.hpp"

namespace bOoM {

template<>
struct ComponentImplementation<Balloon, Renderable> : ComponentWithData<Balloon, Renderable>
{
	virtual void   graphic__del__rendered_image(Image* image);
};

} //namespace bOoM
#endif


