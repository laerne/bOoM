#include <bOoM/aabr.hpp>
#include <bOoM/intersection.hpp>
namespace bOoM {

bool aabr_smallest_subaabr_containing_line (aabr const& r, move2 const& line, aabr& res__aabr)
{
	real2 p1,p2;
	real unused, thouShaltNotPass;
	if(     line_intersection(r, line, p1, unused, p2, thouShaltNotPass)
	  && (   (  (p1.x == r.left()  || p1.x == r.right() )
	         && (p2.x == r.left()  || p2.x == r.right() )
	         )
	     ||  (  (p1.y == r.top()   || p1.y == r.bottom())
	         && (p2.y == r.top()   || p2.y == r.bottom())
	         )
	     )     
	  )
	{
		real2 vertex( MIN(p1.x,p2.x), MIN(p1.y,p2.y));
		real2 size = real2( MIN(p1.x,p2.x), MIN(p1.y,p2.y)) - vertex;
		res__aabr = aabr( vertex, size );
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

