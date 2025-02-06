#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::flow
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
///\
Used for scheduling any type by prefixing with an integral delay. \
May be stacked in order to described integral fades. \

/**/
template <class ..._s> struct  direction;
template <class ..._s> concept direction_q = bond::tag_p<direction, _s...>;
template <class ..._s> using   direction_s = bond::compose_s<packet_t<_s...>, cell::confined<direction<>>>;
/*/
template <class ..._s> struct  direction;
template <class ..._s> using   direction_s =  bond::compose_s<packet_t<_s...>, cell::confined<direction<>>>;
template <class T    > using   direction_u =  valued_u<typename T::direction_signature>;
template <class ..._s> concept direction_q = (bond::tag_p<direction, _s...> and...and same_q<_s, direction_s<direction_u<_s>>>);
/***/

////////////////////////////////////////////////////////////////////////////////

template <>
struct direction<>
{
	using superkind = cell::confer<signed, bond::tag<direction>>;

	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		using S_ = bond::compose_s<S, superkind>;

	public:
		using S_::S_;

		XTAL_FX4_(to) (XTAL_DEF_(return,inline,implicit operator)
		auto(), direction_s<>(S_::head()))

		using direction_signature = XTAL_ALL_(XTAL_ANY_(S).tail())[1];

	};
	template <bond::tag_q<direction> S>
	class subtype<S> : public bond::compose_s<S, superkind>
	{
		using S_ = bond::compose_s<S, superkind>;

	public:
		using S_::S_;

	//	TODO: Limit to instances of `direction`, not just derived...
		using direction_signature = succedent_s<typename S_::direction_signature>;

	};
};


////////////////////////////////////////////////////////////////////////////////
/**/
XTAL_DEF_(return,inline,let)
direction_f(make_q<direction_s<>> auto &&s)
noexcept -> auto
{
	return direction_s< >{XTAL_REF_(s)};
}
XTAL_DEF_(return,inline,let)
direction_f(make_q<direction_s<>> auto &&s, auto &&t)
noexcept -> auto
{
	using T = let_t<XTAL_ALL_(t)>;
	return direction_s<T>(XTAL_REF_(s), T{XTAL_REF_(t)});	
}
template <any_q T> XTAL_DEF_(return,inline,let) operator << (direction_s<>       &&s, T &&t) noexcept -> decltype(auto) {return direction_f(XTAL_MOV_(s), XTAL_REF_(t));}
template <any_q T> XTAL_DEF_(return,inline,let) operator << (direction_s<> const  &s, T &&t) noexcept -> decltype(auto) {return direction_f(XTAL_REF_(s), XTAL_REF_(t));}

/***/
///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
