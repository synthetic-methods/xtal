#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::provision
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/*!
\brief
Associates an abstract view with underlying storage.
*/
template <typename ..._s> struct   stowed;
template <typename ..._s> using    stowed_t = confined_t<stowed<_s...>>;
template <typename ..._s> concept  stowed_q = bond::tag_in_p<stowed, _s...>;


////////////////////////////////////////////////////////////////////////////////

template <iterable_q U_state, iterable_q U_store>
struct stowed<U_state, U_store>
{
	using superkind = bond::compose<bond::tag<stowed>
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
		
		XTAL_NEW_(delete) (subtype, noexcept=default)
//		XTAL_NEW_(create) (subtype, noexcept=default)
		XTAL_NEW_(move)   (subtype, noexcept=default)
		XTAL_NEW_(copy)   (subtype, noexcept=default)
		XTAL_NEW_(then)   (subtype, noexcept:subtype)
	//	XTAL_NEW_(else)   (subtype, noexcept:S_)
	
		XTAL_NEW_(implicit)
		subtype()
		noexcept
		:	subtype{U_store()}
		{}
		XTAL_NEW_(explicit)
		subtype(auto &&...oo)
		noexcept
		:	subtype{U_store(), XTAL_REF_(oo)...}
		{}
		XTAL_NEW_(explicit)
		subtype(U_store o, auto &&...oo)
		noexcept
		:	S_{U_state(o), XTAL_MOV_(o), XTAL_REF_(oo)...}
		{}

		XTAL_DEF_(inline,let)
		store(U_store o, auto &&...oo)
		noexcept -> void
		{
			self(U_state(o), XTAL_MOV_(o), XTAL_REF_(oo)...);
		}
		XTAL_FX4_(to) (XTAL_DEF_(return,inline,get) store(), S_::template head<1>())
		XTAL_FX4_(to) (XTAL_DEF_(return,inline,get) state(auto &&...oo), S_::template head<0>(XTAL_REF_(oo)...))

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
