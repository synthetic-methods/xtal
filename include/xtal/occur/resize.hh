#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::occur
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class U=void> struct        resize;
template <class U=void> using         resize_t =          confined_t<resize<U>>;
template <class  ..._s> concept       resize_q = un_n<0, bond::tag_p<resize, _s>...>;
template <class  ..._s> concept  some_resize_q = in_n<1, bond::tag_p<resize, _s>...>;

XTAL_DEF_(let)   resize_f(auto &&w)
noexcept {return resize_t<>(XTAL_REF_(w));}


//////////////////////////////////////////////////////////////////////////////////

template <class U>
struct resize
{
	using superkind = bond::compose<flow::tag<resize>, defer<U>>;

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
template <>
struct resize<void>
:	resize<size_type>
{
};

static_assert(bond::   tab_compatible_q<resize_t<unsigned>, resize_t<unsigned>>);
static_assert(bond::tab_constructible_q<resize_t<unsigned>, resize_t<  signed>>);


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
