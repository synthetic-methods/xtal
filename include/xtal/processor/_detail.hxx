#pragma once
#ifdef __INTELLISENSE__// stub...
#include "./any.hpp"
#endif





namespace _detail
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

using namespace _retail::_detail;


////////////////////////////////////////////////////////////////////////////////

template <typename T, typename Y=T>
concept connected_p = any_p<T> and requires (T t)
{
	{t.serve()} -> isomorphic_p<Y>;
};
template <typename T, typename Y=T>
concept collected_p = any_p<T> and requires (T t)
{
	{t.serve()} -> isomorphic_p<Y>;
	{t.store()} -> isomorphic_p<Y>;
};
template <typename T, typename Y>
concept recollected_p = collected_p<T, Y> and _std::is_rvalue_reference_v<T>;


////////////////////////////////////////////////////////////////////////////////

struct accessory
{
	using   type = _v3::ranges::category;
	using   pure = constant_t<type::random_access>;
	using impure = constant_t<type::forward>;
	using finite = constant_t<type::sized>;

};
using accessory_t = typename accessory::type;


template <accessory_t N, typename Z>
using access_t = _v3::ranges::any_view<iteratee_t<Z>, N>;

template <accessory_t N>
XTAL_CN2 access_f(XTAL_DEF z)
XTAL_0EX
{
	return access_t<N, XTAL_TYP_(z)>(XTAL_REF_(z));
}
template <accessory_t N>
XTAL_CN2 access_f(XTAL_DEF z)
XTAL_0EX
XTAL_REQ  (N != (N|accessory::finite{})) and requires {z.size();}
{
	return access_f<N|accessory::finite{}>(XTAL_REF_(z))|taker_f(z);
}


XTAL_CN2 purify_f(XTAL_DEF z)
XTAL_0EX
{
	return access_f<accessory::pure{}>(XTAL_REF_(z));
}
XTAL_CN2 impurify_f(XTAL_DEF z)
XTAL_0EX
{
	return access_f<accessory::impure{}>(XTAL_REF_(z));
}


////////////////////////////////////////////////////////////////////////////////

XTAL_CN2 forever_f(XTAL_DEF z)
XTAL_0EX
{
	return purify_f(_v3::views::repeat(XTAL_REF_(z)));
}

XTAL_CN2 zap_f(XTAL_DEF f)
XTAL_0EX
{
	using namespace _v3::views;
	return [f = XTAL_REF_(f)] (XTAL_DEF ...xs)
	XTAL_0FN {
		if constexpr (0 == sizeof...(xs)) {
			return forever_f(f)|transform([] (XTAL_DEF f) XTAL_0FN_(XTAL_REF_(f) ()));
		//	return generate(f);// FIXME!
		}
		else if constexpr (1 == sizeof...(xs)) {
			return transform(XTAL_REF_(xs)..., f);
		}
		else if constexpr (1 <  sizeof...(xs)) {
			return zip_with(f, XTAL_REF_(xs)...);
		}
	};
};

XTAL_LET mix_f = _detail::zap_f([] (XTAL_DEF ...xs) XTAL_0FN_(XTAL_REF_(xs) +...+ 0));

template <typename T> concept      mundane_p = not _retail::any_q<T>;
template <typename T> concept  unprocessed_p = mundane_p<T> and operators_q<T>;
template <typename T> concept preprocessed_p = mundane_p<T> and   iterated_q<T>;


}//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
