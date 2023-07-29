#pragma once
#include "./anybody.hpp"
#include "./phase.hpp"
#include "./pulse.hpp"




XTAL_ENV_(push)
namespace xtal::content
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <                typename ..._s> XTAL_NYM quark;
template <                typename ..._s> XTAL_ASK quark_q = tag_p<quark, _s...>;
template <class U=size_t, typename ...As> XTAL_USE quark_t = confined_t<quark<U>, As...>;


////////////////////////////////////////////////////////////////////////////////
///\
Pairs `pulse` and `phase` to represent e.g. `{phase/frequency, count/trigger}`. \

template <class U>
struct quark<U>
{
	using _computer = compute<U>;
	using delta_t = typename _computer::delta_t;
	using alpha_t = typename _computer::alpha_t;
	
	using subkind = compose<tag<quark>, pulse<delta_t>, phase<alpha_t>>;
	
	template <class S>
	class subtype: public compose_s<S, subkind>
	{
		using S_ = compose_s<S, subkind>;

	public:
		using S_::S_;
		using S_::self;

		XTAL_CON subtype(XTAL_DEF_(integral_group_q) o) XTAL_0EX: S_(XTAL_REF_(o), 0) {}
		XTAL_CON subtype(XTAL_DEF_(    real_field_q) o) XTAL_0EX: S_(0, XTAL_REF_(o)) {}

		XTAL_TO4_(XTAL_FN2 pulse(XTAL_DEF o), S_::template head<0>(XTAL_REF_(o)))
		XTAL_TO4_(XTAL_FN2 phase(XTAL_DEF o), S_::template head<1>(XTAL_REF_(o)))
	
		XTAL_DO4_(XTAL_OP0_(implicit) delta_t(), {return pulse();})
		XTAL_DO4_(XTAL_OP0_(implicit) alpha_t(), {return phase();})
	
	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
