#ifndef H_data
#define H_data

namespace bOoM {

struct Balloon
{
	explicit Balloon(real2 center, real radius)
	        : disk(center,radius) {}
	explicit Balloon(circle disk)
	        : disk(disk) {}
	
	circle disk;
};

} //namespace bOoM

#endif


