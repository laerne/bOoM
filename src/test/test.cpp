#include "test__color.hpp"
#include "test__math2d.hpp"
#include "test__shapes.hpp"
#include "test__GenericEntity.hpp"
#include "test__BitsetAllocator.hpp"
#include "test__TiledArray.hpp"

int main(int argc, char* argv[])
{
	using namespace test;
	CppUnit::TextUi::TestRunner runner;
	runner.addTest( Test__math2d::suite() );
	runner.addTest( Test__shapes::suite() );
	runner.addTest( Test__color::suite() );
	runner.addTest( Test__GenericEntity::suite() );
	runner.addTest( Test__BitsetAllocator::suite() );
	//runner.addTest( Test__TiledArray::suite() );
	return runner.run() ? EXIT_SUCCESS : EXIT_FAILURE;
}
