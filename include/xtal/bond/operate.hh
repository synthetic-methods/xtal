#pragma once
#include "./any.hh"

#include "./fit.hh"




XTAL_ENV_(push)
namespace xtal::bond
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/*!
\brief
Provides an overloaded combination of `<Fs...>`,
conforming to `constant_q` if `applicable_q<Fs...>`.

\details
Defaults to `std::identity` for `<>`.

Facilitates `std::visit`ation via `operator()` when applied to `std::variant`s.
*/
////////////////////////////////////////////////////////////////////////////////

template <class... Fs>
struct operate : Fs...
{
	using type = operate;

	using Fs::operator()...;

	template <class ...Ts> XTAL_DEF_(inline,let) operator() (std::variant<Ts...>       &&v) noexcept -> decltype(auto) {return std::visit(XTAL_MOV_(v), *this);}
	template <class ...Ts> XTAL_DEF_(inline,let) operator() (std::variant<Ts...> const &&v) noexcept -> decltype(auto) {return std::visit(XTAL_MOV_(v), *this);}
	template <class ...Ts> XTAL_DEF_(inline,let) operator() (std::variant<Ts...>        &v) noexcept -> decltype(auto) {return std::visit(XTAL_REF_(v), *this);}
	template <class ...Ts> XTAL_DEF_(inline,let) operator() (std::variant<Ts...> const  &v) noexcept -> decltype(auto) {return std::visit(XTAL_REF_(v), *this);}

	template <class T>
	XTAL_DEF_(return,inline,set)
	object()
	noexcept -> auto
	{
		using U = based_t<T>;
		XTAL_IF0
		XTAL_0IF_(to) (static_cast<U>(operate{}()))
		XTAL_0IF_(to) (U(operate{}()))
		XTAL_0IF_(to) (U{operate{}()})
	}
	template <class T>
	XTAL_DEF_(return,inline,set)
	subject()
	noexcept -> auto
	{
		using U = based_t<T>;
		using V = typename fluid<U>::value_type;
		if constexpr (un_q<U, V> and complete_q<decltype(object<V>())>) {
			return subject<V>();
		}
		else {
			return  object<U>();
		}
	}
	template <class T>
	XTAL_DEF_(return,inline,set)
	surject()
	noexcept -> auto
	{
		return operate{[] XTAL_1FN_(to) (bond::fit<T>::alpha_1/object<T>())};
	}

	template <class T>
	XTAL_DEF_(return,inline,implicit)
	operator T() const
	noexcept {return object<T>();}

	XTAL_DEF_(return,inline,met) operator + (operate const &t)
	noexcept -> auto
	{
		auto constexpr value = operate{}();
		using value_type = decltype(value);
		XTAL_IF0
		XTAL_0IF (un_v<integral_q<value_type>>) return operate<decltype([] XTAL_1FN_(to) (+                 value ))>{};
		XTAL_0IF (in_v<integral_q<value_type>>) return operate<decltype([] XTAL_1FN_(to) (+xtd::signed_cast(value)))>{};
	}
	XTAL_DEF_(return,inline,met) operator - (operate const &t)
	noexcept -> auto
	{
		auto constexpr value = operate{}();
		using value_type = decltype(value);
		XTAL_IF0
		XTAL_0IF (un_v<integral_q<value_type>>) return operate<decltype([] XTAL_1FN_(to) (-                 value ))>{};
		XTAL_0IF (in_v<integral_q<value_type>>) return operate<decltype([] XTAL_1FN_(to) (-xtd::signed_cast(value)))>{};
	}
	XTAL_DEF_(return,inline,met) operator ~ (operate const &t)
	noexcept -> auto
	{
		auto constexpr value = operate{}();
		using value_type = decltype(value);
		return operate<decltype([] XTAL_1FN_(to) (~value))>{};
	}

