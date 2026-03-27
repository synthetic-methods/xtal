#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::occur
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class ..._s> struct   resync;
template <class ..._s> using    resync_t =     confined_t<resync< _s...>>;
template <class ..._s> concept  resync_q = bond::tag_inner_p<resync, _s...> ;


//////////////////////////////////////////////////////////////////////////////////

template <class U>
struct resync<U>
{
	using superkind = bond::compose<flow::tag<resync>, defer<U>>;

	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind>;
		using T_ = typename S_::self_type;
	
	public:// CONSTRUCT
		using S_::S_;

	public:// OPERATE
		using S_::self;
		using S_::head;

		using sync_type = U;

		XTAL_FN1_(go) (XTAL_DEF_(return,inline,get) sync, [] (auto &&o, auto &&...oo)
		XTAL_0FN_(to) (XTAL_REF_(o).head(XTAL_REF_(oo)...)))

	};
};


////////////////////////////////////////////////////////////////////////////////

template <> struct resync<void> : resync<signed> {};
template <> struct resync<    > : resync<signed> {};

XTAL_DEF_(let) resync_f = [] XTAL_1FN_(call) (resync_t<>);


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
