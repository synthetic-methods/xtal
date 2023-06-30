#pragma once
#include "./any.hpp"






XTAL_ENV_(push)
namespace xtal::context
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <typename U=_std::ptrdiff_t>
struct delay
{
	using value_type = U;
	using subkind = confer<value_type, only<delay>>;

	template <concord::any_q S>
	class subtype: public compose_s<S, subkind>
	{
		using S_ = compose_s<S, subkind>;

	public:
		using S_::S_;

		template <int N_switch=0> requires sign_q<N_switch>
		XTAL_FZ2 limit(XTAL_DEF... oo)
		{
			using L = _std::numeric_limits<U>;
			if constexpr (N_switch == -1) return subtype(L::min(), XTAL_REF_(oo)...);
			if constexpr (N_switch ==  0) return subtype(0,        XTAL_REF_(oo)...);
			if constexpr (N_switch == +1) return subtype(L::max(), XTAL_REF_(oo)...);
		}

	};
};
template <typename S=confined_t<>, typename U=_std::ptrdiff_t>
using delay_s = compose_s<S, delay<U>>;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
