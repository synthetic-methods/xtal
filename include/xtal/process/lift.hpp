#pragma once
#include "./any.hpp"






XTAL_ENV_(push)
namespace xtal::process
{///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///\
Produces a decorator incorporating `As...` that defines \
`method<>(...)` by `Y(...)`. \

template <typename Y, typename... As>
struct lift
{
	template <typename T>
	using subkind = confine<T, As...>;

	template <any_q S>
	class subtype: public compose_s<S, subkind<subtype<S>>>
	{
		using co = compose_s<S, subkind<subtype<S>>>;
	public:
		using co::co;

		template <auto...>
		XTAL_FN2 method(XTAL_DEF... xs)
		{
			return Y(XTAL_REF_(xs)...);
		}

	};
};

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
