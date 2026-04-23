#pragma once
#include "./any.hh"

#include "./link.hh"




XTAL_ENV_(push)
namespace xtal::process::math
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/*!
\brief   Maps the first argument with `link_t<As...>`,
         passing the result and remaining arguments to the superclass.

\todo    Incorporate either argument-offset or arguments-list.
*/
template <typename ...As>
struct  left;


////////////////////////////////////////////////////////////////////////////////

template <typename ...As>
struct left
{
	using superkind = defer<link_t<As...>>;

	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		using S_ = bond::compose_s<S, superkind>;
		using Y_ = S ;
		using X_ = S_;

	public:// CONSTRUCT
		using S_::S_;

	public:// OPERATE

		template <auto ...Ns>
		XTAL_DEF_(return,inline,let)
		method(auto &&o, auto &&...oo) const
		noexcept -> decltype(auto)
		requires XTAL_TRY_(to_if) (XTAL_ANY_(Y_ const &).template method<Ns...>
		                          (XTAL_ANY_(X_ const &).template method<Ns...>(XTAL_REF_(o)), XTAL_REF_(oo)...))
		{	return Y_::template method<Ns...>(X_       :: template method<Ns...>(XTAL_REF_(o)), XTAL_REF_(oo)...);
		}
		template <auto ...Ns>
		XTAL_DEF_(return,inline,let)
		method(auto &&o, auto &&...oo)
		noexcept -> decltype(auto)
		requires XTAL_TRY_(to_if) (XTAL_ANY_(Y_       &).template method<Ns...>
		                          (XTAL_ANY_(X_       &).template method<Ns...>(XTAL_REF_(o)), XTAL_REF_(oo)...))
		{	return Y_::template method<Ns...>(X_       :: template method<Ns...>(XTAL_REF_(o)), XTAL_REF_(oo)...);
		}

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
