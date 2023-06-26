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

template <int N, typename Z>
struct collage
{
	using subkind = compose<collate<Z>, collect<N>>;

	template <typename S>
	class subtype: public compose_s<S, subkind>
	{
		using co = compose_s<S, subkind>;
	
	public:
		using co::co;

      using  fluid_t  = typename co:: fluid::type;
      using siphon_t  = typename co::siphon::type;
      using sluice_t  = typename co::sluice::type;
      
      using  solid_t  = typename co:: solid::type;
      using scalar_t  = typename co::scalar::type;
      using product_t = typename co::product::type;
      using sum_t     = typename co::sum::type;
      using series_t  = typename co::series::type;
      using serial_t  = typename co::serial::type;
      using pulsar_t  = typename co::pulsar::type;
      using phasor_t  = typename co::phasor::type;

	};
};

template <int N, typename Z>
using collage_t = compose_t<collage<N, Z>>;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
