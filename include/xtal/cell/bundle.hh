#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::cell
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
Ties `Xs...`. \

template <class ...Xs> struct   bundle;
template <class ...Xs> using    bundle_t = confined_t<bundle<Xs...>>;
//mplate <class ...Xs> using    bundle_s = _std::conditional_t<1 != sizeof...(Xs), confined_t<bundle<Xs...>>, complete_t<bond::seek_front_t<Xs...>, void>>;
template <class ..._s> concept  bundle_q = bond::tag_p<bundle, _s...>;

//////////////////////////////////////////////////////////////////////////////////

template <class ...Xs>
struct bundle
{
	using superkind = bond::compose<bond::tag<bundle>
	,	defer<bond::pack_t<Xs...>>
	>;
	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind>;
		using H_ = typename S_::head_type;

	public:// CONSTRUCT
		using S_::S_;//NOTE: Inherited and respecialized!

		///\
		Initialize `arguments` using those provided. \

		XTAL_NEW_(explicit)
		subtype(Xs &&...xs)
		noexcept
	//	requires make_p<H_, Xs...>
		:	S_{H_{XTAL_REF_(xs)...}}
		{}

	public:// ACCESS
		using S_::self;
		using S_::head;

		//\note\
		Contingent override of `node` allows unextended `bundle`s to be destructured. \
		Use `arguments` for unmitigated access. \

		XTAL_FX4_(to)                    (XTAL_DEF_(return,inline,get)      node(), head())
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
