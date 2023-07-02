#pragma once
#include "./any.hpp"






XTAL_ENV_(push)
namespace xtal::common
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

namespace _detail
{///////////////////////////////////////////////////////////////////////////////

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


template <typename V, size_t N>
struct array: _std::array<V, N> {using _std::array<V, N>::array;};

template <typename T>
concept array_q = value_q<T> and _std::derived_from<based_t<T>, array<value_t<T>, sizeof(T)/sizeof(value_t<T>)>>;


}///////////////////////////////////////////////////////////////////////////////
///\
A decorator that defines the base-types for block-based data storage, \
namely `solid` (sharing the same interface as `std::array`), \
and `fluid` (sharing the same interface as `std::vector`). \
These types are made available to any class with which it is `compose`d, \
and can be further transformed using `collate` to provide differentiated types. \

template <int N_size=-1>
struct collect
{
	template <typename S>
	class subtype: public S
	{
	public:
		using S::S;

		using volume = constant_t<N_size>;///< The capacity of `solid` and `fluid`.
		
		template <typename V> struct solid;///< cf. `std::array`.
		template <typename V> struct fluid;///< cf. `std::vector`.
		///\note\
		If `0 < N_size`, both `solid` and `fluid` are defined and limited by the capacity specified by `N_size`. \
		Otherwise, only `fluid` is defined as `std::vector`. \


		template <typename V> requires (0 <= N_size)
		struct solid<V>
		{
			using type = _detail::array<V, N_size>;

		};
		template <typename V>
		struct fluid
		{
			using type = _std::vector<V>;

		};
		/**/
		template <typename V> requires (0 <= N_size)
		struct fluid<V>
		{
			class type: public iterate_t<type>
			{
				using R_ = iterate_t<type>;
				using A  = aligned_t<V>;

				XTAL_CN2 _ptr_f(      V *i) XTAL_0EX {return appointer_f<      A *>(i);}
				XTAL_CN2 _ptr_f(const V *i) XTAL_0EX {return appointer_f<const A *>(i);}
				XTAL_CN2 _ptr_f(      A *i) XTAL_0EX {return appointer_f<      V *>(i);}
				XTAL_CN2 _ptr_f(const A *i) XTAL_0EX {return appointer_f<const V *>(i);}
				
				XTAL_CN2 _antiptr_f(XTAL_DEF i) XTAL_0EX {return _std::make_reverse_iterator(_ptr_f(XTAL_REF_(i)));}
				
				A  block_m[N_size];
				A* limit_m = block_m;

			public:
			//	using R_;
				using R_::size;

				using             value_type = V;
				using         allocator_type = type;

				using              size_type = _std::size_t;
				using        difference_type = _std::ptrdiff_t;

				using              reference =       value_type &;
				using        const_reference = const value_type &;
				
				using                pointer =       value_type *;
				using          const_pointer = const value_type *;

				using               iterator =       value_type *;
				using         const_iterator = const value_type *;
				
				using       reverse_iterator = _std::reverse_iterator<      iterator>;
				using const_reverse_iterator = _std::reverse_iterator<const_iterator>;
				

				XTAL_DO4_(XTAL_OP2[] (size_type i), *_ptr_f(block_m + i));
				XTAL_DO4_(XTAL_OP2()(size_type i),  _ptr_f(block_m + i));

				XTAL_DO4_(XTAL_FN2 rbegin(), _antiptr_f(limit_m));
				XTAL_DO4_(XTAL_FN2  begin(),     _ptr_f(block_m));
				XTAL_DO4_(XTAL_FN2   rend(), _antiptr_f(block_m));
				XTAL_DO4_(XTAL_FN2    end(),     _ptr_f(limit_m));

				XTAL_FN2 crbegin() XTAL_0FX {return rbegin();}
				XTAL_FN2  cbegin() XTAL_0FX {return  begin();}
				XTAL_FN2   crend() XTAL_0FX {return   rend();}
				XTAL_FN2    cend() XTAL_0FX {return    end();}

				XTAL_DO4_(XTAL_FN2 data(), begin());

				///\
				Clear destructor. \

				~type()
				{
					clear();
				}
				///\
				Default constructor. \

				type() noexcept = default;

				///\
				Insert constructor. \
				Initializes `this` with `sN` values determined by the given arguments. \

				XTAL_CXN type(size_type sN, XTAL_DEF ...ws)
				{
					insert_back(sN, XTAL_REF_(ws)...);
				}

				///\
				Span constructor. \
				Initializes `this` with the values between `i0` and `iN`. \

				template <allomorphic_q<iterator> I0, allomorphic_q<iterator> IN>
				XTAL_CXN type(I0 i0, IN iN)
				{
					using I = _std::common_type_t<I0, IN>;
					I i0_ = i0;
					I iN_ = iN;
					insert_back(i0_, iN_);
				}

				///\
				List constructor. \
				Initializes `this` with the given values. \

