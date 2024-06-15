#pragma once
#include "./any.cc"
#include "./tab.hh"// testing...

#include "./compose.hh"



XTAL_ENV_(push)
namespace xtal::bond::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

struct TagA
{
	template <class S>
	class subtype : public bond::compose_s<S, tab<TagA>>
	{
		using S_ = bond::compose_s<S, tab<TagA>>;

	public:
		using S_::S_;

	};
};
struct TagB
{
	template <class S>
	class subtype : public bond::compose_s<S, tab<TagB>>
	{
		using S_ = bond::compose_s<S, tab<TagB>>;

	public:
		using S_::S_;

	};
};
struct TagZ
{
	template <class S>
	class subtype : public bond::compose_s<S, tab<TagZ>>
	{
		using S_ = bond::compose_s<S, tab<TagZ>>;

	public:
		using S_::S_;

	};
};

using TagAB = bond::compose<TagA, TagB>;
using TypAB = typename TagAB::template subtype<unit_type>;


////////////////////////////////////////////////////////////////////////////////
/**/
TAG_("tab")
{
	TRY_("task")
	{
		TRUE_(any_tab_p<TagA, TypAB>);
		TRUE_(any_tab_p<TagB, TypAB>);
		UNTRUE_(any_tab_p<TagZ, TypAB>);

	}
}
/***/

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
