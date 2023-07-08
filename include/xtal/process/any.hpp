#pragma once
#include "../conflux/any.hpp"// `_retail`

#include "../control/any.hpp"




XTAL_ENV_(push)
namespace xtal::process
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

namespace _retail = xtal::conflux;
#include "../concord/any.hxx"
#include "./_detail.hxx"


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


		///\returns `true` if the pointers are identical, `false` otherwise. \

		XTAL_OP2_(bool) == (subtype const &t)
		XTAL_0FX
		{
			return this == _std::addressof(t);
		}


		///\
		Alias of `method(...)`. \
		
		XTAL_TO2_(
		XTAL_OP2() (XTAL_DEF ...xs), self().method(XTAL_REF_(xs)...)
		)
		
		///\returns the lambda abstraction of `method`, \
		resolved by the `control/any.hpp#dispatch`ed parameters bound to `this`. \

		XTAL_TO4_(template <typename ...Xs>
		XTAL_FN2 reify(), [this] XTAL_1FN_(operator())
		)
		
		///\returns the overloaded function-pointer for the given types. \

		template <typename ...Xs>
		XTAL_FN2 deify()
		XTAL_0FX
		{
			return deify(being<Xs...>::template method_m<>);
		}
		XTAL_FN2 deify(auto const &f0)
		XTAL_0FX
		{
			return f0;
		}

	protected:
		///\
		Defines the subtype-indexed function-pointer table, \
		dynamically indexed by control-value/subtype `T`, \
		and statically-generated from `method<Ks...>` with `sizeof...(Ks)` entries. \

		template <typename ...Xs>
		struct being
		{
			template <auto ...Ks>
			struct resolve
			{
				using return_t = decltype(XTAL_VAL_(T &).template method<Ks...>(XTAL_VAL_(Xs)...));
				using method_t = return_t (T::*) (Xs const &&...);

			};
			template <auto ...Ks>
			requires
			requires (T const t)
			{
				t.template method<Ks...>(XTAL_VAL_(Xs)...);
			}
			struct resolve<Ks...>
			{
				using return_t = decltype(XTAL_VAL_(T const &).template method<Ks...>(XTAL_VAL_(Xs)...));
				using method_t = return_t (T::*) (Xs const &&...) const;

			};
			template <auto ...Ks> XTAL_USE method_t = typename resolve<Ks...>::method_t;
			template <auto ...Ks> XTAL_LET method_m = static_cast<method_t<Ks...>>(&T::template method<Ks...>);
		
		};

	public:

		///\
		Thunkifies the underlying `T` by capturing the arguments `Xs...`. \

		template <typename ...Xs>
		struct bond
		{
			using signature = bundle<let_t<Xs>...>;
			using result_t = typename signature::template invoke_t<T>;
			using return_t = iteratee_t<result_t>;
			
			using subkind = compose<concord::defer<typename signature::type>, defer<T>>;

			template <any_p R>
			class subtype: public compose_s<R, subkind>
			{
				using R_ = compose_s<R, subkind>;

			public:
				using R_::R_;
				using R_::self;
				///\
				Constructs `arguments` using those supplied. \

				XTAL_CXN subtype(Xs &&...xs)
				XTAL_0EX
				:	R_(signature::make(XTAL_REF_(xs)...), T())
				{}
				XTAL_CXN subtype(XTAL_DEF_(is_q<T>) t, Xs &&...xs)
				XTAL_0EX
				:	R_(signature::make(XTAL_REF_(xs)...), XTAL_REF_(t))
				{}

				XTAL_TO4_(XTAL_FN2 arguments(), R_::head())
				
				template <size_t N, size_t ...Ns>
				XTAL_FN2 argument()
				XTAL_0EX
				{
					if constexpr (0 == sizeof...(Ns)) {
						return _std::get<N>(arguments());
					}
					else {
						return _std::get<N>(arguments()).template argument<Ns...>();
					}
				}
				
				XTAL_FN2 apply(XTAL_DEF f)
				XTAL_0EX
				{
					return _std::apply([f = XTAL_REF_(f)] XTAL_1FN_(f), arguments());
				}

				using R_::method;
				///\
				Evaluates the lifted `method` using the bound arguments. \

				template <auto ...Ks>
				XTAL_FN2 method()
				XTAL_0EX
				{
					return _std::apply([this] XTAL_1FN_(R_::template method<Ks...>), arguments());
				}

			//	using R_::efflux;
			//	using R_::influx;

				///\returns the result of `efflux`ing `arguments` then (if `& 1`) `self`. \

				XTAL_FNX efflux(XTAL_DEF ...oo)
				XTAL_0EX
				{
					return XTAL_FLX_(R_::efflux(oo...)) (self().efflux_request(XTAL_REF_(oo)...));
				}
				///\returns the result of `influx`ing `self` then  (if `& 1`) `arguments`. \

				XTAL_FNX influx(XTAL_DEF ...oo)
				XTAL_0EX
				{
					return XTAL_FLX_(self().influx_request(oo...)) (R_::influx(XTAL_REF_(oo)...));
				}

				///\note\
				If prefixed by `null_t()`, the message is forwarded directly to `arguments`. \

				XTAL_FNX efflux(null_t, XTAL_DEF ...oo)
				XTAL_0EX
				{
					return self().efflux_request(XTAL_REF_(oo)...);
				}
				XTAL_FNX influx(null_t, XTAL_DEF ...oo)
				XTAL_0EX
				{
					return self().influx_request(XTAL_REF_(oo)...);
				}

				///\note\
				If prefixed by `constant_q`, the message is forwarded directly to the `argument` specified. \

				XTAL_FNX efflux(constant_q auto i, XTAL_DEF ...oo)
				XTAL_0EX
				{
					return argument<decltype(i){}>().efflux(XTAL_REF_(oo)...);
				}
				XTAL_FNX influx(constant_q auto i, XTAL_DEF ...oo)
				XTAL_0EX
				{
					return argument<decltype(i){}>().influx(XTAL_REF_(oo)...);
				}


				///\
				Forwards the message to `arguments`, bypassing `self`. \

				XTAL_FNX efflux_request(auto ...oo)
				XTAL_0EX
				{
					return apply([&] (XTAL_DEF ...xs)
						XTAL_0FN_(XTAL_REF_(xs).efflux(oo...) &...& -1)
					);
				}
				XTAL_FNX influx_request(auto ...oo)
				XTAL_0EX
				{
					return apply([&] (XTAL_DEF ...xs)
						XTAL_0FN_(XTAL_REF_(xs).influx(oo...) &...& -1)
					);
				}


				///\
				Forwards the message tail to `arguments`, bypassing `self`. \
				If `~I_parity`, the argument at `I_parity` receives the full message. \

				template <int I_parity=-1>
				XTAL_FNX efflux_request_tail(auto o, auto ...oo)
				XTAL_0EX
				{
					if constexpr (I_parity == -1) {
						return efflux_request(XTAL_MOV_(oo)...);
					}
					else {
						static_assert(0 <= I_parity);
						return [&] <auto ...I>(seek_t<I...>)
							XTAL_0FN_(argument<I_parity>().efflux(o, oo...) &...& argument<(I_parity <= I) + I>().efflux(oo...))
						(seek_f<sizeof...(Xs) - 1> {});
					}
				}
				template <int I_parity=-1>
				XTAL_FNX influx_request_tail(auto o, auto ...oo)
				XTAL_0EX
				{
					if constexpr (I_parity == -1) {
						return influx_request(XTAL_MOV_(oo)...);
					}
					else {
						static_assert(0 <= I_parity);
						return [&] <auto ...I>(seek_t<I...>)
							XTAL_0FN_(argument<I_parity>().influx(o, oo...) &...& argument<(I_parity <= I) + I>().influx(oo...))
						(seek_f<sizeof...(Xs) - 1> {});
					}
				}

			};
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
	
		template <typename ...Xs>
		using F_ = typename S_::template bond<Xs...>;

	public:
		using S_::S_;
		using S_::self;

		template <typename ...Xs>
		struct bond: F_<Xs...>
		{
			using type = compose_s<S_, confined<F_<Xs...>>>;
		
		};
		template <typename ...Xs>
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
		using typename S_::head_t;

		///\
		Constant redirection. \

		XTAL_DO2_(
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

		XTAL_TO2_(template <auto ...Ks>
		XTAL_FN2 method(XTAL_DEF ...xs), head().template method<Ks...>(XTAL_REF_(xs)...)
		)

	};
};
template <typename U>
struct refer
:	_retail::refer<U>
{};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
