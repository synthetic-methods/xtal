#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::flow
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
///\
Wrapper used to index an existing type. \

///\see e.g. [../processor/polymer.hh]. \

template <class ..._s>	struct  key;
template <class ..._s>	concept key_q = bond:: tagged_p<key    , _s...>;
template <class ..._s>	using   key_s = bond::compose_s<packet_t<_s...>, cell::confined<key<>>>;
template <class ..._s>	using   key_t = bond::compose_s<packed_t<_s...>, cell::confined<key<>>>;

////////////////////////////////////////////////////////////////////////////////

template <>
struct key<>
{
	using superkind = cell::confer<signed, bond::tag<key>>;

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
		noexcept -> decltype(auto)
		requires same_q<T_, key_s<>>
		{
			return key_s<XTAL_ALL_(u)>(S_::self(), XTAL_REF_(u));
		}

		using key_layout = U_[1];

	};
	template <key_q S>
	class subtype<S> : public bond::compose_s<S, superkind>
	{
		using S_ = bond::compose_s<S, superkind>;

	public:
		using S_::S_;

		XTAL_DEF_(return,inline,let)
		operator << (any_q auto &&u)
		noexcept -> decltype(auto)
		{
			return key_s<>(S_::head()) << (S_::tail() << XTAL_REF_(u));
		}

		using key_layout = succedent_s<typename S_::key_layout>;

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)

