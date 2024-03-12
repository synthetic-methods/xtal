//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//\
Structural...

template <class T> XTAL_LET make_f = [] XTAL_1FN_(T);


////////////////////////////////////////////////////////////////////////////////

template <class Y> XTAL_FN2 force_f(XTAL_DEF_(forcible_q) t) XTAL_0EX {return reinterpret_cast<Y>(XTAL_REF_(t));}
template <class Y> XTAL_FN2 funge_f(XTAL_DEF_(fungible_q) t) XTAL_0EX {return      static_cast<Y>(XTAL_REF_(t));}
template <class Y>
XTAL_FN2 forge_f(XTAL_DEF t)
XTAL_0EX
{
	if constexpr (fungible_q<Y, decltype(t)>) {
		return funge_f<Y>(XTAL_REF_(t));
	}	else
	if constexpr (forcible_q<Y, decltype(t)>) {
		return force_f<Y>(XTAL_REF_(t));
	}
}


////////////////////////////////////////////////////////////////////////////////

template <class  M > XTAL_FN2   member_f(XTAL_DEF w)     XTAL_0EX XTAL_REQ debased_q<M> {return &XTAL_REF_(w);}
template <class  M > XTAL_FN2   member_f(XTAL_DEF w)     XTAL_0EX {return make_f<M>(XTAL_REF_(w));}
template <class  M > XTAL_FN2   member_f(XTAL_DEF ...ws) XTAL_0EX {return make_f<M>(XTAL_REF_(ws)...);}

template <class  W > XTAL_FN2 remember_f(W &&w) XTAL_0EX XTAL_REQ_(*w) {return *XTAL_REF_(w);}
template <class  W > XTAL_FN2 remember_f(W &&w) XTAL_0EX               {return  XTAL_REF_(w);}
///< Governs access to the underlying member. \

template <rebased_q V>
XTAL_FN2 dismember_f(V &v, V w)
XTAL_0EX
{
	_std::swap(w, v); return XTAL_MOV_(v);
}
template <rebased_q V>
XTAL_FN2 dismember_f(V &v, XTAL_DEF... w)
XTAL_0EX
{
	return dismember_f<V>(v, member_f<V>(XTAL_REF_(w)...));
}
///< Replaces the body of the underlying member. \


////////////////////////////////////////////////////////////////////////////////

template <class    I >
XTAL_LET appointer_f = [] (auto i) XTAL_0FN_(_std::launder(reinterpret_cast<I>(i)));


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//\
Ranged...

template <class    T >    XTAL_FN2 deranged_f(T &&t) XTAL_0EX {return deranged_t<T>(XTAL_REF_(t));}

template <iterator_q I>   XTAL_FN2 reverser_f(I   i) XTAL_0EX {return _std::make_reverse_iterator(i);}
template <iterator_q I>   XTAL_FN2    mover_f(I   i) XTAL_0EX {return _std::   make_move_iterator(i);}


////////////////////////////////////////////////////////////////////////////////

template <counter_q I>     XTAL_FN2 counted_f(I i0, I iN) {return counted_t<I>(i0, iN);}
template <class    T>      XTAL_FN2 counted_f(T &&t)      {return counted_t<T>(XTAL_REF_(t));}
template <class    T>      XTAL_FN2 counter_f(T &&t)      {return counter_t<T>(XTAL_REF_(t));}


template <class    T>
XTAL_FN2 count_f(T &&t)
XTAL_0EX
{
	if constexpr (counter_q<T>) {
		return XTAL_REF_(t);
	}	else
	if constexpr (counted_q<T>) {
		return 1 + t.back() - XTAL_REF_(t).front();
	}	else
	if constexpr (bracket_q<T>) {
		return      t.end() - XTAL_REF_(t).begin();
	}	else
	if constexpr (requires {t.size();}) {
		return XTAL_REF_(t).size();
	}	else
	{
		return (sign_t) 0;
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
	return _v3::views::take(count_f(XTAL_REF_(t)));
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//\
Arithmetic...

template <class X, class Y>
XTAL_FN2 equal_f(X const &x, Y const &y)
XTAL_0EX
{
	using W = shared_t<X, Y>;
	return (W) x == (W) y;
}
template <iterated_q X, iterated_q Y> requires epimorphic_q<X, Y>
XTAL_FN2 equal_f(X &&x, Y &&y)
XTAL_0EX
{
	return _v3::ranges::equal(XTAL_REF_(x), XTAL_REF_(y));
}

template <class X, class Y>
XTAL_FN2 equivalent_f(X &&x, Y &&y)
XTAL_0EX
{
	return equal_f(XTAL_REF_(x), XTAL_REF_(y));
}
template <iterated_q X, iterated_q Y> requires isomorphic_q<X, Y>
XTAL_FN2 equivalent_f(X const &x, Y const &y)
XTAL_0EX
{
	return x.begin() == y.begin() and x.end() == y.end();
}


///////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////