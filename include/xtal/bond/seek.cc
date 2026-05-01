#pragma once
#include "./any.cc"
#include "./seek.hh"// testing...





XTAL_ENV_(push)
namespace xtal::bond::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

static_assert(seek_is_q<seek_to_t<0>>);
static_assert(seek_is_q<seek_to_t<1>>);

static_assert(seek_truth_v<                   > == -1);
static_assert(seek_truth_v<               true> ==  0);
static_assert(seek_truth_v<       false,  true> ==  1);
static_assert(seek_truth_v<false, false,  true> ==  2);
static_assert(seek_truth_v<false, false, false> == -1);


////////////////////////////////////////////////////////////////////////////////
/**/
TAG_("seek")
{
	TRY_("seek_value_t<...>::size()")
	{
		TRUE_(1 == seek_value_t<0         >{}.size());
		TRUE_(2 == seek_value_t<0, 1      >{}.size());
		TRUE_(4 == seek_value_t<0, 1, 2   >{}.size());
		TRUE_(4 == seek_value_t<0, 1, 2, 3>{}.size());

	}
	TRY_("seek_index_t<...>::size()")
	{
		TRUE_(1 == seek_index_t<0         >{}.size());
		TRUE_(2 == seek_index_t<0, 1      >{}.size());
		TRUE_(4 == seek_index_t<0, 1, 2   >{}.size());
		TRUE_(4 == seek_index_t<0, 1, 2, 3>{}.size());

	}
	TRY_("seek_index_t<...>::operator[]")
	{
		static_assert(same_q<seek_to_t<4>, seek_in_t<0, 1, 2, 3>>);

		TRUE_(seek_index_t<0, 1,-1>{}[ 0] == 0);
		TRUE_(seek_index_t<0, 1,-1>{}[ 1] == 1);
		TRUE_(seek_index_t<0, 1,-1>{}[-1] == 2);

	}
}
/***/

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
