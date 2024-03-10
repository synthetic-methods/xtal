








namespace _detail
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//\
Standard...

using null_t = XTAL_STD_(null_t);
using unit_t = XTAL_STD_(unit_t);
using sign_t = XTAL_STD_(sign_t);
using byte_t = XTAL_STD_(byte_t);
using size_t = XTAL_STD_(size_t);
using size_s = XTAL_STD_(size_s);
XTAL_LET_(size_t) size_1 = 1;

template <auto     N > XTAL_LET_(sign_t) sign_n = (0 < N) - (N < 0);
template <auto     N >           concept sign_p = _std::integral<decltype(N)> and -1 <= N and N <= 1;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//\
Structural...

template <class      T             >	concept  incomplete_q = not requires {typename _std::void_t<decltype(sizeof(T))>;};
template <class      T             >	concept    complete_q = not incomplete_q<T>;
template <              class ...Ts>	struct     complete              {class type   {};};
template <class      T, class ...Ts>	struct     complete<T, Ts...>:   complete<Ts...> {};
template <complete_q T, class ...Ts>	struct     complete<T, Ts...>    {using type =  T;};
template <              class ...Ts>	using      complete_t = typename complete<Ts...>::type;


template <auto       N >	using    integral   = _std::integral_constant<decltype(N), N>;
template <auto       N >	using    cardinal   = _std::integral_constant<size_t,      N>;
template <auto       N >	using     ordinal   = _std::integral_constant<int,         N>;
template <auto       N >	using     logical   = _std::integral_constant<bool,        N>;

template <class      T >	concept  integral_o = _std::     integral  <T>;
template <class      T >	concept  cardinal_o = _std::  is_unsigned_v<T>;
template <class      T >	concept   ordinal_o = _std::    is_signed_v<T>;
template <class      T >	concept   logical_o = _std:: convertible_to<T, bool>;

template <class      T >	concept  integral_q = _std::derived_from<T, _std::integral_constant<typename T::value_type, T::value>>;
template <class      T >	concept  cardinal_q = integral_q<T> and cardinal_o<typename T::value>;
template <class      T >	concept   ordinal_q = integral_q<T> and  ordinal_o<typename T::value>;
template <class      T >	concept   logical_q = integral_q<T> and  logical_o<typename T::value>;

template <class      T >	concept  integral_p = integral_o<T> or integral_q<T>;
template <class      T >	concept  cardinal_p = cardinal_o<T> or cardinal_q<T>;
template <class      T >	concept   ordinal_p =  ordinal_o<T> or  ordinal_q<T>;
template <class      T >	concept   logical_p =  logical_o<T> or  logical_q<T>;

template <class      T >	concept  terminal_q = integral_q<T> and 0 == T::value;
template <class      T >	concept   liminal_q = integral_q<T> and 0 != T::value;
template <liminal_q  T >	using  subliminal   = integral<(T{} - sign_n<T{}>)>;
template <liminal_q  T >	using semiliminal   = integral<(T{} >> 1)>;


template <class      T >	using       based_t = _std::remove_cvref_t<complete_t<T>>;
template <class      T >	concept     based_q = _std::is_trivially_copyable_v<T>;
template <class      T >	concept   unbased_q =  not based_q<T>;

template <class      T >	struct    debased             : logical<0> {using type = _std::remove_reference_t<T>;};
template <unbased_q  T >	struct    debased<T       & > : logical<1> {using type =       T*;};
template <unbased_q  T >	struct    debased<T const & > : logical<1> {using type = const T*;};
template <class      T >	concept   debased_q = (bool) debased<T>::value;

template <class      T >	struct    rebased             : logical<1> {using type = _std::remove_reference_t<T>;};
template <unbased_q  T >	struct    rebased<T       & > : logical<0> {using type =       T&;};
template <unbased_q  T >	struct    rebased<T const & > : logical<0> {using type = const T&;};
template <class      T >	concept   rebased_q = (bool) rebased<T>::value;


