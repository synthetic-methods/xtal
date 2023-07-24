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
template <>
struct any<>
{	
	template <class S>
	class subtype: public S
	{
	public:
		using S::S;

	protected:
		template <fungible_q ...Ys> struct super: terminal<Ys...> {};

	};
	template <class S> XTAL_REQ_(typename S::template super<S>)
	class subtype<S>: public S
	{
	public:
		using S::S;

	};
};
template <typename A>
struct any<A>
{	
	using subkind = any<>;
	
	template <class S>
	class subtype: public compose_s<S, subkind>
	{
		using S_ = compose_s<S, subkind>;
		
	public:
		using S_::S_;

	};
	template <class S> XTAL_REQ_(typename S::self_t)
	class subtype<S>: public compose_s<S, subkind>
	{
		using S_ = compose_s<S, subkind>;
		using T_ = typename S_::self_t;

	protected:
		using Y = S_;
		///\see `concord/anybody.hpp#defer`. \
		
		template <class X, typename ...Is> struct super:              S_::template super<X, Is...> {};
		template <class X, typename ...Is> struct super<X, A, Is...>: S_::template super<Y, Is...> {};
	
	private:
		template <class X, typename ...Is>
		using super_t = typename super<X, Is...>::type;
		
	public:
		using S_::S_;
		
		XTAL_TO4_(template <size_t I>
		XTAL_FN2 self(XTAL_DEF... oo), self<sequent_t<I>>(XTAL_REF_(oo)...)
		)		
		XTAL_TO4_(template <size_t I>
		XTAL_FN2 head(XTAL_DEF... oo), head<sequent_t<I>>(XTAL_REF_(oo)...)
		)		

		XTAL_TO4_(template <typename ...Is>
		XTAL_FN2 self(XTAL_DEF... oo), S_::template self<super_t<T_, Is...>>(XTAL_REF_(oo)...)
		)
		XTAL_TO4_(template <typename ...Is>
		XTAL_FN2 head(XTAL_DEF... oo), S_::template self<super_t<S_, Is...>>().head(XTAL_REF_(oo)...)
		)

	};
};

}///////////////////////////////////////////////////////////////////////////////

#include "./_detail.hxx"


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
