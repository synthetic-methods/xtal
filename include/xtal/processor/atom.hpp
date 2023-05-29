#pragma once
#include "./any.hpp"
#include "../control/sequel.hpp"
#include "../control/resize.hpp"
#include "../control/respan.hpp"



XTAL_ENV_(push)
namespace xtal::processor
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename, typename ...>
struct atom;

template <typename U, typename ...As>
using atom_t = typename confined<atom<U, As...>>::template subtype<any_of_t<atom>>;

template <typename... Ts>
concept atom_q = any_of_q<atom, Ts...>;

template <typename ...As>
XTAL_FZ2 atom_f(XTAL_DEF u)
{
	return atom_t<decltype(u), As...>(XTAL_REF_(u));
}


namespace _detail
{///////////////////////////////////////////////////////////////////////////////
template <atom_q T>
using covalent_t = XTAL_TYP_(XTAL_VAL_(based_t<T>).template method<>());

template <typename Y, typename ...Ts>
concept covalent_q = is_q<Y, covalent_t<Ts>...> and every_q<_std::is_rvalue_reference_v<Ts>...>;

}///////////////////////////////////////////////////////////////////////////////

template <typename U, typename ...As>
struct atom
{
	using interrupt = typename control::contrived_t<>::interrupt<0>;
	using subkind = confer<U, link<As..., interrupt, common::collect<-1>>>;

	template <any_q S>
	class subtype: public common::compose_s<S, subkind>
	{
		using co = common::compose_s<S, subkind>;
	public:
		using co::co;

		template <typename ...Xs>
		struct bind
		{
			using rebound = typename co::template bind<Xs...>;

			using buffer_u = typename co::template buffer_t<typename rebound::return_t>;
			using debuff_u = typename co::template debuff_t<typename rebound::return_t>;
			using respan_u = control::respan_t<debuff_u>;
			using resize_u = control::resize_t<>;
			
			using subkind = common::compose<content::confer<debuff_u>, content::defer<buffer_u>, rebound>;

			XTAL_LET_(int) N_parity = common::seek_true_v<_detail::covalent_q<debuff_u, Xs>...>;

			template <any_q R>
			class subtype: public common::compose_s<R, subkind>
			{
				using co = common::compose_s<R, subkind>;

				XTAL_NEW_(explicit) subtype(buffer_u &&buffer_o, XTAL_DEF ...etc)
				XTAL_0EX
				:	co((debuff_u) buffer_o, _std::move(buffer_o), XTAL_REF_(etc)...)
				{
				}

			public:
				XTAL_NEW_(explicit) subtype(XTAL_DEF ...etc)
				XTAL_0EX
				:	subtype(buffer_u(), XTAL_REF_(etc)...)
				{
				}

				XTAL_CO2_(subtype);
				XTAL_CO4_(subtype);
			//	using co::co;
				using co::self;

				XTAL_RE4_(XTAL_FN1 store(XTAL_DEF... oo), co::template head<1>(XTAL_REF_(oo)...))
				XTAL_RE4_(XTAL_FN1 serve(XTAL_DEF... oo), co::template head<0>(XTAL_REF_(oo)...))

				template <auto...>
				XTAL_FN2 method()
				XTAL_0EX
				{
					return serve();
				}

			public:
				using co::infuse;
				///\
				Responds to `control::resize` by resizing the internal `store()`. \

				XTAL_FN2_(sign_t) infuse(resize_u resize_o)
				XTAL_0EX
				{
					return co::infuse(resize_o) and (store().resize(XTAL_REF_(resize_o)), 1);
				}
				using co::influx_request;
				///\
				\note Resizing skips intermediate `covalent_p` dependencies, \
				continuing to propagate beyond. \

				XTAL_FN2_(sign_t) influx_request(resize_u resize_o, XTAL_DEF ...oo)
				XTAL_0EX
				requires (0 <= N_parity)
				{
					return co::template influx_request_tail<N_parity>(null_t(), resize_o, XTAL_REF_(oo)...);
				}


			public:
				using co::effuse;
				using co::efflux;
				///\
				Responds to `control::sequel` by rendering the internal `store()`. \
				A match for the following sequel will initiate the `respan` (returning `1`), \
				while a match for the current sequel will terminate (returning `0`). \
				(Deviant behaviour is enforced by `assert`ion on `sequel`.) \

				XTAL_FN2_(sign_t) efflux(XTAL_DEF_(control::sequel_q) sequel_o)
				XTAL_0EX
				{
					return efflux(sequel_o, respan_u(store()));
				}
				///\
				\note When accompanied by `control::respan`, the supplied visor will be used instead. \
				All `arguments` are rendered in-place unless a `visor`-compatible `rvalue` is found, \
				in which case the visor will be reused for the intermediate result. \

				XTAL_FN2_(sign_t) efflux(XTAL_DEF_(control::sequel_q) sequel_o, respan_u respan_o)
				XTAL_0EX
				{
					using _v3::ranges::copy;
					using _v3::ranges::next;
					using _v3::views::slice;
					using _v3::views::take;
					serve(respan_o);

					auto const sequel_m = this->template get<decltype(sequel_o)>();
					if (sequel_m == sequel_o)
					{
						return 0;
					}
					else
					{
						(void) co::infuse(sequel_o);
						iota_t step_n = 0;
						co::redux([&, this](iota_t i, iota_t j)
						XTAL_0FN
						{
							++step_n;// maintain `step()` sequence
							auto const sequel_x = sequel_o.episode(step_n, i, j);
							auto const respan_x = respan_o.episode(step_n, i, j);
							(void) co::template efflux_request_head<N_parity>(sequel_x, respan_x);
							copy(co::template method<>()|take(j - i), next(serve().begin(), i));
						});
						(void) co::influx_request(sequel_o);// set current `step()` and set `size() = 0`
						return 1;
					}
				}

			};
		};

	};
};

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
