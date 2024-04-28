#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::resource
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
///\
Represents a local `{store,serve}` pair, \
used as e.g. a buffer and its abstract/copyable `std::span`. \

template <typename ..._s> XTAL_TYP reflect;
template <typename ..._s> XTAL_USE reflect_t = confined_t<reflect<_s...>>;
template <typename ..._s> XTAL_ASK reflect_q = bond::tag_p<reflect, _s...>;
template <bounded_q U_serve, bounded_q U_store>
struct reflect<U_serve, U_store>
{
	using subkind = bond::compose<bond::tag<reflect>
	,	cell::refer<U_serve>
	,	cell::defer<U_serve>
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
		:	S_(U_serve(o), XTAL_MOV_(o), XTAL_REF_(oo)...)
		{}
		XTAL_TN0 store(U_store o, auto &&...oo)
		XTAL_0EX
		{
			self(U_serve(o), XTAL_MOV_(o), XTAL_REF_(oo)...);
		}
		XTAL_TO4_(XTAL_TN2 store(), S_::template head<1>())
		XTAL_TO4_(XTAL_TN2 serve(auto &&...oo), S_::template head<0>(XTAL_REF_(oo)...))

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
