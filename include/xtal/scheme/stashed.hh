#pragma once
#include "./any.hh"

#include "../atom/blob.hh"




XTAL_ENV_(push)
namespace xtal::scheme
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/*!
\brief
Provides local arena-like storage via `stash()` using `atom::blob`.
*/
template <typename ...Ts> struct   stashed;
template <typename ...Ts> using    stashed_t = confined_t<stashed<Ts...>>;
template <typename ..._s> concept  stashed_q = bond::tag_inner_p<stashed, _s...>;


////////////////////////////////////////////////////////////////////////////////

template <class ...Ts>
struct stashed
{
	using superkind = bond::compose<bond::tag<stashed>
	,	defer<atom::blob_t<Ts...>>
	>;
	template <cell::any_q S>
	class subtype : public bond::compose_s<S, superkind>
	{
		using S_ = bond::compose_s<S, superkind>;

	public:// CONSTRUCT
		using S_::S_;
		
	public:// ACCESS
		using S_::head;

		/*!
		\returns	The contents of `stash` as a tuple of `Vs &...`.
		*/
		XTAL_FN2_(to) (template <class ...Vs> requires variable_q<Vs...>
		XTAL_VAL_(return,inline,get) stash(), head().template form<Vs...>())
		
		/*!
		\returns	The contents of `stash` as a tuple of `Vs &...` prior to replacement with `vs...`.
		*/
		XTAL_FN2_(to) (template <class ...Vs> requires variable_q<Vs...>
		XTAL_VAL_(return,inline,get) stash(Vs const &...vs), head().form(vs...))
		
		template <auto u>
		XTAL_VAL_(inline,let) stash(                 ) noexcept -> void {head().fill(u  );}///< Clears/fills `stash` with the given `byte`.
		XTAL_VAL_(inline,let) stash(constant_t<>     ) noexcept -> void {head().fill(0  );}///< Clears/fills `stash` with the given `byte`.
		XTAL_VAL_(inline,let) stash(constant_q auto f) noexcept -> void {head().fill(f());}///< Clears/fills `stash` with the given `byte`.

	};
};
template <class ...Ts> requires (0 == sizeof...(Ts) or 0 == sizeof(std::tuple<Ts...>))
struct stashed<Ts...> : bond::compose<>
{
};

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
