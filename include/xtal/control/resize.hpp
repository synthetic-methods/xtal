#pragma once
#include "./anybody.hpp"






XTAL_ENV_(push)
namespace xtal::control
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class U=size_t>
struct resize
{
	using subkind = defer<U>;

	template <any_q S>
	class subtype: public compose_s<S, subkind>
	{
		using S_ = compose_s<S, subkind>;
	
	public:
		using S_::S_;
		using size_t = U;

		XTAL_TO4_(XTAL_FN2 size(XTAL_DEF... oo), S_::head(XTAL_REF_(oo)...))
		XTAL_TO4_(XTAL_FN2 empty(), 0 == size())

	};
};
template <iterated_q U>
struct resize<U>: resize<XTAL_TYP_(XTAL_VAL_(U).size())>
{
};
template <class U=size_t>
using resize_t = confined_t<resize<U>>;

XTAL_CN2 resize_f(XTAL_DEF w)
{
	using _computer = compute<XTAL_TYP_(w)>;
	return resize_t<typename _computer::sigma_t>(XTAL_REF_(w));
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
