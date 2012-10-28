#ifndef H_math2d // START math2d.hpp
#define H_math2d

// for printing elements
#include <iostream> 
// for toRot2from
#include "basemath.hpp"

namespace bOoM
{
// Work in a mathematical ring <R>
// So actually our vectors are member of a _module_.

/* 2d Vector */
template<typename R>
class V2
{
public: //methods
    V2(){} //default constructor
    V2(R x_, R y_) : x(x_), y(y_) {}
    V2<R>& operator= (V2<R> const& q) { x = q.x; y= q.y; return *this; }
    V2<R>& operator+=(V2<R> const& q) { x += q.x; y+= q.y; return *this; }
    V2<R>& operator-=(V2<R> const& q) { x -= q.x; y-= q.y; return *this; }
    V2<R>& operator*=(R a) { x *= a; y*= a; return *this; }
    V2<R>  operator+ () const         { return V2( x, y); }
    V2<R>  operator- () const         { return V2(-x,-y); }
    R      operator| (V2<R> const& q) const ///< Dot product.
        { return x*q.x + y*q.y; }
    bool operator==(V2<R> const& q) const { return x==q.x && y==q.y; }
    bool operator!=(V2<R> const& q) const { return x!=q.x || y!=q.y; }
    R norm1()    const { return ABS(x)+ABS(y); }
    R norm2sq()  const { return SQ(x) + SQ(y); }
    R norm_max() const { return MAX(ABS(x),ABS(y)); }

public: //fields
    R x; R y;
};
template<typename R>
V2<R> operator+(V2<R> const& p, V2<R> const& q)
    { return V2<R>(p)+=q; }
template<typename R>
V2<R> operator-(V2<R> const& p, V2<R> const& q)
    { return V2<R>(p)-=q; }
template<typename R>
V2<R> operator*(V2<R> const& p, R a)
    { return V2<R>(p)*=a; }
template<typename R>
R dotProduct(V2<R> const& p, V2<R> const& q)
    { return p.x*q.x + p.y*q.y; }
template<typename R>
R crossProduct_z(V2<R> const& p, V2<R> const& q)
    { return p.x*q.y - p.y*q.x; }
template<typename R>
std::ostream& operator<<(std::ostream& s, V2<R> const& p)
    { s <<"(" << p.x <<"," << p.y <<")";}


/* 2d Rotations */
template<typename R>
class Rot2
{
public:
    Rot2(){} //default constructor
    Rot2<R>& operator=(Rot2<R> r) { cos=r.cos; sin=r.sin; return *this;}
    Rot2<R>& operator*=(Rot2<R> r)
        { const R cos_= cos;
          cos= cos*r.cos -sin*r.sin;
          sin= sin*r.cos_ +cos*r.sin;
          return *this; }
    Rot2<R> operator*(Rot2<R> const& r) const
        { return Rot2<R>(  cos*r.cos-sin*r.sin ,  sin*r.cos+cos*r.sin  ); }
    bool operator==(Rot2<R> const& r) const { return cos==r.cos && sin==r.sin; }
    bool operator!=(Rot2<R> const& r) const { return cos!=r.cos || sin!=r.sin; }
    V2<R> map(V2<R> const& p) const
        { return V2<R>(  p.x*cos-p.y*sin,  p.x*sin+p.y*cos  ); }
    Rot2<R> inv() const {return Rot2<R>(cos, -sin); }
protected:
    Rot2(R cos_, R sin_) : cos(cos_), sin(sin_) {}
    R cos; R sin;
//friends:
    friend Rot2<real> toRot2from(real angle);
    friend Rot2<real> toRot2identity();
    template<typename R0> friend 
        std::ostream& operator<<(std::ostream& s, Rot2<R0> const& r);
};
//class ScaleRot2 is a matrix of form
// / a -b \
// \ b  a /
// without a*a + b*b = 1

template<typename R>
std::ostream& operator<<(std::ostream& s, Rot2<R> const& r)
    { s <<"(cos:" << r.cos <<",sin:" << r.sin <<")";}
Rot2<real> toRot2from(real angle)
    { return Rot2<real>(std::cos(angle), std::sin(angle)); }
Rot2<real> toRot2identity()
    { return Rot2<real>(1.f, 0.f); }



/* 2d Moves (Orientation-preserving isometries) */
template<typename R>
class Move2
{
public: //methods
    Move2(){} //default constructor
    Move2(Rot2<R> const& rotation, V2<R> const& translation)
        : r(rotation), t(translation) {}
    Move2<R>& operator=(Move2<R> const& mv)   { r=mv.r; t=mv.t; return *this; }
    bool operator==(Move2<R> const& mv) const { return r==mv.r && t==mv.t; }
    bool operator!=(Move2<R> const& mv) const { return r!=mv.r || t!=mv.t; }
    V2<R> map(V2<R> const& p) const { return r.map(p) += t; }
    Move2<R>& precompose(Move2<R> const& mv)
        { t=map(mv.t);  r=r*mv.r; return *this; }
    Move2<R>  inv() const
        { const Rot2<R> r_inv=r.inv(); return Move2<R>(r_inv, r_inv.map(t)); }
public: //fields
    Rot2<R> r; V2<R> t;
};
template<typename R>
Move2<R> compose(Move2<R> const& m2, Move2<R> const& m1)
    { return Move2<R>(m2).precompose(m1); }
template<typename R>
std::ostream& operator<<(std::ostream& s, Move2<R> const& mv)
    { s <<"(r:" <<mv.r <<",t:" << mv.t <<")";}

//shortcuts
template<typename R>
V2<R> operator>>(V2<R> const& p, Move2<R> const& mv) { return mv.map(p); }
template<typename R>
V2<R>& operator>>=(V2<R>& p, Move2<R> const& mv) { return p = mv.map(p); }



} //namespace bOoM
#endif // END math2d.hpp

