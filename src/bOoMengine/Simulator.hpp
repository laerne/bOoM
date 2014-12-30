#ifndef HEADERBOOMENGINE_Simulator
#define HEADERBOOMENGINE_Simulator

#include <array>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>
#include <stack>
#include <stdexcept>
#include <thread>
#include <vector>

#include <bOoM/Entity.hpp>

#include "eventual_bool.hpp"


namespace bOoM {


class Job;
class Worker;
class Job_Pool;
class Worker_Pool;

class Job
{
public:
	virtual void process() = 0;
};

class Worker
{
public: /*constructors*/
	Worker( Worker_Pool& pool );
	Worker( Worker&& former );
	Worker( Worker& former ) = delete;

public: /*methods*/
	void operator=( Worker&& former );
	void operator=( Worker& former ) = delete;
	void mark_termination();
	bool marked_for_termination();
	void join();
private: /*methods*/
	void work();

private: /*members*/
	eventual_false proceed;
	Worker_Pool& pool;
	std::thread thread;
};

class Job_Pool
{
public: /*methods*/
	bool has_available_job() const;
	std::unique_ptr<Job> pick();
	void add( std::unique_ptr<Job> job );
	void awake_all();
	
private: /*members*/
	std::queue< std::unique_ptr<Job> > jobs;
	std::mutex mutex;
	std::condition_variable monitor;
	
	friend class Worker;
	friend class Worker_Pool;
	friend class Job_Pool_Consumer_Guard;
	friend class Job_Pool_Producer_Guard;
};

class Job_Pool_Consumer_Guard
{
public: /*constructors*/
	Job_Pool_Consumer_Guard( Job_Pool& jpool, Worker& worker );
	~Job_Pool_Consumer_Guard();
private: /*members*/
	std::unique_lock<std::mutex> lock;
	std::condition_variable& monitor;
};

class Job_Pool_Producer_Guard
{
public: /*constructors*/
	Job_Pool_Producer_Guard( Job_Pool& jpool );
	~Job_Pool_Producer_Guard();
private: /*members*/
	std::lock_guard<std::mutex> guard;
};

class Worker_Pool
{
public: /*constructors*/
	Worker_Pool( std::size_t number_of_workers );
	~Worker_Pool();

public: /*methods*/
	void add_job( std::unique_ptr<Job> job );
	void remove_all_workers();
private: /*methods*/
	void add_worker();
	void remove_worker();
	void add_worker( size_t n );
	void remove_worker( size_t n );

private: /*members*/
	Job_Pool jpool;

	std::vector<Worker> workers;

	friend class Worker;
};


} //namespace bOoM

#endif


