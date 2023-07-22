#include "../common/_kernel.hxx"

namespace _detail
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

using namespace _retail::_detail;


////////////////////////////////////////////////////////////////////////////////

template <class T, class Y=T>
concept connected_p = any_p<T> and requires (T t)
{
	{t.serve()} -> isomorphic_p<Y>;
};
template <class T, class Y=T>
concept collected_p = any_p<T> and requires (T t)
{
	{t.serve()} -> isomorphic_p<Y>;
	{t.store()} -> isomorphic_p<Y>;
};
template <class T, class Y>
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


template <accessory_t N, class Z>
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
	return access_f<N|accessory::finite{}>(XTAL_REF_(z))|recount_f(z);
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

XTAL_LET mix_f = zap_f([] (XTAL_DEF ...xs) XTAL_0FN_(XTAL_REF_(xs) +...+ 0));

template <iterator_q ...Xs>
XTAL_CN2 funnel_f(XTAL_DEF y, Xs &&...xs)
XTAL_0EX
{
	auto w_ = recount_f(y);
	if constexpr (1 < sizeof...(xs)) {
		return mix_f(XTAL_REF_(y), mix_f((*XTAL_REF_(xs)|w_)...));
	}
	else if constexpr (1 == sizeof...(xs)) {
		return mix_f(XTAL_REF_(y), (*XTAL_REF_(xs)|w_)...);
	}
	else if constexpr (0 == sizeof...(xs)) {
		return XTAL_REF_(y);
	}
}
template <iterator_q ...Xs>
XTAL_CN0 tunnel_f(XTAL_DEF y, Xs &&...xs)
XTAL_0EX
{
	auto v_ = y.begin();
	if constexpr (0 < sizeof...(xs)) {
		_v3::ranges::move(funnel_f(XTAL_REF_(y), XTAL_REF_(xs)...), v_);
	}
}

template <size_t N>
XTAL_CN2 funnel_f(XTAL_DEF y, iterator_q auto x)
XTAL_0EX
{
	return [&]<auto ...I>(seek_t<I...>)
		XTAL_0FN_(funnel_f(y, _std::next(x, I)...))
	(seek_f<N> {});
}
template <size_t N>
XTAL_CN0 tunnel_f(XTAL_DEF y, iterator_q auto x)
XTAL_0EX
{
	return [&]<auto ...I>(seek_t<I...>)
		XTAL_0FN_(tunnel_f(y, _std::next(x, I)...))
	(seek_f<N> {});
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <class T> concept unprocessed_p = operators_q<T> and not _retail::any_q<T>;


}//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
