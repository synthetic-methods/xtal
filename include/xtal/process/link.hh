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
template <typename ..._s> concept  link_q = bond::tag_in_p<link, _s...>;


namespace _detail
{///////////////////////////////////////////////////////////////////////////////

template <class U>
struct linker
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

		template <auto ...Is>
		XTAL_DEF_(return,inline,set) S_method_f(auto &&...xs)
		noexcept -> decltype(auto)
		requires XTAL_TRY_(to)
			(S_::template method_f<Is...>(S::template method_f<Is...>(XTAL_REF_(xs)...)))

	public:// CONSTRUCT
		using S_::S_;

	public:// OPERATE
		/*!
		\brief  	Resolves `head` as either a function or value,
		composed with the inherited `method` if the parent is a `defer`red `process`.
		*/
		template <auto ...Is>
		XTAL_DEF_(return,inline,set)
		method_f(auto &&...xs)
		noexcept -> decltype(auto)
		requires XTAL_TRY_(to)
			(S_method_f<Is...>(XTAL_REF_(xs)...))

		template <auto ...Is>
		XTAL_DEF_(return,inline,set)
		method(auto &&...xs)
		noexcept -> decltype(auto)
		requires XTAL_TRY_(to)
			(S_method_f<Is...>(XTAL_REF_(xs)...))

		XTAL_FX2_(do) (template <auto ...Is>
		XTAL_DEF_(return,inline,let)
		method(auto &&...xs),
		noexcept -> decltype(auto)
		requires XTAL_TRY_(unless) (S_method_f<Is...>(XTAL_REF_(xs)...))
		{
			return S_::template method<Is...>(S::template method<Is...>(XTAL_REF_(xs)...));
		})

	};
};



}///////////////////////////////////////////////////////////////////////////////

template <typename     ...As> struct link    : bond::compose<link<As>...                                    > {};
template <   incomplete_q A > struct link<A> : bond::compose<                                               > {};
template <bond::compose_q A > struct link<A> : bond::compose<_detail::linker<confined_t<A>>, bond::tag<link>> {};
template <class           U > struct link<U> : bond::compose<_detail::linker<           U >, bond::tag<link>> {};


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
