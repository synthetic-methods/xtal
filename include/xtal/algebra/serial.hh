#pragma once
#include "./any.hh"
#include "./lattice.hh"
#include "./scalar.hh"




XTAL_ENV_(push)
namespace xtal::algebra
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class           ..._s>	XTAL_TYP serial;
template <class           ..._s>	XTAL_USE serial_t = typename serial<_s...>::type;
template <class           ...Ts>	XTAL_ASK serial_q = bond::head_tag_p<serial_t, Ts...>;
template <size_t N, class ...Ts>	XTAL_ASK serial_p = serial_q<Ts...> and (...and (N == Ts::size()));
template <class  V=void>
XTAL_DEF_(return,inline)
XTAL_LET serial_f(auto &&...oo)
XTAL_0EX {return _detail::initialize<serial_t>::template via<V>(XTAL_REF_(oo)...);}


////////////////////////////////////////////////////////////////////////////////
///\
Extends `lattice` with point-wise addition, and multiplication defined by linear convolution. \

template <column_q A>
struct serial<A>
{
	using _op = bond::operate<A>;
	using U_delta = typename _op::delta_t;
	using U_sigma = typename _op::sigma_t;
	using U_alpha = typename _op::alpha_t;
	
	template <class T>
	using allotype = typename lattice<A>::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<allotype<T>, bond::tag<serial_t>>;

	template <class T>
	class homotype : public holotype<T>
	{
		friend T;
		using  T_ = holotype<T>;
	
	protected:
		using          T_::N_data;
		using typename T_::U_data;

	public:// CONSTRUCT
		using T_::T_;

	public:// ACCESS
		using T_::let;
		using T_::self;
		using T_::twin;
	
	public:// OPERATE
		using T_::operator*=;
	//	using T_::operator+=;
	//	using T_::operator-=;

		XTAL_DEF_(return,inline) XTAL_LET operator  * (auto       const &t) XTAL_0FX {return twin() *=  (t);}
		XTAL_DEF_(return,inline) XTAL_LET operator  + (auto       const &t) XTAL_0FX {return twin() +=  (t);}
		XTAL_DEF_(return,inline) XTAL_LET operator  - (auto       const &t) XTAL_0FX {return twin() -=  (t);}
		XTAL_DEF_(inline)        XTAL_REF operator  *=(embrace_t<U_data> t) XTAL_0EX {return self() *= T(t);}
		XTAL_DEF_(inline)        XTAL_REF operator  +=(embrace_t<U_data> t) XTAL_0EX {return self() += T(t);}
		XTAL_DEF_(inline)        XTAL_REF operator  -=(embrace_t<U_data> t) XTAL_0EX {return self() -= T(t);}

		///\
		Multiplication by linear convolution, truncated by `N_data`. \

	//	XTAL_DEF_(inline)
		XTAL_LET operator *=(T const &t)
		XTAL_0EX -> T &
		{
			auto &s = self();
			
			if constexpr (_op::alignment_n < N_data) {
				for (auto i = N_data; ~--i;) {let(i) *= get<0>(t);
				for (auto j = i; j-- ;) {let(i) += t.let(j)*let(i - j);}}
			}
			else {
				bond::seek_backward_f<N_data, 0>([&, this] (auto I) XTAL_0FN {get<I>(s) *= get<0>(t);
				bond::seek_backward_f<     I, 1>([&, this] (auto J) XTAL_0FN {get<I>(s) += get<J>(t)*get<I - J>(s);});});
			}
			return self();
		}

	//	Vector addition:
		/**/
		XTAL_DEF_(inline)
		XTAL_LET operator +=(T const &t)
		XTAL_0EX -> T &
		{
			auto &s = self();

			[&]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN {auto &s = self(); ((get<I>(s) += get<I>(t)),...);}
			(bond::seek_s<N_data>{});
			
			return s;
		}
		XTAL_DEF_(inline)
		XTAL_LET operator -=(T const &t)
		XTAL_0EX -> T &
		{
			auto &s = self();
			
			[&]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN {auto &s = self(); ((get<I>(s) -= get<I>(t)),...);}
			(bond::seek_s<N_data>{});
			
			return s;
		}
		/***/
		XTAL_DEF_(inline)
		XTAL_LET operator +=(subarray_q<N_data> auto const &t)
		XTAL_0EX -> T &
		{
			auto &s = self();
			
			[&]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN {auto &s = self(); ((get<I>(s) += get<I>(t)),...);}
			(bond::seek_s<count_f(t)>{});
			
			return s;
		}
		XTAL_DEF_(inline)
		XTAL_LET operator -=(subarray_q<N_data> auto const &t)
		XTAL_0EX -> T &
		{
			auto &s = self();
			
			[&]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN {auto &s = self(); ((get<I>(s) -= get<I>(t)),...);}
			(bond::seek_s<count_f(t)>{});
			
			return s;
		}

		///\
		The dual of `T`, defined by `scalar`. \
		
		struct transverse
		{
			template <class L>
			using holotype = typename scalar<A>::template homotype<L>;

			template <class L>
			class homotype : public holotype<L>
			{
				friend L;
				using  L_ = holotype<L>;
			
			public:
				using L_::L_;
				struct transverse {using type = T;};

			};
			using type = bond::isotype<homotype>;

		};
	};
	using type = bond::isotype<homotype>;

};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
