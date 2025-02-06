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

template <        class ..._s>	struct   multiplicative_group;
template <        class ..._s>	using    multiplicative_group_t = typename multiplicative_group<_s...>::type;
template <        class ..._s>	concept  multiplicative_group_q = bond::array_tag_p<multiplicative_group_t, _s...> and fixed_shaped_q<_s...>;

XTAL_FX0_(to) (template <auto f=_std::identity{}>
XTAL_DEF_(return,inline,let)
multiplicative_group_f(auto &&...oo),
	_detail::factory<multiplicative_group_t>::
		template make<f>(XTAL_REF_(oo)...))


template <scalar_q ..._s> requires same_q<_s...>
struct multiplicative_group<_s ...>
:	multiplicative_group<common_t<_s...>[sizeof...(_s)]>
{
};
template <class ..._s>
struct multiplicative_group
{
	template <class T>
	using endotype = typename point<_s...>::template homotype<T>;

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
		requires same_q<_s...>
		{
			_detail::initialize_with(S_::begin(), size(), value_type{1});
		}
		///\
		Constructs the constant `group` using the initializer `w`. \
		If `1 == w.size()`, the provided value is repeated. \

		XTAL_NEW_(implicit)
		homotype(_std::initializer_list<value_type> xs)
		noexcept
		requires same_q<_s...>
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

		using S_::operator* ;
		using S_::operator/ ;
		using S_::operator% ;
		using S_::operator*=;
		using S_::operator/=;
		using S_::operator%=;

		XTAL_DEF_(return,inline,let) operator * (                         auto const &t) const noexcept -> auto   {return S_::template zip_from<[] (auto const &u, auto const &v) XTAL_0FN_(to) (u * v)>(self(),   t );}
		XTAL_DEF_(return,inline,let) operator / (                         auto const &t) const noexcept -> auto   {return S_::template zip_from<[] (auto const &u, auto const &v) XTAL_0FN_(to) (u / v)>(self(),   t );}
		XTAL_DEF_(return,inline,let) operator % (                         auto const &t) const noexcept -> auto   {return S_::template zip_from<[] (auto const &u, auto const &v) XTAL_0FN_(to) (u % v)>(self(),   t );}
		XTAL_DEF_(mutate,inline,let) operator *=(fixed_shaped_q<homotype> auto const &t)       noexcept -> auto & {return S_::template zip_with<[] (auto       &u, auto const &v) XTAL_0FN_(do) (u *=v)>(XTAL_REF_(t));}
		XTAL_DEF_(mutate,inline,let) operator /=(fixed_shaped_q<homotype> auto const &t)       noexcept -> auto & {return S_::template zip_with<[] (auto       &u, auto const &v) XTAL_0FN_(do) (u /=v)>(XTAL_REF_(t));}
		XTAL_DEF_(mutate,inline,let) operator %=(fixed_shaped_q<homotype> auto const &t)       noexcept -> auto & {return S_::template zip_with<[] (auto       &u, auto const &v) XTAL_0FN_(do) (u %=v)>(XTAL_REF_(t));}
		XTAL_DEF_(mutate,inline,let) operator *=(_std::initializer_list<value_type>   t)       noexcept -> auto & requires same_q<_s...> {return S_::self() *= T(t);}
		XTAL_DEF_(mutate,inline,let) operator /=(_std::initializer_list<value_type>   t)       noexcept -> auto & requires same_q<_s...> {return S_::self() /= T(t);}
		XTAL_DEF_(mutate,inline,let) operator %=(_std::initializer_list<value_type>   t)       noexcept -> auto & requires same_q<_s...> {return S_::self() %= T(t);}

	};
	using type = derive_t<homotype>;

};


////////////////////////////////////////////////////////////////////////////////
///\
Extends `point` with point-wise addition. \

template <class ..._s>	struct   additive_group;
template <class ..._s>	using    additive_group_t = typename additive_group<_s...>::type;
template <class ..._s>	concept  additive_group_q = bond::array_tag_p<additive_group_t, _s...> and fixed_shaped_q<_s...>;

XTAL_FX0_(to) (template <auto f=_std::identity{}>
XTAL_DEF_(return,inline,let)
additive_group_f(auto &&...oo),
	_detail::factory<additive_group_t>::
		template make<f>(XTAL_REF_(oo)...))


template <scalar_q ..._s> requires same_q<_s...>
struct additive_group<_s ...>
:	additive_group<common_t<_s...>[sizeof...(_s)]>
{
};
template <class ..._s>
struct additive_group
{
	template <class T>
	using endotype = typename point<_s...>::template homotype<T>;

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
		using S_::operator+ ;
		using S_::operator- ;
		using S_::operator+=;
		using S_::operator-=;

		XTAL_DEF_(return,inline,let) operator + (                         auto const &t) const noexcept -> auto   {return S_::template zip_from<[] (auto const &u, auto const &v) XTAL_0FN_(to) (u + v)>(self(),   t );}
		XTAL_DEF_(return,inline,let) operator - (                         auto const &t) const noexcept -> auto   {return S_::template zip_from<[] (auto const &u, auto const &v) XTAL_0FN_(to) (u - v)>(self(),   t );}
		XTAL_DEF_(mutate,inline,let) operator +=(fixed_shaped_q           auto const &t)       noexcept -> auto & {return S_::template zip_with<[] (auto       &u, auto const &v) XTAL_0FN_(do)     (u +=v)>(XTAL_REF_(t));}
		XTAL_DEF_(mutate,inline,let) operator -=(fixed_shaped_q           auto const &t)       noexcept -> auto & {return S_::template zip_with<[] (auto       &u, auto const &v) XTAL_0FN_(do)     (u -=v)>(XTAL_REF_(t));}
		XTAL_DEF_(mutate,inline,let) operator +=(_std::initializer_list<value_type>   t)       noexcept -> auto & requires same_q<_s...> {return S_::self() += T(t);}
		XTAL_DEF_(mutate,inline,let) operator -=(_std::initializer_list<value_type>   t)       noexcept -> auto & requires same_q<_s...> {return S_::self() -= T(t);}

	};
	using type = derive_t<homotype>;

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
