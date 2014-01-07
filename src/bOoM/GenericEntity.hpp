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
	static constexpr int solve(std::tuple<Es...> const& t, E const& e)
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
	static constexpr int solve(std::tuple<Es...> const& t, E const& e)
		{ return error_index; }
};

template<typename E, typename... Es>
constexpr int tuple_idx(std::tuple<Es...> const& t, E const& e)
{ 
	using firstI = first_type<E,std::tuple<Es...>>;
	return (firstI::index >= 0)? tuple_idx_iter<firstI::index,E,std::tuple<Es...>>::solve(t,e) : error_index;
}


////////////////////////////////////////////////////////////////////////////////
// 2D tuple of function utilities                                             //
////////////////////////////////////////////////////////////////////////////////

//! \brief gives the index of the function of a component.
#define fct_idx(C,f) tuple_idx(C<void>::functions, f<void>)

template<typename ENTITY> struct void_components;

template<template <typename> class... Cs> struct void_components<GenericEntity<Cs...>>
{
	// FIXME the following declaration should be constexpr :
	// This is not possible because tuple as parameters are NEVER constexpr.
	// How should it be done ?
	// The entire above code about finding an index should be re-written not to use a tuple and an element as parameter,
	// but should take no parameter at all and be 100% template by augmenting the parameter list with a list of pointer
	// types.
	// The user could define a component by specialiazin the struct component.
	// This should look like :
	//     template<typename... T,> component<T... t>
	// but this does not works !
	//static constexpr std::tuple<decltype(Cs<void>::functions)*...> components { &(Cs<void>::functions)... };
	static const std::tuple<decltype(Cs<void>::functions)*...> components;
};
template<template <typename> class... Cs>
const std::tuple<decltype(Cs<void>::functions)*...> void_components<GenericEntity<Cs...>>::components { &(Cs<void>::functions)... };

//! \brief gives the index of a component of a DataEntity.
#define cmpnt_idx(ENTITY,C) tuple_idx( bOoM::void_components<ENTITY>::components, &C<void>::functions )

//FIXME-C++14 : replace constexpr no argument functions with constexpr variables.
template<typename ENTITY, int CIDX> using component_table_signature    = decltype(                 std::get<CIDX>(void_components<ENTITY>::components)  );
template<typename ENTITY, int CIDX, int FIDX> using function_signature = decltype( std::get<FIDX>(*std::get<CIDX>(void_components<ENTITY>::components)) );
//FIXME-C++14 : this function can only work in C++14
//template<typename ENTITY> constexpr size_t table_of_components_size(void)          { return std::tuple_size< decltype(                void_components<ENTITY>::components)  >::value; }
template<typename ENTITY, int CIDX> constexpr size_t table_of_functions_size(void)
	{ return std::tuple_size< typename std::remove_reference<decltype(*std::get<CIDX>(void_components<ENTITY>::components))>::type >::value; }
template<template<typename>class C> constexpr size_t component_size(void)
	{ return std::tuple_size< decltype(C<void>::functions) >::value; }

////////////////////////////////////////////////////////////////////////////////
// Computation of the list of pair indexes (the component and the functional  //
// one) and the function type associated with it)                             //
////////////////////////////////////////////////////////////////////////////////
//It is not very efficient but it reuse the above code, most notably function_signature<I,J>

template<int CIDX, int FIDX, typename FType> struct full_function_signature {};

template<typename... Ts> struct flatten_tuples;
template<typename... E1s, typename... E2s, typename... Ts>
struct flatten_tuples<std::tuple<E1s...>,std::tuple<E2s...>,Ts...>
	{ using flat_tuple = typename flatten_tuples<std::tuple<E1s...,E2s...>,Ts...>::flat_tuple; };
template<typename T> struct flatten_tuples<T>
	{ using flat_tuple = T; };

template<typename ENTITY, cmpnt_idx_t CIDX, fct_idx_t FIDX>
struct cmpnt_full_fct_signatures_iter
{
	using this_level_signature = full_function_signature<CIDX,FIDX,function_signature<ENTITY,CIDX,FIDX>>;
	using tuple = typename flatten_tuples<   typename cmpnt_full_fct_signatures_iter<ENTITY,CIDX,FIDX-1>::tuple,   typename std::tuple<this_level_signature>   >::flat_tuple;
};
template<typename ENTITY, cmpnt_idx_t CIDX>
struct cmpnt_full_fct_signatures_iter<ENTITY, CIDX, -1>
	{ using tuple = std::tuple<>; };

template<typename ENTITY, cmpnt_idx_t CIDX>
struct cmpnt_full_fct_signatures
	{ using tuple = typename cmpnt_full_fct_signatures_iter<ENTITY,CIDX,table_of_functions_size<ENTITY,CIDX>()-1>::tuple; };

template<typename ENTITY, cmpnt_idx_t CIDX> struct entity_full_fct_signatures_iter
{
	using this_level_signature = typename cmpnt_full_fct_signatures<ENTITY,CIDX>::tuple;
	using tuple = typename flatten_tuples<   typename entity_full_fct_signatures_iter<ENTITY,CIDX-1>::tuple,   this_level_signature   >::flat_tuple;
};

template<typename ENTITY> struct entity_full_fct_signatures_iter<ENTITY,-1>
	{ using tuple = std::tuple<>; };

template<typename ENTITY> struct entity_full_fct_signatures;
template<template<typename>class... Cs> struct entity_full_fct_signatures<GenericEntity<Cs...>>
{
	using tuple = typename entity_full_fct_signatures_iter<GenericEntity<Cs...>,sizeof...(Cs)-1>::tuple;
	//FIXME-C++14 use the following line rather than the above one.
	//using tuple = typename entity_full_fct_signatures_iter<GenericEntity<Cs...>,table_of_components_size<GenericEntity<Cs...>>()-1>::tuple;
};


////////////////////////////////////////////////////////////////////////////////
// Definition of VirtualEntity<D,Cs...>                                       //
////////////////////////////////////////////////////////////////////////////////
// An entity, with a virtual method to get the function associated with the entity.
template<template<typename> class... Cs>
class VirtualEntity
{
};

////////////////////////////////////////////////////////////////////////////////
// Definition of DataEntity<D,Cs...>                                          //
// contains the tuple of each component (also tuples) as a static member      //
////////////////////////////////////////////////////////////////////////////////

template<typename D, template<typename> class... Cs>
class DataEntity : VirtualEntity<Cs...>
{
public:
	//FIXME put the table protected (though it is const...) and name friend the various tuple index computation devices.
	static std::tuple<decltype(Cs<D>::functions)*...> const components;
};
template<typename D, template<typename> class... Cs>
// FIXME initialization : make sure there is only one per compilation unit
std::tuple<decltype(Cs<D>::functions)*...> const DataEntity<D, Cs...>::components( &Cs<D>::functions... );

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


