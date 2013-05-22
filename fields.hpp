#ifndef H_fields
#define H_fields

#include "basemath.hpp"
namespace bOoM {

struct CubicHillField : public Map_real
{
	CubicHillField(real inner_radius, real outer_radius)
		: support(outer_radius)
	{
		den= 2*CUBE(inner_radius) 
		    -3*SQ(inner_radius)*outer_radius +CUBE(outer_radius);
		c0= outer_radius3 / den;
		c2= -3*outer_radius / den;
		c3= 2.0/den;
	}
	//When needed : virtual ~CubicHillField()

  //! \brief Evaluate the function at point x
	virtual real eval(real x) const
	{
		if(x >= support) return 0.0;
		return c3*CUBE(x) +c2*SQ(x) +c0;
	}

  //! \brief Evaluate the derivative of the function at point x
	virtual real derivative(real x) const
	{
		if(x >= support) return 0.0;
		return 3*c3*SQ(x) +2*c2*x;
	}

	real c0; real c2; real c3;
	real support;
};

struct CubicPlateField : public Map_real
{
	CubicPlateField(real inner_radius, real outer_radius)
		inner_radius(inner_radius), outer_radius(outer_radius)
	{
		real radius_diff = outer_radius - inner_radius;
		real radius_diff2 = SQ(radius_diff);
		real radius_diff3 = radius_diff * radius_diff2;
		c3 = 2.0/radius_diff3
		c2 = -3.0/radius_diff2
	}
	//When needed : virtual ~CubicPlateField()

  //! \brief Evaluate the function at point x
	virtual real eval(real x) const
	{
		if(x <= inner_radius) return 1.0;
		else if (x >= outer_radius) return 0.0;
		x-= inner_radius;
		return c3*CUBE(X) +c2*SQ(x) +1.0;
	}

  //! \brief Evaluate the derivative of the function at point x
	virtual real derivative(real x) const
	{
		if(x <= inner_radius || x >= outer_radius) return 0.0;
		x-= inner_radius;
		x2 = SQ(x);
		return 3*c3*SQ(X) +2*c2*x;
	}

	real inner_radius, real outer_radius;
	real c3, c2;
};


} //namespace bOoM
#endif

