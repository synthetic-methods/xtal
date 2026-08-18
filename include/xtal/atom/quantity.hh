#pragma once
#include "./any.hh"
#include "./quantify.hh"





XTAL_ENV_(push)
namespace xtal::atom
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

/*!
\brief   Extends `quantify` with component-wise operation.
\detail  Resolves as `*_group` based on the supplied operator.
\todo    Refactor `bucket`s like `cell`s to allow `bond::compose`.
*/
template <class     ...Us>	XTAL_TYP_(new) quantity;
template <class     ...Us>	XTAL_TYP_(new) quantity_plus_multiplies;
template <class     ...Us>	XTAL_TYP_(new) quantity_multiplies;
template <class     ...Us>	XTAL_TYP_(new) quantity_plus;

template <class     ...Us>	XTAL_TYP_(let) quantity_t                = typename quantity                <Us...>::type;
template <class     ...Us>	XTAL_TYP_(let) quantity_plus_multiplies_t     = typename quantity_plus_multiplies     <Us...>::type;
template <class     ...Us>	XTAL_TYP_(let) quantity_multiplies_t = typename quantity_multiplies <Us...>::type;
template <class     ...Us>	XTAL_TYP_(let) quantity_plus_t       = typename quantity_plus       <Us...>::type;

template <class     ...Ts>	XTAL_TYP_(ask) quantity_plus_multiplies_q     = bond::tag_inner_fixed_p<quantity_plus_multiplies_t     , Ts...>;
template <class     ...Ts>	XTAL_TYP_(ask) quantity_plus_q                = bond::tag_inner_fixed_p<quantity_plus_t                , Ts...>;
template <class     ...Ts>	XTAL_TYP_(ask) quantity_multiplies_q          = bond::tag_inner_fixed_p<quantity_multiplies_t          , Ts...>;
template <class     ...Ts>	XTAL_TYP_(ask) quantity_q = quantity_plus_multiplies_q<Ts...> or quantity_multiplies_q<Ts...> or quantity_plus_q<Ts...>;


////////////////////////////////////////////////////////////////////////////////

template <scalar_array_q ...Us> requires same_q<Us...>
struct quantity_plus_multiplies<Us ...> : quantity_plus_multiplies<common_t<Us...>[sizeof...(Us)]>
{};
template <class ...Us>
struct quantity_plus_multiplies
{
private:
	template <class T>
	using endotype = typename quantify<Us...>::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<endotype<T>
	,	bond::tag<quantity_plus_t>
	,	bond::tag<quantity_multiplies_t>
	,	bond::tag<quantity_plus_multiplies_t>
	>;

public:
	/*!
	\brief
	Extends `quantify` with component-wise multiplication and addition.
	*/
	template <class T>
	class homotype : public holotype<T>
	{
		using S_ = holotype<T>;
		using A_ = typename S_:: archetype;
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

		template <quantity_plus_multiplies_q W> XTAL_VAL_(return,inline,get) operator * (W const &w) const noexcept requires bond::tab_preference_p<W, T> {return w * self()  ;}
		template <quantity_plus_multiplies_q W> XTAL_VAL_(return,inline,get) operator * (W const &w) const noexcept requires bond::tab_precedence_p<T, W> {return S_::mul2_(w);}
		template <quantity_plus_multiplies_q W> XTAL_VAL_(return,inline,get) operator / (W const &w) const noexcept requires bond::tab_precedence_p<T, W> {return S_::div2_(w);}
		template <quantity_plus_multiplies_q W> XTAL_VAL_(mutate,inline,get) operator *=(W const &w)       noexcept requires bond::tab_precedence_p<T, W> {return S_::mul1_(w);}
		template <quantity_plus_multiplies_q W> XTAL_VAL_(mutate,inline,get) operator /=(W const &w)       noexcept requires bond::tab_precedence_p<T, W> {return S_::div1_(w);}

