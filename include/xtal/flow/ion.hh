#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::flow
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
///\
Reifies the `signed` template-parameter for the `flux` and `fuse` methods. \

template <class ..._s>	struct  ion;
template <class ..._s>	concept ion_q = bond:: tagged_p<ion    , _s...>;
template <class ..._s>	using   ion_s = bond::compose_s<packet_t<_s...>, cell::confined<ion<>>>;
template <class ..._s>	using   ion_t = bond::compose_s<packed_t<_s...>, cell::confined<ion<>>>;

////////////////////////////////////////////////////////////////////////////////

template <>
struct ion<>
{
	using superkind = cell::confer<signed, bond::tag<ion>>;

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
		requires same_q<T_, ion_s<>>
		{
			return ion_s<XTAL_ALL_(u)>(S_::self(), XTAL_REF_(u));
		}

		using ion_layout = U_[1];

	};
	template <ion_q S>
	class subtype<S> : public bond::compose_s<S, superkind>
	{
		using S_ = bond::compose_s<S, superkind>;

	public:
		using S_::S_;

		XTAL_DEF_(return,inline,let)
		operator << (any_q auto &&u)
		noexcept -> auto
		{
			return ion_s<>(S_::head()) << (S_::tail() << XTAL_REF_(u));
		}

		using ion_layout = succedent_s<typename S_::ion_layout>;

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
