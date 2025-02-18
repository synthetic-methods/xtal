#pragma once
#include "./any.hh"

#include "../atom/tee.hh"




XTAL_ENV_(push)
namespace xtal::occur
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class ..._s>	struct   resample;
template <class ..._s>	using    resample_t =  confined_t<resample<_s...>>;
template <class ..._s>	concept  resample_q = bond::tag_p<resample, _s...>;

template <class ..._s>
XTAL_FX0_(to) (XTAL_DEF_(return,inline,let)
resample_f       (auto &&...oo),
resample_t<_s...>(XTAL_REF_(oo)...))


//////////////////////////////////////////////////////////////////////////////////

template <typename ...As>
struct resample
{
	using W = atom::tee_t<>;
	using U = typename W::value_type;

	using superkind = bond::compose<flow::tag<resample>, defer<W>, As...>;

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
		XTAL_NEW_(cast)   (subtype, noexcept)

		XTAL_NEW_(explicit)
		subtype(auto &&...oo)
		noexcept
		:	S_{XTAL_REF_(oo)...}
		{}
		XTAL_NEW_(explicit)
		subtype(U u, auto &&...oo)
		noexcept
		:	subtype{W{u, one/u}, XTAL_REF_(oo)...}
		{}
		XTAL_NEW_(explicit)
		subtype(number_q auto v, auto &&...oo)
		noexcept
		:	subtype{static_cast<U>(v), XTAL_REF_(oo)...}
		{}
		XTAL_NEW_(implicit)
		subtype()
		noexcept
		:	subtype{1}
		{}

	public:// OPERATE

		XTAL_FX4_(to) (XTAL_DEF_(return,inline,get)
		sample(), S_::head())

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
