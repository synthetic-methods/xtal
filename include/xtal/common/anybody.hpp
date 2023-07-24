#pragma once
#include "./any.hpp"






XTAL_ENV_(push)
namespace xtal::common
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <class T>
struct define
{
	template <class S>
	class subtype: public S
	{
		friend T;
		
	public:
		using S::S;

		XTAL_CXN subtype(XTAL_DEF ...oo)
		XTAL_0EX
		:	S(XTAL_REF_(oo)...)
		{}

		///\returns `this` as the `define`d supertype. \

		XTAL_TO4_(XTAL_FN2 core(), S::self())

		///\returns a copy of `*this` with type `Y=T`. \

		XTAL_TO2_(template <class Y=T> XTAL_FN2_(based_t<Y>) twin(), self<Y>())

		///\returns `*this` with type `Y=T`. \

		template <class Y=T> XTAL_FN2 self() XTAL_0FX_(&&) {return forge_f<Y const &&>(XTAL_MOV_(*this));}
		template <class Y=T> XTAL_FN2 self() XTAL_0EX_(&&) {return forge_f<Y       &&>(XTAL_MOV_(*this));}
		template <class Y=T> XTAL_FN2 self() XTAL_0FX_(&)  {return forge_f<Y const  &>(*this);}
		template <class Y=T> XTAL_FN2 self() XTAL_0EX_(&)  {return forge_f<Y        &>(*this);}

		using self_t = T;
		
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
