#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::processor
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ..._s> XTAL_TYP monomer;
template <typename ..._s> XTAL_USE monomer_t = confined_t<monomer< _s...>>;
template <typename ..._s> XTAL_ASK monomer_q = bond::head_tag_p<monomer, _s...>;
template <typename ...As>
XTAL_DEF_(return,inline)
XTAL_FN1     monomer_f(auto &&u)
XTAL_0EX_TO_(monomer_t<XTAL_TYP_(u), As...>(XTAL_REF_(u)))


////////////////////////////////////////////////////////////////////////////////

template <class U_process, typename ...As>
struct monomer<U_process, As...>
{
	using U_resize = occur::resize_t<>;
	using U_render = occur::render_t<>;

	using subkind = confer<U_process, As..., resource::restate<>>;

	template <any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;
	
		template <class ...Xs>
		using S__binding = typename S_::template binding<Xs...>;

		template <class ...Xs>
		using R__binding = bond::compose<As...
		,	U_resize::attach<>
		,	U_render::attach<>
		,	S__binding<Xs...>
		,	bond::tag<monomer>
		>;

	protected:
		using typename S_::T_self; friend T_self;

	public:
		using S_::S_;
		using S_::self;

		template <class ...Xs>
		struct binding
		{
			using Y_result = typename S__binding<Xs...>::Y_result;
			using subkind = bond::compose<cell::confer<Y_result>, R__binding<Xs...>>;

			template <any_q R>
			class subtype : public bond::compose_s<R, subkind>
			{
				using R_ = bond::compose_s<R, subkind>;

			public:// CONSTRUCTION
			//	using R_::R_;

				XTAL_CO0_(subtype);
				XTAL_CO1_(subtype);
				XTAL_CO4_(subtype);

				XTAL_CXN subtype(auto &&...xs)
				XTAL_0EX
				:	subtype(T_self{}, XTAL_REF_(xs)...)
				{}
				XTAL_CXN subtype(is_q<T_self> auto &&t, auto &&...xs)
				XTAL_0EX
				:	R_(R_::functor(XTAL_REF_(xs)...), XTAL_REF_(t), XTAL_REF_(xs)...)
				{}

				XTAL_TO4_(XTAL_TN2 state(auto &&...oo), R_::head(XTAL_REF_(oo)...))
				XTAL_TO2_(template <auto ...> XTAL_DEF_(return,inline) XTAL_TN1 functor(), state())

			public:// FLUXION
				using R_::efflux;

				XTAL_TNX efflux(occur::render_q auto &&render_o)
				XTAL_0EX
				{
					return XTAL_FLX_((void) state(R_::functor()), 0) (R_::efflux(XTAL_REF_(render_o)));
				}

			};
		};
		template <class ...Xs> requires resource::restate_q<S_> and resource::restore_q<S_>
		struct binding<Xs...> : S__binding<Xs...>
		{
			using Y_return = typename S__binding<Xs...>::Y_return;
			using U_store  = typename S_::template store_t<Y_return>;
			using U_state  = typename S_::template state_t<U_store >;
		
			XTAL_LET_(int) N_share = bond::seek_index_n<_detail::recollection_p<Xs, U_state>...>;
			
			using subkind = bond::compose<resource::restash<U_state, U_store>, R__binding<Xs...>>;

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
				XTAL_TN1 functor(),
				{
					XTAL_IF0
					XTAL_0IF (    resizeable_q<U_store>) {return state();}
					XTAL_0IF (not resizeable_q<U_store>) {return state()|account_f(R_::template head_t<U_resize>);}
				})

				XTAL_TN2_(size_t) delay()
				XTAL_0EX
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
					if constexpr (occur::resize_q<decltype(o)> and resizeable_q<U_store>) {
						return R_::infuse(o) || (store().resize(XTAL_REF_(o).size()), 0);
					}
					else {
						return R_::infuse(XTAL_REF_(o));
					}
				}
				using R_::influx_push;
				///\note\
				Resizing skips intermediate `recollection_p` dependencies, \
				continuing to propagate beyond. \

				XTAL_TNX influx_push(occur::resize_q auto &&o_resize, auto &&...oo)
				XTAL_0EX
				XTAL_REQ (0 <= N_share)
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
					return efflux(occur::review_t<U_state>(store()), XTAL_REF_(render_o), XTAL_REF_(oo)...);
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
					if (R_::effuse(render_o) == 1) {
						return 1;
					}
					if constexpr (as_q<Rev, U_state>) {
						(void) state(review_o);
					}
					return self().reflux([&, this] (counted_q auto scan, counter_q auto step)
					XTAL_0FN_(self().efflux_slice(
						review_o.slice(scan),
						render_o.slice(scan).skip(step)
					)))
					&	XTAL_FLX_(self().efflux(oo...)) (R_::template influx_push(XTAL_REF_(render_o)));
				}
				///\
				Renders the buffer slice designated by `review_o` and `render_o`. \
				
				template <occur::review_q Rev, occur::render_q Ren>
				XTAL_TNX efflux_slice(Rev &&review_o, Ren &&render_o)
				XTAL_0EX
				{
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
						XTAL_0IF (1) {for (size_t m = 0; m < n; ++m) {*_i++ = XTAL_MOV_(*_j++);}}

						return 0;
					}
				}

			};
		};

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
