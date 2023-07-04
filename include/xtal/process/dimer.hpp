#pragma once
#include "./any.hpp"






XTAL_ENV_(push)
namespace xtal::process
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <typename ...>
struct dimer;

template <typename ...Ts>
XTAL_ASK dimer_q = tag_q<dimer, Ts...>;

template <typename U, typename ...As>
XTAL_USE dimer_t = confined_t<dimer<U, As...>>;


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

		template <auto ...Ks>
		XTAL_FN2 method(XTAL_DEF... xs)
		XTAL_0EX
		{
			using X = _std::common_type_t<XTAL_TYP_(xs)...>;
			using W = typename collage_t<X, sizeof...(xs)>::scalar_t;
			using M = typename S_::dial_t;
			W const w {XTAL_REF_(xs)...};
			M const m = dial();
			return [&, this]<auto ...I>(seek_t<I...>)
				XTAL_0FN_(S_::template method<Ks...>(w.dot(_std::get<I>(m))...))
			(seek_v<_std::tuple_size_v<M>>);
		}

	};
};

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
