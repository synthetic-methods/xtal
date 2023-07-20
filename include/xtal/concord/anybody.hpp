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
Expands on the `self`-reflection established by `../common/_detail.hpp#epitype`, \
providing the mechanism for traversing the trait-lineage of `T`. \

template <typename T>
struct define
{
	using subkind = _detail::epitype<T>;
	
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
	
		template <typename   Y, typename X, constant_q W> struct super          {using type = Y;};
		template <              typename X, constant_q W> struct super<T, X, W> {using type = T;};
		template <              typename X, constant_q W> struct super<W, X, W> {using type = X;};
		template <constant_q Y, typename X, constant_q W> struct super<Y, X, W> {using type = typename S_::template super_t<substant_t<Y>>;};
		template <typename Y=T> using super_t = typename super<Y, subtype, constant_t<(size_t) 0>>::type;

		XTAL_OP2       <=> (subtype const &t) XTAL_0FX {return _std::strong_ordering::equivalent;}
		XTAL_OP2_(bool) == (subtype const &t) XTAL_0FX {return 1;}///<\returns `true`.
		XTAL_OP2_(bool) != (subtype const &t) XTAL_0FX {return 0;}///<\returns `false`.

		XTAL_FN2 tuple() XTAL_0FX {return bundle_f();}
		using tuple_size = constant_t<(size_t) 0>;

//	protected:
		using self_t = T;

	};
};
///\
Finalizes `T` via CRTP e.g. applying `std::view_interface`, \
binding `subtype` as the default target of `self`. \

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
///\
Proxies the given `U` via `head`, \
providing chained/tupled construction/access. \

///\note\
Mutable `lvalue`s are converted to pointers, \
providing a similar level of utility to `std::reference_wrapper`. \

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
		template <typename   Y, typename X, constant_q W> struct super         : S_::template super<Y, X, W> {};
		template <              typename X, constant_q W> struct super<U, X, W>: S_::template super<X, X, W> {};
		template <              typename X, constant_q W> struct super<W, X, W>: S_::template super<X, X, W> {};
		template <constant_q Y, typename X, constant_q W> struct super<Y, X, W> {using type = typename S_::template super_t<substant_t<Y>>;};
		template <typename Y=U> using super_t = typename super<Y, subtype, constant_t<(size_t) 0>>::type;

	public:
	//	using S_::S_;
		using S_::self;
		using head_t = U;
		using body_t = V;

// NOTE: Making `body_m` `public` permits structural typing when `std::is_const_v`. \
		body_t body_m{};
		body_t body_m;

		///\
		Default constructor. \

		XTAL_CO4_(subtype);
	//	XTAL_CO0_(subtype);
		
		XTAL_CON subtype()
		XTAL_0EX
	//	XTAL_REQ_(body_t{})// NOTE: Required for `MSVC`?
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
///\
Defers selected operations to `U` as required for `refine`ment. \

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
