#include <boost/test/unit_test.hpp>
#include "test_macros.hpp"

#include <bOoM/intersection.hpp>

namespace test {
using namespace bOoM;

struct SomeShapes
{
	
	circle c0, c1, cm1, celse;
	move2 l0, l1;
	SomeShapes
	( circle const& c0 = circle(real2(0_r,0_r), 0.75_r)
	, circle const& c1 = circle(real2(1_r,0_r), 0.75_r)
	, circle const& cm1 = circle(real2(-1_r,0_r), 0.75_r)
	, circle const& celse = circle(real2(0_r,2_r), 1.5_r)
	, move2  const& l0 = move2( real2(-1_r,0_r), real2(2_r,0.75_r/SQRT(2_r)) )
	, move2  const& l1 = move2( real2(-1_r,1_r), real2(3_r,-2_r) )
	)
		: c0(c0), c1(c1), cm1(cm1), celse(celse), l0(l0), l1(l1) {}
};

BOOST_AUTO_TEST_SUITE( shapes )

BOOST_FIXTURE_TEST_CASE( shapes2d__line_line, SomeShapes )
{
	real2 p;
	real f1;
	real f2;
	BOOST_CHECK( line_intersection(l0, l1, p, f1, f2) );
	BOOMST_CHECK_APPROX_EQUAL( real2(1-(0.75_r/SQRT(2_r)),0.75_r/SQRT(2_r)), p );
	BOOMST_CHECK_APPROX_EQUAL( 1 + (0.75_r/SQRT(2_r)), f1 );
	BOOMST_CHECK_APPROX_EQUAL( 2 + (0.75_r/SQRT(2_r)), f2 );
}

BOOST_FIXTURE_TEST_CASE( shapes2d__circle_circle, SomeShapes )
{
	real2 centroid;
	real area;
	BOOST_CHECK( ! has_intersection(cm1,c1) );
	BOOST_CHECK( has_intersection(c0,c1) );
	intersection( c0, c1, centroid, area );
	BOOMST_CHECK_APPROX_EQUAL( real2(0.5_r,0_r), centroid );
	intersection( c0, celse, centroid, area );
	BOOMST_CHECK_APPROX_EQUAL( 0.324616_r, area );
}

BOOST_FIXTURE_TEST_CASE( shapes2d__line_circle, SomeShapes )
{
	real2 point;
	real factor;
	real z = l0.t.y;
	BOOST_CHECK( line_intersection( c0, l0, point, factor ) );
	BOOMST_CHECK_APPROX_EQUAL(real2(z,z),point);
	BOOMST_CHECK_APPROX_EQUAL(2-z,factor);
	
	BOOST_CHECK( line_intersection( c1, l1, point, factor ) );
	BOOMST_CHECK_APPROX_EQUAL(real2(1+z,-z),point);
	
}

BOOST_AUTO_TEST_SUITE_END()

} //namespace test
