#pragma once
#include "./any.hh"

#include "./mark.hh"




XTAL_ENV_(push)
namespace xtal::flux
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
Forwards anything prefixed with `N_mask`. \

template <int N_mask=-1>
struct mask;


//////////////////////////////////////////////////////////////////////////////////

template <int N_mask>
struct mask
{
	static constexpr size_type M_mask =  N_mask;
	static constexpr size_type W_mask = ~M_mask;
	
	template <_retail::any_q S>
	class subtype : public bond::compose_s<S>
	{
		using S_ = bond::compose_s<S>;
	
	public:
		using S_::S_;
		using S_::self;
	//	using S_::influx;

		XTAL_DEF_(short)
		XTAL_LET influx(auto &&...oo)
		noexcept -> signed
		{
			return S_::influx(XTAL_REF_(oo)...);
		}
		XTAL_DEF_(short)
		XTAL_LET influx(mark_q auto o, auto &&...oo)
		noexcept -> signed
		{
			return influx((mark_s<>) o.head(), o.tail(), XTAL_REF_(oo)...);
		}
		XTAL_DEF_(long)
		XTAL_LET influx(mark_s<> o, auto &&...oo)
		noexcept -> signed
		{
			auto m = o.head();
			if (~m & M_mask) {
				return -1;
			}
			else if (m &= W_mask) {
				return S_::influx(mark_s<>(m), XTAL_REF_(oo)...);
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
