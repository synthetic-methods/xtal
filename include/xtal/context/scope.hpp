#pragma once
#include "./any.hpp"
#include "../control/resize.hpp"
#include "../control/sequel.hpp"




XTAL_ENV_(push)
namespace xtal::context
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <bracket_q U>
struct scope
{
	using resize_u = control::resize_t<>;
	using sequel_u = control::sequel_t<>;

	using store_u = based_t<U>;
	using serve_u = deranged_t<U>;
	using subkind = compose<void
	,	concord::defer<serve_u>
	,	concord::defer<store_u>
//	,	typename resize_u::attach
//	,	typename serial_u::attach
	>;

	template <typename S>
	class subtype: public compose_s<S, subkind>
	{
		using S_ = compose_s<S, subkind>;

	public:
	//	using S_::S_;
		using S_::self;
		
		~subtype() = default;
	
	//	XTAL_CO0_(subtype)
		XTAL_CO4_(subtype)
	
		XTAL_CON subtype()
		XTAL_0EX
		:	subtype(store_u())
		{}
		XTAL_CXN subtype(XTAL_DEF ...oo)
		XTAL_0EX
		:	subtype(store_u(), XTAL_REF_(oo)...)
		{}
		
		XTAL_CXN subtype(store_u o, XTAL_DEF ...oo)
		XTAL_0EX
		:	S_(serve_u(o), XTAL_MOV_(o), XTAL_REF_(oo)...)
		{}
		XTAL_FN0 store(store_u o, XTAL_DEF... oo)
		XTAL_0EX
		{
			self(serve_u(o), XTAL_MOV_(o), XTAL_REF_(oo)...);
		}
		XTAL_TO4_(XTAL_FN2 store(), S_::template head<1>())
		XTAL_TO4_(XTAL_FN2 serve(XTAL_DEF... oo), S_::template head<0>(XTAL_REF_(oo)...))

	};
};
template <bracket_q U>
using scope_t = confined_t<scope<U>>;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)