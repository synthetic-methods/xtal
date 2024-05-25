#pragma once
#include "./any.hh"
#include "./lattice.hh"





XTAL_ENV_(push)
namespace xtal::algebra
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class ..._s> XTAL_TYP serial;
template <class ..._s> XTAL_USE serial_t = typename serial<_s...>::type;
template <class ...Ts> XTAL_ASK serial_q = bond::tag_p<serial, Ts...>;


////////////////////////////////////////////////////////////////////////////////
///\
Extends `lattice` with point-wise addition, \
and multiplication defined by linear convolution. \

template <class U_data, int N_data>
struct serial<U_data[N_data]>
{
	using op = bond::operate<U_data>;
	using U_delta = typename op::delta_t;
	using U_sigma = typename op::sigma_t;
	using U_alpha = typename op::alpha_t;
	
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
			if constexpr (op::alignment_n < N_data) {
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
		XTAL_OP1_(T &) += (T const &t) XTAL_0EX {bond::seek_forward_f<N_data>([&, this] (XTAL_NDX i) XTAL_0FN {let(i) += t.get(i);}); return self();}
		XTAL_OP1_(T &) -= (T const &t) XTAL_0EX {bond::seek_forward_f<N_data>([&, this] (XTAL_NDX i) XTAL_0FN {let(i) -= t.get(i);}); return self();}

		template <subarray_q<N_data> W> XTAL_OP1_(T &) += (W const &w) XTAL_0EX {bond::seek_forward_f<devalue_f(w)>([&, this] (XTAL_NDX i) XTAL_0FN {let(i) += w[i];}); return self();}
		template <subarray_q<N_data> W> XTAL_OP1_(T &) -= (W const &w) XTAL_0EX {bond::seek_forward_f<devalue_f(w)>([&, this] (XTAL_NDX i) XTAL_0FN {let(i) -= w[i];}); return self();}

		///\
		The dual of `T`, replacing addition by point-wise multiplication, \
		and implementing the inner sum/product. \
		
		struct transverse
		{
			template <class F>
			using holotype = typename lattice<U_data[N_data]>::template homotype<F>;

			template <class F>
			class homotype : public holotype<F>
			{
				friend F;
				using  F_ = holotype<F>;
			
			public:
				struct transverse {using type = T;};

			public:// OPERATION
				using F_::get;
				using F_::let;
				using F_::self;
				using F_::twin;
				using F_::operator*=;
				using F_::operator/=;

			//	Vector multiplication (Hadamard product):
				
				XTAL_OP1_(F &) *= (F const &f) XTAL_0EX {bond::seek_forward_f<N_data>([&, this] (XTAL_NDX i) XTAL_0FN {let(i) *= f.get(i);}); return self();}
				XTAL_OP1_(F &) /= (F const &f) XTAL_0EX {bond::seek_forward_f<N_data>([&, this] (XTAL_NDX i) XTAL_0FN {let(i) /= f.get(i);}); return self();}

				template <array_q<N_data> W> XTAL_OP1_(F &) *= (W const &w) XTAL_0EX {bond::seek_forward_f<N_data>([&, this] (XTAL_NDX i) XTAL_0FN {let(i) *= w.get(i);}); return self();}
				template <array_q<N_data> W> XTAL_OP1_(F &) /= (W const &w) XTAL_0EX {bond::seek_forward_f<N_data>([&, this] (XTAL_NDX i) XTAL_0FN {let(i) /= w.get(i);}); return self();}

			//	Scalar sum:
				template <int N_sign=1>
				XTAL_TN2 sum(U_data const &u={})
				XTAL_0FX
				{
					using _std::get;
					auto &s = self();

					if constexpr (0 < N_sign) {
						return [&]<auto ...I>(bond::seek_t<I...>)
							XTAL_0FN_(u +...+ (get<I>(s)))
						(bond::seek_s<N_data>{});
					}
					else {
						return [&]<auto ...I>(bond::seek_t<I...>)
							XTAL_0FN_(u +...+ (get<I>(s)*op::assign_f((U_sigma) I)))
						(bond::seek_s<N_data>{});
					}
				}
			//	Scalar product:
				template <int N_sign=1>
				XTAL_TN2 product(U_data u={})
				XTAL_0FX
				{
					using _std::get;
					auto &s = self();
					
					if constexpr (0 < N_sign) {
						bond::seek_forward_f<N_data>([&] (XTAL_NDX i) XTAL_0FN {
							auto const &v = get<i>(s);
							u = op::accumulate_f(u, v, v);
						});
					}
					else {
						bond::seek_forward_f<N_data>([&] (XTAL_NDX i) XTAL_0FN {
							auto const &v = get<i>(s);
							u = op::accumulate_f(u, v, v, op::assign_f((U_sigma) i));
						});
					}
					return u;
				}
				XTAL_TN2 product(iterated_q auto &&t)
				XTAL_0FX
				{
					using _std::get;
					auto &s = self();
					
					U_data u{};
					bond::seek_forward_f<N_data>([&, this] (XTAL_NDX i) XTAL_0FN {
						u = op::accumulate_f(u, get<i>(s), get<i>(t));
					});
					return u;
				}

			public:// CONSTRUCTION
			//	using F_::F_;

				XTAL_CO0_(homotype)
			//	XTAL_CO1_(homotype)
				XTAL_CO4_(homotype)

				XTAL_CON homotype()
				XTAL_0EX
				{
					if (_std::is_constant_evaluated()) {
						bond::seek_forward_f<N_data>([&, this] (XTAL_NDX i) XTAL_0FN {let(i) = U_data{1};});
					}
					else {
						_std::uninitialized_fill_n(F_::data(), F_::size(), U_data{1});
					}
				}
				/***/
				XTAL_CON homotype(embrace_t<U_data> w)
				XTAL_0EX
				{
					_detail::copy_to(F_::begin(), w.begin(), w.end());
					if (1 == w.size()) {
						if (_std::is_constant_evaluated()) {
							bond::seek_forward_f<N_data - 1>([&, this] (XTAL_NDX i) XTAL_0FN {let(i + 1) = get(0);});
						}
						else {
							_std::uninitialized_fill_n(_std::next(F_::data(), w.size()), F_::size() - w.size(), get(0));
						}
					}
					else {
						assert(w.size() == N_data);
					}
				}
				XTAL_CXN homotype(iterated_q auto &&w)
				XTAL_0EX
				:	F_(XTAL_REF_(w))
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
