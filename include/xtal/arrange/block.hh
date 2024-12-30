#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::arrange
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
Defines a fixed-width `type` that supports arithmetic operators. \

template <class ..._s> struct   block;
template <class ..._s> using    block_t = typename block<_s...>::type;
template <class ..._s> concept  block_q = bond::tag_p<block_t, _s...>;


namespace _detail
{///////////////////////////////////////////////////////////////////////////////

template <class ..._s> struct   superblock;
template <class ..._s> using    superblock_t = typename superblock<_s...>::type;

template <class U, size_type N>
struct superblock<U(&)[N]>
{
	using archetype = _std::span<U, N>;
	
	template <class T>
	using holotype = bond::compose_s<archetype, bond::define<T>>;

	template <class T>
	class homotype: public holotype<T>
	{
		using S_ = holotype<T>;

	protected:
		XTAL_SET N_data = N;
		using    U_data = U;

	public:// CONSTRUCT
		using S_::S_;

		XTAL_TO4_(XTAL_DEF_(let) base(), S_::template self<archetype>())

		template <class V_data=U_data>
		XTAL_DEF_(short)
		XTAL_LET twin() const
		noexcept -> decltype(auto)
		{
			return typename T::taboo::template ectotype<V_data[N_data]>(S_::self());
		}

	};	
	using type = bond::isotype<homotype>;

};
template <class U, size_type N>
struct superblock<U[N]>
{
	using archetype = _std::array<U, N>;
	
	template <class T>
	using holotype = bond::compose_s<archetype, bond::define<T>>;

	template <class T>
	class homotype: public holotype<T>
	{
		using S_ = holotype<T>;

	protected:
		XTAL_SET N_data = N;
		using    U_data = U;

	public:// ACCESS
		XTAL_TO4_(XTAL_DEF_(let) base(), S_::template self<archetype>())

		template <class V_data=void>
		XTAL_DEF_(short)
		XTAL_LET twin() const
		noexcept -> decltype(auto)
		{
			if constexpr (incomplete_q<V_data>) {
				return S_::twin();
			}
			else {
				return typename T::taboo::template ectotype<V_data[N_data]>(S_::self());
			}
		}

	public:// CONSTRUCT
		using S_::S_;
	~	homotype()                noexcept=default;
	//	homotype()                noexcept=default;
		XTAL_NEW_(copy, homotype, noexcept=default)
		XTAL_NEW_(move, homotype, noexcept=default)
		
		XTAL_NEW_(explicit) homotype()
		noexcept
		:	homotype(size_0)
		{}
		XTAL_NEW_(explicit) homotype(size_type const n)
		noexcept
		{
			assert(n <= N_data);
			if (_std::is_constant_evaluated() or n < N_data) {
				S_::fill(U_data{});
			}
		}
	//	TODO: Should check `coindexed_q`? Or how to determine if `ordinate` has been replaced?

		XTAL_NEW_(implicit) homotype(_std::initializer_list<U_data> a)
		noexcept
		:	homotype(count_f(XTAL_REF_(a)))
		{
			XTAL_IF0
			XTAL_0IF (covalued_q<T>) {_detail::move_to<XTAL_FUN_(T::ordinate)>(S_::begin(), a);}
			XTAL_0IF_(else)          {_detail::move_to                        (S_::begin(), a);}
		}
		XTAL_NEW_(explicit) homotype(iterable_q auto       &&a)
		noexcept
		:	homotype(count_f(a))
		{
			XTAL_IF0
			XTAL_0IF (covalued_q<T>) {_detail::move_to<XTAL_FUN_(T::ordinate)>(S_::begin(), a);}
			XTAL_0IF_(else)          {_detail::move_to                        (S_::begin(), a);}
		}
		XTAL_NEW_(explicit) homotype(iterable_q auto const  &a)
		noexcept
		:	homotype(count_f(XTAL_REF_(a)))
		{
			XTAL_IF0
			XTAL_0IF (covalued_q<T>) {_detail::copy_to<XTAL_FUN_(T::ordinate)>(S_::begin(), a);}
			XTAL_0IF_(else)          {_detail::copy_to                        (S_::begin(), a);}
		}

	};
	using type = bond::isotype<homotype>;

};


}///////////////////////////////////////////////////////////////////////////////

template <class U, unsigned N, unsigned ...Ns> requires (1 <= sizeof...(Ns)) struct block<U   [N][Ns]...> : block<block_t<U[N]>   [Ns]...> {};
template <class U, unsigned N, unsigned ...Ns> requires (1 <= sizeof...(Ns)) struct block<U(&)[N][Ns]...> : block<block_t<U[N]>(&)[Ns]...> {};

template <vector_q A>
struct block<A>
{
	using _op = bond::operate<A>;
	
	template <class T>
	using endotype = typename _detail::superblock<A>::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<endotype<T>, bond::tag<block_t>>;

	template <class T>
	class homotype : public holotype<T>
	{
		using  S_ = holotype<T>;
		using  I_ = typename S_::difference_type;

	protected:
		using          S_::N_data;
		using typename S_::U_data;
		using U_size = typename S_::size_type;
		using initializer_list = _std::initializer_list<U_data>;

		static constexpr _detail::superblock_t<U_data[N_data]> zeroed_{};

	public:// CONSTRUCT
		using S_::S_;

