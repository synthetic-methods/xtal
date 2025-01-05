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
template <class   ...Ts>	concept          phason_q = bond::tag_p<phason_t, Ts...>;
template <class   ...Ts>	concept     real_phason_q = bond::tag_p<phason_t, Ts...> and   real_number_q<initializer_u<Ts>...>;
template <class   ...Ts>	concept  simplex_phason_q = bond::tag_p<phason_t, Ts...> and simplex_field_q<initializer_u<Ts>...>;
template <class   ...Ts>	concept  complex_phason_q = bond::tag_p<phason_t, Ts...> and complex_field_q<initializer_u<Ts>...>;
template <class  V=void>
XTAL_DEF_(short)
XTAL_LET phason_f(auto &&...oo)
noexcept -> auto
{
	return _detail::initialize<phason_t>::template via<V>(XTAL_REF_(oo)...);
}


////////////////////////////////////////////////////////////////////////////////

template <vector_q A> requires real_number_q<absolve_u<A>>
struct phason<A>
{
	XTAL_SET M_data = _std::extent_v<based_t<A>>;

	using coordinate_type = valued_u<A>;

	using U_   = bond::  forge<coordinate_type>;
	using U_op = bond::operate<coordinate_type>;
	using T_op = typename U_op::template widen<-1>;
	
	using   ordinate_type = bond::compose_s<typename T_op::sigma_type, U_>;
	using inordinate_type = bond::compose_s<typename T_op::delta_type, U_>;

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

	public:// TYPE

		using supertype = S_;


	public:// MAP

		XTAL_DEF_(set)   ordinate(coordinate_type const &co) noexcept {return U_op::template bit_fraction_f<  ordinate_type>(co);}
		XTAL_DEF_(set) coordinate(  ordinate_type const & o) noexcept {return T_op::template     fraction_f<coordinate_type>( o);}

	public:// ACCESS
		using S_::self;
		using S_::twin;

	public:// CONSTRUCT
	//	using S_::S_;
	~	homotype()                noexcept=default;
	//	homotype()                noexcept=default;
		XTAL_NEW_(copy, homotype, noexcept=default)
		XTAL_NEW_(move, homotype, noexcept=default)

		XTAL_NEW_(implicit) homotype()
		noexcept
		:	homotype(size_0)
		{}
		
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
		XTAL_NEW_(implicit) homotype(initializer_s<coordinate_type> o)
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
		XTAL_LET operator >>=(initializer_s<coordinate_type>  o)
		noexcept -> auto &
		{
			auto i0 = S_::data();
			_detail::move_to<XTAL_FUN_(T::ordinate)>(i0, XTAL_REF_(o));
			return self();
		}
		XTAL_DEF_(inline)
		XTAL_LET operator >>=(iterable_q auto &&o)
		noexcept -> auto &
		{
			auto i0 = S_::data();
			_detail::move_to<XTAL_FUN_(T::ordinate)>(i0, XTAL_REF_(o));
			return self();
		}
		XTAL_DEF_(inline)
		XTAL_LET operator >>=(iterable_q auto const &o)
		noexcept -> auto &
		{
			auto i0 = S_::data();
			_detail::copy_to<XTAL_FUN_(T::ordinate)>(i0, XTAL_REF_(o));
			return self();
		}
		
		XTAL_DEF_(inline)
		XTAL_LET operator <<=(initializer_s<coordinate_type> o)
		noexcept -> auto &
		{
			auto i0 = S_::data(), iN = _std::next(i0, S_::size() - o.size());
			_detail::move_to<XTAL_FUN_(T::ordinate)>(iN, XTAL_REF_(o));
			return self();
		}
		XTAL_DEF_(inline)
		XTAL_LET operator <<=(iterable_q auto &&o)
		noexcept -> auto &
		{
			auto i0 = S_::data(), iN = _std::next(i0, S_::size() - o.size());
			_detail::move_to<XTAL_FUN_(T::ordinate)>(iN, XTAL_REF_(o));
			return self();
		}
		XTAL_DEF_(inline)
		XTAL_LET operator <<=(iterable_q auto const &o)
		noexcept -> auto &
		{
			auto i0 = S_::data(), iN = _std::next(i0, S_::size() - o.size());
			_detail::copy_to<XTAL_FUN_(T::ordinate)>(iN, XTAL_REF_(o));
			return self();
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

		XTAL_DEF_(short)  XTAL_LET operator * (auto const &t) const noexcept -> auto {return twin() *= t;}
		XTAL_DEF_(short)  XTAL_LET operator / (auto const &t) const noexcept -> auto {return twin() /= t;}

		XTAL_DEF_(inline) XTAL_LET operator *= (initializer_s<coordinate_type> t) noexcept -> auto & {return self() *= T(t);}
		XTAL_DEF_(inline) XTAL_LET operator /= (initializer_s<coordinate_type> t) noexcept -> auto & {return self() /= T(t);}

		XTAL_DEF_(inline)
		XTAL_LET operator /= (number_q auto const &f)
		noexcept -> auto &
		{
			return operator*=(one/f);
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
		XTAL_LET operator *= (integral_number_q auto const &i)
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
		XTAL_LET operator += (integral_number_q auto const &i)
		noexcept -> auto &
		{
			return self();
		}
		XTAL_DEF_(inline)
		XTAL_LET operator += (real_number_q auto const &f)
		noexcept -> auto &
		{
			get<0>(*this) += T_op::bit_fraction_f(f);
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
