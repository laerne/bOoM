#include <cppunit/TestCase.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

#include <bOoM/math2d.hpp>

namespace test {
using namespace bOoM;

class Test__math2d : public CppUnit::TestCase
{
public:
	void runTest()
	{
		real2 zero(0,0);
		real2 p(1,3), q(2,-2);
		CPPUNIT_ASSERT_EQUAL( p+q, real2(3,1));
		CPPUNIT_ASSERT_EQUAL( real2(2,6), p*2.0_r );
		CPPUNIT_ASSERT_EQUAL( real2(0.5,1.5), p/(2_r) );
		CPPUNIT_ASSERT_EQUAL( -4_r, (p|q) );
		CPPUNIT_ASSERT_EQUAL( -16_r, (p*2_r|q*2_r) );
		CPPUNIT_ASSERT_EQUAL( -4_r, (p+q-q|q+zero) );
		CPPUNIT_ASSERT_EQUAL( -4_r, (p*2_r-p|q+zero*3_r) );
		CPPUNIT_ASSERT_EQUAL( real2(-2,-2), rightOrthogonal(q) );
		CPPUNIT_ASSERT_EQUAL( real2(2,2), leftOrthogonal(q) );
		CPPUNIT_ASSERT_EQUAL( 4_r, norm1(p) );
		CPPUNIT_ASSERT_EQUAL( 10_r, norm2sq(p) );
		CPPUNIT_ASSERT_EQUAL( 2_r, norm_max(q) );
	}
};

} //namespace test

int main(int argc, char* argv[])
{
	CppUnit::TextUi::TestRunner runner;
	runner.addTest( new test::Test__math2d );
	return runner.run() ? 0 : 1;
}


