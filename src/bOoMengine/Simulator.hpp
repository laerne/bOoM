#ifndef HEADERBoOm__Simulator
#define HEADERBoOm__Simulator

#include <array>
#include <condition_variable>
#include <future>
#include <memory>
#include <mutex>
#include <queue>
#include <stdexcept>
#include <stack>
#include <thread>
#include <vector>
#include <bOoM/Entity.hpp>
#include "array_curry.hpp"

namespace bOoM {

//Theater metaphor
using std::unique_ptr;
using std::shared_ptr;
using std::weak_ptr;
using std::array;

class Job;
class ThreadPool;
class Sequencer;
class QueueSequencer;


class Job
{
public:
	virtual void work() = 0;
};

template <unsigned int N>
class JobN : Job
{
public:
	using fct_t = bOoM::function_repeat< void, Entity const&, N >;
	
	template <typename... EntityCastable>
	JobN(   fct_t const& fct,   shared_ptr<EntityCastable> const&... entities   )
		: Job(), fct(fct), entities({entities...}) {}
	JobN(   fct_t const& fct,   array<shared_ptr<Entity>,N> const& entities   )
		: Job(), fct(fct), entities(entities) {}
		
	void work();
	
private:
	fct_t fct;
	array<shared_ptr<Entity>,N> const entities;
};

class ThreadPool
{
public:
	template<typename SequencerType = QueueSequencer> ThreadPool()
		: jobs( new SequencerType() ) {}
private:
	unique_ptr<Sequencer> jobs;
	std::vector< std::thread > workers;
};

class Sequencer
{
public:
	virtual void pushJob(weak_ptr<Job> scene) = 0;
	virtual Job* popJob() = 0;
};

class QueueSequencer : public Sequencer
{
	void schedule_scene(weak_ptr<Job> scene);
	Job* shot_scene();
};

} //namespace bOoM
#endif


