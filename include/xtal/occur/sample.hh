#pragma once
#include "./any.hh"

#include "../atom/couple.hh"




XTAL_ENV_(push)
namespace xtal::occur
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class U=unsigned>	struct   sample;
template <class U=unsigned>	using    sample_t = confined_t<sample<U>>;
template <typename   ..._s>	concept  sample_q = bond::tag_p<sample, _s...>;

XTAL_DEF_(return,inline,let) sample_f(auto &&w)
//\
noexcept -> decltype(auto) {return sample_t<typename bond::fixture<decltype(w)>::delta_type>(XTAL_REF_(w));}
noexcept -> decltype(auto) {return sample_t<>(XTAL_REF_(w));}


//////////////////////////////////////////////////////////////////////////////////

template <class U>
struct sample
{
private:
	using _fix = bond::fixture<U>;
	using U_alpha = typename _fix::alpha_type;
	using W_alpha = atom::couple_t<U_alpha[2]>;

public:
	using superkind = bond::compose<defer<W_alpha>, flow::tag<sample>>;

	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind>;

	public:// CONSTRUCT
	//	using S_::S_;
		
	~	subtype() noexcept=default;
	//	subtype() noexcept=default;

		XTAL_NEW_(copy) (subtype, noexcept=default)
		XTAL_NEW_(move) (subtype, noexcept=default)

		XTAL_NEW_(explicit) subtype(fungible_q<subtype> auto &&o)
		noexcept
		:	subtype(static_cast<subtype &&>(XTAL_REF_(o)))
		{}

		XTAL_NEW_(explicit) subtype(atom::couple_q auto &&o, auto &&...oo)
		noexcept
		:	subtype(get<0>(XTAL_REF_(o)), XTAL_REF_(oo)...)
		{}
		XTAL_NEW_(explicit) subtype(sample_q auto &&o, auto &&...oo)
		noexcept
		:	subtype(XTAL_REF_(o).rate(), XTAL_REF_(oo)...)
		{}
		XTAL_NEW_(explicit) subtype(number_q auto &&n, auto &&...oo)
		noexcept
		//\
		:	S_(W_alpha(_fix::alpha_f(n)), XTAL_REF_(oo)...)
		:	S_(W_alpha{_fix::alpha_f(n), one/_fix::alpha_f(n)}, XTAL_REF_(oo)...)
		{}
		XTAL_NEW_(implicit) subtype()
		noexcept
		:	subtype(1)
		{}

	public:// OPERATE

		XTAL_FX4_(alias) (XTAL_DEF_(return,inline,get)   rate(), get<0>(S_::head()))
		XTAL_FX4_(alias) (XTAL_DEF_(return,inline,get) period(), get<1>(S_::head()))

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
