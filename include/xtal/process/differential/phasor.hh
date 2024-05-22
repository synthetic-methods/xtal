#pragma once
#include "./any.hh"

#include "../../algebra/differential/modular.hh"
#include "../../resource/example.hh"



XTAL_ENV_(push)
namespace xtal::process::differential
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ..._s> XTAL_TYP phasor;
template <typename ..._s> XTAL_USE phasor_t = confined_t<phasor<_s...>>;
template <typename ..._s> XTAL_ASK phasor_q = bond::tag_p<phasor, _s...>;


////////////////////////////////////////////////////////////////////////////////
///\
Manages a truncated fixed-point unit differential like `phasor`, \
providing evaluation/update via succession/replacement. \

template <size_t N_data, class K_data, typename ...As>
struct phasor<K_data[N_data], As...>
{
	template <size_t N>
	using U_modular = algebra::differential::modular_t<K_data[N]>;
	using U_sample = occur::sample_t<>;

	using W_ = U_modular<N_data>;
	
	using re = bond::realize<K_data>;
	using V = typename re::delta_t;
	using U = typename re::alpha_t;
	XTAL_LET_(U) u_onset = bond::seek_constant_t<As..., cardinal_t<0>>{};

	using subkind = bond::compose<bond::tag<phasor>
	,	_detail::refer_multiplicative_group<W_>
	,	typename occur::indent_s<W_>::template funnel<>
	,	As...
	>;
	
	template <class S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;
		using H_ = XTAL_TYP_(XTAL_ANY_(S_).head());

	protected:
		using typename S_::T_self;

	public:
		using S_::S_;

		///\todo\
		Override constructors/accessors to apply initial `u_onset`. \

	public:
		using S_::self;
		using S_::head;

		XTAL_DO4_(XTAL_OP0_(implicit) H_(), {return head();})
		///\note\
		The above is defined in-case `refine_head` is bypassed...

		///\todo\
		...find a cleaner way to define the conversion, perhaps via `refer`?

	public:
		///\
		Access by dynamic index. \
		
		///\todo\
		Replace with accessor-decorator.

		XTAL_TO4_(XTAL_TN2 get(size_t i), head().get(i))

	public:
		///\
		Evaluation by succession. \
		
		template <auto ...Is> requires none_n<Is...>
		XTAL_TN2 functor()
		XTAL_0EX
		{
			if constexpr (resource::example_q<S_>) {
				/**/
				auto phi = ++head();
				return phi()*algebra::series_t<U[N_data]>(S_::sample().rate());
				/*/
				static_assert(N_data == 2);
				auto phi = ++head();
				return bond::pact_f(phi(0), phi(1)*S_::sample().rate());
				/***/
			}
			else {
				return ++head();
			}
		}
		///\
		Evaluation by (possibly indented) replacement then succession. \
		
		template <auto ...Is> requires none_n<Is...>
		XTAL_TN2 functor(subarray_q<N_data> auto &&a)
		XTAL_0EX
		{
			(void) S_::influx(XTAL_REF_(a));
			return functor();
		}
		
		///\todo\
		Use `resource::example` to manage downsampling \
		e.g. by integer multiplication followed by normalization. \

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
