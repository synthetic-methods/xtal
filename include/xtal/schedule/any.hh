#pragma once
#include "../bond.hh"
#include "../flow/any.hh"// `_retail`
#include "../flow/cue.hh"
#include "../flow/ion.hh"



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
		Provides dispatch logic for the `variant`s `Ys...` on the target object. \
		
		///\todo\
		Integrate concatenation using `<<` and `>>` with correct `packet` construction. \

		template <class ...Ys>
		struct inqueue
		{
			template <flow::any_q R>
			class subtype : public bond::compose_s<R>
			{
				using R_ = bond::compose_s<R>;
				static_assert(complete_q<Ys...>);
				
			public:
				using R_::R_;
				using R_::self;

				using   event_type =          flow::cue_s<Ys...>;
				using   delay_type = typename flow::cue_s<Ys...>::head_type;
				using payload_type = typename flow::cue_s<Ys...>::tail_type;

			public:// FLOW
				///\
				Forwards `oo...` downstream. \

				template <signed N_ion>
				XTAL_DEF_(return,inline,let)
				flux(auto &&...oo)
				noexcept -> signed
				{
					return R_::template flux<N_ion>(XTAL_REF_(oo)...);
				}
				///\
				Forwards the descheduled message to `self()`. \

				XTAL_DEF_(return,inline,let)
				flux(flow::ion_s<> x_, auto &&...oo)
				noexcept -> signed
				{
					switch (x_.head()) {
					case  1: return self().template flux< 1>(XTAL_REF_(oo)...);
					case -1: return self().template flux<-1>(XTAL_REF_(oo)...);
					default: _std::terminate(); return -1;
					}
				}
				XTAL_DEF_(return,inline,let)
				flux(flow::ion_s<> x_, either_q<Ys...> auto &&w)
				noexcept -> signed
				{
					//\
					return bond::operate{[x_, this] (auto &&o) XTAL_0FN_(to) (flux(x_, XTAL_REF_(o)))} (XTAL_REF_(w));
					return bond::operate{_std::bind_front([this] XTAL_1FN_(call) (flux), x_)} (XTAL_REF_(w));
				}
				///\
				Unpacks and forwards the dequeued message to `self()`. \

				XTAL_DEF_(return,inline,let)
				flux(flow::ion_s<> x_, flow::packed_q auto &&o)
				noexcept -> signed
				{
					return XTAL_REF_(o).apply([&, this] (auto &&...oo)
						XTAL_0FN_(to) (flux(x_, XTAL_REF_(oo)...))
					);
				}
				XTAL_DEF_(return,inline,let)
				flux(flow::ion_q auto const xo)
				noexcept -> signed
				{
					return flux(flow::ion_s<>(xo.head()), xo.tail());
				}

				///\
				Forwards the event-to-be-scheduled to `self().fuse`. \
				
				///\note\
				Trailing arguments are prevented by `static_assert`, \
				and should be `flux`ed separately (scheduling is considered facile). \

				template <signed N_ion, class ..._s>
				XTAL_DEF_(return,inline,let)
				flux(same_q<event_type> auto &&o, _s &&...)
				noexcept -> signed
				{
					static_assert(none_q<_s...>);
					return self().template fuse<N_ion>(XTAL_REF_(o));
				}
				template <signed N_ion, class ..._s>
				XTAL_DEF_(return,inline,let)
				flux(flow::cue_s<> v, in_q<Ys...> auto &&x, _s &&...)
				noexcept -> signed
				requires multiple_q<Ys...>
				{
					static_assert(none_q<_s...>);
					return flux<N_ion>(event_type{v.head(), XTAL_REF_(x)});
				}
				template <signed N_ion, class ..._s>
				XTAL_DEF_(return,inline,let)
				flux(flow::cue_s<> v, same_q<payload_type> auto &&w, _s &&...)
				noexcept -> signed
				{
					static_assert(none_q<_s...>);
					return flux<N_ion>(event_type{v.head(), XTAL_REF_(w)});
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
	
		template <class ...Ys>
		using S_inqueue = typename S_::template inqueue<Ys...>;

	public:
		using S_::S_;
		using S_::self;

		template <class ...Ys>
		struct inqueue : S_inqueue<Ys...>
		{
			using kind = confined<S_inqueue<Ys...>>;
			using type = bond::compose_s<S_, kind>;
		
		};
		template <class ...Ys>
		using inqueue_t = typename inqueue<Ys...>::type;

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
