#pragma once
#include "./any.hpp"
#include "../block/all.hpp"
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

template <typename Y, typename T>
concept covalent_p = is_q<Y, covalent_t<T>> and _std::is_rvalue_reference_v<T>;


}///////////////////////////////////////////////////////////////////////////////

template <typename U, typename ...As>
struct atom
{
	using interrupt = typename control::confined_t<>::interrupt<0>;
	using subkind = confer<U, link<As..., interrupt, block::collector<-1>>>;

	template <any_q S>
	class subtype: public compose_s<S, subkind>
	{
		using co = compose_s<S, subkind>;
	public:
		using co::co;

		template <typename ...Xs>
		struct bind
		{
			using rebound = typename co::template bind<Xs...>;

			using collected  = block::collected<typename rebound::return_t>;
			using collection = compose_s<co, collected>;
			
			using buffer_u = typename collection::buffer::type;
			using debuff_u = deranged_t<buffer_u>;
			using respan_u = control::respan_t<debuff_u>;
			using resize_u = control::resize_t<>;
			
			using subkind = compose<content::confer<debuff_u>, content::defer<buffer_u>, rebound>;

			XTAL_LET_(int) N_parity = common::seek_true_v<_detail::covalent_p<debuff_u, Xs>...>;

			template <any_q R>
			class subtype: public compose_s<R, subkind>
			{
				using co = compose_s<R, subkind>;

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

				XTAL_CN2_(subtype);
				XTAL_CN4_(subtype);
			//	using co::co;
				using co::self;

				XTAL_RN4_(XTAL_FN1 store(XTAL_DEF... oo), co::template head<1>(XTAL_REF_(oo)...))
				XTAL_RN4_(XTAL_FN1 serve(XTAL_DEF... oo), co::template head<0>(XTAL_REF_(oo)...))

				template <auto...>
				XTAL_FN2 method()
				XTAL_0EX
				{
					return serve();
				}

			public:
				///\
				Responds to `control::resize` by resizing the internal `store()`. \

				XTAL_FNX infuse(XTAL_DEF o)
				XTAL_0EX
				{
					return co::infuse(XTAL_REF_(o));
				}
				XTAL_FNX infuse(resize_u resize_o)
				XTAL_0EX
				{
					return co::infuse(resize_o) and (store().resize(XTAL_REF_(resize_o)), 1);
				}
				using co::influx_request;
				///\
				\note Resizing skips intermediate `covalent_p` dependencies, \
				continuing to propagate beyond. \

				XTAL_FNX influx_request(resize_u resize_o, XTAL_DEF ...oo)
				XTAL_0EX
				XTAL_IF1 (0 <= N_parity)
				{
					return co::template influx_request_tail<N_parity>(null_t(), resize_o, XTAL_REF_(oo)...);
				}


			public:
				using co::efflux;
				///\
				Responds to `control::sequel` by rendering the internal `store()`. \
				A match for the following sequel will initiate the `respan` (returning `1`), \
				while a match for the current sequel will terminate (returning `0`). \
				(Deviant behaviour is enforced by `assert`ion on `sequel`.) \

				XTAL_FNX efflux(control::sequel_q auto sequel_o)
				XTAL_0EX
				{
					return efflux(sequel_o, respan_u(store()));
				}
				///\
				\note When accompanied by `control::respan`, the supplied visor will be used instead. \
				All `arguments` are rendered in-place unless a `visor`-compatible `rvalue` is found, \
				in which case the visor will be reused for the intermediate result. \

				XTAL_FNX efflux(control::sequel_q auto sequel_o, respan_u respan_o)
				XTAL_0EX
				{
					if (co::effuse(sequel_o) == 0) return 0;
				//	else...
				//	delta_t n = 0;
					(void) serve(respan_o);
					(void) co::redux([&, this](auto i, auto j, auto n)
					XTAL_0FN
					{	using namespace _v3;
						auto sequel_x = sequel_o.slice(i, j).skip(n);//++
						auto respan_x = respan_o.slice(i, j);
						(void) co::template efflux_request_head<N_parity>(sequel_x, respan_x);
						ranges::copy(co::template method<>()|views::take(j - i), ranges::next(serve().begin(), i));
					}, skip_n);
				//	(void) co::template influx_request(sequel_o);
					return 1;
				}
		//	NOTE: The definition of `infuse` invoked on `sequel` above assumes sequential update. \
		//	If this is changed (e.g. to allow absolute redressing), \
		//	they can instead be realigned by replacing `n` with `skip_n`: \

			private:
				delta_t skip_n = 0;

			};
		};

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
