#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::arrange
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class ...As>	struct   cache;
template <class ...As>	using    cache_t = typename cache<As...>::type;
template <class ..._s>	concept  cache_q = bond::tag_p<cache, _s...>;


////////////////////////////////////////////////////////////////////////////////
///\
Provides local arena-like storage accessible via `cache<...>()`. \

template <class ...As>
struct cache
{
	template <class T>
	using holotype = bond::compose<bond::tag<cache>, bond::define<T>>;

	template <class T>
	class homotype : public holotype<T>
	{
		using S_ = holotype<T>;
		using I  = valued_u<_std::byte>;

		XTAL_SET N_cache = size_1 << bond::operating::bit_ceiling_f((0U +...+ _detail::aligned_n<As>));
		alignas (N_cache) _std::byte mutable m_cache[N_cache];

	public:
		using S_::S_;
	
		///\returns the size in `byte`s. \

		XTAL_DEF_(return,inline,static)
		XTAL_LET size()
		noexcept -> size_type
		{
			return N_cache;
		}

		///\returns `(void)` after overwriting the `byte`s in the cache with `(char) value`. \

		XTAL_DEF_(inline)
		XTAL_LET fill(I value=I{})
		noexcept -> void
		{
			memset(m_cache, value, N_cache);
		}

		///\returns a tuple of values conforming to `Vs...`, \
		representing the state of the cache prior to updating with `vs...`. \

		XTAL_DO2_(template <class ...Vs>
		XTAL_DEF_(return,inline)
		XTAL_LET form(Vs const &...vs),
		noexcept -> auto
		{
			_std::tuple<Vs &...>       x_ = form<Vs...>();
			_std::tuple<Vs  ...> const y_ = x_; x_ = _std::tie(vs...);
			return y_;
		})
		///\returns a tuple of references conforming to `Vs...`. \

		///\note\
		Access via value-based destructuring, or reference-based `get`. \

		///\usage
		/***```
		cache_t<_xtd::byte[0x40]> cache;

		auto cachet = cache.template form<X, Y>();
		auto [x, y] = cachet;
		auto &x = get<0>(cachet);
		auto &y = get<1>(cachet);
		```***/

		XTAL_DO2_(template <class ...Vs>
		XTAL_DEF_(return,inline)
		XTAL_LET form(),
		noexcept -> auto
		{
			return form<based_t<Vs>...>();
		})
		XTAL_DO2_(template <class ...Vs> requires based_q<Vs...>
		XTAL_DEF_(return,inline)
		XTAL_LET form(),
		noexcept -> auto
		{
			static_assert(_detail::aligned_n<Vs...> <= N_cache);
			static_assert((...and _std::is_standard_layout_v<Vs>));
			static_assert((...and _std::is_trivially_destructible_v<Vs>));

			using W = _std::tuple<Vs &...>;
			int i{0};
			
			return [&] <auto ...I>(bond::seek_t<I...>)
				XTAL_0FN_(W{form<Vs>(i)...})
			(bond::seek_s<sizeof...(Vs)> {});
		})
		XTAL_DO2_(template <class V>
		XTAL_DEF_(return,inline)
		XTAL_LET form(int &i),
		noexcept -> V &
		{
			return reinterpret_cast<V &>(m_cache[_detail::maligned_f<V>(i)]);
		})

	};
	using type = bond::isotype<homotype>;

};
template <>
struct cache<> : cache<size_type[bond::operating::alignment{}]>
{
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
