#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::bond
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <template <typename> typename T_>
struct isokind
{
	template <class S>
	class subtype : public T_<subtype<S>>::template subtype<S>
	{
		using S_ = typename T_<subtype<S>>::template subtype<S>;
	
	public:
		using S_::S_;

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)