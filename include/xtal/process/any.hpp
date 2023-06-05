#pragma once
#include "../context/any.hpp"//_retail






XTAL_ENV_(push)
namespace xtal::process
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

namespace _retail = xtal::context;
#include "../common/any.hxx"


////////////////////////////////////////////////////////////////////////////////
template <typename ...As>
struct link
{
	using subkind = compose<As...>;

	template <any_q S>
	class subtype: public compose_s<S, subkind>
	{
		using co = compose_s<S, subkind>; using T = typename co::self_t;
	public:
		using co::co;

		using linked = constant_t<true>;

		///\
		Thunkifies `T` by binding `Xs...`. \

		template <typename ...Xs>
		struct bind
		{
			using signature = pack<Xs...>;
			using result_t  = typename signature::template invoke_t<T>;
			using return_t  = iteratee_t<result_t>;
			
			using subkind = compose<content::defer<typename signature::type>, As..., defer<T>>;

			template <any_q R>
			class subtype: public compose_s<R, subkind>
			{
				using co = compose_s<R, subkind>;

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

				XTAL_RN4_(XTAL_FN2 arguments(), co::head())
				
				template <size_t N, size_t ...Ns>
				XTAL_FN2 argument()
				XTAL_0EX
				{
					if constexpr (0 == sizeof...(Ns))
					{	return _std::get<N>(arguments());
					}
					else
					{	return _std::get<N>(arguments()).template argument<Ns...>();
					}
				}
				
				XTAL_FN2 apply(XTAL_DEF fx)
				XTAL_0EX
				{
					return _std::apply([&](XTAL_DEF ...xs)
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
					return apply([this](XTAL_DEF ...xs)
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
				\returns the result of `influx`ing `self` then  (if `& 1`) `arguments`. \

				XTAL_FNX influx(XTAL_DEF ...oo)
				XTAL_0EX
				{
					return XTAL_FLX_(self().influx_request(oo...)) (co::influx(XTAL_REF_(oo)...));
				}
				///\
				\returns the result of `efflux`ing `arguments` then (if `& 1`) `self`. \

				XTAL_FNX efflux(XTAL_DEF ...oo)
				XTAL_0EX
				{
					return XTAL_FLX_(co::efflux(oo...)) (self().efflux_request(XTAL_REF_(oo)...));
				}

				///\
				\note If prefixed by `null_t()`, the control is forwarded directly to `arguments`. \

				XTAL_FNX influx(null_t, XTAL_DEF ...oo)
				XTAL_0EX
				{
					return self().influx_request(XTAL_REF_(oo)...);
				}
				XTAL_FNX efflux(null_t, XTAL_DEF ...oo)
				XTAL_0EX
				{
					return self().efflux_request(XTAL_REF_(oo)...);
				}


				///\
				Forwards the control to `arguments`, bypassing `self`. \

				XTAL_FNX influx_request(auto ...oo)
				XTAL_0EX
				{
					return apply([&](XTAL_DEF ...xs)
						XTAL_0FN_(XTAL_REF_(xs).influx(oo...) |...| -1));
				}
				XTAL_FNX efflux_request(auto ...oo)
				XTAL_0EX
				{
					return apply([&](XTAL_DEF ...xs)
						XTAL_0FN_(XTAL_REF_(xs).efflux(oo...) |...| -1));
				}


				///\
				Forwards the control *tail* to `arguments`, bypassing `self`. \
				If `~N_parity`, the argument at `N_parity` receives the full control. \

				template <int N_parity=-1>
				XTAL_FNX influx_request_tail(auto o, auto ...oo)
				XTAL_0EX
				{
					if constexpr (N_parity == -1)
					{	return influx_request(_std::move(oo)...);
					}
					else
					{	static_assert(0 <= N_parity);
						return [&] <auto ...Ns>(seek_t<Ns...>)
							XTAL_0FN_(argument<N_parity>().influx(o, oo...) |...| argument<(N_parity <= Ns) + Ns>().influx(oo...))
						(seek_v<sizeof...(Xs) - 1>);
					}
				}
				///\
				Forwards the control *head* to `arguments`, bypassing `self`. \
				If `~N_parity`, the argument at `N_parity` receives the full control. \

				template <int N_parity=-1>
				XTAL_FNX efflux_request_head(auto o, auto ...oo)
				XTAL_0EX
				{
					if constexpr (N_parity == -1)
					{	return efflux_request(_std::move(o));
					}
					else
					{	static_assert(0 <= N_parity);
						return [&] <auto ...Ns>(seek_t<Ns...>)
							XTAL_0FN_(argument<N_parity>().efflux(o, oo...) |...| argument<(N_parity <= Ns) + Ns>().efflux(o))
						(seek_v<sizeof...(Xs) - 1>);
					}
				}

			};
		};

	};
};


////////////////////////////////////////////////////////////////////////////////
///\
Produces a decorator `subtype<S>` that defines `T` with `As...::subtype` applied. \

template <typename T>
struct define
{
	using subkind = _retail::define<T>;

	template <any_q S>
	class subtype: public compose_s<S, subkind>
	{
		friend T;
		using co = compose_s<S, subkind>;
	
	public:
		using co::co;
		using co::self;

		///\
		\returns `true` if the pointers are identical, `false` otherwise.

