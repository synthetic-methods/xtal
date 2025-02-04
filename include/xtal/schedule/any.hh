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
		The naming is intended to reflect that only `influx` is spooled/`cue`d. \

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
				
			public:
				using R_::R_;
				using R_::self;

				using   pack_type = bond::pack_t  <Xs...>;
				using packed_type = flow::packed_t<Xs...>;
			//	using packet_type = flow::packet_t<Xs...>;
				using  event_type = flow::cue_s   <Xs...>;
				using  delay_type = typename event_type::head_type;

			public:// FLOW

				///\
				Forwards `oo...` to the supertype`. \

				template <signed N_ion>
				XTAL_DEF_(return,inline,let)
				flux(auto &&...oo)
				noexcept -> signed
				{
					return R_::template flux<N_ion>(XTAL_REF_(oo)...);
				}
				///\
				Forwards `oo...` to the supertype`. \

				template <signed N_ion>
				XTAL_DEF_(return,inline,let)
				flux(same_q<identity_t<T>> auto &&, auto &&...oo)
				noexcept -> signed
				{
					return R_::template flux<N_ion>(XTAL_REF_(oo)...);
				}
				///\
				Expands the given unscheduled message, forwarding to `self()`. \

				template <signed N_ion>
				XTAL_DEF_(return,inline,let)
				flux(same_q<packed_type> auto &&o)
				noexcept -> signed
				{
					return XTAL_REF_(o).apply([this] (auto &&...oo)
						//\
						XTAL_0FN_(return) (self().template flux<N_ion>(identity_t<T>{}, XTAL_REF_(oo)...))
						XTAL_0FN_(return) (R_::template flux<N_ion>(XTAL_REF_(oo)...))
					);
				}
				template <signed N_ion>
				XTAL_DEF_(return,inline,let)
				flux(same_q<pack_type> auto &&o)
				noexcept -> signed
				{
					return _std::apply([this] (auto &&...oo)
						//\
						XTAL_0FN_(return) (self().template flux<N_ion>(identity_t<T>{}, XTAL_REF_(oo)...))
						XTAL_0FN_(return) (R_::template flux<N_ion>(XTAL_REF_(oo)...))
					,	XTAL_REF_(o)
					);
				}

				///\
				Condenses the given scheduled message, forwarding to `self().infuse`. \
				
				template <signed N_ion>
				XTAL_DEF_(return,inline,let)
				flux(flow::cue_s<> v, same_q<Xs> auto &&...oo)
				noexcept -> signed
				{
					return confuse<N_ion>(v) (XTAL_REF_(oo)...);
				}
				template <signed N_ion>
				XTAL_DEF_(return,inline,let)
				flux(flow::cue_s<> v, same_q<packed_type> auto &&oo)
				noexcept -> signed
				{
					return XTAL_REF_(oo).apply(confuse<N_ion>(v));
				}
				template <signed N_ion>
				XTAL_DEF_(return,inline,let)
				flux(flow::cue_s<> v, same_q<pack_type> auto &&oo)
				noexcept -> signed
				{
					return _std::apply(confuse<N_ion>(v), XTAL_REF_(oo));
				}

			private:

				template <signed N_ion>
				XTAL_DEF_(return,inline,let)
				confuse(auto &&o)
				noexcept -> decltype(auto)
				{
					return [this, o=XTAL_REF_(o)] (auto &&...oo)
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
