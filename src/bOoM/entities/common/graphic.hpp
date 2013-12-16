#ifndef H_solid_graphic
#define H_solid_graphic

#include <bOoM/Image.hpp>
#include <bOoM/math2d.hpp>
#include <bOoM/aabr.hpp>

namespace bOoM {
namespace graphic {

template<typename DATA>
struct Renderable
{
	/*! \brief 
	 * 
	 * \param screen_zone What space must be rendered in the video game coordinate system.
	 * \param screen_resolution The number of pixels, vertically and horizontally.
	 *    
	 * Note the returned image must be deleted with graphic::Renderable::graphic__del__rendered_image(graphic::Image*&)
	 * The pixel value of rendered image may not be precisely computed from the center of the pixel, but from some other point in
	 * the pixel square.
	 * This is to enable reusability of images, where only a shift smaller than half the size of a pixel may change a few pixel colors
	 */
	virtual Image* graphic__new__rendered_image(aabr const& screen_zone, size_t_2 screen_resolution, rect& result__rendered_zone, size_t& result__pitch, size_t& result__shift);
	/*! \brief deletes a rendered image.
	 * The image might not actually be deleted, but kept stored for later reutilisation, so do not assume that `image` is
	 * an invalid pointer after this call.
	 */
	virtual void   graphic__del__rendered_image(Image* image);
};


} //namespace graphic
} //namespace bOoM

#include "graphic.tpp"

#endif


