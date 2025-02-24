#pragma once
#include "./any.hh"

#include "../flow/assign.hh"




XTAL_ENV_(push)
namespace xtal::occur
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\brief\
Represents the triple `{enter,leave,cancel}` with the `sign_type` `{0, 1,-1}`, \
cf. `*flow`'s `{changed,unchanged,unrecognized}`. \

///\note\
Not intended to be `attach`ed (except with `(?:ex|in)pect`), \
instead intercepted dynamically to interpret state. \

///\note\
Can be `attach`ed for immediate (de)allocation with `(?:ex|in)pect`. \

template <class ..._s> struct   stage;
template <class ..._s> using    stage_t =     confined_t<stage< _s...>>;
template <class ..._s> concept  stage_q = bond::all_tags_p<stage, _s...> ;


////////////////////////////////////////////////////////////////////////////////

template <typename ...As>
struct stage
{
	using superkind = bond::compose<bond::tag<stage>
	,	As...
	,	_detail::refer_equality<signed>
	,	_detail::refer_binary_logic<signed>
	,	defer<signed>
	>;
	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind>;
		using T_ = typename S_::self_type;
	
	public:// CONSTRUCT
		using S_::S_;

		template <class U>
		struct assignment
		{
			template <class R>
			class subtype : public bond::compose_s<R>
			{
				static_assert(cell::any_q<R>);
				using R_ = bond::compose_s<R>;
				
				using U_value = U;
				using U_table = atom::block_t<U[4]>;
				U_table u_table{};
				
			public:// CONSTRUCT
				using R_::R_;

				template <signed N_ion>
				XTAL_DEF_(return,inline,let)
				flux(auto &&...oo)
				noexcept -> signed
				{
					return R_::template flux<N_ion>(XTAL_REF_(oo)...);
				}
				template <signed N_ion> requires in_n<N_ion, -1>
				XTAL_DEF_(return,inline,let)
				flux(same_q<T_> auto &&s, auto &&...oo)
				noexcept -> signed
				{
					(void) R_::self().template flux<N_ion>(u_table[0b11U&s.head()]);
					return R_::       template flux<N_ion>(XTAL_REF_(s), XTAL_REF_(oo)...);
				}
				template <signed N_ion> requires in_n<N_ion, +1>
				XTAL_DEF_(return,inline,let)
				flux(same_q<flow::assign_s<T_>> auto &&t, same_q<U_value> auto &&o, auto &&...oo)
				noexcept -> signed
				{
					auto const &s = t.tail();
					auto const  k = s.head();
					if (k == 0b10) {
						u_table[0b00  ] = o;
						u_table[0b01  ] = o;
						u_table[0b10  ] = o;
						u_table[0b11  ] = o;
					}
					else {
						u_table[0b11&k] = o;
					}
					return R_::template flux<N_ion>(XTAL_REF_(t), XTAL_REF_(o), XTAL_REF_(oo)...);
				}

			};
		};

	};
};


////////////////////////////////////////////////////////////////////////////////

XTAL_DEF_(let) stage_f = [] XTAL_1FN_(call) (stage_t<>);


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