template <class      T >	concept    valued_q = requires {typename based_t<T>::value_type;};
template <class      T >	using      valued_t =           typename based_t<T>::value_type;
template <class      T >	using    devalued_t =  _std::remove_all_extents_t<based_t<T>>;

template <class      T >	struct   revalued     {using value_type = devalued_t<T>;};
template <valued_q   T >	struct   revalued<T>: based_t<T> {};
template <class      T >	using    revalued_t = typename revalued<T>::value_type;

template <class      X >	struct   argument     {using type = X &&;};
template <based_q    X >	struct   argument<X>  {using type = X const &;};


////////////////////////////////////////////////////////////////////////////////

template <           class ...Ts>	struct   identical;// `is_same`
template <           class ...Ts>	struct   isotropic;// `is_same` modulo qualifiers
template <           class ...Ts>	struct   epitropic;// `is_constructible`

template <class  T , class ...Ts>	struct   identical<T, Ts...>: _std::conjunction<_std::is_same<Ts, T>...> {};
template <class  T , class ...Ts>	struct   isotropic<T, Ts...>: _std::conjunction<_std::is_same<based_t<Ts>, based_t<T>>...> {};
template <class  T , class ...Ts>	struct   epitropic<T, Ts...>: _std::conjunction<_std::is_constructible<Ts, T>...> {};

template <           class ...Ts>	using    shared   = _std::common_type  <Ts...>;
template <           class ...Ts>	using    shared_t = _std::common_type_t<Ts...>;
template <           class ...Ts>	concept  shared_q = requires {typename shared_t<Ts...>;};
template <           class ...Ts>	concept  id_q     = identical<Ts...>::value;
template <           class ...Ts>	concept  is_q     = isotropic<Ts...>::value;
template <           class ...Ts>	concept  to_q     = epitropic<Ts...>::value;

template <class  T , class    Y >	concept  of_p = _std::derived_from<based_t<Y>, based_t<T>>;
template <class  T , class    Y >	concept  of_q = _std::derived_from<based_t<T>, based_t<Y>>;

template <class  T , class    Y >	concept    forcible_q = sizeof(T) == sizeof(Y);
template <class  T , class    Y >	concept    fungible_q = of_p<T, Y> or of_q<T, Y>;
template <class  T , class    Y >	concept  unforcible_q = not forcible_q<T, Y>;
template <class  T , class    Y >	concept  infungible_q = not fungible_q<T, Y>;


////////////////////////////////////////////////////////////////////////////////

template <class T>
struct aligned
{
	class type {alignas(alignof(T)) byte_t data[sizeof(T)];};
	XTAL_LET value = sizeof(type);
};

template <class      T >	using    pointed_t =          XTAL_TYP_(*XTAL_VAL_(T));
template <class      T >	using    pointer_t =          XTAL_TYP_(&XTAL_VAL_(T));
template <class      T >	concept  pointed_q = requires {&XTAL_VAL_(T);};
template <class      T >	concept  pointer_q = requires {*XTAL_VAL_(T);};

template <class      T >	XTAL_LET  parity_n = sizeof(T)%aligned<revalued_t<T>>::value;
template <class      T >	XTAL_LET   arity_n = sizeof(T)/aligned<revalued_t<T>>::value;
template <class      T >	using      array_t = _std::array<revalued_t<T>,  arity_n<T>>;
template <class      T >	concept    arity_q = valued_q<T> and 0 ==  parity_n<T>;
template <class      T >	concept    array_q =  arity_q<T> and of_p< array_t<T>, T> or _std::is_array_v<T>;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//\
Ranged...

template <class      T >	using       begin_t = decltype( XTAL_VAL_(T).begin());
template <class      T >	using         end_t = decltype( XTAL_VAL_(T).  end());
template <class      T >	concept     begin_q = requires (T t) {*t.begin();};
template <class      T >	concept       end_q = requires (T t) {*t.  end();};

template <class      W >	using    bracket_t  = _std::initializer_list<W>;
template <class      T >	concept  bracket_q  = begin_q<T> and end_q<T>;