	public:// MAP
		XTAL_DEF_(short,static) XTAL_LET   ordinate(auto &&o) noexcept -> decltype(auto) {return XTAL_REF_(o);}
		XTAL_DEF_(short,static) XTAL_LET coordinate(auto &&o) noexcept -> decltype(auto) {return XTAL_REF_(o);}

	public:// ACCESS
		using S_::self;
		using S_::twin;
		
		XTAL_DEF_(short,static)
		XTAL_LET size()
		noexcept -> auto
		{
			return static_cast<U_size>(N_data);
		}
		template <U_size n_data>
		XTAL_DEF_(short)
		XTAL_LET capsize()
		noexcept -> auto
		{
			static_assert(n_data <= N_data);
			using X = typename T::taboo::template ectotype<U_data   [n_data]> &;
			using Y = typename T::taboo::template ectotype<U_data(&)[n_data]>  ;
			//\
			return reinterpret_cast<X>(*this);
			return Y(*this);
		}
		template <U_size n_data>
		XTAL_DEF_(short)
		XTAL_LET capsize() const
		noexcept -> auto
		{
			static_assert(n_data <= N_data);
			using X = typename T::taboo::template ectotype<U_data   [n_data]> const &;
			using Y = typename T::taboo::template ectotype<U_data(&)[n_data]> const  ;
			//\
			return reinterpret_cast<X>(*this);
			return Y(*this);
		}

		template <size_type I>
		XTAL_DEF_(let) operator () (    ) const noexcept {return self().coordinate(element<I>());}
		XTAL_DEF_(let) operator () (I_ i) const noexcept {return self().coordinate(element(i)  );}
		
		XTAL_DO4_(template <I_ I>
		XTAL_DEF_(short)
		XTAL_LET element(),
		noexcept -> decltype(auto)
		{
			using archetype = typename _detail::superblock<A>::archetype;
			XTAL_IF0
			XTAL_0IF XTAL_TRY_TO_(get<I>(S_::template self<archetype>()))
			XTAL_0IF XTAL_TRY_TO_(element(I))
		})
		XTAL_DO4_(template <I_ I=0>
		XTAL_DEF_(short)
		XTAL_LET element(I_ i),
		noexcept -> decltype(auto)
		{
			XTAL_IF0
			XTAL_0IF (I == 0) {return self().operator[](I + i);}
			XTAL_0IF (I != 0) {return self().operator[](    i);}
		})

	public:// OPERATE
		XTAL_DEF_(alias)   zeroed() const noexcept {return 0 == memcmp(S_::data(), zeroed_.data(), sizeof(*this));}
		XTAL_DEF_(alias) unzeroed() const noexcept {return 0 != memcmp(S_::data(), zeroed_.data(), sizeof(*this));}

		XTAL_TO4_(template <complete_q F>
		XTAL_DEF_(explicit operator) F(), apply(invoke_f<F>))

		template <auto f=XTAL_FUN_(bond::pack_f)>
		XTAL_DEF_(short)
		XTAL_LET apply() const
		noexcept -> decltype(auto)
		{
			return apply(f);
		}
		XTAL_DEF_(short)
		XTAL_LET apply(auto &&f) const
		noexcept -> decltype(auto)
		{
			return [this, f=XTAL_REF_(f)]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN_(f(self() (I)...))
			(bond::seek_s<N_data>{});
		}

		template <auto f>
		XTAL_DEF_(short,static)
		XTAL_LET map_f(auto &&...ts)
		noexcept -> decltype(auto)
		{
			return [f_ = [&] (auto i)
				XTAL_0FN_(f([&] (auto const &t)
					XTAL_0FN {if constexpr (same_q<decltype(t), T>) {return t(i);} else {return t;}}
				(ts)...))
			]<auto ...I> (bond::seek_t<I...>) XTAL_0FN_(T{f_(I)...}) (bond::seek_s<N_data>{});
		}

		///\todo\
		Define in-place `map` via `(?:co)?ordinate`? \

	};
	using type = bond::isotype<homotype>;

};
/*/
template <size_type I> XTAL_DEF_(let) get(block_q auto const &&o) noexcept {return _std::get<I>(XTAL_MOV_(o).base());}
template <size_type I> XTAL_DEF_(let) get(block_q auto       &&o) noexcept {return _std::get<I>(XTAL_MOV_(o).base());}
template <size_type I> XTAL_DEF_(let) get(block_q auto const  &o) noexcept {return _std::get<I>(XTAL_REF_(o).base());}
template <size_type I> XTAL_DEF_(let) get(block_q auto        &o) noexcept {return _std::get<I>(XTAL_REF_(o).base());}
/*/
template <size_type I> XTAL_DEF_(let) get(block_q auto const &&o) noexcept {return XTAL_MOV_(o)[I];}
template <size_type I> XTAL_DEF_(let) get(block_q auto       &&o) noexcept {return XTAL_MOV_(o)[I];}
template <size_type I> XTAL_DEF_(let) get(block_q auto const  &o) noexcept {return XTAL_REF_(o)[I];}
template <size_type I> XTAL_DEF_(let) get(block_q auto        &o) noexcept {return XTAL_REF_(o)[I];}
/***/


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
/**/
namespace std
{///////////////////////////////////////////////////////////////////////////////

template <xtal::arrange::block_q T>
struct tuple_size<T> : integral_constant<size_t, T::size()> {};

template <size_t N_datum, xtal::arrange::block_q T>
struct tuple_element<N_datum, T> {using type = typename T::value_type;};


}/////////////////////////////////////////////////////////////////////////////
/***/
XTAL_ENV_(pop)
