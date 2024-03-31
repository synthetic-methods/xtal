#pragma once
#include "./any.cc"
#include "./chain.ii"// testing...





XTAL_ENV_(push)
namespace xtal::process::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

struct square_root
{
	template <class S>
	class subtype: public bond::compose_s<S>
	{
		using S_ = bond::compose_s<S>;

	public:
		using S_::S_;

		template <auto ...>
		XTAL_FN2 function(auto &&o)
		XTAL_0EX
		{
			return _std::sqrt(o);
		}

	};
};
using square_root_t = confined_t<square_root>;

struct halve
{
	template <class S>
	class subtype: public bond::compose_s<S>
	{
		using S_ = bond::compose_s<S>;

	public:
		using S_::S_;

		template <auto ...>
		XTAL_FN2 function(auto &&o)
		XTAL_0EX
		{
			return o*0.5L;
		}

	};
};
using halve_t = confined_t<halve>;


////////////////////////////////////////////////////////////////////////////////
/**/
TAG_("chain")
{
	using re = bond::realized;
	using T_sigma = typename re::sigma_t;
	using T_delta = typename re::delta_t;
	using T_alpha = typename re::alpha_t;

	TRY_("compose")
	{
		using halve_square_root_t = chain_t<halve_t, square_root_t>;
		using square_root_halve_t = chain_t<square_root_t, halve_t>;
		
		TRUE_(2L == halve_square_root_t::function(16L));
		TRUE_(3L == square_root_halve_t::function(18L));

		TRUE_(2L == halve_square_root_t {}.method(16L));
		TRUE_(3L == square_root_halve_t {}.method(18L));

	}
}
/***/

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
