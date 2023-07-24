#pragma once
#include "./any.hpp"






XTAL_ENV_(push)
namespace xtal::common
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <template <typename ...> class _T=_detail::exotype>
struct tag
{
	class type
	{
	};
	template <class S>
	class subtype: public type, public S
	{
	public:
		using S::S;
		
	};
	template <of_q<type> S>
	class subtype<S>: public S
	{
	public:
		using S::S;
		
	};
};
template <template <typename ...> class _T>
using tag_t = typename tag<_T>::type;

template <template <typename ...> class _T, class ...Ts>
concept tag_p = of_p<tag_t<_T>, Ts...>;

template <class ...Ts>
concept tag_q = tag_p<_detail::exotype, Ts...>;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
