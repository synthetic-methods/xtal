#pragma once
#include "../common/all.hpp"// referenced in `any.hxx`




XTAL_ENV_(push)
namespace xtal::concord
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

namespace _retail::_detail {using namespace common::_detail;}
namespace _retail
{///////////////////////////////////////////////////////////////////////////////
///\
Creates a unique `subtype<S>` tagged by the given `As...`, \
such that e.g. `std::derives_from<any<struct x, struct xs...>, any<struct xs...>>`. \

template <typename ...As>
struct any
{
	using subkind = common::compose<any<As>...>;

	template <typename S>
	using subtype = typename subkind::template subtype<S>;

};
template <typename A>
struct any<A>
{
	template <typename S>
	class subtype: public S
	{
	public:
		using S::S;

	};
};


}///////////////////////////////////////////////////////////////////////////////

#include  "./any.hxx"
#include "./_detail.hxx"


////////////////////////////////////////////////////////////////////////////////

template <typename T>
struct define
{
	using subkind = common::deform<T>;
	
	template <any_p S>
	class subtype: public compose_s<S, subkind>
	{
		using S_ = compose_s<S, subkind>;

	public:
		using S_::S_;
		using S_::self;
		
		///\returns `this` as a subtype of the derived-type `T`. \

		template <typename Y=T>
		XTAL_FN1 self(XTAL_DEF... oo)
		XTAL_0EX
		XTAL_REQ (0 < sizeof...(oo))
		{
			auto &s = S_::self(); return s.template self<Y>() = Y(XTAL_REF_(oo)..., XTAL_MOV_(s));
		}
	
		template <typename   Y, typename X, constant_q _> struct super          {using type = Y;};
		template <              typename X, constant_q _> struct super<T, X, _> {using type = T;};
		template <              typename X, constant_q _> struct super<_, X, _> {using type = X;};
		template <constant_q Y, typename X, constant_q _> struct super<Y, X, _> {using type = typename S_::template super_t<shrink_t<Y>>;};
		template <typename Y=T> using super_t = typename super<Y, subtype, constant_0<size_t>>::type;

		XTAL_OP2       <=> (subtype const &t) XTAL_0FX {return _std::strong_ordering::equivalent;}
		XTAL_OP2_(bool) == (subtype const &t) XTAL_0FX {return 1;}///<\returns `true`.
		XTAL_OP2_(bool) != (subtype const &t) XTAL_0FX {return 0;}///<\returns `false`.

		XTAL_FN2 tuple() XTAL_0FX {return bundle_f();}
		using tuple_size = constant_0<size_t>;

//	protected:
		using self_t = T;

	};
};


////////////////////////////////////////////////////////////////////////////////

template <typename T>
struct refine
{
	using subkind = compose<void
	,	_detail::refine_head
	,	_detail::refine_tuple
	>;

	template <any_p S>
	class subtype: public compose_s<S, subkind>
	{
		using S_ = compose_s<S, subkind>;
	
	public:
		using S_::S_;

	};
	template <any_p S> requires iterable_q<S>
	class subtype<S>: public compose_s<S, subkind>, public iterate_t<T>
	{
		using S_ = compose_s<S, subkind>;
	
	public:
		using S_::S_;

	};
};


///////////////////////////////////////////////////////////////////////////////

template <typename U>
struct defer
{
	template <any_p S>
	class subtype: public compose_s<S>
	{
		using S_ = compose_s<S>;
		using T_ = typename S_::self_t;
		using V  = debased_t<U>;

	protected:
		template <typename   Y, typename X, constant_q _> struct super         : S_::template super<Y, X, _> {};
		template <              typename X, constant_q _> struct super<U, X, _>: S_::template super<X, X, _> {};
		template <              typename X, constant_q _> struct super<_, X, _>: S_::template super<X, X, _> {};
		template <constant_q Y, typename X, constant_q _> struct super<Y, X, _> {using type = typename S_::template super_t<shrink_t<Y>>;};
		template <typename Y=U> using super_t = typename super<Y, subtype, constant_0<size_t>>::type;

		V body_m;
	//	V body_m{};

	public:
	//	using S_::S_;
		using S_::self;
		using body_t = V;
		using head_t = U;

		XTAL_CO0_(subtype);
		XTAL_CO4_(subtype);

		///\
		Chaining constructor: initializes `this` using the first argument, \
		and forwards the rest to super. \

		XTAL_CON subtype()
		XTAL_0EX
		XTAL_REQ_(body_t{})
		:	subtype(body_t{})
		{}
		XTAL_CXN subtype(XTAL_DEF ...oo)
		XTAL_0EX
		XTAL_REQ constant_q<U>
		:	S_(XTAL_REF_(oo)...)
	//	,	subtype(body_t{})
		{}
		template <typename W> requires (not fungible_q<W, subtype>)
		XTAL_CXN subtype(W &&w, XTAL_DEF ...oo)
		XTAL_0EX
		XTAL_REQ variable_q<U> or is_q<U, W>
		:	S_(XTAL_REF_(oo)...)
		,	body_m(member_f<U>(XTAL_REF_(w)))
		{}

