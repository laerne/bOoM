#ifndef HEADERBoOm__Simulator
#define HEADERBoOm__Simulator

#include <array>
#include <condition_variable>
#include <future>
#include <initializer_list>
#include <iterator>
#include <memory>
#include <mutex>
#include <queue>
#include <stack>
#include <stdexcept>
#include <thread>
#include <unordered_set>
#include <vector>
//#include <bOoM/Entity.hpp>
#include "array_curry.hpp"

namespace bOoM {

//Theater metaphor
using std::unique_ptr;
using std::shared_ptr;
using std::weak_ptr;
using std::nullptr_t;

struct Entity;
class Job;
class ThreadPool;
class FIFOSequencer;


class Job
{
public:
	virtual void work() = 0;
	/* Iterators on entities */
	using iterator = std::array<shared_ptr<Entity>,1>::iterator;
	using const_iterator = std::array<shared_ptr<Entity>,1>::const_iterator;
	//virtual iterator       entities_begin() = 0;
	virtual const_iterator entities_begin() const = 0;
	virtual const_iterator entities_cbegin() const = 0;
	//virtual iterator       entities_end() = 0;
	virtual const_iterator entities_end() const = 0;
	virtual const_iterator entities_cend() const = 0;
};

template <unsigned int N>
class JobN : public Job
{
public:
	using fct_t = bOoM::function_repeat< void, Entity const&, N >;
	
	template <typename... EntityCastable>
	JobN(   fct_t const& fct,   shared_ptr<EntityCastable> const&... entities   )
		: Job(), fct(fct), entities({{entities...}}) {}
	JobN(   fct_t const& fct,   std::array<shared_ptr<Entity>,N> const& entities   );
	
	const_iterator entities_begin() const
		{ return entities.cbegin(); }
	const_iterator entities_cbegin() const
		{ return entities.cbegin(); }
	const_iterator entities_end() const
		{ return entities.cend(); }
	const_iterator entities_cend() const
		{ return entities.cend(); }
		
	void work();
	
private:
	fct_t fct;
	std::array<shared_ptr<Entity>,N> const entities;
};

// Some templates are pre-build in the library (up to N equals to 4).
// Export "extern" those templates, except in the compilation unit that defines them
#ifndef SOURCEBoOm__Simulator
extern template class JobN<0>;
extern template class JobN<1>;
extern template class JobN<2>;
extern template class JobN<3>;
extern template class JobN<4>;
#endif

struct Job_delete
{
	constexpr Job_delete( FIFOSequencer* sequencer = nullptr );
	//constexpr Job_delete( Job_delete const& ) = default;
	//constexpr Job_delete & operator=( Job_delete const& ) = default;
	//constexpr ~Job_delete() = default;
	void operator()(Job* ptr);

	FIFOSequencer* sequencer;
};

class FIFOSequencer
{
public:
	FIFOSequencer() = default;
	FIFOSequencer( FIFOSequencer const& ) = delete;
	FIFOSequencer & operator=( FIFOSequencer const& ) = delete;
	~FIFOSequencer() = default;

	using job_ptr = unique_ptr< Job, Job_delete >;
	void offer_job(Job* job);
	/*! \brief Pick a job that can be executed safely, and remove it from the list of job to do.
	 * 
	 * The job is return in a job_ptr, which is an instanciation of unique_ptr.
	 * If there is no job, or no job can be safely executed, an non-owning unique_ptr is returned.
	 */
	job_ptr get_job();
	void did_job(Job const& job); //TODO should be protected, but JobN should be a friend class.
	bool empty() const;
protected:
	bool jobEntitiesAreAvailable( Job const& job ) const;
private:
	std::deque<job_ptr> queue;
	std::mutex queue_access;
	std::unordered_set<Entity*> working_entities;
public:
};

class ThreadPool
{
public:
	ThreadPool() = default;
	ThreadPool( ThreadPool const& ) = delete;
	ThreadPool& operator=( ThreadPool const& ) = delete;
	~ThreadPool() = default;
private:
	FIFOSequencer jobs;
	std::vector< std::thread > workers;
};

} //namespace bOoM

#ifndef SOURCEBoOm__Simulator
namespace std {
//the library instanciate the unique_pointer type used by the sequencers.
extern template class unique_ptr< bOoM::Job, bOoM::Job_delete >;
} //namespace std
#endif

#endif