		template <quantity_plus_multiplies_q W> XTAL_VAL_(return,inline,get) operator + (W const &w) const noexcept requires bond::tab_preference_p<W, T> {return w + self()  ;}
		template <quantity_plus_multiplies_q W> XTAL_VAL_(return,inline,get) operator + (W const &w) const noexcept requires bond::tab_precedence_p<W, T> {return S_::add2_(w);}
		template <quantity_plus_multiplies_q W> XTAL_VAL_(return,inline,get) operator - (W const &w) const noexcept requires bond::tab_precedence_p<W, T> {return S_::sub2_(w);}
		template <quantity_plus_multiplies_q W> XTAL_VAL_(mutate,inline,get) operator +=(W const &w)       noexcept requires bond::tab_precedence_p<W, T> {return S_::add1_(w);}
		template <quantity_plus_multiplies_q W> XTAL_VAL_(mutate,inline,get) operator -=(W const &w)       noexcept requires bond::tab_precedence_p<W, T> {return S_::sub1_(w);}

		XTAL_VAL_(return,inline,get)    operator + () const noexcept {return twin();}
	//	XTAL_VAL_(return,inline,get)    operator + () const noexcept {return S_::template zip_from<[] (auto const &x) XTAL_0FN_(to) (+x)>(self());}
		XTAL_VAL_(return,inline,get)    operator - () const noexcept {return S_::template zip_from<[] (auto const &x) XTAL_0FN_(to) (-x)>(self());}

		XTAL_VAL_(mutate,inline,get)    operator *=(std::initializer_list<U_> w)       noexcept requires fixed_valued_q<A_> {auto &s = self(); s *= T(w); return s;}
		XTAL_VAL_(mutate,inline,get)    operator /=(std::initializer_list<U_> w)       noexcept requires fixed_valued_q<A_> {auto &s = self(); s /= T(w); return s;}

		XTAL_VAL_(mutate,inline,get)    operator +=(std::initializer_list<U_> w)       noexcept requires fixed_valued_q<A_> {auto &s = self(); s += T(w); return s;}
		XTAL_VAL_(mutate,inline,get)    operator -=(std::initializer_list<U_> w)       noexcept requires fixed_valued_q<A_> {auto &s = self(); s -= T(w); return s;}

	};
	using type = bond::derive_t<homotype>;

};


////////////////////////////////////////////////////////////////////////////////
/*!
\brief   Extends `quantify` with component-wise multiplication.
*/
template <scalar_array_q ...Us> requires same_q<Us...>
struct quantity_multiplies<Us ...> : quantity_multiplies<common_t<Us...>[sizeof...(Us)]>
{};
template <class ...Us>
struct quantity_multiplies
{
private:
	template <class T>
	using endotype = typename quantify<Us...>::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<endotype<T>, bond::tag<quantity_multiplies_t>>;

public:
	/*!
	\brief   Extends `quantify` with component-wise multiplication.
	*/
	template <class T>
	class homotype : public holotype<T>
	{
		using S_ = holotype<T>;
		using A_ = typename S_:: archetype;
		using U_ = typename S_::value_type;

	public:// ACCESS
		using S_::size;
		using S_::self;

	public:// CONSTRUCT
	//	using S_::S_;

		XTAL_VAL_(delete) (homotype, noexcept=default)
		XTAL_VAL_(create) (homotype, noexcept=default)
		XTAL_VAL_(move)   (homotype, noexcept=default)
		XTAL_VAL_(copy)   (homotype, noexcept=default)
		XTAL_VAL_(induce) (homotype, noexcept:homotype)
		XTAL_VAL_(reduce) (homotype, noexcept:S_)

