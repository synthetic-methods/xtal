#pragma once
#include "../process/any.hpp"//_detail
#include "../message/any.hpp"
#include "../message/serial.hpp"
#include "../message/resize.hpp"



XTAL_ENV_(push)
namespace xtal::processor
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

namespace _detail = xtal::process;
#include "../common/any.ipp"

template <_std::invocable F>
XTAL_FN2 let_f(F &&f)
XTAL_0EX
requires (not any_q<F>)
{
	return contrive_t<F>(_detail::let_f(XTAL_FWD_(F) (f)));
}


////////////////////////////////////////////////////////////////////////////////
///\
Produces a decorator `subtype<S>` that defines `T`. \

template <typename T>
struct define
{
	using subkind = _detail::define<T>;

	template <any_q S>
	class subtype: public compose_s<S, subkind>
	{
		friend T;
		using co = compose_s<S, subkind>;
	public:
		using co::co;

	protected:
		///\
		Thunkifies `T` by binding `Xs...`. \

		template <typename ...Xs>
		struct bind
		{
		//	TODO: Define `lift_t` to handle the `rvalue`/`lvalue` distinction, \
			e.g. respectively ignoring `resize`/`respan` messages. \

			/*/
			template <typename X> using lift_t = let_t<X>;
			using signature = bundle<lift_t<Xs>...>;
			/*/
			using signature = bundle<Xs...>;
			/***/
			
			using result_t = typename signature::template invoke_t<T>;
			using return_t = iteratee_t<result_t>;

			using serial_n = message::serial_t<countee_t<>>;
			using serial_u = message::serial_t<counted_t<>>;
			using resize_u = message::resize_t<>;

			XTAL_LET_(sigma_t) N_arity = sizeof...(Xs);

			using subkind = compose<context::defer<typename signature::type>
			,	serial_n::attach
			,	serial_u::attach
			,	resize_u::attach
			,	_detail::defer<T>
			>;

			template <any_q R>
			class subtype: public compose_s<R, subkind>
			{
				using co = compose_s<R, subkind>;

			public:
				using co::co;
				using co::self;

				///\
				Constructs `arguments` using those supplied. \

				XTAL_NEW_(explicit) subtype(Xs &&...xs)
				XTAL_0EX
				:	co(signature::make(XTAL_REF_(xs)...))
				{
				}

				XTAL_RE4_(XTAL_FN2 arguments(), co::head())
				
				template <sigma_t I>
				XTAL_FN2 argument()
				XTAL_0EX
				{
					return _std::get<I>(arguments());
				}
				
				XTAL_FN2 apply(XTAL_DEF fx)
				XTAL_0EX
				{
					return _std::apply([&] (XTAL_DEF ...xs)
						XTAL_0FN_(XTAL_REF_(fx) (XTAL_REF_(xs)...))
					,	arguments()
					);
				}

				///\
				Evaluates `T::value` using the bound arguments. \

				template <auto ...Ms>
				XTAL_FN2 method()
				XTAL_0EX
				{
					return apply([this] (XTAL_DEF ...xs)
						XTAL_0FN_(co::template method<Ms...>(XTAL_REF_(xs)...)));
				}

			protected:
				XTAL_LET disorder_v = requires (subtype const &t) {t.template method<>();};

			
			public:
				///\
				\returns the aggregated result of `influx_node` and `influx_push`, \
				evaluating the latter only if the former `!= 0`. \

				XTAL_FN2_(flux_t) influx(XTAL_DEF ...oo)
				XTAL_0EX
				{
					flux_t const _ = self().influx_node(oo...);
					return !_?0: _ & self().influx_push(XTAL_REF_(oo)...);
				}
				///\
				\note When prefixed by `nothing_t()`, \
				`self` is skipped and the message is forwarded directly to `arguments`. \

				XTAL_FN2_(flux_t) influx(nothing_t, XTAL_DEF ...oo)
				XTAL_0EX
				{
					return self().influx_push(XTAL_REF_(oo)...);
				}
			protected:
				///\
				Forwards the message to `self`, bypassing `arguments`. \

				XTAL_FN2_(flux_t) influx_node(XTAL_DEF ...oo)
				XTAL_0EX
				{
					return co::influx(XTAL_REF_(oo)...);
				}
				///\
				Forwards the message to `arguments`, bypassing `self`. \

				XTAL_FN2_(flux_t) influx_push(auto ...oo)
				XTAL_0EX
				{
					return apply([&] (XTAL_DEF ...xs)
						XTAL_0FN_(XTAL_REF_(xs).influx(oo...) |...));
				}
				///\
				Forwards the message *tail* to `arguments`, bypassing `self`. \
				If `N_parity < N_arity`, the complete message is forwarded to `argument<N_parity>()`. \

