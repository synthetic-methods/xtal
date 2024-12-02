#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::occur
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class U=size_type> XTAL_TYP sample;
template <class U=size_type> XTAL_USE sample_t = confined_t<sample<U>>;
template <typename ..._s> XTAL_ASK sample_q = bond::any_tag_p<sample, _s...>;


//////////////////////////////////////////////////////////////////////////////////

template <class W>
struct sample
{
private:
	using _op = bond::operate<W>;
	using U = typename _op:: iota_type;
	using V = typename _op::alpha_type;

	static constexpr U U_1{1};
	static constexpr V V_1{1};

	using M = bond::pack_t<U, V>;

public:
	using superkind = bond::compose<defer<M>, bond::tag<sample>>;

	template <any_q S>
	class subtype : public bond::compose_s<S, superkind>
	{
		using S_ = bond::compose_s<S, superkind>;

	public:
	//	using S_::S_;
		
		XTAL_CO0_(subtype);
	//	XTAL_CO1_(subtype);
		XTAL_CO4_(subtype);

		template <fungible_q<subtype> O>
		XTAL_NEW_(explicit) subtype(O &&o)
		noexcept
		:	subtype(static_cast<subtype &&>(XTAL_REF_(o)))
		{}

		XTAL_NEW_(implicit) subtype()
		noexcept
		:	subtype(1)
		{}
		XTAL_NEW_(explicit) subtype(    real_number_q auto u, auto &&...oo)
		noexcept
		:	S_(M{0 == u? 0: U_1/u, u}, XTAL_REF_(oo)...)
		{}
		XTAL_NEW_(explicit) subtype(integral_number_q auto n, auto &&...oo)
		noexcept
		:	S_(M{n, 0 == n? 0: V_1/n}, XTAL_REF_(oo)...)
		{}

		XTAL_TO4_(XTAL_DEF_(return,inline) XTAL_RET   rate(), get<0>(S_::head()))
		XTAL_TO4_(XTAL_DEF_(return,inline) XTAL_RET period(), get<1>(S_::head()))

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
