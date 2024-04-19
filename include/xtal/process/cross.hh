#pragma once
#include "./any.hh"
#include "../occur/indent.hh"





XTAL_ENV_(push)
namespace xtal::process
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ..._s> struct  cross;
template <typename ..._s> using   cross_t = confined_t<cross< _s...>>;
template <typename ..._s> concept cross_q = bond::tag_p<cross, _s...>;
template <typename ...As>
XTAL_FN2  cross_f(auto &&u)
XTAL_0EZ_(cross_t<XTAL_TYP_(u), As...>(XTAL_REF_(u)))


namespace _detail
{///////////////////////////////////////////////////////////////////////////////

template <size_t N>
XTAL_FN2 dot(auto const &x, auto const &y)
{
	using namespace _std;
	static_assert(N == bond::pack_size_n<decltype(x)>);
	static_assert(N == bond::pack_size_n<decltype(y)>);
	return [&]<size_t ...I>(bond::seek_t<I...>)
		XTAL_0FN_((get<0>(x)*get<0>(y)) +...+ (get<1 + I>(x)*get<1 + I>(y)))
	(bond::seek_f<N - 1> {});
}


}///////////////////////////////////////////////////////////////////////////////

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

		XTAL_DO2_(template <auto ...Ks>
		XTAL_TN2 functor(auto &&...xs),
		{
			auto constexpr N = sizeof...(xs);
			auto const     n = bond::pack_f(XTAL_REF_(xs)...);
			auto const    &m = head();
			auto constexpr M = bond::pack_size_n<decltype(m)>;
			return [&, this]<size_t ...I>(bond::seek_t<I...>)
				XTAL_0FN_(S_::template functor<Ks...>(_detail::dot<N>(n, _std::get<I>(m))...))
			(bond::seek_f<M> {});
		})

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
