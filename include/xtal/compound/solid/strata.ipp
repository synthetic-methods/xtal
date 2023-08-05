#pragma once
#include "./any.ipp"






XTAL_ENV_(push)
namespace xtal::compound::solid
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class ..._s> XTAL_NYM strata;
template <class ..._s> XTAL_USE strata_t = typename strata<_s...>::type;
template <class ...Ts> XTAL_ASK strata_q = tag_p<strata, Ts...>;


////////////////////////////////////////////////////////////////////////////////
///\
Defines a fixed-width `type` that supports arithmetic operators. \

template <class U, size_t N, size_t Ns>
struct strata<U[N][Ns]>
:	strata<strata_t<U[N]>[Ns]>
{};
template <class U, size_t N>
struct strata<U[N]>
{
	using _computer = compute<U>;
	
	template <class T>
	using demitype = compose_s<_std::array<U, N>, define<T>>;

	template <class T>
	using hemitype = compose_s<demitype<T>, tag<strata>>;

	template <class T>
	class homotype: public hemitype<T>
	{
		friend T;
		using S_ = hemitype<T>;
		using I_ = typename S_::size_type;

//	protected:
	public:
		XTAL_DO4_(XTAL_FN0 accept(I_ i), {assert(0 <= i and i < N);})
		XTAL_FN2 access(I_ i) XTAL_0EX_(&&) {return XTAL_MOV_(S_::operator[](i));}
		XTAL_FN2 access(I_ i) XTAL_0FX_(&&) {return XTAL_MOV_(S_::operator[](i));}
		XTAL_FN2 access(I_ i) XTAL_0EX_(&)  {return           S_::operator[](i) ;}
		XTAL_FN2 access(I_ i) XTAL_0FX_(&)  {return           S_::operator[](i) ;}
		XTAL_TO4_(XTAL_FN2 d(I_ i), (accept(i), access(i)))

	public:
		using S_::S_;
		using S_::self;
		using S_::twin;

		template <bracket_q W>
		XTAL_CXN homotype(W &&w)
		{
			_detail::move_to(S_::begin(), w);
		}
		template <bracket_q W>
		XTAL_CXN homotype(W const &w)
		{
			_detail::copy_to(S_::begin(), w);
		}
		XTAL_CON homotype(bracket_t<U> etc)
		XTAL_0EX
		{
		//	TODO: Test partial construction. \
		
			_detail::copy_to(S_::begin(), etc);
			auto const n = etc.size();
			_std::uninitialized_value_construct_n(S_::begin() + n, S_::size() - n);
		}

		template <class W>
		XTAL_CN2_(T &) refer(W &w)
		XTAL_0EX
		{
			static_assert(is_q<valued_t<W>, U> and sizeof(W) == sizeof(T));
			return force_f<T &>(w);
		}

		///\
		Elementwise mutating transformer. \

		XTAL_FN1 transmute(XTAL_DEF_(_std::invocable<U>) ...fs)
		XTAL_0EX
		{
			return (transmute(XTAL_REF_(fs)), ...);
		}
		XTAL_FN1 transmute(XTAL_DEF_(_std::invocable<U>) f)
		XTAL_0EX
		{
			_detail::apply_to(self(), XTAL_REF_(f));
			return self();
		}
		XTAL_FN1 transmute(_std::invocable<U> auto const &f)
		XTAL_0EX
		XTAL_REQ (0 < N) and (N <= _computer::alignment_v)
		{
			seek_e<N>([&, this] (auto i) XTAL_0FN_(d(i) = f(d(i))));
			return self();
		}

		///\
		Elementwise comparators. \

		XTAL_OP2 <=> (homotype const &t)
		XTAL_0FX
		{
			homotype const &s = *this;
			if (0);
			else if (s <  t) return _std::strong_ordering::      less;
			else if (s == t) return _std::strong_ordering::     equal;
			else if (s  > t) return _std::strong_ordering::   greater;
			else             return _std::strong_ordering::equivalent;
		}
		XTAL_OP2_(bool) == (homotype const &t) XTAL_0FX {return [&, this]<auto ...I>(seek_t<I...>) XTAL_0FN_(...and (d(I) == t.d(I))) (seek_f<N> {});}
		XTAL_OP2_(bool) <= (homotype const &t) XTAL_0FX {return [&, this]<auto ...I>(seek_t<I...>) XTAL_0FN_(...and (d(I) <= t.d(I))) (seek_f<N> {});}
		XTAL_OP2_(bool) >= (homotype const &t) XTAL_0FX {return [&, this]<auto ...I>(seek_t<I...>) XTAL_0FN_(...and (d(I) >= t.d(I))) (seek_f<N> {});}
		XTAL_OP2_(bool) <  (homotype const &t) XTAL_0FX {return [&, this]<auto ...I>(seek_t<I...>) XTAL_0FN_(...and (d(I) <  t.d(I))) (seek_f<N> {});}
		XTAL_OP2_(bool) >  (homotype const &t) XTAL_0FX {return [&, this]<auto ...I>(seek_t<I...>) XTAL_0FN_(...and (d(I) >  t.d(I))) (seek_f<N> {});}

		XTAL_OP2_(T)    *  (XTAL_DEF w) XTAL_0FX {return twin() *= XTAL_REF_(w);}
		XTAL_OP2_(T)    /  (XTAL_DEF w) XTAL_0FX {return twin() /= XTAL_REF_(w);}
		XTAL_OP2_(T)    +  (XTAL_DEF w) XTAL_0FX {return twin() += XTAL_REF_(w);}
		XTAL_OP2_(T)    -  (XTAL_DEF w) XTAL_0FX {return twin() -= XTAL_REF_(w);}

		XTAL_OP1_(T &)  *= (XTAL_DEF_(to_q<U>) w) XTAL_0EX {return seek_e<N>([&, this] (auto i) XTAL_0FN_(d(i) *= XTAL_REF_(w))), self();}
		XTAL_OP1_(T &)  /= (XTAL_DEF_(to_q<U>) w) XTAL_0EX {return seek_e<N>([&, this] (auto i) XTAL_0FN_(d(i) /= XTAL_REF_(w))), self();}

	};
	using type = _detail::isotype<homotype>;

};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
/**/
namespace std
{///////////////////////////////////////////////////////////////////////////////

template <xtal::compound::solid::strata_q T>
struct tuple_size<T>: xtal::arity_t<T> {};

template <size_t N, xtal::compound::solid::strata_q T>
struct tuple_element<N, T> {using type = xtal::valued_t<T>;};


}/////////////////////////////////////////////////////////////////////////////
/***/
XTAL_ENV_(pop)
