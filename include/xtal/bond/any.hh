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
		
	public:// CONSTRUCT
		using S_::S_;

		template <fungible_q<subtype> O>
		XTAL_CON_(explicit) subtype(O &&o)
		XTAL_0EX
		:	subtype(static_cast<subtype &&>(XTAL_REF_(o)))
		{}
		XTAL_CON_(explicit) subtype(auto &&...oo)
		XTAL_0EX
		:	S_(XTAL_REF_(oo)...)
		{}

	public:
		XTAL_DO4_(template <fungible_q<subtype> Y=T>
		XTAL_DEF_(return,inline)
		XTAL_LET self(auto &&...oo), -> decltype(auto)
		{
			auto  x = self<Y>();
			auto &y = self<Y>(); y.~ Y();
			return *new (&y) Y(XTAL_REF_(oo)..., XTAL_MOV_(x));
		})
		///\returns `*this` with type `Y=T`. \

		template <fungible_q<subtype> Y=T> XTAL_DEF_(return,inline) XTAL_LET self() XTAL_0FX_(&&) -> decltype(auto) {return static_cast<Y const &&>(XTAL_MOV_(*this));}
		template <fungible_q<subtype> Y=T> XTAL_DEF_(return,inline) XTAL_LET self() XTAL_0EX_(&&) -> decltype(auto) {return static_cast<Y       &&>(XTAL_MOV_(*this));}
		template <fungible_q<subtype> Y=T> XTAL_DEF_(return,inline) XTAL_LET self() XTAL_0FX_(&)  -> decltype(auto) {return static_cast<Y const  &>          (*this) ;}
		template <fungible_q<subtype> Y=T> XTAL_DEF_(return,inline) XTAL_LET self() XTAL_0EX_(&)  -> decltype(auto) {return static_cast<Y        &>          (*this) ;}
		
		///\returns a copy of `*this` with type `Y=T`. \

		template <fungible_q<subtype> Y=T>
		XTAL_DEF_(return,inline)
		XTAL_LET twin()
		XTAL_0FX -> decltype(auto)
		{
			return static_cast<Y>(self());
		}

		///\returns `this` as the `define`d supertype. \

		XTAL_TO4_(XTAL_DEF_(return,inline) XTAL_RET tail(), self<S>())


		template <typename ...Is>
		XTAL_USE head_t = void;
		XTAL_LET head() XTAL_0EX -> void {}
		XTAL_LET head() XTAL_0FX -> void {}


	};
	using type = subtype<unit_type>;

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
