#include "Entity.hpp"
namespace bOoM {
//dummy functions so that the compiler generate a vtable.
bool Entity::new__rendered_image(aabr const& screen_zone, size_t_2 screen_resolution, Image*& res__image, aabr& res__rendered_zone) const
	{ return false; }
bool Entity::del__rendered_image(Image*& to_be_deleted) const
	{ delete to_be_deleted; return true; }

aabr to_physical_coordinates (aabr const& screen_zone, size_t_2 screen_resolution, rectangle<int> const& pixelRect)
{
	real2 pixel_factor;
	aabr realRect;
	
	pixel_factor.x = screen_zone.width()  / real(screen_resolution.x);
	pixel_factor.y = screen_zone.height() / real(screen_resolution.y);
	
	realRect.left =   screen_zone.left   + ( real(pixelRect.left)   * pixel_factor.x );
	realRect.right =  screen_zone.left   + ( real(pixelRect.right)  * pixel_factor.x );
	realRect.bottom = screen_zone.bottom + ( real(pixelRect.bottom) * pixel_factor.y );
	realRect.top =    screen_zone.bottom + ( real(pixelRect.top)    * pixel_factor.y );
	return realRect;
}

real2 to_physical_coordinates (aabr const& screen_zone, size_t_2 screen_resolution, size_t_2 const& pixel)
{
	real2 pixel_factor;
	real2 qixel;
	
	pixel_factor.x = screen_zone.width()  / real(screen_resolution.x);
	pixel_factor.y = screen_zone.height() / real(screen_resolution.y);
	
	qixel.x = screen_zone.left   + ( real(pixel.x) * pixel_factor.x );
	qixel.y = screen_zone.bottom + ( real(pixel.y) * pixel_factor.y );

	return qixel;
}

rectangle<int> to_screen_coordinates (aabr const& screen_zone, size_t_2 screen_resolution, aabr const& realRect)
{
	real2 pixel_factor_inv;
	rectangle<int> pixelRect;
	
	pixel_factor_inv.x = real(screen_resolution.x) / screen_zone.width() ;
	pixel_factor_inv.y = real(screen_resolution.y) / screen_zone.height();
	pixelRect.left   = int( (realRect.left-screen_zone.left)     * pixel_factor_inv.x );
	pixelRect.right  = int( (realRect.right-screen_zone.left)    * pixel_factor_inv.x );
	pixelRect.bottom = int( (realRect.bottom-screen_zone.bottom) * pixel_factor_inv.y );
	pixelRect.top    = int( (realRect.top-screen_zone.bottom)    * pixel_factor_inv.y );
	return pixelRect;
}
	
} //namespace bOoM


