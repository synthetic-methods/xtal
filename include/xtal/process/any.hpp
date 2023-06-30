#pragma once
#include "../conflux/any.hpp"// `_retail`






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
		using S_ = compose_s<S, subkind>;
	
	public:
		using S_::S_;
		using S_::self;

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

		XTAL_RN2_(template <typename ...Xs>
		XTAL_FN2 reify(), [this](XTAL_DEF ...xs) XTAL_0FN_(operator() (XTAL_REF_(xs)...))
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
			XTAL_LET_(typename resolve<Ms...>::method_t) method = &T::template method<Ms...>;
		
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
		using S_ = compose_s<S, subkind>;
	
	public:
		using S_::S_;
		using S_::self;

		template <typename ...Xs>
		struct bind
		{
			using kind = typename S_::template bind<Xs...>;
			using type = typename _retail::confined<kind>::template subtype<S>;

		};
		template <typename ...Xs>
		using     bind_t = typename bind<Xs...>::type;
		XTAL_LET  bind_f =   [](XTAL_DEF ...xs) XTAL_0FN_(bind_t<decltype(xs)...>(        XTAL_REF_(xs)...));
		XTAL_RN4_(XTAL_FN2 bond(XTAL_DEF ...xs),          bind_t<decltype(xs)...>(self(), XTAL_REF_(xs)...))

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
		using S_ = compose_s<S, subkind>;
	
	public:
		using S_::S_;
		using S_::self;
		using S_::head;

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
		using S_ = compose_s<S, subkind>;
	
	public:
		using S_::S_;
		using S_::self;
		using S_::head;

		///\
		Deferred implementation of `T::value`. \

		XTAL_RN2_(template <auto ...>
		XTAL_FN2 method(XTAL_DEF ...xs), head() (XTAL_REF_(xs)...)
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
		using S_ = compose_s<S, subkind>;
	
	public:
		using S_::S_;
		using S_::self;
		using S_::head;

		///\
		Deferred implementation of `T::value`. \

		XTAL_RN2_(template <auto ...Ms>
		XTAL_FN2 method(XTAL_DEF ...xs), head().template method<Ms...>(XTAL_REF_(xs)...)
		)

	};
};
template <typename U>
struct refer
:	_retail::refer<U>
{
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
