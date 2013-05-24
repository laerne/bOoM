#ifndef H_TiledArray
#define H_TiledArray

#include <vector>
#include <iostream>

#include "math2d.hpp"
namespace bOoM {

typedef V2<size_t> size_t_2;

template<typename A>
class TiledArray {
public:
	TiledArray(size_t_2 totalSize, size_t_2 tileSize);
	~TiledArray();

	size_t indexOf(size_t_2 p) const;
	size_t_2 mindexOf(size_t j) const;

	bool isCorrectIndex(size_t idx) const;
	bool isCorrectMindex(size_t_2 midx) const;
	A const& at(size_t_2 midx) const;
	A const& at(size_t idx) const;
	A& operator[](size_t_2 midx);
	A& operator[](size_t idx);

	size_t_2 const localSize;
	size_t_2 const totalSize;
	size_t const tileArea;
private:
	void build_fastArrays(size_t_2 const& sizeInTiles);
	void build_reverseFastArrays(size_t_2 const& sizeInTiles);

	size_t *fastArray_x;
	size_t *fastArray_y;
	size_t_2 *reverseFastArray_tile;
	size_t_2 *reverseFastArray_local;

	A *array;
};

template<typename A>
std::ostream& operator<<(std::ostream& s, TiledArray<A> const& tarray);

namespace TiledArrayUtils {
	size_t_2 paddedToTile(size_t_2 n, size_t_2 t);
	size_t_2 inTileUnits(size_t_2 n, size_t_2 t);
	size_t paddedToTile(size_t n, size_t t);
	size_t inTileUnits(size_t n, size_t t);
} //namespace TiledArrayUtils

} //namespace bOoM

#include "TiledArray.tpp"
#endif

