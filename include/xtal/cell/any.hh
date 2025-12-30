#pragma once
#include "../bond.hh"
#include "../bond/any.hh"// `_retail`





XTAL_ENV_(push)
namespace xtal::cell
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

namespace _retail = xtal::bond;
#include "./_entail.ii"
#include "./_detail.ii"
/*
The following `subtype` decorators are specialized under each `xtal::*` namespace.
They provide instance and proxy initialization/finalization for the generated types in `./any.hxx`.
*/
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/*!
\brief   Extends `bond::define` with decorator-lineage traversal.
*/
template <class T>
struct define
{
	using superkind = bond::compose<void
	,	_detail::define_super<T>
	>;
	template <class S>
	class subtype : public bond::compose_s<S, superkind, _detail::navigate<subtype<S>>>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind, _detail::navigate<subtype<S>>>;

	public:// CONSTRUCT
		using S_::S_;
	
	public:// OPERATE
		using S_::self;

		/*!
		\returns	`true` (when vacant).
		*/
		XTAL_DEF_(return,inline,let)
		operator == (subtype const &t) const
		noexcept -> bool
		{
			return true;
		}

		XTAL_DEF_(return,inline,let) operator << (auto &&t1) const noexcept -> auto {return bond::pack_f(self(), XTAL_REF_(t1));}
		XTAL_DEF_(return,inline,let) operator >> (auto &&t0) const noexcept -> auto {return bond::pack_f(XTAL_REF_(t0), self());}

		XTAL_DEF_(return,inline,met) operator << (bond::tupack_q auto &&t0, subtype      &&s1) noexcept -> auto {return bond::repack_f(XTAL_REF_(t0), bond::pack_f(XTAL_MOV_(s1)));}
		XTAL_DEF_(return,inline,met) operator << (bond::tupack_q auto &&t0, subtype const &s1) noexcept -> auto {return bond::repack_f(XTAL_REF_(t0), bond::pack_f(XTAL_REF_(s1)));}
		XTAL_DEF_(return,inline,met) operator >> (bond::tupack_q auto &&t1, subtype      &&s0) noexcept -> auto {return bond::repack_f(bond::pack_f(XTAL_MOV_(s0)), XTAL_REF_(t1));}
		XTAL_DEF_(return,inline,met) operator >> (bond::tupack_q auto &&t1, subtype const &s0) noexcept -> auto {return bond::repack_f(bond::pack_f(XTAL_REF_(s0)), XTAL_REF_(t1));}

		XTAL_DEF_(return,inline,let)
		then(any_q auto &&...oo) const
		noexcept -> auto
		{
			//\
			return S_::self() << flow::packet_f(XTAL_REF_(oo)...);
			return (S_::self() <<...<< XTAL_REF_(oo));
		}

	};
};
/*!
\brief   Extends `bond::refine` by finalizing `tuple` and `range` interfaces.

Applies `ranges::view_interface` if `begin` and `end` have been defined.
Uses `std::initializer_list` construction if permitted by the `head_type`.
*/
template <class T>
struct refine
{
	using superkind = bond::compose<void
	,	_detail::refine_head<T>
	,	_detail::refine_tuple<T>
	>;

	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind>;
	
	public:
		using S_::S_;

	};
	template <class S> requires iterable_q<S> and un_v<iterated_q<S>> and incomplete_q<typename S::head_type>
	class subtype<S> : public bond::compose_s<S, superkind>, public _xtd::ranges::view_interface<T>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind>;

	public:
		using S_::S_;

	};
	template <class S> requires iterable_q<S> and un_v<iterated_q<S>> and   complete_q<typename S::head_type>
	class subtype<S> : public bond::compose_s<S, superkind>, public _xtd::ranges::view_interface<T>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind>;
		using W_ = typename S_::head_type;
		using U_ = initializer_t<W_>;

	public:
		using S_::S_;

		XTAL_NEW_(implicit)
		subtype(_std::initializer_list<U_> u_)
		noexcept requires make_p<W_, _std::initializer_list<U_>>
		:	S_{W_(u_)}
		{}

	};
};


///////////////////////////////////////////////////////////////////////////////
/*!
\brief   Extends `bond::defer` with decorator-lineage traversal and equality/comparison.

Mutable `lvalue`s are converted to pointers,
providing a similar utility as `std::reference_wrapper`.
*/
template <class U>
struct defer
{
	using superkind = _detail::defer_field<U>;

	template <class S>
	class subtype : public bond::compose_s<S, superkind, _detail::navigate<subtype<S>>>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind, _detail::navigate<subtype<S>>>;
		using U_ = typename S_::head_type;

	public:// CONSTRUCT
		using S_::S_;

	public:// OPERATE
		using S_::self;
		using S_::head;

		/*!
		\brief  	Converts `this` to the base-type (explicit).
		*/
		XTAL_FN0_(go) (XTAL_DEF_(return,inline,explicit) operator U_,
			[] (auto &&o) XTAL_0FN_(to) (XTAL_REF_(o).head()))

		/*!
		\returns	`1` if the supplied value matches `self`, `0` otherwise.
		*/
		XTAL_DEF_(return,inline,let)
		heading(auto &&o) const
		noexcept -> bool
		{
			return S_::heading(XTAL_REF_(o));
		}
		/*!
		\returns	`1` if the supplied value matches `head`, `0` otherwise.
		*/
		XTAL_DEF_(return,inline,let)
		heading(same_q<U_> auto &&o) const
		noexcept -> bool
		{
			return equivalent_f(head(), XTAL_REF_(o));
		}
		
		/*!
		\returns	`true` if the supplied body matches `this`, `false` otherwise.
		*/
		XTAL_DEF_(return,inline,let)
		operator == (subtype const &t) const
		noexcept -> bool
		{
			return equivalent_f(S_::head(), t.head()) and
				S_::template self<constant_t<1>>() == t.template self<constant_t<1>>();
		}

		/*!
		\brief  	Defines the current arity as a `constant_t`.
		*/
		using pack_size = succedent_s<typename S_::pack_size>;

	};
};
/*!
\brief   Extends `bond::refer` by lifting the operators that apply to `U`.
*/
template <class U>
struct refer : bond::compose<void
,	_detail::refer_logics<U>
,	_detail::refer_groups<U>
,	_detail::refer_qualities<U>
,	_detail::refer_iterators<U>
>
{};


////////////////////////////////////////////////////////////////////////////////

/*!
\brief   Forces equality resolution via the member `operator==`.
*/
template <any_q X, any_q Y> requires same_q<X, Y>
XTAL_DEF_(return,inline,let)
operator == (X const &x, Y const &y)
noexcept -> bool
{
	auto const &s = x.self();
	auto const &t = y.self();
	return s.operator==(t);
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////


#ifndef XTAL_DOC
namespace std
{////////////////////////////////////////////////////////////////////////////

template <xtal::cell::any_q T>
struct tuple_size<T> : T::pack_size {};

template <size_t N, xtal::cell::any_q T>
struct tuple_element<N, T> {using type = typename T::template head_t<integral_constant<size_t, N>>;};


}//////////////////////////////////////////////////////////////////////////
#endif
XTAL_ENV_(pop)
