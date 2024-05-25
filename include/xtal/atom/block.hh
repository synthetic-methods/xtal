#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::atom
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class ..._s> XTAL_TYP block;
template <class ..._s> XTAL_USE block_t = typename block<_s...>::type;
template <class ..._s> XTAL_ASK block_q = bond::tag_p<block, _s...>;

XTAL_LET  block_f = []<class ...Xs> (Xs &&...xs)
XTAL_0FN_(block_t<common_t<Xs...>[sizeof...(Xs)]>{XTAL_REF_(xs)...});


////////////////////////////////////////////////////////////////////////////////
///\
Defines a fixed-width `type` that supports arithmetic operators. \

///\todo\
Specialize for SIMDe types. \

///\todo\
Adapt `_detail::apply_to` etc to execute in parallel using SIMDE? \


template <class U, size_t N, int Ns>
struct block<U[N][Ns]> : block<block_t<U[N]>[Ns]>
{};
/*/
template <class U_data, size_t N_data>
struct block<U_data(&)[N_data]>
{
///\todo Adapt as array-of-references using `...member_f` (or uniform `std::tuple`s)? \

};
/***/
template <class U_data, size_t N_data>
struct block<U_data[N_data]>
{
	using op = bond::operate<U_data>;
	
	template <class T>
	using allotype = bond::compose_s<_std::array<U_data, N_data>, bond::define<T>>;

	template <class T>
	using holotype = bond::compose_s<allotype<T>, bond::tag<block>>;

	template <class T>
	class homotype : public holotype<T>
	{
		friend T;
		using  T_ = holotype<T>;
		using  I_ = typename T_::difference_type;

	public:// ACCESS
		using T_::self;
		using T_::twin;
		XTAL_FN2_(typename op::sigma_t) size()
		XTAL_0EX {return N_data;}


		XTAL_FN2   ordinate(auto &&u) XTAL_0EX {return XTAL_REF_(u);}
		XTAL_FN2 coordinate(auto &&u) XTAL_0EX {return XTAL_REF_(u);}

		//\
		template <auto T_f=block_f, class ...Ts>
		template <auto T_f=bond::pack_f, class ...Ts>
		XTAL_TN2 got()
		XTAL_0FX
		{
			return [&]<auto ...Ns> (bond::seek_t<Ns...>)
				XTAL_0FN_(T_f(T::coordinate(bond::pack_item_f<Ns>(self()))...))
			(bond::seek_s<N_data>{});
		};
		XTAL_TN2 got(size_t i) XTAL_0FX {return T::coordinate(self().get(i));}
	//	XTAL_OP2 () (size_t i) XTAL_0FX {return self().got(i);}
	//	XTAL_OP2 () (        ) XTAL_0FX {return self().got( );}

		XTAL_TN2 get(I_ i) XTAL_0FX_(&&) {return XTAL_MOV_(T_::operator[](i));}
		XTAL_TN2 get(I_ i) XTAL_0FX_( &) {return          (T_::operator[](i));}

		XTAL_TN2 let(I_ i) XTAL_0EX_(&&) {return XTAL_MOV_(T_::operator[](i));}
		XTAL_TN2 let(I_ i) XTAL_0EX_( &) {return          (T_::operator[](i));}

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

		//\
		XTAL_TO4_(template <array_q W> XTAL_TN1 transact(), transact<W>(make_f<devalue_u<W>>))
		XTAL_TO4_(template <array_q W> XTAL_TN1 transact(), transact<W>(make_f<typename W::value_type>))
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
		
	public:// CONSTRUCTION
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
		:	homotype(devalue_f(XTAL_REF_(a)))
		{
			_detail::copy_to(T_::begin(), a.begin(), a.end());
		}
		XTAL_CXN homotype(bounded_q auto const &a)
		XTAL_0EX
		:	homotype(devalue_f(XTAL_REF_(a)))
		{
			_detail::copy_to(T_::begin(), a);
		}
		XTAL_CXN homotype(bounded_q auto &&a)
		XTAL_0EX
		:	homotype(devalue_f(XTAL_MOV_(a)))
		{
			_detail::move_to(T_::begin(), a);
		}

	};
	using type = bond::isotype<homotype>;

};

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
