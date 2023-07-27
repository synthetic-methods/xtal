#include "../_.hxx"

namespace _detail
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <template <typename> typename _T>
class isotype: public _T<isotype<_T>>
{
	using S = _T<isotype<_T>>;// -Wsubobject-linkage?
	
public:
	using S::S;

};


////////////////////////////////////////////////////////////////////////////////

template <class T             >   using identity_t = typename T::identity::type;
template <class T, class... Ys> concept identity_p = of_p<identity_t<T>, identity_t<Ys>...>;
template <class T, class... Ys> concept identity_q = of_q<identity_t<T>, identity_t<Ys>...>;

template <class T> concept   identified_p =     requires {typename identity_t<T>;};
template <class T> concept unidentified_p = not requires {typename identity_t<T>;};

template <typename ...As>
struct identify;

template <>
struct identify<>//tag<identify>
{	
	template <class S>
	class subtype: public S
	{
	public:
		using S::S; struct identity {class type {};};

	};
};
template <typename A>
struct identify<A>
{	
	template <class I> struct indent {class type: public I::type {};};

	template <class S>
	class subtype: public S
	{
	public:
		using S::S; using identity = indent<typename S::identity>;
		
	};
};


////////////////////////////////////////////////////////////////////////////////

template <iterator_q I, iterator_q J, _std::invocable<iteratee_t<J>> F>
XTAL_CN0 copy_to(I i, J const j0, J const jN, F &&f, bool o=false)
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
XTAL_CN0 copy_to(I i, J const &j, F &&f, bool o=false)
XTAL_0EX
{
	copy_to(i, j.begin(), j.end(), XTAL_REF_(f), o);
}
template <iterator_q I, iterator_q J>
XTAL_CN0 copy_to(I i, J const j0, J const jN, bool o=false)
XTAL_0EX
{
	copy_to(i, j0, jN, to_f<iteratee_t<I>>, o);
}
template <iterator_q I, iterator_q J>
XTAL_CN0 copy_to(I i, J const j0, J const jN, bool o=false)
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
XTAL_CN0 copy_to(I i, J const &j, bool o=false)
XTAL_0EX
{
	copy_to(i, j.begin(), j.end(), o);
}


template <iterator_q I, iterator_q J, _std::invocable<iteratee_t<J>> F>
XTAL_CN0 move_to(I i, J const j0, J const jN, F &&f, bool o=false)
XTAL_0EX
{
	auto const _j0 = mover_f(j0);
	auto const _jN = mover_f(jN);
	return copy_to(i, _j0, _jN, XTAL_REF_(f), o);
}
template <iterator_q I, bracket_q J, _std::invocable<iteratee_t<J>> F>
XTAL_CN0 move_to(I i, J const &j, F &&f, bool o=false)
XTAL_0EX
{
	move_to(i, j.begin(), j.end(), XTAL_REF_(f), o);
}
template <iterator_q I, iterator_q J>
XTAL_CN0 move_to(I i, J j0, J jN, bool o=false)
XTAL_0EX
{
	auto const _j0 = mover_f(j0);
	auto const _jN = mover_f(jN);
	return copy_to(i, _j0, _jN, o);
}
template <iterator_q I, bracket_q J> requires (not is_q<I, begin_t<J>>)
XTAL_CN0 move_to(I i, J &&j, bool o=false)
XTAL_0EX
{
	_std::is_lvalue_reference_v<J>?
		copy_to(i, j.begin(), j.end(), o):
		move_to(i, j.begin(), j.end(), o);
}
template <iterator_q I, bracket_q J> requires is_q<I, begin_t<J>>
XTAL_CN0 move_to(I i, J &&j)
XTAL_0EX
{
	_std::is_lvalue_reference_v<J>?
		_std::memcpy (i, XTAL_REF_(j).begin(), sizeof(j)):
		_std::memmove(i, XTAL_REF_(j).begin(), sizeof(j));
}


template <bracket_q J, _std::invocable<iteratee_t<J>> F>
XTAL_CN0 apply_to(J &j, F &&f, bool o=false)
XTAL_0EX
{
	move_to(j.begin(), j, XTAL_REF_(f), o);
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
