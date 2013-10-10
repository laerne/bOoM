#include "Solid.hpp"
namespace bOoM {
int Solid::init()
{
	become(idle);
}
int Solid::render(ScreenProperties const& bufferType, ScreenBuffer& buffer);
{
	real2 steps(
			bufferType.up / pixelResolution.y, 
			bufferType.up.rightOrthogonal() / pixel_position.y
			);

	size_t_2 pixelNb;
	for( int pixelNb.x = 0; pixelNb.x < bufferType.pixelResolution.x; ++pixelNb.x )
	for( int pixelNb.y = 0; pixelNb.y < bufferType.pixelResolution.y; ++pixelNb.y )
	{
		real2 pixelPosition = bufferType.origin +steps.x*( 0.5_r+pixelNb.x ) +steps.y*( 0.5+pixelNb.y );
		if( dist2sq(pixelPosition, this->origin) <= this->tmptest__radius )
		{
			buffer.setPixel(pixelNb, whiteColor);
		}
	}
}

} //namespace bOoM

