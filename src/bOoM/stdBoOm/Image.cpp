#include "Image.hpp"
namespace stdBoOm {

uint32_t* Image::argb8888_buffer()
{
	return array;
}
uint32_t const* Image::argb8888_buffer() const
{
	return array;
}

} //namespace stdBoOm


