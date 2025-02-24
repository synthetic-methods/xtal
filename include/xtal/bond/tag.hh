#pragma once
#include "./any.hh"
#include "./tab.hh"
#include "./compose.hh"




XTAL_ENV_(push)
namespace xtal::bond
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <template <class ...> class Y>
struct tag
{
	using superkind = tab<tag<Y>>;

	template <class S>
	class subtype : public compose_s<S, superkind>
	{
		using S_ = compose_s<S, superkind>;
	
	public:
		using S_::S_;

		struct taboo
		:	S_::taboo
		{
			template <class ...Xs>
			using hypertype = Y<Xs...>;

		};

	};
};
template <class ..._s>
struct tagged
{
	template <class T>
	using subtype = typename T::taboo::template hypertype<_s...>;

};


template <class T, template <class ...> class ...Ys> concept          all_tags_q =          all_tabs_q<T, tag<Ys>...>;
template <class T, template <class ...> class ...Ys> concept          any_tags_q =          any_tabs_q<T, tag<Ys>...>;
template <class T, template <class ...> class ...Ys> concept array_or_any_tags_q = array_or_any_tabs_q<T, tag<Ys>...>;

template <template <class ...> class Y, class ...Ts> concept          all_tags_p =          all_tabs_p<tag<Y>, Ts...>;
template <template <class ...> class Y, class ...Ts> concept          any_tags_p =          any_tabs_p<tag<Y>, Ts...>;
template <template <class ...> class Y, class ...Ts> concept array_or_any_tags_p = array_or_any_tabs_p<tag<Y>, Ts...>;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
