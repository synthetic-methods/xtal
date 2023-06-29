#pragma once
#include "../conflux/any.hpp"// `_retail`

#include "../control/any.hpp"




XTAL_ENV_(push)
namespace xtal::process
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

namespace _retail = xtal::conflux;
#include "../concord/any.hxx"


////////////////////////////////////////////////////////////////////////////////

template <typename T>
struct define
{
	using subkind = _retail::define<T>;

	template <any_p S>
	class subtype: public compose_s<S, subkind>
	{
		friend T;
		using co = compose_s<S, subkind>;
	
	public:
		using co::co;
		using co::self;

		///\returns `true` if the pointers are identical, `false` otherwise.

		XTAL_OP2_(bool) == (subtype const &t)
		XTAL_0FX
		{
			return this == _std::addressof(t);
		}

		///\returns `reify()` applied to the given arguments. \

		XTAL_OP2() (XTAL_DEF ...xs) XTAL_0EX {return self().template method<>(XTAL_REF_(xs)...);}
		XTAL_OP2() (XTAL_DEF ...xs) XTAL_0FX {return self().template method<>(XTAL_REF_(xs)...);}

		///\returns the lambda abstraction of `method`, \
			with template parameters resolved by `message::dispatch`. \

		XTAL_RN2_(template <typename ...Xs> XTAL_FN2 reify()
		,	[this](XTAL_DEF ...xs) XTAL_0FN_(operator() (XTAL_REF_(xs)...))
		)

		///\returns the function corresponding to the currently resolved parameters. \

		template <typename ...Xs>
		XTAL_FN2 deify()
		XTAL_0FX
		{
			return deify(being<Xs...>::template method<>);
		}
		XTAL_FN2 deify(auto const &f0)
		XTAL_0FX
		{
			return f0;
		}

		template <typename ...Xs>
		struct being
		{
			template <auto ...Ms>
			struct resolve
			{
				using return_t = decltype(XTAL_VAL_(T &).template method<Ms...>(XTAL_VAL_(Xs)...));
				using method_t = return_t (T::*) (Xs const &&...);

			};
			template <auto ...Ms>
			requires
			requires (T const t)
			{
				t.template method<Ms...>(XTAL_VAL_(Xs)...);
			}
			struct resolve<Ms...>
			{
				using return_t = decltype(XTAL_VAL_(T const &).template method<Ms...>(XTAL_VAL_(Xs)...));
				using method_t = return_t (T::*) (Xs const &&...) const;

			};
			template <auto ...Ms>
			XTAL_FZ1_(typename resolve<Ms...>::method_t) method = &T::template method<Ms...>;
		
		};

	};
};
template <typename T>
struct refine
{
	using subkind = _retail::refine<T>;

	template <any_p S>
	class subtype: public compose_s<S, subkind>
	{
		using co = compose_s<S, subkind>;
	
	public:
		using co::co;
		using co::self;

		template <typename ...Xs>
		struct combined
		{
			using kind = typename T::template bond<Xs...>;
			using type = typename _retail::confined<kind>::template subtype<S>;

		};
		template <typename ...Xs>
		using     bind_t = typename combined<Xs...>::type;
		XTAL_LET  bind_f =   [](XTAL_DEF ...xs) XTAL_0FN_(bind_t<decltype(xs)...>(        XTAL_REF_(xs)...));
		XTAL_RN4_(XTAL_FN2 bind(XTAL_DEF ...xs),          bind_t<decltype(xs)...>(self(), XTAL_REF_(xs)...))

	};
};


////////////////////////////////////////////////////////////////////////////////

template <typename U>
struct defer
{
	using subkind = _retail::defer<U>;

	template <any_p S>
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
	template <any_p S> requires _std::invocable<U>
	class subtype<S>: public compose_s<S, subkind>
	{
		using co = compose_s<S, subkind>;
	
	public:
		using co::co;
		using co::self;
		using co::head;

