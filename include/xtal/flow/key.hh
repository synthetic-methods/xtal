#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::flow
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
///\
Wrapper used to index an existing type. \

///\see e.g. [../processor/polymer.hh]. \

template <class   ..._s>	struct   key;
template <class   ..._s>	concept  key_q = bond::tag_p<key, _s...>;
template <class   ..._s>	using    key_s = bond::compose_s<packet_t<_s...>, cell::confined<key<>>>;


////////////////////////////////////////////////////////////////////////////////

template <>
struct key<>
{
	using superkind = cell::confer<signed, bond::tag<key>>;

	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		using S_ = bond::compose_s<S, superkind>;

	public:
		using S_::S_;

		XTAL_FX4_(alias) (XTAL_DEF_(return,inline,implicit operator) auto(), key_s<>(S_::head()))
		
		using keyed_type = XTAL_ALL_(XTAL_ANY_(S_).tail())[1];

	};
	template <key_q S>
	class subtype<S> : public bond::compose_s<S, superkind>
	{
		using S_ = bond::compose_s<S, superkind>;

	public:
		using S_::S_;

		using keyed_type = superliminal_t<typename S_::keyed_type>;

	};
};


////////////////////////////////////////////////////////////////////////////////
/**/
template <any_q T>
XTAL_DEF_(return,inline,let)
key_f(same_q<key_s<>> auto &&s, T &&t)
noexcept -> auto
{
	using Y = based_t<T>;
	using F =   key_s<Y>;
	XTAL_IF0
	XTAL_0IF (             any_q<T>) {return F(XTAL_REF_(s),                          XTAL_REF_(t) );}
	XTAL_0IF (bond::heteropack_q<T>) {return F(XTAL_REF_(s), bond::repack_f<packed_t>(XTAL_REF_(t)));}
	XTAL_0IF_(else)                  {return F(XTAL_REF_(s),           conferred_t<Y>(XTAL_REF_(t)));}
}
template <any_q T>
XTAL_DEF_(return,inline,let)
key_f(integral_q auto &&s, T &&t)
noexcept -> auto
{
	return key_f(key_s<>(XTAL_REF_(s)), XTAL_REF_(t));
}
template <any_q T> XTAL_DEF_(return,inline,let) operator << (key_s<>       &&s, T &&t) noexcept -> decltype(auto) {return key_f(XTAL_MOV_(s), XTAL_REF_(t));}
template <any_q T> XTAL_DEF_(return,inline,let) operator << (key_s<> const  &s, T &&t) noexcept -> decltype(auto) {return key_f(XTAL_REF_(s), XTAL_REF_(t));}

/***/
///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
