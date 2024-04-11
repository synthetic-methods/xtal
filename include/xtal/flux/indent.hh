#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::flux
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
Wrapper used to tunnel an existing type using `std::tuple`-based traversal.

///\see [../process/cross.ipp].

////////////////////////////////////////////////////////////////////////////////

template <typename     ..._s> struct  indent;
template <typename     ..._s> concept indent_q = bond::tag_p<indent, _s...>;
template <class S, int ...Ns> using   indent_s = bond::compose_s<S, indent<ordinal_t<Ns>...>>;

template <integral_q ...Ns>
struct indent<Ns...>
{
	using path = confined<bond::tag<indent>, confer<Ns>...>;
	
	template <bond::pack_q S> using leaf_u = bond::pack_item_t<S, Ns{}...>;
	template <bond::pack_q S> using leaf_t = conferred_t<leaf_u<S>>;
	template <bond::pack_q S> using node_t = typename path::template subtype<leaf_t<S>>;
	template <bond::pack_q S>
	class subtype : public node_t<S>
	{
		using S_ = node_t<S>;
		using L_ = leaf_u<S>;

	public:
		using S_::S_;
		
		XTAL_CON subtype(braces_t<devalue_t<L_>> w)
		XTAL_REQ bounded_q<L_>
		:	S_{L_(XTAL_MOV_(w))}
		{}

		struct tunnel
		{
			using subkind = defer<L_>;

			template <cell::any_q R> requires (0 == sizeof...(Ns))
			class subtype : public bond::compose_s<R, subkind>
			{
				using R_ = bond::compose_s<R, subkind>;
				
			public:
				using R_::R_;
				using R_::self;
				using R_::head;
			//	using R_::infuse;

				///\todo\
				Implement `indent_q` bounds-checking based on the `rank` specified by `R` or `Ns...`? \
				Requires subsequence ordering for `bond::pack`s? \
				
				XTAL_TNX infuse(auto &&o)
				XTAL_0EX
				{
					return R_::infuse(XTAL_REF_(o));
				}
				XTAL_TNX infuse(flux::indent_q auto &&o)
				XTAL_0EX
				{
					auto &w = bond::pack_item_f(head(), o.apple());
					auto  x = XTAL_TYP_(w) (o);
					_std::swap(w, x);
					return w == x;
				}

			};
		};
	
	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)