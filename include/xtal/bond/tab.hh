#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::bond
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
///\
Tags `subtype` while preserving Standard Layout. \
Avoids the `sizeof` inflation that can occur with multiple-inheritance \
(e.g. frustrated Empty Base Optimization). \

template <class T> concept taboo_q = requires {typename T::taboo;};
template <class T> using   taboo_s =           typename T::taboo::supertype;
template <class T> using   taboo_t =           typename T::taboo::type;

template <class Y, class ...Ts>                              struct tab;//    : _std::conjunction<tab<Y, based_t<Ts>>...>;
template <class Y, class    T >                              struct tab<Y, T> : logical_t<0> {};
template <class Y, taboo_q  T > requires is_q<Y, taboo_t<T>> struct tab<Y, T> : logical_t<1> {};
template <class Y, taboo_q  T >                              struct tab<Y, T> : tab<Y, taboo_s<T>> {};

template <class Y, class ...Ts> concept tab_p = _std::conjunction_v<tab<Y, based_t<Ts>>...>;
template <class T, class ...Ys> concept tab_q = _std::conjunction_v<tab<Ys, based_t<T>>...>;

template <class Y>
struct tab<Y>
{
	template <class S>
	class subtype : public S
	{
	public:
		using S::S;
		
		struct taboo
		{
			using supertype = S;
			using      type = Y;

		};

	};
};



///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
