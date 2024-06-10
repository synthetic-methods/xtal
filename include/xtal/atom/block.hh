#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::atom
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
Defines a fixed-width `type` that supports arithmetic operators. \

template <class ..._s> XTAL_TYP block;
template <class ..._s> XTAL_USE block_t = typename block<_s...>::type;
template <class ..._s> XTAL_ASK block_q = bond::head_tag_p<block_t, _s...>;


namespace _detail
{///////////////////////////////////////////////////////////////////////////////

template <class ..._s>
struct superblock;

template <class U, size_t N>
struct superblock<U(&)[N]>
{
	using supertype = _std::span<U, N>;
	
	template <class T>
	using holotype = bond::compose_s<supertype, bond::define<T>>;

	template <class T>
	class homotype: public holotype<T>
	{
		using T_ = holotype<T>;

	protected:
		XTAL_DEF_(static)
		XTAL_LET N_data = N;
		XTAL_USE U_data = U;

	public:// CONSTRUCT
		using T_::T_;

		XTAL_TO4_(XTAL_DEF_(return,inline)
		XTAL_REF twin(), typename T::template tagged_t<U_data[N_data]>(T_::self()))

	};	
};
template <class U, size_t N>
struct superblock<U[N]>
{
	using supertype = _std::array<U, N>;
	
	template <class T>
	using holotype = bond::compose_s<supertype, bond::define<T>>;

	template <class T>
	class homotype: public holotype<T>
	{
		using T_ = holotype<T>;

	protected:
		XTAL_DEF_(static)
		XTAL_LET N_data = N;
		XTAL_USE U_data = U;

		XTAL_DEF_(return,inline,static)
		XTAL_LET coordinated()
		XTAL_0EX -> bool
		{
			return is_q<XTAL_TYP_(XTAL_ANY_(T).coordinate(XTAL_ANY_(U_data))), U_data>;
		}

	public:// CONSTRUCT
	//	using T_::T_;
		
		XTAL_CO0_(homotype)
	//	XTAL_CO1_(homotype)
		XTAL_CO4_(homotype)
		
		XTAL_CON_(explicit) homotype()
		XTAL_0EX
		:	homotype(size_0)
		{}
		XTAL_CON_(explicit) homotype(size_t const n)
		XTAL_0EX
		{
			if (_std::is_constant_evaluated() or n < N_data) {
				T_::fill(U_data{});
			}
		}
		XTAL_CON_(implicit) homotype(embrace_t<U_data> a)
		XTAL_0EX
		:	homotype(count_f(XTAL_REF_(a)))
		{
			XTAL_IF0
			XTAL_0IF (    coordinated()) {_detail::copy_to(T_::begin(), a.begin(), a.end());}
			XTAL_0IF (not coordinated()) {_detail::copy_to(T_::begin(), a.begin(), a.end(), [this] XTAL_1FN_(T_::self().ordinate));}
		}
		XTAL_CON_(explicit) homotype(bounded_q auto const &a)
		XTAL_0EX
		:	homotype(count_f(XTAL_REF_(a)))
		{
			XTAL_IF0
			XTAL_0IF (    coordinated()) {_detail::copy_to(T_::begin(), a);}
			XTAL_0IF (not coordinated()) {_detail::copy_to(T_::begin(), a, [this] XTAL_1FN_(T_::self().ordinate));}
		}
		XTAL_CON_(explicit) homotype(bounded_q auto &&a)
		XTAL_0EX
		:	homotype(count_f(a))
		{
			XTAL_IF0
			XTAL_0IF (    coordinated()) {_detail::move_to(T_::begin(), a);}
			XTAL_0IF (not coordinated()) {_detail::move_to(T_::begin(), a, [this] XTAL_1FN_(T_::self().ordinate));}
		}

	};
};


}///////////////////////////////////////////////////////////////////////////////

template <class U, size_t N, size_t ...Ns>
struct block<U[N][Ns]...> : block<block_t<U[N]>[Ns]...>
{
};
template <column_q A>
struct block<A>
{
	using _op = bond::operate<A>;
	using U_sigma = typename _op::sigma_t;
	using U_delta = typename _op::delta_t;
	
	template <class T>
	using allotype = typename _detail::superblock<A>::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<allotype<T>, bond::tag<block_t>>;

	template <class T>
	class homotype : public holotype<T>
	{
		friend T;
		using  T_ = holotype<T>;
		using  I_ = typename T_::difference_type;

	protected:
		using          T_::N_data;
		using typename T_::U_data;
		using U_size = typename T_::size_type;

	public:// CONSTRUCT
		using T_::T_;

	public:// MAP
		XTAL_DEF_(return,inline,static) XTAL_REF   ordinate(auto &&o) XTAL_0EX {return XTAL_REF_(o);}
		XTAL_DEF_(return,inline,static) XTAL_REF coordinate(auto &&o) XTAL_0EX {return XTAL_REF_(o);}

