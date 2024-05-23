#pragma once
#include "../process/any.hh"// `_retail`






XTAL_ENV_(push)
namespace xtal::processor
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

#include "./_retail.ii"
#include "./_detail.ii"


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <class T>
struct define
:	_retail::define<T>
{
};
template <class T>
struct refine
:	_retail::refine<T>
{
};


////////////////////////////////////////////////////////////////////////////////

template <class U>
struct defer
:	defer<_retail::let_t<U>>
{
};
template <iterated_q U>
struct defer<U>
:	_retail::defer<U>
{
};
template <_detail::unprocessed_q U>
struct defer<U>
:	defer<_v3::ranges::repeat_view<U>>
{
};
template <_detail::reprocessed_q U>
struct defer<U>
{
	using subkind = _retail::defer<U>;

	template <any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;

	public:
		using S_::S_;
		using S_::self;
		using S_::head;

		///\
		Defines the range-lifted form of `head` by `lift`ing the underlying `process`. \
		This means that parameter resolution is only performed at the beginning of each block. \
		\
		NOTE: Unless the underlying `process` is invocable as `const`, \
		it is assumed to be stateful, and iterator monotonicity is enforced.

		XTAL_DO4_(template <auto ...Is>
		XTAL_DEF_(return,inline)
		XTAL_TN1 functor(auto &&...xs),
		{
			return map_f(head().template functory<iteratee_t<decltype(xs)> const &...>(Is...), XTAL_REF_(xs)...);
		})

	};
};
template <class U>
struct refer
{
	using U_render = occur::render_t<counted_t<>>;
	using subkind  = bond::compose<_retail::refer<U>, U_render::attach<>>;

	template <any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;
	
	public:
		using S_::S_;

	};
	template <any_q S> requires iterated_q<U> or _detail::unprocessed_q<U>
	class subtype<S> : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;
	
	public:
		using S_::S_;

	//	using S_::functor;

		XTAL_DO2_(template <auto ...>
		XTAL_TN2 functor(),
		{
			using _v3::views::slice;

			using I = iteratee_t<U_render>; using re = bond::realize<I>;
			auto const &m = S_::functor();// NOTE: Must be &?
			auto const &u = S_::template head<U_render>();
		//	NOTE: Using `count_f` because `sizeof(u.size()) == sizeof(u::value_type) << 1`. \
		
			I const u_size = count_f(u);
			I const m_size = count_f(m);
			I const m_mask = m_size >> re::positive.depth;
			I i = u.front();
			I j = u_size + i;
			i &= ~m_mask;
			j &= ~m_mask;
			j |=  m_mask&m_size;
			return m|slice(i, j);
		})

		XTAL_TO2_(XTAL_TN2 begin(), functor().begin())
		XTAL_TO2_(XTAL_TN2   end(), functor().  end())

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
