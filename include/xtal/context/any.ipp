#pragma once
#include "./any.hpp"






XTAL_ENV_(push)
namespace xtal::context
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <class T>
struct define
:	_retail::define<T>
{
};
template <class T>
struct refine
:  _retail::refine<T>
{
};


////////////////////////////////////////////////////////////////////////////////

template <class U>
struct defer
:  _retail::defer<U>
{
};
template <field_q U>
struct defer<U>
{
	using subkind = _retail::defer<U>;

	template <class S>
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
		XTAL_REQ equality_q<U> and sign_p<N_polarity>
		{
			using L = _std::numeric_limits<U>;
			if constexpr (N_polarity == +1) return T_(L::max(), XTAL_REF_(oo)...);
			if constexpr (N_polarity ==  0) return T_(0,        XTAL_REF_(oo)...);
			if constexpr (N_polarity == -1) return T_(L::min(), XTAL_REF_(oo)...);
		}

	};
};
template <class U>
struct refer
:  _retail::refer<U>
{
};
template <field_q U>
struct refer<U>: compose<void
,	_detail::refer_quality<U>
>
{
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
