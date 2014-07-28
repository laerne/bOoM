#include <boost/test/unit_test.hpp>
#include "test_macros.hpp"

#include <bOoM/math2d.hpp>


namespace test {
using namespace bOoM;

struct Some2dPoints
{
	real2 p0, p1, p2, p3, q0, q1, r0, r1, zero;
	
	Some2dPoints
	( real2 const& p0 = real2(3_r,2_r)
	, real2 const& p1 = real2(-2_r,1_r)
	, real2 const& p2 = real2(1_r,3_r)
	, real2 const& p3 = real2(2_r,-2_r)
	, real2 const& q0 = real2(3_r,0_r)
	, real2 const& q1 = real2(-0.5_r,-0.5_r)
	, real2 const& r0 = rot2_fromRadian(CST_PI/3)
	, real2 const& r1 = real2(0_r, -1_r)
	)                   
		: p0(p0), p1(p1), p2(p2), p3(p3), q0(q0), q1(q1), r0(r0), r1(r1), zero(bOoM::zero2)
	{}
};

BOOST_AUTO_TEST_SUITE( math2d )

BOOST_FIXTURE_TEST_CASE( math2d__unaryOperators, Some2dPoints )
{
	BOOMST_CHECK_APPROX_EQUAL( -p0, real2(-3_r,-2_r) );
	BOOMST_CHECK_APPROX_EQUAL( +p0, p0 );
}

BOOST_FIXTURE_TEST_CASE( math2d__addition, Some2dPoints )
{
	BOOMST_CHECK_APPROX_EQUAL( real2(6_r,2_r), p0+q0 );
	BOOMST_CHECK_APPROX_EQUAL( real2(-2.5_r,0.5_r), p1+q1  );
	BOOMST_CHECK_APPROX_EQUAL( real2(0_r,2_r), p0-q0 );
	BOOMST_CHECK_APPROX_EQUAL( q0+p0, p0+q0 );
}

BOOST_FIXTURE_TEST_CASE( math2d__multiplication, Some2dPoints )
{
	BOOMST_CHECK_APPROX_EQUAL( p0*2_r, real2(6_r,4_r) );
	BOOMST_CHECK_APPROX_EQUAL( p0*2_r*3_r, real2(18_r,12_r) );
	BOOMST_CHECK_APPROX_EQUAL( p0/2_r, real2(1.5_r,1_r) );
	BOOMST_CHECK_APPROX_EQUAL( p0/2_r*2_r, p0 );
}

BOOST_FIXTURE_TEST_CASE( math2d__dotProduct, Some2dPoints )
{
	BOOMST_CHECK_APPROX_EQUAL( -4_r, (p2|p3) );
	BOOMST_CHECK_APPROX_EQUAL( -16_r, (p2*2_r|p3*2_r) );
	BOOMST_CHECK_APPROX_EQUAL( -4_r, (p2+p3-p3|p3+zero2) );
	BOOMST_CHECK_APPROX_EQUAL( -4_r, (p2*2_r-p2|p3+zero2*3_r) );
}

BOOST_FIXTURE_TEST_CASE( math2d__crossProduct, Some2dPoints )
{
	BOOMST_CHECK_APPROX_EQUAL( -6_r, crossProduct_z(p0,q0) );
	BOOMST_CHECK_APPROX_EQUAL( 0_r, crossProduct_z(p1,zero2) );
}

BOOST_FIXTURE_TEST_CASE( math2d__orthogonal, Some2dPoints )
{
	BOOMST_CHECK_APPROX_EQUAL( real2(-2_r,-2_r), rightOrthogonal(p3) );
	BOOMST_CHECK_APPROX_EQUAL( real2(2_r,2_r), leftOrthogonal(p3) );
	BOOMST_CHECK_APPROX_EQUAL( real2(0_r,3_r), leftOrthogonal(q0) );
}

BOOST_FIXTURE_TEST_CASE( math2d__norms, Some2dPoints )
{
	BOOMST_CHECK_APPROX_EQUAL( 4_r, norm1(p2) );
	BOOMST_CHECK_APPROX_EQUAL( 10_r, norm2sq(p2) );
	BOOMST_CHECK_APPROX_EQUAL( 2_r, norm_max(p3) );
	BOOMST_CHECK_APPROX_EQUAL( 0_r, norm_max(zero2) );
}

BOOST_FIXTURE_TEST_CASE( math2d__rotations, Some2dPoints )
{
	BOOMST_CHECK_APPROX_EQUAL( -r1, rot2_inverse(r1) );
	BOOMST_CHECK_APPROX_EQUAL( rot2_mult(r1,r1), rot2_mult( rot2_mult(r0,r0), r0 ) );
	BOOMST_CHECK_APPROX_EQUAL( rightOrthogonal(p0), rot2_map(r1,p0) );
	BOOMST_CHECK_APPROX_EQUAL( zero2, rot2_map(r0,zero2) );
	BOOMST_CHECK_APPROX_EQUAL( p0, rot2_map(rot2_id,p0) );
}

BOOST_FIXTURE_TEST_CASE( math2d__transformations, Some2dPoints )
{
	move2 m0(r0,p0);
	move2 m1(r1,p1);
	BOOMST_CHECK_APPROX_EQUAL( p2 + p1, leftOrthogonal(p2) >> m1 );
	BOOMST_CHECK_APPROX_EQUAL( m0, inverse(inverse(m0)) );
	BOOMST_CHECK_APPROX_EQUAL( move2_id, compose(inverse(m0),m0) );
	BOOMST_CHECK_APPROX_EQUAL( p1, p1 >> m0 >> inverse(m0) );
	BOOMST_CHECK_APPROX_EQUAL( p0, zero2 >> m0 );
	BOOMST_CHECK_APPROX_EQUAL( p3, move2_id.map(p3) );
}

BOOST_AUTO_TEST_SUITE_END()

} //namespace test
