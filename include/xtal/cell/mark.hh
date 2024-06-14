#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::cell
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
///\
Mediates access to the supertype.\

///\note\
Used to control access to an `address`d `attach`ment.\

///\see e.g. [../occur/any#attach] or [../occur/any#dispatch]. \

template <              class ..._s> XTAL_TYP mark;
template <              class ..._s> XTAL_REQ mark_q = bond::head_tag_p<mark, _s...>;
template <class Y,      class ..._s> XTAL_REQ mark_p = mark_q<_s...> and fungible_q<Y, _s...>;
template <class S=void, class ..._s> XTAL_USE mark_s = bond::compose_s<complete_t<S, confined_t<>>, confined<mark<_s...>>>;

template <>
struct mark<>
:	confer<size_t, bond::tag<mark>>
{
};
template <class U>
struct mark<U>
{
	using subkind = confer<U, bond::tag<mark>>;

	template <any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;
		using Y_ = mark_s<>;

	public:
		using S_::S_;

		XTAL_TO4_(XTAL_DEF_(return,inline)
		XTAL_CVN_(explicit) Y_(), Y_(S_::head())
		)

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
