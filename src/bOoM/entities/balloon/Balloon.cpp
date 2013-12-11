#include "Balloon.hpp"
#include <bOoM/aabr.hpp>

namespace bOoM {

bool Balloon::new__rendered_image(aabr const& screen_zone, size_t_2 screen_resolution, Image*& res__image, aabr& res__rendered_zone) const
{
	aabr displayzone = aabr_intersection( aabr_of(disk), screen_zone );
	if( displayzone.exists() )
	{
		res__rendered_zone = displayzone;
		rect rendered_pixel_zone = to_screen_coordinates(screen_zone, screen_resolution, displayzone);
		res__image = new Image(rendered_pixel_zone.size());

		//TODO syntaxic sugar to iterate on every pixel
		for( size_t_2 p(0,0); p.y < rendered_pixel_zone.height(); ++p.y )
		for( p.x = 0        ; p.x < rendered_pixel_zone.width();  ++p.x )
		{
			//center of pixel box
			real2 q = to_physical_coordinates( displayzone, rendered_pixel_zone.size(), p );

			(*res__image)[p] = dist2sq( disk.center, q ) <= disk.radius ? color::red : color::transparent;
		}
		return true;
	}
	else
	{
		return false;
	}
}

} //namespace bOoM

