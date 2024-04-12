#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::atom
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class ..._s> struct  store;
template <class ..._s> using   store_t = typename store<_s...>::type;
template <class ...Ts> concept store_q = bond::tag_p<store, Ts...>;


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

template <class U_data> requires pointer_q<U_data>
struct store<U_data>
{
	using type = bond::compose_s<_std::vector<pointed_t<U_data>>, bond::tag<store>>;

};
template <class U_data>
struct store<U_data[~0U]>
:	store<U_data *>
{
};
template <class U_data, size_t N_data>
struct store<U_data[N_data]>
{
	using W_data = _detail::aligned_t<U_data>;

	template <class T>
	using holotype = bond::compose_s<initerated_t<T>, bond::tag<store>>;

	template <class T>
	class homotype : public holotype<T>
	{
		using T_ = holotype<T>;

	public:// DEFINITION
		using              size_type  =        size_t;
		using        difference_type  =        size_s;

		using             value_type  =        U_data;
		using         allocator_type  =        T;// TODO: Provide interface?

		using              reference  =        U_data &;
		using        const_reference  =  const U_data &;
		
		using                pointer  =        U_data *;
		using          const_pointer  =  const U_data *;

		using               iterator  =        U_data *;
		using         const_iterator  =  const U_data *;
		using       reverse_iterator  = _std::reverse_iterator<      iterator >;
		using const_reverse_iterator  = _std::reverse_iterator<const_iterator >;
	
	private:
		using               iterator_ =        W_data *;
		using         const_iterator_ =  const W_data *;
		using       reverse_iterator_ = _std::reverse_iterator<      iterator_>;
		using const_reverse_iterator_ = _std::reverse_iterator<const_iterator_>;


		XTAL_DEF_(return,inline) XTAL_LET offence(iterated_q auto const & t) noexcept -> decltype(auto) {return _std::span(offence(t.begin()), offence(t.end()));}
		XTAL_DEF_(return,inline) XTAL_LET offence(              iterator  i) noexcept -> decltype(auto) {return reinterpret_cast<                  iterator_>(i);}
		XTAL_DEF_(return,inline) XTAL_LET offence(              iterator_ i) noexcept -> decltype(auto) {return reinterpret_cast<                  iterator >(i);}
		XTAL_DEF_(return,inline) XTAL_LET offence(        const_iterator  i) noexcept -> decltype(auto) {return reinterpret_cast<            const_iterator_>(i);}
		XTAL_DEF_(return,inline) XTAL_LET offence(        const_iterator_ i) noexcept -> decltype(auto) {return reinterpret_cast<            const_iterator >(i);}
		XTAL_DEF_(return,inline) XTAL_LET offence(      reverse_iterator  i) noexcept -> decltype(auto) {return reinterpret_cast<          reverse_iterator_>(i);}
		XTAL_DEF_(return,inline) XTAL_LET offence(      reverse_iterator_ i) noexcept -> decltype(auto) {return reinterpret_cast<          reverse_iterator >(i);}
		XTAL_DEF_(return,inline) XTAL_LET offence(const_reverse_iterator  i) noexcept -> decltype(auto) {return reinterpret_cast<    const_reverse_iterator_>(i);}
		XTAL_DEF_(return,inline) XTAL_LET offence(const_reverse_iterator_ i) noexcept -> decltype(auto) {return reinterpret_cast<    const_reverse_iterator >(i);}

		XTAL_DEF_(return,inline) XTAL_LET defence(iterated_q auto const & t) noexcept -> decltype(auto) {return _std::span(defence(t.begin()), defence(t.end()));}
		XTAL_DEF_(return,inline) XTAL_LET defence(iterator_q auto         i) noexcept -> decltype(auto) {return _std::launder(offence(XTAL_REF_(i)));}
		

		W_data m_data[N_data]{};
		difference_type n_data{};


	public:// ACCESS
		XTAL_TN2 begin() XTAL_0EX {return defence(reinterpret_cast<      iterator_>(m_data));}
		XTAL_TN2 begin() XTAL_0FX {return defence(reinterpret_cast<const_iterator_>(m_data));}
		XTAL_TO2_(XTAL_TN2 end(), _std::next(begin(), n_data))


	public:// SIZE
		using T_::size;
	
		///\returns the constant `N_data`. \

		XTAL_FN2_(size_type) capacity()
		XTAL_0EX
		{
			return N_data;
		}
		///\
		Does nothing. \

		XTAL_TN0 shrink_make_fit()
		XTAL_0EX
		{}
		///\
		Reshapes `this` with `sN` elements. \

		XTAL_TN0 resize(size_type sN, auto &&...etc)
		{
			size_type const sM = size();
			if (sN < sM) {
				pop_back(sM - sN);
			}
			else {
				insert_back(sN - sM, XTAL_REF_(etc)...);
			}
		}
		///\throws `std::bad_alloc` if the required `sN` exceeds the maximum `N_data`. \

