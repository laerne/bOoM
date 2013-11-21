#ifndef H_test__color
#define H_test__color

#include <cppunit/TestCaller.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>

#include <bOoM/color.hpp>
//#include <bOoM/colorf.hpp>

#include <iostream>

namespace test {
using namespace bOoM;

class Test__color : public CppUnit::TestFixture
{
	color yellow, magenta, purple, rose, orange, brown;
	
public:
	void setUp()
	{
		yellow =  color::from_rgbaFFFF(1.f,1.f,0.f);
		magenta = color::from_rgbaFFFF(1.f,0.f,1.f);
		purple =  color::from_rgbaFFFF(0.4f,0.f,0.8f);
		rose =    color::from_rgbaFFFF(0.8f,0.f,0.4f);
		orange =  color::from_rgbaFFFF(1.f,0.4f,0.f);
		brown =   color::from_rgbaFFFF(0.5f,0.2f,0.f);
	}
	void tearDown() {}

	CPPUNIT_TEST_SUITE( Test__color );
		CPPUNIT_TEST( test_arithmetic );
		CPPUNIT_TEST( test_constructors );
	CPPUNIT_TEST_SUITE_END();

	void test_arithmetic()
	{
		CPPUNIT_ASSERT_EQUAL( yellow, color::red + color::green );
		CPPUNIT_ASSERT_EQUAL( magenta, color::red + color::blue );
		CPPUNIT_ASSERT_EQUAL( purple, color::red*0.4 + color::blue*0.8 );
		CPPUNIT_ASSERT_EQUAL( brown, orange*0.5 );
	}
	
	void test_constructors()
	{
		CPPUNIT_ASSERT_EQUAL( orange, color::from_rgba8888(orange.to_rgba8888() ) );
		CPPUNIT_ASSERT_EQUAL( 0xFFFF00FFu, yellow.to_rgba8888() );
		CPPUNIT_ASSERT_EQUAL( brown, color::from_rgba8888(0x7F3300FFu) );
		CPPUNIT_ASSERT_EQUAL( 0x3780F0FFu, color::from_rgba8888(0x3780F0FFu).to_rgba8888() );
	}
};

} //namespace test
#endif


