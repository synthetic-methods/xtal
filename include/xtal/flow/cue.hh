#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::flow
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
///\
Insulated header for a `flow::let_t<_s...>` `tail`. \
Opaque w.r.t. operations/comparators making it suitable candidate for labelling/ordering. \

///\
Used for scheduling any type by prefixing with an integral delay. \
May be stacked in order to described integral fades. \

template <class ..._s>	struct  cue;
template <class ..._s>	concept cue_q = bond:: tagged_p<cue , _s...>;
template <class ..._s>	using   cue_s = bond::compose_s<let_t<_s...>, cell::confined<cue<>>>;

template <class ..._s>
XTAL_FX0_(to) (XTAL_DEF_(return,inline,let)
cue_f       (auto &&...oo),
cue_s<_s...>(XTAL_REF_(oo)...))


////////////////////////////////////////////////////////////////////////////////

template <>
struct cue<>
{
	using superkind = cell::confer<signed, bond::tag<cue>>;

	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		using S_ = bond::compose_s<S, superkind>;
		using T_ = typename S_::self_type;
		using W_ = typename S_::tail_type;
		using X_ = typename W_::head_type;

	public:// CONSTRUCT
		using S_::S_;

	public:// OPERATE
		/*/
		XTAL_DEF_(return,inline,let)
		operator == (subtype const &t) const
		noexcept -> bool
		{
			if constexpr (complete_q<_std::variant_size<X_>>) {
				return S_::operator==(t) and S_::tail() == t.tail();
			}
			else {
				return S_::operator==(t);
			}
		}
		/***/
		XTAL_DEF_(return,inline,let)
		operator << (auto &&u) const
		noexcept -> decltype(auto)
		{
			return S_::operator<<(XTAL_REF_(u));
		}
		XTAL_DEF_(return,inline,let)
		operator << (any_q auto &&u) const
		noexcept -> auto
		requires same_q<T_, cue_s<>>
		{
			return cue_s<XTAL_ALL_(u)>(S_::self(), XTAL_REF_(u));
		}

		using cue_layout = typename S_::tail_type[1];

	};
	template <cue_q S>
	class subtype<S> : public bond::compose_s<S, superkind>
	{
		using S_ = bond::compose_s<S, superkind>;

	public:
		using S_::S_;

		XTAL_DEF_(return,inline,let)
		operator << (any_q auto &&u) const
		noexcept -> auto
		{
			return cue_f(S_::head()) << (S_::tail() << XTAL_REF_(u));
		}

		using cue_layout = succedent_s<typename S_::cue_layout>;

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
