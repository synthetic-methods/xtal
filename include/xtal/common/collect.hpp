#pragma once
#include "./any.hpp"

#include "./tag.hpp"
#include "./compose.hpp"



XTAL_ENV_(push)
namespace xtal::common
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <class T>
concept collected_p = requires ()
{
	typename T::collected;
	requires constant_q<typename T::collected>;
	requires (0 != T::collected::value);
	
	typename T::template fluid<unit_t>;
	requires iterated_q<typename T::template fluid<unit_t>::type>;

};
template <class ...Ts>
concept collected_q = (...and collected_p<Ts>);

///\
A decorator that provides different kinds of block-based data storage, \
namely `solid` (sharing the same interface as `std::array`), \
and `fluid` (sharing the same interface as `std::vector`). \
These types are made available to any class with which it is `compose`d, \
and can be further transformed using `collate` to provide differentiated types. \

template <int ...Ns>
struct collect;

template <int ...Ns>
using collect_t = typename collect<Ns...>::type;

template <int N_size>
struct collect<N_size>
{
	template <class S>
	class subtype: public S
	{
	public:
		using S::S;
		using collected = constant_t<N_size>;
		
		///\note\
		If `0 < N_size`, both `solid` and `fluid` are defined and limited by the capacity specified by `N_size`. \
		Otherwise, only `fluid` is defined as `std::vector`. \
		

		///\see `std::array`.
		template <class V>
		struct solid;

		template <class V> requires (0 <= N_size)
		struct solid<V>
		{
			using type = compose_s<_std::array<V, N_size>, tag<>>;

		};
		
		///\see `std::vector`.
		template <class V>
		struct fluid
		{
			using type = compose_s<_std::vector<V>, tag<>>;

		};
		template <class V> requires (0 <= N_size)
		struct fluid<V>
		{
			class type: public iterate_t<type>
			{
				using R_ = iterate_t<type>;
				using A  = aligned_t<V>;

			public:// DEFINITION
				using             value_type = V;
				using         allocator_type = type;// TODO: Define!

				using              size_type = size_t;
				using        difference_type = size_x;

				using              reference =       value_type &;
				using        const_reference = const value_type &;
				
				using                pointer =       value_type *;
				using          const_pointer = const value_type *;

				using               iterator =       value_type *;
				using         const_iterator = const value_type *;
				
				using       reverse_iterator = _std::reverse_iterator<      iterator>;
				using const_reverse_iterator = _std::reverse_iterator<const_iterator>;
			
			private:
				A block_m[N_size]; difference_type limit_m = 0;


			public:// ACCESS
				XTAL_TO2_(XTAL_FN2 begin(), injector_(block_m));
				XTAL_TO2_(XTAL_FN2   end(), injector_(block_m + limit_m));

			private:
				XTAL_CN2 injector_(      A *i) XTAL_0EX {return appointer_f<      V *>(i);}
				XTAL_CN2 injector_(const A *i) XTAL_0EX {return appointer_f<const V *>(i);}
				XTAL_CN2 injector_(      V *i) XTAL_0EX {return appointer_f<      A *>(i);}
				XTAL_CN2 injector_(const V *i) XTAL_0EX {return appointer_f<const A *>(i);}


			public:// SIZE
				using R_::size;
			
				///\
				Reshapes `this` with `sN` elements. \

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
				///\throws `std::bad_alloc` if the required `sN` exceeds the maximum `N_size`. \

				XTAL_FN0 reserve(size_type sN)
				{
					if (N_size < sN) {
						throw _std::bad_alloc{};
					}
				}
				///\returns the constant `N_size`. \

				XTAL_FN2_(size_type) capacity()
				XTAL_0EX
				{
					return N_size;
				}
				///\
				Does nothing. \

				XTAL_FN0 shrink_to_fit()
				XTAL_0EX
				{}


			public:// CONSTRUCTION
				~type() {clear();}
				 type() noexcept = default;

				///\
				Insert constructor. \
				Initializes `this` with `sN` values determined by the given arguments. \

				XTAL_CXN type(size_type sN, XTAL_DEF ...etc)
				{
					insert_back(sN, XTAL_REF_(etc)...);
				}
				///\
				Span constructor. \
				Initializes `this` with the values between `i0` and `iN`. \

				template <class I0, class IN> requires epimorphic_p<iterator, I0, IN>
				XTAL_CXN type(I0 i0, IN iN)
				{
					push_back(i0, iN);
				}
				
				///\
				List constructor. \
				Initializes `this` with the given values. \

