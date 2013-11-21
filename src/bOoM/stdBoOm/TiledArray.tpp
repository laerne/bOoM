#include <cmath>
#include <string>
#include <sstream>
namespace bOoM {

template<typename A>
TiledArray<A>::TiledArray(size_t_2 msize, size_t_2 tileSize)
	: localSize(tileSize), msize(msize), tileArea(tileSize.x*tileSize.y)
{
	//precompute a few useful values
	size_t_2 sizeInTiles= TiledArrayUtils::inTileUnits( msize, tileSize );
	size_t_2 paddedSize= TiledArrayUtils::paddedToTile( msize, tileSize );
	size_t areaInTiles= sizeInTiles.x * sizeInTiles.y;
	
	//allocate the arrays
	array= new A[paddedSize.x*paddedSize.y];
	fastArray_x = new size_t[msize.x +msize.y];
	fastArray_y = fastArray_x +msize.x;
	reverseFastArray_tile = new size_t_2[areaInTiles +tileArea];
	reverseFastArray_local = reverseFastArray_tile +areaInTiles;

	//build the index arrays
	build_fastArrays(sizeInTiles);
	build_reverseFastArrays(sizeInTiles);
}

template<typename A>
TiledArray<A>::TiledArray(TiledArray<A> && other)
	: localSize(other.localSize), msize(other.msize), tileArea(other.tileArea)
{
	//delete first the now unused arrays
	delete[] fastArray_x;
	delete[] reverseFastArray_tile;
	delete[] array;
	//then link to the rhs arrays.
	fastArray_x = other.fastArray_x;
	fastArray_y = other.fastArray_y;
	reverseFastArray_tile = other.reverseFastArray_tile;
	reverseFastArray_local = other.reverseFastArray_local;
	array= other.array;
	//unlink the other to the arrays to ensure its destructor won't harm them.
	other.reverseFastArray_tile = nullptr;
	other.reverseFastArray_local = nullptr;
	other.array = nullptr;
	
}

template<typename A>
TiledArray<A>::~TiledArray()
{
	delete[] fastArray_x;
	//delete[] fastArray_y;
	delete[] reverseFastArray_tile;
	//delete[] reverseFastArray_local;
	delete[] array;
}

template<typename A>
void TiledArray<A>::build_fastArrays(size_t_2 const& sizeInTiles)
{
	for(size_t x=0; x<msize.x; ++x)
		fastArray_x[x]= (x/localSize.x) *tileArea + (x%localSize.x);

	for(size_t y=0; y<msize.y; ++y)
		fastArray_y[y]= (y/localSize.y) *sizeInTiles.x *tileArea 
		              + (y%localSize.y) *localSize.x;
}

template<typename A>
void TiledArray<A>::build_reverseFastArrays(size_t_2 const& sizeInTiles)
{
	size_t areaInTiles= sizeInTiles.x * sizeInTiles.y;

	for(size_t t=0; t<areaInTiles; ++t)
		reverseFastArray_tile[t]= size_t_2(
				(t%sizeInTiles.x) *localSize.x ,
				(t/sizeInTiles.x) *localSize.y );

	for(size_t l=0; l<tileArea; ++l)
		reverseFastArray_local[l]= size_t_2(
				(l%localSize.x) ,
				(l/localSize.x) );
}

template<typename A>
size_t TiledArray<A>::indexOf(size_t_2 p) const
	{ return fastArray_x[p.x] + fastArray_y[p.y]; }
template<typename A>
size_t_2 TiledArray<A>::mindexOf(size_t j) const
	{ return reverseFastArray_tile[j/tileArea] + reverseFastArray_local[j%tileArea]; }

template<typename A>
bool TiledArray<A>::isCorrectIndex(size_t idx) const
	{ return isCorrectMindex( mindexOf(idx) ); }
template<typename A>
bool TiledArray<A>::isCorrectMindex(size_t_2 midx) const
	{ return (midx.x<msize.x) && (midx.y<msize.y); }

template<typename A>
A const& TiledArray<A>::operator[](size_t_2 midx) const
	{ return array[indexOf(midx)]; }
template<typename A>
A const& TiledArray<A>::operator[](size_t idx) const
	{ return array[idx]; }
template<typename A>
A& TiledArray<A>::operator[](size_t_2 midx)
	{ return array[indexOf(midx)]; }
template<typename A>
A& TiledArray<A>::operator[](size_t idx)
	{ return array[idx]; }

//<TODO> move elsewhere
//from http://stackoverflow.com/questions/13030967/java-tostring-method-in-c
template <typename A>
std::string toString(const A& typeinstance)
{
	std::ostringstream s;
	s << typeinstance;
	return s.str();  
}
//</TODO>


static size_t maxCellLen=7, sepLen=1;

template<typename A>
std::ostream& operator<<(std::ostream& s, TiledArray<A> const& tarray)
{
	s <<"TiledArray[V]" << std::endl;
	for(size_t_2 p(0,tarray.msize.y-1); p.y<=tarray.msize.y; --(p.y))
	{
		for(p.x=0; p.x < tarray.msize.x; ++(p.x))
		{
			std::string str = toString<A>(tarray[p]);
			str.resize(maxCellLen, ' ');
			std::string whitespaces;
			whitespaces.resize(sepLen, ' ');
			s << str << whitespaces;
		}
		s << std::endl;
	}
	return s;
}

namespace TiledArrayUtils {
	inline size_t_2 paddedToTile(size_t_2 n, size_t_2 t)
		{ return size_t_2( paddedToTile(n.x,t.x), paddedToTile(n.y,t.y) ); }
	inline size_t_2 inTileUnits(size_t_2 n, size_t_2 t)
		{ return size_t_2( inTileUnits(n.x,t.x), inTileUnits(n.y,t.y) ); }
	inline size_t paddedToTile(size_t n, size_t t)
		{ return n + ((-n)%t); }
	inline size_t inTileUnits(size_t n, size_t t)
		{ return ( n%t == 0 )? n/t : (n/t)+1; }
} //namespace TiledArrayUtils

} //namespace bOoM
