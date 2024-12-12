#pragma once
#include "./any.hh"
#include "./serial.hh"





XTAL_ENV_(push)
namespace xtal::algebra
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
Extends `serial` as a fixed-point fractional/cyclic value with a bisected representation. \
\
Allows floating-point construction via `std::initializer_list`, \
and access to the floating-point value via `operator()`/`operator(size_type)`. \
\
Implements truncated floating-point multiplication (affecting all elements) \
and addition (affecting only the initial element). \

///\todo\
Might be worth implementing multiplication for the first element only, \
either by truncating the type or by parameterizing the operator. \
The latter could be achieved using `std::initializer_list`s, \
parameterized by an `continuous_field_q`-wrapper with a distinguished head. \

///\todo\
Rework `operator`s to accommodate `std::complex`. \

template <class   ..._s>	struct           phason;
template <class   ..._s>	using            phason_t = typename phason<_s...>::type;
template <class   ...Ts>	concept          phason_q = bond::any_tag_p<phason_t, Ts...>;
template <class   ...Ts>	concept     real_phason_q = bond::any_tag_p<phason_t, Ts...> and   real_number_q<initializer_u<Ts>...>;
template <class   ...Ts>	concept  simplex_phason_q = bond::any_tag_p<phason_t, Ts...> and simplex_field_q<initializer_u<Ts>...>;
template <class   ...Ts>	concept  complex_phason_q = bond::any_tag_p<phason_t, Ts...> and complex_field_q<initializer_u<Ts>...>;
template <class  V=void>
XTAL_DEF_(short)
XTAL_LET phason_f(auto &&...oo)
noexcept -> auto
{
	return _detail::initialize<phason_t>::template via<V>(XTAL_REF_(oo)...);
}


namespace _detail
{///////////////////////////////////////////////////////////////////////////////

template <        class V> struct circumspect    : circumspect<absolve_u<V>> {};
template <    integer_q V> struct circumspect<V> : bond::operate<V>::template widen< 0> {};
template <real_number_q V> struct circumspect<V> : bond::operate<V>::template widen<-1> {};

template <class V>
struct circumscribe : circumspect<V>
{
	using _op = circumspect<V>;
	using _Op = typename _op::template widen<1>;

	using   ordinate_type = typename _op::sigma_type;
	using inordinate_type = typename _op::delta_type;
	using coordinate_type = typename _Op::alpha_type;

	XTAL_DEF_(short,static)
	XTAL_LET    ordinate(real_number_q auto const &co)
	noexcept -> ordinate_type
	{
		return _op::sigma_f(_op::fractional_f(co));
	};
	XTAL_DEF_(short,static)
	XTAL_LET    coordinate(integer_q auto const &o)
	noexcept -> coordinate_type
	{
		return _Op::haplo_f(_op::full.depth)*_Op::alpha_f(_op::delta_f(o));
	};

};
template <complex_number_q A>
struct circumscribe<A> : circumscribe<valued_u<A>>
{
	using _op = circumscribe<valued_u<A>>;

	using   ordinate_type = _std::complex<typename _op::  ordinate_type>;
	using inordinate_type = _std::complex<typename _op::inordinate_type>;
	using coordinate_type = _std::complex<typename _op::coordinate_type>;

	XTAL_DEF_(short,static)
	XTAL_LET    ordinate(coordinate_type const &co)
	noexcept -> ordinate_type
	{
		auto const o_re = _op::ordinate(co.real());
		auto const o_im = _op::ordinate(co.imag());
		return {o_re, o_im};
	};
	XTAL_DEF_(short,static)
	XTAL_LET    coordinate(ordinate_type const &o)
	noexcept -> coordinate_type
	{
		auto const co_re = _op::coordinate(o.real());
		auto const co_im = _op::coordinate(o.imag());
		return {co_re, co_im};
	};
};
template <column_q A>
struct circumscribe<A> : circumscribe<valued_u<A>>
{
};

static_assert(circumspect <double>::full.width == circumspect <int>::full.width);
static_assert(circumscribe<double>::full.width == circumscribe<int>::full.width);


}///////////////////////////////////////////////////////////////////////////////

template <column_q A>
struct phason<A>
{
	using T_op = _detail::circumscribe<A>;
	using U_op = bond::operate<typename T_op::coordinate_type>;
	
