#include "aabr.hpp"
#include "intersection.hpp"
namespace bOoM {

bool aabr_smallest_subaabr_containing_line (aabr const& r, move2 const& line, aabr& res__aabr)
{
	real2 p1,p2;
	real unused, thouShaltNotPass;
	if(   line_intersection(r, line, p1, unused, p2, thouShaltNotPass)   )
	{
		real2 bottom_left( MIN(p1.x,p2.x), MIN(p1.y,p2.y));
		real2 top_right( MAX(p1.x,p2.x), MAX(p1.y,p2.y));
		res__aabr = aabr( bottom_left, top_right - bottom_left );
		return true;
	}
	else
	  return false;
}

real2 to_physical_coordinates_factor (aabr const& screen_zone, size_t_2 screen_resolution)
{
	return real2(
		screen_zone.width()  / real(screen_resolution.x) ,
		screen_zone.height() / real(screen_resolution.y) );
}

aabr to_physical_coordinates (aabr const& screen_zone, size_t_2 const screen_resolution, rect const& pixelRect, real2 const& precomputedFactor)
{
	aabr physRect;
	
	physRect.s.x =  real(pixelRect.s.x)  *  precomputedFactor.x ;
	physRect.s.y =  real(pixelRect.s.y)  *  precomputedFactor.y ;
	physRect.v.x =  screen_zone.v.x  +                      ( real(pixelRect.v.x) * precomputedFactor.x );
	physRect.v.y =  screen_zone.v.y  +  screen_zone.s.y  -  ( real(pixelRect.v.y - pixelRect.s.y) * precomputedFactor.y ) ;
	return physRect;
}

real2 to_physical_coordinates (aabr const& screen_zone, size_t_2 const screen_resolution, size_t_2 const pixel, real2 const& precomputedFactor)
{
	real2 qixel;
	
	qixel.x =   screen_zone.v.x   +                      ( real(pixel.x) * precomputedFactor.x );
	qixel.y =   screen_zone.v.y   +  screen_zone.s.y  -  ( real(pixel.y) * precomputedFactor.y );

	return qixel;
}

real2    to_screen_coordinates_factor   (aabr const& screen_zone, size_t_2 screen_resolution)
{
	return real2(
		real(screen_resolution.x) / screen_zone.width()  ,
		real(screen_resolution.y) / screen_zone.height() );
}

rect to_screen_coordinates (aabr const& screen_zone, size_t_2 const screen_resolution, aabr const& physRect, real2 const& precomputedFactor)
{
	rect pixelRect;
	
	pixelRect.s.x =      size_t(std::ceil ( physRect.s.x * precomputedFactor.x ));
	pixelRect.s.y =      size_t(std::ceil ( physRect.s.y * precomputedFactor.y ));
	pixelRect.v.x =      size_t(std::floor(  ( physRect.v.x - screen_zone.v.x )  *  precomputedFactor.x  ));
	pixelRect.v.y = -(   size_t(std::floor(  ( physRect.v.y - screen_zone.v.y )  *  precomputedFactor.y  ))   +   pixelRect.s.y   -   screen_resolution.y   );
	// -screen_resolution.y = -screen_zone.s.y * precomputedFactor.y )  -----^----------------------------------------------------^
	// So screen_zone.s.y is factored out because integer arithmetic should be faster
	return pixelRect;
}

size_t_2 to_screen_coordinates (aabr const& screen_zone, size_t_2 const screen_resolution, real2 const physPoint, real2 const& precomputedFactor)
{
	size_t_2 pixel;
	
	pixel.x =      size_t(std::floor(  ( physPoint.x - screen_zone.v.x )  *  precomputedFactor.x  ));
	pixel.y = -(   size_t(std::floor(  ( physPoint.y - screen_zone.v.y )  *  precomputedFactor.y  ))   -   screen_resolution.y   );
	return pixel;
}
	
} //namespace bOoM

