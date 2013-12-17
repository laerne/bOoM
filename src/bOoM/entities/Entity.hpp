#ifndef H_entity
#define H_entity

#include <tuple>
#include "common/graphic.hpp"

namespace bOoM {

// ! WARNING !
// The following code is for advanced level C++ programmers.
// It is a quite straightforward mix of the non-trivial ''Type Erasure'' pattern, variadic template and curiously
// recurring template.  Make sure you have an in-depth understanding of how those concepts works before trying to
// undestand the following code.
// 
// You may also which to see the chart "EntityUML.odg" to see how class behave one to the other.
// The names are change in the files, as following~:
// * GE for GenericEntity
// * EE for ErasedEntity
// * UE for UnerasedEntity
// * Beta for ComponentWithData
// * Gamma for ComponentImplementation
// * Delta for ExecutableComponent


template<typename D, class C>
struct ComponentWithData : virtual C
{
	virtual D& data() = 0;
	virtual D const& data() const = 0;
};

template<typename D, class C>
struct ComponentImplementation : ComponentWithData<D,C>
{
};

template<typename D, class C, typename UnerasedEntity_D_Cs>
struct ExecutableComponent : ComponentImplementation<D, C>
{
	virtual D& data()
		{ return static_cast<UnerasedEntity_D_Cs*>(this)->data_; }
	virtual D const& data() const
		{ return static_cast<UnerasedEntity_D_Cs const*>(this)->data_; }
};

template<class... Cs> struct ErasedEntity;
template<> struct ErasedEntity<> {};
template<class C0, class... Cs>
struct ErasedEntity<C0, Cs...> : virtual C0, virtual ErasedEntity<Cs...>
{};

template<typename D, class... Cs>
struct UnerasedEntity;

template<typename D>
struct UnerasedEntity<D> : virtual ErasedEntity<>
{
	UnerasedEntity(D const&& initialData)
		: data_(std::forward<D const&&>(initialData)) {}
	UnerasedEntity(D const& initialData)
		: data_(std::forward<D const&>(initialData)) {}
	D data_;
};

template<typename D, class C0, class... Cs>
struct UnerasedEntity<D, C0, Cs...> : ExecutableComponent<D,C0,UnerasedEntity<D, C0, Cs...>>, virtual ErasedEntity<C0, Cs...>, UnerasedEntity<D, Cs...>
{
	UnerasedEntity(D const&& initialData)
		: UnerasedEntity<D, Cs...>(std::forward<D const&&>(initialData)) {}
	UnerasedEntity(D const& initialData)
		: UnerasedEntity<D, Cs...>(std::forward<D const&>(initialData)) {}
};

template<class... Cs>
struct GenericEntity
{
	template<typename D>
	GenericEntity(D const&& initialData)
		: ptr( new UnerasedEntity<D,Cs...>(std::forward<D const&&>(initialData)) ) {}
	template<typename D>
	GenericEntity(D const& initialData)
		: ptr( new UnerasedEntity<D,Cs...>(std::forward<D const&>(initialData)) ) {}
	ErasedEntity<Cs...>* ptr;
};

//This is the entity with standard bOoM components.
using Entity = GenericEntity<graphic::Renderable>;

} //namespace bOoM
#endif


