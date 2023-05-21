#pragma once
#include "./any.hpp"
#include "./realize.hpp"





XTAL_ENV_(push)
namespace xtal
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <typename    T >        using     iterate_t     = _v3::ranges::view_interface<T>;

template <typename    T >        concept   iterable_b    = requires (T t) {t.begin();} and not requires (T t) {t.front();};
template <typename    T >        concept   iterated_b    = _v3::ranges::forward_range<based_t<T>>;
template <typename    T >        concept   iterator_b    =  pointer_b<T> or requires {typename _std::iterator_traits<T>::iterator_category;};//_v3::ranges::forward_iterator<based_t<T>>;
template <typename    T >        concept   iteratee_b    = iterated_b<T> or iterator_b<T>;

template <typename    T >        struct    iterated                     {using type = void;};
template <typename    T >        struct    iterator                     {using type = void;};
template <typename    T >        struct    iteratee                     {using type = void;};
template <iterated_b  T >        struct    iterated<T>   : cased<true>  {using type = based_t<T>;};
template <iterator_b  T >        struct    iterator<T>   : cased<true>  {using type = based_t<T>;};
template <iterated_b  T >        struct    iteratee<T>   : cased<true>  {using type = _v3::ranges::range_reference_t<T>;};
template <iterator_b  T >        struct    iteratee<T>   : cased<true>  {using type = _v3::ranges:: iter_reference_t<T>;};
template <iterated_b  T >        struct    iterator<T>   : cased<false> {using type = _v3::ranges::       iterator_t<T>;};


template <typename... Ts>        concept  uniterable_q   =   false_q<iterable_b<Ts>...>;
template <typename... Ts>        concept  uniterated_q   =   false_q<iterated_b<Ts>...>;
template <typename... Ts>        concept    iterable_q   = unfalse_q<iterable_b<Ts>...>;
template <typename... Ts>        concept    iterated_q   = unfalse_q<iterated_b<Ts>...>;
template <typename... Ts>        concept    iterator_q   = unfalse_q<iterator_b<Ts>...>;
template <typename... Ts>        concept    iteratee_q   = unfalse_q<iteratee_b<Ts>...>;
template <typename    T >        using      iterated_t   = typename iterated<T>::type;
template <typename    T >        using      iterator_t   = typename iterator<T>::type;
template <typename    T >        using      iteratee_t   = typename iteratee<T>::type;
template <typename    T >        using      sentinel_t   = _v3::ranges::sentinel_t<T>;

template <typename    V >        using      ioted_t      = _v3::ranges::iota_view<V, V>;
template <typename    V >        using      iotor_t      = iterator_t<ioted_t<V>>;
template <typename    T >        concept    ioted_b      = iterated_b<T> and as_q<T, ioted_t<iteratee_t<T>>>;
template <typename    T >        concept    iotor_b      = iterator_b<T> and as_q<T, iotor_t<iteratee_t<T>>>;

template <typename    T >        struct     counted                     {using type = void;};
template <typename    T >        struct     countor                     {using type = void;};
template <typename    T >        struct     countee                     {using type = void;};

template <ioted_b     T >        struct     counted<T>   : cased<true>  {using type =    based_t<T>;};
template <ioted_b     T >        struct     countee<T>   : cased<false> {using type = iteratee_t<T>;};

template <iotor_b     T >        struct     countor<T>   : cased<true>  {using type =    based_t<T>;};
template <iotor_b     T >        struct     countee<T>   : cased<false> {using type = iteratee_t<T>;};

template <iota_q      T >        struct     countee<T>   : cased<true>  {using type = based_t<T>;};
template <iota_q      T >        struct     counted<T>   : cased<false> {using type = ioted_t<T>;};
template <iota_q      T >        struct     countor<T>   : cased<false> {using type = iotor_t<T>;};

