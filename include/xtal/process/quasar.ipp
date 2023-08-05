#pragma once
#include "./any.ipp"
#include "./star.ipp"
#include "./phasor.ipp"
#include "./pulsar.ipp"
#include "../content/quark.ipp"




XTAL_ENV_(push)
namespace xtal::process
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <                     typename ..._s> XTAL_NYM quasar;
template <                     typename ..._s> XTAL_ASK quasar_q = tag_p<quasar, _s...>;
template <array_q W=size_t[2], typename ...As> XTAL_USE quasar_t = confined_t<quasar<W>, As...>;


////////////////////////////////////////////////////////////////////////////////
///\

template <array_q W, typename ...As>
struct quasar<W, As...>
{
	using phasor_u = phasor_t<W, As...>;
	using pulsar_u = pulsar_t<W, As...>;
	
	XTAL_LET N_ = _std::       extent_v<W>;
	XTAL_USE U_ = _std::remove_extent_t<W>;
	
	using _computer = compute<U_>;
	using delta_t = typename _computer::delta_t;
	using alpha_t = typename _computer::alpha_t;

	using scope_u = content::quark_t<U_>[N_];
	using subkind = compose<tag<quasar>, As..., star<scope_u>>;

	template <class S>
	class subtype: public compose_s<S, subkind>
	{
		using S_ = compose_s<S, subkind>;
	
	public:
		using S_::S_;
		using S_::self;
		using S_::head;
		using S_::d;

		///\
		Access by name/index (dynamic). \
		
		XTAL_TO4_(XTAL_FN2 phase(size_t i), d(i).phase())
		XTAL_TO4_(XTAL_FN2 pulse(size_t i), d(i).pulse())

		///\
		Access by name/index (static). \
		
		XTAL_TO4_(template <size_t I> XTAL_FN2 phase(XTAL_DEF ...oo), _std::get<I>(head()).phase(XTAL_REF_(oo)...))
		XTAL_TO4_(template <size_t I> XTAL_FN2 pulse(XTAL_DEF ...oo), _std::get<I>(head()).pulse(XTAL_REF_(oo)...))

		///\
		Projection to components by name. \

		XTAL_FN2 phasor() XTAL_0FX {return [this]<auto ...I>(seek_t<I...>) XTAL_0FN_(phasor_u(phase<I>()...)) (seek_f<N_>{});}
		XTAL_FN2 pulsar() XTAL_0FX {return [this]<auto ...I>(seek_t<I...>) XTAL_0FN_(pulsar_u(pulse<I>()...)) (seek_f<N_>{});}
		
		///\
		Projection to initial component by type. \

		XTAL_DO4_(XTAL_OP0_(explicit) delta_t(), {return pulse<0>();})
		XTAL_DO4_(XTAL_OP0_(explicit) alpha_t(), {return phase<0>();})

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
