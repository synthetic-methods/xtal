#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::resource
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
Bundles decorators for later use. \

template <typename ..._s> XTAL_TYP voiced;
template <typename ..._s> XTAL_USE voiced_t = confined_t<voiced<_s...>>;
template <typename ..._s> XTAL_REQ voiced_q = bond::any_tag_p<voiced, _s...>;


////////////////////////////////////////////////////////////////////////////////

template <typename ...As>
struct voiced
{
	using metakind = bond::compose<As...>;

	template <class S>
	class subtype : public bond::compose_s<S, metakind>
	{
		using S_ = bond::compose_s<S, metakind>;
		
	public:
		using S_::S_;

		template <class ...Vs>
		struct voice
		{
			using subkind = bond::compose<Vs..., metakind>;
			
			template <class R>
			class subtype : public bond::compose_s<R, subkind>
			{
				using R_ = bond::compose_s<R, subkind>;

			public:// CONSTRUCT
				using R_::R_;

			};
		};
//		template <class ...Xs>
//		struct brace
//		{
//			using subkind = voice<typename S_::template brace<Xs...>>;
//			
//			template <class R>
//			class subtype : public bond::compose_s<R, subkind>
//			{
//				using R_ = bond::compose_s<R, subkind>;
//
//			public:// CONSTRUCT
//				using R_::R_;
//
//			};
//		};

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
