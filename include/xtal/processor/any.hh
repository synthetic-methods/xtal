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
template <_detail::unprocessed_value_q U>
struct defer<U>
:	defer<_detail::arrange_t<U>>
{
};
template <_detail::unprocessed_range_q U>
struct defer<U>
{
	using V_render = occur::render_t<counted_t<>>;

	using subkind = bond::compose<void
	//\
	,	_detail::refer_subhead<U>
	,	_detail::refer_iterators<U>
	,	_retail::defer<U>
	,	typename V_render::attach<>
	>;
	template <any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;
		using U_ = _std::remove_reference_t<U>;

	public:
		using S_::S_;

		XTAL_DO2_(template <auto ...>
		XTAL_DEF_(return,inline)
		XTAL_REF functor(),
		{
			auto &v = S_::template head<V_render>().view();
			return S_::subhead(v);
		})

	};
};
template <_detail::processed_range_q U>
struct defer<U>
:	_retail::defer<U>
{
};
template <_detail::processed_value_q U>
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
		Defines the range-lifted form of `head` by lifting the underlying `process`. \
		This means that parameter resolution is only performed at the beginning of each block. \

		XTAL_DO4_(template <auto ...Is>
		XTAL_DEF_(return,inline)
		XTAL_REF functor(auto &&...xs),
		{
			return iterative_f(head().template refunctor<iteratee_t<decltype(xs)> const &...>(Is...), XTAL_REF_(xs)...);
		})

	};
};

template <class U>
struct refer
:	_retail::refer<U>
{
};
template <_detail::unprocessed_q U>
struct refer<U>
:	bond::compose<_detail::refer_unprocessed<U>, _retail::refer<_detail::arrange_t<U>>>
{
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
