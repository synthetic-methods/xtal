#pragma once
#include "./any.hh"
#include "../resource/spooled.hh"





XTAL_ENV_(push)
namespace xtal::schedule
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

///\
Provides an `in(flux )queue` for `X` on the target object, \
which produces a signal by successive calls to `functor`. \

template <typename ...As>
struct thunk
{
	using subkind = bond::compose<As..., resource::spooled<Integral_t<-1>>>;

	template <any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;
		static_assert(resource::spooled_q<S_>);

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
				using Q_delay = _std::numeric_limits<V_delay>;

				U_spool u_spool{
					(U_event) Q_delay::min(),
					(U_event) Q_delay::max()
				};
				V_delay v_delay{};

			public:
			//	using R_::R_;
				
				XTAL_CO0_(subtype)
				XTAL_CO1_(subtype)
				XTAL_CO4_(subtype)

				XTAL_TNX infuse(auto &&o)
				XTAL_0EX
				{
					return R_::infuse(XTAL_REF_(o));
				}
				XTAL_TNX infuse(is_q<X> auto &&x)
				XTAL_0EX
				{
					return u_spool.begin()->then().infuse(XTAL_REF_(x));
				}
				XTAL_TNX infuse(is_q<U_event> auto &&u)
				XTAL_0EX
				{
					if (u_spool.empty() and u.head() < v_delay) {
						(void) u_spool.abandon()->head(v_delay = 0);
					}
					return u.then() == u_spool.push(XTAL_REF_(u))->then();
				}

				XTAL_REF functor()
				XTAL_0EX
				{
					return u_spool.advance(v_delay++ == u_spool.begin(1)->head())->then().head();
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
