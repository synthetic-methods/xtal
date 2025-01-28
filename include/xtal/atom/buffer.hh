#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::atom
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class ..._s> struct   buffer;
template <class ..._s> using    buffer_t = typename buffer<_s...>::type;
template <class ...Ts> concept  buffer_q = bond::tag_p<buffer_t, Ts...>;


////////////////////////////////////////////////////////////////////////////////
///\
A fluid-sized fixed-capacity analogue of `std::vector`. \
Configured by the array-like parameter `A`, where: \

///\
*	If `A` has capacity `< (unsigned) -1`, \
then a fixed-capacity implementation is provided. \

///\
*	If `A` is either a pointer or an array of length `(unsigned) -1`, \
the default (dynamically allocated) `std::vector` is used. \

template <class U_data> requires pointed_q<U_data>
struct buffer<U_data>
{
	using type = bond::compose_s<_std::vector<pointed_u<U_data>>, bond::tag<buffer_t>>;

};
template <class U_data>
struct buffer<U_data[(unsigned) -1]>
:	buffer<U_data *>
{
};
template <class U_data, auto N_data>
struct buffer<U_data[N_data]>
{
	using T_data = typename _detail::aligned<U_data>::type;

	template <class T>
	using holotype = bond::compose_s<arranged_t<T>, bond::tag<buffer>>;

	template <class T>
	class homotype : public holotype<T>
	{
		using S_ = holotype<T>;
		using I_ = _std::initializer_list<U_data>;

	public:// DEFINITION
		using              size_type  =        ::std::size_t;
		using        difference_type  =        ::std::ptrdiff_t;

		using             value_type  =        U_data;
		using         allocator_type  =        T;// TODO: Provide interface.

		using              reference  =        U_data &;
		using        const_reference  =  const U_data &;
		
		using                pointer  =        U_data *;
		using          const_pointer  =  const U_data *;

		using               iterator  =        U_data *;
		using         const_iterator  =  const U_data *;
		using       reverse_iterator  = _std::reverse_iterator<      iterator >;
		using const_reverse_iterator  = _std::reverse_iterator<const_iterator >;
	
	private:
		using             value_type_ =        T_data;
		using               iterator_ =        T_data *;
		using         const_iterator_ =  const T_data *;
		using       reverse_iterator_ = _std::reverse_iterator<      iterator_>;
		using const_reverse_iterator_ = _std::reverse_iterator<const_iterator_>;


		XTAL_DEF_(return,inline,set) offence_f(iterable_q auto const & t) noexcept -> auto {return _std::span(offence_f(t.begin()), offence_f(t.end()));}
		XTAL_DEF_(return,inline,set) offence_f(              iterator  i) noexcept -> auto {return reinterpret_cast<              iterator_>(i);}
		XTAL_DEF_(return,inline,set) offence_f(              iterator_ i) noexcept -> auto {return reinterpret_cast<              iterator >(i);}
		XTAL_DEF_(return,inline,set) offence_f(        const_iterator  i) noexcept -> auto {return reinterpret_cast<        const_iterator_>(i);}
		XTAL_DEF_(return,inline,set) offence_f(        const_iterator_ i) noexcept -> auto {return reinterpret_cast<        const_iterator >(i);}
		XTAL_DEF_(return,inline,set) offence_f(      reverse_iterator  i) noexcept -> auto {return reinterpret_cast<      reverse_iterator_>(i);}
		XTAL_DEF_(return,inline,set) offence_f(      reverse_iterator_ i) noexcept -> auto {return reinterpret_cast<      reverse_iterator >(i);}
		XTAL_DEF_(return,inline,set) offence_f(const_reverse_iterator  i) noexcept -> auto {return reinterpret_cast<const_reverse_iterator_>(i);}
		XTAL_DEF_(return,inline,set) offence_f(const_reverse_iterator_ i) noexcept -> auto {return reinterpret_cast<const_reverse_iterator >(i);}

		XTAL_DEF_(return,inline,set) defence_f(iterable_q auto const & t) noexcept -> auto {return _std::span(defence_f(t.begin()), defence_f(t.end()));}
		XTAL_DEF_(return,inline,set) defence_f(iterator_q auto         i) noexcept -> auto {return _std::launder(offence_f(XTAL_REF_(i)));}
		

