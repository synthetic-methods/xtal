#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::flow
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
Provides conversion from `tab`-equivalent types when executing `-fuse`. \
Used to adapt internal `attach`ments like `resize`. \

///\todo\
Either define convenience `concept`s based on the `bond::tab` counterparts, \
or integrate into the base-`(?:fuse|flux)`. \

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

		template <signed N_ion>
		XTAL_DEF_(return,inline,let)
		fuse(auto &&o)
		noexcept -> signed
		{
			if constexpr (bond::tab_convertible_q<T_, decltype(o)>) {
				return S_::template fuse<N_ion>(XTAL_REF_(o).template apply<T_>());
			}
			else {
				return S_::template fuse<N_ion>(XTAL_REF_(o));
			}
		}

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
