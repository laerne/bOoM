#include <boost/test/unit_test.hpp>

#include <bOoMengine/Simulator.hpp>
#include <iostream>
#include <sstream>

namespace test {
using namespace bOoM;

class DummyJob : public Job
{
	int id;
public:
	DummyJob( int id) : id(id) {}
	
	virtual void process()
	{
		std::ostringstream str_builder;
		str_builder << "Dummy job " << id << " is done by" << std::this_thread::get_id() << "." << std::endl;
		std::cout << str_builder.str();
	};
};

BOOST_AUTO_TEST_SUITE( simulator )

BOOST_AUTO_TEST_CASE( simulator_initialization )
{
		Worker_Pool pool(4);
		for( int i = 0; i < 25; ++i)
			pool.add_job( std::unique_ptr<Job>(new DummyJob(i)) );
		std::this_thread::sleep_for( std::chrono::seconds(3) );
}

BOOST_AUTO_TEST_SUITE_END()

} //namespace test


