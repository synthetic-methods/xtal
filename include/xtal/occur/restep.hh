#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::occur
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <integral_number_q U=size_s> XTAL_TYP restep;
template <integral_number_q U=size_s> XTAL_USE restep_t = confined_t<restep<U>>;
template <typename ..._s> XTAL_ASK restep_q = bond::head_tag_p<restep, _s...>;
XTAL_FN2 restep_f(auto &&w)
XTAL_0EX
{
	using op = bond::operate<decltype(w)>;
	return restep_t<typename op::delta_t>(XTAL_REF_(w));
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

		XTAL_TO4_(XTAL_TN2 step(auto &&...oo), S_::head(XTAL_REF_(oo)...))

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