	template <inapplicable_p T> XTAL_DEF_(return,inline,met) operator <=> (same_q<operate> auto const &, T const &t) noexcept -> auto   requires XTAL_TRY_(to) (object<T>() <=> t)
	template <inapplicable_p T> XTAL_DEF_(return,inline,met) operator  == (same_q<operate> auto const &, T const &t) noexcept -> bool   requires XTAL_TRY_(to) (object<T>()  == t)
	template <inapplicable_p T> XTAL_DEF_(return,inline,met) operator <=> (T const &t, same_q<operate> auto const &) noexcept -> auto   requires XTAL_TRY_(to) (t <=> object<T>())
	template <inapplicable_p T> XTAL_DEF_(return,inline,met) operator  == (T const &t, same_q<operate> auto const &) noexcept -> bool   requires XTAL_TRY_(to) (t  == object<T>())

	template <inapplicable_p T> XTAL_DEF_(return,inline,met) operator  -  (same_q<operate> auto const &, T const &t) noexcept -> auto   requires XTAL_TRY_(to) (subject<T>()  -  t)
	template <inapplicable_p T> XTAL_DEF_(return,inline,met) operator  +  (same_q<operate> auto const &, T const &t) noexcept -> auto   requires XTAL_TRY_(to) (subject<T>()  +  t)
	template <inapplicable_p T> XTAL_DEF_(return,inline,met) operator  *  (same_q<operate> auto const &, T const &t) noexcept -> auto   requires XTAL_TRY_(to) (subject<T>()  *  t)
	template <inapplicable_p T> XTAL_DEF_(return,inline,met) operator  /  (same_q<operate> auto const &, T const &t) noexcept -> auto   requires XTAL_TRY_(to) (subject<T>()  /  t)
	template <inapplicable_p T> XTAL_DEF_(return,inline,met) operator  %  (same_q<operate> auto const &, T const &t) noexcept -> auto   requires XTAL_TRY_(to) (subject<T>()  %  t)
	template <inapplicable_p T> XTAL_DEF_(return,inline,met) operator  &  (same_q<operate> auto const &, T const &t) noexcept -> auto   requires XTAL_TRY_(to) (subject<T>()  &  t)
	template <inapplicable_p T> XTAL_DEF_(return,inline,met) operator  ^  (same_q<operate> auto const &, T const &t) noexcept -> auto   requires XTAL_TRY_(to) (subject<T>()  ^  t)
	template <inapplicable_p T> XTAL_DEF_(return,inline,met) operator  |  (same_q<operate> auto const &, T const &t) noexcept -> auto   requires XTAL_TRY_(to) (subject<T>()  |  t)
	
	template <    constant_q T> XTAL_DEF_(return,inline,met) operator  -  (same_q<operate> auto const &, T const &t) noexcept -> auto   requires XTAL_TRY_(to) (operate<decltype([] XTAL_1FN_(to) (operate{}() - T{}()))>{})
	template <    constant_q T> XTAL_DEF_(return,inline,met) operator  +  (same_q<operate> auto const &, T const &t) noexcept -> auto   requires XTAL_TRY_(to) (operate<decltype([] XTAL_1FN_(to) (operate{}() + T{}()))>{})
	template <    constant_q T> XTAL_DEF_(return,inline,met) operator  *  (same_q<operate> auto const &, T const &t) noexcept -> auto   requires XTAL_TRY_(to) (operate<decltype([] XTAL_1FN_(to) (operate{}() * T{}()))>{})
	template <    constant_q T> XTAL_DEF_(return,inline,met) operator  /  (same_q<operate> auto const &, T const &t) noexcept -> auto   requires XTAL_TRY_(to) (operate<decltype([] XTAL_1FN_(to) (operate{}() / T{}()))>{})
	template <    constant_q T> XTAL_DEF_(return,inline,met) operator  %  (same_q<operate> auto const &, T const &t) noexcept -> auto   requires XTAL_TRY_(to) (operate<decltype([] XTAL_1FN_(to) (operate{}() % T{}()))>{})
	template <    constant_q T> XTAL_DEF_(return,inline,met) operator  &  (same_q<operate> auto const &, T const &t) noexcept -> auto   requires XTAL_TRY_(to) (operate<decltype([] XTAL_1FN_(to) (operate{}() & T{}()))>{})
	template <    constant_q T> XTAL_DEF_(return,inline,met) operator  ^  (same_q<operate> auto const &, T const &t) noexcept -> auto   requires XTAL_TRY_(to) (operate<decltype([] XTAL_1FN_(to) (operate{}() ^ T{}()))>{})
	template <    constant_q T> XTAL_DEF_(return,inline,met) operator  |  (same_q<operate> auto const &, T const &t) noexcept -> auto   requires XTAL_TRY_(to) (operate<decltype([] XTAL_1FN_(to) (operate{}() | T{}()))>{})

