#pragma once
#include "./any.hh"
#include "../resource/spooled.hh"





XTAL_ENV_(push)
namespace xtal::schedule
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
Provides an (in)queue for `Xs...` on the target object, \
schedule via `influx` and processed in segments via `reflux`. \

///\todo\
Allow for schedule beyond the current window, \
possibly using `occur::render` to convert between absolute and relative delays. \

template <typename ...As>
struct chunk
{
	using subkind = bond::compose<As..., resource::spooled<nominal_t<-1>>>;

	template <any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;
		static_assert(resource::spooled_q<S_>);

	public:
		using S_::S_;
		
		template <class ...Xs>
		struct inqueue
		{
			using subkind = typename S_::template inqueue<Xs...>;
			
			template <flux::any_q R>
			class subtype : public bond::compose_s<R, subkind>
			{
				using R_ = bond::compose_s<R, subkind>;

			protected:
				using typename R_::U_event;
				using typename R_::V_delay;
				using U_spool = typename S_::template spool_t<U_event>;

			private:
				using L_delay = _std::numeric_limits<V_delay>;

				U_spool u_spool{
					(U_event) L_delay::max()
				};
				XTAL_TO4_(XTAL_DEF_(return,inline) XTAL_RET head_(int i), u_spool.begin(i - 1)->head())
				XTAL_TO4_(XTAL_DEF_(return,inline) XTAL_RET then_(int i), u_spool.begin(i - 1)->tail())

			public:
				using R_::R_;
				using R_::self;
				
				///\
				Influxes the `U_event` immediately if the associated delay is `0`, \
				otherwise enqueues the event. \

				XTAL_TNX infuse(auto &&o)
				XTAL_0EX
				{
					return R_::infuse(XTAL_REF_(o));
				}
				XTAL_TNX infuse(is_q<U_event> auto &&u)
				XTAL_0EX
				{
					if (0 == u.head()) {
						return R_::influx(XTAL_REF_(u).tail());
					}
					else {
						u_spool.push(XTAL_REF_(u)); return 0;
					//	NOTE: Always successful, since there's (currently) no collision testing...
					}
				}

				///\returns The delay until the next event to be processed. \

				XTAL_DEF_(inline)
				XTAL_LET delay()
				XTAL_0EX -> V_delay
				{
				//	NOTE: The `std::initializer_list` syntax avoids segfaulting in `RELEASE`. \
				
					return _std::min<V_delay>({R_::delay(), head_(1)});
				}
				///\
				Invokes `influx` for all events up-to the supplied delay `i`. \
				
				///\returns the delay until the next event. \

				XTAL_DEF_(inline)
				XTAL_LET relay(V_delay i)
				XTAL_0EX -> V_delay
				{
					R_::relay(i);
					for (; 0 < u_spool.size() and head_(1) <= i; u_spool.pop()) {
						(void) R_::influx(then_(1));
					}
					return delay();
				}

			};
		};

	};
};
template <class ...Xs>
using chunk_t = confined_t<chunk<Xs...>>;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
