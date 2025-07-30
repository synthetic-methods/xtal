#pragma once
#include "./any.hh"
#include "./point.hh"





XTAL_ENV_(push)
namespace xtal::atom
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/*!
\brief
Extends `point` with component-wise multiplication.
*/
template <class ...Us>	struct  group_multiplication;
template <class ...Us>	using   group_multiplication_t = typename group_multiplication<Us...>::type;
template <class ...Ts>	concept group_multiplication_q = bond::tag_infixed_p<group_multiplication_t, Ts...>;

XTAL_DEF_(let) group_multiplication_f = [] XTAL_1FN_(call) (_detail::factory<group_multiplication_t>::make);


template <scalar_q ...Us> requires common_q<Us...>
struct group_multiplication<Us ...>
:	group_multiplication<common_t<Us...>[sizeof...(Us)]>
{
};
template <class ...Us>
struct group_multiplication
{
private:
	template <class T>
	using endotype = typename point<Us...>::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<endotype<T>, bond::tag<group_multiplication_t>>;

public:
	/*!
	\brief
	Extends `point` with component-wise multiplication.
	*/
	template <class T>
	class homotype : public holotype<T>
	{
		using S_ = holotype<T>;
		using U_ = typename S_::value_type;

	public:// ACCESS
		using S_::size;
		using S_::self;

	public:// CONSTRUCT
	//	using S_::S_;
		XTAL_NEW_(delete) (homotype, noexcept = default)
		XTAL_NEW_(create) (homotype, noexcept = default)
		XTAL_NEW_(move)   (homotype, noexcept = default)
		XTAL_NEW_(copy)   (homotype, noexcept = default)
		XTAL_NEW_(cast)   (homotype, noexcept :        )
		XTAL_NEW_(then)   (homotype, noexcept : S_     )

		XTAL_NEW_(implicit)
		homotype()
		noexcept
		requires common_q<Us...>
		{
			_detail::initialize_with(S_::begin(), size(), U_{1});
		}
		/*!
		\brief  	Constructs the constant `group` using the `std::initializer_list` provided.
		If `1 == w.size()`, the provided value is repeated.
		*/
		XTAL_NEW_(implicit)
		homotype(_std::initializer_list<U_> xs)
		noexcept
		requires common_q<Us...>
		{
			auto const sN = xs.   size(); assert(sN <= size);
			auto       x0 = xs.  begin();
			auto       y0 = S_:: begin();
			_detail::move_to(y0, x0, sN);
			if (1 == sN) {_detail::initialize_with(_std::next(y0, sN), size() - sN, S_::front());}
		}

	public:// OPERATE
		using S_::operator*; using S_::operator*=;
		using S_::operator/; using S_::operator/=;

		template <group_multiplication_q W> XTAL_DEF_(return,inline,get) operator * (W const &w) const noexcept requires bond::tab_preference_p<W, T> {return w * self()  ;}
		template <group_multiplication_q W> XTAL_DEF_(return,inline,get) operator * (W const &w) const noexcept requires bond::tab_precedence_p<T, W> {return S_::mul2_(w);}
		template <group_multiplication_q W> XTAL_DEF_(return,inline,get) operator / (W const &w) const noexcept requires bond::tab_precedence_p<T, W> {return S_::div2_(w);}
		template <group_multiplication_q W> XTAL_DEF_(mutate,inline,get) operator *=(W const &w)       noexcept requires bond::tab_precedence_p<T, W> {return S_::mul1_(w);}
		template <group_multiplication_q W> XTAL_DEF_(mutate,inline,get) operator /=(W const &w)       noexcept requires bond::tab_precedence_p<T, W> {return S_::div1_(w);}

		XTAL_DEF_(mutate,inline,get)                   operator *=(_std::initializer_list<U_> w)       noexcept requires common_q<Us...> {auto &s = self(); s *= T(w); return s;}
		XTAL_DEF_(mutate,inline,get)                   operator /=(_std::initializer_list<U_> w)       noexcept requires common_q<Us...> {auto &s = self(); s /= T(w); return s;}

