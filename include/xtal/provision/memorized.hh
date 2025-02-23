#pragma once
#include "./any.hh"

#include "../atom/blob.hh"




XTAL_ENV_(push)
namespace xtal::provision
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
Provides local blob-like storage via `memory()` using `atom::blob`. \

template <typename ...As> struct   memorized;
template <typename ...As> using    memorized_t = confined_t<memorized<As...>>;
template <typename ..._s> concept  memorized_q = bond::tag_p<memorized, _s...>;


////////////////////////////////////////////////////////////////////////////////

template <class ...As>
struct memorized
{
	using superkind = bond::compose<bond::tag<memorized>
	,	defer<atom::blob_t<As...>>
	>;
	template <cell::any_q S>
	class subtype : public bond::compose_s<S, superkind>
	{
		using S_ = bond::compose_s<S, superkind>;

	public:// CONSTRUCT
		using S_::S_;
		
	public:// ACCESS
		using S_::head;

		///\returns the contents of `memory` as a tuple of `Vs &...`. \

		XTAL_FX4_(to) (template <class ...Vs> requires variable_q<Vs...>
		XTAL_DEF_(return,inline,get) memory(), head().template form<Vs...>())
		
		///\returns the contents of `memory` as a tuple of `Vs &...`, \
		prior to replacing the contents with `vs...`. \

		XTAL_FX4_(to) (template <class ...Vs> requires variable_q<Vs...>
		XTAL_DEF_(return,inline,get) memory(Vs const &...vs), head().form(vs...))
		
		///\
		Fills `memory` with the given `byte` value. \

		template <auto u>
		XTAL_DEF_(inline,let) memory(                 ) noexcept -> void {head().fill(u);}
		XTAL_DEF_(inline,let) memory(constant_t<>     ) noexcept -> void {head().fill(0);}
		XTAL_DEF_(inline,let) memory(constant_q auto f) noexcept -> void {head().fill(f());}

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
