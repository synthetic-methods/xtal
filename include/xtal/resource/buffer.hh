#pragma once
#include "./any.hh"
#include "../atom/buffer.hh"





XTAL_ENV_(push)
namespace xtal::resource
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

XTAL_NEW buffer_a;
template <class ...Ts> concept buffer_q = bond::tab_p<buffer_a, Ts...>;


////////////////////////////////////////////////////////////////////////////////
///\
Provides a specialization of `atom::buffer`. \
If `N == -1`, the member-type `buffer_t` is dynamically allocated. \

template <int N=-1>
struct buffer
{
	using subkind = bond::tab<buffer_a>;
	
	template <_retail::any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;
		
	public:
		using S_::S_;
		
		template <class U>
		using buffer_t = atom::buffer_t<U[(unsigned) N]>;

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
