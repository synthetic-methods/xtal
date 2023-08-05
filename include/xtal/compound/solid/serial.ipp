#pragma once
#include "./any.ipp"
#include "./sector.ipp"





XTAL_ENV_(push)
namespace xtal::compound::solid
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class ..._s> XTAL_NYM serial;
template <class ..._s> XTAL_USE serial_t = typename serial<_s...>::type;
template <class ...Ts> XTAL_ASK serial_q = tag_p<serial, Ts...>;


////////////////////////////////////////////////////////////////////////////////
///\
Extends `sector::type` with multiplication defined by linear convolution. \

template <class U, size_t N>
struct serial<U[N]>
{
	using _computer = compute<U>;
	
	template <class T>
	using demitype = typename sector<U[N]>::template homotype<T>;

	template <class T>
	using hemitype = compose_s<demitype<T>, tag<serial>>;

	template <class T>
	class homotype: public hemitype<T>
	{
	//	TODO: Subclass to define serial pairs like `complex`. \

		friend T;
		using S_ = hemitype<T>;
	
	public:
		using S_::S_;
		using S_::d;
		using S_::self;
		using S_::twin;

		///\
		Multiplication by linear convolution, truncated by `N`. \

		XTAL_OP2_(T) * (T const &t)
		XTAL_0FX
		{
			return twin() *= t;
		}
		XTAL_OP1_(T &) *=(T const &t)
		XTAL_0EX
		{
			auto constexpr H = (size_s) N;
			auto _s = self();
			if constexpr (_computer::alignment_v < H) {
				for (auto i = H;   ~--i;) {d(i) *= t.d(0);
				for (auto j = i; j; --j ) {d(i) += t.d(j)*_s[i - j];}}
			}
			else {
				seek_e<-(size_s) H, 0>([&, this] (auto I) XTAL_0FN {d(I) *= t.d(0);
				seek_e<-(size_s) I, 1>([&, this] (auto J) XTAL_0FN {d(I) += t.d(J)*_s[I - J];});});
			}
			return self();
		}
		///\
		Produces the successor by pairwise addition starting from `begin()`, \
		assuming the entries of `this` are finite differences/derivatives. \

		XTAL_OP1 ++ (int)
		XTAL_0EX
		{
			auto t = twin(); operator++(); return t;
		}
		XTAL_OP1 ++ ()
		XTAL_0EX
		{
		//	auto constexpr N0 = N - 0;
			auto constexpr N1 = N - 1;
			seek_e<N1>([&, this] (auto i) XTAL_0FN_(d(0 + i) += d(1 + i)));
			return self();
		}

		///\
		Produces the predecessor by pairwise subtraction starting from `end()`, \
		assuming the entries of `this` are finite differences/derivatives. \

		XTAL_OP1 -- (int)
		XTAL_0EX
		{
			auto t = twin(); operator--(); return t;
		}
		XTAL_OP1 -- ()
		XTAL_0EX
		{
			auto constexpr N0 = N - 0;
			auto constexpr N1 = N - 1;
			seek_e<N1>([&, this] (auto i) XTAL_0FN_(d(N1 - i) -= d(N0 - i)));
			return self();
		}

	};
	using type = _detail::isotype<homotype>;

};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