				XTAL_CON type(bracket_t<V> w)
				:	type(w.begin(), w.end())
				{}
				///\
				List assignment. \
				Replaces the contents of `this` with the given values. \

				XTAL_OP1 = (bracket_t<V> w)
				{
					return refresh_(w.begin(), w.end());
				}

				///\
				Copy constructor. \
				Initializes `this` with the given data. \

				XTAL_CON type(type const &t)
				:	type(t.begin(), t.end())
				{}
				///\
				Copy assigment. \
				Replaces the contents of `this` with the given data. \

				XTAL_OP1 = (type const &t)
				{
					return refresh_(t.begin(), t.end());
				}

				///\
				Move constructor. \
				Initializes `this` with the given data. \

				XTAL_CON type(type &&t)
				XTAL_REQ _std::move_constructible<V>
				:	type(mover_f(t.begin()), mover_f(t.end()))
				{}
				///\
				Move assigment. \
				Replaces the contents of `this` with the given data. \

				XTAL_OP1 = (type &&t)
				XTAL_REQ _std::move_constructible<V>
				{
					return refresh_(mover_f(t.begin()), mover_f(t.end()));
				}

				///\
				Swaps the contents of `this` with the given data. \

				XTAL_FN0 swap(type &t)
				requires _std::swappable<value_type>
				{
					iterator j0 = t.begin();
					iterator i0 =   begin();
					iterator iN =     end();
					_std::swap_ranges(injector_(i0), injector_(iN), injector_(j0));
				}

			private:
				///\
				Clears `this` and invokes `insert_back` with the given arguments. \

				XTAL_FN1 refresh_(XTAL_DEF... etc)
				{
					clear(); push_back(XTAL_REF_(etc)...);
					return *this;
				}


			public:// ALLOCATION
				///\
				Inserts the values `etc` beginning at `i0`. \

				template <class I0, class IN> requires epimorphic_p<iterator, I0, IN>
				XTAL_FN0 push_back(I0 i0, IN iN)
				{
					insert(end(), i0, iN);
				}
				///\
				Inserts the values `etc` beginning at `i0`. \

				XTAL_FN0 push_back(bracket_t<V> w)
				{
					push_back(w.begin(), w.end());
				}
				///\
				Inserts the values `etc...` beginning at `i0`. \

				XTAL_FN0 push_back(XTAL_DEF_(to_q<V>) ...vs)
				{
					push_back(bracket_t<V>{V(XTAL_REF_(vs))...});
				}
				///\
				Constructs an element at the end of `this` using the given arguments. \
				\returns a reference to the element.

				XTAL_FN1_(reference) emplace_back(XTAL_DEF ...etc)
				{
					return *inplace_back(XTAL_REF_(etc)...);
				}
				///\
				Invokes `insert` at `this->end()` with the given arguments. \

				XTAL_FN1_(iterator) insert_back(XTAL_DEF ...etc)
				{
					return insert(end(), XTAL_REF_(etc)...);
				}

				///\
				Constructs an element at `i` using the given arguments. \
				\returns a reference to the element.

				template <class I> requires common_q<iterator, I>
				XTAL_FN1_(reference) emplace(I i, XTAL_DEF ...etc)
				{
					return *inplace(i, XTAL_REF_(etc)...);
				}

				///\
				Inserts the values delimited by `j0` and `jN` beginning at `i`. \

				template <class I, class J0, class JN> requires epimorphic_p<iterator, I, J0, JN>
				XTAL_FN1_(iterator) insert(I i, J0 j0, JN jN)
				{
					using J = _std::common_type_t<J0, JN>;
					return insert(i, (J) j0, (J) jN);
				}
				template <class I, class J> requires epimorphic_p<iterator, I, J>
				XTAL_FN1_(iterator) insert(I i, J j0, J jN)
				{
					size_type sN = _std::distance(j0, jN);
					inject_(i, sN);
					_detail::copy_to(i, j0, jN);
					return i;
				}
				///\
				Inserts the values `w` beginning at `i`. \

				template <class I> requires common_q<iterator, I>
				XTAL_FN1_(iterator) insert(I i, bracket_t<V> w)
				{
					return insert(i, w.begin(), w.end());
				}
				///\
				Inserts the value `v` at `i`. \

				template <class I> requires common_q<iterator, I>
				XTAL_FN1_(iterator) insert(I i, XTAL_DEF_(common_q<V>) v)
				{
					return inplace(i, XTAL_REF_(v));
				}
				///\
				Initialises `sN` values with `v` beginning at `i`. \

