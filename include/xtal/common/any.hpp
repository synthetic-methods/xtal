#pragma once
#include "../any.hpp"






XTAL_ENV_(push)
namespace xtal::common
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ...> struct compose;
template <typename    > struct realize;


////////////////////////////////////////////////////////////////////////////////
///\
Creates a unique `subtype` tagged by the given `As...`, \
such that e.g. `std::derives_from<any<struct x, struct xs...>, any<struct xs...>>`. \

template <typename ...As>
struct any
{
	using subkind = compose<any<As>...>;

	template <class S>
	using subtype = typename subkind::template subtype<S>;

};
template <typename A>
struct any<A>
{	
	template <class S>
	class subtype: public S
	{
	public:
		using S::S;

	};
	template <class S> XTAL_REQ_(typename S::self_t)
	class subtype<S>: public S
	{
		using T_ = typename S::self_t;

	protected:
		///\see `concord/anybody.hpp#defer`. \
		
		template <class X, typename ...Is> struct super:              S::template super<X, Is...> {};
		template <class X, typename ...Is> struct super<X, A, Is...>: S::template super<S, Is...> {};
		
	public:
		using S::S;
	//	using S::self;
		
		XTAL_DO4_(template <typename ...Is>
		XTAL_FN2 self(XTAL_DEF... oo),
		{
			using X = typename super<T_, Is...>::type;
			return S::template self<X>(XTAL_REF_(oo)...);
		})		
		template <typename ...Is>
		XTAL_FN1 set(XTAL_DEF... oo)
		XTAL_0EX
		{
			return self<Is...>().head(XTAL_REF_(oo)...);
		}
		template <typename ...Is>
		XTAL_FN2 get()
		XTAL_0FX
		{
			return self<Is...>().head();
		}
		
	};
};


////////////////////////////////////////////////////////////////////////////////

#include "./_detail.hxx"


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
