#include <bOoM/intersection.hpp>
#include <utility>

namespace bOoM {

/**************************
 *                        *
 *  STATIC INTERSECTIONS  *
 *                        *
 **************************/

/**************************
 * LINE-LINE INTERSECTION *
 **************************/
 
bool line_intersection( move2 const& l1, move2 const& l2, real2& hitpoint, real& hitpoint_factor )
{
	if(! has_line_intersection(l1,l2) )
		return false;
	real2 const factors= line_intersection_factors( l1.t, l1.r, l2.t, l2.r );
	hitpoint_factor = factors.y;
	hitpoint= l2.t + l2.r*(factors.y);
	return true;
}

bool line_intersection( move2 const& l1, move2 const& l2, real2& hitpoint, real& hitpoint_factor1, real& hitpoint_factor2 )
{
	if(! has_line_intersection(l1,l2) )
		return false;
	real2 const factors= line_intersection_factors( l1.t, l1.r, l2.t, l2.r );
	hitpoint_factor1 = factors.x;
	hitpoint_factor2 = factors.y;
	hitpoint= l1.t + l1.r*hitpoint_factor1;
	return true;
}

/******************************
 * CIRCLE-CIRCLE INTERSECTION *
 ******************************/
bool intersection( circle const& c1, circle const& c2, real2& centroid, real& mesure )
{
	if( ! has_intersection(c1,c2) )
		return false;
	// Now we consider the center of c1 to lie in (0,0) and the center of c2 to lie in (c,0).
	// where c = dist2( c1.center, c2.center )
	// In this system, the intersection point between the two circle are at (l1,h) and (l1,-h).
	// 
	// Using 3 square roots and two arcsines.
	real c = SQRT( dist2sq(c1.center,c2.center) );
	real l1 = ( dist2sq(c1.center,c2.center)+SQ(c1.radius)-SQ(c2.radius) ) / ( 2*c );
	real h = SQRT ( SQ(c1.radius) - SQ(l1) );
	real l2 = c - l1;
	
	real area1 = 2*SQ(c1.radius)*ARCSIN(h/c1.radius) - 2*l1*h ;
	real centroid1_x = ((2_r/3_r) * SQRT( SQ(c1.radius) - SQ(l1) ))/area1;

	real area2 = 2*SQ(c2.radius)*ARCSIN(h/c2.radius) - 2*l2*h ;
	real centroid2_x = ((-2_r/3_r) * SQRT( SQ(c2.radius) - SQ(l2) ))/area2 + c;

	// Computation the result.  Beware the centroid must be described in the canonic reference system.
	mesure = area1 + area2;
	real local_centroid_x = (centroid1_x*area1 + centroid2_x*area2)/mesure;
	centroid =   c1.center   +   ((c2.center-c1.center)/c) * (local_centroid_x);
	return true;
}


/****************************
 * LINE-CIRCLE INTERSECTION *
 ****************************/
bool line_intersection( circle const& c, move2 const& line, real2 & hitpoint, real & hitpoint_factor )
{
	if( !has_line_intersection(c,line) )
		return false;
	//Again, we move the problem in a easier coordinate system.
	//The new system is such that its origin is the center of the circle and it
	//is such that its the input line is parallel to the x-axis.

	//transformation to the new coordinate system.
	//move2 uncentered_circle_and_unhorizontal_line(line.r/SQRT(norm2sq(line.r)),c.center);
	move2 uncentered_circle_and_unhorizontal_line(line.r,c.center);
	real2 horizontal_t = inverse(uncentered_circle_and_unhorizontal_line).map( line.t );

	
	//solution to the problem.
	real2 local_solution(   -SQRT( (1_r/norm2sq(line.r))*SQ(c.radius) - SQ(horizontal_t.y) ), horizontal_t.y   );
	//the transformed line.r (a.k.a. horizontal_r) has already been normalized to 1.
	//thus the following difference is equivalent to how much horizontal_r fits between the local solution and horizontal_t.
	hitpoint_factor = ( local_solution.x - horizontal_t.x );
	
	//transformation to the original coordinate system.
	hitpoint = uncentered_circle_and_unhorizontal_line.map( local_solution );
	return true;
}

/**************************
 * AABR-AABR INTERSECTION *
 **************************/
bool intersection( aabr const& r1, aabr const& r2, real2& centroid, real& mesure )
{
	if( ! has_intersection(r1,r2) )
		return false;
	aabr inner_r = aabr_intersection(r1,r2);
	centroid = inner_r.bottom_left() +(inner_r.size()) *0.5_r;
	mesure = inner_r.width() *inner_r.height();
	return true;
}

/**************************
 * LINE-AABR INTERSECTION *
 **************************/
bool has_intersection( aabr const& r, move2 const& line )
{
	real2 left_hitpoint, right_hitpoint;
	real useless;
	
	line_intersection( line, move2(r.top_left(),real2(0,-1_r)),   left_hitpoint,  useless);
	line_intersection( line, move2(r.top_right(), real2(0,-1_r)), right_hitpoint, useless);

	return !(  ( left_hitpoint.y < r.bottom() && right_hitpoint.y < r.bottom() )
	       ||  ( left_hitpoint.y > r.top()    && right_hitpoint.y > r.top() )  );
}

bool line_intersection( aabr const& r, move2 const& line, real2& hitpoint, real& hitpoint_factor )
{
	real2 useless2;
	real useless;
	return line_intersection(r,line,hitpoint,hitpoint_factor,useless2,useless);
}

bool line_intersection( aabr const& r, move2 const& line,
		real2& hitpoint1, real& hitpoint1_factor, real2& hitpoint2, real& hitpoint2_factor )
{
	real2 left_hitpoint, right_hitpoint;
	real left_factor, right_factor;
	
	line_intersection( line, move2( real2(0,-1_r), r.top_left()  ), left_hitpoint,  left_factor);
	line_intersection( line, move2( real2(0,-1_r), r.top_right() ), right_hitpoint, right_factor);
	
	// Division by case.
	// Comment shows a visual representation of the rectangle made with '-', '|' and '+' and of the line made with '*'
	if(  left_hitpoint.y <= r.top() && left_hitpoint.y >= r.bottom()  )
	{
		hitpoint1 = left_hitpoint;
		hitpoint1_factor = left_factor;
		// +----------+
		// |          |
		// ************
		// |          |
		// +----------+
		if(  right_hitpoint.y <= r.top() && right_hitpoint.y >= r.bottom()  )
		{
			hitpoint2 = right_hitpoint;
			hitpoint2_factor = right_factor;
		}
		// +----------+
		// |          |
		// **         |
		// | **       |
		// +---**-----+
		else if(  right_hitpoint.y < r.bottom() )
		{
			line_intersection( line, move2(r.bottom_left(),real2(0,1_r)),  hitpoint2,  hitpoint2_factor );
		}
		// +----***---+
		// |  **      |
		// ***        |
		// |          |
		// +----------+
		else // (  right_hitpoint.y > r.top()  )
		{
			line_intersection( line, move2(r.top_left(),real2(0,1_r)),  hitpoint2,  hitpoint2_factor );
		}
	}
	else if(  left_hitpoint.y < r.bottom() )
	{
		// +----------+
		// |          |
		// |        ***
		// |     ***  |
		// +--***-----+
		if(  ( right_hitpoint.y <= r.top() && right_hitpoint.y >= r.bottom() )  )
		{
			hitpoint1 = right_hitpoint;
			hitpoint1_factor = right_factor;
			
			line_intersection( line, move2(r.bottom_left(),real2(0,1_r)),  hitpoint2,  hitpoint2_factor );
		}
		// +----------+
		// |          |
		// |          |
		// |          |
		// +----------+
		// ************
		else if(  right_hitpoint.y < r.bottom() )
			return false;
		// +---*------+
		// |    *     |
		// |    *     |
		// |     *    |
		// +-----*----+
		else // (  right_hitpoint.y > r.top()  )
		{
			line_intersection( line, move2(r.bottom_left(),real2(0,1_r)),  hitpoint1,  hitpoint1_factor );
			line_intersection( line, move2(r.top_left(),real2(0,1_r)),  hitpoint2,  hitpoint2_factor );
		}
	}
	else // (  left_hitpoint.y > r.top() )
	{
		// +-***------+
		// |    **    |
		// |      *** |
		// |         **
		// +----------+
		if(  ( right_hitpoint.y <= r.top() && right_hitpoint.y >= r.bottom() )  )
		{
			hitpoint1 = right_hitpoint;
			hitpoint1_factor = right_factor;
			line_intersection( line, move2(r.top_left(),real2(0,1_r)),  hitpoint2,  hitpoint2_factor );
		}
		// +---*------+
		// |   *      |
		// |    *     |
		// |    *     |
		// +-----*----+
		else if(  right_hitpoint.y < r.bottom() )
		{
			line_intersection( line, move2(r.top_left(),real2(0,1_r)),  hitpoint1,  hitpoint1_factor );
			line_intersection( line, move2(r.bottom_left(),real2(0,1_r)),  hitpoint2,  hitpoint2_factor );
		}
		// ************
		// +----------+
		// |          |
		// |          |
		// |          |
		// +----------+
		else // (  right_hitpoint.y > r.top()  )
			return false;
	}

	if( hitpoint2_factor < hitpoint1_factor )
	{
		std::swap(hitpoint1_factor,hitpoint2_factor);
		std::swap(hitpoint1, hitpoint2);
	}
	return true;
}

/***************************
 *                         *
 *  DYNAMIC INTERSECTIONS  *
 *                         *
 ***************************/

/******************************
 * CIRCLE-CIRCLE INTERSECTION *
 ******************************/

bool dynamic_intersection( circle const& c1, circle const& c2,
		real2 const& v, real2 const& w, real2& contact_point, real& contact_factor )
{
	real2 const& p = c1.center;
	real2 const& q = c2.center;
	real const& r_p = c1.radius;
	real const& r_q = c2.radius;
	
	real2 p_q = p-q;
	real2 v_w = v-w;
	real r = r_p+r_q;

	real a0= norm2sq(p_q)-SQ(r);
	real a1= 2*(p_q|v_w);
	real a2= norm2sq(v_w);
	real delta= eqn2_discriminant( a0, a1, a2 );
	if ( delta < 0 )
		return false;
		
	auto ts = eqn2_solve_with_precomputed_discriminant( a0, a1, a2, delta );
	contact_factor = MIN( std::get<0>(ts), std::get<1>(ts) );
	contact_point = (  (p+(v*contact_factor))*r_p + (q+(w*contact_factor))*r_q  )/r;
	return true;
}

} //namespace bOoM
