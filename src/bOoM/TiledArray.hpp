#ifndef H_TiledArray
#define H_TiledArray
/*! \file TiledArray.hpp
 *  \brief File where TiledArray is defined.
 *  \sa TiledArray
 */

#include <iostream>

#include "math2d.hpp"
#include "color.hpp"

namespace bOoM {

#define STD_TILE_SIZE size_t_2(16,16)
/*! \brief A two-dimensional array optimized for both vertical and horizontal acces performance.
 *
 * A tiled array has indices redistributed such that caching neighboring cells
 * are stored not far away one from each other.
 * Conceptually, it can be viewed as nesting regular 2D arrays into a larger
 * regular 2D array.
 * The sub-arrays are called “tiles”.
 * On the implementation level, we can achieve very performed access time with
 * a few smart ideas.
 *
 * Conversion between the 2D and 1D indexes are done with the TiledArray::mindexOf and
 * TiledArray::indexOf methods.
 *
 * The cache efficiency come at a slight expense of some space complexity.
 * The extreme case is a TiledArray whose tileSize is `size_t_2(1,1)` or is the TiledArray's size itself.
 * Such a TiledArray stores its entries as in a regular two-dimensional array,
 * but likely with more than twice the space complexity because of the quick index look-up
 * tables.
 * If \f$(w_t,h_t)\f$ is the size of a tile and \f$(w,h)\f$ is the size of the
 * TiledArray, the space complexity of the look-up tables is given by :
 * \f[
 * 	\mathcal{O}\left(
 * 		w +h +\left\lfloor\frac{w \cdot h}{w_t \cdot h_t}\right\rfloor + w_t \cdot h_t
 * 	\right)
 * \f]
 */
template<typename A>
class TiledArray {
public:
	/*! \brief Construct a tiled array data structure, with size `msize` and
	 *  made of tiles of size `tileSize`.
	 */
	TiledArray(size_t_2 msize, size_t_2 tileSize = STD_TILE_SIZE);
	/*! \brief Destruct a TiledArray.
	 *
	 *  If the TiledArray was an array of pointer, the pointer are just
	 *  forgotten, as destructing a regular array would do.
	 */
	~TiledArray();
	//! \brief Move constructor.  Unallocate the currently allocated array.
	TiledArray(TiledArray<A> const& other) = delete;
	TiledArray(TiledArray<A> && other);

	/*! \brief Returns the one-dimensional index for this table of the given two-dimensional index.
	 *
	 * The access time is efficient : one sum and two array index look-up are performed.
	 */
	size_t indexOf(size_t_2 p) const;

	/*! \brief Returns the one-dimensional index for this table of the given two-dimensional index.
	 *
	 * The access time is slightly less efficient than for TiledArray::indexOf(size_t_2 p) :
	 * one division and modulo, one sum and two array index look-up are performed.
	 */
	size_t_2 mindexOf(size_t j) const;

	/*! \brief Returns whether the given one-dimensional index is a valid index of the TiledArray.
	 *
	 * This test uses TiledArray::mindexOf and TiledArray::isCorrectMindex,
	 * so if you have the choice, prefer to use the TiledArray::isCorrectMindex.
	 */
	bool isCorrectIndex(size_t idx) const;

	//! \brief Returns whether the given two-dimensional index is a valid index of the TiledArray.
	bool isCorrectMindex(size_t_2 midx) const;
	//! \brief Returns a constant reference to the element at index `midx`.
	A const& operator[](size_t_2 midx) const;
	//! \brief Returns a constant reference to the element at index `idx`.
	A const& operator[](size_t idx) const;
	//! \brief Returns a reference to the element at index `midx`.
	A& operator[](size_t_2 midx);
	//! \brief Returns a reference to the element at index `idx`.
	A& operator[](size_t idx);

	size_t_2 size() const { return msize; }
	size_t width()  const { return msize.x; }
	size_t height() const { return msize.y; }
protected:
	//! \brief The size of a tile.
	size_t_2 const localSize;
	//! \brief The total size of the TiledArray.
	size_t_2 const msize;
	//! \brief The number of elements per tile.
	size_t const tileArea;
	
	//! \brief Build TiledArray::fastArray_x and TiledArray::fastArray_y
	void build_fastArrays(size_t_2 const& sizeInTiles);
	//! \brief Build TiledArray::reverseFastArray_tile and TiledArray::reverseFastArray_local
	void build_reverseFastArrays(size_t_2 const& sizeInTiles);

	size_t *fastArray_x; //!< quick 2D->1D index conversion table, x part
	size_t *fastArray_y; //!< quick 2D->1D index conversion table, y part
	size_t_2 *reverseFastArray_tile;  //!< quick 1D->2D index conversion table, (index/tileArea) part
	size_t_2 *reverseFastArray_local; //!< quick 1D->2D index conversion table, (index%tileArea) part

	A *array; //!< Array containing the actual contents.
};

//! \brief Print a tiled array as a 2D representation.
//!
//! Each cell representation is truncated to a maximum of 7 chararters.
//! \relates bOoM::TiledArray
template<typename A>
std::ostream& operator<<(std::ostream& s, TiledArray<A> const& tarray);

namespace TiledArrayUtils {
	//! \brief Round up each component of `n` such that it is a multiple of the correspondant component of `t`.
	inline size_t_2 paddedToTile(size_t_2 n, size_t_2 t);
	//! \brief Return the number of times `t` must be fit in `n` to cover it all, per component.
	inline size_t_2 inTileUnits(size_t_2 n, size_t_2 t);
	//! \brief Round up `n` such that it is a multiple of `t`.
	inline size_t paddedToTile(size_t n, size_t t);
	//! \brief Return the minimal `k` such that `k*t >= n`.
	inline size_t inTileUnits(size_t n, size_t t);
} //namespace TiledArrayUtils

} //namespace bOoM

#include "TiledArray.tpp"
#endif

