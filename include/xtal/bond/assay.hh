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
struct assay
{
	template <class S>
	class subtype : public S
	{
		using S_ = S;
	
	public:
		using S_::S_;

		XTAL_DEF_(return,inline,static)
		XTAL_LET size()
		XTAL_0EX
		{
			return N_width;
		};

	};
};
template <class T>
concept assay_q = requires {{T::size()} -> integral_q;};


}///////////////////////////////////////////////////////////////////////////////

template <class ...Ts>
concept assay_q = (...and _detail::assay_q<Ts>);


////////////////////////////////////////////////////////////////////////////////
///\
Defines the limits of a bit-field. \

template <int N_width>
struct assay
{
	template <size_t N_widen=1>
	using semikind = _detail::assay<N_widen*N_width>;

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
	template <class S> requires assay_q<S>
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
