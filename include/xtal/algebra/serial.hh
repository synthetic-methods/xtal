#pragma once
#include "./any.hh"
#include "./lattice.hh"





XTAL_ENV_(push)
namespace xtal::algebra
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class   ..._s>	XTAL_TYP serial;
template <class   ..._s>	XTAL_USE serial_t = typename serial<_s...>::type;
template <class   ...Ts>	XTAL_ASK serial_q = bond::head_tag_p<serial, Ts...>;
template <class  V=void>
XTAL_DEF_(return,inline)
XTAL_FN1 serial_f(auto &&...oo)
XTAL_0EX {return _detail::initialize<serial_t>::template via<V>(XTAL_REF_(oo)...);}


////////////////////////////////////////////////////////////////////////////////
///\
Extends `lattice` with point-wise addition, and multiplication defined by linear convolution. \

template <class U_data, int N_data>
struct serial<U_data[N_data]>
{
	using _op = bond::operate<U_data>;
	using U_delta = typename _op::delta_t;
	using U_sigma = typename _op::sigma_t;
	using U_alpha = typename _op::alpha_t;
	
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
			auto &s = self();
			if constexpr (_op::alignment_n < N_data) {
				for (auto i = N_data; ~--i;) {let(i) *= t.get(0);
				for (auto j = i; j-- ;) {let(i) += t.get(j)*get(i - j);}}
			}
			else {
				bond::seek_backward_f<N_data, 0>([&, this] (auto I) XTAL_0FN {_std::get<I>(s) *= _std::get<0>(t);
				bond::seek_backward_f<I, 1>([&, this] (auto J) XTAL_0FN {_std::get<I>(s) += _std::get<J>(t)*_std::get<I - J>(s);});});
			}
			return self();
		}

	//	Vector addition:
		/**/
		XTAL_DEF_(inline)
		XTAL_OP1_(T_ &) += (T_ const &t)
		XTAL_0EX
		{
			[&]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN {auto &s = self(); ((_std::get<I>(s) += _std::get<I>(t)),...);}
			(bond::seek_s<N_data>{});
			return self();
		}
		XTAL_DEF_(inline)
		XTAL_OP1_(T_ &) -= (T_ const &t)
		XTAL_0EX
		{
			[&]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN {auto &s = self(); ((_std::get<I>(s) -= _std::get<I>(t)),...);}
			(bond::seek_s<N_data>{});
			return self();
		}
		/***/
		template <class W> requires subarray_q<W, N_data>
		XTAL_DEF_(inline)
		XTAL_OP1_(T_ &) += (W const &w)
		XTAL_0EX
		{
			[&]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN {auto &s = self(); ((_std::get<I>(s) += _std::get<I>(w)),...);}
			(bond::seek_s<N_data>{});
			return self();
		}
		template <class W> requires subarray_q<W, N_data>
		XTAL_DEF_(inline)
		XTAL_OP1_(T_ &) -= (W const &w)
		XTAL_0EX
		{
			[&]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN {auto &s = self(); ((_std::get<I>(s) -= _std::get<I>(w)),...);}
			(bond::seek_s<N_data>{});
			return self();
		}

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
			//	using F_::get;
				using F_::let;
				using F_::base;
				using F_::self;
				using F_::twin;
				using F_::operator*=;
				using F_::operator/=;

			//	Vector multiplication (Hadamard product):
				
				template <class W> requires array_q<W, N_data>
				XTAL_DEF_(inline)
				XTAL_OP1_(F &) *= (W const &w)
				XTAL_0EX
				{
					[&]<auto ...I> (bond::seek_t<I...>)
						XTAL_0FN {auto &s = self(); ((_std::get<I>(s) *= _std::get<I>(w)),...);}
					(bond::seek_s<N_data>{});
					return self();
				}
				template <class W> requires array_q<W, N_data>
				XTAL_DEF_(inline)
				XTAL_OP1_(F &) /= (W const &w)
				XTAL_0EX
				{
					[&]<auto ...I> (bond::seek_t<I...>)
						XTAL_0FN {auto &s = self(); ((_std::get<I>(s) /= _std::get<I>(w)),...);}
					(bond::seek_s<N_data>{});
					return self();
				}

			//	Scalar sum:
				template <int N_sgn=1>
				XTAL_DEF_(return,inline)
				XTAL_TN1 sum(U_data const &u={})
				XTAL_0FX
				{
					auto &s = self();

					if constexpr (0 < N_sgn) {
						return [&]<auto ...I> (bond::seek_t<I...>)
							XTAL_0FN_(u +...+ (_std::get<I>(s)))
						(bond::seek_s<N_data>{});
					}
					else {
						return [&]<auto ...I> (bond::seek_t<I...>)
							XTAL_0FN_(u +...+ (_std::get<I>(s)*U_data(-sign_n<I&1, -1>)))
						(bond::seek_s<N_data>{});
					}
				}
			//	Scalar product:
				template <int N_sgn=1>
				XTAL_DEF_(return,inline)
				XTAL_TN1 product(U_data u={})
				XTAL_0FX
				{
					auto &s = self();
					
					if constexpr (0 < N_sgn) {
						bond::seek_forward_f<N_data>([&] (auto I) XTAL_0FN {
							auto const &v = _std::get<I>(s);
							u = _op::accumulate_f(u, v, v);
						});
					}
					else {
						bond::seek_forward_f<N_data>([&] (auto I) XTAL_0FN {
							auto const &v = _std::get<I>(s);
							u = _op::accumulate_f(u, v, v, U_data(-sign_n<I&1, -1>));
						});
					}
					return u;
				}
				XTAL_DEF_(return,inline)
				XTAL_TN1 product(iterated_q auto &&t)
				XTAL_0FX
				{
					auto &s = self();
					
					U_data u{};
					bond::seek_forward_f<N_data>([&, this] (auto I) XTAL_0FN {
						u = _op::accumulate_f(u, _std::get<I>(s), _std::get<I>(t));
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
					auto &s = self();

					XTAL_IF0
					if (_std::is_constant_evaluated() or N_data <= _op::alignment::value) {
						[&]<auto ...I> (bond::seek_t<I...>)
							XTAL_0FN {((_std::get<I>(s) = U_data{1}),...);}
						(bond::seek_s<N_data>{});
					}
					else {
						_std::uninitialized_fill_n(F_::data(), F_::size(), U_data{1});
					}
				}
				XTAL_CON homotype(embrace_t<U_data> w)
				XTAL_0EX
				{
					auto &s = self();
					auto const m = w.size();
					
					_detail::copy_to(F_::begin(), w);

					assert(1 == m or m == N_data);
					if (1 == m) {
						auto const &u = _std::get<0>(s);
						if (_std::is_constant_evaluated() or N_data <= _op::alignment::value) {
							[&]<auto ...I> (bond::seek_t<I...>)
								XTAL_0FN {((_std::get<I + 1>(s) = u),...);}
							(bond::seek_s<N_data - 1>{});
						}
						else {
							_std::uninitialized_fill_n(_std::next(F_::data(), m), F_::size() - m, u);
						}
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