				template <sigma_t N_parity=N_arity>
				XTAL_FN2_(flux_t) influx_push_tail(auto o, auto ...oo)
				XTAL_0EX
				{
					if constexpr (N_parity == N_arity)
					{
						return influx_push(_std::move(oo)...);
					}
					else
					{
						return [&] <auto ...Ns> (seek_t<Ns...>)
							XTAL_0FN_(argument<N_parity>().influx(o, oo...) |...| argument<(N_parity <= Ns) + Ns>().influx(oo...))
						(seek_v<N_arity - 1>);
					}
				}

			
			public:
				///\
				\returns the aggregated result of `efflux_pull` and `efflux_node`, \
				evaluating the latter only if the former `!= 0`. \

				XTAL_FN2_(flux_t) efflux(XTAL_DEF ...oo)
				XTAL_0EX
				{
					flux_t const _ = self().efflux_pull(oo...);
					return !_?0: _ & self().efflux_node(XTAL_REF_(oo)...);
				}
				///\
				\note When prefixed by `nothing_t()`, \
				`self` is skipped and the message is forwarded directly to `arguments`. \

				XTAL_FN2_(flux_t) efflux(nothing_t, XTAL_DEF ...oo)
				XTAL_0EX
				{
					return self().efflux_pull(XTAL_REF_(oo)...);
				}
			protected:
				///\
				Forwards the message to `self`, bypassing `arguments`. \

				XTAL_FN2_(flux_t) efflux_node(XTAL_DEF ...oo)
				XTAL_0EX
				{
					return co::efflux(XTAL_REF_(oo)...);
				}
				///\
				Forwards the message to `arguments`, bypassing `self`. \

				XTAL_FN2_(flux_t) efflux_pull(auto ...oo)
				XTAL_0EX
				{
					return apply([&] (XTAL_DEF ...xs)
						XTAL_0FN_(XTAL_REF_(xs).efflux(oo...) |...));
				}
				///\
				Forwards the message *head* to `arguments`, bypassing `self`. \
				If `N_parity < N_arity`, the complete message is forwarded to `argument<N_parity>()`. \

				template <sigma_t N_parity=N_arity>
				XTAL_FN2_(flux_t) efflux_pull_head(auto o, auto ...oo)
				XTAL_0EX
				{
					if constexpr (N_parity == N_arity)
					{
						return efflux_pull(_std::move(o));
					}
					else
					{
						return [&] <auto ...Ns> (seek_t<Ns...>)
							XTAL_0FN_(argument<N_parity>().efflux(o, oo...) |...| argument<(N_parity <= Ns) + Ns>().efflux(o))
						(seek_v<N_arity - 1>);
					}
				}


			};
		};

	};
};
////////////////////////////////////////////////////////////////////////////////

template <typename T>
struct refine
{
	using subkind = _detail::refine<T>;

	template <any_q S>
	class subtype: public compose_s<S, subkind>
	{
		using co = compose_s<S, subkind>;
	public:
		using co::co;

		template <typename ...Xs>
		struct bind
		{
			using subkind = _detail::confined<typename co::template bind<Xs...>>;
			
			template <any_q R>
			using subtype = compose_s<R, subkind>;
			
		};
		template <typename ...Xs>
		using     bind_t = typename bind<Xs...>::template subtype<S>;
		XTAL_LET  bind_f = [] (XTAL_DEF ...xs)
		XTAL_0FN_(bind_t<decltype(xs)...>(XTAL_REF_(xs)...));

	};
};

////////////////////////////////////////////////////////////////////////////////
///\
Produces a decorator `subtype<S>` that proxies `U`. \

template <typename U>
struct defer
:	defer<_detail::contrive_t<U>>
{
};
template <_detail::any_q U>
struct defer<U>
{
	using subkind = _detail::defer<U>;

	template <any_q S>
	class subtype: public compose_s<S, subkind>
	{
		using co = compose_s<S, subkind>;

		template <typename F>
		struct zap
		{
			class type
			{
				F function_m;

