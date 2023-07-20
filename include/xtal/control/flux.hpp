#pragma once
#include "./anybody.hpp"






XTAL_ENV_(push)
namespace xtal::control
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <typename ...As>
struct flux
{
	using subkind = compose<void
	,	_detail::refer_equality_comparators<XTAL_FLX>
	,	_detail::refer_bitwise_operators<XTAL_FLX>
//	,	refer<XTAL_FLX>
	,	As...
	,	defer<XTAL_FLX>
	>;

	template <any_p S>
	class subtype: public compose_s<S, subkind>
	{
		using S_ = compose_s<S, subkind>;
	
	public:
		using S_::S_;

	};
};
template <constant_q A, typename ...As>
struct flux<A, As...>
{
	using subkind = compose<void
	,	_detail::refer_equality_comparators<XTAL_FLX>
	,	_detail::refer_bitwise_operators<XTAL_FLX>
//	,	refer<XTAL_FLX>
	,	As...
	,	defer<XTAL_FLX>
	>;

	template <any_p S>
	class subtype: public compose_s<S, subkind>
	{
		using S_ = compose_s<S, subkind>;
	
	public:
		using S_::S_;

	//	XTAL_CO0_(subtype)
		XTAL_CO4_(subtype)
		
		XTAL_CON subtype()
		XTAL_0EX
		{
			S_::head(A{});
		}
		XTAL_CON subtype(XTAL_DEF ...oo)
		XTAL_0EX
		:	S_(XTAL_REF_(oo)...)
		{
			S_::head(A{});
		}


	};
};
template <typename ...As>
using flux_t = confined_t<flux<As..., tag<flux>>>;

template <typename ...As>
XTAL_CN2 flux_f(XTAL_DEF... oo) {return flux_t<As...>(XTAL_REF_(oo)...);}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
