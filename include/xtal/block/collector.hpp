#pragma once
#include "./any.hpp"






XTAL_ENV_(push)
namespace xtal::block
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
///\
A decorator that defines the base-types for block-based data storage, \
namely `fixed` (sharing the same interface as `std::array`), \
and `fluid` (sharing the same interface as `std::vector`). \
These types are made available to any class with which it is `compose`d, \
and can be further transformed using `collected` to provide differentiated types. \

template <int N_size=-1>
struct collector
{
	template <typename S>
	class subtype: public S
	{
		using co = S;
		
		template <typename W> using etc_t = _std::initializer_list<W>;

	public:
		using co::co;
		using arity = constant_t<N_size>;

		template <typename V> struct fixed;
		template <typename V> struct fluid;
		

		template <typename V> requires (0 < N_size)
		struct fixed<V>
		{
			using kind = _std::array<V, N_size>;// FIXME: Just an easy way to access `std::apply` etc for now...
			class type: public kind
			{
				using co = kind;

			public:
				XTAL_NEW type(etc_t<V> in)
				XTAL_0EX
				{
					_detail::copy_to(co::begin(), in.begin(), in.end());
				}
				using co::co;

			};
		};
		template <typename V> requires (N_size < 0)
		struct fluid<V>
		{
			using type = _std::vector<V>;

		};
		template <typename V>
		struct fluid
		{
		private:
			using A = _std::aligned_storage_t<sizeof(V), alignof(V)>;

			template <typename I>
			XTAL_FZ2_(I) appointed_f(XTAL_DEF i) XTAL_0EX {return _std::launder(reinterpret_cast<I>(XTAL_REF_(i)));}
			
			XTAL_FZ2_(A       *) appointee_f(V       *i) XTAL_0EX {return appointed_f<A       *>(i);}
			XTAL_FZ2_(A const *) appointee_f(V const *i) XTAL_0EX {return appointed_f<A const *>(i);}
			XTAL_FZ2_(V       *) appointer_f(A       *i) XTAL_0EX {return appointed_f<V       *>(i);}
			XTAL_FZ2_(V const *) appointer_f(A const *i) XTAL_0EX {return appointed_f<V const *>(i);}
			
			XTAL_FZ2 reverse_appointee_f(XTAL_DEF i) XTAL_0EX {return _std::make_reverse_iterator(appointee_f(XTAL_REF_(i)));}
			XTAL_FZ2 reverse_appointer_f(XTAL_DEF i) XTAL_0EX {return _std::make_reverse_iterator(appointer_f(XTAL_REF_(i)));}

		public:
			template <typename T>
			class homotype: public iterate_t<T>
			{
				using co = iterate_t<T>;
				
			//	alignas(V) _std::byte block_m[sizeof(V)*(N_size)];
				A  block_m[N_size];
				A* limit_m = block_m;

			public:
				XTAL_FN2 get() XTAL_0FX_(&) {return static_cast<T const &>(*this);}
				XTAL_FN2 get() XTAL_0EX_(&) {return static_cast<T       &>(*this);}
				XTAL_RE4_(XTAL_FN2 get(XTAL_DEF i), get()[XTAL_REF_(i)]);

			//	using co;
				using co::size;

				using         allocator_type = T;
				using             value_type = V;

				using              size_type = _std::size_t;
				using        difference_type = _std::ptrdiff_t;

				using              reference = value_type       &;
				using        const_reference = value_type const &;
				
				using                pointer = value_type       *;
				using          const_pointer = value_type const *;

				using               iterator = value_type       *;
				using         const_iterator = value_type const *;
				
				using       reverse_iterator = _std::reverse_iterator<      iterator>;
				using const_reverse_iterator = _std::reverse_iterator<const_iterator>;
				
				XTAL_RE4_(XTAL_OP2[](size_type i), *appointer_f(block_m + i));
				XTAL_RE4_(XTAL_OP2()(size_type i),  appointer_f(block_m + i));

				XTAL_RE4_(XTAL_FN2 rbegin(), reverse_appointer_f(limit_m));
				XTAL_RE4_(XTAL_FN2  begin(),         appointer_f(block_m));
				XTAL_RE4_(XTAL_FN2   rend(), reverse_appointer_f(block_m));
				XTAL_RE4_(XTAL_FN2    end(),         appointer_f(limit_m));
				
				XTAL_FN2 crbegin() XTAL_0FX {return rbegin();}
				XTAL_FN2  cbegin() XTAL_0FX {return  begin();}
				XTAL_FN2   crend() XTAL_0FX {return   rend();}
				XTAL_FN2    cend() XTAL_0FX {return    end();}

				XTAL_RE4_(XTAL_FN2 data(), begin());

				///\
				Clear destructor. \

				~homotype()
				{
					clear();
				}
				///\
				Default constructor. \

				homotype() noexcept = default;

				///\
				Insert constructor. \
				Initializes `this` with `sN` values determined by the given arguments. \

				XTAL_NEW_(explicit) homotype(size_type sN, XTAL_DEF ...ws)
				{
					insert_back(sN, XTAL_REF_(ws)...);
				}

