#ifndef H_blob
#define H_blob

#include "math2d.hpp"
#include "dynamic.hpp"

namespace bOoM {

// TODO move to math2d.hpp
// field include textures. Just create a texture object overloading operator().
template<typename A, typename B>
struct Map
{
	virtual B operator()(A x) const = 0;
	// virtual ~Map(){}
};
 
typedef Map<real  const, real>   Map_real;
typedef Map<real2 const, real>   Field_real;
typedef Map<real  const, color> Map_color;
typedef Map<real2 const, color> Field_color;

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



//blob Zone (bz)
enum class ColorMode : unsigned char
{
	SPECIALIZED,
	PER_BLOB_FILL_VORONOI,
	PER_BLOB_FIELD_VORONOI,
	PER_BLOB_FILL_COLOR_MEAN,
	GLOBAL_FILL,
	GLOBAL_COLORED_PHYS_FIELD,
	GLOBAL_COLOR_FIELD,
	GLOBAL_TEXTURE
};

struct BlobZone
{
// Physical properties
// The shape of blob is assumed to be always a CIRCLE
	real2 cm; // center of mass
	OrientedDynamic mv; // position of the zone

// Color properties
	ColorMode color_mode;
	union {
		Color filled_color;
		Map_real *phys_field_recoloration;
		Texture *texture
	};
	HierarchicalBoundingCircleTree stain_texture;
	HierarchicalBoundingCircleTree lczs;
}





//Blobs

struct CircleBlob
{
	Dynamic dyn;
	Map_real f_phys;
};

struct CircleBlob_ColoredFill : public CircBlob
{
	color col;
};

struct CircleBlob_ColoredField : public CircBlob
{
	Field_color f_col;
};

} //namespace bOoM
#endif

