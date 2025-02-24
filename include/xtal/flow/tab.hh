#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::flow
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
Provides conversion from `tab`-equivalent types when executing `-fuse`. \

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
			return S_::template fuse<N_ion>(XTAL_REF_(o));
		}
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
