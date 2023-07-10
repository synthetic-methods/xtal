#pragma once
#include "./any.hpp"






XTAL_ENV_(push)
namespace xtal::context
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <typename ...>
struct grain;

template <typename U>
struct grain<U>
{
	using subkind = compose<defer<U>, _detail::refer_comparators<U>, tag<grain>>;
	
	template <typename S>
	class subtype: public compose_s<S, subkind>
	{
		using S_ = compose_s<S, subkind>;
		
	public:
		using S_::S_;
		using S_::head;
		
		XTAL_TO4_(XTAL_OP0 U(), head())

	};
};
template <typename ...Ts >
concept grain_q = tag_q<grain, Ts...>;

template <typename S=confined_t<>, typename U=_std::ptrdiff_t>
using grain_s = compose_s<S, confined<grain<U>>>;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
