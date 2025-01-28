#pragma once
#include "./any.hh"
#include "./block.hh"





XTAL_ENV_(push)
namespace xtal::atom
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
Extends `block` with function application and functional construction. \

template <        class ..._s>	struct   quanta;
template <        class ..._s>	using    quanta_t = typename quanta<_s...>::type;
template <        class ..._s>	concept  quanta_q = bond::array_tag_p<quanta_t, _s...> and same_n<sized_n<_s>...>;

template <class U, auto  N, auto  ..._s> struct   quanta<U   [N][_s]...> : quanta<quanta_t<U[_s]...>   [N]> {};
template <class U, auto  N, auto  ..._s> struct   quanta<U(&)[N][_s]...> : quanta<quanta_t<U[_s]...>(&)[N]> {};


XTAL_FX0_(alias) (template <auto f=invoke_n<>>
XTAL_DEF_(return,inline,let) quanta_f(auto &&...oo),
	_detail::build<quanta_t>::template static_factory<f>(XTAL_REF_(oo)...))


////////////////////////////////////////////////////////////////////////////////

template <class ..._s>
struct quanta
{
	template <class T>
	using endotype = typename block<_s...>::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<endotype<T>, bond::tag<quanta_t>>;

	template <class T>
	class homotype : public holotype<T>
	{
		using S_ = holotype<T>;

	protected:
		using          S_::N_data;
		using typename S_::T_data;
		using typename S_::U_data;
		using typename S_::V_data;

	public:// CONSTRUCT
		using S_::S_;

	public:// OPERATE
		using S_::self;
		using S_::twin;
		using S_::size;

		///\returns an instance of `Y` constructed from the elements of `this`. \

		XTAL_FX4_(alias) (template <complete_q Y>
		XTAL_DEF_(return,inline,explicit operator) Y(), apply<Y>())

		///\returns an instance of `Y` constructed from the elements of `this`. \

		template <class Y>
		XTAL_DEF_(return,inline,let)
		apply() const
		noexcept -> decltype(auto)
		{
			return apply<invoke_n<Y>>();
		}
		///\returns the result of applying `f` to the elements of `this`. \

		template <auto  f=[] XTAL_0FN_(alias) (bond::pack_f)>
		XTAL_DEF_(return,inline,let)
		apply() const
		noexcept -> decltype(auto)
		{
			return apply(constant_n<f>);
		}
		///\returns the result of applying `f` to the elements of `this`. \

		XTAL_DEF_(return,inline,let)
		apply(auto &&f) const
		noexcept -> decltype(auto)
		{
			return [this, f=XTAL_REF_(f)]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN_(return) (f(self() (I)...))
			(bond::seek_s<N_data>{});
		}

		///\todo\
		Define in-place `map` via `(?:co)?ordinate`? \

		template <auto f>
		XTAL_DEF_(return,inline,set)
		static_map(auto &&...ts)
		noexcept -> decltype(auto)
		requires vector_q<_s...>
		{
			return [f_ = [&] (auto i)
				XTAL_0FN_(return) (f([&] (auto const &t)
					XTAL_0FN {if constexpr (same_q<decltype(t), T>) {return t(i);} else {return t;}}
				(ts)...))
			]<auto ...I> (bond::seek_t<I...>) XTAL_0FN_(return) (T{f_(I)...}) (bond::seek_s<N_data>{});
		}

	};
	using type = derive_t<homotype>;

};


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
