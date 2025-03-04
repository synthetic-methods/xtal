#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::flow
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/*!
\brief
Duplicates the `concept`s from `bond::tab`.
*/
template <class T, class ...Ks> concept       tab_as_q = bond::       tab_as_q<T, Ks...>;
template <class T, class ...Ks> concept tab_affixed_q = bond:: tab_affixed_q<T, Ks...>;
template <class T, class ...Ks> concept       tab_in_q = bond::       tab_in_q<T, Ks...>;
template <class T, class ...Ks> concept tab_infixed_q = bond:: tab_infixed_q<T, Ks...>;

template <class K, class ...Ts> concept       tab_as_p = bond::       tab_as_p<K, Ts...>;
template <class K, class ...Ts> concept tab_affixed_p = bond:: tab_affixed_p<K, Ts...>;
template <class K, class ...Ts> concept       tab_in_p = bond::       tab_in_p<K, Ts...>;
template <class K, class ...Ts> concept tab_infixed_p = bond:: tab_infixed_p<K, Ts...>;


//////////////////////////////////////////////////////////////////////////////////
/*!
\brief
Provides conversion from `bond::tab_compatible_q` types when `fuse`d.

\details
Intended to override the default `fuse` (which consumes exact matches for `self_type`)
to accommodate types with template-equivalence.
*/
template <typename ..._s>
struct tab
{
	using superkind = bond::compose<bond::tab<_s>...>;

	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind>;
		using T_ = typename S_::self_type;
	
	public:// CONSTRUCT
		using S_::S_;

	public:// *FUSE

		/*!
		\brief  	Forwards message upstream.
		*/
		template <signed N_ion>
		XTAL_DEF_(return,inline,let)
		fuse(auto &&o)
		noexcept -> signed
		{
			return S_::template fuse<N_ion>(XTAL_REF_(o));
		}
		/*!
		\brief  	If the argument has the same `bond::tab` signature as `self_type`,
		attempt reconstruction.
		*/
		template <signed N_ion>
		XTAL_DEF_(return,inline,let)
		fuse(different_q<T_> auto &&o)
		noexcept -> signed
		requires bond::tab_compatible_q<T_, decltype(o)>
		{
			return S_::template fuse<N_ion>(XTAL_REF_(o).template apply<T_>());
		}

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
