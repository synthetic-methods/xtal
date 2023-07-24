#pragma once
#include "../common/all.hpp"// `_retail`






XTAL_ENV_(push)
namespace xtal::concord
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

namespace _retail
{///////////////////////////////////////////////////////////////////////////////

using namespace xtal::common;


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
		using S_ = S;
		using T_ = typename S_::self_t;

	protected:
		using Y = S_;
		///\see `concord/anybody.hpp#defer`. \
		
		template <class X, typename ...Is> struct super:              S_::template super<X, Is...> {};
		template <class X, typename ...Is> struct super<X, A, Is...>: S_::template super<Y, Is...> {};
		
	public:
		using S_::S_;
	//	using S_::self;
	//	using S_::head;
		
		XTAL_DO4_(template <typename ...Is>
		XTAL_FN2 self(XTAL_DEF... oo),
		{
			using X = typename super<T_, Is...>::type;
			return S_::template self<X>(XTAL_REF_(oo)...);
		})		
		XTAL_DO4_(template <typename ...Is>
		XTAL_FN2 head(XTAL_DEF... oo),
		{
			using X = typename super<S_, Is...>::type;
			return S_::template self<X>().head(XTAL_REF_(oo)...);
		})		

		XTAL_TO4_(template <size_t I>
		XTAL_FN2 self(XTAL_DEF... oo),
			self<substant_t<I>>(XTAL_REF_(oo)...)
		)		
		XTAL_TO4_(template <size_t I>
		XTAL_FN2 head(XTAL_DEF... oo),
			head<substant_t<I>>(XTAL_REF_(oo)...)
		)		

	};
};

}///////////////////////////////////////////////////////////////////////////////

#include "./_detail.hxx"


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
