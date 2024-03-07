#pragma once
#include "../common/all.ii"// `_retail`






XTAL_ENV_(push)
namespace xtal::compound
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

namespace _retail {using namespace xtal::common;}
namespace _retail
{///////////////////////////////////////////////////////////////////////////////
///\
Creates a unique `subtype` tagged by the given `As...`, \
such that e.g. `std::derives_from<any<struct x, struct xs...>, any<struct xs...>>`. \

template <typename ...As>
struct any
{
	using subkind = common::compose<any<As>...>;
	
	template <class S>
	using subtype = common::compose_s<S, subkind>;
	using    type = subtype<unit_t>;
	
};
template <>
struct any<>
{	
	template <class S>
	class subtype: public common::compose_s<S, common::identify<>>
	{
		using _S = common::compose_s<S, common::identify<>>;
		
	public:
		using _S::_S;

	protected:
		///\
		Fallback resolver, defaulting to the `back` type/selector. \
		
		template <class ...Ys> struct node: common::seek_back<Ys...> {};

	};
	template <class S> requires common::identity_p<S>
	class subtype<S>: public S
	{
	public:
		using S::S;

	};
	using type = subtype<unit_t>;

};
template <typename A>
struct any<A>
{	
//	NOTE: `identify` records the applied `any`s by _out-of-band_ inheritance. \
	
	using subkind = common::compose<common::identify<A>, any<>>;

	template <class S>
	class subtype: public common::compose_s<S, subkind>
	{
		using _S = common::compose_s<S, subkind>;
		
	public:
		using _S::_S;
		
	};
	template <class S> XTAL_REQ_(typename S::self_u)
	class subtype<S>: public common::compose_s<S, subkind>
	{
		using _S = common::compose_s<S, subkind>;
		using _T = typename _S::self_u;
		using _Y = typename _S::node_u;

	protected:
		template <class X, typename ...Is> struct node: _S::template node< X, Is...> {};
		template <class X, typename ...Is> struct node<X, A, Is...>: node<_Y, Is...> {};
		template <class X, typename ...Is>  using node_t = typename node<X, Is...>::type;

	public:
	//	using _S::_S;
		using _S::self;

		template <typename ...Is> using self_t =          node_t<_T, Is...>;
		template <typename ...Is> using head_t = typename node_t<_Y, Is...>::head_u;

		XTAL_CO0_(subtype);
		XTAL_CO4_(subtype);
		///\
		Attempts construction from infungible-but-compatible types via inspection. \
		
		template <class W>
		requires infungible_q<subtype, W> and
		requires {typename W::template self_t<A>;}
		XTAL_CON subtype(W &&w, XTAL_DEF ...oo)
		XTAL_0EX
		:	_S(w.template head<A>(), XTAL_REF_(w), XTAL_REF_(oo)...)
		{};
		XTAL_CXN subtype(XTAL_DEF ...oo)
		XTAL_0EX
		:	_S(XTAL_REF_(oo)...)
		{}

		XTAL_TO4_(template <size_t ...Is> requires some_n<Is...>
		XTAL_TN2 self(XTAL_DEF... oo), self<cardinal_t<Is>...>(XTAL_REF_(oo)...)
		)		
		XTAL_TO4_(template <size_t ...Is> requires some_n<Is...>
		XTAL_TN2 head(XTAL_DEF... oo), head<cardinal_t<Is>...>(XTAL_REF_(oo)...)
		)		

		XTAL_TO4_(template <typename ...Is>
		XTAL_TN2 self(XTAL_DEF... oo), _S::template self<node_t<_T, Is...>>(XTAL_REF_(oo)...)
		)
		XTAL_TO4_(template <typename ...Is>
		XTAL_TN2 head(XTAL_DEF... oo), _S::template self<node_t<_S, Is...>>().head(XTAL_REF_(oo)...)
		)
		
	};
	using type = subtype<unit_t>;

};

}///////////////////////////////////////////////////////////////////////////////

#include "./_detail.hxx"


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
