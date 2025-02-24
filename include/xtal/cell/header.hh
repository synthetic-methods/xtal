#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::cell
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
///\
Insulated header abstraction. \
The supplied `..._s` are composed via `reinfers` then `confined`, \
providing an opaque decorator for labelling/ordering other `cells`. \

///\see `flow/cue.hh` for example usage. \

///\note\
The supplied `..._s` must be `tag`ged with the type-constructor \
to support reparameterization. \


template <typename ..._s>
struct  header;


namespace _detail
{///////////////////////////////////////////////////////////////////////////////

template <typename ..._s>
struct beheader
{
	using superkind = reinfers<_s...>;
	using supertype = confined_t<superkind>;

	static_assert(bond::intab_q<supertype>);

	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		using S_ = bond::compose_s<S, superkind>;
		using T_ = typename S_::self_type;
		using R_ = typename S_::tail_type;
		using X_ = typename R_::head_type;
		XTAL_DEF_(set) x_ = [] (auto &&o) XTAL_0FN_(to) (XTAL_REF_(o).tail().head());

	public:// CONSTRUCT
		using S_::S_;

	public:// OPERATE
		using S_::operator==;

		XTAL_DEF_(return,inline,let)
		operator == (subtype const &t) const
		noexcept -> bool
		requires complete_q<_std::variant_size<X_>>
		{
			auto const &s = S_::self();
			return s.operator==(t) and x_(s).index() == x_(t).index();
		}

		XTAL_DEF_(return,inline,let)
		operator << (auto &&u) const
		noexcept -> decltype(auto)
		{
			return S_::operator<<(XTAL_REF_(u));
		}
		XTAL_DEF_(return,inline,let)
		operator << (any_q auto &&u) const
		noexcept -> decltype(auto)
		{
			using  V_ = bond::compose_s<S_, bond::tagged<>>;
			using  U_ = bond::compose_s<S_, bond::tagged<XTAL_ALL_(u)>>;
			if constexpr (same_q<T_, V_>) {
				return U_(S_::self(), XTAL_REF_(u));
			}
			else {
				return S_::operator<<(XTAL_REF_(u));
			}
		}
		using layout_type = typename S_::tail_type[1];

	};
	template <bond::tab_comparable_q<supertype> S>
	class subtype<S> : public bond::compose_s<S, superkind>
	{
		using S_ = bond::compose_s<S, superkind>;

	public:
		using S_::S_;

		XTAL_DEF_(return,inline,let)
		operator << (auto &&u) const
		noexcept -> decltype(auto)
		{
			return S_::operator<<(XTAL_REF_(u));
		}
		XTAL_DEF_(return,inline,let)
		operator << (any_q auto &&u) const
		noexcept -> auto
		{
			using  V_ = bond::compose_s<S_, bond::tagged<>>;
			return V_(S_::head()) << (S_::tail() << XTAL_REF_(u));
		}

		using layout_type = succedent_s<typename S_::layout_type>;

	};
};


}///////////////////////////////////////////////////////////////////////////////

template <typename ...As>
struct header
:	confined<_detail::beheader<As...>>
{
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
