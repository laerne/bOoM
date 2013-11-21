#ifndef H_entity
#define H_entity

#include<bOoM/aabr.hpp>
#include<bOoM/color.hpp>
#include<bOoM/math2d.hpp>
#include<bOoM/Image.hpp>

namespace bOoM {

struct Entity
{
	/*! \brief Renders the entity.
	 * 
	 * \param screen_zone : What space must be rendered in the video game coordinate system.
	 * \param screen_resolution : The number of pixels, vertically and horizontally.
	 * \param res__image : The returned image.
	 * \param res__rendered_zone : The object may not create an image that fill the full given screen.
	 *    The actual rendered zone of the screen is stored in this variable.
	 *    The width and height of the rendered image in pixels can be obtained from res__image.
	 *    
	 * Note the returned image must be deleted with EntityType::del__rendered_image(Image*&)
	 */
	//TODO should return bool or a pointer to Image ?
	virtual bool new__rendered_image(aabr const& screen_zone, size_t_2 screen_resolution, Image*& res__image, aabr& res__rendered_zone) const;
	/*! \brief deletes a rendered image.
	 *
	 * This function is trivial in most useful cases, but it is important to allow the programmer of a rendering function
	 * to undo actions it might have done during the rendering.
	 */
	virtual bool del__rendered_image(Image*& to_be_deleted) const;
};

} //namespace bOoM
#endif


