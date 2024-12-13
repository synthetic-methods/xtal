#pragma once
#include "./etc.cc"
#include "./occur/all.hh"
#include "./process/any.hh"
#include "./provision/all.hh"

#include <Eigen/Core>

XTAL_ENV_(push)
namespace xtal::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

static_assert(sized_n<_std::vector  <float   >> == -1);
static_assert(sized_n<_std::array   <float, 1>> ==  1);
static_assert(sized_n<_std::complex <float   >> ==  2);
static_assert(sized_n<constant_t<(unsigned) 2>> ==  2);
static_assert(sized_n<constant_t<(  signed) 2>> ==  2);


static_assert(id_q<unsigned, valued_u<constant_t<(unsigned) 2>>>);
static_assert(id_q<  signed, valued_u<constant_t<(  signed) 2>>>);

static_assert(id_q<const float(&)[2], destruct_t<const float(&)[2]>>);
static_assert(id_q<      float(&)[2], destruct_t<      float(&)[2]>>);
static_assert(id_q<const float   [2], destruct_t<const float   [2]>>);
static_assert(id_q<      float   [2], destruct_t<      float   [2]>>);
static_assert(id_q<const float &    , destruct_u<const float(&)[2]>>);
static_assert(id_q<      float &    , destruct_u<      float(&)[2]>>);
static_assert(id_q<const float      , destruct_u<const float   [2]>>);
static_assert(id_q<      float      , destruct_u<      float   [2]>>);

static_assert(id_q<const float(&)[2], destruct_t<const _std::complex<float> &>>);
static_assert(id_q<      float(&)[2], destruct_t<      _std::complex<float> &>>);
static_assert(id_q<const float   [2], destruct_t<const _std::complex<float>  >>);
static_assert(id_q<      float   [2], destruct_t<      _std::complex<float>  >>);
static_assert(id_q<const float &    , destruct_u<const _std::complex<float> &>>);
static_assert(id_q<      float &    , destruct_u<      _std::complex<float> &>>);
static_assert(id_q<const float      , destruct_u<const _std::complex<float>  >>);
static_assert(id_q<      float      , destruct_u<      _std::complex<float>  >>);

static_assert(id_q<const float(&)[2], dissolve_t<const _std::complex<float> &>>);
static_assert(id_q<      float(&)[2], dissolve_t<      _std::complex<float> &>>);
static_assert(id_q<const float   [2], dissolve_t<const _std::complex<float>  >>);
static_assert(id_q<      float   [2], dissolve_t<      _std::complex<float>  >>);
static_assert(id_q<const float &    , dissolve_u<const _std::complex<float> &>>);
static_assert(id_q<      float &    , dissolve_u<      _std::complex<float> &>>);
static_assert(id_q<const float      , dissolve_u<const _std::complex<float>  >>);
static_assert(id_q<      float      , dissolve_u<      _std::complex<float>  >>);

static_assert(id_q<      float   [2],  absolve_t<const _std::complex<float> &>>);
static_assert(id_q<      float   [2],  absolve_t<      _std::complex<float> &>>);
static_assert(id_q<      float   [2],  absolve_t<const _std::complex<float>  >>);
static_assert(id_q<      float   [2],  absolve_t<      _std::complex<float>  >>);
static_assert(id_q<      float      ,  absolve_u<const _std::complex<float>  >>);
static_assert(id_q<      float      ,  absolve_u<      _std::complex<float>  >>);
static_assert(id_q<      float      ,  absolve_u<const _std::complex<float> &>>);
static_assert(id_q<      float      ,  absolve_u<      _std::complex<float> &>>);


static_assert(            contiguous_field_q<float>);
static_assert(               simplex_field_q<float>);
static_assert(          not  complex_field_q<float>);
static_assert(          not quotient_group_q<float>);
static_assert(              quotient_group_q<  int>);
static_assert(complex_field_q<_std::complex<float>>);


////////////////////////////////////////////////////////////////////////////////

template <int N_index>
XTAL_DEF_(long)
XTAL_LET check_f(auto const &u, auto const &v)
noexcept -> bool
{
	return bond::computrim_f<N_index>(u) == bond::computrim_f<N_index>(v);
}
template <int N_index, int N_limit>
XTAL_DEF_(long)
XTAL_LET check_f(auto const &u, auto const &v)
noexcept -> int
{
	XTAL_LET Z_index = signum_n<N_index>;
	XTAL_LET Z_limit = signum_n<N_limit>;
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
XTAL_DEF_(long)
XTAL_LET check_f(auto const &u, auto const &v)
noexcept -> int
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

		XTAL_DEF_(short)
		XTAL_LET method(auto &&...xs) const
		noexcept -> auto
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

		template <auto onset=0>
		XTAL_DEF_(short,static)
		XTAL_LET function(auto &&...xs)
		noexcept -> auto
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

		XTAL_DEF_(short)
		XTAL_LET method(auto &&...xs)
		noexcept -> auto
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

		XTAL_DEF_(short)
		XTAL_LET method(auto &&x)
		noexcept -> auto
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

		XTAL_DEF_(short)
		XTAL_LET method()
		noexcept -> auto
		{
			auto i = u_count; u_count += this->template head<U_restep>(); return i;
		}

	private:
		U_count u_count = 0;

	};
};
using Px_dynamic_count = typename dynamic_count::type;


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
/**/
template <xtal::iterated_q T, ::std::invocable<xtal::iteratee_t<T>> U>
XTAL_DEF_(short)
XTAL_LET operator | (T &&t, U &&u)
noexcept -> decltype(auto)
{
	return XTAL_REF_(t)|::ranges::views::transform(XTAL_REF_(u));
};
/***/
XTAL_ENV_(pop)
