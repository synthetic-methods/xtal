#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::resource
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ..._s> XTAL_TYP example;
template <typename ..._s> XTAL_USE example_t = confined_t<example<_s...>>;
template <typename ..._s> XTAL_REQ example_q = bond::any_tag_p<example, _s...>;


////////////////////////////////////////////////////////////////////////////////
///\
Provisional sample-rate/period `ex`port with implied scaling. \

///\todo\
Parameterise `sample` by decoration rather-than unit-type? \

template <typename ...As>
struct example
{
	using subkind = bond::compose<bond::tag<example>
	,	typename occur::sample_t<>::template attach<>
	,	As...
	>;
	template <compound::any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;
		
	public:
		using S_::S_;
		
		XTAL_TO4_(XTAL_DEF_(return,inline) XTAL_RET sample(), S_::head())

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
