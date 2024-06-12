#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::processor
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ..._s> XTAL_TYP monomer;
template <typename ..._s> XTAL_USE monomer_t = confined_t<monomer< _s...>>;
template <typename ..._s> XTAL_REQ monomer_q = bond::head_tag_p<monomer, _s...>;
template <typename ...As>
XTAL_DEF_(return,inline)
XTAL_LET monomer_f(auto &&u)
XTAL_0EX
{
	return monomer_t<XTAL_TYP_(u), As...>(XTAL_REF_(u));
}


////////////////////////////////////////////////////////////////////////////////

template <typename A, typename ...As> requires anything_q<confined_t<monomer<As...>>>
struct monomer<A, As...>
:	bond::compose<A, monomer<As...>>
{
};
template <class U, typename ...As>
struct monomer<U, As...>
{
	using U_resize = occur::resize_t<>;
	using U_render = occur::render_t<>;

	using subkind = confer<U, As..., resource::stated<>>;

	template <any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;
	
		template <class ...Xs>
		using S_compound = typename S_::template compound<Xs...>;

		template <class ...Xs>
		using R_compound = bond::compose<As...
		,	U_resize::attach<>
		,	U_render::attach<>
		,	S_compound<Xs...>
		,	bond::tag<monomer>
		>;

	protected:
		using typename S_::T_self;

	public:
		using S_::S_;
		using S_::self;

		template <class ...Xs>
		struct common
		{
			using Y_result = typename S_compound<Xs...>::Y_result;
			using Y_return = typename S_compound<Xs...>::Y_return;
		
			using subkind = R_compound<Xs...>;

			template <any_q R>
			class subtype : public bond::compose_s<R, subkind>
			{
				using R_ = bond::compose_s<R, subkind>;

			public:// CONSTRUCT
				using R_::R_;
				using R_::self;
				using R_::efflux;

				template <occur::review_q Rev, occur::render_q Ren>
				XTAL_TNX efflux(Rev &&review_o, Ren &&render_o, auto &&...oo)
				XTAL_0EX
				{
					if (R_::effuse(render_o) == 1) {
						return 1;
					}
					return self().reflux([&, this] (counted_q auto scan, counter_q auto step)
					XTAL_0FN_(self().efflux_subview(
						review_o.subview(scan),
						render_o.subview(scan).skip(step)
					)))
					&	XTAL_FNX_(efflux(oo...)) (R_::template influx_push(XTAL_REF_(render_o)));
				}
				///\
				Renders the buffer slice designated by `review_o` and `render_o`. \
				
				template <occur::review_q Rev, occur::render_q Ren>
				XTAL_TNX efflux_subview(Rev &&review_o, Ren &&render_o)
				XTAL_0EX
				{
					auto  &u_state = review_o.view();
					using  U_state = XTAL_TYP_(u_state);
					static constexpr int N_share = bond::seek_index_n<_detail::recollection_p<Xs, U_state>...>;
					
					if (1 == R_::template efflux_pull_tail<N_share>(review_o, render_o)) {
						return 1;
					}
					else {
						auto result_o = R_::functor();// Materialize...
						auto _j = point_f(result_o);
						auto _i = point_f(review_o);
						auto  n = count_f(review_o);
						
						using namespace _xtd::ranges;
						XTAL_IF0
						XTAL_0IF XTAL_REQ_DO_(copy_n(_j, n, _i))
						XTAL_0IF XTAL_REQ_DO_(move(result_o|account_f(n), _i))
						XTAL_0IF_(default) {for (size_t m = 0; m < n; ++m) {*_i++ = XTAL_MOV_(*_j++);}}

						return 0;
					}
				}

			};
		};
		template <class ...Xs>
		struct compound
		{
			using Y_result = typename S_compound<Xs...>::Y_result;
			//\
			using subkind = cell::conferred<Y_result, R_compound<Xs...>>;
			using subkind = bond::compose<cell::confer<Y_result>, common<Xs...>>;

			template <any_q R>
			class subtype : public bond::compose_s<R, subkind>
			{
				using R_ = bond::compose_s<R, subkind>;

			public:// CONSTRUCT
			//	using R_::R_;

				XTAL_CO0_(subtype);
				XTAL_CO1_(subtype);
				XTAL_CO4_(subtype);

				XTAL_CON_(explicit) subtype(auto &&...xs)
				XTAL_0EX
				:	subtype(T_self{}, XTAL_REF_(xs)...)
				{}
				XTAL_CON_(explicit) subtype(is_q<T_self> auto &&t, auto &&...xs)
				XTAL_0EX
				:	R_(R_::functor(XTAL_REF_(xs)...), XTAL_REF_(t), XTAL_REF_(xs)...)
				{}

