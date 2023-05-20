#pragma once
#include "./any.hpp"
#include "./process/any.hpp"
#include "./message/numinal.hpp"


#include <catch2/catch_all.hpp>

XTAL_ENV_(push)
namespace xtal
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

using bias_t = message::numinal_t<alpha_t, struct bias>;

struct static_bias_mix_t
:	process::confine_t<static_bias_mix_t
	,	bias_t::template dispatch<(1 << 7)>
	>
{
	template <auto bias>
	XTAL_FN2 method(XTAL_DEF... xs)
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
	XTAL_FN2 method(XTAL_DEF... xs)
	{
		return (XTAL_REF_(xs) + ... + this->template get<bias_t>());
	}
};

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
