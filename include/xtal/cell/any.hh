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


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
///\
The following `subtype` decorators are specialized under each `xtal::*` namespace. \
They provide instance and proxy initialization/finalization for the generated types in `./any.hxx`. \


////////////////////////////////////////////////////////////////////////////////
///\
Expands on the `self`-reflection established by `../bond/any.ipp#define`, \
providing the mechanism for traversing the trait-lineage of `T`. \

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

		//\
		Trivial (`constexpr`) equality. \
		
		XTAL_DEF_(return,inline,let)
		operator == (subtype const &t) const
		noexcept -> bool
		{
			return true;
		}

		XTAL_DEF_(return,inline,let) operator << (auto &&t1) noexcept -> auto {return bond::pack_f(self(), XTAL_REF_(t1));}
		XTAL_DEF_(return,inline,let) operator >> (auto &&t0) noexcept -> auto {return bond::pack_f(XTAL_REF_(t0), self());}

		XTAL_DEF_(return,inline,met) operator << (bond::heteropack_q auto &&t0, subtype      &&s1) noexcept -> auto {return bond::repack_f(XTAL_REF_(t0), bond::pack_f(XTAL_MOV_(s1)));}
		XTAL_DEF_(return,inline,met) operator << (bond::heteropack_q auto &&t0, subtype const &s1) noexcept -> auto {return bond::repack_f(XTAL_REF_(t0), bond::pack_f(XTAL_REF_(s1)));}
		XTAL_DEF_(return,inline,met) operator >> (bond::heteropack_q auto &&t1, subtype      &&s0) noexcept -> auto {return bond::repack_f(bond::pack_f(XTAL_MOV_(s0)), XTAL_REF_(t1));}
		XTAL_DEF_(return,inline,met) operator >> (bond::heteropack_q auto &&t1, subtype const &s0) noexcept -> auto {return bond::repack_f(bond::pack_f(XTAL_REF_(s0)), XTAL_REF_(t1));}

		XTAL_DEF_(return,inline,let)
		then(any_q auto &&...oo)
		noexcept -> auto
		{
			//\
			return S_::self() << flow::packet_f(XTAL_REF_(oo)...);
			return (S_::self() <<...<< XTAL_REF_(oo));
		}

	};
};
///\
Finalizes `T` via CRTP e.g. applying `std::view_interface`, \
with `subtype` as the default target of `self`. \

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
	template <class S> requires iterable_q<S> and un_n<iterated_q<S>>
	class subtype<S> : public bond::compose_s<S, superkind>, public arranged_t<T>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind>;
	
	public:
		using S_::S_;

	};
};


///////////////////////////////////////////////////////////////////////////////
///\
Proxies the given `U` via `head`, \
providing chained/packed construction/access. \

///\note\
Mutable `lvalue`s are converted to pointers, \
providing a similar level of utility to `std::reference_wrapper`. \

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

		///\
		Converts `this` to the base-type (explicit). \

		XTAL_FX4_(to) (XTAL_DEF_(return,inline,explicit operator) U_(), head())

		///\
		\returns `true` if the supplied body matches `head`, `false` otherwise. \

		XTAL_DEF_(return,inline,let)
		heading(auto &&o) const
		noexcept -> bool
		{
			return S_::heading(XTAL_REF_(o));
		}
		XTAL_DEF_(return,inline,let)
		heading(same_q<U_> auto &&o) const
		noexcept -> bool
		{
			return equivalent_f(head(), XTAL_REF_(o));
		}
		
		///\
		\returns `true` if the supplied body matches `this`, `false` otherwise. \

		XTAL_DEF_(return,inline,let)
		operator == (subtype const &t) const
		noexcept -> bool
		{
			return equivalent_f(S_::head(), t.head()) and
				S_::template self<1>() == t.template self<1>();
		}

		///\
		Tuple arity. \

		using pack_size = succedent_s<typename S_::pack_size>;

	};
};
///\
Defers selected operators to `U` as required for `refine`ment. \

template <class U>
struct refer : bond::compose<void
,	_detail::refer_logics<U>
,	_detail::refer_groups<U>
,	_detail::refer_qualities<U>
,	_detail::refer_iterators<U>
>
{};


////////////////////////////////////////////////////////////////////////////////

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


namespace std
{////////////////////////////////////////////////////////////////////////////

template <xtal::cell::any_q T>
struct tuple_size<T> : T::pack_size {};

template <size_t N, xtal::cell::any_q T>
struct tuple_element<N, T> {using type = typename T::template head_t<integral_constant<size_t, N>>;};


}//////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
