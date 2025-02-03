#pragma once
#include "./any.hh"
#include "./compose.hh"





XTAL_ENV_(push)
namespace xtal::bond
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

namespace _detail
{///////////////////////////////////////////////////////////////////////////////

template <size_type N_size>
struct word
{
	template <class S>
	class subtype : public S
	{
		using S_ = S;
	
	public:
		using S_::S_;

		static cardinal_constant_t<N_size> constexpr cardinality{};

	};
};
template <class T>
concept word_q = requires {{T::cardinality()} -> cardinal_q;};


}///////////////////////////////////////////////////////////////////////////////

template <class ...Ts>
concept word_q = (...and _detail::word_q<Ts>);


////////////////////////////////////////////////////////////////////////////////
///\
Defines the limits of a bit-field. \

template <size_type N_size>
struct word
{
	template <int M_size=1>
	using semikind = _detail::word<M_size*N_size>;

	template <class S>
	class subtype : public bond::compose_s<S, semikind<>>
	{
		using S_ = bond::compose_s<S, semikind<>>;
	
	public:
		using S_::S_;

		///\
		Base constructor, expects `0`. \

		template <integral_q A>
		XTAL_NEW_(explicit) subtype(A &&a)
		noexcept
		{
			assert(0 == a);
		};

	};
	template <class S> requires word_q<S>
	class subtype<S> : public bond::compose_s<S, semikind<S::cardinality()>>
	{
		using S_ = bond::compose_s<S, semikind<S::cardinality()>>;
	
	public:
		using S_::S_;

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
