#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::occur
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <integral_number_q U=integral_type> XTAL_TYP restep;
template <integral_number_q U=integral_type> XTAL_USE restep_t = confined_t<restep<U>>;
template <typename ..._s> XTAL_REQ restep_q = bond::any_tag_p<restep, _s...>;
XTAL_DEF_(return,inline)
XTAL_LET restep_f(auto &&w)
XTAL_0EX
{
	using _op = bond::operate<decltype(w)>;
	return restep_t<typename _op::delta_t>(XTAL_REF_(w));
}


////////////////////////////////////////////////////////////////////////////////

template <integral_number_q U>
struct restep
{
	using subkind = bond::compose<defer<U>, bond::tag<restep>>;

	template <any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;
	
	public:
		using S_::S_;
		using U_step = U;

		XTAL_TO4_(XTAL_DEF_(return,inline) XTAL_RET step(auto &&...oo), S_::head(XTAL_REF_(oo)...))

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