				///\
				Span constructor. \
				Initializes `this` with the values between `i0` and `iN`. \

				template <iso_q<iterator> I0, iso_q<iterator> IN>
				XTAL_NEW_(explicit) homotype(I0 i0, IN iN)
				{
					using I = _std::common_type_t<I0, IN>;
					I i0_ = i0;
					I iN_ = iN;
					insert_back(i0_, iN_);
				}

				///\
				List constructor. \
				Initializes `this` with the given values. \

				XTAL_NEW_(explicit) homotype(etc_t<V> etc)
				:	homotype(etc.begin(), etc.end())
				{
				}
				///\
				List assignment. \
				Replaces the contents of `this` with the given values. \

				XTAL_OP1 = (etc_t<V> etc)
				{
					refill(etc.begin(), etc.end());
					return get();
				}

				///\
				Copy constructor. \
				Initializes `this` with the given data. \

				XTAL_NEW homotype(homotype const &t)
				:	homotype(t.begin(), t.end())
				{
				}
				///\
				Copy assigment. \
				Replaces the contents of `this` with the given data. \

				XTAL_OP1 = (homotype const &t)
				{
					refill(t.begin(), t.end());
					return get();
				}

				///\
				Move constructor. \
				Initializes `this` with the given data. \

				XTAL_NEW homotype(homotype &&t)
				:	homotype(_std::make_move_iterator(t.begin()), _std::make_move_iterator(t.end()))
				{
				}
				///\
				Move assigment. \
				Replaces the contents of `this` with the given data. \

				XTAL_OP1 = (homotype &&t)
				{
					refill(_std::make_move_iterator(t.begin()), _std::make_move_iterator(t.end()));
					return get();
				}

				///\
				Swaps the contents of `this` with the given data. \

				XTAL_FN0 swap(homotype &t)
				requires _std::swappable<value_type>
				{
					_std::swap_ranges(begin(), end(), t.begin());
				}

				///\
				\returns the fixed capacity `N_size`. \

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
					if (N_size < sN)
					{	throw _std::bad_alloc {};
					}
				}

				///\
				Resizes `this` to `sN` elements. \

				XTAL_FN0 resize(size_type sN, XTAL_DEF ...ws)
				{
					size_type const sM = size();
					if (sN < sM)
					{	pop_back(sM - sN);
					}
					else
					{	insert_back(sN - sM, XTAL_REF_(ws)...);
					}
				}

				///\
				Clears `this` and invokes `insert_back` with the given arguments. \

				XTAL_FN0 refill(XTAL_DEF ...ws)
				{
					clear();
					insert_back(XTAL_REF_(ws)...);
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

				XTAL_FN0 push_back(etc_t<V> etc)
				{
					insert_back(etc.begin(), etc.end());
				}
				///\
				Inserts the values `etc...` beginning at `i0`. \

				XTAL_FN0 push_back(XTAL_DEF_(to_q<V>) ...etc)
				{
					push_back(etc_t<V>{V(XTAL_REF_(etc))...});
				}

				///\
				Constructs an element at the end of `this` using the given arguments. \
				\returns a reference to the element.

				XTAL_FN1_(reference) emplace_back(XTAL_DEF ...ws)
				{
					return *inplace_back(XTAL_REF_(ws)...);
				}
				///\
				Constructs an element at the end of `this` using the given arguments. \
				\returns a pointer to the element.

				XTAL_FN1_(iterator) inplace_back(XTAL_DEF ...ws)
				{
					reserve(size_type(1) + size());
					return ::new (limit_m++) V(XTAL_REF_(ws)...);
				}

				///\
				Invokes `insert` at `this->end()` with the given arguments. \

				XTAL_FN1_(iterator) insert_back(XTAL_DEF ...ws)
				{
					return insert(end(), XTAL_REF_(ws)...);
				}

				///\
				Inserts the values delimited by `j0` and `jN` beginning at `i`. \

				template <is_q<iterator> I, iso_q<iterator> J0, iso_q<iterator> JN>
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
				Inserts the values `etc` beginning at `i`. \

				template <is_q<iterator> I>
				XTAL_FN1_(iterator) insert(I i, etc_t<V> etc)
				{
					return insert(i, etc.begin(), etc.end());
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
					_std::uninitialized_fill_n(i, sN, _std::move(v));
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
					if (i < end())// and _std::move_constructible<V>)
					{	auto j = reverse_appointer_f(limit_m);
						_detail::move_to(_std::prev(j, sN), j, _std::next(j, sN), true);
					}
					else
					{	assert(i == end());
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
					
					if constexpr (_std::destructible<V>)
					{	_std::destroy(i0_, iN_);
					}
					if (iN_ < end_m)// and _std::move_constructible<V>)
					{	auto jN = appointee_f(iN_);
						auto j0 = appointee_f(i0_);
						_detail::move_to(j0, jN, limit_m, sN <= _std::distance(jN, limit_m));
					}
					else
					{	assert(end_m == iN_);
					}
					limit_m -= sN;
				}

			};
			class type: public homotype<type>
			{
				using co = homotype<type>;
			public:
				using co::co;

			};
		};

	};
};

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)