#pragma once
#include "./any.hpp"
#include "./process/any.hpp"
#include "./control/any.hpp"
#include "./control/restep.hpp"

#include <catch2/catch_all.hpp>

XTAL_ENV_(push)
namespace xtal::__test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

using namespace common;


////////////////////////////////////////////////////////////////////////////////

using bias_t = control::label_t<typename realized::alpha_t, struct T_bias>;
using coef_t = control::label_t<typename realized::alpha_t, struct T_coef>;

struct mix
{
	class type: public process::confine_t<type>
	{
		using S_ = process::confine_t<type>;

	public:
		using S_::S_;

		template <auto bias>
		XTAL_FN2 method(XTAL_DEF ...xs)
		{
			return (XTAL_REF_(xs) +...+ 0);
		}

	};
};
using mix_t = typename mix::type;

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
	using count_t  = typename realized::iota_t;
	using restep_u = control::restep_t<count_t>;

	template <typename T>
	using homotype = process::confine_t<T, restep_u::attach>;

	struct type: public homotype<type>
	{
		using co = homotype<type>;
	
	public:
		using co::co;

		template <auto...>
		XTAL_FN2 method()
		{
			auto i = count; count += this->template get<restep_u>();
			return i;
		}

	protected:
		count_t count = 0;

	};
};
using dynamic_count_t = typename dynamic_count::type;

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
