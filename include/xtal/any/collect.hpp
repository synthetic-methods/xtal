#pragma once
#include "./any.hpp"
#include "./compose.hpp"// next





XTAL_ENV_(push)
namespace xtal
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <typename... Xs>
struct collect
{
	using type = _std::tuple<Xs...>;

	template <typename F> using result   = _std::invoke_result  <F, Xs...>;
	template <typename F> using result_t = _std::invoke_result_t<F, Xs...>;

};
template <typename... Xs>
XTAL_USE  collect_t = typename collect<Xs...>::type;
XTAL_LET  collect_f = [] <typename... Xs> (Xs&&... xs)
XTAL_0FN_(collect_t<Xs...>(XTAL_FWD_(Xs) (xs)...));

XTAL_LET collected_f = [] <typename... Xs> (Xs&&... xs)
XTAL_0FN_(_std::forward_as_tuple<Xs...>(XTAL_FWD_(Xs) (xs)...));

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
