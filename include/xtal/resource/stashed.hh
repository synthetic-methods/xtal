#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::resource
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
Associates an abstract state/view with an underlying store. \

template <typename ..._s> XTAL_TYP stashed;
template <typename ..._s> XTAL_USE stashed_t = confined_t<stashed<_s...>>;
template <typename ..._s> XTAL_ASK stashed_q = bond::any_tag_p<stashed, _s...>;


////////////////////////////////////////////////////////////////////////////////

template <iterable_q U_state, iterable_q U_store>
struct stashed<U_state, U_store>
{
	using superkind = bond::compose<bond::tag<stashed>
	,	cell::refer<U_state>
	,	cell::defer<U_state>
	,	cell::defer<U_store>
	>;
	template <cell::any_q S>
	class subtype : public bond::compose_s<S, superkind>
	{
		using S_ = bond::compose_s<S, superkind>;

	public:
	//	using S_::S_;
		using S_::self;
		
		XTAL_CO0_(subtype)
	//	XTAL_CO1_(subtype)
		XTAL_CO4_(subtype)
	
		template <fungible_q<subtype> O>
		XTAL_NEW_(explicit) subtype(O &&o)
		noexcept
		:	subtype(static_cast<subtype &&>(XTAL_REF_(o)))
		{}

		XTAL_NEW_(implicit) subtype()
		noexcept
		:	subtype(U_store())
		{}
		XTAL_NEW_(explicit) subtype(auto &&...oo)
		noexcept
		:	subtype(U_store(), XTAL_REF_(oo)...)
		{}
		
		XTAL_NEW_(explicit) subtype(U_store o, auto &&...oo)
		noexcept
		:	S_(U_state(o), XTAL_MOV_(o), XTAL_REF_(oo)...)
		{}
		XTAL_LET store(U_store o, auto &&...oo)
		noexcept -> void
		{
			self(U_state(o), XTAL_MOV_(o), XTAL_REF_(oo)...);
		}
		XTAL_TO4_(XTAL_DEF_(return,inline) XTAL_RET store(), S_::template head<1>())
		XTAL_TO4_(XTAL_DEF_(return,inline) XTAL_RET state(auto &&...oo), S_::template head<0>(XTAL_REF_(oo)...))

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
