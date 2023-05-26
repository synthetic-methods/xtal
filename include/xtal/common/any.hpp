#pragma once
#include "../any.hpp"
#include "./buffer.hpp"
#include "./bundle.hpp"
#include "./compose.hpp"



XTAL_ENV_(push)
namespace xtal::common
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

namespace _detail
{
////////////////////////////////////////////////////////////////////////////////
///\
Creates a unique `subtype<S>` identified by the given `As...`, \
e.g. `any<struct thing>`. \

template <typename ...As>
struct any
{
	using subkind = compose<any<As>...>;

	template <typename S>
	using subtype = typename subkind::template subtype<S>;

};
template <typename A>
struct any<A>
{
	template <typename S>
	class subtype: public S
	{
		using co = S;
	public:
		using co::co;

	};
};

}
#include "./any.hxx"

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
