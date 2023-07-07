#pragma once
#include "./any.hpp"






XTAL_ENV_(push)
namespace xtal::control
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

struct per
{
private:
	using U = _std::make_unsigned_t<typename realized::iota_t>;
	using V = typename realized::alpha_t;

public:
	using subkind = compose<defer<U>, defer<V>>;

	template <any_p S>
	class subtype: public compose_s<S, subkind>
	{
		using S_ = compose_s<S, subkind>;

	public:
	//	using S_::S_;
		
		XTAL_CO0_(subtype);
		XTAL_CO4_(subtype);

		XTAL_CXN subtype(XTAL_DEF_(iota_q) n, XTAL_DEF ...ws)
		XTAL_0EX
		:	S_(n, (V) 1/V(XTAL_REF_(n)), XTAL_REF_(ws)...)
		{
		}
		XTAL_CXN subtype(XTAL_DEF_(alpha_q) u, XTAL_DEF ...ws)
		XTAL_0EX
		:	S_((U) 1/V(XTAL_REF_(u)), u, XTAL_REF_(ws)...)
		{
		}

		XTAL_TO4_(XTAL_FN2   rate(), S_::template head<0>())
		XTAL_TO4_(XTAL_FN2 period(), S_::template head<1>())

	};
};
using per_t = confined_t<per>;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