				XTAL_CON type(bracket_t<V> w)
				:	type(w.begin(), w.end())
				{
				}
				///\
				List assignment. \
				Replaces the contents of `this` with the given values. \

				XTAL_OP1 = (bracket_t<V> w)
				{
					refill(w.begin(), w.end());
					return *this;
				}

				///\
				Copy constructor. \
				Initializes `this` with the given data. \

				XTAL_CON type(type const &t)
				:	type(t.begin(), t.end())
				{
				}
				///\
				Copy assigment. \
				Replaces the contents of `this` with the given data. \

				XTAL_OP1 = (type const &t)
				{
					refill(t.begin(), t.end());
					return *this;
				}

				///\
				Move constructor. \
				Initializes `this` with the given data. \

				XTAL_CON type(type &&t)
				:	type(_std::make_move_iterator(t.begin()), _std::make_move_iterator(t.end()))
				{
				}
				///\
				Move assigment. \
				Replaces the contents of `this` with the given data. \

				XTAL_OP1 = (type &&t)
				{
					refill(_std::make_move_iterator(t.begin()), _std::make_move_iterator(t.end()));
					return *this;
				}

				///\
				Swaps the contents of `this` with the given data. \

				XTAL_FN0 swap(type &t)
				requires _std::swappable<value_type>
				{
					_std::swap_ranges(begin(), end(), t.begin());
				}

				///\
				\returns the constant `N_size`. \

				XTAL_FN2_(size_type) capacity()
				XTAL_0EX
				{
					return N_size;
				}

				///\
				Allocates and initializes `sN` elements at the end of the fluid. \

				XTAL_FN2_(iterator) allocate(size_type sN)
				{
					return insert_back(sN);
				}

				///\
				Deletes the elements from `i0` to `end()`. \

				template <is_q<iterator> I0>
				XTAL_FN0 deallocate(I0 i0)
				XTAL_0EX
				{
					erase(i0, end());
				}

				///\
				Deletes all elements. \

				XTAL_FN0 clear()
				XTAL_0EX
				{
					erase(begin(), end());
				}

				///\
				Deletes the element at `i0`. \

				template <is_q<iterator> I0>
				XTAL_FN0 erase(I0 i0)
				XTAL_0EX
				{
					erase(i0, size_type(1));
				}
				///\
				Deletes `sN` elements starting from `i0`. \

				template <is_q<iterator> I0>
				XTAL_FN0 erase(I0 i0, size_type sN)
				XTAL_0EX
				{
					erase(i0, _std::next(i0, sN), sN);
				}
				///\
				Deletes the elements between `i0` and `iN`. \

				template <is_q<iterator> I0, is_q<iterator> IN>
				XTAL_FN0 erase(I0 i0, IN iN)
				XTAL_0EX
				{
					using I = _std::common_type_t<I0, IN>;
					I i0_ = i0;
					I iN_ = iN;
					erase(i0_, iN_, _std::distance(i0_, iN_));
				}
				///\
				Deletes `sN` elements between `i0` and `iN`. \

				template <is_q<iterator> I0, is_q<iterator> IN>
				XTAL_FN0 erase(I0 i0, IN iN, size_type sN)
				XTAL_0EX
				{
					using I = _std::common_type_t<I0, IN>;
					I i0_ = i0;
					I iN_ = iN;
					erode(i0_, iN_, sN);
				}

				///\
				Does nothing. \

				XTAL_FN0 shrink_to_fit()
				XTAL_0EX
				{
				}

				///\
				Does nothing besides `throw std::bad_alloc` if the required `sN` exceeds the maximum `N_size`. \

				XTAL_FN0 reserve(size_type sN)
				{
					if (N_size < sN) {
						throw _std::bad_alloc {};
					}
				}

				///\
				Resizes `this` to `sN` elements. \

				XTAL_FN0 resize(size_type sN, XTAL_DEF ...etc)
				{
					size_type const sM = size();
					if (sN < sM) {
						pop_back(sM - sN);
					}
					else {
						insert_back(sN - sM, XTAL_REF_(etc)...);
					}
				}

				///\
				Clears `this` and invokes `insert_back` with the given arguments. \

				XTAL_FN0 refill(XTAL_DEF ...etc)
				{
					clear();
					insert_back(XTAL_REF_(etc)...);
				}

				///\
				Removes the last element from `this`. \

				XTAL_FN0 pop_back()
				{
					pop_back(size_type(1));
				}
				///\
				Removes the last `sN` elements from `this`. \

				XTAL_FN0 pop_back(size_type sN)
				{
					deallocate(end() - sN);
				}

				///\
				Inserts the values `etc` beginning at `i0`. \

				XTAL_FN0 push_back(bracket_t<V> etc)
				{
					insert_back(etc.begin(), etc.end());
				}
				///\
				Inserts the values `etc...` beginning at `i0`. \

