#ifndef H_test__math2d
#define H_test__math2d

#include <cppunit/TestCaller.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>

#include <bOoM/stdBoOm/math2d.hpp>

#include <cstdlib>

namespace test {
using namespace bOoM;

class Test__math2d : public CppUnit::TestFixture
{
	real2 p0, p1, p2, p3, q0, q1, zero;
public:
	void setUp()
	{
		p0 = real2(3_r,2_r);
		p1 = real2(-2_r,1_r);
		p2 = real2(1_r,3_r);
		p3 = real2(2_r,-2_r);
		q0 = real2(3_r,0_r);
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
	CPPUNIT_TEST_SUITE_END();

	void testUnaryOperators()
	{
		CPPUNIT_ASSERT_EQUAL( -p0, real2(-3_r,-2_r) );
		CPPUNIT_ASSERT_EQUAL( +p0, p0 );
	}

	void testAddition()
	{
		CPPUNIT_ASSERT_EQUAL( real2(6_r,2_r), p0+q0 );
		CPPUNIT_ASSERT_EQUAL( real2(-2.5_r,0.5_r), p1+q1  );
		CPPUNIT_ASSERT_EQUAL( real2(0_r,2_r), p0-q0 );
		CPPUNIT_ASSERT_EQUAL( q0+p0, p0+q0 );
	}

	void testMultiplication()
	{
		CPPUNIT_ASSERT_EQUAL( p0*2_r, real2(6_r,4_r) );
		CPPUNIT_ASSERT_EQUAL( p0*2_r*3_r, real2(18_r,12_r) );
		CPPUNIT_ASSERT_EQUAL( p0/2_r, real2(1.5_r,1_r) );
		CPPUNIT_ASSERT_EQUAL( p0/2_r*2_r, p0 );
	}

	void testDotProduct()
	{
		CPPUNIT_ASSERT_EQUAL( -4_r, (p2|p3) );
		CPPUNIT_ASSERT_EQUAL( -16_r, (p2*2_r|p3*2_r) );
		CPPUNIT_ASSERT_EQUAL( -4_r, (p2+p3-p3|p3+zero2) );
		CPPUNIT_ASSERT_EQUAL( -4_r, (p2*2_r-p2|p3+zero2*3_r) );
	}

	void testCrossProduct()
	{
		CPPUNIT_ASSERT_EQUAL( -6_r, crossProduct_z(p0,q0) );
		CPPUNIT_ASSERT_EQUAL( 0_r, crossProduct_z(p1,zero2) );
	}

	void testOrthogonal()
	{
		CPPUNIT_ASSERT_EQUAL( real2(-2_r,-2_r), rightOrthogonal(p3) );
		CPPUNIT_ASSERT_EQUAL( real2(2_r,2_r), leftOrthogonal(p3) );
		CPPUNIT_ASSERT_EQUAL( real2(0_r,3_r), leftOrthogonal(q0) );
	}

	void testNorms()
	{
		CPPUNIT_ASSERT_EQUAL( 4_r, norm1(p2) );
		CPPUNIT_ASSERT_EQUAL( 10_r, norm2sq(p2) );
		CPPUNIT_ASSERT_EQUAL( 2_r, norm_max(p3) );
		CPPUNIT_ASSERT_EQUAL( 0_r, norm_max(zero2) );
	}
};

} //namespace test

#endif
