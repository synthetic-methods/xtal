#pragma once
#include "./any.hh"
#include "./point.hh"





XTAL_ENV_(push)
namespace xtal::atom
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
///\
Extends `point` with point-wise multiplication. \

template <class ...Us>	struct  multiplicative_group;
template <class ...Us>	using   multiplicative_group_t = typename multiplicative_group<Us...>::type;
template <class ...Us>	concept multiplicative_group_q = bond::array_or_any_tags_p<multiplicative_group_t, Us...> and fixed_shaped_q<Us...>;

XTAL_DEF_(let) multiplicative_group_f = [] XTAL_1FN_(call) (_detail::fake_f<multiplicative_group_t>);


template <scalar_q ...Us> requires common_q<Us...>
struct multiplicative_group<Us ...>
:	multiplicative_group<common_t<Us...>[sizeof...(Us)]>
{
};
template <class ...Us>
struct multiplicative_group
{
	template <class T>
	using endotype = typename point<Us...>::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<endotype<T>, bond::tag<multiplicative_group_t>>;

	template <class T>
	class homotype : public holotype<T>
	{
		using S_ = holotype<T>;

	public:// ACCESS
		using S_::front;
		using S_::size;
		using S_::self;

		using typename S_::value_type;
		using typename S_::scale_type;

	public:// CONSTRUCT
	//	using S_::S_;
		XTAL_NEW_(delete) (homotype, noexcept = default)
		XTAL_NEW_(create) (homotype, noexcept = default)
		XTAL_NEW_(move)   (homotype, noexcept = default)
		XTAL_NEW_(copy)   (homotype, noexcept = default)
		XTAL_NEW_(cast)   (homotype, noexcept)

		XTAL_NEW_(explicit)
		homotype(auto &&...oo)
		noexcept
		:	S_{XTAL_REF_(oo)...}
		{}
		XTAL_NEW_(implicit)
		homotype()
		noexcept
		requires common_q<Us...>
		{
			_detail::initialize_with(S_::begin(), size(), value_type{1});
		}
		///\
		Constructs the constant `group` using the initializer `w`. \
		If `1 == w.size()`, the provided value is repeated. \

		XTAL_NEW_(implicit)
		homotype(_std::initializer_list<value_type> xs)
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
		///\returns the result of `blanked()` before refilling with `N_value=1`. \

		template <auto N_value=1>
		XTAL_DEF_(inline,let)
		blanket()
		noexcept -> bool
		{
			return S_::template blanket<N_value>();
		}

		using S_::operator*; using S_::operator*=;
		using S_::operator/; using S_::operator/=;
		using S_::operator%; using S_::operator%=;

		XTAL_DEF_(return,inline,let)
		operator * (fixed_shaped_q<S_> auto const &o) const
		noexcept -> auto
		requires un_n<requires (value_type v) {v *= o;}>
		{
			if constexpr (bond::tab_preference_p<decltype(o), T>) {
				return o * self();
			}
			else {
				return S_::template zip_from<[] (auto const &x, auto const &y) XTAL_0FN_(to) (x * y)>(self(), o);
			}
		}
	//	XTAL_DEF_(return,inline,let) operator * (fixed_shaped_q<S_>     auto const &o) const noexcept -> auto   requires un_n<requires (value_type v) {v *= o;}> {return S_::template zip_from<[] (auto const &x, auto const &y) XTAL_0FN_(to) (x *  y)>(self(),   o );}
		XTAL_DEF_(return,inline,let) operator / (fixed_shaped_q<S_>     auto const &o) const noexcept -> auto   requires un_n<requires (value_type v) {v /= o;}> {return S_::template zip_from<[] (auto const &x, auto const &y) XTAL_0FN_(to) (x /  y)>(self(),   o );}
		XTAL_DEF_(return,inline,let) operator % (fixed_shaped_q<S_>     auto const &o) const noexcept -> auto   requires un_n<requires (value_type v) {v %= o;}> {return S_::template zip_from<[] (auto const &x, auto const &y) XTAL_0FN_(to) (x %  y)>(self(),   o );}
		XTAL_DEF_(mutate,inline,let) operator *=(fixed_shaped_q<S_>     auto const &o)       noexcept -> auto & requires un_n<requires (value_type v) {v *= o;}> {return S_::template zip_with<[] (auto       &x, auto const &y) XTAL_0FN_(do) (x *= y)>(XTAL_REF_(o));}
		XTAL_DEF_(mutate,inline,let) operator /=(fixed_shaped_q<S_>     auto const &o)       noexcept -> auto & requires un_n<requires (value_type v) {v /= o;}> {return S_::template zip_with<[] (auto       &x, auto const &y) XTAL_0FN_(do) (x /= y)>(XTAL_REF_(o));}
		XTAL_DEF_(mutate,inline,let) operator %=(fixed_shaped_q<S_>     auto const &o)       noexcept -> auto & requires un_n<requires (value_type v) {v %= o;}> {return S_::template zip_with<[] (auto       &x, auto const &y) XTAL_0FN_(do) (x %= y)>(XTAL_REF_(o));}
		XTAL_DEF_(mutate,inline,let) operator *=(_std::initializer_list<value_type> o)       noexcept -> auto & requires common_q<Us...> {return S_::self() *= T(o);}
		XTAL_DEF_(mutate,inline,let) operator /=(_std::initializer_list<value_type> o)       noexcept -> auto & requires common_q<Us...> {return S_::self() /= T(o);}
		XTAL_DEF_(mutate,inline,let) operator %=(_std::initializer_list<value_type> o)       noexcept -> auto & requires common_q<Us...> {return S_::self() %= T(o);}

	};
	using type = bond::derive_t<homotype>;

};


