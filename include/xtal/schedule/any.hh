#pragma once
#include "../flow/any.hh"// `_retail`

#include "../flow/cue.hh"




XTAL_ENV_(push)
namespace xtal::schedule
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

namespace _retail = xtal::flow;
#include "./_entail.ii"
#include "./_detail.ii"


////////////////////////////////////////////////////////////////////////////////

template <class T>
struct define
{
	using superkind = _retail::define<T>;

	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind>;
	
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
			template <flow::any_q R>
			class subtype : public bond::compose_s<R>
			{
				using R_ = bond::compose_s<R>;
				static_assert(complete_q<Xs...>);
				
			protected:
				using W_tuple = bond::pack_t<Xs...>;
				using U_tuple = flow::packed_t<Xs...>;
				using U_event = flow::cue_s<Xs...>;
				using V_event = flow::cue_s<>;
				using V_delay = typename V_event::head_type;

			public:
				using R_::R_;
				using R_::self;

				using event_type = U_event;

			public:// FLOW

				template <signed N_ion>
				XTAL_DEF_(return,inline,let)
				flux(auto &&...oo)
				noexcept -> signed
				{
					return R_::template flux<N_ion>(XTAL_REF_(oo)...);
				}
				///\
				Expands the given unscheduled message, forwarding to `supertype::flux`. \

				template <signed N_ion>
				XTAL_DEF_(return,inline,let)
				flux(same_q<U_tuple> auto &&o)
				noexcept -> signed
				{
					return XTAL_REF_(o).apply([this] (auto &&...oo)
						XTAL_0FN_(return) (R_::template flux<N_ion>(XTAL_REF_(oo)...))
					);
				}
				template <signed N_ion>
				XTAL_DEF_(return,inline,let)
				flux(same_q<W_tuple> auto &&o)
				noexcept -> signed
				{
					return _std::apply([this] (auto &&...oo)
						XTAL_0FN_(return) (R_::template flux<N_ion>(XTAL_REF_(oo)...))
					,	XTAL_REF_(o)
					);
				}

				///\
				Condenses the given scheduled message, forwarding to `self().infuse`. \
				
				template <signed N_ion>
				XTAL_DEF_(return,inline,let)
				flux(same_q<V_event> auto &&d, same_q<Xs> auto &&...oo)
				noexcept -> signed
				{
					return confuse<N_ion>(XTAL_REF_(d)) (XTAL_REF_(oo)...);
				}
				template <signed N_ion>
				XTAL_DEF_(return,inline,let)
				flux(same_q<V_event> auto &&d, same_q<U_tuple> auto &&o)
				noexcept -> signed
				{
					return XTAL_REF_(o).apply(confuse<N_ion>(XTAL_REF_(d)));
				}
				template <signed N_ion>
				XTAL_DEF_(return,inline,let)
				flux(same_q<V_event> auto &&d, same_q<W_tuple> auto &&o)
				noexcept -> signed
				{
					return _std::apply(confuse<N_ion>(XTAL_REF_(d)), XTAL_REF_(o));
				}

			private:

				template <signed N_ion>
				XTAL_DEF_(return,inline,let)
				confuse(auto o)
				noexcept -> decltype(auto)
				{
					return [this, o = XTAL_REF_(o)] (auto &&...oo)
						XTAL_0FN_(return) (self().template fuse<N_ion>((XTAL_REF_(o) <<...<< XTAL_REF_(oo))));
				}

			};
		};

	};
};
template <class T>
struct refine
{
	using superkind = _retail::refine<T>;

	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind>;
	
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
