#pragma once
#include "./any.ipp"
#include "./group.ipp"





XTAL_ENV_(push)
namespace xtal::content
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <                typename ..._s> XTAL_NYM phase;
template <                typename ..._s> XTAL_ASK phase_q = tag_p<phase, _s...>;
template <class U=size_t, typename ...As> XTAL_USE phase_t = confined_t<phase<U>, As...>;


////////////////////////////////////////////////////////////////////////////////
///\
Represents a local `{store,serve}` pair, \
used as e.g. a buffer and its abstract/copyable `std::span`. \

template <class U>
struct phase<U>
{
	using _computer = compute<U>;
	using alpha_t = typename _computer::alpha_t;
	using subkind = compose<tag<phase>, group<alpha_t>>;

	template <class S>
	class subtype: public compose_s<S, subkind>
	{
		using S_ = compose_s<S, subkind>;

	public:
		using S_::S_;
		using S_::self;
		using S_::head;

		XTAL_FN1 normalize()
		XTAL_0EX
		{
			auto &o = head(); o -= _std::round(o);
			return S_::normalize();
		}
	
	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
