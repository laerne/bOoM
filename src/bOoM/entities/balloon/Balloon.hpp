#ifndef H_Balloon
#define H_Balloon

#include "../Entity.hpp"
#include <bOoM/math2d.hpp>
#include <bOoM/circle.hpp>

namespace bOoM {

struct Balloon : public Entity
{
	explicit Balloon(real2 center, real radius)
		: disk(center,radius) {}
	explicit Balloon(circle disk)
		: disk(disk) {}
	
	circle disk;

	virtual bool new__rendered_image(aabr const& screen_zone, size_t_2 screen_resolution, graphic::Image*& res__image, aabr& res__rendered_zone) const;
	virtual bool del__rendered_image(graphic::Image*& to_be_deleted) const;
};

} //namespace bOoM
#endif


