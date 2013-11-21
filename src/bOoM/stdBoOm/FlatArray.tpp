//implementation of templates in "FlatArray.hpp"
namespace bOoM {

template<typename A>
FlatArray<A>::FlatArray(size_t_2 msize)
	: msize(msize)
{
	array= new A[msize.x*msize.y];
}

template<typename A>
FlatArray<A>::FlatArray(FlatArray<A> && other)
	: msize(other.msize)
{
	delete[] array;
	array= other.array;
	other.array= nullptr;
}

template<typename A>
FlatArray<A>::~FlatArray()
	{ delete[] array; }

template<typename A>
size_t FlatArray<A>::indexOf(size_t_2 p) const
	{ return p.y*msize.x + p.x; }
template<typename A>
size_t_2 FlatArray<A>::mindexOf(size_t j) const
	{ return size_t_2( j%msize.x , j/msize.x ); }

template<typename A>
bool FlatArray<A>::isCorrectIndex(size_t idx) const
	{ return idx < msize.x * msize.y; }
template<typename A>
bool FlatArray<A>::isCorrectMindex(size_t_2 midx) const
	{ return (midx.x<msize.x) && (midx.y<msize.y); }

template<typename A>
A const& FlatArray<A>::operator[](size_t_2 midx) const
	{ return array[indexOf(midx)]; }
template<typename A>
A const& FlatArray<A>::operator[](size_t idx) const
	{ return array[idx]; }
template<typename A>
A& FlatArray<A>::operator[](size_t_2 midx)
	{ return array[indexOf(midx)]; }
template<typename A>
A& FlatArray<A>::operator[](size_t idx)
	{ return array[idx]; }

} //namespace bOoM

