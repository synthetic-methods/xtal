#pragma once
#include "../any.hpp"






XTAL_ENV_(push)
namespace xtal::common
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

#include "./_detail.hxx"


////////////////////////////////////////////////////////////////////////////////

template <typename T>
struct deform
{
	template <typename S>
	class subtype: public S
	{
		friend T;
		
	public:
		using S::S;

		XTAL_CXN subtype(XTAL_DEF ...oo)
		XTAL_0EX
		:	S(XTAL_REF_(oo)...)
		{}

		///\returns `*this` with type `Y=T`. \

		template <typename Y=T> XTAL_FN2 self() XTAL_0FX_(&&) {return funge_f<Y const &&>(XTAL_MOV_(*this));}
		template <typename Y=T> XTAL_FN2 self() XTAL_0EX_(&&) {return funge_f<Y       &&>(XTAL_MOV_(*this));}
		template <typename Y=T> XTAL_FN2 self() XTAL_0FX_(&)  {return funge_f<Y const  &>(*this);}
		template <typename Y=T> XTAL_FN2 self() XTAL_0EX_(&)  {return funge_f<Y        &>(*this);}

		///\returns a copy of `*this` with type `Y=T`. \

		XTAL_TO2_(template <typename Y=T> XTAL_FN2_(based_t<Y>) twin(), self<Y>())

		///\returns `this` as the `define`d supertype. \

		XTAL_TO4_(XTAL_FN2 core(), S::self())

	};
};

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
