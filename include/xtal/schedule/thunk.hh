#pragma once
#include "./any.hh"
#include "../resource/spool.hh"





XTAL_ENV_(push)
namespace xtal::schedule
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

///\
Provides an `in(flux )queue` for `X` on the target object, \
which produces a signal by successive calls to `functor`. \

///\todo\
Adapt to provide polling. \

template <typename ...As>
struct thunk
{
	using subkind = bond::compose<As..., resource::spool<-1>>;

	template <any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;
		static_assert(resource::spool_q<S_>);

	public:
		using S_::S_;

		template <class X>
		struct inqueue
		{
			using subkind = typename S_::template inqueue<X>;

			template <_retail::any_q R>
			class subtype : public bond::compose_s<R, subkind>
			{
				using R_ = bond::compose_s<R, subkind>;
			
			protected:
				using typename R_::U_event;
				using typename R_::V_delay;
				using U_spool = typename S_::template spool_t<U_event>;

			private:
				V_delay v_delay{0};
				U_spool u_spool{
					(U_event) numeric_t<V_delay>::min(),
					(U_event) numeric_t<V_delay>::max()
				};

			public:
			//	using R_::R_;
				
				XTAL_CO0_(subtype)
				XTAL_CO4_(subtype)

				XTAL_TNX infuse(auto &&o)
				XTAL_0EX
				{
					return R_::infuse(XTAL_REF_(o));
				}
				XTAL_TNX infuse(is_q<X> auto &&x)
				XTAL_0EX
				{
					return u_spool.peek(0).then().infuse(XTAL_REF_(x));
				}
				XTAL_TNX infuse(is_q<U_event> auto &&u)
				XTAL_0EX
				{
					if (u_spool.empty() and u.head() < v_delay) {
						(void) u_spool.abandon().head(v_delay = 0);
					}
					return u.then() == u_spool.push(XTAL_REF_(u)).then();
				}

				XTAL_TN2 functor()
				XTAL_0EX
				{
					return u_spool.advance(v_delay++ == u_spool.peek(1).head()).then().head();
				}

				///\todo\
				Use `U_tuple=serial` to provide an incremental Dual pair, \
				replacing the first-derivative with the minimum w.r.t. the current difference. \
				\
				Should be straightforward to parameterize with e.g. `<N_ramping=0>`, \
				respectively enabling/disabling if the goal has/hasn't been met. \

				///\todo\
				Once the phasor-type is settled, define a `functor` that updates only on reset. \

			};
		};

	};
};
template <class X>
using thunk_t = confined_t<thunk<X>>;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
