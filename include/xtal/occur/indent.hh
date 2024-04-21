#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::occur
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
	template <class S> using component_t = bond::pack_item_t<S, Ns{}...>;
	using item = bond::compost<component_t>;
	using leaf = bond::compost<conferred_t>;
	using path = confined<bond::tag<indent>, confer<Ns>...>;
	
	using subkind = bond::compose<path, leaf, item>;

	template <bond::pack_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;
	//	using W_ = bond::compose_s<S, item>;
		using W_ = component_t<S>;
		using U_ = devalue_t<reembrace_t<S>>;//   presentation
		using V_ = devalue_t<            S >;// representation

	public:
		using S_::S_;
		
		///\note\
		Any integral/real re/presentation is interpreted as a full-width fixed-point value \
		(\see `algebra/differential/phase.hh`). \

		///\todo\
		Normalize the use of `operator()` to access `block` elements, \
		defining a `concept` to characterize the disparity. \

		XTAL_CON subtype(U_ u)
		XTAL_REQ real_number_q<U_> and integral_number_q<V_>
		:	S_{XTAL_MOV_(u)*bond::realize<U_>::diplo_f()}
		{}
		XTAL_CON subtype(reembrace_t<W_> w)
		XTAL_REQ bounded_q<W_>
		:	S_{w}
		{}

		template <int N_mask=-1>
		struct funnel
		{
			///\todo\
			Test `address`ing, since it's conveyed by the base-`T` (i.e. `path`).

			using subkind = bond::compose<typename S_::template address<N_mask>, defer<W_>>;

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
				XTAL_TNX infuse(indent_q auto &&o)
				XTAL_0EX
				{
					auto &w = bond::pack_item_f(head(), o.pack());
					XTAL_TYP_(w) x(o);
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
