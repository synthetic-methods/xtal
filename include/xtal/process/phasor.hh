#pragma once
#include "./any.hh"

#include "../algebra/phason.hh"
#include "../resource/example.hh"
#include "../resource/biased.hh"
#include "../occur/indent.hh"

XTAL_ENV_(push)
namespace xtal::process
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ..._s> XTAL_TYP phasor;
template <typename ..._s> XTAL_USE phasor_t = confined_t<phasor<_s...>>;
template <typename ..._s> XTAL_ASK phasor_q = bond::any_tag_p<phasor, _s...>;


////////////////////////////////////////////////////////////////////////////////
///\
Manages a truncated fixed-point unit differential like `phasor`, \
providing evaluation/update via succession/replacement. \

///\todo\
Accommodate `std::complex` `value_type`s? \

template <column_q A, typename ...As>
struct phasor<A, As...>
{
	using _op = algebra::_detail::circumscribe<A>;
	using coordinate_type = typename _op::coordinate_type;
	using inordinate_type = typename _op::inordinate_type;
	using   ordinate_type = typename _op::  ordinate_type;

	XTAL_SET N  = _std::extent_v<A>;

	using U_phason = algebra::phason_t<coordinate_type[N]>;
	using U_pulson = algebra::serial_t<inordinate_type[N]>;
	using U_series = algebra::series_t<coordinate_type[N]>;
	
	using semikind = bond::compose<void
	,	_detail::refer_multiplicative_group<U_phason>
	,	typename occur::indent_s<U_phason>::template funnel<>
	,	As...
	>;
	using superkind = bond::compose<bond::tag<phasor>
	,	semikind
	,	resource::biased<nominal_t<1>>
	>;
	template <any_q S>
	class subtype : public bond::compose_s<S, superkind>
	{
		using S_ = bond::compose_s<S, superkind>;
		using U_ = typename S_::head_type;

	public:// ACCESS
		using S_::S_;
		using S_::self;
		using S_::head;

		using algebra_t = U_phason;

		///\note\
		This is defined in-case `refine_head` is bypassed...

		///\todo\
		...find a cleaner way to define the conversion, perhaps via `refer`?

		XTAL_DO4_(XTAL_ION_(implicit) U_(), {return head();})
		
		XTAL_DEF_(return,inline,static)
		XTAL_LET bias()
		noexcept -> auto
		{
			return S_::template bias<coordinate_type>();
		}

		///\
		Access by dynamic index. \
		
		///\todo\
		Replace with accessor-decorator?

		XTAL_TO4_(XTAL_DEF_(return,inline) XTAL_RET let(size_type i), head().let(i))

	public:// EVALUATION
		///\todo\
		Use `resource::example` to manage downsampling \
		e.g. by integer multiplication followed by normalization. \

		///\
		Evaluation by (possibly indented) replacement then succession. \
		
		template <auto ...Is> requires none_n<Is...>
		XTAL_DEF_(return,inline)
		XTAL_LET method(subarray_q<N> auto &&a)
		noexcept -> decltype(auto)
		{
			(void) S_::influx(XTAL_REF_(a));
			return method();
		}

		///\
		Evaluation by uccession. \
		
		template <auto ...Is> requires none_n<Is...>
		XTAL_DEF_(return,inline)
		XTAL_LET method()
		noexcept -> decltype(auto)
		{
			///\todo\
			Override constructors to apply fractional `bias`. \
			
			if constexpr (resource::example_q<S_>) {
				auto const rate = S_::sample().rate();
				auto &phi = ingress();
				XTAL_IF0
				XTAL_0IF (N == 1) {
					//\
					return egress(bond::pack_f(phi(0)));
					return egress(phi(0));
				}
				XTAL_0IF (N == 2) {
					return egress(bond::pack_f(phi(0), phi(1)*(rate)));
				}
				XTAL_0IF_(else) {
					return egress(phi.template apply<XTAL_FUN_(bond::pack_f)>()*U_series(rate));
				}
			}
			else {
				return egress(ingress());
			}
		}

	protected:
		///\
		Evaluation by succession. \
		
		XTAL_DEF_(return,inline)
		XTAL_LET ingress()
		noexcept -> decltype(auto)
		{
			XTAL_IF0
			XTAL_0IF (1 == bias()) {return ++head();}
			XTAL_0IF_(else)        {return   head();}
		};
		template <class Y>
		XTAL_DEF_(return,inline)
		XTAL_LET egress(Y &&y)
		noexcept -> auto
		{
			XTAL_IF0
			XTAL_0IF (0 == bias()) {return (void) ++head(), XTAL_REF_(y);}
			XTAL_0IF_(else)        {return                  XTAL_REF_(y);}
		};
		
	};
	template <any_q S> requires phasor_q<bond::compose_s<S, semikind>>
	class subtype<S> : public bond::compose_s<S, semikind>
	{
		using S_ = bond::compose_s<S, semikind>;
		using U_ = typename S_::head_type;

	public:// ACCESS
		using S_::S_;
		using S_::self;
		using S_::head;

		using algebra_t = U_phason;

		///\note\
		This is defined in-case `refine_head` is bypassed...

		XTAL_DO4_(XTAL_ION_(implicit) U_(), {return head();})
		
		///\
		Access by dynamic index. \
		
		///\todo\
		Replace with accessor-decorator?

		XTAL_TO4_(XTAL_DEF_(return,inline) XTAL_RET let(size_type i), head().let(i))

	public:// REEVALUATION
		///\returns the current differential after scaling the incoming `phi` by `co`. \

		///\todo\
		Supply `precision` and/or `subdivision` `attach`ments? \

		template <int N_root=1>
		XTAL_DEF_(return,inline)
		XTAL_LET method(U_phason phi, coordinate_type co)
		noexcept -> auto
			requires is_q<U_phason, typename S_::template head_t<nominal_t<size_1>>>
		{
			static_assert(bond::dipack_q<U_phason>);

			auto &_phi = S_::template head<1>();
			auto &_psi = S_::template head<0>();

		//	Calculates the deviation of `phi[0]` w.r.t. phi[1], \
		//	using the difference in `phi[1]` to determine the threshold for reset. \

			auto  u_delta = _phi - phi; u_delta[0] += phi[1];
			auto &v_delta = reinterpret_cast<U_pulson const &>(u_delta);
			auto  n_delta = 1 + _op::bit_floor_f(_op::designed_f(v_delta[1]));
			auto  i_delta = condition_f<ordinate_type>(v_delta[0] >> n_delta);

			_phi = XTAL_MOV_(phi);

			phi *= _op::template root_f<N_root>(co);
			_psi[1]  = phi[1];
			_psi.operator++();
			_psi[0] &=       ~i_delta;
			_psi[0] |= phi[0]&i_delta;

			return _psi;
		}

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
