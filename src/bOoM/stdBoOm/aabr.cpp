#include <bOoM/aabr.hpp>
#include <bOoM/intersection.hpp>
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

aabr to_physical_coordinates (aabr const& screen_zone, size_t_2 screen_resolution, rect const& pixelRect)
{
	real2 qixel_factor;
	aabr physRect;
	
	qixel_factor.x = screen_zone.width()  / real(screen_resolution.x);
	qixel_factor.y = screen_zone.height() / real(screen_resolution.y);
	
	physRect.s.x =  real(pixelRect.s.x)  *  qixel_factor.x ;
	physRect.s.y =  real(pixelRect.s.y)  *  qixel_factor.y ;
	physRect.v.x =  screen_zone.v.x  +                      ( real(pixelRect.v.x) * qixel_factor.x );
	physRect.v.y =  screen_zone.v.y  +  screen_zone.s.y  -  ( real(pixelRect.v.y - pixelRect.s.y) * qixel_factor.y ) ;
	return physRect;
}

real2 to_physical_coordinates (aabr const& screen_zone, size_t_2 screen_resolution, size_t_2 pixel)
{
	real2 qixel_factor;
	real2 qixel;
	
	qixel_factor.x = screen_zone.width()  / real(screen_resolution.x);
	qixel_factor.y = screen_zone.height() / real(screen_resolution.y);
	
	qixel.x =   screen_zone.v.x   +                      ( real(pixel.x) * qixel_factor.x );
	qixel.y =   screen_zone.v.y   +  screen_zone.s.y  -  ( real(pixel.y) * qixel_factor.y );

	return qixel;
}

rect to_screen_coordinates (aabr const& screen_zone, size_t_2 screen_resolution, aabr const& physRect)
{
	real2 pixel_factor;
	rect pixelRect;
	
	pixel_factor.x = real(screen_resolution.x) / screen_zone.width() ;
	pixel_factor.y = real(screen_resolution.y) / screen_zone.height();
	
	pixelRect.s.x =      size_t(std::ceil ( physRect.s.x * pixel_factor.x ));
	pixelRect.s.y =      size_t(std::ceil ( physRect.s.y * pixel_factor.y ));
	pixelRect.v.x =      size_t(std::floor(  ( physRect.v.x - screen_zone.v.x )  *  pixel_factor.x  ));
	pixelRect.v.y = -(   size_t(std::floor(  ( physRect.v.y - screen_zone.v.y )  *  pixel_factor.y  ))   +   pixelRect.s.y   -   screen_resolution.y   );
	// -screen_resolution.y = -screen_zone.s.y * pixel_factor.y )  ----------^-----------------------------------------------^
	// So screen_zone.s.y is factored out because integer arithmetic is faster
	return pixelRect;
}

size_t_2 to_screen_coordinates (aabr const& screen_zone, size_t_2 screen_resolution, real2 physPoint)
{
	real2 pixel_factor;
	size_t_2 pixel;
	
	pixel_factor.x = real(screen_resolution.x) / screen_zone.width() ;
	pixel_factor.y = real(screen_resolution.y) / screen_zone.height();
	
	pixel.x =      size_t(std::floor(  ( physPoint.x - screen_zone.v.x )  *  pixel_factor.x  ));
	pixel.y = -(   size_t(std::floor(  ( physPoint.y - screen_zone.v.y )  *  pixel_factor.y  ))   -   screen_resolution.y   );
	return pixel;
}
	
} //namespace bOoM

