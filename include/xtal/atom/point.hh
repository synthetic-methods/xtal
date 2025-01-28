#pragma once
#include "./any.hh"
#include "./quanta.hh"





XTAL_ENV_(push)
namespace xtal::atom
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
Extends `quanta` with point-wise operation. \

template <        class ..._s>	struct   point;
template <        class ..._s>	using    point_t = typename point<_s...>::type;
template <        class ..._s>	concept  point_q = bond::array_tag_p<point_t, _s...> and same_n<sized_n<_s>...>;

template <class U, auto  N, auto  ..._s> struct   point<U   [N][_s]...> : point<point_t<U[_s]...>   [N]> {};
template <class U, auto  N, auto  ..._s> struct   point<U(&)[N][_s]...> : point<point_t<U[_s]...>(&)[N]> {};


XTAL_FX0_(alias) (template <auto f=invoke_n<>>
XTAL_DEF_(return,inline,let) point_f(auto &&...oo),
	_detail::build<point_t>::template static_factory<f>(XTAL_REF_(oo)...))


////////////////////////////////////////////////////////////////////////////////

template <class ..._s>
struct point
{
	template <class T>
	using endotype = typename quanta<_s...>::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<endotype<T>, bond::tag<point_t>>;

	template <class T>
	class homotype : public holotype<T>
	{
		using S_ = holotype<T>;

	protected:
		using          S_::N_data;
		using typename S_::T_data;
		using typename S_::U_data;
		using typename S_::V_data;

		static V_data constexpr V1{1};

	public:// CONSTRUCT
		using S_::S_;

	public:// OPERATE
		using S_::self;
		using S_::twin;
		using S_::size;

		template <auto f>
		XTAL_DEF_(inline,let)
		pointwise()
		noexcept -> auto &
		requires requires (T_data &u) {f(u);}
		{
			auto &s = self();

			[&]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN {(f(get<I>(s)),...);}
			(bond::seek_s<N_data>{});
			
			return s;
		}
		template <auto f>
		XTAL_DEF_(inline,let)
		pointwise(fixed_sized_q auto const &t)
		noexcept -> auto &
		requires requires (T_data &u, XTAL_ALL_(get<0>(t)) const &v) {f(u, v);}
		{
			size_type constexpr N = bond::pack_size_n<decltype(t)>;
			static_assert(N <= N_data);

			auto &s = self();

			[&]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN {(f(get<I>(s), get<I>(t)),...);}
			(bond::seek_s<N>{});
			
			return s;
		}

		template <auto f>
		XTAL_DEF_(return,inline,set)
		pointwise(T const &s)
		noexcept -> auto
		requires requires (T_data const &u) {f(u);}
		{
			using T_ = typename S_::template reforge_t<based_t<_s>...>;

			return [&]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN_(return) (T_{f(get<I>(s))...})
			(bond::seek_s<N_data>{});
		}
		template <auto f>
		XTAL_DEF_(return,inline,set)
		pointwise(T const &s, fixed_sized_q auto const &t)
		noexcept -> auto
		requires requires (T_data const &u, XTAL_ALL_(get<0>(t)) const &v) {f(u, v);}
		{
			size_type constexpr N = bond::pack_size_n<decltype(t)>;
			static_assert(N <= N_data);
			using T_ = typename S_::template reforge_t<based_t<_s>...>;

			return [&]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN_(return) (T_{f(get<I>(s), get<I>(t))...})
			(bond::seek_s<N>{});
		}
		template <auto f>
		XTAL_DEF_(return,inline,set)
		pointwise(T const &s, T_data const &v)
		noexcept -> auto
		requires requires (T_data const &u) {f(u, v);}
		{
			using T_ = typename S_::template reforge_t<based_t<_s>...>;

			return [&]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN_(return) (T_{f(get<I>(s), v)...})
			(bond::seek_s<N_data>{});
		}

		template <auto f, size_t I=N_data - 1>
		XTAL_DEF_(return,inline,let)
		pointless() const
		{
			XTAL_IF0
			XTAL_0IF (0 == I) {return   get<I>(self())                        ;}
			XTAL_0IF (1 <= I) {return f(get<I>(self()), pointless<f, I - 1>());}
		}

