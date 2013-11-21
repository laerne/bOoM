#ifndef H_FlatArray
#define H_FlatArray
namespace bOoM {

template<typename A>
class FlatArray {
public:
	//! \brief Construct a 2d flat array data structure, with size `msize`.
	FlatArray(size_t_2 msize);
	/*! \brief Destruct a FlatArray.
	 *
	 *  If the FlatArray was an array of pointer, the pointer are just
	 *  forgotten, as destructing a regular array would do.
	 */
	~FlatArray();
	FlatArray(FlatArray<A> const& other) = delete;
	//! \brief Move constructor.  Unallocate the currently allocated array.
	FlatArray(FlatArray<A> && other);

	/*! \brief Returns the one-dimensional index for this table of the given two-dimensional index.
	 *
	 * The access time is efficient : one sum and one product are performed
	 */
	size_t indexOf(size_t_2 p) const;

	/*! \brief Returns the one-dimensional index for this table of the given two-dimensional index.
	 *
	 * The access time is slightly less efficient than for FlatArray::indexOf(size_t_2 p) :
	 * one division, one modulo and one sum are performed.
	 */
	size_t_2 mindexOf(size_t j) const;

	//! \brief Returns whether the given one-dimensional index is a valid index of the FlatArray.
	bool isCorrectIndex(size_t idx) const;
	//! \brief Returns whether the given two-dimensional index is a valid index of the FlatArray.
	bool isCorrectMindex(size_t_2 midx) const;
	//! \brief Returns a constant reference to the element at index `midx`.
	A const& operator[](size_t_2 midx) const;
	//! \brief Returns a constant reference to the element at index `idx`.
	A const& operator[](size_t idx) const;
	//! \brief Returns a reference to the element at index `midx`.
	A& operator[](size_t_2 midx);
	//! \brief Returns a reference to the element at index `idx`.
	A& operator[](size_t idx);

	//! \brief The total size of the flatArray.
	size_t_2 const msize;
	
	size_t width() { return msize.x; }
	size_t height() { return msize.y; }
protected:
	A *array; //!< Array containing the actual contents.
};


} //namespace bOoM

#include "stdBoOm/FlatArray.tpp"
#endif


