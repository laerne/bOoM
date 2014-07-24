#ifndef HEADERBoOm_array_curry
#define HEADERBoOm_array_curry

#include <functional>

namespace bOoM {
using std::function;




template< typename Fct, typename... NewArgs > struct functionptr_append_arg;
template< typename Ret, typename... Args, typename... NewArgs > struct functionptr_append_arg< Ret(Args...), NewArgs... >
	{ using type = Ret(Args...,NewArgs...); };

template< typename Ret, typename Arg, int N> struct functionptr_repeat_arg
	{ using type = typename functionptr_append_arg< typename functionptr_repeat_arg<Ret,Arg,N-1>::type, Arg >::type; };
template< typename Ret, typename Arg> struct functionptr_repeat_arg<Ret,Arg,0>
	{ using type = Ret(); };

template<typename Fct> struct function_extract;
template<typename CFct> struct function_extract< std::function<CFct> >
	{ using type = CFct; };
//template<typename Fct, int N, typename... NewArgs> struct function_bind_but_N =
//	std::bind<

template< typename Ret, typename Arg, int N> using function_repeat =
	std::function<   typename functionptr_repeat_arg<Ret,Arg,N>::type   >;
template< typename Fct, typename... NewArgs> using function_append =
	std::function<   typename functionptr_append_arg< typename function_extract<Fct>::type, NewArgs... >::type   >;




template <unsigned int... Is> struct int_list
{
	using build = int_list<>;
};
template <unsigned int K, unsigned int... Is> struct int_list<K,Is...>
{
	using build = typename int_list<K-1,K,Is...>::build;
	using up_to = typename int_list<K-1>::build;
};
template <unsigned int... Is> struct int_list<0,Is...>
{
	using build = int_list<0,Is...>;
	using up_to = int_list<>;
};

template <typename Ret, typename Arg, typename IntList> struct array_curry_invoker;
template <typename Ret, typename Arg, unsigned int... Is> struct array_curry_invoker<Ret,Arg,int_list<Is...>>
{
	static inline Ret invoke( function_repeat<Ret,Arg const&,sizeof...(Is)> fct, std::array<Arg,sizeof...(Is)> const& args )
	{
		return fct( std::get<Is>(args)... );
	}
	template <typename ArgPtr>
	static inline Ret deref_invoke( function_repeat<Ret,Arg,sizeof...(Is)> fct, std::array<ArgPtr,sizeof...(Is)> const& args )
	{
		return fct( *std::get<Is>(args)... );
	}
};

} //namespace bOoM
#endif