		template <int N_sgn=1>
		XTAL_DEF_(inline,let)
		flip()
		noexcept -> auto &
		{
			XTAL_IF0
			XTAL_0IF (0 <= N_sgn) {
				return self();
			}
			XTAL_0IF (N_sgn <  0) {
				return pointwise<[] (auto &x) XTAL_0FN_(return) (x = -XTAL_MOV_(x))>();
			}
		}
		template <int N_sgn=1>
		XTAL_DEF_(inline,let)
		flipped()
		noexcept -> auto
		{
			return twin().template flip<N_sgn>();
		}

	//	Scalar assignment (performed point-wide):
		XTAL_DEF_(inline,let) operator <<= (size_type const &u) noexcept -> T  & {bond::seek_forward_f<N_data>([&, this] (auto I) XTAL_0FN {get<I>(self()) <<= u;}); return self();}
		XTAL_DEF_(inline,let) operator >>= (size_type const &u) noexcept -> T  & {bond::seek_forward_f<N_data>([&, this] (auto I) XTAL_0FN {get<I>(self()) >>= u;}); return self();}

		XTAL_DEF_(inline,let) operator  ^= (auto const &u) noexcept -> T  & requires requires (T_data &w) {w ^= u;} {bond::seek_forward_f<N_data>([       &, this] (auto I) XTAL_0FN {get<I>(self())  ^= u;}); return self();}
		XTAL_DEF_(inline,let) operator  |= (auto const &u) noexcept -> T  & requires requires (T_data &w) {w |= u;} {bond::seek_forward_f<N_data>([       &, this] (auto I) XTAL_0FN {get<I>(self())  |= u;}); return self();}
		XTAL_DEF_(inline,let) operator  &= (auto const &u) noexcept -> T  & requires requires (T_data &w) {w &= u;} {bond::seek_forward_f<N_data>([       &, this] (auto I) XTAL_0FN {get<I>(self())  &= u;}); return self();}
		XTAL_DEF_(inline,let) operator  %= (auto const &u) noexcept -> T  & requires requires (T_data &w) {w %= u;} {bond::seek_forward_f<N_data>([       &, this] (auto I) XTAL_0FN {get<I>(self())  %= u;}); return self();}
		XTAL_DEF_(inline,let) operator  /= (auto const &u) noexcept -> T  & requires requires (T_data &w) {w /= u;} {bond::seek_forward_f<N_data>([n = V1/u, this] (auto I) XTAL_0FN {get<I>(self())  *= n;}); return self();}
		XTAL_DEF_(inline,let) operator  *= (auto const &u) noexcept -> T  & requires requires (T_data &w) {w *= u;} {bond::seek_forward_f<N_data>([       &, this] (auto I) XTAL_0FN {get<I>(self())  *= u;}); return self();}
	//	XTAL_DEF_(inline,let) operator  -= (auto const &u) noexcept -> T  & requires requires (T_data &w) {w -= u;} {bond::seek_forward_f<N_data>([       &, this] (auto I) XTAL_0FN {get<I>(self())  -= u;}); return self();}
	//	XTAL_DEF_(inline,let) operator  += (auto const &u) noexcept -> T  & requires requires (T_data &w) {w += u;} {bond::seek_forward_f<N_data>([       &, this] (auto I) XTAL_0FN {get<I>(self())  += u;}); return self();}

		XTAL_DEF_(return,inline,friend,let)
		operator * (auto const &s, T const &t)
		noexcept -> auto
		requires (dissolve_r<decltype(s)> < dissolve_r<T>)
		{
			return t * s;
		}
		XTAL_DEF_(return,inline,friend,let)
		operator + (auto const &s, T const &t)
		noexcept -> auto
		requires (dissolve_r<decltype(s)> < dissolve_r<T>)
		{
			return t + s;
		}

//		XTAL_DEF_(return,inline,friend,let)
//		operator - (T const &s)
//		noexcept -> auto
//		{
//			return pointwise<[] (auto const &x) XTAL_0FN_(return) (-x)>(s);
//		}


	};
	using type = derive_t<homotype>;

};


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
