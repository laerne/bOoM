#ifndef H_Dispatcher
#define H_Dispatcher
namespace dispatcher {

class Dispatcher
{
	Dispatcher();
	Dispatcher(Dispatcher& other) = delete;
	Registration* registerForEvents(Guard& onWhat);
	unregisterForEvents(Guard& onWhat);
	void notifyEvent(Event& e);
}

class Guard
{
	virtual bool acceptsEvent(Event const& e);
	virtual ~Guard();
}

//Everything else must be a wrapper around a better library, like libcppa


} //namespace dispatcher
#endif


