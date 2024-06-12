#pragma once
#include "../flux/any.hh"// `_retail`

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

	template <class S>
	class subtype : public bond::compose_s<S, subkind>
	{
		friend T;
		using S_ = bond::compose_s<S, subkind>;
	
	public:
		using S_::S_;
		using S_::self;


		///\returns `true` if the pointers are identical, `false` otherwise. \

		XTAL_DEF_(return,inline)
		XTAL_LET operator == (subtype const &t)
		XTAL_0FX -> bool {return this == _std::addressof(t);}
		
		///\
		Alias of `functor(...)`. \
		
		XTAL_TO2_(XTAL_DEF_(return,inline)
		XTAL_LET operator () (auto &&...xs),
			self().functor(XTAL_REF_(xs)...)
		)
		
		///\
		The default `functor` defers to the static `function` (only when `this` is `const`). \

		template <auto ...Is>
		XTAL_DEF_(return,inline)
		XTAL_REF functor(auto &&...xs)
		XTAL_0FX
		{
			return T::template function<Is...>(XTAL_REF_(xs)...);
		}

		///\returns the lambda abstraction of `functor`, \
		resolved by the `[../occur/any.ipp#dispatch]`ed parameters bound to `this`. \

		XTAL_DO4_(template <class ...Xs>
		XTAL_DEF_(return,inline)
		XTAL_REF refunctor(nominal_q auto const ...Is),
		{
			if constexpr (0 == sizeof...(Is)) {
				return [this] XTAL_1FN_(self().functor);
			}
			else {
				return [this, Is...] XTAL_1FN_(self().template functor<Is...>);
			}
		})
		
	protected:
		template <class ...Xs>
		XTAL_DEF_(return,inline)
		XTAL_REF defunctor(nominal_q auto const &...Is)
		XTAL_0FX
		{
			return defunctor(figure<Xs...>::template type<Is...>::value);
		}
		XTAL_DEF_(return,inline)
		XTAL_REF defunctor(auto const &value)
		XTAL_0FX
		{
			return value;
		}

		///\
		Defines the subtype-indexed function-pointer table, \
		dynamically indexed by the underlying subtype `T`, \
		and statically-generated from `functor<Is...>` with `sizeof...(Is)` entries. \

		template <class ...Xs>
		struct figure
		{
			template <class   X> struct argument      {using type = X      &&;};
			template <based_q X> struct argument<X>   {using type = X const &;};
			template <class   X> using  argument_t = typename argument<X>::type;

			template <auto ...Is>
			class type
			{
				using Y_ = decltype(XTAL_ANY_(T &).
					template functor<Is...>(XTAL_ANY_(argument_t<Xs>)...)
				);

			public:
				using value_type = Y_(T::*) (argument_t<Xs>...);
				static constexpr value_type value = &T::template functor<Is...>;

			};
			template <auto ...Is>
			requires
				XTAL_REQ_(XTAL_ANY_(T const &).
					template functor<Is...>(XTAL_ANY_(argument_t<Xs>)...)
				)
			class type<Is...>
			{
				using Y_ = decltype(XTAL_ANY_(T const &).
					template functor<Is...>(XTAL_ANY_(argument_t<Xs>)...)
				);

			public:
				using value_type = Y_(T::*) (argument_t<Xs>...) const;
				static constexpr value_type value = &T::template functor<Is...>;

			};
		};

	private:
		template <class ...Xs>
		using S_compound = typename S_::template compound<Xs...>;

	public:
		///\
		Thunkifies the underlying `T` by capturing the arguments `Xs...`. \

		template <class ...Xs>
		struct compound : compound<let_t<Xs>...>
		{
		};
		template <class ...Xs> requires any_q<Xs...>
		struct compound<Xs...>
		{
			using Xs_packed = typename S_compound<Xs...>::Xs_packed;
			
			using Y_result = _std::invoke_result_t<T, Xs...>;
			using Y_return = iteratee_t<Y_result>;
			
			using subkind = bond::compose<void
			,	defer<T>
			,	S_compound<Xs...>
			>;
			template <any_q R>
			class subtype : public bond::compose_s<R, subkind>
			{
				using R_ = bond::compose_s<R, subkind>;

			public:// CONSTRUCT
				using R_::R_;
				///\
				Initializes `slots` using the arguments supplied. \

				XTAL_CON_(explicit) subtype(Xs &&...xs)
				XTAL_0EX
				:	subtype(T{}, XTAL_REF_(xs)...)
				{}
				XTAL_CON_(explicit) subtype(fungible_q<S_> auto &&t, Xs &&...xs)
				XTAL_0EX
				//\
				:	R_(XTAL_REF_(t), Xs_packed(process::let_f(XTAL_REF_(xs))...))
				:	R_(XTAL_REF_(t), Xs_packed(XTAL_REF_(xs)...))
				{}

			public:// OPERATE
				using R_::self;
				using R_::slots;
				using R_::functor;
				///\
				Evaluates the lifted `functor` using the bound slots. \

				template <auto ...Is>
				XTAL_DEF_(return,inline)
				XTAL_REF functor()
				XTAL_0EX
				{
					return slots().apply([this] XTAL_1FN_(R_::template functor<Is...>));
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
	
		template <class ...Xs>
		using S_compound = typename S_::template compound<Xs...>;

	public:// CONSTRUCT
		using S_::S_;

	public:// ACCESS
		using S_::self;

	public:// BIND

		template <class ...Xs>
		struct binding
		{
			using subkind = confined<S_compound<Xs...>>;

			template <class R>
			using subtype = bond::compose_s<R, subkind>;
			using    type = subtype<S_>;

		};
		template <class ...Xs>
		XTAL_USE binding_t = typename binding<Xs...>::type;
		/*/
		XTAL_DEF_(return,inline,static)
		XTAL_LET     binding_f(auto &&...xs)
		XTAL_0EX_TO_(binding_t<decltype(xs)...>(XTAL_REF_(xs)...))
		/*/
		XTAL_DEF_(return,inline,static)
		XTAL_LET     binding_f(                  auto &&...xs)
		XTAL_0EX_TO_(binding_t<decltype(xs)...>(              process::let_f(XTAL_REF_(xs))...))
		/***/
		XTAL_DEF_(return,inline,static)
		XTAL_LET     binding_f(is_q<T> auto &&t, auto &&...xs)
		XTAL_0EX_TO_(binding_t<decltype(xs)...>(XTAL_REF_(t), process::let_f(XTAL_REF_(xs))...))
		
		XTAL_TO4_(template <class ...Xs>
		XTAL_DEF_(return,inline)
		XTAL_LET bind(Xs &&...xs), binding_f(self(), XTAL_REF_(xs)...)
		)

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
		using U0 = typename S_::template head_t<nominal_t<0>>;
		using U1 = typename S_::template head_t<nominal_t<1>>;
	
	public:// CONSTRUCT
		using S_::S_;

	public:// INVOCATION
		///\note\
		Adjacent `defer`red processes are composed. \

		XTAL_DO2_(template <auto ...Is>
		XTAL_DEF_(return,inline)
		XTAL_REF functor(auto &&...xs),
		{
			XTAL_IF0
			XTAL_0IF (    any_q<U1>) {return functor_<Is...>(S_::template functor <Is...>(XTAL_REF_(xs)...));}
			XTAL_0IF (not any_q<U1>) {return functor_<Is...>(                             XTAL_REF_(xs)... );}
		})
		template <auto ...Is>
		XTAL_DEF_(return,inline,static)
		XTAL_REF function(auto &&...xs)
		XTAL_0EX
		{
			XTAL_IF0
			XTAL_0IF (    any_q<U1>) {return function_<Is...>(S_::template function<Is...>(XTAL_REF_(xs)...));}
			XTAL_0IF (not any_q<U1>) {return function_<Is...>(                             XTAL_REF_(xs)... );}
		}

	private:

		XTAL_DO2_(template <auto ...Is>
		XTAL_DEF_(return,inline)
		XTAL_REF functor_(auto &&...xs),
		{
			XTAL_IF0
			XTAL_0IF XTAL_REQ_TO_(S_::head().template functor<Is...>(XTAL_REF_(xs)...))
			XTAL_0IF XTAL_REQ_TO_(S_::head()                        (XTAL_REF_(xs)...))
			XTAL_0IF_(default) {return S_::head(); static_assert(0 == sizeof...(xs));}
		})
		template <auto ...Is>
		XTAL_DEF_(return,inline,static)
		XTAL_REF function_(auto &&...xs)
		XTAL_0EX
		{
			XTAL_IF0
			XTAL_0IF XTAL_REQ_TO_(U0{}.template function<Is...>(XTAL_REF_(xs)...))
			XTAL_0IF XTAL_REQ_TO_(U0{}                         (XTAL_REF_(xs)...))
			XTAL_0IF_(default) {return invoke_f<U0>(XTAL_REF_(xs)...);}
		}

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
