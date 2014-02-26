#ifndef HEADERBoOm_BitsetAlloctator
#define HEADERBoOm_BitsetAlloctator

#include <bitset>
#include <mutex>

#include "cfg.hpp"

namespace bOoM {

//Designed for linked lists
template <typename T, uint32_t L>
struct BitsetAllocator
{
public:
	BitsetAllocator()
		: allocation_map(), nb_allocated(0), alloc_idx(0) {}

	using pointer = T*;
	using const_pointer = T const*;
	using void_pointer = void*;
	using const_void_pointer = void const*;
	using value_type = T;
	using size_type = size_t;

	T* allocate()
	{
		//CRITICAL SECTION
		{ std::lock_guard<std::mutex> lock(nb_gate);
			if( L == nb_allocated )
				return nullptr; //no more memory, TODO: have an extensible BitsetAllocator
			else 
				++nb_allocated;
		}

		{ std::lock_guard<std::mutex> lock(idx_gate);
			while( allocation_map[alloc_idx] )
				alloc_idx = (alloc_idx+1) % L;
			allocation_map.set(alloc_idx);
		}

		return &cell[alloc_idx];
	};

	void deallocate(T* ptr)
	{
		size_t idx = (ptr - cell);
		allocation_map.reset(idx);

		{ std::lock_guard<std::mutex> lock(nb_gate);
			--nb_allocated;
		}
	}

private:
	std::bitset<L> allocation_map;
	size_t nb_allocated = 0;
	size_t alloc_idx = 0;
	std::mutex nb_gate;
	std::mutex idx_gate;

	T cell[L];
};

} //namespace bOoM
#endif


