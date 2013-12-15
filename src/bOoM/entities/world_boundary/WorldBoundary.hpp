#ifndef H_WorldBoundary
#define H_WorldBoundary

#include<bOoM/math2d.hpp>

#include "../Entity.hpp"

namespace bOoM {

/*! \brief A half plane entity used to fill the level boundaries like a roof, a floor or an ocean.
 * 
 * We assume the identity-oriented WorldBoundary is the half-plane whose area is on the area below of the x-axis.
 */
struct WorldBoundary : public Entity
{
	explicit WorldBoundary(move2 orientation);
	
	move2 orientation;

	virtual bool new__rendered_image(aabr const& screen_zone, size_t_2 screen_resolution, graphic::Image*& res__image, aabr& res__rendered_zone) const;
	//virtual bool del__rendered_image(graphic::Image*& to_be_deleted) const;
};


} //namespace bOoM
#endif

