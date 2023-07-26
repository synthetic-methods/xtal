#pragma once
#include "./anybody.hpp"

#include "../conflux/any.hpp"




XTAL_ENV_(push)
namespace xtal::context
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
Wrapper used to tunnel an existing type using `std::tuple`-based traversal.

///\see [../process/matrix.hpp].

////////////////////////////////////////////////////////////////////////////////

template <typename   ...   > struct  shard;
template <typename   ...Ts > concept shard_q = tag_p<shard, Ts...>;
template <constant_q ...Ns >
struct shard<Ns...>
{
	using subkind = confined<confer<Ns>..., tag<shard>>;
	template <bundle_q S> using basetype = bundle_part_t<S, Ns{}...>;
	template <bundle_q S> using basekind = conflux::conferred<basetype<S>>;
	template <class S> using semikind = compose<subkind, basekind<S>>;
	template <class S> using semitype = compose_s<conflux::any_t<>, semikind<S>>;
	template <class S>
	class subtype: public semitype<S>
	{
		using S_ = semitype<S>;

	public:
		using S_::S_;

	};
	template <bundle_q S> requires iterated_q<basetype<S>>
	class subtype<S>: public semitype<S>
	{
		using S_ = semitype<S>;
		using U_ = basetype<S>;
		using V_ = value_t<U_>;

	public:
		using S_::S_;

		XTAL_CON subtype(bracket_t<V_> w)
		:	S_{U_(XTAL_MOV_(w))}
		{}
 
	};
};
template <class S, int ...Ns>
using shard_s = typename shard<constant_t<Ns>...>::template subtype<S>;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
