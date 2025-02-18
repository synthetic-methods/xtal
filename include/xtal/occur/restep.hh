#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::occur
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class ..._s> struct   restep;
template <class ..._s> using    restep_t =  confined_t<restep< _s...>>;
template <class ..._s> concept  restep_q = bond::tag_p<restep, _s...> ;

XTAL_FX0_(to) (XTAL_DEF_(return,inline,let)
restep_f  (auto &&...oo),
restep_t<>(XTAL_REF_(oo)...))


////////////////////////////////////////////////////////////////////////////////

template <class U>
struct restep<U>
{
	static_assert(integral_variable_q<U>);

	using superkind = bond::compose<flow::tag<restep>, defer<U>>;

	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind>;
	
	public:// CONSTRUCT
		using S_::S_;

	public:// ACCESS
		using S_::self;
		using S_::head;

		using step_type = U;

		XTAL_FX4_(to) (XTAL_DEF_(return,inline,get)
		step(auto &&...oo), head(XTAL_REF_(oo)...))

	};
};
template <> struct restep<void> : restep<extent_type> {};
template <> struct restep<    > : restep<extent_type> {};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
