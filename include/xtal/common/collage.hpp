#pragma once
#include "./any.hpp"
#include "./seek.hpp"
#include "./collate.hpp"
#include "./realize.hpp"



XTAL_ENV_(push)
namespace xtal::common
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ...> XTAL_NYM collaged;
template <class  ...Ts> XTAL_ASK collaged_q = tag_p<collaged, Ts...>;


////////////////////////////////////////////////////////////////////////////////
///\
Remixes the classes defined by `collate`, \
providing heterogeneous combinations of vectorized values. \

template <int ...Ns> XTAL_NYM collage;
template <int ...Ns> XTAL_USE collage_t = typename collage<Ns...>::type;

template <int N_size>
struct collage<N_size>
{
	using  metatype = collate_t<N_size>;
	using orthotype = collate_t<N_size - (0 < N_size)>;

	using subkind = tag<collaged>;

	template <class S>
	class subtype: public compose_s<S, subkind>
	{
		using S_ = compose_s<S, subkind>;

	public:
		using S_::S_;
		using collaged = integer_t<N_size>;

		///\
		Combines both `phasor` and `pulsar` from `collate`, \
		producing a discrete/continuous pair representing e.g. \
		`{{phi, omega}, {iota, gamma}}` if `N_size == 2`. \
		
		///\note\
		Provides explicit/implicit conversions to/from the head `phase`. \
		
		template <class V>
		struct quasar
		{
			using _realized = realize<V>;
			using phase_u = typename _realized::alpha_t;
			using pulse_u = typename _realized::delta_t;
			
			using phase_t = typename  metatype::template phasor_t<phase_u>;
			using pulse_t = typename  metatype::template pulsar_t<pulse_u>;
			
			using phase_s = typename orthotype::template phasor_t<phase_u>;
			using pulse_s = typename orthotype::template pulsar_t<pulse_u>;
			
			template <class T>
			XTAL_LET ortho_v = requires (T t)
			{
				{t.phase()} -> is_q<phase_s>;
				{t.pulse()} -> is_q<pulse_s>;
			};
			
			template <class T>
			using hemitype = typename define<T>::type;

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

				template <typename O> requires (ortho_v<O>)
				XTAL_CXN homotype(O const &o1)
				XTAL_0EX
				:	phase_m(o1.phase())
				,	pulse_m(o1.pulse())
				{}
				template <typename O> requires (ortho_v<O>)
				XTAL_CXN homotype(O &&o1)
				XTAL_0EX
				:	phase_m(XTAL_MOV_(o1.phase()))
				,	pulse_m(XTAL_MOV_(o1.pulse()))
				{}

				///\
				Primary value conversion. \
				
				XTAL_CON homotype(phase_u p0, pulse_u q0=0)
				XTAL_0EX
				:	phase_m{p0 - _std::round(p0)}
				,	pulse_m{q0}
				{}
				XTAL_TO4_(XTAL_OP0_(implicit) phase_t(), phase())
				XTAL_TO4_(XTAL_OP0_(implicit) pulse_t(), pulse())
				
				XTAL_TO4_(XTAL_OP1_(explicit) phase_u(), phase(0))
				XTAL_TO4_(XTAL_OP1_(explicit) pulse_u(), pulse(0))
				
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
