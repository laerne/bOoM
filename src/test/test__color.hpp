#ifndef H_test__color
#define H_test__color

#include <cppunit/TestCaller.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>

#include <bOoM/color.hpp>

#include <iostream>

namespace test {
using namespace bOoM;

class Test__color : public CppUnit::TestFixture
{
	color yellow, magenta, purple, rose, orange, brown;
	
public:
	void setUp()
	{
		yellow = color(1.f,1.f,0.f);
		magenta = color(1.f,0.f,1.f);
		purple = color(0.4f,0.f,0.8f);
		rose = color(0.8f,0.f,0.4f);
		orange = color(1.f,0.4f,0.f);
		brown = color(0.5f,0.2f,0.f);
	}
	void tearDown() {}

	CPPUNIT_TEST_SUITE( Test__color );
		CPPUNIT_TEST( test_arithmetic );
	CPPUNIT_TEST_SUITE_END();

	void test_arithmetic()
	{
		CPPUNIT_ASSERT_EQUAL( yellow, tone::red + tone::green );
		CPPUNIT_ASSERT_EQUAL( magenta, tone::red + tone::blue );
		CPPUNIT_ASSERT_EQUAL( purple, tone::red*0.4 + tone::blue*0.8 );
		CPPUNIT_ASSERT_EQUAL( brown, orange*0.5 );
	}
};

} //namespace test
#endif


