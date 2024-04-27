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
	,	_retail::define<T>
	>;
	
	template <class S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;

	protected:
		using typename S_::T_self;
		using U_self = subtype;

	public:
		template <class _, class ...Is>
		using super = typename _detail::query<S_, U_self>::type::template super<_, Is...>;

		XTAL_TN0 head() XTAL_0EX {}
		XTAL_TN0 head() XTAL_0FX {}

	public:
		using S_::S_;
	//	using S_::self;

		template <typename ...Is>
		using self_s = typename super<T_self, Is...>::type;

		XTAL_TO4_(
		XTAL_TN2 self(), S_::self()
		)
		XTAL_TO4_(template <fungible_q<subtype> X=T>
		XTAL_TN2 self(), S_::template self<X>()
		)
		///<\returns `this` as `T`, or `fungible_q<subtype>`. \
		
		
		XTAL_DO4_(template <typename ...Is>
		XTAL_TN2 self(auto &&...oo),
		{
			using X = typename super<T, Is...>::type;
			if constexpr (0 == sizeof...(oo)) {
				return S_::template self<X>();
			}
			else {
				return S_::template self<X>() = X(XTAL_REF_(oo)..., XTAL_MOV_(self()));
			}
		})
		///<\returns `this` indexed by `Is...`, \
		emplacing the matching part of `self` if arguments are supplied. \

		//\
		Trivial (in)equality. \
		
		XTAL_OP2_(bool) == (subtype const &t) XTAL_0FX {return true;}
		XTAL_OP2_(bool) != (subtype const &t) XTAL_0FX {return not self().operator==(t.self());}
		XTAL_OP2 <=> (subtype const &t)
		XTAL_0FX
		{
			using is = _std::partial_ordering;
			return self().operator==(t.self())? is::equivalent: is::unordered;
		}

		XTAL_TN2 pack()
		XTAL_0FX
		{
		//	static_assert(sizeof(S_) == sizeof(bond::pack_f()));
			return bond::pack_f();
		}
		///<\returns a tuple representation of `this`. \

		using arity = cardinal_0;
		///< The `std::tuple_size` of `this`. \

	};
};
///\
Finalizes `T` via CRTP e.g. applying `std::view_interface`, \
binding `subtype` as the default target of `self`. \

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
	template <any_q S> requires iterable_q<S>
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
	using subkind = bond::compose<bond::tab<U>, _detail::defer_field<U>>;

	template <any_q S>
	using epitype = XTAL_TYP_(XTAL_ANY_(bond::compose_s<S, subkind>).head());

	template <any_q S>
	class subtype : public bond::compose_s<S, subkind, _detail::query<S, subtype<S>, epitype<S>>>
	{
		using S_ = bond::compose_s<S, subkind, _detail::query<S, subtype<S>, epitype<S>>>;
		using H_ = XTAL_TYP_(XTAL_ANY_(S_).head());

	protected:
		using typename S_::T_self;
		using U_self = subtype;

	public:
		using S_::self;
		using S_::head;

	public:
		using S_::S_;

		///\
		Converts `this` to the base-type (explicit). \

		XTAL_TO4_(XTAL_OP1_(explicit) H_(), head())

		///\
		\returns `true` if the supplied body matches `head`, `false` otherwise. \

		XTAL_TN2_(bool) heading(H_ const &w)
		XTAL_0FX
		{
			return equivalent_f(head(), w);
		}
		
		///\
		\returns `true` if the supplied body matches `this`, `false` otherwise. \

		XTAL_OP2_(bool) == (subtype const &t)
		XTAL_0FX
		{
			return heading(t.head()) and S_::template self<1>() == t;
		}

		///\
		Tuple arity. \

		using arity = cardinal_t<S_::arity::value + 1>;
		///\
		Tuple application. \

		XTAL_TN2 apply(auto &&f)// TODO: Require `std::invocable`.
		XTAL_0FX
		{
			return [this, f = XTAL_REF_(f)] <size_t ...I>(bond::seek_t<I...>)
				XTAL_0FN_(f(S_::template head<I>()...)) (bond::seek_s<arity::value> {});
		}
		template <class F>
		XTAL_TN2 make()
		XTAL_0EX {return apply([] XTAL_1FN_(F));}

		///\
		Tuple conversion (via `make`). \

		XTAL_TN2 pack()
		XTAL_0FX
		{
			return apply(bond::pack_f);
		}
		XTAL_FN2 pack(XTAL_TYP_(XTAL_ANY_(S_).pack()) const &tuple)
		XTAL_0EX
		{
			return _std::apply([] XTAL_1FN_(S_), tuple);
		}

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

template <any_q W> XTAL_OP2 == (W const &x, W const &y) XTAL_0EX {return x.self().operator== (y.self());}
template <any_q W> XTAL_OP2 != (W const &x, W const &y) XTAL_0EX {return x.self().operator!= (y.self());}
template <any_q W> XTAL_OP2 <=>(W const &x, W const &y) XTAL_0EX {return x.self().operator<=>(y.self());}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////

namespace xtal
{////////////////////////////////////////////////////////////////////////////

template <size_t N> XTAL_TN1 get(cell::any_q auto const &&t) {return _std::move(t).template head<N>();};
template <size_t N> XTAL_TN1 get(cell::any_q auto       &&t) {return _std::move(t).template head<N>();};
template <size_t N> XTAL_TN1 get(cell::any_q auto const  &t) {return             t.template head<N>();};
template <size_t N> XTAL_TN1 get(cell::any_q auto        &t) {return             t.template head<N>();};


}//////////////////////////////////////////////////////////////////////////
namespace std
{////////////////////////////////////////////////////////////////////////////

template <xtal::cell::any_q T>
struct tuple_size<T> : xtal::cardinal_t<T::arity::value> {};

template <size_t N, xtal::cell::any_q T>
struct tuple_element<N, T> {using type = XTAL_TYP_(XTAL_ANY_(T).template head<N>());};


}//////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
