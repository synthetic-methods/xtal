#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::flow
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
Governs access to the `supertype`. \

///\see `flow::mask`. \

template <class ..._s>	struct  mark;
template <class ..._s>	concept mark_q = bond:: tagged_p<mark    , _s...>;
template <class ..._s>	using   mark_s = bond::compose_s<packet_t<_s...>, cell::confined<mark<>>>;
template <class ..._s>	using   mark_t = bond::compose_s<packed_t<_s...>, cell::confined<mark<>>>;

////////////////////////////////////////////////////////////////////////////////

template <>
struct mark<>
{
	using superkind = cell::confer<signed, bond::tag<mark>>;

	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		using S_ = bond::compose_s<S, superkind>;
		using U_ = XTAL_ALL_(XTAL_ANY_(S).tail());
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
		requires same_q<T_, mark_s<>>
		{
			return mark_s<XTAL_ALL_(u)>(S_::self(), XTAL_REF_(u));
		}

		using mark_layout = U_[1];

	};
	template <mark_q S>
	class subtype<S> : public bond::compose_s<S, superkind>
	{
		using S_ = bond::compose_s<S, superkind>;

	public:
		using S_::S_;

		XTAL_DEF_(return,inline,let)
		operator << (any_q auto &&u)
		noexcept -> auto
		{
			return mark_s<>(S_::head()) << (S_::tail() << XTAL_REF_(u));
		}

		using mark_layout = succedent_s<typename S_::mark_layout>;

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
