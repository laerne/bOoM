#ifndef HEADERBoOmTEST__TiledArray
#define HEADERBoOmTEST__TiledArray

#include <cppunit/TestCaller.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>

#include <bOoM/TiledArray.hpp>

namespace test {

using namespace bOoM;
class Test__TiledArray : public CppUnit::TestFixture
{
	TiledArray<int>* tarray_int;
public:
	void setUp()
	{
		size_t_2 asize = {9,7};
		size_t_2 tsize = {3,4};
		tarray_int = new TiledArray<int>( asize, tsize );
	}

	void tearDown()
	{
		delete tarray_int;
	}
  
	CPPUNIT_TEST_SUITE( Test__TiledArray );
		CPPUNIT_TEST( testIndex );
		CPPUNIT_TEST( testAssign );
	CPPUNIT_TEST_SUITE_END();

	void testIndex()
	{
		size_t_2 m = {5,2};
		size_t i = 23;

		CPPUNIT_ASSERT_EQUAL(   m,   tarray_int->mindexOf(tarray_int->indexOf(m))   );
		CPPUNIT_ASSERT_EQUAL(   i,   tarray_int->indexOf(tarray_int->mindexOf(i))   );
	}
	
	void testAssign()
	{
		size_t_2 asize = {6,6};
		size_t_2 tsize = {2,2};
		TiledArray<int> t = TiledArray<int>( asize, tsize );
	}
};

} //namespace test
#endif


