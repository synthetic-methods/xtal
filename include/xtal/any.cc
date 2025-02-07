#pragma once
#include "./any.cxx"
#include "./occur/all.hh"
#include "./process/any.hh"
#include "./provision/all.hh"

#include <Eigen/Core>

XTAL_ENV_(push)
namespace xtal::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

static_assert(incomplete_q           <void     > );
static_assert(incomplete_q           <void_type> );
static_assert(  complete_q<complete_t<void     >>);
static_assert(  complete_q<complete_t<void_type>>);



static_assert(same_q<evoke_t<>, evoke_t<>>);
static_assert(same_q<evoke_t<>, decltype(evoke_t<>{})>);

static_assert(    integral_q<constant_t<1>>);
static_assert(    integral_q<  int>);
static_assert(not integral_q<float>);


static_assert(         same_n<0>);
static_assert(not different_n<0>);
static_assert(         same_n<0, 0, 0>);
static_assert(not different_n<0, 0, 0>);


//atic_assert(desolve<_std::complex<float>>::rank() < desolve<_std::array<float, 2>>::rank());
static_assert(assayed<1, 2   >::extents() <= assayed<1, 2, 3>::extents());
static_assert(assayed<1, 2, 3>::extents() <= assayed<1, 2, 4>::extents());
static_assert(assayed<1, 2, 3>::extents() == assayed<1, 2, 3>::extents());
static_assert(assayed<       1            >::extent() ==   1);
static_assert(assayed<       1, 2, 3, 4, 5>::extent() == 120);
static_assert(assayed<    0, 1, 2, 3, 4, 5>::extent() ==   0);
static_assert(assayed<-1, 0, 1, 2, 3, 4, 5>::extent() ==  -1);
static_assert(assayed<       1, 2, 3, 4, 5>::rank() ==   5);
static_assert(assayed<    0, 1, 2, 3, 4, 5>::rank() ==   5);
static_assert(assayed<-1, 0, 1, 2, 3, 4, 5>::rank() ==   5);


static_assert(shaped<_std::vector  <float   >>::extent() == -1);
static_assert(shaped<_std::array   <float, 1>>::extent() ==  1);
static_assert(shaped<_std::complex <float   >>::extent() ==  2);
static_assert(shaped<cardinal_constant_t<2>>::extent() ==  2);
static_assert(shaped< ordinal_constant_t<2>>::extent() ==  2);


static_assert(cardinal_q<valued_u<cardinal_constant_t<2>>>);
static_assert( ordinal_q<valued_u< ordinal_constant_t<2>>>);

static_assert(_std::same_as<        const float(&)[2]   , destruct_t<const float(&)[2]>>);
static_assert(_std::same_as<              float(&)[2]   , destruct_t<      float(&)[2]>>);
static_assert(_std::same_as<        const float   [2]   , destruct_t<const float   [2]>>);
static_assert(_std::same_as<              float   [2]   , destruct_t<      float   [2]>>);
static_assert(_std::same_as<        const float &       , destruct_u<const float(&)[2]>>);
static_assert(_std::same_as<              float &       , destruct_u<      float(&)[2]>>);
static_assert(_std::same_as<        const float         , destruct_u<const float   [2]>>);
static_assert(_std::same_as<              float         , destruct_u<      float   [2]>>);

static_assert(_std::same_as<        const float(&)[2]   , destruct_t<const _std::complex<float> &>>);
static_assert(_std::same_as<              float(&)[2]   , destruct_t<      _std::complex<float> &>>);
static_assert(_std::same_as<        const float   [2]   , destruct_t<const _std::complex<float>  >>);
static_assert(_std::same_as<              float   [2]   , destruct_t<      _std::complex<float>  >>);
static_assert(_std::same_as<        const float &       , destruct_u<const _std::complex<float> &>>);
static_assert(_std::same_as<              float &       , destruct_u<      _std::complex<float> &>>);
static_assert(_std::same_as<        const float         , destruct_u<const _std::complex<float>  >>);
static_assert(_std::same_as<              float         , destruct_u<      _std::complex<float>  >>);

static_assert(_std::same_as<_std::complex<float>  [2]   , abstruct_t<const _std::complex<float>(&)[2]>>);
static_assert(_std::same_as<_std::complex<float>  [2]   , abstruct_t<      _std::complex<float>(&)[2]>>);
static_assert(_std::same_as<_std::complex<float>  [2]   , abstruct_t<const _std::complex<float>   [2]>>);
static_assert(_std::same_as<_std::complex<float>  [2]   , abstruct_t<      _std::complex<float>   [2]>>);
static_assert(_std::same_as<_std::complex<float>        , abstruct_u<const _std::complex<float>(&)[2]>>);
static_assert(_std::same_as<_std::complex<float>        , abstruct_u<      _std::complex<float>(&)[2]>>);
static_assert(_std::same_as<_std::complex<float>        , abstruct_u<const _std::complex<float>   [2]>>);
static_assert(_std::same_as<_std::complex<float>        , abstruct_u<      _std::complex<float>   [2]>>);


