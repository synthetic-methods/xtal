#pragma once
#include "./any.ipp"






XTAL_ENV_(push)
namespace xtal::control
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

struct per
{
private:
	using U = unsigned_t<typename computer::iota_t>;
	using V = typename computer::alpha_t;

public:
	using subkind = compose<defer<U>, defer<V>>;

	template <any_q S>
	class subtype: public compose_s<S, subkind>
	{
		using S_ = compose_s<S, subkind>;

	public:
	//	using S_::S_;
		
		XTAL_CO0_(subtype);
		XTAL_CO4_(subtype);

		XTAL_CXN subtype(_std::integral auto n, XTAL_DEF ...oo)
		XTAL_0EX
		:	S_(n, (V) 1/V(n), XTAL_REF_(oo)...)
		{}
		XTAL_CXN subtype(_std::floating_point auto u, XTAL_DEF ...oo)
		XTAL_0EX
		:	S_((U) 1/V(u), u, XTAL_REF_(oo)...)
		{}

		XTAL_TO4_(XTAL_FN2   rate(), S_::template head<0>())
		XTAL_TO4_(XTAL_FN2 period(), S_::template head<1>())

	};
};
using per_t = confined_t<per>;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
