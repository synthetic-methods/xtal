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

template <class U_data, size_t N_data>
struct superblock<U_data(&)[N_data]>
{
	using supertype = _std::span<U_data, N_data>;
	
	template <class T>
	using holotype = bond::compose_s<supertype, bond::define<T>>;

	template <class T>
	class homotype: public holotype<T>
	{
		using T_ = holotype<T>;

	public:// CONSTRUCT
		using T_::T_;

		/**/
		XTAL_TO4_(XTAL_DEF_(return,inline)
		//\
		XTAL_TN1 twin(), based_t<typename T::template endomorphism_t<based_t<U_data>[N_data]>>(*this))
		XTAL_TN1 twin(), based_t<typename T::template endomorphism_t<based_t<U_data>[N_data]>>{*this})
		/***/

	};	
};
template <class U_data, size_t N_data>
struct superblock<U_data   [N_data]>
{
	using supertype = _std::array<U_data, N_data>;
	
	template <class T>
	using holotype = bond::compose_s<supertype, bond::define<T>>;

	template <class T>
	class homotype: public holotype<T>
	{
		using T_ = holotype<T>;

	public:// CONSTRUCT
	//	using T_::T_;
		
		XTAL_CO0_(homotype)
	//	XTAL_CO1_(homotype)
		XTAL_CO4_(homotype)
		
