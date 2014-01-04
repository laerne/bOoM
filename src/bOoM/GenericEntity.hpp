#ifndef HEADERBoOm__GenericEntity
#define HEADERBoOm__GenericEntity

#include <memory>
#include <functional>
#include <tuple>


namespace bOoM {
using std::shared_ptr;

/******************************************************************************
 * TODO : compute using template magic, for an entity with its list of        *
 * components, the possible function types, and cppa will become() on each    *
 * possible function type calling template<fct_type> call()                   *
 ******************************************************************************/


////////////////////////////////////////////////////////////////////////////////
// Declaration in advance of the meaningful data types.                       //
////////////////////////////////////////////////////////////////////////////////

template<template<typename> class... Components>
class GenericEntity;

template<template<typename> class... Components>
class VirtualEntity;

template<typename D, template<typename> class... Componentss>
class DataEntity;

using fct_idx_t = int;
using cmpnt_idx_t = int;


////////////////////////////////////////////////////////////////////////////////
// macro to declare a component                                               //
////////////////////////////////////////////////////////////////////////////////


//template<typename Datatype, template <typename> class... FunctionTypes>
//struct user_made_component
//{
//	static std::tuple<FunctionTypes<Datatype>*...> const functions; 
//};
//
//template<template <typename> class FunctionType>
//struct template_function_type
//{
//	//we do not care of the arguments value, we just need their types
//	constexpr user_made_component(FunctionType<void> const& ...) {}
//	template<typename Datatype>
//	using get = FunctionType<Datatype>;
//}
////TODO find boost preprocessor library
//
////#define BoOm__ITER_APPEND(R,CONST,ELEM) BOOST_PP_CAT(ELEM,CONST) //or :
//#define BoOm__ITER_APPEND(R,CONST,ELEM) ELEM CONST
//#define BoOm__ITER_TEMPLATE_TYPE(R,CONST,I,ELEM) template_function_type(BoOm__ITER_APPEND(ELEM,<void>))::get<Datatype> BOOST_PP_COMMA_IF(I)
//
//#define BoOm__COMPONENT( NAME, ... )
//template<typename Datatype>
//using NAME = user_made_component_tuple<Datatype, BOOST_PP_SEQ_FOR_EACH( BoOm__ITER_TEMPLATE_TYPE, <Datatype>, BOOST_PP_VARIADIC_TO_SEQ( __VA_ARGS__ )) >;
//template<typename Datatype>                                                  // V !!! Warning !!! reverse loop !!!
//decltype(NAME<Datatype>::functions) NAME<Datatype>::functions = std::make_tuple( BOOST_PP_SEQ_FOR_EACH_I_R( BoOm__ITER_APPEND, <Datatype>, BOOST_PP_VARIADIC_TO_SEQ( __VA_ARGS__ ))... )


////////////////////////////////////////////////////////////////////////////////
// Computation of the index of an element in a tuple                          //
////////////////////////////////////////////////////////////////////////////////

//This struct with constexpr member simply returns the index of the first occurence of a member with data type TYPE.
//It must be started at index 0.
constexpr int error_index = -1;
template<int ITERATION_INDEX, typename TYPE, typename TUPLE> struct next_type_iter;

template<int I, typename Ex, typename E0, typename... Es>
struct next_type_iter<I,Ex,std::tuple<E0,Es...>>
	{ static constexpr int index = next_type_iter<I+1,Ex,std::tuple<Es...>>::index; };
	
template<int I, typename Ex, typename... Es>
struct next_type_iter<I,Ex,std::tuple<Ex,Es...>>
	{ static constexpr int index = I; };

template<int I, typename Ex>
struct next_type_iter<I,Ex,std::tuple<>>
	{ static constexpr int index = error_index; };
	
	
//This struct with constexpr member simply returns the index of the first occurence of a member with data type TYPE and
//index greater than I.
// TODO Make this struct-function tail recursive as well.
template<int ITERATION_INDEX, typename TYPE, typename TUPLE> struct next_type;

template<int I, typename Ex, typename E0, typename... Es>
struct next_type<I,Ex,std::tuple<E0,Es...>>
{
	using next_type_tail = next_type<I-1,Ex,std::tuple<Es...>>;
	static constexpr int index = (next_type_tail::index != error_index) ? 1 + next_type_tail::index : error_index ; 
};
	
template<typename Ex, typename E0, typename... Es>
struct next_type<0,Ex,std::tuple<E0,Es...>>
	{ static constexpr int index = next_type_iter<0,Ex,std::tuple<E0,Es...>>::index; };
	
template<int I, typename Ex>
struct next_type<I,Ex,std::tuple<>>
	{ static constexpr int index = error_index; };

template<typename TYPE, typename TUPLE> using first_type = next_type<0,TYPE,TUPLE>;



//this struct is actually a function.
//but the function is defined as a function in order to be able to do template specialisation.
template<int I, typename E, typename T> struct tuple_idx_iter;

//this is the generic recursive method : we check a previously unchecked element of type E in the tuple.
//If this element is e, then we return its index, else we recurse with the next element of type E in the tuple.
template<int I, typename E, typename... Es> struct tuple_idx_iter<I,E,std::tuple<Es...>>
{
	static constexpr int solve(std::tuple<Es...> t, E e)
	{
		using nextI = next_type<I+1,E,std::tuple<Es...>>;
		return ( std::get<I>(t) == e ) ?
			(I) : (tuple_idx_iter<nextI::index,E,std::tuple<Es...>>::solve(t,e));
	}
};

//this is the template specialization to end recursion when there is no type element of type E that matches e.
//In the former function, if there is no more element of type E left to check, an negative error index is returned,
//so when it recurse with this error_index, it will call this function that ensures the error index is returned.
template<typename E, typename... Es > struct tuple_idx_iter<error_index,E,std::tuple<Es...>>
{
	static constexpr int solve(std::tuple<Es...> t, E e)
		{ return error_index; }
};

template<typename E, typename... Es>
constexpr int tuple_idx(std::tuple<Es...> t, E e)
{ 
	using firstI = first_type<E,std::tuple<Es...>>;
	return (firstI::index >= 0)? tuple_idx_iter<firstI::index,E,std::tuple<Es...>>::solve(t,e) : error_index;
}


// Macro that gives the index of a component of a DataEntity////////////////////
#define fct_idx(C,f) tuple_idx(C<void>::functions, f<void>)

template<typename E> struct void_components;

template<template <typename> class... Cs> struct void_components<GenericEntity<Cs...>>
	{ static constexpr std::tuple<decltype(Cs<void>::functions)*...> const& components = DataEntity<void, Cs...>::components ; };
#define cmpnt_idx(E,C) tuple_idx( void_components<E>::components, &C<void>::functions )

////////////////////////////////////////////////////////////////////////////////
// Definition of DataEntity<D,Cs...>                                          //
// contains the tuple of each component (also tuples) as a static member      //
////////////////////////////////////////////////////////////////////////////////

template<typename D, template<typename> class... Cs>
class DataEntity : VirtualEntity<Cs...>
{
public:
	static std::tuple<decltype(Cs<D>::functions)*...> const components;
};
template<typename D, template<typename> class... Cs>
// FIXME initialization : make sure there is only one per compilation unit
std::tuple<decltype(Cs<D>::functions)*...> const DataEntity<D, Cs...>::components( &Cs<D>::functions... );

	
////////////////////////////////////////////////////////////////////////////////
// Definition of VirtualEntity<D,Cs...>                                       //
////////////////////////////////////////////////////////////////////////////////
// An entity, with a virtual method to get the function associated with the entity.
template<template<typename> class... Cs>
class VirtualEntity
{
};

////////////////////////////////////////////////////////////////////////////////
// Definition of GenericEntity<D,Cs...>                                       //
////////////////////////////////////////////////////////////////////////////////
template<template<typename> class... Cs>
class GenericEntity
{
protected:
	shared_ptr<VirtualEntity<Cs...>> ptr;
};





} //namespace bOoM
#endif


