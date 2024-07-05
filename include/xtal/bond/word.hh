#pragma once
#include "./any.hh"
#include "./compose.hh"





XTAL_ENV_(push)
namespace xtal::bond
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

namespace _detail
{///////////////////////////////////////////////////////////////////////////////

template <int N_width>
struct word
{
	template <class S>
	class subtype : public S
	{
		using S_ = S;
	
	public:
		using S_::S_;

		XTAL_DEF_(return,inline)
		XTAL_SET size()
		XTAL_0EX
		{
			return N_width;
		};

	};
};
template <class T>
concept word_q = requires {{T::size()} -> integral_q;};


}///////////////////////////////////////////////////////////////////////////////

template <class ...Ts>
concept word_q = (...and _detail::word_q<Ts>);


////////////////////////////////////////////////////////////////////////////////
///\
Defines the limits of a bit-field. \

template <int N_width>
struct word
{
	template <size_type N_widen=1>
	using semikind = _detail::word<N_widen*N_width>;

	template <class S>
	class subtype : public bond::compose_s<S, semikind<>>
	{
		using S_ = bond::compose_s<S, semikind<>>;
	
	public:
		using S_::S_;

		///\
		Default `nominal_q` constructor, expects `0`. \

		template <integral_q A>
		XTAL_CON_(explicit) subtype(A &&a)
		XTAL_0EX
		{
			assert(0 == a);
		};

	};
	template <class S> requires word_q<S>
	class subtype<S> : public bond::compose_s<S, semikind<S::size()>>
	{
		using S_ = bond::compose_s<S, semikind<S::size()>>;
	
	public:
		using S_::S_;

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
