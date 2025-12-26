#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::atom
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class ..._s> struct   buffer;
template <class ..._s> using    buffer_t = typename buffer<_s...>::type;
template <class ...Ts> concept  buffer_q = bond::tag_in_p<buffer_t, Ts...>;


////////////////////////////////////////////////////////////////////////////////
/*!
\brief  	Analogue of `std::vector`, parameterized by shape `value_type[capacity]`.

Implementation depends on parameter `value_type[capacity]`, where:

-	If `0 <  capacity and capacity <= XTAL_SYS_(extent)`,
then a fixed-capacity implementation is provided.

-	If `0 == capacity or  capacity >= XTAL_SYS_(extent)`,
	or the parameter provided `std::is_pointer_v`,
	the default (dynamically allocated) `std::vector` is used.

\todo    Implement support functions like `std::erase(?:_if)`, and any additions to C++20.
*/
template <scalar_q U_data>
struct buffer<U_data *>
{
	using type = bond::compose_s<_std::vector<U_data>, bond::tag<buffer_t>>;

};
template <vector_q A_data> requires _detail::  elastic_fixed_q<A_data>
struct buffer<A_data>
{
	using U_data = typename fixed<A_data>::value_type;

	using type = bond::compose_s<_std::vector<U_data>, bond::tag<buffer_t>>;

};
template <vector_q A_data> requires _detail::inelastic_fixed_q<A_data>
struct buffer<A_data>
{
	using U_data = typename fixed<A_data>::value_type;
	using T_data = typename _detail::aligned<U_data>::type;
	static auto constexpr N_data = fixed<A_data>::extent();

	template <class T>
	using holotype = bond::compose_s<_xtd::ranges::view_interface<T>, bond::tag<buffer_t>>;

	template <class T>
	class homotype : public holotype<T>
	{
		using S_ = holotype<T>;

	public:// DEFINITION
		using                  size_type  =        ::std::size_t;
		using            difference_type  =        ::std::ptrdiff_t;

		using                 value_type  =        U_data;
		using             allocator_type  =        T;// TODO: Provide interface.

		using                  reference  =        U_data &;
		using            const_reference  =  const U_data &;
		
		using                    pointer  =        U_data *;
		using              const_pointer  =  const U_data *;

		using                   iterator  =        U_data *;
		using             const_iterator  =  const U_data *;
		using           reverse_iterator  = _std::reverse_iterator<      iterator >;
		using     const_reverse_iterator  = _std::reverse_iterator<const_iterator >;
	
	private:
		static auto constexpr value_size_ = _detail::aligned<value_type>::size;
		using                 value_type_ =        T_data;

		using                   iterator_ =        T_data *;
		using             const_iterator_ =  const T_data *;
		using           reverse_iterator_ = _std::reverse_iterator<      iterator_>;
		using     const_reverse_iterator_ = _std::reverse_iterator<const_iterator_>;

		value_type_ m_data[N_data]{};
		difference_type n_data{};


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

		XTAL_DEF_(return,inline,let)  modify_f(                  auto  i) noexcept -> auto {return i;}//NOTE: Assumed non-const...
		XTAL_DEF_(return,inline,let)  modify_f(        const_iterator  i) noexcept -> auto {return _std::next( begin(), _std::distance( cbegin(), i));}
		XTAL_DEF_(return,inline,let)  modify_f(const_reverse_iterator  i) noexcept -> auto {return _std::next(rbegin(), _std::distance(crbegin(), i));}


	public:// ACCESS
		XTAL_DEF_(return,inline,let)     end()       noexcept -> auto {return _std::next(  begin(), n_data);}
		XTAL_DEF_(return,inline,let)     end() const noexcept -> auto {return _std::next(  begin(), n_data);}
		XTAL_DEF_(return,inline,let)    cend() const noexcept -> auto {return _std::next( cbegin(), n_data);}
		XTAL_DEF_(return,inline,let)    rend() const noexcept -> auto {return _std::next( rbegin(), n_data);}
		XTAL_DEF_(return,inline,let)   crend() const noexcept -> auto {return _std::next(crbegin(), n_data);}
		XTAL_DEF_(return,inline,let)   begin()       noexcept -> auto {return defence_f(reinterpret_cast<      iterator_>(m_data));}
		XTAL_DEF_(return,inline,let)   begin() const noexcept -> auto {return defence_f(reinterpret_cast<const_iterator_>(m_data));}
		XTAL_DEF_(return,inline,let)  cbegin() const noexcept -> auto {return defence_f(reinterpret_cast<const_iterator_>(m_data));}
		XTAL_DEF_(return,inline,let)  rbegin() const noexcept -> auto {return _std::make_reverse_iterator( begin());}
		XTAL_DEF_(return,inline,let) crbegin() const noexcept -> auto {return _std::make_reverse_iterator(cbegin());}


