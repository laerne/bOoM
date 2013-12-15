#ifndef H_solid_graphic
#define H_solid_graphic

#include <memory>
#include "Image.hpp"
#include <bOoM/math2d.hpp>
#include <bOoM/aabr.hpp>

namespace bOoM{
namespace graphic {

template<typename DATA>
struct Renderable
{
	Renderable() = default;
	/*! \brief Renders the entity.
	 * 
	 * \param screen_zone What space must be rendered in the video game coordinate system.
	 * \param screen_resolution The number of pixels, vertically and horizontally.
	 * \param res__image The returned image.
	 * \param res__rendered_zone The object may not create an image that fill the full given screen.
	 *    The actual rendered zone of the screen (in pixels) is stored in this variable.
	 *    
	 * Note the returned image must be deleted with Entity::del__rendered_image(graphic::Image*&)
	 */
	Image* new__rendered_image(aabr const& screen_zone, size_t_2 screen_resolution, rect& result__rendered_zone, size_t& result__pitch, size_t& result__shift) const;
	/*! \brief deletes a rendered image.
	 *
	 * This function might be trivial, but it is important to allow the programmer of a rendering function to undo actions
	 * it might have done during the rendering.
	 */
	void   del__rendered_image(Image* image);
};


//TODO move this in another file.
using std::unique_ptr;
struct SingleImageEntity
{
public:
	SingleImageEntity() = default;
	void set_image(unique_ptr<Image>& image_ptr)
		{ the_image = std::move(image_ptr); }
	void set_image(Image&& image_ref)
		{ the_image.reset(&image_ref); }
	Image& image()
		{ return *the_image; }
	Image const& image() const
		{ return *the_image; }
protected:
	unique_ptr<Image> the_image;
};


template<int N>
struct StaticCyclicImageEntity
{
public:
	StaticCyclicImageEntity() = default;
	void set_image(size_t index, unique_ptr<Image>& image_ptr)
		{ images[index] = image_ptr; }
	void set_image(size_t index, Image&& image_ref)
		{ images[index].reset(image_ref); }
	Image& image(size_t index)
		{ return *images[index]; }
	Image const& image(size_t index) const
		{ return *images[index]; }
protected:
	unique_ptr<Image> images[N];
};

} //namespace graphic
} //namespace bOoM

#endif


