#include "test__math2d.hpp"
#include "test__TiledArray.hpp"

int main(int argc, char* argv[])
{
	using namespace test;
	CppUnit::TextUi::TestRunner runner;
	runner.addTest( Test__math2d::suite() );
	runner.addTest( Test__TiledArray::suite() );
	return runner.run() ? EXIT_SUCCESS : EXIT_FAILURE;
}