	template <inapplicable_p T> XTAL_DEF_(return,inline,met) operator  -  (T const &t, same_q<operate> auto const &) noexcept -> auto   requires XTAL_TRY_(to) (t  -  subject<T>())
	template <inapplicable_p T> XTAL_DEF_(return,inline,met) operator  +  (T const &t, same_q<operate> auto const &) noexcept -> auto   requires XTAL_TRY_(to) (t  +  subject<T>())
	template <inapplicable_p T> XTAL_DEF_(return,inline,met) operator  *  (T const &t, same_q<operate> auto const &) noexcept -> auto   requires XTAL_TRY_(to) (t  *  subject<T>())
	template <inapplicable_p T> XTAL_DEF_(return,inline,met) operator  /  (T const &t, same_q<operate> auto const &) noexcept -> auto   requires XTAL_TRY_(to) (t  *  surject<T>())
	template <inapplicable_p T> XTAL_DEF_(return,inline,met) operator  %  (T const &t, same_q<operate> auto const &) noexcept -> auto   requires XTAL_TRY_(to) (t  %  subject<T>())
	template <inapplicable_p T> XTAL_DEF_(return,inline,met) operator  &  (T const &t, same_q<operate> auto const &) noexcept -> auto   requires XTAL_TRY_(to) (t  &  subject<T>())
	template <inapplicable_p T> XTAL_DEF_(return,inline,met) operator  ^  (T const &t, same_q<operate> auto const &) noexcept -> auto   requires XTAL_TRY_(to) (t  ^  subject<T>())
	template <inapplicable_p T> XTAL_DEF_(return,inline,met) operator  |  (T const &t, same_q<operate> auto const &) noexcept -> auto   requires XTAL_TRY_(to) (t  |  subject<T>())
	template <inapplicable_p T> XTAL_DEF_(return,inline,met) operator >>  (T const &t, same_q<operate> auto const &) noexcept -> auto   requires XTAL_TRY_(to) (t >>  subject<T>())
	template <inapplicable_p T> XTAL_DEF_(return,inline,met) operator <<  (T const &t, same_q<operate> auto const &) noexcept -> auto   requires XTAL_TRY_(to) (t <<  subject<T>())

