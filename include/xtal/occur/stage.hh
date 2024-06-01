#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::occur
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <typename ...As>
struct stage
{
	using subkind = bond::compose<void
	,	_detail::infer_equality<XTAL_FLX>
	,	_detail::infer_binary_logic<XTAL_FLX>
	,	As...
	,	defer<XTAL_FLX>
	>;

	template <any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;
	
	public:
		using S_::S_;

	};
};
template <cointegral_q A, typename ...As>
struct stage<A, As...>
{
	using subkind = bond::compose<void
	,	_detail::infer_equality<XTAL_FLX>
	,	_detail::infer_binary_logic<XTAL_FLX>
	,	As...
	,	defer<XTAL_FLX>
	>;

	template <any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;
	
	public:
		using S_::S_;

		XTAL_CO0_(subtype)
	//	XTAL_CO1_(subtype)
		XTAL_CO4_(subtype)
		
		XTAL_CON subtype()
		XTAL_0EX
		{
			S_::head(A{});
		}
		XTAL_CXN subtype(auto &&...oo)
		XTAL_0EX
		:	S_(XTAL_REF_(oo)...)
		{
			S_::head(A{});
		}


	};
};
template <typename ...As>
using stage_t = confined_t<stage<As..., bond::tag<stage>>>;

template <typename ...As>
XTAL_DEF_(return,inline)
XTAL_FN1     stage_f(auto &&...oo)
XTAL_0EX_TO_(stage_t<As...>(XTAL_REF_(oo)...))


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
