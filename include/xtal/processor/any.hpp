#pragma once
#include "../process/any.hpp"// `_retail`

#include "../message/sequel.hpp"
#include "../message/resize.hpp"



XTAL_ENV_(push)
namespace xtal::processor
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

namespace _retail = xtal::process;
#include "../concord/any.hxx"


////////////////////////////////////////////////////////////////////////////////

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


namespace _detail
{///////////////////////////////////////////////////////////////////////////////

XTAL_FZ2 iterate_forward_f(XTAL_DEF z)
XTAL_0EX
{
	using namespace _v3::ranges;
	using  Z = any_view<iteratee_t<XTAL_TYP_(z)>, category::forward>;
	return Z(XTAL_REF_(z));
}
XTAL_FZ2 iterate_forward_f(XTAL_DEF z)
XTAL_0EX
XTAL_IF2 {z.size();}
{
	using namespace _v3::ranges;
	using  Z = any_view<iteratee_t<XTAL_TYP_(z)>, category::forward|category::sized>;
	return Z(XTAL_REF_(z))|_v3::views::take(z.size());
}
XTAL_LET iterate_function_f = [](XTAL_DEF f)
XTAL_0FN_([g = XTAL_REF_(f)](XTAL_DEF ...xs)
XTAL_0FN
{
	using namespace _v3::views;
	if constexpr (0 == sizeof...(xs))
	{	return iota(0)|transform([=](auto &&) XTAL_0FN_(g(XTAL_REF_(xs)...)));
//	{	return generate(_std::move(g));// FIXME?
	}
	else
	if constexpr (1 == sizeof...(xs))
	{	return transform(XTAL_REF_(xs)..., g);
	}
	else
	{	return zip_with(g, XTAL_REF_(xs)...);
	}
});


}///////////////////////////////////////////////////////////////////////////////

template <typename U>
struct defer
:	defer<_retail::let_t<U>>
{
};
template <_retail::any_q U>
struct defer<U>
{
	using subkind = _retail::defer<U>;

	template <any_q S>
	class subtype: public compose_s<S, subkind>
	{
		using co = compose_s<S, subkind>;

		template <typename ...Xs>
		XTAL_FN2 reified_()
		XTAL_0RN_(_detail::iterate_function_f(head().template reify<iteratee_t<Xs>...>()))

	public:
		using co::co;
		using co::self;
		using co::head;

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
			return _detail::iterate_forward_f(reified_<decltype(xs)...>() (XTAL_REF_(xs)...));
		}
		template <auto...>
		XTAL_FN2 method(XTAL_DEF ...xs)
		XTAL_0FX
		{
			return reified_<decltype(xs)...>() (XTAL_REF_(xs)...);
		}
		template <auto...>
		XTAL_FN2 method(XTAL_DEF ...xs)
		XTAL_0EX
		XTAL_IF2 (U const &u)
		{
			(void) u.template method<iteratee_t<decltype(xs)>...>(XTAL_REF_(xs)...);
		}
		{
			return reified_<decltype(xs)...>() (XTAL_REF_(xs)...);
		}

	};
};
template <iterated_q U> requires (not any_q<U>)
struct defer<U>
{
	using sequel_u = message::sequel_t<counted_t<>>;
	using subkind  = compose<_retail::defer<U>, sequel_u::attach>;

	template <any_q S>
	class subtype: public compose_s<S, subkind>
	{
		using co = compose_s<S, subkind>;
	
	public:
		using co::co;

		///\
		Deferred implementation of `T::value`. \

		template <auto...>
		XTAL_FN2 method()
		XTAL_0FX
		{
			using I = iteratee_t<sequel_u>; using _realized = realize<I>;
			auto const &v = co::template method<>();
			auto const &m = co::template get<sequel_u>();
			I const m_size = m.count();// `sizeof(m.size()) == sizeof(m::value_type) << 1`
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


////////////////////////////////////////////////////////////////////////////////

template <typename ...As>
struct link
{
	using resize_u  = message::resize_t<>;
	using sequel_u  = message::sequel_t<>;
	using subkind = _retail::link<As..., sequel_u::attach, resize_u::attach>;

	template <any_q S>
	using subtype = compose_s<S, subkind>;

};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
