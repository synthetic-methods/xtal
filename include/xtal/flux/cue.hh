#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::flux
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
///\
Used for scheduling any type by prefixing with an integral delay. \

template <class	..._s> struct   cue;
template <class	..._s> concept  cue_q = bond::tag_p<cue, _s...>;
template <class	..._s> using    cue_s = bond::compose_s<flux::packet_t<_s...>, cell::confined<cue<>>>;


////////////////////////////////////////////////////////////////////////////////

template <>
struct cue<>
{
	using _op = bond::operating;

	using superkind = cell::confer<typename _op::iota_type, bond::tag<cue>>;

	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		using S_ = bond::compose_s<S, superkind>;

	public:
		using S_::S_;

		XTAL_TO4_(XTAL_DEF_(implicit operator) auto(), cue_s<>(S_::head()))

		using cue_type = XTAL_ALL_(XTAL_ANY_(S_).tail());
		using cue_size = constant_t<size_type{1}>;

	};
	template <cue_q S>
	class subtype<S> : public bond::compose_s<S, superkind>
	{
		using S_ = bond::compose_s<S, superkind>;

	public:
		using S_::S_;

	//	TODO: Limit to instances of `cue`, not just derived...
		using cue_size = superliminal_s<typename S_::cue_size>;
	};
};


////////////////////////////////////////////////////////////////////////////////
/**/
template <any_q T>
XTAL_DEF_(short)
XTAL_LET cue_f(XTAL_SYN_(cue_s<>) auto &&s, T &&t)
noexcept -> auto
{
	using Y = based_t<T>;
	using F =   cue_s<Y>;
	XTAL_IF0
	XTAL_0IF (             any_q<T>) {return F(XTAL_REF_(s),                          XTAL_REF_(t) );}
	XTAL_0IF (bond::heteropack_q<T>) {return F(XTAL_REF_(s), bond::repack_f<packed_t>(XTAL_REF_(t)));}
	XTAL_0IF_(else)                  {return F(XTAL_REF_(s),           conferred_t<Y>(XTAL_REF_(t)));}
	
}
template <any_q T> XTAL_DEF_(short) XTAL_LET operator << (cue_s<>       &&s, T &&t) noexcept -> decltype(auto) {return cue_f(XTAL_MOV_(s), XTAL_REF_(t));}
template <any_q T> XTAL_DEF_(short) XTAL_LET operator << (cue_s<> const  &s, T &&t) noexcept -> decltype(auto) {return cue_f(XTAL_REF_(s), XTAL_REF_(t));}

/***/
///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