	public:// ACCESS
		using T_::self;
		using T_::twin;
		
		XTAL_DEF_(return,inline,static)
		XTAL_LET size()
		XTAL_0EX
		{
			return static_cast<U_size>(N_data);
		}

		XTAL_DEF_(return,inline)
		XTAL_REF operator () (I_ i)
		XTAL_0FX
		{
			return self().coordinate(self().let(i));
		}
		XTAL_TO4_(
		XTAL_DEF_(return,inline)
		XTAL_REF let(I_ i), self().operator[](i)
		)
		XTAL_TO4_(template <I_ I>
		XTAL_DEF_(return,inline)
		XTAL_REF let(), get<I>(self())
		)

	public:// OPERATE
		XTAL_TO4_(template <class F>
		XTAL_DEF_(inline)
		XTAL_CVN_(explicit) F(), apply<F>()
		)
		template <class F=decltype(bond::pack_f)>
		XTAL_DEF_(return,inline)
		XTAL_REF apply()
		XTAL_0FX
		{
			return apply(invoke_f<F>);
		}
		template <class F>
		XTAL_DEF_(return,inline)
		XTAL_REF apply(F &&f)
		XTAL_0FX
		{
			return [&, this]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN_(f(self().coordinate(get<I>(self()))...))
			(bond::seek_s<N_data>{});
		}

		///\todo\
		Map `transact` with `(?:co)?ordinate`? \

		///\
		Elementwise immutative transformer. \

		//\
		XTAL_TO4_(template <array_q W> XTAL_DEF_(inline) XTAL_REF transact(), transact<W>(invoke_f<devalued_t<W>>))
		XTAL_TO4_(template <array_q W> XTAL_DEF_(inline) XTAL_REF transact(), transact<W>(invoke_f<typename W::value_type>))
		template <array_q W> XTAL_DEF_(inline) XTAL_REF transact(_std::invocable<U_data> auto &&f) XTAL_0EX_(&&) {return move_by<W>(XTAL_REF_(f));}
		template <array_q W> XTAL_DEF_(inline) XTAL_REF transact(_std::invocable<U_data> auto &&f) XTAL_0FX_(&&) {return move_by<W>(XTAL_REF_(f));}
		template <array_q W> XTAL_DEF_(inline) XTAL_REF transact(_std::invocable<U_data> auto &&f) XTAL_0EX_( &) {return copy_by<W>(XTAL_REF_(f));}
		template <array_q W> XTAL_DEF_(inline) XTAL_REF transact(_std::invocable<U_data> auto &&f) XTAL_0FX_( &) {return copy_by<W>(XTAL_REF_(f));}
		template <array_q W> XTAL_DEF_(inline) XTAL_REF  move_by(_std::invocable<U_data> auto &&f) XTAL_0EX {based_t<W> w; _detail::move_to(w.begin(), self(), XTAL_REF_(f)); return w;}
		template <array_q W> XTAL_DEF_(inline) XTAL_REF  copy_by(_std::invocable<U_data> auto &&f) XTAL_0FX {based_t<W> w; _detail::copy_to(w.begin(), self(), XTAL_REF_(f)); return w;}
		///\
		Elementwise mutative transformer. \

		XTAL_DEF_(inline)
		XTAL_REF transact(_std::invocable<U_data> auto &&...fs)
		XTAL_0EX
		{
			return (transact(XTAL_REF_(fs)), ...);
		}
		XTAL_DEF_(inline)
		XTAL_REF transact(_std::invocable<U_data> auto &&f)
		XTAL_0EX
		{
			_detail::apply_to(self(), XTAL_REF_(f));
			return self();
		}
		
	};
	using type = bond::isotype<homotype>;

};

template <size_t I> XTAL_DEF_(return,inline,static) XTAL_REF get(block_q auto const &&o) {return XTAL_MOV_(o).let(I);}
template <size_t I> XTAL_DEF_(return,inline,static) XTAL_REF get(block_q auto const  &o) {return          (o).let(I);}
template <size_t I> XTAL_DEF_(return,inline,static) XTAL_REF get(block_q auto       &&o) {return XTAL_MOV_(o).let(I);}
template <size_t I> XTAL_DEF_(return,inline,static) XTAL_REF get(block_q auto        &o) {return          (o).let(I);}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
/**/
namespace std
{///////////////////////////////////////////////////////////////////////////////

template <xtal::atom::block_q T>
struct tuple_size<T> : integral_constant<size_t, T::size()> {};

template <size_t N_datum, xtal::atom::block_q T>
struct tuple_element<N_datum, T> {using type = typename T::value_type;};


}/////////////////////////////////////////////////////////////////////////////
/***/
XTAL_ENV_(pop)
