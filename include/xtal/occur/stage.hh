#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::occur
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\brief\
Represents the triple `{enter,leave,cancel}` with the `sign_type` `{0, 1,-1}`, \
cf. `*flow`'s `{changed,unchanged,unrecognized}`. \

///\note\
Not intended to be `attach`ed (except with `(?:ex|in)pect`), \
instead intercepted dynamically to interpret state. \

///\note\
Can be `attach`ed for immediate (de)allocation with `(?:ex|in)pect`. \

template <class ..._s> struct   stage;
template <class ..._s> using    stage_t =     confined_t<stage< _s...>>;
template <class ..._s> concept  stage_q = bond::tagged_p<stage, _s...> ;

template <typename ...As>
XTAL_DEF_(return,inline,let) stage_f(auto &&...oo)
noexcept -> decltype(auto) {return stage_t<As...>(XTAL_REF_(oo)...);}


////////////////////////////////////////////////////////////////////////////////

template <typename ...As>
struct stage
{
	using superkind = bond::compose<bond::tag<stage>
	,	As...
	,	_detail::refer_equality<signed>
	,	_detail::refer_binary_logic<signed>
	,	defer<signed>
	>;
	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind>;
	
	public:// CONSTRUCT
		using S_::S_;

	public:// ACCESS
		using S_::self;
		using S_::head;

	};
};
template <constant_q A, typename ...As>
struct stage<A, As...>
{
	using superkind = stage<As...>;

	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind>;
	
	public:// CONSTRUCT
	//	using S_::S_;

		XTAL_NEW_(delete) (subtype, noexcept = default)
//		XTAL_NEW_(create) (subtype, noexcept = default)
		XTAL_NEW_(move)   (subtype, noexcept = default)
		XTAL_NEW_(copy)   (subtype, noexcept = default)
		XTAL_NEW_(cast)   (subtype, noexcept)
		
		XTAL_NEW_(implicit)
		subtype()
		noexcept
		{
			S_::head(A{});
		}
		XTAL_NEW_(explicit)
		subtype(auto &&...oo)
		noexcept
		:	S_(XTAL_REF_(oo)...)
		{
			S_::head(A{});
		}

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
