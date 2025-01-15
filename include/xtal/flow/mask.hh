#pragma once
#include "./any.hh"

#include "./mark.hh"




XTAL_ENV_(push)
namespace xtal::flow
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
Forwards anything prefixed with `N_mask`. \

template <extent_type N_mask=-1>
struct mask;


//////////////////////////////////////////////////////////////////////////////////

template <extent_type N_mask>
struct mask
{
	static constexpr extent_type M_mask =  N_mask;
	static constexpr extent_type W_mask = ~M_mask;
	
	template <_retail::any_q S>
	class subtype : public bond::compose_s<S>
	{
		using S_ = bond::compose_s<S>;
	
	public:
		using S_::S_;
		using S_::self;

		template <signed N_ion>
		XTAL_DEF_(short)
		XTAL_LET flux(auto &&...oo)
		noexcept -> signed
		{
			return S_::template flux<N_ion>(XTAL_REF_(oo)...);
		}
		template <signed N_ion>
		XTAL_DEF_(short)
		XTAL_LET flux(mark_q auto o, auto &&...oo)
		noexcept -> signed
		{
			return flux<N_ion>((mark_s<>) o.head(), o.tail(), XTAL_REF_(oo)...);
		}
		template <signed N_ion>
		XTAL_DEF_(short)
		XTAL_LET flux(mark_s<> o, auto &&...oo)
		noexcept -> signed
		{
			auto m = o.head();
			if (~m & M_mask) {
				return -1;
			}
			else if (m &= W_mask) {
				return S_::template flux<N_ion>(mark_s<>(m), XTAL_REF_(oo)...);
			}
			else {
				return S_::template flux<N_ion>(XTAL_REF_(oo)...);
			}
		}

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
