#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::cell
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/*!
\brief  	Opaque wrapper for `any_q`.
\note   	The supplied `...As` must include a self-`tag`ged decorator to support reparameterization.

The supplied types `...As` are composed via `reinfers` then `confined`,
providing an opaque decorator for labelling/ordering other types of `cell::any_q`.

Opaque w.r.t. operations/comparators making it suitable candidate for labelling/ordering,
while transparently convertible to the underlying type.
*/
template <typename ...As>
struct  header;


namespace _detail
{///////////////////////////////////////////////////////////////////////////////

template <typename ...As>
struct beheader
{
	using superkind = reinfers<As...>;
	using supertype = confined_t<superkind>;

	static_assert(bond::tab_q<supertype>);

	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		using S_ = bond::compose_s<S, superkind>;
		using T_ = typename S_::self_type;
		using L_ = typename S_::tail_type;
		XTAL_DEF_(set) x_ = [] (auto &&o) XTAL_0FN_(to) (XTAL_REF_(o).tail().head());

	public:// CONSTRUCT
		using S_::S_;

		XTAL_FX4_(to) (XTAL_DEF_(return,inline,implicit)
		operator L_(), S_::tail())

	public:// OPERATE
		using S_::operator==;
		using S_::operator<=>;

		XTAL_DEF_(return,inline,let)
		operator == (subtype const &t) const
		noexcept -> bool
		requires complete_q<_std::variant_size<typename L_::head_type>>
		{
			auto const &s = S_::self();
			return s.operator==(t) and x_(s).index() == x_(t).index();
		}
		/*/
		template <bond::tab_comparable_q<T_> W> requires infungible_q<subtype, W>
		XTAL_DEF_(return,inline,let)
		operator == (W const &w) const
		noexcept -> bool
		{
			return S_::head() == w.head();
		}
		template <bond::tab_comparable_q<T_> W> requires infungible_q<subtype, W>
		XTAL_DEF_(return,inline,let)
		operator <=> (W const &w) const
		noexcept -> bool
		{
			return S_::head() <=> w.head();
		}
		/***/

		XTAL_DEF_(return,inline,let)
		operator << (auto &&u) const
		noexcept -> auto
		{
			return S_::operator<<(XTAL_REF_(u));
		}
		XTAL_DEF_(return,inline,let)
		operator << (any_q auto &&u) const
		noexcept -> auto
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
		using layout_type = L_[1];

	};
	template <bond::tab_comparable_q<supertype> S>
	class subtype<S> : public bond::compose_s<S, superkind>
	{
		using S_ = bond::compose_s<S, superkind>;

	public:
		using S_::S_;

		XTAL_DEF_(return,inline,let)
		operator << (auto &&u) const
		noexcept -> auto
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