				XTAL_TO4_(XTAL_DEF_(return,inline)
				XTAL_REF state(auto &&...oo),
				R_::template head<Y_result>(XTAL_REF_(oo)...)
				)
				XTAL_TO2_(template <auto ...>
				XTAL_DEF_(return,inline)
				XTAL_REF functor(), state()
				)

			public:// FLUXION
				using R_::efflux;

				XTAL_TNX efflux(occur::render_q auto &&render_o)
				XTAL_0EX
				{
					return XTAL_FNX_((void) state(R_::functor()), 0) (R_::efflux(XTAL_REF_(render_o)));
				}

			};
		};
		template <class ...Xs> requires resource::stated_q<S_> and resource::stored_q<S_>
		struct compound<Xs...> : S_compound<Xs...>
		{
			using Y_return = typename S_compound<Xs...>::Y_return;
			using U_store  = typename S_::template store_t<Y_return>;
			using U_state  = typename S_::template state_t<U_store >;
		
			static constexpr int N_share = bond::seek_index_n<_detail::recollection_p<Xs, U_state>...>;
			
			using subkind = bond::compose<resource::stashed<U_state, U_store>, common<Xs...>>;

			template <any_q R>
			class subtype : public bond::compose_s<R, subkind>
			{
				using R_ = bond::compose_s<R, subkind>;

			public:
				using R_::R_;
				using R_::self;
				using R_::state;
				using R_::store;
				
				XTAL_DO2_(template <auto ...>
				XTAL_DEF_(return,inline)
				XTAL_REF functor(),
				{
					return state();
				})
				
				XTAL_DEF_(return,inline)
				XTAL_LET delay()
				XTAL_0EX -> size_t
				{
					size_t const n = R_::delay();
					return 0 < n? n: R_::template head<U_resize>();
				}

			//	using R_::infuse;
				///\
				Responds to `occur::resize` by resizing the internal `store()`. \

				XTAL_TNX infuse(auto &&o)
				XTAL_0EX
				{
					return R_::infuse(XTAL_REF_(o));
				}
				XTAL_TNX infuse(occur::resize_q auto &&o)
				XTAL_0EX
				{
					if (R_::infuse(o) == 1) {
						return 1;
					}
					else {
						auto &u = store();
						auto  i = u.begin();
						auto  n = XTAL_REF_(o).size();
						XTAL_IF0
						XTAL_0IF XTAL_REQ_DO_(u.resize(n))
						(void) state(i, i);//NOTE: For consistency with `vector` stores.
						return 0;
					}
				}
				using R_::influx_push;
				///\note\
				Resizing skips intermediate `recollection_p` dependencies, \
				continuing to propagate beyond. \

				XTAL_TNX influx_push(occur::resize_q auto &&o_resize, auto &&...oo)
				XTAL_0EX requires (0 <= N_share)
				{
					return R_::template influx_push_tail<N_share>(null_t(), XTAL_REF_(o_resize), XTAL_REF_(oo)...);
				}

				using R_::efflux;
				///\
				Responds to `occur::render` by rendering the internal `store()`. \
				A match for the following render will initiate the `review` (returning `1`), \
				while a match for the current render will terminate (returning `0`). \
				(Deviant behaviour is enforced by `assert`ion on `render`.) \

				template <occur::render_q Ren>
				XTAL_TNX efflux(Ren &&render_o, auto &&...oo)
				XTAL_0EX
				{
					size_t vN = R_::template head<U_resize>();
					occur::review_t<U_state> v_(store());
					return efflux(v_.subview(vN), XTAL_REF_(render_o), XTAL_REF_(oo)...);
				}
				///\note\
				When accompanied by `occur::review`, the supplied visor will be used instead. \
				All bound arguments are rendered privately unless a compatible `rvalue` is found, \
				in which case the visor will be reused for the intermediate result. \

				///\note\
				When the visor is unrecognized, \
				the zipped `functor` is rendered without saving the result in `state()`, \
				which will remain empty. \

				template <occur::review_q Rev, occur::render_q Ren>
				XTAL_TNX efflux(Rev &&review_o, Ren &&render_o, auto &&...oo)
				XTAL_0EX
				{
					if constexpr (as_q<Rev, U_state>) {
						(void) state(review_o);
					}
					return R_::efflux(XTAL_REF_(review_o), XTAL_REF_(render_o), XTAL_REF_(oo)...);
				}

			};
		};

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
