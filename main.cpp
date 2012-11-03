#include <iostream>
#define TOSTRING(s) #s
#define PRINT_EXPR(e) std::cout << TOSTRING(e) << " : " << (e) << std::endl
#define PRINTLN() std::cout << std::endl;

//TODO replace <<= by something more usable.

#include "math2d.hpp"
#include "dynamic.hpp"

void test__math2d()
{
    std::cout << "test__math2d()" << std::endl;
    bOoM::V2<real> zero(0,0);
    bOoM::V2<real> p(1,3), q(2,-2);
    bOoM::V2<real> undef;
    bOoM::V2<real> def = p;

    PRINT_EXPR(zero);
    PRINT_EXPR(p);
    PRINT_EXPR(q);
    PRINT_EXPR(undef);
    PRINT_EXPR(def);
    PRINT_EXPR(p+q);
    PRINT_EXPR(p*2.f);
    PRINT_EXPR((p|q));
    PRINT_EXPR(p.norm1());
    PRINT_EXPR(p.norm2sq());
    PRINT_EXPR(q.norm_max());
    PRINTLN();

    #define PI 3.14159265
    bOoM::Rot2<real> r1 = bOoM::rot2from(PI/3);
    bOoM::Rot2<real> r2 = bOoM::rot2from(PI/6);
    bOoM::Rot2<real> id = bOoM::rot2_id;
    PRINT_EXPR(r1);
    PRINT_EXPR(r2);
    PRINT_EXPR(id);
    PRINT_EXPR(r1*r2);
    PRINT_EXPR(r1.inv());
    PRINT_EXPR(r1.map(q));
    PRINTLN();

    bOoM::V2<real> tt(1,0);
    bOoM::Move2<real> t(r1,tt);
    bOoM::Move2<real> up(id,tt);
    PRINT_EXPR(t);
    PRINT_EXPR(t.map(q));
    PRINT_EXPR(up.map(q));
    PRINT_EXPR(q >> up >> up);
    PRINT_EXPR(q >>= up);
    PRINT_EXPR(q);
    PRINTLN();
}

void test__dynamic()
{
    std::cout << "test__dynamic()" << std::endl;
    bOoM::real2 t1(2,0);
    bOoM::rot2 r1 = bOoM::rot2from(PI/3);
    bOoM::move2 m1(r1,t1);
    bOoM::real2 t2(3,1);
    bOoM::rot2 r2 = bOoM::rot2from(PI/6);
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

int main()
{
    //test__math2d();
    test__dynamic();
    return 0;
}

