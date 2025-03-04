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
		
		XTAL_NEW_(delete) (subtype, noexcept = default)
//		XTAL_NEW_(create) (subtype, noexcept = default)
		XTAL_NEW_(move)   (subtype, noexcept = default)
		XTAL_NEW_(copy)   (subtype, noexcept = default)
		XTAL_NEW_(cast)   (subtype, noexcept :        )
		XTAL_NEW_(then)   (subtype, noexcept : S_     )

		XTAL_NEW_(explicit)
		subtype(number_q auto v, auto &&...oo)
		noexcept
		:	subtype{U2(static_cast<U0>(v)), XTAL_REF_(oo)...}
		{}
		XTAL_NEW_(implicit)
		subtype()
		noexcept
		:	subtype{1}
		{}

	public:// OPERATE

		XTAL_FX4_(to) (XTAL_DEF_(return,inline,get)
		sample(), S_::head())

		XTAL_FX4_(to) (XTAL_DEF_(return,inline,get)   rate(), get<0>(S_::head()))
		XTAL_FX4_(to) (XTAL_DEF_(return,inline,get) period(), get<1>(S_::head()))

	};
};


////////////////////////////////////////////////////////////////////////////////

XTAL_DEF_(let) resample_f = [] XTAL_1FN_(call) (resample_t<>);


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
