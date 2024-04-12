#pragma once
#include "./any.hh"
#include "./lattice.hh"





XTAL_ENV_(push)
namespace xtal::algebra
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class ..._s> struct  serial;
template <class ..._s> using   serial_t = typename serial<_s...>::type;
template <class ...Ts> concept serial_q = bond::tag_p<serial, Ts...>;


////////////////////////////////////////////////////////////////////////////////
///\
Extends `lattice` with point-wise addition, \
and multiplication defined by linear convolution. \

template <class U_data, int N_data>
struct serial<U_data[N_data]>
{
	using re = bond::realize<U_data>;
	using U_delta = typename re::delta_t;
	using U_sigma = typename re::sigma_t;
	using U_alpha = typename re::alpha_t;
	
	template <class T>
	using allotype = typename lattice<U_data[N_data]>::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<allotype<T>, bond::tag<serial>>;

	template <class T>
	class homotype : public holotype<T>
	{
		friend T;
		using  T_ = holotype<T>;
	
	public:// CONSTRUCTION
		using T_::T_;

	public:// OPERATION
		using T_::get;
		using T_::let;
		using T_::self;
		using T_::twin;
		using T_::operator*=;
		using T_::operator+=;
		using T_::operator-=;

		///\
		Multiplication by linear convolution, truncated by `N_data`. \

		XTAL_OP1_(T &) *= (T const &t)
		XTAL_0EX
		{
			if constexpr (re::alignment_n < N_data) {
				for (auto i = N_data; ~--i;) {let(i) *= t.get(0);
				for (auto j = i; j-- ;) {let(i) += t.get(j)*get(i - j);}}
			}
			else {
				bond::seek_backward_f<N_data, 0>([&, this] (auto I) XTAL_0FN {let(I) *= t.get(0);
				bond::seek_backward_f<I, 1>([&, this] (auto J) XTAL_0FN {let(I) += t.get(J)*get(I - J);});});
			}
			return self();
		}

	//	Vector addition:
		XTAL_OP1_(T &) += (T const &t) XTAL_0EX {bond::seek_forward_f<N_data>([&, this] (auto i) XTAL_0FN {let(i) += t.get(i);}); return self();}
		XTAL_OP1_(T &) -= (T const &t) XTAL_0EX {bond::seek_forward_f<N_data>([&, this] (auto i) XTAL_0FN {let(i) -= t.get(i);}); return self();}

		template <subarray_q<N_data> Y> XTAL_OP1_(T &) += (Y const &w) XTAL_0EX {bond::seek_forward_f<array_n<XTAL_TYP_(w)>>([&, this] (auto i) XTAL_0FN {let(i) += w[i];}); return self();}
		template <subarray_q<N_data> Y> XTAL_OP1_(T &) -= (Y const &w) XTAL_0EX {bond::seek_forward_f<array_n<XTAL_TYP_(w)>>([&, this] (auto i) XTAL_0FN {let(i) -= w[i];}); return self();}

		///\
		The dual of `T`, replacing addition by point-wise multiplication, \
		and implementing the inner sum/product. \
		
		struct transverse
		{
			template <class L>
			using holotype = typename lattice<U_data[N_data]>::template homotype<L>;

			template <class L>
			class homotype : public holotype<L>
			{
				friend L;
				using  L_ = holotype<L>;
			
			public:
				struct transverse {using type = T;};

			public:// OPERATION
				using L_::get;
				using L_::let;
				using L_::self;
				using L_::twin;
				using L_::operator*=;
				using L_::operator/=;

			//	Vector multiplication (Hadamard product):
				XTAL_OP1_(L &) *= (L const &t) XTAL_0EX {bond::seek_forward_f<N_data>([&, this] (auto i) XTAL_0FN {let(i) *= t.get(i);}); return self();}
				XTAL_OP1_(L &) /= (L const &t) XTAL_0EX {bond::seek_forward_f<N_data>([&, this] (auto i) XTAL_0FN {let(i) /= t.get(i);}); return self();}

			//	Scalar sum:
				template <int N_sign=1>
				XTAL_TN2 sum(U_data const &u={})
				XTAL_0FX
				{
					if constexpr (0 < N_sign) {
						return [&, this]<auto ...M>(bond::seek_t<M...>)
							XTAL_0FN_(u +...+ (get(M)))
						(bond::seek_f<N_data>{});
					}
					else {
						return [&, this]<auto ...M>(bond::seek_t<M...>)
							XTAL_0FN_(u +...+ (get(M)*re::assign_f((U_sigma) M)))
						(bond::seek_f<N_data>{});
					}
				}
			//	Scalar product:
				template <int N_sign=1>
				XTAL_TN2 product(U_data u={})
				XTAL_0FX
				{
					if constexpr (0 < N_sign) {
						bond::seek_forward_f<N_data>([&, this] (auto i) XTAL_0FN {
							auto const &v = get(i);
							u = re::accumulate_f(u, v, v);
						});
					}
					else {
						bond::seek_forward_f<N_data>([&, this] (auto i) XTAL_0FN {
							auto const &v = get(i);
							u = re::accumulate_f(u, v, v, re::assign_f((U_sigma) i));
						});
					}
					return u;
				}
				XTAL_TN2 product(iterated_q auto &&t)
				XTAL_0FX
				{
					U_data u{}; T &s = self();
					bond::seek_forward_f<N_data>([&, this] (auto i) XTAL_0FN {
						u = re::accumulate_f(u, s[i], t[i]);
					});
					return u;
				}

			public:// CONSTRUCTION
			//	using L_::L_;

				XTAL_CO0_(homotype)
			//	XTAL_CO1_(homotype)
				XTAL_CO4_(homotype)

				XTAL_CON homotype()
				XTAL_0EX
				{
					_std::uninitialized_fill_n(L_::data(), L_::size(), U_data{1});
				}
				/***/
				XTAL_CON homotype(braces_t<U_data> w)
				XTAL_0EX
				{
					_detail::copy_to(L_::begin(), w.begin(), w.end());
					if (1 == w.size()) {
						_std::uninitialized_fill_n(_std::next(L_::data(), w.size()), L_::size() - w.size(), get(0));
					}
					else {
						assert(w.size() == N_data);
					}
				}
				XTAL_CON homotype(iterated_q auto &&w)
				XTAL_0EX
				:	L_(XTAL_REF_(w))
				{}
				
			};
			using type = bond::isotype<homotype>;

		};
	};
	using type = bond::isotype<homotype>;

};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
