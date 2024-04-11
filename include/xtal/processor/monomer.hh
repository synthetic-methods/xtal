#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::processor
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ..._s> struct  monomer;
template <typename ..._s> using   monomer_t = confined_t<monomer< _s...>>;
template <typename ..._s> concept monomer_q = bond::tag_p<monomer, _s...>;
template <typename ...As>
XTAL_FN2  monomer_f(auto &&u)
XTAL_0EZ_(monomer_t<XTAL_TYP_(u), As...>(XTAL_REF_(u)))


////////////////////////////////////////////////////////////////////////////////

template <class U, typename ...As>
struct monomer<U, As...>
{
	using U_resize = occur::resize_t<>;
	using U_render = occur::render_t<>;

	using subkind = confer<U, As...>;

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
		using typename S_::T_self;

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

				XTAL_TO4_(XTAL_TN2 serve(auto &&...oo), R_::head(XTAL_REF_(oo)...))
				XTAL_TO2_(template <auto ...> XTAL_TN2 functor(), serve())


			public:// FLUXION
				using R_::efflux;

				XTAL_TNX efflux(occur::render_q auto &&render_o)
				XTAL_0EX
				{
					return XTAL_FLX_((void) serve(R_::functor()), 0) (R_::efflux(XTAL_REF_(render_o)));
				}

			};
		};
		template <class ...Xs> requires resource::restore_q<S_>
		struct binding<Xs...> : S__binding<Xs...>
		{
			using Y_return = typename S__binding<Xs...>::Y_return;
			using U_buffer = typename S_::template store_t<Y_return>;
			using U_serve  = reiterated_t<U_buffer>;
			using U_review = occur::review_t<U_serve>;
		
			XTAL_LET_(int)  N_share = bond::seek_truth_n<_detail::recollection_p<Xs, U_serve>...>;
			XTAL_LET_(bool) N_sized = requires (U_buffer &u) {u.resize(U_resize{});};

			using subkind = bond::compose<resource::reserve<U_buffer>, R__binding<Xs...>>;

			template <any_q R>
			class subtype : public bond::compose_s<R, subkind>
			{
				using R_ = bond::compose_s<R, subkind>;

			public:
				using R_::R_;
				using R_::self;
				using R_::serve;
				using R_::store;
				XTAL_TO2_(template <auto ...>
				XTAL_TN2 functor(), N_sized? serve(): serve()|recount_f(R_::template head_t<U_resize>))

			//	using R_::infuse;
				///\
				Responds to `occur::resize` by resizing the internal `store()`. \

				XTAL_TNX infuse(auto &&o)
				XTAL_0EX
				{
					if constexpr (is_q<U_resize, decltype(o)>) {
						return R_::infuse(o) or ([o = XTAL_REF_(o), this] ()
						XTAL_0FN
						{
							if constexpr (N_sized) {store().resize(XTAL_MOV_(o));}
							return XTAL_FLX{};
						}	());
					}
					else {
						return R_::infuse(XTAL_REF_(o));
					}
				}
				using R_::influx_push;
				///\note\
				Resizing skips intermediate `recollection_p` dependencies, \
				continuing to propagate beyond. \

				XTAL_TNX influx_push(U_resize o_resize, auto &&...oo)
				XTAL_0EX
				XTAL_REQ (0 <= N_share)
				{
					return R_::template influx_push_tail<N_share>(null_t(), o_resize, XTAL_REF_(oo)...);
				}


				using R_::efflux;
				///\
				Responds to `occur::render` by rendering the internal `store()`. \
				A match for the following render will initiate the `review` (returning `1`), \
				while a match for the current render will terminate (returning `0`). \
				(Deviant behaviour is enforced by `assert`ion on `render`.) \

				template <occur::render_q Rn>
				XTAL_TNX efflux(Rn render_o, auto &&...oo)
				XTAL_0EX
				{
					return efflux(U_review(store()), render_o, XTAL_REF_(oo)...);
				}
				///\note\
				When accompanied by `occur::review`, the supplied visor will be used instead. \
				All `slots` are rendered locally unless a `visor`-compatible `rvalue` is found, \
				in which case the visor will be reused for the intermediate result. \

				template <occur::review_q Rv, occur::render_q Rn>
				XTAL_TNX efflux(Rv review_o, Rn render_o, auto &&...oo)
				XTAL_0EX
				{
					static_assert(is_q<Rv, U_review>);// Otherwise...?

					if (R_::effuse(render_o) == 1) {
						return 1;
					}
					else {
						(void) serve(review_o);
						return self().reflux([&, this] (auto step, counted_q auto scan)
							XTAL_0FN_(self().efflux_pull_slice(review_o.slice(scan), render_o.slice(scan).skip(step), oo...))
						) & R_::template influx_push(render_o);
					}
				}
				///\
				Renders the buffer slice designated by `review_o` and `render_o`. \
				
				template <occur::review_q Rv, occur::render_q Rn>
				XTAL_TNX efflux_pull_slice(Rv review_o, Rn render_o, auto &&...oo)
				XTAL_0EX
				{
					static_assert(is_q<Rv, U_review>);// Otherwise...?

					return 1 == R_::template efflux_pull_tail<N_share>(review_o, render_o, oo...) or
						(_v3::ranges::move(R_::functor()|recount_f(review_o), review_o.begin()), 0);
				}

			};
		};

	};
};

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
