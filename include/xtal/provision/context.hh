#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::provision
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
Composes `As...`, and reifying the result as the member decorator `subtext`. \
Used to provide a uniform interface between different instantiations. \

template <typename ..._s> struct   context;
template <typename ..._s> using    context_t = confined_t<context<_s...>>;
template <typename ..._s> concept  context_q = bond::any_tag_p<context, _s...>;


////////////////////////////////////////////////////////////////////////////////

template <typename ...As>
struct context
{
	using superkind = bond::compose<As...>;

	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		using S_ = bond::compose_s<S, superkind>;
		
	public:
		using S_::S_;

		template <class ...Vs>
		struct subtext
		{
			using duperkind = bond::compose<Vs..., superkind>;
			
			template <class R>
			using subtype = bond::compose_s<R, duperkind>;

		};
		template <class ...Vs> requires bond::compose_q<typename S_::template subtext<>>
		struct subtext<Vs...>
		{
			using duperkind = typename bond::compose<Vs..., superkind, typename S_::template subtext<>>;
			
			template <class R>
			using subtype = bond::compose_s<R, duperkind>;

		};

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
