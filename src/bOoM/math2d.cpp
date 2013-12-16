#include "math2d.hpp"

namespace bOoM {

// _quadrants_:
//  \_  1  _/
//    \_ _/
//  3  _X_  0
//   _/   \_
// _/   2   \_
// Given in degrees on interval ]-180,180].

real approxDeg4(real2 const& p)
{
	if( equals_about(p.x,0_r) && equals_about(p.y,0_r) )
		return 0_r;
	if( p.y >= -p.x)
	{
		if( p.y <= p.x ) //quadrant 0
			return 45_r*(p.y/p.x);
		else //quadrant 1
			return 90_r -45_r*(p.x/p.y);
	}
	else
	{
		if( p.y <= p.x ) //quadrant 2
			return -90_r -45_r*(p.x/p.y);
		else //quadrant 3
		{
			real yx = 45_r*(p.y/p.x);
			return (yx <= 0_r)? (180_r+yx) : (-180_r+yx);
		}
	}
}



// _half-quadrants :
//  \_2 | 1_/
//  3 \ | / 0
//  ----+----
//  4_/ | \_7
// _/ 5 | 6 \_


real approxDeg8(real2 const& p)
{
	if( equals_about(p.x,0_r) && equals_about(p.y,0_r) )
		return 0_r;

	real2 a, b; //pivot point of the quadrant
	real shift; //angle shift

	if(p.y >= 0_r)
	{
		if(p.x >= 0_r)
		{
			if(p.y <= p.x) // half-quadrant 0
			{
				a= real2( 1_r, 0_r );
				b= real2( CST_SQRT2/2_r, CST_SQRT2/2_r );
				shift=0_r;
			}
			else // half-quadrant 1
			{
				a= real2( CST_SQRT2/2_r, CST_SQRT2/2_r );
				b= real2( 0_r, 1_r );
				shift=45_r;
			}
		}
		else
		{
			if(p.y > -p.x) // half-quadrant 2
			{
				a= real2( 0_r, 1_r );
				b= real2( -CST_SQRT2/2_r, CST_SQRT2/2_r );
				shift=90_r;
			}
			else // half-quadrant 3
			{
				a= real2( -CST_SQRT2/2_r, CST_SQRT2/2_r );
				b= real2( -1_r, 0_r );
				shift=135_r;
			}
		}
	}
	else
	{
		if(p.x < 0_r)
		{
			if(p.y >= p.x) // half-quadrant 4
			{
				a= real2( -1_r, 0_r );
				b= real2( -CST_SQRT2/2_r, -CST_SQRT2/2_r );
				shift=-180_r;
			}
			else // half-quadrant 5
			{
				a= real2( -CST_SQRT2/2_r, -CST_SQRT2/2_r );
				b= real2( 0_r, -1_r );
				shift=-135_r;
			}
		}
		else
		{
			if(-p.y > p.x) // half-quadrant 6
			{
				a= real2( 0_r, -1_r );
				b= real2( CST_SQRT2/2_r, -CST_SQRT2/2_r );
				shift=-90_r;
			}
			else // half-quadrant 7
			{
				real2 a( CST_SQRT2/2_r, -CST_SQRT2/2_r );
				real2 b( 0_r, 1_r );
				shift=-45_r;
			}
		}
	}

	real proportion= crossProduct_z(p,a) / crossProduct_z(p,(a-b)) ;
	return 45_r*proportion + shift;
}

} //namespace bOoM
