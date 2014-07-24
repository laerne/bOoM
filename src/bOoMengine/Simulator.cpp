#include "Simulator.hpp"
#include "array_curry.hpp"

namespace bOoM {


//template<typename Ret, typename Arg, unsigned int N> Ret call_with_n_args()

template <unsigned int N> void JobN<N>::work()
{
	array_curry_invoker< void, Entity, typename int_list<N>::up_to >::deref_invoke( fct, entities );
}


template class JobN<0>;
template class JobN<1>;
template class JobN<2>;
template class JobN<3>;
template class JobN<4>;

} //namespace bOoM

