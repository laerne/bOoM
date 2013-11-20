#include <bOoM/entities/world_boundary/WorldBoundary.hpp>
#include <bOoM/aabr.hpp>
#include <bOoM/color.hpp>
#include <bOoM/intersection.hpp>
#include <bOoM/TiledArray.hpp>

namespace bOoM {

WorldBoundary::WorldBoundary(move2 orientation)
	: orientation(orientation) {}

bool WorldBoundary::new__rendered_image(aabr const& screen_zone, size_t_2 screen_resolution, Image*& res__image, aabr& res__rendered_zone)
{
	aabr render_zone;
	if(!  aabr_smallest_subaabr_containing_line( screen_zone, orientation, res__rendered_zone )  )
	{
		if(  crossProduct_z( orientation.r, screen_zone.top_left()-orientation.t ) <= 0  )
		{
			//every pixel must be rendered
			res__rendered_zone = screen_zone;
			res__image = new Image(screen_resolution, tile_of40kbytes_for_data_of4bytes);
			//TODO This does not seems to be so advantageous to use a TiledArray, why not use a FlatArray ?
			for(size_t_2 p(0,0); p.y < screen_resolution.y; ++p.y)
			for(p.x = 0        ; p.x < screen_resolution.x;  ++p.x)
			{
				(*res__image)[p] = tone::white;
			}
		}
		else
			//res__image = nullptr;
			//res__rendered_zone = aabr(0,0,0,0);
			return false;
	}
	else
	{
		size_t_2 image_resolution;
		//TODO beware of rounding error when casting to size_t !  Use some kind of ceil.
		image_resolution.x = size_t( real(screen_resolution.x) *screen_zone.width()  /res__rendered_zone.width() );
		image_resolution.y = size_t( real(screen_resolution.y) *screen_zone.height() /res__rendered_zone.height() );
		res__image = new Image(image_resolution, tile_of40kbytes_for_data_of4bytes);
		for(size_t_2 p(0,0); p.y < image_resolution.y; ++p.y)
		for(p.x = 0        ; p.x < image_resolution.x; ++p.x)
		{
			real2 q; //center of pixel
			q.x = screen_zone.left + (real(p.x) + 0.5_r) /real(image_resolution.x) *screen_zone.width();
			q.y = screen_zone.bottom + (real(p.y) + 0.5_r) /real(image_resolution.y) *screen_zone.height();

			(*res__image)[p] = crossProduct_z( orientation.r, q-orientation.t ) <= 0 ? tone::white : tone::blue;
		}
	}

	return true;
};

bool WorldBoundary::del__rendered_image( Image*& image )
{
	delete image;
	//image = nullptr;
}


} //namespace bOoM

