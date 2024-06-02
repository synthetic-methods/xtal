#pragma once
#include "./any.hh"

#include "../../algebra/differential/circular.hh"
#include "../../resource/example.hh"
#include "../../resource/biased.hh"


XTAL_ENV_(push)
namespace xtal::process::differential
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ..._s> XTAL_TYP phasor;
template <typename ..._s> XTAL_USE phasor_t = confined_t<phasor<_s...>>;
template <typename ..._s> XTAL_ASK phasor_q = bond::head_tag_p<phasor, _s...>;


////////////////////////////////////////////////////////////////////////////////
///\
Manages a truncated fixed-point unit differential like `phasor`, \
providing evaluation/update via succession/replacement. \

template <size_t N_data, class K_data, typename ...As>
struct phasor<K_data[N_data], As...>
{
	using Op = bond::operate<K_data>;

	using V_data = typename Op::delta_t;
	using U_data = typename Op::alpha_t;

	using  _data = U_data[N_data];
	using W_data = algebra::d_:: circular_t<_data>;
	using L_data = algebra::d_::   linear_t<_data>;
	using S_data = algebra::       series_t<_data>;
	using R_data = bond::pack_row_t<L_data>;
	
	using subkind = bond::compose<bond::tag<phasor>
	,	_detail::refer_multiplicative_group<W_data>
	,	typename occur::indent_s<W_data>::template funnel<>
	,	As...
	,	resource::biased<Ordinal_1>
	>;
	
	template <class S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;

	protected:
		using typename S_::T_self; friend T_self;
		using typename S_::U_head;

	public:
		using S_::S_;

	public:
		using S_::self;
		using S_::head;

		XTAL_DO4_(XTAL_OP0_(implicit) U_head(), {return head();})
		///\note\
		The above is defined in-case `refine_head` is bypassed...

		///\todo\
		...find a cleaner way to define the conversion, perhaps via `refer`?

		XTAL_DEF_(return,inline)
		XTAL_FN1 bias()
		XTAL_0EX_TO_(S_::template bias<U_data>())

	public:
		///\
		Access by dynamic index. \
		
		///\todo\
		Replace with accessor-decorator.

		XTAL_TO4_(XTAL_TN2 get(size_t i), head().get(i))

	public:
		///\
		Evaluation by succession. \
		
		XTAL_DEF_(return,inline)
		XTAL_GET ingress()
		XTAL_0EX
		{
			XTAL_IF0
			XTAL_0IF (1 == bias()) {return ++head();}
			XTAL_0IF_(else)        {return   head();}
		};
		template <class Y>
		XTAL_DEF_(return,inline)
		XTAL_SET egress(Y &&y)
		XTAL_0EX
		{
			XTAL_IF0
			XTAL_0IF (0 == bias()) {return (void) ++head(), XTAL_REF_(y);}
			XTAL_0IF_(else)        {return                  XTAL_REF_(y);}
		};
		template <auto ...Is> requires none_n<Is...>
		XTAL_TN2 functor()
		XTAL_0EX
		{
			///\todo\
			Override constructors to apply fractional `bias`. \
			
			if constexpr (resource::example_q<S_>) {
				auto const rate = S_::sample().rate();
				auto &phi = ingress();
				XTAL_IF0
				XTAL_0IF (N_data == 1) {
					//\
					return egress(bond::repack_f(phi(0)));
					return egress(phi(0));
				}
				XTAL_0IF (N_data == 2) {
					return egress(bond::repack_f(phi(0), phi(1)*(rate)));
				}
				XTAL_0IF_(else) {
					return egress(phi.template got<decltype(bond::repack_f)>()*S_data(rate));
				}
			}
			else {
				return egress(ingress());
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
