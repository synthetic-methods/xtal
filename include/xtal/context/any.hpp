#pragma once
#include "../concord/any.hpp"// `_retail`






XTAL_ENV_(push)
namespace xtal::context
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

namespace _retail = xtal::concord;
#include "../concord/any.hxx"


////////////////////////////////////////////////////////////////////////////////

template <typename T>
struct define
{
	using subkind = _retail::define<T>;

	template <typename S>
	class subtype: public compose_s<S, subkind>
	{
		using S_ = compose_s<S, subkind>;

	public:
		using S_::S_;

	};
};
template <typename T>
struct refine
:  _retail::refine<T>
{
};


////////////////////////////////////////////////////////////////////////////////

template <typename U>
struct defer
{
	using subkind = _retail::defer<U>;

	template <typename S>
	class subtype: public compose_s<S, subkind>
	{
		using S_ = compose_s<S, subkind>;
		using T_ = typename S_::self_t;

	public:
		using S_::S_;

		using value_type = U;

		///\returns the `sentinel` boundary in the direction of `N_polarity`. \

		template <int N_polarity=0>
		XTAL_CN2 sentry(XTAL_DEF... oo)
		XTAL_0EX
		XTAL_REQ comparators_p<U> and sign_q<N_polarity>
		{
			using L = _std::numeric_limits<U>;
			if constexpr (N_polarity == +1) return T_(L::max(), XTAL_REF_(oo)...);
			if constexpr (N_polarity ==  0) return T_(0,        XTAL_REF_(oo)...);
			if constexpr (N_polarity == -1) return T_(L::min(), XTAL_REF_(oo)...);
		}

	};
};
template <typename U>
struct refer
:  _retail::refer<U>
{
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
