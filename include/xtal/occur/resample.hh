#pragma once
#include "./any.hh"

#include "../atom/couple.hh"




XTAL_ENV_(push)
namespace xtal::occur
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class ..._s>	struct   resample;
template <class ..._s>	using    resample_t =  confined_t<resample<_s...>>;
template <class ..._s>	concept  resample_q = bond::tag_in_p<resample, _s...>;


//////////////////////////////////////////////////////////////////////////////////

template <typename ...As>
struct resample
{
	using U0 = typename bond::fit<>::alpha_type;
	using U2 = atom::couple_t<U0[2]>;

	using superkind = bond::compose<flow::tag<resample>, defer<U2>, As...>;

	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind>;

	public:// CONSTRUCT
	//	using S_::S_;
		
		XTAL_NEW_(delete) (subtype, noexcept=default)
//		XTAL_NEW_(create) (subtype, noexcept=default)
		XTAL_NEW_(move)   (subtype, noexcept=default)
		XTAL_NEW_(copy)   (subtype, noexcept=default)
		XTAL_NEW_(then)   (subtype, noexcept:subtype)
		XTAL_NEW_(else)   (subtype, noexcept:S_)

		XTAL_NEW_(explicit)
		subtype(number_q auto v, auto &&...oo)
		noexcept
		:	subtype{U2{static_cast<U0>(v), _std::in_place}, XTAL_REF_(oo)...}
		{}
		XTAL_NEW_(implicit)
		subtype()
		noexcept
		:	subtype{1}
		{}

	public:// OPERATE

		XTAL_DEF_(return,inline,set)
		sample_f(auto &&o, auto &&...oo)
		noexcept -> decltype(auto)
		{
			return XTAL_REF_(o).head(XTAL_REF_(oo)...);
		}
		XTAL_DEF_(return,inline,set)
		period_f(auto &&o, auto &&...oo)
		noexcept -> decltype(auto)
		{
			static_assert(0 == sizeof...(oo));
			return get<1>(sample_f(XTAL_REF_(o)));
		}
		XTAL_DEF_(return,inline,set)
		  rate_f(auto &&o, auto &&...oo)
		noexcept -> decltype(auto)
		{
			static_assert(0 == sizeof...(oo));
			return get<0>(sample_f(XTAL_REF_(o)));
		}
		XTAL_FN1_(go) (XTAL_DEF_(return,inline,get) sample, sample_f)
		XTAL_FN1_(go) (XTAL_DEF_(return,inline,get) period, period_f)
		XTAL_FN1_(go) (XTAL_DEF_(return,inline,get)   rate,   rate_f)

	};
};


////////////////////////////////////////////////////////////////////////////////

XTAL_DEF_(let) resample_f = [] XTAL_1FN_(call) (resample_t<>);


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
