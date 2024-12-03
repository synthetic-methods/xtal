#pragma once
#include "./any.cc"
#include "./cache.hh"// testing...


XTAL_ENV_(push)
namespace xtal::arrange::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/**/
TAG_("cache")
{
	TRY_("allocation stepping") {
		size_type i{};
		TRUE_(_detail::maligned_f<_std::byte   >(i) == 0x0);
		TRUE_(_detail::maligned_f<_std::int16_t>(i) == 0x2);
		TRUE_(_detail::maligned_f<_std::byte   >(i) == 0x4);
		TRUE_(_detail::maligned_f<_std::byte   >(i) == 0x5);
		TRUE_(_detail::maligned_f<_std::int16_t>(i) == 0x6);
		TRUE_(_detail::maligned_f<_std::byte   >(i) == 0x8);
		TRUE_(_detail::maligned_f<_std::int16_t>(i) == 0xA);

	}
}
/***/

////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
