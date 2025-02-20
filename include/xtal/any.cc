#pragma once
#include "./any.c"
#include "./occur/all.hh"
#include "./process/any.hh"
#include "./provision/all.hh"

#include <Eigen/Core>

XTAL_ENV_(push)
namespace xtal::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <int N>
void echo_rule_()
{
	for (int n = -N; n <= N; ++n) {
		_std::cout << '-';
	}
	_std::cout << _std::endl;
}
template <int N>
void echo_plot_(iterated_q auto const o)
{
	for (auto e: o) {
		e *= N;
		e *= 2;
		e += 0 < e;
		e -= e < 0;
		auto u = static_cast<int>(e);
		for (int n = -N; n <= N; ++n) {
			auto m = n << 1;
			if (n == 0)                     {                  } else
			if (u < 0 and n < 0 and u == m) {_std::cout << "╼";} else
			if (u < 0 and n < 0 and u <= m) {_std::cout << "━";} else
			if (0 < u and 0 < n and u == m) {_std::cout << "╾";} else
			if (0 < u and 0 < n and u >= m) {_std::cout << "━";} else
			/**/                            {_std::cout << ' ';}
		}
		_std::cout << _std::endl;
	}
}


////////////////////////////////////////////////////////////////////////////////

static_assert(incomplete_q           <void     > );
static_assert(incomplete_q           <void_type> );
static_assert(  complete_q<complete_t<void     >>);
static_assert(  complete_q<complete_t<void_type>>);



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
static_assert(fixed_shaped_q<const _std::complex<float>(&)[2]>);
static_assert(       fixed_q<const _std::complex<float>(&)[2]>);

static_assert(            contiguous_field_q<float>);
static_assert(               simplex_field_q<float>);
static_assert(          not  complex_field_q<float>);
static_assert(          not quotient_group_q<float>);
static_assert(              quotient_group_q<  int>);
static_assert(complex_field_q<_std::complex<float>>);




static_assert(_xtd::extent_v<int[0][2][3]> == 0);
static_assert(_xtd::extent_v<int[1][2][3]> == 1);

static_assert(_xtd::extent_v<const int   [0][2][3]> == 0);
static_assert(_xtd::extent_v<const int   [1][2][3]> == 1);
static_assert(_xtd::extent_v<const int(&)[0][2][3]> == 0);
static_assert(_xtd::extent_v<const int(&)[1][2][3]> == 1);

static_assert(_xtd::extent_v<const int(&)[1][2][3], 0> == 1);
static_assert(_xtd::extent_v<const int(&)[1][2][3], 1> == 2);
static_assert(_xtd::extent_v<const int(&)[1][2][3], 2> == 3);

static_assert(same_q<_xtd::remove_extent_t<const int   [0]      >, const int         >);
static_assert(same_q<_xtd::remove_extent_t<const int   [1]      >, const int         >);
static_assert(same_q<_xtd::remove_extent_t<const int(&)[0]      >, const int &       >);
static_assert(same_q<_xtd::remove_extent_t<const int(&)[1]      >, const int &       >);

static_assert(same_q<_xtd::remove_extent_t<const int   [0][2][3]>, const int   [2][3]>);
static_assert(same_q<_xtd::remove_extent_t<const int   [1][2][3]>, const int   [2][3]>);
static_assert(same_q<_xtd::remove_extent_t<const int(&)[0][2][3]>, const int(&)[2][3]>);
static_assert(same_q<_xtd::remove_extent_t<const int(&)[1][2][3]>, const int(&)[2][3]>);

static_assert(same_q<_xtd::remove_all_extents_t<const int   [0][2][3]>, const int  >);
static_assert(same_q<_xtd::remove_all_extents_t<const int   [1][2][3]>, const int  >);
static_assert(same_q<_xtd::remove_all_extents_t<const int(&)[0][2][3]>, const int &>);
static_assert(same_q<_xtd::remove_all_extents_t<const int(&)[1][2][3]>, const int &>);


static_assert( array_shaped_q<int[0][2][3]>);
static_assert( array_shaped_q<int[1][2][3]>);

static_assert( array_valued_q<int[0][2][3]>);
static_assert( array_valued_q<int[1][2][3]>);

static_assert( antecedent_q<int[0][2][3]>);
static_assert(intercedent_q<int[1][2][3]>);
static_assert(same_q<precedent_s<int[1][2][3]>, int[0][2][3]>);
static_assert(same_q<succedent_s<int[0][2][3]>, int[1][2][3]>);



////////////////////////////////////////////////////////////////////////////////

TAG_("any")
{
	TRY_("ordering")
	{
		using is = _std::partial_ordering;

		TRUE_(0 == disordering_f(is::equivalent));
		TRUE_(1 == disordering_f(is::greater));
		TRUE_(2 == disordering_f(is::less));
		TRUE_(3 == disordering_f(is::unordered));
		
		TRUE_(0 == disordering_f( 0.0));
		TRUE_(1 == disordering_f( 1.0));
		TRUE_(2 == disordering_f(-1.0));

		TRUE_(0 == disordering_f( 0x0000));
		TRUE_(1 == disordering_f( 0x1000));
		TRUE_(2 == disordering_f(-0x1000));
		
	}
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