		value_type_ m_data[N_data]{};
		difference_type n_data{};


	public:// ACCESS
		XTAL_DEF_(return,inline,let) begin()       noexcept -> auto {return defence_f(reinterpret_cast<      iterator_>(m_data));}
		XTAL_DEF_(return,inline,let) begin() const noexcept -> auto {return defence_f(reinterpret_cast<const_iterator_>(m_data));}
		XTAL_DEF_(return,inline,let)   end()       noexcept -> auto {return _std::next(begin(), n_data);}
		XTAL_DEF_(return,inline,let)   end() const noexcept -> auto {return _std::next(begin(), n_data);}


	public:// SIZE
		using S_::size;
	
		///\returns the constant `N_data`. \

		XTAL_DEF_(return,inline,set)
		capacity()
		noexcept -> size_type
		{
			return N_data;
		}
		///\
		Does nothing. \

		XTAL_DEF_(inline,let)
		shrink_make_fit()
		noexcept -> void
		{}
		///\
		Reshapes `this` with `sN` elements. \

		XTAL_DEF_(inline,let)
		resize(size_type sN, auto &&...oo)
		noexcept(false) -> void
		{
			size_type const sM = size();
			if (sN < sM) {
				pop_back(sM - sN);
			}
			else {
				insert_back(sN - sM, XTAL_REF_(oo)...);
			}
		}
		///\throws `std::bad_alloc` if the required `sN` exceeds the maximum `N_data`. \

		XTAL_DEF_(inline,let)
		reserve(size_type sN)
		noexcept(false) -> void
		{
			if (N_data < sN) {
				throw _std::bad_alloc{};
			}
		}
	
	protected:
		///\
		Allocates `sN` additional elements. \

		XTAL_DEF_(inline,let)
		deserve(size_type sN)
		noexcept(false) -> void
		{
			reserve(sN + size());
		}
		///\
		Allocates `sN` additional elements beginning at `i0`, \
		repositioning the cross-over if necessary. \

		///\note\
		Currently assumes move-invariance. \

		XTAL_DEF_(inline,let)
		deserve(size_type sN, iterator i0)
		noexcept(false) -> void
		{
			deserve(sN);
			auto iN = _std::next(i0, sN);
			auto sX = _std::distance(i0, end());
			if (0 < sX) {
				static_assert(_std::is_move_constructible_v<value_type>);
				_std::memmove(offence_f(iN), offence_f(i0), sX*_detail::aligned<value_type>::size());
			}
			n_data += sN;
		}


	public:// CONSTRUCT
	~	homotype() {clear();}
		homotype() noexcept=default;
	
		///\
		Insert constructor. \
		Initializes `this` with `sN` values determined by the given arguments. \

		XTAL_NEW_(explicit) homotype(size_type sN, auto &&...oo)
		{
			insert_back(sN, XTAL_REF_(oo)...);
		}
		///\
		Span constructor. \
		Initializes `this` with the values between `i0` and `iN`. \

		template <class I0, class IN> requires epimorphic_q<iterator, I0, IN>
		XTAL_NEW_(explicit) homotype(I0 i0, IN iN)
		{
			push_back(i0, iN);
		}
		template <class I0, class IN> requires epimorphic_q<iterator, I0, IN>
		XTAL_DEF_(inline,let)
		assign(I0 i0, IN iN)
		noexcept(false) -> void
		{
			clear(); push_back(i0, iN);
		}
		template <class I0, class IN> requires epimorphic_q<iterator, I0, IN>
		XTAL_DEF_(inline,let)
		assign(size_type sN, U_data const &u)
		noexcept(false) -> void
		{
			_std::uninitialized_fill_n((iterator_) m_data, sN, XTAL_REF_(u));
		}
		
		///\
		List constructor. \
		Initializes `this` with the given values. \

		XTAL_NEW_(implicit) homotype(I_ w)
		noexcept(false)
		:	homotype(w.begin(), w.end())
		{}
		///\
		List assignment. \
		Replaces the contents of `this` with the given values. \

		XTAL_DEF_(inline,let)
		operator = (I_ w)
		noexcept(false) -> homotype &
		{
			assign(w);
			return *this;
		}
		XTAL_DEF_(inline,let)
		assign(I_ w)
		noexcept(false) -> void
		{
			assign(w.begin(), w.end());
		}

