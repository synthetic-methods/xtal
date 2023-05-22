#pragma once
#include "./any.hpp"






XTAL_ENV_(push)
namespace xtal::process
{///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///\
Produces a decorator incorporating `As...` that defines \
`method<auto...>(...)` by `Y<auto...>(...)`. \

template <template <auto...> typename Y, typename ...As>
struct nift
{
	template <typename T>
	using homotype = confine<T, As...>;

	template <any_q S>
	class subtype: public compose_s<S, homotype<subtype<S>>>
	{
		using co = compose_s<S, homotype<subtype<S>>>;
	public:
		using co::co;

		template <auto ...Ms>
		XTAL_FN2 method(XTAL_DEF ...xs)
		{
			return Y<Ms...>(XTAL_REF_(xs)...);
		}

	};
};

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