			public:
				XTAL_NEW_(explicit) type(F&&f)
				XTAL_0EX
				:	function_m(XTAL_FWD_(F) (f))
				{
				}
				XTAL_OP2() () &&
				XTAL_0EX
				{
					return _v3::views::generate(_std::move(function_m));
				}
				XTAL_OP2() (XTAL_DEF x) &&
				XTAL_0EX
				{
					return _v3::views::transform(XTAL_REF_(x), _std::move(function_m));
				}
				XTAL_OP2() (XTAL_DEF ...xs) &&
				XTAL_0EX
				{
					return _v3::views::zip_with(_std::move(function_m), XTAL_REF_(xs)...);
				}

			};
		};
		template <typename F>
		using     zap_t = typename zap<F>::type;
		XTAL_LET  zap_f = [] (XTAL_DEF f)
		XTAL_0FN_(zap_t<decltype(f)>(XTAL_REF_(f)));

		template <typename ...Xs>
		struct review
		{
			using Ref = _std::invoke_result_t<U, iteratee_t<Xs>...>;
			using cat = _v3::ranges::category;
			XTAL_LET Cat = cat::forward|cat::sized;
			using type = _v3::ranges::any_view<Ref, Cat>;
		};
		template <typename ...Xs>
		using review_t = typename review<Xs...>::type;

	//	TODO: It appears that both `category::sized` and `views::take` must be applied \
		for `size` to be defined by `ranges::view_interface`, but maybe there's a better way? \

	public:
		using co::co;
		using co::self;
		using co::head;

		///\
		Defines the range-lifted form of `head` by `reify`ing the underlying `process`. \
		This means that parameter resolution is only performed at the beginning of each block. \
		\
		NOTE: Unless the underlying `process` is invocable as `const`, \
		it is assumed to be stateful, and iterator monotonicity is enforced.

		template <auto...>
		XTAL_FN2 method(XTAL_DEF ...xs)
		XTAL_0EX
		{
			static_assert(unfalse_p<iterated_q<XTAL_TYP_(xs)>...>);
			auto f = head().template reify<iteratee_t<decltype(xs)>...>();
			auto z = zap_f(_std::move(f)) (XTAL_REF_(xs)...);
			auto n = delta_t(z.size());
			return review_t<decltype(xs)...>(_std::move(z))|_v3::views::take(std::move(n));
		}
		template <auto...>
		XTAL_FN2 method(XTAL_DEF ...xs)
		XTAL_0FX
	//	requires
	//	requires (U const &u) {u.template method<>(XTAL_REF_(xs)...);}
		{
			static_assert(unfalse_p<iterated_q<XTAL_TYP_(xs)>...>);
			auto f = head().template reify<iteratee_t<decltype(xs)>...>();
			return zap_f(std::move(f)) (XTAL_REF_(xs)...);
		}

	};
};
template <iterated_q U>
struct defer<U>
{
	using serial_n = message::serial_t<counted_t<>>;
//	using serial_n = message::serial_t<countee_t<>>;

	using subkind = compose<_detail::defer<U>, serial_n::attach>;
//	using subkind = compose<serial_n::attach, _detail::defer<U>>;

	template <any_q S>
	class subtype: public compose_s<S, subkind>
	{
		using co = compose_s<S, subkind>;
	public:
		using co::co;

		///\
		Deferred implementation of `T::value`. \

		template <auto...>
		XTAL_FN2 method()
		XTAL_0FX
		{
			auto const &v = co::template method<>();
			auto const &m = co::template get<serial_n>();
			auto const &i = iota_t(m.front());
			auto const &j = iota_t(m.size()) + i;
			return -1 == v.size()? v:v|_v3::views::slice(i, j);
		}

		XTAL_FN2 begin()
		XTAL_0FX
		{
			return method<>().begin();
		}

		XTAL_FN2 end()
		XTAL_0FX
		{
			return method<>().end();
		}

	};
};
template <numeric_q V>
struct defer<V>
{
	using subkind = _detail::defer<repeated_t<V>>;

	template <any_q S>
	class subtype: public compose_s<S, subkind>
	{
		using co = compose_s<S, subkind>;
	public:
		using co::co;

		XTAL_NEW_(explicit) subtype(XTAL_DEF_(of_q<V>) v)
		XTAL_0EX
		:	co(repeated_t<V>(XTAL_REF_(v)))
		{
		}

	};
};
////////////////////////////////////////////////////////////////////////////////
///\
Produces a decorator `subtype<S>` that lifts the operations of `U`. \

template <typename U>
struct refer
{
	using subkind = _detail::refer<U>;

	template <any_q S>
	using subtype = compose_s<S, subkind>;

};
template <numeric_q V>
struct refer<V>
{
	using subkind = _detail::refer<repeated_t<V>>;

	template <any_q S>
	using subtype = compose_s<S, subkind>;

};

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
