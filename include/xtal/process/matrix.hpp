#pragma once
#include "./anybody.hpp"

#include "../context/shard.hpp"




XTAL_ENV_(push)
namespace xtal::process
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ..._s> XTAL_NYM matrix;
template <typename ..._s> XTAL_ASK matrix_q =      tag_p<matrix, _s...>;
template <typename ..._s> XTAL_USE matrix_t = confined_t<matrix< _s...>>;
template <typename ...As>
XTAL_CN2 matrix_f(XTAL_DEF u) {return matrix_t<XTAL_TYP_(u), As...>(XTAL_REF_(u));}


namespace _detail
{///////////////////////////////////////////////////////////////////////////////

template <size_t N>
XTAL_CN2 dot(auto const &x, auto const &y)
{
	using namespace _std;
	static_assert(N == bundle_size_v<decltype(x)>);
	static_assert(N == bundle_size_v<decltype(y)>);
	return [&]<size_t ...I>(seek_t<I...>)
		XTAL_0FN_((get<0>(x)*get<0>(y)) +...+ (get<1 + I>(x)*get<1 + I>(y)))
	(seek_f<N - 1> {});
}


}///////////////////////////////////////////////////////////////////////////////

template <class W, class U, typename ...As>
struct matrix<W, U, As...>
{
	using shard_w = typename context::shard_s<W>::refract;
	using subkind = compose<shard_w, confer<U>, As..., tag<matrix>>;

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
			auto const     n = bundle_f(XTAL_REF_(xs)...);
			auto const    &m = head();
			auto constexpr M = bundle_size_v<decltype(m)>;
			return [&, this]<size_t ...I>(seek_t<I...>)
				XTAL_0FN_(S_::template method<Ks...>(_detail::dot<N>(n, _std::get<I>(m))...))
			(seek_f<M> {});
		})

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
