#include "../cell/_kernel.hxx"








namespace _detail
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

using namespace _retail::_detail;


////////////////////////////////////////////////////////////////////////////////

template <class T, class Y=T>
concept connection_p = any_q<T> and requires (T t)
{
	{t.serve()} -> isomorphic_q<Y>;
};
template <class T, class Y=T>
concept collection_p = any_q<T> and requires (T t)
{
	{t.serve()} -> isomorphic_q<Y>;
	{t.store()} -> isomorphic_q<Y>;
};
template <class T, class Y>
concept recollection_p = collection_p<T, Y> and _std::is_rvalue_reference_v<T>;


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
XTAL_FN2 access_f(auto &&z)
XTAL_0EX
{
	return access_t<N, XTAL_TYP_(z)>(XTAL_FWD_(z));
}
template <accessory_t N>
XTAL_FN2 access_f(auto &&z)
XTAL_0EX
XTAL_REQ  (N != (N|accessory::finite{})) and requires {z.size();}
{
	return access_f<N|accessory::finite{}>(XTAL_FWD_(z))|recount_f(z);
}


XTAL_FN2 purify_f(auto &&z)
XTAL_0EX
{
	return access_f<accessory::pure{}>(XTAL_FWD_(z));
}
XTAL_FN2 impurify_f(auto &&z)
XTAL_0EX
{
	return access_f<accessory::impure{}>(XTAL_FWD_(z));
}


////////////////////////////////////////////////////////////////////////////////

XTAL_FN2 forever_f(auto &&z)
XTAL_0EX
{
	return purify_f(_v3::views::repeat(XTAL_FWD_(z)));
}

XTAL_FN2 map_f(auto &&f)
XTAL_0EX
{
	using namespace _v3::views;
	return [f = XTAL_FWD_(f)] (auto &&...xs)
	XTAL_0FN {
		if constexpr (0 == sizeof...(xs)) {
			return forever_f(f)|transform([] (auto &&f) XTAL_0FN_(XTAL_FWD_(f) ()));
		//	return generate(f);// FIXME!
		}	else
		if constexpr (1 == sizeof...(xs)) {
			return transform(XTAL_FWD_(xs)..., f);
		}	else
		if constexpr (1 <  sizeof...(xs)) {
			return zip_with(f, XTAL_FWD_(xs)...);
		}
	};
};

XTAL_LET zip_f = [] XTAL_1FN_(_v3::views::zip);
XTAL_LET zap_f = map_f([] XTAL_1FN_(_std::tie));
XTAL_LET mix_f = map_f([] (auto &&...xs) XTAL_0FN_(XTAL_FWD_(xs) +...+ 0));

template <iterator_q ...Xs>
XTAL_FN2 funnel_f(auto &&y, Xs &&...xs)
XTAL_0EX
{
	auto w_ = recount_f(y);
	if constexpr (1 < sizeof...(xs)) {
		return mix_f(XTAL_FWD_(y), mix_f((*XTAL_FWD_(xs)|w_)...));
	}	else
	if constexpr (1 == sizeof...(xs)) {
		return mix_f(XTAL_FWD_(y), (*XTAL_FWD_(xs)|w_)...);
	}	else
	if constexpr (0 == sizeof...(xs)) {
		return XTAL_FWD_(y);
	}
}
template <iterator_q ...Xs>
XTAL_FN0 tunnel_f(auto &&y, Xs &&...xs)
XTAL_0EX
{
	auto v_ = y.begin();
	if constexpr (0 < sizeof...(xs)) {
		_v3::ranges::move(funnel_f(XTAL_FWD_(y), XTAL_FWD_(xs)...), v_);
	}
}

template <size_t N>
XTAL_FN2 funnel_f(auto &&y, iterator_q auto x)
XTAL_0EX
{
	return [&]<auto ...I>(bond::seek_t<I...>)
		XTAL_0FN_(funnel_f(y, _std::next(x, I)...))
	(bond::seek_f<N> {});
}
template <size_t N>
XTAL_FN0 tunnel_f(auto &&y, iterator_q auto x)
XTAL_0EX
{
	return [&]<auto ...I>(bond::seek_t<I...>)
		XTAL_0FN_(tunnel_f(y, _std::next(x, I)...))
	(bond::seek_f<N> {});
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

XTAL_FN2 squint_f(auto &&it, size_t is)
XTAL_0EX
{
	using It = XTAL_TYP_(it);
	using At = iteratee_t<It>;
	return _v3::ranges::span<At>(XTAL_FWD_(it), is);
}
template <size_t N_width>
XTAL_FN2 squint_f(auto &&it, size_t is)
XTAL_0EX
{
	return [&] <auto ...I>(bond::seek_t<I...>)
		XTAL_0FN_(_v3::views::zip(squint_f(it[I], is)...))
	(bond::seek_f<N_width>{});
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <class T> concept unprocessed_p = algebraic_field_q<T> and not _retail::any_q<T>;


}//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
