#pragma once
#include "./any.hh"
#include "./pack.hh"
#include "./seek.hh"

//#include <ranges>


XTAL_ENV_(push)
namespace xtal::bond
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <class ...Us>
XTAL_TYP pact
{	using type = _std::tuple<Us...>;
};
template <class ...Us> requires (2 == sizeof...(Us))
XTAL_TYP pact<Us...>
{	using type = _std::pair <Us...>;
};
template <class ...Us>
using pact_t = typename pact<Us...>::type;

XTAL_LET pact_f = []<class ...Us> (Us &&...us)
XTAL_0FN
{
	return pact_t<Us...>(XTAL_REF_(us)...);
};


template <class ...Ts>
XTAL_TYP pact_size : cardinal_t<(0 +...+ pact_size<Ts>::value)> {};

template <class T>
XTAL_TYP pact_size<T> : _std::tuple_size<T> {};

template <devalue_q T>
XTAL_TYP pact_size<T> : cardinal_t<devalue_n<T>> {};

template <class ...Ts>
XTAL_LET pact_size_n = pact_size<_std::remove_reference_t<Ts>...>::value;

template <class ...Ts>
XTAL_FN2 pact_size_f(Ts &&...)
XTAL_0EX {return pact_size_n<Ts...>;}


template <size_t I, class ...Ts>
XTAL_TYP pact_element;

template <size_t I, class T>
XTAL_TYP pact_element<I, T> : _std::tuple_element<I, T> {};

template <size_t I, devalue_q T>
XTAL_TYP pact_element<I, T> {using type = typename T::value_type;};

template <size_t I, class T, class ...Ts> requires (I >= pact_size_n<T>)
XTAL_TYP pact_element<I, T, Ts...> : pact_element<I - pact_size_n<T>, Ts...> {};

template <size_t I, class ...Ts>
XTAL_USE pact_element_t = typename pact_element<I, _std::remove_reference_t<Ts>...>::type;

template <class Q, size_t I, class ...Ts>
XTAL_ASK pact_element_q = is_q<Q, pact_element_t<I, Ts...>>;


template <size_t I, class T>
XTAL_FN2 pact_item_f(T &&t)
XTAL_0EX
{
	XTAL_IF0
	XTAL_0IF_(requires {{get<I>(XTAL_REF_(t))} -> pact_element_q<I, T>;}) {
		return get<I>(XTAL_REF_(t));
	}
	XTAL_0IF_(devalue_q<T> and not _std::is_const_v<T>) {
		return reinterpret_cast<      devalue_u<T>(&)[devalue_f(t)]>(XTAL_REF_(t))[I];
	}
	XTAL_0IF_(devalue_q<T> and     _std::is_const_v<T>) {
		return reinterpret_cast<const devalue_u<T>(&)[devalue_f(t)]>(XTAL_REF_(t))[I];
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
XTAL_TYP pact_make
{
	template <class     > struct build;
	template <auto ...Is> struct build<bond::seek_t<Is...>>
	{
		using type = pact_t<pact_element_t<Is, Ts...>...>;

	};
	using type = typename build<bond::seek_s<pact_size_n<Ts...>>>::type;

};
template <class ...Ts>
XTAL_USE pact_make_t = typename pact_make<_std::remove_reference_t<Ts>...>::type;

XTAL_LET pact_make_f = []<class ...Ts> (Ts &&...ts)
XTAL_0FN
{
	return [&]<auto ...Is> (bond::seek_t<Is...>)
		XTAL_0FN_(pact_make_t<Ts...>(pact_item_f<Is>(ts...)...))
	(bond::seek_s<pact_size_n<Ts...>>{});
};
template <auto f>
XTAL_LET impact_make_f = []<class ...Ts> (Ts &&...ts)
XTAL_0FN
{
	return [&]<auto ...Is> (bond::seek_t<Is...>)
		XTAL_0FN_(pact_f(f(pact_item_f<Is>(ts...))...))
	(bond::seek_s<pact_size_n<Ts...>>{});
};



template <class ...Ts>
XTAL_TYP pact_made
{
	template <class     > struct build;
	template <auto ...Is> struct build<bond::seek_t<Is...>>
	{
		using type = pact_t<pact_element_t<Is, Ts...> &...>;

	};
	using type = typename build<bond::seek_s<pact_size_n<Ts...>>>::type;

};
template <class ...Ts>
XTAL_USE pact_made_t = typename pact_made<_std::remove_reference_t<Ts>...>::type;

XTAL_LET pact_made_f = []<class ...Ts> (Ts &&...ts)
XTAL_0FN
{
	return [&]<auto ...Is> (bond::seek_t<Is...>) XTAL_0FN {
		return pact_made_t<Ts...>(pact_item_f<Is>(ts...)...);
	}	(bond::seek_s<pact_size_n<Ts...>>{});
};


////////////////////////////////////////////////////////////////////////////////

template <size_t N, accessed_q W>
XTAL_FN2 pact_bind_f(W &&w, size_t const &n)
XTAL_0EX
{
	using _std::span;
	//\
	using _std::ranges::views::zip;
	using _v3::views::zip;

	return [&]<size_t ...Is> (bond::seek_t<Is...>)
		XTAL_0FN_(zip(span(point_f(w[Is]), n)...))
	(bond::seek_s<N>{});
}
template <size_t N, accessed_q W>
XTAL_FN2 pact_bind_f(size_t const &n, W &&w)
XTAL_0EX
{
	return pact_bind_f<N>(XTAL_REF_(w), n);
}
template <size_t N>
XTAL_FN2 pact_bind_f(size_t n)
XTAL_0EX
{
	return [=] (auto &&w) XTAL_0FN_(pact_bind_f<N>(n, XTAL_REF_(w)));
}


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
