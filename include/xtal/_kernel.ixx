//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//\
Structural...

template <class T>
XTAL_LET as_f = [] XTAL_1FN_(T);


////////////////////////////////////////////////////////////////////////////////

template <class T>
XTAL_FN2 funge_f(auto &&u)
XTAL_0EX
{
	using U = decltype(u);
	static_assert(fungible_q<T, U>);
	return      static_cast<qualify_t<T, U>>(XTAL_FWD_(u));
}
template <class T>
XTAL_FN2 force_f(auto &&u)
XTAL_0EX
{
	using U = decltype(u);
	static_assert(forcible_q<T, U>);
	return reinterpret_cast<qualify_t<T, U>>(XTAL_FWD_(u));
}

template <class T>
XTAL_FN2 forge_f(auto &&u)
XTAL_0EX
{
	using U = decltype(u);
	if constexpr (fungible_q<T, U>) {
		return funge_f<T>(XTAL_FWD_(u));
	}	else
	if constexpr (forcible_q<T, U>) {
		return force_f<T>(XTAL_FWD_(u));
	}
}


////////////////////////////////////////////////////////////////////////////////

template <class  M > XTAL_FN2   member_f(auto &&w)     XTAL_0EX XTAL_REQ debased_q<M> {return &XTAL_FWD_(w);}
template <class  M > XTAL_FN2   member_f(auto &&w)     XTAL_0EX {return as_f<M>(XTAL_FWD_(w));}
template <class  M > XTAL_FN2   member_f(auto &&...ws) XTAL_0EX {return as_f<M>(XTAL_FWD_(ws)...);}

template <class  W > XTAL_FN2 remember_f(W &&w) XTAL_0EX XTAL_REQ_(*w) {return *XTAL_FWD_(w);}
template <class  W > XTAL_FN2 remember_f(W &&w) XTAL_0EX               {return  XTAL_FWD_(w);}
///< Governs access to the underlying member. \

template <rebased_q V>
XTAL_FN2 dismember_f(V &v, V w)
XTAL_0EX
{
	_std::swap(w, v); return XTAL_MOV_(v);
}
template <rebased_q V>
XTAL_FN2 dismember_f(V &v, auto &&...w)
XTAL_0EX
{
	return dismember_f<V>(v, member_f<V>(XTAL_FWD_(w)...));
}
///< Replaces the body of the underlying member. \


////////////////////////////////////////////////////////////////////////////////

template <class    I >
XTAL_LET appointer_f = [] (auto i) XTAL_0FN_(_std::launder(reinterpret_cast<I>(i)));


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//\
Ranged...

template <class      T >   XTAL_FN2    visor_f(T &&t) XTAL_0EX {return visor_t<T>(XTAL_FWD_(t));}
template <iterator_q I >	XTAL_FN2    mover_f(I   i) XTAL_0EX {return _std::   make_move_iterator(i);}
template <iterator_q I >	XTAL_FN2 reverser_f(I   i) XTAL_0EX {return _std::make_reverse_iterator(i);}


////////////////////////////////////////////////////////////////////////////////

template <counter_q  I >	XTAL_FN2 counted_f(I i0, I iN) {return counted_t<I>(i0, iN);}
template <class      T >	XTAL_FN2 counted_f(T &&t)      {return counted_t<T>(XTAL_FWD_(t));}
template <class      T >	XTAL_FN2 counter_f(T &&t)      {return counter_t<T>(XTAL_FWD_(t));}


template <class    T>
XTAL_FN2 count_f(T &&t)
XTAL_0EX
{
	if constexpr (counter_q<T>) {
		return XTAL_FWD_(t);
	}	else
	if constexpr (counted_q<T>) {
		return 1 + t.back() - XTAL_FWD_(t).front();
	}	else
	if constexpr (bracket_q<T>) {
		return      t.end() - XTAL_FWD_(t).begin();
	}	else
	if constexpr (requires {t.size();}) {
		return XTAL_FWD_(t).size();
	}	else
	{
		return (size_t) 0;
	}
}
///<\returns the `size` of the given range. \

///<\note\
If provided with an `iota_view`, \
returns a `value_type` instead of `size_type` which is twice the width. \

template <class  T>
XTAL_FN2 recount_f(T &&t)
XTAL_0EX
{
	return _v3::views::take(count_f(XTAL_FWD_(t)));
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//\
Arithmetic...

template <class X, class Y>
XTAL_FN2 equal_f(X const &x, Y const &y)
XTAL_0EX
{
	using W = common_t<X, Y>;
	return (W) x == (W) y;
}
template <iterated_q X, iterated_q Y> requires epimorphic_q<X, Y>
XTAL_FN2 equal_f(X &&x, Y &&y)
XTAL_0EX
{
	return _v3::ranges::equal(XTAL_FWD_(x), XTAL_FWD_(y));
}

template <class X, class Y>
XTAL_FN2 equivalent_f(X &&x, Y &&y)
XTAL_0EX
{
	return equal_f(XTAL_FWD_(x), XTAL_FWD_(y));
}
template <iterated_q X, iterated_q Y> requires isomorphic_q<X, Y>
XTAL_FN2 equivalent_f(X const &x, Y const &y)
XTAL_0EX
{
	return x.begin() == y.begin() and x.end() == y.end();
}


////////////////////////////////////////////////////////////////////////////////

template <extremum_q T>
XTAL_FN2 extremum_f(sign_t const &n_direction)
XTAL_0EX
{
	switch (n_direction) {
	case -1: return extremum_t<T>::min();
	case  1: return extremum_t<T>::max();
	default: return (T) 0;
	}
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#if not XTAL_SIC
class
{
public:
	XTAL_OP1() (auto &&...xs)
	{
		if constexpr (0 < sizeof...(xs)) {
			return (XTAL_FWD_(xs), ...);
		}
	}

} echo;
#else
class
{
	XTAL_TN0 print_list(auto &&x)
	{
		for (auto &&w: XTAL_FWD_(x)) ::std::cout << XTAL_FWD_(w) << '\t';
	}
	XTAL_TN0 print_item(auto &&x)
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
		::std::cout << XTAL_FWD_(x) << '\t';
	}
	XTAL_TN1 put(auto &&x)
	{
		using W = XTAL_TYP_(x);
		if constexpr (_v3::ranges::range<W> and requires {::std::is_arithmetic_v<typename W::value_type>;}) {
			print_list(XTAL_FWD_(x));
		}
		else {
			print_item(XTAL_FWD_(x));
		}
		return XTAL_FWD_(x);
	}

public:
	XTAL_OP1() (auto &&...xs)
	{
		if constexpr (0 < sizeof...(xs)) {
			::std::cout << '\t'; auto const x = (put(XTAL_FWD_(xs)), ...);
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
//////////////////////////////////////////////////////////////////////////////
