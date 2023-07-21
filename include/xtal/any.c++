#pragma once
#include "./any.hpp"
#include "./process/anybody.hpp"
#include "./control/anybody.hpp"
#include "./control/restep.hpp"

#include <catch2/catch_all.hpp>

XTAL_ENV_(push)
namespace xtal::__test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

using namespace common;

using level_t = control::label_t<typename realized::alpha_t, struct T_level>;
using  bias_t = control::label_t<typename realized::alpha_t, struct T_bias >;
using  coef_t = control::label_t<typename realized::alpha_t, struct T_coef >;
using  wang_t = control::label_t<const typename realized::alpha_t, struct T_wang >;

template <wang_t wang_o>
XTAL_FN0 wanghus()
{
}

////////////////////////////////////////////////////////////////////////////////

struct mix
{
	class type: public process::confine_t<type>
	{
	public:

		XTAL_FN2 method(XTAL_DEF ...xs)
		XTAL_0FX
		{
			return (XTAL_REF_(xs) +...+ 0);
		}

	};
};
using mix_t = typename mix::type;


struct static_bias_mix
{
	class type: public process::confine_t<type, bias_t::template dispatch<(1<<7)>>
	{
	public:

		template <auto bias>
		XTAL_FN2 method(XTAL_DEF ...xs)
		XTAL_0FX
		{
			return (XTAL_REF_(xs) +...+ bias);
		}

	};
};
using static_bias_mix_t = typename static_bias_mix::type;


struct dynamic_bias_mix
{
	class type: public process::confine_t<type, bias_t::attach>
	{
	public:

		XTAL_FN2 method(XTAL_DEF ...xs)
		XTAL_0EX
		{
			return (XTAL_REF_(xs) +...+ this->template get<bias_t>());
		}

	};
};
using dynamic_bias_mix_t = typename dynamic_bias_mix::type;


struct dynamic_term
{
	class type: public process::confine_t<type, coef_t::attach>
	{
	public:

		XTAL_FN2 method(XTAL_DEF x)
		XTAL_0EX
		{
			return XTAL_REF_(x)*this->template get<coef_t>();
		}

	};
};
using dynamic_term_t = typename dynamic_term::type;


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

		XTAL_FN2 method()
		XTAL_0EX
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
