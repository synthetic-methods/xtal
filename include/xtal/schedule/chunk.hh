#pragma once
#include "./any.hh"
#include "../provision/spooled.hh"





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
	using superkind = bond::compose<As..., provision::spooled<constant_t<-1>>>;

	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind>;
		static_assert(provision::spooled_q<S_>);

	public:
		using S_::S_;
		
		template <class ...Xs>
		struct inqueue
		{
			using superkind = typename S_::template inqueue<Xs...>;
			
			template <flux::any_q R>
			class subtype : public bond::compose_s<R, superkind>
			{
				using R_ = bond::compose_s<R, superkind>;

			protected:
				using typename R_::U_event;
				using typename R_::V_delay;
				using U_spool = typename S_::template spool_t<U_event>;

			private:
				using L_delay = _std::numeric_limits<V_delay>;

				U_spool u_spool{
					(U_event) L_delay::max()
				};
				XTAL_TO4_(XTAL_DEF_(alias) head_(int i), u_spool.begin(i - 1)->head())
				XTAL_TO4_(XTAL_DEF_(alias) then_(int i), u_spool.begin(i - 1)->tail())

			public:
				using R_::R_;
				using R_::self;
				
				///\
				Influxes the `U_event` immediately if the associated delay is `0`, \
				otherwise enqueues the event. \

				XTAL_DEF_(short)
				XTAL_LET infuse(auto &&o)
				noexcept -> signed
				{
					return R_::infuse(XTAL_REF_(o));
				}
				XTAL_DEF_(long)
				XTAL_LET infuse(XTAL_SYN_(U_event) auto &&u)
				noexcept -> signed
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
				noexcept -> V_delay
				{
				//	NOTE: The `std::initializer_list` syntax avoids segfaulting in `RELEASE`. \
				
					return _std::min<V_delay>({R_::delay(), head_(1)});
				}
				///\
				Invokes `influx` for all events up-to the supplied delay `i`. \
				
				///\returns the delay until the next event. \

				XTAL_DEF_(inline)
				XTAL_LET relay(V_delay i)
				noexcept -> V_delay
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
