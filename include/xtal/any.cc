#pragma once
#include "./process/any.ii"
#include "./message/any.ii"
#include "./message/restep.ii"

#include <catch2/catch_all.hpp>


#define UNTRUE_(...)   REQUIRE(not (__VA_ARGS__))
#define   TRUE_(...)   REQUIRE(    (__VA_ARGS__))
#define    TRY_(...)   SECTION(    (__VA_ARGS__))
#define    EST_(...) BENCHMARK(    (__VA_ARGS__))

#define TAG_(...) TEST_CASE(__FILE__ ":" XTAL_S1_(__LINE__), TAG_N_(__VA_ARGS__))
#define TAG_N_(...)                                 XTAL_F1_(TAG_1_,__VA_ARGS__)
#define TAG_1_(...)                                             "[" __VA_ARGS__ "]"


XTAL_ENV_(push)
namespace xtal::__test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

using namespace common;

using scale_t = message::label_t<typename common::computer::alpha_t, class T_scale>;
using level_t = message::label_t<typename common::computer::alpha_t, class T_level>;
/*/
using onset_t = message::label_t<typename common::computer::alpha_t, class T_onset>;
/*/
struct onset
{
	using subkind = message::confer<typename common::computer::alpha_t, message::any<class T_onset>>;
	template <class S>
	class subtype: public compose_s<S, subkind>
	{
		using S_ = compose_s<S, subkind>;
	
	public:
		using S_::S_;
		
		using cardinality = cardinal_t<(128)>;
	
	};
};
using onset_t = message::confined_t<onset>;
/***/

////////////////////////////////////////////////////////////////////////////////

struct mix
{
	class type: public process::confine_t<type>
	{
	public:

		XTAL_TN2 method(XTAL_DEF ...xs)
		XTAL_0FX
		{
			return (XTAL_REF_(xs) +...+ 0);
		}

	};
};
using mix_t = typename mix::type;


struct static_onset_mix
{
	class type: public process::confine_t<type
	,	onset_t::dispatch<>
	>
	{
	public:

		template <auto onset>
		XTAL_TN2 method(XTAL_DEF ...xs)
		XTAL_0FX
		{
			return (XTAL_REF_(xs) +...+ onset);
		}
		template <auto onset>
		XTAL_TN2 method(XTAL_DEF ...xs)
		XTAL_0EX
		{
			return (XTAL_REF_(xs) +...+ onset);
		}

	};
};
using static_onset_mix_t = typename static_onset_mix::type;


struct dynamic_onset_mix
{
	class type: public process::confine_t<type, onset_t::assign<>>
	{
	public:

		XTAL_TN2 method(XTAL_DEF ...xs)
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
	class type: public process::confine_t<type, scale_t::assign<>>
	{
	public:

		XTAL_TN2 method(XTAL_DEF x)
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
	using count_t  = typename common::computer::iota_t;
	using restep_u = message::restep_t<count_t>;

	template <class T>
	using homotype = process::confine_t<T, restep_u::assign<>>;

	struct type: public homotype<type>
	{
		using co = homotype<type>;
	
	public:
		using co::co;

		XTAL_TN2 method()
		XTAL_0EX
		{
			auto i = count; count += this->template head<restep_u>();
			return i;
		}

	protected:
		count_t count = 0;

	};
};
using dynamic_count_t = typename dynamic_count::type;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)