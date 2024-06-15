#pragma once
#include "./any.hh"
#include "../occur/indent.hh"





XTAL_ENV_(push)
namespace xtal::process
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ..._s> XTAL_TYP cross;
template <typename ..._s> XTAL_USE cross_t = confined_t<cross<_s...>>;
template <typename ..._s> XTAL_REQ cross_q = bond::any_tag_p<cross, _s...>;
template <typename ...As>
XTAL_DEF_(return,inline)
XTAL_LET     cross_f(auto &&u)
XTAL_0EX_TO_(cross_t<XTAL_ALL_(u), As...>(XTAL_REF_(u)))


////////////////////////////////////////////////////////////////////////////////

template <class W, class U, typename ...As>
struct cross<W, U, As...>
{
	using W_indent = typename occur::indent_s<W>::template funnel<>;
	using subkind = bond::compose<W_indent, confer<U>, As..., bond::tag<cross>>;

	template <any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;
		
	public:
		using S_::S_;
		using S_::self;
		using S_::head;

		XTAL_DO2_(template <auto ...Is>
		XTAL_DEF_(return,inline)
		XTAL_RET functor(auto &&...xs),
		{
			auto const &y_ = head();
			auto const  x  = bond::pack_f(XTAL_REF_(xs)...);
			return [&, this]<size_type ...I>(bond::seek_t<I...>)
				XTAL_0FN_(S_::template functor<Is...>(bond::pack_dot_f(x, get<I>(y_))...))
			(bond::seek_s<bond::pack_size_n<decltype(y_)>> {});
		})

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
