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
		using S_ = common::compose_s<S, common::identify<>>;
		
	public:
		using S_::S_;

	protected:
		///\
		Fallback resolver, defaulting to the `back` type/selector. \
		
		template <class ...Ys> struct super: common::seek_back<Ys...> {};

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
		using S_ = common::compose_s<S, subkind>;
		
	public:
		using S_::S_;
		
	};
	template <class S> XTAL_REQ_(typename S::self_t)
	class subtype<S>: public common::compose_s<S, subkind>
	{
		using S_ = common::compose_s<S, subkind>;
		using T_ = typename S_::self_t;

	protected:
		using Y = typename S_::duper_t;
		
		template <class X, typename ...Is> struct super: S_::template super<X, Is...> {};
		template <class X, typename ...Is> struct super<X, A, Is...>: super<Y, Is...> {};
		template <class X, typename ...Is> using super_t = typename super<X, Is...>::type;

	public:
	//	using S_::S_;
		using S_::self;

		XTAL_CO0_(subtype);
		XTAL_CO4_(subtype);
		
		///\
		Attempts construction from infungible-but-compatible types via inspection. \
		
		template <class W> requires infungible_q<subtype, W> and common::identity_p<subtype, W>
		XTAL_CON subtype(W &&w, XTAL_DEF ...oo)
		XTAL_0EX
		:	S_(w.template head <A>(), XTAL_REF_(w), XTAL_REF_(oo)...)
		{};
		XTAL_CXN subtype(XTAL_DEF ...oo)
		XTAL_0EX
		:	S_(XTAL_REF_(oo)...)
		{}

		XTAL_TO4_(template <size_t ...Is> requires some_n<Is...>
		XTAL_TN2 self(XTAL_DEF... oo), self<cardinal_t<Is>...>(XTAL_REF_(oo)...)
		)		
		XTAL_TO4_(template <size_t ...Is> requires some_n<Is...>
		XTAL_TN2 head(XTAL_DEF... oo), head<cardinal_t<Is>...>(XTAL_REF_(oo)...)
		)		

		XTAL_TO4_(template <typename ...Is>
		XTAL_TN2 self(XTAL_DEF... oo), S_::template self<super_t<T_, Is...>>(XTAL_REF_(oo)...)
		)
		XTAL_TO4_(template <typename ...Is>
		XTAL_TN2 head(XTAL_DEF... oo), S_::template self<super_t<S_, Is...>>().head(XTAL_REF_(oo)...)
		)
		
	};
	using type = subtype<unit_t>;

};

}///////////////////////////////////////////////////////////////////////////////

#include "./_detail.hxx"


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
