#pragma once
#include "../any.hpp"






XTAL_ENV_(push)
namespace xtal::common
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ...> struct compose;
template <typename    > struct realize;


////////////////////////////////////////////////////////////////////////////////
///\
Creates a unique `subtype<S>` tagged by the given `As...`, \
such that e.g. `std::derives_from<any<struct x, struct xs...>, any<struct xs...>>`. \

template <typename ...As>
struct any
{
	using subkind = compose<any<As>...>;

	template <class S>
	using subtype = typename subkind::template subtype<S>;

};
template <typename A>
struct any<A>
{
	template <class S>
	class subtype: public S
	{
	public:
		using S::S;

	protected:
		template <typename Y, class X, constant_q W> struct super         : S::template super<Y, X, W> {};
		template <            class X, constant_q W> struct super<A, X, W>: S::template super<X, X, W> {};

	};
};


////////////////////////////////////////////////////////////////////////////////

#include "./_detail.hxx"


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
