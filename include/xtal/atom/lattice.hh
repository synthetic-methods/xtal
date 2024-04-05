#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::atom
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class ..._s> XTAL_NEW lattice;
template <class ..._s> XTAL_USE lattice_t = typename lattice<_s...>::type;
template <class ..._s> XTAL_ASK lattice_q = bond::tag_p<lattice, _s...>;


////////////////////////////////////////////////////////////////////////////////
///\
Defines a fixed-width `type` that supports arithmetic operators. \
Only scalar multiplication is defined by default. \

///\todo\
Specialize for SIMDe types. \

///\todo\
Adapt `_detail::apply_to` etc to execute in parallel using SIMDE? \


template <class U, size_t N, int Ns>
struct lattice<U[N][Ns]> : lattice<lattice_t<U[N]>[Ns]>
{};
template <class U, size_t N>
struct lattice<U[N]>
{
	using re = bond::realize<U>;
	
	template <class T>
	using demitype = bond::compose_s<_std::array<U, N>, bond::define<T>>;

	template <class T>
	using hemitype = bond::compose_s<demitype<T>, bond::tag<lattice>>;

	template <class T>
	class homotype : public hemitype<T>
	{
		friend T;
		using  T_ = hemitype<T>;
		using  I_ = typename T_::difference_type;

	public:// ACCESS
		using T_::self;
		using T_::twin;
		XTAL_FN2_(typename re::sigma_t) size() {return N;}

		XTAL_TN2 get(I_ i) XTAL_0FX_(&&) {return XTAL_MOV_(T_::operator[](i));}
		XTAL_TN2 get(I_ i) XTAL_0EX_(&&) {return XTAL_MOV_(T_::operator[](i));}
		XTAL_TN2 get(I_ i) XTAL_0FX_(&)  {return           T_::operator[](i) ;}
		XTAL_TN2 get(I_ i) XTAL_0EX_(&)  {return           T_::operator[](i) ;}

	public:// CONVERSION
		template <template <class> class _t> using exomorph_t =        _t<U[N]>;
		template <                 class  V> using isomorph_t = lattice_t<V[N]>;
		
		///\
		Elementwise immutative transformer. \

		XTAL_TO4_(template <array_q W> XTAL_TN1 transmorph(), transmorph<W>(as_f<value_t<W>>))
		template <array_q W> XTAL_TN1 transmorph(_std::invocable<U> auto &&f) XTAL_0EX_(&&) {return transmove<W>(XTAL_REF_(f));}
		template <array_q W> XTAL_TN1 transmorph(_std::invocable<U> auto &&f) XTAL_0FX_(&&) {return transmove<W>(XTAL_REF_(f));}
		template <array_q W> XTAL_TN1 transmorph(_std::invocable<U> auto &&f) XTAL_0EX_( &) {return transcopy<W>(XTAL_REF_(f));}
		template <array_q W> XTAL_TN1 transmorph(_std::invocable<U> auto &&f) XTAL_0FX_( &) {return transcopy<W>(XTAL_REF_(f));}
		template <array_q W> XTAL_TN1 transmove (_std::invocable<U> auto &&f) XTAL_0EX {based_t<W> w; _detail::move_to(w.begin(), self(), XTAL_REF_(f)); return w;}
		template <array_q W> XTAL_TN1 transcopy (_std::invocable<U> auto &&f) XTAL_0FX {based_t<W> w; _detail::copy_to(w.begin(), self(), XTAL_REF_(f)); return w;}

		///\
		Elementwise mutative transformer. \

		XTAL_TN1 transmorph(_std::invocable<U> auto &&...fs)
		XTAL_0EX
		{
			return (transmorph(XTAL_REF_(fs)), ...);
		}
		XTAL_TN1 transmorph(_std::invocable<U> auto &&f)
		XTAL_0EX
		{
			_detail::apply_to(self(), XTAL_REF_(f));
			return self();
		}
		

	public:// OPERATION

