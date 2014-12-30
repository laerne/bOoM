#ifndef HEADERBOOMENGINE_eventual_bool
#define HEADERBOOMENGINE_eventual_bool
#include <cassert>

namespace bOoM {

template<bool eventual_value>
struct eventual_bool {
	bool value = !eventual_value;
	eventual_bool() = default;
	eventual_bool( bool initial_value )
		: value( initial_value ) {}
	eventual_bool( eventual_bool const& ) = default;
	
	void toggle()
		{ value = eventual_value; }
		
	void operator=( bool new_value )
		{ assert( new_value == eventual_value ); toggle(); }
	operator bool()
		{ return value; }
};

using eventual_true = eventual_bool<true>;
using eventual_false = eventual_bool<false>;

} //namespace bOoM
#endif


