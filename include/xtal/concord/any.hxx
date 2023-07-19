#ifdef __INTELLISENSE__// stub...
#include "../any.hpp"
using namespace xtal;
namespace _retail
{
template <typename ...As>
struct any
{
	template <typename S>
	class subtype
	{};
};
}
#endif


//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
///\
Tags `subtype` with this namespace and the supplied types. \

template <typename ...As> struct any   : _retail::any<As..., any<>> {};
template <typename ...As> using  any_t = common::compose_s<unit_t, any<As...>>;
///\
Matches any `T` that inherits from `any_t<As...>`. \

template <typename T, typename ...As>
concept any_p = _std::derived_from<based_t<T>, any_t<As...>>;

template <typename ...Ts>
concept any_q = (... and any_p<Ts>);

template <typename ...Ts>
concept not_any_q = not (... or any_p<Ts>);


///////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
