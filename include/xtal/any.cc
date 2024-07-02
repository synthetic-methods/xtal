#pragma once
#include "./etc.cc"
#include "./occur/all.hh"
#include "./process/any.hh"
#include "./resource/all.hh"

#include <Eigen/Core>

XTAL_ENV_(push)
namespace xtal::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <int N_index>
XTAL_DEF_(return)
XTAL_LET check_f(auto const &u, auto const &v)
XTAL_0EX -> bool
{
	return bond::computrim_f<N_index>(u) == bond::computrim_f<N_index>(v);
}
template <int N_index, int N_limit>
XTAL_DEF_(return)
XTAL_LET check_f(auto const &u, auto const &v)
XTAL_0EX -> int
{
	XTAL_LET Z_index = sign_n<N_index>;
	XTAL_LET Z_limit = sign_n<N_limit>;
	static_assert(Z_index == Z_limit);

	XTAL_IF0
	XTAL_0IF (Z_limit*N_limit <  Z_index*N_index) {
		return check_f<N_limit, N_index>(u, v);
	}
	XTAL_0IF (Z_limit*N_limit == Z_index*N_index) {
		return 0;
	}
	XTAL_0IF (Z_index == -1) {
		return check_f<N_index>(u, v)? N_index: check_f<Z_index + N_index, N_limit>(u, v);
	}
	XTAL_0IF (Z_index ==  1) {
		return check_f<N_limit>(u, v)? N_limit: check_f<N_index, N_limit - Z_limit>(u, v);
	}
}
XTAL_DEF_(return)
XTAL_LET check_f(auto const &u, auto const &v)
XTAL_0EX -> int
{
	return check_f<-1, 1 - (int) bond::operating::fraction.depth>(u, v);
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

using namespace bond;

using Ox_scale = occur::reinferred_t<class A_scale, typename bond::operating::alpha_type>;
using Ox_level = occur::reinferred_t<class A_level, typename bond::operating::alpha_type>;
/*/
using Ox_onset = occur::reinferred_t<class onset_a, typename bond::operating::alpha_type>;
/*/
struct onset
:	occur::confer<typename bond::operating::alpha_type
	,	occur::any<class onset_a>
	,	bond::word<(1 << 7)>
	>
{
};
using Ox_onset = occur::confined_t<onset>;
/***/

////////////////////////////////////////////////////////////////////////////////

struct mix
{
	class type : public process::confine_t<type>
	{
	public:

		XTAL_DEF_(return,inline)
		XTAL_LET method(auto &&...xs)
		XTAL_0FX -> auto
		{
			return (XTAL_REF_(xs) +...+ 0);
		}

	};
};
using Px_mix = typename mix::type;


struct static_onset_mix
{
	class type : public process::confine_t<type
	,	Ox_onset::dispatch<>
	>
	{
	public:

		template <size_type onset=0>
		XTAL_DEF_(return,inline,static)
		XTAL_LET function(auto &&...xs)
		XTAL_0EX
		{
			return (XTAL_REF_(xs) +...+ onset);
		}

	};
};
using Px_static_onset_mix = typename static_onset_mix::type;


struct dynamic_onset_mix
{
	class type : public process::confine_t<type, Ox_onset::attach<>>
	{
	public:

		XTAL_DEF_(return,inline)
		XTAL_LET method(auto &&...xs)
		XTAL_0EX -> auto
		{
			return (XTAL_REF_(xs) +...+ this->template head<Ox_onset>());
		}

	};
};
using Px_dynamic_onset_mix = typename dynamic_onset_mix::type;


////////////////////////////////////////////////////////////////////////////////

struct dynamic_term
{
	class type : public process::confine_t<type, Ox_scale::attach<>>
	{
	public:

		XTAL_DEF_(return,inline)
		XTAL_LET method(auto &&x)
		XTAL_0EX -> auto
		{
			return XTAL_REF_(x)*this->template head<Ox_scale>();
		}

	};
};
using Px_dynamic_term = typename dynamic_term::type;


////////////////////////////////////////////////////////////////////////////////

struct dynamic_count
{
	using U_count  = typename bond::operating::delta_type;
	using U_restep = occur::restep_t<U_count>;

	template <class T>
	using homotype = process::confine_t<T, U_restep::attach<>>;

	struct type : public homotype<type>
	{
		using T_ = homotype<type>;
	
	public:
		using T_::T_;

		XTAL_DEF_(return,inline)
		XTAL_LET method()
		XTAL_0EX -> auto
		{
			auto i = u_count; u_count += this->template head<U_restep>();
			return i;
		}

	private:
		U_count u_count = 0;

	};
};
using Px_dynamic_count = typename dynamic_count::type;


////////////////////////////////////////////////////////////////////////////////

TAG_("maligned")
{
	TRY_("allocation stepping") {
		size_type i{};
		TRUE_(maligned_f<_std::byte   >(i) == 0x0);
		TRUE_(maligned_f<_std::int16_t>(i) == 0x2);
		TRUE_(maligned_f<_std::byte   >(i) == 0x4);
		TRUE_(maligned_f<_std::byte   >(i) == 0x5);
		TRUE_(maligned_f<_std::int16_t>(i) == 0x6);
		TRUE_(maligned_f<_std::byte   >(i) == 0x8);
		TRUE_(maligned_f<_std::int16_t>(i) == 0xA);
	}
}


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
/**/
template <xtal::iterated_q T, ::std::invocable<xtal::iteratee_t<T>> U>
XTAL_DEF_(return,inline)
XTAL_LET operator | (T &&t, U &&u)
XTAL_0EX -> decltype(auto)
{
	return XTAL_REF_(t)|::ranges::views::transform(XTAL_REF_(u));
};
/***/
XTAL_ENV_(pop)
