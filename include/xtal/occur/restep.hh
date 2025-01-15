#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::occur
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class U=typename bond::operating::delta_type> struct   restep;
template <class U=typename bond::operating::delta_type> using    restep_t =  confined_t<restep<U>>;
template <     typename ...Qs> concept  restep_q = bond::tag_p<restep, Qs...>;

XTAL_DEF_(let) restep_f(auto &&w)
noexcept {return restep_t<typename bond::operate<decltype(w)>::delta_type>(XTAL_REF_(w));}


////////////////////////////////////////////////////////////////////////////////

template <class U>
struct restep
{
	static_assert(integral_variable_q<U>);

	using superkind = bond::compose<flux::tag<restep>, defer<U>>;

	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind>;
	
	public:// CONSTRUCT
		using S_::S_;

	public:// ACCESS
		using step_type = U;
		XTAL_TO4_(XTAL_DEF_(let) step(auto &&...oo), S_::head(XTAL_REF_(oo)...))

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
