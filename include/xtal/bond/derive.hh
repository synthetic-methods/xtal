#pragma once
#include "./any.hh"
#include "./compose.hh"





XTAL_ENV_(push)
namespace xtal::bond
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
Binds the derived `(?sub)?type`s with the CRTP-template `template <class T> class Y`. \

///\note\
May require `-Wsubobject-linkage` to be suppressed. \

template <         template <class> class Y>	struct   derive;
template <         template <class> class Y>	using    derive_t	=  typename derive<Y>::type;
template <class S, template <class> class Y>	using    derive_s	=  bond::compose_s<S, derive<Y>>;


////////////////////////////////////////////////////////////////////////////////

template <template <class> class Y>
struct derive
{
	template <class S>
	class subtype : public bond::compose_s<S, Y<subtype<S>>>
	{
		using S_ = bond::compose_s<S, Y<subtype<S>>>;
		
	public:
		using S_::S_;

	};
	class type : public Y<type>
	{
		using S_ = Y<type>;
		
	public:
		using S_::S_;

	};
};


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