	//	Vector comparators (performed point-wise):
		XTAL_OP2 <=> (homotype const &t)
		XTAL_0FX
		{
			homotype const &s = *this;
			return\
				s <  t? _std::strong_ordering::      less:
			   s == t? _std::strong_ordering::     equal:
			   s  > t? _std::strong_ordering::   greater:
			           _std::strong_ordering::equivalent;
		}
		XTAL_OP2_(bool) == (homotype const &t)                 XTAL_0FX {return [&, this]<auto ...I>(bond::seek_t<I...>) XTAL_0FN_(...and (get(I) == t.get(I))) (bond::seek_f<N> {});}
		XTAL_OP2_(bool) <= (homotype const &t)                 XTAL_0FX {return [&, this]<auto ...I>(bond::seek_t<I...>) XTAL_0FN_(...and (get(I) <= t.get(I))) (bond::seek_f<N> {});}
		XTAL_OP2_(bool) >= (homotype const &t)                 XTAL_0FX {return [&, this]<auto ...I>(bond::seek_t<I...>) XTAL_0FN_(...and (get(I) >= t.get(I))) (bond::seek_f<N> {});}
		XTAL_OP2_(bool) <  (homotype const &t)                 XTAL_0FX {return [&, this]<auto ...I>(bond::seek_t<I...>) XTAL_0FN_(...and (get(I) <  t.get(I))) (bond::seek_f<N> {});}
		XTAL_OP2_(bool) >  (homotype const &t)                 XTAL_0FX {return [&, this]<auto ...I>(bond::seek_t<I...>) XTAL_0FN_(...and (get(I) >  t.get(I))) (bond::seek_f<N> {});}

	//	Vector operators (via `std::initializer_list` reconstruction):
		XTAL_OP1_(T &) <<= (braces_t<U> w)                     XTAL_0EX {return              self() <<= T(w);}
		XTAL_OP1_(T &) >>= (braces_t<U> w)                     XTAL_0EX {return              self() >>= T(w);}
		XTAL_OP1_(T &)  &= (braces_t<U> w)                     XTAL_0EX {return              self()  &= T(w);}
		XTAL_OP1_(T &)  ^= (braces_t<U> w)                     XTAL_0EX {return              self()  ^= T(w);}
		XTAL_OP1_(T &)  |= (braces_t<U> w)                     XTAL_0EX {return              self()  |= T(w);}
		XTAL_OP1_(T &)  *= (braces_t<U> w)                     XTAL_0EX {return              self()  *= T(w);}
		XTAL_OP1_(T &)  /= (braces_t<U> w)                     XTAL_0EX {return              self()  /= T(w);}
		XTAL_OP1_(T &)  += (braces_t<U> w)                     XTAL_0EX {return              self()  += T(w);}
		XTAL_OP1_(T &)  -= (braces_t<U> w)                     XTAL_0EX {return              self()  -= T(w);}

	//	Generic operators (via lifted assignment):
		XTAL_OP2_(T)   <<  (auto &&u)                          XTAL_0FX {return              twin() <<= XTAL_REF_(u);}
		XTAL_OP2_(T)   >>  (auto &&u)                          XTAL_0FX {return              twin() >>= XTAL_REF_(u);}

		XTAL_OP2_(T)    &  (auto &&u)                          XTAL_0FX {return              twin()  &= XTAL_REF_(u);}
		XTAL_OP2_(T)    ^  (auto &&u)                          XTAL_0FX {return              twin()  ^= XTAL_REF_(u);}
		XTAL_OP2_(T)    |  (auto &&u)                          XTAL_0FX {return              twin()  |= XTAL_REF_(u);}
		XTAL_OP2_(T)    *  (auto &&u)                          XTAL_0FX {return              twin()  *= XTAL_REF_(u);}
		XTAL_OP2_(T)    /  (auto &&u)                          XTAL_0FX {return              twin()  /= XTAL_REF_(u);}
		XTAL_OP2_(T)    +  (auto &&u)                          XTAL_0FX {return              twin()  += XTAL_REF_(u);}
		XTAL_OP2_(T)    -  (auto &&u)                          XTAL_0FX {return              twin()  -= XTAL_REF_(u);}

