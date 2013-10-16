#ifndef H_message_names
#define H_message_names

namespace common {

enum class message_name : int_fast16_t {
	// rendering-related messages
	RENDER = 1,
	DID_RENDER,
	// collision-related messages
	TEST_POSSIBLE_COLLISION = 0X10,
	TELL_POSSIBLE_COLLISION_DETECTED,
	TELL_COLLISION_DETECTED,
}

} //namespace common
#endif


