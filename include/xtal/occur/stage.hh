#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::occur
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\brief\
Represents the triple `{enter,leave,cancel}` with the `sign_type` `{0, 1,-1}`, \
cf. `*flux`'s `{changed,unchanged,unrecognized}`. \

///\note\
Not intended to be `attach`ed (except with `(?:ex|in)pect`), \
instead intercepted dynamically to affect/query state. \

///\note\
Can be `attach`ed for immediate (de)allocation with `(?:ex|in)pect`. \

template <typename ...As>	struct    stage	;
template <   class ..._s>	concept   stage_q = bond::tag_p<stage, _s...>;
template <typename ...As>	using     stage_t = confined_t<stage<As...>>;
template <typename ...As>
XTAL_DEF_(let) stage_f(auto &&...oo) noexcept {return stage_t<As...>(XTAL_REF_(oo)...);}


////////////////////////////////////////////////////////////////////////////////

template <typename ...As>
struct stage
{
	using superkind = bond::compose<bond::tag<stage>
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
	using superkind = bond::compose<bond::tag<stage>
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
	
	public:// CONSTRUCT
	//	using S_::S_;

	~	subtype()                noexcept=default;
	//	subtype()                noexcept=default;
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

	public:// ACCESS
		using S_::self;
		using S_::head;

	public:// *FUSE
	//	using S_::infuse;

		XTAL_DEF_(long)
		XTAL_LET influx(stage_q auto &&o)
		noexcept -> signed
		{
			if constexpr (stage_q<decltype(o)>) {
			//	TODO: Configure transition-rules (returning `-1` if invalid)?
				switch (head()) {
				case  0:;
				case  1:;
				case -1:;
				}
			}
			return S_::infuse(XTAL_REF_(o));
		}

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
