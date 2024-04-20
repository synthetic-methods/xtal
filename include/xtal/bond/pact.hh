#pragma once
#include "./any.hh"
#include "./pack.hh"
#include "./seek.hh"




XTAL_ENV_(push)
namespace xtal::bond
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <class ...Us>
XTAL_DEF pact
{	using type = _v3::ranges::common_tuple<Us...>;
};
template <class ...Us> requires (2 == sizeof...(Us))
XTAL_DEF pact<Us...>
{	using type = _v3::ranges::common_pair <Us...>;
};
template <class ...Us>
using pact_t = typename pact<Us...>::type;


template <class ...Ts>
XTAL_DEF pact_size : cardinal_t<(0 +...+ pact_size<Ts>::value)> {};

template <class T>
XTAL_DEF pact_size<T> : _std::tuple_size<T> {};

template <devalue_q T>
XTAL_DEF pact_size<T> : cardinal_t<devalue_n<T>> {};

template <class ...Ts>
XTAL_LET pact_size_n = pact_size<_std::remove_reference_t<Ts>...>::value;

template <class ...Ts>
XTAL_FN2 pact_size_f(Ts &&...)
XTAL_0EX {return pact_size_n<Ts...>;}


template <size_t I, class ...Ts>
XTAL_DEF pact_element;

template <size_t I, class T>
XTAL_DEF pact_element<I, T> : _std::tuple_element<I, T> {};

template <size_t I, devalue_q T>
XTAL_DEF pact_element<I, T> {using type = typename T::value_type;};

template <size_t I, class T, class ...Ts> requires (I >= pact_size_n<T>)
XTAL_DEF pact_element<I, T, Ts...> : pact_element<I - pact_size_n<T>, Ts...> {};

template <size_t I, class ...Ts>
XTAL_USE pact_element_t = typename pact_element<I, _std::remove_reference_t<Ts>...>::type;

template <class Q, size_t I, class ...Ts>
XTAL_ASK pact_element_q = is_q<Q, pact_element_t<I, Ts...>>;


template <size_t I, class T>
XTAL_FN2 pact_item_f(T &&t)
XTAL_0EX
{
	XTAL_IF0
	XTAL_0IF_(requires {{_std::get<I>(XTAL_REF_(t))} -> pact_element_q<I, T>;}) {
		return _std::get<I>(XTAL_REF_(t));
	}
	XTAL_0IF_(devalue_q<T> and not _std::is_const_v<T>) {
		return reinterpret_cast<      devalue_t<T>(&)[devalue_n<T>]>(XTAL_REF_(t))[I];
	}
	XTAL_0IF_(devalue_q<T> and     _std::is_const_v<T>) {
		return reinterpret_cast<const devalue_t<T>(&)[devalue_n<T>]>(XTAL_REF_(t))[I];
	}
}
template <size_t I, class T, class ...Ts>
XTAL_FN2 pact_item_f(T &&t, Ts &&...ts)
XTAL_0EX
{
	if constexpr (I >= pact_size_n<T>) {
		return pack_item_f<I - pact_size_n<T>>(XTAL_REF_(ts)...);
	}
	else {
		return pack_item_f<I>(XTAL_REF_(t));
	}
}


template <class ...Ts>
XTAL_DEF pact_make
{
	template <class     > struct solve;
	template <auto ...Is> struct solve<bond::seek_t<Is...>>
	{
		using type = pact_t<pact_element_t<Is, Ts...>...>;

	};
	using type = typename solve<bond::seek_f<pact_size_n<Ts...>>>::type;

};
template <class ...Ts>
XTAL_USE pact_make_t = typename pact_make<_std::remove_reference_t<Ts>...>::type;

template <class ...Ts>
XTAL_FN2 pact_make_f(Ts &&...ts)
XTAL_0EX
{
	return [&]<auto ...I>(bond::seek_t<I...>)
		XTAL_0FN_(pact_make_t<Ts...>(pact_item_f<I>(ts...)...))
	(bond::seek_f<pact_size_n<Ts...>> {});
}



template <class ...Ts>
XTAL_DEF pact_made
{
	template <class     > struct solve;
	template <auto ...Is> struct solve<bond::seek_t<Is...>>
	{
		using type = pact_t<pact_element_t<Is, Ts...> &...>;

	};
	using type = typename solve<bond::seek_f<pact_size_n<Ts...>>>::type;

};
template <class ...Ts>
XTAL_USE pact_made_t = typename pact_made<_std::remove_reference_t<Ts>...>::type;

template <class ...Ts>
XTAL_FN2 pact_made_f(Ts &&...ts)
XTAL_0EX
{
	return [&]<auto ...I>(bond::seek_t<I...>)
		XTAL_0FN_(pact_made_t<Ts...>(pact_item_f<I>(ts...)...))
	(bond::seek_f<pact_size_n<Ts...>> {});
}


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
