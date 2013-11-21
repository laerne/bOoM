#ifndef H_Image
#define H_Image

#include "TiledArray.hpp"
#include "FlatArray.hpp"

namespace bOoM {

class Image : public FlatArray<color>
{
public:
	using FlatArray<color>::FlatArray;  //inherit the constructors
	uint32_t* argb8888_buffer()
		{ return (uint32_t*) array; }
	uint32_t const* argb8888_buffer() const
		{ return (uint32_t*) array; }
	size_t byteWidth()
		{ return width() * sizeof(uint32_t); }
};

} //namespace bOoM
#endif


