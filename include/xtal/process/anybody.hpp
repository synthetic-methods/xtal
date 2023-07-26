#pragma once
#include "./any.hpp"






XTAL_ENV_(push)
namespace xtal::process
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <class T>
struct define
{
	using subkind = _retail::define<T>;

	template <any_q S>
	class subtype: public compose_s<S, subkind>
	{
		friend T;
		using S_ = compose_s<S, subkind>;
	
	public:
		using S_::S_;
		using S_::self;


		///\returns `true` if the pointers are identical, `false` otherwise. \

		XTAL_OP2_(bool) == (subtype const &t)
		XTAL_0FX {return this == _std::addressof(t);}
		
		///\
		Alias of `method(...)`. \
		
		XTAL_TO2_(
		XTAL_OP2() (XTAL_DEF ...xs),
			self().method(XTAL_REF_(xs)...)
		)
		
		///\returns the lambda abstraction of `method`, \
		resolved by the `control/any.hpp#dispatch`ed parameters bound to `this`. \

		XTAL_DO4_(template <class ...Xs>
		XTAL_FN2 reify(value_q auto const ...ks),
		{
			if constexpr (0 == sizeof...(ks)) {
				return [&, this] XTAL_1FN_(self().method);
			}
			else {
				return [&, this] XTAL_1FN_(self().template method<value_f(ks)...>);
			}
		})
		//\
		XTAL_FN2 reify(auto const ...ks), 
		
		///\returns the overloaded function-pointer for the given types. \

		template <class ...Xs>
		XTAL_FN2 deify(auto const ...ks)
		XTAL_0FX
		{
			return deify_(being<Xs...>::template method_m<value_f(ks)...>);
		}
		XTAL_FN2 deify_(auto const &f0)
		XTAL_0FX
		{
			return f0;
		}

	protected:
		///\
		Defines the subtype-indexed function-pointer table, \
		dynamically indexed by control-value/subtype `T`, \
		and statically-generated from `method<Ks...>` with `sizeof...(Ks)` entries. \

		template <class ...Xs>
		struct being
		{
			template <auto ...Ks>
			class resolve
			{
			public:
				using return_t = decltype(XTAL_VAL_(T &).template method<Ks...>(XTAL_VAL_(Xs)...));
				using method_t = return_t (T::*) (argument_t<Xs>...);

			};
			template <auto ...Ks>
			XTAL_REQ_(XTAL_VAL_(T const &).template method<Ks...>(XTAL_VAL_(Xs)...))
			class resolve<Ks...>
			{
			public:
				using return_t = decltype(XTAL_VAL_(T const &).template method<Ks...>(XTAL_VAL_(Xs)...));
				using method_t = return_t (T::*) (argument_t<Xs>...) const;

			};
			template <auto ...Ks> XTAL_USE method_t = typename resolve<Ks...>::method_t;
			template <auto ...Ks> XTAL_LET method_m = static_cast<method_t<Ks...>>(&T::template method<Ks...>);
		
		};

	public:

		///\
		Thunkifies the underlying `T` by capturing the arguments `Xs...`. \

		template <class ...Xs>
		struct bond
		{
			using signature = bundle<let_t<Xs>...>;
			using result_t = typename signature::template invoke_t<T>;
			using return_t = iteratee_t<result_t>;
			
			using subkind = compose<concord::defer<typename signature::type>, defer<T>>;

			template <any_q R>
			class subtype: public compose_s<R, subkind>
			{
				using R_ = compose_s<R, subkind>;

			public:
				using R_::R_;
				using R_::self;
				///\
				Initializes `slots` using the arguments supplied. \

				XTAL_CXN subtype(Xs &&...xs)
				XTAL_0EX
				:	subtype(T{}, XTAL_REF_(xs)...)
				{}
				XTAL_CXN subtype(XTAL_DEF_(is_q<T>) t, Xs &&...xs)
				XTAL_0EX
				:	R_(signature::make(XTAL_REF_(xs)...), XTAL_REF_(t))
				{}

				XTAL_TO4_(XTAL_FN2 slots(), R_::head())
				
				template <size_t N, size_t ...Ns>
				XTAL_FN2 slot()
				XTAL_0EX
				{
					if constexpr (0 == sizeof...(Ns)) {
						return _std::get<N>(slots());
					}
					else {
						return _std::get<N>(slots()).template slot<Ns...>();
					}
				}
				XTAL_FN2 apply(XTAL_DEF f)
				XTAL_0EX {return _std::apply([f = XTAL_REF_(f)] XTAL_1FN_(f), slots());}

				///\
				Evaluates the lifted `method` using the bound slots. \

				template <auto ...Ks>
				XTAL_FN2 method()
				XTAL_0EX {return _std::apply([this] XTAL_1FN_(R_::template method<Ks...>), slots());}
				
				using R_::method;
			//	using R_::influx;
			//	using R_::efflux;

				///\returns the result of `influx`ing `self` then  (if `& 1`) `slots`. \

				XTAL_FNX influx(XTAL_DEF ...oo)
				XTAL_0EX
				{
					return XTAL_FLX_(self().influx_push(oo...)) (R_::influx(XTAL_REF_(oo)...));
				}
				///\returns the result of `efflux`ing `slots` then (if `& 1`) `self`. \

				XTAL_FNX efflux(XTAL_DEF ...oo)
				XTAL_0EX
				{
					return XTAL_FLX_(R_::efflux(oo...)) (self().efflux_pull(XTAL_REF_(oo)...));
				}

