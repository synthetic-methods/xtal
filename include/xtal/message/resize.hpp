#pragma once
#include "./any.hpp"






XTAL_ENV_(push)
namespace xtal::message
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename U=size_t>
struct resize
{
	using subkind = defer<U>;

	template <any_q S>
	class subtype: public compose_s<S, subkind>
	{
		using co = compose_s<S, subkind>;
	
	public:
		using co::co;
		using size_t = U;

		XTAL_RN2_(XTAL_FN1 size(XTAL_DEF... oo), co::head(XTAL_REF_(oo)...))
		XTAL_RN2_(XTAL_FN2 empty(), 0 == size())

	};
};
template <iterated_q U>
struct resize<U>: resize<_v3::ranges::size_type_t<U>>
{
};
template <typename U=size_t>
using resize_t = confined_t<resize<U>>;

XTAL_FZ2 resize_f(XTAL_DEF w)
{
	using _realized = realize<XTAL_TYP_(w)>;
	return resize_t<typename _realized::sigma_t>(XTAL_REF_(w));
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
