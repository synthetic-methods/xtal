#pragma once
#include "../process/any.hh"// `_retail`

#include "../occur/render.hh"
#include "../occur/resize.hh"
#include "../resource/invoice.hh"


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
{
	using U_resize = occur::resize_t<>;
	using U_render = occur::render_t<>;

	using subkind = _retail::define<T>;

	template <any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;
		using T_ = typename S_::self_type;
	
	public:
		using S_::S_;
		using S_::self;

		template <class ...Xs>
		struct brace
		{
			using subkind = bond::compose<void
			,	U_resize::attach<>
			,	U_render::attach<>
			,	typename S_::template brace<Xs...>
			>;
			template <any_q R>
			class subtype : public bond::compose_s<R, subkind>
			{
				using R_ = bond::compose_s<R, subkind>;

			public:// CONSTRUCT
				using R_::R_;

			public:// ACCESS

				XTAL_DEF_(return,inline)
				XTAL_LET delay()
				XTAL_0EX
				{
					auto const n = R_::delay(); using T_iota = decltype(n);
					return 0 < n? n: static_cast<T_iota>(R_::template head<U_resize>());
				}

			public:// *FLUX
				using R_::efflux;
				
				template <occur::review_q Rev, occur::render_q Ren>
				XTAL_TNX efflux(Rev &&review_o, Ren &&render_o, auto &&...oo)
				XTAL_0EX
				{
					auto &s = R_::self();
					
					if (R_::effuse(render_o) == 1) {
						return 1;
					}
					else {
						return s.reflux([&] (counted_q auto scan, counter_q auto step)
							XTAL_0FN_(s.efflux_subview(
								review_o.subview(scan),
								render_o.subview(scan).skip(step)
							)))
						&	XTAL_FNX_(R_::efflux(oo...)) (R_::template influx_push(XTAL_REF_(render_o)));
					}
				}
				///\
				Renders the buffer slice designated by `review_o` and `render_o`. \
				
				template <occur::review_q Rev, occur::render_q Ren>
				XTAL_TNX efflux_subview(Rev &&review_o, Ren &&render_o)
				XTAL_0EX
				{
					auto    &u_state = review_o.view();
					XTAL_USE U_state = XTAL_ALL_(u_state);
					XTAL_LET N_share = bond::seek_index_n<_detail::recollection_p<Xs, U_state>...>;
					
					if (1 == R_::template efflux_pull<N_share>(review_o, render_o)) {
						return 1;
					}
					else {
						using namespace _xtd::ranges;
						
						auto result_o = R_::method();// Materialize...
						auto _j = point_f(result_o);
						auto _i = point_f(review_o);
						auto  n = count_f(review_o);
						
						XTAL_IF0
						XTAL_0IF XTAL_TRY_DO_(copy_n(_j, n, _i))
						XTAL_0IF XTAL_TRY_DO_(move(result_o|account_f(n), _i))
						XTAL_0IF_(default) {for (size_type m = 0; m < n; ++m) {*_i++ = XTAL_MOV_(*_j++);}}

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
template <_detail::unprocessed_value_q U>
struct defer<U>
:	defer<_detail::repeated_t<U>>
{
};
template <_detail::unprocessed_range_q U>
struct defer<U>
{
	using V_render = occur::render_t<counted_t<>>;

	using subkind = bond::compose<void
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
		XTAL_LET method(), -> decltype(auto)
		{
			auto &v = S_::template head<V_render>().view();
			return S_::subhead(v);
		})

	};
};
/*/
template <_detail::processed_range_q U>
struct defer<U>
:	_retail::defer<U>
{
};
/*/
template <any_q U>
struct defer<U>
{
	using subkind = _retail::defer<U>;

	template <any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;

	public:
		using S_::S_;

	//	NOTE: Wrapped by the identity, rather than reiterated...
		
		XTAL_DO2_(template <auto ...Is>
		XTAL_DEF_(return,inline)
		XTAL_LET method(auto &&...xs),
		->	decltype(auto)
		{
			return S_::template method<Is...>(XTAL_REF_(xs)...);
		})
		XTAL_DO0_(template <auto ...Is>
		XTAL_DEF_(return,inline)
		XTAL_SET function(auto &&...xs),
		->	decltype(auto)
			requires XTAL_TRY_TO_(S_::template function<Is...>(XTAL_REF_(xs)...))
		)

	};
};
/***/
template <_detail::processed_value_q U>
struct defer<U>
{
	using subkind = _retail::defer<U>;

	template <any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;
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
		Only `method` participates in parameter resolution, since `function` is stateless. \

		///\note\
		The `template-method` is type-erased with `ranges::any_view` (so it can be `vtable`d), \
		but it only works if `this` is mutable... \

		template <auto ...Is>
		XTAL_DEF_(return,inline)
		XTAL_LET method(auto &&...xs)
		XTAL_0EX -> decltype(auto)
		{
			using namespace _xtd::ranges;

			auto  y_ = iterative_f([this] XTAL_1FN_(head().template operator()<Is...>), XTAL_REF_(xs)...);
			using Y_ = decltype(y_);
			using Z_ = any_view<range_reference_t<Y_>, get_categories<Y_>()>;
			if constexpr XTAL_TRY_(y_.size()) {
				auto const z_affix = account_f(y_);//NOTE: `any_view` doesn't propagate `size()`...
				return Z_(XTAL_MOV_(y_))|z_affix;
			}
			else {
				return Z_(XTAL_MOV_(y_));
			}
		}
		XTAL_DO2_(template <auto ...Is> requires none_n<Is...>
		XTAL_DEF_(return,inline)
		XTAL_LET method(auto &&...xs), -> decltype(auto)
		{
			return iterative_f([this] XTAL_1FN_(head().template operator()<Is...>), XTAL_REF_(xs)...);
		})

		XTAL_DO0_(template <auto ...Is> requires none_n<Is...>
		XTAL_DEF_(return,inline)
		XTAL_LET function(auto &&...xs), -> decltype(auto)
			requires XTAL_TRY_(U_::template function<Is...>
				(XTAL_ANY_(_xtd::ranges::range_reference_t<decltype(xs)>)...)
			)
		{
			return iterative_f([] XTAL_1FN_(U_::template function<Is...>)
			,	XTAL_REF_(xs)...
			);
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
:	bond::compose<_detail::refer_unprocessed<U>, _retail::refer<_detail::repeated_t<U>>>
{
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
