#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::resource
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ..._s> XTAL_TYP cached;
template <typename ..._s> XTAL_USE cached_t = confined_t<cached<_s...>>;
template <typename ..._s> XTAL_REQ cached_q = bond::any_tag_p<cached, _s...>;


////////////////////////////////////////////////////////////////////////////////
///\
Provides local arena-like storage accessible via `cache<...>()`. \

template <class A, unsigned N>
struct cached<A[N]>
{
	using _op = bond::operating;
	
	using subkind = bond::tag<cached>;

	template <compound::any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;
		
	//	NOTE: Expected maximum is 64/8: 6 doubles not including coefficients...
		XTAL_SET L_cache = _op::alignment{}*sizeof(size_type);
		XTAL_SET N_cache = size_1 << _op::bit_ceiling_f(L_cache + sizeof(A)*N) - 1;
		alignas (N_cache) _std::byte m_cache[N_cache];

	public:
		using S_::S_;
		
		template <class ...Us>
		XTAL_DEF_(return,inline)
		XTAL_LET cache()
		XTAL_0EX
		{
			static_assert(aligned_n<Us...> <= N_cache);
			static_assert((...and _std::is_trivially_destructible_v<Us>));

			using W = _std::tuple<Us &...>;
			size_type i{};
			
			return [&] <auto ...I>(bond::seek_t<I...>)
				XTAL_0FN_(W{reinterpret_cast<bond::pack_item_t<I, W> &>(
					m_cache[maligned_f<bond::pack_item_t<I, W>>(i)]
				)...})
			(bond::seek_s<sizeof...(Us)> {});
		}

	};
};
template <>
struct cached<> : cached<size_type[bond::operating::alignment{}]>
{
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
