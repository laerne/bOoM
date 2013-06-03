#include "test__math2d.hpp"

int main(int argc, char* argv[])
{
	using namespace test;
	CppUnit::TextUi::TestRunner runner;
	runner.addTest( Test__math2d::suite() );
	return runner.run() ? EXIT_SUCCESS : EXIT_FAILURE;
}
