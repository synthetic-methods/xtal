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

template <typename V, int ...Ns>
struct collage;

template <typename V, int ...Ns>
using collage_t = typename collage<V, Ns...>::type;


template <typename V, int N>
struct collage<V, N>
{
	template <typename S>
	class subtype: public S
	{
	public:
		using S::S;

		using fluid_t = typename collate_t<N>::_fluid<V>::type;
		using spool_t = typename collate_t<N>:: spool<V>::type;

	};
	template <typename S> requires (0 < N)
	class subtype<S>: public S
	{
	public:
		using S::S;

		using  fluid_t = typename collate_t<N>::template _fluid<V>::type;
		using  spool_t = typename collate_t<N>::template  spool<V>::type;
		using  solid_t = typename collate_t<N>::template _solid<V>::type;
		using  group_t = typename collate_t<N>::template  group<V>::type;
		using scalar_t = typename collate_t<N>::template scalar<V>::type;
		using sector_t = typename collate_t<N>::template sector<V>::type;
		using series_t = typename collate_t<N>::template series<V>::type;
		using serial_t = typename collate_t<N>::template serial<V>::type;
		using pulsar_t = typename collate_t<N>::template pulsar<V>::type;
		using phasor_t = typename collate_t<N>::template phasor<V>::type;

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
