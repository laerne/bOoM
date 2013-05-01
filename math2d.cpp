#include "math2d.hpp"

namespace bOoM {

// _quadrants_:
//  \_  1  _/
//    \_ _/
//  3  _X_  0
//   _/   \_
// _/   2   \_
// Given in degrees on interval ]-180,180].

real approx_angle4(real2 const& p)
{
	if( is_too_small(p.x) && is_too_small(p.y)) return 0.0;
	if( p.y >= -p.x)
	{
		if( p.y <= p.x ) //quadrant 0
			return 45*(p.y/p.x);
		else //quadrant 1
			return 90 -45*(p.x/p.y);
	}
	else
	{
		if( p.y <= p.x ) //quadrant 2
			return -90 -45*(p.x/p.y);
		else //quadrant 3
		{
			real yx = 45*(p.y/p.x);
			return (yx <= 0)? (180+yx) : (-180+yx);
		}
	}
}



// _half-quadrants :
//  \_2 | 1_/
//  3 \ | / 0
//  ----+----
//  4_/ | \_7
// _/ 5 | 6 \_


real approx_angle8(real2 const& p)
{
	if( is_too_small(p.x) && is_too_small(p.y))
		return 0.0;

	real2 a, b; //pivot point of the quadrant
	real shift; //angle shift

	if(p.y >= 0)
	{
		if(p.x >= 0)
		{
			if(p.y <= p.x) // half-quadrant 0
			{
				a= real2( 1, 0 );
				b= real2( CST_SQRT2/2, CST_SQRT2/2 );
				shift=0.0;
			}
			else // half-quadrant 1
			{
				a= real2( CST_SQRT2/2, CST_SQRT2/2 );
				b= real2( 0, 1 );
				shift=45.0;
			}
		}
		else
		{
			if(p.y > -p.x) // half-quadrant 2
			{
				a= real2( 0, 1 );
				b= real2( -CST_SQRT2/2, CST_SQRT2/2 );
				shift=90.0;
			}
			else // half-quadrant 3
			{
				a= real2( -CST_SQRT2/2, CST_SQRT2/2 );
				b= real2( -1, 0 );
				shift=135.0;
			}
		}
	}
	else
	{
		if(p.x < 0)
		{
			if(p.y >= p.x) // half-quadrant 4
			{
				a= real2( -1, 0 );
				b= real2( -CST_SQRT2/2, -CST_SQRT2/2 );
				shift=-180.0;
			}
			else // half-quadrant 5
			{
				a= real2( -CST_SQRT2/2, -CST_SQRT2/2 );
				b= real2( 0, -1 );
				shift=-135.0;
			}
		}
		else
		{
			if(-p.y > p.x) // half-quadrant 6
			{
				a= real2( 0, -1 );
				b= real2( CST_SQRT2/2, -CST_SQRT2/2 );
				shift=-90.0;
			}
			else // half-quadrant 7
			{
				real2 a( CST_SQRT2/2, -CST_SQRT2/2 );
				real2 b( 0, 1 );
				shift=-45.0;
			}
		}
	}

	real proportion= crossProduct_z(p,a) / crossProduct_z(p,(a-b)) ;
	return 45.0*proportion + shift;
}

} //namespace bOoM
