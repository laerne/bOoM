#define SOURCEBoOm__Simulator
#include "Simulator.hpp"
#include "array_curry.hpp"

namespace bOoM {
using std::lock_guard;

template <unsigned int N>
JobN<N>::JobN(   fct_t const& fct,   std::array<shared_ptr<Entity>,N> const& entities   )
	: Job(), fct(fct), entities(entities) {}

template <unsigned int N> void JobN<N>::work()
{
	array_curry_deref_invoke< void, Entity&, N >( fct, entities );
}

//Instanciate common instances of JobN in the library itself.
template class JobN<0>;
template class JobN<1>;
template class JobN<2>;
template class JobN<3>;
template class JobN<4>;

constexpr Job_delete::Job_delete( FIFOSequencer* sequencer )
	: sequencer( sequencer ) {}
void Job_delete::operator()(Job* ptr)
{
	//TODO : inherit from this class.
	std::default_delete<Job> d;
	if(sequencer)
		sequencer->did_job(*ptr);
	d( ptr );
}

void FIFOSequencer::offer_job(Job* job)
{
	lock_guard<std::mutex> guard(queue_access);
	queue.emplace_back( job, this );
}


FIFOSequencer::job_ptr FIFOSequencer::get_job()
{
	lock_guard<std::mutex> guard(queue_access);
	for( auto i = queue.begin(); i != queue.end(); ++i )
	{
		if(   jobEntitiesAreAvailable( *(i->get()) )   )
		{
			job_ptr ptr ( std::move(*i) );
			queue.erase(i);
			for( auto i = ptr->entities_cbegin(); i != ptr->entities_cend(); ++i )
				working_entities.insert( i->get() );
			
			return ptr;
		}
	}
	return job_ptr( nullptr, this );
}

bool FIFOSequencer::jobEntitiesAreAvailable( Job const& job ) const
{
	for( auto i = job.entities_cbegin(); i != job.entities_cend(); ++i )
		if( working_entities.count( i->get() ) > 0 )
			return false;
	return true;
}

bool FIFOSequencer::empty() const
{
	return queue.empty();
}

void FIFOSequencer::did_job(Job const& job)
{
	for( auto i = job.entities_cbegin(); i != job.entities_cend(); ++i )
		working_entities.erase( i->get() );
}




} //namespace bOoM

namespace std {
//explicit instanciation of the unique_pointer used by the sequencers.
template class unique_ptr< bOoM::Job, bOoM::Job_delete >;
} //namespace std

