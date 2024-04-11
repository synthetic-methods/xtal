#pragma once
#include "../flux/any.hh"// `_retail`

#include "../cell/cue.hh"




XTAL_ENV_(push)
namespace xtal::schedule
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

#include "./_retail.ii"
#include "./_detail.ii"


////////////////////////////////////////////////////////////////////////////////

template <class T>
struct define
{
	using subkind = _retail::define<T>;

	template <class S>
	class subtype : public bond::compose_s<S, subkind>
	{
		friend T;
		using S_ = bond::compose_s<S, subkind>;
	
	public:
		using S_::S_;
		using S_::self;

		///\
		Provides dispatch logic for `Xs...` on the target object. \
		
		///\note\
		The naming is intended to reflect that only `influx` is queued/`cue`d. \

		template <class ...Xs>
		struct inqueue
		{
			template <flux::any_q R>
			class subtype : public bond::compose_s<R>
			{
				using R_ = bond::compose_s<R>;
				static_assert(complete_q<Xs...>);
				
			protected:
				using W_tuple = _std::tuple<Xs...>;
				using U_tuple = occur::packed_t<Xs...>;
				using U_event = cell::cue_s<U_tuple>;
				using U_delay = cell::cue_s<>;
				using V_delay = typename U_delay::template head_t<>;

			public:
				using R_::R_;
				using R_::self;

			public:// POLL
			//	using R_::infuse;

				XTAL_TNX infuse(auto &&o)
				XTAL_0EX
				{
					return R_::infuse(XTAL_REF_(o));
				}
				XTAL_TNX infuse(U_tuple u_tuple)
				XTAL_0EX
				{
					return u_tuple.apply([&, this] XTAL_1FN_(influx));
				}
				XTAL_TNX infuse(W_tuple w_tuple)
				XTAL_0EX
				{
					return _std::apply([&, this] XTAL_1FN_(influx), w_tuple);
				}

			public:// ENQUEUE
			//	using R_::influx;

				XTAL_TNX influx(auto &&...oo)
				XTAL_0EX
				{
					return R_::influx(XTAL_REF_(oo)...);
				}

				XTAL_TNX influx(U_delay d_t, U_tuple d_u)
				XTAL_0EX
				{
					return influx(U_event(d_t, d_u));
				}
				XTAL_TNX influx(U_delay d_t, W_tuple d_v)
				XTAL_0EX
				{
					return influx(U_event(d_t, U_tuple::apple(d_v)));
				}
				XTAL_TNX influx(U_delay d_t, is_q<Xs> auto &&...d_xs)
				XTAL_0EX
				{
					return influx(U_event(d_t, U_tuple(XTAL_REF_(d_xs)...)));
				}

			};
		};

	};
};
template <class T>
struct refine
{
	using subkind = _retail::refine<T>;

	template <any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;
	
		template <class ...Xs>
		using S_inqueue = typename S_::template inqueue<Xs...>;

	public:
		using S_::S_;
		using S_::self;

		template <class ...Xs>
		struct inqueue : S_inqueue<Xs...>
		{
			using kind = confined<S_inqueue<Xs...>>;
			using type = bond::compose_s<S_, kind>;
		
		};
		template <class ...Xs>
		using inqueue_t = typename inqueue<Xs...>::type;

	};
};


////////////////////////////////////////////////////////////////////////////////

template <class U>
struct defer
:	_retail::defer<U>
{
};
template <class U>
struct refer
:	_retail::refer<U>
{
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)