#pragma once
#include "../bond/all.ii"// `_retail`
#include "../group/all.ii"





XTAL_ENV_(push)
namespace xtal::cell
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

namespace _retail {using namespace xtal::bond;}
namespace _retail
{///////////////////////////////////////////////////////////////////////////////
///\
Creates a unique `subtype` tagged by the given `As...`, \
such that e.g. `std::derives_from<any<struct x, struct xs...>, any<struct xs...>>`. \

template <typename ...As>
struct any
{
	using subkind = bond::compose<any<As>...>;
	
	template <class S>
	using subtype = bond::compose_s<S, subkind>;
	
};
template <>
struct any<void>
{	
	template <class S>
	using subtype = S;

};
template <typename A>
struct any<A>
{	
	template <class S> requires some_q<typename S::T_self>
	class subtype: public bond::compose_s<S>
	{
		using S_ = bond::compose_s<S>;

	public://protected:
		using typename S::T_self;
		using typename S::U_self;

	public:
		template <class _, class ...Is> struct duper: S_::template super<_,      Is...> {};
		template <class _, class ...Is> struct super             : duper<_,      Is...> {};
		template <class _, class ...Is> struct super<_, A, Is...>: super<U_self, Is...> {};

	public:
		template <class ...Is> using self_s = typename super<T_self, Is...>::type;
		template <class ...Is> using head_s = typename super<U_self, Is...>::type;
		template <class ...Is> using head_t = typename head_s<Is...>::U_head;

	//	using S_::self;
	//	using S_::head;
		
		XTAL_TO4_(template <class  ...Is>// requires some_q<Is...>
		XTAL_TN2 self(auto &&...oo), S_::template self<self_s<Is...>>(XTAL_FWD_(oo)...)
		)
		XTAL_TO4_(template <class  ...Is>// requires some_q<Is...>
		XTAL_TN2 head(auto &&...oo), S_::template self<head_s<Is...>>().head(XTAL_FWD_(oo)...)
		)
		XTAL_TO4_(template <size_t ...Is> requires some_n<Is...>
		XTAL_TN2 self(auto &&...oo), self<cardinal_t<Is>...>(XTAL_FWD_(oo)...)
		)
		XTAL_TO4_(template <size_t ...Is> requires some_n<Is...>
		XTAL_TN2 head(auto &&...oo), head<cardinal_t<Is>...>(XTAL_FWD_(oo)...)
		)
	
	public:
	//	using S_::S_;

		XTAL_CO0_(subtype);
		XTAL_CO4_(subtype);
		///\
		Attempts construction from infungible-but-compatible types via inspection. \
		
		template <class W>
		requires infungible_q<subtype, W> and
		requires {typename W::template self_s<A>;}
		XTAL_CON subtype(W &&w, auto &&...oo)
		XTAL_0EX
		:	S_(w.template head<A>(), XTAL_FWD_(w), XTAL_FWD_(oo)...)
		{};
		XTAL_CXN subtype(auto &&...oo)
		XTAL_0EX
		:	S_(XTAL_FWD_(oo)...)
		{}

	};
};

}///////////////////////////////////////////////////////////////////////////////

#include "./_detail.hxx"


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
