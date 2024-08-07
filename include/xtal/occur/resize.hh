#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::occur
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class U=size_type> XTAL_TYP resize;
template <class U=size_type> XTAL_USE resize_t = confined_t<resize<U>>;
template <typename ..._s> XTAL_REQ resize_q = bond::any_tag_p<resize, _s...>;
XTAL_DEF_(return,inline)
XTAL_LET resize_f(auto &&w)
XTAL_0EX
{
	using _op = bond::operate<decltype(w)>;
	return resize_t<typename _op::sigma_type>(XTAL_REF_(w));
}


//////////////////////////////////////////////////////////////////////////////////

template <class U>
struct resize
{
	using subkind = bond::compose<flux::tag<resize>, defer<U>>;

	template <any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;
		using T_ = typename S_::self_type;
	
	public:// CONSTRUCT
		using S_::S_;

	public:// OPERATE
		using S_::self;
		using S_::head;

		using size_type = U;
		XTAL_TO4_(XTAL_DEF_(return,inline) XTAL_RET size(auto &&...oo), head(XTAL_REF_(oo)...))
		XTAL_TO4_(XTAL_DEF_(return,inline) XTAL_RET empty(), 0 == size())

	};
};
template <iterated_q U>
struct resize<U> : resize<count_t<U>>
{
};

static_assert(not bond::twin_tab_q<resize_t<size_type>, resize_t<size_type>>);
static_assert(    bond::twin_tab_q<resize_t<size_type>, resize_t<int   >>);
static_assert(    bond::self_tab_q<resize_t<size_type>, resize_t<size_type>>);


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
