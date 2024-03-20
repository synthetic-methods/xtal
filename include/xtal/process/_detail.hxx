#include "../cell/_kernel.hxx"








namespace _detail
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

using namespace _retail::_detail;


////////////////////////////////////////////////////////////////////////////////

template <class X> using ipsoscalar_t = X;
template <class X> using endoscalar_t = typename atom::realize<X>::delta_t;
template <class X> using ectoscalar_t = typename atom::realize<X>::alpha_t;

XTAL_LET endoscalar_f = []<class X> (X &&x)
XTAL_0FN
{
	using re = atom::realize<X>;
	if constexpr (_std::is_floating_point_v<X>) {
		return endoscalar_t<X>(XTAL_FWD_(x)*re::diplo_f(re::N_depth));
	}
	else {
		return endoscalar_t<X>(XTAL_FWD_(x));
	}
};
XTAL_LET ectoscalar_f = []<class X> (X &&x)
XTAL_0FN
{
	using re = atom::realize<X>;
	if constexpr (_std::is_floating_point_v<X>) {
		return ectoscalar_t<X>(XTAL_FWD_(x));
	}
	else {
		return ectoscalar_t<X>(XTAL_FWD_(x))*re::haplo_f(re::N_depth);
	}
};


////////////////////////////////////////////////////////////////////////////////

template <array_q Xs> using ipsovector_t = bond::serial_t<array_t<Xs>>;
template <array_q Xs> using endovector_t = bond::serial_t<endoscalar_t<value_t<Xs>>[arity_n<Xs>]>;
template <array_q Xs> using ectovector_t = bond::serial_t<ectoscalar_t<value_t<Xs>>[arity_n<Xs>]>;

XTAL_LET endovector_f = []<array_q Xs> (Xs &&xs)
XTAL_0FN
{
	return forge_f<ipsovector_t<Xs>>(XTAL_FWD_(xs)).template transmute<endovector_t<Xs>>(endoscalar_f);
};
XTAL_LET ectovector_f = []<array_q Xs> (Xs &&xs)
XTAL_0FN
{
	return forge_f<ipsovector_t<Xs>>(XTAL_FWD_(xs)).template transmute<ectovector_t<Xs>>(ectoscalar_f);
};


////////////////////////////////////////////////////////////////////////////////

}//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
