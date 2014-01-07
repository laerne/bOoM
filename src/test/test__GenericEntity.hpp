#ifndef H_test__GenericEntity
#define H_test__GenericEntity

#include <cppunit/TestCaller.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>

#include <bOoM/GenericEntity.hpp>

namespace test {

using namespace bOoM;

// functions //////////////////////////////////////////////////////////////////
template<typename D> void f0(int) {}
template<typename D> long f1(int x) { return x*x; }
template<typename D> long f2(void) { return -1; }
template<typename D> void f3(int) {}
template<typename D> void f4(int,int) {}
template<typename D> void f5(float,int) {}
template<typename D> void f6(size_t) {}
template<typename D> void f7() {}
template<typename D> void f8(int,int,int,int) {}
template<typename D> void f9(std::tuple<> const&) {}
template<typename D> void f10(double) {}
template<typename D> void f11(double) {}
template<typename D> void f12(double) {}
template<typename D> void f13(double) {}
template<typename D> void f14(double) {}
template<typename D> void f15(double) {}
// component 0 ////////////////////////////////////////////////////////////////
template<typename D>
struct component0
	{ static std::tuple<decltype(f0<D>)*,decltype(f1<D>)*,decltype(f2<D>)*,decltype(f3<D>)*> const functions; };
template<typename D>
std::tuple<decltype(f0<D>)*,decltype(f1<D>)*,decltype(f2<D>)*,decltype(f3<D>)*> const component0<D>::functions= std::make_tuple( f0<D>, f1<D>, f2<D>, f3<D> );
// component 1 ////////////////////////////////////////////////////////////////
template<typename D>
struct component1
	{ static std::tuple<decltype(f4<D>)*,decltype(f5<D>)*,decltype(f6<D>)*,decltype(f7<D>)*> const functions; };
template<typename D>
std::tuple<decltype(f4<D>)*,decltype(f5<D>)*,decltype(f6<D>)*,decltype(f7<D>)*> const component1<D>::functions= std::make_tuple( f4<D>, f5<D>, f6<D>, f7<D> );
//component(component1,f4,f5,f6,f7);
// component 2 ////////////////////////////////////////////////////////////////
template<typename D>
struct component2
	{ static std::tuple<decltype(f8<D>)*,decltype(f9<D>)*,decltype(f10<D>)*,decltype(f11<D>)*> const functions; };
template<typename D>
std::tuple<decltype(f8<D>)*,decltype(f9<D>)*,decltype(f10<D>)*,decltype(f11<D>)*> const component2<D>::functions= std::make_tuple( f8<D>, f9<D>, f10<D>, f11<D> );
// component 3 ////////////////////////////////////////////////////////////////
template<typename D>
struct component3
	{ static std::tuple<decltype(f12<D>)*,decltype(f13<D>)*,decltype(f14<D>)*,decltype(f15<D>)*> const functions; };
template<typename D>
std::tuple<decltype(f12<D>)*,decltype(f13<D>)*,decltype(f14<D>)*,decltype(f15<D>)*> const component3<D>::functions= std::make_tuple( f12<D>, f13<D>, f14<D>, f15<D> );
// cppunit test class /////////////////////////////////////////////////////////
typedef GenericEntity<component0,component1,component2,component3> TestEntity;



class Test__GenericEntity : public CppUnit::TestFixture
{
public:
	CPPUNIT_TEST_SUITE( Test__GenericEntity );
		CPPUNIT_TEST( test_indexGetters );
	CPPUNIT_TEST_SUITE_END();

	void test_indexGetters()
	{
		int c0i = cmpnt_idx(TestEntity,component0);
		int c1i = cmpnt_idx(TestEntity,component1);
		int c2i = cmpnt_idx(TestEntity,component2);
		int c3i = cmpnt_idx(TestEntity,component3);
		CPPUNIT_ASSERT_EQUAL( 0, c0i );
		CPPUNIT_ASSERT_EQUAL( 1, c1i );
		CPPUNIT_ASSERT_EQUAL( 2, c2i );
		CPPUNIT_ASSERT_EQUAL( 3, c3i );
		
		int f5i = fct_idx(component1,f5);
		//CPPUNIT_ASSERT_EQUAL( 1, f5i );

		entity_full_fct_signatures<TestEntity>::tuple x;
		CPPUNIT_ASSERT_EQUAL( (x,1), 1 );
	}
};
///////////////////////////////////////////////////////////////////////////////

} //namespace test
#endif



