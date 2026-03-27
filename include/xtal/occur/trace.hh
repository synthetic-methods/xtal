#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::occur
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/*!
\brief
Responds to `flux<+M_ion>` by interrogating the internal state without modification,
forcing update via `flux<-M_ion>` only.
*/
template <signed M_ion>
struct trace;


////////////////////////////////////////////////////////////////////////////////

template <signed M_ion>
struct trace
{
	template <class S>
	class subtype : public bond::compose_s<S>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S>;
		using T_ = typename S_::self_type;
	
	public:// CONSTRUCT
		using S_::S_;

	public:// TYPE

		template <extent_type N_mask=1>
		struct attach
		{
			using superkind = typename S_::template attach<N_mask>;
			
			template <flow::any_q R>
			class subtype : public bond::compose_s<R, superkind>
			{
				using R_ = bond::compose_s<R, superkind>;
			
			public:
				using R_::R_;

				template <signed N_ion>
				XTAL_DEF_(return,inline,let)
				fuse(auto &&o)
				noexcept -> signed
				{
					return R_::template fuse<N_ion>(XTAL_REF_(o));
				}
				template <signed N_ion>
				XTAL_DEF_(return,inline,let)
				fuse(same_q<T_> auto &&o)
				noexcept -> signed
				{
					XTAL_IF0
					XTAL_0IF (M_ion == N_ion) {return R_::             heading(XTAL_REF_(o));}
					XTAL_0IF (M_ion != N_ion) {return R_::template fuse<N_ion>(XTAL_REF_(o));}
				}

			};
		};

	};
};


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
