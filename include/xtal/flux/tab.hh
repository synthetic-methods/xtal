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
	using subkind = bond::compose<bond::tab<_s>...>;

	template <any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;
		using T_ = typename S_::T_self;
	
	public:// CONSTRUCT
		using S_::S_;

	public:// FUSE

		XTAL_TNX infuse(auto &&o)
		XTAL_0EX
		{
			if constexpr (bond::twin_tab_q<T_, decltype(o)>) {
				return S_::infuse(XTAL_REF_(o).apply(invoke_f<T_>));
			}
			else {
				return S_::infuse(XTAL_REF_(o));
			}
		}
		XTAL_TNX effuse(auto &&o)
		XTAL_0EX
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
