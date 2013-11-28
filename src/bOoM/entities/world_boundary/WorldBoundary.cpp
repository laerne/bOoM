#include <bOoM/entities/world_boundary/WorldBoundary.hpp>
#include <bOoM/aabr.hpp>
#include <bOoM/color.hpp>
#include <bOoM/intersection.hpp>
#include <bOoM/TiledArray.hpp>
#include <iostream>

namespace bOoM {

WorldBoundary::WorldBoundary(move2 orientation)
	: orientation(orientation) {}

bool WorldBoundary::new__rendered_image(aabr const& screen_zone, size_t_2 screen_resolution, Image*& res__image, aabr& res__rendered_zone) const
{
	//std::cout <<"screen_zone = " <<screen_zone <<std::endl;
	//std::cout <<"screen_resolution = " <<screen_resolution <<std::endl;
	//std::cout <<"orientation = " <<orientation <<std::endl;
	//std::cout <<"aabr_smallest_subaabr_containing_line( screen_zone, orientation, res__rendered_zone ) = "
	//	<<aabr_smallest_subaabr_containing_line( screen_zone, orientation, res__rendered_zone ) <<std::endl;
	//if(!  aabr_smallest_subaabr_containing_line( screen_zone, orientation, res__rendered_zone )  )
	//{
	//	if(  crossProduct_z( orientation.r, screen_zone.top_left()-orientation.t ) <= 0  )
	//	{
	//		//every pixel must be rendered
	//		res__rendered_zone = screen_zone;
	//		res__image = new Image(screen_resolution);
	//		for(size_t_2 p(0,0); p.y < screen_resolution.y; ++p.y)
	//		for(p.x = 0        ; p.x < screen_resolution.x;  ++p.x)
	//		{
	//			(*res__image)[p] = color::white;
	//		}
	//	}
	//	else
	//		//res__image = nullptr;
	//		//res__rendered_zone = aabr(0,0,0,0);
	//		return false;
	//}
	//else
	//{
	  res__rendered_zone = screen_zone; //TODO use `aabr_smallest_subaabr_containing_line`
		size_t_2 image_resolution;
		//size_t_2 image_resolution = screen_resolution;
		//We must round up not to miss any colored pixel, so we're using ceil.
		image_resolution.x = size_t( std::ceil( real(screen_resolution.x) *screen_zone.width()  /res__rendered_zone.width()  ) );
		image_resolution.y = size_t( std::ceil( real(screen_resolution.y) *screen_zone.height() /res__rendered_zone.height() ) );
		res__image = new Image(image_resolution);
		for(size_t_2 p(0,0); p.y < image_resolution.y; ++p.y)
		for(p.x = 0        ; p.x < image_resolution.x; ++p.x)
		{
			real2 q; //center of pixel
			q.x = 0; q.y = 0;
			q.x = screen_zone.left + (real(p.x) + 0.5_r) /real(image_resolution.x) *screen_zone.width();
			q.y = screen_zone.bottom + (real(p.y) + 0.5_r) /real(image_resolution.y) *screen_zone.height();

			(*res__image)[p] = crossProduct_z( orientation.r, q-orientation.t ) > 0 ? color::white : color::transparent;
			
			//std::cout <<p <<" " <<q <<" " <<(*res__image)[p] <<std::endl;
			//std::cout <<"    " <<color::white <<color::blue <<std::endl;
		}
	//}

	return true;
};

//bool WorldBoundary::del__rendered_image( Image*& image ) const
//{
//	delete image;
//	//image = nullptr;
//	return true;
//}


} //namespace bOoM

