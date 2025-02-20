#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::flow
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
///\
Used for scheduling any type by prefixing with an integral delay. \
May be stacked in order to described integral fades. \

template <class ..._s>	struct  cue;
template <class ..._s>	concept cue_q = bond:: tagged_p<cue , _s...>;
template <class ..._s>	using   cue_s = bond::compose_s<let_t<_s...>, cell::confined<cue<>>>;


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

	public:
		using S_::S_;

		XTAL_DEF_(return,inline,let)
		operator << (auto &&u)
		noexcept -> decltype(auto)
		{
			return S_::operator<<(XTAL_REF_(u));
		}
		XTAL_DEF_(return,inline,let)
		operator << (any_q auto &&u)
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
		operator << (any_q auto &&u)
		noexcept -> auto
		{
			return cue_s<>(S_::head()) << (S_::tail() << XTAL_REF_(u));
		}

		using cue_layout = succedent_s<typename S_::cue_layout>;

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