				XTAL_FN0 push_back(XTAL_DEF_(to_q<V>) ...etc)
				{
					push_back(bracket_t<V>{V(XTAL_REF_(etc))...});
				}

				///\
				Constructs an element at the end of `this` using the given arguments. \
				\returns a reference to the element.

				XTAL_FN1_(reference) emplace_back(XTAL_DEF ...etc)
				{
					return *inplace_back(XTAL_REF_(etc)...);
				}
				///\
				Constructs an element at the end of `this` using the given arguments. \
				\returns a pointer to the element.

				XTAL_FN1_(iterator) inplace_back(XTAL_DEF ...etc)
				{
					reserve(size_type(1) + size());
					return ::new (limit_m++) V(XTAL_REF_(etc)...);
				}

				///\
				Invokes `insert` at `this->end()` with the given arguments. \

				XTAL_FN1_(iterator) insert_back(XTAL_DEF ...etc)
				{
					return insert(end(), XTAL_REF_(etc)...);
				}

				///\
				Inserts the values delimited by `j0` and `jN` beginning at `i`. \

				template <is_q<iterator> I, allomorphic_q<iterator> J0, allomorphic_q<iterator> JN>
				XTAL_FN1_(iterator) insert(I i, J0 j0, JN jN)
				{
					using J = _std::common_type_t<J0, JN>;
					J j0_ = j0;
					J jN_ = jN;
					inject(i, _std::distance(j0_, jN_));
					_detail::copy_to(i, j0_, jN_);
					return i;
				}

				///\
				Inserts the values `w` beginning at `i`. \

				template <is_q<iterator> I>
				XTAL_FN1_(iterator) insert(I i, bracket_t<V> w)
				{
					return insert(i, w.begin(), w.end());
				}

				///\
				Initialises `sN` values with `v` beginning at `i`. \

				template <is_q<iterator> I>
				XTAL_FN1_(iterator) insert(I i, size_type sN, V const &v)
				{
					inject(i, sN);
					_std::uninitialized_fill_n(i, sN, v);
					return i;
				}
				template <is_q<iterator> I>
				XTAL_FN1_(iterator) insert(I i, size_type sN, V &&v)
				{
					inject(i, sN);
					_std::uninitialized_fill_n(i, sN, XTAL_MOV_(v));
					return i;
				}

				///\
				Initialises `sN` values beginning at `i`. \

				template <is_q<iterator> I>
				XTAL_FN1_(iterator) insert(I i, size_type sN)
				{
					inject(i, sN);
					_std::uninitialized_value_construct_n(i, sN);
					return i;
				}
				
			protected:
				///\
				Allocates `sN` elements beginning at `i`. \

				template <is_q<iterator> I>
				XTAL_FN1_(iterator) inject(I i, size_type sN)
				{
					reserve(sN + size());
					if (i < end() and _std::move_constructible<V>) {
						reverse_iterator iN = rbegin();
						_detail::move_to(_std::prev(iN, sN), iN, _std::next(iN, sN), true);
					}
					else {
						assert(i == end());
					}
					limit_m += sN;
					return i;
				}

				///\
				Deletes `sN` elements between `i0` and `iN`. \

				template <is_q<iterator> I0, is_q<iterator> IN>
				XTAL_FN0 erode(I0 i0, IN iN, size_type sN)
				XTAL_0EX
				{
					using I = _std::common_type_t<I0, IN>;
					I i0_ = i0;
					I iN_ = iN;
					I begin_m = begin(), end_m = end();
					
					assert(begin_m <= i0_ and iN_ <= end_m and _std::distance(i0_, iN_) == sN);
					
					if constexpr (_std::destructible<V>) {
						_std::destroy(i0_, iN_);
					}
					if (iN_ < end_m and _std::move_constructible<V>) {
						A* hN = _ptr_f(iN_);
						A* h0 = _ptr_f(i0_);
						_detail::move_to(h0, hN, limit_m, sN <= _std::distance(hN, limit_m));
					}
					else {
						assert(end_m == iN_);
					}
					limit_m -= sN;
				}

			};
		};
		/***/

	};
	using type = subtype<unit_t>;
};
template <int N_size=-1>
using collect_t = typename collect<N_size>::template subtype<unit_t>;

template <typename T>
concept collect_p = requires ()
{
	typename T::template solid<unit_t>;
	typename T::template fluid<unit_t>;
	requires iterated_q<typename T::template fluid<unit_t>::type>;

};
template <typename ...Ts>
concept collect_q = conjunct_q<collect_p<Ts>...>;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
/**/
namespace std
{///////////////////////////////////////////////////////////////////////////////

template <xtal::common::_detail::array_q T>
struct tuple_size<T>: xtal::constant_t<sizeof(T)/sizeof(xtal::value_t<T>)> {};

template <size_t N, xtal::common::_detail::array_q T>
struct tuple_element<N, T> {using type = xtal::value_t<T>;};


}/////////////////////////////////////////////////////////////////////////////
/***/
XTAL_ENV_(pop)
