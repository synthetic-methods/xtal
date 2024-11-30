#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::flux
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
Governs access to the `supertype`. \

///\see `flux::mask`. \

template <class	..._s> XTAL_TYP mark;
template <class	..._s> XTAL_REQ mark_q = bond::any_tag_p<mark, _s...>;
template <class	..._s> XTAL_USE mark_s = bond::compose_s<flux::packet_t<_s...>, compound::confined<mark<>>>;


////////////////////////////////////////////////////////////////////////////////

template <>
struct mark<>
{
	using _op = bond::operating;

	using superkind = compound::confer<typename _op::sigma_type, bond::tag<mark>>;

	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		using S_ = bond::compose_s<S, superkind>;

	public:
		using S_::S_;

		XTAL_TO4_(XTAL_DEF_(return,inline) XTAL_CVN_(implicit) auto(), mark_s<>(S_::head()))
		
		using mark_type = XTAL_ALL_(XTAL_ANY_(S_).tail());
		using mark_size = nominal_t<size_1>;

	};
	template <mark_q S>
	class subtype<S> : public bond::compose_s<S, superkind>
	{
		using S_ = bond::compose_s<S, superkind>;

	public:
		using S_::S_;

		using mark_size = superliminal_s<typename S_::mark_size>;

	};
};


////////////////////////////////////////////////////////////////////////////////
/**/
template <any_q T>
XTAL_DEF_(return,inline)
XTAL_LET mark_f(XTAL_ARG_(mark_s<>) &&s, T &&t)
XTAL_0EX
{
	using Y = based_t<T>;
	using F =   mark_s<Y>;
	XTAL_IF0
	XTAL_0IF (             any_q<T>) {return F(XTAL_REF_(s),                            XTAL_REF_(t) );}
	XTAL_0IF (bond::heteropack_q<T>) {return F(XTAL_REF_(s), bond::repack_f<packed_t>(XTAL_REF_(t)));}
	XTAL_0IF_(else)                  {return F(XTAL_REF_(s),             conferred_t<Y>(XTAL_REF_(t)));}
	
}
template <any_q T> XTAL_DEF_(return,inline) XTAL_LET operator << (mark_s<>       &&s, T &&t) XTAL_0EX -> decltype(auto) {return mark_f(XTAL_MOV_(s), XTAL_REF_(t));}
template <any_q T> XTAL_DEF_(return,inline) XTAL_LET operator << (mark_s<> const  &s, T &&t) XTAL_0EX -> decltype(auto) {return mark_f(XTAL_REF_(s), XTAL_REF_(t));}

/***/
///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
