#pragma once
#include "./occur/all.hh"
#include "./process/any.hh"
#include "./resource/all.hh"
#include <catch2/catch_all.hpp>

#define UNTRUE_(...)   REQUIRE(not (__VA_ARGS__))
#define   TRUE_(...)   REQUIRE(    (__VA_ARGS__))
#define    TRY_(...)   SECTION(    (__VA_ARGS__))
#define    EST_(...) BENCHMARK(    (__VA_ARGS__))

#define TAG_(...) TEST_CASE(__FILE__ ":" XTAL_S1_(__LINE__), TAG_N_(__VA_ARGS__))
#define TAG_N_(...)                                 XTAL_F1_(TAG_1_,__VA_ARGS__)
#define TAG_1_(...)                                             "[" __VA_ARGS__ "]"


XTAL_ENV_(push)
namespace xtal::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

using namespace bond;

using scale_t = occur::inferred_t<class scale_a, typename bond::realized::alpha_t>;
using level_t = occur::inferred_t<class level_a, typename bond::realized::alpha_t>;
/*/
using onset_t = occur::inferred_t<class onset_a, typename bond::realized::alpha_t>;
/*/
struct onset
:	occur::confer<typename bond::realized::alpha_t
	,	occur::any<class onset_a>
	,	bond::assay<(1 << 7)>
	>
{
};
using onset_t = occur::confined_t<onset>;
/***/

////////////////////////////////////////////////////////////////////////////////

struct mix
{
	class type : public process::confine_t<type>
	{
	public:

		XTAL_TN2 functor(auto &&...xs)
		XTAL_0FX
		{
			return (XTAL_REF_(xs) +...+ 0);
		}

	};
};
using mix_t = typename mix::type;


struct static_onset_mix
{
	class type : public process::confine_t<type
	,	onset_t::dispatch<>
	>
	{
	public:

		template <size_t onset=0>
		XTAL_FN2 function(auto &&...xs)
		XTAL_0EX
		{
			return (XTAL_REF_(xs) +...+ onset);
		}

	};
};
using static_onset_mix_t = typename static_onset_mix::type;


struct dynamic_onset_mix
{
	class type : public process::confine_t<type, onset_t::attach<>>
	{
	public:

		XTAL_TN2 functor(auto &&...xs)
		XTAL_0EX
		{
			return (XTAL_REF_(xs) +...+ this->template head<onset_t>());
		}

	};
};
using dynamic_onset_mix_t = typename dynamic_onset_mix::type;


////////////////////////////////////////////////////////////////////////////////

struct dynamic_term
{
	class type : public process::confine_t<type, scale_t::attach<>>
	{
	public:

		XTAL_TN2 functor(auto &&x)
		XTAL_0EX
		{
			return XTAL_REF_(x)*this->template head<scale_t>();
		}

	};
};
using dynamic_term_t = typename dynamic_term::type;


////////////////////////////////////////////////////////////////////////////////

struct dynamic_count
{
	using U_count  = typename bond::realized::iota_t;
	using U_restep = occur::restep_t<U_count>;

	template <class T>
	using homotype = process::confine_t<T, U_restep::attach<>>;

	struct type : public homotype<type>
	{
		using T_ = homotype<type>;
	
	public:
		using T_::T_;

		XTAL_TN2 functor()
		XTAL_0EX
		{
			auto i = u_count; u_count += this->template head<U_restep>();
			return i;
		}

	private:
		U_count u_count = 0;

	};
};
using dynamic_count_t = typename dynamic_count::type;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
