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


XTAL_USE scope = _v3::ranges::category;

template <auto N>
XTAL_CN2 scope_f(XTAL_DEF z)
XTAL_0EX
{
	return _v3::ranges::any_view<iteratee_t<XTAL_TYP_(z)>, N>(XTAL_REF_(z));
}
template <auto N>
XTAL_CN2 scope_f(XTAL_DEF z)
XTAL_0EX
XTAL_REQ  (N != (N|scope::sized)) and requires {z.size();}
{
	using namespace _v3::views;
	return scope_f<N|scope::sized>(XTAL_REF_(z))|take(z.size());
}

XTAL_LET zap_f = [] (XTAL_DEF f)
XTAL_0FN_([g = XTAL_REF_(f)] (XTAL_DEF ...xs)
XTAL_0FN
{
	using namespace _v3::views;
	if constexpr (0 == sizeof...(xs)) {
		return iota(0)|transform([=] (XTAL_DEF) XTAL_0FN_(g(XTAL_REF_(xs)...)));
	//	return generate(XTAL_MOV_(g));// FIXME?
	}
	else if constexpr (1 == sizeof...(xs)) {
		return transform(XTAL_REF_(xs)..., g);
	}
	else if constexpr (1 <  sizeof...(xs)) {
		return zip_with(g, XTAL_REF_(xs)...);
	}
});


template <typename T> concept      mundane_p = not any_q<T>;
template <typename T> concept preprocessed_p = mundane_p<T> and iterated_q<T>;


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
template <_detail::preprocessed_p U>
struct defer<U>
:	_retail::defer<U>
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

		XTAL_TO2_(template <typename ...Xs>
		XTAL_FN2 reified_(), _detail::zap_f(head().template reify<iteratee_t<Xs>...>())
		)

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

		template <typename ...Xs>
		XTAL_FN2 method(Xs &&...xs)
		XTAL_0EX
		{
			using namespace _detail;
			return scope_f<scope::forward>(reified_<Xs...>() (XTAL_REF_(xs)...));
		}
		template <typename ...Xs>
		XTAL_FN2 method(Xs &&...xs)
		XTAL_0EX
		XTAL_REQ_(XTAL_VAL_(U const &).method(XTAL_VAL_(iteratee_t<Xs>)...))
		{
			return reified_<Xs...>() (XTAL_REF_(xs)...);
		}
		template <typename ...Xs>
		XTAL_FN2 method(Xs &&...xs)
		XTAL_0FX
		{
			return reified_<Xs...>() (XTAL_REF_(xs)...);
		}

	};
};
template <typename U>
struct refer
{
	using sequel_u = control::sequel_t<counted_t<>>;
	using subkind  = _retail::refer<U>;

	template <any_p S>
	class subtype: public compose_s<S, subkind>
	{
		using S_ = compose_s<S, subkind>;
	
	public:
		using S_::S_;

	};
//	template <any_p S> XTAL_REQ_(XTAL_VAL_(compose_s<S, subkind>).method())
	template <any_p S> requires _detail::preprocessed_p<U> or numeric_operators_q<U>
	class subtype<S>: public compose_s<S, subkind, sequel_u::attach>
	{
		using S_ = compose_s<S, subkind, sequel_u::attach>;
	
	public:
		using S_::S_;

		using S_::method;
		///\
		Deferred implementation of `T::value`. \

		XTAL_DO2_(
		XTAL_FN2 method(),
		{
			using I = iteratee_t<sequel_u>; using _realized = realize<I>;
			auto const &m = S_::method();
			auto const &u = S_::template get<sequel_u>();
		//	NOTE: Using `count_f` because `sizeof(u.size()) == sizeof(u::value_type) << 1`. \
		
			I const u_size = count_f(u);
			I const m_size = count_f(m);
			I const m_mask = m_size >> _realized::positive::depth;
			I i = u.front();
			I j = u_size + i;
			i &= ~m_mask;
			j &= ~m_mask;
			j |=  m_mask&m_size;
			return m|_v3::views::slice(i, j);
		})

		XTAL_TO2_(XTAL_FN2 begin(), method().begin())
		XTAL_TO2_(XTAL_FN2   end(), method().  end())

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
