#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::atom
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
Provides local arena-like storage for `atomic_q` values. \

template <class ...As>	struct   blob;
template <class ...As>	using    blob_t = typename blob<As...>::type;
template <class ..._s>	concept  blob_q = bond::tag_p<blob, _s...>;


////////////////////////////////////////////////////////////////////////////////

template <class ...As>
struct blob
{
	template <class T>
	using holotype = bond::compose<bond::tag<blob>, bond::define<T>>;

	template <class T>
	class homotype : public holotype<T>
	{
		using S_ = holotype<T>;
		using U  = _std::underlying_type_t<_std::byte>;

		static size_type constexpr N_bytes = one << _std::bit_width(_detail::aligned<As...>::size() - one);
		alignas (N_bytes) static _std::byte constexpr m_zeros[N_bytes]{};
		alignas (N_bytes)        _std::byte mutable   m_bytes[N_bytes]  ;

	public:// CONSTRUCT
		using S_::S_;
	
	public:// OPERATE

		///\returns the size in `byte`s. \

		static cardinal_constant_t<N_bytes> constexpr size{};

		///\returns `true` if the underlying `data` is zero, `false` otherwise. \

		XTAL_DEF_(return,inline,let)
		blanked() const
		noexcept -> auto
		{
			return 0 == _std::memcmp(m_zeros, m_bytes, N_bytes);
		}

		///\returns `(void)` after overwriting the `byte`s in the blob with `(U) value`. \

		XTAL_DEF_(inline,let)
		fill(auto value=0)
		noexcept -> void
		{
			_std::memset(m_bytes, static_cast<U>(value), N_bytes);
		}

		///\returns a tuple of values conforming to `Vs...`, \
		representing the state of the blob prior to updating with `vs...`. \

		XTAL_FX2_(do) (template <class ...Vs>
		XTAL_DEF_(return,inline,let)
		form(Vs const &...vs),
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
		blob_t<_xtd::byte[0x40]> blob;

		auto glob = blob.template form<X, Y>();
		auto [x, y] = glob;
		auto &x = get<0>(glob);
		auto &y = get<1>(glob);
		```***/

		XTAL_FX2_(do) (template <class ...Vs>
		XTAL_DEF_(return,inline,let)
		form(),
		noexcept -> auto
		{
			return form<based_t<Vs>...>();
		})
		XTAL_FX2_(do) (template <class ...Vs> requires based_q<Vs...>
		XTAL_DEF_(return,inline,let)
		form(),
		noexcept -> auto
		{
			static_assert(_detail::aligned<Vs...>::size() <= N_bytes);
		//	static_assert(_xtd::trivially_constructible<Vs...>);

			using W = _std::tuple<Vs &...>;
			int i{0};
			
			return [&] <auto ...I>(bond::seek_t<I...>)
				XTAL_0FN_(to) (W{form<Vs>(i)...})
			(bond::seek_s<sizeof...(Vs)> {});
		})
		XTAL_FX2_(do) (template <class V>
		XTAL_DEF_(return,inline,let)
		form(int &i),
		noexcept -> V &
		{
			return reinterpret_cast<V &>(m_bytes[_detail::aligned<V>::static_bump(i)]);
		})

	};
	using type = bond::derive_t<homotype>;

};
template <>
struct blob<> : blob<size_type[bond::fit<>::alignment{}()]>
{
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
