#pragma once
#include "../any.hh"






XTAL_ENV_(push)
namespace xtal::bond
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

#include "./_detail.ii"


////////////////////////////////////////////////////////////////////////////////

template <class T>
struct define
{
	template <class S>
	class subtype : public S
	{
		friend T;
		using S_ = S;

	public:
		using S_::S_;

		XTAL_CXN subtype(auto &&...oo)
		XTAL_0EX
		:	S_(XTAL_REF_(oo)...)
		{}
		XTAL_CXN subtype(fungible_q<S_> auto &&s, auto &&...oo)
		XTAL_0EX
		:	S_(static_cast<S_ &&>(s), XTAL_REF_(oo)...)
		{}

	protected:
		using  T_self = T;
		using  U_self = subtype;
		struct U_tail
		{
			template <class _, typename ...Is> struct super    : super<Is...> {};
			template <class _                > struct super<_> {using type = _;};
		};

	public:
		template <class _, class ...Is>
		using super = typename _detail::query<U_tail, U_self>::type::template super<_, Is...>;

	public:
		template <class ...Is>
		using self_s = typename super<T_self, Is...>::type;

		///\returns `*this` with type `Y=T`. \

		template <class Y=T> XTAL_DEF_(return,inline) XTAL_TN1              self() XTAL_0FX_(&&) {return static_cast<Y const &&>(XTAL_MOV_(*this));}
		template <class Y=T> XTAL_DEF_(return,inline) XTAL_TN1              self() XTAL_0EX_(&&) {return static_cast<Y       &&>(XTAL_MOV_(*this));}
		template <class Y=T> XTAL_DEF_(return,inline) XTAL_TN1              self() XTAL_0FX_(&)  {return static_cast<Y const  &>          (*this) ;}
		template <class Y=T> XTAL_DEF_(return,inline) XTAL_TN1              self() XTAL_0EX_(&)  {return static_cast<Y        &>          (*this) ;}
		
		///\returns a copy of `*this` with type `Y=T`. \

		template <class Y=T> XTAL_DEF_(return,inline) XTAL_TN1              twin() XTAL_0FX_(&&) {return static_cast<Y const &&>(XTAL_MOV_(*this));}
		template <class Y=T> XTAL_DEF_(return,inline) XTAL_TN1              twin() XTAL_0EX_(&&) {return static_cast<Y       &&>(XTAL_MOV_(*this));}
		template <class Y=T> XTAL_DEF_(return,inline) XTAL_TN1_(based_t<Y>) twin() XTAL_0FX_(&)  {return static_cast<Y const  &>          (*this) ;}
		template <class Y=T> XTAL_DEF_(return,inline) XTAL_TN1_(based_t<Y>) twin() XTAL_0EX_(&)  {return static_cast<Y        &>          (*this) ;}

		///\returns `this` as the `define`d supertype. \

		XTAL_TO4_(XTAL_TN2 then(), self<S_>())

	};
	using type = subtype<unit_t>;

};
template <class T>
struct refine;


////////////////////////////////////////////////////////////////////////////////

template <class U>
struct defer;

template <class U>
struct refer;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
