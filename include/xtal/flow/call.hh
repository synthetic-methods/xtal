#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::flow
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
///\
Reifies the `signed` template-parameter for the `flux` and `fuse` methods. \

/**/
template <class ..._s> struct  call;
template <class ..._s> concept call_q = bond::tag_p<call, _s...>;
template <class ..._s> using   call_s = bond::compose_s<packet_t<_s...>, cell::confined<call<>>>;
/*/
template <class ..._s> struct  call;
template <class ..._s> using   call_s =  bond::compose_s<packet_t<_s...>, cell::confined<call<>>>;
template <class T    > using   call_u =  valued_u<typename T::call_signature>;
template <class ..._s> concept call_q = (bond::tag_p<call, _s...> and...and same_q<_s, call_s<call_u<_s>>>);
/***/

////////////////////////////////////////////////////////////////////////////////

template <>
struct call<>
{
	using superkind = cell::confer<signed, bond::tag<call>>;

	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		using S_ = bond::compose_s<S, superkind>;

	public:
		using S_::S_;

		XTAL_FX4_(to) (XTAL_DEF_(return,inline,implicit operator)
		auto(), call_s<>(S_::head()))

		using call_signature = XTAL_ALL_(XTAL_ANY_(S).tail())[1];

	};
	template <bond::tag_q<call> S>
	class subtype<S> : public bond::compose_s<S, superkind>
	{
		using S_ = bond::compose_s<S, superkind>;

	public:
		using S_::S_;

	//	TODO: Limit to instances of `call`, not just derived...
		using call_signature = succedent_s<typename S_::call_signature>;

	};
};


////////////////////////////////////////////////////////////////////////////////
/**/
XTAL_DEF_(return,inline,let)
call_f(make_q<call_s<>> auto &&s)
noexcept -> auto
{
	return call_s< >{XTAL_REF_(s)};
}
XTAL_DEF_(return,inline,let)
call_f(make_q<call_s<>> auto &&s, auto &&t)
noexcept -> auto
{
	using T = let_t<XTAL_ALL_(t)>;
	return call_s<T>(XTAL_REF_(s), T{XTAL_REF_(t)});	
}
template <any_q T> XTAL_DEF_(return,inline,let) operator << (call_s<>       &&s, T &&t) noexcept -> decltype(auto) {return call_f(XTAL_MOV_(s), XTAL_REF_(t));}
template <any_q T> XTAL_DEF_(return,inline,let) operator << (call_s<> const  &s, T &&t) noexcept -> decltype(auto) {return call_f(XTAL_REF_(s), XTAL_REF_(t));}

/***/
///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