	XTAL_SET M_data = _std::extent_v<based_t<A>>;

	using   ordinate_type = typename T_op::  ordinate_type;
	using inordinate_type = typename T_op::inordinate_type;
	using coordinate_type = typename T_op::coordinate_type;

	static_assert(_std::numeric_limits<absolve_u<ordinate_type>>::is_modulo);// D'oh!

	using holotag  = bond::tag<phason_t>;
	using holokind = serial<ordinate_type[M_data]>;

	template <class T>
	using holotype = bond::compose_s<typename holokind::template homotype<T>, holotag>;

	template <class T>
	class homotype : public holotype<T>
	{
		using  S_ = holotype<T>;

	protected:
		using          S_::N_data;
		using typename S_::U_data;
		using initializer_list = _std::initializer_list<coordinate_type>;

	public:// TYPE

		using supertype = S_;


	public:// MAP

		XTAL_DEF_(short,static)
		XTAL_LET ordinate(coordinate_type const &co)
		noexcept -> ordinate_type
		{
			return T_op::ordinate(co);
		}
		XTAL_DEF_(short,static)
		XTAL_LET coordinate(ordinate_type const &o)
		noexcept -> coordinate_type
		{
			return T_op::coordinate(o);
		}

	public:// ACCESS
		using S_::self;
		using S_::twin;
		using S_::let;

	public:// CONSTRUCT
	//	using S_::S_;

	~	homotype() noexcept=default;
	//	homotype() noexcept=default;

		XTAL_NEW_(implicit) homotype()
		noexcept
		:	homotype(size_0)
		{}
		XTAL_NEW_(copy, homotype, noexcept=default)
		XTAL_NEW_(move, homotype, noexcept=default)
		
		XTAL_NEW_(explicit) homotype(size_type const n)
		noexcept
		:	S_(n)
		{}

		XTAL_NEW_(explicit) homotype(real_number_q auto &&...oo)
		noexcept
		:	homotype(sizeof...(oo))
		{
			operator>>=({XTAL_REF_(oo)...});
		}
		XTAL_NEW_(implicit) homotype(initializer_list o)
		noexcept
		:	homotype(count_f(o))
		{
			operator>>=(XTAL_REF_(o));
		}
		XTAL_NEW_(explicit) homotype(iterable_q auto &&o)
		noexcept
		:	homotype(count_f(o))
		{
			operator>>=(XTAL_REF_(o));
		}
		
	public:// RECONSTRUCT
		using S_::operator >>=;
		using S_::operator <<=;

		XTAL_DEF_(inline)
		XTAL_LET operator >>=(initializer_list  o)
		noexcept -> homotype &
		{
			_detail::copy_to(S_::data()
			,	XTAL_REF_(o), [this] XTAL_1FN_(self().ordinate)
			);
			return *this;
		}
		XTAL_DEF_(inline)
		XTAL_LET operator >>=(iterable_q auto &&o)
		noexcept -> homotype &
		{
			_detail::move_to(S_::data()
			,	XTAL_REF_(o), [this] XTAL_1FN_(self().ordinate)
			);
			return *this;
		}
		
		XTAL_DEF_(inline)
		XTAL_LET operator <<=(initializer_list  o)
		noexcept -> homotype &
		{
			_detail::copy_to(_std::next(S_::data(), S_::size() - o.size())
			,	XTAL_REF_(o), [this] XTAL_1FN_(self().ordinate)
			);
			return *this;
		}
		XTAL_DEF_(inline)
		XTAL_LET operator <<=(iterable_q auto &&o)
		noexcept -> homotype &
		{
			_detail::move_to(_std::next(S_::data(), S_::size() - o.size())
			,	XTAL_REF_(o), [this] XTAL_1FN_(self().ordinate)
			);
			return *this;
		}

	public:// OPERATE
		
		///\
		Scales all elements. \

		///\note\
		The symmetric signatures for `/=` and `*=` are declared-but-undefined \
		to avoid compilation-failure when type-checking e.g. `multiplicative_group_q`. \

		using S_::operator*=;
		using S_::operator/=;

		auto operator *= (T const &) noexcept -> T &;// Asymmetric!
		auto operator /= (T const &) noexcept -> T &;// Asymmetric!

