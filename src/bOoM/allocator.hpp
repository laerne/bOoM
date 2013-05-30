#ifndef H_allocator
#define H_allocator

/*! \file allocator.hpp \brief File containing multiple custom allocators.
 *
 *  This file is concerned with compact allocation schemes, and defines some
 *  classes for specific-case pre-allocate strategies.
 */

#include <cstdlib>
#include <cstdint>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <vector>

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

struct StackAllocator;
struct StackAllocator_Page;
std::ostream& operator<<(std::ostream& s, StackAllocator const& a);
std::ostream& operator<<(std::ostream& s, StackAllocator_Page const& page);

//!inspired from box2d
struct StackAllocator_Page
{
	explicit StackAllocator_Page()
		: buffer(NULL), next(NULL), buffer_end(NULL)
	{
	}

	explicit StackAllocator_Page(std::size_t size)
	{
		buffer=(uint8_t*) std::malloc(size);
		//TODO fail if buffer == null
		next= buffer;
		buffer_end= buffer+size;
	}
	StackAllocator_Page(StackAllocator_Page const& other) = delete; // not copyable
	StackAllocator_Page(StackAllocator_Page && other)               // but moveable
	{
		buffer = other.buffer;
		next = other.next;
		buffer_end = other.buffer_end;
		other.buffer = NULL;
		other.next = NULL;
		other.buffer_end = NULL;
	}

	~StackAllocator_Page()
	{
		free(buffer);
	}

	void *allocate(std::size_t size)
	{
		//Double the size of the buffer if we do not have enough room left.
		//TODO extract the realloc outside the loop.
		assert( next +size +sizeof(std::size_t) <= buffer_end );
		void* ptr= next;
		next += size;
		*( (size_t*)next ) = size ;
		next += sizeof(std::size_t);
		return ptr;
	}
	void deallocate(void *ptr)
	{
		assert( ptr >= buffer && ptr < buffer_end );
		next -= sizeof(std::size_t);
		size_t size = *( (size_t*)next );
		next -= size;
		assert( ptr == next );
	}

	uint8_t* buffer;
	uint8_t* next;
	uint8_t* buffer_end;
};

inline std::size_t minimalLengthFor(std::size_t l)
{
	return l + sizeof(std::size_t);
}

struct StackAllocator
{
	StackAllocator() = delete;
	StackAllocator(std::size_t page_length)
		: page_length(page_length), pages(0)
	{}
	StackAllocator(StackAllocator const&) = delete;

	void *allocate(std::size_t size)
	{
		for(auto page_it = pages.begin(); page_it < pages.end(); ++page_it)
		{
			if( (page_it->next) +size +sizeof(std::size_t) < page_it->buffer_end )
				return page_it->allocate(size);
		}
 		pages.emplace_back(   std::max( page_length, minimalLengthFor(size) )   );
		return pages.back().allocate(size);
	}

	void deallocate(void *ptr)
	{
		for(auto page_it = pages.begin(); page_it < pages.end(); ++page_it)
		{
			if( ptr >= page_it->buffer && ptr < page_it->buffer_end )
			{
				page_it->deallocate(ptr);
				return;
			}
		}
		//if we reach here, the pointer do not reference to any page.
		assert(false);
	}

	void clearPages()
	{
		while( pages.rbegin() != pages.rend() && pages.rbegin()->buffer == pages.rbegin()->next )
			pages.pop_back();
	}

	~StackAllocator(){}
	std::size_t page_length;
	std::vector<StackAllocator_Page> pages;
};


#define PRINT_WIDTH__RAW_MEMORY 96

std::ostream& operator<<(std::ostream& s, StackAllocator_Page const& page)
{
	int charactersOnLines= 0;
	for(uint8_t* byte= page.buffer; byte < page.buffer_end; ++byte)
	{
		s << ( byte==page.next ? '|' : ' ' );
		s << std::hex << std::setw(2) << (int)*byte;
		charactersOnLines += 3;
		if(charactersOnLines >= PRINT_WIDTH__RAW_MEMORY)
		{
			s << std::endl;
			charactersOnLines=0;
		}
	}
	if(charactersOnLines!=0)
			s << std::endl;

	return s;
}

std::ostream& operator<<(std::ostream& s, StackAllocator const& a)
{
	std::string hline;
	hline.resize( PRINT_WIDTH__RAW_MEMORY +1 - sizeof("--StackAllocator"), '-' );
	s << "--StackAllocator" << hline << std::endl;
	hline.resize( PRINT_WIDTH__RAW_MEMORY, '-' );
	for(auto page_it = a.pages.begin(); page_it < a.pages.end(); ++page_it)
	{
		s << *page_it;
		s << hline << std::endl;
	}

	return s;
}

} //namespace bOoM
#endif

