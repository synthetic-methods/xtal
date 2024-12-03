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
	using superkind = bond::compose<void
	,	_detail::infer_equality<sign_type>
	,	_detail::infer_binary_logic<sign_type>
	,	As...
	,	defer<sign_type>
	>;

	template <any_q S>
	class subtype : public bond::compose_s<S, superkind>
	{
		using S_ = bond::compose_s<S, superkind>;
	
	public:
		using S_::S_;

	};
};
template <constant_q A, typename ...As>
struct stage<A, As...>
{
	using superkind = bond::compose<void
	,	_detail::infer_equality<sign_type>
	,	_detail::infer_binary_logic<sign_type>
	,	As...
	,	defer<sign_type>
	>;

	template <any_q S>
	class subtype : public bond::compose_s<S, superkind>
	{
		using S_ = bond::compose_s<S, superkind>;
	
	public:
		using S_::S_;

		XTAL_CO0_(subtype)
	//	XTAL_CO1_(subtype)
		XTAL_CO4_(subtype)
		
		XTAL_NEW_(implicit) subtype()
		noexcept
		{
			S_::head(A{});
		}
		XTAL_NEW_(explicit) subtype(auto &&...oo)
		noexcept
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
XTAL_LET stage_f(auto &&...oo)
noexcept -> auto
{
	return stage_t<As...>(XTAL_REF_(oo)...);
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
