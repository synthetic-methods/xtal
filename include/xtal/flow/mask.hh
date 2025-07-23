#pragma once
#include "./any.hh"

#include "./mark.hh"




XTAL_ENV_(push)
namespace xtal::flow
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/*!
\brief  	Intercepts `mark`ed messages, forwarding only those matching `N_mask`.
\note    Both `mask` and `mark` comprise products of prime numbers,
         with sieving provided by modulo and division.
			This admits a broader range of elements than the current bit-depth,
			while limiting the available combinations as the elements increase.
*/
template <size_type N_mask=1>
struct mask;


//////////////////////////////////////////////////////////////////////////////////

template <size_type N_mask>
struct mask
{
	template <_retail::any_q S>
	class subtype : public bond::compose_s<S>
	{
		using S_ = bond::compose_s<S>;
	
	public:
		using S_::S_;
		using S_::self;

		template <signed N_ion>
		XTAL_DEF_(return,inline,let)
		flux(auto &&...oo)
		noexcept -> signed
		{
			return S_::template flux<N_ion>(XTAL_REF_(oo)...);
		}
		template <signed N_ion>
		XTAL_DEF_(return,inline,let)
		flux(mark_q auto o, auto &&...oo)
		noexcept -> signed
		{
			return flux<N_ion>((mark_s<>) o.head(), o.tail(), XTAL_REF_(oo)...);
		}
		template <signed N_ion>
		XTAL_DEF_(return,let)
		flux(mark_s<> o, auto &&...oo)
		noexcept -> signed
		{
			auto n_mark = o.head();
			if (n_mark%N_mask) {
				return -1;
			}
			n_mark /= N_mask;
			if (1 == n_mark) {
				return S_::template flux<N_ion>(XTAL_REF_(oo)...);
			}
			else {
				return S_::template flux<N_ion>(mark_s<>(n_mark), XTAL_REF_(oo)...);
			}
		}

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