		XTAL_VAL_(new,implicit)
		homotype()
		noexcept
		requires un_v<0, size> and fixed_valued_q<A_>
		{
			_detail::initialize_with(S_::begin(), size(), U_{one});
		}
		/*!
		\brief  	Constructs the constant `quantity` using the `std::initializer_list` provided.
		If `1 == w.size()`, the provided value is repeated.
		*/
		XTAL_VAL_(new,implicit)
		homotype(std::initializer_list<U_> xs)
		noexcept
		requires un_v<0, size> and fixed_valued_q<A_>
		{
			auto const sN = xs.   size(); assert(sN <= size);
			auto       x0 = xs.  begin();
			auto       y0 = S_:: begin();
			_detail::move_to(y0, x0, sN);
			if (1 == sN) {_detail::initialize_with(std::next(y0, sN), size() - sN, S_::front());}
		}

	public:// OPERATE
		using S_::operator*; using S_::operator*=;
		using S_::operator/; using S_::operator/=;

		template <quantity_multiplies_q W> XTAL_VAL_(return,inline,get) operator * (W const &w) const noexcept requires bond::tab_preference_p<W, T> {return w * self()  ;}
		template <quantity_multiplies_q W> XTAL_VAL_(return,inline,get) operator * (W const &w) const noexcept requires bond::tab_precedence_p<T, W> {return S_::mul2_(w);}
		template <quantity_multiplies_q W> XTAL_VAL_(return,inline,get) operator / (W const &w) const noexcept requires bond::tab_precedence_p<T, W> {return S_::div2_(w);}
		template <quantity_multiplies_q W> XTAL_VAL_(mutate,inline,get) operator *=(W const &w)       noexcept requires bond::tab_precedence_p<T, W> {return S_::mul1_(w);}
		template <quantity_multiplies_q W> XTAL_VAL_(mutate,inline,get) operator /=(W const &w)       noexcept requires bond::tab_precedence_p<T, W> {return S_::div1_(w);}

		XTAL_VAL_(mutate,inline,get) operator *=(std::initializer_list<U_> w)                         noexcept requires fixed_valued_q<A_> {auto &s = self(); s *= T(w); return s;}
		XTAL_VAL_(mutate,inline,get) operator /=(std::initializer_list<U_> w)                         noexcept requires fixed_valued_q<A_> {auto &s = self(); s /= T(w); return s;}

		/*!
		\returns	The reduction of `self` w.r.t. multiplication.
		*/
		XTAL_VAL_(return,inline,let)
		crush() const
		noexcept -> auto
		{
			return S_::template reduce<std::multiplies<>{}>();
		}

	};
	using type = bond::derive_t<homotype>;

};


////////////////////////////////////////////////////////////////////////////////
/*!
\brief   Extends `quantify` with component-wise addition.
*/
template <scalar_array_q ...Us> requires same_q<Us...>
struct quantity_plus<Us ...> : quantity_plus<common_t<Us...>[sizeof...(Us)]>
{};
template <class ...Us>
struct quantity_plus
{
private:
	template <class T>
	using endotype = typename quantify<Us...>::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<endotype<T>, bond::tag<quantity_plus_t>>;

public:
	template <class T>
	class homotype : public holotype<T>
	{
		using S_ = holotype<T>;
		using A_ = typename S_:: archetype;
		using U_ = typename S_::value_type;

	public:// ACCESS
		using S_::size;
		using S_::self;

	public:// CONSTRUCT
		using S_::S_;

	public:// OPERATE
		using S_::operator+; using S_::operator+=;
		using S_::operator-; using S_::operator-=;

		template <quantity_plus_q W> XTAL_VAL_(return,inline,get) operator + (W const &w) const noexcept requires bond::tab_preference_p<W, T> {return w + self()  ;}
		template <quantity_plus_q W> XTAL_VAL_(return,inline,get) operator + (W const &w) const noexcept requires bond::tab_precedence_p<W, T> {return S_::add2_(w);}
		template <quantity_plus_q W> XTAL_VAL_(return,inline,get) operator - (W const &w) const noexcept requires bond::tab_precedence_p<W, T> {return S_::sub2_(w);}
		template <quantity_plus_q W> XTAL_VAL_(mutate,inline,get) operator +=(W const &w)       noexcept requires bond::tab_precedence_p<W, T> {return S_::add1_(w);}
		template <quantity_plus_q W> XTAL_VAL_(mutate,inline,get) operator -=(W const &w)       noexcept requires bond::tab_precedence_p<W, T> {return S_::sub1_(w);}

