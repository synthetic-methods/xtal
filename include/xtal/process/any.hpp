#pragma once
#include "../context/any.hpp"//_detail






XTAL_ENV_(push)
namespace xtal::process
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

namespace _detail = xtal::context;
#include "../common/any.hxx"

////////////////////////////////////////////////////////////////////////////////
///\
Produces a decorator `subtype<S>` that defines `T` with `As...::subtype` applied. \

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
		///\
		\returns the `lambda` abstraction of `method`, \
			with template parameters resolved by `message::dispatch`. \

		template <typename ...Xs>
		XTAL_FN2 reify()
		XTAL_0EX
		{
			return [this] (XTAL_DEF ...xs) XTAL_0FN_(self().template method<>(XTAL_REF_(xs)...));
		}
		template <typename ...Xs>
		XTAL_FN2 reify()
		XTAL_0FX
		{
			return [this] (XTAL_DEF ...xs) XTAL_0FN_(self().template method<>(XTAL_REF_(xs)...));
		}
		
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
			template <auto ...Ms>
			requires
			requires (T const t) {t.template method<Ms...>(XTAL_VAL_(Xs)...);}
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
////////////////////////////////////////////////////////////////////////////////

template <typename T>
struct refine
{
	using subkind = _detail::refine<T>;

	template <any_q S>
	using subtype = common::compose_s<S, subkind>;

};

////////////////////////////////////////////////////////////////////////////////
///\
Produces a decorator `subtype<S>` that proxies `U`. \

template <typename U>
struct defer
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
		Constant redirection. \

		template <auto...>
		XTAL_FN2 method()
		XTAL_0FX
		{
			return head();
		}

	};
	template <any_q S>
	requires _std::invocable<U>
	class subtype<S>: public common::compose_s<S, subkind>
	{
		using co = common::compose_s<S, subkind>;
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
		Deferred implementation of `T::value`. \

		template <auto ...Ms>
		XTAL_FN2 method(XTAL_DEF ...xs)
		XTAL_0EX
		{
			return head().template method<Ms...>(XTAL_REF_(xs)...);
		}
		template <auto ...Ms>
		XTAL_FN2 method(XTAL_DEF ...xs)
		XTAL_0FX
		{
			return head().template method<Ms...>(XTAL_REF_(xs)...);
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
