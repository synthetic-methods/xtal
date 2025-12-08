#pragma once
#include "./any.hh"
#include "./wrap.hh"
#include "./group.hh"
#include "./field.hh"



XTAL_ENV_(push)
namespace xtal::atom
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/*!
\brief
Extends `group_multiplication` with the scalar sum/product,
providing even/odd-reflection iff `size() == 2`.
*/
template <class ...Us>	struct  couple;
template <class ...Us>	using   couple_t = typename couple<Us...>::type; ///<\brief  Type-factory for `couple`.
template <class ...Us>	concept couple_q = bond::tag_infixed_p<couple_t, Us...>;

XTAL_DEF_(let) couple_f = [] XTAL_1FN_(call) (_detail::factory<couple_t>::make);///<\brief Value-factory for `couple`.


////////////////////////////////////////////////////////////////////////////////

template <scalar_q ...Us> requires common_q<Us...>
struct couple<Us ...>
:	couple<common_t<Us...>[sizeof...(Us)]>
{
};
template <class ...Us>
struct couple
{
	using _fit = bond::fit<Us...>;
	using sigma_type = typename _fit::sigma_type;
	using delta_type = typename _fit::delta_type;
	using alpha_type = typename _fit::alpha_type;
	
	template <class T>
	//\
	using endotype = typename field<wrap_s<Us, _xtd::plus_multiplies>...>::template homotype<T>;
	using endotype = typename group<wrap_s<Us, _std::multiplies     >...>::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<endotype<T>
	,	bond::tag<couple_t>
	>;
	template <class T>
	class homotype : public holotype<T>
	{
		using S_ = holotype<T>;
		static auto constexpr N_ = static_cast<int>(S_::size());

	public:// ACCESS
		using S_::size;
		using S_::self;
		using S_::twin;

		using typename S_::value_type;
		using typename S_::scale_type;

	private:
		using U_arg = complete_t<value_type, scale_type>;

		template <int N_slot=0>
		XTAL_DEF_(return,inline,set)
		versus_f(auto &&v)
		noexcept -> auto
		{
			using V = XTAL_ALL_(v);
			scale_type constexpr one{1};
			XTAL_IF0
			XTAL_0IF (continuous_field_q<V> and       1 == N_slot) {return       versus_f(one/XTAL_REF_(v));}
			XTAL_0IF (   logical_group_q<V> and       1 == N_slot) {return       versus_f(not XTAL_REF_(v));}
			XTAL_0IF (   logical_group_q<V> and integral_q<U_arg>) {return                   -XTAL_REF_(v) ;}
			XTAL_0IF (            same_q<V,                U_arg>) {return                    XTAL_REF_(v) ;}
			XTAL_0IF_(else)                                        {return static_cast<U_arg>(XTAL_REF_(v));}
		}

	public:// CONSTRUCT
		using S_::S_;

 		XTAL_NEW_(explicit)
		homotype(bool  const u, _std::in_place_t)
		noexcept
		requires in_n<size, 2>
		:	S_{versus_f<0>(u), versus_f<1>(u)}
		{}
		XTAL_NEW_(explicit)
		homotype(U_arg const u, _std::in_place_t)
 		noexcept
		requires in_n<size, 2>
		:	S_{versus_f<0>(u), versus_f<1>(u)}
 		{
 		}

	public:// OPERATE
		using S_::operator+; using S_::operator+=;
		using S_::operator-; using S_::operator-=;

		template <couple_q W> XTAL_DEF_(return,inline,get) operator + (W const &w) const noexcept requires bond::tab_preference_p<W, T> {return w + self()  ;}
		template <couple_q W> XTAL_DEF_(return,inline,get) operator + (W const &w) const noexcept requires bond::tab_precedence_p<W, T> {return S_::add2_(w);}
		template <couple_q W> XTAL_DEF_(return,inline,get) operator - (W const &w) const noexcept requires bond::tab_precedence_p<W, T> {return S_::sub2_(w);}
		template <couple_q W> XTAL_DEF_(mutate,inline,get) operator +=(W const &w)       noexcept requires bond::tab_precedence_p<W, T> {return S_::add1_(w);}
		template <couple_q W> XTAL_DEF_(mutate,inline,get) operator -=(W const &w)       noexcept requires bond::tab_precedence_p<W, T> {return S_::sub1_(w);}

		/*!
		\brief  	Produces the progressive sum/difference, starting from zero if post-fixed.
		\brief  	Defined only for `const this`, because this is whack (but fun).
		*/
		XTAL_DEF_(inline,let)
		operator++() const
		noexcept -> auto
		{
			auto t = S_::twin();
			bond::seek_until_f<N_ - 1>([&]<constant_q I> (I) XTAL_0FN {
				get<I{} + 1>(t) += get<I{}>(t);
			});
			return t;
		}
		XTAL_DEF_(inline,let)
		operator--() const
		noexcept -> auto
		{
			auto t = S_::twin();
			bond::seek_until_f<1 - N_>([&]<constant_q I> (I) XTAL_0FN {
				get<I{} + 1>(t) -= get<I{}>(t);
			});
			return t;
		}

