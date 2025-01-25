#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::flow
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
Governs access to the `supertype`. \

///\see `flow::mask`. \

template <class	..._s> struct   mark;
template <class	..._s> concept  mark_q = bond::tag_p<mark, _s...>;
template <class	..._s> using    mark_s = bond::compose_s<flow::packet_t<_s...>, cell::confined<mark<>>>;


////////////////////////////////////////////////////////////////////////////////

template <>
struct mark<>
{
	using superkind = cell::confer<extent_type, bond::tag<mark>>;

	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		using S_ = bond::compose_s<S, superkind>;

	public:
		using S_::S_;

		XTAL_FX4_(alias) (XTAL_DEF_(return,inline,implicit operator) auto(), mark_s<>(S_::head()))
		
		using marked_type = XTAL_ALL_(XTAL_ANY_(S_).tail())[1];

	};
	template <mark_q S>
	class subtype<S> : public bond::compose_s<S, superkind>
	{
		using S_ = bond::compose_s<S, superkind>;

	public:
		using S_::S_;

		using marked_type = superliminal_t<typename S_::marked_type>;

	};
};


////////////////////////////////////////////////////////////////////////////////
/**/
template <any_q T>
XTAL_DEF_(return,inline,let)
mark_f(same_q<mark_s<>> auto &&s, T &&t)
noexcept -> auto
{
	using Y = based_t<T>;
	using F =   mark_s<Y>;
	XTAL_IF0
	XTAL_0IF (             any_q<T>) {return F(XTAL_REF_(s),                          XTAL_REF_(t) );}
	XTAL_0IF (bond::heteropack_q<T>) {return F(XTAL_REF_(s), bond::repack_f<packed_t>(XTAL_REF_(t)));}
	XTAL_0IF_(else)                  {return F(XTAL_REF_(s),           conferred_t<Y>(XTAL_REF_(t)));}
	
}
template <any_q T> XTAL_DEF_(return,inline,let) operator << (mark_s<>       &&s, T &&t) noexcept -> decltype(auto) {return mark_f(XTAL_MOV_(s), XTAL_REF_(t));}
template <any_q T> XTAL_DEF_(return,inline,let) operator << (mark_s<> const  &s, T &&t) noexcept -> decltype(auto) {return mark_f(XTAL_REF_(s), XTAL_REF_(t));}

/***/
///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
