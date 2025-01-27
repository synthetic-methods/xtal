#pragma once
#include "./any.hh"

#include "../atom/cache.hh"




XTAL_ENV_(push)
namespace xtal::provision
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
Provides local arena-like storage via `stow()` using `atom::cache`. \

template <typename ...As> struct   stowed;
template <typename ...As> using    stowed_t = confined_t<stowed<As...>>;
template <typename ..._s> concept  stowed_q = bond::tag_p<stowed, _s...>;


////////////////////////////////////////////////////////////////////////////////

template <class ...As>
struct stowed
{
	using superkind = bond::compose<bond::tag<stowed>
	,	defer<atom::cache_t<As...>>
	>;
	template <cell::any_q S>
	class subtype : public bond::compose_s<S, superkind>
	{
		using S_ = bond::compose_s<S, superkind>;
		using U  = _std::underlying_type_t<_std::byte>;

	public:// CONSTRUCT
		using S_::S_;
		
	public:// ACCESS
		using S_::head;

		XTAL_FX4_(alias) (XTAL_DEF_(return,inline,get) stow(), head())
		
		XTAL_FX4_(alias) (template <variable_q ...Vs> requires (1 <= sizeof...(Vs))
		XTAL_DEF_(return,inline,get) stow(), head().template form<Vs...>())
		
		XTAL_FX4_(alias) (template <variable_q ...Vs> requires (1 <= sizeof...(Vs))
		XTAL_DEF_(return,inline,get) stow(Vs const &...vs), head().form(vs...))
		
		template <         U u> XTAL_DEF_(inline,let) stow( ) noexcept -> void {head().fill(u       );}
		template <constant_q I> XTAL_DEF_(inline,let) stow(I) noexcept -> void {head().fill(I::value);}

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