				///\note\
				If prefixed by `null_t()`, the message is forwarded directly to `slots`. \

				XTAL_FNX influx(null_t, XTAL_DEF ...oo) XTAL_0EX {return self().influx_push(XTAL_REF_(oo)...);}
				XTAL_FNX efflux(null_t, XTAL_DEF ...oo) XTAL_0EX {return self().efflux_pull(XTAL_REF_(oo)...);}

				///\note\
				If prefixed by `constant_q`, the message is forwarded directly to the `slot` specified. \

				XTAL_FNX influx(constant_q auto i, XTAL_DEF ...oo) XTAL_0EX {return slot<i>().influx(XTAL_REF_(oo)...);}
				XTAL_FNX efflux(constant_q auto i, XTAL_DEF ...oo) XTAL_0EX {return slot<i>().efflux(XTAL_REF_(oo)...);}

				///\
				Forwards the message to `slots`, bypassing `self`. \

				XTAL_FNX influx_push(auto ...oo)
				XTAL_0EX
				{
					return apply([&] (XTAL_DEF ...xs)
						XTAL_0FN_(XTAL_REF_(xs).influx(oo...) &...& -1)
					);
				}
				XTAL_FNX efflux_pull(auto ...oo)
				XTAL_0EX
				{
					return apply([&] (XTAL_DEF ...xs)
						XTAL_0FN_(XTAL_REF_(xs).efflux(oo...) &...& -1)
					);
				}
				///\
				Forwards the message tail to `slots`, bypassing `self`. \
				If `~N_slot`, the slot at `N_slot` receives the full message. \

				template <int N_slot=-1>
				XTAL_FNX influx_push_tail(auto o, auto ...oo)
				XTAL_0EX
				{
					if constexpr (N_slot == -1) {
						return influx_push(XTAL_MOV_(oo)...);
					}
					else {
						static_assert(0 <= N_slot);
						return [&] <auto ...I>(seek_t<I...>)
							XTAL_0FN_(slot<N_slot>().influx(o, oo...) &...& slot<(N_slot <= I) + I>().influx(oo...))
						(seek_f<sizeof...(Xs) - 1> {});
					}
				}
				template <int N_slot=-1>
				XTAL_FNX efflux_pull_tail(auto o, auto ...oo)
				XTAL_0EX
				{
					if constexpr (N_slot == -1) {
						return efflux_pull(XTAL_MOV_(oo)...);
					}
					else {
						static_assert(0 <= N_slot);
						return [&] <auto ...I>(seek_t<I...>)
							XTAL_0FN_(slot<N_slot>().efflux(o, oo...) &...& slot<(N_slot <= I) + I>().efflux(oo...))
						(seek_f<sizeof...(Xs) - 1> {});
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
	class subtype: public compose_s<S, subkind>
	{
		using S_ = compose_s<S, subkind>;
	
		template <class ...Xs>
		using F_ = typename S_::template bond<Xs...>;

	public:
		using S_::S_;
		using S_::self;

		template <class ...Xs>
		struct bond: F_<Xs...>
		{
			using kind = confined<F_<Xs...>>;
			using type = compose_s<S_, kind>;
		
		};
		template <class ...Xs>
		using bond_t = typename bond<Xs...>::type;

		template <typename ...As>
		XTAL_CN2 bond_f(XTAL_DEF ...xs)
		XTAL_0EX
		{
			using  kind = confined<As..., F_<decltype(xs)...>>;
			using  type = compose_s<S_, kind>;
			return type(XTAL_REF_(xs)...);
		}
		template <typename ...As>
		XTAL_CN2 bond_f(XTAL_DEF_(is_q<T>) t, XTAL_DEF ...xs)
		XTAL_0EX
		{
			using  kind = confined<As..., F_<decltype(xs)...>>;
			using  type = compose_s<S_, kind>;
			return type(XTAL_REF_(t), XTAL_REF_(xs)...);
		}
		XTAL_TO4_(template <typename ...As>
		XTAL_FN2 bind(XTAL_DEF ...xs), bond_f<As...>(self(), XTAL_REF_(xs)...)
		)

	};
};


////////////////////////////////////////////////////////////////////////////////

template <class U>
struct defer
{
	using subkind = _retail::defer<U>;

	template <any_q S>
	class subtype: public compose_s<S, subkind>
	{
		using S_ = compose_s<S, subkind>;
	
	public:
		using S_::S_;
		using S_::self;
		using S_::head;
		using typename S_::head_t;

		///\
		Constant redirection. \

		XTAL_DO2_(template <auto ...Ks>
		XTAL_FN2 method(XTAL_DEF ...xs),
		{
			if constexpr (_std::invocable<head_t, decltype(xs)...>) {
				return head() (XTAL_REF_(xs)...);
			}
			else {
				static_assert(0 == sizeof...(xs));
				return head();
			}
		})

	};
};
template <any_q U>
struct defer<U>
{
	using subkind = _retail::defer<U>;

	template <any_q S>
	class subtype: public compose_s<S, subkind>
	{
		using S_ = compose_s<S, subkind>;
	
	public:
		using S_::S_;
		using S_::self;
		using S_::head;

		XTAL_DO2_(template <auto ...Ks>
		XTAL_FN2 method(XTAL_DEF ...xs),
		{
			return head().template method<Ks...>(XTAL_REF_(xs)...);
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