		XTAL_TN0 reserve(size_type sN)
		{
			if (N_data < sN) {
				throw _std::bad_alloc{};
			}
		}
	
	protected:
		///\
		Allocates `sN` additional elements. \

		XTAL_TN0 deserve(size_type sN)
		{
			reserve(sN + size());
		}
		///\
		Allocates `sN` additional elements beginning at `i0`, \
		repositioning the cross-over if necessary. \

		///\note\
		Currently assumes move-invariance. \

		XTAL_TN0 deserve(size_type sN, iterator i0)
		{
			deserve(sN);
			auto iN = _std::next(i0, sN);
			auto sX = _std::distance(i0, end());
			if (0 < sX) {
				static_assert(_std::is_move_constructible_v<value_type>);
				_std::memmove(offence(iN), offence(i0), sX*_detail::aligned_n<value_type>);
			}
			n_data += sN;
		}


	public:// CONSTRUCTION
	~	homotype() {clear();}
	
	//	XTAL_CO0_(homotype)
		XTAL_CO1_(homotype)

		///\
		Insert constructor. \
		Initializes `this` with `sN` values determined by the given arguments. \

		XTAL_CXN homotype(size_type sN, auto &&...etc)
		{
			insert_back(sN, XTAL_REF_(etc)...);
		}
		///\
		Span constructor. \
		Initializes `this` with the values between `i0` and `iN`. \

		template <class I0, class IN> requires epimorphic_q<iterator, I0, IN>
		XTAL_CXN homotype(I0 i0, IN iN)
		{
			push_back(i0, iN);
		}
		template <class I0, class IN> requires epimorphic_q<iterator, I0, IN>
		XTAL_TN0 assign(I0 i0, IN iN)
		{
			clear(); push_back(i0, iN);
		}
		template <class I0, class IN> requires epimorphic_q<iterator, I0, IN>
		XTAL_TN0 assign(size_type sN, U_data const &u)
		{
			_std::uninitialized_fill_n((iterator_) m_data, sN, XTAL_REF_(u));
		}
		
		///\
		List constructor. \
		Initializes `this` with the given values. \

		XTAL_CON homotype(braces_t<U_data> w)
		:	homotype(w.begin(), w.end())
		{}
		///\
		List assignment. \
		Replaces the contents of `this` with the given values. \

		XTAL_OP1_(homotype &) = (braces_t<U_data> w)
		{
			assign(w);
			return *this;
		}
		XTAL_TN0 assign(braces_t<U_data> w)
		{
			assign(w.begin(), w.end());
		}

		///\
		Copy constructor. \
		Initializes `this` with the given data. \

		XTAL_CON homotype(homotype const &t)
		:	homotype(t.begin(), t.end())
		{}
		///\
		Copy assigment. \
		Replaces the contents of `this` with the given data. \

		XTAL_OP1_(homotype &) = (homotype const &t)
		{
			assign(t);
			return *this;
		}
		XTAL_TN0 assign(homotype const &t)
		{
			assign(t.begin(), t.end());
		}

		///\
		Move constructor. \
		Initializes `this` with the given data. \

		XTAL_CON homotype(homotype &&t)
		XTAL_REQ _std::move_constructible<U_data>
		:	homotype(_detail::mover_f(t.begin()), _detail::mover_f(t.end()))
		{}
		///\
		Move assigment. \
		Replaces the contents of `this` with the given data. \

		XTAL_OP1_(homotype &) = (homotype &&t)
		XTAL_REQ _std::move_constructible<U_data>
		{
			assign(XTAL_MOV_(t));
			return *this;
		}
		XTAL_TN0 assign(homotype &&t)
		XTAL_REQ _std::move_constructible<U_data>
		{
			assign(_detail::mover_f(t.begin()), _detail::mover_f(t.end()));
		}

		///\
		Swaps the contents of `this` with the given data. \

		XTAL_TN0 swap(homotype &t)
		requires _std::swappable<value_type>
		{
			_detail::swap_with(offence(begin()), offence(t));
		}


	public:// ALLOCATION
		///\
		Inserts the values `etc` beginning at `i0`. \

		template <class I0, class IN> requires epimorphic_q<iterator, I0, IN>
		XTAL_TN0 push_back(I0 i0, IN iN)
		{
			insert(end(), i0, iN);
		}
		///\
		Inserts the values `etc` beginning at `i0`. \

		XTAL_TN0 push_back(braces_t<U_data> w)
		{
			push_back(w.begin(), w.end());
		}
		///\
		Inserts the values `etc...` beginning at `i0`. \

		XTAL_TN0 push_back(make_q<U_data> auto &&...vs)
		{
			push_back(braces_t<U_data>{U_data(XTAL_REF_(vs))...});
		}
		///\
		Constructs an element at the end of `this` using the given arguments. \
		\returns a reference to the element.