		XTAL_TO4_(template <typename W=T_> XTAL_FN2 self(), S_::template self<super_t<W>>())

		///\returns the kernel-value (prior to reconstruction using the given arguments, if provided). \

		XTAL_TO4_(template <size_t N_index=0>
		XTAL_FN1 head(XTAL_DEF... oo), self<constant_t<N_index>>().head(XTAL_REF_(oo)...)
		)
		XTAL_FN2 head() XTAL_0FX_(&&) {return remember_f(XTAL_MOV_(body_m));}
		XTAL_FN2 head() XTAL_0EX_(&&) {return remember_f(XTAL_MOV_(body_m));}
		XTAL_FN2 head() XTAL_0FX_( &) {return remember_f(body_m);}
		XTAL_FN2 head() XTAL_0EX_( &) {return remember_f(body_m);}
		
		XTAL_FN1 head(XTAL_DEF o, XTAL_DEF... oo)
		XTAL_0EX
		{
			return heady(member_f<U>(XTAL_REF_(o), XTAL_REF_(oo)...));
		}
		XTAL_FN1 heady(body_t v)
		XTAL_0EX
		XTAL_REQ remember_q<U>
		{
			_std::swap(body_m, v); return remember_f(XTAL_MOV_(v));
		}

		///\
		Converts `this` to the kernel-type (explicit). \

		XTAL_TO4_(XTAL_OP1_(explicit) U(), head())

		XTAL_FN2 apply(XTAL_DEF f)// TODO: Require `std::invocable`.
		XTAL_0FX
		{
			return [this, g = XTAL_REF_(f)] <size_t ...I>(seek_t<I...>)
				XTAL_0FN_(g(head<I>()...)) (seek_f<tuple_size::value> {});
		}
		
		XTAL_FN2 tuple()
		XTAL_0FX
		{
			return apply(bundle_f);
		}
		using tuple_size = constant_t<S_::tuple_size::value + 1>;
		
		///\
		Setter: applied when the template parameter matches the kernel-type. \
		\returns the previous value.

		template <typename W=U>
		XTAL_FN1 set(XTAL_DEF... ws)
		XTAL_0EX
		{
			return S_::template self<super_t<W>>().head(XTAL_REF_(ws)...);
		}
		///\
		Getter: applied when the template parameter matches the kernel-type. \
		\returns the current value.

		template <typename W=U>
		XTAL_FN2 get()
		XTAL_0FX
		{
			return S_::template self<super_t<W>>().head();
		}

		///\
		Membership testing. \
		\returns `true` if the supplied value matches `head`, `false` otherwise. \

		XTAL_FN2_(bool) has(U const &w)
		XTAL_0FX
		{
			U const &u = head();
			if constexpr (requires {u.operator==(w);}) {
				return u.operator==(w);
			}
			else if constexpr (requires {u == w;}) {
				return u == w;
			}
			else if constexpr (iterated_q<U>) {
				return u.begin() == w.begin() and u.end() == w.end();
			}
		}
		
		///\
		Equality testing. \
		\returns `true` if the supplied value matches `this`, `false` otherwise. \

		XTAL_OP2_(bool) == (subtype const &t)
		XTAL_0FX
		{
			return has(t.head()) and S_::operator==(static_cast<S_ const &>(t));
		}

	};
};
template <typename U>
struct refer: compose<void
,	_detail::refer_comparators<U>
,	_detail::refer_operators<U>
,	_detail::refer_iterators<U>
>
{};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
/**/
namespace std
{///////////////////////////////////////////////////////////////////////////////

template <xtal::concord::any_p T> requires (0 < T::tuple_size::value)
struct tuple_size<T>: xtal::constant_t<(size_t) T::tuple_size::value> {};

template <size_t N, xtal::concord::any_p T> requires (0 < T::tuple_size::value)
struct tuple_element<N, T> {using type = XTAL_TYP_(XTAL_VAL_(T).template head<N>());};

template <size_t N, xtal::concord::any_p T> requires (0 < T::tuple_size::value)
XTAL_FN1 get(T const &&t) {return std::move(t).template head<N>();};

template <size_t N, xtal::concord::any_p T> requires (0 < T::tuple_size::value)
XTAL_FN1 get(T       &&t) {return std::move(t).template head<N>();};

template <size_t N, xtal::concord::any_p T> requires (0 < T::tuple_size::value)
XTAL_FN1 get(T const  &t) {return t.template head<N>();};

template <size_t N, xtal::concord::any_p T> requires (0 < T::tuple_size::value)
XTAL_FN1 get(T        &t) {return t.template head<N>();};

}/////////////////////////////////////////////////////////////////////////////
/***/
XTAL_ENV_(pop)
