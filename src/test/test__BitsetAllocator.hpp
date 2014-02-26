#ifndef HEADERBoOmTEST__BitsetAllocator
#define HEADERBoOmTEST__BitsetAllocator

#include <cppunit/TestCaller.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>

#include <bOoM/BitsetAllocator.hpp>

namespace test {

using namespace bOoM;

struct Euler
	{ size_t v0, e1, s2, v3; };

class Test__BitsetAllocator : public CppUnit::TestFixture
{
	BitsetAllocator<Euler,4> allocator;
public:
	void setUp()
	{
	}

	void tearDown()
	{
	}
  
	CPPUNIT_TEST_SUITE( Test__BitsetAllocator );
		CPPUNIT_TEST( testBasicAllocation );
	CPPUNIT_TEST_SUITE_END();

	void testBasicAllocation()
	{
		Euler* a = allocator.allocate();
		Euler* b = allocator.allocate();
		Euler* c = allocator.allocate();
		Euler* d = allocator.allocate();
		Euler* e = allocator.allocate();
		CPPUNIT_ASSERT_EQUAL( (Euler*)nullptr, e );
		allocator.deallocate(d);
		allocator.deallocate(c);
		allocator.deallocate(b);
		allocator.deallocate(a);
		//PRINT_EXPR(a);
		//PRINT_EXPR(b);
		//PRINT_EXPR(c);
		//PRINT_EXPR(d);
		//PRINT_EXPR(e);
		b = allocator.allocate();
		c = allocator.allocate();
		d = allocator.allocate();
		e = allocator.allocate();
		//PRINT_EXPR(a);
		//PRINT_EXPR(b);
		//PRINT_EXPR(c);
		//PRINT_EXPR(d);
		//PRINT_EXPR(e);
	}
	
};

} //namespace test
#endif


