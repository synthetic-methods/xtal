#pragma once
#include "./any.hh"
#include "./couple.hh"





XTAL_ENV_(push)
namespace xtal::atom
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
Extends `couple` with `operator*` redefined by the scalar product. \

template <class ..._s>	struct  dot;
template <class ..._s>	using   dot_t = typename dot<_s...>::type;
template <class ..._s>	concept dot_q = bond::array_tag_p<dot_t, _s...> and fixed_shaped_q<_s...>;

/*/
XTAL_FX0_(to) (template <auto f=_std::identity{}>
XTAL_DEF_(return,inline,let)
dot_f(auto &&...oo),
	_detail::factory<dot_t>::
		template make<f>(XTAL_REF_(oo)...))
/*/
auto constexpr dot_f = [] XTAL_1FN_(call) (_detail::factory<dot_t>::make);
/***/


////////////////////////////////////////////////////////////////////////////////

template <scalar_q ..._s> requires same_q<_s...>
struct dot<_s ...>
:	dot<common_t<_s...>[sizeof...(_s)]>
{
};
template <class ..._s>
struct dot
{
	template <class T>
	using endotype = typename couple<_s...>::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<endotype<T>, bond::tag<dot_t>>;

	template <class T>
	class homotype : public holotype<T>
	{
		using S_ = holotype<T>;

	public:// CONSTRUCT
		using S_::S_;

	public:// OPERATE

		XTAL_DEF_(return,inline,let)
		operator * (auto const &t) const
		noexcept -> auto
		{
			return S_::product(t);
		}

	};
	using type = bond::derive_t<homotype>;

};
template <scalar_q U>
struct dot<U>
:	dot<U[2]>
{
};


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
