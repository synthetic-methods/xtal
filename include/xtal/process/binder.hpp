#pragma once
#include "./any.hpp"
#include "../control/any.hpp"





XTAL_ENV_(push)
namespace xtal::process
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
///\
Provides a common substrate for decorating both the immediate `subtype` and that of `bind`, \
which thunkifies the underlying type by capturing its arguments. \

template <typename ...As>
struct binder
{
	using interrupt = typename control::confined_t<>::interrupt<0>;
	using interkind = compose<As..., interrupt>;
	
	using subkind = interkind;

	template <any_p S>
	class subtype: public compose_s<S, subkind>
	{
		using S_ = compose_s<S, subkind>;
		using T_ = typename S_::self_t;

	public:
		using S_::S_;
		///\
		Thunkifies `T_` by binding `Xs...`. \

		template <typename ...Xs>
		struct bind
		{
			using signature = bundle<Xs...>;
			using result_t  = typename signature::template invoke_t<T_>;
			using return_t  = iteratee_t<result_t>;
			
			using subkind = compose<concord::defer<typename signature::type>, interkind, defer<T_>>;

			template <any_p R>
			class subtype: public compose_s<R, subkind>
			{
				using R_ = compose_s<R, subkind>;

			public:
				using R_::R_;
				using R_::self;
				///\
				Constructs `arguments` using those supplied. \

				XTAL_NEW subtype(Xs &&...xs)
				XTAL_0EX
				:	R_(signature::make(XTAL_FWD_(Xs) (xs)...), T_())
				{
				}
				XTAL_NEW subtype(XTAL_DEF_(is_q<T_>) t, Xs &&...xs)
				XTAL_0EX
				:	R_(signature::make(XTAL_FWD_(Xs) (xs)...), XTAL_REF_(t))
				{
				}

				XTAL_RN4_(XTAL_FN2 arguments(), R_::head())
				
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
						XTAL_0FN_(XTAL_REF_(fx) (XTAL_REF_(xs)...)),
						arguments()
					);
				}

				///\
				Evaluates the lifted `method` using the bound arguments. \

				template <auto ...Ms>
				XTAL_FN2 method()
				XTAL_0EX
				{
					return apply([this](XTAL_DEF ...xs)
						XTAL_0FN_(R_::template method<Ms...>(XTAL_REF_(xs)...))
					);
				}
				template <auto ...Ms>
				XTAL_FN2 method(XTAL_DEF... xs)
				XTAL_0EX
				{
					return R_::template method<Ms...>(XTAL_REF_(xs)...);
				}

			public:
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


				///\
				Forwards the message to `arguments`, bypassing `self`. \

				XTAL_FNX efflux_request(auto ...oo)
				XTAL_0EX
				{
					return apply([&](XTAL_DEF ...xs)
						XTAL_0FN_(XTAL_REF_(xs).efflux(oo...) &...& -1)
					);
				}
				XTAL_FNX influx_request(auto ...oo)
				XTAL_0EX
				{
					return apply([&](XTAL_DEF ...xs)
						XTAL_0FN_(XTAL_REF_(xs).influx(oo...) &...& -1)
					);
				}


				///\
				Forwards the message *tail* to `arguments`, bypassing `self`. \
				If `~I_parity`, the argument at `I_parity` receives the full message. \

				template <int I_parity=-1>
				XTAL_FNX efflux_request_tail(auto o, auto ...oo)
				XTAL_0EX
				{
					if constexpr (I_parity == -1)
					{	return efflux_request(XTAL_MOV_(oo)...);
					}
					else
					{	static_assert(0 <= I_parity);
						return [&] <auto ...I>(seek_t<I...>)
							XTAL_0FN_(argument<I_parity>().efflux(o, oo...) &...& argument<(I_parity <= I) + I>().efflux(oo...))
						(seek_v<sizeof...(Xs) - 1>);
					}
				}
				template <int I_parity=-1>
				XTAL_FNX influx_request_tail(auto o, auto ...oo)
				XTAL_0EX
				{
					if constexpr (I_parity == -1)
					{	return influx_request(XTAL_MOV_(oo)...);
					}
					else
					{	static_assert(0 <= I_parity);
						return [&] <auto ...I>(seek_t<I...>)
							XTAL_0FN_(argument<I_parity>().influx(o, oo...) &...& argument<(I_parity <= I) + I>().influx(oo...))
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
