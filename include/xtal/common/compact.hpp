#pragma once
#include "../any.hpp"






XTAL_ENV_(push)
namespace xtal::common
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <template <typename> typename T_>
struct compact
{
	class type: public T_<type>
	{
		using co = T_<type>;
	public:
		using co::co;

	};

};
template <template <typename> typename T_>
using compact_t = typename compact<T_>::type;

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
