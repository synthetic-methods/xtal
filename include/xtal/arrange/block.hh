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
template <class ..._s> concept  block_q = bond::any_tag_p<block_t, _s...>;


namespace _detail
{///////////////////////////////////////////////////////////////////////////////

template <class ..._s>
struct superblock;

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

		XTAL_TO4_(XTAL_DEF_(short)
		XTAL_LET twin(), typename T::template tagged_t<U_data[N_data]>(S_::self()))

	};	
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

	public:// CONSTRUCT
	//	using S_::S_;
		
	~	homotype() noexcept=default;
	//	homotype() noexcept=default;

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
		XTAL_NEW_(implicit) homotype(_std::initializer_list<U_data> a)
		noexcept
		:	homotype(count_f(XTAL_REF_(a)))
		{
			XTAL_IF0
			XTAL_0IF (    correlated_q<T>) {_detail::move_to(S_::begin(), a);}
			XTAL_0IF (not correlated_q<T>) {_detail::move_to(S_::begin(), a, [this] XTAL_1FN_(T::ordinate));}
		}
		XTAL_NEW_(explicit) homotype(iterable_q auto       &&a)
		noexcept
		:	homotype(count_f(a))
		{
			XTAL_IF0
			XTAL_0IF (    correlated_q<T>) {_detail::move_to(S_::begin(), a);}
			XTAL_0IF (not correlated_q<T>) {_detail::move_to(S_::begin(), a, [this] XTAL_1FN_(T::ordinate));}
		}
		XTAL_NEW_(explicit) homotype(iterable_q auto const  &a)
		noexcept
		:	homotype(count_f(XTAL_REF_(a)))
		{
			XTAL_IF0
			XTAL_0IF (    correlated_q<T>) {_detail::copy_to(S_::begin(), a);}
			XTAL_0IF (not correlated_q<T>) {_detail::copy_to(S_::begin(), a, [this] XTAL_1FN_(T::ordinate));}
		}

	};
};


}///////////////////////////////////////////////////////////////////////////////

template <class U, size_type N, size_type ...Ns>
struct block<U[N][Ns]...> : block<block_t<U[N]>[Ns]...>
{
};
template <column_q A>
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
			using X = typename T::template tagged_t<U_data   [n_data]> &;
			using Y = typename T::template tagged_t<U_data(&)[n_data]>  ;
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
			using X = typename T::template tagged_t<U_data   [n_data]> const &;
			using Y = typename T::template tagged_t<U_data(&)[n_data]> const  ;
			//\
			return reinterpret_cast<X>(*this);
			return Y(*this);
		}

		template <size_type I>
		XTAL_DEF_(short)
		XTAL_LET operator () () const
		noexcept -> decltype(auto)
		{
			return self().coordinate(let<I>());
		}
		XTAL_DEF_(short)
		XTAL_LET operator () (I_ i) const
		noexcept -> decltype(auto)
		{
			return self().coordinate(let(i));
		}
		
		XTAL_DO4_(template <I_ I>
		XTAL_DEF_(short)
		XTAL_LET let(),
		noexcept -> decltype(auto)
		{
			using archetype = typename _detail::superblock<A>::archetype;
			XTAL_IF0
			XTAL_0IF XTAL_TRY_TO_(get<I>(S_::template self<archetype>()))
			XTAL_0IF XTAL_TRY_TO_(let(I))
		})
		XTAL_DO4_(template <I_ I=0>
		XTAL_DEF_(short)
		XTAL_LET let(I_ i),
		noexcept -> decltype(auto)
		{
			XTAL_IF0
			XTAL_0IF (I == 0) {return self().operator[](I + i);}
			XTAL_0IF (I != 0) {return self().operator[](    i);}
		})

	public:// OPERATE
		XTAL_TO4_(template <complete_q F>
		XTAL_DEF_(explicit operator) F(), apply<F>())

		template <class F=XTAL_FUN_(bond::pack_f)>
		XTAL_DEF_(short)
		XTAL_LET apply() const
		noexcept -> decltype(auto)
		{
			return apply(invoke_f<F>);
		}
		template <class F>
		XTAL_DEF_(short)
		XTAL_LET apply(F &&f) const
		noexcept -> decltype(auto)
		{
			return [&, this]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN_(f(self().coordinate(get<I>(self()))...))
			(bond::seek_s<N_data>{});
		}

		///\todo\
		Map `transact` with `(?:co)?ordinate`? \

		///\
		Elementwise immutative transformer. \

		XTAL_TO4_(template <array_q W>
		XTAL_DEF_(alias) transact(), transact<W>(invoke_f<valued_u<W>>))

		template <array_q W> XTAL_DEF_(inline) XTAL_LET transact(_std::invocable<U_data> auto &&f)       &&noexcept -> W&& {return move_by<W>(XTAL_REF_(f));}
		template <array_q W> XTAL_DEF_(inline) XTAL_LET transact(_std::invocable<U_data> auto &&f) const &&noexcept -> W&& {return move_by<W>(XTAL_REF_(f));}
		template <array_q W> XTAL_DEF_(inline) XTAL_LET transact(_std::invocable<U_data> auto &&f)        &noexcept -> W&& {return copy_by<W>(XTAL_REF_(f));}
		template <array_q W> XTAL_DEF_(inline) XTAL_LET transact(_std::invocable<U_data> auto &&f) const  &noexcept -> W&& {return copy_by<W>(XTAL_REF_(f));}
		
		template <array_q W> XTAL_DEF_(inline) XTAL_LET  move_by(_std::invocable<U_data> auto &&f)         noexcept -> W&& {W w; _detail::move_to(w.begin(), self(), XTAL_REF_(f)); return XTAL_MOV_(w);}
		template <array_q W> XTAL_DEF_(inline) XTAL_LET  copy_by(_std::invocable<U_data> auto &&f) const   noexcept -> W&& {W w; _detail::copy_to(w.begin(), self(), XTAL_REF_(f)); return XTAL_MOV_(w);}
		///\
		Elementwise mutative transformer. \

		XTAL_DEF_(inline)
		XTAL_LET transact(_std::invocable<U_data> auto &&...fs)
		noexcept -> decltype(auto)
		{
			return (transact(XTAL_REF_(fs)), ...);
		}
		XTAL_DEF_(inline)
		XTAL_LET transact(_std::invocable<U_data> auto &&f)
		noexcept -> decltype(auto)
		{
			_detail::apply_to(self(), XTAL_REF_(f));
			return self();
		}
		
	};
	using type = bond::isotype<homotype>;

};

template <size_type I> XTAL_DEF_(short,static) XTAL_LET get(block_q auto const &&o) -> decltype(auto) {return XTAL_MOV_(o).template let<I>();}
template <size_type I> XTAL_DEF_(short,static) XTAL_LET get(block_q auto const  &o) -> decltype(auto) {return           o .template let<I>();}
template <size_type I> XTAL_DEF_(short,static) XTAL_LET get(block_q auto       &&o) -> decltype(auto) {return XTAL_MOV_(o).template let<I>();}
template <size_type I> XTAL_DEF_(short,static) XTAL_LET get(block_q auto        &o) -> decltype(auto) {return           o .template let<I>();}


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
