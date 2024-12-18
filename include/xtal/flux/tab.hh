#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::flux
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
Provides conversion from `tab`-equivalent types when executing `-fuse`.

///\note\
Does not currently apply to `-flux`. \

///\note\
Used to adapt internal `attach`ments like `resize`. \

template <typename ..._s>
struct tab;


//////////////////////////////////////////////////////////////////////////////////

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

		template <class O>
		XTAL_DEF_(short)
		XTAL_LET infuse(O &&o)
		noexcept -> signed
		{
			if constexpr (bond::same_tabs_q<T_, O> and not same_q<T_, O>) {
				return S_::infuse(XTAL_REF_(o).apply(invoke_f<T_>));
			}
			else {
				return S_::infuse(XTAL_REF_(o));
			}
		}
		template <class O>
		XTAL_DEF_(short)
		XTAL_LET effuse(O &&o)
		noexcept -> signed
		{
			if constexpr (bond::same_tabs_q<T_, O> and not same_q<T_, O>) {
				return S_::effuse(XTAL_REF_(o).apply(invoke_f<T_>));
			}
			else {
				return S_::effuse(XTAL_REF_(o));
			}
		}

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
