#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::atom
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
Provides local arena-like storage for `atomic_q` values. \

///\usage
/***```
blob_t<_xtd::byte[0x40]> blob;

auto glob = blob.template form<X, Y>();
auto [x, y] = glob;
auto &x = get<0>(glob);
auto &y = get<1>(glob);
```***/

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

	protected:
		template <class ...Us>
		using form_t = bond::pack_t<Us...>;

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

		///\returns a tuple of _rvalues_ conforming to `Vs...`, \
		representing the state of the blob prior to updating with `vs...`. \

		XTAL_FX2_(do) (template <class ...Vs>
		XTAL_DEF_(return,inline,let)
		form(Vs const &...vs),
		noexcept -> decltype(auto)
		{
			form_t<Vs  ...> f = form  <Vs      &&...>();
			form  <Vs &...>() = form_t<Vs const &...>{vs...};
			return f;
		})

		///\returns a tuple of references conforming to `Vs...`. \

		///\note\
		Access via value-based destructuring, or reference-based `get`. \

		XTAL_FX2_(do) (template <class ...Vs>
		XTAL_DEF_(return,inline,let)
		form(),
		noexcept -> decltype(auto)
		{
			return form<Vs &...>();
		})
		XTAL_FX2_(do) (template <_xtd::reference ...Vs>
		XTAL_DEF_(return,inline,let)
		form(),
		noexcept -> decltype(auto)
		{
			static_assert(_detail::aligned<Vs...>::size() <= N_bytes);
			int i{0};
			return [&] <auto ...I>(bond::seek_t<I...>)
				XTAL_0FN_(to) (form_t<Vs &&...>{form<Vs &&>(i)...})
			(bond::seek_s<sizeof...(Vs)> {});
		})
		XTAL_FX2_(do) (template <class V>
		XTAL_DEF_(return,inline,let)
		form(int &i),
		noexcept -> decltype(auto)
		{
			return reinterpret_cast<V &&>(m_bytes[_detail::aligned<V>::advance(i)]);
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
