#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::occur
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class U=size_type>	struct   sample;
template <class U=size_type>	using    sample_t = confined_t<sample<U>>;
template <typename    ..._s>	concept  sample_q = bond::tag_p<sample, _s...>;


//////////////////////////////////////////////////////////////////////////////////

template <class W>
struct sample
{
private:
	using _op = bond::operate<W>;
	using U = typename _op:: iota_type;
	using V = typename _op::alpha_type;

	static constexpr U U_1{1};
	static constexpr V V_1{1};

	using M = bond::pack_t<U, V>;

public:
	using superkind = bond::compose<defer<M>, bond::tag<sample>>;

	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind>;

	public:
	//	using S_::S_;
		
	~	subtype() noexcept=default;
	//	subtype() noexcept=default;

		XTAL_NEW_(copy, subtype, noexcept=default)
		XTAL_NEW_(move, subtype, noexcept=default)

		XTAL_NEW_(explicit) subtype(fungible_q<subtype> auto &&o)
		noexcept
		:	subtype(static_cast<subtype &&>(XTAL_REF_(o)))
		{}

		XTAL_NEW_(implicit) subtype()
		noexcept
		:	subtype(1)
		{}
		XTAL_NEW_(explicit) subtype(integral_number_q auto n, auto &&...oo)
		noexcept
		:	S_(M{n, 0 == n? 0: V_1/n}, XTAL_REF_(oo)...)
		{}
		XTAL_NEW_(explicit) subtype(real_number_q auto u, auto &&...oo)
		noexcept
		:	S_(M{0 == u? 0: U_1/u, u}, XTAL_REF_(oo)...)
		{}

		XTAL_TO4_(XTAL_DEF_(let)   rate(), get<0>(S_::head()))
		XTAL_TO4_(XTAL_DEF_(let) period(), get<1>(S_::head()))

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
