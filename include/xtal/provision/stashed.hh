#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::provision
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
Associates an abstract state/view with an underlying store. \

template <typename ..._s> struct   stashed;
template <typename ..._s> using    stashed_t = confined_t<stashed<_s...>>;
template <typename ..._s> concept  stashed_q = bond::tag_p<stashed, _s...>;


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
		
	~	subtype()                 noexcept=default;
	//	subtype()                 noexcept=default;
		XTAL_NEW_(copy) (subtype, noexcept=default)
		XTAL_NEW_(move) (subtype, noexcept=default)
		XTAL_NEW_(auto) (subtype, noexcept)
	
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
		XTAL_DEF_(inline,let)
		store(U_store o, auto &&...oo)
		noexcept -> void
		{
			self(U_state(o), XTAL_MOV_(o), XTAL_REF_(oo)...);
		}
		XTAL_FX4_(alias) (XTAL_DEF_(return,inline,get) store(), S_::template head<1>())
		XTAL_FX4_(alias) (XTAL_DEF_(return,inline,get) state(auto &&...oo), S_::template head<0>(XTAL_REF_(oo)...))

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
