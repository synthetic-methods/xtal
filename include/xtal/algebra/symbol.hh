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
	using U_delta = re::delta_t;
	using U_sigma = re::sigma_t;
	using U_alpha = re::alpha_t;
	
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
			size_t constexpr M_size = N_data  - 1;
			size_t constexpr K      = M_size >> 1;
			size_t           k      = N_subscript;
			let(0) = {};

			if constexpr (integral_number_q<U_data>) {
				bond::seek_forward_f<M_size>([&, this] (auto const &i) XTAL_0FN {
					let(k%N_data) = i - M_size*(K < i);
					k *= K;
				});
			}
			else {
				U_data w =  1;
				U_data u = -1;
				if constexpr (complex_field_q<U_data>) {
					u = re::circle_f(re::patio_f(2, M_size));
				}
				bond::seek_forward_f<K>([&, this] (auto &&) XTAL_0FN {
					auto const head = k%N_data;
					auto const tail =   N_data - head;
					let(head) =  w;
					let(tail) = -w;
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
