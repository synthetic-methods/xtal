#pragma once
#include "./any.hh"

#include "./fit.hh"




XTAL_ENV_(push)
namespace xtal::bond
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
Provides an overloaded combination of `<Fs...>`, \
functionally lifted form of `<T>`, or `std::identity` for `<>`. \
Can be used to `std::visit` `std::variant`s via `operator()`, \
and to provide a universal/virtual `constant_q` for non-`std::integral_constant`s. \


////////////////////////////////////////////////////////////////////////////////

template <class... Fs>
struct operate : Fs...
{
	using type = operate;

	using Fs::operator()...;

	template <class ...Ts> XTAL_DEF_(inline,let) operator() (_std::variant<Ts...>       &&v) noexcept -> decltype(auto) {return _std::visit(XTAL_MOV_(v), *this);}
	template <class ...Ts> XTAL_DEF_(inline,let) operator() (_std::variant<Ts...> const &&v) noexcept -> decltype(auto) {return _std::visit(XTAL_MOV_(v), *this);}
	template <class ...Ts> XTAL_DEF_(inline,let) operator() (_std::variant<Ts...>        &v) noexcept -> decltype(auto) {return _std::visit(XTAL_REF_(v), *this);}
	template <class ...Ts> XTAL_DEF_(inline,let) operator() (_std::variant<Ts...> const  &v) noexcept -> decltype(auto) {return _std::visit(XTAL_REF_(v), *this);}

	template <class T>
	XTAL_DEF_(return,inline,set)
	object()
	noexcept -> auto
	requires requires {operate{}();}
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
	requires requires {operate{}();}
	{
		using U = based_t<T>;
		using V = fluid_valued_u<U>;
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
	requires requires {operate{}();}
	{
		return operate{[] XTAL_1FN_(to) (1.F/object<T>())};
	}

	template <class T>
	XTAL_DEF_(return,inline,implicit)
	operator T() const
	noexcept {return object<T>();}

	XTAL_DEF_(return,inline,met) operator + (operate const &t) noexcept -> auto {return operate<decltype([] XTAL_1FN_(to) (+_xtd::make_signed_f(operate{}())))>{};}
	XTAL_DEF_(return,inline,met) operator - (operate const &t) noexcept -> auto {return operate<decltype([] XTAL_1FN_(to) (-_xtd::make_signed_f(operate{}())))>{};}
	XTAL_DEF_(return,inline,met) operator ~ (operate const &t) noexcept -> auto {return operate<decltype([] XTAL_1FN_(to) (~                    operate{}() ))>{};}

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
	
	///\returns the bit-shifted result if `integral_q<T>`, \
	otherwise fractional mutiplication by `exp2(t)`. \
	
	template <inapplicable_p T>
	//\
	XTAL_DEF_(return,met)
	XTAL_DEF_(return,inline,met)
	operator << (same_q<operate> auto const &, T const &t)
	noexcept -> decltype(object<T>())
	{
		auto o = object<T>();
		if constexpr (integral_variable_q<T, decltype(o)>)  {
			if (t < T{}) {o >>= -t;}
			else         {o <<=  t;}
		}
		else {
			o *= fit<T>::diplo_f(t);
		}
		return o;
	}
	///\returns the bit-shifted result if `integral_q<T>`, \
	otherwise fractional division by `exp2(t)`. \
	
	template <inapplicable_p T>
	//\
	XTAL_DEF_(return,met)
	XTAL_DEF_(return,inline,met)
	operator >> (same_q<operate> auto const &, T const &t)
	noexcept -> decltype(object<T>())
	{
		auto o = object<T>();
		if constexpr (integral_variable_q<T, decltype(o)>)  {
			if (t < T{}) {o <<= -t;}
			else         {o >>=  t;}
		}
		else {
			o *= fit<T>::haplo_f(t);
		}
		return o;
	}

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
XTAL_0FN
{
	XTAL_IF0
	XTAL_0IF_(to) (T   {XTAL_REF_(oo)...})
	XTAL_0IF_(to) (T   (XTAL_REF_(oo)...))
	XTAL_0IF_(to) (T{} (XTAL_REF_(oo)...))
})>
{
};
template <>
struct operate<> : _std::identity
{
};


////////////////////////////////////////////////////////////////////////////////

template <class ...Fs>
operate(Fs...) -> operate<Fs...>;

template <auto ...fs>
using operate_t = decltype(operate{fs...});


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
