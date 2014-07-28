#include <boost/test/unit_test.hpp>

#include <bOoM/TiledArray.hpp>

namespace test {
using namespace bOoM;

BOOST_AUTO_TEST_SUITE( tiledArray )

BOOST_AUTO_TEST_CASE( tiledArray__Index )
{
	size_t_2 asize = {9,7};
	size_t_2 tsize = {3,4};
	TiledArray<int> tarray_int( asize, tsize );
	
	size_t_2 m = {5,2};
	size_t i = 23;

	BOOST_CHECK_EQUAL(   m,   tarray_int.mindexOf(tarray_int.indexOf(m))   );
	BOOST_CHECK_EQUAL(   i,   tarray_int.indexOf(tarray_int.mindexOf(i))   );
}

BOOST_AUTO_TEST_CASE( tiledArray__Assign )
{
	size_t_2 asize = {6,6};
	size_t_2 tsize = {2,2};
	TiledArray<int> t = TiledArray<int>( asize, tsize );
}

BOOST_AUTO_TEST_SUITE_END()

} //namespace test

