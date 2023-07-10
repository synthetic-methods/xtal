#pragma once
#ifdef __INTELLISENSE__// stub...
#include "./any.hpp"
#endif





namespace _detail
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <iterator_q I, iterator_q J, _std::invocable<iteratee_t<J>> F>
XTAL_CN0 copy_to(I i, J const j0, J const jN, F &&f, bool const &o=false)
XTAL_0EX
{
	using namespace _std;
#ifdef __cpp_lib_execution
	auto constexpr seq = execution::  seq;
	auto constexpr par = execution::unseq;
	if (o) transform(seq, j0, jN, i, XTAL_REF_(f));
	else   transform(par, j0, jN, i, XTAL_REF_(f));
#else
	transform(j0, jN, i, XTAL_REF_(f));
#endif
}
template <iterator_q I, bracket_q J, _std::invocable<iteratee_t<J>> F>
XTAL_CN0 copy_to(I i, J const &j, F &&f, bool const &o=false)
XTAL_0EX
{
	copy_to(i, j.begin(), j.end(), XTAL_REF_(f), o);
}
template <iterator_q I, iterator_q J>
XTAL_CN0 copy_to(I i, J const j0, J const jN, bool const &o=false)
XTAL_0EX
{
	copy_to(i, j0, jN, to_f<iteratee_t<I>>, o);
}
template <iterator_q I, iterator_q J>
XTAL_CN0 copy_to(I i, J const j0, J const jN, bool const &o=false)
XTAL_0EX
XTAL_REQ isomorphic_p<I, J>
{
	using namespace _std;
#ifdef __cpp_lib_execution
	auto constexpr seq = execution::  seq;
	auto constexpr par = execution::unseq;
	if (o) copy(seq, j0, jN, i);
	else   copy(par, j0, jN, i);
#else
	copy(j0, jN, i);
#endif
}
template <iterator_q I, bracket_q J>
XTAL_CN0 copy_to(I i, J const &j, bool const &o=false)
XTAL_0EX
{
	copy_to(i, j.begin(), j.end(), o);
}


template <iterator_q I, iterator_q J, _std::invocable<iteratee_t<J>> F>
XTAL_CN0 move_to(I i, J const j0, J const jN, F &&f, bool const &o=false)
XTAL_0EX
{
	using namespace _std;
	auto const _j0 = make_move_iterator(j0);
	auto const _jN = make_move_iterator(jN);
	return copy_to(i, _j0, _jN, XTAL_REF_(f), o);
}
template <iterator_q I, bracket_q J, _std::invocable<iteratee_t<J>> F>
XTAL_CN0 move_to(I i, J const &j, F &&f, bool const &o=false)
XTAL_0EX
{
	move_to(i, j.begin(), j.end(), XTAL_REF_(f), o);
}
template <iterator_q I, iterator_q J>
XTAL_CN0 move_to(I i, J j0, J jN, bool const &o=false)
XTAL_0EX
{
	using namespace _std;
	auto const _j0 = make_move_iterator(j0);
	auto const _jN = make_move_iterator(jN);
	return copy_to(i, _j0, _jN, o);
}
template <iterator_q I, bracket_q J>
XTAL_CN0 move_to(I i, J const &j, bool const &o=false)
XTAL_0EX
{
	move_to(i, j.begin(), j.end(), o);
}


template <bracket_q J, _std::invocable<iteratee_t<J>> F>
XTAL_CN0 apply_to(J &j, F &&f, bool const &o=false)
XTAL_0EX
{
	move_to(j.begin(), j, XTAL_REF_(f), o);
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
