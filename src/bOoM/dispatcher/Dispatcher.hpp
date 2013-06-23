#ifndef H_Dispatcher
#define H_Dispatcher
namespace dispatcher {

class Dispatcher
{
	Dispatcher();
	Dispatcher(Dispatcher& other) = delete;
	tellIWantToBeNotified(Condition onWhat);
	notifyEvent(Condition onWhat);
}

} //namespace dispatcher
#endif