		XTAL_CXN homotype()
		XTAL_0EX
		:	homotype(size_0)
		{}
		XTAL_CXN homotype(size_t const n)
		XTAL_0EX
		{
			if (_std::is_constant_evaluated() or n < N_data) {
				T_::fill(U_data{});
			}
		}
		XTAL_CON homotype(embrace_t<U_data> a)
		XTAL_0EX
		:	homotype(count_f(XTAL_REF_(a)))
		{
			if constexpr (idempotent_p<U_data, decltype([] XTAL_1FN_(T::coordinate_f))>) {
				_detail::copy_to(T_::begin(), a.begin(), a.end());
			}
			else {
				_detail::copy_to(T_::begin(), a.begin(), a.end(), [] XTAL_1FN_(T::ordinate_f));
			}
		}
		XTAL_CXN homotype(bounded_q auto const &a)
		XTAL_0EX
		:	homotype(count_f(XTAL_REF_(a)))
		{
			if constexpr (idempotent_p<U_data, decltype([] XTAL_1FN_(T::coordinate_f))>) {
				_detail::copy_to(T_::begin(), a);
			}
			else {
				_detail::copy_to(T_::begin(), a, [] XTAL_1FN_(T::ordinate_f));
			}
		}
		XTAL_CXN homotype(bounded_q auto &&a)
		XTAL_0EX
		:	homotype(count_f(a))
		{
			if constexpr (idempotent_p<U_data, decltype([] XTAL_1FN_(T::coordinate_f))>) {
				_detail::move_to(T_::begin(), a);
			}
			else {
				_detail::move_to(T_::begin(), a, [] XTAL_1FN_(T::ordinate_f));
			}
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
		XTAL_LET N_data = _std::       extent_v<based_t<A>>;
		XTAL_USE U_data = _std::remove_extent_t<based_t<A>>;

	public:// CONSTRUCT
		using T_::T_;

	public:// MAP
		XTAL_DEF_(return,inline) XTAL_FN1   ordinate_f(auto &&o) XTAL_0EX {return XTAL_REF_(o);}
		XTAL_DEF_(return,inline) XTAL_FN1 coordinate_f(auto &&o) XTAL_0EX {return XTAL_REF_(o);}

	public:// ACCESS
		using T_::self;
		using T_::twin;
		
		XTAL_DEF_(return,inline)
		XTAL_FN1_(U_sigma) size() XTAL_0EX {return N_data;}


		XTAL_TO4_(template <class F>
		XTAL_DEF_(inline)
		XTAL_OP0_(explicit) F(), got<F>())

		template <class F=decltype(bond::pack_f)>
		XTAL_DEF_(return,inline)
		XTAL_TN1 got()
		XTAL_0FX
		{
			using _std::get;

			return [&]<auto ...Ns> (bond::seek_t<Ns...>)
				XTAL_0FN_(invoke_f<F>(T::coordinate_f(get<Ns>(self()))...))
			(bond::seek_s<N_data>{});
		}
		template <class F>
		XTAL_DEF_(return,inline)
		XTAL_TN1 got(F &&f)
		XTAL_0FX
		XTAL_REQ
		XTAL_REQ_TO_(got<F>())

		XTAL_DEF_(return,inline) XTAL_TN1 got(size_t i) XTAL_0FX {return T::coordinate_f(self().get(i));}
		XTAL_DEF_(return,inline) XTAL_OP1 () (auto &&o) XTAL_0FX {return self().got(XTAL_REF_(o));}
	//	XTAL_DEF_(return,inline) XTAL_OP1 () (        ) XTAL_0FX {return self().got( );}

		XTAL_DEF_(return,inline) XTAL_TN1 get(I_ i) XTAL_0FX_(&&) {return XTAL_MOV_(T_::operator[](i));}
		XTAL_DEF_(return,inline) XTAL_TN1 get(I_ i) XTAL_0FX_( &) {return          (T_::operator[](i));}

		XTAL_DEF_(return,inline) XTAL_TN1 let(I_ i) XTAL_0EX_(&&) {return XTAL_MOV_(T_::operator[](i));}
		XTAL_DEF_(return,inline) XTAL_TN1 let(I_ i) XTAL_0EX_( &) {return          (T_::operator[](i));}

	public:// CONVERSION
		XTAL_TN2 apply(auto &&f)
		XTAL_0FX
		{
			using _std::get;

			return [&, this]<auto ...I>(bond::seek_t<I...>)
				XTAL_0FN_(f(get<I>(*this)...))
			(bond::seek_s<N_data> {});
		}
		template <class F>
		XTAL_TN2 apply()
		XTAL_0EX
		{
			using _std::get;

			return [&, this]<auto ...I>(bond::seek_t<I...>)
				XTAL_0FN_(F(get<I>(*this)...))
			(bond::seek_s<N_data> {});
		}

		///\
		Elementwise immutative transformer. \

		///\todo\
		Map `transact` with `(?:co)?ordinate_f`.

		//\
		XTAL_TO4_(template <array_q W> XTAL_TN1 transact(), transact<W>(invoke_f<devalued_t<W>>))
		XTAL_TO4_(template <array_q W> XTAL_TN1 transact(), transact<W>(invoke_f<typename W::value_type>))
		template <array_q W> XTAL_TN1 transact(_std::invocable<U_data> auto &&f) XTAL_0EX_(&&) {return move_by<W>(XTAL_REF_(f));}
		template <array_q W> XTAL_TN1 transact(_std::invocable<U_data> auto &&f) XTAL_0FX_(&&) {return move_by<W>(XTAL_REF_(f));}
		template <array_q W> XTAL_TN1 transact(_std::invocable<U_data> auto &&f) XTAL_0EX_( &) {return copy_by<W>(XTAL_REF_(f));}
		template <array_q W> XTAL_TN1 transact(_std::invocable<U_data> auto &&f) XTAL_0FX_( &) {return copy_by<W>(XTAL_REF_(f));}
		template <array_q W> XTAL_TN1  move_by(_std::invocable<U_data> auto &&f) XTAL_0EX {based_t<W> w; _detail::move_to(w.begin(), self(), XTAL_REF_(f)); return w;}
		template <array_q W> XTAL_TN1  copy_by(_std::invocable<U_data> auto &&f) XTAL_0FX {based_t<W> w; _detail::copy_to(w.begin(), self(), XTAL_REF_(f)); return w;}

		///\
		Elementwise mutative transformer. \

		XTAL_TN1 transact(_std::invocable<U_data> auto &&...fs)
		XTAL_0EX
		{
			return (transact(XTAL_REF_(fs)), ...);
		}
		XTAL_TN1 transact(_std::invocable<U_data> auto &&f)
		XTAL_0EX
		{
			_detail::apply_to(self(), XTAL_REF_(f));
			return self();
		}
		
	};
	using type = bond::isotype<homotype>;

};

template <size_t I> XTAL_DEF_(return,inline) XTAL_FN1 get(block_q auto const &&o) {return XTAL_MOV_(o).get(I);}
template <size_t I> XTAL_DEF_(return,inline) XTAL_FN1 get(block_q auto const  &o) {return          (o).get(I);}
template <size_t I> XTAL_DEF_(return,inline) XTAL_FN1 get(block_q auto       &&o) {return XTAL_MOV_(o).let(I);}
template <size_t I> XTAL_DEF_(return,inline) XTAL_FN1 get(block_q auto        &o) {return          (o).let(I);}


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
