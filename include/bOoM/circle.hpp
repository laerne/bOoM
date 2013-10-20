#ifndef H_circle
#define H_circle
namespace bOoM {

struct circle
{
	circle() = default;
	circle( real2 center, real radius)
		: center(center), radius(radius ) {}
	circle( real center_x, real center_y, real radius )
		: center(center_x, center_y), radius(radius) {}
	circle( circle const& other ) = default;


	real2 center;
	real2 radius;
};

bool has_intersection( circle const& c1, circl const& c2 )
	{ return( dist2sq(c1.center,c2.center) <= SQ(c1.radius+c2.radius) ); }

bool has_intersection( circle const& c, move2 const& line )
{ 
	//real cry_over_crx = c.radius.y / c.radius.x;
	//real x2_factor = 1 + SQ(cry_over_crx);
	//real x1_factor = 2 *( c.center.x 
	//                    - line.t.x*SQ(cry_over_crx)
	//                    + line.t.y*cry_over_crx
	//                    - c.center.y * cry_over_crx
	//                    );
	//real x0_factor = SQ(c.center.x)
	//               + SQ(c.center.y)
	//               + SQ(line.t.y)
	//               + SQ(line.t.x)*SQ(cry_over_crx)
	//               - 2* line.t.x * line.t.y * cry_over_crx
	//               - 2* line.t.y * c.center.y
	//               + 2* line.t.x * cry_over_crx * c.center.y ;
	//return eqn2_discriminant(x2_factor, x1_factor, x0_factor) >= 0_r; 
}

} //namespace bOoM
#endif


