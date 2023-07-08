#pragma once
#include "./any.hpp"
#include "./compose.hpp"
#include "./collect.hpp"
#include "./collate.hpp"





XTAL_ENV_(push)
namespace xtal::common
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

namespace _detail
{///////////////////////////////////////////////////////////////////////////////

template <typename T>
using row_t = typename T::sector_t;

template <typename T>
using column_t = typename T::scalar_t;


}///////////////////////////////////////////////////////////////////////////////

template <typename V, int ...Ns>
struct collage;

template <typename V, int ...Ns>
using collage_t = typename collage<V, Ns...>::type;


template <typename V, int N>
struct collage<V, N>
{
	using subkind = compose<collate<V>, collect<N>>;

	template <typename S>
	class subtype: public compose_s<S, subkind>
	{
		using S_ = compose_s<S, subkind>;
	
	public:
		using S_::S_;

		using  fluid_t = typename S_::fluid ::type;
		using  spool_t = typename S_::spool ::type;
		using  solid_t = typename S_::solid ::type;
		using  group_t = typename S_::group ::type;
		using scalar_t = typename S_::scalar::type;
		using sector_t = typename S_::sector::type;
		using series_t = typename S_::series::type;
		using serial_t = typename S_::serial::type;
		using pulsar_t = typename S_::pulsar::type;
		using phasor_t = typename S_::phasor::type;

	};
	using type = subtype<unit_t>;
};
template <typename V, int N, int ...Ns>
struct collage<V, N, Ns...>
{
	template <typename S>
	class subtype: public S
	{
	public:
		using S::S;

		using value_t = typename collage_t<V, N>::group_t;
		using group_t = typename collage_t<value_t, Ns...>::group_t;

	};
	using type = subtype<unit_t>;
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
