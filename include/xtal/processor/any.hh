#pragma once
#include "../bond.hh"
#include "../process/any.hh"// `_retail`
#include "../occur/cursor.hh"
#include "../occur/resize.hh"
#include "../provision/voiced.hh"


XTAL_ENV_(push)
namespace xtal::processor
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

namespace _retail = xtal::process;
#include "./_entail.ii"
#include "./_detail.ii"


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/*!
\brief   Extends `process::define` with range-based data-flow.
*/
template <class T>
struct define
{
	using U_cursor = occur::cursor_t<>;
	using U_resize = occur::resize_t<>;

	using superkind = _retail::define<T>;

	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind>;
		using T_ = typename S_::self_type;
	
	public:// CONSTRUCT
		using S_::S_;

		template <class ...Xs>
		struct binding
		{
			using superkind = bond::compose<void
			,	U_cursor::attach<>
			,	U_resize::attach<>
			,	typename S_::template binding<Xs...>
			>;
			template <class R>
			class subtype : public bond::compose_s<R, superkind>
			{
				static_assert(any_q<R>);
				using R_ = bond::compose_s<R, superkind>;

			public:// CONSTRUCT
				using R_::R_;

			public:// ACCESS
				using R_::self;

				/*!
				\brief  	Determines the size of the first chunk to be rendered.
				\brief  	The current delay if available, otherwise the size of the current block.
				*/
				XTAL_DEF_(return,inline,let)
				delay()
				noexcept -> auto
				{
					auto const n = R_::delay();
					return 0 < n? n: static_cast<XTAL_ALL_(n)>(R_::template head<U_resize>());
				}

			public:// FLOW

				/*!
				\brief  	Forwards the message upstream.
				*/
				template <signed N_ion>
				XTAL_DEF_(return,inline,let)
				flux(auto &&...oo)
				noexcept -> signed
				{
					return R_::template flux<N_ion>(XTAL_REF_(oo)...);
				}
				/*!
				\brief  	Renders the given `occur::review`, split into subviews if required.
				\brief  	Invokes the super-method `pump` to handle chunking and event dispatch.
				*/
				template <signed N_ion> requires in_v<N_ion, -1>
				XTAL_DEF_(return,let)
				flux(occur::review_q auto &&rev, occur::cursor_q auto &&cur)
				noexcept -> signed
				{
					auto &s = R_::self();
					auto &u = R_::template head<U_cursor>();
					
					if (s.template fuse<N_ion>(cur) == 1) {
						return 1;
					}
					if (s.pump([&] (counted_q auto scan, counter_q auto step)
						XTAL_0FN_(to) (s.template flux<N_ion>(occur::render_f(rev, cur)
						,	rev.subview(scan)
						,	cur.subview(scan).skip(step)
						))
					))	{
						(void) R_::template flux<+1>(constant_t<-1>{}, cur);
					}
					return 0;
				}
				/*!
				\brief  	Renders the subslice of `ren` designated by `rev` and `cur`.
				*/
				template <signed N_ion> requires in_v<N_ion, -1>
				XTAL_DEF_(return,let)
				flux(occur::render_q auto &&ren, occur::review_q auto &&rev, occur::cursor_q auto &&cur)
				noexcept -> signed
				{
					using          V_state = XTAL_ALL_(rev.view());
					auto constexpr N_share = bond::seek_truth_v<_detail::recollection_p<Xs, V_state>...>;
					if (1 == R_::template flux_unrest<N_ion>(ordinal_constant_t<N_share>{}, XTAL_REF_(rev), XTAL_REF_(cur))) {
						return 1;
					}
					else {
						auto res = R_::method();// Materialize...
						auto x0 = point_f(res);
						auto y0 = point_f(rev);
						auto sN = count_f(rev);
						_detail::copy_to(y0, x0, sN);
						return 0;
					}
				}

			};
		};

	};
};
/*!
\brief   Aliases `process::refine`.
*/
template <class T>
struct refine
:	_retail::refine<T>
{
};


