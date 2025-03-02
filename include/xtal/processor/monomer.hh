#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::processor
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class ..._s> struct  monomer;
template <class ..._s> using   monomer_t =  confined_t<monomer< _s...>>;
template <class ..._s> concept monomer_q = bond::tagged_with_p<monomer, _s... >;

////////////////////////////////////////////////////////////////////////////////

template <typename ...As>
XTAL_DEF_(let) monomer_f = []<class U> (U &&u)
XTAL_0FN_(to) (monomer_t<based_t<U>, As...>(XTAL_REF_(u)));


////////////////////////////////////////////////////////////////////////////////

template <incomplete_q A, typename ...As>
struct monomer<A, As...>
:	monomer<As...>
{
};
template <bond::compose_q A, typename ...As>
struct monomer<A, As...>
:	bond::compose<A, monomer<As...>>
{
};
template <class U, typename ...As>
struct monomer<U, As...>
{
	using superkind = confer<U, As..., provision::stated<>, provision::voiced<>>;

	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind>;
		using T_ = typename S_::self_type;

		template <class ...Xs>
		using F_ = bond::compose<bond::tag<monomer>, As...
		,	typename S_::template binding<Xs...>
		>;
	
	public:
		using S_::S_;
		using S_::self;

		template <class ...Xs>
		struct binding
		{
			using Y_result = return_t<T_, return_t<Xs>...>;
		//	using Y_return = deiteratee_t<Y_result>;

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
				XTAL_NEW_(delete) (subtype, noexcept = default)
				XTAL_NEW_(create) (subtype, noexcept = default)
				XTAL_NEW_(move)   (subtype, noexcept = default)
				XTAL_NEW_(copy)   (subtype, noexcept = default)
				XTAL_NEW_(cast)   (subtype, noexcept)

				XTAL_NEW_(explicit)
				subtype(same_q<Xs> auto &&...xs)
				noexcept
				:	subtype{T_{}, XTAL_REF_(xs)...}
				{}
				XTAL_NEW_(explicit)
				subtype(same_q<T_> auto &&t, same_q<Xs> auto &&...xs)
				noexcept
				:	subtype{R_::method(XTAL_REF_(xs)...), XTAL_REF_(t), XTAL_REF_(xs)...}
				{}
				XTAL_NEW_(explicit)
				subtype(auto &&f, same_q<T_> auto &&t, same_q<Xs> auto &&...xs)
				noexcept
				:	R_(XTAL_REF_(f), XTAL_REF_(t), XTAL_REF_(xs)...)
				{}

			public:// ACCESS

				XTAL_FX4_(to) (XTAL_DEF_(return,inline,get)
				state(auto &&...oo),
					R_::template head<Y_result>(XTAL_REF_(oo)...))

			public:// OPERATE

				XTAL_FX2_(do) (template <auto ...>
				XTAL_DEF_(return,inline,let)
				method(),
				noexcept -> decltype(auto)
				{
					return state();
				})

			public:// FLOW
				template <signed N_ion>
				XTAL_DEF_(return,inline,let)
				flux(auto &&...oo)
				noexcept -> signed
				{
					return R_::template flux<N_ion>(XTAL_REF_(oo)...);
				}
				template <signed N_ion> requires in_n<N_ion, -1>
				XTAL_DEF_(return,inline,let)
				flux(occur::cursor_q auto &&cur, auto &&...oo)
				noexcept -> signed
				{
					return [&, this]
						XTAL_1FN_(and) ((void) state(R_::method()), 0)
							(R_::template flux<N_ion>(XTAL_REF_(cur), XTAL_REF_(oo)...));
				}

			};
		};
		template <class ...Xs> requires provision::stated_q<S_> and provision::stored_q<S_>
		struct binding<Xs...>
		{
			using Y_result = return_t<T_, return_t<Xs>...>;
			using Y_return = deiteratee_t<Y_result>;

			using U_store  = typename S_::template store_t<Y_return>;
			using U_state  = typename S_::template state_t<U_store >;
		
			static constexpr int N_share = bond::seek_truth_n<_detail::recollection_p<Xs, U_state>...>;
			
			using superkind = bond::compose<provision::stowed<U_state, U_store>, F_<Xs...>>;

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
				
				XTAL_FX2_(do) (template <auto ...>
				XTAL_DEF_(return,inline,let)
				method(),
				noexcept -> decltype(auto)
				{
					return state();
				})
				
			public:// FLOW

				XTAL_FX0_(to) (template <signed N_ion>
				XTAL_DEF_(return,inline,let)
				fuse(auto &&o),
					R_::template fuse<N_ion>(XTAL_REF_(o)))

				XTAL_FX0_(to) (template <signed N_ion>
				XTAL_DEF_(return,inline,let)
				flux(auto &&...oo),
					R_::template flux<N_ion>(XTAL_REF_(oo)...))

				///\
				Responds to `occur::resize` by resizing the `store()`. \

				template <signed N_ion> requires in_n<N_ion, +1>
				XTAL_DEF_(return,let)
				fuse(occur::resize_q auto &&o)
				noexcept -> signed
				{
					if (R_::template fuse<N_ion>(o) == 1) {
						return 1;
					}
					else {
						auto &u = store();
						auto  i = point_f(u);
						auto  n = count_f(XTAL_REF_(o));
						XTAL_IF1_(do) (u.resize(n))
						(void) state(i, i);//NOTE: For consistency with `vector` stores.
						return 0;
					}
				}
				///\note\
				Resizing skips immediate shared/`recollection_p` dependencies, \
				continuing to propagate beyond. \

				template <signed N_ion>
				XTAL_DEF_(return,let)
				flux_rest(auto &&...oo)
				noexcept -> signed
				{
					return R_::template flux_rest<N_ion>(XTAL_REF_(oo)...);
				}
				template <signed N_ion>
				XTAL_DEF_(return,let)
				flux_rest(auto &&...oo)
				noexcept -> signed
				requires in_n<1, occur::resize_q<decltype(oo)>...>
				{
					using I_head = ordinal_constant_t<N_share>;
					using I_path = ordinal_constant_t<-1>;
					return R_::template flux_unrest<N_ion>(I_head{}, I_path{}, XTAL_REF_(oo)...);
				}

				///\brief\
				Responds to `occur::cursor` by rendering the `store()`. \
				
				///\returns `0` if the supplied cursor is next in sequence and can be rendered to `store()`, \
				`1` if the cursor is current and the outcome has already been rendered, \
				otherwise the system is inconsistent and checked by `assert`ion. \
				
				template <signed N_ion> requires in_n<N_ion, -1>
				XTAL_DEF_(return,inline,let)
				flux(occur::cursor_q auto &&cur, auto &&...oo)
				noexcept -> signed
				{
					occur::review_t<U_state> rev(store()); rev = rev.subview(cur.size());
					return flux<N_ion>(XTAL_MOV_(rev), XTAL_REF_(cur), XTAL_REF_(oo)...);
				}
				///\note\
				When accompanied by `occur::review`, the supplied `subrange` or `span` will be used instead. \
				All arguments `Xs...` are rendered internally unless a compatible `rvalue` is found, \
				in which case the `review` will be passed upstream. \

				template <signed N_ion> requires in_n<N_ion, -1>
				XTAL_DEF_(return,inline,let)
				flux(occur::review_q auto &&rev, occur::cursor_q auto &&cur, auto &&...oo)
				noexcept -> signed
				{
					if constexpr (requires {U_state(rev);}) {(void) state(rev);}
					return R_::template flux<N_ion>(XTAL_REF_(rev), XTAL_REF_(cur), XTAL_REF_(oo)...);
				}

			};
		};

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
