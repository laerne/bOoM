#include <bOoM/color.hpp>
namespace bOoM {

color const color::red         = color( COLORCHANNEL_RANGE_MAX, COLORCHANNEL_RANGE_MIN, COLORCHANNEL_RANGE_MIN );
color const color::green       = color( COLORCHANNEL_RANGE_MIN, COLORCHANNEL_RANGE_MAX, COLORCHANNEL_RANGE_MIN );
color const color::blue        = color( COLORCHANNEL_RANGE_MIN, COLORCHANNEL_RANGE_MIN, COLORCHANNEL_RANGE_MAX );
color const color::white       = color( COLORCHANNEL_RANGE_MAX, COLORCHANNEL_RANGE_MAX, COLORCHANNEL_RANGE_MAX );
color const color::black       = color( COLORCHANNEL_RANGE_MIN, COLORCHANNEL_RANGE_MIN, COLORCHANNEL_RANGE_MIN );
color const color::transparent = color( COLORCHANNEL_RANGE_MIN, COLORCHANNEL_RANGE_MIN, COLORCHANNEL_RANGE_MIN, COLORCHANNEL_RANGE_MIN );

} //namespace bOoM

