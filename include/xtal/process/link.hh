#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::process
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/*!
\brief
Provides `method` composition by linking `head`s.

\details
Besides handling composition,
most of the work is done via `processor::defer`.
*/
template <typename ..._s> struct   link;
template <typename ..._s> using    link_t = confined_t<link<_s...>>;
template <typename ..._s> concept  link_q = bond::tag_inner_p<link, _s...>;


namespace _detail
{///////////////////////////////////////////////////////////////////////////////

template <class U>
struct linked
{
	using superkind = defer<U>;

	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind>;

	public:// CONSTRUCT
		using S_::S_;

	};
	template <class S> requires any_q<typename S::head_type>
	class subtype<S> : public bond::compose_s<S, superkind>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind>;
		using X_ = S ;
		using Y_ = S_;

	public:// CONSTRUCT
		using S_::S_;

	public:// OPERATE
		/*!
		\brief  	Resolves `head` as either a function or value,
		composed with the inherited `method` if the parent is a `defer`red `process`.
		*/
		template <auto ...Ns>
		XTAL_DEF_(return,inline,let)
		method(auto &&...oo) const
		noexcept -> decltype(auto)
		requires XTAL_TRY_(to_if) (XTAL_ANY_(Y_ const &).template method<Ns...>
		                          (XTAL_ANY_(X_ const &).template method<Ns...>(XTAL_REF_(oo)...)))
		{	return Y_::template method<Ns...>(X_       :: template method<Ns...>(XTAL_REF_(oo)...));
		}
		template <auto ...Ns>
		XTAL_DEF_(return,inline,let)
		method(auto &&...oo)
		noexcept -> decltype(auto)
		requires XTAL_TRY_(to_if) (XTAL_ANY_(Y_       &).template method<Ns...>
		                          (XTAL_ANY_(X_       &).template method<Ns...>(XTAL_REF_(oo)...)))
		{	return Y_::template method<Ns...>(X_       :: template method<Ns...>(XTAL_REF_(oo)...));
		}

	};
};



}///////////////////////////////////////////////////////////////////////////////

template <typename     ...As> struct link    : bond::compose<link<As>...                                    > {};
template <   incomplete_q A > struct link<A> : bond::compose<                                               > {};
template <bond::compose_q A > struct link<A> : bond::compose<_detail::linked<confined_t<A>>, bond::tag<link>> {};
template <class           U > struct link<U> : bond::compose<_detail::linked<           U >, bond::tag<link>> {};


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
