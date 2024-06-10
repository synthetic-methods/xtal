#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::occur
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class U=size_t> XTAL_TYP resize;
template <class U=size_t> XTAL_USE resize_t = confined_t<resize<U>>;
template <typename ..._s> XTAL_ASK resize_q = bond::head_tag_p<resize, _s...>;
XTAL_DEF_(return,inline)
XTAL_LET resize_f(auto &&w)
XTAL_0EX
{
	using _op = bond::operate<decltype(w)>;
	return resize_t<typename _op::sigma_t>(XTAL_REF_(w));
}


//////////////////////////////////////////////////////////////////////////////////

template <class U>
struct resize
{
	using subkind = bond::compose<bond::tag<resize>, defer<U>>;

	template <any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;
	
	public:
		using S_::S_;
		using U_size = U;

		XTAL_TO4_(XTAL_DEF_(return,inline) XTAL_REF size(auto &&...oo), S_::head(XTAL_REF_(oo)...))
		XTAL_TO4_(XTAL_DEF_(return,inline) XTAL_REF empty(), 0 == size())

	};
};
template <iterated_q U>
struct resize<U> : resize<XTAL_TYP_(XTAL_ANY_(U).size())>
{
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
