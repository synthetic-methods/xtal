#pragma once
#include "./any.hpp"






XTAL_ENV_(push)
namespace xtal
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//\
Structural types...

template <class X, class Y>
XTAL_CN2 equal_f(X const &x, Y const &y)
XTAL_0EX
{
	using W = common_t<X, Y>;
	return (W) x == (W) y;
}
template <iterated_q X, iterated_q Y> requires epimorphic_p<X, Y>
XTAL_CN2 equal_f(X &&x, Y &&y)
XTAL_0EX
{
	return _v3::ranges::equal(XTAL_REF_(x), XTAL_REF_(y));
}

template <class X, class Y>
XTAL_CN2 equivalent_f(X &&x, Y &&y)
XTAL_0EX
{
	return equal_f(XTAL_REF_(x), XTAL_REF_(y));
}
template <iterated_q X, iterated_q Y> requires isomorphic_p<X, Y>
XTAL_CN2 equivalent_f(X const &x, Y const &y)
XTAL_0EX
{
	return x.begin() == y.begin() and x.end() == y.end();
}


////////////////////////////////////////////////////////////////////////////////

template <auto   ... >  XTAL_CN2 method_f(XTAL_DEF o) {return XTAL_REF_(o);}
///< Parameter-agnostic identity `method`. \

template <class    M >   XTAL_CN2 member_f(XTAL_DEF w)     XTAL_0EX XTAL_REQ debased_q<M> {return &XTAL_REF_(w);}// obtain address
template <class    M >   XTAL_CN2 member_f(XTAL_DEF w)     XTAL_0EX {return to_f<M>(XTAL_REF_(w));}
template <class    M >   XTAL_CN2 member_f(XTAL_DEF ...ws) XTAL_0EX {return to_f<M>(XTAL_REF_(ws)...);}

template <class    W > XTAL_CN2 remember_f(W &&w) XTAL_0EX XTAL_REQ_(*w) {return *XTAL_REF_(w);}
template <class    W > XTAL_CN2 remember_f(W &&w) XTAL_0EX               {return  XTAL_REF_(w);}
///< Governs access to the underlying member. \

template <remember_q V>
XTAL_CN2 dismember_f(V &v, V w)
XTAL_0EX
{
	_std::swap(w, v); return XTAL_MOV_(v);
}
template <remember_q V>
XTAL_CN2 dismember_f(V &v, XTAL_DEF... w)
XTAL_0EX
{
	return dismember_f<V>(v, member_f<V>(XTAL_REF_(w)...));
}
///< Replaces the body of the underlying member. \


template <class    I >
XTAL_LET appointer_f = [] (auto i) XTAL_0FN_(_std::launder(reinterpret_cast<I>(i)));


template <class Y> XTAL_CN2 force_f(XTAL_DEF_(forcible_q) t) XTAL_0EX {return reinterpret_cast<Y>(XTAL_REF_(t));}
template <class Y> XTAL_CN2 funge_f(XTAL_DEF_(fungible_q) t) XTAL_0EX {return      static_cast<Y>(XTAL_REF_(t));}
template <class Y>
XTAL_CN2 forge_f(XTAL_DEF t)
XTAL_0EX
{
	XTAL_IF1 (fungible_q<Y, decltype(t)>) {
		return funge_f<Y>(XTAL_REF_(t));
	}
	XTAL_IF2 (forcible_q<Y, decltype(t)>) {
		return force_f<Y>(XTAL_REF_(t));
	}
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//\
Range types...

template <class    T >    XTAL_CN2 deranged_f(T &&t) XTAL_0EX {return deranged_t<T>(XTAL_REF_(t));}

template <iterator_q I>   XTAL_CN2 reverser_f(I   i) XTAL_0EX {return _std::make_reverse_iterator(i);}
template <iterator_q I>   XTAL_CN2    mover_f(I   i) XTAL_0EX {return _std::   make_move_iterator(i);}


template <counter_p I>     XTAL_CN2 counted_f(I i0, I iN) {return counted_t<I>(i0, iN);}
template <class    T>      XTAL_CN2 counted_f(T &&t)      {return counted_t<T>(XTAL_REF_(t));}
template <class    T>      XTAL_CN2 counter_f(T &&t)      {return counter_t<T>(XTAL_REF_(t));}
template <class    T>
XTAL_CN2 count_f(T &&t)
XTAL_0EX
{
	if constexpr (counter_q<T>) {
		return XTAL_REF_(t);
	}
	else if constexpr (counted_q<T>) {
		return 1 + t.back() - XTAL_REF_(t).front();
	}
	else if constexpr (bracket_q<T>) {
		return      t.end() - XTAL_REF_(t).begin();
	}
	else if constexpr (requires {t.size();}) {
		return XTAL_REF_(t).size();
	}
	else {
		return (sign_t) 0;
	}
}
///<\returns the `size` of the given range. \

///<\note\
If provided with an `iota_view`, \
returns a `value_type` instead of `size_type` which is twice the width. \

template <class  T>
XTAL_CN2 recount_f(T &&t)
XTAL_0EX
{
	return _v3::views::take(count_f(XTAL_REF_(t)));
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//\
Debugging...

#if not XTAL_LOG
class
{
public:
	XTAL_OP1() (XTAL_DEF ...xs)
	{
		if constexpr (0 < sizeof...(xs)) {
			return (XTAL_REF_(xs), ...);
		}
	}

} echo;
#else
#include <iostream>
class
{
	XTAL_FN0 print_list(XTAL_DEF x)
	{
		for (XTAL_DEF w: XTAL_REF_(x)) ::std::cout << XTAL_REF_(w) << '\t';
	}
	XTAL_FN0 print_item(XTAL_DEF x)
	{
		using W = XTAL_TYP_(x);
		if constexpr (::std::is_floating_point_v<W>) {
			::std::cout.precision(17);
		}
		if constexpr (::std::is_arithmetic_v<W>) {
			if (::std::copysign(1.0, x) == 1.0) {
				 ::std::cout << ' ';
			}
		}
		::std::cout << XTAL_REF_(x) << '\t';
	}
	XTAL_FN1 put(XTAL_DEF x)
	{
		using W = XTAL_TYP_(x);
		if constexpr (_v3::ranges::range<W> and requires {::std::is_arithmetic_v<typename W::value_type>;}) {
			print_list(XTAL_REF_(x));
		}
		else {
			print_item(XTAL_REF_(x));
		}
		return XTAL_REF_(x);
	}

public:
	XTAL_OP1() (XTAL_DEF ...xs)
	{
		if constexpr (0 < sizeof...(xs)) {
			::std::cout << '\t'; auto const x = (put(XTAL_REF_(xs)), ...);
			::std::cout << '\n';
			return x;
		}
		else {
			::std::cout << '\n';
		}
	}

} echo;
#endif


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
