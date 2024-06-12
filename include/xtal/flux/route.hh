#pragma once
#include "./any.hh"

#include "../cell/mark.hh"




XTAL_ENV_(push)
namespace xtal::flux
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
Forwards anything prefixed with `N_mask`. \

template <int N_mask=-1>
struct route;


//////////////////////////////////////////////////////////////////////////////////

template <int N_mask>
struct route
{
	using U_mark = cell::mark_s<>;

	static constexpr size_t M_mask =  N_mask;
	static constexpr size_t W_mask = ~M_mask;
	
	template <_retail::any_q S>
	class subtype : public bond::compose_s<S>
	{
		using S_ = bond::compose_s<S>;
	
	public:
		using S_::S_;
		using S_::self;
	//	using S_::influx;

		XTAL_TNX influx(auto &&...oo)
		XTAL_0EX
		{
			return S_::influx(XTAL_REF_(oo)...);
		}
		XTAL_TNX influx(cell::mark_q auto o, auto &&...oo)
		XTAL_0EX
		{
			return influx(U_mark(o), o.then(), XTAL_REF_(oo)...);
		}
		XTAL_TNX influx(U_mark o, auto &&...oo)
		XTAL_0EX
		{
			auto m = o.head();
			if (~m & M_mask) {
				return -1;
			}
			else if (m &= W_mask) {
				return S_::influx(U_mark(m), XTAL_REF_(oo)...);
			}
			else {
				return S_::influx(           XTAL_REF_(oo)...);
			}
		}

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
