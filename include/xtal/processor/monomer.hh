#pragma once
#include "./any.hh"

#include "../flux/slot.hh"




XTAL_ENV_(push)
namespace xtal::processor
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ..._s> XTAL_TYP monomer;
template <typename ..._s> XTAL_USE monomer_t = confined_t<monomer< _s...>>;
template <typename ..._s> XTAL_ASK monomer_q = bond::any_tag_p<monomer, _s...>;
template <typename ...As>
XTAL_DEF_(return,inline)
XTAL_LET monomer_f(auto &&u)
noexcept -> auto
{
	return monomer_t<XTAL_ALL_(u), As...>(XTAL_REF_(u));
}


////////////////////////////////////////////////////////////////////////////////

template <bond::compose_q A, typename ...As>
struct monomer<A, As...>
:	bond::compose<A, monomer<As...>>
{
};
template <class U, typename ...As>
struct monomer<U, As...>
{
	using U_resize = occur::resize_t<>;
//	using U_render = occur::render_t<>;

	using superkind = confer<U, As..., resource::stated<>, resource::invoice<>>;

	template <any_q S>
	class subtype : public bond::compose_s<S, superkind>
	{
		using S_ = bond::compose_s<S, superkind>;
		using T_ = typename S_::self_type;

		template <class ...Xs>
		using F_ = bond::compose<bond::tag<monomer>, As...
//		,	U_resize::attach<>
//		,	U_render::attach<>
		,	typename S_::template bracket<Xs...>
		>;
	
	public:
		using S_::S_;
		using S_::self;

		template <class ...Xs>
		struct bracket
		{
			using Y_result = _std::invoke_result_t<T_, _std::invoke_result_t<Xs>...>;
		//	using Y_return = iteratee_t<Y_result>;

			using superkind = bond::compose<void
			,	cell::confer<Y_result>
			,	F_<Xs...>
			>;
			template <any_q R>
			class subtype : public bond::compose_s<R, superkind>
			{
				using R_ = bond::compose_s<R, superkind>;

			public:// CONSTRUCT
			//	using R_::R_;
				XTAL_CO0_(subtype);
				XTAL_CO1_(subtype);
				XTAL_CO4_(subtype);

				XTAL_NEW_(explicit) subtype(XTAL_ARG_(Xs) &&...xs)
				noexcept
				:	subtype(T_{}, XTAL_REF_(xs)...)
				{}
				XTAL_NEW_(explicit) subtype(XTAL_ARG_(T_) &&t, XTAL_ARG_(Xs) &&...xs)
				noexcept
				:	subtype(R_::method(XTAL_REF_(xs)...), XTAL_REF_(t), XTAL_REF_(xs)...)
				{}
				XTAL_NEW_(explicit) subtype(auto &&f, XTAL_ARG_(T_) &&t, XTAL_ARG_(Xs) &&...xs)
				noexcept
				:	R_(XTAL_REF_(f), XTAL_REF_(t), XTAL_REF_(xs)...)
				{}

			public:// ACCESS

				XTAL_DO4_(XTAL_DEF_(return,inline)
				XTAL_LET state(auto &&...oo), -> decltype(auto)
				{
					return R_::template head<Y_result>(XTAL_REF_(oo)...);
				})

			public:// FUNC*
			//	using R_::method;

				XTAL_DO2_(template <auto ...>
				XTAL_DEF_(return,inline)
				XTAL_LET method(), -> decltype(auto)
				{
					return state();
				})

			public:// *FLUX
				using R_::efflux;

				XTAL_DEF_(return,inline)
				XTAL_LET efflux(occur::render_q auto &&render_o)
				noexcept -> sign_type
				{
					return [this] XTAL_XFN_((void) state(R_::method()), 0) (R_::efflux(XTAL_REF_(render_o)));
				}

			};
		};
		template <class ...Xs> requires resource::stated_q<S_> and resource::stored_q<S_>
		struct bracket<Xs...>
		{
			using Y_result = _std::invoke_result_t<T_, _std::invoke_result_t<Xs>...>;
			using Y_return = iteratee_t<Y_result>;

			using U_store  = typename S_::template store_t<Y_return>;
			using U_state  = typename S_::template state_t<U_store >;
		
			static constexpr int N_share = bond::seek_index_n<_detail::recollection_p<Xs, U_state>...>;
			
			using superkind = bond::compose<resource::stashed<U_state, U_store>, F_<Xs...>>;

			template <any_q R>
			class subtype : public bond::compose_s<R, superkind>
			{
				using R_ = bond::compose_s<R, superkind>;

			public:// CONSTRUCT
				using R_::R_;

			public:// ACCESS
				using R_::self;
				using R_::state;
				using R_::store;

			public:// FUNC*
			//	using R_::method;
				
				XTAL_DO2_(template <auto ...>
				XTAL_DEF_(return,inline)
				XTAL_LET method(), -> decltype(auto)
				{
					return state();
				})
				
			public:// *FLUX

			//	using R_::infuse;
				///\
				Responds to `occur::resize` by resizing the internal `store()`. \

				XTAL_DEF_(return,inline)
				XTAL_LET infuse(auto &&o)
				noexcept -> sign_type
				{
					return R_::infuse(XTAL_REF_(o));
				}
				XTAL_DEF_(return)
				XTAL_LET infuse(occur::resize_q auto &&o)
				noexcept -> sign_type
				{
					if (R_::infuse(o) == 1) {
						return 1;
					}
					else {
						auto &u = store();
						auto  i = u.begin();
						auto  n = XTAL_REF_(o).size();
						XTAL_IF0
						XTAL_0IF XTAL_TRY_DO_(u.resize(n))
						(void) state(i, i);//NOTE: For consistency with `vector` stores.
						return 0;
					}
				}
				using R_::influx_push;
				///\note\
				Resizing skips intermediate `recollection_p` dependencies, \
				continuing to propagate beyond. \

				XTAL_DEF_(return,inline)
				XTAL_LET influx_push(occur::resize_q auto &&o_resize, auto &&...oo)
				noexcept -> sign_type
				{
					return R_::template influx_push<N_share>(flux::slot_n<-1>, XTAL_REF_(o_resize), XTAL_REF_(oo)...);
				}

				using R_::efflux;
				///\
				Responds to `occur::render` by rendering the internal `store()`. \
				A match for the following render will initiate the `review` (returning `1`), \
				while a match for the current render will terminate (returning `0`). \
				(Deviant behaviour is enforced by `assert`ion on `render`.) \

				template <occur::render_q Ren>
				XTAL_DEF_(return)
				XTAL_LET efflux(Ren &&render_o, auto &&...oo)
				noexcept -> sign_type
				{
					size_type vN = R_::template head<U_resize>();
					occur::review_t<U_state> v_(store());
					return efflux(v_.subview(vN), XTAL_REF_(render_o), XTAL_REF_(oo)...);
				}
				///\note\
				When accompanied by `occur::review`, the supplied visor will be used instead. \
				All bound arguments are rendered privately unless a compatible `rvalue` is found, \
				in which case the visor will be reused for the intermediate result. \

				///\note\
				When the visor is unrecognized, \
				the zipped `method` is rendered without saving the result in `state()`, \
				which will remain empty. \

				template <occur::review_q Rev, occur::render_q Ren>
				XTAL_DEF_(return,inline)
				XTAL_LET efflux(Rev &&review_o, Ren &&render_o, auto &&...oo)
				noexcept -> sign_type
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
