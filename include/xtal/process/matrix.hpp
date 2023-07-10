#pragma once
#include "./any.hpp"

#include "../context/shard.hpp"




XTAL_ENV_(push)
namespace xtal::process
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ...>
struct matrix;

template <typename ...Ts>
XTAL_ASK matrix_q = tag_q<matrix, Ts...>;

template <typename ..._s>
XTAL_USE matrix_t = confined_t<matrix<_s...>>;

template <typename ..._s>
XTAL_CN2 matrix_f(XTAL_DEF w) {return matrix_t<decltype(w), _s...>(XTAL_REF_(w));}


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

template <typename W, typename U, typename... As>
struct matrix<W, U, As...>
{
	static_assert(bundle_q<W>);
	using subkind = compose<conflux::defer<W>, confer<U>, As..., tag<matrix>>;

	template <any_p S>
	class subtype: public compose_s<S, subkind>
	{
		using S_ = compose_s<S, subkind>;
		
	public:
		using S_::S_;
		using S_::self;
		using S_::head;
		using S_::influx;

		XTAL_FNX influx(context::shard_q auto shard_o, XTAL_DEF ...oo)
		XTAL_0EX
		{
			auto &w = bundle_part_f(head(), shard_o.tuple());
			auto &x = decltype(w) (shard_o);
			_std::swap(w, x);
			return w == x or S_::influx(XTAL_REF_(oo)...);
		}

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
