#pragma once
#include "./any.hpp"






XTAL_ENV_(push)
namespace xtal::control
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <counted_q U=counted_t<>>
struct rescan
{
	using subkind = defer<U>;

	template <any_p S>
	class subtype: public compose_s<S, subkind>
	{
		using S_ = compose_s<S, subkind>;
	
	public:
		using S_::S_;
		using scan_t = U;
			
		XTAL_TO4_(XTAL_FN1 scan(XTAL_DEF... oo), S_::head(XTAL_REF_(oo)...))

	};
};
template <counted_q U=counted_t<>>
using rescan_t = confined_t<rescan<U>>;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