		XTAL_VAL_(mutate,inline,get) operator +=(std::initializer_list<U_> w)                   noexcept requires fixed_valued_q<A_> {auto &s = self(); s += T(w); return s;}
		XTAL_VAL_(mutate,inline,get) operator -=(std::initializer_list<U_> w)                   noexcept requires fixed_valued_q<A_> {auto &s = self(); s -= T(w); return s;}

		/*!
		\returns	The reduction of `self` w.r.t. addition.
		*/
		XTAL_VAL_(return,inline,let)
		crush() const
		noexcept -> auto
		{
			return S_::template reduce<std::plus<>{}>();
		}

	};
	using type = bond::derive_t<homotype>;

};


////////////////////////////////////////////////////////////////////////////////

XTAL_VAL_(let) quantity_plus_multiplies_f = [] XTAL_1FN_(call) (_detail::factory<quantity_plus_multiplies_t >::make);
XTAL_VAL_(let) quantity_multiplies_f      = [] XTAL_1FN_(call) (_detail::factory<quantity_multiplies_t      >::make);
XTAL_VAL_(let) quantity_plus_f            = [] XTAL_1FN_(call) (_detail::factory<quantity_plus_t            >::make);

template <scalar_array_q  ...Us> requires quantity_multiplies_q <               Us...          > struct quantity<Us...> : quantity_multiplies<Us...> {};
template <vector_array_q     Us> requires quantity_multiplies_q <typename fixed<Us>::value_type> struct quantity<Us   > : quantity_multiplies<Us   > {};
template <scalar_array_q  ...Us> requires quantity_plus_q       <               Us...          > struct quantity<Us...> : quantity_plus      <Us...> {};
template <vector_array_q     Us> requires quantity_plus_q       <typename fixed<Us>::value_type> struct quantity<Us   > : quantity_plus      <Us   > {};
template <scalar_array_q  ...Us> requires integral_variable_q   <               Us...          > struct quantity<Us...> : quantity_plus      <Us...> {};
template <vector_array_q     Us> requires integral_variable_q   <typename fixed<Us>::value_type> struct quantity<Us   > : quantity_plus      <Us   > {};

template <class     ...Us> struct quantity<xtd::plus_multiplies <Us>   ...> : quantity_plus_multiplies<Us...  > {};///<\brief Resolves as `quantity_plus_multiplies`.;
template <class U, auto N> struct quantity<xtd::plus_multiplies <U >   [N]> : quantity_plus_multiplies<U   [N]> {};///<\brief Resolves as `quantity_plus_multiplies`.
template <class U, auto N> struct quantity<xtd::plus_multiplies <U >(&)[N]> : quantity_plus_multiplies<U(&)[N]> {};///<\brief Resolves as `quantity_plus_multiplies`.

template <class     ...Us> struct quantity<std::     multiplies <Us>   ...> : quantity_multiplies<Us...  > {};///<\brief Resolves as `quantity_multiplies`.;
template <class U, auto N> struct quantity<std::     multiplies <U >   [N]> : quantity_multiplies<U   [N]> {};///<\brief Resolves as `quantity_multiplies`.
template <class U, auto N> struct quantity<std::     multiplies <U >(&)[N]> : quantity_multiplies<U(&)[N]> {};///<\brief Resolves as `quantity_multiplies`.

template <class     ...Us> struct quantity<std::plus            <Us>   ...> : quantity_plus      <Us...  > {};///<\brief Resolves as `quantity_plus`.;
template <class U, auto N> struct quantity<std::plus            <U >   [N]> : quantity_plus      <U   [N]> {};///<\brief Resolves as `quantity_plus`.
template <class U, auto N> struct quantity<std::plus            <U >(&)[N]> : quantity_plus      <U(&)[N]> {};///<\brief Resolves as `quantity_plus`.


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
