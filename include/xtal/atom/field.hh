#pragma once
#include "./any.hh"
#include "./groupoid.hh"
#include "./group.hh"




XTAL_ENV_(push)
namespace xtal::atom
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/*!
\brief   Extends `groupoid` with component-wise multiplication and addition.
\todo    Refactor `block`s like `cell`s to allow `bond::compose`.
*/
template <class ...Us>	struct  field_arithmetic;
template <class ...Us>	using   field_arithmetic_t = typename field_arithmetic<Us...>::type;
template <class ...Ts>	concept field_arithmetic_q = bond::tag_infixed_p<field_arithmetic_t, Ts...>;

XTAL_DEF_(let) field_arithmetic_f = [] XTAL_1FN_(call) (_detail::factory<field_arithmetic_t>::make);


template <scalar_q ...Us> requires same_q<Us...>
struct field_arithmetic<Us ...>
:	field_arithmetic<common_t<Us...>[sizeof...(Us)]>
{
};
template <class ...Us>
struct field_arithmetic
{
private:
	template <class T>
	using endotype = typename groupoid<Us...>::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<endotype<T>
	,	bond::tag<field_arithmetic_t>
	,	bond::tag<group_multiplication_t>
	,	bond::tag<group_addition_t>
	>;

public:
	/*!
	\brief
	Extends `groupoid` with component-wise multiplication and addition.
	*/
	template <class T>
	class homotype : public holotype<T>
	{
		using S_ = holotype<T>;
		using U_ = typename S_::value_type;

	public:// ACCESS
		using S_::size;
		using S_::self;
		using S_::twin;

	public:// CONSTRUCT
		using S_::S_;

	public:// OPERATE
		using S_::operator*; using S_::operator*=;
		using S_::operator/; using S_::operator/=;
		using S_::operator+; using S_::operator+=;
		using S_::operator-; using S_::operator-=;

		template <field_arithmetic_q W> XTAL_DEF_(return,inline,get) operator * (W const &w) const noexcept requires bond::tab_preference_p<W, T> {return w * self()  ;}
		template <field_arithmetic_q W> XTAL_DEF_(return,inline,get) operator * (W const &w) const noexcept requires bond::tab_precedence_p<T, W> {return S_::mul2_(w);}
		template <field_arithmetic_q W> XTAL_DEF_(return,inline,get) operator / (W const &w) const noexcept requires bond::tab_precedence_p<T, W> {return S_::div2_(w);}
		template <field_arithmetic_q W> XTAL_DEF_(mutate,inline,get) operator *=(W const &w)       noexcept requires bond::tab_precedence_p<T, W> {return S_::mul1_(w);}
		template <field_arithmetic_q W> XTAL_DEF_(mutate,inline,get) operator /=(W const &w)       noexcept requires bond::tab_precedence_p<T, W> {return S_::div1_(w);}

		template <field_arithmetic_q W> XTAL_DEF_(return,inline,get) operator + (W const &w) const noexcept requires bond::tab_preference_p<W, T> {return w + self()  ;}
		template <field_arithmetic_q W> XTAL_DEF_(return,inline,get) operator + (W const &w) const noexcept requires bond::tab_precedence_p<W, T> {return S_::add2_(w);}
		template <field_arithmetic_q W> XTAL_DEF_(return,inline,get) operator - (W const &w) const noexcept requires bond::tab_precedence_p<W, T> {return S_::sub2_(w);}
		template <field_arithmetic_q W> XTAL_DEF_(mutate,inline,get) operator +=(W const &w)       noexcept requires bond::tab_precedence_p<W, T> {return S_::add1_(w);}
		template <field_arithmetic_q W> XTAL_DEF_(mutate,inline,get) operator -=(W const &w)       noexcept requires bond::tab_precedence_p<W, T> {return S_::sub1_(w);}

		XTAL_DEF_(return,inline,get)    operator + () const noexcept {return twin();}
	//	XTAL_DEF_(return,inline,get)    operator + () const noexcept {return S_::template zip_from<[] (auto const &x) XTAL_0FN_(to) (+x)>(self());}
		XTAL_DEF_(return,inline,get)    operator - () const noexcept {return S_::template zip_from<[] (auto const &x) XTAL_0FN_(to) (-x)>(self());}

		XTAL_DEF_(mutate,inline,get)    operator *=(_std::initializer_list<U_> w)       noexcept requires same_q<Us...> {auto &s = self(); s *= T(w); return s;}
		XTAL_DEF_(mutate,inline,get)    operator /=(_std::initializer_list<U_> w)       noexcept requires same_q<Us...> {auto &s = self(); s /= T(w); return s;}

		XTAL_DEF_(mutate,inline,get)    operator +=(_std::initializer_list<U_> w)       noexcept requires same_q<Us...> {auto &s = self(); s += T(w); return s;}
		XTAL_DEF_(mutate,inline,get)    operator -=(_std::initializer_list<U_> w)       noexcept requires same_q<Us...> {auto &s = self(); s -= T(w); return s;}

	};
	using type = bond::derive_t<homotype>;

};


////////////////////////////////////////////////////////////////////////////////
/*!
\brief   Resolves as `*_field` based on the supplied operator.
*/
template <class     ...Ts>	XTAL_TYP_(new) field;
template <class     ...Ts>	XTAL_TYP_(let) field_t = typename field<Ts...>::type;
template <class     ...Ts>	XTAL_TYP_(ask) field_q = field_arithmetic_q<Ts...>;

template <class     ...Ts> struct field<_xtd::plus_multiplies <Ts>...>   : field_arithmetic<Ts...  > {};///<\brief Resolves as `field_arithmetic`.;
template <class U, auto N> struct field<_xtd::plus_multiplies <U>   [N]> : field_arithmetic<U   [N]> {};///<\brief Resolves as `field_arithmetic`.
template <class U, auto N> struct field<_xtd::plus_multiplies <U>(&)[N]> : field_arithmetic<U(&)[N]> {};///<\brief Resolves as `field_arithmetic`.


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
