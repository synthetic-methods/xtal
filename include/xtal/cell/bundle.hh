#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::cell
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/*!
\brief
Ties `Xs...` together as a tuple,
materializing any `rvalue`s or atomic `lvalue`s.
*/
template <class ...Xs> struct   bundle;
template <class ...Xs> using    bundle_t = confined_t<bundle<Xs...>>;
template <class ..._s> concept  bundle_q = bond::tag_in_p<bundle, _s...>;

//////////////////////////////////////////////////////////////////////////////////

XTAL_DEF_(let) bundle_f = []<class ...Xs> (Xs &&...xs)
XTAL_0FN {
	XTAL_IF0
	XTAL_0IF (un_v<0, objective_q<Xs>...>) {return bundle_t<objective_t<Xs>...>{            XTAL_REF_(xs) ...};}
	XTAL_0IF (in_v<0, objective_q<Xs>...>) {return bundle_t<objective_t<Xs>...>{objective_f(XTAL_REF_(xs))...};}
};


//////////////////////////////////////////////////////////////////////////////////

template <class ...Xs>
struct bundle
{
	using superkind = bond::compose<bond::tag<bundle>
	,	defer<bond::pack_t<_xtd::decay_trivial_value_reference_t<Xs>...>>
	>;
	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind>;
		using H_ = typename S_::head_type;

	public:// CONSTRUCT
		using S_::S_;//NOTE: Inherited and respecialized!

		/*!
		\brief  	Initialize `arguments` using those provided.
		*/
		XTAL_NEW_(explicit)
		subtype(Xs &&...xs)
		noexcept
	//	requires make_p<H_, Xs...>
		:	S_{H_{XTAL_REF_(xs)...}}
		{}

	public:// ACCESS
		using S_::self;
		using S_::head;

		XTAL_FX4_(to)                    (XTAL_DEF_(return,inline,get) arguments(), head())
		XTAL_FX4_(to) (template <auto  f> XTAL_DEF_(return,inline,get) arguments(),      _std::apply(          f , arguments()))
		XTAL_FX4_(to) (template <class F> XTAL_DEF_(return,inline,get) arguments(F &&f), _std::apply(XTAL_REF_(f), arguments()))

		XTAL_FX2_(to) (template <size_type ...Is>
		XTAL_DEF_(return,inline,get)
		argument(), bond::pack_item_f<Is...>(head()))

	};
	using type = confined_t<bond::compose_t<subtype>>;

};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
