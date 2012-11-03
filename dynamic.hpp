#ifndef H_dynamic
#define H_dynamic
#include "math2d.hpp"
// used for printing elements
#include <iostream> 

namespace bOoM {
struct PointDynamic
{
    PointDynamic(real2 const& position
            , real2 const& velocity, real2 const& acceleration)
        : pos(position), vel(velocity), acc(acceleration) {}
    void step() { pos+= vel; vel+= acc; }

    real2 pos; //position
    real2 vel; //velocity in distance-per-steps
    real2 acc; //acceleration in distance-per-steps^2
};

std::ostream& operator<<(std::ostream& s, PointDynamic const& dyn)
    { s <<"(pos:" <<dyn.pos <<",vel:" <<dyn.vel <<",acc:" <<dyn.acc <<")";}

struct OrientedDynamic
{
    OrientedDynamic(move2 const& position
            , move2 const& velocity, move2 const& acceleration)
        : pos(position), vel(velocity) , acc(acceleration) {}
//    OrientedDynamic (real2 const& position
//            , real2 const& velocity, real2 const& acceleration)
//        : pos(rot2_id, position), vel(rot2_id, velocity)
//        , acc(rot2_id, acceleration) {}
    PointDynamic asPointDynamic() const
        { return PointDynamic(pos.t,vel.t,acc.t); }
    void step() 
        { pos.t+=vel.t; pos.r*=vel.r; vel.t+=acc.t; vel.r*=acc.r; }

    move2 pos; //position and angle
    move2 vel; //velocity and angular velocity
    move2 acc; //acceleration and angular acceleration
};
std::ostream& operator<<(std::ostream& s, OrientedDynamic const& dyn)
    { s <<"(pos:" <<dyn.pos <<",vel:" <<dyn.vel <<",acc:" <<dyn.acc <<")";}

} //namespace bOoM
#endif

