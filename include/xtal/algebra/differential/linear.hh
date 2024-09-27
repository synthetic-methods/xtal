#pragma once
#include "./any.hh"
#include "../serial.hh"
#include "../series.hh"




XTAL_ENV_(push)
namespace xtal::algebra::differential
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class   ..._s>	XTAL_TYP linear;
template <class   ..._s>	XTAL_USE linear_t = typename linear<_s...>::type;
template <class   ...Ts>	XTAL_REQ linear_q = bond::any_tag_p<linear_t, Ts...>;
template <class  V=void>
XTAL_DEF_(return,inline)
XTAL_LET linear_f(auto &&...oo)
XTAL_0EX {return _detail::initialize<linear_t>::template via<V>(XTAL_REF_(oo)...);}


////////////////////////////////////////////////////////////////////////////////
///\
Extends `serial` with succession. \

template <column_q A>
struct linear<A>
{
	using _op = bond::operate<A>;
	
	template <class T>
	using allotype = typename serial<A>::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<allotype<T>, bond::tag<linear_t>>;

	template <class T>
	class homotype : public holotype<T>
	{
		friend T;
		using  S_ = holotype<T>;
	
	protected:
		using          S_::N_data;
		using typename S_::U_data;

	public:// CONSTRUCT
		using S_::S_;

	public:// OPERATE
	//	using S_::get;
		using S_::let;
		using S_::self;
		using S_::twin;

		template <class Y=U_data>
		XTAL_DEF_(inline)
		XTAL_LET advice()
		XTAL_0EX -> auto
		{
		//TODO: Should accumulate `advice` for all except the last element? Or like all?
		//TODO: Handle downwards ramps too, so should just ensure they are all identical or whatever.
			using _op = bond::operate<Y>;
			using alpha_type = typename _op::alpha_type;
			using sigma_type = typename _op::sigma_type;
			using delta_type = typename _op::delta_type;

			auto const sign_bit = get<0>(*this)&_op::sign.mask;
			auto const sign_val = static_cast<Y>(sign_bit) >> _op::sign.shift;
			XTAL_IF0
			XTAL_0IF (       is_q<bool, Y>) {return !sign_bit;}
			XTAL_0IF (integral_number_q<Y>) {return  sign_val;}
			XTAL_0IF (    real_number_q<Y>) {return _xtd::bit_cast<alpha_type>(sign_bit|sign_val&_op::unit.mask);}
		}
		template <int N=1>
		XTAL_DEF_(inline)
		XTAL_LET advent()
		XTAL_0EX -> auto
		{
			auto &s = self();
			auto const n = s.advice(); s.template advance<N>();
			auto const m = s.advice(); return m^n;
		}
		template <int N=1>
		XTAL_DEF_(inline)
		XTAL_LET advance()
		XTAL_0EX -> T &
		{
			XTAL_IF0
			XTAL_0IF (0 < N) {
				return operator++();
			}
			XTAL_0IF (N < 0) {
				return operator--();
			}
		}
		template <int N=1>
		XTAL_DEF_(inline)
		XTAL_LET advanced()
		XTAL_0EX -> T
		{
			XTAL_IF0
			XTAL_0IF (0 < N) {
				return operator++(0);
			}
			XTAL_0IF (N < 0) {
				return operator--(0);
			}
		}
		///\
		Produces the successor by pairwise addition from `begin()` to `end()`, \
		assuming the entries of `this` are finite differences/derivatives. \

		XTAL_DEF_(inline)
		XTAL_LET operator ++ (int)
		XTAL_0EX -> T
		{
			auto t = twin(); operator++(); return t;
		}
		XTAL_DEF_(inline)
		XTAL_LET operator ++ ()
		XTAL_0EX -> T &
		{
			auto &s = self();

			[&]<auto ...I> (bond::seek_t<I...>)
			XTAL_0FN {
				if constexpr (_std::is_signed_v<U_data>) {
					((reinterpret_cast<_std::make_unsigned_t<U_data> &>(get<I>(s)) += get<I + 1>(s)^advice()),...);

				}
				else {
					((get<I>(s) += get<I + 1>(s)),...);
				}
			}
			(bond::seek_s<N_data - 1>{});
			
			return s;
		}

		///\
		Produces the predecessor by pairwise subtraction from `end()` to `begin()`, \
		assuming the entries of `this` are finite differences/derivatives. \

		XTAL_DEF_(inline)
		XTAL_LET operator -- (int)
		XTAL_0EX -> T
		{
			auto t = twin(); operator--(); return t;
		}
		XTAL_DEF_(inline)
		XTAL_LET operator -- ()
		XTAL_0EX -> T &
		{
			auto &s = self();

			[&]<auto ...I> (bond::seek_t<I...>)
			XTAL_0FN {
				if constexpr (_std::is_signed_v<U_data>) {
					((reinterpret_cast<_std::make_unsigned_t<U_data> &>(get<I>(s)) -= get<I + 1>(s)^advice()),...);
				}
				else {
					((get<I>(s) -= get<I + 1>(s)),...);
				}
			}
			(bond::antiseek_s<N_data - 1>{});
			
			return s;
		}

	};
	using type = bond::isotype<homotype>;

};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
