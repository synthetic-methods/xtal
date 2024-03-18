#pragma once
#include "../bond/all.ii"// `_retail`






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
	using    type = subtype<unit_t>;
	
};
template <>
struct any<void>
{	
	template <class S>
	using subtype = S;
	using    type = subtype<unit_t>;

};
template <typename A>
struct any<A>
{	
	//\
	using subkind = bond::compose<>;
	using subkind = bond::tab<A>;

	template <class S>
	class subtype: public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;
		
	public:
		using S_::S_;
		
	};
	template <class S> requires some_q<typename S::T_self>
	and bond::untabbed_p<A, S>
	//\

	class subtype<S>: public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;

	public:
	//	using S_::S_;

		XTAL_CO0_(subtype);
		XTAL_CO4_(subtype);
		///\
		Attempts construction from infungible-but-compatible types via inspection. \
		
		template <class W>
		requires infungible_q<subtype, W> and
		requires {typename W::template self_t<A>;}
		XTAL_CON subtype(W &&w, auto &&...oo)
		XTAL_0EX
		:	S_(w.template head<A>(), XTAL_FWD_(w), XTAL_FWD_(oo)...)
		{};
		XTAL_CXN subtype(auto &&...oo)
		XTAL_0EX
		:	S_(XTAL_FWD_(oo)...)
		{}

	public://protected:
		using typename S::T_self;
		using typename S::U_self;

	protected:
		template <class Y_self, typename ...Is> struct super:      S_::template super<Y_self, Is...> {};
		template <class Y_self, typename ...Is> struct super<Y_self, A, Is...>: super<U_self, Is...> {};

	public:
		template <typename ...Is> using self_t = typename super<T_self, Is...>::type;
		template <typename ...Is> using head_t = typename super<U_self, Is...>::type::U_head;

		XTAL_TO4_(template <size_t ...Is> requires (0 < sizeof...(Is))
		XTAL_TN2 self(auto &&...oo), self<cardinal_t<Is>...>(XTAL_FWD_(oo)...)
		)		
		XTAL_TO4_(template <size_t ...Is> requires (0 < sizeof...(Is))
		XTAL_TN2 head(auto &&...oo), head<cardinal_t<Is>...>(XTAL_FWD_(oo)...)
		)		

		XTAL_TO4_(template <class ...Is>
		XTAL_TN2 self(auto &&...oo), S_::template self<typename super<T_self, Is...>::type>(XTAL_FWD_(oo)...)
		)
		XTAL_TO4_(template <class ...Is>
		XTAL_TN2 head(auto &&...oo), S_::template self<typename super<U_self, Is...>::type>().head(XTAL_FWD_(oo)...)
		)
		
	};
};

}///////////////////////////////////////////////////////////////////////////////

#include "./_detail.hxx"


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
