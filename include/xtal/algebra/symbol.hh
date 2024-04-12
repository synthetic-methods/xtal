#pragma once
#include "./any.hh"
#include "./scalar.hh"





XTAL_ENV_(push)
namespace xtal::algebra
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class ..._s> struct  symbol;
template <class ..._s> using   symbol_t = typename symbol<_s...>::type;
template <class ...Ts> concept symbol_q = bond::tag_p<symbol, Ts...>;


////////////////////////////////////////////////////////////////////////////////
///\
Extends `scalar` with Dirichlet characterization and modulo access. \

template <class U_data, int N_data>
struct symbol<U_data[N_data]>
{
	using re = bond::realize<U_data>;
	using U_delta = typename re::delta_t;
	using U_sigma = typename re::sigma_t;
	using U_alpha = typename re::alpha_t;
	
	template <class T>
	using demitype = typename scalar<U_data[N_data]>::template homotype<T>;

	template <class T>
	using hemitype = bond::compose_s<demitype<T>, bond::tag<symbol>>;

	template <class T>
	class homotype : public hemitype<T>
	{
		friend T;
		using  T_ = hemitype<T>;
		using  I_ = typename T_::difference_type;

		XTAL_LET modulo = [] (I_ i) XTAL_0FN_(((i%N_data) + N_data)%N_data);

	public:
		using T_::get;
		using T_::let;
		using T_::self;
		using T_::twin;


	public:// OPERATE

		XTAL_TN2 get(I_ i) XTAL_0FX_(&&) {return XTAL_MOV_(T_::operator[](modulo(i)));}
		XTAL_TN2 get(I_ i) XTAL_0FX_(&)  {return          (T_::operator[](modulo(i)));}

		XTAL_TN2 let(I_ i) XTAL_0EX_(&&) {return XTAL_MOV_(T_::operator[](modulo(i)));}
		XTAL_TN2 let(I_ i) XTAL_0EX_(&)  {return          (T_::operator[](modulo(i)));}


	public:// CONSTRUCT
		using T_::T_;

		///\
		Dirichlet character generation. \

		template <int N_subscript=1>
		XTAL_TN1_(T &) characterize()
		XTAL_0EX
		XTAL_REQ ((bool) (1&N_data))
		{
			size_s constexpr N = N_data;
			size_s constexpr M = N_data - 1;
			size_s constexpr K = M >> 1;
			size_s           k = N_subscript;
			let(0) = {};

			if constexpr (integral_number_q<U_data>) {
				bond::seek_forward_f<K>([&, this] (auto const &i) XTAL_0FN {
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
					u = re::circle_f(re::patio_f(1, K));
				}
				bond::seek_forward_f<K>([&, this] (auto &&) XTAL_0FN {
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
		XTAL_TN1_(T &) subcharacterize()
		XTAL_0EX
		{
			size_t constexpr N = N_data*2 + 1;
			size_t constexpr M = N_data*2 + 0;
			size_t constexpr K = N_data;
			size_t           k = N_data;

			if constexpr (integral_number_q<U_data>) {
				bond::seek_forward_f<K>([&, this] (auto const &i) XTAL_0FN {
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
					u = re::circle_f(re::patio_f(1, K));
				}
				else {
					u = 1;
				}
				w = u;
				bond::seek_forward_f<K>([&, this] (auto &&) XTAL_0FN {
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
