#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::occur
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class ..._s> struct   resize;
template <class ..._s> using    resize_t =  confined_t<resize< _s...>>;
template <class ..._s> concept  resize_q = bond::tag_in_p<resize, _s...> ;


//////////////////////////////////////////////////////////////////////////////////

template <class U>
struct resize<U>
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

		XTAL_FX4_(to) (XTAL_DEF_(return,inline,get)
		size (auto &&...oo), head(XTAL_REF_(oo)...))

		XTAL_FX4_(to) (XTAL_DEF_(return,inline,get)
		empty(), 0 == size())

	};
};
template <iterated_q U>
struct resize<U> : resize<counter_t<U>>
{
};


////////////////////////////////////////////////////////////////////////////////

template <> struct resize<void> : resize<size_type> {};
template <> struct resize<    > : resize<size_type> {};

XTAL_DEF_(let) resize_f = [] XTAL_1FN_(call) (resize_t<>);


////////////////////////////////////////////////////////////////////////////////

static_assert(bond::tab_compatible_q<resize_t<unsigned>, resize_t<unsigned>>);
static_assert(bond::tab_compatible_q<resize_t<unsigned>, resize_t<  signed>>);


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