		XTAL_DEF_(inline,let)
		operator++(int) const
		noexcept -> auto
		requires common_q<Us...>
		{
			auto t = S_::twin();
			value_type u{};
			value_type v{};
			bond::seek_until_f<+N_>([&]<constant_q I> (I) XTAL_0FN {
				u += get<I{}>(t); get<I{}>(t) = v;
				v = u;
			});
			return t;
		}
		XTAL_DEF_(inline,let)
		operator--(int) const
		noexcept -> auto
		requires common_q<Us...>
		{
			auto t = S_::twin();
			value_type u;
			value_type v{t.sum()};
			bond::seek_until_f<-N_>([&]<constant_q I> (I) XTAL_0FN {
				u = get<I{}>(t); get<I{}>(t) = v - u;
				v = u;
			});
			return t;
		}

		XTAL_DEF_(return,inline,let)
		operator ~ () const
		noexcept -> auto
		{
			return flipped();
		}
		XTAL_DEF_(return,inline,let)
		flipped() const
		noexcept -> auto
		{
			auto const &e0 = S_::template element<0>();
			auto const &e1 = S_::template element<1>();
			return S_::form(e1, e0);
		}
		XTAL_DEF_(return,inline,let)
		flipped(simplex_field_q auto const side) const
		noexcept -> auto
		{
			auto const &e0 = S_::template element<0>();
			auto const &e1 = S_::template element<1>();
			auto const  f0 =   half*(e0 + e1);
			auto const  f1 =   side*(f0 - e1);
			return S_::form(f0 + f1, f0 - f1);
		}

		/*!
		\returns	The ratio between the two elements of `this`, raised to the power `-1 <= N_pow <= 1`.
		*/
		template <int N_pow=1> requires (size == 2)
		XTAL_DEF_(return,inline,let)
		ratio() const
		noexcept -> auto
		{
			auto &s = self();
			
			XTAL_IF0
			XTAL_0IF (N_pow ==  0) {return value_type{one};}
			XTAL_0IF (N_pow ==  1) {return get<0>(s)/get<1>(s);}
			XTAL_0IF (N_pow == -1) {return get<1>(s)/get<0>(s);}
		}


		template <int N_dir=0>
		XTAL_DEF_(return,inline,let)
		resolution() const
		noexcept -> decltype(auto)
		{
			XTAL_IF0
			XTAL_0IF (N_dir ==  1) {return self().template element<0>();}
			XTAL_0IF (N_dir == -1) {return self().template element<1>();}
		}
		XTAL_DEF_(return,inline,let)
		resolution(constant_q auto const n) const
		noexcept -> decltype(auto)
		{
			return resolution<XTAL_ALL_(n){}>();
		}

		XTAL_DEF_(return,inline,let)
		resolution() const
		noexcept -> decltype(auto)
		{
			return self();
		}

		/*!
		\returns	The mutually inverse `lhs +/- rhs` scaled by `reflector<N_par>()`.
		*/
		template <int N_dir=0>
		XTAL_DEF_(return,inline,let)
		reflection() const
		noexcept -> auto
		requires (size == 2) and same_q<Us...>
		{
			auto const &x = self().template element<0>();
			auto const &y = self().template element<1>();
			XTAL_IF0
			XTAL_0IF (N_dir ==  0) {return S_::form(x + y, x - y);}
			XTAL_0IF (N_dir ==  1) {return x + y;}
			XTAL_0IF (N_dir == -1) {return x - y;}
		}
		XTAL_DEF_(return,inline,let)
		reflection(constant_q auto const n) const
		noexcept -> decltype(auto)
		requires (size == 2) and same_q<Us...>
		{
			return reflection<XTAL_ALL_(n){}>();
		}

		XTAL_DEF_(return,inline,let)  maximum() const noexcept -> auto const & {return *_xtd::ranges::max_element(self());}
		XTAL_DEF_(return,inline,let)  minimum() const noexcept -> auto const & {return *_xtd::ranges::min_element(self());}
		XTAL_DEF_(return,inline,let)  miximum() const noexcept -> auto const & {
			auto const &[min_, max_] = _xtd::ranges::minmax_element(self());
			return _std::tie(*min_, *max_);
		}
		template <int N=0>
		XTAL_DEF_(return,inline,let)
		extremum() const
		noexcept -> auto
		{
			XTAL_IF0
			XTAL_0IF (0 < N) {return maximum();}
			XTAL_0IF (N < 0) {return minimum();}
			XTAL_0IF_(else)  {return miximum();}
		}

		XTAL_DEF_(return,inline,let) maximal() const noexcept -> auto {return S_::template reduce<[] XTAL_1FN_(call) (_std::lcm)>();}
		XTAL_DEF_(return,inline,let) minimal() const noexcept -> auto {return S_::template reduce<[] XTAL_1FN_(call) (_std::gcd)>();}
		XTAL_DEF_(return,inline,let) miximal() const noexcept -> auto {return bond::pack_f(minimal(), maximal());}
		template <int N=0>
		XTAL_DEF_(return,inline,let)
		extremal() const
		noexcept -> auto
		{
			XTAL_IF0
			XTAL_0IF (0 < N) {return maximal();}
			XTAL_0IF (N < 0) {return minimal();}
			XTAL_0IF_(else)  {return miximal();}
		}


	};
	using type = bond::derive_t<homotype>;

};
template <scalar_q U>
struct couple<U>
:	couple<U[2]>
{
};


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
