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
void echo_rule_(auto const z)
{
	for (int n = -N; n <= -1; ++n) {
		_std::cout << z;
	}
	for (int n = +1; n <= +N; ++n) {
		_std::cout << z;
	}
	_std::cout << _std::endl;
}
template <int N>
void echo_rule_()
{
	echo_rule_<N>("\u2500");// BOX DRAWINGS LIGHT HORIZONTAL
}
template <int N>
void echo_plot_(int line, auto item, integral_q auto ...markers)
{
	auto uZERO = 0 == line? "\u2504": "\u0020";// ...BOX DRAWINGS LIGHT TRIPLE-DASH HORIZONTAL, or ...SPACE
	_std::vector<int> m_{markers...};
	bool marked = _std::find(m_.begin(), m_.end(), line) < m_.end();
	item *= N;
	item *= 2;
	item += 0 < item;
	item -= item < 0;
	auto w = static_cast<int>(item);
	item /= 2;
	auto u = static_cast<int>(item);
	for (int n = -N; n <= -1; ++n) {
		auto const m = n << 1;
		if (false);
		else if (m <  w     and n == -1 and marked) _std::cout << "\u22A3";// -| TACK LEFT
		else if (m <  w - 1 and n != -1 or  u == 0) _std::cout <<   uZERO ;//    ...
		else if (m == w - 1 and          line == 0) _std::cout << "\u2574";// -  BOX DRAWINGS LIGHT LEFT
		else if (n <  u)                            _std::cout << "\u0020";//    SPACE
		else if (u <  n)                            _std::cout << "\u2501";// == BOX DRAWINGS HEAVY HORIZONTAL
		else if (w <  m)                            _std::cout << "\u257A";//  = BOX DRAWINGS HEAVY RIGHT
		else                                        _std::cout << "\u0020";//    SPACE
	}
	for (int n = +1; n <= +N; ++n) {
		auto const m = n << 1;
		if (false);
		else if (w <  m     and n == +1 and marked) _std::cout << "\u22A2";// |- TACK RIGHT
		else if (w <  m - 1 and n != +1 or  u == 0) _std::cout <<   uZERO ;//    ...
		else if (w == m - 1 and          line == 0) _std::cout << "\u2576";//  - BOX DRAWINGS LIGHT RIGHT
		else if (u <  n - 0)                        _std::cout << "\u0020";//    SPACE
		else if (n <  u)                            _std::cout << "\u2501";// == BOX DRAWINGS HEAVY HORIZONTAL
		else if (m <  w)                            _std::cout << "\u2578";// =  BOX DRAWINGS HEAVY LEFT
		else                                        _std::cout << "\u0020";//    SPACE
	}
	_std::cout << "\u0020";//    SPACE
}
template <int N>
void echo_plot_(iterated_q auto const list, integral_q auto ...markers)
{
	using _std::get;
	using W = XTAL_ALL_(list);
	using U = iteratee_t<W>;
	using _fit = bond::fit<decltype(list)>;
	_std::vector<typename _fit::alpha_type> part;
	int line{};
	for (auto item: list) {
		using List = XTAL_ALL_(list);
		using Item = XTAL_ALL_(item);
		if constexpr (destruct_q<Item>) {
			auto etc = destruct_f(item);
			[&]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN_(do) (echo_plot_<N>(line, bond::pack_item_f<I>(item), markers...), ...)
			(bond::seek_s<fixed_shaped<Item>::extent()>{});
		}
		else {
			echo_plot_<N>(line, item, markers...);
		}
		echo_();
		++line;
	}
}


////////////////////////////////////////////////////////////////////////////////

static_assert(incomplete_q           <void     > );
static_assert(incomplete_q           <void_type> );
static_assert(  complete_q<complete_t<void     >>);
static_assert(  complete_q<complete_t<void_type>>);

static_assert(not            common_q<int, null_type> );
static_assert(not complete_q<common_t<int, null_type>>);


static_assert(    integral_q<constant_t<1>>);
static_assert(    integral_q<  int>);
static_assert(not integral_q<float>);


