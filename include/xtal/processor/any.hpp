#pragma once
#include "../process/any.hpp"//_detail
#include "../message/all.hpp"





XTAL_ENV_(push)
namespace xtal::processor
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

namespace _detail = xtal::process;
#include "../common/any.ipp"

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

		template <typename... Xs>
		struct bind
		{
			using resize_u = message::resize_t<>;
			using serial_u = message::serial_t<>;

			using signature_t = collect_t<processor::let_t<Xs>...>;
			using signature   = collect<Xs...>;

			using subkind = compose<context::defer<signature_t>
			,	resize_u::attach
			,	serial_u::attach
			,	_detail::defer<T>
			>;

			template <any_q _S>
			class subtype: public compose_s<_S, subkind>
			{
				using co = compose_s<_S, subkind>;

			protected:
				using result_t = typename signature::template result_t<T>;

				XTAL_RE4_(XTAL_FN2 arguments(), co::head())

			public:
				using co::co;

				///\
				Constructs `arguments` using the given arguments. \

				XTAL_NEW_(explicit) subtype(Xs&&... xs)
				XTAL_0EX
				:	co(collect_f(processor::let_f(XTAL_FWD_(Xs) (xs))...))
				{
				}

				///\
				Evaluates `T::value` using the bound arguments. \

				template <auto... Ms>
				XTAL_FN2 method()
				XTAL_0EX
				{
					return _std::apply([this] (XTAL_DEF... ws)
						XTAL_0FN_(co::template method<Ms...>(Xs(XTAL_REF_(ws))...))
					,	arguments()
					);
				}

				///\
				Forwards the message to `this` then the bound arguments. \

				XTAL_FN2_(iota_t) influx(XTAL_DEF... ws)
				XTAL_0EX
				{
					auto const &_ = co::influx(ws...);
					return !_?0:_ & _std::apply([&] (XTAL_DEF... xs)
						XTAL_0FN_(XTAL_REF_(xs).influx(ws...) | ...)
					,	arguments()
					);
				}

				///\
				Forwards the message to the bound arguments then `this`. \

				XTAL_FN2_(iota_t) efflux(XTAL_DEF... ws)
				XTAL_0EX
				{
					auto const &_ = _std::apply([&] (XTAL_DEF... xs)
						XTAL_0FN_(XTAL_REF_(xs).efflux(ws...) | ...)
					,	arguments()
					);
					return !_?0:_ & co::efflux(XTAL_REF_(ws)...);
				}

			protected:
				XTAL_LET disorder_v = requires (subtype const &t) {t.template method<>();};

			};
		};
		///\
		An isomorphic binding, representing a `1:1` mapping. \
		\
		NOTE: Messages are propagated using `std::move`, \
		signalling to the upstream `processor` that the data can be shared. \

		template <typename X>
		XTAL_IF1 isomorphic_q<typename collect<X>::template result_t<T>, X>
		struct bind<X>
		{
			using serial_u = message::serial_t<>;
			using resize_u = message::resize_t<>;

			using subkind = compose<context::defer<X>
			,	serial_u::attach
			,	resize_u::attach
			,	_detail::defer<T>
			>;

			template <any_q _S>
			class subtype: public compose_s<_S, subkind>
			{
				using co = compose_s<_S, subkind>;

			protected:
				using result_t = typename collect<X>::template result_t<T>;

				XTAL_RE4_(XTAL_FN2 argument(), co::head())

			public:
				using co::co;

				///\
				Evaluates `T::value` using the bound argument. \

				template <auto... Ms>
				XTAL_FN2 method()
				XTAL_0EX
				{
					return co::template method<Ms...>(argument());
				}

				///\
				Forwards the message to `this` then the bound argument. \

				XTAL_FN2_(iota_t) influx(XTAL_DEF... ws)
				XTAL_0EX
				{
					auto const &_ = [=, this] ()
						XTAL_0FN_(co::influx(_std::move(ws)...))
					();
					return !_?0:_ & processor::let_f(argument()).influx(XTAL_REF_(ws)...);
				}

				///\
				Forwards the message to the bound argument then `this`. \

				XTAL_FN2_(iota_t) efflux(XTAL_DEF... ws)
				XTAL_0EX
				{
					auto const &_ = [=, this] ()
						XTAL_0FN_(processor::let_f(argument()).efflux(_std::move(ws)...))
					();
					return !_?0:_ & co::efflux(XTAL_REF_(ws)...);
				}

			protected:
				XTAL_LET disorder_v = requires (subtype const &t) {t.template method<>();};

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

		template <typename... Xs>
		struct combined
		{
			using kind = _detail::confined<typename T::template bind<Xs...>>;
			using type = compose_s<S, kind>;

		};
		template <typename... Xs>
		using     bind_t = typename combined<Xs...>::type;
		XTAL_LET  bind_f = [] <typename... Xs>(Xs&&... xs)
		XTAL_0FN_(bind_t<Xs...>(XTAL_FWD_(Xs) (xs)...));

	};
};

////////////////////////////////////////////////////////////////////////////////
///\
Produces a decorator `subtype<S>` that proxies `U`. \

template <typename U>
struct defer
{
	using serial_u = message::serial_t<counted_t<>>;
//	using serial_n = message::serial_t<countee_t<>>;

	using subkind = compose<_detail::defer<U>, serial_u::attach>;
//	using subkind = compose<serial_u::attach, _detail::defer<U>>;

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
			auto const &m = co::template get<serial_u>();
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
				XTAL_OP2() (XTAL_DEF... xs) &&
				XTAL_0EX
				{
					return _v3::views::zip_with(_std::move(function_m), XTAL_REF_(xs)...);
				}

			};
		};
		template <typename F>
		using  zap_t = typename zap<F>::type;
		XTAL_LET  zap_f = [] <typename F>(F&&f)
		XTAL_0FN_(zap_t<F>(XTAL_FWD_(F) (f)));

		template <typename... Xs>
		struct review
		{
			using Ref = _std::invoke_result_t<U, iteratee_t<Xs>...>;
			using cat = _v3::ranges::category;
			XTAL_LET Cat = cat::forward|cat::sized;
			using type = _v3::ranges::any_view<Ref, Cat>;
		};
		template <typename... Xs>
		using review_t = typename review<Xs...>::type;

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
		XTAL_FN2 method(XTAL_DEF... xs)
		XTAL_0EX
		{
		//	TODO: It appears that both `category::sized` and `views::take` must be applied \
			for `size` to be defined by `ranges::view_interface`, but maybe there's a better way? \

			auto f = head().template reify<iteratee_t<decltype(xs)>...>();
			auto z = zap_f(_std::move(f)) (XTAL_REF_(xs)...);
			auto n = delta_t(z.size());
			return review_t<decltype(xs)...>(_std::move(z))|_v3::views::take(std::move(n));
		}
		template <auto...>
		XTAL_FN2 method(XTAL_DEF... xs)
		XTAL_0FX
		XTAL_IF2 (U const &u) {u.template method<>(XTAL_REF_(xs)...);}
		{
			auto f = head().template reify<iteratee_t<decltype(xs)>...>();
			return zap_f(std::move(f)) (XTAL_REF_(xs)...);
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