		/*!
		\returns	The reduction of `self` w.r.t. multiplication.
		*/
		XTAL_DEF_(return,inline,let)
		crush() const
		noexcept -> auto
		{
			return S_::template reduce<_std::multiplies<>{}>();
		}
		/*!
		\returns	The result of `blanked()` before refilling with `N_value=1`.
		*/
		template <auto N_value=1>
		XTAL_DEF_(inline,let)
		blanket()
		noexcept -> bool
		{
			return S_::template blanket<N_value>();
		}

	};
	using type = bond::derive_t<homotype>;

};


////////////////////////////////////////////////////////////////////////////////
/*!
\brief
Extends `point` with component-wise addition.
*/
template <class ...Us>	struct  group_addition;
template <class ...Us>	using   group_addition_t = typename group_addition<Us...>::type;
template <class ...Ts>	concept group_addition_q = bond::tag_infixed_p<group_addition_t, Ts...>;

XTAL_DEF_(let) group_addition_f = [] XTAL_1FN_(call) (_detail::factory<group_addition_t>::make);


template <scalar_q ...Us> requires common_q<Us...>
struct group_addition<Us ...>
:	group_addition<common_t<Us...>[sizeof...(Us)]>
{
};
template <class ...Us>
struct group_addition
{
private:
	template <class T>
	using endotype = typename point<Us...>::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<endotype<T>, bond::tag<group_addition_t>>;

public:
	template <class T>
	class homotype : public holotype<T>
	{
		using S_ = holotype<T>;
		using U_ = typename S_::value_type;

	public:// ACCESS
		using S_::size;
		using S_::self;

	public:// CONSTRUCT
		using S_::S_;

	public:// OPERATE
		using S_::operator+; using S_::operator+=;
		using S_::operator-; using S_::operator-=;

		template <group_addition_q W> XTAL_DEF_(return,inline,get) operator + (W const &w) const noexcept requires bond::tab_preference_p<W, T> {return w + self()  ;}
		template <group_addition_q W> XTAL_DEF_(return,inline,get) operator + (W const &w) const noexcept requires bond::tab_precedence_p<W, T> {return S_::add2_(w);}
		template <group_addition_q W> XTAL_DEF_(return,inline,get) operator - (W const &w) const noexcept requires bond::tab_precedence_p<W, T> {return S_::sub2_(w);}
		template <group_addition_q W> XTAL_DEF_(mutate,inline,get) operator +=(W const &w)       noexcept requires bond::tab_precedence_p<W, T> {return S_::add1_(w);}
		template <group_addition_q W> XTAL_DEF_(mutate,inline,get) operator -=(W const &w)       noexcept requires bond::tab_precedence_p<W, T> {return S_::sub1_(w);}

		XTAL_DEF_(mutate,inline,get)             operator +=(_std::initializer_list<U_> w)       noexcept requires common_q<Us...> {auto &s = self(); s += T(w); return s;}
		XTAL_DEF_(mutate,inline,get)             operator -=(_std::initializer_list<U_> w)       noexcept requires common_q<Us...> {auto &s = self(); s -= T(w); return s;}

		/*!
		\returns	The reduction of `self` w.r.t. addition.
		*/
		XTAL_DEF_(return,inline,let)
		crush() const
		noexcept -> auto
		{
			return S_::template reduce<_std::plus<>{}>();
		}

	};
	using type = bond::derive_t<homotype>;

};


////////////////////////////////////////////////////////////////////////////////
/*!
\brief
Resolves as `*_group` based on the supplied operator.
*/
template <class T        > struct group;

template <class U, auto N> struct group<_std::multiplies <U>   [N]> : group_multiplication<U   [N]> {};///<\brief Resolves as `group_multiplication`.
template <class U, auto N> struct group<_std::multiplies <U>(&)[N]> : group_multiplication<U(&)[N]> {};///<\brief Resolves as `group_multiplication`.

template <class U, auto N> struct group<_std::plus       <U>   [N]> : group_addition      <U   [N]> {};///<\brief Resolves as `group_addition`.
template <class U, auto N> struct group<_std::plus       <U>(&)[N]> : group_addition      <U(&)[N]> {};///<\brief Resolves as `group_addition`.

template <class ...Ts>	concept group_q = group_multiplication_q<Ts...> or group_addition_q<Ts...>;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
