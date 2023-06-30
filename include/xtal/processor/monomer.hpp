#pragma once
#include "./any.hpp"
#include "../process/binder.hpp"
#include "../message/sequel.hpp"




XTAL_ENV_(push)
namespace xtal::processor
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ...>
struct monomer;

template <typename T>
XTAL_ASK monomer_p = only_p<T, monomer>;

template <typename ...Ts>
XTAL_ASK monomer_q = conjunct_q<monomer_p<Ts>...>;

template <typename U, typename ...As>
XTAL_USE monomer_t = compose_s<only_t<monomer>, lift<U, monomer<As...>>>;

template <typename ...As>
XTAL_FZ2 monomer_f(XTAL_DEF u) {return monomer_t<XTAL_TYP_(u), As...>(XTAL_REF_(u));}


////////////////////////////////////////////////////////////////////////////////

template <typename ...As>
struct monomer
{
	using resize_u = message::resize_t<>;
	using sequel_u = message::sequel_t<>;
	using subkind = _retail::binder<As..., sequel_u::attach, resize_u::attach>;

	template <any_p S>
	class subtype: public compose_s<S, subkind>
	{
		using S_ = compose_s<S, subkind>;
		using T_ = typename S_::self_t;
	
	public:
		using S_::S_;
		using S_::self;

		template <typename ...Xs>
		struct bind
		{
			using rebound = typename S_::template bind<Xs...>;
			using subkind = compose<void
			,	concord::confer<typename rebound::result_t>
			,	rebound
			>;
			template <typename R>
			class subtype: public compose_s<R, subkind>
			{
				using R_ = compose_s<R, subkind>;

			public:
				XTAL_CN4_(subtype);
				XTAL_CN2_(subtype);
			//	using R_::R_;

				XTAL_NEW_(explicit) subtype(XTAL_DEF ...xs)
				XTAL_0EX
				:	R_(R_::method(XTAL_REF_(xs)...), XTAL_REF_(xs)...)
				{
				}
				XTAL_NEW_(explicit) subtype(XTAL_DEF_(is_q<T_>) t, XTAL_DEF ...xs)
				XTAL_0EX
				:	R_(R_::method(XTAL_REF_(xs)...), XTAL_REF_(t), XTAL_REF_(xs)...)
				{
				}

				XTAL_RN2_(XTAL_FN1 serve(XTAL_DEF... oo), R_::head(XTAL_REF_(oo)...))

				template <auto...>
				XTAL_FN2 method()
				XTAL_0EX
				{
					return serve();
				}

			public:
				using R_::efflux;

				XTAL_FNX efflux(XTAL_DEF_(message::sequel_q) sequel_o)
				XTAL_0EX
				{
					return XTAL_FLX_((void) serve(R_::method()), -1) (R_::efflux(XTAL_REF_(sequel_o)));
				}

			};
		};
		template <typename ...Xs> requires collect_q<S_>
		struct bind<Xs...>
		{
			using rebound = typename S_::template bind<Xs...>;
		
		private:
			using buffer_u = typename S_::template fluid<typename rebound::return_t>::type;
			using debuff_u = deranged_t<buffer_u>;
			using respan_u = message::respan_t<debuff_u>;
			using resize_u = message::resize_t<>;
		
			XTAL_LET_(int) I_parity = seek_true_v<_detail::recollected_p<Xs, debuff_u>...>;

		public:
			using subkind = compose<void
			,	concord::confer<debuff_u>
			,	concord::defer <buffer_u>
			,	rebound
			>;
			template <any_p R>
			class subtype: public compose_s<R, subkind>
			{
				using R_ = compose_s<R, subkind>;

				XTAL_NEW_(explicit) subtype(buffer_u &&buffer_o, XTAL_DEF ...etc)
				XTAL_0EX
				:	R_((debuff_u) buffer_o, XTAL_MOV_(buffer_o), XTAL_REF_(etc)...)
				{
				}

			public:
				XTAL_NEW_(explicit) subtype(XTAL_DEF ...etc)
				XTAL_0EX
				:	subtype(buffer_u(), XTAL_REF_(etc)...)
				{
				}

				XTAL_CN2_(subtype);
				XTAL_CN4_(subtype);
			//	using R_::R_;
				using R_::self;

				XTAL_RN4_(XTAL_FN1 store(XTAL_DEF... oo), R_::template head<1>(XTAL_REF_(oo)...))
				XTAL_RN4_(XTAL_FN1 serve(XTAL_DEF... oo), R_::template head<0>(XTAL_REF_(oo)...))

				template <auto...>
				XTAL_FN2 method()
				XTAL_0EX
				{
					return serve();
				}

				using R_::efflux;
				///\
				Responds to `message::sequel` by rendering the internal `store()`. \
				A match for the following sequel will initiate the `respan` (returning `1`), \
				while a match for the current sequel will terminate (returning `0`). \
				(Deviant behaviour is enforced by `assert`ion on `sequel`.) \

				XTAL_FNX efflux(message::sequel_q auto sequel_o, XTAL_DEF ...oo)
				XTAL_0EX
				{
					return efflux(respan_u(store()), sequel_o, XTAL_REF_(oo)...);
				}
				///\note\
				When accompanied by `message::respan`, the supplied visor will be used instead. \
				All `arguments` are rendered in-place unless a `visor`-compatible `rvalue` is found, \
				in which case the visor will be reused for the intermediate result. \

				XTAL_FNX efflux(respan_u respan_o, message::sequel_q auto sequel_o, XTAL_DEF ...oo)
				XTAL_0EX
				{
					if (R_::effuse(sequel_o, oo...) == 1) return 1;
				//	else...
					serve(respan_o);
					R_::redux([&, this](auto i, auto j, auto n)
					XTAL_0FN
					{	using namespace _v3;
						auto sequel_x = sequel_o.slice(i, j).skip(n);
						auto respan_x = respan_o.slice(i, j);
						(void) R_::template efflux_request_tail<I_parity>(respan_x, sequel_x, oo...);
						ranges::copy(R_::template method<>()|views::take(j - i), ranges::next(serve().begin(), i));
					});
					return R_::template influx_request(sequel_o);
				}

			//	using R_::infuse;
				///\
				Responds to `message::resize` by resizing the internal `store()`. \

				XTAL_FNX infuse(resize_u resize_o)
				XTAL_0EX
				{
					return R_::infuse(resize_o) or (store().resize(XTAL_REF_(resize_o)), 0);
				}
				XTAL_FNX infuse(XTAL_DEF o)
				XTAL_0EX
				{
					return R_::infuse(XTAL_REF_(o));
				}
				
				using R_::influx_request;
				///\note\
				Resizing skips intermediate `recollected_p` dependencies, \
				continuing to propagate beyond. \

				XTAL_FNX influx_request(resize_u resize_o, XTAL_DEF ...oo)
				XTAL_0EX
				XTAL_IF1 (0 <= I_parity)
				{
					return R_::template influx_request_tail<I_parity>(null_t(), resize_o, XTAL_REF_(oo)...);
				}

			};
		};

	};
};

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
