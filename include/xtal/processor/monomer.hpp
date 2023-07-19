#pragma once
#include "./etc.hpp"
#include "../context/scope.hpp"
#include "../control/resize.hpp"
#include "../control/respan.hpp"
#include "../control/sequel.hpp"


XTAL_ENV_(push)
namespace xtal::processor
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ...>
struct monomer;

template <typename ...Ts>
XTAL_ASK monomer_q = tag_q<monomer, Ts...>;

template <typename ..._s>
XTAL_USE monomer_t = confined_t<monomer<_s...>>;

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
		using F_ = typename S_::template bond<Xs...>;

	public:
		using S_::S_;
		using S_::self;

		template <typename ...Xs>
		struct bond: F_<Xs...>
		{
			using rebound = F_<Xs...>;
			using subkind = compose<tag<monomer>
			,	concord::confer<typename rebound::result_t>
		//	,	As...
		//	,	resize_u::attach
			,	sequel_u::attach
			,	rebound
			>;
			template <any_q R>
			class subtype: public compose_s<R, subkind>
			{
				using R_ = compose_s<R, subkind>;

			public:
			//	using R_::R_;
				XTAL_CO0_(subtype);
				XTAL_CO4_(subtype);

				XTAL_CXN subtype(XTAL_DEF ...xs)
				XTAL_0EX
				:	subtype(T_{}, XTAL_REF_(xs)...)
				{}
				XTAL_CXN subtype(XTAL_DEF_(is_q<T_>) t, XTAL_DEF ...xs)
				XTAL_0EX
				:	R_(R_::method(XTAL_REF_(xs)...), XTAL_REF_(t), XTAL_REF_(xs)...)
				{}

				XTAL_TO4_(XTAL_FN2 serve(XTAL_DEF... oo), R_::head(XTAL_REF_(oo)...))
				XTAL_TO2_(template <auto ...> XTAL_FN2 method(), serve())


				using R_::efflux;

				XTAL_FNX efflux(XTAL_DEF_(control::sequel_q) sequel_o)
				XTAL_0EX
				{
					return XTAL_FLX_((void) serve(R_::method()), -1) (R_::efflux(XTAL_REF_(sequel_o)));
				}

			};
		};
		template <typename ...Xs> requires collected_q<S_>
		struct bond<Xs...>: F_<Xs...>
		{
			using rebound = F_<Xs...>;
			
			using return_t = typename rebound::return_t;
			using  store_u = typename S_::template fluid<return_t>::type;
			using  serve_u = deranged_t<store_u>;
			using respan_u = control::respan_t<serve_u>;
		
			XTAL_LET_(int) N_share = seek_true_v<_detail::recollected_p<Xs, serve_u>...>;

			using subkind = compose<tag<monomer>
			,	concord::refer<serve_u>
			,	context::scope<store_u>
			,	As...// NOTE: Necessary for `intermit`...
			,	resize_u::attach
			,	sequel_u::attach
			,	rebound
			>;
			template <any_p R>
			class subtype: public compose_s<R, subkind>
			{
				using R_ = compose_s<R, subkind>;

			public:
				using R_::R_;
				using R_::self;
				using R_::serve;
				using R_::store;
				XTAL_TO2_(template <auto ...> XTAL_FN2 method(), serve())

			//	using R_::infuse;
				///\
				Responds to `control::resize` by resizing the internal `store()`. \

				XTAL_FNX infuse(XTAL_DEF o)
				XTAL_0EX
				{
					if constexpr (is_q<resize_u, decltype(o)>) {
						return R_::infuse(o) or (store().resize(XTAL_REF_(o)), 0);
					}
					else {
						return R_::infuse(XTAL_REF_(o));
					}
				}
				using R_::influx_push;
				///\note\
				Resizing skips intermediate `recollected_p` dependencies, \
				continuing to propagate beyond. \

				XTAL_FNX influx_push(resize_u resize_o, XTAL_DEF ...oo)
				XTAL_0EX
				XTAL_REQ (0 <= N_share)
				{
					return R_::template influx_push_tail<N_share>(null_t(), resize_o, XTAL_REF_(oo)...);
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
				All `slots` are rendered locally unless a `visor`-compatible `rvalue` is found, \
				in which case the visor will be reused for the intermediate result. \

				XTAL_FNX efflux(respan_u respan_o, control::sequel_q auto sequel_o, XTAL_DEF ...oo)
				XTAL_0EX
				{
					if (R_::effuse(sequel_o) == 1) return 1;
				//	else...
					(void) serve(respan_o);
					return self().reflux([&, this] (auto n, counted_q auto w)
						XTAL_0FN_(self().efflux_pull_slice(respan_o.slice(w), sequel_o.slice(w).skip(n), oo...))
					) & R_::template influx_push(sequel_o);
				}
				///\
				Renders the buffer slice designated by `respan_x` and `sequel_x`. \
				
				XTAL_FNX efflux_pull_slice(respan_u respan_x, control::sequel_q auto sequel_x, XTAL_DEF ...oo)
				XTAL_0EX
				{
					using namespace _v3;
					auto const  t_ = begin_f(respan_x);
					auto const _n  = taker_f(respan_x);
					return 1 == R_::template efflux_pull_tail<N_share>(respan_x, sequel_x, oo...) or
						(ranges::move(R_::method()|_n, t_), 0);
				}

			};
		};

	};
};

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
