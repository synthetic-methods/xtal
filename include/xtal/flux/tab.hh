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

		XTAL_DEF_(return,inline)
		XTAL_LET infuse(auto &&o)
		noexcept -> sign_type
		{
			if constexpr (bond::twin_tab_q<T_, decltype(o)>) {
				return S_::infuse(XTAL_REF_(o).apply(invoke_f<T_>));
			}
			else {
				return S_::infuse(XTAL_REF_(o));
			}
		}
		XTAL_DEF_(return,inline)
		XTAL_LET effuse(auto &&o)
		noexcept -> sign_type
		{
			if constexpr (bond::twin_tab_q<T_, decltype(o)>) {
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
