#pragma once
#include "./any.hh"

#include "../../algebra/differential/phase.hh"




XTAL_ENV_(push)
namespace xtal::process::differential
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ..._s> struct  phasor;
template <typename ..._s> using   phasor_t = confined_t<phasor<_s...>>;
template <typename ..._s> concept phasor_q = bond::tag_p<phasor, _s...>;


////////////////////////////////////////////////////////////////////////////////
///\
Manages a truncated fixed-point unit differential like `phasor`, \
providing evaluation/update via succession/replacement. \

template <size_t N_data, class W_data, typename ...As>
struct phasor<W_data[N_data], As...>
{
	template <size_t N>
	using phase_u = algebra::differential::phase_t<W_data[N]>;

	using W_ = phase_u<N_data>;
	
	using re = bond::realize<W_data>;
	using V = typename re::delta_t;
	using U = typename re::alpha_t;

	using subkind = bond::compose<bond::tag<phasor>
	,	As...
	,	_detail::refer_multiplicative_group<W_, 1>// Necessary?
	,	typename occur::indent_s<W_>::template funnel<>
	>;
	
	template <class S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;

	public://protected:
		using typename S_::T_self;

	public:
		using S_::S_;

	public:
		using S_::self;
		using S_::head;


	public:
		///\
		Access by dynamic index. \
		
		///\todo\
		Replace with accessor-decorator.

		XTAL_TO4_(XTAL_TN2 get(size_t i), head().get(i))

	public:
		///\
		Evaluation by succession. \
		
		XTAL_DO2_(template <auto ...Is> requires none_n<Is...>
		XTAL_TN2 functor(),
		{
			++head(); return head();
		})
		///\
		Evaluation by (possibly indented) replacement then succession. \
		
		XTAL_DO2_(template <auto ...Is> requires none_n<Is...>
		XTAL_TN2 functor(subarray_q<N_data> auto &&a),
		{
			(void) S_::influx(XTAL_REF_(a));
			return functor();
		})
		
		///\todo\
		Introduce `occur::sample` etc to manage downsampling \
		(by integer multiplication followed by normalization). \

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
