#pragma once
#include "../flux/any.hh"// `_retail`

#include "../flux/brace.hh"
#include "../occur/all.hh"
#include "../resource/all.hh"
#include "../schedule/all.hh"

XTAL_ENV_(push)
namespace xtal::process
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

#include "./_retail.ii"
#include "./_detail.ii"


////////////////////////////////////////////////////////////////////////////////

template <class T>
struct define
{
	using subkind = _retail::define<T>;

	template <any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		friend T;
		
		using S_ = bond::compose_s<S, subkind>;
		using T_ = typename S_::self_type;
	
	public:// CONSTRUCT
		using S_::S_;

	protected:// CODEX
		///\
		Resolves the function pointer for the given `Xs...` and `Is...`, \
		providing the kernel for the table constructed by `occur/any.hh#dispatch`. \

		template <class ...Xs>
		struct codex
		{
			template <class   X> struct argument    {using type = X       &&;};
			template <based_q X> struct argument<X> {using type = X const  &;};
			template <class   X> using  argument_t = typename argument<X>::type;

			template <auto ...Is>
			class index
			{
				using Y = decltype(XTAL_ANY_(T &).template method<Is...>(XTAL_ANY_(argument_t<Xs>)...));

			public:
				using point_type = Y (T::*) (argument_t<Xs>...);
				static_assert(not _std::is_const_v<point_type>);
				static constexpr point_type point = &T::template method<Is...>;

			};
			template <auto ...Is>
				requires XTAL_TRY_(XTAL_ANY_(T const &).template method<Is...>(XTAL_ANY_(argument_t<Xs>)...))
			class index<Is...>
			{
				using Y = decltype(XTAL_ANY_(T const &).template method<Is...>(XTAL_ANY_(argument_t<Xs>)...));

			public:
				using point_type = _std::add_const_t<Y (T::*) (argument_t<Xs>...) const>;
				static_assert(_std::is_const_v<point_type>);
				static constexpr point_type point = &T::template method<Is...>;

			};
		};
		template <class ...Xs>
		XTAL_DEF_(return,inline)
		XTAL_LET deify(nominal_q auto const ...Is)
		XTAL_0FX -> decltype(auto)
		{
			return deify(codex<Xs...>::template index<Is...>::point);
		}
		XTAL_DEF_(return,inline)
		XTAL_LET deify(auto const &point)
		XTAL_0FX -> decltype(auto)
		{
			return point;
		}

	public:// OPERATE
		using S_::self;

		///\returns the lambda abstraction of `method`, \
		resolved by the `[../occur/any.ipp#dispatch]`ed parameters bound to `this`. \

		XTAL_DO2_(template <class ...Xs>
		XTAL_DEF_(return,inline)
		XTAL_LET reify(nominal_q auto const ...Is), -> decltype(auto)
		{
			return [=, this] XTAL_1FN_(self().operator());
		})

		///\
		Alias of `method(...)`, \
		with dynamic template-parameter aliasing if defined (\see `occur::any`). \
		
		XTAL_DO2_(template <auto ...Is>
		XTAL_DEF_(return,inline)
		XTAL_LET operator() (auto &&...xs),
		->	decltype(auto)
		{
			XTAL_IF0
			XTAL_0IF XTAL_TRY_TO_(self().template method<Is...>(XTAL_REF_(xs)...))
			XTAL_0IF XTAL_TRY_TO_(self().         method       (XTAL_REF_(xs)...))
		})
		
		///\
		The default `method` defers to the static `function` (only when `this` is `const`). \

		template <auto ...Is>
		XTAL_DEF_(return,inline)
		XTAL_LET method(auto &&...xs)
		XTAL_0FX -> decltype(auto)
			requires none_n<Is...> and XTAL_TRY_(T::         function       (XTAL_REF_(xs)...))
			or       some_n<Is...> and XTAL_TRY_(T::template function<Is...>(XTAL_REF_(xs)...))
		{
			XTAL_IF0
			XTAL_0IF (none_n<Is...>) {return T::         function       (XTAL_REF_(xs)...);}
			XTAL_0IF (some_n<Is...>) {return T::template function<Is...>(XTAL_REF_(xs)...);}
		}

	public:
		///\
		Thunkifies the underlying `T` by capturing the arguments `Xs...`. \

		template <class ...Xs> requires any_q<Xs...>
		struct bundle
		{
			using subkind = bond::compose<void
			,	defer<T_>
			,	flux::brace<Xs...>
			>;
			template <any_q R>
			class subtype : public bond::compose_s<R, subkind>
			{
				using R_ = bond::compose_s<R, subkind>;

				using H0_ = typename R_::template head_t<nominal_t<0>>;
				using H1_ = typename R_::template head_t<nominal_t<1>>;

			public:// CONSTRUCT
				using R_::R_;
				///\
				Initialize `slots` using the arguments supplied. \

				XTAL_CON_(explicit) subtype(Xs &&...xs)
				XTAL_0EX
				:	subtype(T{}, XTAL_REF_(xs)...)
				{}
				XTAL_CON_(explicit) subtype(fungible_q<S_> auto &&t, Xs &&...xs)
				XTAL_0EX
				:	R_(XTAL_REF_(t), H1_(XTAL_REF_(xs)...))
				{}

