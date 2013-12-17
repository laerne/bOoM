#include "graphic.hpp"

namespace bOoM {

void ComponentImplementation<Balloon,graphic::Renderable>::graphic__del__rendered_image(graphic::Image* image)
{
	std::cout <<"Hello, I'm circle " <<data().disk <<std::endl;
}

} //namespace bOoM


