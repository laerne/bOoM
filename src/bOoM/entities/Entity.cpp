#include "Entity.hpp"
namespace bOoM {
//dummy functions so that the compiler generates a vtable.
bool Entity::new__rendered_image(aabr const& screen_zone, size_t_2 screen_resolution, Image*& res__image, aabr& res__rendered_zone) const
	{ return false; }
bool Entity::del__rendered_image(Image*& to_be_deleted) const
	{ delete to_be_deleted; to_be_deleted = nullptr; return true; }

} //namespace bOoM


