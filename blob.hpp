#ifndef H_blob
#define H_blob

#include "math2d.hpp"
#include "dynamic.hpp"

namespace bOoM {

// field include textures. Just create a texture object overloading operator().
template<typename A, typename B>
struct Map
{
	virtual B operator()(A x) const = 0;
	// virtual ~Map(){}
};
 
typedef Map<real  const, real>   Map_real;
typedef Map<real2 const, real>   Field_real;
typedef Map<real  const, colorA> Map_colorA;
typedef Map<real2 const, colorA> Field_colorA;

//template<typename A, typename B, typename C>
//struct CompositionMap : public Map<A,C>
//{
//	CompositionMap( Map<B,C> g, Map<A,B> f ) : f(f), g(g) {}
//    virtual real operator()(real x) const override
//		{ return g(f(x)); }
//	Map<A,B> f;
//	Map<B,C> g;
//}


struct CubicHillField : public Map_real
{
	CubicHillField(real inner_radius, real outer_radius)
		: support(outer_radius)
	{
		den= 2*CUBE(inner_radius) 
		    -3*SQ(inner_radius)*outer_radius +CUBE(outer_radius);
		c0= outer_radius3 / den;
		c2= -3*inner_radius / den;
		c3= 2.0/den;
	}
	//When needed : virtual ~CubicHillField()

	virtual real operator()(real x) const override
	{
		if(x >= support) return 0.0;
		x2 = SQ(x);
		return c0 +c2*x2 +c3*x2*x;
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

	virtual real operator(real x) const override
	{
		if(x <= inner_radius) return 1.0;
		else if (x >= outer_radius) return 0.0;
		x-= inner_radius;
		x2 = SQ(x);
		return c3*x*x2 + c2*x2 +1.0;
	}
	real inner_radius, real outer_radius;
	real c3, c2;
};






//Blobs

struct CircBlob
{
	PointDynamic dyn;
	real_field1 f_phys;
};
struct CircBlob_ColPlain : public CircBlob
{
	colorA col;
};
 struct CircBlob_ColHeight : public CircBlob
{
	Map_colorA f_col_in;
};
struct CircBlob_ColField : public CircBlob
{
	Map_colorA f_col_in;
	Map_colorA f_col_out;
};
struct OrientedBlob
{
	dyn;
	f_phys;
};

struct OrientedBlob_ColField : public OrientedBlob
{
	f_col_in;
	f_col_out;
};


struct BlobZone
{
// The shape of blob is assumed to be always a CIRCLE
	blendingMode col_blend; // norm 2 Voronoi, mean of colors weighted by distances, ...
	real_field2 shared_f_col_in; // =NULL when not using shared field function
	real_field2 shared_f_col_out; // =NULL when not using shared field function

	real2 cm; // center of mass
	OrientedDynamic mv; // position of the zone
}

} //namespace bOoM
#endif
