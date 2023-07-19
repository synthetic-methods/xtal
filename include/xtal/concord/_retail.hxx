#pragma once
#ifdef __INTELLISENSE__// stub...
#include "./any.hpp"
#endif





namespace _retail
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

namespace _detail {using namespace common::_detail;}


////////////////////////////////////////////////////////////////////////////////
///\
Creates a unique `subtype<S>` tagged by the given `As...`, \
such that e.g. `std::derives_from<any<struct x, struct xs...>, any<struct xs...>>`. \

template <typename ...As>
struct any
{
	using subkind = common::compose<any<As>...>;

	template <typename S>
	using subtype = typename subkind::template subtype<S>;

};
template <typename A>
struct any<A>
{
	template <typename S>
	class subtype: public S
	{
	public:
		using S::S;

	};
};


}//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
