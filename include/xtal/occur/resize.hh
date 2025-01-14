#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::occur
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class U=size_type> struct   resize;
template <class U=size_type> using    resize_t = confined_t<resize<U>>;
template <typename   ..._s> concept  resize_q = bond::tag_p<resize, _s...>;
XTAL_DEF_(short)
XTAL_LET resize_f(auto &&w)
noexcept -> auto
{
	using _op = bond::operate<decltype(w)>;
	return resize_t<typename _op::sigma_type>(XTAL_REF_(w));
}


//////////////////////////////////////////////////////////////////////////////////

template <class U>
struct resize
{
	using superkind = bond::compose<flux::tag<resize>, defer<U>>;

	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind>;
		using T_ = typename S_::self_type;
	
	public:// CONSTRUCT
		using S_::S_;

	public:// OPERATE
		using S_::self;
		using S_::head;

		using size_type = U;
		XTAL_TO4_(XTAL_DEF_(let) size(auto &&...oo), head(XTAL_REF_(oo)...))
		XTAL_TO4_(XTAL_DEF_(let) empty(), 0 == size())

	};
};
template <iterated_q U>
struct resize<U> : resize<counter_t<U>>
{
};

static_assert(bond::same_tabs_q<resize_t<unsigned>, resize_t<unsigned>>);
static_assert(bond::same_tabs_q<resize_t<unsigned>, resize_t<  signed>>);


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