				template <class I> requires common_q<iterator, I>
				XTAL_FN1_(iterator) insert(I i, size_type sN, XTAL_DEF_(common_q<V>) v)
				{
					inject_(i, sN);
					_std::uninitialized_fill_n(injector_(i), sN, XTAL_REF_(v));
					return i;
				}
				///\
				Initialises `sN` values beginning at `i`. \

				template <class I> requires common_q<iterator, I>
				XTAL_FN1_(iterator) insert(I i, size_type sN)
				{
					inject_(i, sN);
					_std::uninitialized_value_construct_n(injector_(i), sN);
					return i;
				}
				
			protected:
				XTAL_FN1_(iterator) inplace_back(XTAL_DEF ...etc)
				{
					reserve(1 + size());
					return ::new (block_m + limit_m++) V(XTAL_REF_(etc)...);
				}
				template <class I> requires common_q<iterator, I>
				XTAL_FN1_(iterator) inplace(I i, XTAL_DEF ...etc)
				{
					inject_(i, 1);
					return ::new (injector_(i)) V(XTAL_REF_(etc)...);
				}
				///\
				Allocates `sN` elements beginning at `i`. \

				XTAL_FN1_(iterator) inject_(iterator i0, size_type sN)
				{
					reserve(sN + size());
					iterator j0 = end();
					if (i0 < j0) {
						auto iN = _std::next(i0, sN);
						auto jN = _std::next(j0, sN);
						assert(_std::move_constructible<V>);
						_std::memmove(iN, i0, _std::distance(i0, j0)*sizeof(A));
					}
					limit_m += sN;
					return i0;
				}


			public:// DEALLOCATION
				///\
				Removes the last element from `this`. \

				XTAL_FN0 pop_back()
				{
					pop_back(1);
				}
				///\
				Removes the last `sN` elements from `this`. \

				XTAL_FN0 pop_back(size_type sN)
				{
					erase(end() - sN, end(), sN);
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

				template <class I0> requires common_q<iterator, I0>
				XTAL_FN1 erase(I0 i0)
				XTAL_0EX
				{
					return erase(i0, 1);
				}
				///\
				Deletes `sN` elements starting from `i0`. \

				template <class I0> requires common_q<iterator, I0>
				XTAL_FN1 erase(I0 i0, size_type sN)
				XTAL_0EX
				{
					return erase(i0, _std::next(i0, sN), sN);
				}
				///\
				Deletes the elements between `i0` and `iN`. \

				template <class I0, class IN> requires common_q<iterator, I0, IN>
				XTAL_FN1 erase(I0 i0, IN iN)
				XTAL_0EX
				{
					using I = _std::common_type_t<I0, IN>;
					return erase((I) i0, (I) iN, _std::distance((I) i0, (I) iN));
				}
				///\
				Deletes `sN` elements between `i0` and `iN`. \

				template <class I0, class IN> requires common_q<iterator, I0, IN>
				XTAL_FN1 erase(I0 i0, IN iN, size_type sN)
				XTAL_0EX
				{
					using I = _std::common_type_t<I0, IN>;
					erode_((I) i0, (I) iN, sN);
					return i0;
				}
			
			protected:
				///\
				Deletes `sN` elements between `i0` and `iN`. \

				template <class I> requires common_q<iterator, I>
				XTAL_FN0 erode_(I i0, I iN, size_type sN)
				XTAL_0EX
				{
					assert(begin() <= i0 and iN <= end() and _std::distance(i0, iN) == sN);
					churn_(i0, iN, sN);
					iterator iM = end();
					if (iN < iM) {
						assert(_std::move_constructible<V>);
						_std::memmove(i0, iN, _std::distance(iN, iM)*sizeof(A));
					}
					limit_m -= sN;
				}
				template <class I> requires common_q<iterator, I>
				XTAL_FN0 churn_(I i0, I iN, size_type sN)
				XTAL_0EX
				{
					if constexpr (_std::destructible<V>) {
						_std::destroy(i0, iN);
					}
				}

			};
		};

		template <class V> using fluid_t = typename fluid<V>::type;
		template <class V> using solid_t = typename solid<V>::type;

	};
	using type = subtype<unit_t>;
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
/**/
namespace std
{///////////////////////////////////////////////////////////////////////////////

template <xtal::array_q T> requires xtal::common::tag_q<T>
struct tuple_size<T>: xtal::arity_t<T> {};

template <size_t N, xtal::array_q T> requires xtal::common::tag_q<T>
struct tuple_element<N, T> {using type = xtal::value_t<T>;};


}/////////////////////////////////////////////////////////////////////////////
/***/
XTAL_ENV_(pop)
