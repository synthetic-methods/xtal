#pragma once
#include "./any.hpp"
#include "./process/any.hpp"
#include "./control/numinal.hpp"
#include "./control/restep.hpp"

#include <catch2/catch_all.hpp>

XTAL_ENV_(push)
namespace xtal
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

using bias_t = control::numinal_t<alpha_t, struct bias>;
using coef_t = control::numinal_t<alpha_t, struct coefficient>;

struct static_bias_mix_t
:	process::confine_t<static_bias_mix_t
	,	bias_t::template dispatch<(1 << 7)>
	>
{
	template <auto bias>
	XTAL_FN2 method(XTAL_DEF ...xs)
	{
		return (XTAL_REF_(xs) +...+ bias);
	}
};
struct dynamic_bias_mix_t
:	process::confine_t<dynamic_bias_mix_t
	,	bias_t::attach
	>
{
	template <auto...>
	XTAL_FN2 method(XTAL_DEF ...xs)
	{
		auto &o = this->template self<bias_t>();
		return (XTAL_REF_(xs) +...+ o.head());
	}
};
struct dynamic_term_t
:	process::confine_t<dynamic_term_t
	,	coef_t::attach
	>
{
	template <auto...>
	XTAL_FN2 method(XTAL_DEF x)
	{
		auto &o = this->template self<coef_t>();
		return XTAL_REF_(x)*o.head();
	}
};
struct dynamic_count
{
	using restep_u = control::restep_t<iota_t>;

	template <typename T>
	using homotype = process::confine_t<T
	,	restep_u::attach
	>;

	struct type: public homotype<type>
	{
		iota_t count = 0;

		using co = homotype<type>;
	public:
		using co::co;

		template <auto...>
		XTAL_FN2 method()
		{
			auto  &o = this->template self<restep_u>();
			iota_t i = count; count += o.head();
			return i;
		}

	};
};
using dynamic_count_t = typename dynamic_count::type;

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