////////////////////////////////////////////////////////////////////////////////
/*!
\brief   Extends `process::defer` by range-lifting the underlying `U`.
*/
template <class U>
struct defer
:	defer<_retail::let_t<U>>
{
};
/*!
\brief   Extends `process::defer` by proxying the range `U`.
*/
template <_detail::  processed_range_q U>
struct defer<U>
:	_retail::defer<U>
{
};

/*!
\brief   Extends `process::defer` by proxying the range `U`.
*/
template <_detail::unprocessed_range_q U>
struct defer<U>
{
	using V_cursor = occur::cursor_t<counted_t<>>;

	using superkind = bond::compose<void
	,	_detail::refer_iterators<U>
	,	_retail::defer<U>
	,	typename V_cursor::attach<>
	>;
	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind>;
		using U_ = _std::remove_reference_t<U>;

	public:
		using S_::S_;

		XTAL_FX2_(do) (template <auto ...>
		XTAL_DEF_(return,inline,let)
		method(),
		noexcept -> auto
		{
			auto &v = S_::template head<V_cursor>().view();
			return S_::subhead(v);
		})

	};
};
/*!
\brief   Extends `process::defer` by repeating the value `U`.
*/
template <_detail::unprocessed_value_q U>
struct defer<U>
:	defer<_detail::repetitive_t<U>>
{
};
/*!
\brief   Extends `process::defer` by range-mapping the process/function `U`.
*/
template <_detail::  processed_value_q U>
struct defer<U>
{
	using superkind = _retail::defer<U>;

	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind>;
		using U_ = typename S_::head_type;

	public:// CONSTRUCT
		using S_::S_;

	public:// OPERATE
		using S_::self;
		using S_::head;

		/*!
		\brief  	Defines the range-lifted form of `head` by lifting the underlying `process`.
		\brief  	Parameter resolution is only performed at the beginning of each block.
		\brief  	Only `method` participates in parameter resolution, since `method_f` is stateless.
		\brief  	If `1 <= sizeof...(Is)`, the returned range is type-erased with `ranges::any_view` (so it can be `vtable`d).
		*/
	//	template <auto ...Is>
	//	XTAL_DEF_(return,inline,set)
	//	method  (auto &&...xs)
	//	noexcept -> auto
	//		requires XTAL_TRY_(to)
	//			(method_f<Is...>(XTAL_ANY_(decltype(xs))...))

		XTAL_FX2_(do) (template <auto ...Is>
		XTAL_DEF_(return,inline,let)
		method  (auto &&...xs),
		noexcept -> auto
		//	requires XTAL_TRY_(to_unless)
		//		(method_f<Is...>(XTAL_ANY_(decltype(xs))...))
		{
			return normalize_f<Is...>(iterative_f(head().template
				reify<iteratee_t<decltype(xs)> &&...>(constant_t<Is>{}...), XTAL_REF_(xs)...));
		})
		template <auto ...Is>
		XTAL_DEF_(return,inline,set)
		method_f(auto &&...xs)
		noexcept -> auto
			requires XTAL_TRY_(to_if) (U_::template method_f<Is...>(XTAL_ANY_(iteratee_t<decltype(xs)> &&)...))
		{
			return normalize_f<Is...>(iterative_f<[] XTAL_1FN_(call)
				(U_::template method_f<Is...>)>(XTAL_REF_(xs)...));
		}

	private:

		template <auto ...Is>
		XTAL_DEF_(return,inline,set)
		normalize_f(auto &&y)
		noexcept -> decltype(auto)
		{
			XTAL_IF0
			XTAL_0IF (none_v<Is...>) {return           XTAL_REF_(y) ;}
			XTAL_0IF (some_v<Is...>) {return derange_f(XTAL_REF_(y));}
		}
		

	};
};
/*!
\brief   Aliases `process::refer`.
*/
template <class U>
struct refer
:	_retail::refer<U>
{
};
/*!
\brief   Extends `process::refer` by range-lifting the supplied-value `U`.
*/
template <_detail::unprocessed_q U>
struct refer<U>
:	bond::compose<_detail::refer_unprocessed<U>, _retail::refer<_detail::repetitive_t<U>>>
{
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
