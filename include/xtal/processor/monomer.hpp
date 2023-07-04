#pragma once
#include "./any.hpp"
#include "../control/resize.hpp"
#include "../control/sequel.hpp"




XTAL_ENV_(push)
namespace xtal::processor
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ...>
struct monomer;

template <typename ...Ts>
XTAL_ASK monomer_q = conjunct_q<only_p<Ts, monomer>...>;

template <typename U, typename ...As>
XTAL_USE monomer_t = typename confined<monomer<U, As...>>::template subtype<only_t<monomer>>;

template <typename ...As>
XTAL_CN2 monomer_f(XTAL_DEF u) {return monomer_t<XTAL_TYP_(u), As...>(XTAL_REF_(u));}


////////////////////////////////////////////////////////////////////////////////

template <typename U, typename ...As>
struct monomer<U, As...>
{
	using resize_u = control::resize_t<>;
	using sequel_u = control::sequel_t<>;

	using subkind = confer<U, As...>;

	template <any_p S>
	class subtype: public compose_s<S, subkind>
	{
		using S_ = compose_s<S, subkind>;
		using T_ = typename S_::self_t;
	
		template <typename ...Xs>
		using B_ = typename S_::template binding<Xs...>;

	public:
		using S_::S_;
		using S_::self;

		template <typename ...Xs>
		struct binding: B_<Xs...>
		{
			using rebound = B_<Xs...>;
			using subkind = compose<As...
			,	concord::confer<typename rebound::result_t>
			,	rebound
			,	sequel_u::attach
		//	,	resize_u::attach
			>;
			template <typename R>
			class subtype: public compose_s<R, subkind>
			{
				using R_ = compose_s<R, subkind>;

			public:
			//	using R_::R_;
				XTAL_CO0_(subtype);
				XTAL_CO4_(subtype);

				XTAL_CXN subtype(XTAL_DEF ...xs)
				XTAL_0EX
				:	R_(R_::method(XTAL_REF_(xs)...), XTAL_REF_(xs)...)
				{
				}
				XTAL_CXN subtype(XTAL_DEF_(is_q<T_>) t, XTAL_DEF ...xs)
				XTAL_0EX
				:	R_(R_::method(XTAL_REF_(xs)...), XTAL_REF_(t), XTAL_REF_(xs)...)
				{
				}

				XTAL_DO4_(XTAL_FN1 serve(XTAL_DEF... oo), R_::head(XTAL_REF_(oo)...))

				template <auto...>
				XTAL_FN2 method()
				XTAL_0EX
				{
					return serve();
				}

			public:
				using R_::efflux;

				XTAL_FNX efflux(XTAL_DEF_(control::sequel_q) sequel_o)
				XTAL_0EX
				{
					return XTAL_FLX_((void) serve(R_::method()), -1) (R_::efflux(XTAL_REF_(sequel_o)));
				}

			};
		};
		template <typename ...Xs> requires collect_q<S_>
		struct binding<Xs...>: B_<Xs...>
		{
			using rebound = B_<Xs...>;
		
			using buffer_u = typename S_::template fluid<typename rebound::return_t>::type;
			using debuff_u = deranged_t<buffer_u>;
			using respan_u = control::respan_t<debuff_u>;
			using resize_u = control::resize_t<>;
		
			XTAL_LET_(int) I_parity = seek_true_v<_detail::recollected_p<Xs, debuff_u>...>;

			using subkind = compose<As...
			,	concord::confer<debuff_u>
			,	concord::defer <buffer_u>
			,	rebound
			,	sequel_u::attach
			,	resize_u::attach
			,	typename control::confined_t<>::interrupt<0>
			>;
			template <any_p R>
			class subtype: public compose_s<R, subkind>
			{
				using R_ = compose_s<R, subkind>;

				XTAL_CXN subtype(buffer_u &&buffer_o, XTAL_DEF ...etc)
				XTAL_0EX
				:	R_((debuff_u) buffer_o, XTAL_MOV_(buffer_o), XTAL_REF_(etc)...)
				{
				}

			public:
			//	using R_::R_;
				using R_::self;

				XTAL_CO0_(subtype);
				XTAL_CO4_(subtype);

				XTAL_CXN subtype(XTAL_DEF ...etc)
				XTAL_0EX
				:	subtype(buffer_u(), XTAL_REF_(etc)...)
				{
				}

				XTAL_DO4_(XTAL_FN1 store(XTAL_DEF... oo), R_::template head<1>(XTAL_REF_(oo)...))
				XTAL_DO4_(XTAL_FN1 serve(XTAL_DEF... oo), R_::template head<0>(XTAL_REF_(oo)...))

				template <auto...>
				XTAL_FN2 method()
				XTAL_0EX
				{
					return serve();
				}

				using R_::efflux;
				///\
				Responds to `control::sequel` by rendering the internal `store()`. \
				A match for the following sequel will initiate the `respan` (returning `1`), \
				while a match for the current sequel will terminate (returning `0`). \
				(Deviant behaviour is enforced by `assert`ion on `sequel`.) \

				XTAL_FNX efflux(control::sequel_q auto sequel_o, XTAL_DEF ...oo)
				XTAL_0EX
				{
					return efflux(respan_u(store()), sequel_o, XTAL_REF_(oo)...);
				}
				///\note\
				When accompanied by `control::respan`, the supplied visor will be used instead. \
				All `arguments` are rendered in-place unless a `visor`-compatible `rvalue` is found, \
				in which case the visor will be reused for the intermediate result. \

				XTAL_FNX efflux(respan_u respan_o, control::sequel_q auto sequel_o, XTAL_DEF ...oo)
				XTAL_0EX
				{
					if (R_::effuse(sequel_o, oo...) == 1) return 1;
				//	else...
					serve(respan_o);
					R_::replay([&, this] (auto i, auto j, auto n)
					XTAL_0FN {
						using namespace _v3;
						auto sequel_x = sequel_o.slice(i, j).skip(n);
						auto respan_x = respan_o.slice(i, j);
						(void) R_::template efflux_request_tail<I_parity>(respan_x, sequel_x, oo...);
						ranges::copy(R_::template method<>()|views::take(j - i), ranges::next(serve().begin(), i));
					});
					return R_::template influx_request(sequel_o);
				}

			//	using R_::infuse;
				///\
				Responds to `control::resize` by resizing the internal `store()`. \

				XTAL_FNX infuse(resize_u resize_o)
				XTAL_0EX
				{
					return R_::infuse(resize_o) or (store().resize(XTAL_REF_(resize_o)), 0);
				}
				XTAL_FNX infuse(XTAL_DEF o)
				XTAL_0EX
				{
					return R_::infuse(XTAL_REF_(o));
				}
				
				using R_::influx_request;
				///\note\
				Resizing skips intermediate `recollected_p` dependencies, \
				continuing to propagate beyond. \

				XTAL_FNX influx_request(resize_u resize_o, XTAL_DEF ...oo)
				XTAL_0EX
				XTAL_REQ (0 <= I_parity)
				{
					return R_::template influx_request_tail<I_parity>(null_t(), resize_o, XTAL_REF_(oo)...);
				}

			};
		};

	};
};

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