		XTAL_OP2_(bool) == (subtype const &t)
		XTAL_0FX
		{
			return this == _std::addressof(t);
		}

		///\
		\returns the application of `reify()` to the supplied arguments. \

		/*/
		XTAL_RN2_(XTAL_OP2() (XTAL_DEF ...xs)
		,	self().template method<>(XTAL_REF_(xs)...)
		)
		/*/
		XTAL_OP2() (XTAL_DEF ...xs)
		XTAL_0EX
		{
			return self().template method<>(XTAL_REF_(xs)...);
		}
		XTAL_OP2() (XTAL_DEF ...xs)
		XTAL_0FX
		{
			return self().template method<>(XTAL_REF_(xs)...);
		}
		/***/
		///\
		\returns the `lambda` abstraction of `method`, \
			with template parameters resolved by `control::dispatch`. \

		XTAL_RN2_(template <typename ...Xs> XTAL_FN2 reify()
		,	[this](XTAL_DEF ...xs) XTAL_0FN_(self().template method<>(XTAL_REF_(xs)...))
		)
		
		///\
		\returns the function corresponding to the currently resolved parameters. \

		XTAL_FN2 deify(auto const &f)
		XTAL_0FX
		{
			return f;
		}

		template <typename ...Xs>
		struct being
		{
			template <typename X>
			struct argument
			{
				using type = X&&;
			};
			template <based_q X>
			struct argument<X>
			{
				using type = based_t<X> const &;
			};
			template <typename X>
			using argument_t = typename argument<X>::type;

			template <auto ...Ms>
			struct solve
			{
				using return_t = decltype(XTAL_VAL_(T&).template method<Ms...>(XTAL_VAL_(Xs)...));
				using method_t = return_t (T::*) (argument_t<Xs>...);

			};
			template <auto ...Ms> requires requires (T const t) {t.template method<Ms...>(XTAL_VAL_(Xs)...);}
			struct solve<Ms...>
			{
				using return_t = decltype(XTAL_VAL_(T const &).template method<Ms...>(XTAL_VAL_(Xs)...));
				using method_t = return_t (T::*) (argument_t<Xs>...) const;

			};
			
			template <auto ...Ms>
			using method_t = typename solve<Ms...>::method_t;

			template <auto ...Ms>
			XTAL_FZ1_(method_t<Ms...>) method = &T::template method<Ms...>;
		
		};

	};
};
template <typename T>
struct refine
{
	using subkind = _retail::refine<T>;

	template <any_q S>
	class subtype: public compose_s<S, subkind>
	{
		using co = compose_s<S, subkind>;
	
	public:
		using co::co;
		using co::self;

	};
	template <any_q S> requires constant_q<typename compose_s<S, subkind>::linked>
	class subtype<S>: public compose_s<S, subkind>
	{
		using co = compose_s<S, subkind>;
	
	public:
		using co::co;
		using co::self;

		template <typename ...Xs>
		struct combined
		{
			using kind = typename T::template bind<Xs...>;
			using type = typename _retail::confined<kind>::template subtype<S>;

		};
		template <typename ...Xs>
		using     bind_t = typename combined<Xs...>::type;
		XTAL_LET  bind_f = [](XTAL_DEF ...xs) XTAL_0FN_(bind_t<decltype(xs)...>(XTAL_REF_(xs)...));
		XTAL_RN4_(XTAL_FN2 bind_to(XTAL_DEF ...xs)
		,	bind_t<decltype(xs)...>(self(), XTAL_REF_(xs)...)
		)

	};
};


////////////////////////////////////////////////////////////////////////////////
///\
Produces a decorator `subtype<S>` that proxies `U`. \

template <typename U>
struct defer
{
	using subkind = _retail::defer<U>;

	template <any_q S>
	class subtype: public compose_s<S, subkind>
	{
		using co = compose_s<S, subkind>;
	
	public:
		using co::co;
		using co::self;
		using co::head;

		///\
		Constant redirection. \

		template <auto...>
		XTAL_FN2 method()
		XTAL_0FX
		{
			return head();
		}

	};
	template <any_q S> requires _std::invocable<U>
	class subtype<S>: public compose_s<S, subkind>
	{
		using co = compose_s<S, subkind>;
	
	public:
		using co::co;
		using co::self;
		using co::head;

		///\
		Deferred implementation of `T::value`. \

		template <auto ...>
		XTAL_FN2 method(XTAL_DEF ...xs)
		XTAL_0FX
		{
			return head() (XTAL_REF_(xs)...);
		}

	};
};
template <any_q U>
struct defer<U>
{
	using subkind = _retail::defer<U>;

	template <any_q S>
	class subtype: public compose_s<S, subkind>
	{
		using co = compose_s<S, subkind>;
	
	public:
		using co::co;
		using co::self;
		using co::head;

		///\
		Deferred implementation of `T::value`. \

		XTAL_RN2_(template <auto ...Ms> XTAL_FN2 method(XTAL_DEF ...xs)
		,	head().template method<Ms...>(XTAL_REF_(xs)...)
		)

	};
};
///\
Produces a decorator `subtype<S>` that lifts the operations of `U`. \

template <typename U>
struct refer: _retail::refer<U>
{
};

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
