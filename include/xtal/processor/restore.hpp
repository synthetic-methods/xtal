#pragma once
#include "./any.hpp"






XTAL_ENV_(push)
namespace xtal::processor
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

XTAL_NYM T_restore;
template <class ...Ts> concept restore_q = tab_p<T_restore, Ts...>;


////////////////////////////////////////////////////////////////////////////////
///\
Provides the type `store` as a specialization of `fluid::sluice`. \
If `N == 0` the `store` is allocated dynamically. \

template <size_t N=0>
struct restore
{
	using subkind = tab<T_restore>;
	
	template <any_q S>
	class subtype: public compose_s<S, subkind>
	{
		using S_ = compose_s<S, subkind>;
		
	public:
		using S_::S_;
		
		template <class U>
		using store = fluid::sluice<U[N]>;

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