template <class      W >	using    interval_t = _v3::ranges::iota_view<W, W>;
template <class      T >	using     iterate_t = _v3::ranges::view_interface<T>;


template <class      T >	concept  iterable_q = begin_q<T> and not requires (T t) {t.front();};
template <class      T >	concept  iterated_q = begin_q<T> and     requires (T t) {t.front();};//_v3::ranges::forward_range
template <class      T >	concept  iterator_q = requires (T t) {*++t;};//_v3::ranges::forward_iterator


template <class      T >	struct   iterated;
template <class      T >	struct   iterator;
template <class      T >	struct   iteratee;

template <class      T >	using    iterated_t = typename iterated<T>::type;
template <class      T >	using    iterator_t = typename iterator<T>::type;//_v3::ranges::iterator_t
template <class      T >	using    iteratee_t = typename iteratee<T>::type;//_v3::ranges::range_reference_t, _v3::ranges::iter_reference_t

template <iterated_q T >	struct   iterated<T>: logical<1> {using type =               based_t<T> ;};
template <iterator_q T >	struct   iterated<T>: logical<0> {using type =                     void ;};
template <integral_p T >	struct   iterated<T>: logical<0> {using type =            interval_t<T> ;};

template <iterable_q T >	struct   iterator<T>: logical<0> {using type =               begin_t<T> ;};
template <iterated_q T >	struct   iterator<T>: logical<0> {using type =               begin_t<T> ;};
template <iterator_q T >	struct   iterator<T>: logical<1> {using type =               based_t<T> ;};
template <integral_p T >	struct   iterator<T>: logical<0> {using type = iterator_t<interval_t<T>>;};

template <iterable_q T >	struct   iteratee<T>: logical<0> {using type =     pointed_t<begin_t<T>>;};
template <iterated_q T >	struct   iteratee<T>: logical<0> {using type =     pointed_t<begin_t<T>>;};
template <iterator_q T >	struct   iteratee<T>: logical<0> {using type =             pointed_t<T> ;};
template <integral_p T >	struct   iteratee<T>: logical<1> {using type =               based_t<T> ;};

template <class      T >	using    sentinel_t = based_t<_v3::ranges::sentinel_t<T>>;
template <class      T >	using    distance_t = XTAL_TYP_(_std::distance(XTAL_VAL_(iterator_t<T>), XTAL_VAL_(iterator_t<T>)));
template <class      T >	using    deranged_t = _v3::ranges::subrange<iterator_t<T>, sentinel_t<T>>;


template <class      T >	concept  counted_q  = iterated_q<T> and to_q<T, interval_t<iteratee_t<T>>>;
template <class      T >	concept  counter_q  = integral_p<T>;

template <class      T >	struct   counted;
template <class      T >	struct   counter;

template <counted_q  T >	struct   counted<T> : logical<1> {using type =    based_t<T>;};
template <counter_q  T >	struct   counted<T> : logical<0> {using type = iterated_t<T>;};

template <counted_q  T >	struct   counter<T> : logical<0> {using type = iteratee_t<T>;};
template <counter_q  T >	struct   counter<T> : logical<1> {using type =    based_t<T>;};


////////////////////////////////////////////////////////////////////////////////

template <class      ...Ts>	struct   isomorphic       : isotropic<Ts...> {};
template <iterated_q ...Ts>	struct   isomorphic<Ts...>: isomorphic<iteratee_t<Ts>...> {};
template <iterator_q ...Ts>	struct   isomorphic<Ts...>: isomorphic<iteratee_t<Ts>...> {};

template <class      ...Ts>	struct   epimorphic       : epitropic<Ts...> {};
template <iterated_q ...Ts>	struct   epimorphic<Ts...>: epimorphic<iteratee_t<Ts>...> {};
template <iterator_q ...Ts>	struct   epimorphic<Ts...>: epimorphic<iteratee_t<Ts>...> {};


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//\
Arithmetic...