////////////////////////////////////////////////////////////////////////////////
///\
Extends `point` with point-wise addition. \

template <class ...Us>	struct  additive_group;
template <class ...Us>	using   additive_group_t = typename additive_group<Us...>::type;
template <class ...Us>	concept additive_group_q = bond::array_or_any_tags_p<additive_group_t, Us...> and fixed_shaped_q<Us...>;

XTAL_DEF_(let) additive_group_f = [] XTAL_1FN_(call) (_detail::fake_f<additive_group_t>);


template <scalar_q ...Us> requires common_q<Us...>
struct additive_group<Us ...>
:	additive_group<common_t<Us...>[sizeof...(Us)]>
{
};
template <class ...Us>
struct additive_group
{
	template <class T>
	using endotype = typename point<Us...>::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<endotype<T>, bond::tag<additive_group_t>>;

	template <class T>
	class homotype : public holotype<T>
	{
		using S_ = holotype<T>;
	
	public:// ACCESS
		using S_::size;
		using S_::self;

		using typename S_::value_type;
		using typename S_::scale_type;

	public:// CONSTRUCT
		using S_::S_;

	public:// OPERATE
		using S_::operator+; using S_::operator+=;
		using S_::operator-; using S_::operator-=;

		XTAL_DEF_(return,inline,let)
		operator + (fixed_shaped_q auto const &o) const
		noexcept -> auto
		requires un_n<requires (value_type v) {v += o;}>
		{
			if constexpr (bond::tab_preference_p<decltype(o), T>) {
				return o + self();
			}
			else {
				return S_::template zip_from<[] (auto const &x, auto const &y) XTAL_0FN_(to) (x + y)>(self(), o);
			}
		}
	//	XTAL_DEF_(return,inline,let) operator + (fixed_shaped_q         auto const &o) const noexcept -> auto   requires un_n<requires (value_type v) {v += o;}> {return S_::template zip_from<[] (auto const &x, auto const &y) XTAL_0FN_(to) (x +  y)>(self(),   o );}
		XTAL_DEF_(return,inline,let) operator - (fixed_shaped_q         auto const &o) const noexcept -> auto   requires un_n<requires (value_type v) {v -= o;}> {return S_::template zip_from<[] (auto const &x, auto const &y) XTAL_0FN_(to) (x -  y)>(self(),   o );}
		XTAL_DEF_(mutate,inline,let) operator +=(fixed_shaped_q         auto const &o)       noexcept -> auto & requires un_n<requires (value_type v) {v += o;}> {return S_::template zip_with<[] (auto       &x, auto const &y) XTAL_0FN_(do) (x += y)>(XTAL_REF_(o));}
		XTAL_DEF_(mutate,inline,let) operator -=(fixed_shaped_q         auto const &o)       noexcept -> auto & requires un_n<requires (value_type v) {v -= o;}> {return S_::template zip_with<[] (auto       &x, auto const &y) XTAL_0FN_(do) (x -= y)>(XTAL_REF_(o));}
		XTAL_DEF_(mutate,inline,let) operator +=(_std::initializer_list<value_type> o)       noexcept -> auto & requires common_q<Us...> {return S_::self() += T(o);}
		XTAL_DEF_(mutate,inline,let) operator -=(_std::initializer_list<value_type> o)       noexcept -> auto & requires common_q<Us...> {return S_::self() -= T(o);}

	};
	using type = bond::derive_t<homotype>;

};


////////////////////////////////////////////////////////////////////////////////

template <class T        > struct group;

template <class U, auto N> struct group<_std::plus       <U>   [N]> :       additive_group<U   [N]> {};
template <class U, auto N> struct group<_std::plus       <U>(&)[N]> :       additive_group<U(&)[N]> {};

template <class U, auto N> struct group<_std::multiplies <U>   [N]> : multiplicative_group<U   [N]> {};
template <class U, auto N> struct group<_std::multiplies <U>(&)[N]> : multiplicative_group<U(&)[N]> {};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
