#pragma once
#include "./any.hpp"
#include "./compose.hpp"
#include "./collect.hpp"
#include "./collate.hpp"





XTAL_ENV_(push)
namespace xtal::common
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <typename V, int... Ns>
struct collage
{
	using subkind = compose<collate<V>, collect<Ns...>>;

	template <typename S>
	class subtype: public compose_s<S, subkind>
	{
		using S_ = compose_s<S, subkind>;
	
	public:
		using S_::S_;

		using solid_t    = typename S_::solid    ::type;
		using fluid_t    = typename S_::fluid    ::type;
		using spool_t    = typename S_::spool    ::type;
		using sequence_t = typename S_::sequence ::type;
		using product_t  = typename S_::product  ::type;
		using sum_t      = typename S_::sum      ::type;
		using series_t   = typename S_::series   ::type;
		using serial_t   = typename S_::serial   ::type;
		using pulsar_t   = typename S_::pulsar   ::type;
		using phasor_t   = typename S_::phasor   ::type;

	};
};

template <typename V, int... Ns>
using collage_t = compose_s<unit_t, collage<V, Ns...>>;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
