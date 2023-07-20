#pragma once
#include "./any.hpp"






XTAL_ENV_(push)
namespace xtal::common
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ...>
struct tag_ {};


////////////////////////////////////////////////////////////////////////////////

template <template <typename ...> typename F=tag_>
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
template <template <typename ...> typename F>
using tag_t = typename tag<F>::type;

template <template <typename ...> typename F, typename ...Ts>
concept tag_p = (...and _std::derived_from<based_t<Ts>, tag_t<F>>);

template <typename ...Ts>
concept tag_q = tag_p<tag_, Ts...>;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
