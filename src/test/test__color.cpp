#include <boost/test/unit_test.hpp>

#include <bOoM/color.hpp>
//#include <bOoM/colorf.hpp>

namespace test {
using namespace bOoM;

struct SomeColors
{
	color yellow, magenta, purple, rose, orange, brown;
	
public:
	SomeColors()
	: yellow  ( color::from_rgbaFFFF(1.f,1.f,0.f) )
	, magenta ( color::from_rgbaFFFF(1.f,0.f,1.f) )
	, purple  ( color::from_rgbaFFFF(0.4f,0.f,0.8f) )
	, rose    ( color::from_rgbaFFFF(0.8f,0.f,0.4f) )
	, orange  ( color::from_rgbaFFFF(1.f,0.4f,0.f) )
	, brown   ( color::from_rgbaFFFF(0.5f,0.2f,0.f) )
	{}
};

BOOST_AUTO_TEST_SUITE( colors )

BOOST_FIXTURE_TEST_CASE( colors__arithmetic, SomeColors )
{
	BOOST_CHECK_EQUAL( yellow, color::red + color::green );
	BOOST_CHECK_EQUAL( magenta, color::red + color::blue );
	BOOST_CHECK_EQUAL( purple, color::red*0.4 + color::blue*0.8 );
	BOOST_CHECK_EQUAL( brown, orange*0.5 );
}

BOOST_FIXTURE_TEST_CASE( colors__constructors, SomeColors )
{
	BOOST_CHECK_EQUAL( orange, color::from_rgba8888(orange.to_rgba8888() ) );
	BOOST_CHECK_EQUAL( 0xFFFF00FFu, yellow.to_rgba8888() );
	BOOST_CHECK_EQUAL( brown, color::from_rgba8888(0x7F3300FFu) );
	BOOST_CHECK_EQUAL( 0x3780F0FFu, color::from_rgba8888(0x3780F0FFu).to_rgba8888() );
}

BOOST_AUTO_TEST_SUITE_END()

} //namespace test


