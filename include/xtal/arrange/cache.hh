#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::arrange
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class ...As>	struct   cache;
template <class ...As>	using    cache_t = typename cache<As...>::type;
template <class ..._s>	concept  cache_q = bond::any_tag_p<cache, _s...>;


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
		using I  = _std::underlying_type_t<_std::byte>;

	//	NOTE: Expected maximum is 64/8: 6 doubles not including coefficients...
		XTAL_SET L_cache = bond::operate<_std::byte>::alignment{};
		XTAL_SET N_cache = size_1 << bond::operating::bit_ceiling_f((L_cache +...+ sizeof(As))) - 1;
		//\
		XTAL_SET A_cache = alignof(common_t<scalar_t<As>...>);
		XTAL_SET A_cache = N_cache;
		alignas (A_cache) _std::byte m_cache[N_cache];

	public:
		using S_::S_;
	
		XTAL_LET free(I value=0)
		noexcept -> void
		{
			memset(m_cache, value, N_cache);
		}
		template <class V>
		XTAL_DEF_(short)
		XTAL_LET form(int &i)
		noexcept -> V &
		{
			return reinterpret_cast<V &>(m_cache[_detail::maligned_f<V>(i)]);
		}
		template <class ...Vs>
		XTAL_DEF_(long)
		XTAL_LET form()
		noexcept -> auto
		{
			static_assert(_detail::aligned_n<Vs...> <= N_cache);
			static_assert((...and _std::is_trivially_destructible_v<Vs>));

			using W = _std::tuple<Vs &...>;
			int i{0};
			
			return [&] <auto ...I>(bond::seek_t<I...>)
				XTAL_0FN_(W{form<Vs>(i)...})
			(bond::seek_s<sizeof...(Vs)> {});
		}

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
