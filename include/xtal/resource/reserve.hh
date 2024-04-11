#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::resource
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
///\
Represents a local `{buffer,serve}` pair, \
used as e.g. a buffer and its abstract/copyable `std::span`. \

template <typename ..._s> struct reserve;
template <typename ..._s> using  reserve_t = confined_t<reserve<_s...>>;
template <bounded_q U>
struct reserve<U>
{
	using U_buffer = based_t<U>;
	using U_serve  = reiterated_t<U>;
	using subkind  = bond::compose<void
	,	cell::refer<U_serve>
	,	cell::defer<U_serve>
	,	cell::defer<U_buffer>
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
		:	subtype(U_buffer())
		{}
		XTAL_CXN subtype(auto &&...oo)
		XTAL_0EX
		:	subtype(U_buffer(), XTAL_REF_(oo)...)
		{}
		
		XTAL_CXN subtype(U_buffer o, auto &&...oo)
		XTAL_0EX
		:	S_(U_serve(o), XTAL_MOV_(o), XTAL_REF_(oo)...)
		{}
		XTAL_TN0 store(U_buffer o, auto &&...oo)
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
