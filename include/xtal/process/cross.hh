#pragma once
#include "./any.hh"
#include "../occur/indent.hh"





XTAL_ENV_(push)
namespace xtal::process
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ..._s> struct   cross;
template <typename ..._s> using    cross_t = confined_t<cross<_s...>>;
template <typename ..._s> concept  cross_q = bond::tag_p<cross, _s...>;
template <typename ...As>
XTAL_DEF_(return,inline,let)
cross_f(auto &&u)
noexcept -> auto
{
	return cross_t<XTAL_ALL_(u), As...>(XTAL_REF_(u));
}


////////////////////////////////////////////////////////////////////////////////

template <class W, class U, typename ...As>
struct cross<W, U, As...>
{
	using superkind = bond::compose<void
	,	typename occur::indent_s<W>::template incept<>
	,	confer<U>
	,	As...
	,	bond::tag<cross>
	>;

	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind>;
		
	public:
		using S_::S_;
		using S_::self;
		using S_::head;

		template <auto ...Is>
		XTAL_DEF_(return,let)
		method(auto &&...xs) const
		noexcept -> auto
		{
			auto const &x_ = head();
			auto const  y  = bond::pack_f(XTAL_REF_(xs)...);
			return [&, this]<auto ...I>(bond::seek_t<I...>)
				XTAL_0FN_(to) (S_::template method<Is...>(bond::pack_dot_f(get<I>(x_), y)...))
			(bond::seek_s<bond::pack_size_n<decltype(x_)>> {});
		}

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
