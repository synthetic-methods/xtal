#pragma once

#include "./any.h"





XTAL_ENV_(push)
namespace xtal
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

namespace _std = ::std;
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include "./_xtd.ii"
#include "./_retail.ii"
#include "./_entail.ii"
#include "./_detail.ii"


template <auto f>
XTAL_DEF_(return,inline,let) objective_f(auto &&...) noexcept -> auto;///< Mapping    for expression-templates.
XTAL_DEF_(return,inline,let) operative_f(auto &&   ) noexcept -> auto;///< Resolution for expression-templates.

template <auto f>
XTAL_DEF_(return,inline,let)
operative_f(auto &&...xs)
noexcept -> auto
{
	return f(XTAL_REF_(xs)...);
}
XTAL_DEF_(return,inline,let)
objective_f(auto &&o)
noexcept -> auto
{
	XTAL_IF0
	//\
	XTAL_0IF (applicable_p<decltype(o)>) {return XTAL_REF_(o)();}
	XTAL_0IF (  constant_q<decltype(o)>) {return XTAL_REF_(o)();}
	XTAL_0IF (  variable_q<decltype(o)>) {return XTAL_REF_(o)  ;}
}
template <class ...Xs>
using objective_t = common_t<XTAL_ALL_(objective_f(XTAL_ANY_(Xs)))...>;
///< Obtains the common objective `type` for `Xs...`.

template <class ...Xs>
concept  objective_q = same_q<objective_t<Xs>..., Xs...>;

template <class ...Xs>
concept subjective_q = not objective_q<Xs...>;

template <class ...Ts> auto   surjective_f(            Ts... ) -> objective_t<valued_u<Ts>...>;
template <class ...Ts> auto   surjective_f(_std::tuple<Ts...>) -> objective_t<Ts...>;
template <class ...Ts> auto   surjective_f(_std::pair <Ts...>) -> objective_t<Ts...>;
template <class ...Ts> using  surjective_t = common_t<XTAL_ALL_(surjective_f(XTAL_ANY_(Ts)))...>;
///< Obtains the common objective `value_type` for `Xs...`.

//\todo\
Generalize `surjective_f` using `bond::pack`? \


///\returns an instance of the given template applied to either `Xs...` or `common_t<Xs...>`. \

template <template <class ...> class F, class ...Xs>
XTAL_DEF_(return,inline,let)
construxion_f(Xs &&...xs)
noexcept -> auto;

template <template <class ...> class F, class ...Xs>
XTAL_DEF_(return,inline,let)
construxion_f(Xs &&...xs)
noexcept -> auto
{
	XTAL_IF0
	XTAL_0IF (requires {typename F<based_t<Xs>...>;}) {return operative_f<[] XTAL_1FN_(constructor) (F<based_t<Xs>...>)>(XTAL_REF_(xs)...);}
	XTAL_0IF (requires {typename F<cased_t<Xs...>>;}) {return operative_f<[] XTAL_1FN_(constructor) (F<cased_t<Xs...>>)>(XTAL_REF_(xs)...);}
	XTAL_0IF_(terminate)
}

///\returns an instance of `std::complex` applied to `common_t<Xs...>`. \

template <class ...Xs>
XTAL_DEF_(return,inline,let)
complexion_f(Xs &&...xs)
noexcept -> auto;

template <class ...Xs>
XTAL_DEF_(return,inline,let)
complexion_f(Xs &&...xs)
noexcept -> auto
{
	return construxion_f<_std::complex>(XTAL_REF_(xs)...);
}


////////////////////////////////////////////////////////////////////////////////

#if XTAL_LOG
class
{
	void print_list(auto const &x) const {
		for (auto const &w: x) {
			::std::cout << w << '\t';
		}
	}
	void print_item(auto const &x) const {
		using X = XTAL_ALL_(x); using namespace ::std;
		if constexpr (continuous_field_q<X>) {
			cout.precision(17);
		}
		if constexpr (is_arithmetic_v<X>) {
			if (1.0 == copysign(1.0, x)) {
				 cout << ' ';
			}
		}
		cout << x << '\t';
	}
	auto put(auto &&x) const noexcept -> decltype(auto) {
		using X = XTAL_ALL_(x);
		if constexpr (_xtd::ranges::range<X> and requires {::std::is_arithmetic_v<typename X::value_type>;}) {
			print_list(x);
		}
		else {
			print_item(x);
		}
		return XTAL_REF_(x);
	}

public:
	auto operator() (auto &&...xs) const noexcept -> decltype(auto) {
		if constexpr (1 <= sizeof...(xs)) {
			::std::cout << '\t'; auto const x = (put(XTAL_REF_(xs)), ...);
			::std::cout << '\n';
		}
		else {
			::std::cout << '\n';
		}
	}

}
#else
class
{
public:
	auto operator() (auto &&...xs) -> decltype(auto) {
		if constexpr (1 <= sizeof...(xs)) {
			return (XTAL_REF_(xs), ...);
		}
	}

}
#endif
const echo_;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
