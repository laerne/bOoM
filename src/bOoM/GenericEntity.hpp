#ifndef HEADERBoOm__GenericEntity
#define HEADERBoOm__GenericEntity

#include <memory>

namespace bOoM {
using std::shared_ptr;

// ! WARNING !
// The following code is for advanced level C++ programmers.
// It is a quite straightforward mix of the non-trivial ''Type Erasure'' pattern, variadic template and curiously
// recurring template.  Make sure you have an in-depth understanding of how those concepts works before trying to
// undestand the following code.
// 
// You may also which to see the chart "EntityUML.odg" to see how class behave one to the other.
// The names are abbreviated in the files, as follow :
// * GE for GenericEntity
// * EE for ErasedEntity
// * UE for UnerasedEntity
// * CWD for ComponentWithData
// * CI for ComponentImplementation


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

template<class... Cs>
struct ErasedEntity : virtual Cs...
{};

template<typename D, class... Cs>
struct UnerasedEntity : ComponentImplementation<D,Cs>..., ErasedEntity<Cs...>
{
	UnerasedEntity(D const&& initialData)
		: data_(std::forward<D const&&>(initialData)) {}
	UnerasedEntity(D const& initialData)
		: data_(std::forward<D const&>(initialData)) {}
	virtual D& data()
		{ return static_cast<UnerasedEntity<D,Cs...>*>(this)->data_; }
	virtual D const& data() const
		{ return static_cast<UnerasedEntity<D,Cs...> const*>(this)->data_; }
	D data_;
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
	GenericEntity(GenericEntity<Cs...> const& other)
		: ptr( std::forward<shared_ptr<ErasedEntity<Cs...>>&>(other.ptr) ) {}
	GenericEntity(GenericEntity<Cs...> const&& other)
		: ptr( std::forward<shared_ptr<ErasedEntity<Cs...>>&&>(other.ptr) ) {}
	GenericEntity& operator=(GenericEntity<Cs...> const& other)
		{ ptr = std::forward<shared_ptr<ErasedEntity<Cs...>>&> (other.ptr) ; }
	GenericEntity& operator=(GenericEntity<Cs...> const&& other)
		{ ptr = std::forward<shared_ptr<ErasedEntity<Cs...>>&&> (other.ptr) ; }
	ErasedEntity<Cs...>& operator*()
		{ return ptr.operator*(); }
	ErasedEntity<Cs...>& operator->()
		{ return ptr.operator->(); }
		
	shared_ptr<ErasedEntity<Cs...>> ptr;
};



} //namespace bOoM
#endif