static_assert(         same_n<0>);
static_assert(not different_n<0>);
static_assert(         same_n<0, 0, 0>);
static_assert(not different_n<0, 0, 0>);


//atic_assert(restruct<_std::complex<float>>::rank() < restruct<_std::array<float, 2>>::rank());
static_assert(_retail::assayed<1, 2   >::extents() <= _retail::assayed<1, 2, 3>::extents());
static_assert(_retail::assayed<1, 2, 3>::extents() <= _retail::assayed<1, 2, 4>::extents());
static_assert(_retail::assayed<1, 2, 3>::extents() == _retail::assayed<1, 2, 3>::extents());
static_assert(_retail::assayed<       1            >::extent() ==   1);
static_assert(_retail::assayed<       1, 2, 3, 4, 5>::extent() == 120);
static_assert(_retail::assayed<    0, 1, 2, 3, 4, 5>::extent() ==   0);
static_assert(_retail::assayed<-1, 0, 1, 2, 3, 4, 5>::extent() ==  -1);
static_assert(_retail::assayed<       1, 2, 3, 4, 5>::rank() ==   5);
static_assert(_retail::assayed<    0, 1, 2, 3, 4, 5>::rank() ==   5);
static_assert(_retail::assayed<-1, 0, 1, 2, 3, 4, 5>::rank() ==   5);


static_assert(fluid_shaped<_std::vector  <float   >>::extent() == -1);
static_assert(fixed_shaped<_std::array   <float, 1>>::extent() ==  1);
static_assert(fixed_shaped<_std::complex <float   >>::extent() ==  2);


static_assert(cardinal_q<valued_u<cardinal_constant_t<2>>>);
static_assert( ordinal_q<valued_u< ordinal_constant_t<2>>>);


static_assert(_std::same_as<disqualify_s<const float( &)[2]>, const float( &)[2]>);
static_assert(_std::same_as<disqualify_s<      float( &)[2]>,       float( &)[2]>);
static_assert(_std::same_as<disqualify_s<const float    [2]>, const float    [2]>);
static_assert(_std::same_as<disqualify_s<      float    [2]>,       float    [2]>);
static_assert(_std::same_as<disqualify_s<const float(&&)[2]>, const float    [2]>);
static_assert(_std::same_as<disqualify_s<      float(&&)[2]>,       float    [2]>);

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

static_assert(_std::same_as<        const float(&)[2][2], restruct_t<const _std::complex<float>(&)[2]>>);
static_assert(_std::same_as<              float(&)[2][2], restruct_t<      _std::complex<float>(&)[2]>>);
static_assert(_std::same_as<        const float   [2][2], restruct_t<const _std::complex<float>   [2]>>);
static_assert(_std::same_as<              float   [2][2], restruct_t<      _std::complex<float>   [2]>>);

static_assert(_std::same_as<        const float &       , restruct_u<const _std::complex<float>(&)[2]>>);
static_assert(_std::same_as<              float &       , restruct_u<      _std::complex<float>(&)[2]>>);
static_assert(_std::same_as<        const float         , restruct_u<const _std::complex<float>   [2]>>);
static_assert(_std::same_as<              float         , restruct_u<      _std::complex<float>   [2]>>);

static_assert(_std::same_as<              float         , unstruct_u<const _std::complex<float>(&)[2]>>);
static_assert(_std::same_as<              float         , unstruct_u<      _std::complex<float>(&)[2]>>);
static_assert(_std::same_as<              float         , unstruct_u<const _std::complex<float>   [2]>>);
static_assert(_std::same_as<              float         , unstruct_u<      _std::complex<float>   [2]>>);

static_assert(_std::same_as<      int( &)[2]   , decltype(destruct_f(XTAL_ANY_(      _std::complex<int>  &   )))>);
static_assert(_std::same_as<const int( &)[2]   , decltype(destruct_f(XTAL_ANY_(const _std::complex<int>  &   )))>);
static_assert(_std::same_as<      int(&&)[2]   , decltype(destruct_f(XTAL_ANY_(      _std::complex<int> &&   )))>);
static_assert(_std::same_as<const int(&&)[2]   , decltype(destruct_f(XTAL_ANY_(const _std::complex<int> &&   )))>);

