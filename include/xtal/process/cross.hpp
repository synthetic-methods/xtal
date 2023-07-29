#pragma once
#include "./anybody.hpp"

#include "../context/shard.hpp"




XTAL_ENV_(push)
namespace xtal::process
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ..._s> XTAL_NYM cross;
template <typename ..._s> XTAL_ASK cross_q =      tag_p<cross, _s...>;
template <typename ..._s> XTAL_USE cross_t = confined_t<cross< _s...>>;
template <typename ...As>
XTAL_CN2 cross_f(XTAL_DEF u) {return cross_t<XTAL_TYP_(u), As...>(XTAL_REF_(u));}


namespace _detail
{///////////////////////////////////////////////////////////////////////////////

template <size_t N>
XTAL_CN2 dot(auto const &x, auto const &y)
{
	using namespace _std;
	static_assert(N == pack_size_v<decltype(x)>);
	static_assert(N == pack_size_v<decltype(y)>);
	return [&]<size_t ...I>(seek_t<I...>)
		XTAL_0FN_((get<0>(x)*get<0>(y)) +...+ (get<1 + I>(x)*get<1 + I>(y)))
	(seek_f<N - 1> {});
}


}///////////////////////////////////////////////////////////////////////////////

template <class W, class U, typename ...As>
struct cross<W, U, As...>
{
	using shard_w = typename context::shard_s<W>::refract;
	using subkind = compose<shard_w, confer<U>, As..., tag<cross>>;

	template <any_q S>
	class subtype: public compose_s<S, subkind>
	{
		using S_ = compose_s<S, subkind>;
		
	public:
		using S_::S_;
		using S_::self;
		using S_::head;

		XTAL_DO2_(template <auto ...Ks>
		XTAL_FN2 method(XTAL_DEF... xs),
		{
			auto constexpr N = sizeof...(xs);
			auto const     n = pack_f(XTAL_REF_(xs)...);
			auto const    &m = head();
			auto constexpr M = pack_size_v<decltype(m)>;
			return [&, this]<size_t ...I>(seek_t<I...>)
				XTAL_0FN_(S_::template method<Ks...>(_detail::dot<N>(n, _std::get<I>(m))...))
			(seek_f<M> {});
		})

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)