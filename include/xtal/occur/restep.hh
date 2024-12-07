#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::occur
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <integer_q U=integer_type> struct   restep;
template <integer_q U=integer_type> using    restep_t = confined_t<restep<U>>;
template <typename ..._s> concept  restep_q = bond::any_tag_p<restep, _s...>;
XTAL_DEF_(short)
XTAL_LET restep_f(auto &&w)
noexcept -> auto
{
	using _op = bond::operate<decltype(w)>;
	return restep_t<typename _op::delta_type>(XTAL_REF_(w));
}


////////////////////////////////////////////////////////////////////////////////

template <integer_q U>
struct restep
{
	using superkind = bond::compose<defer<U>, bond::tag<restep>>;

	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind>;
	
	public:
		using S_::S_;
		using U_step = U;

		XTAL_TO4_(XTAL_DEF_(alias) step(auto &&...oo), S_::head(XTAL_REF_(oo)...))

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
