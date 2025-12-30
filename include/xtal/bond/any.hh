#pragma once
//nclude "../bond.hh"
#include "../any.hh"// `_retail`





XTAL_ENV_(push)
namespace xtal::bond
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

namespace _retail = xtal;
#include "./_entail.ii"
#include "./_detail.ii"


////////////////////////////////////////////////////////////////////////////////
/*!
\brief
Creates a unique `subtype` tagged by the given `As...`.

\details
Maintains the invariant `std::derives_from<any<struct x, struct xs...>, any<struct xs...>>`.
*/
template <typename ...As>
struct any
{
	using superkind = _detail::excompose<any<As>...>;
	
	template <class S>
	using subtype = _detail::incompose_s<S, superkind>;
	
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
	class subtype : public _detail::incompose_s<S, _detail::navigate<subtype<S>, A>>
	{
		using S_ = _detail::incompose_s<S, _detail::navigate<subtype<S>, A>>;

	public:
		using S_::S_;

	};
};


////////////////////////////////////////////////////////////////////////////////

/*!
\brief   Establishes `self`-reflection and `twin`-creation.
*/
template <class T>
struct define
{
	template <class S>
	class subtype : public S
	{
	public:// CONSTRUCT
		using S::S;

		using self_type = T;
		using tail_type = S;
		using head_type = void;

	public:
		template <class Y=T>
		XTAL_DEF_(return,inline,set)
		self_f(auto &&o)
		noexcept -> decltype(auto)
		{
			return qualify_f<Y>(XTAL_REF_(o));
		}
		XTAL_FN1_(go) (template <class Y=T> XTAL_DEF_(return,inline,get) self, self_f<Y>)///<\returns	A reference to `*this` with type `Y=T`.
		XTAL_FN1_(go) (template <class Y=T> XTAL_DEF_(return,inline,let) twin, self_f<Y>)///<\returns	A copy      of `*this` with type `Y=T`.
		XTAL_FN1_(go) (                     XTAL_DEF_(return,inline,get) tail, self_f<S>)///<\returns	`this` as the `define`d supertype.

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
