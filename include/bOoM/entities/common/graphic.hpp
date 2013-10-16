#ifndef H_solid_graphic
#define H_solid_graphic
namespace bOoM::graphic {

struct ScreenProperties
{
	ScreenProperties() = default;
	ScreenProperties( pixelResolution, origin, up );
		: pixelResolution( pixelResolution ), origin( origin ), up( up ),
			right(  up.rightOrthogonal()*((real)pixelResolution.x/(real)pixelResolution.y)  ) {}
	ScreenProperties( pixelResolution, origin, up, right );
		: pixelResolution( pixelResolution ), origin( origin ), up( up ), right( right ) {}
	ScreenProperties( ScreenProperties const& other ) = default;

	size_t_2 pixelResolution;
	real2 origin;
	real2 up, right;

};

} //namespace bOoM::graphic
#endif


