#pragma once
#include "./any.hpp"
#include "../message/sequel.hpp"
#include "../message/resize.hpp"
#include "../message/respan.hpp"



XTAL_ENV_(push)
namespace xtal::processor
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename, typename ...>
struct molecule;

template <typename U, typename ...As>
using molecule_t = typename confined<molecule<U, As...>>::template subtype<any_of_t<molecule>>;

template <typename... Ts>
concept molecule_q = any_of_q<molecule, Ts...>;

template <typename ...As>
XTAL_FZ2 molecule_f(XTAL_DEF u)
{
	return molecule_t<decltype(u), As...>(XTAL_REF_(u));
}


namespace _detail
{///////////////////////////////////////////////////////////////////////////////
template <molecule_q T>
using covalent_t = XTAL_TYP_(XTAL_VAL_(based_t<T>).template method<>());

template <typename Y, typename T>
concept covalent_p = is_q<Y, covalent_t<T>> and _std::is_rvalue_reference_v<T>;


}///////////////////////////////////////////////////////////////////////////////

template <typename U, typename ...As>
struct molecule
{
	using interrupt = typename control::confined_t<>::interrupt<0>;
	using subkind = confer<U, link<As..., interrupt, collect<-1>>>;

	template <any_q S>
	class subtype: public compose_s<S, subkind>
	{
		using co = compose_s<S, subkind>;
	
	public:
		using co::co;

		template <typename ...Xs>
		struct bond
		{
			using rebound  = typename co::template bond<Xs...>;
			using return_t = typename rebound::return_t;

			using buffer_u = typename co::template fluid<return_t>::type;
			using debuff_u = deranged_t<buffer_u>;
			using respan_u = message::respan_t<debuff_u>;
			using resize_u = message::resize_t<>;
			
			using subkind = compose<concord::confer<debuff_u>, concord::defer<buffer_u>, rebound>;

			XTAL_LET_(int) I_parity = seek_true_v<_detail::covalent_p<debuff_u, Xs>...>;

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
				Responds to `message::resize` by resizing the internal `store()`. \

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
				///\note\
				Resizing skips intermediate `covalent_p` dependencies, \
				continuing to propagate beyond. \

				XTAL_FNX influx_request(resize_u resize_o, XTAL_DEF ...oo)
				XTAL_0EX
				XTAL_IF1 (0 <= I_parity)
				{
					return co::template influx_request_tail<I_parity>(null_t(), resize_o, XTAL_REF_(oo)...);
				}


			public:
				using co::efflux;
				///\
				Responds to `message::sequel` by rendering the internal `store()`. \
				A match for the following sequel will initiate the `respan` (returning `1`), \
				while a match for the current sequel will terminate (returning `0`). \
				(Deviant behaviour is enforced by `assert`ion on `sequel`.) \

				XTAL_FNX efflux(message::sequel_q auto sequel_o)
				XTAL_0EX
				{
					return efflux(sequel_o, respan_u(store()));
				}
				///\note\
				When accompanied by `message::respan`, the supplied visor will be used instead. \
				All `arguments` are rendered in-place unless a `visor`-compatible `rvalue` is found, \
				in which case the visor will be reused for the intermediate result. \

				XTAL_FNX efflux(message::sequel_q auto sequel_o, respan_u respan_o)
				XTAL_0EX
				{
					if (co::effuse(sequel_o) == 0) return 0;
				//	else...
					serve(respan_o);
					co::redux([&, this](auto i, auto j, auto n)
					XTAL_0FN
					{	using namespace _v3;
						auto sequel_x = sequel_o.slice(i, j).skip(n);
						auto respan_x = respan_o.slice(i, j);
						(void) co::template efflux_request_head<I_parity>(sequel_x, respan_x);
						ranges::copy(co::template method<>()|views::take(j - i), ranges::next(serve().begin(), i));
					});
					return co::template influx_request(sequel_o);
				}

			};
		};

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
