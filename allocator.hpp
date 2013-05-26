#ifndef H_allocator
#define H_allocator
#include <cstdlib>
#include <cstdint>
#include <cassert>

class StdAllocator
{
	void *allocate(std::size_t size)
	{
		return std::malloc(size);
	}
	virtual void deallocate(void *size)
	{
		return std::free(size);
	}
};
//! Global StdAllocator (like a singleton)
StdAllocator stdAllocator;

//!inspired from box2d
class StackAllocator
{
	size_t size = 0x40000; //2^18 = 256kB
	StdAllocator(size =StackAllocatorDefaultSize)
	{
		buffer = std::malloc(size);
		next = buffer;
		buffer_end = buffer + size;
	}
	~StdAllocator()
	{
		free(buffer);
	}
	void *allocate(std::size_t size)
	{
		//Double the size of the buffer if we do not have enough room left.
		if( next +size +sizeof(std::size_t) >= buffer_end )
		{
			next_relative= next - buffer;
			fullSize= buffer_end - buffer;
			buffer= std::realloc( buffer, 2*fullSize );
			next= buffer +next_relative;
			buffer_end= buffer +fullSize;
		}
		next += size;
		*( const_cast<size_t*>(next) ) = size ;
		next += sizeof(std::size_t);
	}
	void deallocate(void *ptr)
	{
		assert( ptr == next && ptr > buffer);
		next -= sizeof(std::size_t);
		size_t size = *( const_cast<size_t*>(next) );
		next -= size;
	}

	void* buffer;
	void* next;
	void* buffer_end;
	//TODO add a threshold to div by 2 the size of the buffer ?
};


#endif

