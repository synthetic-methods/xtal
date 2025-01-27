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

template <class T, template <class ...> class ...Ys> using       tagged_s =   tabbed_s<T, tag<Ys>...>;
template <class T, template <class ...> class ...Ys> concept     tagged_q =   tabbed_q<T, tag<Ys>...>;

template <class T, template <class ...> class ...Ys> concept        tag_q =      tab_q<T, tag<Ys>...>;
template <template <class ...> class Y, class ...Ts> concept        tag_p =      tab_p<tag<Y>, Ts...>;

template <class T, template <class ...> class ...Ys> concept   some_tag_q = some_tab_q<T, tag<Ys>...>;
template <template <class ...> class Y, class ...Ts> concept   some_tag_p = some_tab_p<tag<Y>, Ts...>;

template <class T, template <class ...> class ...Ys> concept  array_tag_q = some_tag_q<T, Ys...> and (...and (array_sized_q<T > or tag_q<T , Ys>));
template <template <class ...> class Y, class ...Ts> concept  array_tag_p = some_tag_p<Y, Ts...> and (...and (array_sized_q<Ts> or tag_q<Ts, Y >));


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
