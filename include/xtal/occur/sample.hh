#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::occur
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class U=size_t> XTAL_TYP sample;
template <class U=size_t> XTAL_USE sample_t = confined_t<sample<U>>;
template <typename ..._s> XTAL_ASK sample_q = bond::head_tag_p<sample, _s...>;


//////////////////////////////////////////////////////////////////////////////////

template <class W>
struct sample
{
private:
	using _op = bond::operate<W>;
	using U = typename _op:: iota_t;
	using V = typename _op::alpha_t;

	static constexpr U U_1{1};
	static constexpr V V_1{1};

	using M = bond::pack_t<U, V>;

public:
	using subkind = bond::compose<defer<M>, bond::tag<sample>>;

	template <any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;

	public:
	//	using S_::S_;
		
		XTAL_CO0_(subtype);
	//	XTAL_CO1_(subtype);
		XTAL_CO4_(subtype);

		XTAL_CON_(implicit) subtype()
		XTAL_0EX
		:	subtype(1)
		{}
		XTAL_CON_(explicit) subtype(integral_number_q auto n, auto &&...oo)
		XTAL_0EX
		:	S_(M{n, 0 == n? 0: V_1/n}, XTAL_REF_(oo)...)
		{}
		XTAL_CON_(explicit) subtype(real_number_q auto u, auto &&...oo)
		XTAL_0EX
		:	S_(M{0 == u? 0: U_1/u, u}, XTAL_REF_(oo)...)
		{}

		XTAL_TO4_(XTAL_DEF_(return,inline) XTAL_REF   rate(), get<0>(S_::head()))
		XTAL_TO4_(XTAL_DEF_(return,inline) XTAL_REF period(), get<1>(S_::head()))

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
