#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::resource
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
///\
Represents a local `{store,state}` pair, \
used as e.g. a buffer and its abstract/copyable `std::span`. \

template <typename ..._s> XTAL_TYP restash;
template <typename ..._s> XTAL_USE restash_t = confined_t<restash<_s...>>;
template <typename ..._s> XTAL_ASK restash_q = bond::tag_head_p<restash, _s...>;
template <bounded_q U_state, bounded_q U_store>
struct restash<U_state, U_store>
{
	using subkind = bond::compose<bond::tag<restash>
	,	cell::refer<U_state>
	,	cell::defer<U_state>
	,	cell::defer<U_store>
	>;

	template <class S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;

	public:
	//	using S_::S_;
		using S_::self;
		
		XTAL_CO0_(subtype)
	//	XTAL_CO1_(subtype)
		XTAL_CO4_(subtype)
	
		XTAL_CON subtype()
		XTAL_0EX
		:	subtype(U_store())
		{}
		XTAL_CXN subtype(auto &&...oo)
		XTAL_0EX
		:	subtype(U_store(), XTAL_REF_(oo)...)
		{}
		
		XTAL_CXN subtype(U_store o, auto &&...oo)
		XTAL_0EX
		:	S_(U_state(o), XTAL_MOV_(o), XTAL_REF_(oo)...)
		{}
		XTAL_TN0 store(U_store o, auto &&...oo)
		XTAL_0EX
		{
			self(U_state(o), XTAL_MOV_(o), XTAL_REF_(oo)...);
		}
		XTAL_TO4_(XTAL_TN2 store(), S_::template head<1>())
		XTAL_TO4_(XTAL_TN2 state(auto &&...oo), S_::template head<0>(XTAL_REF_(oo)...))

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
