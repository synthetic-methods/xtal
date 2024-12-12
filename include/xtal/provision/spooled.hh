#pragma once
#include "./any.hh"
#include "../arrange/all.hh"





XTAL_ENV_(push)
namespace xtal::provision
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ..._s> struct   spooled;
template <typename ..._s> using    spooled_t = confined_t<spooled<_s...>>;
template <typename ..._s> concept  spooled_q = bond::any_tag_p<spooled, _s...>;


////////////////////////////////////////////////////////////////////////////////
///\
Provides a specialization of `arrange::spool`. \

template <bond::compose_q A>
struct spooled<A>
{
	using superkind = bond::tag<spooled>;
	
	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		using S_ = bond::compose_s<S, superkind>;
		
	public:
		using S_::S_;
		
		template <class U>
		using spool_t = typename A::template subtype<U>;

	};
};
template <constant_q A>
struct spooled<A>
{
	using superkind = bond::tag<spooled>;
	
	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		using S_ = bond::compose_s<S, superkind>;
		
	public:
		using S_::S_;
		
		template <class U>
		using spool_t = arrange::spool_t<U[static_cast<unsigned>(A{})]>;

	};
};
template <auto N>
struct spooled<unit_type[N]>
:	spooled<constant_t<unsigned(N)>>
{
};
template <auto N>
struct spooled<null_type[N]>
:	spooled<constant_t<  signed(N)>>
{
};
template <>
struct spooled<>
:	spooled<constant_t<-1>>
{};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
