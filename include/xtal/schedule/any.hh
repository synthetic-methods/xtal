#pragma once
#include "../flux/any.hh"// `_retail`

#include "../flux/cue.hh"
#include "../algebra/differential/linear.hh"



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

	template <any_q S>
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

		///\todo\
		Make it easier to glean the relevant `schedule` types. \

		template <class ...Xs>
		struct inqueue
		{
			template <flux::any_q R>
			class subtype : public bond::compose_s<R>
			{
				using R_ = bond::compose_s<R>;
				static_assert(complete_q<Xs...>);
				
			protected:
				using W_tuple = bond::pack_t<Xs...>;
				using U_tuple = flux::packed_t<Xs...>;
				using U_event = flux::cue_s<Xs...>;
				using V_event = flux::cue_s<>;
				using V_delay = typename V_event::head_type;

			public:
				using R_::R_;
				using R_::self;

				using event_type = U_event;

			public:// *FLUX
				using R_::influx;

				///\
				Expands the given unscheduled message, forwarding to `supertype::influx`. \

				XTAL_TNX influx(XTAL_ARG_(U_tuple) &&o)
				XTAL_0EX
				{
					return XTAL_REF_(o).apply([this] XTAL_1FN_(R_::influx));
				}
				XTAL_TNX influx(XTAL_ARG_(W_tuple) &&o)
				XTAL_0EX
				{
					return _std::apply([this] XTAL_1FN_(R_::influx), XTAL_REF_(o));
				}

				///\
				Condenses the given scheduled message, forwarding to `self().infuse`. \
				
				XTAL_TNX influx(V_event d, XTAL_ARG_(Xs) &&...oo)
				XTAL_0EX
				{
					return joining_(XTAL_MOV_(d)) (XTAL_REF_(oo)...);
				}
				XTAL_TNX influx(V_event d, XTAL_ARG_(U_tuple) &&o)
				XTAL_0EX
				{
					return XTAL_REF_(o).apply(joining_(XTAL_MOV_(d)));
				}
				XTAL_TNX influx(V_event d, XTAL_ARG_(W_tuple) &&o)
				XTAL_0EX
				{
					return _std::apply(joining_(XTAL_MOV_(d)), XTAL_REF_(o));
				}

			private:
				XTAL_DEF_(return,inline)
				XTAL_RET joining_(auto o)
				XTAL_0EX
				{
					return [=, this] (auto &&...oo) XTAL_0FN_(join_(XTAL_MOV_(o), XTAL_REF_(oo)...));
				}
				XTAL_TNX join_(auto &&...oo)
				XTAL_0EX
				{
					return self().infuse((...<< XTAL_REF_(oo)));
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
