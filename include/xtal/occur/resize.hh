#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::occur
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class U=size_t>
struct resize
{
	using subkind = defer<U>;

	template <any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;
	
	public:
		using S_::S_;
		using U_size = U;

		XTAL_TO4_(XTAL_TN2 size(auto &&...oo), S_::head(XTAL_REF_(oo)...))
		XTAL_TO4_(XTAL_TN2 empty(), 0 == size())

	};
};
template <iterated_q U>
struct resize<U> : resize<XTAL_TYP_(XTAL_VAL_(U).size())>
{
};
template <class U=size_t>
using resize_t = confined_t<resize<U>>;

XTAL_FN2 resize_f(auto &&w)
XTAL_0EX
{
	using re = bond::realize<XTAL_TYP_(w)>;
	return resize_t<typename re::sigma_t>(XTAL_REF_(w));
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
