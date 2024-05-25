#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::occur
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class U=size_t> XTAL_TYP sample;
template <class U=size_t> XTAL_USE sample_t = confined_t<sample<U>>;
template <typename ..._s> XTAL_ASK sample_q = bond::tag_p<sample, _s...>;


//////////////////////////////////////////////////////////////////////////////////

template <class W>
struct sample
{
private:
	using op = bond::operate<W>;
	using U = typename op:: iota_t;
	using V = typename op::alpha_t;

	XTAL_LET_(U) U_1 = 1;
	XTAL_LET_(V) V_1 = 1;

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

		XTAL_CON subtype()
		XTAL_0EX
		:	subtype(1)
		{}
		XTAL_CXN subtype(integral_number_q auto n, auto &&...oo)
		XTAL_0EX
		:	S_(M{n, 0 == n? 0: V_1/n}, XTAL_REF_(oo)...)
		{}
		XTAL_CXN subtype(real_number_q auto u, auto &&...oo)
		XTAL_0EX
		:	S_(M{0 == u? 0: U_1/u, u}, XTAL_REF_(oo)...)
		{}

		XTAL_TO4_(XTAL_TN2   rate(), get<0>(S_::head()))
		XTAL_TO4_(XTAL_TN2 period(), get<1>(S_::head()))

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
