#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::occur
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class W=size_t>
struct sample
{
private:
	using re = bond::realize<W>;
	using U = typename re:: iota_t;
	using V = typename re::alpha_t;

	XTAL_LET_(U) U_1 = 1;
	XTAL_LET_(V) V_1 = 1;

public:
	using subkind = bond::compose<defer<U>, defer<V>>;

	template <any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;
		//\todo\
		Skip `head<1>` by inheriting `query<S_::template self_s<1>>`? \

	public:
	//	using S_::S_;
		
		XTAL_CO0_(subtype);
		XTAL_CO1_(subtype);
		XTAL_CO4_(subtype);

		XTAL_CXN subtype(integral_number_q auto n, auto &&...oo)
		XTAL_0EX
		:	S_(n, V_1/n, XTAL_REF_(oo)...)
		{}
		XTAL_CXN subtype(real_number_q auto u, auto &&...oo)
		XTAL_0EX
		:	S_(U_1/u, u, XTAL_REF_(oo)...)
		{}

		XTAL_TO4_(XTAL_TN2   rate(), S_::template head<0>())
		XTAL_TO4_(XTAL_TN2 period(), S_::template head<1>())

	};
};
template <class U=size_t>
using sample_t = confined_t<sample<U>>;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