static_assert(_std::same_as<      int( &)[2][2], decltype(restruct_f(XTAL_ANY_(      _std::complex<int>(&)[2])))>);
static_assert(_std::same_as<const int( &)[2][2], decltype(restruct_f(XTAL_ANY_(const _std::complex<int>(&)[2])))>);
static_assert(_std::same_as<      int(&&)[2][2], decltype(restruct_f(XTAL_ANY_(      _std::complex<int>   [2])))>);
static_assert(_std::same_as<const int(&&)[2][2], decltype(restruct_f(XTAL_ANY_(const _std::complex<int>   [2])))>);


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


//NOTE: Commented lines are for MSVC, but support for zero-length arrays is not critical...

//atic_assert(_xtd::extent_v<int[0][2][3]> == 0);
static_assert(_xtd::extent_v<int[1][2][3]> == 1);

//atic_assert(_xtd::extent_v<const int   [0][2][3]> == 0);
static_assert(_xtd::extent_v<const int   [1][2][3]> == 1);
//atic_assert(_xtd::extent_v<const int(&)[0][2][3]> == 0);
static_assert(_xtd::extent_v<const int(&)[1][2][3]> == 1);

static_assert(_xtd::extent_v<const int(&)[1][2][3], 0> == 1);
static_assert(_xtd::extent_v<const int(&)[1][2][3], 1> == 2);
static_assert(_xtd::extent_v<const int(&)[1][2][3], 2> == 3);

//atic_assert(same_q<_xtd::remove_extent_t<const int   [0]      >, const int         >);
static_assert(same_q<_xtd::remove_extent_t<const int   [1]      >, const int         >);
//atic_assert(same_q<_xtd::remove_extent_t<const int(&)[0]      >, const int &       >);
static_assert(same_q<_xtd::remove_extent_t<const int(&)[1]      >, const int &       >);

//atic_assert(same_q<_xtd::remove_extent_t<const int   [0][2][3]>, const int   [2][3]>);
static_assert(same_q<_xtd::remove_extent_t<const int   [1][2][3]>, const int   [2][3]>);
//atic_assert(same_q<_xtd::remove_extent_t<const int(&)[0][2][3]>, const int(&)[2][3]>);
static_assert(same_q<_xtd::remove_extent_t<const int(&)[1][2][3]>, const int(&)[2][3]>);

//atic_assert(same_q<_xtd::remove_all_extents_t<const int   [0][2][3]>, const int  >);
static_assert(same_q<_xtd::remove_all_extents_t<const int   [1][2][3]>, const int  >);
//atic_assert(same_q<_xtd::remove_all_extents_t<const int(&)[0][2][3]>, const int &>);
static_assert(same_q<_xtd::remove_all_extents_t<const int(&)[1][2][3]>, const int &>);


//atic_assert( array_shaped_q<int[0][2][3]>);
static_assert( array_shaped_q<int[1][2][3]>);

//atic_assert( array_valued_q<int[0][2][3]>);
static_assert( array_valued_q<int[1][2][3]>);

//atic_assert( antecedent_q<int[0][2][3]>);
static_assert(intercedent_q<int[1][2][3]>);
//atic_assert(same_q<precedent_s<int[1][2][3]>, int[0][2][3]>);
//atic_assert(same_q<succedent_s<int[0][2][3]>, int[1][2][3]>);



////////////////////////////////////////////////////////////////////////////////

TAG_("any")
{
	TRY_("text")
	{
		text_type constexpr  first{"1st"};
		text_type constexpr _first{"1st"};
		text_type constexpr second{"2nd"};

		TRUE_(first ==  first);
		TRUE_(first == _first);
		TRUE_(first != second);
		
	};
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
		
	};
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
