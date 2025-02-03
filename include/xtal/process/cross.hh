#pragma once
#include "./any.hh"
#include "../flow/indent.hh"





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
	using W_indent = typename flow::indent_s<W>::template afflux<>;
	using superkind = bond::compose<W_indent, confer<U>, As..., bond::tag<cross>>;

	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind>;
		
	public:
		using S_::S_;
		using S_::self;
		using S_::head;

		XTAL_FX2_(do) (template <auto ...Is>
		XTAL_DEF_(return,let)
		method(auto &&...xs),
		noexcept -> decltype(auto)
		{
			auto const &y_ = head();
			auto const  x  = bond::pack_f(XTAL_REF_(xs)...);
			return [&, this]<auto ...I>(bond::seek_t<I...>)
				XTAL_0FN_(return) (S_::template method<Is...>(bond::pack_dot_f(x, get<I>(y_))...))
			(bond::seek_s<bond::pack_size_n<decltype(y_)>> {});
		})

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
