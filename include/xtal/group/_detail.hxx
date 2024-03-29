








namespace _detail
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

using namespace _retail::_detail;


////////////////////////////////////////////////////////////////////////////////

template <iterator_q I, iterator_q J, _std::invocable<iteratee_t<J>> F>
XTAL_FN0 copy_to(I i, J const j0, J const jN, F &&f, bool o=false)
XTAL_0EX
{
	using namespace _std;
#ifdef __cpp_lib_execution
	auto constexpr seq = execution::  seq;
	auto constexpr par = execution::unseq;
	if (o) transform(seq, j0, jN, i, XTAL_FWD_(f));
	else   transform(par, j0, jN, i, XTAL_FWD_(f));
#else
	transform(j0, jN, i, XTAL_FWD_(f));
#endif
}
template <iterator_q I, bracket_q J, _std::invocable<iteratee_t<J>> F>
XTAL_FN0 copy_to(I i, J const &j, F &&f, bool o=false)
XTAL_0EX
{
	copy_to(i, j.begin(), j.end(), XTAL_FWD_(f), o);
}
template <iterator_q I, iterator_q J>
XTAL_FN0 copy_to(I i, J const j0, J const jN, bool o=false)
XTAL_0EX
{
	copy_to(i, j0, jN, as_f<based_t<iteratee_t<I>>>, o);
}
template <iterator_q I, iterator_q J>
XTAL_FN0 copy_to(I i, J const j0, J const jN, bool o=false)
XTAL_0EX
XTAL_REQ isomorphic_q<I, J>
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
XTAL_FN0 copy_to(I i, J const &j, bool o=false)
XTAL_0EX
{
	copy_to(i, j.begin(), j.end(), o);
}


template <iterator_q I, iterator_q J, _std::invocable<iteratee_t<J>> F>
XTAL_FN0 move_to(I i, J const j0, J const jN, F &&f, bool o=false)
XTAL_0EX
{
	auto const _j0 = mover_f(j0);
	auto const _jN = mover_f(jN);
	return copy_to(i, _j0, _jN, XTAL_FWD_(f), o);
}
template <iterator_q I, bracket_q J, _std::invocable<iteratee_t<J>> F>
XTAL_FN0 move_to(I i, J const &j, F &&f, bool o=false)
XTAL_0EX
{
	move_to(i, j.begin(), j.end(), XTAL_FWD_(f), o);
}
template <iterator_q I, iterator_q J>
XTAL_FN0 move_to(I i, J j0, J jN, bool o=false)
XTAL_0EX
{
	auto const _j0 = mover_f(j0);
	auto const _jN = mover_f(jN);
	return copy_to(i, _j0, _jN, o);
}
template <iterator_q I, bracket_q J> requires (not is_q<I, begin_t<J>>)
XTAL_FN0 move_to(I i, J &&j, bool o=false)
XTAL_0EX
{
	_std::is_lvalue_reference_v<J>?
		copy_to(i, j.begin(), j.end(), o):
		move_to(i, j.begin(), j.end(), o);
}
template <iterator_q I, bracket_q J> requires is_q<I, begin_t<J>>
XTAL_FN0 move_to(I i0, J &&j)
XTAL_0EX
{
	_std::is_lvalue_reference_v<J>?
		_std::memcpy (i0, XTAL_FWD_(j).begin(), sizeof(j)):
		_std::memmove(i0, XTAL_FWD_(j).begin(), sizeof(j));
}


template <bracket_q J, _std::invocable<iteratee_t<J>> F>
XTAL_FN0 apply_to(J &&j, F &&f, bool o=false)
XTAL_0EX
{
	move_to(j.begin(), j, XTAL_FWD_(f), o);
}


}//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
