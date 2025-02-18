#pragma once
#include "./any.hh"
#include "./group.hh"





XTAL_ENV_(push)
namespace xtal::atom
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
Restricts `couple` to a mutually inverse temporal pair, \
with the components respectively identified by `rate()` and `period()`. \

template <class ..._s>	struct   tee;
template <class ..._s>	using    tee_t = typename tee<_s...>::type;
template <class ..._s>	concept  tee_q = bond::array_tag_p<tee_t, _s...> and fixed_shaped_q<_s...>;


XTAL_FX0_(to) (template <auto f=_std::identity{}>
XTAL_DEF_(return,inline,let)
tee_f(auto &&...oo),
	_detail::factory<tee_t>::
		template make<f>(XTAL_REF_(oo)...))


////////////////////////////////////////////////////////////////////////////////

template <scalar_q ..._s> requires same_q<_s...> and (2 <= sizeof...(_s))
struct tee<_s ...>
:	tee<common_t<_s...>[sizeof...(_s)]>
{
};
template <class ..._s>
struct tee
{
	template <class T>
	using endotype = typename multiplicative_group<_s...>::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<endotype<T>, bond::tag<tee_t>>;

	template <class T>
	class homotype : public holotype<T>
	{
		using S_ = holotype<T>;
	
	public:// ACCESS
		using S_::size;
		using S_::self;
		using S_::twin;

		using typename S_::value_type;
		using typename S_::scale_type;

		static_assert(2 == size() and same_q<_s...>);
		static_assert(real_variable_q<value_type>);

		XTAL_FX4_(to) (XTAL_DEF_(return,inline,get)   rate(), get<0>(self()))
		XTAL_FX4_(to) (XTAL_DEF_(return,inline,get) period(), get<1>(self()))

	public:// CONSTRUCT
		using S_::S_;
	//	NOTE: Uses the inverting-constructor `homotype(value_type const &u)`.

	};
	using type = bond::derive_t<homotype>;

};
template <scalar_q U>
struct tee<U>
:	tee<U[2]>
{
};
template <>
struct tee<>
:	tee<typename bond::fit<>::alpha_type>
{
};


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
