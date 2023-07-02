#pragma once
#include "./any.hpp"






XTAL_ENV_(push)
namespace xtal::control
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <typename U>
struct redial
{
	using subkind = defer<U>;

	template <any_p S>
	class subtype: public compose_s<S, subkind>
	{
		using S_ = compose_s<S, subkind>;
	
	public:
		using S_::S_;
		using dial_t = U;
			
		XTAL_DO4_(XTAL_FN1 dial(XTAL_DEF... oo), S_::head(XTAL_REF_(oo)...))

	};
};
template <typename U, typename ...As>
using redial_t = confined_t<redial<U>, As...>;

template <typename T>
concept redial_p = requires (T t) {{t.dial()} -> is_q<typename T::dial_t>;};

template <typename ...Ts>
concept redial_q = conjunct_q<redial_p<Ts>...>;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
