#include <iostream>
#define PRINT_EXPR(e) std::cout << #e << " : " << (e) << std::endl
#define PRINTLN() std::cout << std::endl

#include "basemath.hpp"
#include "math2d.hpp"
#include "dynamic.hpp"
#include "intersection.hpp"

//! print pairs
template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& s, std::pair<T1,T2> const pair)
	{ s <<"{" << std::get<0>(pair) <<"," << std::get<1>(pair) <<"}"; return s; }

//! unit test for math2d.hpp.
void test__math2d()
{
	std::cout << "test__math2d()" << std::endl;
	bOoM::V2<bOoM::real> zero(0,0);
	bOoM::V2<bOoM::real> p(1,3), q(2,-2);
	bOoM::V2<bOoM::real> undef;
	bOoM::V2<bOoM::real> def = p;

	PRINT_EXPR(zero);
	PRINT_EXPR(p);
	PRINT_EXPR(q);
	PRINT_EXPR(undef);
	PRINT_EXPR(def);
	PRINT_EXPR(p+q);
	PRINT_EXPR(p*2.0_r);
	PRINT_EXPR(p/(2_r));
	PRINT_EXPR((p|q));
	PRINT_EXPR((p+q-q|q+zero));
	PRINT_EXPR(p.norm1());
	PRINT_EXPR(p.norm2sq());
	PRINT_EXPR(q.norm_max());
	PRINTLN();

	bOoM::Rot2<bOoM::real> r1 = bOoM::rot2from(CST_PI/3);
	bOoM::Rot2<bOoM::real> r2 = bOoM::rot2from(CST_PI/6);
	bOoM::Rot2<bOoM::real> id = bOoM::rot2_id;
	PRINT_EXPR(r1);
	PRINT_EXPR(r2);
	PRINT_EXPR(id);
	PRINT_EXPR(r1*r2);
	PRINT_EXPR(r1.inv());
	PRINT_EXPR(r1.map(q));
	PRINTLN();

	bOoM::V2<bOoM::real> tt(1,0);
	bOoM::Move2<bOoM::real> t(r1,tt);
	bOoM::Move2<bOoM::real> up(id,tt);
	PRINT_EXPR(t);
	PRINT_EXPR(t.map(q));
	PRINT_EXPR(up.map(q));
	PRINT_EXPR(q >> up >> up);
	PRINT_EXPR(q >>= up);
	PRINT_EXPR(q);
	PRINTLN();
}

void test__math2d__approx_angle()
{
	std::cout << "test__math2d__approx_angle()" << std::endl;
	bOoM::real2 angle0(3,0);
	bOoM::real2 angle20( std::cos((20./180.)*CST_PI), std::sin((20./180.)*CST_PI) );
	bOoM::real2 angle30( std::sqrt(3), 1 );
	bOoM::real2 angle40( std::cos((40./180.)*CST_PI), std::sin((40./180.)*CST_PI) );
	bOoM::real2 angle45( 17, 17 );
	bOoM::real2 angle80( std::cos((80./180.)*CST_PI), std::sin((80./180.)*CST_PI) );
	bOoM::real2 angle120( std::cos((120./180.)*CST_PI), std::sin((120./180.)*CST_PI) );
	bOoM::real2 angle180( -8, 0 );
	bOoM::real2 angle234( 2*std::cos((234./180.)*CST_PI), 2*std::sin((234./180.)*CST_PI) );
	PRINT_EXPR(angle0);
	PRINT_EXPR(bOoM::approx_angle4(angle0));
	PRINT_EXPR(bOoM::approx_angle8(angle0));
	PRINT_EXPR(angle20);
	PRINT_EXPR(bOoM::approx_angle4(angle20));
	PRINT_EXPR(bOoM::approx_angle8(angle20));
	PRINT_EXPR(angle30);
	PRINT_EXPR(bOoM::approx_angle4(angle30));
	PRINT_EXPR(bOoM::approx_angle8(angle30));
	PRINT_EXPR(angle40);
	PRINT_EXPR(bOoM::approx_angle4(angle40));
	PRINT_EXPR(bOoM::approx_angle8(angle40));
	PRINT_EXPR(angle45);
	PRINT_EXPR(bOoM::approx_angle4(angle45));
	PRINT_EXPR(bOoM::approx_angle8(angle45));
	PRINT_EXPR(angle80);
	PRINT_EXPR(bOoM::approx_angle4(angle80));
	PRINT_EXPR(bOoM::approx_angle8(angle80));
	PRINT_EXPR(angle120);
	PRINT_EXPR(bOoM::approx_angle4(angle120));
	PRINT_EXPR(bOoM::approx_angle8(angle120));
	PRINT_EXPR(angle180);
	PRINT_EXPR(bOoM::approx_angle4(angle180));
	PRINT_EXPR(bOoM::approx_angle8(angle180));
	PRINT_EXPR(angle234);
	PRINT_EXPR(bOoM::approx_angle4(angle234));
	PRINT_EXPR(bOoM::approx_angle8(angle234));
	PRINTLN();
}

