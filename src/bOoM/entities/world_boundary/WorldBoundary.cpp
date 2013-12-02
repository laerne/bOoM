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
	//std::cout <<"aabr_intersection( screen_zone, orientation, res__rendered_zone ) = "
	//	<<aabr_intersection( screen_zone, orientation, res__rendered_zone ) <<std::endl;
	if(!  aabr_smallest_subaabr_containing_line( screen_zone, orientation, res__rendered_zone )  )
	{
		if(  crossProduct_z( orientation.r, screen_zone.top_left()-orientation.t ) <= 0  )
		{
			//every pixel must be rendered
			res__rendered_zone = screen_zone;
			res__image = new Image(screen_resolution);
			for(size_t_2 p(0,0); p.y < screen_resolution.y; ++p.y)
			for(p.x = 0        ; p.x < screen_resolution.x;  ++p.x)
			{
				(*res__image)[p] = color::white;
			}
		}
		else
			//res__image = nullptr;
			//res__rendered_zone = aabr(0,0,0,0);
			return false;
	}
	else
	{
		//we partially view the boundary
		//enlarge the line aabr to contain the `filled' part of the WorldBoundary
		if(orientation.r.x < 0)
		{
			if(orientation.r.y < 0)
			{
				res__rendered_zone.top = screen_zone.top;
				res__rendered_zone.left = screen_zone.left;
			}
			else //(orientation.r.y >= 0)
			{
				res__rendered_zone.top = screen_zone.top;
				res__rendered_zone.right = screen_zone.right;
			}
		}
		else //(orientation.r.x >= 0)
		{
			if(orientation.r.y < 0)
			{
				res__rendered_zone.bottom = screen_zone.bottom;
				res__rendered_zone.left = screen_zone.left;
			}
			else //(orientation.r.y >= 0)
			{
				res__rendered_zone.bottom = screen_zone.bottom;
				res__rendered_zone.right = screen_zone.right;
			}
		}
		rectangle<int> rendered_pixel_zone = to_screen_coordinates(screen_zone, screen_resolution, res__rendered_zone);
		size_t_2 image_resolution = rendered_pixel_zone.size();
		res__image = new Image(image_resolution);
		//std::cout <<"!!! " <<image_resolution <<", " <<rendered_pixel_zone <<std::endl;
		//std::cout <<"!!! " <<res__rendered_zone <<to_physical_coordinates(res__rendered_zone,image_resolution,real2(0,image_resolution.y-1)) <<std::endl;
		
		for(size_t_2 p(0,0); p.y < image_resolution.y; ++p.y)
		for(p.x = 0        ; p.x < image_resolution.x; ++p.x)
		{
			real2 q = to_physical_coordinates(res__rendered_zone, image_resolution, p);

			(*res__image)[p] = crossProduct_z( orientation.r, q-orientation.t ) <= 0 ? color::blue : color::black;
			
			//std::cout <<p <<" " <<q <<" " <<(*res__image)[p] <<std::endl;
			//std::cout <<"    " <<color::white <<color::blue <<std::endl;
		}
	}

	return true;
};

//bool WorldBoundary::del__rendered_image( Image*& image ) const
//{
//	delete image;
//	//image = nullptr;
//	return true;
//}


} //namespace bOoM

