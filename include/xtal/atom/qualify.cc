#pragma once
#include "./any.cc"





#include "./qualify.hh"// testing...
XTAL_ENV_(push)
namespace xtal::atom::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

static_assert(same_q<       std::plus<int>      , bond::compose_s<      int      , qualify<std::plus>>>);
static_assert(same_q<       std::plus<int>   [4], bond::compose_s<      int   [4], qualify<std::plus>>>);
static_assert(same_q<       std::plus<int>(&)[4], bond::compose_s<      int(&)[4], qualify<std::plus>>>);
static_assert(same_q<const std::plus<int>   [4], bond::compose_s<const int   [4], qualify<std::plus>>>);
static_assert(same_q<const std::plus<int>(&)[4], bond::compose_s<const int(&)[4], qualify<std::plus>>>);

//atic_assert(same_q<std::type_identity<std::plus<int>>, bond::compose_s<std::type_identity<int>, qualify<std::plus>>>);


////////////////////////////////////////////////////////////////////////////////
/*/
TAG_("qualify")
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