//! unit test for dynamic.hpp.
void test__dynamic()
{
	std::cout << "test__dynamic()" << std::endl;
	bOoM::real2 t1(2,0);
	bOoM::rot2 r1 = bOoM::rot2from(CST_PI/3);
	bOoM::move2 m1(r1,t1);
	bOoM::real2 t2(3,1);
	bOoM::rot2 r2 = bOoM::rot2from(CST_PI/6);
	bOoM::move2 m2(r2,t2);
	bOoM::PointDynamic point_dyn(bOoM::zero2, t1, bOoM::zero2);
	bOoM::OrientedDynamic dyn(bOoM::move2_id, m1, m2);

	PRINT_EXPR(point_dyn);
	point_dyn.step();                     PRINT_EXPR(point_dyn);
	point_dyn.step(); point_dyn.acc = t2; PRINT_EXPR(point_dyn);
	point_dyn.step();                     PRINT_EXPR(point_dyn);
	point_dyn.step();                     PRINT_EXPR(point_dyn);
	PRINT_EXPR(dyn);
	dyn.step(); PRINT_EXPR(dyn);
	dyn.step(); PRINT_EXPR(dyn);
	dyn.step(); PRINT_EXPR(dyn);
	dyn.step(); PRINT_EXPR(dyn);
	PRINT_EXPR(point_dyn);
	PRINTLN();
}

//! unit test for bOoM::eqn2 namespace
void test__eqn2()
{
	std::cout << "test__eqn2()" << std::endl;
	PRINT_EXPR(bOoM::eqn2_discriminant(1_r,0_r,-1_r));
	PRINT_EXPR(bOoM::eqn2_solve(1_r,0_r,-1_r));

	PRINT_EXPR(bOoM::eqn2_discriminant(1_r,0_r,1_r));
	PRINT_EXPR(bOoM::eqn2_solve(1_r,0_r,1_r));

	PRINT_EXPR(bOoM::eqn2_discriminant(1_r,-2_r,1_r));
	PRINT_EXPR(bOoM::eqn2_solve(1_r,-2_r,1_r));
	PRINTLN();
}

//! unit test for intersection.hpp.
void test__intersection()
{
	std::cout << "test__intersection()" << std::endl;
	bOoM::real2 p(1,-3), q(-2,1);
	bOoM::real2 v(-1,0), w(-1,4);
	PRINT_EXPR(std::make_pair(p,v));
	PRINT_EXPR(std::make_pair(q,w));
	PRINT_EXPR(bOoM::line_intersection_factors(p,v,q,w));
	PRINT_EXPR(bOoM::line_intersection(p,v,q,w));
	PRINT_EXPR(bOoM::pointed_vector_intersection(p,v,q,w));
	PRINT_EXPR(bOoM::pointed_vector_intersection(p,v*4_r,q,w));
	PRINT_EXPR(bOoM::pointed_vector_intersection(p,v,p,v));
	PRINTLN();

	bOoM::real2 p1(2,0), p2(0,2);
	bOoM::real2 v1(-1,0), v2(0,-1);
	bOoM::real r1= 1.0, r2= 1.0;
	PRINT_EXPR(std::make_pair(p1,p2));
	PRINT_EXPR(std::make_pair(v1,v2));
	PRINT_EXPR(std::make_pair(r1,r2));
	PRINT_EXPR(bOoM::line_intersection(p1,v1,p2,v2));
	PRINT_EXPR(bOoM::ball_intersection(p1,v1,r1,p2,v2,r2));
	PRINT_EXPR(bOoM::ball_intersection(p1,-v1,r1,p2,v2,r2));
	PRINT_EXPR(bOoM::ball_intersection(p1,v1,r1,p2,v2*2_r,r2));
	PRINTLN();
}

int main(void)
{
	test__math2d();
	test__math2d__approx_angle();
	test__dynamic();
	test__eqn2();
	test__intersection();
	return 0;
}

