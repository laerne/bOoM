#include <boost/test/unit_test.hpp>

#include <bOoM/BitsetAllocator.hpp>

namespace test {
using namespace bOoM;

struct Euler
	{ size_t v0, e1, s2, v3; };

BOOST_AUTO_TEST_SUITE( colors )

BOOST_AUTO_TEST_CASE( bitSetAllocator_basicAllocation )
{
	BitsetAllocator<Euler,4> allocator;
	Euler* a = allocator.allocate();
	Euler* b = allocator.allocate();
	Euler* c = allocator.allocate();
	Euler* d = allocator.allocate();
	Euler* e = allocator.allocate();
	BOOST_CHECK_EQUAL( (Euler*)nullptr, e );
	allocator.deallocate(d);
	allocator.deallocate(c);
	allocator.deallocate(b);
	allocator.deallocate(a);
	b = allocator.allocate();
	c = allocator.allocate();
	d = allocator.allocate();
	e = allocator.allocate();
}

BOOST_AUTO_TEST_SUITE_END()
	
} //namespace test


