#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::scheme
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/*!
\brief
Associates an abstract view with underlying storage.
*/
template <typename ..._s> struct   stowed;
template <typename ..._s> using    stowed_t = confined_t<stowed<_s...>>;
template <typename ..._s> concept  stowed_q = bond::tag_inner_p<stowed, _s...>;


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
		
		XTAL_VAL_(delete) (subtype, noexcept=default)
//		XTAL_VAL_(create) (subtype, noexcept=default)
		XTAL_VAL_(move)   (subtype, noexcept=default)
		XTAL_VAL_(copy)   (subtype, noexcept=default)
		XTAL_VAL_(induce) (subtype, noexcept:subtype)
	//	XTAL_VAL_(reduce) (subtype, noexcept:S_)
	
		XTAL_VAL_(new,implicit)
		subtype()
		noexcept
		:	subtype{U_store()}
		{}
		XTAL_VAL_(new,explicit)
		subtype(auto &&...oo)
		noexcept
		:	subtype{U_store(), XTAL_REF_(oo)...}
		{}
		XTAL_VAL_(new,explicit)
		subtype(U_store o, auto &&...oo)
		noexcept
		:	S_{U_state(o), XTAL_MOV_(o), XTAL_REF_(oo)...}
		{}

		XTAL_VAL_(inline,let)
		store(U_store o, auto &&...oo)
		noexcept -> void
		{
			self(U_state(o), XTAL_MOV_(o), XTAL_REF_(oo)...);
		}
		XTAL_FN2_(to) (XTAL_VAL_(return,inline,get) store(), S_::template head<constant_t<1>>())
		XTAL_FN2_(to) (XTAL_VAL_(return,inline,get) state(auto &&...oo), S_::template head<constant_t<0>>(XTAL_REF_(oo)...))

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
