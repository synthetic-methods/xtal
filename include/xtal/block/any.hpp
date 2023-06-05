#pragma once
#include "../any.hpp"





#include "../common/all.hpp"

XTAL_ENV_(push)
namespace xtal::block
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

using namespace xtal::common;

namespace _detail
{///////////////////////////////////////////////////////////////////////////////

template <iterator_q I, iterator_q J>
XTAL_FZ0 copy_to(I i, J const j0, J const jN, bool const &ord=false)
XTAL_0EX
XTAL_IF1 iso_q<I, J>
{
	using namespace _std;
#ifdef __cpp_lib_execution
	auto constexpr seq = execution::  seq;
	auto constexpr par = execution::unseq;
	if (ord) copy(seq, j0, jN, i);
	else     copy(par, j0, jN, i);
#else
	copy(j0, jN, i);
#endif
}
template <iterator_q I, iterator_q J>
XTAL_FZ0 copy_to(I i, J const j0, J const jN, bool const &ord=false)
XTAL_0EX
{
	copy_to(i, j0, jN, to_f<iteratee_t<I>>, ord);
}
template <iterator_q I, iterator_q J, _std::invocable<iteratee_t<J>> F>
XTAL_FZ0 copy_to(I i, J const j0, J const jN, F &&f, bool const &ord=false)
XTAL_0EX
{
	using namespace _std;
#ifdef __cpp_lib_execution
	auto constexpr seq = execution::  seq;
	auto constexpr par = execution::unseq;
	if (ord) transform(seq, j0, jN, i, XTAL_FWD_(F) (f));
	else     transform(par, j0, jN, i, XTAL_FWD_(F) (f));
#else
	transform(j0, jN, i, XTAL_FWD_(F) (f));
#endif
}

template <iterator_q I, iterated_q J>
XTAL_FZ0 copy_to(I i, J const &j, bool const &ord=false)
XTAL_0EX
{
	copy_to(i, j.begin(), j.end(), ord);
}
template <iterator_q I, iterated_q J, _std::invocable<iteratee_t<J>> F>
XTAL_FZ0 copy_to(I i, J const &j, F &&f, bool const &ord=false)
XTAL_0EX
{
	copy_to(i, j.begin(), j.end(), XTAL_FWD_(F) (f), ord);
}


template <iterator_q I, iterator_q J>
XTAL_FZ0 move_to(I i, J j0, J jN, bool const &ord=false)
XTAL_0EX
{
	auto const _j0 = _std::make_move_iterator(j0);
	auto const _jN = _std::make_move_iterator(jN);
	return copy_to(i, _j0, _jN, ord);
}
template <iterator_q I, iterator_q J, _std::invocable<iteratee_t<J>> F>
XTAL_FZ0 move_to(I i, J const j0, J const jN, F &&f, bool const &ord=false)
XTAL_0EX
{
	auto const _j0 = _std::make_move_iterator(j0);
	auto const _jN = _std::make_move_iterator(jN);
	return copy_to(i, _j0, _jN, XTAL_FWD_(F) (f), ord);
}

template <iterator_q I, iterated_q J>
XTAL_FZ0 move_to(I i, J const &j, bool const &ord=false)
XTAL_0EX
{
	move_to(i, j.begin(), j.end(), ord);
}
template <iterator_q I, iterated_q J, _std::invocable<iteratee_t<J>> F>
XTAL_FZ0 move_to(I i, J const &j, F &&f, bool const &ord=false)
XTAL_0EX
{
	move_to(i, j.begin(), j.end(), XTAL_FWD_(F) (f), ord);
}

template <iterated_q J, _std::invocable<iteratee_t<J>> F>
XTAL_FZ0 apply_to(J &j, F &&f, bool const &ord=false)
XTAL_0EX
{
	move_to(j.begin(), j, XTAL_FWD_(F) (f), ord);
}

}///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
