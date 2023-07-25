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
	using subtype = compose_s<S, subkind>;
	using    type = subtype<_detail::unitype>;
	
};
template <>
struct any<>
{	
	template <class S>
	class subtype: public S
	{
	public:
		using S::S;
		struct identity: unit_t {};

	protected:
		template <fungible_q ...Ys> struct super: terminal<Ys...> {};

	};
	template <class S> XTAL_REQ_(typename S::identity)
	class subtype<S>: public S
	{
	public:
		using S::S;

	};
	using type = subtype<_detail::unitype>;

};
template <typename A>
struct any<A>
{	
	template <class I> struct endo: I {};

	struct subkind
	{
		template <class S>
		class subtype: public compose_s<S, any<>>
		{
			using S_ = compose_s<S, any<>>;
			
		public:
			using S_::S_; using identity = endo<typename S_::identity>;

		};
	};
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
	using type = subtype<_detail::unitype>;

};

}///////////////////////////////////////////////////////////////////////////////

#include "./_detail.hxx"


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
