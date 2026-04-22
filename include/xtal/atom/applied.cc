#pragma once
#include "./any.cc"





#include "./applied.hh"// testing...
XTAL_ENV_(push)
namespace xtal::atom::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

static_assert(same_q<      _std::plus<int>      , bond::compose_s<      int      , applied<_std::plus>>>);
static_assert(same_q<      _std::plus<int>   [4], bond::compose_s<      int   [4], applied<_std::plus>>>);
static_assert(same_q<      _std::plus<int>(&)[4], bond::compose_s<      int(&)[4], applied<_std::plus>>>);
static_assert(same_q<const _std::plus<int>   [4], bond::compose_s<const int   [4], applied<_std::plus>>>);
static_assert(same_q<const _std::plus<int>(&)[4], bond::compose_s<const int(&)[4], applied<_std::plus>>>);

//atic_assert(same_q<_std::type_identity<_std::plus<int>>, bond::compose_s<_std::type_identity<int>, applied<_std::plus>>>);


////////////////////////////////////////////////////////////////////////////////
/*/
TAG_("applied")
{
	TRY_("task")
	{
		TRUE_(true);

	}
}
/***/

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
