#pragma once
#include "../process/any.hh"// `_retail`

#include "../occur/render.hh"
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

template <class T>
struct define
{
	using U_resize = occur::resize_t<>;
	using U_render = occur::render_t<>;

	using superkind = _retail::define<T>;

	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind>;
		using T_ = typename S_::self_type;
	
	public:
		using S_::S_;
		using S_::self;

		template <class ...Xs>
		struct binding
		{
			using superkind = bond::compose<void
			,	U_resize::attach<>
			,	U_render::attach<>
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

				XTAL_DEF_(return,inline,let)
				delay()
				noexcept -> auto
				{
					using R_delay = XTAL_ALL_(R_::delay());
					R_delay const n = R_::delay();
					return 0 < n? n: static_cast<R_delay>(R_::template head<U_resize>());
				}

			public:// FLOW

				template <signed N_ion>
				XTAL_DEF_(return,inline,let)
				flux(auto &&...oo)
				noexcept -> signed
				{
					return R_::template flux<N_ion>(XTAL_REF_(oo)...);
				}
				
				template <signed N_ion> requires in_n<N_ion, -1>
				XTAL_DEF_(return,let)
				flux(occur::review_q auto &&review_o, occur::render_q auto &&render_o, auto &&...oo
				)
				noexcept -> signed
				{
					auto &s = R_::self();
					
					if (R_::template fuse<N_ion>(render_o) == 1) {
						return 1;
					}
					else {
						return s.reflux([&] (counted_q auto scan, counter_q auto step)
							XTAL_0FN_(return) (s.template subview_flux<N_ion>(review_o.subview(scan), render_o.subview(scan).skip(step)))
						)
						&	[this, ...oo=XTAL_REF_(oo)]
								XTAL_0FN_(and) (R_::template flux<N_ion>(oo...))
									(R_::template flux_arguments<+1>(XTAL_REF_(render_o)));
					}
				}
				///\
				Renders the buffer slice designated by `review_o` and `render_o`. \
				
				template <signed N_ion> requires in_n<N_ion, -1>
				XTAL_DEF_(return,let)
				subview_flux(occur::review_q auto &&review_o, occur::render_q auto &&render_o)
				noexcept -> signed
				{
					auto          &u_state = review_o.view();
					using          U_state = XTAL_ALL_(u_state);
					auto constexpr N_share = bond::seek_truth_n<_detail::recollection_p<Xs, U_state>...>;
					
					if (1 == R_::template flux_arguments_<N_ion, N_share>(review_o, render_o)) {
						return 1;
					}
					else {
						using namespace _xtd::ranges;
						
						auto result_o = R_::method();// Materialize...
						auto y0 = point_f(review_o);
						auto yN = count_f(review_o);
						_detail::move_to(y0, point_f(result_o), yN);

						return 0;
					}
				}

			};
		};
		template <class U>
		using bracelet = processor::let<U>;

	};
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
//\
template <any_q U>
template <_detail::  processed_range_q U>
struct defer<U>
:	_retail::defer<U>
{
};
template <_detail::unprocessed_range_q U>
struct defer<U>
{
	using V_render = occur::render_t<counted_t<>>;

	using superkind = bond::compose<void
	,	_detail::refer_iterators<U>
	,	_retail::defer<U>
	,	typename V_render::attach<>
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
		noexcept -> decltype(auto)
		{
			auto &v = S_::template head<V_render>().view();
			return S_::subhead(v);
		})

	};
};

template <_detail::unprocessed_value_q U>
struct defer<U>
:	defer<_detail::repeated_t<U>>
{
};
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

		///\
		Defines the range-lifted form of `head` by lifting the underlying `process`. \
		Parameter resolution is only performed at the beginning of each block. \

		///\note\
		Only `method` participates in parameter resolution, since `method_f` is stateless. \

		///\note\
		If `1 <= sizeof...(Is)`, the returned range is type-erased with `ranges::any_view` \
 		(so it can be `vtable`d). \

		XTAL_FX2_(do) (template <auto ...Is>
		XTAL_DEF_(return,inline,let)
		method(auto &&...xs),
		noexcept -> auto
		{
			auto const f = head().template reify<iteratee_t<decltype(xs)> &&...>(constant_t<Is>{}...);
			XTAL_IF0
			XTAL_0IF (0 == sizeof...(Is)) {return           iterative_f(XTAL_MOV_(f), XTAL_REF_(xs)...) ;}
			XTAL_0IF (1 <= sizeof...(Is)) {return derange_f(iterative_f(XTAL_MOV_(f), XTAL_REF_(xs)...));}
		})
		template <auto ...Is>
		XTAL_DEF_(return,inline,set)
		method_f(auto &&...xs)
		noexcept -> auto
		requires requires {U_::template method_f<Is...>(XTAL_ANY_(iteratee_t<decltype(xs)> &&)...);}
		{
			auto constexpr f = [] XTAL_0FN_(alias) (U_::template method_f<Is...>);
			XTAL_IF0
			XTAL_0IF (0 == sizeof...(Is)) {return           iterative_f<f>(XTAL_REF_(xs)...) ;}
			XTAL_0IF (1 <= sizeof...(Is)) {return derange_f(iterative_f<f>(XTAL_REF_(xs)...));}
		}

	};
};

template <class U>
struct refer
:	_retail::refer<U>
{
};
template <_detail::unprocessed_q U>
struct refer<U>
:	bond::compose<_detail::refer_unprocessed<U>, _retail::refer<_detail::repeated_t<U>>>
{
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
