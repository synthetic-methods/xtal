#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::provision
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/*!
Provides `bias()` determined from the constant provided within `As...`.
*/
template <typename ..._s> struct   biased;
template <typename ..._s> using    biased_t = confined_t<biased<_s...>>;
template <typename ..._s> concept  biased_q = bond::tag_in_p<biased, _s...>;


////////////////////////////////////////////////////////////////////////////////

template <typename ...As>
struct biased
{
	using    U_bias = bond::seek_constant_t<As..., constant_t<0>>;

	using superkind = bond::compose<bond::tag<biased>, As...>;

	template <cell::any_q S>
	class subtype : public bond::compose_s<S, superkind>
	{
		using S_ = bond::compose_s<S, superkind>;
		
	public:
		using S_::S_;
		
		template <class U=U_bias>
		XTAL_DEF_(return,inline,set)
		bias()
		noexcept -> auto
		{
			return static_cast<U>(U_bias{});
		}

	};
};


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
