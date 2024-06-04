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

		XTAL_OP2_(bool) == (subtype const &t)
		XTAL_0FX {return this == _std::addressof(t);}
		
		///\
		Alias of `functor(...)`. \
		
		XTAL_TO2_(
		XTAL_OP2 () (auto &&...xs),
			self().functor(XTAL_REF_(xs)...)
		)
		
		///\
		The default `functor` defers to the static `function` (only when `this` is `const`). \

		template <auto ...Is>
		XTAL_DEF_(return,inline)
		XTAL_TN1 functor(auto &&...xs)
		XTAL_0FX
		{
			return T::template function<Is...>(XTAL_REF_(xs)...);
		}

		///\returns the lambda abstraction of `functor`, \
		resolved by the `[../occur/any.ipp#dispatch]`ed parameters bound to `this`. \

		XTAL_DO4_(template <class ...Xs>
		XTAL_DEF_(return,inline)
		XTAL_TN1 refunctor(Integral_q auto const ...is),
		{
			if constexpr (0 == sizeof...(is)) {
				return [this] XTAL_1FN_(self().functor);
			}
			else {
				return [this, is...] XTAL_1FN_(self().template functor<is...>);
			}
		})
		
	protected:
		template <class ...Xs>
		XTAL_TN2 refunctor_(Integral_q auto const &...is)
		XTAL_0FX
		{
			return refunctor_(figure<Xs...>::template type<is...>::value);
		}
		XTAL_TN2 refunctor_(auto const &value)
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
				using Y_ = decltype(XTAL_ANY_(T &).template functor<Is...>(XTAL_ANY_(argument_t<Xs>)...));

			public:
				XTAL_USE value_type = Y_(T::*) (argument_t<Xs>...);
				XTAL_LET value = static_cast<value_type>(&T::template functor<Is...>);

			};
			template <auto ...Is>
			XTAL_REQ
			XTAL_REQ_(XTAL_ANY_(T const &).template functor<Is...>(XTAL_ANY_(argument_t<Xs>)...))
			class type<Is...>
			{
				using Y_ = decltype(XTAL_ANY_(T const &).template functor<Is...>(XTAL_ANY_(argument_t<Xs>)...));

			public:
				XTAL_USE value_type = Y_(T::*) (argument_t<Xs>...) const;
				XTAL_LET value = static_cast<value_type>(&T::template functor<Is...>);

			};
		};

	public:

		///\
		Thunkifies the underlying `T` by capturing the arguments `Xs...`. \

		template <class ...Xs>
		struct binding : binding<let_t<Xs>...>
		{
		};
		template <class ...Xs> requires any_q<Xs...>
		struct binding<Xs...>
		{
			using signature_t = cell::packed_t<Xs...>;
			
			using Y_result = _std::invoke_result_t<T, Xs...>;
			using Y_return = iteratee_t<Y_result>;
			
			using subkind = bond::compose<void
			,	defer<T>
			,	cell::defer<signature_t>
			>;

			template <any_q R>
			class subtype : public bond::compose_s<R, subkind>
			{
				using R_ = bond::compose_s<R, subkind>;

			public:
				using R_::R_;
				///\
				Initializes `slots` using the arguments supplied. \

				XTAL_CXN subtype(Xs &&...xs)
				XTAL_0EX
				:	subtype(T{}, XTAL_REF_(xs)...)
				{}
				XTAL_CXN subtype(fungible_q<T> auto &&t, Xs &&...xs)
				XTAL_0EX
				:	R_(XTAL_REF_(t), signature_t(XTAL_REF_(xs)...))
				{}

			public:// ACCESS
				using R_::self;

				XTAL_TO4_(XTAL_TN2 slots(), R_::template head<1>())
				
				template <size_t ...Ns>
				XTAL_TN2 slot()
				XTAL_0EX
				{
					return bond::pack_item_f<Ns...>(slots());
				}
				template <class F>
				XTAL_TN2 apply()
				XTAL_0FX
				{
					return apply([] XTAL_1FN_(F));
				}
				XTAL_DO2_(XTAL_TN2 apply(auto &&f),
				{
					//\
					return _std::apply(XTAL_REF_(f), slots());
					return slots().apply(XTAL_REF_(f));
				})


			public:// OPERATION
				using R_::functor;
				///\
				Evaluates the lifted `functor` using the bound slots. \

				template <auto ...Is>
				XTAL_DEF_(return,inline)
				XTAL_TN1 functor()
				XTAL_0EX
				{
					return apply([this] XTAL_1FN_(R_::template functor<Is...>));
				}
			
			public:// FLUXION
			//	using R_::influx;
			//	using R_::efflux;

				///\returns the result of `influx`ing `self` then  (if `& 1`) `slots`. \

				XTAL_TNX influx(auto &&...oo)
				XTAL_0EX
				{
					return XTAL_FLX_(self().influx_push(oo...)) (R_::influx(XTAL_REF_(oo)...));
				}
				///\returns the result of `efflux`ing `slots` then (if `& 1`) `self`. \

				XTAL_TNX efflux(auto &&...oo)
				XTAL_0EX
				{
					return XTAL_FLX_(R_::efflux(oo...)) (self().efflux_pull(XTAL_REF_(oo)...));
				}

				///\note\
				If prefixed by `null_t()`, forwards the occur to all `slots`. \

				XTAL_TNX influx(null_t, auto &&...oo) XTAL_0EX {return self().influx_push(XTAL_REF_(oo)...);}
				XTAL_TNX efflux(null_t, auto &&...oo) XTAL_0EX {return self().efflux_pull(XTAL_REF_(oo)...);}

				///\note\
				If prefixed by `Integral_q`, forwards the occur to the `slot` specified. \

				XTAL_TNX influx(Integral_q auto i, auto &&...oo) XTAL_0EX {return slot<i>().influx(XTAL_REF_(oo)...);}
				XTAL_TNX efflux(Integral_q auto i, auto &&...oo) XTAL_0EX {return slot<i>().efflux(XTAL_REF_(oo)...);}

				///\
				Forwards the occur to all `slots`, bypassing `self`. \

				XTAL_TNX influx_push(auto &&...oo)
				XTAL_0EX
				{
					return apply([...oo=XTAL_REF_(oo)] (auto &&...xs)
						XTAL_0FN_(XTAL_REF_(xs).influx(oo...) &...& -1)
					);
				}
				XTAL_TNX efflux_pull(auto &&...oo)
				XTAL_0EX
				{
					return apply([...oo=XTAL_REF_(oo)] (auto &&...xs)
						XTAL_0FN_(XTAL_REF_(xs).efflux(oo...) &...& -1)
					);
				}
				///\
				Forwards the occur-tail to all `slots`, bypassing `self`. \
				If `~N_slot`, the slot at `N_slot` receives the full occur. \

				template <int N_slot=-1>
				XTAL_TNX influx_push_tail(auto o, auto ...oo)
				XTAL_0EX
				{
					if constexpr (N_slot == -1) {
						return influx_push(XTAL_MOV_(oo)...);
					}
					else {
						static_assert(0 <= N_slot);
						return [&] <auto ...I>(bond::seek_t<I...>)
							XTAL_0FN_(slot<N_slot>().influx(o, oo...) &...& slot<(N_slot <= I) + I>().influx(oo...))
						(bond::seek_s<sizeof...(Xs) - 1> {});
					}
				}
				template <int N_slot=-1>
				XTAL_TNX efflux_pull_tail(auto o, auto ...oo)
				XTAL_0EX
				{
					if constexpr (N_slot == -1) {
						return efflux_pull(XTAL_MOV_(oo)...);
					}
					else {
						static_assert(0 <= N_slot);
						return [&] <auto ...I>(bond::seek_t<I...>)
							XTAL_0FN_(slot<N_slot>().efflux(o, oo...) &...& slot<(N_slot <= I) + I>().efflux(oo...))
						(bond::seek_s<sizeof...(Xs) - 1> {});
					}
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
		using S_binding = typename S_::template binding<Xs...>;

	public:
		using S_::S_;
		using S_::self;

		template <class ...Xs>
		struct combined : S_binding<Xs...>
		{
			using kind = confined<S_binding<Xs...>>;
			using type = bond::compose_s<S_, kind>;
		
		};
		template <class ...Xs>
		XTAL_USE bind_t = typename combined<Xs...>::type;
		
		XTAL_FN2 bind_f(                  auto &&...xs) XTAL_0EX {return bind_t<decltype(xs)...>(              XTAL_REF_(xs)...);}
		XTAL_FN2 bind_f(is_q<T> auto &&t, auto &&...xs) XTAL_0EX {return bind_t<decltype(xs)...>(XTAL_REF_(t), XTAL_REF_(xs)...);}

		XTAL_TO4_(template <class ...Xs>
		XTAL_TN2 bind(Xs &&...xs), bind_f(self(), XTAL_REF_(xs)...)
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
		using U0 = typename S_::template head_t<Cardinal_0>;
		using U1 = typename S_::template head_t<Cardinal_1>;
	
	public:// CONSTRUCTION
		using S_::S_;

	public:// INVOCATION
		///\note\
		Adjacent `defer`red processes are composed. \

		XTAL_DO2_(template <auto ...Is>
		XTAL_DEF_(return,inline)
		XTAL_TN1 functor(auto &&...xs),
		{
			XTAL_IF0
			XTAL_0IF (    any_q<U1>) {return functor_<Is...>(S_::template functor <Is...>(XTAL_REF_(xs)...));}
			XTAL_0IF (not any_q<U1>) {return functor_<Is...>(                             XTAL_REF_(xs)... );}
		})
		XTAL_DO0_(template <auto ...Is>
		XTAL_DEF_(return,inline)
		XTAL_FN1 function(auto &&...xs),
		{
			XTAL_IF0
			XTAL_0IF (    any_q<U1>) {return function_<Is...>(S_::template function<Is...>(XTAL_REF_(xs)...));}
			XTAL_0IF (not any_q<U1>) {return function_<Is...>(                             XTAL_REF_(xs)... );}
		})

	private:

		XTAL_DO2_(template <auto ...Is>
		XTAL_DEF_(return,inline)
		XTAL_TN1 functor_(auto &&...xs),
		{
			XTAL_IF0
			XTAL_0IF   XTAL_REQ_TO_(S_::head().template functor<Is...>(XTAL_REF_(xs)...))
			XTAL_0IF   XTAL_REQ_TO_(S_::head()                        (XTAL_REF_(xs)...))
			XTAL_0IF_(else) {return S_::head(); static_assert(0 == sizeof...(xs));}
		})
		XTAL_DO0_(template <auto ...Is>
		XTAL_DEF_(return,inline)
		XTAL_FN1 function_(auto &&...xs),
		{
			XTAL_IF0
			XTAL_0IF   XTAL_REQ_TO_(U0{}.template function<Is...>(XTAL_REF_(xs)...))
			XTAL_0IF   XTAL_REQ_TO_(U0{}                         (XTAL_REF_(xs)...))
			XTAL_0IF_(else) {return invoke_f<U0>(XTAL_REF_(xs)...);}
		})

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
