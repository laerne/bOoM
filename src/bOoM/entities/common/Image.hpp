#ifndef H_Image
#define H_Image

#include <bOoM/TiledArray.hpp>
#include <bOoM/FlatArray.hpp>

namespace bOoM {
namespace graphic {


class Image : public FlatArray<color>
{
public:
	using FlatArray<color>::FlatArray;  //inherit the constructors
	uint32_t* rgba8888_buffer()
		{ return (uint32_t*) array; }
	uint32_t const* argb8888_buffer() const
		{ return (uint32_t*) array; }
};

inline constexpr uint32_t redMask()
	{ return 0x000000FF; }
inline constexpr uint32_t greenMask()
	{ return 0x0000FF00; }
inline constexpr uint32_t blueMask()
	{ return 0x00FF0000; }
inline constexpr uint32_t alphaMask()
	{ return 0xFF000000; }
	
inline constexpr int byte_depth()
	{ return sizeof(uint32_t); }
inline constexpr int bit_depth()
	{ return 8*byte_depth(); }
inline int pitch( Image const& img )
	{ return img.width() * byte_depth(); }

} //namespace graphic
} //namespace bOoM
#endif

