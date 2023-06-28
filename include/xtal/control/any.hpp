#pragma once
#include "../conflux/any.hpp"// `_retail`

#include "../context/delay.hpp"




XTAL_ENV_(push)
namespace xtal::control
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

namespace _retail = xtal::conflux;
#include "../concord/any.hxx"


////////////////////////////////////////////////////////////////////////////////
///\
Produces a decorator `subtype<S>` that defines `T` with `As...::subtype` applied. \

template <typename T>
struct define
{
	using subkind = _retail::define<T>;

	template <any_q S>
	class subtype: public compose_s<S, subkind>
	{
		friend T;
		using co = compose_s<S, subkind>;
	
	public:
		using co::co;

		template <int N_event=-1>
		struct hold
		{
			template <conflux::any_q R>
			class subtype: public compose_s<R>
			{
				using co = compose_s<R>;

				using delay_t = context::delay_t;
				using event_t = context::delay_s<T>;
				using limit_t = _std::numeric_limits<delay_t>;
				using queue_t = typename collage_t<N_event, event_t>::siphon_t;

				delay_t d_{0};
				queue_t q_{(event_t) limit_t::min(), (event_t) limit_t::max()};

			public:
				using co::co;
				using co::self;


				using co::influx;
				///\
				\returns the aggregate `flux` of queuing the messages with the given delay.. \

				XTAL_FNX influx(context::delay_s<> d_t, XTAL_DEF ...oo)
				XTAL_0EX
				{
					return influx(context::delay_s<XTAL_TYP_(oo)>(d_t.head(), XTAL_REF_(oo))...);
				}
				XTAL_FNX influx(context::delay_s<T> dot, XTAL_DEF ...oo)
				XTAL_0EX
				{
					if (dot.head() < d_ and q_.empty())
					{	q_.abandon().head(d_ = 0);
					}
					q_.push(_std::move(dot));
					return co::influx(oo...);
				}


				template <auto...>
				XTAL_FN1_(T) method()
				XTAL_0EX
				{
					return q_.advance(d_++ == q_.top().head()).tail();
				}
			//	TODO: Once the phasor-type is settled, define a `method` that updates only on reset. \

			};
		};

	};
};

template <typename T>
struct refine
:	_retail::refine<T>
{
};


////////////////////////////////////////////////////////////////////////////////
///\
Produces a decorator `subtype<S>` that proxies `U`. \

template <typename U>
struct defer
:	_retail::defer<U>
{
};
template <constant_q W> requires sigma_q<value_t<W>>
struct defer<W>
{
	using subkind = defer<value_t<W>>;

	template <any_q S>
	class subtype: public compose_s<S, subkind>
	{
		using co = compose_s<S, subkind>;
	
	public:
		using co::co;

		using dispatch = typename co::template dispatch<value_v<W>>;

	};
};

///\
Produces a decorator `subtype<S>` that lifts the operations of `U`. \

template <typename U>
struct refer
:	_retail::refer<U>
{
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
