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
struct hypertag
{
	template <class T>
	using subtype = typename T::taboo::template hypertype<_s...>;

};


template <class T, template <class ...> class ...Ys> concept        tag_q =      tab_q<T, tag<Ys>...>;
template <class T, template <class ...> class ...Ys> concept   some_tag_q = some_tab_q<T, tag<Ys>...>;
template <class T, template <class ...> class ...Ys> concept  array_tag_q = some_tab_q<T, tag<Ys>...> and (...and (array_shaped_q<T > or tag_q<T , Ys>));

template <template <class ...> class Y, class ...Ts> concept        tag_p =      tab_p<tag<Y>, Ts...>;
template <template <class ...> class Y, class ...Ts> concept   some_tag_p = some_tab_p<tag<Y>, Ts...>;
template <template <class ...> class Y, class ...Ts> concept  array_tag_p = some_tab_p<tag<Y>, Ts...> and (...and (array_shaped_q<Ts> or tag_q<Ts, Y >));


template <class T, template <class ...> class ...Ys> concept     tagged_q =                         tabbed_q<T, tag<Ys>...>;
template <class T, template <class ...> class ...Ys> concept   retagged_q = tag_q<T, Ys...> and not tabbed_q<T, tag<Ys>...>;

template <template <class ...> class Y, class ...Ts> concept     tagged_p =                         tabbed_p<tag<Y>, Ts...>;
template <template <class ...> class Y, class ...Ts> concept   retagged_p = tag_p<Y, Ts...> and not tabbed_p<tag<Y>, Ts...>;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