		///\
		Copy constructor. \
		Initializes `this` with the given data. \

		XTAL_NEW_(implicit) homotype(homotype const &t)
		noexcept(false)
		:	homotype(t.begin(), t.end())
		{}
		///\
		Copy assigment. \
		Replaces the contents of `this` with the given data. \

		XTAL_DEF_(inline,let)
		operator = (homotype const &t)
		noexcept(false) -> homotype &
		{
			assign(t);
			return *this;
		}
		XTAL_DEF_(inline,let)
		assign(homotype const &t)
		noexcept(false) -> void
		{
			assign(t.begin(), t.end());
		}

		///\
		Move constructor. \
		Initializes `this` with the given data. \

		XTAL_NEW_(implicit) homotype(homotype &&t)
		noexcept(_std::is_nothrow_move_constructible_v<U_data>)
		requires _std::           move_constructible  <U_data>
		:	homotype(_detail::mover_f(t.begin()), _detail::mover_f(t.end()))
		{}
		///\
		Move assigment. \
		Replaces the contents of `this` with the given data. \

		XTAL_DEF_(inline,let)
		operator = (homotype &&t)
		noexcept(_std::is_nothrow_move_constructible_v<U_data>) ->homotype &
		requires _std::           move_constructible  <U_data>
		{
			assign(XTAL_MOV_(t));
			return *this;
		}
		XTAL_DEF_(inline,let)
		assign(homotype &&t)
		noexcept(false) -> void
		requires _std::move_constructible<U_data>
		{
			assign(_detail::mover_f(t.begin()), _detail::mover_f(t.end()));
		}

		///\
		Swaps the contents of `this` with the given data. \

		XTAL_DEF_(inline,let)
		swap(homotype &t)
		noexcept(false) -> void
		requires _std::swappable<value_type>
		{
			_detail::swap_with(offence_f(begin()), offence_f(t));
		}


	public:// ALLOCATION

		template <class I0, class IN> requires epimorphic_q<iterator, I0, IN>
		XTAL_DEF_(inline,let)
		push_back(I0 i0, IN iN)
		noexcept(false) -> void
		{
			insert(end(), i0, iN);
		}

		XTAL_DEF_(inline,let)
		push_back(I_ w)
		noexcept(false) -> void
		{
			push_back(w.begin(), w.end());
		}

		XTAL_DEF_(inline,let)
		push_back(make_q<U_data> auto &&...vs)
		noexcept(false) -> void
		{
			push_back(I_{U_data(XTAL_REF_(vs))...});
		}
		///\
		Constructs an element at the end of `this` using the given arguments. \
		\returns a reference to the element.

		XTAL_DEF_(inline,let)
		emplace_back(auto &&...oo)
		noexcept(false) -> reference
		{
			return *inplace_back(XTAL_REF_(oo)...);
		}
		///\
		Invokes `insert` at `this->end()` with the given arguments. \

		XTAL_DEF_(inline,let)
		insert_back(auto &&...oo)
		noexcept(false) -> iterator
		{
			return insert(end(), XTAL_REF_(oo)...);
		}

		///\
		Constructs an element at `i` using the given arguments. \
		\returns an iterator at the element.

		template <class I> requires common_q<iterator, I>
		XTAL_DEF_(inline,let)
		emplace(I i, auto &&...oo)
		noexcept(false) -> iterator
		{
			return inplace(i, XTAL_REF_(oo)...);
		}

		///\
		Inserts the values delimited by `j0` and `jN` beginning at `i`. \

		template <class I, class J0, class JN> requires epimorphic_q<iterator, I, J0, JN>
		XTAL_DEF_(inline,let)
		insert(I i, J0 j0, JN jN)
		noexcept(false) -> iterator
		{
			using J = common_t<J0, JN>;
			return insert(i, (J) j0, (J) jN);
		}
		template <class I, class J> requires epimorphic_q<iterator, I, J>
		XTAL_DEF_(inline,let)
		insert(I i, J j0, J jN)
		noexcept(false) -> iterator
		{
			size_type sN = _std::distance(j0, jN);
			deserve(sN, i);
			_detail::copy_to(i, j0, jN);
			return i;
		}
		///\
		Inserts the values `w` beginning at `i`. \

