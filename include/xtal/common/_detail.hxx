#include "./_.hxx"

namespace _detail
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

struct unikind
{
	template <typename S>
	class subtype: public S
	{
	public:
		using S::S;

		template <typename Y, typename X, constant_q O> struct super          {using type = Y;};
		template <            typename X, constant_q O> struct super<O, X, O> {using type = X;};

	};
	using type = subtype<unit_t>;
	
};
using unitype = typename unikind::type;

template <typename T>
struct epikind
{
	template <typename S>
	class subtype: public S
	{
		friend T;
		
	public:
		using S::S;

		XTAL_CXN subtype(XTAL_DEF ...oo)
		XTAL_0EX
		:	S(XTAL_REF_(oo)...)
		{}

		///\returns `*this` with type `Y=T`. \

		template <typename Y=T> XTAL_FN2 self() XTAL_0FX_(&&) {return funge_f<Y const &&>(XTAL_MOV_(*this));}
		template <typename Y=T> XTAL_FN2 self() XTAL_0EX_(&&) {return funge_f<Y       &&>(XTAL_MOV_(*this));}
		template <typename Y=T> XTAL_FN2 self() XTAL_0FX_(&)  {return funge_f<Y const  &>(*this);}
		template <typename Y=T> XTAL_FN2 self() XTAL_0EX_(&)  {return funge_f<Y        &>(*this);}

		///\returns a copy of `*this` with type `Y=T`. \

		XTAL_TO2_(template <typename Y=T> XTAL_FN2_(based_t<Y>) twin(), self<Y>())

		///\returns `this` as the `define`d supertype. \

		XTAL_TO4_(XTAL_FN2 core(), S::self())

	};
	using type = subtype<unit_t>;

};
template <typename T>
using epitype = typename epikind<T>::type;

template <template <typename> typename T_>
class isotype: public T_<isotype<T_>>
{
	using S_ = T_<isotype<T_>>;// -Wsubobject-linkage?
	
public:
	using S_::S_;

};


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
	auto const _j0 = mover_f(j0);
	auto const _jN = mover_f(jN);
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
	auto const _j0 = mover_f(j0);
	auto const _jN = mover_f(jN);
	return copy_to(i, _j0, _jN, o);
}
template <iterator_q I, bracket_q J> requires (not is_q<I, begin_t<J>>)
XTAL_CN0 move_to(I i, J &&j, bool const &o=false)
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
XTAL_CN0 apply_to(J &j, F &&f, bool const &o=false)
XTAL_0EX
{
	move_to(j.begin(), j, XTAL_REF_(f), o);
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
