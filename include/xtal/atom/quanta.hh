#pragma once
#include "./any.hh"
#include "./block.hh"





XTAL_ENV_(push)
namespace xtal::atom
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
Extends `block` with function application and functional construction. \

template <        class ..._s>	struct   quanta;
template <        class ..._s>	using    quanta_t = typename quanta<_s...>::type;
template <        class ..._s>	concept  quanta_q = bond::array_tag_p<quanta_t, _s...> and fixed_shaped_q<_s...>;

template <class U, auto  N, auto  ..._s> struct   quanta<U   [N][_s]...> : quanta<quanta_t<U[_s]...>   [N]> {};
template <class U, auto  N, auto  ..._s> struct   quanta<U(&)[N][_s]...> : quanta<quanta_t<U[_s]...>(&)[N]> {};


XTAL_FX0_(alias) (template <auto f=_std::identity{}>
XTAL_DEF_(return,inline,let)
quanta_f(auto &&...oo),
	_detail::factory<quanta_t>::
		template make<f>(XTAL_REF_(oo)...))


////////////////////////////////////////////////////////////////////////////////

template <scalar_q ..._s> requires same_q<_s...>
struct quanta<_s ...>
:	quanta<common_t<_s...>[sizeof...(_s)]>
{
};
template <class ..._s>
struct quanta
{
	template <class T>
	using endotype = typename block<_s...>::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<endotype<T>, bond::tag<quanta_t>>;

	template <class T>
	class homotype : public holotype<T>
	{
		using S_ = holotype<T>;

	public:// CONSTRUCT
		using S_::S_;

		using typename S_::value_type;
		using typename S_::scale_type;

	public:// ACCESS
		using S_::size;
		using S_::self;
		using S_::twin;

	public:// OPERATE

		XTAL_DEF_(return,inline,friend,let)
		operator==(homotype const &s, homotype const &t)
		noexcept -> bool
		{
			XTAL_IF0
		//	XTAL_0IF (same_q<_s...> and _std::is_standard_layout_v<value_type>) {
		//		return 0 == _std::memcmp(s.data(), t.data(), S_::size_bytes());//FIXME: Not working for complex values?
		//	}
			XTAL_0IF XTAL_TRY_(return) (
				static_cast<S_ const &>(s) == static_cast<S_ const &>(t)
			)
			XTAL_0IF_(else) {
				return [&]<auto ...I>(bond::seek_t<I...>)
					XTAL_0FN_(return) (...and (get<I>(s) == get<I>(t)))
				(bond::seek_s<size>{});
			}
		}

		///\returns `true` if the underlying `data` is zero, `false` otherwise. \

		template <auto N_value=0>
		XTAL_DEF_(return,inline,let)
		blanked() const
		noexcept -> auto
		{
			typename S_::template form_t<based_t<_s>...> constexpr z{N_value};
			return   z == self();
		}
		///\returns the result of `blanked()` before refilling with `N_value=0`. \

		template <auto N_value=0>
		XTAL_DEF_(inline,let)
		blanket()
		noexcept -> bool
		requires same_q<_s...>
		{
			using sigma_type  = typename bond::fixture<scale_type>::sigma_type;
			auto constexpr u  =    static_cast<scale_type>(N_value);
			auto constexpr v  = _xtd::bit_cast<sigma_type>(u);
			bool const     z  = blanked();
			auto const     zu = u* static_cast<scale_type>(z);
			auto const    _zv = v&-z;
#if XTAL_ENV_(LLVM)
			if constexpr (false) {}
#else
			if constexpr (anyplex_q<value_type>) {
				auto &s = desolve_f(*this);
				bond::seek_forward_f<size>([&] (auto I) XTAL_0FN {
					XTAL_IF0
					XTAL_0IF (simplex_q<value_type>) {return reinterpret_cast<sigma_type &>(s[I]   ) |= _zv;}
					XTAL_0IF (complex_q<value_type>) {return reinterpret_cast<sigma_type &>(s[I][0]) |= _zv;}
				});
			}
#endif
			else {
				auto const n = static_cast<value_type>(z)*u;
				auto      &s = *this;
				bond::seek_forward_f<size>([&] (auto I) XTAL_0FN {
					get<I>(s) += n;
				});
			}
			return z;
		}

	public:
		///\returns an instance of `Y` constructed from the elements of `this`. \

		XTAL_FX4_(alias) (template <complete_q Y>
		XTAL_DEF_(return,inline,explicit operator) Y(), apply<Y>())

		///\returns an instance of `Y` constructed from the elements of `this`. \

		XTAL_DEF_(return,inline,let)
		apply() const
		noexcept -> decltype(auto)
		{
			if constexpr (same_q<_s...>) {
				using coordinate_type = XTAL_ALL_(T::coordinate(XTAL_ANY_(value_type)));
				return apply<typename S_::template form_t<coordinate_type[size]>>();
			}
			else {
				return apply<based_t<_s>...>();
			}
		}
		template <class F>
		XTAL_DEF_(return,inline,let)
		apply() const
		noexcept -> decltype(auto)
		{
			return apply<evoke_t<F>{}>();
		}
		///\returns the result of applying `f` to the elements of `this`. \

		template <auto  f>
		XTAL_DEF_(return,inline,let)
		apply() const
		noexcept -> decltype(auto)
		{
			return apply(constant_t<f>{});
		}
		///\returns the result of applying `f` to the elements of `this`. \

		XTAL_DEF_(return,inline,let)
		apply(auto &&f) const
		noexcept -> decltype(auto)
		{
			return [this, f=XTAL_REF_(f)]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN_(return) (f(S_::template coelement<I>()...))
			(bond::seek_s<size>{});
		}

	};
	using type = derive_t<homotype>;

};


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