	public:// SIZE
		using S_::size;
	
		/*!
		\returns	The parameterized size.
		*/
		static cardinal_constant_t<N_data> constexpr capacity{};

		/*!
		\brief  	Does nothing.
		*/
		XTAL_DEF_(inline,let)
		shrink_make_fit()
		noexcept -> void
		{}
		/*!
		\brief  	Reshapes `this` with `sN` elements.
		*/
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
		/*!
		\brief  	Does nothing.
		\throws `std::bad_alloc` if the required `sN` exceeds the maximum `N_data`.
		*/

		XTAL_DEF_(inline,let)
		reserve(size_type sN)
		noexcept(false) -> void
		{
			if (N_data < sN) [[unlikely]] {
				throw _std::bad_alloc{};
			}
		}
	
	protected:
		/*!
		\brief  	Allocates `sN` additional elements.
		*/
		XTAL_DEF_(inline,let)
		deserve(size_type sN)
		noexcept(false) -> void
		{
			reserve(sN + size());
		}
		/*!
		\brief  	Allocates `sN` additional elements beginning at `i0`,
		repositioning the cross-over if necessary.
		*/
		XTAL_DEF_(inline,let)
		deserve (size_type sN, const_iterator i0)
		noexcept(false) -> void
		{
			return deserve_(sN, modify_f(i0));
		}
		XTAL_DEF_(inline,let)
		deserve_(size_type sN, iterator i0)
		noexcept(false) -> void
		{
			deserve(sN);
			auto iN  = _std::next(i0, sN);

			auto i0_ = offence_f(i0);
			auto iN_ = offence_f(iN);
			auto iZ_ = offence_f(end());

			auto sZ  = _std::distance(i0_, iZ_);
			if  (sZ) {
				XTAL_IF0
				//\
				XTAL_0IF_(do) (_detail::move_to(iN_, i0_,             sZ))
				XTAL_0IF_(do) (_std::memmove   (iN_, i0_, value_size_*sZ))
				XTAL_0IF_(else) {
					_detail::swap_to(i0_, iZ_, _std::next(iZ_, sN));
				}
			}
			n_data += sN;
		}


	public:// CONSTRUCT

		XTAL_NEW_(delete) (homotype, {clear();})
	//	XTAL_NEW_(delete) (homotype, noexcept=default)
		XTAL_NEW_(create) (homotype, noexcept=default)
	
		XTAL_NEW_(implicit)    homotype(homotype                   const  &t) noexcept(_std::is_nothrow_copy_constructible_v<value_type>) requires _std::copy_constructible<value_type> and in_v<_xtd::trivially_copyable<value_type>> = default;
		XTAL_NEW_(implicit)    homotype(homotype                         &&t) noexcept(_std::is_nothrow_move_constructible_v<value_type>) requires _std::move_constructible<value_type> and in_v<_xtd::trivially_movable <value_type>> = default;

		XTAL_NEW_(implicit)    homotype(_std::initializer_list<value_type> t) noexcept(_std::is_nothrow_copy_constructible_v<value_type>)                                                                                              : homotype(                 t.begin() ,                  t.end() ) {}
		XTAL_NEW_(implicit)    homotype(homotype                   const  &t) noexcept(_std::is_nothrow_copy_constructible_v<value_type>) requires _std::copy_constructible<value_type> and un_v<_xtd::trivially_copyable<value_type>> : homotype(                 t.begin() ,                  t.end() ) {}
		XTAL_NEW_(implicit)    homotype(homotype                         &&t) noexcept(_std::is_nothrow_move_constructible_v<value_type>) requires _std::move_constructible<value_type> and un_v<_xtd::trivially_movable <value_type>> : homotype(_detail::move_it(t.begin()), _detail::move_it(t.end())) {}

		XTAL_DEF_(inline,let)    assign(_std::initializer_list<value_type> t) noexcept(_std::is_nothrow_copy_assignable_v   <value_type>) -> void {assign(                 t.begin() ,                  t.end() );}
		XTAL_DEF_(inline,let)    assign(homotype                   const  &t) noexcept(_std::is_nothrow_copy_assignable_v   <value_type>) -> void {assign(                 t.begin() ,                  t.end() );}
		XTAL_DEF_(inline,let)    assign(homotype                         &&t) noexcept(_std::is_nothrow_move_assignable_v   <value_type>) -> void {assign(_detail::move_it(t.begin()), _detail::move_it(t.end()));}

