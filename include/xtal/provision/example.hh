#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::provision
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ..._s> struct   example;
template <typename ..._s> using    example_t = confined_t<example<_s...>>;
template <typename ..._s> concept  example_q = bond::tag_p<example, _s...>;


////////////////////////////////////////////////////////////////////////////////
///\
Provisional sample-rate/period `ex`port with implied scaling. \

///\todo\
Parameterise `sample` by decoration rather-than unit-type? \

template <typename ...As>
struct example
{
	using superkind = bond::compose<bond::tag<example>
	,	typename occur::sample_t<>::template attach<>
	,	As...
	>;
	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		static_assert(cell::any_q<S>);
		using S_ = bond::compose_s<S, superkind>;
		
	public:
		using S_::S_;
		
		XTAL_TO4_(XTAL_DEF sample(), S_::head())

	};
	template <class S> requires example_q<S>
	class subtype<S> : public bond::compose_s<S>
	{
		static_assert(cell::any_q<S>);
		using S_ = bond::compose_s<S, superkind>;
		
	public:
		using S_::S_;

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