//atic_assert(_std::same_as<        const float(&)[2][2], desolve_t<const _std::complex<float>(&)[2]>>);
//atic_assert(_std::same_as<              float(&)[2][2], desolve_t<      _std::complex<float>(&)[2]>>);
//atic_assert(_std::same_as<        const float   [2][2], desolve_t<const _std::complex<float>   [2]>>);
//atic_assert(_std::same_as<              float   [2][2], desolve_t<      _std::complex<float>   [2]>>);
static_assert(_std::same_as<        const float &       , desolve_u<const _std::complex<float>(&)[2]>>);
static_assert(_std::same_as<              float &       , desolve_u<      _std::complex<float>(&)[2]>>);
static_assert(_std::same_as<        const float         , desolve_u<const _std::complex<float>   [2]>>);
static_assert(_std::same_as<              float         , desolve_u<      _std::complex<float>   [2]>>);

//atic_assert(_std::same_as<              float   [2][2],  absolve_t<const _std::complex<float>(&)[2]>>);
//atic_assert(_std::same_as<              float   [2][2],  absolve_t<      _std::complex<float>(&)[2]>>);
//atic_assert(_std::same_as<              float   [2][2],  absolve_t<const _std::complex<float>   [2]>>);
//atic_assert(_std::same_as<              float   [2][2],  absolve_t<      _std::complex<float>   [2]>>);
static_assert(_std::same_as<              float         ,  absolve_u<const _std::complex<float>(&)[2]>>);
static_assert(_std::same_as<              float         ,  absolve_u<      _std::complex<float>(&)[2]>>);
static_assert(_std::same_as<              float         ,  absolve_u<const _std::complex<float>   [2]>>);
static_assert(_std::same_as<              float         ,  absolve_u<      _std::complex<float>   [2]>>);

static_assert(_std::same_as<      int( &)[2], decltype(destruct_f(XTAL_ANY_(      _std::complex<int>  &)))>);
static_assert(_std::same_as<const int( &)[2], decltype(destruct_f(XTAL_ANY_(const _std::complex<int>  &)))>);
static_assert(_std::same_as<      int(&&)[2], decltype(destruct_f(XTAL_ANY_(      _std::complex<int> &&)))>);
static_assert(_std::same_as<const int(&&)[2], decltype(destruct_f(XTAL_ANY_(const _std::complex<int> &&)))>);

//atic_assert(_std::same_as<      int( &)[2][2], decltype(desolve_f(XTAL_ANY_(      _std::complex<int>(&)[2])))>);
//atic_assert(_std::same_as<const int( &)[2][2], decltype(desolve_f(XTAL_ANY_(const _std::complex<int>(&)[2])))>);
//atic_assert(_std::same_as<      int(&&)[2][2], decltype(desolve_f(XTAL_ANY_(      _std::complex<int>   [2])))>);
//atic_assert(_std::same_as<const int(&&)[2][2], decltype(desolve_f(XTAL_ANY_(const _std::complex<int>   [2])))>);


static_assert(array_valued_q<const _std::complex<float>(&)[2]>);
static_assert(fixed_valued_q<const _std::complex<float>(&)[2]>);
static_assert( fixed_shaped_q<const _std::complex<float>(&)[2]>);
static_assert(       fixed_q<const _std::complex<float>(&)[2]>);

static_assert(            contiguous_field_q<float>);
static_assert(               simplex_field_q<float>);
static_assert(          not  complex_field_q<float>);
static_assert(          not quotient_group_q<float>);
static_assert(              quotient_group_q<  int>);
static_assert(complex_field_q<_std::complex<float>>);


////////////////////////////////////////////////////////////////////////////////

template <int N_index>
XTAL_DEF_(return,inline,let)
check_f(auto const &u, auto const &v)
noexcept -> bool
{
	using _fit = bond::fit<decltype(u), decltype(v)>;
	return _fit::template trim_f<N_index>(u) == _fit::template trim_f<N_index>(v);
}
template <int N_index, int N_limit>
XTAL_DEF_(return,inline,let)
check_f(auto const &u, auto const &v)
noexcept -> int
{
	auto constexpr Z_index = sign_n<N_index>;
	auto constexpr Z_limit = sign_n<N_limit>;
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
XTAL_DEF_(return,inline,let)
check_f(auto const &u, auto const &v)
noexcept -> int
{
	return check_f<-1, 1 - (int) bond::fit<>::fraction.depth>(u, v);
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

using namespace bond;

using Ox_scale = occur::reinferred_t<class A_scale, typename bond::fit<>::alpha_type>;
using Ox_level = occur::reinferred_t<class A_level, typename bond::fit<>::alpha_type>;
/*/
using Ox_onset = occur::reinferred_t<class onset_a, typename bond::fit<>::alpha_type>;
/*/
struct onset
:	occur::infers<typename bond::fit<>::sigma_type
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

		XTAL_DEF_(return,inline,let)
		method(auto &&...xs) const
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
		XTAL_DEF_(return,inline,set)
		method_f(auto &&...xs)
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

		XTAL_DEF_(return,inline,let)
		method(auto &&...xs)
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

		XTAL_DEF_(return,inline,let)
		method(auto &&x)
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
	using U_count  = typename bond::fit<>::delta_type;
	using U_restep = occur::restep_t<U_count>;

	template <class T>
	using homotype = process::confine_t<T, U_restep::attach<>>;

	struct type : public homotype<type>
	{
		using T_ = homotype<type>;
	
	public:
		using T_::T_;

		XTAL_DEF_(return,inline,let)
		method()
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
XTAL_ENV_(pop)