			public:// OPERATE
				using R_::slots;
				using R_::method;
				///\
				Evaluates the lifted `method` using the bound slots. \

				template <auto ...Is>
				XTAL_DEF_(return,inline)
				XTAL_LET method(auto &&...xs)
				XTAL_0EX -> decltype(auto)
				{
					XTAL_LET M = sizeof...(Xs);
					XTAL_LET N = sizeof...(xs);
					XTAL_IF0
					XTAL_0IF (M == N) {return R_::template method<Is...>(XTAL_REF_(xs) ()...);}
					XTAL_0IF (0 == N) {return         slots().apply([this] XTAL_1FN_(method));}
				}

			};
		};

	};
};

template <class T>
struct refine
{
	using subkind = _retail::refine<T>;

	template <any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;
	
	public:// CONSTRUCT
		using S_::S_;

	public:// BIND*
		template <class ...Xs>
		struct binds
		{
			using subkind = confined<typename S_::template bundle<process::let_t<Xs>...>>;

			template <class R>
			using subtype = bond::compose_s<R, subkind>;
			using    type = subtype<S_>;

		};
		template <class ...Xs>
		XTAL_USE binds_t = typename binds<Xs...>::type;

		XTAL_DEF_(return,inline,static)
		XTAL_LET binds_f(auto &&...xs)
		XTAL_0EX -> decltype(auto)
		{
			return binds_t<decltype(xs)...>(process::let_f(XTAL_REF_(xs))...);
		}
		XTAL_DEF_(return,inline,static)
		XTAL_LET binds_f(is_q<T> auto &&t, auto &&...xs)
		XTAL_0EX -> decltype(auto)
		{
			return binds_t<decltype(xs)...>(XTAL_REF_(t), process::let_f(XTAL_REF_(xs))...);
		}
		
		XTAL_DO4_(template <class ...Xs>
		XTAL_DEF_(return,inline)
		XTAL_LET bind(Xs &&...xs), -> decltype(auto)
		{
			return binds_f(S_::self(), XTAL_REF_(xs)...);
		})

	};
};


////////////////////////////////////////////////////////////////////////////////

template <class U>
struct defer
{
	using subkind = _retail::defer<U>;

	template <any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;
		using T_ = typename S_::self_type;
		using U0 = typename S_::template head_t<nominal_t<0>>;
		using U1 = typename S_::template head_t<nominal_t<1>>;
	
		///\
		Resolves `head` as either a function or value. \

		XTAL_DO2_(template <auto ...Is>
		XTAL_DEF_(return,inline)
		XTAL_LET _method(auto &&...xs),
		->	decltype(auto)
		{
			XTAL_IF0
			XTAL_0IF XTAL_TRY_TO_(S_::head().template operator()<Is...>(XTAL_REF_(xs)...))
			XTAL_0IF XTAL_TRY_TO_(S_::head()                           (XTAL_REF_(xs)...))
			XTAL_0IF_(default) {
				static_assert(0 == sizeof...(xs));
				return S_::head();
			}
		})
		XTAL_DO0_(template <auto ...Is>
		XTAL_DEF_(return,inline,static)
		XTAL_LET _function(auto &&...xs),
		->	decltype(auto)
		{
			XTAL_IF0
			XTAL_0IF (any_q<U0>) {return U0::template function<Is...>(XTAL_REF_(xs)...);}
			XTAL_0IF_(default)   {return U0{}                        (XTAL_REF_(xs)...);}
		})

	public:// FUNC*

		///\
		Resolves `head` as either a function or value, \
		composed with the inherited `method` or `function` if `defer`red. \

		///\note\
		Only `method`s participate in parameter resolution. \

		XTAL_DO2_(template <auto ...Is>
		XTAL_DEF_(return,inline)
		XTAL_LET method(auto &&...xs), -> decltype(auto)
		{
			XTAL_IF0
			XTAL_0IF (any_q<U1>) {return _method<Is...>(S::template method<Is...>(XTAL_REF_(xs)...));}
			XTAL_0IF_(default)   {return _method<Is...>(                          XTAL_REF_(xs)... );}
		})

		template <auto ...Is>
		XTAL_DEF_(return,inline,static)
		XTAL_LET function(auto &&...xs)
		XTAL_0EX -> decltype(auto)
			requires XTAL_TRY_TO_(_function<Is...>(S::template function<Is...>(XTAL_REF_(xs)...)))

		template <auto ...Is>
		XTAL_DEF_(return,inline,static)
		XTAL_LET function(auto &&...xs)
		XTAL_0EX -> decltype(auto)
			requires (not XTAL_TRY_(S::template function<Is...>(XTAL_REF_(xs)...)))
			          and XTAL_TRY_TO_(        _function<Is...>(XTAL_REF_(xs)...))

	public:// CONSTRUCT
		using S_::S_;

	};
};

template <class U>
struct refer
:	_retail::refer<U>
{
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
