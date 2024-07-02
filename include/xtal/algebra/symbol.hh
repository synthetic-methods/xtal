#pragma once
#include "./any.hh"
#include "./scalar.hh"





XTAL_ENV_(push)
namespace xtal::algebra
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class   ..._s>	XTAL_TYP symbol;
template <class   ..._s>	XTAL_USE symbol_t = typename symbol<_s...>::type;
template <class   ...Ts>	XTAL_REQ symbol_q = bond::any_tag_p<symbol_t, Ts...>;
template <class  V=void>
XTAL_DEF_(return,inline)
XTAL_LET symbol_f(auto &&...oo)
XTAL_0EX {return _detail::initialize<symbol_t>::template via<V>(XTAL_REF_(oo)...);}


////////////////////////////////////////////////////////////////////////////////
///\
Extends `scalar` with Dirichlet characterization and modulo access. \

template <column_q A>
struct symbol<A>
{
	using _op = bond::operate<A>;
	
	template <class T>
	using allotype = typename scalar<A>::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<allotype<T>, bond::tag<symbol_t>>;

	template <class T>
	class homotype : public holotype<T>
	{
		friend T;
		using  S_ = holotype<T>;
		using  I_ = typename S_::difference_type;

	protected:
		using          S_::N_data;
		using typename S_::U_data;

		static constexpr auto modulo = [] (I_ i) XTAL_0FN_(((i%N_data) + N_data)%N_data);

	public:// ACCESS
		using S_::let;
		using S_::self;
		using S_::twin;

	public:// OPERATE

		XTAL_DEF_(return,inline) XTAL_LET let(I_ i) XTAL_0FX_(&&) -> decltype(auto) {return XTAL_MOV_(S_::operator[](modulo(i)));}
		XTAL_DEF_(return,inline) XTAL_LET let(I_ i) XTAL_0FX_( &) -> decltype(auto) {return           S_::operator[](modulo(i)) ;}

		XTAL_DEF_(return,inline) XTAL_LET let(I_ i) XTAL_0EX_(&&) -> decltype(auto) {return XTAL_MOV_(S_::operator[](modulo(i)));}
		XTAL_DEF_(return,inline) XTAL_LET let(I_ i) XTAL_0EX_( &) -> decltype(auto) {return           S_::operator[](modulo(i)) ;}


	public:// CONSTRUCT
		using S_::S_;

		///\
		Dirichlet character generation. \

		template <int N_subscript=1> requires ((bool) (1&N_data))
		XTAL_LET characterize()
		XTAL_0EX -> T &
		{
			integral_type constexpr N = N_data;
			integral_type constexpr M = N_data - 1;
			integral_type constexpr K = M >> 1U;
			integral_type           k = N_subscript;
			let(0) = {};

			if constexpr (integral_number_q<U_data>) {
				bond::seek_forward_f<K>([&, this] (size_type i) XTAL_0FN {
					auto const o = k%N;
					let(    o) =  i;
					let(N - o) =  i - K;
					k *= K;
				});
				let(1) = 0;
			}
			else {
				U_data w =  1;
				U_data u = -1;
				if constexpr (complex_field_q<U_data>) {
					u = _op::circle_f(_op::patio_f(1, K));
				}
				bond::seek_forward_f<K>([&, this] (size_type i) XTAL_0FN {
					auto const o = k%N;
					let(    o) =  w;
					let(N - o) = -w;
					w *= u;
					k *= K;
				});
			}
			return self();
		}
		template <int N_subscript=1>
		XTAL_LET subcharacterize()
		XTAL_0EX -> T &
		{
			size_type constexpr N = N_data*2 + 1;
			size_type constexpr M = N_data*2 + 0;
			size_type constexpr K = N_data;
			size_type           k = N_data;

			if constexpr (integral_number_q<U_data>) {
				bond::seek_forward_f<K>([&, this] (size_type i) XTAL_0FN {
					auto const o = k%N;
					if (K < o) {
						let(M - o) = (1 + i) - K;
					}
					else {
						let(o - 1) = (1 + i);
					}
					k *= K;
				});
				let(0) = 0;
			}
			else {
				U_data w, u;
				if constexpr (complex_field_q<U_data>) {
					u = _op::circle_f(_op::patio_f(1, K));
				}
				else {
					u = 1;
				}
				w = u;
				bond::seek_forward_f<K>([&, this] (size_type i) XTAL_0FN {
					auto const o = k%N;
					if (K < o) {
						let(M - o) = -w;
					}
					else {
						let(o - 1) =  w;
					}
					w *= u;
					k *= K;
				});
			}
			return self();
		}

	};
	using type = bond::isotype<homotype>;

};

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
