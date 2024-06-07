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
		using S_ = S;

	public:
		using S_::S_;

		XTAL_CXN subtype(auto &&...oo)
		XTAL_0EX
		:	S_(XTAL_REF_(oo)...)
		{}
		XTAL_CXN subtype(fungible_q<S_> auto &&s, auto &&...oo)
		XTAL_0EX
		:	S_(static_cast<S_ &&>(XTAL_REF_(s)), XTAL_REF_(oo)...)
		{}

	protected:
		using  T_self = T; friend T_self;
		using  U_self = subtype;
		using  U_head = void;

	public:
		template <class _, typename ...Is> struct super    : super<Is...> {};
		template <class _                > struct super<_> {using type = _;};

	public:
		XTAL_DO4_(template <fungible_q<subtype> Y>
		XTAL_DEF_(return,inline)
		XTAL_TN1 self(auto &&...oo),
		XTAL_REQ (0 < sizeof...(oo))
		{
			return self<Y>() = Y(XTAL_REF_(oo)..., XTAL_MOV_(self()));
		})
		///\returns `*this` with type `Y=T`. \

		template <fungible_q<subtype> Y=T> XTAL_DEF_(return,inline) XTAL_TN1              self() XTAL_0FX_(&&) {return static_cast<Y const &&>(XTAL_MOV_(*this));}
		template <fungible_q<subtype> Y=T> XTAL_DEF_(return,inline) XTAL_TN1              self() XTAL_0EX_(&&) {return static_cast<Y       &&>(XTAL_MOV_(*this));}
		template <fungible_q<subtype> Y=T> XTAL_DEF_(return,inline) XTAL_TN1              self() XTAL_0FX_(&)  {return static_cast<Y const  &>          (*this) ;}
		template <fungible_q<subtype> Y=T> XTAL_DEF_(return,inline) XTAL_TN1              self() XTAL_0EX_(&)  {return static_cast<Y        &>          (*this) ;}
		
		///\returns a copy of `*this` with type `Y=T`. \

		template <fungible_q<subtype> Y=T> XTAL_DEF_(return,inline) XTAL_TN1              twin() XTAL_0FX_(&&) {return static_cast<Y const &&>(XTAL_MOV_(*this));}
		template <fungible_q<subtype> Y=T> XTAL_DEF_(return,inline) XTAL_TN1              twin() XTAL_0EX_(&&) {return static_cast<Y       &&>(XTAL_MOV_(*this));}
		template <fungible_q<subtype> Y=T> XTAL_DEF_(return,inline) XTAL_TN1_(based_t<Y>) twin() XTAL_0FX_(&)  {return static_cast<Y const  &>          (*this) ;}
		template <fungible_q<subtype> Y=T> XTAL_DEF_(return,inline) XTAL_TN1_(based_t<Y>) twin() XTAL_0EX_(&)  {return static_cast<Y        &>          (*this) ;}

		///\returns `this` as the `define`d supertype. \

		XTAL_TO4_(XTAL_TN2 then(), self<S_>())

		template <typename ...Is>
		XTAL_USE head_t = void;
		XTAL_TN0 head() XTAL_0EX {}
		XTAL_TN0 head() XTAL_0FX {}


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
