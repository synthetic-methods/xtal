#pragma once
#include "./any.hh"

#include "../flow/argument.hh"




XTAL_ENV_(push)
namespace xtal::processor
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ..._s> struct   monomer;
template <typename ..._s> using    monomer_t =  confined_t<monomer< _s...>>;
template <typename ..._s> concept  monomer_q = bond::tag_p<monomer, _s... >;
template <typename ...As>
XTAL_DEF_(short)
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

	using superkind = confer<U, As..., provision::stated<>, provision::context<>>;

	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind>;
		using T_ = typename S_::self_type;

		template <class ...Xs>
		using F_ = bond::compose<bond::tag<monomer>, As...
//		,	U_resize::attach<>
//		,	U_render::attach<>
		,	typename S_::template closure<Xs...>
		>;
	
	public:
		using S_::S_;
		using S_::self;

		template <class ...Xs>
		struct closure
		{
			using Y_result = return_t<T_, return_t<Xs>...>;
		//	using Y_return = iterated_u<Y_result>;

			using superkind = bond::compose<void
			,	cell::confer<Y_result>
			,	F_<Xs...>
			>;
			template <class R>
			class subtype : public bond::compose_s<R, superkind>
			{
				static_assert(any_q<R>);
				using R_ = bond::compose_s<R, superkind>;

			public:// CONSTRUCT
			//	using R_::R_;
			~	subtype()                noexcept=default;
				subtype()                noexcept=default;
				XTAL_NEW_(copy, subtype, noexcept=default)
				XTAL_NEW_(move, subtype, noexcept=default)

				XTAL_NEW_(explicit) subtype(same_q<Xs> auto &&...xs)
				noexcept
				:	subtype(T_{}, XTAL_REF_(xs)...)
				{}
				XTAL_NEW_(explicit) subtype(same_q<T_> auto &&t, same_q<Xs> auto &&...xs)
				noexcept
				:	subtype(R_::method(XTAL_REF_(xs)...), XTAL_REF_(t), XTAL_REF_(xs)...)
				{}
				XTAL_NEW_(explicit) subtype(auto &&f, same_q<T_> auto &&t, same_q<Xs> auto &&...xs)
				noexcept
				:	R_(XTAL_REF_(f), XTAL_REF_(t), XTAL_REF_(xs)...)
				{}

			public:// ACCESS

				XTAL_TO4_(XTAL_DEF_(let) state(auto &&...oo), R_::template head<Y_result>(XTAL_REF_(oo)...))

			public:// OPERATE

				XTAL_DO2_(template <auto ...>
				XTAL_DEF_(short)
				XTAL_LET method(),
				noexcept -> decltype(auto)
				{
					return state();
				})

			public:// FLOW
				template <signed N_ion>
				XTAL_DEF_(short)
				XTAL_LET flux(auto &&...oo)
				noexcept -> signed
				{
					return R_::template flux<N_ion>(XTAL_REF_(oo)...);
				}
				template <signed N_ion> requires in_n<N_ion, -1>
				XTAL_DEF_(short)
				XTAL_LET flux(occur::render_q auto &&render_o)
				noexcept -> signed
				{
					return [this]
						XTAL_XFN_(1, &, (void) state(R_::method()), 0)
							(R_::template flux<N_ion>(XTAL_REF_(render_o)));
				}

			};
		};
		template <class ...Xs> requires provision::stated_q<S_> and provision::stored_q<S_>
		struct closure<Xs...>
		{
			using Y_result = return_t<T_, return_t<Xs>...>;
			using Y_return = iterated_u<Y_result>;

			using U_store  = typename S_::template store_t<Y_return>;
			using U_state  = typename S_::template state_t<U_store >;
		
			static constexpr int N_share = bond::seek_truth_n<_detail::recollection_p<Xs, U_state>...>;
			
			using superkind = bond::compose<provision::stashed<U_state, U_store>, F_<Xs...>>;

			template <class R>
			class subtype : public bond::compose_s<R, superkind>
			{
				static_assert(any_q<R>);
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
				XTAL_DEF_(short)
				XTAL_LET method(),
				noexcept -> decltype(auto)
				{
					return state();
				})
				
			public:// FLOW

				template <signed N_ion> XTAL_DEF_(let) fuse(auto &&o    ) noexcept {return R_::template fuse<N_ion>(XTAL_REF_(o)    );}
				template <signed N_ion> XTAL_DEF_(let) flux(auto &&...oo) noexcept {return R_::template flux<N_ion>(XTAL_REF_(oo)...);}

				///\
				Responds to `occur::resize` by resizing the internal `store()`. \

				template <signed N_ion> requires in_n<N_ion, +1>
				XTAL_DEF_(short)
				XTAL_LET fuse(occur::resize_q auto &&o)
				noexcept -> signed
				{
					if (R_::template fuse<N_ion>(o) == 1) {
						return 1;
					}
					else {
						auto &u = store();
						auto  i = point_f(u);
						auto  n = count_f(XTAL_REF_(o));
						if constexpr XTAL_TRY_DO_(u.resize(n))
						(void) state(i, i);//NOTE: For consistency with `vector` stores.
						return 0;
					}
				}
				///\note\
				Resizing skips intermediate `recollection_p` dependencies, \
				continuing to propagate beyond. \

				template <signed N_ion>
				XTAL_DEF_(short)
				XTAL_LET flux_arguments(auto &&...oo)
				noexcept -> signed
				{
					XTAL_LET N_dex = occur::some_resize_q<decltype(oo)...>? N_share: -1;
					return R_::template flux_arguments_<N_ion, N_dex>(flow::argument_n<-1>, XTAL_REF_(oo)...);
				}

				///\
				Responds to `occur::render` by rendering the internal `store()`. \
				A match for the following render will initiate the `review` (returning `1`), \
				while a match for the current render will terminate (returning `0`). \
				(Deviant behaviour is enforced by `assert`ion on `render`.) \

				template <signed N_ion> requires in_n<N_ion, -1>
				XTAL_DEF_(short)
				XTAL_LET flux(occur::render_q auto &&render_o, auto &&...oo)
				noexcept -> signed
				{
					size_type const n_resize = R_::template head<U_resize>();
					occur::review_t<U_state> v_(store());
					return flux<N_ion>(v_.subview(n_resize), XTAL_REF_(render_o), XTAL_REF_(oo)...);
				}
				///\note\
				When accompanied by `occur::review`, the supplied visor will be used instead. \
				All bound arguments are rendered privately unless a compatible `rvalue` is found, \
				in which case the visor will be reused for the intermediate result. \

				///\note\
				When the visor is unrecognized, \
				the zipped `method` is rendered without saving the result in `state()`, \
				which will remain empty. \

				template <signed N_ion> requires in_n<N_ion, -1>
				XTAL_DEF_(short)
				XTAL_LET flux(occur::review_q auto &&review_o, occur::render_q auto &&render_o, auto &&...oo)
				noexcept -> signed
				{
					if constexpr (make_p<U_state, decltype(review_o)>) {
						(void) state(review_o);
					}
					return R_::template flux<N_ion>(XTAL_REF_(review_o), XTAL_REF_(render_o), XTAL_REF_(oo)...);
				}

			};
		};

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