	template <inapplicable_p T> XTAL_DEF_(mutate,inline,met) operator  -= (T       &t, same_q<operate> auto const &) noexcept -> auto & requires XTAL_TRY_(to) (t  -= subject<T>())
	template <inapplicable_p T> XTAL_DEF_(mutate,inline,met) operator  += (T       &t, same_q<operate> auto const &) noexcept -> auto & requires XTAL_TRY_(to) (t  += subject<T>())
	template <inapplicable_p T> XTAL_DEF_(mutate,inline,met) operator  *= (T       &t, same_q<operate> auto const &) noexcept -> auto & requires XTAL_TRY_(to) (t  *= subject<T>())
	template <inapplicable_p T> XTAL_DEF_(mutate,inline,met) operator  /= (T       &t, same_q<operate> auto const &) noexcept -> auto & requires XTAL_TRY_(to) (t  *= surject<T>())
	template <inapplicable_p T> XTAL_DEF_(mutate,inline,met) operator  %= (T       &t, same_q<operate> auto const &) noexcept -> auto & requires XTAL_TRY_(to) (t  %= subject<T>())
	template <inapplicable_p T> XTAL_DEF_(mutate,inline,met) operator  &= (T       &t, same_q<operate> auto const &) noexcept -> auto & requires XTAL_TRY_(to) (t  &= subject<T>())
	template <inapplicable_p T> XTAL_DEF_(mutate,inline,met) operator  ^= (T       &t, same_q<operate> auto const &) noexcept -> auto & requires XTAL_TRY_(to) (t  ^= subject<T>())
	template <inapplicable_p T> XTAL_DEF_(mutate,inline,met) operator  |= (T       &t, same_q<operate> auto const &) noexcept -> auto & requires XTAL_TRY_(to) (t  |= subject<T>())
	template <inapplicable_p T> XTAL_DEF_(mutate,inline,met) operator <<= (T       &t, same_q<operate> auto const &) noexcept -> auto & requires XTAL_TRY_(to) (t <<= subject<T>())
	template <inapplicable_p T> XTAL_DEF_(mutate,inline,met) operator >>= (T       &t, same_q<operate> auto const &) noexcept -> auto & requires XTAL_TRY_(to) (t >>= subject<T>())

};
template <inapplicable_q T>
struct operate<T> : operate<decltype([] (auto &&...oo)
XTAL_0FN -> decltype(auto)
{
	XTAL_IF0
	XTAL_0IF_(to) (T   {XTAL_REF_(oo)...})
	XTAL_0IF_(to) (T   (XTAL_REF_(oo)...))
	XTAL_0IF_(to) (T{} (XTAL_REF_(oo)...))
})>
{
};
template <>
struct operate<> : std::identity
{
};


template <class ...Fs>
operate(Fs...) -> operate<Fs...>;


////////////////////////////////////////////////////////////////////////////////

/*!
\returns	The bit-shifted result if `integral_q<T>`,
otherwise fractional mutiplication by `exp2(t)`.
*/
template <inapplicable_p T, class ...Fs>
XTAL_DEF_(return,inline,let)
operator << (operate<Fs...> const &, T const &t)
noexcept -> decltype(auto)
{
	auto o = operate<Fs...>::template object<T>();
	if constexpr (integral_variable_q<T, decltype(o)>)  {
		if (t < T{}) {o >>= -t;}
		else         {o <<=  t;}
	}
	else {
		o *= fit<T>::diplo_f(t);
	}
	return o;
}
/*!
\returns	The bit-shifted result if `integral_q<T>`,
otherwise fractional division by `exp2(t)`.
*/
template <inapplicable_p T, class ...Fs>
XTAL_DEF_(return,inline,let)
operator >> (operate<Fs...> const &, T const &t)
noexcept -> decltype(auto)
{
	auto o = operate<Fs...>::template object<T>();
	if constexpr (integral_variable_q<T, decltype(o)>)  {
		if (t < T{}) {o <<= -t;}
		else         {o >>=  t;}
	}
	else {
		o *= fit<T>::haplo_f(t);
	}
	return o;
}


namespace _detail
{///////////////////////////////////////////////////////////////////////////////

template <auto o>
auto constexpr operate_v = [] XTAL_1FN -> auto {
	XTAL_IF0
	XTAL_0IF (  applicable_q<decltype(o)>) {return                  (o);}
	XTAL_0IF (inapplicable_q<decltype(o)>) {return [] XTAL_1FN_(to) (o);}
}();


}///////////////////////////////////////////////////////////////////////////////

template <auto ...oo>
auto constexpr operate_v = operate{_detail::operate_v<oo>...};

template <auto ...oo>
using operate_t = decltype(operate_v<oo...>);


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
