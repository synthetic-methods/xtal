#pragma once
#include "./any.hh"

#include "./trace.hh"
#include "../flow/assign.hh"




XTAL_ENV_(push)
namespace xtal::occur
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/*!
\brief
Encodes the triple `{enter,leave,cancel}` with the `sign_type` `{0, 1,-1}`,
analagous to `flux|fuse`'s `{changed,unchanged,unrecognized}`.

\details
Responds to `fuse<+1>` by interrogating the internal state without modification.
*/
template <class ..._s> struct   stage;
template <class ..._s> using    stage_t =        confined_t<stage< _s...>>;
template <class ..._s> concept  stage_q = bond::tag_outer_p<stage, _s...> ;


////////////////////////////////////////////////////////////////////////////////

template <typename ...As>
struct stage
{
	using innertype = signed;
	using superkind = bond::compose<bond::tag<stage>
	,	trace<1>
	,	As...
	,	_detail::refer_qualities     <innertype>
	,	_detail::refer_digital_group <innertype>
	,	defer<innertype>
	>;
	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind>;
		using T_ = typename S_::self_type;
	
	public:// CONSTRUCT
		using S_::S_;

	public:// OPERATE
		using S_::self;
		using S_::head;

	public:// TYPE

		template <class U>
		struct assignment
		{
			template <class R>
			class subtype : public bond::compose_s<R>
			{
				static_assert(cell::any_q<R>);
				using R_ = bond::compose_s<R>;
				
				XTAL_DEF_(set) K_size = 4;
				XTAL_DEF_(set) K_mask = K_size  - 1;
				XTAL_DEF_(set) K_fill = K_size >> 1;

				using U_value =  U;
				using U_table = _std::array<U, K_size>;
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
				template <signed N_ion> requires in_v<N_ion, -1>
				XTAL_DEF_(return,inline,let)
				flux(same_q<T_> auto &&s, auto &&...oo)
				noexcept -> signed
				{
					signed const  k = s.head();
					(void) R_::self().template flux<+1>(u_table[K_mask&k]);
					return R_::       template flux<N_ion>(XTAL_REF_(s), XTAL_REF_(oo)...);
				}
				template <signed N_ion> requires in_v<N_ion, +1>
				XTAL_DEF_(return,inline,let)
				flux(same_q<flow::assign_s<T_>> auto &&t, same_q<U_value> auto &&o, auto &&...oo)
				noexcept -> signed
				{
					auto   const &s = t.tail();
					signed const  k = s.head();
					if (K_fill == k) {u_table.fill        (o);}
					else             {u_table[K_mask&k] = (o);}
					return R_::template flux<N_ion>(XTAL_REF_(t), XTAL_REF_(o), XTAL_REF_(oo)...);
				}

			};
		};

	};
};


////////////////////////////////////////////////////////////////////////////////

XTAL_DEF_(let) stage_f = [] (auto &&o)
XTAL_0FN {
	if constexpr (stage_q<decltype(o)>)
		{return XTAL_REF_(o);} else {return stage_t<>{XTAL_REF_(o)};}
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
