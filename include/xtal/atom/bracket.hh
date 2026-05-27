#pragma once
#include "./any.hh"
#include "./bucket.hh"





XTAL_ENV_(push)
namespace xtal::atom
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/*!
\brief
Extends `bucket` with function application and functional construction.
*/
template <class ...Us>	struct  bracket;
template <class ...Us>	using   bracket_t = typename bracket<Us...>::type;
template <class ...Us>	concept bracket_q = bond::tag_inner_fixed_p<bracket_t, Us...>;

XTAL_DEF_(let) bracket_f = [] XTAL_1FN_(call) (_detail::factory<bracket_t>::make);


////////////////////////////////////////////////////////////////////////////////

template <class U, auto N, auto ...Ns> struct   bracket<U   [N][Ns]...> : bracket<bracket_t<U[Ns]...>   [N]> {};
template <class U, auto N, auto ...Ns> struct   bracket<U(&)[N][Ns]...> : bracket<bracket_t<U[Ns]...>(&)[N]> {};


////////////////////////////////////////////////////////////////////////////////

template <scalar_array_q ...Us> requires same_q<Us...>
struct bracket<Us ...>
:	bracket<common_t<Us...>[sizeof...(Us)]>
{
};
template <class ...Us>
struct bracket
{
	template <class T>
	using endotype = typename bucket<Us...>::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<endotype<T>, bond::tag<bracket_t>>;

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
		//	XTAL_0IF (same_q<Us...> and atomic_q<value_type>) {
		//		return 0 == std::memcmp(s.data(), t.data(), S_::size_bytes());//TODO: Not working for complex values?
		//	}
			XTAL_0IF XTAL_TRY_(to) (
				static_cast<S_ const &>(s) == static_cast<S_ const &>(t)
			)
			XTAL_0IF_(else) {
				return [&]<auto ...I>(bond::seek_in_t<I...>)
					XTAL_0FN_(to) (...and (get<I>(s) == get<I>(t)))
				(bond::seek_to_t<size>{});
			}
		}

	public:
		using S_::reform;

		/*!
		\returns	A `revalue_f`d instance of `this`.
		*/
		XTAL_FN2_(to) (XTAL_DEF_(return,inline,let) reform(), apply())

		/*!
		\returns	A `revalue_f`d instance of `this`.
		*/
		XTAL_DEF_(return,inline,let)
		apply() const
		noexcept -> decltype(auto)
		{
			using F = decltype(T::revalue_f);
			if constexpr (same_q<Us...>) {
				return apply<typename S_::template form_t<return_t<F, value_type>[size]>>();
			}
			else {
				return apply<return_t<F, Us>...>();
			}
		}

		/*!
		\returns	An invocation of `F` applied to the `revalue_f`s of `this`.
		*/
		template <complete_q F>
		XTAL_DEF_(return,inline,explicit)
		operator F() const
		noexcept
		{
			return apply<F>();
		}

		/*!
		\returns	An invocation of `F` applied to the `revalue_f`s of `this`.
		*/
		template <class F>
		XTAL_DEF_(return,inline,let)
		apply() const
		noexcept -> decltype(auto)
		{
			return apply<bond::operate<F>{}>();
		}
		/*!
		\returns	The result of applying `f` to the `revalue_f`s of `this`.
		*/
		template <auto  f>
		XTAL_DEF_(return,inline,let)
		apply() const
		noexcept -> decltype(auto)
		{
			return apply(f);
		}
		/*!
		\returns	The result of applying `f` to the `revalue_f`s of `this`.
		*/
		XTAL_DEF_(return,inline,let)
		apply(auto &&f) const
		noexcept -> decltype(auto)
		{
			return [this, f=XTAL_REF_(f)]<auto ...I> (bond::seek_in_t<I...>)
				XTAL_0FN_(to) (f(S_::template coelement<I>()...))
			(bond::seek_to_t<size>{});
		}

	};
	using type = bond::derive_t<homotype>;

};


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
