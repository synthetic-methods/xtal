#pragma once
#include "./any.hh"

#include "./map.hh"




XTAL_ENV_(push)
namespace xtal::process
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

namespace _detail
{///////////////////////////////////////////////////////////////////////////////

template <auto F>
XTAL_TYP operate
{
	class type
	{
	public:
		XTAL_OP1() (auto &&...oo)
		{
			return F(XTAL_REF_(oo)...);
		}

	};
};
template <auto F>
XTAL_USE operate_t = typename operate<F>::type;


}///////////////////////////////////////////////////////////////////////////////

template <auto F, typename ..._s> XTAL_TYP mop   : map<_detail::operate_t<F>> {};
template <auto F, typename ..._s> XTAL_USE mop_t = confined_t<mop<F, _s...>>;
template <        typename ..._s> XTAL_ASK mop_q = map_q<_s...>;


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
