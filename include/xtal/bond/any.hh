#pragma once
#include "../any.hh"// `_retail`






XTAL_ENV_(push)
namespace xtal::bond
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

namespace _retail = xtal;
#include "./_entail.ii"
#include "./_detail.ii"


////////////////////////////////////////////////////////////////////////////////
///\
Creates a unique `subtype` tagged by the given `As...`, \
such that e.g. `std::derives_from<any<struct x, struct xs...>, any<struct xs...>>`. \

template <typename ...As>
struct any
{
	using superkind = _detail::excompose<any<As>...>;
	
	template <class S>
	using subtype = _detail::excompose_s<S, superkind>;
	
};
template <>
struct any<void>
{	
	template <class S>
	using subtype = S;

};
template <typename A>
struct any<A>
{	
	template <class S>
	class subtype : public _detail::excompose_s<S, _detail::query<subtype<S>, A>>
	{
		using S_ = _detail::excompose_s<S, _detail::query<subtype<S>, A>>;

	public:
		/**/
		using S_::S_;
		/*/
	~	subtype()                 noexcept=default;
		subtype()                 noexcept=default;
		XTAL_NEW_(copy) (subtype, noexcept=default)
		XTAL_NEW_(move) (subtype, noexcept=default)

		XTAL_NEW_(explicit) subtype(auto &&...oo)
		noexcept
		:	S_(XTAL_REF_(oo)...)
		{}
		XTAL_NEW_(explicit) subtype(fungible_q<subtype> auto &&o)
		noexcept
		:	subtype(static_cast<subtype &&>(XTAL_REF_(o)))
		{}
		///\
		Attempts construction from infungible-but-compatible types via inspection. \
		
		XTAL_NEW_(explicit) subtype(infungible_q<subtype> auto &&w, auto &&...oo)
		noexcept
		requires requires {typename W::template self_s<A>;}
		:	S_(w.template head<A>(), XTAL_REF_(w), XTAL_REF_(oo)...)
		{};
		/***/

	};
};


////////////////////////////////////////////////////////////////////////////////

template <class T>
struct define
{
	template <class S>
	class subtype : public S
	{
	public:// CONSTRUCT
		using S::S;

	public:
		///\returns `*this` with type `Y=T`. \

		template <fungible_q<subtype> Y=T> XTAL_DEF_(return,inline,let) self()       && noexcept -> decltype(auto) {return static_cast<Y       &&>(XTAL_MOV_(*this));}
		template <fungible_q<subtype> Y=T> XTAL_DEF_(return,inline,let) self() const && noexcept -> decltype(auto) {return static_cast<Y const &&>(XTAL_MOV_(*this));}
		template <fungible_q<subtype> Y=T> XTAL_DEF_(return,inline,let) self()        & noexcept -> decltype(auto) {return static_cast<Y        &>          (*this) ;}
		template <fungible_q<subtype> Y=T> XTAL_DEF_(return,inline,let) self() const  & noexcept -> decltype(auto) {return static_cast<Y const  &>          (*this) ;}

		///\returns a copy of `*this` with type `Y=T`. \

		template <fungible_q<subtype> Y=T>
		XTAL_DEF_(return,inline,let)
		twin() const
		noexcept -> decltype(auto)
		{
			return static_cast<Y>(self());
		}

		///\returns `this` as the `define`d supertype. \

		XTAL_FX4_(alias) (XTAL_DEF_(return,inline,get) tail(), self<S>())

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
