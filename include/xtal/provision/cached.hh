#pragma once
#include "./any.hh"

#include "../arrange/cache.hh"




XTAL_ENV_(push)
namespace xtal::provision
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
Provides local arena-like storage via `cache()`. \

template <typename ...As> struct   cached;
template <typename ...As> using    cached_t = confined_t<cached<As...>>;
template <typename ..._s> concept  cached_q = bond::any_tag_p<cached, _s...>;


////////////////////////////////////////////////////////////////////////////////

template <class ...As>
struct cached
{
	using superkind = bond::compose<bond::tag<cached>
	,	defer<arrange::cache_t<As...>>
	>;

	template <cell::any_q S>
	class subtype : public bond::compose_s<S, superkind>
	{
		using S_ = bond::compose_s<S, superkind>;
		
	public:// CONSTRUCT
		using S_::S_;
		
	public:// ACCESS
		using S_::head;

		XTAL_TO4_(XTAL_GET cache(), head())
		
		XTAL_TO4_(template <class ...Vs> requires some_q<Vs...>
		XTAL_GET cache(), head().template form<Vs...>())
		
		template <bite_type I>
		XTAL_DEF_(inline) XTAL_LET cache(           ) noexcept -> void {head().free(I);}
		XTAL_DEF_(inline) XTAL_LET cache(bite_type i) noexcept -> void {head().free(i);}

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
