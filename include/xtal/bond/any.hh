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

		XTAL_CON_(explicit) subtype(auto &&...oo)
		XTAL_0EX
		:	S_(XTAL_REF_(oo)...)
		{}
		XTAL_CON_(explicit) subtype(fungible_q<S_> auto &&s, auto &&...oo)
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
		XTAL_DO4_(template <fungible_q<subtype> Y=T>
		XTAL_DEF_(return,inline)
		XTAL_REF self(auto &&...oo),
		XTAL_REQ (0 < sizeof...(oo))
		{
			auto &y = self<Y>();
			if constexpr (_std::is_trivially_destructible_v<Y>) {
				new (&y) Y(XTAL_REF_(oo)..., XTAL_MOV_(y));
			}
			else {
				auto x = self<Y>(); y.~Y();
				new (&y) Y(XTAL_REF_(oo)..., XTAL_MOV_(x));
			}
			return y;
		})
		///\returns `*this` with type `Y=T`. \

		template <fungible_q<subtype> Y=T> XTAL_DEF_(return,inline) XTAL_REF self() XTAL_0FX_(&&) {return static_cast<Y const &&>(XTAL_MOV_(*this));}
		template <fungible_q<subtype> Y=T> XTAL_DEF_(return,inline) XTAL_REF self() XTAL_0EX_(&&) {return static_cast<Y       &&>(XTAL_MOV_(*this));}
		template <fungible_q<subtype> Y=T> XTAL_DEF_(return,inline) XTAL_REF self() XTAL_0FX_(&)  {return static_cast<Y const  &>          (*this) ;}
		template <fungible_q<subtype> Y=T> XTAL_DEF_(return,inline) XTAL_REF self() XTAL_0EX_(&)  {return static_cast<Y        &>          (*this) ;}
		
		///\returns a copy of `*this` with type `Y=T`. \

		template <fungible_q<subtype> Y=T>
		XTAL_DEF_(return,inline)
		XTAL_REF twin() XTAL_0FX {return static_cast<Y>(self());}

		///\returns `this` as the `define`d supertype. \

		XTAL_TO4_(XTAL_DEF_(return,inline) XTAL_REF then(), self<S_>())

		template <typename ...Is>
		XTAL_USE head_t = void;
		XTAL_LET head() XTAL_0EX -> void {}
		XTAL_LET head() XTAL_0FX -> void {}


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
