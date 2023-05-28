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
#include "../common/any.hxx"

////////////////////////////////////////////////////////////////////////////////
///\
Produces a decorator `subtype<S>` that defines `T`. \

template <typename T>
struct define
{
	using subkind = _detail::define<T>;

	template <any_q S>
	class subtype: public common::compose_s<S, subkind>
	{
		friend T;
		using co = common::compose_s<S, subkind>;
	public:
		using co::co;

	protected:
		///\
		Thunkifies `T` by binding `Xs...`. \

		template <typename ...Xs>
		struct bind
		{
			using signature = common::bundle<let_t<Xs>...>;
			using result_t  = typename signature::template invoke_t<T>;
			using return_t  = iteratee_t<result_t>;

			using serial_n = message::serial_t<countee_t<>>;
			using serial_u = message::serial_t<counted_t<>>;
			using resize_u = message::resize_t<>;
			using subkind  = common::compose<context::defer<typename signature::type>
			,	serial_n::attach
			,	serial_u::attach
			,	resize_u::attach
			,	_detail::defer<T>
			>;

			XTAL_LET_(sigma_t) N_arity = sizeof...(Xs);

			template <any_q R>
			class subtype: public common::compose_s<R, subkind>
			{
				using co = common::compose_s<R, subkind>;

			public:
				using co::co;
				using co::self;

				///\
				Constructs `arguments` using those supplied. \

				XTAL_NEW subtype(Xs &&...xs)
				XTAL_0EX
				:	co(signature::make(XTAL_FWD_(Xs) (xs)...), T())
				{
				}
				XTAL_NEW subtype(XTAL_DEF_(is_q<T>) t, Xs &&...xs)
				XTAL_0EX
				:	co(signature::make(XTAL_FWD_(Xs) (xs)...), XTAL_REF_(t))
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
				template <auto ...Ms>
				XTAL_FN2 method(XTAL_DEF... xs)
				XTAL_0EX
				{
					return co::template method<Ms...>(XTAL_REF_(xs)...);
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
				\note When prefixed by `null_t()`, \
				`self` is skipped and the message is forwarded directly to `arguments`. \

				XTAL_FN2_(flux_t) influx(null_t, XTAL_DEF ...oo)
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
						XTAL_0FN_(XTAL_REF_(xs).influx(oo...) |...| -1));
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
				\returns the aggregated result of `efflux_pull` and `efflux_this`, \
				evaluating the latter only if the former `!= 0`. \

				XTAL_FN2_(flux_t) efflux(XTAL_DEF ...oo)
				XTAL_0EX
				{
					flux_t const _ = self().efflux_pull(oo...);
					return !_?0: _ & self().efflux_this(XTAL_REF_(oo)...);
				}
				///\
				\note When prefixed by `null_t()`, \
				`self` is skipped and the message is forwarded directly to `arguments`. \

				XTAL_FN2_(flux_t) efflux(null_t, XTAL_DEF ...oo)
				XTAL_0EX
				{
					return self().efflux_pull(XTAL_REF_(oo)...);
				}
			protected:
				///\
				Forwards the message to `self`, bypassing `arguments`. \

				XTAL_FN2_(flux_t) efflux_this(XTAL_DEF ...oo)
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
						XTAL_0FN_(XTAL_REF_(xs).efflux(oo...) |...| -1));
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
	class subtype: public common::compose_s<S, subkind>
	{
		using co = common::compose_s<S, subkind>;
	public:
		using co::co;
		using co::self;

		template <typename ...Xs>
		struct bind
		{
			using subkind = _detail::confined<typename co::template bind<Xs...>>;
			
			template <any_q R>
			using subtype = common::compose_s<R, subkind>;
			
		};
		template <typename ...Xs>
		using     bind_t = typename bind<Xs...>::template subtype<S>;
		XTAL_LET  bind_f = [] (XTAL_DEF ...xs)
		XTAL_0FN_(bind_t<decltype(xs)...>(XTAL_REF_(xs)...));

		XTAL_FN2 bond(XTAL_DEF ...xs)
		{
			return bind_t<decltype(xs)...>(self(), XTAL_REF_(xs)...);
		}

	};
};

////////////////////////////////////////////////////////////////////////////////
///\
Produces a decorator `subtype<S>` that proxies `U`. \

template <typename U>
struct defer
:	defer<_detail::let_t<U>>
{
};
template <_detail::any_q U>
struct defer<U>
{
	using subkind = _detail::defer<U>;

	template <any_q S>
	class subtype: public common::compose_s<S, subkind>
	{
		using co = common::compose_s<S, subkind>;

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
			return iterate_forward_f(iterate_map_f(head().template reify<iteratee_t<decltype(xs)>...>()) (XTAL_REF_(xs)...));
		}
		template <auto...>
		XTAL_FN2 method(XTAL_DEF ...xs)
		XTAL_0EX
		requires
		requires (U const &u) {u.template method<iteratee_t<decltype(xs)>...>(XTAL_REF_(xs)...);}
		{
			return iterate_map_f(head().template reify<iteratee_t<decltype(xs)>...>()) (XTAL_REF_(xs)...);
		}
		template <auto...>
		XTAL_FN2 method(XTAL_DEF ...xs)
		XTAL_0FX
		{
			return iterate_map_f(head().template reify<iteratee_t<decltype(xs)>...>()) (XTAL_REF_(xs)...);
		}

	};
};
template <iterated_q U>
requires (not any_q<U>)
struct defer<U>
{
	using serial_n = message::serial_t<counted_t<>>;
//	using serial_n = message::serial_t<countee_t<>>;

	using subkind = common::compose<_detail::defer<U>, serial_n::attach>;
//	using subkind = common::compose<serial_n::attach, _detail::defer<U>>;

	template <any_q S>
	class subtype: public common::compose_s<S, subkind>
	{
		using co = common::compose_s<S, subkind>;
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
			iota_t const m_front = m.front();
			iota_t const m_size  = m.size();
			iota_t const v_size  = v.size();
			bool   const v_sized = v.size() != -1;
			bool   const o_sized = v.size() == -1;
			iota_t i = m_front;
			iota_t j = m_size + i;
			i *= v_sized;
			j *= v_sized;
			j += o_sized*v_size;
			return v|_v3::views::slice(i, j);
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
////////////////////////////////////////////////////////////////////////////////
///\
Produces a decorator `subtype<S>` that lifts the operations of `U`. \

template <typename U>
struct refer
{
	using subkind = _detail::refer<U>;

	template <any_q S>
	using subtype = common::compose_s<S, subkind>;

};

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
