#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::resource
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
Bundles decorators for later use. \

template <typename ..._s> XTAL_TYP invoice;
template <typename ..._s> XTAL_USE invoice_t = confined_t<invoice<_s...>>;
template <typename ..._s> XTAL_ASK invoice_q = bond::any_tag_p<invoice, _s...>;


////////////////////////////////////////////////////////////////////////////////

template <typename ...As>
struct invoice
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
			using superkind = bond::compose<Vs..., metakind>;
			
			template <class R>
			class subtype : public bond::compose_s<R, superkind>
			{
				using R_ = bond::compose_s<R, superkind>;

			public:// CONSTRUCT
				using R_::R_;

			};
		};
//		template <class ...Xs>
//		struct bracket
//		{
//			using superkind = voice<typename S_::template bracket<Xs...>>;
//			
//			template <class R>
//			class subtype : public bond::compose_s<R, superkind>
//			{
//				using R_ = bond::compose_s<R, superkind>;
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
