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
template <class ..._s> using    stage_t =  confined_t<stage< _s...>>;
template <class ..._s> concept  stage_q = bond::tag_p<stage, _s...> ;

template <typename ...As>
XTAL_DEF_(return,inline,let) stage_f(auto &&...oo)
noexcept -> decltype(auto) {return stage_t<As...>(XTAL_REF_(oo)...);}


////////////////////////////////////////////////////////////////////////////////

template <typename ...As>
struct stage
{
	using superkind = bond::compose<bond::tag<stage>
	,	_detail::refer_equality<signed>
	,	_detail::refer_binary_logic<signed>
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
	,	_detail::refer_equality<signed>
	,	_detail::refer_binary_logic<signed>
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

	~	subtype()                 noexcept=default;
	//	subtype()                 noexcept=default;
		XTAL_NEW_(copy) (subtype, noexcept=default)
		XTAL_NEW_(move) (subtype, noexcept=default)
		
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

		template <signed N_ion>
		XTAL_DEF_(return,inline,let)
		fuse(auto &&o)
		noexcept -> signed
		{
			return S_::template fuse<N_ion>(XTAL_REF_(o));
		}
		///\returns the result of influxing `stage_q` if `>= 0`, otherwise `-1`. \

		template <signed N_ion> requires in_n<N_ion, +1>
		XTAL_DEF_(return,inline,let)
		fuse(stage_q auto &&o)
		noexcept -> signed
		{
			return head() == -1? -1: S_::template fuse<N_ion>(XTAL_REF_(o));
		}
		/**/
		///\returns `1` if the `stage_q` matches `head()`, otherwise `0` (simulating `fuse<+1>`). \

		template <signed N_ion> requires in_n<N_ion, -1>
		XTAL_DEF_(return,inline,let)
		fuse(stage_q auto &&o)
		noexcept -> signed
		{
			return heading(XTAL_REF_(o));
		}
		/***/

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
