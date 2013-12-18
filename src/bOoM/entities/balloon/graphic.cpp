#include "graphic.hpp"

namespace bOoM {

void ComponentImplementation<Balloon,Renderable>::graphic__del__rendered_image(Image* image)
{
	std::cout <<"Hello, I'm circle " <<data().disk <<std::endl;
}

} //namespace bOoM


