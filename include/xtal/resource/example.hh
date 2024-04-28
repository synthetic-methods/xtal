#pragma once
#include "./any.hh"
#include "../atom/store.hh"





XTAL_ENV_(push)
namespace xtal::resource
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ..._s> XTAL_TYP example;
template <typename ..._s> XTAL_USE example_t = confined_t<example<_s...>>;
template <typename ..._s> XTAL_ASK example_q = bond::tag_p<example, _s...>;


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
	template <class S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;
		
	public:
		using S_::S_;
		
		XTAL_TO4_(XTAL_TN2 sample(), S_::head())

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
