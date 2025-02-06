#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::occur
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
Ties `Xs...` to unify handling, arithmetic, etc. \

template <class ...Xs> struct   bundle;
template <class ...Xs> using    bundle_t = confined_t<bundle<Xs...>>;
template <class ..._s> concept  bundle_q = bond::tag_p<bundle, _s...>;

template <auto f=_std::identity{}, class ...Xs>
XTAL_DEF_(return,inline,let)
bundle_f(Xs &&...xs)
noexcept -> auto
{
	using F = decltype(f);
	XTAL_IF0
	XTAL_0IF (same_q<_std::identity, F>)         {return bundle_f<[] XTAL_1FN_(function) (objective_f)>(XTAL_REF_(xs) ...);}
	XTAL_0IF (un_n<0, automorphism_p<F, Xs>...>) {return bundle_t<   return_t<F, Xs>...>          {  XTAL_REF_(xs) ...};}
	XTAL_0IF (in_n<0, automorphism_p<F, Xs>...>) {return bundle_t<   return_t<F, Xs>...>          {f(XTAL_REF_(xs))...};}
}


//////////////////////////////////////////////////////////////////////////////////

template <class ...Xs>
struct bundle
{
	using superkind = bond::compose<bond::tag<bundle>
	,	_retail::bundle<Xs...>
	>;
	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind>;
		using T_ = typename S_::self_type;

	public:// CONSTRUCT
		using S_::S_;

	public:// ACCESS
		using S_::self;
		using S_::twin;
		using S_::node;
		using S_::head;
		using S_::arguments;

		XTAL_FX2_(do) (template <size_type ...Ns>
		XTAL_DEF_(return,inline,let)
		argument(),
		noexcept -> decltype(auto)
		{
			return S_::template argument<Ns...>();
		})

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
