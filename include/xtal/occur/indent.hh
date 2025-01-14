#pragma once
#include "./any.hh"

#include "../flux/mask.hh"




XTAL_ENV_(push)
namespace xtal::occur
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
Wrapper used to tunnel an existing type using `std::tuple`-based traversal.

///\see [../process/cross.ipp].

////////////////////////////////////////////////////////////////////////////////

template <typename     ..._s> struct   indent;
template <typename     ..._s> concept  indent_q = bond::tag_p<indent, _s...>;
template <class S, int ...Ns> using    indent_s = bond::compose_s<S, indent<constant_t<Ns>...>>;

template <constant_q ...Ns>
struct indent<Ns...>
{
	template <class S>
	using component_t = bond::pack_item_t<S, Ns{}...>;
	
	using item = bond::compose_t<component_t>;
	using leaf = bond::compose_t<conferred_t>;
	using path = confined<bond::tag<indent>, confer<Ns>...>;
	
	using superkind = bond::compose<path, leaf, item>;

	template <bond::pack_q S>
	class subtype : public bond::compose_s<S, superkind>
	{
		using S_ = bond::compose_s<S, superkind>;
	//	using U_ = bond::compose_s<S, item>;
		using U_ = component_t<S>;

	public:
		using S_::S_;
		
		///\note\
		When `covalued_q<S>`, `S::ordinate` is invoked to produce the edit. \

		///\todo\
		Find a better way to invoke `S::ordinate` implicitly for any `indent`ed scalar fragments. \

		/*/
		XTAL_NEW_(explicit) subtype(initializer_u<S> u)
		noexcept
		:	S_{XTAL_MOV_(u)}
		{}
		/*/
		XTAL_NEW_(explicit) subtype(initializer_u<S> u)
		noexcept
		requires   in_n<iterable_q<initializer_u<S>>>
		:	S_{XTAL_MOV_(u)}
		{}
		XTAL_NEW_(explicit) subtype(initializer_u<S> u)
		noexcept
		requires   un_n<iterable_q<initializer_u<S>>>
		:	S_{S::ordinate(XTAL_MOV_(u))}
		{
		}
		/***/

		XTAL_NEW_(implicit) subtype(initializer_t<U_> w)
		noexcept
		requires iterable_q<U_>
		:	S_{w}
		{}

		template <extent_type N_mask=-1>
		struct funnel
		{
			///\todo\
			Test `address`ing, since it's conveyed by the base-`T` (i.e. `path`).

			using superkind = bond::compose<flux::mask<N_mask>, defer<U_>>;

			template <cell::any_q R> requires (0 == sizeof...(Ns))
			class subtype : public bond::compose_s<R, superkind>
			{
				using R_ = bond::compose_s<R, superkind>;
				
			public:
				using R_::R_;
				using R_::self;
				using R_::head;
			//	using R_::infuse;

				///\todo\
				Implement `indent_q` bounds-checking based on the `rank` specified by `R` or `Ns...`? \
				Requires subsequent ordering for `bond::pack`s? \
				
				XTAL_DEF_(short)
				XTAL_LET infuse(auto &&o)
				noexcept -> signed
				{
					return R_::infuse(XTAL_REF_(o));
				}
				XTAL_DEF_(long)
				XTAL_LET infuse(indent_q auto &&o)
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
