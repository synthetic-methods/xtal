#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::process
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ..._s> XTAL_TYP map;
template <typename ..._s> XTAL_USE map_t = confined_t<map<_s...>>;
template <typename ..._s> XTAL_ASK map_q = bond::tag_p<map, _s...>;


namespace _detail
{///////////////////////////////////////////////////////////////////////////////
}///////////////////////////////////////////////////////////////////////////////

template <class F, typename ...As>
struct map<F, As...>
{
	using subkind = bond::compose<As..., bond::tag<map>>;

	template <any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;
		
	public:
		using S_::S_;
		using S_::self;
		using S_::head;

		XTAL_DO2_(template <auto ...Ks>
		XTAL_TN2 functor(auto &&...xs),
		{
			return F{}(S_::functor(XTAL_REF_(xs)...));
		})

		XTAL_TN2 function(auto &&...xs)
		XTAL_0FX
		{
			return F{}(S_::function(XTAL_REF_(xs)...));
		}

	};
};


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
