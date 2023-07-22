#pragma once
#include "./any.hpp"
#include "./seek.hpp"
#include "./compose.hpp"
#include "./collate.hpp"



XTAL_ENV_(push)
namespace xtal::common
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
Remixes the classes defined by `collate`, \
providing heterogeneous combinations of vectorized values. \


////////////////////////////////////////////////////////////////////////////////

template <class T>
concept collaged_p = requires ()
{
	typename T::collaged;
	requires constant_q<typename T::collaged>;
	requires (0 != T::collaged::value);
	
	typename T::template spool<unit_t>;
	requires iterated_q<typename T::template spool<unit_t>::type>;

};
template <class ...Ts>
concept collaged_q = (...and collaged_p<Ts>);


template <int ...Ns>
struct collage;

template <int ...Ns>
using collage_t = typename collage<Ns...>::type;

template <int N_size>
struct collage<N_size>
{
	using metatype = collate_t<N_size>;

	template <class S>
	class subtype: public S
	{
	public:
		using S::S;
		using collaged = constant_t<N_size>;

		///\
		Combines both `pulsar` and `phasor` from `collate`, \
		producing a discrete/continuous pair representing trigger/position, \
		and providing conversions to/from the initial value of `phase`. \
		
		template <class V>
		struct quasar
		{
			using _realized = realize<V>;
			using alpha_t = typename _realized::alpha_t;
			using delta_t = typename _realized::delta_t;
			
			using phase_t = typename metatype::template phasor_t<alpha_t>;
			using pulse_t = typename metatype::template pulsar_t<delta_t>;
			
			template <class T>
			using hemitype = typename _detail::epikind<T>::type;

			template <class T>
			class homotype: public hemitype<T>
			{
				friend T;
				using R_ = hemitype<T>;
			
				phase_t phase_m{};
				pulse_t pulse_m{};
			
			public:
				using R_::R_;
				using R_::self;
				using R_::twin;

				///\
				Trailing subsequence construction. \

				XTAL_CXN homotype(auto const &o1)
				XTAL_0EX
				XTAL_REQ requires ()
				{
					phase_t(o1.phase());
					pulse_t(o1.pulse());
				}
				:	phase_m(o1.phase())
				,	pulse_m(o1.pulse())
				{}
				XTAL_CXN homotype(auto &&o1)
				XTAL_0EX
				XTAL_REQ requires ()
				{
					phase_t(XTAL_MOV_(o1.phase()));
					pulse_t(XTAL_MOV_(o1.pulse()));
				}
				:	phase_m(XTAL_MOV_(o1.phase()))
				,	pulse_m(XTAL_MOV_(o1.pulse()))
				{}

				///\
				Primary value conversion. \
				
				XTAL_CON homotype(alpha_t o0)
				XTAL_0EX
				:	phase_m{o0 - _std::round(o0)}
				{}
				XTAL_TO4_(XTAL_OP1_(explicit) alpha_t(), phase(0))
				
				///\
				Accessories. \

				XTAL_TO4_(XTAL_FN2 phase(size_t i), phase().at_(i))
				XTAL_TO4_(XTAL_FN2 pulse(size_t i), pulse().at_(i))

				XTAL_FN2 phase() XTAL_0EX_( &) {return          (phase_m);}
				XTAL_FN2 phase() XTAL_0FX_( &) {return          (phase_m);}
				XTAL_FN2 phase() XTAL_0EX_(&&) {return XTAL_MOV_(phase_m);}
				XTAL_FN2 phase() XTAL_0FX_(&&) {return XTAL_MOV_(phase_m);}

				XTAL_FN2 pulse() XTAL_0EX_( &) {return          (pulse_m);}
				XTAL_FN2 pulse() XTAL_0FX_( &) {return          (pulse_m);}
				XTAL_FN2 pulse() XTAL_0EX_(&&) {return XTAL_MOV_(pulse_m);}
				XTAL_FN2 pulse() XTAL_0FX_(&&) {return XTAL_MOV_(pulse_m);}

				///\
				Phase-wrapping. \

				XTAL_FN1 reduce()
				XTAL_0EX
				{
					phase_m.reduce(); return self();
				}

				///\
				Synchronized finite differencing. \

				XTAL_OP1 ++ (int) XTAL_0EX {auto t = twin(); operator++(); return t;}
				XTAL_OP1 -- (int) XTAL_0EX {auto t = twin(); operator--(); return t;}
				XTAL_OP1 ++ ()
				XTAL_0EX
				{
					++pulse_m;
					++phase_m;
					return self();
				}
				XTAL_OP1 -- ()
				XTAL_0EX
				{
					--pulse_m;
					--phase_m;
					return self();
				}

			};
			using type = _detail::isotype<homotype>;
		};
		template <class V> using quasar_t = typename quasar<V>::type;

	};
	using type = subtype<unit_t>;
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
