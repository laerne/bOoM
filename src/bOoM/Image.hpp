#ifndef H_Image
#define H_Image

#include "TiledArray.hpp"
#include "FlatArray.hpp"

namespace bOoM {

class Image : public FlatArray<color>
{
public:
	using FlatArray<color>::FlatArray;  //inherit the constructors
	uint32_t* rgba8888_buffer()
		{ return (uint32_t*) array; }
	uint32_t const* argb8888_buffer() const
		{ return (uint32_t*) array; }
	static int depth()
		{ return 8*sizeof(uint32_t); }
	static uint32_t redMask()
		{ return 0x000000FF; }
	static uint32_t greenMask()
		{ return 0x0000FF00; }
	static uint32_t blueMask()
		{ return 0x00FF0000; }
	static uint32_t alphaMask()
		{ return 0xFF000000; }
	size_t pitch()
		{ return width() * sizeof(uint32_t); }
};

} //namespace bOoM
#endif


