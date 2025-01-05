#pragma once
#include "../bond/all.hh"// `_retail`






XTAL_ENV_(push)
namespace xtal::cell
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

#include "./_retail.ii"
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
	class subtype : public bond::compose_s<S, superkind, _detail::query<subtype<S>>>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind, _detail::query<subtype<S>>>;

		XTAL_DEF_(short)
		XTAL_LET equal_to_(subtype const &t) const
		noexcept -> bool
		{
			return self().operator==(t.self());
		}

	public:
		using S_::S_;
		using S_::self;

		//\
		Trivial (in)equality. \
		
		XTAL_DEF_(short)
		XTAL_LET operator == (subtype const &t) const
		noexcept -> bool
		{
			return true;
		}
		XTAL_DEF_(short)
		XTAL_LET operator != (subtype const &t) const
		noexcept -> bool
		{
			return not equal_to_(t);
		}
		XTAL_DEF_(short)
		XTAL_LET operator <=> (subtype const &t) const
		{
			using is = _std::partial_ordering;
			return equal_to_(t)? is::equivalent: is::unordered;
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
	class subtype : public bond::compose_s<S, superkind, _detail::query<subtype<S>>>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind, _detail::query<subtype<S>>>;
		using U_ = typename S_::head_type;

	public:
		using S_::self;
		using S_::head;

	public:
		using S_::S_;

		///\
		Converts `this` to the base-type (explicit). \

		XTAL_TO4_(XTAL_DEF_(explicit operator) U_(), head())

		///\
		\returns `true` if the supplied body matches `head`, `false` otherwise. \

		XTAL_DEF_(short)
		XTAL_LET heading(auto &&o) const
		noexcept -> bool
		{
			return equivalent_f(head(), XTAL_REF_(o));
		}
		
		///\
		\returns `true` if the supplied body matches `this`, `false` otherwise. \

		XTAL_DEF_(short)
		XTAL_LET operator == (subtype const &t) const
		noexcept -> bool
		{
			return heading(t.head()) and S_::template self<1>() == t;
		}

		///\
		Tuple arity. \

		using pack_size = constant_t<S_::pack_size::value + 1>;

	};
};
///\
Defers selected operators to `U` as required for `refine`ment. \

template <class U>
struct refer : bond::compose<void
,	_detail::infer_logics<U>
,	_detail::infer_groups<U>
,	_detail::infer_iterators<U>
,	_detail::infer_qualities<U>
>
{};


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <any_q W> XTAL_DEF_(short) XTAL_LET operator == (W const &x, W const &y) noexcept -> bool {return x.self().operator== (y.self());}
template <any_q W> XTAL_DEF_(short) XTAL_LET operator != (W const &x, W const &y) noexcept -> bool {return x.self().operator!= (y.self());}
template <any_q W> XTAL_DEF_(short) XTAL_LET operator <=>(W const &x, W const &y) noexcept -> auto {return x.self().operator<=>(y.self());}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////

XTAL_DEF_(let) operator << (xtal::cell::any_q auto &&x0, auto &&x1) noexcept {return xtal::bond::pack_f(XTAL_REF_(x0), XTAL_REF_(x1));}
XTAL_DEF_(let) operator >> (xtal::cell::any_q auto &&x1, auto &&x0) noexcept {return xtal::bond::pack_f(XTAL_REF_(x0), XTAL_REF_(x1));}

XTAL_DEF_(let) operator << (xtal::bond::heteropack_q auto &&x0, xtal::cell::any_q auto &&x1) noexcept {return xtal::bond::repack_f(XTAL_REF_(x0), xtal::bond::pack_f(XTAL_REF_(x1)));}
XTAL_DEF_(let) operator >> (xtal::bond::heteropack_q auto &&x1, xtal::cell::any_q auto &&x0) noexcept {return xtal::bond::repack_f(xtal::bond::pack_f(XTAL_REF_(x0)), XTAL_REF_(x1));}


namespace std
{////////////////////////////////////////////////////////////////////////////

template <xtal::cell::any_q T> requires xtal::complete_q<typename T::node_type>
struct tuple_size<T> : T::node_type::pack_size {};

template <size_t N, xtal::cell::any_q T> requires xtal::complete_q<typename T::node_type>
struct tuple_element<N, T> {using type = typename T::node_type::template head_t<integral_constant<size_t, N>>;};


}//////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
