#include <bOoM/aabr.hpp>
#include <bOoM/intersection.hpp>
namespace bOoM {

bool aabr_smallest_subaabr_containing_line( aabr const& r, move2 const& line, aabr& res__aabr)
{
	real2 p1,p2;
	real unused, thouShaltNotPass;
	if(     line_intersection(r, line, p1, unused, p2, thouShaltNotPass)
	  && (   (  (p1.x == r.left || p1.x == r.right )
	         && (p2.x == r.left || p2.x == r.right )
	         )
	     ||  (  (p1.y == r.top  || p1.y == r.bottom)
	         && (p2.y == r.top  || p2.y == r.bottom)
	         )
	     )     
	  )
	{
		res__aabr = aabr( MAX(p1.y,p2.y), MIN(p1.x,p2.x), MIN(p1.y,p2.y), MAX(p1.x,p2.x) );
		return true;
	}
	else
	  return false;
}

} //namespace bOoM

