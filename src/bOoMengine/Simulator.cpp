#include "Simulator.hpp"
#include <bOoM/base.hpp>
#include <iostream>
#include <mutex>
#include <cassert>

namespace bOoM {

using std::unique_ptr;

/*
 * Worker 
 */
Worker::Worker( Worker_Pool& pool )
	: proceed( true )
	, pool( pool )
	, thread( &Worker::work, this )
{}

Worker::Worker( Worker&& former )
	: proceed( former.proceed )
	, pool( former.pool )
	, thread( std::move( former.thread ) )
{
}

void Worker::operator=( Worker&& former )
{
	assert( &pool == &former.pool );

	if( !former.proceed )
		proceed = false;
	thread = std::move( former.thread );
}

void Worker::mark_termination()
{
	proceed = false;
	pool.jpool.monitor.notify_all();
}

bool Worker::marked_for_termination()
{
	return !proceed;
}

void Worker::join()
{
	thread.join();
}

void Worker::work()
{
	unique_ptr<Job> job;
	
	forever
	{
		scope
		{
			Job_Pool_Consumer_Guard guard( pool.jpool, *this );
			
			// Both the return and the assignment below should delete former job.
			if( !proceed )
				return;
			job = pool.jpool.pick();
		}
		
		job->process();
	}
}

/*
 * Job_Pool 
 */
bool Job_Pool::has_available_job() const
{
	return !jobs.empty();
}

unique_ptr<Job> Job_Pool::pick()
{
	unique_ptr<Job> front_elem( std::move( jobs.front() ) );
	jobs.pop();
	return std::move( front_elem );
}

void Job_Pool::add( unique_ptr<Job> job )
{
	jobs.push( std::move(job) );
}

void Job_Pool::awake_all()
{
	monitor.notify_all();
}

/*
 * Job_Pool_.*_Guard 
 */
Job_Pool_Consumer_Guard::Job_Pool_Consumer_Guard( Job_Pool& jpool, Worker& worker )
	: lock( jpool.mutex )
	, monitor( jpool.monitor )
{
	monitor.wait( lock, [&worker,&jpool](){ return worker.marked_for_termination() || jpool.has_available_job(); } );
}

Job_Pool_Consumer_Guard::~Job_Pool_Consumer_Guard()
{
	lock.unlock();
	monitor.notify_one();
}

Job_Pool_Producer_Guard::Job_Pool_Producer_Guard( Job_Pool& jpool )
	: guard( jpool.mutex )
{}

Job_Pool_Producer_Guard::~Job_Pool_Producer_Guard()
{}

/*
 * Worker_Pool 
 */
Worker_Pool::Worker_Pool( size_t number_of_workers )
	: jpool()
	, workers()
{
	add_worker( number_of_workers );
}
	
Worker_Pool::~Worker_Pool()
{
	remove_all_workers();
}

void Worker_Pool::add_job( unique_ptr<Job> job )
{
	Job_Pool_Producer_Guard guard( jpool );
	jpool.add( std::move(job) );
}

void Worker_Pool::remove_all_workers()
{
	for( Worker& w : workers )
		w.mark_termination();
	jpool.awake_all();
	for( Worker& w : workers )
		w.join();
	workers.clear();
}

void Worker_Pool::add_worker()
{
	workers.emplace_back(*this);
}

void Worker_Pool::remove_worker()
{
	Worker& wlast = workers.back();
	wlast.mark_termination();
	jpool.awake_all();
	wlast.join();
	workers.pop_back();
}

void Worker_Pool::add_worker( size_t n )
{
	workers.reserve( workers.size() + n );
	for( size_t i = 0; i < n; ++i )
		workers.emplace_back(*this);
}

void Worker_Pool::remove_worker( size_t n )
{
	auto const size = workers.size();
	auto const new_size = size - n;
	for( size_t i = new_size; i < size; ++i )
		workers[i].mark_termination();
	jpool.awake_all();
	for( size_t i = new_size; i < size; ++i )
		workers[i].join();
	workers.erase( workers.end() - n, workers.end() );
}

} //namespace bOoM


