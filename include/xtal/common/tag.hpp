#pragma once
#include "./any.hpp"






XTAL_ENV_(push)
namespace xtal::common
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <template <typename...> typename F>
struct tag
{
	class type
	{};
	template <typename S>
	class subtype: public type, public S
	{
	public:
		using S::S;
		
	};
};
template <template <typename...> typename F>
using tag_t = typename tag<F>::type;

template <template <typename...> typename F, typename T>
concept tag_p = _std::derived_from<based_t<T>, tag_t<F>>;

template <template <typename...> typename F, typename ...Ts>
concept tag_q = (... and tag_p<F, Ts>);


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
