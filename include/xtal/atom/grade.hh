#pragma once
#include "./any.hh"
#include "./group.hh"





XTAL_ENV_(push)
namespace xtal::atom
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
Extends `group` with point-wise addition and differential succession. \

template <class         ..._s>	struct   grade;
template <class         ..._s>	using    grade_t = typename grade<_s...>::type;
template <class         ..._s>	concept  grade_q = bond::array_tag_p<grade_t, _s...> and same_n<sized_n<_s>...>;

template <auto f=null_type{}>
XTAL_DEF_(return,inline,let)
grade_f(auto &&...oo)
noexcept -> auto
{
	return _detail::build<grade_t>::template with<f>(XTAL_REF_(oo)...);
}

////////////////////////////////////////////////////////////////////////////////

template <class ..._s>
struct grade
{
	template <class T>
	using endotype = typename group<_std::plus<void>, _s...>::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<endotype<T>, bond::tag<grade_t>>;

	template <class T>
	class homotype : public holotype<T>
	{
		using S_ = holotype<T>;
	
	protected:
		using          S_::N_data;
		using typename S_::U_data;

	public:// CONSTRUCT
		using S_::S_;

	public:// ACCESS
		using S_::element;
		using S_::self;
		using S_::twin;
	
	public:// OPERATE
		XTAL_DEF_(inline,let) operator ++(int) noexcept -> auto {auto t = twin(); operator++(); return t;}
		XTAL_DEF_(inline,let) operator --(int) noexcept -> auto {auto t = twin(); operator--(); return t;}

		///\
		Produces the successor by pairwise addition from `begin()` to `end()`, \
		assuming the entries of `this` are finite differences/derivatives. \

		XTAL_DEF_(inline,let)
		operator ++ ()
		noexcept -> T &
		{
			[this]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN {((get<I>(self()) += get<I + 1>(self())),...);}
			(bond::seek_s<N_data - 1>{});
			
			return self();
		}
		///\
		Produces the predecessor by pairwise subtraction from `end()` to `begin()`, \
		assuming the entries of `this` are finite differences/derivatives. \

		XTAL_DEF_(inline,let)
		operator -- ()
		noexcept -> T &
		{
			[this]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN {((get<I>(self()) -= get<I + 1>(self())),...);}
			(bond::antiseek_s<N_data - 1>{});
			
			return self();
		}

	};
	using type = derive_t<homotype>;

};
static_assert(atomic_q<grade_t<float[2]>>);


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
