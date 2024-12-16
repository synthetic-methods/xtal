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

		XTAL_NEW_(explicit) subtype(fungible_q<subtype> auto &&o)
		noexcept
		:	subtype(static_cast<subtype &&>(XTAL_REF_(o)))
		{}
		XTAL_NEW_(explicit) subtype(auto &&...oo)
		noexcept
		:	S_(XTAL_REF_(oo)...)
		{}

	public:
		XTAL_DO4_(template <fungible_q<subtype> Y=T>
		XTAL_DEF_(short)
		XTAL_LET self(auto &&...oo),
		noexcept -> decltype(auto)
		{
			auto  x = self<Y>();
			auto &y = self<Y>(); y.~ Y();
			return *new (&y) Y(XTAL_REF_(oo)..., XTAL_MOV_(x));
		})
		///\returns `*this` with type `Y=T`. \

		template <fungible_q<subtype> Y=T> XTAL_DEF_(alias) self()       && noexcept {return static_cast<Y       &&>(XTAL_MOV_(*this));}
		template <fungible_q<subtype> Y=T> XTAL_DEF_(alias) self() const && noexcept {return static_cast<Y const &&>(XTAL_MOV_(*this));}
		template <fungible_q<subtype> Y=T> XTAL_DEF_(alias) self()        & noexcept {return static_cast<Y        &>          (*this) ;}
		template <fungible_q<subtype> Y=T> XTAL_DEF_(alias) self() const  & noexcept {return static_cast<Y const  &>          (*this) ;}

		///\returns a copy of `*this` with type `Y=T`. \

		template <fungible_q<subtype> Y=T>
		XTAL_DEF_(short)
		XTAL_LET twin() const
		noexcept -> decltype(auto)
		{
			return static_cast<Y>(self());
		}

		///\returns `this` as the `define`d supertype. \

		XTAL_TO4_(XTAL_DEF_(alias) tail(), self<S>())


		template <typename ...Is>
		using    head_t = void;
		XTAL_LET head()       noexcept -> void {}
		XTAL_LET head() const noexcept -> void {}


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
