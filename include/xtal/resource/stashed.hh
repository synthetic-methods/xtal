#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::resource
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
///\
Associates an abstract state/view with an underlying store. \

template <typename ..._s> XTAL_TYP stashed;
template <typename ..._s> XTAL_USE stashed_t = confined_t<stashed<_s...>>;
template <typename ..._s> XTAL_ASK stashed_q = bond::head_tag_p<stashed, _s...>;
template <bounded_q U_state, bounded_q U_store>
struct stashed<U_state, U_store>
{
	using subkind = bond::compose<bond::tag<stashed>
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
	
		XTAL_CON_(implicit) subtype()
		XTAL_0EX
		:	subtype(U_store())
		{}
		XTAL_CON_(explicit) subtype(auto &&...oo)
		XTAL_0EX
		:	subtype(U_store(), XTAL_REF_(oo)...)
		{}
		
		XTAL_CON_(explicit) subtype(U_store o, auto &&...oo)
		XTAL_0EX
		:	S_(U_state(o), XTAL_MOV_(o), XTAL_REF_(oo)...)
		{}
		XTAL_LET store(U_store o, auto &&...oo)
		XTAL_0EX -> void
		{
			self(U_state(o), XTAL_MOV_(o), XTAL_REF_(oo)...);
		}
		XTAL_TO4_(XTAL_DEF_(return,inline) XTAL_REF store(), S_::template head<1>())
		XTAL_TO4_(XTAL_DEF_(return,inline) XTAL_REF state(auto &&...oo), S_::template head<0>(XTAL_REF_(oo)...))

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
