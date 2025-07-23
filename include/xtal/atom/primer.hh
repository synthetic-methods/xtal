#pragma once
#include "./any.hh"
#include "./block.hh"





XTAL_ENV_(push)
namespace xtal::atom
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/*!
\brief  	Extends `block` initialized with the prime numbers.
\note   	Size must be exactly `0x80`, for now.
*/

template <class ...Us>	struct  primer;
template <class ...Us>	using   primer_t = typename primer<Us...>::type;
template <class ...Us>	concept primer_q = bond::tag_infixed_p<primer_t, Us...>;

XTAL_DEF_(let) primer_f = [] XTAL_1FN_(call) (_detail::factory_f<primer_t>);


////////////////////////////////////////////////////////////////////////////////

template <class U, auto  N, auto  ...Ns> struct   primer<U   [N][Ns]...> : primer<primer_t<U[Ns]...>   [N]> {};
template <class U, auto  N, auto  ...Ns> struct   primer<U(&)[N][Ns]...> : primer<primer_t<U[Ns]...>(&)[N]> {};


////////////////////////////////////////////////////////////////////////////////

template <scalar_q ...Us> requires common_q<Us...>
struct primer<Us ...>
:	primer<common_t<Us...>[sizeof...(Us)]>
{
};
template <class ...Us>
struct primer
{
	using _fit = bond::fit<Us...>;

	template <class T>
	using endotype = typename block<Us...>::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<endotype<T>, bond::tag<primer_t>>;

	template <class T>
	class homotype : public holotype<T>
	{
		using S_ = holotype<T>;

		static_assert(S_::size() == 0x80);

	public:// CONSTRUCT
		using S_::S_;

		XTAL_NEW_(implicit)
		homotype()
		noexcept
		:	S_{  2U
			,	  3U// 2^2 - 1
			,	  5U
			,	  7U// 2^3 - 1
			,	 11U
			,	 13U
			,	 17U
			,	 19U
			,	 23U
			,	 29U
			,	 31U// 2^5 - 1
			,	 37U
			,	 41U
			,	 43U
			,	 47U
			,	 53U
			,	 59U
			,	 61U
			,	 67U
			,	 71U
			,	 73U
			,	 79U
			,	 83U
			,	 89U
			,	 97U
			,	101U
			,	103U
			,	107U
			,	109U
			,	113U
			,	127U// 2^7 - 1
			,	131U
			,	137U
			,	139U
			,	149U
			,	151U
			,	157U
			,	163U
			,	167U
			,	173U
			,	179U
			,	181U
			,	191U
			,	193U
			,	197U
			,	199U
			,	211U
			,	223U
			,	227U
			,	229U
			,	233U
			,	239U
			,	241U
			,	251U
			,	257U
			,	263U
			,	269U
			,	271U
			,	277U
			,	281U
			,	283U
			,	293U
			,	307U
			,	311U
			,	313U
			,	317U
			,	331U
			,	337U
			,	347U
			,	349U
			,	353U
			,	359U
			,	367U
			,	373U
			,	379U
			,	383U
			,	389U
			,	397U
			,	401U
			,	409U
			,	419U
			,	421U
			,	431U
			,	433U
			,	439U
			,	443U
			,	449U
			,	457U
			,	461U
			,	463U
			,	467U
			,	479U
			,	487U
			,	491U
			,	499U
			,	503U
			,	509U
			,	521U
			,	523U
			,	541U
			,	547U
			,	557U
			,	563U
			,	569U
			,	571U
			,	577U
			,	587U
			,	593U
			,	599U
			,	601U
			,	607U
			,	613U
			,	617U
			,	619U
			,	631U
			,	641U
			,	643U
			,	647U
			,	653U
			,	659U
			,	661U
			,	673U
			,	677U
			,	683U
			,	691U
			,	701U
			,	709U
			,	719U
			}
		{
		}

	};
	using type = bond::derive_t<homotype>;

};


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
