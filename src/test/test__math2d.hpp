#ifndef HEADERBoOmTEST__math2d
#define HEADERBoOmTEST__math2d

#include <cppunit/TestCaller.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>

#include <bOoM/math2d.hpp>

#include <cstdlib>
#include <iostream>

namespace test {
using namespace bOoM;

class Test__math2d : public CppUnit::TestFixture
{
	real2 p0, p1, p2, p3, q0, q1, r0, r1, zero;
public:
	void setUp()
	{
		p0 = real2(3_r,2_r);
		p1 = real2(-2_r,1_r);
		p2 = real2(1_r,3_r);
		p3 = real2(2_r,-2_r);
		q0 = real2(3_r,0_r);
		r0 = rot2_fromRadian(CST_PI/3);
		r1 = real2(0_r, -1_r);
		q1 = real2(-0.5_r,-0.5_r);
	}
	void tearDown() {}

	CPPUNIT_TEST_SUITE( Test__math2d );
		CPPUNIT_TEST( testAddition );
		CPPUNIT_TEST( testMultiplication );
		CPPUNIT_TEST( testDotProduct );
		CPPUNIT_TEST( testCrossProduct );
		CPPUNIT_TEST( testOrthogonal );
		CPPUNIT_TEST( testNorms );
		CPPUNIT_TEST( testRotations );
		CPPUNIT_TEST( testTransformations );
	CPPUNIT_TEST_SUITE_END();

	void testUnaryOperators()
	{
		CPPUNIT_ASSERT( equals_about( -p0, real2(-3_r,-2_r) ) );
		CPPUNIT_ASSERT( equals_about( +p0, p0 ) );
	}

	void testAddition()
	{
		CPPUNIT_ASSERT( equals_about( real2(6_r,2_r), p0+q0 ) );
		CPPUNIT_ASSERT( equals_about( real2(-2.5_r,0.5_r), p1+q1  ) );
		CPPUNIT_ASSERT( equals_about( real2(0_r,2_r), p0-q0 ) );
		CPPUNIT_ASSERT( equals_about( q0+p0, p0+q0 ) );
	}

	void testMultiplication()
	{
		CPPUNIT_ASSERT( equals_about( p0*2_r, real2(6_r,4_r) ) );
		CPPUNIT_ASSERT( equals_about( p0*2_r*3_r, real2(18_r,12_r) ) );
		CPPUNIT_ASSERT( equals_about( p0/2_r, real2(1.5_r,1_r) ) );
		CPPUNIT_ASSERT( equals_about( p0/2_r*2_r, p0 ) );
	}

	void testDotProduct()
	{
		CPPUNIT_ASSERT( equals_about( -4_r, (p2|p3) ) );
		CPPUNIT_ASSERT( equals_about( -16_r, (p2*2_r|p3*2_r) ) );
		CPPUNIT_ASSERT( equals_about( -4_r, (p2+p3-p3|p3+zero2) ) );
		CPPUNIT_ASSERT( equals_about( -4_r, (p2*2_r-p2|p3+zero2*3_r) ) );
	}

	void testCrossProduct()
	{
		CPPUNIT_ASSERT( equals_about( -6_r, crossProduct_z(p0,q0) ) );
		CPPUNIT_ASSERT( equals_about( 0_r, crossProduct_z(p1,zero2) ) );
	}

	void testOrthogonal()
	{
		CPPUNIT_ASSERT( equals_about( real2(-2_r,-2_r), rightOrthogonal(p3) ) );
		CPPUNIT_ASSERT( equals_about( real2(2_r,2_r), leftOrthogonal(p3) ) );
		CPPUNIT_ASSERT( equals_about( real2(0_r,3_r), leftOrthogonal(q0) ) );
	}

	void testNorms()
	{
		CPPUNIT_ASSERT( equals_about( 4_r, norm1(p2) ) );
		CPPUNIT_ASSERT( equals_about( 10_r, norm2sq(p2) ) );
		CPPUNIT_ASSERT( equals_about( 2_r, norm_max(p3) ) );
		CPPUNIT_ASSERT( equals_about( 0_r, norm_max(zero2) ) );
	}

	void testRotations()
	{
		CPPUNIT_ASSERT( equals_about( -r1, rot2_inverse(r1) ) );
		CPPUNIT_ASSERT( equals_about( rot2_mult(r1,r1), rot2_mult( rot2_mult(r0,r0), r0 ) ) );
		CPPUNIT_ASSERT( equals_about( rightOrthogonal(p0), rot2_map(r1,p0) ) );
		CPPUNIT_ASSERT( equals_about( zero2, rot2_map(r0,zero2) ) );
		CPPUNIT_ASSERT( equals_about( p0, rot2_map(rot2_id,p0) ) );
	}
	
	void testTransformations()
	{
		move2 m0(r0,p0);
		move2 m1(r1,p1);
		CPPUNIT_ASSERT( equals_about( p2 + p1, leftOrthogonal(p2) >> m1 ) );
		CPPUNIT_ASSERT( equals_about( m0, inverse(inverse(m0)) ) );
		CPPUNIT_ASSERT( equals_about( move2_id, compose(inverse(m0),m0) ) );
		CPPUNIT_ASSERT( equals_about( p1, p1 >> m0 >> inverse(m0) ) );
		CPPUNIT_ASSERT( equals_about( p0, zero2 >> m0 ) );
		CPPUNIT_ASSERT( equals_about( p3, move2_id.map(p3) ) );
	}
};

} //namespace test

#endif