		XTAL_TN1_(reference) emplace_back(auto &&...etc)
		{
			return *inplace_back(XTAL_REF_(etc)...);
		}
		///\
		Invokes `insert` at `this->end()` with the given arguments. \

		XTAL_TN1_(iterator) insert_back(auto &&...etc)
		{
			return insert(end(), XTAL_REF_(etc)...);
		}

		///\
		Constructs an element at `i` using the given arguments. \
		\returns a reference to the element.

		template <class I> requires common_q<iterator, I>
		XTAL_TN1_(reference) emplace(I i, auto &&...etc)
		{
			return *inplace(i, XTAL_REF_(etc)...);
		}

		///\
		Inserts the values delimited by `j0` and `jN` beginning at `i`. \

		template <class I, class J0, class JN> requires epimorphic_q<iterator, I, J0, JN>
		XTAL_TN1_(iterator) insert(I i, J0 j0, JN jN)
		{
			using J = common_t<J0, JN>;
			return insert(i, (J) j0, (J) jN);
		}
		template <class I, class J> requires epimorphic_q<iterator, I, J>
		XTAL_TN1_(iterator) insert(I i, J j0, J jN)
		{
			size_type sN = _std::distance(j0, jN);
			deserve(sN, i);
			_detail::copy_to(i, j0, jN);
			return i;
		}
		///\
		Inserts the values `w` beginning at `i`. \

		template <class I> requires common_q<iterator, I>
		XTAL_TN1_(iterator) insert(I i, braces_t<U_data> w)
		{
			return insert(i, w.begin(), w.end());
		}
		///\
		Inserts the value `v` at `i`. \

		template <class I> requires common_q<iterator, I>
		XTAL_TN1_(iterator) insert(I i, common_q<U_data> auto &&u)
		{
			return inplace(i, XTAL_REF_(u));
		}
		///\
		Initialises `sN` values with `u` beginning at `i`. \

		template <class I> requires common_q<iterator, I>
		XTAL_TN1_(iterator) insert(I i, size_type sN, common_q<U_data> auto &&u)
		{
			deserve(sN, i);
			_std::uninitialized_fill_n(offence(i), sN, XTAL_REF_(u));
			return i;
		}
		///\
		Initialises `sN` values beginning at `i`. \

		template <class I> requires common_q<iterator, I>
		XTAL_TN1_(iterator) insert(I i, size_type sN)
		{
			deserve(sN, i);
			_std::uninitialized_value_construct_n(offence(i), sN);
			return i;
		}
		
	protected:
		XTAL_TN1_(iterator) inplace_back(auto &&...oo)
		{
			deserve(1);
			iterator i = end(); ++n_data;
			return (iterator) ::new(offence(i)) value_type(XTAL_REF_(oo)...);
		}
		XTAL_TN1_(iterator) inplace(iterator i, auto &&...oo)
		{
			deserve(1, i);
			return (iterator) ::new(offence(i)) value_type(XTAL_REF_(oo)...);
		}


	public:// DEALLOCATION
		///\
		Removes the last element from `this`. \

		XTAL_TN0 pop_back()
		{
			pop_back(1);
		}
		///\
		Removes the last `sN` elements from `this`. \

		XTAL_TN0 pop_back(size_type sN)
		{
			erase(_std::prev(end(), sN), end(), sN);
		}
		///\
		Deletes all elements. \

		XTAL_TN0 clear()
		XTAL_0EX
		{
			erase(begin(), end());
		}
		///\
		Deletes the element at `i0`. \

		template <class I0> requires common_q<iterator, I0>
		XTAL_TN1 erase(I0 i0)
		XTAL_0EX
		{
			return erase(i0, 1);
		}
		///\
		Deletes `sN` elements starting from `i0`. \

		template <class I0> requires common_q<iterator, I0>
		XTAL_TN1 erase(I0 i0, size_type sN)
		XTAL_0EX
		{
			return erase(i0, _std::next(i0, sN), sN);
		}
		///\
		Deletes the elements between `i0` and `iN`. \

		template <class I0, class IN> requires common_q<iterator, I0, IN>
		XTAL_TN1 erase(I0 i0, IN iN)
		XTAL_0EX
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

		XTAL_TN1 erase(iterator i0, iterator iN, size_type sN)
		XTAL_0EX
		{
			assert(begin() <= i0 and iN <= end() and _std::distance(i0, iN) == sN);
			if constexpr (_std::destructible<value_type>) {
				_std::destroy(i0, iN);
			}
			auto const sX = _std::distance(iN, end());
			if (0 < sX) {
				static_assert(_std::is_move_constructible_v<value_type>);
				_std::memmove(i0, iN, sX*_detail::aligned_n<value_type>);
			}
			n_data -= sN;
			return i0;
		}

	};
	using type = bond::isotype<homotype>;

};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
