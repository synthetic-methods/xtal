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
	using subkind = bond::compose<void
	,	_detail::define_super<T>
	>;
	template <class S>
	class subtype : public bond::compose_s<S, subkind, _detail::query<subtype<S>>>
	{
		using S_ = bond::compose_s<S, subkind, _detail::query<subtype<S>>>;

	protected:
		using typename S_::T_self;
		using U_self = subtype;

	public:
		using S_::S_;
		using S_::self;

		//\
		Trivial (in)equality. \
		
		XTAL_DEF_(return,inline) XTAL_LET operator ==  (subtype const &t) XTAL_0FX -> bool {return true;}
		XTAL_DEF_(return,inline) XTAL_LET operator !=  (subtype const &t) XTAL_0FX -> bool {return not self().operator==(t.self());}
		XTAL_DEF_(return,inline) XTAL_REF operator <=> (subtype const &t)
		XTAL_0FX
		{
			using is = _std::partial_ordering;
			return self().operator==(t.self())? is::equivalent: is::unordered;
		}

		XTAL_DEF_(return,inline)
		XTAL_LET pack()
		XTAL_0FX
		{
			return bond::pack_f();
		}
		///<\returns a tuple representation of `this`. \

		using pack_size = nominal_t<0>;
		///< The `std::tuple_size` of `this`. \

	};
};
///\
Finalizes `T` via CRTP e.g. applying `std::view_interface`, \
compound `subtype` as the default target of `self`. \

template <class T>
struct refine
{
	using subkind = bond::compose<void
	,	_detail::refine_head<T>
	,	_detail::refine_tuple<T>
	>;

	template <any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;
	
	public:
		using S_::S_;

	};
	template <any_q S> requires iterable_q<S> and uniterated_q<S>
	class subtype<S> : public bond::compose_s<S, subkind>, public initerated_t<T>
	{
		using S_ = bond::compose_s<S, subkind>;
	
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
	using subkind = _detail::defer_field<U>;

	template <any_q S>
	class subtype : public bond::compose_s<S, subkind, _detail::query<subtype<S>>>
	{
		using S_ = bond::compose_s<S, subkind, _detail::query<subtype<S>>>;

	protected:
		using typename S_::T_self;
		using typename S_::U_head;
		using U_self = subtype;

	public:
		using S_::self;
		using S_::head;

	public:
		using S_::S_;

		///\
		Converts `this` to the base-type (explicit). \

		XTAL_TO4_(XTAL_CVN_(explicit) U_head(), head())

		///\
		\returns `true` if the supplied body matches `head`, `false` otherwise. \

		XTAL_DEF_(return,inline)
		XTAL_LET heading(auto &&o)
		XTAL_0FX -> bool
		{
			return equivalent_f(head(), XTAL_REF_(o));
		}
		
		///\
		\returns `true` if the supplied body matches `this`, `false` otherwise. \

		XTAL_DEF_(return,inline)
		XTAL_LET operator == (subtype const &t)
		XTAL_0FX -> bool
		{
			return heading(t.head()) and S_::template self<1>() == t;
		}

		///\
		Tuple arity. \

		using pack_size = nominal_t<S_::pack_size::value + 1>;

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

template <any_q W> XTAL_DEF_(return,inline) XTAL_LET operator == (W const &x, W const &y) XTAL_0EX -> bool {return x.self().operator== (y.self());}
template <any_q W> XTAL_DEF_(return,inline) XTAL_LET operator != (W const &x, W const &y) XTAL_0EX -> bool {return x.self().operator!= (y.self());}
template <any_q W> XTAL_DEF_(return,inline) XTAL_REF operator <=>(W const &x, W const &y) XTAL_0EX         {return x.self().operator<=>(y.self());}


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
