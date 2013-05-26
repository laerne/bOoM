#ifndef H_allocator
#define H_allocator
#include <cstdlib>
#include <cstdint>
#include <cassert>
#include <iostream>
#include <iomanip>

constexpr std::size_t operator"" _bytes(unsigned long long const x)
	{ return static_cast<std::size_t>(x); }
constexpr std::size_t operator"" _kilobytes(unsigned long long const x)
	{ return static_cast<std::size_t>(x*1024); }
constexpr std::size_t operator"" _megabytes(unsigned long long const x)
	{ return static_cast<std::size_t>(x*1048576); }
constexpr std::size_t operator"" _gigabytes(unsigned long long const x)
	{ return static_cast<std::size_t>(x*1073741824); }

namespace bOoM {

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
struct StackAllocator
{
	explicit StackAllocator(std::size_t size = 1_megabytes)
	{
		buffer=(uint8_t*) std::malloc(size);
		//TODO fail if buffer == null
		next= buffer;
		buffer_end= buffer+size;
	}

	~StackAllocator() { free(buffer); }

	void *allocate(std::size_t size)
	{
		//Double the size of the buffer if we do not have enough room left.
		if( next +size +sizeof(std::size_t) >= buffer_end )
		{
			size_t next_relative= next - buffer;
			size_t fullSize= buffer_end - buffer;
			buffer= (uint8_t*) std::realloc( buffer, 2*fullSize );
			next= buffer +next_relative;
			buffer_end= buffer + (2*fullSize);
		}
		void* ptr= next;
		next += size;
		*( (size_t*)next ) = size ;
		next += sizeof(std::size_t);
		return ptr;
	}
	void deallocate(void *ptr)
	{
		assert( ptr == next && ptr > buffer);
		next -= sizeof(std::size_t);
		size_t size = *( (size_t*)next );
		next -= size;
	}

	uint8_t* buffer;
	uint8_t* next;
	uint8_t* buffer_end;
	//TODO add a threshold to div by 2 the size of the buffer ?
};

std::ostream& operator<<(std::ostream& s, StackAllocator const& a)
{
	s << "StdAllocator[" << std::endl;
	int charactersOnLines= 0;
	for(uint8_t* byte= a.buffer; byte < a.buffer_end; ++byte)
	{
		s << std::hex << std::setw(2) << (int)*byte << " ";
		charactersOnLines += 3;
		if(charactersOnLines >= 80)
		{
			s << std::endl;
			charactersOnLines=0;
		}
	}
	s << "]";

	return s;
}

} //namespace bOoM
#endif

