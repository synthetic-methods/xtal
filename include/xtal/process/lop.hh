#pragma once
#include "./any.hh"

#include "./link.hh"




XTAL_ENV_(push)
namespace xtal::process::math
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/*!
\brief   Maps the first argument with `lift_t<As...>`/`link_t<As...>`,
         passing the result and remaining arguments to the superclass..
*/
template <typename ...As>
struct  lop;


////////////////////////////////////////////////////////////////////////////////

template <typename ...As>
struct lop
{
	using supertype = link_t<As...>;
	using superkind = defer<supertype>;

	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		using S_ = bond::compose_s<S, superkind>;

	public:// CONSTRUCT
		using S_::S_;

	public:// OPERATE

		XTAL_FX2_(do) (template <auto ...Is>
		XTAL_DEF_(return,inline,let)
		method(auto &&o, auto &&...oo),
		noexcept -> auto
		{
			return S::template method  <Is...>(S_::head().template method  <Is...>(XTAL_REF_(o)), XTAL_REF_(oo)...);
		})
		template <auto ...Is>
		XTAL_DEF_(return,inline,set)
		method_f(auto &&o, auto &&...oo)
		noexcept -> auto
		requires in_n<requires {supertype::template method_f<Is...>(o);}>
		{
			return S::template method_f<Is...>(supertype::template method_f<Is...>(XTAL_REF_(o)), XTAL_REF_(oo)...);
		}

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
