#pragma once
#include "./any.hpp"

#include "../conflux/any.hpp"




XTAL_ENV_(push)
namespace xtal::context
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
References content at the supplied integral path.


////////////////////////////////////////////////////////////////////////////////

template <typename   ...   > struct  dial;
template <typename   ...Ts > concept dial_q = tag_q<dial, Ts...>;
template <constant_q ...Ns >
struct dial<Ns...>
{
	using subkind = confined<confer<Ns>..., tag<dial>>;
	template <bundle_q S> using basetype = bundle_part_t<S, Ns::value...>;
	template <bundle_q S> using basekind = conflux::lift<basetype<S>>;
	template <bundle_q S> using semikind = compose<subkind, basekind<S>>;
	template <bundle_q S> using semitype = compose_s<conflux::base_t, semikind<S>>;
	template <bundle_q S>
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
		{
		}
 
	};
};
template <typename S, int ...Ns>
using dial_s = typename dial<constant_t<Ns>...>::template subtype<S>;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