template <typename... Ts>        concept    counted_q    = unfalse_q<counted<Ts>::value...>;
template <typename... Ts>        concept    countor_q    = unfalse_q<countor<Ts>::value...>;
template <typename... Ts>        concept    countee_q    = iota_q<Ts...>;//unfalse_q<countee<Ts>::value...>;
template <typename    T=iota_t>  using      counted_t    = typename counted<T>::type;
template <typename    T=iota_t>  using      countor_t    = typename countor<T>::type;
template <typename    T=iota_t>  using      countee_t    = typename countee<T>::type;

template <typename    V >        using      repeated_t   = _v3::ranges::repeat_view<V>;
template <typename    T >        using      rendered_t   = _v3::ranges::subrange<iterator_t<T>, sentinel_t<T>>;

//\
TODO: Shim `std::views::repeat` by e.g. \
`std::views::iota(0)|std::views::transform([&] (auto&& _) {return value;})`? \

//\
TODO: Shim `std::views::generate` by e.g. \
`std::views::iota(0)|std::views::transform([&] (auto&& _) {return function();})`? \

////////////////////////////////////////////////////////////////////////////////

template <iteratee_q... Ys>
struct isomorphic<Ys...>
:	isomeric<iteratee_t<Ys>...>
{};

////////////////////////////////////////////////////////////////////////////////

template <iterator_q I, iterator_q J>
XTAL_FZ1_(void) copy_linear_f(bool const &order, I i, J const j0, J const jN)
{
	copy_linear_f(i, j0, jN, craft_f<iteratee_t<I>>);
}
template <iterator_q I, iterator_q J>
XTAL_FZ1_(void) copy_linear_f(bool const &order, I i, J const j0, J const jN)
XTAL_IF1 isomorphic_q<I, J>
{
#ifdef __cpp_lib_execution
	if (order) _std::copy(_std::execution::seq, j0, jN, i);
	else     _std::copy(_std::execution::unseq, j0, jN, i);
#else
	_std::copy(j0, jN, i);
#endif
}
template <iterator_q I, iterator_q J, _std::invocable<iteratee_t<J>> F>
XTAL_FZ1_(void) copy_linear_f(bool const &order, I i, J const j0, J const jN, F &&f)
{
#ifdef __cpp_lib_execution
	if (order) _std::transform(_std::execution::seq, j0, jN, i, XTAL_FWD_(F) (f));
	else     _std::transform(_std::execution::unseq, j0, jN, i, XTAL_FWD_(F) (f));
#else
	_std::transform(j0, jN, i, XTAL_FWD_(F) (f));
#endif
}

template <iterator_q I, iterated_q J>
XTAL_FZ1_(void) copy_linear_f(bool const &order, I i, J const &j)
{
	copy_linear_f(order, i, j.begin(), j.end());
}
template <iterator_q I, iterated_q J, _std::invocable<iteratee_t<J>> F>
XTAL_FZ1_(void) copy_linear_f(bool const &order, I i, J const &j, F &&f)
{
	copy_linear_f(order, i, j.begin(), j.end(), XTAL_FWD_(F) (f));
}


template <iterator_q I, iterator_q J>
XTAL_FZ1_(void) move_linear_f(bool const &order, I i, J j0, J jN)
{
	auto const _j0 = _std::make_move_iterator(j0);
	auto const _jN = _std::make_move_iterator(jN);
	return copy_linear_f(order, i, _j0, _jN);
}
template <iterator_q I, iterator_q J, _std::invocable<iteratee_t<J>> F>
XTAL_FZ1_(void) move_linear_f(bool const &order, I i, J const j0, J const jN, F &&f)
{
	auto const _j0 = _std::make_move_iterator(j0);
	auto const _jN = _std::make_move_iterator(jN);
	return copy_linear_f(order, i, _j0, _jN, XTAL_FWD_(F) (f));
}

template <iterator_q I, iterated_q J>
XTAL_FZ1_(void) move_linear_f(bool const &order, I i, J const &j)
{
	move_linear_f(order, i, j.begin(), j.end());
}
template <iterator_q I, iterated_q J, _std::invocable<iteratee_t<J>> F>
XTAL_FZ1_(void) move_linear_f(bool const &order, I i, J const &j, F &&f)
{
	move_linear_f(order, i, j.begin(), j.end(), XTAL_FWD_(F) (f));
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