		///\
		Deferred implementation of `T::value`. \

		XTAL_RN2_(template <auto ...> XTAL_FN2 method(XTAL_DEF ...xs)
		,	head() (XTAL_REF_(xs)...)
		)

	};
};
template <any_p U>
struct defer<U>
{
	using subkind = _retail::defer<U>;

	template <any_p S>
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
template <typename U>
struct refer
:	_retail::refer<U>
{
};


////////////////////////////////////////////////////////////////////////////////

template <typename ...As>
struct link
{
	using interrupt = typename control::confined_t<>::interrupt<0>;
	using interkind = compose<As..., interrupt>;
	
	using subkind = interkind;

	template <any_p S>
	class subtype: public compose_s<S, subkind>
	{
		using co = compose_s<S, subkind>;
		using T = typename co::self_t;

	public:
		using co::co;
		///\
		Thunkifies `T` by binding `Xs...`. \

		template <typename ...Xs>
		struct bond
		{
			using signature = bundle<Xs...>;
			using result_t  = typename signature::template invoke_t<T>;
			using return_t  = iteratee_t<result_t>;
			
			using subkind = compose<concord::defer<typename signature::type>, interkind, defer<T>>;

			template <any_p R>
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

			public:
				///\returns the result of `influx`ing `self` then  (if `& 1`) `arguments`. \

				XTAL_FNX influx(XTAL_DEF ...oo)
				XTAL_0EX
				{
					return XTAL_FLX_(self().influx_request(oo...)) (co::influx(XTAL_REF_(oo)...));
				}
				///\returns the result of `efflux`ing `arguments` then (if `& 1`) `self`. \

				XTAL_FNX efflux(XTAL_DEF ...oo)
				XTAL_0EX
				{
					return XTAL_FLX_(co::efflux(oo...)) (self().efflux_request(XTAL_REF_(oo)...));
				}

				///\note\
				If prefixed by `null_t()`, the message is forwarded directly to `arguments`. \

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
				Forwards the message to `arguments`, bypassing `self`. \

				XTAL_FNX influx_request(auto ...oo)
				XTAL_0EX
				{
					return apply([&](XTAL_DEF ...xs)
						XTAL_0FN_(XTAL_REF_(xs).influx(oo...) &...& -1));
				}
				XTAL_FNX efflux_request(auto ...oo)
				XTAL_0EX
				{
					return apply([&](XTAL_DEF ...xs)
						XTAL_0FN_(XTAL_REF_(xs).efflux(oo...) &...& -1));
				}


				///\
				Forwards the message *tail* to `arguments`, bypassing `self`. \
				If `~I_parity`, the argument at `I_parity` receives the full message. \

				template <int I_parity=-1>
				XTAL_FNX influx_request_tail(auto o, auto ...oo)
				XTAL_0EX
				{
					if constexpr (I_parity == -1)
					{	return influx_request(_std::move(oo)...);
					}
					else
					{	static_assert(0 <= I_parity);
						return [&] <auto ...I>(seek_t<I...>)
							XTAL_0FN_(argument<I_parity>().influx(o, oo...) &...& argument<(I_parity <= I) + I>().influx(oo...))
						(seek_v<sizeof...(Xs) - 1>);
					}
				}
				///\
				Forwards the message *head* to `arguments`, bypassing `self`. \
				If `~I_parity`, the argument at `I_parity` receives the full message. \

				template <int I_parity=-1>
				XTAL_FNX efflux_request_head(auto o, auto ...oo)
				XTAL_0EX
				{
					if constexpr (I_parity == -1)
					{	return efflux_request(_std::move(o));
					}
					else
					{	static_assert(0 <= I_parity);
						return [&] <auto ...I>(seek_t<I...>)
							XTAL_0FN_(argument<I_parity>().efflux(o, oo...) &...& argument<(I_parity <= I) + I>().efflux(o))
						(seek_v<sizeof...(Xs) - 1>);
					}
				}

			};
		};

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