		XTAL_OP3_(T)    &  (anisomorphic_q<T> auto &&u, T &&t) XTAL_0EX {return XTAL_REF_(t).twin()  &= XTAL_REF_(u);}
		XTAL_OP3_(T)    ^  (anisomorphic_q<T> auto &&u, T &&t) XTAL_0EX {return XTAL_REF_(t).twin()  ^= XTAL_REF_(u);}
		XTAL_OP3_(T)    |  (anisomorphic_q<T> auto &&u, T &&t) XTAL_0EX {return XTAL_REF_(t).twin()  |= XTAL_REF_(u);}
		XTAL_OP3_(T)    *  (anisomorphic_q<T> auto &&u, T &&t) XTAL_0EX {return XTAL_REF_(t).twin()  *= XTAL_REF_(u);}
		XTAL_OP3_(T)    /  (anisomorphic_q<T> auto &&u, T &&t) XTAL_0EX {return XTAL_REF_(t).twin()  /= XTAL_REF_(u);}
		XTAL_OP3_(T)    +  (anisomorphic_q<T> auto &&u, T &&t) XTAL_0EX {return XTAL_REF_(t).twin()  += XTAL_REF_(u);}
		XTAL_OP3_(T)    -  (anisomorphic_q<T> auto &&u, T &&t) XTAL_0EX {return XTAL_REF_(t).twin()  -= XTAL_REF_(u);}

	//	Scalar operators (performed point-wise):
		XTAL_OP1_(T &) <<= (anisomorphic_q<T> auto &&u)        XTAL_0EX {bond::seek_forward_f<N>([u = XTAL_REF_(u), this] (auto i) XTAL_0FN_(get(i) <<= u)); return self();}
		XTAL_OP1_(T &) >>= (anisomorphic_q<T> auto &&u)        XTAL_0EX {bond::seek_forward_f<N>([u = XTAL_REF_(u), this] (auto i) XTAL_0FN_(get(i) >>= u)); return self();}
		XTAL_OP1_(T &)  *= (anisomorphic_q<T> auto &&u)        XTAL_0EX {bond::seek_forward_f<N>([u = XTAL_REF_(u), this] (auto i) XTAL_0FN_(get(i)  *= u)); return self();}
		XTAL_OP1_(T &)  /= (anisomorphic_q<T> auto &&u)        XTAL_0EX {bond::seek_forward_f<N>([u = XTAL_REF_(u), this] (auto i) XTAL_0FN_(get(i)  /= u)); return self();}

	//	XTAL_OP1_(T &)  *= (auto &&w) XTAL_0EX {return self() = self() * XTAL_REF_(w);}
	//	XTAL_OP1_(T &)  /= (auto &&w) XTAL_0EX {return self() = self() / XTAL_REF_(w);}
	//	XTAL_OP1_(T &)  += (auto &&w) XTAL_0EX {return self() = self() + XTAL_REF_(w);}
	//	XTAL_OP1_(T &)  -= (auto &&w) XTAL_0EX {return self() = self() - XTAL_REF_(w);}
		

	public:// CONSTRUCTION
	//	using T_::T_;

		~homotype() {};
		XTAL_CO4_(homotype)
		
		XTAL_CON homotype()
		XTAL_0EX
		:	homotype((size_t) 0)
		{}
		XTAL_CXN homotype(size_t n)
		XTAL_0EX
		{
			_std::uninitialized_value_construct_n(_std::next(T_::data(), n), T_::size() - n);
		}
		XTAL_CON homotype(braces_t<U> a)
		XTAL_0EX
		:	homotype(a.size())
		{
			_detail::copy_to(T_::begin(), a.begin(), a.end());
		}
		template <bounded_q A>
		XTAL_CXN homotype(A const &a)
		:	homotype(a.size())
		{
			_detail::copy_to(T_::begin(), a);
		}
		template <bounded_q A>
		XTAL_CXN homotype(A &&a)
		:	homotype(a.size())
		{
			_detail::move_to(T_::begin(), a);
		}
		
	};
	using type = bond::isotype<homotype>;

};

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
/**/
namespace std
{///////////////////////////////////////////////////////////////////////////////

template <xtal::atom::lattice_q T>
struct tuple_size<T> : xtal::cardinal_t<T::size()> {};

template <size_t N, xtal::atom::lattice_q T>
struct tuple_element<N, T> {using type = xtal::devalue_t<T>;};


}/////////////////////////////////////////////////////////////////////////////
/***/
XTAL_ENV_(pop)
