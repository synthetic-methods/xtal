#pragma once
#include "./any.hh"
#include "./lattice.hh"





XTAL_ENV_(push)
namespace xtal::atom
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class ..._s> XTAL_NEW sector;
template <class ..._s> XTAL_USE sector_t = typename sector<_s...>::type;
template <class ...Ts> XTAL_ASK sector_q = bond::tag_p<sector, Ts...>;


////////////////////////////////////////////////////////////////////////////////
///\
Extends `lattice` with pointwise addition. \
Represents a `s(?:tatic_v)?ector`. \

template <class U, int N>
struct sector<U[N]>
{
	using re = bond::realize<U>;
	
	template <class T>
	using demitype = typename lattice<U[N]>::template homotype<T>;

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
		The dual of `T`, \
		replacing addition by pointwise multiplication. \

		struct dual
		{
			template <class L>
			using hemitype = typename lattice<U[N]>::template homotype<L>;

			template <class L>
			class homotype : public hemitype<L>
			{
				friend L;
				using  L_ = hemitype<L>;
			
			public:// CONSTRUCTION
				using L_::L_;
				
				struct dual {using type = T;};

			public:// OPERATION
				using L_::get;
				using L_::let;
				using L_::self;
				using L_::twin;
				using L_::operator*=;
				using L_::operator/=;

			//	Vector multiplication (Hadamard product):
				XTAL_OP1_(L &) *= (L const &t) XTAL_0EX {bond::seek_forward_f<N>([&, this] (auto i) XTAL_0FN {let(i) *= t.get(i);}); return self();}
				XTAL_OP1_(L &) /= (L const &t) XTAL_0EX {bond::seek_forward_f<N>([&, this] (auto i) XTAL_0FN {let(i) /= t.get(i);}); return self();}

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
		XTAL_OP1_(T &) += (T const &t) XTAL_0EX {bond::seek_forward_f<N>([&, this] (auto i) XTAL_0FN {let(i) += t.get(i);}); return self();}
		XTAL_OP1_(T &) -= (T const &t) XTAL_0EX {bond::seek_forward_f<N>([&, this] (auto i) XTAL_0FN {let(i) -= t.get(i);}); return self();}

		template <subarray_q<N> Y> XTAL_OP1_(T &) += (Y const &w) XTAL_0EX {bond::seek_forward_f<array_n<XTAL_TYP_(w)>>([&, this] (auto i) XTAL_0FN {let(i) += w[i];}); return self();}
		template <subarray_q<N> Y> XTAL_OP1_(T &) -= (Y const &w) XTAL_0EX {bond::seek_forward_f<array_n<XTAL_TYP_(w)>>([&, this] (auto i) XTAL_0FN {let(i) -= w[i];}); return self();}

	};
	using type = bond::isotype<homotype>;

};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
