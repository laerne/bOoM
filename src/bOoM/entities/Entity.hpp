#ifndef H_entity
#define H_entity

#include <tuple>
#include "common/graphic.hpp"

namespace bOoM {

/***********
 * WARNING *
 ***********/
// The following code is for advanced level C++ programmers.
// It is a quite straightforward mix of the non-trivial ''Type Erasure'' pattern, template templates and variadic template concept.
// Make sure you have an in-depth understanding of how the Type Erasure pattern, template templates and the variadic templates work
// before trying to undestand the following code

template<typename DataType, template<typename> class... Components>
struct ComponentPack;

template<typename DataType, template<typename> class Component0, template<typename> class... Components>
struct ComponentPack<DataType, Component0, Components...> : Component0<DataType>, ComponentPack<DataType, Components...>
{};

template<typename DataType>
struct ComponentPack<DataType>
{};

//This is the common interface to all entity tuple
template< template<typename> class... Components >
struct ErasedEntity : public ComponentPack<void, Components...>
{
public:
	//TODO interface
};

//This is the template tuple of a datatype and a component
template<typename DataType, template<typename> class... Components >
//How to specify "Component0<DataType>, Component1<DataType>, Component2<Datatype>, ..."
struct UnerasedEntity : public ErasedEntity<Components...>, public ComponentPack<DataType, Components...>
{
public:
	UnerasedEntity( DataType const&& data )
		: data(std::forward<DataType const&&>(data)) {}
protected:
	DataType data;
};

//This is the pointer towards the intanciated UnerasedEntity so that the interface ErasedEntity can be virtual.
template< template<typename> class... Components >
struct GenericEntity
{
public:
	template <typename DataType>
	GenericEntity( DataType const&& data )
		: ptr( new UnerasedEntity<DataType,Components...>(std::forward<DataType const&&>(data)) ) {}
//protected:
	ErasedEntity<Components...>* ptr;
};

//This is the entity with standard bOoM components.
using Entity = GenericEntity<graphic::Renderable>;

} //namespace bOoM
#endif