		XTAL_DEF_(inline,let) operator=(_std::initializer_list<value_type> t) noexcept(_std::is_nothrow_copy_assignable_v   <value_type>) -> homotype & {assign(XTAL_REF_(t)); return *this;}
		XTAL_DEF_(inline,let) operator=(homotype                   const  &t) noexcept(_std::is_nothrow_copy_assignable_v   <value_type>) -> homotype & {assign(XTAL_REF_(t)); return *this;}
		XTAL_DEF_(inline,let) operator=(homotype                         &&t) noexcept(_std::is_nothrow_move_assignable_v   <value_type>) -> homotype & {assign(XTAL_MOV_(t)); return *this;}

		template <class J> requires epimorphic_q<iterator, J> XTAL_NEW_(explicit) homotype(J j0, J jN) noexcept         {         push_back(j0, jN);}
		template <class J> requires epimorphic_q<iterator, J> XTAL_DEF_(inline,let) assign(J j0, J jN) noexcept -> void {clear(); push_back(j0, jN);}

		XTAL_NEW_(explicit)
		homotype(size_type sN, auto &&...etc)
		noexcept
		{
			insert_back(sN, XTAL_REF_(etc)...);
		}
		XTAL_DEF_(inline,let)
		assign(size_type sN, U_data const &u)
		noexcept -> void
		{
			_detail::fill_with(+m_data, sN, XTAL_REF_(u));
		}
		XTAL_DEF_(inline,let)
		swap(homotype &t)
		noexcept -> void
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
			insert(cend(), i0, iN);
		}

		XTAL_DEF_(inline,let)
		push_back(_std::initializer_list<value_type> w)
		noexcept(false) -> void
		{
			push_back(w.begin(), w.end());
		}

		XTAL_DEF_(inline,let)
		push_back(make_q<U_data> auto &&...vs)
		noexcept(false) -> void
		{
			push_back(_std::initializer_list<value_type>{U_data(XTAL_REF_(vs))...});
		}
		/*!
		\brief  	Constructs an element at the end of `this` using the given arguments.
		\brief  	A reference to the element.
		*/
		XTAL_DEF_(inline,let)
		emplace_back(auto &&...oo)
		noexcept(false) -> reference
		{
			return *inplace_back(XTAL_REF_(oo)...);
		}
		/*!
		\brief  	Invokes `insert` at `this->end()` with the given arguments.
		*/
		XTAL_DEF_(inline,let)
		insert_back(auto &&...oo)
		noexcept(false) -> iterator
		{
			return insert(end(), XTAL_REF_(oo)...);
		}

		/*!
		\brief  	Constructs an element at `i` using the given arguments.
		\brief  	An iterator at the `emplace`d element.
		*/

		XTAL_DEF_(inline,let)
		emplace(const_iterator i, auto &&...oo)
		noexcept(false) -> iterator
		{
			return inplace(i, XTAL_REF_(oo)...);
		}

