#pragma once
#include "./any.hh"
#include "./block.hh"





XTAL_ENV_(push)
namespace xtal::atom
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/*!
\brief
Extends `block` with function application and functional construction.
*/
template <class ...Us>	struct  brace;
template <class ...Us>	using   brace_t = typename brace<Us...>::type;
template <class ...Us>	concept brace_q = bond::tag_infixed_p<brace_t, Us...>;

XTAL_DEF_(let) brace_f = [] XTAL_1FN_(call) (_detail::factory<brace_t>::make);


////////////////////////////////////////////////////////////////////////////////

template <class U, auto N, auto ...Ns> struct   brace<U   [N][Ns]...> : brace<brace_t<U[Ns]...>   [N]> {};
template <class U, auto N, auto ...Ns> struct   brace<U(&)[N][Ns]...> : brace<brace_t<U[Ns]...>(&)[N]> {};


////////////////////////////////////////////////////////////////////////////////

template <scalar_q ...Us> requires same_q<Us...>
struct brace<Us ...>
:	brace<common_t<Us...>[sizeof...(Us)]>
{
};
template <class ...Us>
struct brace
{
	template <class T>
	using endotype = typename block<Us...>::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<endotype<T>, bond::tag<brace_t>>;

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
		//		return 0 == _std::memcmp(s.data(), t.data(), S_::size_bytes());//TODO: Not working for complex values?
		//	}
			XTAL_0IF XTAL_TRY_(to) (
				static_cast<S_ const &>(s) == static_cast<S_ const &>(t)
			)
			XTAL_0IF_(else) {
				return [&]<auto ...I>(bond::seek_t<I...>)
					XTAL_0FN_(to) (...and (get<I>(s) == get<I>(t)))
				(bond::seek_s<size>{});
			}
		}

		/*!
		\returns	`true` if the underlying `data` is zero, `false` otherwise.
		*/
		template <auto N_value=0>
		XTAL_DEF_(return,inline,let)
		blanked() const
		noexcept -> auto
		{
			typename S_::template form_t<based_t<Us>...> constexpr z{N_value};
			return   z == self();
		}
		/*!
		\returns	The result of `blanked()` before refilling with `N_value=0`.
		*/
		template <auto N_value=0>
		XTAL_DEF_(inline,let)
		blanket()
		noexcept -> bool
		requires same_q<Us...>
		{
			using sigma_type  = typename bond::fit<scale_type>::sigma_type;
			auto constexpr u  =    static_cast<scale_type>(N_value);
			auto constexpr v  = _xtd::bit_cast<sigma_type>(u);
			bool const     z  = blanked();
			auto const     zu = u* static_cast<scale_type>(z);
			auto const    _zv = v&-z;
#if XTAL_ENV_(LLVM)
			if constexpr (false) {}
#else
			if constexpr (numeric_q<value_type>) {
				auto &s = restruct_f(*this);
				bond::seek_until_f<size>([&]<constant_q I> (I) XTAL_0FN {
					XTAL_IF0
					XTAL_0IF (simplex_q<value_type>) {return reinterpret_cast<sigma_type &>(s[I{}]   ) |= _zv;}
					XTAL_0IF (complex_q<value_type>) {return reinterpret_cast<sigma_type &>(s[I{}][0]) |= _zv;}
				});
			}
#endif
			else {
				auto const n = static_cast<value_type>(z)*u;
				auto      &s = *this;
				bond::seek_until_f<size>([&]<constant_q I> (I) XTAL_0FN {
					get<I{}>(s) += n;
				});
			}
			return z;
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
			return [this, f=XTAL_REF_(f)]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN_(to) (f(S_::template coelement<I>()...))
			(bond::seek_s<size>{});
		}

	};
	using type = bond::derive_t<homotype>;

};


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