		XTAL_DEF_(short)
		XTAL_LET operator * (auto const &t) const
		noexcept -> auto {
			return twin() *= t;
		}
		XTAL_DEF_(short)
		XTAL_LET operator / (auto const &t) const
		noexcept -> auto {
			return twin() /= t;
		}
		XTAL_DEF_(inline)
		XTAL_LET operator *= (initializer_list t)
		noexcept -> auto &
		{
			return self() *= T(t);
		}
		XTAL_DEF_(inline)
		XTAL_LET operator /= (initializer_list t)
		noexcept -> auto &
		{
			return self() /= T(t);
		}

		XTAL_DEF_(inline)
		XTAL_LET operator /= (number_q auto const &f)
		noexcept -> auto &
		{
			return operator*=(T_op::alpha_1/f);
		}
	//	XTAL_DEF_(inline)
		XTAL_LET operator *= (real_number_q auto const &f)
		noexcept -> auto &
		{
			using _op = bond::operate<decltype(f)>;
			auto &s = reinterpret_cast<serial_t<inordinate_type[N_data]> &>(self());
			/*/
			size_type constexpr M_bias = T_op::half.depth >> T_op::half.width;
			size_type constexpr M_size = T_op::half.depth - M_bias;
			auto [m, n] = bond::operate<decltype(f)>::scientific_f(f);
			m >>= n - M_size;
			s >>=     M_size;
			s  *= m;
			/*/
			XTAL_IF0
			XTAL_0IF (1*sizeof(ordinate_type) == sizeof(coordinate_type)) {
				int constexpr M_bias = T_op::half.depth >> T_op::half.width;
				int constexpr M_size = T_op::half.depth - M_bias;
				auto [m, n] = _op::scientific_f(f);
				m >>= n - M_size;
				s >>=     M_size;
				s  *= m;
			}
			XTAL_IF0
			XTAL_0IF (2*sizeof(ordinate_type) == sizeof(coordinate_type)) {
				typename T_op::sigma_type t_[2];
				typename U_op::sigma_type const u(f*_op::diplo_f(T_op::full.depth));
				#pragma unroll
				for (int i{}; i < N_data; ++i) {
					reinterpret_cast<typename U_op::sigma_type &>(t_) = u*s[i];
				//	t_[1] += t_[0] >> T_op::positive.depth;// Round...
					s [i]  = t_[1];
				}
			}
			/***/
			return self();
		}
		XTAL_DEF_(inline)
		XTAL_LET operator *= (integer_q auto const &i)
		noexcept -> auto &
		{
			return S_::operator*=(i);
		}

		///\
		Offsets the first element. \
		
		using S_::operator-=;
		using S_::operator+=;

		XTAL_DEF_(inline)
		XTAL_LET operator -= (number_q auto const &f)
		noexcept -> auto &
		{
			return operator+=(-f);
		}
		XTAL_DEF_(inline)
		XTAL_LET operator += (integer_q auto const &i)
		noexcept -> auto &
		{
			return self();
		}
		XTAL_DEF_(inline)
		XTAL_LET operator += (real_number_q auto const &f)
		noexcept -> auto &
		{
			get<0>(*this) += T_op::fractional_f(f);
			return self();
		}

		template <class Y=coordinate_type>
		XTAL_DEF_(short)
		XTAL_LET continuity()
		noexcept -> Y
		{
			return condition_f<Y>(not discontinuity<bool>());
		}
		template <class Y=coordinate_type>
		XTAL_DEF_(short)
		XTAL_LET discontinuity()
		noexcept -> Y
		{
			auto [u0, u1] = *this;
			auto const v0 = _xtd::bit_cast<inordinate_type>(u0) >> T_op::positive.depth; u0 ^= v0; u0 -= v0;
			auto const v1 = _xtd::bit_cast<inordinate_type>(u1) >> T_op::positive.depth; u1 ^= v1; u1 -= v1;
			return condition_f<Y>(v0 == v1 and u0 < u1);
		}

	};
	using type = bond::isotype<homotype>;

};
static_assert(atomic_q<phason_t<float[2]>>);

static_assert(bond::pack_size_q<phason_t<double[2]>>);


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
