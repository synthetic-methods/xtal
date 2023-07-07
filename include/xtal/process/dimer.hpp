#pragma once
#include "./any.hpp"






XTAL_ENV_(push)
namespace xtal::process
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ...>
struct dimer;

template <typename ...Ts>
XTAL_ASK dimer_q = tag_q<dimer, Ts...>;

template <typename ..._s>
XTAL_USE dimer_t = confined_t<dimer<_s...>>;

template <typename ...As>
XTAL_CN2 dimer_f(XTAL_DEF u) {return dimer_t<decltype(u), As...>(XTAL_REF_(u));}


////////////////////////////////////////////////////////////////////////////////

template <typename U, typename... As>
struct dimer<U, As...>
{
	using subkind = confer<U, As..., tag<dimer>>;

	template <any_p S>
	class subtype: public compose_s<S, subkind>
	{
		using S_ = compose_s<S, subkind>;

	public:
		using S_::S_;
		using S_::self;
		using S_::dial;

		XTAL_DO2_(template <auto ...Ks>
		XTAL_FN2 method(XTAL_DEF... xs),
		{
			using X = _std::common_type_t<XTAL_TYP_(xs)...>;
			using W = typename collage_t<X, sizeof...(xs)>::scalar_t;
			using M = typename S_::dial_t;
			W const w {XTAL_REF_(xs)...};
			M const m = dial();
			return [&, this]<auto ...I>(seek_t<I...>)
				XTAL_0FN_(S_::template method<Ks...>(w.dot(_std::get<I>(m))...))
			(seek_v<_std::tuple_size_v<M>>);
		})

	};
};

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
