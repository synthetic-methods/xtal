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
	,	_detail::infer_equality<signed>
	,	_detail::infer_binary_logic<signed>
	,	As...
	,	defer<signed>
	>;

	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind>;
	
	public:
		using S_::S_;

	};
};
template <constant_q A, typename ...As>
struct stage<A, As...>
{
	using superkind = bond::compose<void
	,	_detail::infer_equality<signed>
	,	_detail::infer_binary_logic<signed>
	,	As...
	,	defer<signed>
	>;

	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind>;
	
	public:
		using S_::S_;

	~	subtype() noexcept=default;
	//	subtype() noexcept=default;

		XTAL_NEW_(copy, subtype, noexcept=default)
		XTAL_NEW_(move, subtype, noexcept=default)
		
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
XTAL_DEF_(short)
XTAL_LET stage_f(auto &&...oo)
noexcept -> auto
{
	return stage_t<As...>(XTAL_REF_(oo)...);
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
