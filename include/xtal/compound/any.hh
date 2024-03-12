#pragma once
#include "../atom/all.ii"// `_retail`






XTAL_ENV_(push)
namespace xtal::compound
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

namespace _retail {using namespace xtal::atom;}
namespace _retail
{///////////////////////////////////////////////////////////////////////////////
///\
Creates a unique `subtype` tagged by the given `As...`, \
such that e.g. `std::derives_from<any<struct x, struct xs...>, any<struct xs...>>`. \

template <typename ...As>
struct any
{
	using subkind = atom::compose<any<As>...>;
	
	template <class S>
	using subtype = atom::compose_s<S, subkind>;
	using    type = subtype<unit_t>;
	
};
template <>
struct any<void>
{	
	template <class S>
	using subtype = S;
	
	using type = subtype<unit_t>;

};
template <>
struct any<>
{	
	template <class S>
	class subtype: public atom::compose_s<S, atom::identify<>>
	{
		using S_ = atom::compose_s<S, atom::identify<>>;
		
	public:
		using S_::S_;

	protected:
		///\
		Fallback resolver, defaulting to the `back` type/selector. \
		
		template <class ...Ys> struct super: atom::seek_back<Ys...> {};

	};
	template <class S> requires atom::identity_p<S>
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
	
	using subkind = atom::compose<atom::identify<A>, any<>>;

	template <class S>
	class subtype: public atom::compose_s<S, subkind>
	{
		using S_ = atom::compose_s<S, subkind>;
		
	public:
		using S_::S_;
		
	};
	template <class S> XTAL_REQ_(typename S::T_self)
	class subtype<S>: public atom::compose_s<S, subkind>
	{
		using S_ = atom::compose_s<S, subkind>;

	public://protected:
		using typename S::T_self;
		using typename S::U_self;

	protected:
		template <class A_self, typename ...Is> struct super:      S_::template super<A_self, Is...> {};
		template <class A_self, typename ...Is> struct super<A_self, A, Is...>: super<U_self, Is...> {};
		template <class A_self, typename ...Is>  using super_t =       typename super<A_self, Is...>::type;

	public:
	//	using S_::S_;
		using S_::self;

		template <typename ...Is> using self_t =          super_t<T_self, Is...>;
		template <typename ...Is> using head_t = typename super_t<U_self, Is...>::U_head;

		XTAL_CO0_(subtype);
		XTAL_CO4_(subtype);
		///\
		Attempts construction from infungible-but-compatible types via inspection. \
		
		template <class W>
		requires infungible_q<subtype, W> and
		requires {typename W::template self_t<A>;}
		XTAL_CON subtype(W &&w, XTAL_DEF ...oo)
		XTAL_0EX
		:	S_(w.template head<A>(), XTAL_REF_(w), XTAL_REF_(oo)...)
		{};
		XTAL_CXN subtype(XTAL_DEF ...oo)
		XTAL_0EX
		:	S_(XTAL_REF_(oo)...)
		{}

		XTAL_TO4_(template <size_t ...Is> requires (0 < sizeof...(Is))
		XTAL_TN2 self(XTAL_DEF... oo), self<cardinal_t<Is>...>(XTAL_REF_(oo)...)
		)		
		XTAL_TO4_(template <size_t ...Is> requires (0 < sizeof...(Is))
		XTAL_TN2 head(XTAL_DEF... oo), head<cardinal_t<Is>...>(XTAL_REF_(oo)...)
		)		

		XTAL_TO4_(template <typename ...Is>
		XTAL_TN2 self(XTAL_DEF... oo), S_::template self<super_t<T_self, Is...>>(XTAL_REF_(oo)...)
		)
		XTAL_TO4_(template <typename ...Is>
		XTAL_TN2 head(XTAL_DEF... oo), S_::template self<super_t<U_self, Is...>>().head(XTAL_REF_(oo)...)
		)
		
	};
	using type = subtype<unit_t>;

};

}///////////////////////////////////////////////////////////////////////////////

#include "./_detail.hxx"


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