		template <class I> requires common_q<iterator, I>
		XTAL_DEF_(inline,let)
		insert(I i, I_ w)
		noexcept(false) -> iterator
		{
			return insert(i, w.begin(), w.end());
		}
		///\
		Inserts the value `v` at `i`. \

		template <class I> requires common_q<iterator, I>
		XTAL_DEF_(inline,let)
		insert(I i, common_q<U_data> auto &&u)
		noexcept(false) -> iterator
		{
			return inplace(i, XTAL_REF_(u));
		}
		///\
		Initialises `sN` values with `u` beginning at `i`. \

		template <class I> requires common_q<iterator, I>
		XTAL_DEF_(inline,let)
		insert(I i, size_type sN, common_q<U_data> auto &&u)
		noexcept(false) -> iterator
		{
			deserve(sN, i);
			_std::uninitialized_fill_n(offence_f(i), sN, XTAL_REF_(u));
			return i;
		}
		///\
		Initialises `sN` values beginning at `i`. \

		template <class I> requires common_q<iterator, I>
		XTAL_DEF_(inline,let)
		insert(I i, size_type sN)
		noexcept(false) -> iterator
		{
			deserve(sN, i);
			_std::uninitialized_value_construct_n(offence_f(i), sN);
			return i;
		}
		
	protected:
		XTAL_DEF_(inline,let)
		inplace_back(auto &&...oo)
		noexcept(false) -> iterator
		{
			deserve(1);
			iterator i = end(); ++n_data;
			return (iterator) ::new(offence_f(i)) value_type(XTAL_REF_(oo)...);
		}
		XTAL_DEF_(inline,let)
		inplace(iterator i, auto &&...oo)
		noexcept(false) -> iterator
		{
			deserve(1, i);
			return (iterator) ::new(offence_f(i)) value_type(XTAL_REF_(oo)...);
		}


	public:// DEALLOCATION
		///\
		Removes the last element from `this`. \

		XTAL_DEF_(inline,let)
		pop_back()
		noexcept(false) -> void
		{
			pop_back(1);
		}
		///\
		Removes the last `sN` elements from `this`. \

		XTAL_DEF_(inline,let)
		pop_back(size_type sN)
		noexcept(false) -> void
		{
			erase(_std::prev(end(), sN), end(), sN);
		}
		///\
		Deletes all elements. \

		XTAL_DEF_(inline,let)
		clear()
		noexcept -> void
		{
			erase(begin(), end());
		}
		///\
		Deletes the element at `i0`. \

		template <class I0> requires common_q<iterator, I0>
		XTAL_DEF_(inline,let)
		erase(I0 i0)
		noexcept -> decltype(auto)
		{
			return erase(i0, 1);
		}
		///\
		Deletes `sN` elements starting from `i0`. \

		template <class I0> requires common_q<iterator, I0>
		XTAL_DEF_(inline,let)
		erase(I0 i0, size_type sN)
		noexcept -> decltype(auto)
		{
			return erase(i0, _std::next(i0, sN), sN);
		}
		///\
		Deletes the elements between `i0` and `iN`. \

		template <class I0, class IN> requires common_q<iterator, I0, IN>
		XTAL_DEF_(inline,let)
		erase(I0 i0, IN iN)
		noexcept -> decltype(auto)
		{
			using I = common_t<I0, IN>;
			return erase((I) i0, (I) iN, _std::distance((I) i0, (I) iN));
		}
		///\
		Deletes `sN` elements between `i0` and `iN`. \

		///\note\
		Non-standard signature. \

		///\note\
		Currently assumes move-invariance. \

		XTAL_DEF_(inline,let)
		erase(iterator i0, iterator iN, size_type sN)
		noexcept -> decltype(auto)
		{
			assert(begin() <= i0 and iN <= end() and _std::distance(i0, iN) == sN);
			if constexpr (_std::destructible<value_type>) {
				_std::destroy(i0, iN);
			}
			auto const sX = _std::distance(iN, end());
			if (0 < sX) {
				static_assert(_std::is_move_constructible_v<value_type>);
				_std::memmove(i0, iN, sX*_detail::aligned<value_type>::size());
			}
			n_data -= sN;
			return i0;
		}

	};
	using type = derive_t<homotype>;

};


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
