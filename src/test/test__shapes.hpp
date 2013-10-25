#ifndef H_test__shapes
#define H_test__shapes

#include <cppunit/TestCaller.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>

#include <bOoM/intersection.hpp>

#include <iostream>

namespace test {
using namespace bOoM;

class Test__shapes : public CppUnit::TestFixture
{
	
	circle c0, c1, cm1, celse;
	move2 l0, l1;
public:
	void setUp() {
		c0 = circle(real2(0_r,0_r), 0.75_r);
		c1 = circle(real2(1_r,0_r), 0.75_r);
		cm1 = circle(real2(-1_r,0_r), 0.75_r);
		celse = circle(real2(0_r,2_r), 1.5_r);
		l0 = move2( real2(-1_r,0_r), real2(2_r,0.75_r/SQRT(2_r)) );
		l1 = move2( real2(-1_r,1_r), real2(3_r,-2_r) );
	}
	void tearDown() {}

	CPPUNIT_TEST_SUITE( Test__shapes );
		CPPUNIT_TEST( test_circle_circle );
		CPPUNIT_TEST( test_line_circle );
	CPPUNIT_TEST_SUITE_END();

	void test_circle_circle()
	{
		real2 centroid;
		real area;
		CPPUNIT_ASSERT( ! has_intersection(cm1,c1) );
		CPPUNIT_ASSERT( has_intersection(c0,c1) );
		intersection( c0, c1, centroid, area );
		CPPUNIT_ASSERT( equals_about( real2(0.5_r,0_r), centroid ) );
		intersection( c0, celse, centroid, area );
		CPPUNIT_ASSERT( equals_about( 0.324616_r, area ) );
	}
	
	void test_line_circle()
	{
		real2 point;
		real factor;
		real z = l0.t.y;
		CPPUNIT_ASSERT( line_intersection( c0, l0, point, factor ) );
		CPPUNIT_ASSERT( equals_about(real2(z,z),point) );
		CPPUNIT_ASSERT( equals_about(2-z,factor));
		
		CPPUNIT_ASSERT( line_intersection( c1, l1, point, factor ) );
		CPPUNIT_ASSERT( equals_about(real2(1+z,-z),point) );
		
	}
};

} //namespace test
#endif


