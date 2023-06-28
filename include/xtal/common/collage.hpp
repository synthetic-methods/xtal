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

template <int N, typename V>
struct collage
{
	using subkind = compose<collate<V>, collect<N>>;

	template <typename S>
	class subtype: public compose_s<S, subkind>
	{
		using co = compose_s<S, subkind>;
	
	public:
		using co::co;

		using solid_t = typename co::solid::type;
		using fluid_t = typename co::fluid::type;

		using sequence_t = typename co::sequence ::type;
		using product_t  = typename co::product  ::type;
		using sum_t      = typename co::sum      ::type;
		using series_t   = typename co::series   ::type;
		using serial_t   = typename co::serial   ::type;
		using pulsar_t   = typename co::pulsar   ::type;
		using phasor_t   = typename co::phasor   ::type;
		using siphon_t   = typename co::siphon   ::type;

	};
};

template <int N, typename V>
using collage_t = compose_t<collage<N, V>>;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
