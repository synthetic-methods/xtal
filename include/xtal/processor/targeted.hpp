#pragma once
#include "./any.hpp"
#include "../message/any.hpp"
#include "../message/serial.hpp"
#include "../message/resize.hpp"
#include "../message/respan.hpp"


XTAL_ENV_(push)
namespace xtal::processor
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ...Xs>
concept cotargetable_q = is_q<typename based_t<Xs>::target_t...>;

template <typename X, typename T>
concept retargetable_q = is_q<typename based_t<X>::target_t, T> and _std::is_rvalue_reference_v<X>;

template <typename U, typename ...As>
struct targeted
{
	using interrupt = typename message::contrived_t<>::interrupt<0>;
//	using subkind = confer<U, As..., interrupt, buffer<-1>>;
	using subkind = confer<U, buffer<-1>>;

	template <any_q S>
	class subtype: public compose_s<S, subkind>
	{
		using co = compose_s<S, subkind>;
	public:
		using co::co;

		template <typename ...Xs>
		struct bind
		{
			using superkind = typename co::template bind<Xs...>;
			using signature = typename superkind::signature;
			using result_t = typename superkind::result_t;
			using return_t = typename superkind::return_t;
			
			using buffer_u = typename co::template vector_t<return_t>;
			using target_u = spanned_t<buffer_u>;
			using respan_u = message::respan_t<target_u>;
			using resize_u = message::resize_t<>;
			using subkind  = compose<content::confer<target_u>, content::defer<buffer_u>, As..., interrupt, superkind>;

			XTAL_LET_(sigma_t) N_arity = sizeof...(Xs), N_parity = truth_index_v<retargetable_q<Xs, target_u>...>;

			template <any_q R>
			class subtype: public compose_s<R, subkind>
			{
				using co = compose_s<R, subkind>; using T = typename co::self_t;

			public:
				using co::co;
				using co::self;

				using buffer_t = buffer_u;
				using target_t = target_u;
				using respan_t = respan_u;

				XTAL_RE4_(XTAL_FN1 target(XTAL_DEF... oo), co::template head<0>(XTAL_REF_(oo)...))
				XTAL_RE4_(XTAL_FN1 buffer(XTAL_DEF... oo), co::template head<1>(XTAL_REF_(oo)...))

				template <auto...>
				XTAL_FN2 method()
				XTAL_0EX
				{
					return target();
				}


			public:
				using co::infuse;
				///\
				Responds to `message::resize` by resizing the internal `buffer()`. \

				XTAL_FN2_(flux_t) infuse(resize_u resize_o)
				XTAL_0EX
				{
					if (co::infuse(resize_o))// NOTE: Depends on the `attach`ment `define`d in `./any.hpp`.
					{
						buffer().resize(XTAL_REF_(resize_o));
						return 1;
					}
					else
					{
						return 0;
					}
				}
				using co::influx_push;
				///\
				\note Resizing skips intermediate `retargetable_q` dependencies, \
				continuing to propagate beyond. \

				XTAL_FN2_(flux_t) influx_push(resize_u resize_o, XTAL_DEF ...oo)
				XTAL_0EX
				requires (N_parity < N_arity)
				{
					return co::template influx_push_tail<N_parity>(nothing_t(), resize_o, XTAL_REF_(oo)...);
				}


			public:
				using co::effuse;
				///\
				Responds to `message::respan` by rendering the provided target, \
				fulfilling any dependencies in advance. \
				If any `message`s are bound to this `processor` via `interrupt`, \
				the source will be chunked in intervals necessary to update state. \

				XTAL_FN2_(flux_t) effuse(respan_t respan_o)
				XTAL_0EX
				{
					using _v3::ranges::copy;
					using _v3::ranges::next;
					using _v3::views::slice;
					
					target(respan_o);
					co::redux([this] (iota_t i, iota_t j)
						XTAL_0FN_(copy(co::template method<>()|slice(i, j), next(target().begin(), i)))
					);
					return 1;
				}

				using co::efflux;
				///\
				Responds to `message::serial` by resolving the internal `buffer()`. \
				A match for the following cycle will initiate the `respan` (returning `1`), \
				while a match for the current cycle will terminate (returning `0`). \
				(Deviant behaviour is enforced by `assert`ion.) \

				XTAL_FN2_(flux_t) efflux(XTAL_DEF_(message::serial_q) serial_o)
				XTAL_0EX
				{
					return efflux(serial_o, respan_t(buffer()));
				}
				///\
				\note When accompanied by `message::respan`, the supplied target will be used instead. \
				All `arguments` are rendered in-place unless a `target`-compatible `rvalue` is found, \
				in which case the target will be reused for the intermediate result. \

				XTAL_FN2_(flux_t) efflux(XTAL_DEF_(message::serial_q) serial_o, respan_t respan_o)
				XTAL_0EX
				{
					return co::template efflux_pull_head<N_parity>(serial_o, respan_o)
						and effuse(serial_o) and effuse(respan_o);
				}
				

			};
		};

	};
};
template <typename U, typename ...As>
using     targeted_t = confined_t<targeted<U, As...>>;
XTAL_LET  targeted_f = [] (XTAL_DEF u)
XTAL_0FN_(targeted_t<decltype(u)>(XTAL_REF_(u)));

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
