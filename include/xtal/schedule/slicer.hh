#pragma once
#include "./any.hh"

#include "../flow/ion.hh"
#include "../provision/spooled.hh"



XTAL_ENV_(push)
namespace xtal::schedule
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
Provides an (in)queue for the `variant`s `Ys...` on the target object, \
schedule via `influx` and processed in segments via `reflux`. \

///\todo\
Allow for schedule beyond the current window, \
possibly using `occur::cursor` to convert between absolute and relative delays. \

template <typename ...As>
struct slicer
{
	using superkind = bond::compose<As..., provision::spooled<extent_constant_t<-1>>>;

	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind>;
		static_assert(provision::spooled_q<S_>);

	public:
		using S_::S_;
		
		template <class ...Ys>
		struct inqueue
		{
			using superkind = typename S_::template inqueue<Ys...>;
			
			template <flow::any_q R>
			class subtype : public bond::compose_s<R, superkind>
			{
				using R_ = bond::compose_s<R, superkind>;

			public:
				using typename R_::  event_type;
				using typename R_::  delay_type;
				using typename R_::payload_type;

			private:
				using U_payload = flow::ion_s<payload_type>;
				using U_event   = flow::cue_s<U_payload>;
				using U_spool   = typename S_::template spool_t<U_event>;
				
				U_spool u_spool{bond::seek_t<>{}
				,	_std::numeric_limits<delay_type>::max()
				};

				XTAL_FX4_(to) (XTAL_DEF_(return,inline,get)
				next(),
					u_spool.peek())

			public:
				using R_::R_;
				using R_::self;
				
				template <signed N_ion>
				XTAL_DEF_(return,inline,let)
				fuse(auto &&o)
				noexcept -> signed
				{
					return R_::template fuse<N_ion>(XTAL_REF_(o));
				}
				///\
				Influxes the `event_type` immediately if the associated delay is `0`, \
				otherwise enqueues the event. \

				///\note\
				Delayed messages always return `0`	since there's (currently) no collision testing. \
				
				template <signed N_ion>// requires in_n<N_ion, +1>
				XTAL_DEF_(return,inline,let)
				fuse(same_q<event_type> auto &&q)
				noexcept -> signed
				{
					U_payload o{N_ion, q.tail()};//TODO: Make `const`?
					if (0 == q.head()) {
						return R_::flux(XTAL_MOV_(o));
					}
					else {
						u_spool.push(U_event{XTAL_REF_(q), XTAL_MOV_(o)}); return 0;
					}
				}

				///\returns the delay until the next event to be processed. \

				XTAL_DEF_(return,inline,let)
				delay()
				noexcept -> delay_type
				{
					return bond::fit<delay_type>::minimum_f(R_::delay(), next().head());
				}
				//\returns the size of the render cycle, \
				after all future events have been brought forward. \

				XTAL_DEF_(mutate,inline,let)
				belay()
				noexcept -> delay_type
				{
					auto const i = R_::belay();
					for (auto &u:u_spool) {
						u -= i; assert(0 <= u.head());
					}
					return i;
				}
				///\
				Invokes `influx` for all events up-to the supplied delay `<= i`. \
				
				///\returns the delay until the next event. \
				
				XTAL_DEF_(mutate,inline,let)
				relay(delay_type i)
				noexcept -> delay_type
				{
					R_::relay(i);
					while (0 < u_spool.size() and next().head() <= i) {
						(void) R_::flux(next().tail());
						(void) u_spool.pop();
					}
					return delay();
				}

			};
		};

	};
};
template <class ...Ys>
using slicer_t = confined_t<slicer<Ys...>>;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
