#pragma once
#include "./any.hh"

#include "../algebra/all.hh"
#include "../provision/example.hh"
#include "../provision/biased.hh"
#include "../occur/indent.hh"

XTAL_ENV_(push)
namespace xtal::process
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ..._s> struct   phasor;
template <typename ..._s> using    phasor_t = confined_t<phasor<_s...>>;
template <typename ..._s> concept  phasor_q = bond::tag_p<phasor, _s...>;


////////////////////////////////////////////////////////////////////////////////
///\
Manages a truncated fixed-point unit differential like `phasor`, \
providing evaluation/update via succession/replacement. \

///\todo\
Accommodate `std::complex` `value_type`s? \

template <vector_q A, typename ...As>
struct phasor<A, As...>
{
	using _op =   bond::operate<A>;
	using _ph = algebra::phason<A>;
	using coordinate_type = typename _ph::coordinate_type;
	using inordinate_type = typename _ph::inordinate_type;
	using   ordinate_type = typename _ph::  ordinate_type;

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
	,	provision::biased<constant_t<1>>
	>;
	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		static_assert(any_q<S>);
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

		XTAL_TO4_(XTAL_DEF_(implicit operator) U_(), head())
		
		XTAL_DEF_(short,static)
		XTAL_LET bias()
		noexcept -> auto
		{
			return S_::template bias<coordinate_type>();
		}

	public:// EVALUATION
		///\todo\
		Use `provision::example` to manage downsampling \
		e.g. by integer multiplication followed by normalization. \

		///\
		Evaluation by (possibly indented) replacement then succession. \
		
		template <auto ...Is> requires (0 == sizeof...(Is))
		XTAL_DEF_(short)
		XTAL_LET method(subarray_q<N> auto &&a)
		noexcept -> decltype(auto)
		{
			(void) S_::influx(XTAL_REF_(a));
			return method();
		}

		///\
		Evaluation by uccession. \
		
		template <auto ...Is> requires (0 == sizeof...(Is))
		XTAL_DEF_(short)
		XTAL_LET method()
		noexcept -> decltype(auto)
		{
			///\todo\
			Override constructors to apply fractional `bias`. \
			
			if constexpr (provision::example_q<S_>) {
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
		
		XTAL_DEF_(short)
		XTAL_LET ingress()
		noexcept -> decltype(auto)
		{
			XTAL_IF0
			XTAL_0IF (1 == bias()) {return ++head();}
			XTAL_0IF_(else)        {return   head();}
		};
		template <class Y>
		XTAL_DEF_(short)
		XTAL_LET egress(Y &&y)
		noexcept -> auto
		{
			XTAL_IF0
			XTAL_0IF (0 == bias()) {return (void) ++head(), XTAL_REF_(y);}
			XTAL_0IF_(else)        {return                  XTAL_REF_(y);}
		};
		
	};
	template <class S> requires phasor_q<bond::compose_s<S, semikind>>
	class subtype<S> : public bond::compose_s<S, semikind>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, semikind>;
		using U_ = typename S_::head_type;

	public:// ACCESS
		using S_::S_;
		using S_::self;
		using S_::head;

		using algebra_t = U_phason;

		///\note\
		This is defined in-case `refine_head` is bypassed...

		XTAL_TO4_(XTAL_DEF_(implicit operator) U_(), head())
		
	public:// REEVALUATION
		///\returns the current differential after scaling the incoming `phi` by `co`. \

		///\todo\
		Supply `precision` and/or `subdivision` `attach`ments? \

		template <int N_root=1>
		XTAL_DEF_(long)
		XTAL_LET method(U_phason phi, coordinate_type co)
		noexcept -> auto
			requires same_q<U_phason, typename S_::template head_t<constant_t<size_1>>>
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
