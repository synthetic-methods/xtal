#pragma once
#include "./any.hh"
#include "../atom/spool.hh"





XTAL_ENV_(push)
namespace xtal::resource
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

XTAL_NEW spool_a;
template <class ...Ts> concept spool_q = bond::tab_p<spool_a, Ts...>;


////////////////////////////////////////////////////////////////////////////////
///\
Provides a specialization of `atom::spool`. \
If `N == -1`, the member-type `spool_t` is dynamically allocated. \

template <int N=-1>
struct spool
{
	using subkind = bond::tab<spool_a>;
	
	template <_retail::any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;
		
	public:
		using S_::S_;
		
		template <class U>
		using spool_t = atom::spool_t<U[(unsigned) N]>;

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
