#pragma once
#include "./any.hpp"






XTAL_ENV_(push)
namespace xtal::concord
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
The following `subtype` decorators are specialized under each `xtal::*` namespace. \
They provide instance and proxy initialization/finalization for the generated types in `./anybody.hxx`. \


////////////////////////////////////////////////////////////////////////////////
///\
Expands on the `self`-reflection established by `../common/_detail.hpp#epikind`, \
providing the mechanism for traversing the trait-lineage of `T`. \

template <class T>
struct define
{
	using subkind = _detail::epikind<T>;
	
	template <any_p S>
	class subtype: public compose_s<S, subkind>
	{
		using S_ = compose_s<S, subkind>;
		
	protected:
		using _ = void;
		
		template <class  X, typename ...Is> struct super: S_::template super<_, Is...> {};
		template <class  X, typename ...Is> struct super<X, _, Is...>: super<X, Is...> {};
		template <class  X, typename ...Is> struct super<X, T, Is...>: super<T, Is...> {};
		template <void_q X, typename ...Is> struct super<X,    Is...>: super<T, Is...> {};
		template <class  X                > struct super<X> {using type = X;};
		
	public:
		using S_::S_;
		using S_::self;
		///\
		Reassigns and returns the part of `self` that matches `X`. \

		template <typename ...Is>
		XTAL_FN2 self(XTAL_DEF... oo)
		XTAL_0EX
		XTAL_REQ (0 < sizeof...(oo))
		{
			auto &s = S_::self();
			using Y = typename super<T, Is...>::type;
			return s.template self<Y>() = Y(XTAL_REF_(oo)..., XTAL_MOV_(s));
		}
		//\
		Trivial (in)equality. \
		
		XTAL_OP2       <=> (subtype const &t) XTAL_0FX {return _std::strong_ordering::equivalent;}
		XTAL_OP2_(bool) == (subtype const &t) XTAL_0FX {return 1;}///<\returns `true`.
		XTAL_OP2_(bool) != (subtype const &t) XTAL_0FX {return 0;}///<\returns `false`.

		XTAL_FN2 tuple() XTAL_0FX {return bundle_f();}
		using tuple_size = constant_t<(size_t) 0>;

	};
};
///\
Finalizes `T` via CRTP e.g. applying `std::view_interface`, \
binding `subtype` as the default target of `self`. \

template <class T>
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
///\
Proxies the given `U` via `head`, \
providing chained/tupled construction/access. \

///\note\
Mutable `lvalue`s are converted to pointers, \
providing a similar level of utility to `std::reference_wrapper`. \

template <class U>
struct defer
{
	template <any_p S>
	class subtype: public compose_s<S>
	{
		using S_ = compose_s<S>;
		using T_ = typename S_::self_t;
		using V  = debased_t<U>;

	public:
	//	using S_::S_;
	//	using S_::self;
		using head_t = U;
		using body_t = V;

		body_t body_m;// NOTE: `public` access allows structural typing when `std::is_const_v`.

	//	XTAL_CO0_(subtype);
		XTAL_CO4_(subtype);
		
		XTAL_CON subtype()
		XTAL_0EX
		:	subtype(body_t{})
		{}
		
		///\
		Chaining constructor: initializes `this` using the first argument, \
		and forwards the rest to super. \

		XTAL_CXN subtype(XTAL_DEF ...oo)
		XTAL_0EX
		XTAL_REQ constant_q<U>
		:	S_(XTAL_REF_(oo)...)
	//	,	subtype(body_t{})
		{}
		template <class W> requires (not fungible_q<W, subtype>)
		XTAL_CXN subtype(W &&w, XTAL_DEF ...oo)
		XTAL_0EX
		XTAL_REQ variable_q<U> or is_q<U, W>
		:	S_(XTAL_REF_(oo)...)
		,	body_m(member_f<U>(XTAL_REF_(w)))
		{}

		///\
		Converts `this` to the base-type (explicit). \

		XTAL_TO4_(XTAL_OP1_(explicit) U(), head())

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
		XTAL_REQ remember_q<U>
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
		Accesses the `head`s as a `std::tuple`. \

		XTAL_USE tuple_size = constant_t<1 + S_::tuple_size::value>;
		XTAL_FN2 tuple()
		XTAL_0FX
		{
			return apply(bundle_f);
		}
		XTAL_FN2 apply(XTAL_DEF f)// TODO: Require `std::invocable`.
		XTAL_0FX
		{
			return [this, g = XTAL_REF_(f)] <size_t ...I>(seek_t<I...>)
				XTAL_0FN_(g(head<I>()...)) (seek_f<tuple_size::value> {});
		}

	protected:
		using Y = subtype;
		using O = constant_t<(size_t) 0>;
		///\
		Resolves the query/answer `X` w.r.t. the supplied context. \

		template <class  X, typename ...Is> struct super: S_::template super<X, Is...> {};
		template <class  X, typename ...Is> struct super<X, Y, Is...>: super<Y, Is...> {};
		template <class  X, typename ...Is> struct super<X, U, Is...>: super<Y, Is...> {};
		template <class  X, typename ...Is> struct super<X, O, Is...>: super<Y, Is...> {};
		template <void_q X, typename ...Is> struct super<X,    Is...>: super<Y, Is...> {};
		template <class  X, substant_q N, typename ...Is> struct super<X, N, Is...>: S_::template super<S_, substant_t<N>, Is...> {};

	public:
		///\returns `this` as specified by `Is...`. \
		
		XTAL_DO4_(template <typename ...Is>
		XTAL_FN2 self(XTAL_DEF... oo),
		{
			using X = typename super<T_, Is...>::type;
			return S_::template self<X>(XTAL_REF_(oo)...);
		})
		///\
		Setter applied when the template parameter matches the kernel-type. \

		///\returns the value of `head()` prior to `emplace`ment. \
		
		template <typename ...Is>
		XTAL_FN1 set(XTAL_DEF... oo)
		XTAL_0EX
		{
			return self<Is...>().head(XTAL_REF_(oo)...);
		}
		///\
		Getter applied when the template parameter matches the kernel-type. \
		
		///\returns the value of `head()`. \
		
		template <typename ...Is>
		XTAL_FN2 get()
		XTAL_0FX
		{
			return self<Is...>().head();
		}
		///\
		Membership testing. \
		\returns `true` if the supplied value matches `head`, `false` otherwise. \

		XTAL_FN2_(bool) has(U const &w)
		XTAL_0FX
		{
			return equivalent_f(head(), w);
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
///\
Defers selected operations to `U` as required for `refine`ment. \

template <class U>
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
