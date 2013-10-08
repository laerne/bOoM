#include "Type.hpp"
namespace bOoM {
//Shameful ersatz of a yet-to-design plugin system

struct Type
{
	color (*color_field)(real2 position);
	bool (*phys_field)(real2 position);
};

} //namespace common