		/*!
		\brief  	Inserts the values delimited by `j0` and `jN` beginning at `i`.
		*/
		template <iterator_q J>
		XTAL_DEF_(inline,let)
		insert(const_iterator i0, J j0, J jN)
		noexcept(false) -> iterator
		{
			return insert_(modify_f(i0), j0, jN);
		}
		template <iterator_q J>
		XTAL_DEF_(inline,let)
		insert_(iterator i0, J j0, J jN)
		noexcept(false) -> iterator
		{
			return insert_(i0, j0, _std::distance(j0, jN));
		}
		template <iterator_q J>
		XTAL_DEF_(inline,let)
		insert_(iterator i0, J j0, size_type sN)
		noexcept(false) -> iterator
		{
			auto iN  = end();
			auto iN_ = offence_f(iN);
			auto i0_ = offence_f(i0);
			XTAL_IF0
			XTAL_0IF (submolecular_q<value_type> and same_q<iterator, J>) {
				deserve(sN, i0); _std::memcpy(i0_, offence_f(j0), value_size_*sN);
			}
			XTAL_0IF (not _xtd::trivially_constructible<value_type>) {
				for (; sN--; ++j0) {
					emplace_back(*j0);
				}
				_detail::swap_to(i0_, iN_, offence_f(end()));
			}
			XTAL_0IF_(else) {
				deserve(sN, i0); _detail::copy_to(i0, j0, sN);
			}
			return i0;
		}
		/*!
		\brief  	Inserts the values `w` beginning at `i`.
		*/
		XTAL_DEF_(inline,let)
		insert(const_iterator i, _std::initializer_list<value_type> w)
		noexcept(false) -> iterator
		{
			return insert(i, w.begin(), w.end());
		}
		/*!
		\brief  	Inserts the value `v` at `i`.
		*/
		XTAL_DEF_(inline,let)
		insert(const_iterator i, common_q<U_data> auto &&u)
		noexcept(false) -> iterator
		{
			return inplace(i, XTAL_REF_(u));
		}
		/*!
		\brief  	Initialises `sN` values with `u` beginning at `i`.
		*/
		XTAL_DEF_(inline,let)
		insert(const_iterator i, size_type sN, common_q<U_data> auto &&u)
		noexcept(false) -> iterator
		{
			deserve(sN, i);
			_std::uninitialized_fill_n(offence_f(i), sN, XTAL_REF_(u));
			return i;
		}
		/*!
		\brief  	Initialises `sN` values beginning at `i`.
		*/
		XTAL_DEF_(inline,let)
		insert(const_iterator i0, size_type sN)
		noexcept(false) -> iterator
		{
			return insert_(modify_f(i0), sN);
		}
		XTAL_DEF_(inline,let)
		insert_(iterator i0, size_type sN)
		noexcept(false) -> iterator
		{
			deserve(sN, i0);
			_std::uninitialized_value_construct_n(offence_f(i0), sN);
			return i0;
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
		inplace(const_iterator i0, auto &&...oo)
		noexcept(false) -> iterator
		{
			return inplace_(modify_f(i0), XTAL_REF_(oo)...);
		}
		XTAL_DEF_(inline,let)
		inplace_(iterator i0, auto &&...oo)
		noexcept(false) -> iterator
		{
			deserve(1, i0);
			return (iterator) ::new(offence_f(i0)) value_type(XTAL_REF_(oo)...);
		}


	public:// DEALLOCATION
		/*!
		\brief  	Removes the last element from `this`.
		*/
		XTAL_DEF_(inline,let)
		pop_back()
		noexcept(false) -> void
		{
			pop_back(1);
		}
		/*!
		\brief  	Removes the last `sN` elements from `this`.
		*/
		XTAL_DEF_(inline,let)
		pop_back(size_type sN)
		noexcept(false) -> void
		{
			erase(_std::prev(end(), sN), end(), sN);
		}
		/*!
		\brief  	Deletes all elements.
		*/
		XTAL_DEF_(inline,let)
		clear()
		noexcept -> void
		{
			erase(begin(), end());
		}
		/*!
		\brief  	Deletes the element at `i0`.
		*/
		XTAL_DEF_(inline,let)
		erase(const_iterator i0)
		noexcept -> decltype(auto)
		{
			return erase(i0, 1);
		}
		/*!
		\brief  	Deletes `sN` elements starting from `i0`.
		*/
		XTAL_DEF_(inline,let)
		erase(const_iterator i0, size_type sN)
		noexcept -> decltype(auto)
		{
			return erase(i0, _std::next(i0, sN), sN);
		}
		/*!
		\brief  	Deletes the elements between `i0` and `iN`.
		*/
		XTAL_DEF_(inline,let)
		erase(const_iterator i0, const_iterator iN)
		noexcept -> decltype(auto)
		{
			return erase(i0, iN, _std::distance(i0, iN));
		}
		/*!
		\brief  	Deletes `sN` elements between `i0` and `iN`.
		*/
		/*!
		\note   	Non-standard signature.
		*/
		/*!
		\note   	Currently assumes move-invariance.
		*/
		XTAL_DEF_(inline,let)
		erase(const_iterator i0, const_iterator iN, size_type sN)
		noexcept -> decltype(auto)
		{
			return erase_(modify_f(i0), modify_f(iN), sN);
		}
		XTAL_DEF_(inline,let)
		erase_(iterator i0, iterator iN, size_type sN)
		noexcept -> decltype(auto)
		{
			assert(begin() <= i0 and iN <= end() and _std::distance(i0, iN) == sN);
			if constexpr (_std::destructible<value_type>) {
				_std::destroy(i0, iN);
			}
			auto iZ = end();
			if (iN < iZ) {
				auto sX  = _std::distance(iN, iZ);
				auto i0_ = offence_f(i0);
				auto iN_ = offence_f(iN);
				auto iZ_ = offence_f(iZ);
				XTAL_IF0
				//\
				XTAL_0IF_(do) (_detail::move_to(i0_, iN_,             sX))
				XTAL_0IF_(do) (_std::memmove   (i0_, iN_, value_size_*sX))
				XTAL_0IF_(else) {
					_detail::swap_to(i0_, iN_, iZ_);
				}
			}
			n_data -= sN;
			return i0;
		}

	};
	using type = bond::derive_t<homotype>;

};
/***/

////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
