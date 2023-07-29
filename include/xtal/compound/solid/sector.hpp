#pragma once
#include "./any.hpp"
#include "./strata.hpp"
#include "./scalar.hpp"




XTAL_ENV_(push)
namespace xtal::compound::solid
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class ..._s> XTAL_NYM sector;
template <class ..._s> XTAL_USE sector_t = typename sector<_s...>::type;
template <class ...Ts> XTAL_ASK sector_q = tag_p<sector, Ts...>;


////////////////////////////////////////////////////////////////////////////////
///\
Extends `strata::type` with elementwise addition/subtracion. \

template <class U, size_t N>
struct sector<U[N]>
{
	using _computer = compute<U>;
	
	template <class T>
	using demitype = typename strata<U[N]>::template homotype<T>;

	template <class T>
	using hemitype = compose_s<demitype<T>, tag<sector>>;

	template <class T>
	class homotype: public hemitype<T>
	{
		friend T;
		using S_ = hemitype<T>;
	
	public:
		using S_::S_;
		using S_::d;
		using S_::self;
		using S_::twin;

		///\
		The counterpart to `this` for which multiplication is linear. \

		template <class Z>
		using dual_t = typename scalar<U[N]>::type;

		XTAL_OP1_(T &) += (bracket_t<U> w) XTAL_0EX {return self() += T(w.begin(), w.end());}
		XTAL_OP1_(T &) -= (bracket_t<U> w) XTAL_0EX {return self() -= T(w.begin(), w.end());}
		
		XTAL_OP1_(T &) += (T const &t) XTAL_0EX {return seek_e<N>([&, this] (auto i) XTAL_0FN_(d(i) += t.d(i))), self();}
		XTAL_OP1_(T &) -= (T const &t) XTAL_0EX {return seek_e<N>([&, this] (auto i) XTAL_0FN_(d(i) -= t.d(i))), self();}

		template <subarray_q<N> Y> XTAL_OP1_(T &) += (Y const &w) XTAL_0EX {return seek_e<arity_v<decltype(w)>>([&, this] (auto i) XTAL_0FN_(d(i) += w[i])), self();}
		template <subarray_q<N> Y> XTAL_OP1_(T &) -= (Y const &w) XTAL_0EX {return seek_e<arity_v<decltype(w)>>([&, this] (auto i) XTAL_0FN_(d(i) -= w[i])), self();}

	};
	using type = _detail::isotype<homotype>;

};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
