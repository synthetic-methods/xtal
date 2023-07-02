#pragma once
#include "../process/any.hpp"// `_retail`

#include "../control/sequel.hpp"
#include "../control/resize.hpp"



XTAL_ENV_(push)
namespace xtal::processor
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

namespace _retail = xtal::process;
#include "../concord/any.hxx"


namespace _detail
{///////////////////////////////////////////////////////////////////////////////

template <typename T, typename Y=T>
concept connected_p = any_p<T> and requires (T t)
{
	{t.serve()} -> isomorphic_q<Y>;
};
template <typename T, typename Y=T>
concept collected_p = any_p<T> and requires (T t)
{
	{t.serve()} -> isomorphic_q<Y>;
	{t.store()} -> isomorphic_q<Y>;
};
template <typename T, typename Y>
concept recollected_p = collected_p<T, Y> and _std::is_rvalue_reference_v<T>;


template <int code=0>   struct iterate_access;
template <          >   struct iterate_access<0> {XTAL_LET category = _v3::ranges::category::random_access;};
template <          >   struct iterate_access<1> {XTAL_LET category = _v3::ranges::category::forward;};
template <int code=0>
XTAL_CN2 iterate_access_f(XTAL_DEF z)
XTAL_0EX
{
	using namespace _v3::ranges;
	using  Z = any_view<iteratee_t<XTAL_TYP_(z)>, iterate_access<code>::category>;
	return Z(XTAL_REF_(z));
}
template <int code=0>
XTAL_CN2 iterate_access_f(XTAL_DEF z)
XTAL_0EX
XTAL_REQ_(z.size())
{
	using namespace _v3::ranges;
	using  Z = any_view<iteratee_t<XTAL_TYP_(z)>, iterate_access<code>::category|category::sized>;
	return Z(XTAL_REF_(z))|_v3::views::take(z.size());
}

XTAL_LET iterate_function_f = [] (XTAL_DEF f)
XTAL_0FN_([g = XTAL_REF_(f)] (XTAL_DEF ...xs)
XTAL_0FN
{
	using namespace _v3::views;
	if constexpr (0 == sizeof...(xs)) {
		return iota(0)|transform([=] (XTAL_DEF) XTAL_0FN_(g(XTAL_REF_(xs)...)));
//		return generate(XTAL_MOV_(g));// FIXME?
	}
	else if constexpr (1 == sizeof...(xs)) {
		return transform(XTAL_REF_(xs)..., g);
	}
	else if constexpr (1 <  sizeof...(xs)) {
		return zip_with(g, XTAL_REF_(xs)...);
	}
});


}///////////////////////////////////////////////////////////////////////////////

template <typename T>
struct define
:	_retail::define<T>
{
};
template <typename T>
struct refine
:	_retail::refine<T>
{
};


////////////////////////////////////////////////////////////////////////////////

template <typename U>
struct defer
:	defer<_retail::let_t<U>>
{
};
template <_retail::any_p U>
struct defer<U>
{
	using subkind = _retail::defer<U>;

	template <any_p S>
	class subtype: public compose_s<S, subkind>
	{
		using S_ = compose_s<S, subkind>;
		using U_ = U const &;

		template <typename ...Xs>
		XTAL_FN2 reified_()
		XTAL_0EX
		{
			return _detail::iterate_function_f(head().template reify<iteratee_t<Xs>...>());
		}

	public:
		using S_::S_;
		using S_::self;
		using S_::head;

		///\
		Defines the range-lifted form of `head` by `reify`ing the underlying `process`. \
		This means that parameter resolution is only performed at the beginning of each block. \
		\
		NOTE: Unless the underlying `process` is invocable as `const`, \
		it is assumed to be stateful, and iterator monotonicity is enforced.

		template <auto...>
		XTAL_FN2 method(XTAL_DEF ...xs)
		XTAL_0EX
		{
			return _detail::iterate_access_f<1>(reified_<decltype(xs)...>() (XTAL_REF_(xs)...));
		}
		template <auto...>
		XTAL_FN2 method(XTAL_DEF ...xs)
		XTAL_0EX
		XTAL_REQ_(XTAL_VAL_(U_).template method<>(XTAL_VAL_(iteratee_t<decltype(xs)>)...))
		{
		//	return _detail::iterate_access_f<0>(reified_<decltype(xs)...>() (XTAL_REF_(xs)...));
			return reified_<decltype(xs)...>() (XTAL_REF_(xs)...);
		}
		template <auto...>
		XTAL_FN2 method(XTAL_DEF ...xs)
		XTAL_0FX
		{
		//	return _detail::iterate_access_f<0>(reified_<decltype(xs)...>() (XTAL_REF_(xs)...));
			return reified_<decltype(xs)...>() (XTAL_REF_(xs)...);
		}

	};
};
template <iterated_q U> requires (not any_p<U>)
struct defer<U>
{
	using sequel_u = control::sequel_t<counted_t<>>;
	using subkind  = compose<_retail::defer<U>, sequel_u::attach>;

	template <any_p S>
	class subtype: public compose_s<S, subkind>
	{
		using S_ = compose_s<S, subkind>;
	
	public:
		using S_::S_;

		///\
		Deferred implementation of `T::value`. \

		template <auto...>
		XTAL_FN2 method()
		XTAL_0FX
		{
			using I = iteratee_t<sequel_u>; using _realized = realize<I>;
			auto const &v = S_::template method<>();
			auto const &m = S_::template get<sequel_u>();
		//	NOTE: Using `count_f` because `sizeof(m.size()) == sizeof(m::value_type) << 1`. \
		
			I const m_size = count_f(m);
			I const v_size = v.size();
			I const v_mask = v_size >> _realized::positive::depth;
			I i = m.front();
			I j = m_size + i;
			i &= ~v_mask;
			j &= ~v_mask;
			j |=  v_mask&v_size;
			return v|_v3::views::slice(i, j);
		}

		XTAL_FN2 begin()
		XTAL_0FX
		{
			return method<>().begin();
		}

		XTAL_FN2 end()
		XTAL_0FX
		{
			return method<>().end();
		}

	};
};
template <typename U>
struct refer
:	_retail::refer<U>
{
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
