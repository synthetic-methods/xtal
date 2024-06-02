#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::resource
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ..._s> XTAL_TYP biased;
template <typename ..._s> XTAL_USE biased_t = confined_t<biased<_s...>>;
template <typename ..._s> XTAL_ASK biased_q = bond::head_tag_p<biased, _s...>;


////////////////////////////////////////////////////////////////////////////////
///\
Provides a fixed amount of biased/behind determined from the constant provided \
(at any position in `As...`). \

template <typename ...As>
struct biased
{
	XTAL_USE U_bias = bond::seek_constant_t<As..., ordinal_t<0>>;

	using subkind = bond::compose<bond::tag<biased>, As...>;

	template <class S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;
		
	public:
		using S_::S_;
		
		template <class U=U_bias>
		XTAL_DEF_(return,inline)
		XTAL_FN1 bias()
		XTAL_0EX_TO_(static_cast<U>(U_bias {}))

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
