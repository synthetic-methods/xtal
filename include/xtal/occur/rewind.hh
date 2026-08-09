#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::occur
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class ..._s> struct   rewind;
template <class ..._s> using    rewind_t =        confined_t<rewind< _s...>>;
template <class ..._s> concept  rewind_q = bond::tag_inner_p<rewind, _s...> ;


//////////////////////////////////////////////////////////////////////////////////

template <class U>
struct rewind<U>
{
	using superkind = bond::compose<flow::tag<rewind>, defer<U>>;

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

		using wind_type = U;

		XTAL_FN1_(go) (XTAL_VAL_(return,inline,get) wind, [] (auto &&o, auto &&...oo)
		XTAL_0FN_(to) (XTAL_REF_(o).head(XTAL_REF_(oo)...)))

	};
};


////////////////////////////////////////////////////////////////////////////////

template <> struct rewind<void> : rewind<signed> {};
template <> struct rewind<    > : rewind<signed> {};

XTAL_VAL_(let) rewind_f = [] XTAL_1FN_(call) (rewind_t<>);


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
