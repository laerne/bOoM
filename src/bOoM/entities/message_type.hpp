#ifndef H_message_type
#define H_message_type

namespace common {

enum message_type : int_fast16_t {
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


