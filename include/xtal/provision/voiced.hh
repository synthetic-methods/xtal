#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::provision
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
Composes `As...` as the member decorator `voice`, \
used to provide the context for different instantiations (\see `polymer`). \

template <typename ..._s> struct   voiced;
template <typename ..._s> using    voiced_t = confined_t<voiced<_s...>>;
template <typename ..._s> concept  voiced_q = bond::tagged_with_p<voiced, _s...>;


////////////////////////////////////////////////////////////////////////////////

template <typename ...As>
struct voiced
{
	using superkind = bond::compose<As...>;

	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		using S_ = bond::compose_s<S, superkind>;
		
	public:
		using S_::S_;

		template <class ...Vs>
		struct voice
		{
			using duperkind = bond::compose<Vs..., superkind>;
			
			template <class R>
			using subtype = bond::compose_s<R, duperkind>;

		};
		template <class ...Vs> requires bond::compose_q<typename S_::template voice<>>
		struct voice<Vs...>
		{
			using duperkind = typename bond::compose<Vs..., superkind, typename S_::template voice<>>;
			
			template <class R>
			using subtype = bond::compose_s<R, duperkind>;

		};

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