template <class T, size_t N_arity=2>
concept equality_p = requires (T t, T u)
{
	requires N_arity == 2;
	{t == u} -> is_q<bool>;
	{t != u} -> is_q<bool>;
};
template <class T, size_t N_arity=2>
concept inequality_p = equality_p<T> and requires (T t, T u)
{
	requires N_arity == 2;
	{t <= u} -> is_q<bool>;
	{t <  u} -> is_q<bool>;
	{t >= u} -> is_q<bool>;
	{t >  u} -> is_q<bool>;
};
template <class T, size_t N_arity=2>
concept quality_p = equality_p<T, N_arity> and inequality_p<T, N_arity>;


template <class T, size_t N_arity=0>
concept boolean_logic_p = requires (T t, T u)
{
	requires N_arity == 2 or requires
	{
		{!u} -> is_q<T>;
	};
	requires N_arity == 1 or requires
	{
		{t || u} -> is_q<T>;
		{t && u} -> is_q<T>;
	};
};
template <class T, size_t N_arity=0>
concept binary_logic_p = requires (T t, T u)
{
	requires N_arity == 2 or requires
	{
		{   ~  u} -> is_q<T>;
		{t  ^= u} -> is_q<T>;
		{t  |= u} -> is_q<T>;
		{t  &= u} -> is_q<T>;
	};
	requires N_arity == 1 or requires
	{
		{t  ^  u} -> is_q<T>;
		{t  |  u} -> is_q<T>;
		{t  &  u} -> is_q<T>;
	};
};


template <class T, size_t N_arity=0>
concept multiplicative_group_p = requires (T t, T u)
{
	requires N_arity == 2 or requires
	{
		{t  *= u} -> is_q<T>;
		{t  /= u} -> is_q<T>;
	};
	requires N_arity == 1 or requires
	{
		{t  *  u} -> is_q<T>;
		{t  /  u} -> is_q<T>;
	};
};
template <class T, size_t N_arity=0>
concept additive_group_p = requires (T t, T u)
{
	requires N_arity == 2 or requires
	{
		{t  += u} -> is_q<T>;
		{t  -= u} -> is_q<T>;
	};
	requires N_arity == 1 or requires
	{
		{t  +  u} -> is_q<T>;
		{t  -  u} -> is_q<T>;
		{   -  u} -> is_q<T>;
	};
};
template <class T, size_t N_arity=0>
concept discrete_group_p = requires (T t, T u)
{
	requires N_arity == 2 or requires
	{
		{t  ++  } -> is_q<T>;
		{   ++ u} -> is_q<T>;
		{t  --  } -> is_q<T>;
		{   -- u} -> is_q<T>;
	};
};
template <class T, size_t N_arity=0>
concept quotient_group_p = requires (T t, T u)
{
	requires N_arity == 2 or requires
	{
		{t  %= u} -> is_q<T>;
	};
	requires N_arity == 1 or requires
	{
		{t  %  u} -> is_q<T>;
	};
};
template <class T, size_t N_arity=0>
concept integral_group_p = _std::integral<T> or discrete_group_p<T, N_arity> and quotient_group_p<T, N_arity>;


template <class T, size_t N_arity=0>
concept algebraic_field_p = multiplicative_group_p<T, N_arity> and additive_group_p<T, N_arity>;

template <class T, size_t N_arity=0>
concept real_field_p = _std::floating_point<T> or
requires (T t)
{
	requires quality_p<T> and algebraic_field_p<T, N_arity>;
	{_std::abs(t)} -> is_q<T>;
};

template <class T, size_t N_arity=2>
concept complex_field_p = of_q<T, _std::complex<revalued_t<T>>> or requires (T t)
{
	requires N_arity == 2;
	requires equality_p<T> and algebraic_field_p<T, 2>;
	{_std::abs(t)} -> is_q<valued_t<T>>;
	{t.real()}     -> is_q<valued_t<T>>;
	{t.imag()}     -> is_q<valued_t<T>>;
};


}//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
