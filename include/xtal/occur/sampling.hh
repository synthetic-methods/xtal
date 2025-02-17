#pragma once
#include "./any.hh"

#include "../atom/couple.hh"




XTAL_ENV_(push)
namespace xtal::occur
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class U=unsigned>	struct   sampling;
template <class U=unsigned>	using    sampling_t = confined_t<sampling<U>>;
template <typename   ..._s>	concept  sampling_q = bond::tag_p<sampling, _s...>;

XTAL_FX0_(to) (XTAL_DEF_(return,inline,let)
sampling_f  (auto &&...oo),
sampling_t<>(XTAL_REF_(oo)...))


namespace _detail
{/////////////////////////////////////////////////////////////////////////////////

struct sampling_attachment
{
	template <class S>
	class subtype : public S
	{
	public:// CONSTRUCT
		using S::S;
		
	public:// MESSAGE

		template <extent_type N_mask=-1>
		struct attach
		{
			using superkind = typename S::template attach<N_mask>;

			template <class R>
			class subtype : public bond::compose_s<R, superkind>
			{
				static_assert(cell::any_q<R>);
				using R_ = bond::compose_s<R, superkind>;
				
			public:
				using R_::R_;
				
				XTAL_FX4_(to) (XTAL_DEF_(return,inline,get)
				sampling(), R_::head())

			};
		};

	};
};


}/////////////////////////////////////////////////////////////////////////////////

template <class U>
struct sampling
{
private:
	using U_alpha = typename bond::fit<U>::alpha_type;
	using W_alpha = atom::couple_t<U_alpha[2]>;

public:
	using superkind = bond::compose<void
	,	_detail::sampling_attachment
	,	defer<W_alpha>
	,	flow::tag<sampling>
	>;
	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind>;

	public:// CONSTRUCT
	//	using S_::S_;
		
		XTAL_NEW_(delete) (subtype, noexcept = default)
//		XTAL_NEW_(create) (subtype, noexcept = default)
		XTAL_NEW_(move)   (subtype, noexcept = default)
		XTAL_NEW_(copy)   (subtype, noexcept = default)
		XTAL_NEW_(cast)   (subtype, noexcept)

		XTAL_NEW_(explicit)
		subtype(atom::couple_q auto &&o, auto &&...oo)
		noexcept
		:	subtype{get<0>(XTAL_REF_(o)), XTAL_REF_(oo)...}
		{}
		XTAL_NEW_(explicit)
		subtype(sampling_q auto &&o, auto &&...oo)
		noexcept
		:	subtype{XTAL_REF_(o).rate(), XTAL_REF_(oo)...}
		{}
		XTAL_NEW_(explicit)
		subtype(number_q auto &&n, auto &&...oo)
		noexcept
		//\
		:	S_{W_alpha(U_alpha(n)), XTAL_REF_(oo)...}
		:	S_{W_alpha{U_alpha(n), one/U_alpha(n)}, XTAL_REF_(oo)...}
		{}
		XTAL_NEW_(implicit)
		subtype()
		noexcept
		:	subtype{1}
		{}

	public:// OPERATE

		XTAL_FX4_(to) (XTAL_DEF_(return,inline,get)   rate(), get<0>(S_::head()))
		XTAL_FX4_(to) (XTAL_DEF_(return,inline,get) period(), get<1>(S_::head()))

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
