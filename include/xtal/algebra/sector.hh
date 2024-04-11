#pragma once
#include "./any.hh"
#include "./lattice.hh"





XTAL_ENV_(push)
namespace xtal::algebra
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class ..._s> struct  sector;
template <class ..._s> using   sector_t = typename sector<_s...>::type;
template <class ...Ts> concept sector_q = bond::tag_p<sector, Ts...>;


////////////////////////////////////////////////////////////////////////////////
///\
Extends `lattice` with point-wise addition. \

///\note\
Naming intended to evoke `static_vector`, \
and the `scalar` member-type `dual`. \

template <class U_data, int N_data>
struct sector<U_data[N_data]>
{
	using re = bond::realize<U_data>;
	using U_delta = re::delta_t;
	using U_sigma = re::sigma_t;
	using U_alpha = re::alpha_t;
	
	template <class T>
	using demitype = typename lattice<U_data[N_data]>::template homotype<T>;

	template <class T>
	using hemitype = bond::compose_s<demitype<T>, bond::tag<sector>>;

	template <class T>
	class homotype : public hemitype<T>
	{
		friend T;
		using  T_ = hemitype<T>;
	
	public:// CONSTRUCTION
		using T_::T_;

		///\
		The dual of `T`, replacing addition by point-wise multiplication, \
		and implementing the inner sum/product. \
		
		struct dual
		{
			template <class L>
			using hemitype = typename lattice<U_data[N_data]>::template homotype<L>;

			template <class L>
			class homotype : public hemitype<L>
			{
				friend L;
				using  L_ = hemitype<L>;
			
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
				
				struct dual {using type = T;};

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

			};
			using type = bond::isotype<homotype>;

		};

	public:// OPERATION
		using T_::get;
		using T_::self;
		using T_::twin;
		using T_::operator+=;
		using T_::operator-=;

	//	Vector addition:
		XTAL_OP1_(T &) += (T const &t) XTAL_0EX {bond::seek_forward_f<N_data>([&, this] (auto i) XTAL_0FN {let(i) += t.get(i);}); return self();}
		XTAL_OP1_(T &) -= (T const &t) XTAL_0EX {bond::seek_forward_f<N_data>([&, this] (auto i) XTAL_0FN {let(i) -= t.get(i);}); return self();}

		template <subarray_q<N_data> Y> XTAL_OP1_(T &) += (Y const &w) XTAL_0EX {bond::seek_forward_f<array_n<XTAL_TYP_(w)>>([&, this] (auto i) XTAL_0FN {let(i) += w[i];}); return self();}
		template <subarray_q<N_data> Y> XTAL_OP1_(T &) -= (Y const &w) XTAL_0EX {bond::seek_forward_f<array_n<XTAL_TYP_(w)>>([&, this] (auto i) XTAL_0FN {let(i) -= w[i];}); return self();}

	};
	using type = bond::isotype<homotype>;

};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
