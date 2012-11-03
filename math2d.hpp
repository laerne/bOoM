#ifndef H_math2d
#define H_math2d

// used for printing elements
#include <iostream> 
// used by rot2from(real)
#include "basemath.hpp"

namespace bOoM {
// Work in a mathematical ring <R>
// So actually our vectors are member of a _module_.

/* 2d Vector */
template<typename R>
struct V2
{
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
//struct ScaleRot2 is a matrix of form
// / a -b \
// \ b  a /
// without a*a + b*b = 1
//
// real scaleFactor() const { return SQ(cos) + SQ(sin); }
//
template<typename R>
struct Rot2
{
    Rot2(){} //default constructor
    Rot2(R cos_, R sin_) : cos(cos_), sin(sin_) {}
    Rot2<R>& operator=(Rot2<R> r) { cos=r.cos; sin=r.sin; return *this;}
    Rot2<R>& operator*=(Rot2<R> r)
        { const R cos_= cos;
          cos= cos*r.cos -sin*r.sin;
          sin= sin*r.cos +cos*r.sin;
          return *this; }
    bool operator==(Rot2<R> const& r) const { return cos==r.cos && sin==r.sin; }
    bool operator!=(Rot2<R> const& r) const { return cos!=r.cos || sin!=r.sin; }
    V2<R> map(V2<R> const& p) const
        { return V2<R>(  p.x*cos-p.y*sin,  p.x*sin+p.y*cos  ); }
    Rot2<R> inv() const {return Rot2<R>(cos, -sin); }

    R cos; R sin;
};

template<typename R>
Rot2<R> operator*(Rot2<R> copy, Rot2<R> const& r)
    { return copy*=r; }
template<typename R>
std::ostream& operator<<(std::ostream& s, Rot2<R> const& r)
    { s <<"(cos:" << r.cos <<",sin:" << r.sin <<")";}
Rot2<real> rot2from(real angle)
    { return Rot2<real>(std::cos(angle), std::sin(angle)); }


/* 2d Moves (Orientation-preserving isometries) */
template<typename R>
struct Move2
{
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



// Common data types
//typedef v2<std::size_t> size_t_2;
typedef V2<real> real2;
typedef Rot2<real> rot2;
typedef Move2<real> move2;
// Usefull constants
real2 const zero2(0,0);
rot2 const rot2_id(1.f,0.f);
move2 const move2_id(rot2_id, zero2);




} //namespace bOoM
#endif

