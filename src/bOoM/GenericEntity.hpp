#ifndef HEADERBoOm__GenericEntity
#define HEADERBoOm__GenericEntity

#include <memory>
#include <functional>


namespace bOoM {
using std::shared_ptr;

/******************************************************************************
 * TODO : replace the cmpnt_t as a tuple                                      *
 * //example of how a component should be declared                            *
 * struct component { static std::tuple<                                      *
 *        decltype(fct1), decltype(fct2), decltype(fct3)                      *
 *     > const pack; };                                                       *
 * fct_idx should use   decltype<C::pack>   to recurse on the given tuple     *
 *                                                                            *
 * TODO : commit before                                                       *
 * similarly, entity_components<D,GenericEntity<Cs...>> should hold           *
 * std::tuple< decltype(<Cs::pack>)... > pack;                                *
 ******************************************************************************/

using fct_t = void(*)(...);
using cmpnt_t = fct_t const*;
using fct_idx_t = size_t;
using cmpnt_idx_t = size_t;

/******************************************************************************
 * //example of how a component should be declared                            *
 * struct component { static fct_t const table[]; };                          *
 ******************************************************************************/
template<template<typename> class... Cs>
class GenericEntity;
	

//The following function computes the index of element 'e' in array 'a' at compile-time.
template<typename T>
constexpr size_t arrayidx( T const a[], T const& e, size_t current_idx )
	{ return (a[current_idx] == e) ? current_idx : arrayidx<T>(a, e, current_idx+1); }
template<typename T>
constexpr size_t arrayidx( T const a[], T const& e)
	{ return arrayidx<T>(a, e, 0); }
	
//The following function computes the index of function f in component C at compile-time.
#define fct_idx(C,f) arrayidx<fct_t>(C<void>::table, f<void>)

//A table of each component's table
template<typename D, class GE>
struct entity_components;
template<typename D, template<typename> class... Cs>
struct entity_components<D, GenericEntity<Cs...>>
{
	static cmpnt_t const table[];
};
template<typename D, template<typename> class... Cs>
cmpnt_t const entity_components<D, GenericEntity<Cs...>>::table[] = { Cs<D>::table... };
#define cmpnt_idx(E,C) arrayidx<cmpnt_t>( entity_components<void,E>::table, C<void>::table)

	
//An entity, with a virtual method to get the function associated with the entity.
template<template<typename> class... Cs>
class VirtualEntity
{
public:
	virtual cmpnt_t operator[](cmpnt_idx_t) = 0;
};

//An entity with a data component.
template<typename D, template<typename> class... Cs>
class DataEntity : VirtualEntity<Cs...>
{
public:
	virtual cmpnt_t operator[](cmpnt_idx_t cmpnt)
		{ return entity_components<D,GenericEntity<Cs...>>::table[cmpnt]; }
	static cmpnt_t const table[];
};

//pointer to an entity
template<template<typename> class... Cs>
class GenericEntity
{
public:
	template<GenericEntity> void call(cmpnt_idx_t cidx, fct_idx fidx, ...)
	{
		return (*ptr)[cidx][fidx](args);
	}
protected:
	shared_ptr<VirtualEntity<Cs...>> ptr;
};





} //namespace bOoM
#endif


