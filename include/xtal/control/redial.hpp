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

	template <typename S>
	class subtype: public compose_s<S, subkind>
	{
		using S_ = compose_s<S, subkind>;
	
	public:
	//	using S_::S_;
			
		XTAL_CO0_(subtype);
		XTAL_CO4_(subtype);

		///\
		Constructs the `attach`ed `control` using its default, \
		before `forward`ing the arguments to `this`. \

		XTAL_CXN subtype(XTAL_DEF ...xs)
		XTAL_0EX
		:	S_(U(), XTAL_REF_(xs)...)
		{
		}

		XTAL_TO4_(XTAL_FN1 dial(XTAL_DEF... oo), S_::head(XTAL_REF_(oo)...))


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
