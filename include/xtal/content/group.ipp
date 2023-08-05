#pragma once
#include "./any.ipp"






XTAL_ENV_(push)
namespace xtal::content
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <         typename ..._s> XTAL_NYM group;
template <         typename ..._s> XTAL_ASK group_q = tag_p<group, _s...>;
template <class U, typename ...As> XTAL_USE group_t = confined_t<group<U>, As...>;


////////////////////////////////////////////////////////////////////////////////
///\
Represents a local `{store,serve}` pair, \
used as e.g. a buffer and its abstract/copyable `std::span`. \

template <additive_group_q U>
struct group<U>
{
	using subkind = confer<U, tag<group>>;

	template <class S>
	class subtype: public compose_s<S, subkind>
	{
		using S_ = compose_s<S, subkind>;

	public:
		using S_::S_;
		using S_::self;
		using S_::twin;

		XTAL_CON subtype(XTAL_DEF_(to_q<U>) w)
		XTAL_0EX
		:	S_(XTAL_REF_(w))
		{
			normalize();
		}
		XTAL_FN1 normalize()
		XTAL_0EX
		{
			return self();
		}

		XTAL_OP2 + (XTAL_DEF w) XTAL_0FX {return twin() += XTAL_REF_(w);}
		XTAL_OP2 - (XTAL_DEF w) XTAL_0FX {return twin() -= XTAL_REF_(w);}
				
		XTAL_OP1 += (subtype const &t) XTAL_0EX {S_::head() += t.head(); return self().normalize();}
		XTAL_OP1 -= (subtype const &t) XTAL_0EX {S_::head() -= t.head(); return self().normalize();}
	
	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
