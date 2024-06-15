#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::flux
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
///\
Wrapper used to index an existing type. \

///\see e.g. [../processor/polymer.hh]. \

template <class   ..._s>	XTAL_TYP key;
template <class   ..._s>	XTAL_REQ key_q = bond::any_tag_p<key, _s...>;
template <class   ..._s>	XTAL_USE key_s = bond::compose_s<packet_t<_s...>, cell::confined<key<>>>;


////////////////////////////////////////////////////////////////////////////////

template <>
struct key<>
{
	using _op = bond::operating;

	using subkind = cell::confer<typename _op::iota_t, bond::tag<key>>;

	template <class S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;

	public:
		using S_::S_;

		XTAL_TO4_(XTAL_DEF_(return,inline) XTAL_CVN_(implicit) auto(), key_s<>(S_::head()))
		
		using key_type = XTAL_ALL_(XTAL_ANY_(S_).tail());
		using key_size = nominal_t<size_1>;

	};
	template <key_q S>
	class subtype<S> : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;

	public:
		using S_::S_;

		using key_size = superliminal_s<typename S_::key_size>;
	//	TODO: Adapt `assay` for this?

	};
};


////////////////////////////////////////////////////////////////////////////////
/**/
template <any_q T>
XTAL_DEF_(return,inline)
XTAL_LET key_f(XTAL_ARG_(key_s<>) &&s, T &&t)
XTAL_0EX
{
	using Y = based_t<T>;
	using F =   key_s<Y>;
	XTAL_IF0
	XTAL_0IF (             any_q<T>) {return F(XTAL_REF_(s),                            XTAL_REF_(t) );}
	XTAL_0IF (bond::heteropack_q<T>) {return F(XTAL_REF_(s), bond::pack_row_f<packed_t>(XTAL_REF_(t)));}
	XTAL_0IF_(default)               {return F(XTAL_REF_(s),             conferred_t<Y>(XTAL_REF_(t)));}
	
}
template <any_q T> XTAL_DEF_(return,inline) XTAL_RET operator << (key_s<>       &&s, T &&t) XTAL_0EX {return key_f(XTAL_MOV_(s), XTAL_REF_(t));}
template <any_q T> XTAL_DEF_(return,inline) XTAL_RET operator << (key_s<> const  &s, T &&t) XTAL_0EX {return key_f(XTAL_REF_(s), XTAL_REF_(t));}

/***/
///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
