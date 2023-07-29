#pragma once
#include "./any.hpp"






XTAL_ENV_(push)
namespace xtal::processor
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

XTAL_NYM T_restash;
template <class ...Ts> concept restash_q = tab_p<T_restash, Ts...>;


////////////////////////////////////////////////////////////////////////////////
///\
Provides the type `stash` as a specialization of `fluid::siphon`. \
If `N == 0` the `stash` is allocated dynamically. \

template <size_t N=0>
struct restash
{
	using subkind = tab<T_restash>;
	
	template <any_q S>
	class subtype: public compose_s<S, subkind>
	{
		using S_ = compose_s<S, subkind>;
		
	public:
		using S_::S_;
		
		template <class U>
		using stash = fluid::siphon<U[N]>;

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)