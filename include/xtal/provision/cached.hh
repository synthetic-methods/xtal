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
		using I  = _std::underlying_type_t<_std::byte>;

	public:// CONSTRUCT
		using S_::S_;
		
	public:// ACCESS
		using S_::head;

		XTAL_TO4_(XTAL_DEF_(alias) cache(), head())
		
		XTAL_TO4_(template <class ...Vs> requires (1 <= sizeof...(Vs))
		XTAL_DEF_(alias) cache(), head().template form<Vs...>())
		
		template <I i>
		XTAL_DEF_(inline) XTAL_LET cache(   ) noexcept -> void {head().fill(i);}
		XTAL_DEF_(inline) XTAL_LET cache(I i) noexcept -> void {head().fill(i);}

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
