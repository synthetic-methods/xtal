#pragma once
#include "./any.cc"
#include "./sample.hh"// testing...





XTAL_ENV_(push)
namespace xtal::occur::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

TAG_("sample")
{
	TRY_("construction")
	{
		using Op = bond::operating;

		using T_sigma = typename Op::sigma_t;
		using T_alpha = typename Op::alpha_t;

		auto constexpr b = (T_sigma) Op::diplo_f(16);
		auto constexpr p = (T_alpha) Op::haplo_f(16);

		auto d = sample_t<>{b};
		auto q = sample_t<>{p};

		TRUE_(b == d.rate());
		TRUE_(b == q.rate());

		TRUE_(p == d.period());
		TRUE_(p == q.period());

	}
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
