#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::occur
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ..._s> XTAL_TYP review;
template <typename ..._s> XTAL_ASK review_q = bond::tag_p<review, _s...>;
template <iterable_q  U > XTAL_USE review_t = confined_t<review<U>, bond::tag<review>>;
template <iterable_q  U > XTAL_FN2 review_f(U &&u) XTAL_0EX {return review_t<U>(XTAL_REF_(u));};

template <class U>
struct review<U>
{
	using subkind = confer<U>;

	template <any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;
	
	public:
		using S_::S_;
		using S_::self;
		using S_::twin;
		using S_::head;
		
		XTAL_TO4_(XTAL_TN2 view(auto &&...oo), S_::head(XTAL_REF_(oo)...))

		XTAL_DO2_(XTAL_TN2 slice(counted_q auto &&w),
		{
			distance_t<U> const i = w.front(), j = w.back() + 1;
			
			if constexpr (accessed_q<U>) {
				using _xtd::ranges::next;
			
				auto _o = point_f(view());
				auto _i = next(_o, i);
				auto _j = next(_o, j);
				return review_f(reiterated_t<U>(_i, _j));
			}
			else {
				using _xtd::ranges::views::slice;

				//\
				return review_f(view()|discount_f(i)|account_f(j - i));
				return review_f(view()|slice(i, j));
			}
		})

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
