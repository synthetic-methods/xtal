#pragma once
#include "./any.hh"

#include "./mask.hh"




XTAL_ENV_(push)
namespace xtal::flow
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
Wrapper used to tunnel an existing type using `std::tuple`-based traversal.

///\see [../process/cross.ipp].

////////////////////////////////////////////////////////////////////////////////

template <typename     ..._s> struct   indent;
template <typename     ..._s> concept  indent_q = bond::tag_p<indent, _s...>;
template <class S, int ...Ns> using    indent_s = bond::compose_s<S, indent<ordinal_constant_t<Ns>...>>;

template <constant_q ...Ns>
struct indent<Ns...>
{
	template <class S> using component_t = bond::pack_item_t<S, Ns{}...>;
	template <class S> using component_s = bond::pack_item_s<S, Ns{}...>;
	
	using superkind = bond::compose<void
	,	confined<bond::tag<indent>, confer<Ns>...>
	,	bond::compose_t<conferred_t>
	,	bond::compose_t<component_t>
	>;
	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		static_assert(bond::pack_q<S>);
		using S_ = bond::compose_s<S, superkind>;
		using W_ =     component_s<S >;
		using U_ =   initializer_u<W_>;

	public:
		using S_::S_;//NOTE: Inherited and respecialized!
		
		///\note\
		Scalar fragments are currently mapped with `ordinate`, if detected. \

		///\todo\
		Use strong-`value_type`s to map between fractional integral and floating-point values? \

		XTAL_NEW_(explicit)
		subtype(U_ u)
		noexcept requires un_n<iterable_q<U_>> and in_n<requires {W_::ordinate(u);}>
		:	S_{W_::ordinate(XTAL_MOV_(u))}
		{}
		XTAL_NEW_(explicit)
		subtype(U_ u)
		noexcept requires in_n<iterable_q<U_>> or  un_n<requires {W_::ordinate(u);}>
		:	S_{             XTAL_MOV_(u) }
		{}
		XTAL_NEW_(implicit)
		subtype(_std::initializer_list<U_> w)
		noexcept requires in_n<iterable_q<U_>>
		:	S_{w}
		{}

		template <extent_type N_mask=-1>
		struct afflux
		{
			///\todo\
			Test `address`ing, since it's conveyed by the base-`T` (i.e. `path`).

			using superkind = bond::compose<flow::mask<N_mask>, defer<component_t<S>>>;

			template <class R> requires un_n<sizeof...(Ns)>
			class subtype : public bond::compose_s<R, superkind>
			{
				static_assert(flow::any_q<R>);
				using R_ = bond::compose_s<R, superkind>;
				
			public:
				using R_::R_;
				using R_::self;
				using R_::head;

				///\todo\
				Implement `indent_q` bounds-checking based on the `rank` specified by `R` or `Ns...`? \
				
				template <signed N_ion>
				XTAL_DEF_(return,inline,let)
				fuse(auto &&o)
				noexcept -> signed
				{
					return R_::template fuse<N_ion>(XTAL_REF_(o));
				}
				template <signed N_ion> requires in_n<N_ion, +1>
				XTAL_DEF_(return,let)
				fuse(indent_q auto &&o)
				noexcept -> signed
				{
					/*/
					auto &m = bond::pack_item_f(o.seek(), head());
					XTAL_ALL_(m) x(o);
					_std::swap(m, x);
					return m == x;
					/*/
					auto &m = bond::pack_item_f(o.seek(), head());
					using M = XTAL_ALL_(m);
					m.~M(); new (&m) M(XTAL_REF_(o));
					return 0;
					/***/
				}

			};
		};

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
