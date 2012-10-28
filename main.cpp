// START main.cpp
#include <iostream>
#define TOSTRING(s) #s
#define PRINT_EXPR(e) std::cout << TOSTRING(e) << " : " << (e) << std::endl
#define PRINTLN() std::cout << std::endl;

//TODO replace <<= by something more usable.

#include "math2d.hpp"
void test__math2d()
{
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
    bOoM::Rot2<real> r1 = bOoM::toRot2from(PI/3);
    bOoM::Rot2<real> r2 = bOoM::toRot2from(PI/6);
    bOoM::Rot2<real> id = bOoM::toRot2identity();
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
}

int main()
{
    test__math2d();
    return 0;
}

// END main.cpp

