#pragma once
#include "./anybody.hpp"

#include "../conflux/any.hpp"




XTAL_ENV_(push)
namespace xtal::context
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
Wrapper used to tunnel an existing type using `std::tuple`-based traversal.

///\see [../process/cross.hpp].

////////////////////////////////////////////////////////////////////////////////

template <typename     ..._s> XTAL_NYM shard;
template <typename     ...Ts> XTAL_ASK shard_q = tag_p<shard, Ts...>;
template <class S, int ...Ns> XTAL_USE shard_s = compose_s<S, shard<integer_t<Ns>...>>;

template <constant_q ...Ns>
struct shard<Ns...>
{
	using path = confined<tag<shard>, confer<Ns>...>;
	
	template <pack_q S> using leaf_t = pack_item_t<S, Ns{}...>;
	template <pack_q S> using leaf_s = conflux::conferred_t<leaf_t<S>>;
	template <pack_q S> using node_s = compose_s<leaf_s<S>, path>;
	template <pack_q S>
	class subtype: public node_s<S>
	{
		using S_ = node_s<S>;
		using L_ = leaf_t<S>;

	public:
		using S_::S_;
		
		XTAL_CON subtype(bracket_t<devalued_t<L_>> w)
		XTAL_REQ bracket_q<L_>
		:	S_{L_(XTAL_MOV_(w))}
		{}
 
		struct refract
		{
			using subkind = conflux::defer<L_>;

			template <concord::any_q R> requires (0 == sizeof...(Ns))
			class subtype: public compose_s<R, subkind>
			{
				using R_ = compose_s<R, subkind>;
				
			public:
				using R_::R_;
				using R_::self;
				using R_::head;
				using R_::influx;

				///\todo\
				Implement `shard_q` bounds-checking based on the `rank` specified by `R` or `Ns...`? \
				Requires subsequence ordering for `pack`s? \
				
				XTAL_FNX influx(context::shard_q auto shard_o, XTAL_DEF ...oo)
				XTAL_0EX
				{
					auto &w = pack_item_f(head(), shard_o.tuple());
					auto &x = decltype(w) (shard_o);
					_std::swap(w, x);
					return w == x or R_::influx(XTAL_REF_(oo)...);
				}

			};
		};
	
	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
