#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::occur
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class U=void> struct        restep;
template <class U=void> using         restep_t =          confined_t<restep<U>>;
template <class  ..._s> concept       restep_q = un_n<0, bond::tag_p<restep, _s>...>;
template <class  ..._s> concept  some_restep_q = in_n<1, bond::tag_p<restep, _s>...>;

XTAL_DEF_(return,inline,let)   restep_f(auto &&w)
noexcept -> decltype(auto) {return restep_t<>(XTAL_REF_(w));}


////////////////////////////////////////////////////////////////////////////////

template <class U>
struct restep
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
		using step_type = U;
		XTAL_FX4_(alias) (XTAL_DEF_(return,inline,get) step(auto &&...oo), S_::head(XTAL_REF_(oo)...))

	};
};
template <>
struct restep<void>
:	restep<extent_type>
{
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
