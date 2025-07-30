#pragma once
#include "./any.hh"
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
	using endotype = typename     field_arithmetic<Us...>::template homotype<T>;
	using endotype = typename group_multiplication<Us...>::template homotype<T>;

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

	public:// CONSTRUCT
		using S_::S_;//NOTE: Inherited and respecialized!

		XTAL_NEW_(explicit)
		homotype(bool u)
		noexcept
		requires common_q<Us...> and in_n<size, 2>
		:	S_{static_cast<value_type>(u), static_cast<value_type>(not u)}
		{}
		XTAL_NEW_(explicit)
		homotype(complete_t<value_type, scale_type> u)
		noexcept
		requires common_q<Us...> and in_n<size, 2> and continuous_field_q<value_type>
		:	S_{u, scale_type{one}/u}
		{
			assert(u != value_type{0});
		}
		XTAL_NEW_(explicit)
		homotype(subjective_q auto const &u)
		noexcept
		requires common_q<Us...> and in_n<size, 2> and continuous_field_q<value_type>
		:	homotype{objective_f(u)}
		{}

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
			bond::seek_out_f<N_ - 1>([&]<constant_q I> (I) XTAL_0FN {
				get<I{} + 1>(t) += get<I{}>(t);
			});
			return t;
		}
		XTAL_DEF_(inline,let)
		operator--() const
		noexcept -> auto
		{
			auto t = S_::twin();
			bond::seek_out_f<1 - N_>([&]<constant_q I> (I) XTAL_0FN {
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
			bond::seek_out_f<+N_>([&]<constant_q I> (I) XTAL_0FN {
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
			bond::seek_out_f<-N_>([&]<constant_q I> (I) XTAL_0FN {
				u = get<I{}>(t); get<I{}>(t) = v - u;
				v = u;
			});
			return t;
		}

	//	Scalar sum:
		template <int N_sgn=1>
		XTAL_DEF_(return,inline,let)
		sum() const
		noexcept -> auto
		{
			return sum<N_sgn>(scale_type{0});
		}
		template <int N_sgn=1>
		XTAL_DEF_(return,inline,let)
		sum(auto const &u) const
		noexcept -> auto
		{
			auto &s = self();

			if constexpr (0 < N_sgn) {
				return [&]<auto ...I> (bond::seek_t<I...>)
					XTAL_0FN_(to) (u +...+ get<I>(s))
				(bond::seek_s<size>{});
			}
			else {
				return [&]<auto ...I> (bond::seek_t<I...>)
					XTAL_0FN_(to) (u +...+ (scale_type{cosign_v<I>}*get<I>(s)))
				(bond::seek_s<size>{});
			}
		}

	//	Scalar product:
		template <int N_sgn=1>
		XTAL_DEF_(return,inline,let)
		product() const
		noexcept -> auto
		{
			return product<N_sgn>(scale_type{0});
		}
		template <int N_sgn=1>
		XTAL_DEF_(return,inline,let)
		product(auto u) const
		noexcept -> auto
		requires in_n<requires (value_type v) {v += u;}>
		{
			auto &s = self();
			
			bond::seek_out_f<size>([&]<constant_q I> (I) XTAL_0FN {
				sigma_type constexpr  i{I{}};
				scale_type constexpr _1{cosign_v<i>};
				auto const &v = get<I>(s);
				XTAL_IF0
				XTAL_0IF (0 < N_sgn) {u = _xtd::plus_multiplies(XTAL_MOV_(u),    v, v);}
				XTAL_0IF (N_sgn < 0) {u = _xtd::plus_multiplies(XTAL_MOV_(u), _1*v, v);}
			});

			return u;
		}
		template <int N_sgn=1> requires common_q<Us...>
		XTAL_DEF_(return,inline,let)
		product(auto &&t) const
		noexcept -> auto
		requires un_n<requires (value_type v) {v += t;}> and fixed_shaped_q<decltype(t), S_>
		{
			auto &s = self();
			value_type u{0};
			
			bond::seek_out_f<size>([&, this]<constant_q I> (I) XTAL_0FN {
				sigma_type constexpr  i{I{}};
				scale_type constexpr _1{cosign_v<i>};
				XTAL_IF0
				XTAL_0IF (0 < N_sgn) {u = _xtd::plus_multiplies(XTAL_MOV_(u),    get<i>(s), get<i>(t));}
				XTAL_0IF (N_sgn < 0) {u = _xtd::plus_multiplies(XTAL_MOV_(u), _1*get<i>(s), get<i>(t));}
			});
			
			return u;
		}

		/*!
		\returns	The ratio between the two elements of `this`, raised to the power `-1 <= N_pow <= 1`.
		*/
		template <int N_pow=1> requires (size == 2)
		XTAL_DEF_(return,inline,let)
		ratio()
		noexcept -> auto
		{
			auto &s = self();
			
			XTAL_IF0
			XTAL_0IF (0 == N_pow) {return value_type{one};}
			XTAL_0IF (0 <  N_pow) {return get<0>(s)/get<1>(s);}
			XTAL_0IF (N_pow <  0) {return get<1>(s)/get<0>(s);}
		}
		/*!
		\returns	This, with the two elements `reflected`.
		*/
		template <int N_par=0> requires (size == 2)
		XTAL_DEF_(mutate,inline,let)
		reflect()
		noexcept -> T &
		{
			return self() = reflected<N_par>();
		}
		/*!
		\returns	The mutually inverse `lhs +/- rhs` scaled by `reflector<N_par>()`.
		*/
		template <int N_par=0> requires (size == 2)
		XTAL_DEF_(return,inline,let)
		reflected() const
		noexcept -> decltype(auto)
		{
			auto &s = self();
			auto constexpr o = reflector<N_par>();
			auto const     x = o*get<0>(s);
			auto const     y = o*get<1>(s);
			return decltype(twin()) {x + y, x - y};
		}
		/*!
		\returns	The reflection coefficient indexed by `N_par`: `{-1, 0, 1} -> {0.5, std::sqrt(0.5), 1.0}`.
		*/
		template <int N_par=0> requires (size() == 2)
		XTAL_DEF_(return,inline,set)
		reflector()
		noexcept -> auto
		{
			XTAL_IF0
			XTAL_0IF (N_par == +1) {return one >> scale_type{0.0F};}
			XTAL_0IF (N_par ==  0) {return one >> scale_type{0.5F};}
			XTAL_0IF (N_par == -1) {return one >> scale_type{1.0F};}
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
