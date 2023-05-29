#pragma once
#include "./any.hpp"
#include "./process/any.hpp"
#include "./message/numinal.hpp"
#include "./message/restep.hpp"

#include <catch2/catch_all.hpp>

XTAL_ENV_(push)
namespace xtal
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

using bias_t = message::numinal_t<alpha_t, struct bias>;
using coefficient_t = message::numinal_t<alpha_t, struct coefficient>;

struct static_bias_mix_t
:	process::confine_t<static_bias_mix_t
	,	bias_t::template dispatch<(1 << 7)>
	>
{
	template <auto bias>
	XTAL_FN2 method(XTAL_DEF ...xs)
	{
		return (XTAL_REF_(xs) + ... + bias);
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
		return (XTAL_REF_(xs) + ... + this->template get<bias_t>());
	}
};
struct dynamic_term_t
:	process::confine_t<dynamic_term_t
	,	coefficient_t::attach
	>
{
	template <auto...>
	XTAL_FN2 method(XTAL_DEF x)
	{
		return XTAL_REF_(x)*this->template get<coefficient_t>();
	}
};
struct dynamic_count
{
	using restep_u = message::restep_t<iota_t>;

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
			iota_t o = count; count += this->template get<restep_u>();
			return o;
		}

	};
};
using dynamic_count_t = boxed_t<dynamic_count>;

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
